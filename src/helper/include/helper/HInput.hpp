//
// Purpur Tentakel
// 24.10.2022
//

#pragma once

namespace hlp {
    // confirm
    [[nodiscard]] bool IsConfirmInputPressed();

    [[nodiscard]] bool IsConfirmInputReleased();

    [[nodiscard]] bool IsConfirmInputDown();

    [[nodiscard]] bool IsConfirmInputUp();

    // only enter confirm
    [[nodiscard]] bool IsOnlyEnterConfirmInputPressed();

    [[nodiscard]] bool IsOnlyEnterConfirmInputReleased();

    [[nodiscard]] bool IsOnlyEnterConfirmInputDown();

    [[nodiscard]] bool IsOnlyEnterConfirmInputUp();

    // back input
    [[nodiscard]] bool IsBackInputPressed();

    [[nodiscard]] bool IsBackInputReleased();

    [[nodiscard]] bool IsBackInputDown();

    [[nodiscard]] bool IsBackInputUp();

    // other
    [[nodiscard]] bool IsToggleFullscreenInput();

    [[nodiscard]] bool IsSkipInput();

    [[nodiscard]] bool IsQuitInput();
} // namespace hlp
