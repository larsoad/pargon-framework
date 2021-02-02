#pragma once

#include "Pargon/Debugging.h"
#include "Pargon/Containers/Array.h"
#include "Pargon/Containers/Buffer.h"
#include "Pargon/Containers/List.h"
#include "Pargon/Containers/Map.h"
#include "Pargon/Containers/String.h"
#include "Pargon/Files/File.h"
#include "Pargon/Graphics/GraphicsResource.h"
#include "Pargon/Math/Vector.h"

#include <memory>

namespace Pargon
{
	class Texture;

	using TextureId = GraphicsId<Texture>;
	using TextureHandle = GraphicsHandle<Texture>;

	enum class TextureFormat
	{
		Unknown,
		ColorBuffer4x8,
		ColorTarget4x8,
		DepthStencilTarget24_8
	};

	struct TextureLocation
	{
		static constexpr auto Invalid() -> TextureLocation;

		unsigned int X;
		unsigned int Y;
	};

	struct TextureSize
	{
		static constexpr auto FullWidth = std::numeric_limits<unsigned int>::max();
		static constexpr auto FullHeight = std::numeric_limits<unsigned int>::max();

		static constexpr auto Full() -> TextureSize;
		static constexpr auto Invalid() -> TextureSize;

		unsigned int Width;
		unsigned int Height;
	};

	struct TextureCoordinates
	{
		float U1;
		float V1;
		float U2;
		float V2;
	};

	struct TextureReservation
	{
		TextureLocation Location;
		TextureSize Size;
		unsigned int Pitch;

		BufferReference Data;
	};

	struct TextureRegionId
	{
	public:
		TextureRegionId();

		auto IsAssigned() const -> bool;

	private:
		friend class Texture;

		TextureRegionId(int id);

		int _id;
	};

	struct TextureLoadResult
	{
		bool Success;
		String Identifier;
		List<String> Errors;

		void WriteResult(Log& log);
	};

	class Texture : public GraphicsResource<Texture>
	{
	public:
		auto Size() const -> TextureSize;
		auto Depth() const -> unsigned int;
		auto Format() const -> TextureFormat;
		auto SampleCount() const -> int;
		auto Identifier() const -> StringView;
		auto Reservations() const -> List<TextureReservation>;

		auto Reset(const File& file) -> TextureLoadResult;
		auto Reset(BufferView data, StringView identifier) -> TextureLoadResult;
		auto Reset(TextureSize size, TextureFormat format, StringView identifier) -> TextureLoadResult;
		auto Reserve(TextureLocation location, TextureSize size) -> TextureReservation;

		void SetSampleCount(int count);

		auto GetCoordinates(TextureLocation location, TextureSize size) const -> TextureCoordinates;

	protected:
		void Clear() override;

	private:
		friend class GraphicsDevice;

		struct Reservation
		{
			TextureLocation Location;
			TextureSize Size;
			unsigned int Pitch;

			Buffer Data;
		};

		using GraphicsResource<Texture>::GraphicsResource;

		TextureSize _size = { 0, 0 };
		unsigned int _depth = 0;
		TextureFormat _format = TextureFormat::Unknown;
		int _sampleCount = 1;

		String _identifier;

		List<Reservation> _reservations;
		Map<String, int> _names;
	};
}

constexpr
auto Pargon::TextureLocation::Invalid() -> TextureLocation
{
	constexpr auto invalid = std::numeric_limits<unsigned int>::max();
	return { invalid, invalid };
}

constexpr
auto Pargon::TextureSize::Full() -> TextureSize
{
	return { FullWidth, FullHeight };
}

constexpr
auto Pargon::TextureSize::Invalid() -> TextureSize
{
	return { 0, 0 };
}

inline
Pargon::TextureRegionId::TextureRegionId() :
	_id(-1)
{
}

inline
auto Pargon::TextureRegionId::IsAssigned() const -> bool
{
	return _id >= 0;
}

inline
Pargon::TextureRegionId::TextureRegionId(int id) :
	_id(id)
{
}

inline
auto Pargon::Texture::Size() const -> TextureSize
{
	return _size;
}

inline
auto Pargon::Texture::Depth() const -> unsigned int
{
	return _depth;
}

inline
auto Pargon::Texture::Format() const -> TextureFormat
{
	return _format;
}

inline
auto Pargon::Texture::SampleCount() const -> int
{
	return _sampleCount;
}

inline
auto Pargon::Texture::Identifier() const -> StringView
{
	return _identifier;
}

inline
auto Pargon::Texture::Reservations() const -> List<TextureReservation>
{
	List<TextureReservation> reservations;

	for (auto& reservation : _reservations)
		reservations.Add({ reservation.Location, reservation.Size, reservation.Pitch, reservation.Data });

	return reservations;
}
