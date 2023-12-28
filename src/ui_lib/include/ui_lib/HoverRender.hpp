//
// Purpur Tentakel
// 14.05.2023
//

#pragma once
#include <CustomRaylib.hpp>
#include <event/EventListener.hpp>
#include <vector>

class Hover;

class HoverRender final : public EventListener {
private:
    std::vector<Hover*> m_elements;
    static float constexpr m_renderGap{ 3.0f };

    [[nodiscard]] Vector2 GetStartRenderingOffset() const;

public:
    HoverRender();

    ~HoverRender() override;

    void Render();

    void OnEvent(Event const& event) override;
};
