//
// Purpur Tentakel
// 01.01.2023
//

#pragma once
#include <string>

/**
 * streams the error message into error log file.
 * creates the error log dirs and file if needed.
 */
void LogError(std::string const& error);
/**
 * closes the error log file if needed.
 */
void CloseErrorStream();
