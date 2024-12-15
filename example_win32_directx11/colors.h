#include "imgui.h"

// WIDGET COLORS

namespace c {

    ///////////////////////////////////////////// TABS

    inline ImVec4 tab_text_active = ImColor(255, 255, 255, 255);
    inline ImVec4 tab_text_hov = ImColor(98, 112, 122, 255);
    inline ImVec4 tab_text = ImColor(88, 92, 112, 255);

    inline ImVec4 tab_active = ImColor(88, 109, 202, 255);
    inline ImVec4 glow_active = ImColor(78, 99, 192, 230);

    ///////////////////////////////////////////// TEXT

    inline ImVec4 text_active = ImColor(255, 255, 255, 255);
    inline ImVec4 text_hov = ImColor(76, 75, 80, 255);
    inline ImVec4 text = ImColor(66, 65, 70, 255);

    ///////////////////////////////////////////// CHILD

    inline ImVec4 child_background = ImColor(22, 21, 26, 255);
    inline ImVec4 border_child = ImColor(28, 27, 32, 255);
    inline ImVec4 child_gradient = ImColor(75, 89, 153, 255);

    inline ImVec4 border_child_default = ImColor(22, 21, 26, 255);
    inline ImVec4 child_name = ImColor(62, 61, 65, 255);

    ///////////////////////////////////////////// GRADIENT

    inline ImVec4 checkbox_gradient_start = ImColor(72, 88, 171, 255);
    inline ImVec4 checkbox_gradient_end = ImColor(51, 60, 100, 255);

    ///////////////////////////////////////////// CHECKBOXES

    inline ImVec4 checkbox_bg = ImColor(17, 16, 21, 255);
    inline ImVec4 checkbox_mark = ImColor(255, 255, 255, 255);

    ///////////////////////////////////////////// SLIDERS

    inline ImVec4 slider_background = ImColor(17, 16, 21, 255);
    inline ImVec4 circle_push_gradient = ImColor(51, 49, 59, 255);
    inline ImVec4 circle_pop_gradient = ImColor(61, 60, 76, 255);

    ///////////////////////////////////////////// INPUTTEXT

    inline ImVec4 input_push_gradient = ImColor(27, 26, 31, 255);
    inline ImVec4 input_pop_gradient = ImColor(17, 16, 21, 255);


    ///////////////////////////////////////////// SCROLLBAR

    inline ImVec4 scroll_background = ImColor(15, 17, 20, 255);
    inline ImVec4 scroll_keep = ImColor(36, 35, 40, 255);

    ///////////////////////////////////////////// COMBOBOX

    inline ImVec4 combo_background = ImColor(28, 27, 32, 255);

    inline ImVec4 combo_push_gradient = ImColor(27, 26, 31, 255);
    inline ImVec4 combo_pop_gradient = ImColor(17, 16, 21, 255);

    ///////////////////////////////////////////// BUTTON

    inline ImVec4 button_push_gradient_active = ImColor(27, 26, 31, 255);
    inline ImVec4 button_pop_gradient_active = ImColor(17, 16, 21, 255);
                 
    inline ImVec4 button_push_gradient_hovered = ImColor(30, 29, 34, 255);
    inline ImVec4 button_pop_gradient_hovered = ImColor(19, 20, 24, 255);
                 
    inline ImVec4 button_push_gradient = ImColor(27, 26, 31, 255);
    inline ImVec4 button_pop_gradient = ImColor(17, 16, 21, 255);

    ///////////////////////////////////////////// KEYBIND

    inline ImVec4 keybind_background = ImColor(18, 18, 20, 255);
    inline ImVec4 keybind_border = ImColor(16, 16, 18, 255);

    ///////////////////////////////////////////// TAB VISIBLE

    inline ImVec4 tab_push_gradient = ImColor(79, 102, 209, 255);
    inline ImVec4 tab_pop_gradient = ImColor(50, 66, 138, 255);
}
