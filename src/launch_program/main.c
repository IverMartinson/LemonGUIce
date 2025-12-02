#include "../headers/lemonguice.h"

int main(){
    LG_init(); // init

    LG_font_face* font_face = LG_new_font_face("fonts/times_new_roman.ttf");
    LG_font_style* font_style = LG_new_font_style();

    font_style->font_color = 0xFFFFFFFF;
    font_style->font_face = font_face;
    font_style->font_size = 20;


    LG_widget* root_panel = LG_new_window("LemonGUIce", 800, 800); // create new SDL window, return the root panel 

    // LG_add_child_panel(root_panel, new_panel); // maybe?
/*
    LG_widget* left_panel = LG_new_child_panel(root_panel);
    LG_widget* right_panel = LG_new_child_panel(root_panel);

    LG_widget* button = LG_add_button_widget(left_panel);

    button->button_widget_data.text_data.font_style = font_style;

    LG_widget* text_1 = LG_add_text_widget(left_panel);

    text_1->text_widget_data.text_data.font_style = font_style;

    LG_widget* text_2 = LG_add_text_widget(left_panel);

    text_2->text_widget_data.text_data.font_style = font_style;

    LG_widget* image = LG_add_image_widget(right_panel);

    image->image_widget_data.image = LG_load_image("images/test_image.bmp");
*/

    LG_context* context = LG_get_context();

    while (context->current_window_panel_count){
        LG_render_window(root_panel);
    }

    return 0;
}