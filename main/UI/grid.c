#include <stdio.h>
#include <string.h>
#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "UI.h"

LV_IMG_DECLARE(m_camera)
LV_IMG_DECLARE(m_code)
LV_IMG_DECLARE(m_color)
LV_IMG_DECLARE(m_face)
LV_IMG_DECLARE(m_set)

typedef struct 
{
  app_name menuId;  
  const char str[10];  
  
} mainMenu;

mainMenu myMenu[9] = { 
                        {APP_SETTING, "setting"}, 
                        {APP_CAMERA, "camera"} , 
                        {APP_CODE, "code"}, 
                        {APP_COLOR, "color"}, 
                        {APP_FACE, "face"},
                        {9, "ready1"},
                        {10, "ready2"},
                        {11, "ready3"},
                        {12, "ready4"}
                     };


static void btn_event_cb(lv_event_t * e)
{
    lv_obj_t *myBtn = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(myBtn, 1);
    const char *txt = lv_label_get_text(label);
        
    printf("%s was pressed\n", txt);   
}

void lv_example_grid_1(void)
{
    static lv_coord_t col_dsc[] = {64, 64, 64, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {85, 85, 85, LV_GRID_TEMPLATE_LAST};

    lv_obj_clean(lv_scr_act());

    static lv_style_t style_black;
    lv_style_init(&style_black);
    lv_style_set_bg_color(&style_black, lv_color_black());
    
    static lv_style_t style_gray;
    lv_style_init(&style_gray);
    lv_style_set_bg_color(&style_gray, lv_color_hex(0x606060));
    

    /*Create a container with grid*/
    lv_obj_t *panel = lv_obj_create(lv_scr_act());
    lv_obj_set_grid_align(panel, LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_SPACE_BETWEEN);
    lv_obj_set_grid_dsc_array(panel, col_dsc, row_dsc);
    //lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    //lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(panel, 240, 320);
    //lv_obj_add_style(cont, &style_black, LV_PART_MAIN);
    lv_obj_center(panel);
    lv_obj_set_layout(panel, LV_LAYOUT_GRID);

   
    uint32_t i;
    for(i = 0; i < 9; i++) 
    {
        uint8_t col = i % 3;
        uint8_t row = i / 3;

        lv_obj_t *btn = lv_btn_create(panel);
        lv_obj_t *img = lv_img_create(btn); 
        lv_obj_t *label = lv_label_create(btn);      
        /*Stretch the cell horizontally and vertically too
         *Set span to 1 to make the cell 1 column/row sized*/
        lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, col, 1,
                             LV_GRID_ALIGN_STRETCH, row, 1);
        lv_obj_add_style(btn, &style_gray, LV_PART_MAIN);
               
        if(i == 0) lv_img_set_src(img, &m_set);
        else if(i == 1) lv_img_set_src(img, &m_camera);
        else if(i == 2)  lv_img_set_src(img, &m_code);
        else if(i == 3) lv_img_set_src(img, &m_color);
        else if(i == 4) lv_img_set_src(img, &m_face);  
        lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 0);             
                
        //lv_label_set_text_fmt(label, "c%d, r%d", col, row);
        lv_label_set_text(label, &myMenu[i].str);       
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 10);
        
        lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, panel);  
    }
}
