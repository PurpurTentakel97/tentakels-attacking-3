//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include <constants/CConstants.hpp>
#include <event/EventListener.hpp>
#include <event/EventManager.hpp>
#include <event/EventsUI.hpp>
#include <helper/HAssetManager.hpp>
#include <helper/HColors.hpp>
#include <helper/HConcepts.hpp>
#include <helper/HLaguageManager.hpp>
#include <helper/HLogicAlias.hpp>
#include <helper/HPlayerCollection.hpp>
#include <helper/HSoundManager.hpp>
#include <string>

struct AppContext final : public EventListener {
public:
    SoundManager soundManager;
    AssetManager assetManager;
    HLanguageManager languageManager;
    EventManager eventManager;
    PlayerCollection playerCollection;
    Colors colors;
    cst::Constants constants;

    [[nodiscard]] static AppContext_ty GetInstance();

    void LoadLanguages();

    void LoadConfig() const;

    static void SaveConfig();

    void ValidateConfig();

    template<arithmetic D>
    inline void ValidateMinCurrentMax(D min, D& current, D max) const {

        current = min <= current ? current : min;
        current = max >= current ? current : max;
    }

    template<arithmetic D>
    inline void ValidateMinMax(D& lhs, D& rhs, std::string const& lhsMessage, std::string const& rhsMessage) const {

        if (lhs < rhs) {
            return;
        }

        rhs = lhs + 1;
        ShowMessagePopUpEvent const event{ "Invalid Config",
                                           lhsMessage + " >= " + rhsMessage + "\nset " + rhsMessage + " to "
                                                   + std::to_string(rhs),
                                           []() {} };
        eventManager.InvokeEvent(event);
    }

    template<arithmetic D>
    inline void ValidateLowerEqual(D& value, D max, std::string const& valueMessage) const {

        if (value <= max) {
            return;
        }

        value = max;
        ShowMessagePopUpEvent const event{ "Invalid Config",
                                           valueMessage + " > " + std::to_string(max) + "\nset " + valueMessage + " to "
                                                   + std::to_string(value),
                                           []() {} };
        eventManager.InvokeEvent(event);
    }

    template<arithmetic D>
    inline void ValidateGreaterEqual(D& value, D min, std::string const& valueMessage) const {

        if (value >= min) {
            return;
        }

        value = min;
        ShowMessagePopUpEvent const event{ "Invalid Config",
                                           valueMessage + " < " + std::to_string(min) + "\nset " + valueMessage + " to "
                                                   + std::to_string(value),
                                           []() {} };
        eventManager.InvokeEvent(event);
    }

    void OnEvent(Event const& event) override;

    [[nodiscard]] Vector2 GetResolution() const;

    AppContext(AppContext const&) = delete;
    AppContext(AppContext&&) = delete;
    AppContext& operator=(AppContext const&) = delete;
    AppContext& operator=(AppContext&&) = delete;

private:
    AppContext();

    ~AppContext() override;
};
