//
// Purpur Tentakel
// 28.12.2023
//

#pragma once

#include <CustomRaylib.hpp>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace utl {
    using usize                = std::size_t;
    using input_variant_col_ty = std::variant<utl::usize, double, std::string, Color>;
    using input_variant_ty     = std::variant<utl::usize, double, std::string>;

    template<typename T>
    struct Vec2;
    using vec2pos_ty       = Vec2<int>;
    using vec2pos_ty_ref   = Vec2<int>&;
    using vec2pos_ty_c     = Vec2<int> const;
    using vec2pos_ty_ref_c = Vec2<int> const&;

    class ResultUpdate;
    struct ResultFleet;

    class ResultEvent;
    class ResultEventPirates;
    class ResultEventRevolts;
    class ResultEventRenegadeShips;
    class ResultEventEngineProblem;
    class ResultEventSupernova;

    enum class FleetInstructionType;

    struct RepresentationFleet;
    struct RepresentationTargetPoint;
    struct RepresentationPlanet;
    struct RepresentationGalaxy;
} // namespace utl
