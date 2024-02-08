//
// PurpurTentakel
// 08.02.24
//

#pragma once

#include "EventsResults.hpp"
#include "ResultFight.hpp"
#include "ResultMerge.hpp"

namespace utl {
    class UpdateResult final {
        friend class lgk::GameManager;
    private:
        std::vector<ResultEvent> m_events{};
        std::vector<ResultMerge> m_merges{};
        std::vector<ResultFight> m_fights{};

    public:
        UpdateResult() = default;

        UpdateResult(std::vector<ResultEvent> events, std::vector<ResultMerge> merges, std::vector<ResultFight> fights)
            : m_events{ std::move(events) },
              m_merges{ std::move(merges) },
              m_fights{ std::move(fights) } { }

        [[nodiscard]] std::vector<ResultEvent> Events() const {
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
