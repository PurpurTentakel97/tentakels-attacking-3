//
// PurpurTentakel
// 16.02.22
//

#include "Fleet.hpp"
#include "Galaxy.hpp"
#include "GetTarget.hpp"
#include <app/AppContext.hpp>
#include <cmath>
#include <helper/HPrint.hpp>

namespace lgk {
    Fleet::Fleet(utl::usize const ID, utl::vec2pos_ty_ref_c position, Player_ty_c player, SpaceObject_ty target)
        : SpaceObject{ ID, position, player },
          m_target{ std::move(target) } { }

    Fleet::Fleet(utl::usize const ID,
                 utl::vec2pos_ty_ref_c position,
                 utl::usize ships,
                 Player_ty_c player,
                 SpaceObject_ty target)
        : SpaceObject{ ID, position, ships, player },
          m_target{ std::move(target) } { }

    bool Fleet::IsFleet() const {
        return true;
    }

    SpaceObject_ty Fleet::GetTarget() const {
        return m_target;
    }

    std::pair<bool, SpaceObject_ty> Fleet::GetFairTarget() const {
        return hlp::TryGetTarget(this, m_target);
    }

    void Fleet::SetTarget(SpaceObject_ty target) {
        m_target = std::move(target);
    }

    bool Fleet::IsArrived() const {
        return m_position == m_target->GetPos();
    }

    bool Fleet::IsFarArrived() const {
        auto [valid, dummy]{ hlp::TryGetTarget(this, m_target) };
        if (not valid) {
            return false;
        }

        return m_position == dummy->GetPos();
    }

    bool Fleet::IsFriendly() const {
        return m_player == m_target->GetPlayer();
    }

    bool Fleet::IsFarFriendly() const {
        auto [valid, target]{ hlp::TryGetTarget(this, m_target) };
        if (not valid) {
            return false;
        }

        return m_player == target->GetPlayer();
    }


    utl::usize Fleet::GetEngineProblemYears() const {
        return m_engineProblemYears;
    }

    void Fleet::SetEngineProblemYears(utl::usize years) {
        m_engineProblemYears = years;
    }
    void Fleet::Update(Galaxy_ty_raw galaxy) {

        if (m_engineProblemYears > 0) {
            --m_engineProblemYears;
            return;
        }

        auto [valid, target]{ hlp::TryGetTarget(this, m_target) };
        if (not valid) {
            target = m_target;
        }

        auto speed = static_cast<int>(app::AppContext::GetInstance().constants.fleet.currentFleetSpeed);
        auto constexpr dl{ 0.001f };
        auto const x1{ m_position.x };
        auto const y1{ m_position.y };
        auto const x2{ target->GetPos().x };
        auto const y2{ target->GetPos().y };
        auto const dx{ x2 - x1 };
        auto const dy{ y2 - y1 };
        std::vector<utl::vec2pos_ty> route;

        auto addPosition = [&](utl::vec2pos_ty_ref_c new_) {
            for (auto const& v : route) {
                if (v == new_) {
                    return;
                }
            }
            route.push_back(new_);
        };
        auto generatePosition = [&]() {
            for (float l = 0.0f; l < 1.0f; l += dl) {
                utl::vec2pos_ty newPos{ x1 + static_cast<int>(std::floor(static_cast<float>(dx) * l + 0.5f)),
                                        y1 + static_cast<int>(std::floor(static_cast<float>(dy) * l + 0.5f)) };
                addPosition(newPos);
            }
        };
        auto setSpeed = [&](utl::vec2pos_ty_ref_c old, utl::vec2pos_ty_ref_c new_) {
            utl::vec2pos_ty offset{ old.x - new_.x, old.y - new_.y };
            offset = Abs<int>(offset);
            speed -= offset.x;
            speed -= offset.y;
        };
        auto filterPosition = [&]() -> utl::vec2pos_ty {
            utl::vec2pos_ty new_ = target->GetPos();
            for (utl::usize i = 1; i < route.size(); ++i) {
                utl::vec2pos_ty old = route.at(i - 1);
                new_                = route.at(i);
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

        hlp::Print(hlp::PrintType::ONLY_DEBUG, "fleet moved -> id: {} -> pos: {}", m_ID, m_position.ToString());
    }
} // namespace lgk
