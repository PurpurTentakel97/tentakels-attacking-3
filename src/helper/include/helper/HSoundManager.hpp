//
// Purpur Tentakel
// 24.08.2022
//

#pragma once

#include "HSoundType.hpp"
#include <CustomRaylib.hpp>
#include <array>
#include <event/EventListener.hpp>
#include <string>
#include <unordered_map>
#include <vector>


class SoundManager final : public EventListener {
private:
    std::unordered_map<SoundType, Sound> m_sounds;
    std::array<std::string, 5> m_files{
        // clang-format off
        "clicked_accepted_std.mp3",
        "clicked_press_std.mp3",
        "clicked_release_std.mp3",
        "clicked_disabled_std.mp3",
        "hovered_std.mp3",
        // clang-format on
    };

    std::vector<Sound> m_textSounds;

    void LoadSounds();

    void PlaySound(SoundType soundType) const;

    void PlayTextSound() const;

    void MuteMasterSoundLevel(bool mute) const;

    void SetMasterSoundLevel(float level) const;

    void OnEvent(Event const& event) override;

public:
    SoundManager();

    ~SoundManager() override;
};
