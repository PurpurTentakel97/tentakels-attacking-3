//
// Purpur Tentakel
// 16.07.2023
//

#pragma once

#include "UIElement.hpp"


namespace uil {
    class ExpandingButton : public UIElement {
    public:
        enum Direction { LEFT, DOWN, RIGHT, UP };

    private:
        struct Btn {
            ClassicButton_ty btn;
            bool enabled;
            Vector2 pos;
        };

        bool m_isExpanded{ false };
        bool m_wasKeyInput{ false };
        bool m_delayedCollapse{ false };
        double m_collapseStartTime{ 0.0 };
        double m_delayedCollapseTime{ 1.0 };
        float m_spacing;
        float m_expandingSpeed;
        std::vector<Btn> m_buttons{};
        Direction m_direction;
        ToggleButton_ty m_mainButton;

        void Initialize(int focusID, std::string const& btnText);

        void HandleExpandChance(bool expanding, bool keyInput);

        void HandleExpand();

        void HandleCollapse();

        [[nodiscard]] bool IsBtnMoving() const;

    public:
        ExpandingButton(
                int focusID,
                Vector2 pos,
                Vector2 size,
                Alignment alignment,
                Direction direction,
                float spacing,
                float expandingSpeed,
                std::string const& btnText
        );

        void Add(ClassicButton_ty const& btn, bool enabled);

        void Remove(ClassicButton_ty const& btn);

        void Remove(size_t ind);

        void Expand();

        void Collapse();

        [[nodiscard]] double GetDelayedCollapseTime() const;

        void SetDelayedCollapseTime(double time);

        void SetDirection(Direction direction);

        [[nodiscard]] Direction GetDirection() const;

        void Update();

        void UpdateCollider() override;

        void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c) override;
    };
} // namespace uil
