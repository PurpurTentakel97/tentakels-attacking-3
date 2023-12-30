//
// PurpurTentakel
// 23.05.23
//

#include "ManagerGalaxy.hpp"
#include "CopyGalaxyType.hpp"
#include "Galaxy.hpp"
#include "ManagerGame.hpp"
#include "Player.hpp"
#include <alias/AliasUtils.hpp>
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HPrint.hpp>
#include <utils/FleetResult.hpp>
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
        utl::vec2pos_ty_c size = { appContext.constants.world.currentDimensionX,
                                   appContext.constants.world.currentDimensionY };
        auto const galaxy = std::make_shared<Galaxy>(
                size,
                appContext.constants.world.currentPlanetCount,
                m_gameManager->m_players,
                m_gameManager->m_npcs[PlayerType::NEUTRAL]
        );

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
            appContext.constants.world.showDimensionX,
            appContext.constants.world.showDimensionY,
        };

        auto const galaxy = std::make_shared<Galaxy>(
                size,
                appContext.constants.world.showPlanetCount,
                m_gameManager->m_players,
                m_gameManager->m_npcs[PlayerType::NEUTRAL]
        );

        if (galaxy->IsValid()) {
            m_showGalaxy = galaxy;
            eve::SendGalaxyPointerEvent const event{ m_showGalaxy.get(), true };
            appContext.eventManager.InvokeEvent(event);
        } else if (m_showGalaxy) {
            eve::SendGalaxyPointerEvent const event{ m_showGalaxy.get(), true };
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
            for (auto e : objects) {
                if (e->GetPlayer()->GetID() == player->GetID()) {
                    e->SetPlayer(neutralPlayer);
                }
            }
        } };

        filter(m_mainGalaxy->GetPlanets());
        filter(m_mainGalaxy->GetTargetPoints());
        filter(m_mainGalaxy->GetFleets());
    }

    utl::UpdateResult_ty GalaxyManager::Update() {
        return m_mainGalaxy->Update();
    }
} // namespace lgk
