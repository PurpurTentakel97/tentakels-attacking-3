//
// Purpur Tentakel
// 04.03.2024
//

#pragma once

#include "G_Config_Enum.hpp"
#include "G_Config_IO.hpp"
#include <alias/AliasUtils.hpp>
#include <app/AppContext.hpp>
#include <cassert>
#include <helper/HPrint.hpp>
#include <helper/SaveLoadFile.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace cst {
    inline std::string const defaultValuePrefix{ "-> using default value -> overwrite config by save" };
    utl::usize loadEntryCount{ 0 };

    // print
    inline void PrintMissingSection(G_Config_Enum const section) {
        hlp::Print(hlp::PrintType::ERROR, "section \"{}\" in config missing {}", CToS(section), defaultValuePrefix);
    }

    inline void PrintMissingEntry(G_Config_Enum const entry) {
        hlp::Print(hlp::PrintType::ERROR, "entry \"{}\" in config missing {}", CToS(entry), defaultValuePrefix);
    }

    inline void PrintNotMatchingCount(G_Config_Enum const section,
                                      utl::usize const expected,
                                      utl::usize const provided) {
        hlp::Print(hlp::PrintType::ERROR,
                   R"(section "{}" entry count in config is not matching -> expected: "{}" -> provided: "{}")",
                   CToS(section),
                   expected,
                   provided);
    }

    inline void PrintWrongDatatype(G_Config_Enum const entry) {
        hlp::Print(
                hlp::PrintType::ERROR, "entry \"{}\" in config has wrong datatype {}", CToS(entry), defaultValuePrefix);
    }

    // check
    inline bool IsNull(nlohmann::json const& son, G_Config_Enum const type) {
        assert(not son.is_null());
        if (son.is_null()) {
            PrintMissingSection(type);
            return true;
        }
        return false;
    }

    inline bool IsExistingSection(nlohmann::json const& son, G_Config_Enum const type) {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            PrintMissingSection(type);
            return false;
        }
        return true;
    }

    inline bool IsExistingEntry(nlohmann::json const& son, G_Config_Enum const type) {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            PrintMissingEntry(type);
            return false;
        }
        return true;
    }

    inline bool IsMatchingSize(nlohmann::json const& son, G_Config_Enum const section, utl::usize const count) {
        assert(son.size() == count);
        if (son.size() != count) {
            PrintNotMatchingCount(section, count, son.size());
            return false;
        }
        return true;
    }

    // load
    [[nodiscard]] inline bool LoadSection(nlohmann::json const& son,
                                          nlohmann::json& out,
                                          G_Config_Enum const section,
                                          utl::usize const count) {
        if (not IsExistingSection(son, section)) {
            return false;
        }
        son.at(CToS(section)).get_to(out);

        if (IsNull(out, section)) {
            return false;
        }
        IsMatchingSize(out, section, count);

        return true;
    }

    [[nodiscard]] inline bool LoadString(nlohmann::json const& son, std::string& out, G_Config_Enum const entry) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(CToS(entry)).is_string());
        if (not son.at(CToS(entry)).is_string()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(CToS(entry)).get_to(out);
        return true;
    }

    [[nodiscard]] inline bool LoadUSize(nlohmann::json const& son, utl::usize& out, G_Config_Enum const entry) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(CToS(entry)).is_number_unsigned());
        if (not son.at(CToS(entry)).is_number_unsigned()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(CToS(entry)).get_to(out);
        return true;
    }

    [[nodiscard]] inline bool LoadFloat(nlohmann::json const& son, float& out, G_Config_Enum const entry) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(CToS(entry)).is_number_float());
        if (not son.at(CToS(entry)).is_number_float()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(CToS(entry)).get_to(out);
        return true;
    }

    [[nodiscard]] inline bool LoadBool(nlohmann::json const& son, bool& out, G_Config_Enum const entry) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(CToS(entry)).is_boolean());
        if (not son.at(CToS(entry)).is_boolean()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(CToS(entry)).get_to(out);
        return true;
    }

    [[nodiscard]] inline bool LoadAndValidateConfigJson(nlohmann::json& son) {
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
        if (IsNull(son, G_Config_Enum::CONFIG)) {
            hlp::Print(hlp::PrintType::ERROR, "provided config is null {}", defaultValuePrefix);
            return false;
        }
        if (not IsMatchingSize(son, G_Config_Enum::CONFIG, Global::configSectionCount)) {
            hlp::Print(hlp::PrintType::ERROR,
                       "config section count is not matching {} -> expected: {} -> provided: {}",
                       defaultValuePrefix,
                       Global::configSectionCount,
                       son.size());
        }
        // version
        if (nlohmann::json version;
            LoadSection(son, version, G_Config_Enum::G_VERSION, constants.g_version.get_total_config_entry_count())) {
            if (std::string versionConfig; LoadString(version, versionConfig, G_Config_Enum::G_VERSION_CONFIG_VERSION)) {
                if (versionConfig != constants.g_version.get_config_version()) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "config version in config is not matching -> expected: {} -> provided: {} -> overwrite "
                               "config by "
                               "save",
                               constants.g_version.get_config_version(),
                               versionConfig);
                } else {
                    hlp::Print(hlp::PrintType::INFO, "config versions matching -> version: {}", versionConfig);
                }
            } else {
                hlp::Print(hlp::PrintType::ERROR, "unable to check if config version is matching");
            }
            if (std::string versionGame; LoadString(version, versionGame, G_Config_Enum::G_VERSION_GAME_VERSION)) {
                if (versionGame != constants.g_version.get_game_version()) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "game version is not matching -> expected: {} -> provided: {} -> overwrite by "
                               "save",
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

    void CheckLoadEntryCount() {
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
        constants.window.isFullScreen = false;
        hlp::Print(hlp::PrintType::DEBUG, "set full screen to false");
        constants.window.currentResolutionEnum = Resolution::HD;
        hlp::Print(hlp::PrintType::DEBUG, "set resolution to HD");
#endif // _DEBUG
    }

} // namespace cst
