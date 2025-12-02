#include "../headers/lemonguice.h"
#include "../headers/sourparse.h"
#include "../headers/pitmap.h"

LG_context context;

LG_context* LG_get_context(){
    return &context;
}

LG_font_face* LG_new_font_face(char* filename){
    LG_font_face* font_face = malloc(sizeof(LG_font_face));
    
    font_face->font = SP_load_font(filename);

    return font_face;
}

LG_font_style* LG_new_font_style(){
    LG_font_style* font_style = malloc(sizeof(LG_font_style));

    *font_style = *context.default_font_style;

    return font_style;
}

LG_widget* LG_new_window(char* title, uint16_t width, uint16_t height){
    LG_widget* widget = malloc(sizeof(LG_widget));
  
    *widget = *context.default_widget;    

    widget->window_data = malloc(sizeof(LG_window_data));
    
    widget->id = context.current_id++;
    widget->children = NULL;
    widget->parent = NULL;
    widget->type = LG_WIDGET_TYPE_PANEL;

    widget->window_data->width = width;
    widget->window_data->height = height;

    widget->window_data->sdl_window = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, 
        height, 0
    );
    widget->window_data->sdl_renderer = SDL_CreateRenderer(widget->window_data->sdl_window, -1, SDL_RENDERER_ACCELERATED);
    widget->window_data->sdl_window_texture = SDL_CreateTexture(
        widget->window_data->sdl_renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        width, 
        height
    );

    widget->window_data->frame_buffer = malloc(
        sizeof(uint32_t) * width * height
    );

    context.current_window_panel_count++;

    return widget;
}

LG_widget* LG_add_widget(LG_widget* parent_widget){
    LG_widget* widget = malloc(sizeof(LG_widget));

    *widget = *context.default_widget;

    parent_widget->children = realloc(parent_widget->children, sizeof(LG_widget*) * ++parent_widget->child_count);

    parent_widget->children[parent_widget->child_count - 1] = widget;    

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

    return image;
}

int LG_render_window(LG_widget* window_widget){
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT: {
                context.current_window_panel_count--;

                break;
            }

            default: {
                break;
            }
        }
    }

    int child_count = window_widget->child_count;

    uint16_t current_width = window_widget->window_data->width;
    uint16_t current_height = window_widget->window_data->height;

    // generate styling

    // for (int child_i = 0; child_i < child_count; child_i++){
    //     uint16_t width;
    //     uint16_t height;

    //     if ()

    //     for (int y = 0; y < )
    // }

    // rasterize

    uint16_t r = window_widget->widget_style->radius;

    for (int y = 0; y < current_height; y++){
        int x_offset;

        if (y < r) x_offset = r - (int)((float)r * ((float)sqrt((float)1 - ((float)(r - y) / (float)r) * ((float)(r - y) / (float)r))));
        else if (y < current_height - r) x_offset = 0;
        else x_offset = r - (int)((float)r * ((float)sqrt((float)1 - ((float)(r - (current_height - y)) / (float)r) * ((float)(r - (current_height - y)) / (float)r))));

        for (int x = x_offset; x < current_width - x_offset; x++){
            window_widget->window_data->frame_buffer[y * current_height + x] = window_widget->widget_style->background_color;
        }
    }

    // copy frame data to window

    int width_int = (int)window_widget->window_data->width;

    SDL_LockTexture(
        window_widget->window_data->sdl_window_texture, 
        NULL, 
        (void*)&window_widget->window_data->frame_buffer, 
        &width_int
    );

    SDL_UnlockTexture(window_widget->window_data->sdl_window_texture);

    SDL_RenderCopy(window_widget->window_data->sdl_renderer, window_widget->window_data->sdl_window_texture, NULL, NULL);
    SDL_RenderPresent(window_widget->window_data->sdl_renderer);

    return 0;
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

    context.default_widget->widget_style = malloc(sizeof(LG_widget_style));

    context.default_widget->id = context.current_id++;
    context.default_widget->children = NULL;
    context.default_widget->child_count = 0;
    context.default_widget->parent = NULL;
    context.default_widget->type = LG_WIDGET_TYPE_PANEL;
    context.default_widget->widget_style->background_color = 0xAAAAFFFF;
    context.default_widget->widget_style->border_color = 0xFFFFFFFF;
    context.default_widget->widget_style->radius = 40;
    context.default_widget->widget_style->border_size = 10;
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
