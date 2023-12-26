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

/**
 * contains all global variables of the game.
 * contains all assets and colors.
 * contains the event management.
 * is a singleton.
 */
struct AppContext final : public EventListener {
public:
    SoundManager soundManager;         ///< loads and manage all sounds
    AssetManager assetManager;         ///< loads and manage all assets
    HLanguageManager languageManager;  /// loads and manages all language things
    EventManager eventManager;         ///< manage the EventListener and invokes events
    PlayerCollection playerCollection; ///< contains non logic info's about player
    Colors colors;                     ///< contains all colors and check valid color
    Constants constants;               ///< contains all constants of the game


    /**
	 * creates a Singleton.
	 * returns an instance.
	 */
    [[nodiscard]] static AppContext_ty GetInstance();

    /**
	 * loads the languages.
	 */
    void LoadLanguages();

    /**
	 * loads config.
	 * if no config exists a config is generated.
	 * validate loaded data.
	 */
    void LoadConfig();
    /**
	 * saves the config.
	 * is also used to generate a config if no config exists.
	 */
    void SaveConfig();

    /**
	 * validate all constants in constants that can be loaded by the config.
	 */
    void ValidateConfig();
    /**
	 * allows only arithmetic types.
	 * validate if a current value is between min and max.
	 * if not: the current value is set to the edge case.
	 */
    template<arithmetic D>
    inline void ValidateMinCurrentMax(D min, D& current, D max) const {

        current = min <= current ? current : min;
        current = max >= current ? current : max;
    }
    /**
	 * allows only arithmetic types.
	 * validate if lhs is smaller than rhs.
	 * if not: rhs is set to lhs +1.
	 * generates a popup if rhs gets set.
	 */
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
    /**
	 * allows only arithmetic types.
	 * validate if a value is smaller than or even to max.
	 * if not: value is set to max.
	 * generates a popup if value gets set.
	 */
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
    /**
	 * allows only arithmetic types.
	 * validate if a value is greater than or even to min.
	 * if not: value is set to min.
	 * generates a popup if value gets set.
	 */
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

    /**
	 * receives the events vom the manager.
	 * checks if the expected event is deployed if so it calls a member function.
	 */
    void OnEvent(Event const& event) override;

    /**
	 * returns the current resolution.
	 */
    [[nodiscard]] Vector2 GetResolution() const;

    AppContext(AppContext const&) = delete;
    AppContext(AppContext&&) = delete;
    AppContext& operator=(AppContext const&) = delete;
    AppContext& operator=(AppContext&&) = delete;

private:
    /**
	 * private Constructor so that the member function GetInstance()
	 * is the only place were an instance can be created.
	 */
    AppContext();

    /**
	 * just vor debugging
	 */
    ~AppContext() override;
};
