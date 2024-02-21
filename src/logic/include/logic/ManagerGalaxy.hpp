//
// PurpurTentakel
// 23.05.23
//

#pragma once
#include <alias/AliasEvent.hpp>
#include <alias/AliasLogic.hpp>
#include <alias/AliasUtils.hpp>
#include <memory>
#include <vector>


namespace lgk {
    class GalaxyManager final {
        friend class Galaxy;

    private:
        GameManager* m_gameManager;
        Galaxy_ty m_mainGalaxy{ nullptr };
        Galaxy_ty m_startGalaxy{ nullptr };
        Galaxy_ty m_currentGalaxy{ nullptr };
        Galaxy_ty m_showGalaxy{ nullptr };

        void FilterCurrentGalaxy();

    public:
        explicit GalaxyManager(GameManager* gameManager);

        void GenerateGalaxy();

        void GenerateShowGalaxy();

        void CopyGalaxies(CopyGalaxyType copyType);

        [[nodiscard]] Galaxy* GetGalaxy();

        [[nodiscard]] bool AddFleet(eve::SendFleetInstructionEvent const* event, Player_ty const& currentPlayer);

        [[nodiscard]] bool HasMovesLeft(Player_ty_c player) const;

        void KillPlayer(Player_ty_c player, Player_ty_c neutral_player);

        [[nodiscard]] utl::ResultUpdate Update();

        [[nodiscard]] std::shared_ptr<utl::ResultEventPirates> HandlePirates(Player_ty_c pirate, utl::usize ships);

        [[nodiscard]] std::shared_ptr<utl::ResultEventRevolts> HandleRevolts(Player_ty_c player);

        [[nodiscard]] std::shared_ptr<utl::ResultEventSupernova> HandleSupernova(Player_ty_c invalid_player);

        [[nodiscard]] std::shared_ptr<utl::ResultEventEngineProblem> HandleEngineProblem(utl::usize years);
    };
} // namespace lgk
