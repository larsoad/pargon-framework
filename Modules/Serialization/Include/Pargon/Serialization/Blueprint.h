#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Pargon
{
	enum class BlueprintType
	{
		Invalid,
		Null,
		Boolean,
		Integer,
		FloatingPoint,
		String,
		List,
		Map
	};

	class Blueprint
	{
	public:
		using Invalid = struct {};
		using Null = struct {};
		using Boolean = bool;
		using Integer = long long;
		using FloatingPoint = double;
		using String = std::string;
		using List = std::vector<Blueprint>;
		using Map = std::unordered_map<std::string, Blueprint>;

		Blueprint() = default;
		Blueprint(const Blueprint& copy);
		~Blueprint();

		auto operator=(const Blueprint& copy) -> Blueprint&;

		auto Type() const -> BlueprintType;
		auto IsInvalid() const -> bool;
		auto IsNull() const -> bool;
		auto IsBoolean() const -> bool;
		auto IsInteger() const -> bool;
		auto IsFloatingPoint() const -> bool;
		auto IsString() const -> bool;
		auto IsList() const -> bool;
		auto IsMap() const -> bool;

		auto AsBoolean() const -> bool;
		auto AsInteger() const -> long long;
		auto AsFloatingPoint() const -> double;
		auto AsString() const -> const String*;
		auto AsList() const -> const List*;
		auto AsMap() const -> const Map*;

		auto AsString() -> String*;
		auto AsList() -> List*;
		auto AsMap() -> Map*;

		auto AsStringView() const -> std::string_view;

		void SetToInvalid();
		void SetToNull();
		void SetToBoolean(Boolean value);
		void SetToInteger(Integer value);
		void SetToFloatingPoint(FloatingPoint value);
		void SetToString(std::string_view value);
		auto SetToString() -> String&;
		auto SetToList() -> List&;
		auto SetToMap() -> Map&;

	private:
		using Storage = std::aligned_union_t<0, Invalid, Null, Boolean, Integer, FloatingPoint, String, List, Map>;

		BlueprintType _type = BlueprintType::Invalid;
		Storage _value;
	};
}

inline
auto Pargon::Blueprint::Type() const -> BlueprintType
{
	return _type;
}

inline
auto Pargon::Blueprint::IsInvalid() const -> bool
{
	return _type == BlueprintType::Invalid;
}

inline
auto Pargon::Blueprint::IsNull() const -> bool
{
	return _type == BlueprintType::Null;
}

inline
auto Pargon::Blueprint::IsBoolean() const -> bool
{
	return _type == BlueprintType::Boolean;
}

inline
auto Pargon::Blueprint::IsInteger() const -> bool
{
	return _type == BlueprintType::Integer;
}

inline
auto Pargon::Blueprint::IsFloatingPoint() const -> bool
{
	return _type == BlueprintType::FloatingPoint;
}

inline
auto Pargon::Blueprint::IsString() const -> bool
{
	return _type == BlueprintType::String;
}

inline
auto Pargon::Blueprint::IsList() const -> bool
{
	return _type == BlueprintType::List;
}

inline
auto Pargon::Blueprint::IsMap() const -> bool
{
	return _type == BlueprintType::Map;
}

inline
auto Pargon::Blueprint::AsBoolean() const -> Boolean
{
	return IsBoolean() ? *reinterpret_cast<const Boolean*>(&_value) : false;
}

inline
auto Pargon::Blueprint::AsInteger() const -> Integer
{
	return IsInteger() ? *reinterpret_cast<const Integer*>(&_value) : 0;
}

inline
auto Pargon::Blueprint::AsFloatingPoint() const -> FloatingPoint
{
	return IsFloatingPoint() ? *reinterpret_cast<const FloatingPoint*>(&_value) : 0.0;
}

inline
auto Pargon::Blueprint::AsString() const -> const String*
{
	return IsString() ? reinterpret_cast<const String*>(&_value) : nullptr;
}

inline
auto Pargon::Blueprint::AsList() const -> const List*
{
	return IsList() ? reinterpret_cast<const List*>(&_value) : nullptr;
}

inline
auto Pargon::Blueprint::AsMap() const -> const Map*
{
	return IsMap() ? reinterpret_cast<const Map*>(&_value) : nullptr;
}

inline
auto Pargon::Blueprint::AsString() -> String*
{
	return IsString() ? reinterpret_cast<String*>(&_value) : nullptr;
}

inline
auto Pargon::Blueprint::AsList() -> List*
{
	return IsList() ? reinterpret_cast<List*>(&_value) : nullptr;
}

inline
auto Pargon::Blueprint::AsMap() -> Map*
{
	return IsMap() ? reinterpret_cast<Map*>(&_value) : nullptr;
}

inline
auto Pargon::Blueprint::AsStringView() const -> std::string_view
{
	return IsString() ? *reinterpret_cast<const String*>(&_value) : std::string_view();
}
