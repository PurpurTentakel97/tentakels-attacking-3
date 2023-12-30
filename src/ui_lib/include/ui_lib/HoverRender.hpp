//
// Purpur Tentakel
// 14.05.2023
//

#pragma once

#include <CustomRaylib.hpp>
#include <alias/AliasUiLib.hpp>
#include <event/EventListener.hpp>
#include <vector>


namespace uil {
    class HoverRender final : public eve::EventListener {
    private:
        std::vector<Hover*> m_elements;
        static float constexpr m_renderGap{ 3.0f };

        [[nodiscard]] Vector2 GetStartRenderingOffset() const;

    public:
        HoverRender();

        ~HoverRender() override;

        void Render();

        void OnEvent(eve::Event const& event) override;
    };
} // namespace uil
