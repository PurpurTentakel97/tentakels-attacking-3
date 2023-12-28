//
// Purpur Tentakel
// 06.10.2022
//

#include "SceneNewGamePlayer.hpp"
#include "ManagerUI.hpp"
#include <event/EventGenerel.hpp>
#include <helper/HFocusEvents.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/ColorPicker.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/Table.hpp>
#include <ui_lib/Text.hpp>
#include <ui_lib/Title.hpp>

void NewGamePlayerScene::Initialize() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    auto title = std::make_shared<Title>(
            GetElementPosition(0.5f, 0.025f),
            GetElementSize(0.8f, 0.25f),
            Alignment::TOP_MID,
            false
    );
    m_elements.push_back(title);

    auto addPlayerText = std::make_shared<Text>(
            GetElementPosition(0.1f, 0.28f),
            GetElementSize(0.25f, 0.05f),
            Alignment::TOP_LEFT,
            Alignment::TOP_LEFT,
            0.05f,
            appContext.languageManager.Text("scene_new_game_player_add_player_headline", ":")
    );
    m_elements.push_back(addPlayerText);

    auto inputLine = std::make_shared<InputLine<std::string>>(
            1,
            GetElementPosition(0.1f, 0.35f),
            GetElementSize(0.35f, 0.05f),
            Alignment::TOP_LEFT,
            20
    );
    inputLine->SetPlaceholderText(appContext.languageManager.Text("scene_new_game_player_player_name_placeholder"));
    inputLine->SetOnEnter([this]() { this->AddPlayer(); });
    m_elements.push_back(inputLine);
    m_inputLine = inputLine.get();

    auto colorPicker = std::make_shared<ColorPicker>(
            2,
            GetElementPosition(0.1f, 0.45f),
            GetElementSize(0.35f, 0.35f),
            Alignment::TOP_LEFT
    );
    colorPicker->SetColor(appContext.playerCollection.GetPossibleColor());
    colorPicker->SetOnEnter([this]() { this->AddPlayer(); });
    m_elements.push_back(colorPicker);
    m_nestedFocus.push_back(colorPicker.get());
    m_colorPicker = colorPicker.get();

    auto resetBTN = std::make_shared<ClassicButton>(
            7,
            GetElementPosition(0.45f, 0.85f),
            GetElementSize(0.15f, 0.1f),
            Alignment::TOP_RIGHT,
            appContext.languageManager.Text("scene_new_game_player_reset_btn"),
            SoundType::ACCEPTED
    );
    resetBTN->SetOnClick([]() { NewGamePlayerScene::Reset(); });
    m_elements.push_back(resetBTN);

    auto backBtn = std::make_shared<ClassicButton>(
            8,
            GetElementPosition(0.1f, 0.85f),
            GetElementSize(0.15f, 0.1f),
            Alignment::TOP_LEFT,
            appContext.languageManager.Text("scene_new_game_player_back_btn"),
            SoundType::CLICKED_RELEASE_STD
    );
    backBtn->SetOnClick([]() {
        AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::MAIN_MENU));
    });
    m_elements.push_back(backBtn);

    auto line = std::make_shared<Line>(GetElementPosition(0.5f, 0.25f), GetElementPosition(0.5f, 0.95f), 2.0f, WHITE);
    m_elements.push_back(line);

    auto currentPlayerText = std::make_shared<Text>(
            GetElementPosition(0.55f, 0.28f),
            GetElementSize(0.25f, 0.05f),
            Alignment::TOP_LEFT,
            Alignment::TOP_LEFT,
            0.05f,
            appContext.languageManager.Text("scene_new_game_player_current_player_headline", ":")
    );
    m_elements.push_back(currentPlayerText);

    auto currentPlayerCount = std::make_shared<Text>(
            GetElementPosition(0.55f, 0.33f),
            GetElementSize(0.25f, 0.05f),
            Alignment::TOP_LEFT,
            Alignment::TOP_LEFT,
            0.02f,
            appContext.languageManager.Text(
                    "scene_new_game_player_min_player_count_subtext",
                    ":",
                    appContext.constants.player.minPlayerCount
            )
    );
    m_elements.push_back(currentPlayerCount);

    auto table = std::make_shared<Table>(
            GetElementPosition(0.9f, 0.35f),
            GetElementSize(0.35f, 0.45f),
            Alignment::TOP_RIGHT,
            5,
            static_cast<int>(appContext.constants.player.maxPlayerCount + 1),
            3,
            Vector2(0.33f, 0.1f),
            0.1f
    );
    table->SetRowEditable(0, false);
    table->SetColumnEditable(0, false);
    table->SetHeadlineValues<std::string>({
            appContext.languageManager.Text("scene_new_game_player_table_headline_id"),
            appContext.languageManager.Text("scene_new_game_player_table_headline_name"),
            appContext.languageManager.Text("scene_new_game_player_table_headline_color"),
    });

    table->SetUpdateSpecificCell<std::string>(
            [this](AbstractTableCell const* cell, std::string const& oldValue, std::string const& newValue) {
                this->UpdatePlayerName(cell, oldValue, newValue);
            }
    );
    table->SetUpdateSpecificCell<Color>([this](AbstractTableCell const* cell, Color oldValue, Color newValue) {
        UpdatePlayerColor(cell, oldValue, newValue);
    });

    m_elements.push_back(table);
    m_nestedFocus.push_back(table.get());
    m_table = table.get();

    auto addPlayerBtn = std::make_shared<ClassicButton>(
            3,
            GetElementPosition(0.55f, 0.85f),
            GetElementSize(0.15f, 0.1f),
            Alignment::TOP_LEFT,
            appContext.languageManager.Text("scene_new_game_player_add_player_btn"),
            SoundType::ACCEPTED
    );
    addPlayerBtn->SetOnClick([this]() { this->AddPlayer(); });
    m_elements.push_back(addPlayerBtn);

    m_nextBTN = std::make_shared<ClassicButton>(
            6,
            GetElementPosition(0.9f, 0.85f),
            GetElementSize(0.15f, 0.1f),
            Alignment::TOP_RIGHT,
            appContext.languageManager.Text("scene_new_game_player_next_btn"),
            SoundType::ACCEPTED
    );
    m_nextBTN->SetOnClick([]() { NewGamePlayerScene::CheckPlayerCount(); });
    m_elements.push_back(m_nextBTN);

    InitializePlayerButtons();
}

