//
// Purpur Tentakel
// 12.07.2023
//

#include "CGameEvents.h"


void CGameEvents::SetFlag(HGameEventType const type, bool const active) {
	if (active) {
		events |= type;
	}
	else {
		if ((type & HGameEventType::GLOBAL) == HGameEventType::GLOBAL) {
			events = static_cast<HGameEventType>(0b11000000);
			return;
		}
		events &= ~type;
	}
}
bool CGameEvents::IsFlag(HGameEventType const type) const {
	return (events & type) == type;
}
