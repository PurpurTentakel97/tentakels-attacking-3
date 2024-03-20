//
// Purpur Tentakel
// 09.03.2024
//


#pragma once

#include <alias/AliasUtils.hpp>
#include <utils/G_Save_Enum.hpp>
#include <constants/G_Config_Enum.hpp>
#include <helper/HPrint.hpp>
#include <nlohmann/json.hpp>
#include <utils/Concepts.hpp>

namespace hlp {
    inline std::string const defaultValuePrefix{ "-> using default value -> overwrite by save" };

    static std::string EToS(cst::G_Config_Enum const value) {
        return cst::CToS(value);
    }
    [[maybe_unused]] static std::string EToS(utl::G_Save_Enum const value) {
        return utl::SToS(value);
    }

    // print
    template<utl::IsEnum E>
    inline void PrintMissingSection(E const section) {
        Print(PrintType::ERROR, "section \"{}\" in config missing {}", EToS(section), defaultValuePrefix);
    }

    template<utl::IsEnum E>
    inline void PrintMissingEntry(E const entry) {
        Print(PrintType::ERROR, "entry \"{}\" in config missing {}", EToS(entry), defaultValuePrefix);
    }

    template<utl::IsEnum E>
    inline void PrintNotMatchingCount(E const section, utl::usize const expected, utl::usize const provided) {
        Print(PrintType::ERROR,
              R"(section "{}" entry count in config is not matching -> expected: "{}" -> provided: "{}")",
              EToS(section),
              expected,
              provided);
    }

    template<utl::IsEnum E>
    inline void PrintWrongDatatype(E const entry) {
        Print(PrintType::ERROR, "entry \"{}\" in config has wrong datatype {}", EToS(entry), defaultValuePrefix);
    }

    // check
    template<utl::IsEnum E>
    inline bool IsNull(nlohmann::json const& son, E const type) {
        assert(not son.is_null());
        if (son.is_null()) {
            PrintMissingSection(type);
            return true;
        }
        return false;
    }

    template<utl::IsEnum E>
    inline bool IsExistingSection(nlohmann::json const& son, E const type) {
        assert(son.contains(EToS(type)));
        if (not son.contains(EToS(type))) {
            PrintMissingSection(type);
            return false;
        }
        return true;
    }

    template<utl::IsEnum E>
    inline bool IsExistingEntry(nlohmann::json const& son, E const type) {
        assert(son.contains(EToS(type)));
        if (not son.contains(EToS(type))) {
            PrintMissingEntry(type);
            return false;
        }
        return true;
    }

    template<utl::IsEnum E>
    inline bool IsMatchingSize(nlohmann::json const& son, E const section, utl::usize const count) {
        assert(son.size() == count);
        if (son.size() != count) {
            PrintNotMatchingCount(section, count, son.size());
            return false;
        }
        return true;
    }

    // load
    template<utl::IsEnum E>
    [[nodiscard]] inline bool LoadSection(nlohmann::json const& son,
                                          nlohmann::json& out,
                                          E const section,
                                          utl::usize const count) {
        if (not IsExistingSection(son, section)) {
            return false;
        }
        son.at(EToS(section)).get_to(out);

        if (IsNull(out, section)) {
            return false;
        }
        if (count != 0) {
            IsMatchingSize(out, section, count);
        }
        return true;
    }

    template<utl::IsEnum E>
    [[nodiscard]] inline bool LoadString(nlohmann::json const& son,
                                         std::string& out,
                                         E const entry,
                                         utl::usize& loadEntryCount) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(EToS(entry)).is_string());
        if (not son.at(EToS(entry)).is_string()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(EToS(entry)).get_to(out);
        return true;
    }

    template<utl::IsEnum E>
    [[nodiscard]] inline bool LoadUSize(nlohmann::json const& son,
                                        utl::usize& out,
                                        E const entry,
                                        utl::usize& loadEntryCount) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(EToS(entry)).is_number_unsigned());
        if (not son.at(EToS(entry)).is_number_unsigned()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(EToS(entry)).get_to(out);
        return true;
    }

    template<utl::IsEnum E>
    [[nodiscard]] inline bool LoadFloat(nlohmann::json const& son,
                                        float& out,
                                        E const entry,
                                        utl::usize& loadEntryCount) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(EToS(entry)).is_number_float());
        if (not son.at(EToS(entry)).is_number_float()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(EToS(entry)).get_to(out);
        return true;
    }

    template<utl::IsEnum E>
    [[nodiscard]] inline bool LoadBool(nlohmann::json const& son,
                                       bool& out,
                                       E const entry,
                                       utl::usize& loadEntryCount) {
        ++loadEntryCount;
        if (not IsExistingEntry(son, entry)) {
            return false;
        }
        assert(son.at(EToS(entry)).is_boolean());
        if (not son.at(EToS(entry)).is_boolean()) {
            PrintWrongDatatype(entry);
            return false;
        }

        son.at(EToS(entry)).get_to(out);
        return true;
    }
} // namespace hlp
