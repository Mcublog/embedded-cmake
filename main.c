/**
 * @file main.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-09-03
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "FreeRTOSConfig.h"

#include "app/utils/app_utils.h"

//>>---------------------- Log control
#define LOG_MODULE_NAME main
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define mainQUEUE_SEND_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

/* The rate at which data is sent to the queue.  The times are converted from
milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define mainTASK_SEND_FREQUENCY_MS pdMS_TO_TICKS(500UL)
#define mainTIMER_SEND_FREQUENCY_MS pdMS_TO_TICKS(1000UL)

/* The values sent to the queue receive task from the queue send task and the
queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK (100UL)
#define mainVALUE_SENT_FROM_TIMER (200UL)


static SemaphoreHandle_t xStdioMutex;
static StaticSemaphore_t xStdioMutexBuffer;

// static void console_init(void);
// static void console_print(const char *fmt, ...);

static void DummyTask(void *pvParameters);

int main(void)
{
    LOG_INFO("Hello");
    // console_init();
    xTaskCreate(DummyTask, "DummyTask", configMINIMAL_STACK_SIZE, NULL,
                mainQUEUE_SEND_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
    for (;;)
    {
        LOG_ERROR("Critacal error");
    }
}

static void DummyTask(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        LOG_INFO("DummyTask");
        vTaskDelay(1000);
    }
}

// static void console_init(void)
// {
//     xStdioMutex = xSemaphoreCreateMutexStatic(&xStdioMutexBuffer);
// }

// static void console_print(const char *fmt, ...)
// {
//     char buff[60];
//     time_t t = time(NULL);
//     strftime(buff, 60, "%T", localtime(&t));
//     va_list vargs;

//     va_start(vargs, fmt);

//     xSemaphoreTake(xStdioMutex, portMAX_DELAY);
//     printf("%s: ", buff);

//     vprintf(fmt, vargs);

//     xSemaphoreGive(xStdioMutex);

//     va_end(vargs);
// }
