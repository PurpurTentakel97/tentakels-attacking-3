//
// Purpur Tentakel
// 18.06.2023
//

#pragma once
#include "HPrint.hpp"
#include <event/EventListener.hpp>
#include <format>
#include <nlohmann/json.hpp>

class HLanguageManager final : public eve::EventListener {
private:
    nlohmann::json m_default_language_json;
    nlohmann::json m_current_language_json;
    static inline std::vector<std::string> m_availableLanguages;
    static inline std::string const m_wrong_format_text{ "wrong format" };
    static inline std::string const m_missing_language_text{ "no language loaded" };
    static inline std::string const m_default_text{ "text not found" };
    static inline std::string const m_default_language{ "english" };
    static inline std::string const m_version_key{ "version" };

    void InitializeLanguage();
    static void InitializeAvailableLanguages();

    void ChanceLanguage(std::string const& language);
    [[nodiscard]] bool LoadLanguage(std::string const& language, bool defaultLanguage = false);

    [[nodiscard]] std::pair<bool, std::string> RawText(std::string const& key, bool defaultLanguage = false) const;

    [[nodiscard]] static std::string ReplacePlaceholders(std::string const& text);
    template<typename... Args>
    [[nodiscard]] std::string ReplacePlaceholders(std::string_view text, Args const&... args) const;

public:
    HLanguageManager();

    void Initialize();

    [[nodiscard]] static std::vector<std::string> GetAvailableLanguages();

    [[nodiscard]] std::string Text(std::string const& key) const;
    template<typename... Args>
    [[nodiscard]] std::string Text(std::string const& key, Args const&... args) const;

    void OnEvent(eve::Event const& event) override;
};

template<typename... Args>
inline std::string HLanguageManager::ReplacePlaceholders(std::string_view const text, Args const&... args) const {
    try {
        return std::vformat(text, std::make_format_args(args...));
    } catch (std::format_error const&) {
        Print(PrintType::ERROR,
              "wrong format for language text. appears mostly when arguments not matching the provided string -> "
              R"("{}")",
              text);
        assert(false and "wrong format");
        return m_wrong_format_text;
    } catch (std::bad_alloc const&) {
        Print(PrintType::ERROR, R"(bad alloc while language text -> "{}")", text);
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
