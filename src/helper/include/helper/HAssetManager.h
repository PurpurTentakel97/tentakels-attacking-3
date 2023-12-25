//
// Purpur Tentakel
// 31.08.2022
//

#pragma once

#include "HAssetType.hpp"
#include "CustomRaylib.h"
#include <array>
#include <unordered_map>
#include <string>
#include <vector>

/**
 * contains all assets and manage them
 */
class AssetManager final {
private:
	using FileArray = std::array<std::string, 9>; ///< the datatype for the files
	FileArray m_files{ ///< contains all asset file strings
		"btn_f_default.png",
		"exclamation_mark.png",
		"question_mark.png",
		"check.png",
		"logo.png",
		"arrow_up.png",
		"arrow_right.png",
		"arrow_down.png",
		"arrow_left.png",
	};
	std::unordered_map<AssetType, Texture2D> m_assets; ///< contains all assets
	std::vector<std::string> m_title; ///< contains the tile
	Font m_font; ///< contains the font

	/**
	 * loads the title.
	 */
	void LoadTitle();
	/**
	 * loads the font.
	 */
	void LoadFont();
	/**
	 * loads all files.
	 * ity important, that the file strings an the enum in in the same order
	 */
	void LoadFiles();

public:
	/**
	 * loads all needed files.
	 */
	AssetManager();
	/**
	 * unloads all needed files.
	 */
	~AssetManager();

	/**
	 * returns a texture* according to the AssetType.
	 */
	[[nodiscard]] Texture* GetTexture(AssetType assetType);
	/**
	 * returns a texture* according to the AssetType const.
	 */
	[[nodiscard]] Texture const* GetTexture(AssetType assetType) const;
	/**
	 * returns the title pointer.
	 */
	std::vector<std::string>* GetTitle();
	/**
	 * returns a font*.
	 */
	[[nodiscard]] Font const* GetFont() const;
};
