//
// Purpur Tentakel
// 01.01.2023
//

#include "HErrorLog.hpp"
#include "HPrint.hpp"
#include <chrono>
#include <constants/CFiles.hpp>
#include <filesystem>

void SetErrorLogFileName() {
    auto const now{ std::chrono::system_clock::now() };
    std::stringstream filename{};
    filename << "tentakels_attacking_debug_" << now.time_since_epoch().count() << ".txt";

    cst::CFiles::SetDebugLogFile(filename.str());
    Print(PrintType::INFO, "debug file name set");
}

void GenerateFileStream() {
    SetErrorLogFileName();

    if (!std::filesystem::exists(cst::CFiles::debugLogDir())) {
        std::filesystem::create_directories(cst::CFiles::debugLogDir());
        Print(PrintType::INFO, "created debug directory");
    } else if (!std::filesystem::is_directory(cst::CFiles::debugLogDir())) {
        std::filesystem::remove(cst::CFiles::debugLogDir());
        std::filesystem::create_directories(cst::CFiles::debugLogDir());
        Print(PrintType::INFO, "removed debug file and added debug directory");
    }

    cst::CFiles::debugLogStream.open(cst::CFiles::debugLogFile());
    Print(PrintType::INFO, "opened debug log");
}

void LogError(std::string const& error) {
    if (!cst::CFiles::debugLogStream.is_open()) {
        GenerateFileStream();
    }

    cst::CFiles::debugLogStream << error;
    Print(PrintType::INFO, "logged error");
}

void CloseErrorStream() {
    if (!cst::CFiles::debugLogStream.is_open()) {
        return;
    }

    cst::CFiles::debugLogStream.close();
    Print(PrintType::INFO, "closed debug log");
}
