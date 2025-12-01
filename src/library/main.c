#include "headers/lemonguice.h"
#include "headers/sourparse.h"
#include "headers/pitmap.h"

LG_context context;

LG_font_face* LG_new_font_face(char* filename){
    LG_font_face* font_face = malloc(sizeof(LG_font_face));
    
    font_face->font = SP_load_font(filename);

    return font_face;
}

LG_font_style* LG_new_font_style(){
    LG_font_style* font_style = malloc(sizeof(LG_new_font_style));

    *font_style = *context.default_font_style;

    return font_style;
}

LG_widget* LG_new_window(){
    LG_widget* widget = malloc(sizeof(LG_widget));

    *widget = *context.default_widget;

    widget->id = context.current_id++;
    widget->children = NULL;
    widget->parent = NULL;
    widget->type = LG_WIDGET_TYPE_PANEL;

    return widget;
}

LG_widget* LG_add_widget(LG_widget* parent_widget){
    LG_widget* widget = malloc(sizeof(LG_widget));

    *widget = *context.default_widget;

    parent_widget->children = realloc(parent_widget->children, sizeof(LG_widget*) * ++parent_widget->child_count);

    parent_widget->children[parent_widget->child_count - 1] = &widget;    

    widget->id = context.current_id++;

    return widget;
}

LG_widget* LG_add_panel_widget(LG_widget* parent_widget){
    LG_widget* widget = LG_add_widget(parent_widget);

    widget->type = LG_WIDGET_TYPE_PANEL;

    return widget;
}

LG_widget* LG_add_text_widget(LG_widget* parent_widget){
    LG_widget* widget = LG_add_widget(parent_widget);

    widget->type = LG_WIDGET_TYPE_TEXT;

    return widget;
}

LG_widget* LG_add_button_widget(LG_widget* parent_widget){
    LG_widget* widget = LG_add_widget(parent_widget);

    widget->type = LG_WIDGET_TYPE_BUTTON;

    return widget;
}

LG_image* LG_load_image(char* filename){
    LG_image* image = malloc(sizeof(LG_image));

    PM_image* temp_image = PM_load_image(filename, 0);

    image->image_data = temp_image->frame_buffer;
    image->width = temp_image->width;
    image->height = temp_image->height;

    free(temp_image);
}

int LG_init(){
    context.default_font_face = LG_new_font_face("fonts/times_new_roman.ttf");

    context.default_font_style = malloc(sizeof(LG_font_style));

    context.default_font_style->flags = 0;
    // xxxxx 0<- 1 for center 0<- 0 for left, 1 for right 0<- 0 for up, 1 for down
    context.default_font_style->font_alignment = 1 << 2;
    context.default_font_style->font_color = 0xAAAAAAFF;
    context.default_font_style->font_face = context.default_font_face;
    context.default_font_style->font_size = 16;
    context.default_font_style->kerning = -1;

    context.default_widget = malloc(sizeof(LG_widget));

    context.default_widget->id = context.current_id++;
    context.default_widget->children = NULL;
    context.default_widget->child_count = 0;
    context.default_widget->parent = NULL;
    context.default_widget->type = LG_WIDGET_TYPE_PANEL;
    context.default_widget->widget_style->background_color = 0x2E2E2EFF;
    context.default_widget->widget_style->border_color = 0x000000FF;
    context.default_widget->widget_style->border_radius = 0;
    context.default_widget->widget_style->border_size = 4;
    context.default_widget->widget_style->height = -1;
    context.default_widget->widget_style->width = -1;
    context.default_widget->widget_style->margin = 0;
    context.default_widget->widget_style->margin = -1;
    context.default_widget->widget_style->margin = -1;
    context.default_widget->widget_style->margin = -1;
    context.default_widget->widget_style->margin = -1;
    context.default_widget->widget_style->padding = 20;
    context.default_widget->widget_style->padding = -1;
    context.default_widget->widget_style->padding = -1;
    context.default_widget->widget_style->padding = -1;
    context.default_widget->widget_style->padding = -1;
    context.default_widget->widget_style->widget_alignment_horizontal = LG_WIDGET_ALIGNMENT_CENTER_HORIZONTAL;
    context.default_widget->widget_style->widget_alignment_vertical = LG_WIDGET_ALIGNMENT_CENTER_VERTICAL;


    context.current_id = 0;

    return 0;
}
