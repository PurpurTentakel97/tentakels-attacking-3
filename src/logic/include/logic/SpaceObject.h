//
// Purpur Tentakel
// 06.11.2022
//

#pragma once
#include "helper/HLogicAlias.hpp"
#include "helper/Vec2.hpp"
#include <string>
#include <memory>


/**
 * the basic space object, that every element in the galaxy is implementing.
 */
class SpaceObject{
protected:
	unsigned int m_ID; ///< contains the unique id
	size_t m_ships; ///< contains the current amount of ships
	vec2pos_ty m_position; ///< contains the absolute position within the galaxy
	Player_ty m_player; ///< contains a pointer to a player who owns the object
	bool m_isDiscovered{ false }; ///< contains if the current player has discovered this object

	[[nodiscard]] static bool IsInRange(SpaceObject_ty_raw first, SpaceObject_ty_raw second, int range);

public:
	/**
	 * ctor without ships.
	 * only initialisation
	 */
	SpaceObject(unsigned int ID, vec2pos_ty position, Player_ty player);
	/**
	 * ctor.
	 * only initialisation.
	 */
	SpaceObject(unsigned int ID, vec2pos_ty position, size_t ships, Player_ty player);
	/**
	 * virtual dtor to provide a default one.
	 */
	virtual ~SpaceObject() = default;

	/**
	 * trans fairs all ships from the provided origin to this space object.
	 * the origin has no langer any ships.
	 */
	void TransferShipsFrom(SpaceObject* origin);

	/**
	 * updates the SpaceObject.
 	 */
	virtual void Update(Galaxy_ty_raw galaxy) = 0; 

	/**
	 * returns the unique id.
	 */
	[[nodiscard]] unsigned int GetID() const;

	/**
	 * sets a new player as owner of the object.
	 */
	void SetPlayer(Player_ty player);
	/**
	 * returns the current player who owns the object.
	 */
	[[nodiscard]] Player_ty GetPlayer() const;

	/**
	 * sets a new position in the galaxy.
	 */
	void SetPos(vec2pos_ty pos);
	/**
	 * returns the current position.
	 */
	[[nodiscard]] vec2pos_ty GetPos() const;

	/**
	 * sets a new ship count.
	 * only if necessary.
	 */
	void SetShipCount(size_t shipCount);
	/**
	 * returns the current ship Count
	 */
	[[nodiscard]] size_t GetShipCount() const;


	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] virtual bool IsPlanet() const;
	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] virtual bool IsFleet() const;
	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] virtual bool IsTargetPoint() const;

	/**
	 * returns if the provided SpaceObject is in discover range of this.
	 */
	[[nodiscard]] bool IsInDiscoverRange(SpaceObject_ty_c object) const;
	/**
	 * returns if the provided SpaceObject is in fight range of this.
	 */
	[[nodiscard]] bool IsInFightRange(SpaceObject_ty_c object) const;

	/**
	 * set if the planet is discovered.
	 */
	void SetDiscovered(bool isDescovered);
	/**
	 * returns if the planet is discovered from any player.
	 */
	[[nodiscard]] bool IsDiscovered() const;

	/**
	 * adds and returns the ship count of an object and a number.
	 */
	friend size_t operator+ (SpaceObject const& object, size_t ships);
	/**
	 * adds and returns the ship count of an object and a number.
	 */
	friend size_t operator+ (size_t ships, SpaceObject const& object);
	/**
	 * adds and returns two ship counts.
	 */
	friend size_t operator+ (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * substracts and returns the ship count of an object and a number.
	 */
	friend size_t operator- (SpaceObject const& object, size_t ships);
	/**
	 * substracts and returns the ship count of an object and a number.
	 */
	friend size_t operator- (size_t ships, SpaceObject const& object);
	/**
	 * substracts and returns two ship counts.
	 */
	friend size_t operator- (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is smaller than the number. 
	 */
	friend bool operator< (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is smaller than the ship count.
	 */
	friend bool operator< (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count smaller than the rhs ship count.
	 */
	friend bool operator< (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is smaller than or equal to the number.
	 */
	friend bool operator<= (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is smaller than or equal to the ship count.
	 */
	friend bool operator<= (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count smaller than or equal to the rhs ship count.
	 */
	friend bool operator<= (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is greater than the number.
	 */
	friend bool operator> (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is greater than the ship count.
	 */
	friend bool operator> (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count greater than the rhs ship count.
	 */
	friend bool operator> (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is greater than or equal to the number.
	 */
	friend bool operator>= (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is greater than or equal to the ship count.
	 */
	friend bool operator>= (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count greater than or equal to the rhs ship count.
	 */
	friend bool operator>= (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * add an amount of ships to the ship count.
	 */
	SpaceObject& operator+=(size_t ships);
	/**
	 * add an other ship count to the ship count.
	 */
	SpaceObject& operator+=(SpaceObject const& object);

	/**
	 * substract an amount of ships to the ship count.
	 */
	SpaceObject& operator-=(size_t ships);
	/**
	 * substract an other ship count to the ship count.
	 */
	SpaceObject& operator-=(SpaceObject const& object);

	/**
	 * compares two objects by id.
	 */
	[[nodiscard]] bool operator== (SpaceObject const& other) const;
};

// doc strings at the friends function
[[nodiscard]] size_t operator+ (SpaceObject const& object, size_t ships);
[[nodiscard]] size_t operator+ (size_t ships, SpaceObject& object);
[[nodiscard]] size_t operator+ (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] size_t operator- (SpaceObject const& object, size_t ships);
[[nodiscard]] size_t operator- (size_t ships, SpaceObject const& object);
[[nodiscard]] size_t operator- (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator< (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator< (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator< (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator<= (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator<= (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator<= (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator> (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator> (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator> (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator>= (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator>= (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator>= (SpaceObject const& lhs, SpaceObject const& rhs);
