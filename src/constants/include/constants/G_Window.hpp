//
// Purpur Tentakel
// 16.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include "CResolution.hpp"
#include <alias/AliasUtils.hpp>
#include <utils/Vec2.hpp>

namespace app {
     struct AppContext;
}

namespace cst {
    class G_Window final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 5;
        static inline utl::usize constexpr s_load_config_entry_count = 3;
        Resolution m_current_resolution_enum = Resolution::LAST;
        bool m_is_full_screen = true;
        utl::usize m_fps = 60;

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] Resolution get_current_resolution_enum() const {
            return m_current_resolution_enum;
        }
        [[nodiscard]] bool get_is_full_screen() const {
            return m_is_full_screen;
        }
        [[nodiscard]] utl::usize get_fps() const {
            return m_fps;
        }

        void set_current_resolution_enum(Resolution const value) {
            m_current_resolution_enum = value;
        }
        void set_is_full_screen(bool const value) {
            m_is_full_screen = value;
        }
        void set_fps(utl::usize const value) {
            m_fps = value;
        }
    };

} // namespace cst
