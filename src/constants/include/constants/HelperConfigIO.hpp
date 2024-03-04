//
// Purpur Tentakel
// 04.03.2024
//

#pragma once

#include "CConfigEnum.hpp"
#include "CConfigIO.hpp"
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
    inline void PrintMissingSection(ConfigTypes const section) {
        hlp::Print(hlp::PrintType::ERROR, "section \"{}\" in config missing {}", CToS(section), defaultValuePrefix);
    }

    inline void PrintMissingEntry(ConfigTypes const entry) {
        hlp::Print(hlp::PrintType::ERROR, "entry \"{}\" in config missing {}", CToS(entry), defaultValuePrefix);
    }

    inline void PrintNotMatchingCount(ConfigTypes const section, utl::usize const expected, utl::usize const provided) {
        hlp::Print(hlp::PrintType::ERROR,
                   R"(section "{}" entry count in config is not matching -> expected: "{}" -> provided: "{}")",
                   CToS(section),
                   expected,
                   provided);
    }

    inline void PrintWrongDatatype(ConfigTypes const entry) {
        hlp::Print(
                hlp::PrintType::ERROR, "entry \"{}\" in config has wrong datatype {}", CToS(entry), defaultValuePrefix);
    }

    // check
    inline bool IsNull(nlohmann::json const& son, ConfigTypes const type) {
        assert(not son.is_null());
        if (son.is_array()) {
            PrintMissingSection(type);
            return true;
        }
        return false;
    }

    inline bool IsExistingSection(nlohmann::json const& son, ConfigTypes const type) {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            PrintMissingSection(type);
            return false;
        }
        return true;
    }

    inline bool IsExistingEntry(nlohmann::json const& son, ConfigTypes const type) {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            PrintMissingEntry(type);
            return false;
        }
        return true;
    }

    inline bool IsMatchingSize(nlohmann::json const& son, ConfigTypes const section, utl::usize const count) {
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
                                          ConfigTypes const section,
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

    [[nodiscard]] inline bool LoadString(nlohmann::json const& son, std::string& out, ConfigTypes const entry) {
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

    [[nodiscard]] inline bool LoadUSize(nlohmann::json const& son, utl::usize& out, ConfigTypes const entry) {
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

    [[nodiscard]] inline bool LoadFloat(nlohmann::json const& son, float& out, ConfigTypes const entry) {
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

    [[nodiscard]] inline bool LoadBool(nlohmann::json const& son, bool& out, ConfigTypes const entry) {
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
            SaveConfig();
            return false;
        }


        std::stringstream stream{ input };
        stream >> son;

        // from json
        // config
        if (IsNull(son, ConfigTypes::CONFIG)) {
            hlp::Print(hlp::PrintType::ERROR, "provided config is null {}", defaultValuePrefix);
            return false;
        }
        if (not IsMatchingSize(son, ConfigTypes::CONFIG, Global::configSectionCount)) {
            hlp::Print(hlp::PrintType::ERROR,
                       "config section count is not matching {} -> expected: {} -> provided: {}",
                       defaultValuePrefix,
                       Global::configSectionCount,
                       son.size());
        }
        // version
        if (nlohmann::json version; LoadSection(son, version, ConfigTypes::VERSION, Global::configVersionCount)) {
            if (std::string versionConfig; LoadString(version, versionConfig, ConfigTypes::VERSION_CONFIG)) {
                if (versionConfig != Global::configVersion) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "config version in config is not matching -> expected: {} -> provided: {} -> overwrite "
                               "config by "
                               "save",
                               Global::configVersion,
                               versionConfig);
                } else {
                    hlp::Print(hlp::PrintType::INFO, "config versions matching -> version: {}", versionConfig);
                }
            } else {
                hlp::Print(hlp::PrintType::ERROR, "unable to check if config version is matching");
            }
            if (std::string versionGame; LoadString(version, versionGame, ConfigTypes::VERSION_GAME)) {
                if (versionGame != Global::gameVersion) {
                    hlp::Print(hlp::PrintType::ERROR,
                               "game version is not matching -> expected: {} -> provided: {} -> overwrite by "
                               "save",
                               Global::gameVersion,
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
        assert(loadEntryCount == Constants::GetConfigValueCount());
        if (auto count = Constants::GetConfigValueCount(); loadEntryCount != count) {
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
        auto& constants = app::AppContext::GetInstance().constants;
        constants.window.isFullScreen = false;
        hlp::Print(hlp::PrintType::DEBUG, "set full screen to false");
        constants.window.currentResolutionEnum = Resolution::HD;
        hlp::Print(hlp::PrintType::DEBUG, "set resolution to HD");
#endif // _DEBUG
    }

} // namespace cst
