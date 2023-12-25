//
// Purpur Tentakel
// 06.11.2022
//

#include "SpaceObject.h"
#include "AppContext.h"
#include <cassert>

bool SpaceObject::IsInRange(SpaceObject_ty_raw first, SpaceObject_ty_raw second, int range) {
	auto const actualRange{ (first->GetPos() - second->GetPos()).Length() };
	return range >= actualRange;
}

SpaceObject::SpaceObject(unsigned int ID, vec2pos_ty position, Player_ty player)
	: SpaceObject{ ID, position, 0, player } {}
SpaceObject::SpaceObject(unsigned int ID, vec2pos_ty position, size_t ships, Player_ty player)
	: m_ID{ID}, m_position{position}, m_player{player}, m_ships{ships} {}

void SpaceObject::TransferShipsFrom(SpaceObject* origin) {
	m_ships += origin->GetShipCount();
	origin->SetShipCount(0);
}

unsigned int SpaceObject::GetID() const {
	return m_ID;
}

void SpaceObject::SetPlayer(Player_ty player) {
	m_player = player;
}
Player_ty SpaceObject::GetPlayer() const {
	return m_player;
}

void SpaceObject::SetPos(vec2pos_ty pos) {
	m_position = pos;
}
vec2pos_ty SpaceObject::GetPos() const {
	return m_position;
}

void SpaceObject::SetShipCount(size_t shipCount) {
	m_ships = shipCount;
}

size_t SpaceObject::GetShipCount() const {
	return m_ships;
}

bool SpaceObject::IsPlanet() const {
	return false;
}
bool SpaceObject::IsFleet() const {
	return false;
}
bool SpaceObject::IsTargetPoint() const {
	return false;
}

bool SpaceObject::IsInDiscoverRange(SpaceObject_ty_c object) const {
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	auto const range = appContext.constants.world.discoverRangeFactor * 
		appContext.constants.fleet.currentFleetSpeed;
	return IsInRange(object.get(), this, range);
}
bool SpaceObject::IsInFightRange(SpaceObject_ty_c object) const {
	auto const range = AppContext::GetInstance().constants.fight.fleetFightRange;
	return IsInRange(object.get(), this, range);
}

void SpaceObject::SetDiscovered(bool isDiscovered) {
	m_isDiscovered = isDiscovered;
}
bool SpaceObject::IsDiscovered() const {
	return m_isDiscovered;
}

SpaceObject& SpaceObject::operator+=(size_t ships) {
	m_ships += ships;
	return *this;
}
SpaceObject& SpaceObject::operator+=(SpaceObject const& object) {
	m_ships += object.m_ships;
	return *this;
}
SpaceObject& SpaceObject::operator-=(size_t ships) {
	assert(m_ships >= ships);
	m_ships -= ships;
	return *this;
}
SpaceObject& SpaceObject::operator-=(SpaceObject const& object) {
	assert(m_ships >= object.m_ships);
	m_ships -= object.m_ships;
	return *this;
}
bool SpaceObject::operator==(SpaceObject const& other) const {
	return m_ID == other.m_ID;
}


// operator
size_t operator+(SpaceObject const& object, size_t ships) {
	return object.m_ships + ships;
}
size_t operator+(size_t ships, SpaceObject const& object) {
	return object + ships;
}
size_t operator+(SpaceObject const& lhs, SpaceObject const& rhs) {
	return lhs.m_ships + rhs.m_ships;
}

size_t operator-(SpaceObject const& object, size_t ships) {
	assert(object.m_ships >= ships);
	return object.m_ships - ships;
}
size_t operator-(size_t ships, SpaceObject const& object) {
	assert(ships >= object.m_ships);
	return ships - object.m_ships;
}
size_t operator-(SpaceObject const& lhs, SpaceObject const& rhs) {
	assert(lhs.m_ships >= rhs.m_ships);
	return lhs.m_ships - rhs.m_ships;
}

bool operator<(SpaceObject const& object, size_t ships) {
	return object.m_ships < ships;
}
bool operator<(size_t ships, SpaceObject const& object) {
	return ships < object.m_ships;
}
bool operator<(SpaceObject const& lhs, SpaceObject const& rhs) {
	return lhs.m_ships < rhs.m_ships;
}

bool operator<=(SpaceObject const& object, size_t ships) {
	return !(object > ships);
}
bool operator<=(size_t ships, SpaceObject const& object) {
	return !(ships > object);
}
bool operator<=(SpaceObject const& lhs, SpaceObject const& rhs) {
	return !(lhs > rhs);
}

bool operator>(SpaceObject const& object, size_t ships) {
	return object.m_ships > ships;
}
bool operator>(size_t ships, SpaceObject const& object) {
	return ships > object.m_ships;
}
bool operator>(SpaceObject const& lhs, SpaceObject const& rhs) {
	return lhs.m_ships > rhs.m_ships;
}

bool operator>=(SpaceObject const& object, size_t ships) {
	return !(object < ships);
}
bool operator>=(size_t ships, SpaceObject const& object) {
	return !(ships < object);
}
bool operator>=(SpaceObject const& lhs, SpaceObject const& rhs) {
	return !(lhs < rhs);
}
