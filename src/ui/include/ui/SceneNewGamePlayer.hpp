//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include <event/EventListener.hpp>
#include <ui_lib/InputLine.hpp>
#include <ui_lib/Scene.hpp>
#include <ui_lib/TableCellAbstract.hpp>


class NewGamePlayerScene final : public Scene, public EventListener {
private:
    InputLine<std::string>* m_inputLine;
    ColorPicker* m_colorPicker;
    Table* m_table;
    ClassicButton_ty m_nextBTN;
    std::vector<Focusable_ty_raw> m_nestedFocus;
    std::vector<ClassicButton_ty> m_playerButtons;

    void Initialize();

    void InitializePlayerButtons();

    void CheckForNestedFocus(Vector2 const& mousePosition) const;

    void UpdateSceneEntries();

    void AddPlayer();

    void UpdatePlayer(unsigned int ID, std::string const& name, Color color);

    void UpdatePlayerName(AbstractTableCell const* cell, std::string oldValue, std::string newValue);

    void UpdatePlayerColor(AbstractTableCell const* cell, Color oldValue, Color newValue);

    void DeletePlayer(unsigned int ID);

    void CheckPlayerCount() const;

    void NextScene(bool valid);

    void Reset();

    void SetNextButton();

public:
    NewGamePlayerScene();

    ~NewGamePlayerScene() override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;

    void OnEvent(Event const& event) override;
};
