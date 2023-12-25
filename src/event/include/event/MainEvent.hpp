//
// Purpur Tentakel
// 15.08.2022
//

#pragma once

/**
 * the basic events without function where every other event will inherit from.
 */
class Event {
protected:
	Event() = default;

public:
	virtual ~Event() = default;
};
