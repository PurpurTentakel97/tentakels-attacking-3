//
// Purpur Tentakel
// 05.06.2023
//

#pragma once

#include <alias/AliasEvent.hpp>
#include <alias/AliasUtils.hpp>
#include <event/EventListener.hpp>
#include <ui_lib/Scene.hpp>
#include <utils/Result.hpp>


namespace ui {
    class UpdateEvaluationScene final : public uil::Scene, public eve::EventListener {
    private:
        enum class ResultType {
            EVENT,
            BLACK_HOLE,
            MERGE,
            FIGHT,
            LAST,
        };

    private:
        utl::ResultUpdate m_result;
        ResultType m_currentResultType{ ResultType::EVENT };
        utl::usize m_currentIndex{ 0 };
        utl::usize m_popupCount{ 0 };
        bool m_nextPopup{ false };

        static void TestPrint(eve::SendUpdateEvaluation const* event);

        void DisplayEventResult();

        void DisplayBlackHoleResult();

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
