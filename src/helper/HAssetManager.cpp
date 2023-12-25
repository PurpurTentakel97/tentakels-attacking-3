//
// Purpur Tentakel
// 31.08.2022
//

#include "HAssetManager.h"
#include "HPrint.h"
#include <fstream>
#include <filesystem>


void AssetManager::LoadTitle() {
	std::fstream newFile;
	m_title.clear();
	std::string line;

	std::string const filename{ "Assets/Text/title.txt" };
	if (!std::filesystem::exists(filename)) {
		Print(
			PrintType::ERROR,
			"title does not exists -> {}",
			filename
		);
		return;
	}

	newFile.open(filename, std::ios::in);

	if (!newFile.is_open()) {
		Print(
			PrintType::ERROR,
			"can't open title -> {}",
			filename
		);
		return;
	}

	while (getline(newFile, line)) {
		m_title.push_back(line);
	}

	newFile.close();
}
void AssetManager::LoadFont() {
	std::string const filename{ "Assets/Fonts/default_font.ttf" };

	if (!std::filesystem::exists(filename)) {
		Print(
			PrintType::ERROR,
			"font does not exist -> {}",
			filename
		);
		return;
	}

	m_font = LoadFontEx(filename.c_str(), 128, 0, 250);

}

void AssetManager::LoadFiles() {
	for (int i = 0; i < m_files.size(); ++i) {
		auto const filename{ "Assets/Pictures/" + m_files.at(i) };

		if (!std::filesystem::exists(filename)) {
			Print(
				PrintType::ERROR,
				"Assets does not exist -> {}",
				filename
			);
			continue;
		}

		Texture2D const texture{ LoadTexture(filename.c_str()) };
		m_assets[static_cast<AssetType>(i)] = texture;
	}
}

AssetManager::AssetManager() {
	LoadFiles();
	LoadTitle();
	LoadFont();
}
AssetManager::~AssetManager() {
	for (auto const &[type, asset] : m_assets) {
		UnloadTexture(asset);
	}
	UnloadFont(m_font);
}

Texture* AssetManager::GetTexture(AssetType assetType) {
	return &m_assets.at(assetType);
}
Texture const* AssetManager::GetTexture(AssetType assetType) const {
	return &m_assets.at(assetType);
}
std::vector<std::string>* AssetManager::GetTitle() {
	return &m_title;
}
Font const* AssetManager::GetFont() const {
	return &m_font;
}
