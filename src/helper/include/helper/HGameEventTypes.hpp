//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include <cstdint>
#include <type_traits>

/**
 * provides the Types of all game events.
 */
enum class HGameEventType : uint8_t /* unsinged char */ {
	PIRATES =        0b00000001, // 1
	REVOLTS =        0b00000010, // 2
	RENEGADE_SHIPS = 0b00000100, // 4
	BLACK_HOLE =     0b00001000, // 8
	SUPERNOVA =      0b00010000, // 16
	ENGINE_PROBLEM = 0b00100000, // 32
	GLOBAL =         0b11111111,
};

inline HGameEventType operator|(HGameEventType lhs, HGameEventType rhs) {
	return static_cast<HGameEventType>(
		   static_cast<std::underlying_type_t<HGameEventType>>(lhs)
		 | static_cast<std::underlying_type_t<HGameEventType>>(rhs));
}
inline HGameEventType& operator|=(HGameEventType& lhs, HGameEventType rhs) {
	 return lhs = { lhs | rhs };
}
inline HGameEventType operator&(HGameEventType lhs, HGameEventType rhs) {
	return static_cast<HGameEventType>(
		   static_cast<std::underlying_type_t<HGameEventType>>(lhs)
		 & static_cast<std::underlying_type_t<HGameEventType>>(rhs));
}
inline HGameEventType& operator&=(HGameEventType& lhs, HGameEventType rhs) {
	return lhs = { lhs & rhs };
}
inline HGameEventType operator~(HGameEventType value) {
	return static_cast<HGameEventType>(
		~(static_cast<std::underlying_type_t<HGameEventType>>(value))	
	);
}
