//
// Purpur Tentakel
// 06.10.2022
//


#include "SceneNewGamePlayer.hpp"
#include "ManagerUI.hpp"
#include <alias/AliasUtils.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HFocusEvents.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/ColorPicker.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/Table.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>


namespace ui {
    void NewGamePlayerScene::Initialize() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        auto title = std::make_shared<uil::Title>(
                GetElementPosition(0.5f, 0.025f), GetElementSize(0.8f, 0.25f), uil::Alignment::TOP_MID, false);
        m_elements.push_back(title);

        auto addPlayerText = std::make_shared<uil::Text>(
                GetElementPosition(0.1f, 0.28f),
                GetElementSize(0.25f, 0.05f),
                uil::Alignment::TOP_LEFT,
                uil::Alignment::TOP_LEFT,
                0.05f,
                appContext.languageManager.Text("scene_new_game_player_add_player_headline", ":"));
        m_elements.push_back(addPlayerText);

        m_inputLine = std::make_shared<uil::InputLine>(1,
                                                       GetElementPosition(0.1f, 0.35f),
                                                       GetElementSize(0.35f, 0.05f),
                                                       uil::Alignment::TOP_LEFT,
                                                       std::string());
        m_inputLine->SetPlaceholderText(
                appContext.languageManager.Text("scene_new_game_player_player_name_placeholder"));
        m_inputLine->SetOnEnter([this](uil::InputLine&) { this->AddPlayer(); });
        m_elements.push_back(m_inputLine);


        m_colorPicker = std::make_shared<uil::ColorPicker>(
                2, GetElementPosition(0.1f, 0.45f), GetElementSize(0.35f, 0.35f), uil::Alignment::TOP_LEFT);
        m_colorPicker->SetColor(appContext.playerCollection.GetPossibleColor());
        m_colorPicker->SetOnEnter([this]() { this->AddPlayer(); });
        m_elements.push_back(m_colorPicker);
        m_nestedFocus.push_back(m_colorPicker.get());

        auto resetBTN =
                std::make_shared<uil::ClassicButton>(7,
                                                     GetElementPosition(0.45f, 0.85f),
                                                     GetElementSize(0.15f, 0.1f),
                                                     uil::Alignment::TOP_RIGHT,
                                                     appContext.languageManager.Text("scene_new_game_player_reset_btn"),
                                                     app::SoundType::ACCEPTED);
        resetBTN->SetOnClick([]() { NewGamePlayerScene::Reset(); });
        m_elements.push_back(resetBTN);

        auto backBtn =
                std::make_shared<uil::ClassicButton>(8,
                                                     GetElementPosition(0.1f, 0.85f),
                                                     GetElementSize(0.15f, 0.1f),
                                                     uil::Alignment::TOP_LEFT,
                                                     appContext.languageManager.Text("scene_new_game_player_back_btn"),
                                                     app::SoundType::CLICKED_RELEASE_STD);
        backBtn->SetOnClick([]() {
            app::AppContext::GetInstance().eventManager.InvokeEvent(eve::SwitchSceneEvent(uil::SceneType::MAIN_MENU));
        });
        m_elements.push_back(backBtn);

        auto line = std::make_shared<uil::Line>(
                GetElementPosition(0.5f, 0.25f), GetElementPosition(0.5f, 0.95f), 2.0f, WHITE);
        m_elements.push_back(line);

        auto currentPlayerText = std::make_shared<uil::Text>(
                GetElementPosition(0.55f, 0.28f),
                GetElementSize(0.25f, 0.05f),
                uil::Alignment::TOP_LEFT,
                uil::Alignment::TOP_LEFT,
                0.05f,
                appContext.languageManager.Text("scene_new_game_player_current_player_headline", ":"));
        m_elements.push_back(currentPlayerText);

        auto currentPlayerCount = std::make_shared<uil::Text>(
                GetElementPosition(0.55f, 0.33f),
                GetElementSize(0.25f, 0.05f),
                uil::Alignment::TOP_LEFT,
                uil::Alignment::TOP_LEFT,
                0.02f,
                appContext.languageManager.Text("scene_new_game_player_min_player_count_subtext",
                                                ":",
                                                appContext.constants.player.minPlayerCount));
        m_elements.push_back(currentPlayerCount);

