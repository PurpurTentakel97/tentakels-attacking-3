//
// PurpurTentakel
// 16.02.22
//

#include "Fleet.h"
#include "AppContext.hpp"
#include "Galaxy.h"
#include "helper/HGalaxy.hpp"
#include "helper/HPrint.hpp"
#include <cmath>

Fleet::Fleet(unsigned int ID, vec2pos_ty position, Player_ty player,
    SpaceObject_ty target)
    : SpaceObject{ ID, position, player }, m_target{ target } { }

Fleet::Fleet(unsigned int ID, vec2pos_ty position, size_t ships, Player_ty player,
    SpaceObject_ty target)
    : SpaceObject{ ID, position, ships, player }, m_target{ target } { }

bool Fleet::IsFleet() const {
    return true;
}

SpaceObject_ty Fleet::GetTarget() const {
    return m_target;
}
std::pair<bool, SpaceObject_ty> Fleet::GetFairTarget() const {
    return TryGetTarget(this, m_target);
}
void Fleet::SetTarget(SpaceObject_ty target) {
    m_target = target;
}

bool Fleet::IsArrived() const {
    return m_position == m_target->GetPos();
}
bool Fleet::IsFarArrived() const {
    auto [valid, dummy] { TryGetTarget(this, m_target) };
    if (not valid) { return false; }

    return m_position == dummy->GetPos();
}

bool Fleet::IsFriendly() const {
    return m_player == m_target->GetPlayer();
}
bool Fleet::IsFarFriendly() const {
    auto [valid, target] { TryGetTarget(this, m_target) };
    if (not valid) { return false; }

    return m_player == target->GetPlayer();
}


void Fleet::Update(Galaxy_ty_raw galaxy) {

    auto [valid, target] { TryGetTarget(this, m_target) };
    if (not valid) { target = m_target; };

    int speed = AppContext::GetInstance().constants.fleet.currentFleetSpeed;
    float constexpr dl{ 0.001f };
    int   const     x1{ m_position.x };
    int   const     y1{ m_position.y };
    int   const     x2{ target->GetPos().x };
    int   const     y2{ target->GetPos().y };
    int   const     dx{ x2 - x1 };
    int   const     dy{ y2 - y1 };
    std::vector<vec2pos_ty> route;

    auto addPosition = [&](vec2pos_ty_ref_c new_) {
        for (auto const& v : route) {
            if (v == new_) {
                return;
            }
        }
        route.push_back(new_);
    };
    auto generatePosition = [&]() {
        for (float l = 0.0f; l < 1.0f; l += dl) {
            vec2pos_ty newPos{ x1 + static_cast<int>(std::floor(static_cast<float>(dx) * l + 0.5f)),
                               y1 + static_cast<int>(std::floor(static_cast<float>(dy) * l + 0.5f)) };
            addPosition(newPos);
        }
    };
    auto setSpeed = [&](vec2pos_ty_ref_c old, vec2pos_ty_ref_c new_) {
        vec2pos_ty offset = Abs<int>(old - new_);
        speed -= offset.x;
        speed -= offset.y;
    };
    auto filterPosition = [&]() -> vec2pos_ty {
        vec2pos_ty old = m_position;
        vec2pos_ty new_ = target->GetPos();
        for (size_t i = 1; i < route.size(); ++i) {
            old = route.at(i - 1);
            new_ = route.at(i);
            if (galaxy->IsValidPosition(new_)) {
                setSpeed(old, new_);
            }

            if (speed <= 0) {
                break;
            }
        }
        return new_;
    };

    generatePosition();
    m_position = filterPosition();

    Print(
        PrintType::ONLY_DEBUG,
        "fleet moved -> id: {} -> pos: {}",
        m_ID,
        m_position.ToString()
    );
}