void NewGamePlayerScene::InitializePlayerButtons() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    size_t const maxPlayerCount{ appContext.constants.player.maxPlayerCount };
    size_t const currentPlayerCount{ appContext.playerCollection.GetPlayerCount() };
    float const rowHeight{ 0.45f / static_cast<float>(maxPlayerCount + 1) };
    float const initialY{ 0.35f + rowHeight };

    for (size_t i = 0; i < maxPlayerCount; ++i) {
        auto button = std::make_shared<ClassicButton>(
                static_cast<int>(100 + i),
                GetElementPosition(0.905f, initialY + rowHeight * static_cast<float>(i) + 0.005f),
                GetElementSize(rowHeight * 0.7f, rowHeight - 0.01f),
                Alignment::TOP_LEFT,
                "X",
                SoundType::CLICKED_RELEASE_STD
        );

        button->SetEnabled(i < currentPlayerCount);
        button->SetOnClick([i]() { NewGamePlayerScene::DeletePlayer(static_cast<unsigned int>(i + 1)); });

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
            DeleteFocusLayer();
        }
    }
}

void NewGamePlayerScene::UpdateSceneEntries() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    m_colorPicker->SetColor(appContext.playerCollection.GetPossibleColor());

    m_inputLine->Clear();
    if (m_colorPicker->IsNestedFocus()) {
        m_colorPicker->SetNestedFocus(false);
        DeleteFocusLayerEvent const focusEvent;
        appContext.eventManager.InvokeEvent(focusEvent);
    }

    SelectFocusElementEvent const event{ m_inputLine };
    appContext.eventManager.InvokeEvent(event);

    auto const PlayerData{ appContext.playerCollection.GetPlayerData() };

    size_t index{ 1 };
    for (auto& p : PlayerData) {
        m_table->SetValue<int>(index, 0, static_cast<int>(p.ID));
        m_table->SetValue<std::string>(index, 1, p.GetName());
        m_table->SetValue<Color>(index, 2, p.color);

        m_table->SetSingleEditable(index, 1, true);
        m_table->SetSingleEditable(index, 2, true);

        unsigned int ID_{ p.ID };
        m_playerButtons.at(index - 1)->SetEnabled(true);
        m_playerButtons.at(index - 1)->SetOnClick([ID_]() { NewGamePlayerScene::DeletePlayer(ID_); });

        ++index;
    }
    for (size_t row = index; row < m_table->GetRowCount(); ++row) {
        for (size_t column = 0; column < m_table->GetColumnCount(); ++column) {
            m_table->SetValue<std::string>(row, column, "");
            m_table->SetSingleEditable(row, column, false);
        }
        m_playerButtons.at(row - 1)->SetEnabled(false);
    }
}

