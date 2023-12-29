//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "EventMain.hpp"
#include <CustomRaylib.hpp>
#include <app/SoundType.hpp>
#include <functional>
#include <helper/HLogicAlias.hpp>
#include <helper/HUIAlias.hpp>
#include <helper/HVec2.hpp>
#include <string>
#include <utils/FightResult.hpp>

class Focusable;
class PopUp;
class Hover;
enum class SceneType;
enum class Resolution;

namespace eve {
    class CloseWindowEvent final : public Event { };

    class SetTargetFPSEvent final : public Event {
    private:
        size_t m_fps;

    public:
        explicit SetTargetFPSEvent(size_t const fps) : m_fps{ fps } { }

        [[nodiscard]] size_t GetFPS() const {
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
        Resolution m_resolution;

    public:
        explicit SetNewResolutionEvent(Resolution const resolution) : m_resolution{ resolution } { }

        [[nodiscard]] Resolution GetResolution() const {
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
        Hover* m_hover;

    public:
        explicit RenderHoverEvent(Hover* const hover) : m_hover{ hover } { }

        [[nodiscard]] Hover* GetHover() const {
            return m_hover;
        }
    };

    class FocusEvent : public Event {
    protected:
        Focusable_ty_raw m_focusable;

    public:
        explicit FocusEvent(Focusable_ty_raw focusable) : m_focusable{ focusable } { }

        [[nodiscard]] Focusable_ty_raw GetFocusable() const {
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
        SceneType m_sceneType;

    public:
        explicit SwitchSceneEvent(SceneType const sceneType) : m_sceneType{ sceneType } { }

        [[nodiscard]] SceneType GetSceneType() const {
            return m_sceneType;
        }
    };

    class ClosePopUpEvent final : public Event {
    private:
        PopUp* m_popUp;

    public:
        explicit ClosePopUpEvent(PopUp* const popUp) : m_popUp{ popUp } { }

        [[nodiscard]] PopUp* GetPop() const {
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

    class ShowDeletePlayerPopUpEvent final : public PopUpEvent {
        std::function<void(unsigned int)> m_onClick;

    public:
        ShowDeletePlayerPopUpEvent(std::string title, std::string subTitle, std::function<void(unsigned int)> onClick)
            : PopUpEvent{ std::move(title), std::move(subTitle) },
              m_onClick{ std::move(onClick) } { }

        [[nodiscard]] std::function<void(unsigned int)> GetOnClick() const {
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

    class ShowFightResultEvent final : public Event {
    private:
        utl::FightResult m_result;
        using callback_ty = std::function<void()>;
        callback_ty m_callback{ []() {} };

    public:
        ShowFightResultEvent(utl::FightResult result, callback_ty callback)
            : m_result{ std::move(result) },
              m_callback{ std::move(callback) } { }

        [[nodiscard]] utl::FightResult GetResult() const {
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
        unsigned int m_originID;
        unsigned int m_destID;
        vec2pos_ty m_destCoordinates;

    public:
        DragLineFleetInstructionEvent(
                unsigned int const originID,
                unsigned int const destID,
                vec2pos_ty destCoordinates
        )
            : m_originID{ originID },
              m_destID{ destID },
              m_destCoordinates{ std::move(destCoordinates) } { }

        [[nodiscard]] unsigned int GetOriginID() const {
            return m_originID;
        }
        [[nodiscard]] unsigned int GetDestID() const {
            return m_destID;
        }
        [[nodiscard]] vec2pos_ty GetDestCoordinates() const {
            return m_destCoordinates;
        }
    };

    class RefreshNewGamePlayerScene final : public Event { };
} // namespace eve
