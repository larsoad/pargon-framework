#include "Pargon/Types/Guid.h"

#include <objbase.h>

auto Pargon::GenerateGuid() -> Guid
{
	GUID newId;
	auto result = CoCreateGuid(&newId);
	auto guid = Guid();

	if (result == S_OK)
	{
		guid.SetBytes({{
			static_cast<uint8_t>((newId.Data1 >> 24) & 0xFF),
			static_cast<uint8_t>((newId.Data1 >> 16) & 0xFF),
			static_cast<uint8_t>((newId.Data1 >> 8) & 0xFF),
			static_cast<uint8_t>((newId.Data1) & 0xFF),
			static_cast<uint8_t>((newId.Data2 >> 8) & 0xFF),
			static_cast<uint8_t>((newId.Data2) & 0xFF),
			static_cast<uint8_t>((newId.Data3 >> 8) & 0xFF),
			static_cast<uint8_t>((newId.Data3) & 0xFF),
			newId.Data4[0],
			newId.Data4[1],
			newId.Data4[2],
			newId.Data4[3],
			newId.Data4[4],
			newId.Data4[5],
			newId.Data4[6],
			newId.Data4[7]
			}});
	}

	return guid;
}
