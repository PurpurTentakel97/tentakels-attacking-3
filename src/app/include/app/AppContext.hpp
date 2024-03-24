//
// Purpur Tentakel
// 25.08.2022
//

#pragma once

#include "AliasManager.hpp"
#include "AssetManager.hpp"
#include "LanguageManager.hpp"
#include "PlayerCollection.hpp"
#include "SoundManager.hpp"
#include "utils/Concepts.hpp"
#include <logic/ManagerGame.hpp>
#include <alias/AliasApp.hpp>
#include <constants/CConstants.hpp>
#include <event/EventListener.hpp>
#include <event/EventManager.hpp>
#include <event/EventsUI.hpp>
#include <string>
#include <utils/Colors.hpp>

namespace app {
    struct AppContext final : public eve::EventListener {
    public:
        lgk::GameManager gameManager{};
        SoundManager soundManager;
        AssetManager assetManager;
        LanguageManager languageManager;
        eve::EventManager eventManager;
        PlayerCollection playerCollection;
        utl::Colors colors;
        cst::Constants constants;
        AliasManager aliasManager;

        [[nodiscard]] static AppContext_ty GetInstance();

        void LoadLanguages();

        void LoadConfig() const;

        static void SaveConfig();

        void LoadGame(std::string const& dir, std::string const& file);

        void SaveGame(std::string const& dir, std::string const& file) const;

        void ValidateConfig();

        template<utl::arithmetic D>
        inline void ValidateMinCurrentMax(D min, D& current, D max) const {

            current = min <= current ? current : min;
            current = max >= current ? current : max;
        }

        template<utl::arithmetic D>
        inline void ValidateMinMax(D& lhs, D& rhs, std::string const& lhsMessage, std::string const& rhsMessage) const {

            if (lhs < rhs) {
                return;
            }

            rhs = lhs + 1;
            eve::ShowMessagePopUpEvent const event{ "Invalid Config",
                                                    lhsMessage + " >= " + rhsMessage + "\nset " + rhsMessage + " to "
                                                            + std::to_string(rhs),
                                                    []() {} };
            eventManager.InvokeEvent(event);
        }

        template<utl::arithmetic D>
        inline void ValidateLowerEqual(D& value, D max, std::string const& valueMessage) const {

            if (value <= max) {
                return;
            }

            value = max;
            eve::ShowMessagePopUpEvent const event{ "Invalid Config",
                                                    valueMessage + " > " + std::to_string(max) + "\nset " + valueMessage
                                                            + " to " + std::to_string(value),
                                                    []() {} };
            eventManager.InvokeEvent(event);
        }

        template<utl::arithmetic D>
        inline void ValidateGreaterEqual(D& value, D min, std::string const& valueMessage) const {

            if (value >= min) {
                return;
            }

            value = min;
            eve::ShowMessagePopUpEvent const event{ "Invalid Config",
                                                    valueMessage + " < " + std::to_string(min) + "\nset " + valueMessage
                                                            + " to " + std::to_string(value),
                                                    []() {} };
            eventManager.InvokeEvent(event);
        }

        void OnEvent(eve::Event const& event) override;

        [[nodiscard]] Vector2 GetResolution() const;

        void Unload();

        AppContext(AppContext const&)            = delete;
        AppContext(AppContext&&)                 = delete;
        AppContext& operator=(AppContext const&) = delete;
        AppContext& operator=(AppContext&&)      = delete;

    private:
        AppContext();

        ~AppContext() override;
    };
} // namespace app
