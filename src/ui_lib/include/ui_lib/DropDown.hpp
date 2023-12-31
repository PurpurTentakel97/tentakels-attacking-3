//
// Purpur Tentakel
// 01.12.2022
//

#pragma once

#include "Focusable.hpp"
#include "UIElement.hpp"
#include <alias/AliasUiLib.hpp>
#include <functional>
#include <memory>
#include <vector>


namespace uil {
    class DropDown : public UIElement, public Focusable {
    private:
        bool m_isEnabled{ true };
        bool m_isFoldouts{ false };
        bool m_isScrolling{ true };
        std::vector<std::shared_ptr<DropDownElement>> m_dropDownElements;

        Texture const* m_arrowTexture{};
        Rectangle m_arrowTextureRec{};
        Rectangle m_arrowCollider{};

        std::shared_ptr<DropDownElement> m_currentElement{ nullptr };
        std::string m_currentElementText{};
        float m_fontSize{ 0.0f };
        Vector2 m_textPosition{ 0.0f, 0.0f };

        float m_dropDownHeight;
        Rectangle m_dropDownCollider{};
        std::function<void(utl::usize)> m_onSave{ [](utl::usize) {} };

        void Initialize(std::vector<std::string> const& elements, utl::usize startFocusID);

        void OnElementClick(utl::usize ID);

        void SetCurrentElement(std::shared_ptr<DropDownElement> const& element);

        void SetCurrentElementOutUpdate(std::shared_ptr<DropDownElement> const& element);

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
                utl::usize focusID,
                utl::usize startElementFocusID,
                std::vector<std::string> const& elements
        );

        [[nodiscard]] std::shared_ptr<DropDownElement> GetCurrentElement() const;

        bool SetCurrentElementByID(utl::usize ID);

        bool SetCurrentElementByString(std::string const& element);

        void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;

        [[nodiscard]] bool IsEnabled() const override;

        void SetEnabled(bool isEnabled);

        [[nodiscard]] bool IsFoldedOut() const;

        [[nodiscard]] Rectangle GetCollider() const override;

        void SetOnSave(std::function<void(utl::usize)> onSave);
    };
} // namespace uil
