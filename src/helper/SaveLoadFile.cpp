//
// Purpur Tentakel
// 02.03.2024
//

#include "SaveLoadFile.hpp"
#include "HPrint.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace hlp {
    static std::string Join(std::string const& dir, std::string const& file) {
        return dir + '/' + file;
    }

    static void GenDir(std::string const& dir) {
        if (not std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
            Print(PrintType::INFO, "directory generated:{}", dir);
        }
    }

    bool IsFileExisting(std::string const& dir, std::string const& file) {
        return std::filesystem::exists(Join(dir, file));
    }

    void SaveFile(std::string const& dir, std::string const& file, std::string const& content) {
        GenDir(dir);

        std::ofstream f{};

        f.open(Join(dir, file));
        f << content;
        f.close();
    }

    std::string TryLoadFile(std::string const& dir, std::string const& file) {
        if (not IsFileExisting(dir, file)) {
            Print(PrintType::ERROR, "file does not exists: {}", Join(dir, file));
            return "";
        }

        std::ifstream f{};

        f.open(Join(dir, file));
        if (not f.is_open()){
            Print(PrintType::ERROR, "not able to open file: {}", Join(dir, file));
            return "";
        }

        std::stringstream stream;
        stream << f.rdbuf();
        f.close();
        return stream.str();
    }
} // namespace hlp
