//
// Purpur Tentakel
// 01.10.2022
//

#pragma once

#include <alias/AliasApp.hpp>
#include <ui_lib/NewInputLine.hpp>
#include <ui_lib/Scene.hpp>

namespace ui {
    class TestScene : public uil::Scene {
        using line_ty = std::shared_ptr<uil::NewInputLine>;

    private:
        line_ty m_line1;
        void Initialize(app::AppContext_ty appContext);

    public:
        TestScene();
        void SetActive(bool active, app::AppContext_ty_c appContext) override;

        static void TestLambdaValue(uil::NewInputLine& line);

        static void TestLambdaEnter(uil::NewInputLine& line);

        void SwitchInputLineType();

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
        void Render(app::AppContext_ty_c appContext) override;
        void Resize(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
