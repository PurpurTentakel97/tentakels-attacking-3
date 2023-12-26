//
// Purpur Tentakel
// 05.11.2022
//

#include "AppContext.hpp"
#include "HSceneCreditTable.hpp"
#include "ui_lib/Line.h"
#include "ui_lib/Text.h"
#include <cassert>
#include <stdexcept>


void CreditTableScene::Initialize(std::string const& headline, creditEntries const& entries, bool containsLink) {
    // headline
    auto headlineText = std::make_shared<Text>(
            GetElementPosition(0.5f, 0.0f),
            GetElementSize(0.8f, 0.15f),
            Alignment::TOP_MID,
            Alignment::TOP_MID,
            0.15f * m_size.y,
            headline
    );
    // headlineText->RenderRectangle(true);
    m_elements.push_back(headlineText);

    auto headlineLine =
            std::make_shared<Line>(GetElementPosition(0.15f, 0.15f), GetElementPosition(0.85f, 0.15f), 3.0f, WHITE);
    m_elements.push_back(headlineLine);

    // elements
    float const textHeight{ 0.07f };

    for (size_t i = 0; i < entries.size(); ++i) {
        auto e{ entries.at(i) };
        if (e.size() == 0) {
            continue;
        }
        if (containsLink && e.size() % 2 != 0) {
            throw std::out_of_range("not able to divide by 2 with link");
        }
        if (e.size() > 4) {
            throw std::out_of_range("too many Entries with link");
        }
        if (!containsLink && e.size() > 2) {
            throw std::out_of_range("too many Entries without link");
        }

        size_t position{ 0 };
        if ((e.size() == 2 && !containsLink) or (e.size() == 4 && containsLink)) {
            auto entry = std::make_shared<Text>(
                    GetElementPosition(0.49f, 0.2f + textHeight * static_cast<float>(i)),
                    GetElementSize(0.5f, textHeight),
                    Alignment::TOP_RIGHT,
                    Alignment::TOP_RIGHT,
                    textHeight * m_size.y,
                    e.at(position)
            );
            // entry->RenderRectangle(true);
            m_elements.push_back(entry);
            ++position;

            if (containsLink) {
                entry->SetURL(e.at(position));
                ++position;
            }

            entry = std::make_shared<Text>(
                    GetElementPosition(0.51f, 0.2f + textHeight * static_cast<float>(i)),
                    GetElementSize(0.5f, textHeight),
                    Alignment::TOP_LEFT,
                    Alignment::TOP_LEFT,
                    textHeight * m_size.y,
                    e.at(position)
            );
            // entry->RenderRectangle(true);
            m_elements.push_back(entry);
            ++position;

            if (containsLink) {
                entry->SetURL(e.at(position));
                ++position;
            }
        } else {
            auto entry = std::make_shared<Text>(
                    GetElementPosition(0.5f, 0.23f + textHeight * static_cast<float>(i)),
                    GetElementSize(1.0f, textHeight),
                    Alignment::MID_MID,
                    Alignment::MID_MID,
                    textHeight * m_size.y,
                    e.at(position)
            );
            // entry->RenderRectangle(true);
            m_elements.push_back(entry);
            ++position;

            if (containsLink) {
                entry->SetURL(e.at(position));
                ++position;
            }
        }
    }
}

CreditTableScene::CreditTableScene(
        Vector2 pos,
        Vector2 size,
        Alignment alignment,
        std::string const& headline,
        creditEntries const& entries,
        bool containsLink
)
    : Scene{ pos, size, alignment } {
    Initialize(headline, entries, containsLink);
}
