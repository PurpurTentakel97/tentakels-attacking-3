//
// Purpur Tentakel
// 05.06.2023
//

#include <event/EventListener.hpp>
#include <ui_lib/Scene.hpp>
#pragma once


namespace eve {
    class SendUpdateEvaluation;
}

class UpdateEvaluationScene final : public Scene, public eve::EventListener {
private:
    enum class ResultType {
        MERGE,
        FIGHT,
        LAST,
    };

private:
    std::vector<HMergeResult> m_mergeResults;
    std::vector<utl::FightResult> m_fightResults;
    ResultType m_currentResultType{ ResultType::MERGE };
    size_t m_currentIndex{ 0 };
    int m_popupCount{ 0 };
    bool m_nextPopup{ false };

    static void TestPrint(eve::SendUpdateEvaluation const* event);

    void DisplayMergeResult();

    void DisplayFightResult();

    void HandleNextPopup();

public:
    UpdateEvaluationScene();

    ~UpdateEvaluationScene() override;

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void OnEvent(eve::Event const& event) override;
};
