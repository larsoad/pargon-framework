#pragma once

namespace Pargon
{
	class BufferReader;
	class BufferWriter;
	class ColorHdr;
	class StringReader;
	class StringView;
	class StringWriter;

	class Color
	{
	public:
		uint8_t R;
		uint8_t G;
		uint8_t B;
		uint8_t A;

		auto AsHdr() const -> ColorHdr;
		auto AsHex() const -> uint32_t;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);

		auto operator==(Color other) const -> bool;
		auto operator!=(Color other) const -> bool;
	};


	class ColorHdr
	{
	public:
		ColorHdr() = default;
		constexpr ColorHdr(float r, float g, float b, float a);
		constexpr ColorHdr(Color color, float intensity);

		float R;
		float G;
		float B;
		float A;

		auto Clamped() const -> Color;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};

	constexpr
	auto operator""_rgb(unsigned long long hex) -> Color
	{
		return {
			static_cast<unsigned char>((hex >> 16) & 0xFF),
			static_cast<unsigned char>((hex >> 8) & 0xFF),
			static_cast<unsigned char>(hex & 0xFF),
			static_cast<unsigned char>(0xFF)
		};
	}

	constexpr
	auto operator""_rgba(unsigned long long hex) -> Color
	{
		return {
			static_cast<unsigned char>((hex >> 24) & 0xFF),
			static_cast<unsigned char>((hex >> 16) & 0xFF),
			static_cast<unsigned char>((hex >> 8) & 0xFF),
			static_cast<unsigned char>(hex & 0xFF)
		};
	}

	constexpr Color White = 0xFFFFFF_rgb;
	constexpr Color Black = 0x000000_rgb;
	constexpr Color Red = 0xFF0000_rgb;
	constexpr Color Green = 0x00FF00_rgb;
	constexpr Color Blue = 0x0000FF_rgb;
	constexpr Color Yellow = 0xFFFF00_rgb;
	constexpr Color Purple = 0xFF00FF_rgb;
	constexpr Color Turquoise = 0x00FFFF_rgb;
	constexpr Color Grey = 0x808080_rgb;
	constexpr Color Transparent = 0x00000000_rgba;
	constexpr Color TransparentWhite = 0xFFFFFF00_rgba;
}

inline
auto Pargon::Color::AsHdr() const -> ColorHdr
{
	return ColorHdr(*this, 1.0f);
}

inline
auto Pargon::Color::AsHex() const -> uint32_t
{
	return uint32_t(R << 24) | (G << 16) | (B << 8) | A;
}

inline
auto Pargon::Color::operator==(Color other) const -> bool
{
	return R == other.R
		&& G == other.G
		&& B == other.B
		&& A == other.A;
}

inline
auto Pargon::Color::operator!=(Color other) const -> bool
{
	return R != other.R
		|| G != other.G
		|| B != other.B
		|| A != other.A;
}

constexpr
Pargon::ColorHdr::ColorHdr(float r, float g, float b, float a) :
	R(r),
	G(g),
	B(b),
	A(a)
{
}

constexpr
Pargon::ColorHdr::ColorHdr(Color color, float intensity) :
	R(color.R / 255.0f * intensity),
	G(color.G / 255.0f * intensity),
	B(color.B / 255.0f * intensity),
	A(color.A / 255.0f * intensity)
{
}
