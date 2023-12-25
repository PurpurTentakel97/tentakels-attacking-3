//
// Purpur Tentakel
// 05.06.2023
//

#include "event/EventListener.hpp"
#include "ui_lib/Scene.h"
#pragma once

class SendUpdateEvaluation;

class UpdateEvaluationScene final : public Scene, public EventListener {
private:
    enum class ResultType {
        MERGE,
        FIGHT,
        LAST,
    };

private:
    std::vector<HMergeResult> m_mergeResults;            ///< contains the fleet merge results via event from the logic
    std::vector<HFightResult> m_fightResults;            ///< contains the fight results via event from the logic
    ResultType m_currentResultType{ ResultType::MERGE }; ///< contains the current type for the correct popup
    size_t m_currentIndex{ 0 };                          ///< contains the current index within the current type
    int m_popupCount{ 0 }; ///< counts the overall ammount of popups displayed to know if it was 0
    bool m_nextPopup{
        false
    }; ///< contains if the next frame opens the next popup -> need so that the current popup has time to close itself

    /**
	 * prints the result to the console.
	 * only for debugging.
	 */
    void TestPrint(SendUpdateEvaluation const* event) const;

    /**
	 * displays the next merge result popup.
	 */
    void DisplayMergeResult();
    /**
	 * displays the next fight result popup.
	 */
    void DisplayFightResult();
    /**
	 * handles witch popup is shown next.
	 * calls the last popup when all popups are shown.
	 */
    void HandleNextPopup();

public:
    /**
	 * adds the event listener to the event system.
	 */
    UpdateEvaluationScene();
    /**
	 * removes the event listener from the event system.
	 */
    ~UpdateEvaluationScene();

    /**
	 * calls the Scene to update.
	 * calls the next popup.
	 */
    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    /**
	 * receives the events.
	 */
    void OnEvent(Event const& event) override;
};