        m_table = std::make_shared<uil::Table>(GetElementPosition(0.9f, 0.35f),
                                               GetElementSize(0.35f, 0.45f),
                                               uil::Alignment::TOP_RIGHT,
                                               5,
                                               static_cast<int>(appContext.constants.player.maxPlayerCount + 1),
                                               3,
                                               Vector2(0.33f, 0.1f),
                                               0.1f);
        m_table->SetRowEditable(0, false);
        m_table->SetColumnEditable(0, false);
        m_table->SetHeadlineValues<std::string>({
                appContext.languageManager.Text("scene_new_game_player_table_headline_id"),
                appContext.languageManager.Text("scene_new_game_player_table_headline_name"),
                appContext.languageManager.Text("scene_new_game_player_table_headline_color"),
        });

        m_table->SetUpdateCellType<std::string>([this](uil::TableCell& cell) { this->UpdatePlayerName(cell); });
        m_table->SetUpdateCellType<Color>([this](uil::TableCell& cell) { this->UpdatePlayerColor(cell); });
        m_table->SetHighlightHover(true);

        m_elements.push_back(m_table);
        m_nestedFocus.push_back(m_table.get());

        auto addPlayerBtn = std::make_shared<uil::ClassicButton>(
                3,
                GetElementPosition(0.55f, 0.85f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::TOP_LEFT,
                appContext.languageManager.Text("scene_new_game_player_add_player_btn"),
                app::SoundType::ACCEPTED);
        addPlayerBtn->SetOnClick([this]() { this->AddPlayer(); });
        m_elements.push_back(addPlayerBtn);

        m_nextBTN =
                std::make_shared<uil::ClassicButton>(6,
                                                     GetElementPosition(0.9f, 0.85f),
                                                     GetElementSize(0.15f, 0.1f),
                                                     uil::Alignment::TOP_RIGHT,
                                                     appContext.languageManager.Text("scene_new_game_player_next_btn"),
                                                     app::SoundType::ACCEPTED);
        m_nextBTN->SetOnClick([]() { NewGamePlayerScene::CheckPlayerCount(); });
        m_elements.push_back(m_nextBTN);

        InitializePlayerButtons();
    }

    void NewGamePlayerScene::InitializePlayerButtons() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        utl::usize const maxPlayerCount{ appContext.constants.player.maxPlayerCount };
        utl::usize const currentPlayerCount{ appContext.playerCollection.GetPlayerCount() };
        float const rowHeight{ 0.45f / static_cast<float>(maxPlayerCount + 1) };
        float const initialY{ 0.35f + rowHeight };

