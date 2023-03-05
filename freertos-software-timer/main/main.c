#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

#define FIRST_TIMER_PERIOD (pdMS_TO_TICKS(2000UL))
#define SECOND_TIMER_PERIOD (pdMS_TO_TICKS(3000UL))

static TimerHandle_t xSecondTimer, xFirstTimer;
/*-----------------------------------------------------------*/
static void prvTimerCallback(TimerHandle_t xTimer)
{
    TickType_t xTimeNow;
    uint32_t ulExecutionCount;

    ulExecutionCount = (uint32_t)pvTimerGetTimerID(xTimer);
    ulExecutionCount++;
    vTimerSetTimerID(xTimer, (void *)ulExecutionCount);

    xTimeNow = xTaskGetTickCount();

    if (xTimer == xFirstTimer)
    {
        printf("ahihi: %d - %d\n", xTimeNow, ulExecutionCount);
        if (ulExecutionCount == 10)
        {
            xTimerStop(xTimer, 0);
        }
    }
    else if (xTimer == xSecondTimer && ulExecutionCount <= 5)
    {
        printf("----ihaha: %d - %d\n", xTimeNow, ulExecutionCount);
    }
}
/*-----------------------------------------------------------*/

void app_main(void)
{
    xFirstTimer = xTimerCreate("FirstTimer", FIRST_TIMER_PERIOD, pdTRUE, 0, prvTimerCallback);
    xSecondTimer = xTimerCreate("SecondTimer", SECOND_TIMER_PERIOD, pdTRUE, 0, prvTimerCallback);

    if ((xFirstTimer != NULL) && (xSecondTimer != NULL))
    {
        xTimerStart(xFirstTimer, 0);
        xTimerStart(xSecondTimer, 0);
    }
}