//
// Purpur Tentakel
// 24.10.2022
//

#pragma once

/**
 * returns if enter, num enter or space is pressed.
 */
[[nodiscard]] bool IsConfirmInputPressed();
/**
 * returns if enter, num enter or space is released.
 */
[[nodiscard]] bool IsConfirmInputReleased();
/**
 * returns if enter, num enter or space is down.
 */
[[nodiscard]] bool IsConfirmInputDown();
/**
 * returns if enter, num enter or space is up.
 */
[[nodiscard]] bool IsConfirmInputUp();

/**
 * returns if enter or num enter is pressed.
 */
[[nodiscard]] bool IsOnlyEnterConfirmInputPressed();
/**
 * returns if enter or num enter is released.
 */
[[nodiscard]] bool IsOnlyEnterConfirmInputReleased();
/**
 * returns if enter or num enter is down.
 */
[[nodiscard]] bool IsOnlyEnterConfirmInputDown();
/**
 * returns if enter or num enter is up.
 */
[[nodiscard]] bool IsOnlyEnterConfirmInputUp();

/**
 * returns if escape or num enter is pressed.
 */
[[nodiscard]] bool IsBackInputPressed();
/**
 * returns if escape or num enter is released.
 */
[[nodiscard]] bool IsBackInputReleased();
/**
 * returns if escape or num enter is down.
 */
[[nodiscard]] bool IsBackInputDown();
/**
 * returns if escape or num enter is up.
 */
[[nodiscard]] bool IsBackInputUp();

/**
 * returns if F11 or alt and enter is pressed.
 */
[[nodiscard]] bool IsToggleFullscreenInput();

/**
 * returns if alt is pressed.
 */
[[nodiscard]] bool IsSkipInput();

/**
 * returns if alt and F4 is pressed.
 */
[[nodiscard]] bool IsQuitInput();
