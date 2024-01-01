//
// Purpur Tentakel
// 05.09.2022
//

#pragma once

#include "UIElement.hpp"
#include <memory>
#include <vector>

namespace uil {
    class Scene : public UIElement {
    protected:
        std::vector<std::shared_ptr<UIElement>> m_elements;
        std::vector<std::shared_ptr<UIElement>> m_elementsOutUpdates;
        bool m_active{ false };

        void SetFocusActive(app::AppContext_ty_c appContext);

        Vector2 GetElementPosition(float x, float y);

        Vector2 GetElementSize(float x, float y);

        [[nodiscard]] Focusable_ty_raw GetFocusableByFocusID(utl::usize ID) const;


    public:
        Scene(Vector2 pos, Vector2 size, Alignment alignment);

        [[nodiscard]] bool IsActive() const;

        virtual void SetActive(bool active, app::AppContext_ty_c appContext);

        void SetPosition(Vector2 pos) override;

        void SetSize(Vector2 size) override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;


        void MoveBySpeed(float relativeSpeed, float angle) override;

        void MoveToPositionLinear(Vector2 position, float relativeSpeed) override;

        void MoveToPositionAsymptotic(Vector2 position, float relativeSpeed) override;

        void StopMoving() override;
    };
} // namespace uil
