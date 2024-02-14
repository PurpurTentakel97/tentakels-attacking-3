//
// Purpur Tentakel
// 25.08.2022
//

#pragma once

#include "EventMain.hpp"
#include <CustomRaylib.hpp>
#include <alias/AliasApp.hpp>
#include <alias/AliasConstants.hpp>
#include <alias/AliasUiLib.hpp>
#include <alias/AliasUtils.hpp>
#include <functional>
#include <string>
#include <utils/ResultFight.hpp>
#include <utils/Vec2.hpp>

namespace eve {
    class CloseWindowEvent final : public Event { };

    class SetTargetFPSEvent final : public Event {
    private:
        utl::usize m_fps;

    public:
        explicit SetTargetFPSEvent(utl::usize const fps) : m_fps{ fps } { }

        [[nodiscard]] utl::usize GetFPS() const {
            return m_fps;
        }
    };

    class ToggleFullscreenEvent final : public Event {
    private:
        bool m_isNextFullscreen;

    public:
        explicit ToggleFullscreenEvent(bool const isNextFullscreen) : m_isNextFullscreen{ isNextFullscreen } { }

        [[nodiscard]] bool IsNextFullscreen() const {
            return m_isNextFullscreen;
        }
    };

    class SetNewResolutionEvent final : public Event {
    private:
        cst::Resolution m_resolution;

    public:
        explicit SetNewResolutionEvent(cst::Resolution const resolution) : m_resolution{ resolution } { }

        [[nodiscard]] cst::Resolution GetResolution() const {
            return m_resolution;
        }
    };

    class PlaySoundEvent final : public Event {
    private:
        app::SoundType m_soundType;

    public:
        explicit PlaySoundEvent(app::SoundType const soundType) : m_soundType{ soundType } { }
        [[nodiscard]] app::SoundType GetSoundType() const {
            return m_soundType;
        }
    };

    class SetMasterVolumeEvent final : public Event {
    private:
        float m_level;

    public:
        explicit SetMasterVolumeEvent(float const level) : m_level{ level } {};

        [[nodiscard]] float GetLevel() const {
            return m_level;
        }
    };

    class MuteMasterVolumeEvent final : public Event {
    private:
        bool m_mute;

    public:
        explicit MuteMasterVolumeEvent(bool const mute) : m_mute{ mute } { }

        [[nodiscard]] bool GetMute() const {
            return m_mute;
        }
    };

    class RenderHoverEvent final : public Event {
    private:
        uil::Hover* m_hover;

    public:
        explicit RenderHoverEvent(uil::Hover* const hover) : m_hover{ hover } { }

        [[nodiscard]] uil::Hover* GetHover() const {
            return m_hover;
        }
    };

    class FocusEvent : public Event {
    protected:
        uil::Focusable_ty_raw m_focusable;

    public:
        explicit FocusEvent(uil::Focusable_ty_raw focusable) : m_focusable{ focusable } { }

        [[nodiscard]] uil::Focusable_ty_raw GetFocusable() const {
            return m_focusable;
        }
    };

    class RenderFocusEvent final : public Event {
    private:
        bool m_render;

    public:
        explicit RenderFocusEvent(bool const render) : m_render{ render } { }

        [[nodiscard]] bool GetRender() const noexcept {
            return m_render;
        }
    };

    class NewFocusElementEvent final : public FocusEvent {
    public:
        using FocusEvent::FocusEvent;
    };

    class NewFocusPopUpElementEvent final : public FocusEvent {
    public:
        using FocusEvent::FocusEvent;
    };

    class DeleteFocusElementEvent final : public FocusEvent {
    public:
        using FocusEvent::FocusEvent;
    };

    class DeleteFocusPopUpElementEvent final : public FocusEvent {
    public:
        using FocusEvent::FocusEvent;
    };

    class SelectFocusElementEvent final : public FocusEvent {
    public:
        using FocusEvent::FocusEvent;
    };

    class SelectFocusPopUpElementEvent final : public FocusEvent {
    public:
        using FocusEvent::FocusEvent;
    };

    class SelectNextFocusElementEvent final : public Event { };

    class NewFocusPopUpLayerEvent final : public Event { };

    class NewFocusLayerEvent final : public Event { };

    class DeleteFocusPopUpLayerEvent final : public Event { };

    class DeleteFocusLayerEvent final : public Event { };

    class ClearFocusEvent final : public Event { };


    class SwitchSceneEvent final : public Event {
    private:
        uil::SceneType m_sceneType;

    public:
        explicit SwitchSceneEvent(uil::SceneType const sceneType) : m_sceneType{ sceneType } { }

        [[nodiscard]] uil::SceneType GetSceneType() const {
            return m_sceneType;
        }
    };

    class SwitchMainSceneEvent final : public Event { };

    class ClosePopUpEvent final : public Event {
    private:
        uil::PopUp* m_popUp;

    public:
        explicit ClosePopUpEvent(uil::PopUp* const popUp) : m_popUp{ popUp } { }

        [[nodiscard]] uil::PopUp* GetPop() const {
            return m_popUp;
        }
    };

    class PopUpEvent : public Event {
    private:
        std::string m_title;
        std::string m_subTitle;

    public:
        PopUpEvent(std::string title, std::string subTitle)
            : m_title{ std::move(title) },
              m_subTitle{ std::move(subTitle) } { }

        [[nodiscard]] std::string const& GetTitle() const {
            return m_title;
        }
        [[nodiscard]] std::string const& GetSubTitle() const {
            return m_subTitle;
        }
    };

    class ShowMessagePopUpEvent final : public PopUpEvent {
    private:
        std::function<void()> m_callback;