        for (utl::usize i = 0; i < maxPlayerCount; ++i) {
            auto button = std::make_shared<uil::ClassicButton>(
                    static_cast<int>(100 + i),
                    GetElementPosition(0.905f, initialY + rowHeight * static_cast<float>(i) + 0.005f),
                    GetElementSize(rowHeight * 0.7f, rowHeight - 0.01f),
                    uil::Alignment::TOP_LEFT,
                    "X",
                    app::SoundType::CLICKED_RELEASE_STD);

            button->SetEnabled(i < currentPlayerCount);
            button->SetOnClick([i]() { NewGamePlayerScene::DeletePlayer(i + 1); });

            m_elements.push_back(button);
            m_playerButtons.push_back(button);
        }
    }

    void NewGamePlayerScene::CheckForNestedFocus(Vector2 const& mousePosition) const {
        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return;
        }

        for (auto f : m_nestedFocus) {
            if (!f->IsFocused()) {
                continue;
            }
            if (!f->IsNestedFocus()) {
                continue;
            }

            if (!CheckCollisionPointRec(mousePosition, f->GetCollider())) {
                f->SetNestedFocus(false);
                hlp::DeleteFocusLayer();
            }
        }
    }

    void NewGamePlayerScene::UpdateSceneEntries() {
        m_updating = true;
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        m_colorPicker->SetColor(appContext.playerCollection.GetPossibleColor());

        m_inputLine->Clear();
        if (m_colorPicker->IsNestedFocus()) {
            m_colorPicker->SetNestedFocus(false);
            eve::DeleteFocusLayerEvent const focusEvent;
            appContext.eventManager.InvokeEvent(focusEvent);
        }

        eve::SelectFocusElementEvent const event{ m_inputLine.get() };
        appContext.eventManager.InvokeEvent(event);

        auto const PlayerData{ appContext.playerCollection.GetPlayerData() };

        utl::usize index{ 1 };
        for (auto& p : PlayerData) {
            m_table->SetValue(index, 0, p.ID);
            m_table->SetValue(index, 1, p.GetName());
            m_table->SetValue(index, 2, p.color);

            m_table->SetSingleEditable(index, 1, true);
            m_table->SetSingleEditable(index, 2, true);

            utl::usize ID_{ p.ID };
            m_playerButtons.at(index - 1)->SetEnabled(true);
            m_playerButtons.at(index - 1)->SetOnClick([ID_]() { NewGamePlayerScene::DeletePlayer(ID_); });

            ++index;
        }
        for (utl::usize row = index; row < m_table->GetRowCount(); ++row) {
            for (utl::usize column = 0; column < m_table->GetColumnCount(); ++column) {
                m_table->SetValue<std::string>(row, column, "");
                m_table->SetSingleEditable(row, column, false);
            }
            m_playerButtons.at(row - 1)->SetEnabled(false);
        }
        m_updating = false;
    }

    void NewGamePlayerScene::AddPlayer() {
        app::AppContext_ty_c appContext = app::AppContext::GetInstance();

        eve::AddPlayerEvent const event{ m_inputLine->Value<std::string>(), m_colorPicker->GetColor() };
        appContext.eventManager.InvokeEvent(event);
    }

    void NewGamePlayerScene::UpdatePlayer(utl::usize const ID, std::string const& name, Color const color) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        eve::EditPlayerEvent const event{ ID, name, color };
        appContext.eventManager.InvokeEvent(event);

        UpdateSceneEntries();
    }

    void NewGamePlayerScene::UpdatePlayerName(uil::TableCell& cell) {
        if (m_updating) {
            return;
        }

        bool const valid{ cell.IsA<std::string>() and cell.IsAOld<std::string>() };
        if (not valid) {
            return;
        }

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        app::PlayerData const playerData{ appContext.playerCollection.GetPlayerByName(cell.ValueOld<std::string>()) };

        UpdatePlayer(playerData.ID, cell.Value<std::string>(), playerData.color);
    }

    void NewGamePlayerScene::UpdatePlayerColor(uil::TableCell& cell) {
        if (m_updating) {
            return;
        }

        bool const valid{ cell.IsA<Color>() and cell.IsAOld<Color>() };
        if (not valid) {
            return;
        }

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        app::PlayerData const playerData{ appContext.playerCollection.GetPlayerByColor(cell.ValueOld<Color>()) };

        UpdatePlayer(playerData.ID, playerData.GetName(), cell.Value<Color>());
    }

    void NewGamePlayerScene::DeletePlayer(utl::usize const ID) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        eve::DeletePlayerEvent const event{ ID };
        appContext.eventManager.InvokeEvent(event);
    }

    void NewGamePlayerScene::CheckPlayerCount() {
        eve::ValidatePlayerCountEvent const event;
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void NewGamePlayerScene::NextScene(bool const valid) {
        if (!valid) {
            return;
        }

        eve::SwitchSceneEvent const event{ uil::SceneType::NEW_GAME_PARAMETER };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    void NewGamePlayerScene::Reset() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        eve::ResetPlayerEvent const event;
        appContext.eventManager.InvokeEvent(event);
    }

    void NewGamePlayerScene::SetNextButton() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        utl::usize const playerCount{ appContext.playerCollection.GetPlayerData().size() };
        bool const validPlayerCount{ playerCount >= appContext.constants.player.minPlayerCount
                                     and playerCount <= appContext.constants.player.maxPlayerCount };

        if (validPlayerCount != m_nextBTN->IsEnabled()) {
            m_nextBTN->SetEnabled(validPlayerCount);
        }
    }

    NewGamePlayerScene::NewGamePlayerScene()
        : Scene{
              { 0.0f, 0.0f },
              { 1.0f, 1.0f },
              uil::Alignment::DEFAULT
    } {

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        Initialize();
        UpdateSceneEntries();
        appContext.eventManager.AddListener(this);
    }

    NewGamePlayerScene::~NewGamePlayerScene() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    void NewGamePlayerScene::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        CheckForNestedFocus(mousePosition);

        SetNextButton();

        for (auto& e : m_elements) {
            e->CheckAndUpdate(mousePosition, appContext);
        }
    }

    void NewGamePlayerScene::Render(app::AppContext_ty_c appContext) {
        for (auto& e : m_elements) {
            e->Render(appContext);
        }
    }

    void NewGamePlayerScene::Resize(app::AppContext_ty_c appContext) {
        for (auto& e : m_elements) {
            e->Resize(appContext);
        }
    }

    void NewGamePlayerScene::OnEvent(eve::Event const& event) {

        if (auto const* CountEvent = dynamic_cast<eve::ValidatePlayerCountResultEvent const*>(&event)) {
            NextScene(CountEvent->GetValid());
            return;
        }
        if ([[maybe_unused]] auto const* RefreshEvent = dynamic_cast<eve::RefreshNewGamePlayerScene const*>(&event)) {
            UpdateSceneEntries();
            return;
        }
    }
} // namespace ui
