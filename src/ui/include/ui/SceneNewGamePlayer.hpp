//
// Purpur Tentakel
// 06.10.2022
//

#pragma once

#include <alias/AliasUiLib.hpp>
#include <event/EventListener.hpp>
#include <ui_lib/InputLine.hpp>
#include <ui_lib/Scene.hpp>
#include <ui_lib/TableCell.hpp>


namespace ui {
    class NewGamePlayerScene final : public uil::Scene, public eve::EventListener {
    private:
        uil::InputLine_ty m_inputLine;
        uil::ColorPicker_ty m_colorPicker;
        uil::Table_ty m_table;
        uil::ClassicButton_ty m_nextBTN;
        std::vector<uil::Focusable_ty_raw> m_nestedFocus;
        std::vector<uil::ClassicButton_ty> m_playerButtons;
        bool m_updating{ true };

        void Initialize();

        void InitializePlayerButtons();

        void CheckForNestedFocus(Vector2 const& mousePosition) const;

        void UpdateSceneEntries();

        void AddPlayer();

        void UpdatePlayer(utl::usize ID, std::string const& name, Color color);

        void UpdatePlayerName(uil::TableCell& cell);

        void UpdatePlayerColor(uil::TableCell& cell);

        static void DeletePlayer(utl::usize ID);

        static void CheckPlayerCount();

        static void NextScene(bool valid);

        static void Reset();

        void SetNextButton();

    public:
        NewGamePlayerScene();

        ~NewGamePlayerScene() override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;

        void OnEvent(eve::Event const& event) override;
    };
} // namespace ui
