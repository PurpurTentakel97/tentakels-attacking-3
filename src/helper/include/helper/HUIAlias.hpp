//
// Purpur Tentakel
// 26.05.2023
//

#pragma once
#include <memory>
#include <string>

struct AppContext;
using AppContext_ty =   AppContext&;
using AppContext_ty_c = AppContext const&;

struct Vector2;
using Resolution_ty   = Vector2&;
using Resolution_ty_c = Vector2 const&;

struct CWindow;
using Window_ty   = CWindow&;
using Window_ty_c = CWindow const&;

// Elements
// Button
class ClassicButton;
using ClassicButton_ty =   std::shared_ptr<ClassicButton>;
using ClassicButton_ty_c = std::shared_ptr<ClassicButton> const&;

class SliderButton;
using SliderButton_ty =   std::shared_ptr<SliderButton>;
using SliderButton_ty_c = std::shared_ptr<SliderButton> const&;

class ToggleButton;
using ToggleButton_ty =   std::shared_ptr<ToggleButton>;
using ToggleButton_ty_c = std::shared_ptr<ToggleButton> const&;

// Color Picker
class ColorPicker;
using ColorPicker_ty =   std::shared_ptr<ColorPicker>;
using ColorPicker_ty_c = std::shared_ptr<ColorPicker> const&;

class ColorPickerCell;
using ColorPickerCell_ty =   std::shared_ptr<ColorPickerCell>;
using ColorPickerCell_ty_c = std::shared_ptr<ColorPickerCell> const&;
// Default
class Arrow;
using Arrow_ty =   std::shared_ptr<Arrow>;
using Arrow_ty_c = std::shared_ptr<Arrow> const&;

class CheckBox;
using CheckBox_ty =   std::shared_ptr<CheckBox>;
using CheckBox_ty_c = std::shared_ptr<CheckBox> const&;

class Hover;
using Hover_ty =   std::shared_ptr<Hover>;
using Hover_ty_c = std::shared_ptr<Hover> const&;

template <typename T>
class InputLine;
using InputLine_int_ty =      std::shared_ptr<InputLine<int>>;
using InputLine_int_ty_c =    std::shared_ptr<InputLine<int>> const&;
using InputLine_float_ty =    std::shared_ptr<InputLine<float>>;
using InputLine_float_ty_c =  std::shared_ptr<InputLine<float>> const&;
using InputLine_double_ty =   std::shared_ptr<InputLine<double>>;
using InputLine_double_ty_c = std::shared_ptr<InputLine<double>> const&;
using InputLine_str_ty =      std::shared_ptr<InputLine<std::string>>;
using InputLine_str_ty_c =    std::shared_ptr<InputLine<std::string>> const&;

class Line;
using Line_ty =   std::shared_ptr<Line>;
using Line_ty_c = std::shared_ptr<Line> const&;

class LineDrag;
using LineDrag_ty =   std::shared_ptr<LineDrag>;
using LineDrag_ty_c = std::shared_ptr<LineDrag> const&;

class Picture;
using Picture_ty =   std::shared_ptr<Picture>;
using Picture_ty_c = std::shared_ptr<Picture> const&;

class Slider;
using Slider_ty =   std::shared_ptr<Slider>;
using Slider_ty_c = std::shared_ptr<Slider> const&;

class Text;
using Text_ty =   std::shared_ptr<Text>;
using Text_ty_c = std::shared_ptr<Text> const&;

class CountingNumber;
using CountingNumber_ty =   std::shared_ptr<CountingNumber>;
using CountingNumber_ty_c = std::shared_ptr<CountingNumber> const&;

class Title;
using Title_ty =   std::shared_ptr<Title>;
using Title_ty_c = std::shared_ptr<Title> const&;

// DropDown
class DropDown;
using DropDown_ty =   std::shared_ptr<DropDown>;
using DropDown_ty_c = std::shared_ptr<DropDown> const&;

class DropDownElement;
using DropDownElement_ty =   std::shared_ptr<DropDownElement>;
using DropDownElement_ty_c = std::shared_ptr<DropDownElement> const&;

// Galaxy
class UIGalaxy;
using UIGalaxy_ty =   std::shared_ptr<UIGalaxy>;
using UIGalaxy_ty_c = std::shared_ptr<UIGalaxy> const&;

class UIGalaxyElement;
using UIGalaxyElement_ty =   std::shared_ptr<UIGalaxyElement>;
using UIGalaxyElement_ty_c = std::shared_ptr<UIGalaxyElement> const&;

class UIPlanet;
using UIPlanet_ty =   std::shared_ptr<UIPlanet>;
using UIPlanet_ty_c = std::shared_ptr<UIPlanet> const&;

class UITargetPoint;
using UITargetPoint_ty =   std::shared_ptr<UITargetPoint>;
using UITargetPoint_ty_c = std::shared_ptr<UITargetPoint> const&;

class UIFleet;
using UIFleet_ty =   std::shared_ptr<UIFleet>;
using UIFleet_ty_c = std::shared_ptr<UIFleet> const&;

class CountRing;
using CountRing_ty   = std::shared_ptr<CountRing>;
using CountRing_ty_c = std::shared_ptr<CountRing> const&;

// Table
class AbstractTableCell;
using AbstractTableCell_ty =   std::shared_ptr<AbstractTableCell>;
using AbstractTableCell_ty_c = std::shared_ptr<AbstractTableCell> const&;

class Table;
using Table_ty =   std::shared_ptr<Table>;
using Table_ty_c = std::shared_ptr<Table> const&;


// public
// Focusable
class Focusable;
using Focusable_ty_raw = Focusable*;
