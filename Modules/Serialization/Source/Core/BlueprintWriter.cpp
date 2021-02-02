#include "Pargon/Serialization/BlueprintWriter.h"

using namespace Pargon;

void BlueprintWriter::WriteBoolean(bool value)
{
	_current->SetToBoolean(value);
}

void BlueprintWriter::WriteInteger(long long value)
{
	_current->SetToInteger(value);
}

void BlueprintWriter::WriteFloatingPoint(double value)
{
	_current->SetToFloatingPoint(value);
}

void BlueprintWriter::WriteString(std::string_view value)
{
	_current->SetToString(value);
}

auto BlueprintWriter::MoveDown(int index) -> bool
{
	if (!_current->IsList())
		_current->SetToList();

	auto list = _current->AsList();

	while (list->size() <= index)
		list->emplace_back();

	auto& child = list->at(index);

	_tree.push_back({ _current, _currentIndex });
	_current = std::addressof(child);
	_currentIndex = 0u;

	return true;
}

auto BlueprintWriter::MoveDown(std::string_view name) -> bool
{
	if (!_current->IsMap())
		_current->SetToMap();

	auto object = _current->AsMap();
	auto location = object->emplace(std::string(name), Blueprint{}).first;

	_tree.push_back({ _current, _currentIndex });
	_current = std::addressof(location->second);
	_currentIndex = 0u;

	return true;
}

void BlueprintWriter::MoveUp()
{
	auto parent = _tree.back();

	_current = parent.Node;
	_currentIndex = parent.Index;

	_tree.pop_back();
}
