//
// Purpur Tentakel
// 06.03.2024
// This is a generated file. Do not edit this file.
//

#pragma once

#include <alias/AliasUtils.hpp>

namespace app {
     struct AppContext;
}

namespace cst {
    class G_Player final {
    public:
        friend struct G_Config_IO;
        friend struct app::AppContext;

    private:
        static inline utl::usize constexpr s_total_config_entry_count = 5;
        static inline utl::usize constexpr s_load_config_entry_count = 3;
        utl::usize m_min_count = 2;
        utl::usize m_max_count = 7;
        bool m_is_shuffle = false;

    public:
        [[nodiscard]] utl::usize get_total_config_entry_count() const {
            return s_total_config_entry_count;
        }
        [[nodiscard]] utl::usize get_load_config_entry_count() const {
            return s_load_config_entry_count;
        }
        [[nodiscard]] utl::usize get_min_count() const {
            return m_min_count;
        }
        [[nodiscard]] utl::usize get_max_count() const {
            return m_max_count;
        }
        [[nodiscard]] bool get_is_shuffle() const {
            return m_is_shuffle;
        }

         void set_min_count(utl::usize const value) {
            m_min_count = value;
        }
         void set_max_count(utl::usize const value) {
            m_max_count = value;
        }
         void set_is_shuffle(bool const value) {
            m_is_shuffle = value;
        }
    };

} // namespace cst
