//
// Purpur Tentakel
// 18.06.2023
//

#include "LanguageManager.hpp"
#include "AppContext.hpp"
#include <filesystem>

namespace app {
    void LanguageManager::InitializeLanguage() {
        bool const valid{ LoadLanguage(m_default_language, true) };
        if (not valid) {
            hlp::Print(
                    hlp::PrintType::ERROR,
                    R"(not able to load default language "{}" -> not able to show fallback text if the chosen language does )"
                    "not contain the key",
                    m_default_language
            );
        }
        ChanceLanguage(app::AppContext::GetInstance().constants.global.currentLanguageName);
    }

    void LanguageManager::InitializeAvailableLanguages() {
        std::string const directory{ "Assets/Languages" };
        m_availableLanguages.clear();
        auto const contains{ [&](std::string const& name) -> bool {
            for (auto const& f : m_availableLanguages) {
                if (f == name) {
                    return true;
                }
            }
            return false;
        } };

        if (not DirectoryExists(directory.c_str())) {
            hlp::Print(hlp::PrintType::ERROR, "directory \"{}\" not found -> no language available", directory);
            return;
        }
        for (auto const& entry : std::filesystem::directory_iterator(directory)) {
            std::filesystem::path file{ entry.path().filename() };
            if (not file.has_extension()) {
                hlp::Print(hlp::PrintType::ERROR, "language file \"{}\" has no extension", file.string());
                continue;
            }
            if (file.extension() != ".tal") {
                hlp::Print(hlp::PrintType::ERROR, "file \"{}\" has wrong datatype", file.string());
                continue;
            }
            auto const& fileName{ file.replace_extension() };
            if (contains(fileName.string())) {
                hlp::Print(hlp::PrintType::ERROR, "language \"{}\" loaded multiple times", fileName.string());
                continue;
            }
            m_availableLanguages.push_back(fileName.string());
        }
    }

    void LanguageManager::ChanceLanguage(std::string const& language) {
        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        auto handleUpdateLanguage{ [&]() {
            auto const event{ eve::UpdateLanguageInUIEvent(appContext.constants.global.currentLanguageName) };
            appContext.eventManager.InvokeEvent(event);
        } };

        bool const validLoad{ LoadLanguage(language) };

        if (not validLoad) {
            if (not m_current_language_json.empty()) {
                hlp::Print(hlp::PrintType::INFO, "not able to load new language -> fallback to old language");
                handleUpdateLanguage();
                return;
            }
            if (language != m_default_language) {
                bool const validDefaultLoad{ LoadLanguage(m_default_language) };
                if (validDefaultLoad) {
                    hlp::Print(hlp::PrintType::ERROR, "fallback to default language: \"{}\"", m_default_language);
                    handleUpdateLanguage();
                    return;
                }
                m_current_language_json.clear();
                appContext.constants.global.currentLanguageName = "";
                hlp::Print(hlp::PrintType::ERROR, "not able to load any language.");
            }
        } else {
            handleUpdateLanguage();
        }
    }

