#pragma once

#include "Pargon/Serialization/Blueprint.h"
#include "Pargon/Serialization/Serializer.h"

#include <string_view>
#include <vector>

namespace Pargon
{
	class BlueprintReader
	{
		struct BlueprintTreeNode
		{
			const Blueprint* Node;
			int Index;
		};

		std::vector<BlueprintTreeNode> _tree;

		const Blueprint* _current;
		int _currentIndex;

	public:
		BlueprintReader(const Blueprint& blueprint);
		
		template<typename T> void Read(T& value);

		auto ReadBoolean() -> bool;
		auto ReadInteger() -> long long;
		auto ReadFloatingPoint() -> double;
		auto ReadString() -> std::string_view;
		
		auto MoveDown(int index) -> bool;
		auto MoveDown(std::string_view name) -> bool;
		void MoveUp();

	private:
		friend class GenericSerializer;
		friend class BlueprintSerializer;

		template<typename T> void Serialize(T& value);
		void SerializeBoolean(bool& value);
		void SerializeInteger(long long& value);
		void SerializeFloatingPoint(double& value);
		void SerializeString(std::string& string);
	};
}

template<typename T>
void Pargon::BlueprintReader::Read(T& value)
{
	Pargon::Serializer<T>().Serialize(*this, value);
}

template<typename T>
void Pargon::BlueprintReader::Serialize(T& value)
{
	Pargon::Serializer<T>().Serialize(*this, value);
}

inline
void Pargon::BlueprintReader::SerializeBoolean(bool& value)
{
	value = ReadBoolean();
}

inline
void Pargon::BlueprintReader::SerializeInteger(long long& value)
{
	value = ReadInteger();
}

inline
void Pargon::BlueprintReader::SerializeFloatingPoint(double& value)
{
	value = ReadFloatingPoint();
}

inline
void Pargon::BlueprintReader::SerializeString(std::string& value)
{
	value = ReadString();
}
