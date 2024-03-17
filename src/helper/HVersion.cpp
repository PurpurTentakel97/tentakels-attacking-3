//
// Purpur Tentakel
// 17.03.2024
//

#include "HVersion.hpp"
#include <cassert>
#include <regex>

namespace hlp {
    version_ty ParseVersion(std::string const& versionString) {
        version_ty versionNumbers{};
        std::regex pattern(R"(v(\d+)\.(\d+)\.(\d+)\.(\d+))");
        std::smatch matches;
        if (std::regex_match(versionString, matches, pattern)) {
            for (size_t i = 1; i < matches.size(); ++i) {
                versionNumbers[i - 1] = (static_cast<utl::usize>(std::stoi(matches[i])));
            }
        }
        return versionNumbers;
    }

    VersionResult CompareVersion(std::string const& provided, std::string const& expected) {
        return CompareVersion(ParseVersion(provided), ParseVersion(expected));
    }
    VersionResult CompareVersion(version_ty const& provided, version_ty const& expected) {
        assert(provided.size() == expected.size());
        for (utl::usize i = 0; i < provided.size(); ++i) {
            if (provided[i] > expected[i]) {
                return VersionResult::HIGHER;
            }
            if (provided[i] < expected[i]) {
                return VersionResult::LOWER;
            }
        }
        return VersionResult::SAME;
    }

} // namespace hlp
