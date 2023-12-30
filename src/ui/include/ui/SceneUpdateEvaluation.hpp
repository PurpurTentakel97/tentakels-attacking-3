//
// Purpur Tentakel
// 05.06.2023
//

#pragma once

#include <event/EventListener.hpp>
#include <ui_lib/Scene.hpp>
#include <alias/AliasEvent.hpp>


namespace ui {
    class UpdateEvaluationScene final : public uil::Scene, public eve::EventListener {
    private:
        enum class ResultType {
            MERGE,
            FIGHT,
            LAST,
        };

    private:
        std::vector<utl::MergeResult> m_mergeResults;
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
} // namespace ui
