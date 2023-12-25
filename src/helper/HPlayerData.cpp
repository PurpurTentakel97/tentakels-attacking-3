//
// Purpur Tentakel
// 36.06.2023
//

#include "HPlayerData.h"
#include "AppContext.h"

PlayerData::PlayerData(unsigned int id, std::string const& name, Color col, std::string const& key)
	: ID{ id }, color{ col }, m_name{ name }, m_nameKey{ key }{ }

void PlayerData::SetName(std::string const& name) {
	m_name = name;
}

std::string PlayerData::GetName() const {
	if (not m_name.empty()) { return m_name; }
	return AppContext::GetInstance().languageManager.Text(m_nameKey);
}
