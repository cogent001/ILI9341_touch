#include<stdio.h>
#include "lvgl.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"

#define TAG "LVGL_UI"
#define MOUNT_POINT "/sdcard"

LV_IMG_DECLARE(esp_logo)
LV_IMG_DECLARE(esp_text)

lv_obj_t *temp;
lv_obj_t *img_logo;
lv_obj_t *img_text;

uint32_t rn;

static FILE *f;

//lv_obj_t img_logo;
//lv_obj_t img_text;



static const char * btnm_map[] = {"1", "2", "3", "4", "5", "\n",
                                  "6", "7", "8", "9", "0", "\n",
                                  "Action1", "Action2", ""
                                 };


static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        const char * txt = lv_btnmatrix_get_btn_text(obj, id);

        LV_LOG_USER("%s was pressed\n", txt);
    }
}


void lvgl_ui_start(lv_obj_t *scr)
{
    lv_fs_file_t file;
    static bool firstRun = false;
    static int j = 0;
   
    const char *file_name = MOUNT_POINT"/esp_logo.bin";

    if(firstRun == false)
    {
        temp = lv_img_create(scr);
        img_logo = lv_img_create(scr);
        img_text = lv_img_create(scr);
    
        //lv_fs_res_t res = lv_fs_open(&f, "S:esp_logo.bin", LV_FS_MODE_RD);
        //if(res != LV_FS_RES_OK) ESP_LOGI(TAG, "file not found");
        
        //f = fopen(file_name, "r");
        //if(f == NULL) ESP_LOGI(TAG, "file not found");
        //else ESP_LOGI(TAG, "file read!!");
        //fseek(f, 0, SEEK_END);
        //int sizeF = ftell(f); 
        //fseek(f, 0, SEEK_SET);

        //memcpy(temp, f, sizeF);
        //lv_fs_read(&f, temp, sizeof(uint8_t) * 1000, &rn);
        //lv_img_set_src(img_logo, &f);
        //lv_img_set_src(img_logo, f);
        lv_img_set_src(img_logo, "S:esp_logo.bin");
        //lv_img_set_src(img_logo, &temp);
        //lv_img_set_src(img_logo, &esp_text);

        lv_img_set_src(img_text, LV_SYMBOL_OK "Accept");
        ESP_LOGI(TAG, "load finish!");      
        //fclose(f);
        
        lv_obj_t * btnm1 = lv_btnmatrix_create(scr);
        lv_btnmatrix_set_map(btnm1, btnm_map);
        lv_btnmatrix_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
        lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
        lv_btnmatrix_set_btn_ctrl(btnm1, 11, LV_BTNMATRIX_CTRL_CHECKED);
        lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
        lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);
        ESP_LOGI(TAG, "UI draw finish!");

        firstRun = true;       
    }

    lv_obj_align(img_logo, LV_ALIGN_OUT_BOTTOM_MID, 5, 20 + j);
    lv_obj_align(img_text, LV_ALIGN_OUT_BOTTOM_MID, 50, 100);  
    j++;
    if (j > 50) j = 50;   
     ESP_LOGI(TAG, "INCREASE %d\n", j);      
}