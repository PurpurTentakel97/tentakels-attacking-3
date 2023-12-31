//
// Purpur Tentakel
// 11.10.2022
//

#include <AppContext.hpp>
#include <PlayerCollection.hpp>
#include <algorithm>
#include <event/EventGeneral.hpp>
#include <event/EventsUI.hpp>
#include <stdexcept>


namespace app {
    bool PlayerCollection::ContainsName(std::string const& name) const {
        for (auto const& p : m_playerData) {
            if (p.GetName() == name) {
                return true;
            }
        }

        for (auto const& p : m_npcData) {
            if (p.GetName() == name) {
                return true;
            }
        }

        return false;
    }

    bool PlayerCollection::ContainsColor(Color const color) const {
        for (auto const& p : m_playerData) {
            if (p.color == color) {
                return true;
            }
        }

        for (auto const& p : m_npcData) {
            if (p.color == color) {
                return true;
            }
        }

        return false;
    }

    void PlayerCollection::CheckValidColor(Color& color) const {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        if (appContext.colors.CheckValidColor(color)) {
            eve::ShowMessagePopUpEvent const event{
                appContext.languageManager.Text("helper_player_collection_invalid_color_popup_title"),
                appContext.languageManager.Text("helper_player_collection_already_existing_color_popup_text"),
                []() {}
            };
            appContext.eventManager.InvokeEvent(event);
            color = GetPossibleColor();
        }
    }

    void PlayerCollection::CheckRemainingColor(Color& color) {
        if (ContainsColor(color)) {
            app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
            eve::ShowMessagePopUpEvent const event{
                appContext.languageManager.Text("helper_player_collection_invalid_color_popup_title"),
                appContext.languageManager.Text("helper_player_collection_already_existing_color_popup_text"),
                []() {}
            };
            appContext.eventManager.InvokeEvent(event);
            color = GetPossibleColor();
        }
    }

    void PlayerCollection::CheckRemainingName(std::string& name) {

        bool invalidName{ false };
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        if (name.empty()) {
            eve::ShowMessagePopUpEvent const event{
                appContext.languageManager.Text("helper_player_collection_invalid_name_popup_title"),
                appContext.languageManager.Text("helper_player_collection_no_name_popup_text."),
                []() {}
            };
            appContext.eventManager.InvokeEvent(event);
            invalidName = true;
        }

        if (ContainsName(name)) {
            eve::ShowMessagePopUpEvent const event{
                appContext.languageManager.Text("helper_player_collection_invalid_name_popup_title"),
                appContext.languageManager.Text("helper_player_collection_already_existing_name_popup_text"),
                []() {}
            };
            appContext.eventManager.InvokeEvent(event);
            invalidName = true;
        }

        if (invalidName) {
            static utl::usize invalidNameCounter{ 1 };
            name = appContext.languageManager.Text("helper_player_collection_invalid_name_popup_title") + " "
                   + std::to_string(invalidNameCounter);
            ++invalidNameCounter;
        }
    }

    PlayerData& PlayerCollection::GetPlayerByIDmut(utl::usize const ID) {

        for (auto& p : m_playerData) {
            if (p.ID == ID) {
                return p;
            }
        }

        // skip ncps here because it makes no sense to return them as a player

        throw std::out_of_range("Accessing non existing ID");
    }

    void PlayerCollection::SortPlayers() {
        std::sort(m_playerData.begin(), m_playerData.end(), SortPlayerByID_ASC);
    }

    void PlayerCollection::AddPlayer(utl::usize ID, std::string name, Color color) {

        CheckValidColor(color);
        CheckRemainingColor(color);
        CheckRemainingName(name);

        m_playerData.emplace_back(ID, name, color);
        SortPlayers();
        eve::RefreshNewGamePlayerScene const event{};
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void PlayerCollection::EditPlayer(utl::usize const ID, std::string name, Color color) {

        PlayerData& playerData{ GetPlayerByIDmut(ID) };

        if (playerData.GetName() != name) {
            CheckRemainingName(name);
            playerData.SetName(name);
        }

        if (playerData.color != color) {
            CheckValidColor(color);
            CheckRemainingColor(color);
            playerData.color = color;
        }

        SortPlayers();
        eve::RefreshNewGamePlayerScene const event{};
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void PlayerCollection::DeletePlayer(utl::usize const ID) {
        auto const& toDelete{ GetPlayerByIDmut(ID) };

        m_playerData.erase(std::remove(m_playerData.begin(), m_playerData.end(), toDelete), m_playerData.end());

        SortPlayers();
        eve::RefreshNewGamePlayerScene const event{};
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void PlayerCollection::ResetPlayer() {
        m_playerData.clear();
        eve::RefreshNewGamePlayerScene const event{};
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    Color PlayerCollection::GetPossibleColor() const {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        for (auto const c : appContext.colors.GetColors()) {
            if (!ContainsColor(c)) {
                return c;
            }
        }
        return appContext.colors.GetColors().at(0);
    }

    std::vector<PlayerData> PlayerCollection::GetPlayerData() const {
        return m_playerData;
    }

    PlayerData PlayerCollection::GetPlayerByID(utl::usize const ID) const {

        if (ID == m_defaultPlayer.ID) {
            return m_defaultPlayer;
        }

        for (auto const& p : m_playerData) {
            if (p.ID == ID) {
                return p;
            }
        }

        throw std::out_of_range("Accessing non existing ID");
    }

    PlayerData PlayerCollection::GetPlayerOrNpcByID(utl::usize const ID) const {

        for (auto const& p : m_npcData) {
            if (p.ID == ID) {
                return p;
            }
        }

        return GetPlayerByID(ID);
    }

    PlayerData PlayerCollection::GetPlayerByIDOrDefaultPlayer(utl::usize const ID) const {

        for (auto const& p : m_playerData) {
            if (ID == p.ID) {
                return p;
            }
        }

        return m_defaultPlayer;
    }

    PlayerData PlayerCollection::GetPlayerByName(std::string const& name) const {
        for (auto const& p : m_playerData) {
            if (p.GetName() == name) {
                return p;
            }
        }

        throw std::out_of_range("Accessing non existing Name");
    }

    PlayerData PlayerCollection::GetPlayerByColor(Color const color) const {
        for (auto const& p : m_playerData) {
            if (p.color == color) {
                return p;
            }
        }

        throw std::out_of_range("Accessing non existing Color");
    }

    Color PlayerCollection::GetColorByID(utl::usize const ID) const {
        for (auto const& p : m_playerData) {
            if (p.ID == ID) {
                return p.color;
            }
        }
        return WHITE;
    }

    utl::usize PlayerCollection::GetPlayerCount() const {
        return m_playerData.size();
    }

    void PlayerCollection::OnEvent(eve::Event const& event) {

        if (auto const* playerEvent = dynamic_cast<eve::AddPlayerUIEvent const*>(&event)) {
            AddPlayer(playerEvent->GetID(), playerEvent->GetName(), playerEvent->GetColor());
            return;
        }
        if (auto const* playerEvent = dynamic_cast<eve::EditPlayerUIEvent const*>(&event)) {
            EditPlayer(playerEvent->GetID(), playerEvent->GetName(), playerEvent->GetColor());
            return;
        }
        if (auto const* playerEvent = dynamic_cast<eve::DeletePlayerUIEvent const*>(&event)) {
            DeletePlayer(playerEvent->GetID());
            return;
        }
        if ([[maybe_unused]] auto const* playerEvent = dynamic_cast<eve::ResetPlayerUIEvent const*>(&event)) {
            ResetPlayer();
            return;
        }
    }
} // namespace app
