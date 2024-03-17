//
// Purpur Tentakel
// 17.03.2024
//

#pragma once

#include "AppContext.hpp"
#include "G_Save_Enum.hpp"
#include "G_Version.hpp"
#include <alias/AliasUtils.hpp>
#include <event/EventsUI.hpp>
#include <helper/HLohmann.hpp>
#include <helper/HPrint.hpp>
#include <helper/HVersion.hpp>
#include <helper/SaveLoadFile.hpp>
#include <sstream>
#include <string>

namespace app {
    [[nodiscard]] inline bool LoadAndValidateSaveJson(nlohmann::json& son,
                                                      utl::usize& currentEntryCount,
                                                      std::string const& dir,
                                                      std::string const& file) {
        auto const input       = hlp::TryLoadFile(dir, file);
        auto const& appContext = AppContext::GetInstance();
        if (input.empty()) {
            auto const event =
                    eve::ShowMessagePopUpEvent(appContext.languageManager.Text("ui_popup_no_save_file_title"),
                                               appContext.languageManager.Text("ui_popup_no_save_file_text", file),
                                               []() {});
            appContext.eventManager.InvokeEvent(event);
            hlp::Print(hlp::PrintType::ERROR, "not able to load save file: {}", file);
            return false;
        }

        auto const& constants = appContext.constants;
        std::stringstream stream{ input };
        stream >> son;

        if (hlp::IsNull(son, G_Save_Enum::G_SAVE)) {
            auto const event =
                    eve::ShowMessagePopUpEvent(appContext.languageManager.Text("ui_popup_empty_save_file_title"),
                                               appContext.languageManager.Text("ui_popup_empty_save_file_text", file),
                                               []() {});
            appContext.eventManager.InvokeEvent(event);
            hlp::Print(hlp::PrintType::ERROR, "loaded save file is empty: {}", file);
            return false;
        }

        auto const checkVersion = [&](std::string const& provided,
                                      std::string const& expected,
                                      std::string const& titleKey,
                                      std::string const& textKey,
                                      std::string const& versionName) {
            auto const result = hlp::CompareVersion(provided, expected);
            switch (result) {
                case hlp::VersionResult::HIGHER: {
                    auto const event =
                            eve::ShowMessagePopUpEvent(appContext.languageManager.Text(titleKey),
                                                       appContext.languageManager.Text(textKey, expected, provided),
                                                       []() {});
                    appContext.eventManager.InvokeEvent(event);
                    hlp::Print(hlp::PrintType::ERROR,
                               "higher save file version detected -> not able to load {} -> expected: {}, "
                               "provided:{}",
                               versionName,
                               expected,
                               provided);
                    return false;
                }
                case hlp::VersionResult::SAME:
                    hlp::Print(hlp::PrintType::INFO, "matching {} version: {}", versionName, provided);
                    break;
                case hlp::VersionResult::LOWER:
                    hlp::Print(hlp::PrintType::INFO,
                               "lower {} version detected -> expected: {}, provided:{}",
                               versionName,
                               expected,
                               provided);
                    break;
            }
            return true;
        };

        if (nlohmann::json version; hlp::LoadSection(son, version, G_Save_Enum::G_VERSION, 0)) {

            if (std::string saveVersion;
                hlp::LoadString(version, saveVersion, G_Save_Enum::G_VERSION_SAVE_VERSION, currentEntryCount)) {
                if (not checkVersion(saveVersion,
                                     constants.g_version.get_game_version(),
                                     "ui_popup_higher_save_file_version_title",
                                     "ui_popup_higher_save_file_version_text",
                                     "save file")) {
                    return false;
                }
            } else {
                auto const event = eve::ShowMessagePopUpEvent(
                        appContext.languageManager.Text("ui_popup_missing_save_game_version_title"),
                        appContext.languageManager.Text("ui_popup_missing_save_game_version_text"),
                        []() {});
                appContext.eventManager.InvokeEvent(event);
                hlp::Print(hlp::PrintType::ERROR, "not able to check save file version");
                return false;
            }

            if (std::string gameVersion;
                hlp::LoadString(version, gameVersion, G_Save_Enum::G_VERSION_GAME_VERSION, currentEntryCount)) {
                if (not checkVersion(gameVersion,
                                     constants.g_version.get_game_version(),
                                     "ui_popup_higher_game_version_title",
                                     "ui_popup_higher_game_version_text",
                                     "game")) {
                    return false;
                }
            } else {
                auto const event = eve::ShowMessagePopUpEvent(
                        appContext.languageManager.Text("ui_popup_missing_game_version_title"),
                        appContext.languageManager.Text("ui_popup_missing_game_version_text"),
                        []() {});
                appContext.eventManager.InvokeEvent(event);
                hlp::Print(hlp::PrintType::ERROR, "not able to check game version");
                return false;
            }

        } else {
            auto const event = eve::ShowMessagePopUpEvent(
                    appContext.languageManager.Text("ui_popup_missing_version_section_title"),
                    appContext.languageManager.Text("ui_popup_missing_version_section_text"),
                    []() {});
            appContext.eventManager.InvokeEvent(event);
            hlp::Print(hlp::PrintType::ERROR, "not able to check game or save state version");
            return false;
        }

        return true;
    }
} // namespace app
