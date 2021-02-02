#pragma once

#include <exception>

namespace Pargon
{
	template<typename T> struct Serializer;

	class SerializerException : public std::exception
	{
	public:
		auto what() const noexcept -> const char* override;
	};
}

inline
auto Pargon::SerializerException::what() const noexcept -> const char*
{
	return "PSSE";
}
