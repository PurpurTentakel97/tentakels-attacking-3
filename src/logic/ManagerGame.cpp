//
// PurpurTentakel
// 10.08.22
//

#include "ManagerGame.hpp"
#include "CopyGalaxyType.hpp"
#include "RepresentationGenerator.hpp"
#include <algorithm>
#include <alias/AliasUtils.hpp>
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HPrint.hpp>
#include <helper/HRandom.hpp>
#include <ranges>
#include <span>
#include <stdexcept>

namespace lgk {
    // help Lambdas
    static auto popup = [](std::string const& text) {
        eve::ShowMessagePopUpEvent const popupEvent{
            app::AppContext::GetInstance().languageManager.Text("logic_galaxy_invalid_input_headline"), text, []() {}
        };
        app::AppContext::GetInstance().eventManager.InvokeEvent(popupEvent);
    };

    // player
    bool GameManager::ValidAddPlayer() const {
        return app::AppContext::GetInstance().constants.player.maxPlayerCount > m_players.size();
    }

    utl::usize GameManager::GetNextPlayerID() const {
        utl::usize nextID{ 1 };
        while (true) {
            bool freeID{ true };
            for (auto const& p : m_players) {
                if (p->GetID() == nextID) {
                    freeID = false;
                    break;
                }
            }

            if (freeID) {
                return nextID;
            }

            ++nextID;
        }
    }

    bool GameManager::IsExistingPlayerID(utl::usize const ID) const {
        for (auto const& p : m_players) {
            if (p->GetID() == ID) {
                return true;
            }
        }
        return false;
    }

    bool GameManager::GetCurrentPlayer(Player_ty& currentPlayer) const {
        if (m_currentRoundPlayers.empty()) {
            return false;
        }

        currentPlayer = m_currentRoundPlayers.back();
        return true;
    }

    bool GameManager::GetNextPlayer(Player_ty& nextPlayer) const {
        if (m_currentRoundPlayers.size() < 2) {
            return false;
        }

        nextPlayer = m_currentRoundPlayers.at(m_currentRoundPlayers.size() - 2);
        return true;
    }

    void GameManager::AddPlayer(eve::AddPlayerEvent const* const event) {

        auto name{ event->GetName() };
        auto color{ event->GetColor() };
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto const l{ [&, name, color](bool valid) {
            if (valid) {
                eve::StopGameEvent const eventRet{};
                app::AppContext::GetInstance().eventManager.InvokeEvent(eventRet);
                eve::AddPlayerEvent const eventPlay{ name, color };
                this->AddPlayer(&eventPlay);
            }
        } };
        if (not CheckValidAddRemovePlayer(l)) {
            return;
        }

        if (!ValidAddPlayer()) {
            eve::ShowMessagePopUpEvent const UIEvent{ appContext.languageManager.Text("ui_popup_max_player_title"),
                                                      appContext.languageManager.Text("ui_popup_max_player_subtitle"),
                                                      []() {} };
            appContext.eventManager.InvokeEvent(UIEvent);
            return;
        }

        utl::usize const newID{ GetNextPlayerID() };
        auto const player = std::make_shared<Player>(newID, PlayerType::HUMAN);
        m_players.push_back(player);

        eve::AddPlayerUIEvent const AddEvent{ newID, name, color };
        appContext.eventManager.InvokeEvent(AddEvent);
    }

    void GameManager::EditPlayer(eve::EditPlayerEvent const* const event) const {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        if (!IsExistingPlayerID(event->GetID())) {
            eve::ShowMessagePopUpEvent const UIEvent{ appContext.languageManager.Text("helper_invalid_id"),
                                                      appContext.languageManager.Text("ui_popup_invalid_id_subtitle",
                                                                                      event->GetID()),
                                                      []() {} };
            appContext.eventManager.InvokeEvent(UIEvent);
            return;
        }

        eve::EditPlayerUIEvent const editEvent{ event->GetID(), event->GetName(), event->GetColor() };
        appContext.eventManager.InvokeEvent(editEvent);
    }

