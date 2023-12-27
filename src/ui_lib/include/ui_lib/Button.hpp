//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "UIElement.hpp"
#include <functional>
#include <string>


class Button : public UIElement {
protected:
    enum class State {
        ENABLED,
        HOVER,
        PRESSED,
        DISABLED,
    };

    std::string m_text{};
    SoundType m_sound{};

    Vector2 m_textPosition{};
    Texture2D* m_texture{};
    Rectangle m_textureRec{};

    float m_textSize{ 24.0f };
    bool m_isPressed{ false };

    State m_state{ State::ENABLED };
    int m_buttonParts{ 4 };


    std::function<void()> m_onClick{ []() {} };
    std::function<void()> m_onPress{ []() {} };

    void SetTextSizeAndPosition(AppContext_ty_c appContext);

    [[nodiscard]] bool IsSameState(State state) const;

    void UpdateCollider() override;

public:
    Button(Vector2 pos, Vector2 size, Alignment alignment, std::string const& text, SoundType releaseSound);

    Button();

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;

    void SetOnClick(std::function<void()> onClick);

    void SetOnPress(std::function<void()> onPress);

    void SetText(std::string const& text);

    [[nodiscard]] std::string GetText() const;

    virtual void SetEnabled(bool enabled);

    [[nodiscard]] bool IsEnabled() const;

    void SetCollider(Rectangle collider) override;

    void SetPosition(Vector2 pos) override;
};
