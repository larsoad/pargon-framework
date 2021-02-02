#include "Pargon/Serialization/BlueprintReader.h"

using namespace Pargon;

BlueprintReader::BlueprintReader(const Blueprint& blueprint) :
	_current(std::addressof(blueprint)),
	_currentIndex(0u)
{
}

auto BlueprintReader::ReadBoolean() -> bool
{
	return _current->AsBoolean();
}

auto BlueprintReader::ReadInteger() -> long long
{
	return _current->AsInteger();
}

auto BlueprintReader::ReadFloatingPoint() -> double
{
	return _current->AsFloatingPoint();
}

auto BlueprintReader::ReadString() -> std::string_view
{
	return _current->AsStringView();
}

auto BlueprintReader::MoveDown(int index) -> bool
{
	auto array = _current->AsList();

	if (array == nullptr || array->empty() || index >= array->size())
		return false;

	_tree.push_back({ _current, _currentIndex });
	_current = std::addressof(array->at(index));
	_currentIndex = 0u;

	return true;
}

auto BlueprintReader::MoveDown(std::string_view name) -> bool
{
	auto object = _current->AsMap();

	if (object == nullptr || object->empty())
		return false;

	auto location = object->find(std::string(name)); // PENDING: C++20 has heterogenous lookup.

	if (location == object->end())
		return false;

	_tree.push_back({ _current, _currentIndex });
	_current = std::addressof(location->second);
	_currentIndex = 0u;
	
	return true;
}

void BlueprintReader::MoveUp()
{
	auto parent = _tree.back();

	_current = parent.Node;
	_currentIndex = parent.Index;

	_tree.pop_back();
}
