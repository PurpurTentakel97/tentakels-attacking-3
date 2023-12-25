//
// Purpur Tentakel
// 01.01.2023
//

#include "HErrorLog.h"
#include "AppContext.h"
#include "HPrint.h"
#include <filesystem>
#include <chrono>

/**
 * sets the name if the current error log file based on the chrono timestamp.
 */
void SetErrorLogFileName() {
	auto& files{ AppContext::GetInstance().constants.files };

	auto const now{ std::chrono::system_clock::now() };
	std::stringstream filename{ };
	filename << "tentakels_attacking_debug_" << now.time_since_epoch().count() << ".txt";

	files.SetDebugLogFile(filename.str());
	Print(PrintType::INFO, "debug file name set");
}

/**
 * opens the error log file.
 * creates the dirs and file if needed.
 */
void GenerateFileStream() {
	auto& files{ AppContext::GetInstance().constants.files };

	SetErrorLogFileName();

	if (!std::filesystem::exists(files.debugLogDir())) {
		std::filesystem::create_directories(files.debugLogDir());
		Print(PrintType::INFO, "created debug directory");
	}
	else if (!std::filesystem::is_directory(files.debugLogDir())) {
		std::filesystem::remove(files.debugLogDir());
		std::filesystem::create_directories(files.debugLogDir());
		Print(PrintType::INFO, "removed debug file and added debug directory");
	}

	files.debugLogStream.open(files.debugLogFile());
	Print(PrintType::INFO, "opened debug log");
}

void LogError(std::string const& error) {
	auto& files{ AppContext::GetInstance().constants.files };

	if (!files.debugLogStream.is_open()) {
		GenerateFileStream();
	}

	files.debugLogStream << error;
	Print(PrintType::INFO, "logged error");
}

void CloseErrorStream() {
	auto& files{ AppContext::GetInstance().constants.files };

	if (!files.debugLogStream.is_open()) {
		return;
	}

	files.debugLogStream.close();
	Print(PrintType::INFO, "closed debug log");
}
