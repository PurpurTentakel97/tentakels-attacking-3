//
// Purpur Tentakel
// 28.12.2023
//

#pragma once

#include <utility>
#include <vector>

namespace utl {
    template<typename T>
    struct Vec2;
    using vec2pos_ty = Vec2<int>;
    using vec2pos_ty_ref = Vec2<int>&;
    using vec2pos_ty_c = Vec2<int> const;
    using vec2pos_ty_ref_c = Vec2<int> const&;

    struct MergeResult;
    struct FightResult;
    struct FleetResult;
    using UpdateResult_ty = std::pair<std::vector<utl::MergeResult>, std::vector<utl::FightResult>>;

} // namespace utl
