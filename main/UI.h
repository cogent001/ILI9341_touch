#include <stdlib.h>
#include "freertos/timers.h"

#define CANVAS_WIDTH  240
#define CANVAS_HEIGHT 240

enum UI_staus
{
    UI_STAT_RUNNING = 0,
    UI_STAT_CLOSING,
    UI_STAT_CLOSED
};

enum UI_control
{
    UI_PENDING = 0,
    UI_START,
    UI_CLEAR_AND_STOP
};

typedef enum 
{
    APP_TITLE = 0,
    APP_EYE_MOVE,
    APP_MENU,
    APP_SETTING,
    APP_CAMERA,
    APP_CODE,
    APP_COLOR,
    APP_FACE,
    APP_WORK_IN_PROGRESS
}app_name;

typedef struct 
{
    int icon_number;
    int data0;
    int data1;

} return_data_t;

typedef struct
{
    int status;
    int appName;
    return_data_t data;

} app_return_t;

typedef struct 
{
    uint32_t key;
    lv_indev_state_t state;

} key_input;

//for timer callback
TimerHandle_t xAutoReloadTimer;
BaseType_t xTimer1Started, xTimer1Stopped;

static int32_t gCount = 0;
static void pvTimerCallback(TimerHandle_t xTimer)
{
    static TickType_t xTimeNow;
    xTimeNow = xTaskGetTickCount();
    printf("Auto-reload timer callback executing %d\r\n", xTimeNow);
    gCount++;
}