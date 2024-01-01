//
// Purpur Tentakel
// 06.11.2022
//

#pragma once

#include <alias/AliasLogic.hpp>
#include <alias/AliasUtils.hpp>
#include <memory>
#include <string>
#include <utils/Vec2.hpp>


namespace lgk {
    class SpaceObject {
    protected:
        utl::usize m_ID;
        utl::usize m_ships;
        utl::vec2pos_ty m_position;
        Player_ty m_player;
        bool m_isDiscovered{ false };

        [[nodiscard]] static bool IsInRange(SpaceObject_ty_raw first, SpaceObject_ty_raw second, utl::usize range);

    public:
        SpaceObject(utl::usize ID, utl::vec2pos_ty_ref_c position, Player_ty_c player);

        SpaceObject(utl::usize ID, utl::vec2pos_ty position, utl::usize ships, Player_ty player);

        virtual ~SpaceObject() = default;

        void TransferShipsFrom(SpaceObject* origin);

        virtual void Update(Galaxy_ty_raw galaxy) = 0;

        [[nodiscard]] utl::usize GetID() const;

        void SetPlayer(Player_ty player);

        [[nodiscard]] Player_ty GetPlayer() const;

        void SetPos(utl::vec2pos_ty_ref_c pos);

        [[nodiscard]] utl::vec2pos_ty GetPos() const;

        void SetShipCount(utl::usize shipCount);

        [[nodiscard]] utl::usize GetShipCount() const;

        [[nodiscard]] virtual bool IsPlanet() const;

        [[nodiscard]] virtual bool IsFleet() const;

        [[nodiscard]] virtual bool IsTargetPoint() const;

        [[nodiscard]] bool IsInDiscoverRange(SpaceObject_ty_c object) const;

        [[nodiscard]] bool IsInFightRange(SpaceObject_ty_c object) const;

        void SetDiscovered(bool isDiscovered);

        [[nodiscard]] bool IsDiscovered() const;

        friend utl::usize operator+(SpaceObject const& object, utl::usize ships);

        friend utl::usize operator+(utl::usize ships, SpaceObject const& object);

        friend utl::usize operator+(SpaceObject const& lhs, SpaceObject const& rhs);

        friend utl::usize operator-(SpaceObject const& object, utl::usize ships);

        friend utl::usize operator-(utl::usize ships, SpaceObject const& object);

        friend utl::usize operator-(SpaceObject const& lhs, SpaceObject const& rhs);

        friend bool operator<(SpaceObject const& object, utl::usize ships);

        friend bool operator<(utl::usize ships, SpaceObject const& object);

        friend bool operator<(SpaceObject const& lhs, SpaceObject const& rhs);

        friend bool operator<=(SpaceObject const& object, utl::usize ships);

        friend bool operator<=(utl::usize ships, SpaceObject const& object);

        friend bool operator<=(SpaceObject const& lhs, SpaceObject const& rhs);

        friend bool operator>(SpaceObject const& object, utl::usize ships);

        friend bool operator>(utl::usize ships, SpaceObject const& object);

        friend bool operator>(SpaceObject const& lhs, SpaceObject const& rhs);

        friend bool operator>=(SpaceObject const& object, utl::usize ships);

        friend bool operator>=(utl::usize ships, SpaceObject const& object);

        friend bool operator>=(SpaceObject const& lhs, SpaceObject const& rhs);

        SpaceObject& operator+=(utl::usize ships);

        SpaceObject& operator+=(SpaceObject const& object);

        SpaceObject& operator-=(utl::usize ships);

        SpaceObject& operator-=(SpaceObject const& object);

        [[nodiscard]] bool operator==(SpaceObject const& other) const;
    };

    [[nodiscard]] utl::usize operator+(SpaceObject const& object, utl::usize ships);
    [[nodiscard]] utl::usize operator+(utl::usize ships, SpaceObject& object);
    [[nodiscard]] utl::usize operator+(SpaceObject const& lhs, SpaceObject const& rhs);

    [[nodiscard]] utl::usize operator-(SpaceObject const& object, utl::usize ships);
    [[nodiscard]] utl::usize operator-(utl::usize ships, SpaceObject const& object);
    [[nodiscard]] utl::usize operator-(SpaceObject const& lhs, SpaceObject const& rhs);

    [[nodiscard]] bool operator<(SpaceObject const& object, utl::usize ships);
    [[nodiscard]] bool operator<(utl::usize ships, SpaceObject const& object);
    [[nodiscard]] bool operator<(SpaceObject const& lhs, SpaceObject const& rhs);

    [[nodiscard]] bool operator<=(SpaceObject const& object, utl::usize ships);
    [[nodiscard]] bool operator<=(utl::usize ships, SpaceObject const& object);
    [[nodiscard]] bool operator<=(SpaceObject const& lhs, SpaceObject const& rhs);

    [[nodiscard]] bool operator>(SpaceObject const& object, utl::usize ships);
    [[nodiscard]] bool operator>(utl::usize ships, SpaceObject const& object);
    [[nodiscard]] bool operator>(SpaceObject const& lhs, SpaceObject const& rhs);

    [[nodiscard]] bool operator>=(SpaceObject const& object, utl::usize ships);
    [[nodiscard]] bool operator>=(utl::usize ships, SpaceObject const& object);
    [[nodiscard]] bool operator>=(SpaceObject const& lhs, SpaceObject const& rhs);
} // namespace lgk