void NewGamePlayerScene::AddPlayer() {
    AppContext_ty_c appContext = AppContext::GetInstance();

    AddPlayerEvent const event{ m_inputLine->GetValue(), m_colorPicker->GetColor() };
    appContext.eventManager.InvokeEvent(event);
}

void NewGamePlayerScene::UpdatePlayer(unsigned int ID, std::string const& name, Color color) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    EditPlayerEvent const event{ ID, name, color };
    appContext.eventManager.InvokeEvent(event);

    UpdateSceneEntries();
}

void NewGamePlayerScene::UpdatePlayerName(AbstractTableCell const*, std::string const& oldValue, std::string const& newValue) {

    AppContext_ty_c appContext{ AppContext::GetInstance() };
    PlayerData const playerData{ appContext.playerCollection.GetPlayerByName(oldValue) };

    UpdatePlayer(playerData.ID, newValue, playerData.color);
}

void NewGamePlayerScene::UpdatePlayerColor(AbstractTableCell const*, Color oldValue, Color newValue) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    PlayerData const playerData{ appContext.playerCollection.GetPlayerByColor(oldValue) };

    UpdatePlayer(playerData.ID, playerData.GetName(), newValue);
}

void NewGamePlayerScene::DeletePlayer(unsigned int ID) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    DeletePlayerEvent const event{ ID };
    appContext.eventManager.InvokeEvent(event);
}

void NewGamePlayerScene::CheckPlayerCount() {
    ValidatePlayerCountEvent const event;
    AppContext::GetInstance().eventManager.InvokeEvent(event);
}

void NewGamePlayerScene::NextScene(bool valid) {
    if (!valid) {
        return;
    }

    SwitchSceneEvent const event{ SceneType::NEW_GAME_PARAMETER };
    AppContext::GetInstance().eventManager.InvokeEvent(event);
}

void NewGamePlayerScene::Reset() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    ResetPlayerEvent const event;
    appContext.eventManager.InvokeEvent(event);
}

void NewGamePlayerScene::SetNextButton() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    size_t const playerCount{ appContext.playerCollection.GetPlayerData().size() };
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
          Alignment::DEFAULT
} {

    AppContext_ty appContext{ AppContext::GetInstance() };
    Initialize();
    UpdateSceneEntries();
    appContext.eventManager.AddListener(this);
}

NewGamePlayerScene::~NewGamePlayerScene() {
    AppContext::GetInstance().eventManager.RemoveListener(this);
}

void NewGamePlayerScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

    CheckForNestedFocus(mousePosition);

    SetNextButton();

    for (auto& e : m_elements) {
        e->CheckAndUpdate(mousePosition, appContext);
    }
}

void NewGamePlayerScene::Render(AppContext_ty_c appContext) {
    for (auto& e : m_elements) {
        e->Render(appContext);
    }
}

void NewGamePlayerScene::Resize(AppContext_ty_c appContext) {
    for (auto& e : m_elements) {
        e->Resize(appContext);
    }
}

void NewGamePlayerScene::OnEvent(Event const& event) {

    if (auto const* CountEvent = dynamic_cast<ValidatePlayerCountResultEvent const*>(&event)) {
        NextScene(CountEvent->GetValid());
        return;
    }
    if ([[maybe_unused]] auto const* RefreshEvent = dynamic_cast<RefreshNewGamePlayerScene const*>(&event)) {
        UpdateSceneEntries();
        return;
    }
}