    void GameManager::DeletePlayer(eve::DeletePlayerEvent const* const event) {

        auto id{ event->GetID() };
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto const l{ [&, id](bool valid) {
            if (valid) {
                eve::StopGameEvent const eventRet{};
                app::AppContext::GetInstance().eventManager.InvokeEvent(eventRet);
                eve::DeletePlayerEvent const eventPlay{ id };
                this->DeletePlayer(&eventPlay);
            }
        } };
        if (not CheckValidAddRemovePlayer(l)) {
            return;
        }

        Player_ty toDelete{ nullptr };
        for (auto& p : m_players) {
            if (p->GetID() == event->GetID()) {
                toDelete = p;
                break;
            }
        }

        if (!toDelete) {
            eve::ShowMessagePopUpEvent const messageEvent{ appContext.languageManager.Text("helper_invalid_id"),
                                                           appContext.languageManager.Text(
                                                                   "ui_popup_invalid_id_subtitle", event->GetID()),
                                                           []() {} };
            app::AppContext::GetInstance().eventManager.InvokeEvent(messageEvent);
            return;
        }

        m_players.erase(std::remove(m_players.begin(), m_players.end(), toDelete), m_players.end());

        eve::DeletePlayerUIEvent const deleteEvent{ event->GetID() };
        app::AppContext::GetInstance().eventManager.InvokeEvent(deleteEvent);
    }

    void GameManager::ResetPlayer() {
        auto const l{ [&](bool valid) {
            if (valid) {
                eve::StopGameEvent const eventRet{};
                app::AppContext::GetInstance().eventManager.InvokeEvent(eventRet);
                this->ResetPlayer();
            }
        } };
        if (not CheckValidAddRemovePlayer(l)) {
            return;
        }

        m_players.clear();

        eve::ResetPlayerUIEvent const event{};
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void GameManager::KillPlayer(Player_ty const& player) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        player->Kill();
        m_galaxyManager.KillPlayer(player, m_npcs[PlayerType::NEUTRAL]);
        eve::ShowMessagePopUpEvent msg{ appContext.languageManager.Text("ui_popup_player_removed_title"),
                                        appContext.languageManager.Text("ui_popup_player_removed_subtitle"),
                                        [this]() {
                                            if (this->m_currentRoundPlayers.size() <= 1) {
                                                this->NextRound(true);
                                            } else {
                                                this->NextTurn(true);
                                            }
                                        } };
        appContext.eventManager.InvokeEvent(msg);
    }

    void GameManager::CheckPlayerCount() const {

        auto const l{ [this](bool valid) {
            if (valid) {
                eve::StopGameEvent const eventRet{};
                app::AppContext::GetInstance().eventManager.InvokeEvent(eventRet);
                this->CheckPlayerCount();
            }
        } };
        if (not CheckValidAddRemovePlayer(l)) {
            return;
        }

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        bool valid;

        if (m_players.size() < appContext.constants.player.minPlayerCount) {
            eve::ShowMessagePopUpEvent const event{
                appContext.languageManager.Text("ui_popup_player_count_title"),
                appContext.languageManager.Text(
                        "ui_popup_player_count_min_subtitle", '\n', appContext.constants.player.minPlayerCount),
                []() {}
            };
            appContext.eventManager.InvokeEvent(event);
            valid = false;
        } else if (m_players.size() > appContext.constants.player.maxPlayerCount) {
            eve::ShowMessagePopUpEvent const event{
                appContext.languageManager.Text("ui_popup_player_count_title"),
                appContext.languageManager.Text(
                        "ui_popup_player_count_max_subtitle", '\n', appContext.constants.player.maxPlayerCount),
                []() {}
            };
            appContext.eventManager.InvokeEvent(event);
            valid = false;
        } else {
            valid = true;
        }

        eve::ValidatePlayerCountResultEvent const event{ valid };
        appContext.eventManager.InvokeEvent(event);
    }

    void GameManager::ShuffleCurrentRoundPlayer() {
        if (not app::AppContext::GetInstance().constants.player.shuffle) {
            return;
        }

        std::shuffle(m_currentRoundPlayers.begin(), m_currentRoundPlayers.end(), m_random);

        hlp::Print(hlp::PrintType::ONLY_DEBUG, "player shuffled");
    }

