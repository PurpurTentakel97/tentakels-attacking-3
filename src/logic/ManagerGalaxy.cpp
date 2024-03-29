//
// PurpurTentakel
// 23.05.23
//

#include "ManagerGalaxy.hpp"
#include "CopyGalaxyType.hpp"
#include "Galaxy.hpp"
#include "ManagerGame.hpp"
#include "Player.hpp"
#include "RepresentationGenerator.hpp"
#include <alias/AliasUtils.hpp>
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HPrint.hpp>
#include <helper/HRandom.hpp>
#include <utils/ResultFleet.hpp>
#include <utils/Vec2.hpp>

namespace lgk {
    void GalaxyManager::FilterCurrentGalaxy() {
        Player_ty currentPlayer{ nullptr };
        bool const valid{ m_gameManager->GetCurrentPlayer(currentPlayer) };
        if (not valid) {
            return;
        }
        m_mainGalaxy->SetDiscoverByPlayer(currentPlayer->GetID());
        m_currentGalaxy->SetDiscoverByPlayer(currentPlayer->GetID());
        m_currentGalaxy->FilterByDiscovered();
    }

    GalaxyManager::GalaxyManager(GameManager* const gameManager) : m_gameManager{ gameManager } { }

    void GalaxyManager::GenerateGalaxy() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        utl::vec2pos_ty_c size = { static_cast<int>(appContext.constants.g_world.get_current_dimension_x()),
                                   static_cast<int>(appContext.constants.g_world.get_current_dimension_y()) };
        auto const galaxy      = std::make_shared<Galaxy>(size,
                                                     appContext.constants.g_world.get_current_planet_count(),
                                                     m_gameManager->m_players,
                                                     m_gameManager->m_npcs[PlayerType::NEUTRAL]);

