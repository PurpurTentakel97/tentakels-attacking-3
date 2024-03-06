//
// Purpur Tentakel
// 06.03.2024
//

#include "HelperGameEvents.hpp"
#include <app/AppContext.hpp>
#include <utils/GameEventTypes.hpp>
#include <utils/Probability.hpp>


namespace cst {
    static constexpr std::array<utl::GameEventType, 6> s_ev{
        // do NOT add 'utl::GameEventsType::Global'. It will course an endless loop.
        // clang-format off
        utl::GameEventType::PIRATES,
        utl::GameEventType::REVOLTS,
        utl::GameEventType::RENEGADE_SHIPS,
        utl::GameEventType::SUPERNOVA,
        utl::GameEventType::ENGINE_PROBLEM,
        utl::GameEventType::PRODUCTION_PROBLEM,
        // clang-format on
    };

    utl::Probability HelperGameEvents::ChanceByType(utl::GameEventType const type) const {
        auto const& events = app::AppContext::GetInstance().constants.g_game_events;
        switch (type) {
                // clang-format off
            case utl::GameEventType::PIRATES:            return events.get_pirate_chance();
            case utl::GameEventType::REVOLTS:            return events.get_revolts_chance();
            case utl::GameEventType::RENEGADE_SHIPS:     return events.get_renegade_ships_chance();
            case utl::GameEventType::SUPERNOVA:          return events.get_supernova_chance();
            case utl::GameEventType::ENGINE_PROBLEM:     return events.get_engine_problem_chance();
            case utl::GameEventType::PRODUCTION_PROBLEM: return events.get_production_problem_chance();
            case utl::GameEventType::GLOBAL:             return events.get_global_chance();
                // clang-format on
        }
        std::unreachable();
    }

    bool HelperGameEvents::IsEventByType(utl::GameEventType const type) const {
        auto const& events = app::AppContext::GetInstance().constants.g_game_events;
        switch (type) {
                // clang-format off
            case utl::GameEventType::PIRATES:            return events.get_is_pirates();
            case utl::GameEventType::REVOLTS:            return events.get_is_revolts();
            case utl::GameEventType::RENEGADE_SHIPS:     return events.get_is_renegade_ships();
            case utl::GameEventType::SUPERNOVA:          return events.get_is_supernova();
            case utl::GameEventType::ENGINE_PROBLEM:     return events.get_is_engine_problem();
            case utl::GameEventType::PRODUCTION_PROBLEM: return events.get_is_production_problem();
                // clang-format on
            case utl::GameEventType::GLOBAL: {

                for (auto const& e : s_ev) {
                    if (not IsEventByType(e)) {
                        return false;
                    }
                }
                return true;
            }
        }
        std::unreachable();
    }

    void HelperGameEvents::SetEventByType(utl::GameEventType const type, bool const is_active) {
        auto& events = app::AppContext::GetInstance().constants.g_game_events;
        switch (type) {
                // clang-format off
            case utl::GameEventType::PIRATES:            events.set_is_pirates(is_active);            return;
            case utl::GameEventType::REVOLTS:            events.set_is_revolts(is_active);            return;
            case utl::GameEventType::RENEGADE_SHIPS:     events.set_is_renegade_ships(is_active);     return;
            case utl::GameEventType::SUPERNOVA:          events.set_is_supernova(is_active);          return;
            case utl::GameEventType::ENGINE_PROBLEM:     events.set_is_engine_problem(is_active);     return;
            case utl::GameEventType::PRODUCTION_PROBLEM: events.set_is_production_problem(is_active); return;
                // clang-format on
            case utl::GameEventType::GLOBAL: {
                for (auto const e : s_ev) {
                    SetEventByType(e, is_active);
                }
                return;
            };
        }
        std::unreachable();
    }
} // namespace cst
