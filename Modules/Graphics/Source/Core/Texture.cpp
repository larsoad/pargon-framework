#include "Pargon/Debugging.h"
#include "Pargon/Files/File.h"
#include "Pargon/Graphics/GraphicsDevice.h"
#include "Pargon/Graphics/Texture.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/StringReader.h"
#include "Pargon/Serialization/StringWriter.h"

#include <png.h>

using namespace Pargon;

void TextureLoadResult::WriteResult(Log& log)
{
	if (Success)
	{
		//Log::Write("successfully loaded {}", Identifier);
	}
	else
	{
		//Log::Write("failed to load {}", Identifier);

		//for (auto& error : Errors)
		//	Log::Write(" - {}", error);
	}
}

auto Texture::Reset(const File& file) -> TextureLoadResult
{
	assert(IsLocked());

	auto contents = file.ReadData();

	if (!contents.Exists)
		return { false, file.Path(), { "file could not be read"_s } };

	return Reset(contents.Data, file.Path());
}

auto Texture::Reset(BufferView data, StringView identifier) -> TextureLoadResult
{
	assert(IsLocked());

	png_image png;
	memset(&png, 0, sizeof(png));
	png.version = PNG_IMAGE_VERSION;

	if (!png_image_begin_read_from_memory(&png, data.begin(), data.Size()))
		return { false, identifier, { "data is not a png"_s } };

	if (auto result = Reset({ static_cast<unsigned int>(png.width), static_cast<unsigned int>(png.height) }, TextureFormat::ColorBuffer4x8, identifier); !result.Success)
		return result;

	auto reservation = Reserve({ 0, 0 }, _size);

	png.format = PNG_FORMAT_RGBA;
	if (!png_image_finish_read(&png, NULL, reservation.Data.begin(), reservation.Pitch, NULL))
		return { false, identifier, { "failed to read the png data"_s } };

	return { true, identifier, {} };
}

namespace
{
	auto GetDepth(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::ColorBuffer4x8: return 4;
			case TextureFormat::ColorTarget4x8: return 4;
			case TextureFormat::DepthStencilTarget24_8: return 4;
			case TextureFormat::Unknown: return 0;
		}

		return 0;
	}
}

auto Texture::Reset(TextureSize size, TextureFormat format, StringView identifier) -> TextureLoadResult
{
	assert(IsLocked());

	_size = size;
	_depth = GetDepth(format);
	_format = format;
	_identifier = identifier;
	_reservations.Clear();
	_names.Clear();

	return { true, identifier, {} };
}

auto Texture::Reserve(TextureLocation location, TextureSize size) -> TextureReservation
{
	auto x = location.X;
	auto y = location.Y;
	auto width = size.Width == TextureSize::FullWidth ? _size.Width - location.X : size.Width;
	auto height = size.Height == TextureSize::FullHeight ? _size.Height - location.Y : size.Height;

	assert(IsLocked());
	assert(x + width <= _size.Width && y + height <= _size.Height);

	for (auto& reservation : _reservations)
	{
		auto right = reservation.Location.X + reservation.Size.Width;
		auto bottom = reservation.Location.Y + reservation.Size.Height;

		if (x >= reservation.Location.X && y >= reservation.Location.Y && x + width <= right && y + height <= bottom)
		{
			auto xDifference = x - reservation.Location.X;
			auto yDifference = y - reservation.Location.Y;
			auto data = reservation.Data.GetReference(yDifference * reservation.Pitch + xDifference * _depth, height * reservation.Pitch);

			return { { x, y }, { width, height }, reservation.Pitch, data };
		}
	}

	auto& reservation = _reservations.Increment();
	reservation.Location = { x, y };
	reservation.Size = { width, height };
	reservation.Pitch = width * _depth;
	reservation.Data.Reserve(width * height * _depth);

	return { reservation.Location, reservation.Size, reservation.Pitch, reservation.Data };
}

void Texture::SetSampleCount(int count)
{
	assert(IsLocked());
	assert(_format == TextureFormat::ColorTarget4x8 || _format == TextureFormat::DepthStencilTarget24_8);

	_sampleCount = count; // TODO: clamp to valid counts
}

auto Texture::GetCoordinates(TextureLocation location, TextureSize size) const -> TextureCoordinates
{
	auto w = 1.0f / _size.Width;
	auto h = 1.0f / _size.Height;
	auto u = location.X * w;
	auto v = location.Y * h;

	return { u, v, u + size.Width * w, v + size.Height * h };
}

void Texture::Clear()
{
	_reservations.Clear();
}
