//
// Purpur Tentakel
// 14.05.2023
//

#include "HoverRender.hpp"
#include "Hover.hpp"
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>


namespace uil {
    HoverRender::HoverRender() {
        app::AppContext::GetInstance().eventManager.AddListener(this);
    }

    HoverRender::~HoverRender() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    Vector2 HoverRender::GetStartRenderingOffset() const {
        Vector2 offset{ 0.0f, 0.0f };
        for (auto const& e : m_elements) {
            auto const singleOffset = e->GetRenderOffset();
            if (offset.x < singleOffset.x) {
                offset.x = singleOffset.x;
            }
            if (offset.y < singleOffset.y) {
                offset.y = singleOffset.y;
            }
        }

        return offset;
    }

    void HoverRender::Render() {
        auto const handleReturn{ [&]() { m_elements.clear(); } };
        // no elements
        if (m_elements.empty()) {
            handleReturn();
            return;
        }

        // one element
        app::AppContext_ty appContext = app::AppContext::GetInstance();
        if (m_elements.size() == 1) {
            m_elements.at(0)->Render(appContext);
            handleReturn();
            return;
        }

        // multiple elements
        auto renderingOffset{ GetStartRenderingOffset() };
        auto const increase{ [&](float offset, bool high) {
            if (high) {
                renderingOffset.y -= offset + m_renderGap;
            } else {
                renderingOffset.y += offset + m_renderGap;
            }
        } };

        auto const& window{ appContext.constants.g_window };
        auto const& helper{ appContext.constants.h_window };
        auto const& resolution{ helper.GetIntFromResolution(window.get_current_resolution_enum()) };
        bool const high{ static_cast<float>(resolution.y) / 2.0f > GetMousePosition().y };

        if (high) {
            auto const offset{ m_elements.at(0)->GetCollider().height };
            increase(offset, high);
            increase(offset, high);
        }

        for (auto const& hover : m_elements) {
            auto const newOffset = hover->RenderOffset(appContext, renderingOffset);
            increase(newOffset, high);
        }
        handleReturn();
    }

    void HoverRender::OnEvent(eve::Event const& event) {
        if (auto const* HoverEvent = dynamic_cast<eve::RenderHoverEvent const*>(&event)) {
            m_elements.push_back(HoverEvent->GetHover());
            return;
        }
    }
} // namespace uil
