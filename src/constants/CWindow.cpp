//
// Purpur Tentakel
// 10.12.2022
//

#include "CWindow.hpp"
#include <CustomRaylib.hpp>
#include <helper/HPrint.hpp>

bool CWindow::IsPossibleResolution(Resolution toProve) const {
    auto const value = GetIntFromResolution(toProve) ;

    if (nativeResolutionVec.x < value.x) {
        return false;
    }
    if (nativeResolutionVec.y < value.y) {
        return false;
    }
    return true;
}

std::vector<std::pair<Resolution, std::string>> CWindow::GetAllResolutionsAsString() const {
    std::vector<std::pair<Resolution, std::string>> toReturn;

    for (int i = 0; i != static_cast<int>(Resolution::LAST); ++i) {

        Resolution const entry{ static_cast<Resolution>(i) };

        if (!IsPossibleResolution(entry)) {
            continue;
        }
        toReturn.emplace_back(entry, GetStringFromResolution(entry));
    }

    return toReturn;
}

std::string CWindow::GetStringFromResolution(Resolution resolution) const {

    switch (resolution) {

            // 16:9
        case Resolution::UHD2:
            return "UHD2 16:9 (7600 x 4320)";
        case Resolution::_5K:
            return "5K 16:9 (5120 x 2160)";
        case Resolution::UHD1:
            return "UHD1 16:9 (3840 x 2162)";
        case Resolution::WQHD:
            return "WQHD 16:9 (2560 x 1440)";
        case Resolution::FULL_HD:
            return "Full HD 16:9 (1920 x 1080)";
        case Resolution::HD:
            return "HD 16:9 (1280 x 720)";

            // 21:9
        case Resolution::_5K_ULTRA_WIDE:
            return "5K Ultrawide 21:9 (5120 x 2160)";
        case Resolution::UWQHD:
            return "UWQHD 21:9 (3440 x 1440)";
        case Resolution::UWHD:
            return "UWHD 21:9 (2560 X 1080)";

            // 4:3
        case Resolution::QXGA:
            return "QXGA 4:3 (2048 x 1536)";
        case Resolution::UXGA:
            return "UXGA 4:3 (1600 x 1200)";
        case Resolution::SXGA_Plus:
            return "SXGA Plus 4:3 (1400 x 1050)";
        case Resolution::XGA_plus:
            return "XGA Plus 4:3 (1152 x 864)";
        case Resolution::XGA:
            return "XGA 4:3 (1024 x 768)";
        case Resolution::SVGA:
            return "SVGA 4:3 (800 x 600)";
        case Resolution::PAL:
            return "PAL 4:3 (768 x 576)";
        case Resolution::VGA:
            return "VGA 4:3 (640 x 480)";

        case Resolution::NATIVE:
            return "Native (" + std::to_string(nativeResolutionVec.x) + " x " + std::to_string(nativeResolutionVec.y)
                   + ")";
        case Resolution::SCREEN: {
            auto const value = GetIntFromResolution(resolution);
            return "Screen (" + std::to_string(value.x) + " x " + std::to_string(value.y) + ")";
        }
        case Resolution::LAST:
        default:
            Print(PrintType::ERROR, "invalid resolution selected {}", static_cast<int>(resolution));
            return "invalid resolution";
    }
}

HVec2<int> CWindow::GetIntFromResolution(Resolution resolution) const {

    switch (resolution) {

            // 16:9
        case Resolution::UHD2:
            return { 7600, 4320 };
        case Resolution::_5K:
            return { 5120, 2160 };
        case Resolution::UHD1:
            return { 3840, 2162 };
        case Resolution::WQHD:
            return { 2560, 1440 };
        case Resolution::FULL_HD:
            return { 1920, 1080 };
        case Resolution::HD:
            return { 1280, 720 };

            // 21:9
        case Resolution::_5K_ULTRA_WIDE:
            return { 5120, 2460 };
        case Resolution::UWQHD:
            return { 3440, 1440 };
        case Resolution::UWHD:
            return { 2560, 1080 };

            // 4:3
        case Resolution::QXGA:
            return { 2048, 1536 };
        case Resolution::UXGA:
            return { 1600, 1200 };
        case Resolution::SXGA_Plus:
            return { 1400, 1050 };
        case Resolution::XGA_plus:
            return { 1152, 864 };
        case Resolution::XGA:
            return { 1024, 768 };
        case Resolution::SVGA:
            return { 800, 600 };
        case Resolution::PAL:
            return { 768, 576 };
        case Resolution::VGA:
            return { 640, 480 };


        case Resolution::NATIVE:
            return nativeResolutionVec;
        case Resolution::SCREEN: {
            int const screen{ GetCurrentMonitor() };
            int const height{ GetMonitorHeight(screen) };
            int const width{ GetMonitorWidth(screen) };

            return { width, height };
        }
        case Resolution::LAST:
        default:
            Print(PrintType::ERROR, "invalid resolution selected {}", static_cast<int>(resolution));
            return { 100, 100 };
    }
}
