//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <memory>
#include <vector>

class UIManager;

class Scene : public UIElement {
protected:
    std::vector<std::shared_ptr<UIElement>> m_elements;
    std::vector<std::shared_ptr<UIElement>> m_elementsOutUpdates;
    bool m_active{ false };

    void SetFocusActive(AppContext_ty_c appContext);

    Vector2 GetElementPosition(float x, float y);

    Vector2 GetElementSize(float x, float y);

    [[nodiscard]] Focusable_ty_raw GetFocusableByFocusID(unsigned int ID) const;


public:
    Scene(Vector2 pos, Vector2 size, Alignment alignment);

    [[nodiscard]] bool IsActive() const;

    virtual void SetActive(bool active, AppContext_ty_c appContext);

    void SetPosition(Vector2 pos) override;

    void SetSize(Vector2 size) override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void Render(AppContext_ty_c appContext) override;

    void Resize(AppContext_ty_c appContext) override;


    void MoveBySpeed(float relativeSpeed, float angle) override;

    void MoveToPositionLinear(Vector2 position, float relativeSpeed) override;

    void MoveToPositionAsymptotic(Vector2 position, float relativeSpeed) override;

    void StopMoving() override;
};
