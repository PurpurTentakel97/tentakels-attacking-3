//
// Purpur Tentakel
// 28.12.2023
//


#pragma once

#include <memory>
#include <string>

namespace uil {
    class Scene;
    enum class SceneType;

    enum class Alignment;
    enum class TextAlignment;

    class PopUp;

    class ClassicButton;
    using ClassicButton_ty   = std::shared_ptr<ClassicButton>;
    using ClassicButton_ty_c = std::shared_ptr<ClassicButton> const&;

    class SliderButton;
    using SliderButton_ty   = std::shared_ptr<SliderButton>;
    using SliderButton_ty_c = std::shared_ptr<SliderButton> const&;

    class ToggleButton;
    using ToggleButton_ty   = std::shared_ptr<ToggleButton>;
    using ToggleButton_ty_c = std::shared_ptr<ToggleButton> const&;

    class ColorPicker;
    using ColorPicker_ty   = std::shared_ptr<ColorPicker>;
    using ColorPicker_ty_c = std::shared_ptr<ColorPicker> const&;

    class ColorPickerCell;
    using ColorPickerCell_ty   = std::shared_ptr<ColorPickerCell>;
    using ColorPickerCell_ty_c = std::shared_ptr<ColorPickerCell> const&;

    class Arrow;
    using Arrow_ty   = std::shared_ptr<Arrow>;
    using Arrow_ty_c = std::shared_ptr<Arrow> const&;

    class CheckBox;
    using CheckBox_ty   = std::shared_ptr<CheckBox>;
    using CheckBox_ty_c = std::shared_ptr<CheckBox> const&;

    class Hover;
    using Hover_ty   = std::shared_ptr<Hover>;
    using Hover_ty_c = std::shared_ptr<Hover> const&;

    class InputLine;
    using InputLine_ty   = std::shared_ptr<InputLine>;
    using InputLine_ty_c = std::shared_ptr<InputLine> const&;

    class Line;
    using Line_ty   = std::shared_ptr<Line>;
    using Line_ty_c = std::shared_ptr<Line> const&;

    class LineDrag;
    using LineDrag_ty   = std::shared_ptr<LineDrag>;
    using LineDrag_ty_c = std::shared_ptr<LineDrag> const&;

    class Picture;
    using Picture_ty   = std::shared_ptr<Picture>;
    using Picture_ty_c = std::shared_ptr<Picture> const&;

    class Slider;
    using Slider_ty   = std::shared_ptr<Slider>;
    using Slider_ty_c = std::shared_ptr<Slider> const&;

    class Text;
    using Text_ty   = std::shared_ptr<Text>;
    using Text_ty_c = std::shared_ptr<Text> const&;

    class CountingNumber;
    using CountingNumber_ty   = std::shared_ptr<CountingNumber>;
    using CountingNumber_ty_c = std::shared_ptr<CountingNumber> const&;

    class Title;
    using Title_ty   = std::shared_ptr<Title>;
    using Title_ty_c = std::shared_ptr<Title> const&;

    class DropDown;
    using DropDown_ty   = std::shared_ptr<DropDown>;
    using DropDown_ty_c = std::shared_ptr<DropDown> const&;

    class DropDownElement;
    using DropDownElement_ty   = std::shared_ptr<DropDownElement>;
    using DropDownElement_ty_c = std::shared_ptr<DropDownElement> const&;

    class CountRing;
    using CountRing_ty   = std::shared_ptr<CountRing>;
    using CountRing_ty_c = std::shared_ptr<CountRing> const&;

    class TableCell;
    using TableCell_ty   = std::shared_ptr<TableCell>;
    using TableCell_ty_c = std::shared_ptr<TableCell> const&;

    class Table;
    using Table_ty   = std::shared_ptr<Table>;
    using Table_ty_c = std::shared_ptr<Table> const&;

    class NewTable;
    using NewTable_ty   = std::shared_ptr<NewTable>;
    using NewTable_ty_c = std::shared_ptr<NewTable> const&;

    class Focusable;
    using Focusable_ty_raw = Focusable*;
} // namespace uil
