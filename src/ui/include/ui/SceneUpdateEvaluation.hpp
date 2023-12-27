//
// Purpur Tentakel
// 05.06.2023
//

#include <event/EventListener.hpp>
#include <ui_lib/Scene.hpp>
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
    std::vector<HMergeResult> m_mergeResults;
    std::vector<HFightResult> m_fightResults;
    ResultType m_currentResultType{ ResultType::MERGE };
    size_t m_currentIndex{ 0 };
    int m_popupCount{ 0 };
    bool m_nextPopup{ false };

    void TestPrint(SendUpdateEvaluation const* event) const;

    void DisplayMergeResult();

    void DisplayFightResult();

    void HandleNextPopup();

public:
    UpdateEvaluationScene();

    ~UpdateEvaluationScene() override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    void OnEvent(Event const& event) override;
};
