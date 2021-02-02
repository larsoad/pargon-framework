set(INCLUDES
	Pargon/Serialization.h
	Pargon/Serialization/Blueprint.h
	Pargon/Serialization/BlueprintReader.h
	Pargon/Serialization/BlueprintSerializer.h
	Pargon/Serialization/BlueprintWriter.h
	Pargon/Serialization/Buffer.h
	Pargon/Serialization/BufferReader.h
	Pargon/Serialization/BufferSerializer.h
	Pargon/Serialization/BufferWriter.h
	Pargon/Serialization/GenericSerializer.h
	Pargon/Serialization/Serializer.h
	Pargon/Serialization/Serializers/Fundamental.h
	Pargon/Serialization/Serializers/Fundamental/bool-serializer.h
	Pargon/Serialization/Serializers/Fundamental/char16_t-serializer.h
	Pargon/Serialization/Serializers/Fundamental/char32_t-serializer.h
	Pargon/Serialization/Serializers/Fundamental/char-serializer.h
	Pargon/Serialization/Serializers/Fundamental/double-serializer.h
	Pargon/Serialization/Serializers/Fundamental/float-serializer.h
	Pargon/Serialization/Serializers/Fundamental/int-serializer.h
	Pargon/Serialization/Serializers/Fundamental/long-double-serializer.h
	Pargon/Serialization/Serializers/Fundamental/long-long-serializer.h
	Pargon/Serialization/Serializers/Fundamental/long-serializer.h
	Pargon/Serialization/Serializers/Fundamental/short-serializer.h
	Pargon/Serialization/Serializers/Fundamental/signed-char-serializer.h
	Pargon/Serialization/Serializers/Fundamental/unsigned-char-serializer.h
	Pargon/Serialization/Serializers/Fundamental/unsigned-int-serializer.h
	Pargon/Serialization/Serializers/Fundamental/unsigned-long-long-serializer.h
	Pargon/Serialization/Serializers/Fundamental/unsigned-long-serializer.h
	Pargon/Serialization/Serializers/Fundamental/unsigned-short-serializer.h
	Pargon/Serialization/Serializers/Fundamental/wchar_t-serializer.h
	Pargon/Serialization/Serializers/Stl.h
	Pargon/Serialization/Serializers/Stl/string-serializer.h
)

set(SOURCES
	Core/Blueprint.cpp
	Core/BlueprintReader.cpp
	Core/BlueprintWriter.cpp
	Core/Buffer.cpp
	Core/BufferReader.cpp
	Core/BufferWriter.cpp
)

set(LIBRARIES
	PargonShim
)

set(TESTS
	SerializationTests.h
	SerializationTests.cpp
	SerializerTests.cpp
)

add_pargon_module(PargonSerialization "${INCLUDES}" "${SOURCES}" "${LIBRARIES}" "${TESTS}")
