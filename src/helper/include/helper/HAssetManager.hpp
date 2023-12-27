//
// Purpur Tentakel
// 31.08.2022
//

#pragma once

#include "HAssetType.hpp"
#include <CustomRaylib.hpp>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>


class AssetManager final {
private:
    using FileArray = std::array<std::string, 9>;
    FileArray m_files{
        // clang-format off
        "btn_f_default.png",
        "exclamation_mark.png",
        "question_mark.png",
        "check.png",
        "logo.png",
        "arrow_up.png",
        "arrow_right.png",
        "arrow_down.png",
        "arrow_left.png",
        // clang-format on
    };
    std::unordered_map<AssetType, Texture2D> m_assets;
    std::vector<std::string> m_title;
    Font m_font;

    void LoadTitle();

    void LoadFont();

    void LoadFiles();

public:
    AssetManager();

    ~AssetManager();

    [[nodiscard]] Texture* GetTexture(AssetType assetType);

    [[nodiscard]] Texture const* GetTexture(AssetType assetType) const;

    std::vector<std::string>* GetTitle();

    [[nodiscard]] Font const* GetFont() const;
};
