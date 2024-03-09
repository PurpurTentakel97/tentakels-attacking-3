//
// Purpur Tentakel
// 09.03.2024
//


#pragma once

#include <alias/AliasUtils.hpp>
#include <constants/G_Config_Enum.hpp>
#include <helper/HPrint.hpp>
#include <nlohmann/json.hpp>

namespace hlp {
    inline std::string const defaultValuePrefix{ "-> using default value -> overwrite by save" };
    // print
    inline void PrintMissingSection(cst::G_Config_Enum const section) {
        hlp::Print(hlp::PrintType::ERROR, "section \"{}\" in config missing {}", CToS(section), defaultValuePrefix);
    }

    inline void PrintMissingEntry(cst::G_Config_Enum const entry) {
        hlp::Print(hlp::PrintType::ERROR, "entry \"{}\" in config missing {}", CToS(entry), defaultValuePrefix);
    }

    inline void PrintNotMatchingCount(cst::G_Config_Enum const section,
                                      utl::usize const expected,
                                      utl::usize const provided) {
        hlp::Print(hlp::PrintType::ERROR,
                   R"(section "{}" entry count in config is not matching -> expected: "{}" -> provided: "{}")",
                   CToS(section),
                   expected,
                   provided);
    }

    inline void PrintWrongDatatype(cst::G_Config_Enum const entry) {
        hlp::Print(
                hlp::PrintType::ERROR, "entry \"{}\" in config has wrong datatype {}", CToS(entry), defaultValuePrefix);
    }

    // check
    inline bool IsNull(nlohmann::json const& son, cst::G_Config_Enum const type) {
        assert(not son.is_null());
        if (son.is_null()) {
            PrintMissingSection(type);
            return true;
        }
        return false;
    }

    inline bool IsExistingSection(nlohmann::json const& son, cst::G_Config_Enum const type) {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            PrintMissingSection(type);
            return false;
        }
        return true;
    }

    inline bool IsExistingEntry(nlohmann::json const& son, cst::G_Config_Enum const type) {
        assert(son.contains(CToS(type)));
        if (not son.contains(CToS(type))) {
            PrintMissingEntry(type);
            return false;
        }
        return true;
    }

    inline bool IsMatchingSize(nlohmann::json const& son, cst::G_Config_Enum const section, utl::usize const count) {
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
                                          cst::G_Config_Enum const section,
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

    [[nodiscard]] inline bool LoadString(nlohmann::json const& son,
                                         std::string& out,
                                         cst::G_Config_Enum const entry,
                                         utl::usize& loadEntryCount) {
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

    [[nodiscard]] inline bool LoadUSize(nlohmann::json const& son,
                                        utl::usize& out,
                                        cst::G_Config_Enum const entry,
                                        utl::usize& loadEntryCount) {
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

    [[nodiscard]] inline bool LoadFloat(nlohmann::json const& son,
                                        float& out,
                                        cst::G_Config_Enum const entry,
                                        utl::usize& loadEntryCount) {
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

    [[nodiscard]] inline bool LoadBool(nlohmann::json const& son,
                                       bool& out,
                                       cst::G_Config_Enum const entry,
                                       utl::usize& loadEntryCount) {
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
} // namespace hlp