        if (galaxy->IsValid()) {
            m_mainGalaxy = galaxy;
            CopyGalaxies(CopyGalaxyType::COPY_ALL);
            eve::GalaxyGeneratedUIEvent const event{};
            appContext.eventManager.InvokeEvent(event);
        } else {
            eve::ShowMessagePopUpEvent const event{
                appContext.languageManager.Text("logic_galaxy_manager_unable_generate_galaxy_title"),
                appContext.languageManager.Text("logic_galaxy_manager_unable_generate_galaxy_text", "\n"),
                []() {}
            };
            appContext.eventManager.InvokeEvent(event);
        }
    }

    void GalaxyManager::GenerateShowGalaxy() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        utl::vec2pos_ty_c size = {
            static_cast<int>(appContext.constants.g_world.get_show_dimension_x()),
            static_cast<int>(appContext.constants.g_world.get_show_dimension_y()),
        };

        auto const galaxy = std::make_shared<Galaxy>(size,
                                                     appContext.constants.g_world.get_show_planet_count(),
                                                     m_gameManager->m_players,
                                                     m_gameManager->m_npcs[PlayerType::NEUTRAL]);

        if (galaxy->IsValid()) {
            m_showGalaxy = galaxy;
            eve::SendGalaxyRepresentationEvent const event{ GenGalaxyRep(m_showGalaxy.get()), true };
            appContext.eventManager.InvokeEvent(event);
        } else if (m_showGalaxy) {
            eve::SendGalaxyRepresentationEvent const event{ GenGalaxyRep(m_showGalaxy.get()), true };
            appContext.eventManager.InvokeEvent(event);
            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "Could not generated ShowGalaxy -> Use old Galaxy");
        } else {
            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "Could not generated ShowGalaxy -> No Galaxy");
        }
    }

    void GalaxyManager::CopyGalaxies(CopyGalaxyType const copyType) {
        if (copyType == CopyGalaxyType::COPY_ALL) {
            m_startGalaxy = std::make_shared<Galaxy>(*m_mainGalaxy);
        }
        m_currentGalaxy = std::make_shared<Galaxy>(*m_startGalaxy);
        FilterCurrentGalaxy();
    }

    Galaxy* GalaxyManager::GetGalaxy() {
        if (m_currentGalaxy and not m_currentGalaxy->IsFiltered()) {
            FilterCurrentGalaxy();
        }
        return m_currentGalaxy.get();
    }

    bool GalaxyManager::AddFleet(eve::SendFleetInstructionEvent const* const event, Player_ty const& currentPlayer) {

        auto const result = m_mainGalaxy->AddFleet(event, currentPlayer);
        if (not result.valid) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "Not able to add Fleet to main Galaxy");

            eve::ReturnFleetInstructionEvent const returnEvent{ result.valid };
            app::AppContext::GetInstance().eventManager.InvokeEvent(returnEvent);
            return false;
        }
        m_currentGalaxy->HandleFleetResult(result, currentPlayer);

        return true;
    }

    bool GalaxyManager::HasMovesLeft(Player_ty_c player) const {
        return m_mainGalaxy->HasMovesLeft(player);
    }

    void GalaxyManager::KillPlayer(Player_ty_c player, Player_ty_c neutralPlayer) {
        auto filter{ [&](auto const& objects) {
            for (auto& e : objects) {
                if (e->GetPlayer()->GetID() == player->GetID()) {
                    e->SetPlayer(neutralPlayer);
                }
            }
        } };

        filter(m_mainGalaxy->GetPlanets());
        filter(m_mainGalaxy->GetTargetPoints());
        filter(m_mainGalaxy->GetFleets());
    }

    utl::ResultUpdate GalaxyManager::Update() {
        return m_mainGalaxy->Update();
    }

    // events

    std::shared_ptr<utl::ResultEventPirates> GalaxyManager::HandlePirates(Player_ty_c pirate, utl::usize const ships) {
        auto planets       = m_mainGalaxy->GetPlanets();
        auto objects       = m_mainGalaxy->GetSpaceObjects();
        auto const& size   = m_mainGalaxy->GetSize();
        auto const& planet = hlp::RandomElementFromList(planets);
        auto& random       = hlp::Random::GetInstance();

        utl::vec2pos_ty position{};
        while (true) {
            position = { static_cast<int>(random.random(static_cast<std::mt19937_64::result_type>(size.x))),
                         static_cast<int>(random.random(static_cast<std::mt19937_64::result_type>(size.y))) };

            for (auto const& o : objects) {
                if (o->GetPos() == position) {
                    continue;
                }
            }
            break;
        }

        auto const& fleet = m_mainGalaxy->AddFleetOutCheck(pirate, ships, planet, position);
        return std::make_shared<utl::ResultEventPirates>(
                fleet->GetPlayer()->GetID(), fleet->GetShipCount(), fleet->GetPos());
    }

    std::shared_ptr<utl::ResultEventRevolts> GalaxyManager::HandleRevolts(Player_ty_c player) {
        auto planets                  = m_mainGalaxy->GetPlanets();
        app::AppContext_ty appContext = app::AppContext::GetInstance();
        if (planets.empty()) {
            return {};
        }

    repeat:
        auto& planet = hlp::RandomElementFromList(planets);
        if (not appContext.constants.g_game_events.get_is_event_on_home_world() and planet->IsHomePlanet()) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "planet {} is a home planet", planet->GetID());
            goto repeat;
        }
        auto& random     = hlp::Random::GetInstance();
        auto const count = random.random(planet->GetShipCount()) + 1;
        planet->SetShipCount(planet->GetShipCount() - count);

    repeat2:
        auto& destination = hlp::RandomElementFromList(planets);
        if (not appContext.constants.g_game_events.get_is_event_on_home_world() and destination->IsHomePlanet()) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "planet {} is a home planet", planet->GetID());
            goto repeat2;
        }
        if (destination->GetID() == planet->GetID()) {
            goto repeat2;
        }

        auto const& fleet = m_mainGalaxy->AddFleetOutCheck(player, count, destination, planet->GetPos());
        return std::make_shared<utl::ResultEventRevolts>(
                planet->GetPlayer()->GetID(), planet->GetID(), fleet->GetShipCount());
    }

    std::shared_ptr<utl::ResultEventRenegadeShips> GalaxyManager::HandleRenegadeShips(Player_ty_c player) {
        auto fleets  = m_mainGalaxy->GetFleets();
        auto planets = m_mainGalaxy->GetPlanets();
        if (fleets.empty()) {
            return {};
        }

        auto const& fleet = hlp::RandomElementFromList(fleets);

    repeat:
        auto const& destination = hlp::RandomElementFromList(planets);
        if (not app::AppContext::GetInstance().constants.g_game_events.get_is_event_on_home_world()
            and destination->IsHomePlanet()) {
            goto repeat;
        }

        auto& random     = hlp::Random::GetInstance();
        auto const count = random.random(fleet->GetShipCount()) + 1;

        fleet->SetShipCount(fleet->GetShipCount() - count);

        auto const new_fleet = m_mainGalaxy->AddFleetOutCheck(player, count, destination, fleet->GetPos());

        return std::make_shared<utl::ResultEventRenegadeShips>(
                fleet->GetPlayer()->GetID(), fleet->GetID(), new_fleet->GetShipCount());
    }

    std::shared_ptr<utl::ResultEventSupernova> GalaxyManager::HandleSupernova(Player_ty_c invalid_player) {
        auto planets = m_mainGalaxy->GetPlanets();
        if (planets.empty()) {
            return {};
        }

        for (int i = 0; i < 20; ++i) {
            auto& planet = hlp::RandomElementFromList(planets);

            if (not app::AppContext::GetInstance().constants.g_game_events.get_is_event_on_home_world()
                and planet->IsHomePlanet()) {
                hlp::Print(hlp::PrintType::ONLY_DEBUG, "planet {} is a home planet", planet->GetID());
                continue;
            }

            auto const& fleets = m_mainGalaxy->GetFleetsOfTarget(planet);
            m_mainGalaxy->DeletePlanet(planet);
            auto const blackHole =
                    m_mainGalaxy->AddBlackHoleWithoutCheck(planet->GetPos(), invalid_player, planet->GetShipCount());
            for (auto const& f : fleets) {
                f->SetTarget(blackHole);
            }
            return std::make_shared<utl::ResultEventSupernova>(
                    planet->GetPlayer()->GetID(), planet->GetID(), planet->GetShipCount());
        }
        return {};
    }

    std::shared_ptr<utl::ResultEventEngineProblem> GalaxyManager::HandleEngineProblem(utl::usize const years) {
        auto fleets = m_mainGalaxy->GetFleets();
        if (fleets.empty()) {
            return {};
        }
        for (int i = 0; i < 20; ++i) {
            auto& fleet = hlp::RandomElementFromList(fleets);
            if (fleet->GetEngineProblemYears() != 0) {
                continue;
            }
            fleet->SetEngineProblemYears(years);
            return std::make_shared<utl::ResultEventEngineProblem>(fleet->GetPlayer()->GetID(), fleet->GetID(), years);
        }
        return {};
    }

    std::shared_ptr<utl::ResultEventProductionProblem> GalaxyManager::HandleProductionProblem(utl::usize const years) {
        auto planets = m_mainGalaxy->GetPlanets();
        if (planets.empty()) {
            return {};
        }

        for (auto i = 0; i < 10; ++i) {
            auto& planet = hlp::RandomElementFromList(planets);
            if (planet->GetProductionProblemYears() != 0) {
                continue;
            }
            if (not app::AppContext::GetInstance().constants.g_game_events.get_is_event_on_home_world()
                and planet->IsHomePlanet()) {
                continue;
            }

            planet->SetProductionProblemYears(years);
            return std::make_shared<utl::ResultEventProductionProblem>(
                    planet->GetPlayer()->GetID(), planet->GetID(), planet->GetProductionProblemYears());
        }
        return {};
    }
} // namespace lgk
