//
// Purpur Tentakel
// 02.03.2024
//

#pragma once

#include <string>

namespace hlp {
    bool IsFileExisting(std::string const& dir, std::string const& file);

    void SaveFile(std::string const& dir, std::string const& file, std::string const& content);

    std::string TryLoadFile(std::string const& dir, std::string const& file);
} // namespace hlp
