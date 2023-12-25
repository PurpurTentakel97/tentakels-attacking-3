//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <string>
#include <fstream>

/**
 * contains the file constants.
 */
struct CFiles final {
private:
	static inline const std::string m_configFile{ "config.tac" }; ///< config file name
	static inline std::string m_debugLogFile{ "default.txt" }; ///< debug log file name
	static inline const std::string m_debugLogDir{ "debug" }; ///< debug log dir name

public:
	static inline const std::string savesDir{ "saves" }; ///< saves dir name
	static inline std::ofstream debugLogStream{ }; ///< contains the debug log stream

	/**
	 * return the complete path of the config file.
	 */
	[[nodiscard]] inline std::string configFile() const {
		return { savesDir + "/" + m_configFile };
	}
	[[nodiscard]] inline std::string debugLogDir() const {
		return { savesDir + "/" + m_debugLogDir };
	}
	[[nodiscard]] inline std::string debugLogFile() const {
		return { debugLogDir() + "/" + m_debugLogFile };
	}
	void inline SetDebugLogFile(std::string const& filename) {
		m_debugLogFile = filename;
	}
};
