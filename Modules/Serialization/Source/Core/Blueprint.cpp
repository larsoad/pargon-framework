#include "Pargon/Serialization/Blueprint.h"

using namespace Pargon;

namespace
{
	template<typename T, class... Args>
	auto Construct(T* storage, Args&&... args) -> T* // PENDING: Use construct_at in c++20.
	{
		return new (storage) T(std::forward<Args>(args)...);
	}

	void Change(void* storage, BlueprintType& from, BlueprintType to)
	{
		if (from == BlueprintType::String)
			std::destroy_at(reinterpret_cast<Blueprint::String*>(storage));
		else if (from == BlueprintType::List)
			std::destroy_at(reinterpret_cast<Blueprint::List*>(storage));
		else if (from == BlueprintType::Map)
			std::destroy_at(reinterpret_cast<Blueprint::Map*>(storage));

		from = to;
	}
}

Blueprint::Blueprint(const Blueprint& copy)
{
	if (copy._type == BlueprintType::String)
	{
		SetToString(copy.AsStringView());
	}
	else if (copy._type == BlueprintType::List)
	{
		SetToList() = *copy.AsList();
	}
	else if (copy._type == BlueprintType::Map)
	{
		SetToMap() = *copy.AsMap();
	}
	else
	{
		_type = copy._type;
		_value = copy._value;
	}
}

Blueprint::~Blueprint()
{
	Change(std::addressof(_value), _type, BlueprintType::Invalid);
}

auto Blueprint::operator=(const Blueprint& copy) -> Blueprint&
{
	if (copy._type == BlueprintType::String)
	{
		SetToString(copy.AsStringView());
	}
	else if (copy._type == BlueprintType::List)
	{
		SetToList() = *copy.AsList();
	}
	else if (copy._type == BlueprintType::Map)
	{
		SetToMap() = *copy.AsMap();
	}
	else
	{
		_type = copy._type;
		_value = copy._value;
	}

	return *this;
}

void Blueprint::SetToInvalid()
{
	Change(std::addressof(_value), _type, BlueprintType::Invalid);
}

void Blueprint::SetToNull()
{
	Change(std::addressof(_value), _type, BlueprintType::Null);
}

void Blueprint::SetToBoolean(Boolean value)
{
	Change(std::addressof(_value), _type, BlueprintType::Boolean);
	*reinterpret_cast<Boolean*>(std::addressof(_value)) = value;
}

void Blueprint::SetToInteger(Integer value)
{
	Change(std::addressof(_value), _type, BlueprintType::Integer);
	*reinterpret_cast<Integer*>(std::addressof(_value)) = value;
}

void Blueprint::SetToFloatingPoint(FloatingPoint value)
{
	Change(std::addressof(_value), _type, BlueprintType::FloatingPoint);
	*reinterpret_cast<FloatingPoint*>(std::addressof(_value)) = value;
}

void Blueprint::SetToString(std::string_view value)
{
	Change(std::addressof(_value), _type, BlueprintType::String);
	Construct(reinterpret_cast<String*>(std::addressof(_value)), value);
}

auto Blueprint::SetToString() -> String&
{
	Change(std::addressof(_value), _type, BlueprintType::String);
	return *Construct(reinterpret_cast<String*>(std::addressof(_value)));
}

auto Blueprint::SetToList() -> List&
{
	Change(std::addressof(_value), _type, BlueprintType::List);
	return *Construct(reinterpret_cast<List*>(std::addressof(_value)));
}

auto Blueprint::SetToMap() -> Map&
{
	Change(std::addressof(_value), _type, BlueprintType::Map);
	return *Construct(reinterpret_cast<Map*>(std::addressof(_value)));
}
