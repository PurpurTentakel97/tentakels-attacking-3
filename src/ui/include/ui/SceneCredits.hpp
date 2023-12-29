//
// Purpur Tentakel
// 04.11.2022
//

#pragma once

#include <ui_lib/Scene.hpp>


class CreditsScene final : public Scene {
private:
    Title_ty m_title;
    Line_ty m_titleLine;
    ClassicButton_ty m_endBTN;
    ClassicButton_ty m_speedBTN;
    float m_speed{ 0.07f };
    int m_maxSpeedLevel{ 3 };
    int m_speedLevel{ 1 };
    std::vector<std::shared_ptr<UIElement>> m_movingElements;


    using creditEntries = std::vector<std::vector<std::string>>;
    static inline creditEntries const libVec = {
        {     "raylib", "",          "www.raylib.com",          "https://www.raylib.com" },
        { "random lib", "", "www.github.com/mgerhold", "https://www.github.com/mgerhold" },
    };
    static inline creditEntries const inspirationVec = {
        { "my Dad" },
        { "coder2k" },
    };
    static inline creditEntries const testerVec = {
        { "Kiki3578" },
        { "TODO" },
    };
    static inline creditEntries const specialThanksVec = {
        { "coder2k" },
        { "r00tifant" },
        { "Clemens" },
        { "CrazyNightowl01" },
        { "NECROMENZER" },
        { "german coding community on twitch" },
        { "the discord of coder2k" },
        { "TODO: more to come" },
    };
    static inline creditEntries const contactVec = {
        { "discord", "",          "www.discord.gg/JG5fsFZqEE",          "https://www.discord.gg/JG5fsFZqEE" },
        {  "twitch", "", "www.twitch.tv/codingPurpurTentakel", "https://www.twitch.tv/codingpurpurtentakel" },
        {  "gitHub", "",    "www.github.com/PurpurTentakel97",    "https://www.github.com/PurpurTentakel97" },
    };


    void Initialize();

    void AddMovingElement(std::shared_ptr<UIElement> const& element);

    void ToggleSpeedLevel();

    void CheckCreditsFinished();

public:
    CreditsScene();

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;
};