    bool LanguageManager::LoadLanguage(std::string const& language, bool const defaultLanguage) {
        bool found{ false };
        for (auto const& l : m_availableLanguages) {
            if (l == language) {
                found = true;
                break;
            }
        }
        if (not found) {
            assert(false and "language is not available");
            hlp::Print(hlp::PrintType::ERROR, "language \"{}\" is not available", language);
            return false;
        }

        std::string const directory{ "Assets/Languages" };
        if (not DirectoryExists(directory.c_str())) {
            assert(false and "language directory missing");
            hlp::Print(
                    hlp::PrintType::ERROR,
                    "directory \"{}\" not existing. unable to load provided language",
                    directory
            );
            return false;
        }

        std::ifstream in;
        in.open(directory + "/" + language + ".tal");
        if (not in.is_open()) {
            assert(false and "not able to open language file");
            hlp::Print(hlp::PrintType::ERROR, "not able tp open language: \"{}\"", language);
            return false;
        }

        try {
            if (defaultLanguage) {
                in >> m_default_language_json;
            } else {
                in >> m_current_language_json;
            }
        } catch (nlohmann::json::parse_error const& e) {
            assert(false and "language parse error");
            hlp::Print(
                    hlp::PrintType::ERROR,
                    "not able tp parse \"{}\" -> message: {} -> byte: {} -> id: {}",
                    language,
                    e.what(),
                    e.byte,
                    e.id
            );
            in.close();
            return false;
        }

        in.close();

        if (defaultLanguage) {
            hlp::Print(hlp::PrintType::INITIALIZE, "default language loaded -> \"{}\"", language);
        } else {
            app::AppContext::GetInstance().constants.global.currentLanguageName = language;

            hlp::Print(hlp::PrintType::INITIALIZE, "current language loaded -> \"{}\"", language);
        }

        nlohmann::json dummy{ nullptr };

        if (defaultLanguage) {
            dummy = m_default_language_json;
        } else {
            dummy = m_current_language_json;
        }

        if (dummy == nullptr) {
            assert(dummy);
            hlp::Print(
                    hlp::PrintType::ERROR,
                    "not able to check language version -> loaded language is nullptr -> \"{}\"",
                    language
            );
            return false;
        } else if (dummy.is_null()) {
            assert(not dummy.is_null());
            hlp::Print(
                    hlp::PrintType::ERROR,
                    "not able to check language version -> loaded language json in null -> \"{}\"",
                    language
            );
            return false;
        } else if (not dummy.contains(m_version_key)) {
            assert(dummy.contains(m_version_key));
            hlp::Print(
                    hlp::PrintType::ERROR,
                    R"(not able to check language version -> language does not contain key "{}" -> "{}")",
                    m_version_key,
                    language
            );
            return false;
        } else {
            auto const& version{ static_cast<std::string>(dummy[m_version_key]) };
            if (version == cst::Global::languageVersion) {
                hlp::Print(
                        hlp::PrintType::INFO,
                        R"(loaded language version matches the expected version -> "{}" -> "{}")",
                        language,
                        version
                );
            } else {
                if (defaultLanguage) {
                    hlp::Print(
                            hlp::PrintType::ERROR,
                            "versions of default language does not match -> language \"{}\" -> expected \"{}\" -> "
                            "provided "
                            "\"{}\" -> it is possible that not every text can be displayed",
                            language,
                            cst::Global::languageVersion,
                            version
                    );
                } else {
                    hlp::Print(
                            hlp::PrintType::ERROR,
                            "versions of current language does not match -> language \"{}\" -> expected -> \"{}\" -> "
                            "provided \"{}\" -> it is possible that the default language tried to be displayed",
                            language,
                            cst::Global::languageVersion,
                            version
                    );
                }
            }
        }

        return true;
    }

    std::pair<bool, std::string> LanguageManager::RawText(std::string const& key, bool const defaultLanguage) const {

        nlohmann::json dummy{};
        std::string dummyText{};

        if (defaultLanguage) {
            dummy = m_default_language_json;
            dummyText = "default";
        } else {
            dummy = m_current_language_json;
            dummyText = "current";
        }

        if (dummy == nullptr) {
            hlp::Print(hlp::PrintType::ERROR, "No {} language loaded", dummyText);
            return { false, m_missing_language_text };
        } else if (dummy.is_null()) {
            hlp::Print(hlp::PrintType::ERROR, "{} language is null", dummyText);
            return { false, m_missing_language_text };
        } else if (not dummy.contains(key)) {
            hlp::Print(hlp::PrintType::ERROR, "{} language does not contain \"{}\"", dummyText, key);
            return { false, m_default_text };
        } else {
            return { true, dummy[key] };
        }
    }
    std::string LanguageManager::ReplacePlaceholders(std::string const& text) {
        return text;
    }

    LanguageManager::LanguageManager() {
        hlp::Print(hlp::PrintType::INITIALIZE, "LanguageManager");
    }

    void LanguageManager::Initialize() {
        InitializeAvailableLanguages();
        InitializeLanguage();
    }

    std::vector<std::string> LanguageManager::GetAvailableLanguages() {
        return m_availableLanguages;
    }

    std::string LanguageManager::Text(std::string const& key) const {
        auto [valid, text]{ RawText(key) };

        if (valid) {
            return text;
        } else {
            return RawText(key, true).second;
        }
    }

    void LanguageManager::OnEvent(eve::Event const& event) {
        if (auto const* ChaneEvent = dynamic_cast<eve::ChangeLanguageEvent const*>(&event)) {
            ChanceLanguage(ChaneEvent->GetLanguage());
        }
    }
} // namespace app
