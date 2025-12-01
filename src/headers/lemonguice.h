#ifndef LEMON_GUICE_H
#define LEMON_GUICE_H

#include <stdlib.h>
#include <stdint.h>
#include "../headers/sourparse.h"

enum {
    LG_WIDGET_TYPE_PANEL = 0,
    LG_WIDGET_TYPE_TEXT = 1,
    LG_WIDGET_TYPE_BUTTON = 2,
    LG_WIDGET_TYPE_INPUT = 3,
    LG_WIDGET_TYPE_IMAGE = 4,
};

enum {
    LG_WIDGET_ALIGNMENT_LEFT = 0,
    LG_WIDGET_ALIGNMENT_CENTER_HORIZONTAL = 1,
    LG_WIDGET_ALIGNMENT_RIGHT = 2,
    LG_WIDGET_ALIGNMENT_UP = 3,
    LG_WIDGET_ALIGNMENT_CENTER_VERTICAL = 4,
    LG_WIDGET_ALIGNMENT_DOWN = 5,
};


typedef struct {
    uint32_t* image_data;
    int width;
    int height;
} LG_image;

typedef struct {
    SP_font* font;
} LG_font_face;

typedef struct {
    LG_font_face* font_face;
    uint32_t font_size;
    uint32_t font_color;
    uint8_t flags; // e.g., use defualt kerning or custom
    int32_t kerning;
    uint8_t font_alignment; // left, center, right, top, bottom, et cetera
} LG_font_style;

typedef struct {
    uint32_t background_color;
    
    uint32_t border_color;
    uint32_t border_size;
    uint32_t border_radius;
    
    int32_t width;
    int32_t height;
    
    uint8_t widget_alignment_horizontal;
    uint8_t widget_alignment_vertical;
    
    int32_t margin;
    int32_t margin_left;  // specific margin directions 
    int32_t margin_right; // should be -1 if auto
    int32_t margin_top;
    int32_t margin_bottom;
    
    int32_t padding;
    int32_t padding_left;  // specific margin directions 
    int32_t padding_right; // should be -1 if auto
    int32_t padding_top;
    int32_t padding_bottom;
} LG_widget_style;

typedef struct {
    char* text;
    LG_font_style* font_style;
} LG_text_data;

typedef struct {
    LG_image* image;
} LG_image_widget_data;

typedef struct {
    LG_text_data placeholder_text_data;
    LG_text_data input_text_data;
} LG_input_field_widget_data;

typedef struct {
    LG_text_data text_data;
} LG_button_widget_data;

typedef struct {
    LG_text_data text_data;
} LG_text_widget_data;

typedef struct {
    uint32_t type; // 0 panel, 1 text, 2 button, 3 input, 4 image
    uint32_t id;
    LG_image_widget_data image_widget_data;
    LG_input_field_widget_data input_field_widget_data;
    LG_button_widget_data button_widget_data;
    LG_text_widget_data text_widget_data;
    LG_widget_style* widget_style;
    LG_widget** children;
    uint32_t child_count;
    LG_widget* parent;
} LG_widget;

typedef struct {
    LG_font_face* default_font_face;    
    LG_font_style* default_font_style;
    LG_widget* default_widget;
    uint32_t current_id;
} LG_context;

// functions

LG_font_face* LG_new_font_face(char* filename);

LG_font_style* LG_new_font_style();

LG_widget* LG_new_window();

LG_widget* LG_add_panel_widget(LG_widget* parent_widget);

LG_widget* LG_add_text_widget(LG_widget* parent_widget);

LG_widget* LG_add_button_widget(LG_widget* parent_widget);

LG_image* LG_load_image(char* filename);

#endif // LEMON_GUICE_H