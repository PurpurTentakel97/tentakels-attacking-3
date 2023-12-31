add_library(ui_lib STATIC
            include/ui_lib/Alignment.hpp
            include/ui_lib/Button.hpp
            include/ui_lib/CheckBox.hpp
            include/ui_lib/ButtonClassic.hpp
            include/ui_lib/ColorPicker.hpp
            include/ui_lib/ColorPickerCell.hpp
            include/ui_lib/CountingNumber.hpp
            include/ui_lib/DropDown.hpp
            include/ui_lib/DropDownElement.hpp
            include/ui_lib/ButtonExpanding.hpp
            include/ui_lib/Focus.hpp
            include/ui_lib/Focusable.hpp
            include/ui_lib/Hover.hpp
            include/ui_lib/HoverRender.hpp
            include/ui_lib/Line.hpp
            include/ui_lib/LineDrag.hpp
            include/ui_lib/Picture.hpp
            include/ui_lib/PopUp.hpp
            include/ui_lib/Scene.hpp
            include/ui_lib/SceneType.hpp
            include/ui_lib/ShipCountRing.hpp
            include/ui_lib/Slider.hpp
            include/ui_lib/ButtonSlider.hpp
            include/ui_lib/Table.hpp
            include/ui_lib/TableCell.hpp
            include/ui_lib/Text.hpp
            include/ui_lib/Title.hpp
            include/ui_lib/ButtonToggle.hpp
            include/ui_lib/UIElement.hpp
            include/ui_lib/InputLine.hpp
            Alignment.cpp
            Button.cpp
            CheckBox.cpp
            ButtonClassic.cpp
            ColorPicker.cpp
            ColorPickerCell.cpp
            CountingNumber.cpp
            DropDown.cpp
            DropDownElement.cpp
            ButtonExpanding.cpp
            Focus.cpp
            Focusable.cpp
            Hover.cpp
            HoverRender.cpp
            Line.cpp
            LineDrag.cpp
            Picture.cpp
            PopUp.cpp
            Scene.cpp
            SceneType.cpp
            ShipCountRing.cpp
            Slider.cpp
            ButtonSlider.cpp
            Table.cpp
            Text.cpp
            Title.cpp
            ButtonToggle.cpp
            InputLine.cpp
            TableCell.cpp
)

target_include_directories(ui_lib
                           PRIVATE include/ui_lib
                           INTERFACE include
)

target_link_libraries(ui_lib
                      PRIVATE
                      project_options
                      PUBLIC
                      alias
                      app
                      custom_raylib
                      event
                      helper
                      utils
)