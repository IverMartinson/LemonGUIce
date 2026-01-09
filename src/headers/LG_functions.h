#ifndef LG_FUNCTIONS_H
#define LG_FUNCTIONS_H

// functions

LG_font_face* LG_new_font_face(char* filename);

LG_font_style* LG_new_font_style();

LG_widget* LG_new_window(char* title, uint16_t width, uint16_t height);

LG_widget* LG_add_panel_widget(LG_widget* parent_widget);

LG_widget* LG_add_text_widget(LG_widget* parent_widget);

LG_widget* LG_add_button_widget(LG_widget* parent_widget);

LG_image* LG_load_image(char* filename);

int LG_render_window(LG_widget* window_widget);

int LG_init();

LG_context* LG_get_context();

#endif