    bool GameManager::CheckValidAddRemovePlayer(std::function<void(bool valid)> forPopup) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        if (appContext.constants.global.isGameRunning) {
            eve::ShowValidatePopUp const event{ appContext.languageManager.Text("ui_popup_game_still_running_title"),
                                                appContext.languageManager.Text("ui_popup_game_still_running_subtitle"),
                                                std::move(forPopup) };
            appContext.eventManager.InvokeEvent(event);
            return false;
        }
        return true;
    }

    void GameManager::SendCurrentPlayerID() {
        utl::usize ID;
        Player_ty player{ nullptr };

        if (GetCurrentPlayer(player)) {
            ID = player->GetID();
        } else {
            ID = 0;
        }

        eve::UpdateCurrentPlayerIDEvent const event{ ID };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void GameManager::SendNextPlayerID() {
        utl::usize ID;
        Player_ty player{ nullptr };

        if (GetNextPlayer(player)) {
            ID = player->GetID();
        } else {
            ID = 0;
        }

        eve::UpdateNextPlayerIDEvent const event{ ID };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    // rounds
    void GameManager::NextRound(bool const valid) {

        if (!valid) {
            return;
        }

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        appContext.constants.global.isGameSaved = false;
        // events and so on first
        Update();

        m_currentRoundPlayers = m_players;
        std::erase_if(m_currentRoundPlayers, [](Player_ty_c player) { return not player->IsAlive(); });
        ShuffleCurrentRoundPlayer();
        if (m_currentRoundPlayers.empty()) {
            hlp::Print(hlp::PrintType::TODO, "no possible moves for any player left. game should be over now.");
        }

        m_galaxyManager.CopyGalaxies(CopyGalaxyType::COPY_ALL);

        SendCurrentPlayerID();
        SendNextPlayerID();

        ++appContext.constants.global.currentRound;

        Player_ty player{};
        bool validPlayer{ GetCurrentPlayer(player) };
        if (not validPlayer) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "next round started -> can't get current player");
        } else {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "next round started -> player {}", player->GetID());
        }

        if (validPlayer) {
            if (not m_galaxyManager.HasMovesLeft(player)) {
                player->Kill();
                app::AppContext::GetInstance().eventManager.InvokeEvent(eve::ShowSkipTurnEvent{});
                return;
            }
        }

        appContext.eventManager.InvokeEvent(eve::ShowEvaluationEvent());
    }

    void GameManager::NextTurn(bool const valid) {

        if (!valid) {
            return;
        }

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        appContext.constants.global.isGameSaved = false;
        m_currentRoundPlayers.pop_back();

        m_galaxyManager.CopyGalaxies(CopyGalaxyType::COPY_START);

        SendCurrentPlayerID();
        SendNextPlayerID();

        Player_ty player{};
        bool validPlayer{ GetCurrentPlayer(player) };

        if (not validPlayer) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "next turn started -> can't get current player");
        } else {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "next turn started -> player {}", player->GetID());
        }

        if (validPlayer) {
            if (not m_galaxyManager.HasMovesLeft(player)) {
                player->Kill();
                app::AppContext::GetInstance().eventManager.InvokeEvent(eve::ShowSkipTurnEvent{});
                return;
            }
        }

        app::AppContext::GetInstance().eventManager.InvokeEvent(eve::ShowNextTurnEvent());
    }

    void GameManager::ValidateNextTurn() {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        if (m_currentRoundPlayers.size() <= 1) {
            eve::ShowValidatePopUp const event{
                appContext.languageManager.Text("logic_game_manager_popup_next_round_title", "?"),
                appContext.languageManager.Text("logic_game_manager_popup_next_round_text"),
                [this](bool valid) { this->NextRound(valid); }
            };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        } else {
            eve::ShowValidatePopUp const event{
                appContext.languageManager.Text("logic_game_manager_popup_next_turn_title", "?"),
                appContext.languageManager.Text("logic_game_manager_popup_next_turn_text"),
                [this](bool valid) { this->NextTurn(valid); }
            };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    // Fleet
    void GameManager::AddFleet(eve::SendFleetInstructionEvent const* const event) {

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        Player_ty currentPlayer{ nullptr };
        if (!GetCurrentPlayer(currentPlayer)) {
            popup(appContext.languageManager.Text("ui_popup_no_player_subtitle"));
            return;
        }

        bool const isValidFleet{ m_galaxyManager.AddFleet(event, currentPlayer) };
        eve::ReturnFleetInstructionEvent const returnEvent{ isValidFleet };
        appContext.eventManager.InvokeEvent(returnEvent);
    }

    // events
    std::vector<utl::ResultUpdate::event_ty> GameManager::UpdateEvents() {
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "-> update Events");
        auto const& constants = app::AppContext::GetInstance().constants;
        if (constants.gameEvents.isMinEventYear
            and constants.global.currentRound < constants.gameEvents.minEventYear) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG,
                       "no update of events because current year ({}) in smaller than min event year ({})",
                       constants.global.currentRound,
                       constants.gameEvents.minEventYear);
            return{};
        }
        std::array<utl::GameEventType, 6> constexpr events{
            // clang-format off
            utl::GameEventType::PIRATES,
            utl::GameEventType::REVOLTS,
            utl::GameEventType::RENEGADE_SHIPS,
            utl::GameEventType::BLACK_HOLE,
            utl::GameEventType::SUPERNOVA,
            utl::GameEventType::ENGINE_PROBLEM,
            // don't check for global. it just represents if all other events are active or not.
            // clang-format on
        };
        std::vector<utl::ResultUpdate::event_ty> toReturn{};
        for (auto const& e : events) {
            if (not IsSingleGameEvent(e)) {
                continue;
            }
            auto const result = RaiseEvent(e);
            if (not result) {
                continue;
            }
            toReturn.push_back(result);
        }
        return toReturn;

        /*
         * I tried to work with ranges.
         * It did not work out.
         * When I add 'filter([](auto const& e) { return e != nullptr; })' 'RaiseEvent(e)' gets executed 7 times
         * even tho there are just 6 events.
         * I can not figure out why that is.
         * So it stays as a for-loop for now.
         * If you know why. contact me. :)
         */
        // using std::ranges::views::filter, std::ranges::to, std::ranges::views::transform;
        /*
            return events | filter(IsSingleGameEvent)
             | transform([this](auto const& e) { return std::move(RaiseEvent(e)); })
             | filter([](auto const& e) { return e != nullptr; }) | to<std::vector>();
        */
        /*
            auto tmp0 = events | filter(IsSingleGameEvent);
            auto tmp1 = tmp0 | transform([this](auto const& e){return std::move(RaiseEvent(e));});
            // auto tmp2 = tmp1 | filter([](auto const& e){return e != nullptr;});
            auto tmp3 = tmp1 | to<std::vector>();
            return tmp3;
        */
    }

    bool GameManager::IsSingleGameEvent(utl::GameEventType type) {
        auto const& constants = app::AppContext::GetInstance().constants.gameEvents;

        if (not constants.IsFlag(type)) {
            return false;
        }

        auto const typeChance = constants.globalChance * constants.ChanceByType(type);
        auto& random          = hlp::Random::GetInstance();
        auto chance           = random.random(utl::Probability::maxValue);

        return chance < typeChance;
    }


    utl::ResultUpdate::event_ty GameManager::RaiseEvent(utl::GameEventType type) {
        switch (type) {
                // clang-format off
            case utl::GameEventType::PIRATES:        return HandlePirates();
            case utl::GameEventType::REVOLTS:        return HandleRevolts();
            case utl::GameEventType::RENEGADE_SHIPS: return HandleRenegadeShips();
            case utl::GameEventType::BLACK_HOLE:     return HandleBlackHole();
            case utl::GameEventType::SUPERNOVA:      return HandleSupernova();
            case utl::GameEventType::ENGINE_PROBLEM: return HandleEngineProblem();
            case utl::GameEventType::GLOBAL:         std::unreachable();
                // clang-format on
        }
        std::unreachable();
    }

    std::shared_ptr<utl::ResultEvent> GameManager::HandlePirates() {
        hlp::Print(hlp::PrintType::TODO, "Handle Pirate Event in GameManager");
        return {};
    }

    std::shared_ptr<utl::ResultEvent> GameManager::HandleRevolts() {
        hlp::Print(hlp::PrintType::TODO, "Handle Revolts Event in GameManager");
        return {};
    }

    std::shared_ptr<utl::ResultEvent> GameManager::HandleRenegadeShips() {
        hlp::Print(hlp::PrintType::TODO, "Handle Renegade Ships Event in GameManager");
        return {};
    }

    std::shared_ptr<utl::ResultEvent> GameManager::HandleBlackHole() {
        hlp::Print(hlp::PrintType::TODO, "Handle Black Hole Event in GameManager");
        return {};
    }

    std::shared_ptr<utl::ResultEvent> GameManager::HandleSupernova() {
        hlp::Print(hlp::PrintType::TODO, "Handle Supernova Event in GameManager");
        return m_galaxyManager.HandleSupernova();
    }

    std::shared_ptr<utl::ResultEventEngineProblem> GameManager::HandleEngineProblem() {
        auto const& appContext = app::AppContext::GetInstance();
        auto& random           = hlp::Random::GetInstance();
        auto const years       = random.random(appContext.constants.gameEvents.maxYearsEngineProblem) + 1;
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "Handle Engine Problem Event in GameManager ({} years)", years);
        return m_galaxyManager.HandleEngineProblem(years);
    }

    // game
    void GameManager::StartGame() {
        app::AppContext_ty appContext{ app::AppContext::GetInstance() };

        if (appContext.constants.global.isGameRunning and not appContext.constants.global.isGameSaved) {
            eve::ShowValidatePopUp const event{ appContext.languageManager.Text("ui_popup_game_still_running_title"),
                                                appContext.languageManager.Text("ui_popup_game_still_running_subtitle",
                                                                                '\n'),
                                                [this](bool valid) {
                                                    if (valid) {
                                                        GameManager::StopGame();
                                                        this->StartGame();
                                                    }
                                                } };
            appContext.eventManager.InvokeEvent(event);
            return;
        }

        m_currentRoundPlayers = m_players;

        ShuffleCurrentRoundPlayer();
        SendCurrentPlayerID();
        SendNextPlayerID();
        for (auto const& p : m_players) {
            p->Revive();
        }

        appContext.constants.global.currentRound  = 1;
        appContext.constants.global.isGameRunning = true;
        appContext.constants.global.isGamePaused  = false;
        appContext.constants.global.isGameSaved   = false;

        Player_ty player{};
        if (not GetCurrentPlayer(player)) {
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "game started -> can't get current player");
        }

        hlp::Print(hlp::PrintType::ONLY_DEBUG, "game started -> player {}", player->GetID());
        eve::SwitchMainSceneEvent const event{};
        appContext.eventManager.InvokeEvent(event);
    }

    void GameManager::StopGame() {
        app::AppContext_ty appConstants{ app::AppContext::GetInstance() };
        appConstants.constants.global.isGameRunning = false;
        appConstants.constants.global.isGamePaused  = true;
        appConstants.aliasManager.Clear();
        m_currentRoundPlayers.clear();
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "game stopped and paused");
    }

    void GameManager::PauseGame() {
        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        appContext.constants.global.isGamePaused = true;
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "game paused");
    }

    void GameManager::ResumeGame() {
        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        if (not appContext.constants.global.isGameRunning) {
            eve::ShowMessagePopUpEvent const event{ appContext.languageManager.Text("ui_popup_no_game_title"),
                                                    appContext.languageManager.Text("ui_popup_no_game_subtitle"),
                                                    []() {} };
            appContext.eventManager.InvokeEvent(event);
            hlp::Print(hlp::PrintType::ONLY_DEBUG, "not able to resume to game because its no game running");
            return;
        }
        appContext.constants.global.isGamePaused = false;
        hlp::Print(hlp::PrintType::ONLY_DEBUG, "resumed to game");
        eve::SwitchMainSceneEvent const event{};
        appContext.eventManager.InvokeEvent(event);
    }

    void GameManager::QuitGame() {
        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        if (not appContext.constants.global.isGameSaved) {
            eve::ShowValidatePopUp const event{ appContext.languageManager.Text("ui_popup_not_saved_title"),
                                                appContext.languageManager.Text("ui_popup_not_saved_subtitle", '\n'),
                                                [this](bool valid) {
                                                    if (valid) {
                                                        app::AppContext::GetInstance().constants.global.isGameSaved =
                                                                true;
                                                        this->QuitGame();
                                                    }
                                                } };
            appContext.eventManager.InvokeEvent(event);
            return;
        }

        eve::CloseWindowEvent const event{};
        appContext.eventManager.InvokeEvent(event);
    }

    GameManager::GameManager() : m_galaxyManager{ this } {

        app::AppContext::GetInstance().eventManager.AddListener(this);
        m_npcs[PlayerType::NEUTRAL] = std::make_shared<Player>(100, PlayerType::NEUTRAL);

        hlp::Print(hlp::PrintType::INITIALIZE, "GameManager");
    }

    GameManager::~GameManager() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    void GameManager::Update() {
        auto result         = UpdateEvents();
        m_lastUpdateResults = m_galaxyManager.Update();
        m_lastUpdateResults.SetEvents(std::move(result));
    }

    void GameManager::OnEvent(eve::Event const& event) {

        // Player
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::AddPlayerEvent const*>(&event)) {
            AddPlayer(playerEvent);
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::EditPlayerEvent const*>(&event)) {
            EditPlayer(playerEvent);
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::DeletePlayerEvent const*>(&event)) {
            DeletePlayer(playerEvent);
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::ResetPlayerEvent const*>(&event)) {
            ResetPlayer();
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::ValidatePlayerCountEvent const*>(&event)) {
            CheckPlayerCount();
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::LoadCurrentPlayerEvent const*>(&event)) {
            SendCurrentPlayerID();
            SendNextPlayerID();
            return;
        }
        if ([[maybe_unused]] auto const* PlayerEvent = dynamic_cast<eve::KillCurrentPlayerEvent const*>(&event)) {
            app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
            auto msgEvent{
                eve::ShowValidatePopUp{ appContext.languageManager.Text("ui_popup_resign_title", '?'),
                                       appContext.languageManager.Text("ui_popup_resign_subtitle"),
                                       [this](bool valid) {
                                            if (not valid) {
                                                return;
                                            }
                                            Player_ty player;
                                            if (not this->GetCurrentPlayer(player)) {
                                                return;
                                            }
                                            this->KillPlayer(player);
                                        } }
            };
            appContext.eventManager.InvokeEvent(msgEvent);
            return;
        }

        // Galaxy
        if ([[maybe_unused]] auto const* galaxyEvent = dynamic_cast<eve::GenerateGalaxyEvent const*>(&event)) {
            m_galaxyManager.GenerateGalaxy();
            return;
        }
        if ([[maybe_unused]] auto const* galaxyEvent = dynamic_cast<eve::GetGalaxyPointerEvent const*>(&event)) {
            eve::SendGalaxyRepresentationEvent const returnEvent{ GenGalaxyRep(m_galaxyManager.GetGalaxy()), false };
            app::AppContext::GetInstance().eventManager.InvokeEvent(returnEvent);
            return;
        }
        if ([[maybe_unused]] auto const* galaxyEvent = dynamic_cast<eve::GetShowGalaxyPointerEvent const*>(&event)) {
            m_galaxyManager.GenerateShowGalaxy();
            return;
        }

        // Game
        if ([[maybe_unused]] auto const* gameEvent = dynamic_cast<eve::StartGameEvent const*>(&event)) {
            StartGame();
            return;
        }
        if ([[maybe_unused]] auto const* gameEvent = dynamic_cast<eve::StopGameEvent const*>(&event)) {
            StopGame();
            return;
        }
        if ([[maybe_unused]] auto const* gameEvent = dynamic_cast<eve::PauseGameEvent const*>(&event)) {
            PauseGame();
            return;
        }
        if ([[maybe_unused]] auto const* gameEvent = dynamic_cast<eve::ResumeGameEvent const*>(&event)) {
            ResumeGame();
            return;
        }
        if ([[maybe_unused]] auto const* gameEvent = dynamic_cast<eve::QuitGameEvent const*>(&event)) {
            QuitGame();
            return;
        }
        if ([[maybe_unused]] auto const* gameEvent = dynamic_cast<eve::TriggerNextTurnEvent const*>(&event)) {
            ValidateNextTurn();
            return;
        }
        if ([[maybe_unused]] auto const* gameEvent = dynamic_cast<eve::GetUpdateEvaluation const*>(&event)) {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::SendUpdateEvaluation{ m_lastUpdateResults });
            return;
        }

        // Fleet
        if (auto const* fleetEvent = dynamic_cast<eve::SendFleetInstructionEvent const*>(&event)) {
            AddFleet(fleetEvent);
            return;
        }
    }
} // namespace lgk
