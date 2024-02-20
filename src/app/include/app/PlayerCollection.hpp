//
// Purpur Tentakel
// 11.10.2022
//

#pragma once

#include "PlayerData.hpp"
#include <alias/AliasUtils.hpp>
#include <array>
#include <event/EventListener.hpp>
#include <helper/HGeneral.hpp>
#include <string>
#include <vector>

namespace app {
    class PlayerCollection final : public eve::EventListener {
    private:
        std::vector<PlayerData> m_playerData;
        std::vector<PlayerData> m_npcData{
            { 100, "", WHITE, "helper_player_collection_npc_neutral_player" },
            { 101, "", RED,   "helper_player_collection_npc_no_player"      },
        };
        PlayerData m_defaultPlayer{ 0, "", WHITE, "helper_player_collection_npc_no_player" };

        [[nodiscard]] bool ContainsName(std::string const& name) const;

        [[nodiscard]] bool ContainsColor(Color color) const;

        void CheckValidColor(Color& color) const;

        void CheckRemainingColor(Color& color);

        void CheckRemainingName(std::string& name);

        [[nodiscard]] PlayerData& GetPlayerByIDmut(utl::usize ID);

        void SortPlayers();

        void AddPlayer(utl::usize ID, std::string name, Color color);

        void EditPlayer(utl::usize ID, std::string name, Color color);

        void DeletePlayer(utl::usize ID);

        void ResetPlayer();

    public:
        [[nodiscard]] Color GetPossibleColor() const;

        [[nodiscard]] std::vector<PlayerData> GetPlayerData() const;

        [[nodiscard]] PlayerData GetPlayerByID(utl::usize ID) const;

        [[nodiscard]] PlayerData GetPlayerOrNpcByID(utl::usize ID) const;

        [[nodiscard]] PlayerData GetPlayerByIDOrDefaultPlayer(utl::usize ID) const;

        [[nodiscard]] PlayerData GetPlayerByName(std::string const& name) const;

        [[nodiscard]] PlayerData GetPlayerByColor(Color color) const;

        [[nodiscard]] Color GetColorByID(utl::usize ID) const;

        [[nodiscard]] utl::usize GetPlayerCount() const;

        void OnEvent(eve::Event const& event) override;
    };
} // namespace app
