//
// Purpur Tentakel
// 24.10.2022
//

#include "HInput.hpp"
#include <CustomRaylib.hpp>
#include <app/AppContext.hpp>

namespace hlp {
    bool IsConfirmInputPressed() {
        bool const triggered{ IsKeyPressed(KEY_SPACE) or IsKeyPressed(KEY_KP_ENTER)
                              or (IsKeyPressed(KEY_ENTER) and not IsSkipInput()
                                  and not app::AppContext::GetInstance().constants.acceptInputTriggered) };

        if (triggered) {
            app::AppContext::GetInstance().constants.acceptInputTriggered = true;
        }

        return triggered;
    }

    bool IsConfirmInputReleased() {
        bool const triggered{ IsKeyReleased(KEY_SPACE) or IsKeyReleased(KEY_KP_ENTER)
                              or (IsKeyReleased(KEY_ENTER) and !IsSkipInput()
                                  and !app::AppContext::GetInstance().constants.acceptInputTriggered) };

        if (triggered) {
            app::AppContext::GetInstance().constants.acceptInputTriggered = true;
        }

        return triggered;
    }

    bool IsConfirmInputDown() {
        return IsKeyDown(KEY_SPACE) or IsKeyDown(KEY_KP_ENTER) or (IsKeyDown(KEY_ENTER) and !IsSkipInput());
    }

    bool IsConfirmInputUp() {
        return IsKeyUp(KEY_KP_ENTER) or IsKeyUp(KEY_SPACE) or (IsKeyUp(KEY_ENTER) and !IsSkipInput());
    }

    bool IsOnlyEnterConfirmInputPressed() {
        bool const triggered{ IsKeyPressed(KEY_KP_ENTER)
                              or (IsKeyPressed(KEY_ENTER) and !IsSkipInput()
                                  and !app::AppContext::GetInstance().constants.acceptInputTriggered) };

        if (triggered) {
            app::AppContext::GetInstance().constants.acceptInputTriggered = true;
        }

        return triggered;
    }

    bool IsOnlyEnterConfirmInputReleased() {
        bool const triggered{ IsKeyReleased(KEY_KP_ENTER)
                              or (IsKeyReleased(KEY_ENTER) and !IsSkipInput()
                                  and !app::AppContext::GetInstance().constants.acceptInputTriggered) };

        if (triggered) {
            app::AppContext::GetInstance().constants.acceptInputTriggered = true;
        }

        return triggered;
    }

    bool IsOnlyEnterConfirmInputDown() {
        return IsKeyDown(KEY_KP_ENTER) or (IsKeyDown(KEY_ENTER) and !IsSkipInput());
    }

    bool IsOnlyEnterConfirmInputUp() {
        return IsKeyUp(KEY_KP_ENTER) or (IsKeyUp(KEY_ENTER) and !IsSkipInput());
    }

    bool IsBackInputPressed() {
        return IsKeyPressed(KEY_ESCAPE);
    }

    bool IsBackInputReleased() {
        return IsKeyReleased(KEY_ESCAPE);
    }

    bool IsBackInputDown() {
        return IsKeyDown(KEY_ESCAPE);
    }

    bool IsBackInputUp() {
        return IsKeyUp(KEY_ESCAPE);
    }

    bool IsToggleFullscreenInput() {
        return IsKeyPressed(KEY_F11) or ((IsKeyDown(KEY_LEFT_ALT) and (IsKeyPressed(KEY_ENTER))));
    }

    bool IsSkipInput() {
        return IsKeyDown(KEY_LEFT_ALT);
    }

    bool IsQuitInput() {
        return IsKeyDown(KEY_LEFT_ALT) and IsKeyDown(KEY_F4);
    }
} // namespace hlp
