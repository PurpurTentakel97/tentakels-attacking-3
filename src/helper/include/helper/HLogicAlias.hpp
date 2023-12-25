//
// Purpur Tentakel
// 26.05.2023
//

#pragma once
#include <vector>
#include <memory>

struct AppContext;
using AppContext_ty = AppContext&;
using AppContext_ty_c = AppContext const&;

template<typename T>
struct Vec2;
using vec2pos_ty = Vec2<int>;
using vec2pos_ty_ref = Vec2<int>&;
using vec2pos_ty_c = Vec2<int> const;
using vec2pos_ty_ref_c = Vec2<int> const&;

class SpaceObject;
using SpaceObject_ty = std::shared_ptr<SpaceObject>;
using SpaceObject_ty_c = std::shared_ptr<SpaceObject> const&;
using SpaceObject_ty_raw = SpaceObject const*;
using SpaceObject_ty_raw_c = SpaceObject const* const;

class Galaxy;
using Galaxy_ty = std::shared_ptr<Galaxy>;
using Galaxy_ty_c = Galaxy_ty const&;
using Galaxy_ty_c_raw = Galaxy const* const;
using Galaxy_ty_raw = Galaxy const*;

class Fleet;
using Fleet_ty = std::shared_ptr<Fleet>;
using Fleet_ty_c = std::shared_ptr<Fleet> const&;
using Fleet_ty_raw = Fleet const*;
using Fleet_ty_raw_c = Fleet const* const;

class Planet;
using Planet_ty = std::shared_ptr<Planet>;
using Planet_ty_c = std::shared_ptr<Planet> const&;
using Planet_ty_raw = Planet const*;
using Planet_ty_raw_c = Planet const* const;

class TargetPoint;
using TargetPoint_ty = std::shared_ptr<TargetPoint>;
using TargetPoint_ty_c = std::shared_ptr<TargetPoint> const&;
using TargetPoint_ty_raw = TargetPoint const*;
using TargetPoint_ty_raw_c = TargetPoint const* const;

class Player;
using Player_ty = std::shared_ptr<Player>;
using Player_ty_c = Player_ty const&;
using Player_ty_raw = Player const*;
using Player_ty_raw_c = Player const* const;

struct HMergeResult;
struct HFightResult;
using UpdateResult_ty = std::pair<std::vector<HMergeResult>, std::vector<HFightResult>>;
