//
// Purpur Tentakel
// 05.11.2022
//

#pragma once

#include <ui_lib/Scene.hpp>


class CreditTableScene : public Scene {
private:
    using creditEntries = std::vector<std::vector<std::string>>;

    void Initialize(std::string const& headline, creditEntries const& entries, bool containsLink);

public:
    CreditTableScene(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            std::string const& headline,
            creditEntries const& entries,
            bool containsLink = false
    );
};