    public:
        ShowMessagePopUpEvent(std::string title, std::string subTitle, std::function<void()> callback)
            : PopUpEvent{ std::move(title), std::move(subTitle) },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] std::function<void()> GetCallback() const {
            return m_callback;
        }
    };

    class ShowStringPopupEvent final : public PopUpEvent {
    public:
        using callback_ty = std::function<void(std::string)>;

    private:
        std::string m_value;
        callback_ty m_callback;

    public:
        ShowStringPopupEvent(std::string const& title, std::string value, callback_ty callback)
            : PopUpEvent{ title, "" },
              m_value{ std::move(value) },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] std::string Value() const {
            return m_value;
        }

        [[nodiscard]] callback_ty Callback() const {
            return m_callback;
        }
    };

    class ShowUSizePopupEvent final : public PopUpEvent {
    public:
        using callback_ty = std::function<void(utl::usize)>;

    private:
        utl::usize m_value;
        callback_ty m_callback;

    public:
        ShowUSizePopupEvent(std::string const& title, utl::usize value, callback_ty callback)
            : PopUpEvent{ title, "" },
              m_value{ value },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] utl::usize Value() const {
            return m_value;
        }

        [[nodiscard]] callback_ty Callback() const {
            return m_callback;
        }
    };

    class ShowDoublePopupEvent final : public PopUpEvent {
    public:
        using callback_ty = std::function<void(double)>;

    private:
        double m_value;
        callback_ty m_callback;

    public:
        ShowDoublePopupEvent(std::string const& title, double value, callback_ty callback)
            : PopUpEvent{ title, "" },
              m_value{ value },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] double Value() const {
            return m_value;
        }

        [[nodiscard]] callback_ty Callback() const {
            return m_callback;
        }
    };

    class ShowColorPopupEvent final : public PopUpEvent {
    public:
        using callback_ty = std::function<void(Color)>;

    private:
        Color m_value;
        callback_ty m_callback;

    public:
        ShowColorPopupEvent(std::string const& title, Color value, callback_ty callback)
            : PopUpEvent{ title, "" },
              m_value{ std::move(value) },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] Color Value() const {
            return m_value;
        }

        [[nodiscard]] callback_ty Callback() const {
            return m_callback;
        }
    };

    template<typename T>
    class ShowCellPopUpEvent final : public PopUpEvent {
    private:
        T m_currentValue{};
        std::function<void(T)> m_onClick;

    public:
        ShowCellPopUpEvent(std::string const& title, T const currentValue, std::function<void(T)> const onClick)
            : PopUpEvent{ title, "" },
              m_currentValue{ currentValue },
              m_onClick{ onClick } { }

        [[nodiscard]] T GetCurrentValue() const {
            return m_currentValue;
        }
        [[nodiscard]] std::function<void(T)> GetOnClick() const {
            return m_onClick;
        }
    };

    class ShowValidatePopUp final : public PopUpEvent {
    private:
        std::function<void(bool)> m_callback;

    public:
        ShowValidatePopUp(std::string title, std::string subTitle, std::function<void(bool)> callback)
            : PopUpEvent{ std::move(title), std::move(subTitle) },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] std::function<void(bool)> GetCallback() const {
            return m_callback;
        }
    };

    class ShowInitialSoundLevelPopUpEvent final : public PopUpEvent {
    public:
        using PopUpEvent::PopUpEvent;
    };

    class ShowEventResultPopUp final : public PopUpEvent{
    private:
        std::function<void()> m_callback;

    public:
        ShowEventResultPopUp(std::string title, std::string subTitle, std::function<void()> callback)
                : PopUpEvent{ std::move(title), std::move(subTitle) },
                  m_callback{ std::move(callback) } { }

        [[nodiscard]] std::function<void()> GetCallback() const {
            return m_callback;
        }
    };

    class ShowFightResultEvent final : public Event {
    private:
        utl::ResultFight m_result;
        using callback_ty = std::function<void()>;
        callback_ty m_callback{ []() {} };

    public:
        ShowFightResultEvent(utl::ResultFight result, callback_ty callback)
            : m_result{ std::move(result) },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] utl::ResultFight GetResult() const {
            return m_result;
        }
        [[nodiscard]] callback_ty GetCallback() const {
            return m_callback;
        }
    };

    class ChangeLanguageEvent final : public Event {
    private:
        std::string m_language;

    public:
        explicit ChangeLanguageEvent(std::string language) : m_language{ std::move(language) } { }

        [[nodiscard]] std::string GetLanguage() const {
            return m_language;
        }
    };

    class UpdateLanguageInUIEvent final : public Event {
    private:
        std::string m_language;

    public:
        explicit UpdateLanguageInUIEvent(std::string language) : m_language{ std::move(language) } { }

        [[nodiscard]] std::string GetLanguage() const {
            return m_language;
        }
    };

    class DragLineFleetInstructionEvent final : public Event {
    private:
        utl::usize m_originID;
        utl::usize m_destID;
        utl::vec2pos_ty m_destCoordinates;

    public:
        DragLineFleetInstructionEvent(utl::usize const originID,
                                      utl::usize const destID,
                                      utl::vec2pos_ty destCoordinates)
            : m_originID{ originID },
              m_destID{ destID },
              m_destCoordinates{ destCoordinates } { }

        [[nodiscard]] utl::usize GetOriginID() const {
            return m_originID;
        }
        [[nodiscard]] utl::usize GetDestID() const {
            return m_destID;
        }
        [[nodiscard]] utl::vec2pos_ty GetDestCoordinates() const {
            return m_destCoordinates;
        }
    };

    class RefreshNewGamePlayerScene final : public Event { };
} // namespace eve
