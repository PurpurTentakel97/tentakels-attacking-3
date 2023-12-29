//
// Purpur Tentakel
// 28.12.2023
//

// namespace to come

#pragma once

#include <memory>

class GameEventSettings;
class SliderAndInputLine;
enum class SliderType;
class UIManager;
class GalaxyScene;
class PlanetTable;
class FleetAndTargetPointTable;

class UIGalaxy;
using UIGalaxy_ty = std::shared_ptr<UIGalaxy>;
using UIGalaxy_ty_c = std::shared_ptr<UIGalaxy> const&;

class UIGalaxyElement;
using UIGalaxyElement_ty = std::shared_ptr<UIGalaxyElement>;
using UIGalaxyElement_ty_c = std::shared_ptr<UIGalaxyElement> const&;

class UIPlanet;
using UIPlanet_ty = std::shared_ptr<UIPlanet>;
using UIPlanet_ty_c = std::shared_ptr<UIPlanet> const&;

class UITargetPoint;
using UITargetPoint_ty = std::shared_ptr<UITargetPoint>;
using UITargetPoint_ty_c = std::shared_ptr<UITargetPoint> const&;
