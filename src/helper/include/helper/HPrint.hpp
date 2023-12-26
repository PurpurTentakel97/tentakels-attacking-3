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

/**
 * provides all kinds of print types.
 */
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

/**
 * returns the provided print type as string.
 */
[[nodiscard]] static inline std::string GetPrintTypeString(PrintType printType) {
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
/**
 * exports the message when according to the print type.
 */
static inline void TryExport(std::string const& message, PrintType printType) {
    switch (printType) {
        case PrintType::EXPECTED_ERROR:
        case PrintType::ERROR:
            LogError(message);
            break;
        default:
            break;
    }
}

/**
 * print to the console with a print type tag and additional values.
 * values must match with the provided `{}` inside the string.
 */
template<typename... Args>
void Print(PrintType printType, std::string const& message, Args const&... args);
/**
 * print to the console with a print type tag.
 */
void Print(PrintType printType, std::string const& message);

template<typename... Args>
inline void Print(PrintType printType, std::string const& message, Args const&... args) {
#ifndef _DEBUG
    if (printType == PrintType::ONLY_DEBUG) {
        return;
    }
#endif // _DEBUG

    std::string const typeS{ GetPrintTypeString(printType) };
    std::string const toExport{ typeS + ' ' + message + '\n' };
    try {
        std::string out{ std::vformat(message, std::make_format_args(args...)) };
        std::cout << std::setw(static_cast<int>(GetPrintTypeString(longestType).size())) << typeS << ' ' << out << '\n';
        TryExport(toExport, printType);

    } catch (std::format_error const&) {
        Print(PrintType::ERROR, "format while printing with arguments");
        std::cout << std::setw(static_cast<int>(GetPrintTypeString(longestType).size())) << typeS << ' ' << message
                  << '\n';
        TryExport(toExport, printType);
    } catch (std::bad_alloc const&) {
        Print(PrintType::ERROR, "bad alloc while printing with arguments");
        std::cout << std::setw(static_cast<int>(GetPrintTypeString(longestType).size())) << typeS << ' ' << message
                  << '\n';
        TryExport(toExport, printType);
    }
}