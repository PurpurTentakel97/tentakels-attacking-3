//
// Purpur Tentakel
// 19.10.2022
//

#pragma once
#include <CustomRaylib.hpp>
#include <string>


struct PlayerData final {
    unsigned int ID{ 0 };
    Color color{ WHITE };
    PlayerData(unsigned int id, std::string name, Color col, std::string key = "");

    void SetName(std::string const& name);
    [[nodiscard]] std::string GetName() const;

private:
    std::string m_name{};
    std::string m_nameKey{};
};

[[nodiscard]] inline bool SortPlayerByID_ASC(PlayerData const& lhs, PlayerData const& rhs) {
    return lhs.ID < rhs.ID;
}

[[nodiscard]] inline bool SortPlayerByID_DSC(PlayerData const& lhs, PlayerData const& rhs) {
    return lhs.ID > rhs.ID;
}

[[nodiscard]] inline bool operator==(PlayerData const& lhs, PlayerData const& rhs) {
    return lhs.ID == rhs.ID;
}

[[nodiscard]] inline bool operator!=(PlayerData const& lhs, PlayerData const& rhs) {
    return !(lhs == rhs);
}
