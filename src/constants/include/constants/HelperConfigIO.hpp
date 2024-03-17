//
// Purpur Tentakel
// 04.03.2024
//

#pragma once


#include "G_Config_IO.hpp"
#include <app/AppContext.hpp>
#include <cassert>
#include <helper/HLohmann.hpp>
#include <helper/SaveLoadFile.hpp>
#include <string>

namespace cst {
    inline std::string const defaultValuePrefix{ "-> using default value -> overwrite by save" };

    [[nodiscard]] inline bool LoadAndValidateConfigJson(nlohmann::json& son, utl::usize& loadEntryCount) {
        auto const input = hlp::TryLoadFile(Files::s_savesDir, Files::s_configFile);
        if (input.empty()) {
            hlp::Print(hlp::PrintType::INFO, "try generate a new config");
            G_Config_IO::SaveConfig();
            return false;
        }

        auto const& constants = app::AppContext::GetInstance().constants;

        std::stringstream stream{ input };
        stream >> son;

        // from json
        // config
        if (hlp::IsNull(son, G_Config_Enum::CONFIG)) {
            hlp::Print(hlp::PrintType::ERROR, "provided config is null {}", defaultValuePrefix);
            return false;
        }
        if (not hlp::IsMatchingSize(son, G_Config_Enum::CONFIG, constants.g_global.get_config_section_count())) {
            hlp::Print(hlp::PrintType::ERROR,
                       "config section count is not matching {} -> expected: {} -> provided: {}",
                       defaultValuePrefix,
                       constants.g_global.get_config_section_count(),
                       son.size());
        }
        // version
        if (nlohmann::json version; hlp::LoadSection(
                    son, version, G_Config_Enum::G_VERSION, constants.g_version.get_total_config_entry_count())) {
            if (std::string versionConfig;
                hlp::LoadString(version, versionConfig, G_Config_Enum::G_VERSION_CONFIG_VERSION, loadEntryCount)) {
                if (versionConfig != constants.g_version.get_config_version()) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "config version in config is not matching -> expected: {} -> provided: {} -> overwrite "
                               "config by save",
                               constants.g_version.get_config_version(),
                               versionConfig);
                } else {
                    hlp::Print(hlp::PrintType::INFO, "config versions matching -> version: {}", versionConfig);
                }
            } else {
                hlp::Print(hlp::PrintType::ERROR, "unable to check if config version is matching");
            }
            if (std::string versionGame;
                hlp::LoadString(version, versionGame, G_Config_Enum::G_VERSION_GAME_VERSION, loadEntryCount)) {
                if (versionGame != constants.g_version.get_game_version()) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "game version is not matching -> expected: {} -> provided: {} -> overwrite by save",
                               constants.g_version.get_game_version(),
                               versionGame);
                } else {
                    hlp::Print(hlp::PrintType::INFO, "game versions matching -> version: {}", versionGame);
                }
            } else {
                hlp::Print(hlp::PrintType::ERROR, "unable to check if config version is matching");
            }
        } else {
            hlp::Print(hlp::PrintType::ERROR, "not able to check if config and game versions match");
        }
        return true;
    }

    void CheckLoadEntryCount(utl::usize loadEntryCount) {
        auto& constants = app::AppContext::GetInstance().constants;
        assert(loadEntryCount == constants.GetConfigValueCount());
        if (auto count = constants.GetConfigValueCount(); loadEntryCount != count) {
            hlp::Print(
                    hlp::PrintType::ERROR,
                    "Entry count in config is not matching -> expected: {} -> provided: {} -> some values will use the "
                    "default value",
                    count,
                    loadEntryCount);
        } else {
            hlp::Print(hlp::PrintType::INFO, "Entry count in config is matching -> count {}", loadEntryCount);
        }

#ifdef _DEBUG
        constants.g_window.set_is_full_screen(false);
        hlp::Print(hlp::PrintType::DEBUG, "set full screen to false");
        constants.g_window.set_current_resolution_enum(Resolution::HD);
        hlp::Print(hlp::PrintType::DEBUG, "set resolution to HD");
#endif // _DEBUG
    }

} // namespace cst
