//
// Purpur Tentakel
// 19.09.2022
//

#pragma once

#include "UIElement.hpp"
#include <array>
#include <vector>


namespace uil {
    class Title final : public UIElement {
    private:
        static inline std::array<std::string, 10> const m_postFixes{
            // clang-format off
        "  /-\\-",
        "  \\--/",
        "  -/--/",
        "  -\\_-\\",
        "  _/_\\",
        "  -_/\\-",
        "  --__-",
        "  __\\\\/",
        "  \\__-/",
        "  \\/-__",
            // clang-format on
        };
        std::vector<std::string>* m_title;
        float m_fontSize{};
        size_t m_charCount{ 0 };
        size_t m_maxCharCount{};
        bool m_titleFinish;
        bool m_lastFinishedTitle{ false };

        void RenderTitle(app::AppContext_ty_c appContext);

        void RenderTitleSequence(app::AppContext_ty_c appContext);

        void MeasureTitleLength();

        void RecalculateCollider(app::AppContext_ty_c appContext);

        void TitleFinish(app::AppContext_ty_c appContext);

    public:
        Title(Vector2 pos, Vector2 size, Alignment alignment, bool drawTitle);

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;

        [[nodiscard]] bool HasFinishedTitle() const;

        [[nodiscard]] bool IsTitleFinished() const;
    };
} // namespace uil
