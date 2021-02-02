#pragma once

#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"

#include <functional>
#include <string_view>
#include <utility>
#include <variant>

namespace Pargon
{
	class BlueprintSerializer
	{
	public:
		BlueprintSerializer(BlueprintReader& reader);
		BlueprintSerializer(BlueprintWriter& writer);
	
		template<typename T> void Serialize(T&& value);

		void SerializeBoolean(bool& value);
		void SerializeInteger(long long& value);
		void SerializeFloatingPoint(double& value);
		void SerializeString(std::string& value);

		auto MoveDown(int index) -> bool;
		auto MoveDown(std::string_view name) -> bool;
		void MoveUp();
	
	private:
		using Variant = std::variant<
			std::reference_wrapper<BlueprintReader>,
			std::reference_wrapper<BlueprintWriter>
		>;
	
		Variant _serializer;
	};
}

inline
Pargon::BlueprintSerializer::BlueprintSerializer(BlueprintReader& reader) :
	_serializer(reader)
{
}

inline
Pargon::BlueprintSerializer::BlueprintSerializer(BlueprintWriter& writer) :
	_serializer(writer)
{
}

template<typename T>
void Pargon::BlueprintSerializer::Serialize(T&& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().Serialize(std::forward<T>(value));
	}, _serializer);
}

inline
void Pargon::BlueprintSerializer::SerializeBoolean(bool& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().SerializeBoolean(value);
	}, _serializer);
}

inline
void Pargon::BlueprintSerializer::SerializeInteger(long long& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().Serialize(value);
	}, _serializer);
}

inline
void Pargon::BlueprintSerializer::SerializeFloatingPoint(double& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().Serialize(value);
	}, _serializer);
}

inline
void Pargon::BlueprintSerializer::SerializeString(std::string& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().Serialize(value);
	}, _serializer);
}

inline
auto Pargon::BlueprintSerializer::MoveDown(int index) -> bool
{
	std::visit([&](auto&& variant)
	{
		variant.get().MoveDown(index);
	}, _serializer);
}

inline
auto Pargon::BlueprintSerializer::MoveDown(std::string_view name) -> bool
{
	std::visit([&](auto&& variant)
	{
		variant.get().MoveDown(name);
	}, _serializer);
}

inline
void Pargon::BlueprintSerializer::MoveUp()
{
	std::visit([&](auto&& variant)
	{
		variant.get().MoveUp();
	}, _serializer);
}
