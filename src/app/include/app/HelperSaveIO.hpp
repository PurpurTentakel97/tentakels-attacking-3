//
// Purpur Tentakel
// 17.03.2024
//

#pragma once

#include "AppContext.hpp"
#include "G_Save_Enum.hpp"
#include "G_Global.hpp"
#include <alias/AliasUtils.hpp>
#include <event/EventsUI.hpp>
#include <helper/HLohmann.hpp>
#include <helper/HPrint.hpp>
#include <helper/SaveLoadFile.hpp>
#include <sstream>
#include <string>

namespace app {
    inline std::string const defaultValuePrefix{ "-> using default value -> overwrite by save" };

    [[nodiscard]] inline bool LoadAndValidateSaveJson(nlohmann::json& son,
                                                      utl::usize& currentEntryCount,
                                                      std::string const& dir,
                                                      std::string const& file) {
        auto const input       = hlp::TryLoadFile(dir, file);
        auto const& appContext = AppContext::GetInstance();
        if (input.empty()) {
            auto const event =
                    eve::ShowMessagePopUpEvent("Missing File", "not able to load save file: " + file, []() {});
            appContext.eventManager.InvokeEvent(event);
            hlp::Print(hlp::PrintType::ERROR, "not able to load save file: {}", file);
            return false;
        }

        auto const& constants = appContext.constants;
        std::stringstream stream{ input };
        stream >> son;

        if (hlp::IsNull(son, G_Save_Enum::G_SAVE)) {
            auto const event = eve::ShowMessagePopUpEvent("Empty File", "loaded file is empty: " + file, []() {});
            appContext.eventManager.InvokeEvent(event);
            hlp::Print(hlp::PrintType::ERROR, "loaded save file is empty: {}", file);
            return false;
        }

        if (nlohmann::json global; hlp::LoadSection(son, global, G_Save_Enum::G_GLOBAL, constants.g_saveFiles.total_version_count()))

    }
} // namespace app
