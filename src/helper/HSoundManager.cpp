//
// Purpur Tentakel
// 24.08.2022
//

#include "HSoundManager.hpp"
#include "HPrint.hpp"
#include "HRandom.hpp"
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>
#include <filesystem>


void SoundManager::LoadSounds() {
    for (size_t i = 0; i < m_files.size(); ++i) {
        auto const filename{ "Assets/Sounds/" + m_files[i] };

        if (!std::filesystem::exists(filename)) {
            hlp::Print(hlp::PrintType::ERROR, "sound does not exist -> \"{}\"", filename);
            return;
        }

        Sound const sound{ LoadSound(filename.c_str()) };
        m_sounds[static_cast<SoundType>(i)] = sound;
    }

    std::string const files{ "Assets/Sounds/TextSounds" };

    if (!std::filesystem::exists(files)) {
        hlp::Print(hlp::PrintType::ERROR, "text sounds does not exist -> \"{}\"", files);
        return;
    }

    for (auto const& entry : std::filesystem::directory_iterator(files)) {
        Sound const sound{ LoadSound(entry.path().string().c_str()) };
        m_textSounds.push_back(sound);
    }
}

void SoundManager::PlaySound(SoundType const soundType) const {
    if (soundType == SoundType::TEXT) {
        PlayTextSound();
        return;
    }

    ::PlaySound(m_sounds.at(soundType));
}

void SoundManager::PlayTextSound() const {
    hlp::Random& random{ hlp::Random::GetInstance() };

    static unsigned long long lastIndex{ 0 };

    unsigned long long nextIndex;
    do {
        nextIndex = random.random(m_textSounds.size());
    } while (lastIndex == nextIndex);

    ::PlaySound(m_textSounds.at(nextIndex));
    lastIndex = nextIndex;
}

void SoundManager::MuteMasterSoundLevel(bool const mute) {
    AppContext_ty appContext{ AppContext::GetInstance() };
    appContext.constants.sound.muteVolume = mute;
    SetMasterSoundLevel(appContext.constants.sound.masterVolume);
}

void SoundManager::SetMasterSoundLevel(float const level) {
    AppContext_ty appContext{ AppContext::GetInstance() };

    appContext.constants.sound.masterVolume = level;
    if (appContext.constants.sound.muteVolume) {
        SetMasterVolume(0.0f);
        return;
    }

    SetMasterVolume((level / 100.0f));
}

SoundManager::SoundManager() {
    InitAudioDevice();
    LoadSounds();
}
SoundManager::~SoundManager() {
    for (auto const& [_, sound] : m_sounds) {
        UnloadSound(sound);
    }
    CloseAudioDevice();
}

void SoundManager::OnEvent(eve::Event const& event) {
    if (auto const soundEvent = dynamic_cast<eve::PlaySoundEvent const*>(&event)) {
        PlaySound(soundEvent->GetSoundType());
        return;
    }

    if (auto const LevelEvent = dynamic_cast<eve::SetMasterVolumeEvent const*>(&event)) {
        SetMasterSoundLevel(LevelEvent->GetLevel());
        return;
    }
    if (auto const MuteEvent = dynamic_cast<eve::MuteMasterVolumeEvent const*>(&event)) {
        MuteMasterSoundLevel(MuteEvent->GetMute());
        return;
    }
}
