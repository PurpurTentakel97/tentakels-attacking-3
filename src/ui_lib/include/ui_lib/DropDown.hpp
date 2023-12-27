//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "Focusable.hpp"
#include "UIElement.hpp"
#include <functional>
#include <memory>
#include <vector>

class DropDownElement;

class DropDown : public UIElement, public Focusable {
private:
    bool m_isEnabled{ true };
    bool m_isFoldouts{ false };
    bool m_isScrolling{ true };
    std::vector<std::shared_ptr<DropDownElement>> m_dropDownElements;

    Texture const* m_arrowTexture;
    Rectangle m_arrowTextureRec;
    Rectangle m_arrowCollider;

    std::shared_ptr<DropDownElement> m_currentElement{ nullptr };
    std::string m_currentElementText{};
    float m_fontSize{ 0.0f };
    Vector2 m_textPosition{ 0.0f, 0.0f };

    float m_dropDownHeight;
    Rectangle m_dropDownCollider;
    std::function<void(unsigned int)> m_onSave{ [](unsigned int) {} };

    void Initialize(std::vector<std::string> const& elements, unsigned int startFocusID);

    void OnElementClick(unsigned int ID);

    void SetCurrentElement(std::shared_ptr<DropDownElement> element);

    void SetCurrentElementOutUpdate(std::shared_ptr<DropDownElement> element);

    void SetText();

    void ToggleFoldedOut();

    [[nodiscard]] Rectangle GetTemporaryCollider(Rectangle collider) const;

    void CheckAndSetElementsEnabled();

    void ScrollMove(float wheel);

    void ClampScrolling();

    void CheckIfScrolling();

    void UpdateCollider() override;

public:
    DropDown(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            float dropDownSize,
            unsigned int focusID,
            unsigned int startElementFocusID,
            std::vector<std::string> const& elements
    );

    [[nodiscard]] std::shared_ptr<DropDownElement> GetCurrentElement() const;

    bool SetCurrentElementByID(unsigned int ID);

    bool SetCurrentElementByString(std::string const& element);

    void CheckAndUpdate(Vector2 const&, AppContext_ty_c) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;

    [[nodiscard]] bool IsEnabled() const override;

    void SetEnabled(bool isEnabled);

    [[nodiscard]] bool IsFoldedOut() const;

    [[nodiscard]] Rectangle GetCollider() const override;

    void SetOnSave(std::function<void(unsigned int)> onSave);
};
