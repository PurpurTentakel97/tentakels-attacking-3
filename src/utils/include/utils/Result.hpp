//
// PurpurTentakel
// 08.02.24
//

#pragma once

#include "ResultsEvents.hpp"
#include "ResultsUpdate.hpp"

namespace lgk {
    class GameManager;
}

namespace utl {
    class ResultUpdate final {
    public:
        friend class lgk::GameManager;
        using event_ty = std::shared_ptr<ResultEvent>;

    private:
        std::vector<event_ty> m_events{};
        std::vector<ResultMerge> m_merges{};
        std::vector<ResultFight> m_fights{};

        void SetEvents(std::vector<event_ty> events) {
            m_events = std::move(events);
        }

    public:
        ResultUpdate() = default;

        ResultUpdate(std::vector<ResultMerge> merges, std::vector<ResultFight> fights)
            : m_merges{ std::move(merges) },
              m_fights{ std::move(fights) } { }

        [[nodiscard]] std::vector<event_ty> Events() const {
            return m_events;
        }

        [[nodiscard]] std::vector<ResultMerge> Merges() const {
            return m_merges;
        }

        [[nodiscard]] std::vector<ResultFight> Fights() const {
            return m_fights;
        }
    };
} // namespace utl
