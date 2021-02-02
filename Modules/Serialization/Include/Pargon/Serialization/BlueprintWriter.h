#pragma once

#include "Pargon/Serialization/Blueprint.h"
#include "Pargon/Serialization/Serializer.h"

#include <string_view>
#include <vector>

namespace Pargon
{
	class BlueprintWriter
	{
		struct BlueprintTreeNode
		{
			Blueprint* Node;
			int Index;
		};

		std::vector<BlueprintTreeNode> _tree;

		Blueprint _blueprint;
		Blueprint* _current = std::addressof(_blueprint);
		int _currentIndex;

	public:
		auto ViewBlueprint() const -> const Blueprint&;
		auto TakeBlueprint() -> Blueprint;

		template<typename T> void Write(T& value);

		void WriteBoolean(bool value);
		void WriteInteger(long long value);
		void WriteFloatingPoint(double value);
		void WriteString(std::string_view string);

		auto MoveDown(int index) -> bool;
		auto MoveDown(std::string_view name) -> bool;
		void MoveUp();

	private:
		friend class GenericSerializer;
		friend class BlueprintSerializer;

		template<typename T> void Serialize(const T& value);
		void SerializeBoolean(bool value);
		void SerializeInteger(long long value);
		void SerializeFloatingPoint(double value);
		void SerializeString(std::string_view string);
	};
}

inline
auto Pargon::BlueprintWriter::ViewBlueprint() const-> const Blueprint&
{
	return _blueprint;
}

inline
auto Pargon::BlueprintWriter::TakeBlueprint() -> Blueprint
{
	auto blueprint = std::move(_blueprint);

	_tree.clear();
	_current = std::addressof(_blueprint);
	_currentIndex = 0u;

	return blueprint;
}

template<typename T>
void Pargon::BlueprintWriter::Write(T& value)
{
	Pargon::Serializer<T>().Serialize(*this, value);
}

template<typename T>
void Pargon::BlueprintWriter::Serialize(const T& value)
{
	Pargon::Serializer<T>().Serialize(*this, value);
}

inline
void Pargon::BlueprintWriter::SerializeBoolean(bool value)
{
	WriteBoolean(value);
}

inline
void Pargon::BlueprintWriter::SerializeInteger(long long value)
{
	WriteInteger(value);
}

inline
void Pargon::BlueprintWriter::SerializeFloatingPoint(double value)
{
	WriteFloatingPoint(value);
}

inline
void Pargon::BlueprintWriter::SerializeString(std::string_view value)
{
	WriteString(value);
}
