//
// Purpur Tentakel
// 28.10.2022
//

#pragma once

#include "HErrorLog.hpp"
#include <format>
#include <iomanip>
#include <iostream>
#include <string>


namespace hlp {
    enum class PrintType {
        INFO,
        EXPECTED_ERROR,
        ERROR,
        INITIALIZE,
        BUILD,
        ONLY_DEBUG,
        DEBUG,
        TODO,
    };
    static PrintType longestType{ PrintType::EXPECTED_ERROR };

    [[nodiscard]] static inline std::string GetPrintTypeString(PrintType const printType) {
        switch (printType) {
            default:
            case PrintType::INFO:
                return "[INFO]";
            case PrintType::EXPECTED_ERROR:
                return "[EXPECTED_ERROR]";
            case PrintType::ERROR:
                return "[ERROR]";
            case PrintType::INITIALIZE:
                return "[INITIALIZE]";
            case PrintType::BUILD:
                return "[BUILD]";
            case PrintType::ONLY_DEBUG:
                return "[ONLY_DEBUG]";
            case PrintType::DEBUG:
                return "[DEBUG]";
            case PrintType::TODO:
                return "[TODO]";
        }
    }

    static inline void TryExport(std::string const& message, PrintType const printType) {
        switch (printType) {
            case PrintType::EXPECTED_ERROR:
            case PrintType::ERROR:
                LogError(GetPrintTypeString(printType) + ' ' + message + '\n');
                break;
            default:
                break;
        }
    }

    template<typename... Args>
    void Print(PrintType printType, std::string const& message, Args const&... args);

    void Print(PrintType printType, std::string const& message);

    template<typename... Args>
    inline void Print(PrintType const printType, std::string const& message, Args const&... args) {
#ifdef NDEBUG
        if (printType == PrintType::ONLY_DEBUG) {
            return;
        }
#endif // NDEBUG

        std::string const typeS{ GetPrintTypeString(printType) };
        try {
            std::string out{ std::vformat(message, std::make_format_args(args...)) };
            std::cout << std::setw(static_cast<int>(GetPrintTypeString(longestType).size())) << typeS << ' ' << out
                      << '\n';
            TryExport(out, printType);

        } catch (std::format_error const&) {
            Print(PrintType::ERROR, "format while printing with arguments");
            std::cout << std::setw(static_cast<int>(GetPrintTypeString(longestType).size())) << typeS << ' ' << message
                      << '\n';
            TryExport(message, printType);
        } catch (std::bad_alloc const&) {
            Print(PrintType::ERROR, "bad alloc while printing with arguments");
            std::cout << std::setw(static_cast<int>(GetPrintTypeString(longestType).size())) << typeS << ' ' << message
                      << '\n';
            TryExport(message, printType);
        }
    }
} // namespace hlp
