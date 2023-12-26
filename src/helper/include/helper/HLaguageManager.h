//
// Purpur Tentakel
// 18.06.2023
//

#pragma once
#include "HPrint.h"
#include "event/EventListener.hpp"
#include <nlohmann/json.hpp>
#include <format>

class HLanguageManager final : public EventListener {
private:
    nlohmann::json m_default_language_json;                      ///< contains all text in english
    nlohmann::json m_current_language_json;                      ///< contains all text in a specific language
    static inline std::vector<std::string> m_availableLanguages; ///< contains all available languages
    static inline std::string const m_wrong_format_text{
        "wrong format"
    }; ///< contains the default string. this gets returnd when the format is wrong
    static inline std::string const m_missing_language_text{
        "no language loaded"
    }; ///< contains the default string. this gets returnd when no language is loaded
    static inline std::string const m_default_text{
        "text not found"
    }; ///< contains the default string. this gets returnd when key is not exsisting
    static inline std::string const m_default_language{
        "english"
    }; ///< contains the default language -> gets loaded when the provided language is not able to be loaded
    static inline std::string const m_version_key{ "version" }; ///< contains the json key for the language version

    void InitializeLanguage();
    void InitializeAvailableLanguages();

    void ChanceLanguage(std::string const& language);
    [[nodiscard]] bool LoadLanguage(std::string const& language, bool const defaultLanguage = false);

    [[nodiscard]] std::pair<bool, std::string> RawText(std::string const& key, bool const defaultLanguage = false)
            const;

    [[nodiscard]] std::string ReplacePlaceholders(std::string const& text) const;
    template<typename... Args>
    [[nodiscard]] std::string ReplacePlaceholders(std::string_view text, Args const&... args) const;

public:
    HLanguageManager();

    void Initialize();

    [[nodiscard]] std::vector<std::string> GetAvailableLanguages() const;

    [[nodiscard]] std::string Text(std::string const& key) const;
    template<typename... Args>
    [[nodiscard]] std::string Text(std::string const& key, Args const&... args) const;

    void OnEvent(Event const& event) override;
};

template<typename... Args>
inline std::string HLanguageManager::ReplacePlaceholders(std::string_view text, Args const&... args) const {
    try {
        return std::vformat(text, std::make_format_args(args...));
    } catch (std::format_error const&) {
        Print(PrintType::ERROR,
              "wrong format for language text. appears mostly when arguments not matching the provided string -> "
              "\"{}\"",
              text);
        assert(false and "wrong format");
        return m_wrong_format_text;
    } catch (std::bad_alloc const&) {
        Print(PrintType::ERROR, "bad alloc while language text -> \"{}\"", text);
        assert(false and "bad alloc");
        return m_wrong_format_text;
    }
}

template<typename... Args>
inline std::string HLanguageManager::Text(std::string const& key, Args const&... args) const {
    auto [valid, text]{ RawText(key) };
    if (not valid) {
        text = RawText(key, true).second;
    }
    return ReplacePlaceholders(text, args...);
}
