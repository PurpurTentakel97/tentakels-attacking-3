//
// Purpur Tentakel
// 01.01.2023
//

#include "HErrorLog.hpp"
#include "HPrint.hpp"
#include <chrono>
#include <constants/CFiles.hpp>
#include <filesystem>

namespace hlp {
    void SetErrorLogFileName() {
        auto const now{ std::chrono::system_clock::now() };
        std::stringstream filename{};
        filename << "tentakels_attacking_debug_" << now.time_since_epoch().count() << ".txt";

        cst::Files::SetDebugLogFile(filename.str());
        Print(PrintType::INFO, "debug file name set");
    }

    void GenerateFileStream() {
        SetErrorLogFileName();

        if (!std::filesystem::exists(cst::Files::debugLogDir())) {
            std::filesystem::create_directories(cst::Files::debugLogDir());
            Print(PrintType::INFO, "created debug directory");
        } else if (!std::filesystem::is_directory(cst::Files::debugLogDir())) {
            std::filesystem::remove(cst::Files::debugLogDir());
            std::filesystem::create_directories(cst::Files::debugLogDir());
            Print(PrintType::INFO, "removed debug file and added debug directory");
        }

        cst::Files::s_debugLogStream.open(cst::Files::debugLogDir() + '/' +  cst::Files::s_debugLogFile);
        Print(PrintType::INFO, "opened debug log");
    }

    void LogError(std::string const& error) {
        if (!cst::Files::s_debugLogStream.is_open()) {
            GenerateFileStream();
        }

        cst::Files::s_debugLogStream << error;
        Print(PrintType::INFO, "logged error");
    }

    void CloseErrorStream() {
        if (!cst::Files::s_debugLogStream.is_open()) {
            return;
        }

        cst::Files::s_debugLogStream.close();
        Print(PrintType::INFO, "closed debug log");
    }
} // namespace hlp
