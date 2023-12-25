//
// Purpur Tentakel
// 14.05.2023
//

#include "CustomRaylib.h"
#include "event/EventListener.hpp"
#include <vector>
#pragma once

class Hover;

class HoverRender final : public EventListener {
private:
    std::vector<Hover*> m_elements;             ///< contains all hover that gets renders this frame
    static float constexpr m_renderGap{ 3.0f }; ///< contains the gap between two renders

    /**
	 * returns the start position for rendering
	 */
    [[nodiscard]] Vector2 GetStartRenderingOffset() const;

public:
    /**
	 * registers as EventListener
	 */
    HoverRender();

    /**
	 * removes the EventListener
	 */
    ~HoverRender() override;

    /**
	 * renders all hovers of the frame and clears the queue
	 */
    void Render();

    /**
	 * handles the events
	 */
    void OnEvent(Event const& event) override;
};
