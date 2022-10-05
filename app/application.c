/**
 * @file application.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-10-05
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
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include "FreeRTOSConfig.h"
#include "app/utils/app_utils.h"

#include "application.h"
#include "version.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME app
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local defines
/* Priorities at which the tasks are created. */
#define mainQUEUE_SEND_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

static void DummyTask(void *pvParameters);
//<<----------------------

//>>---------------------- Local definitions
static void DummyTask(void *pvParameters)
{
    const char *name = (const char *)pvParameters;
    for (;;)
    {
        LOG_INFO("Hello from %s", name);
        vTaskDelay(1000);
    }
}
//<<----------------------

//>>---------------------- Global
void application(void)
{
    printf("Dummy test v%s\r\n", VERSION);
    xTaskCreate(DummyTask, "DummyTask", configMINIMAL_STACK_SIZE, (void *)"DummyTask0",
                mainQUEUE_SEND_TASK_PRIORITY, NULL);
    xTaskCreate(DummyTask, "DummyTask", configMINIMAL_STACK_SIZE, (void *)"DummyTask1",
                mainQUEUE_SEND_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
    for (;;)
    {
        LOG_ERROR("Critacal error");
    }
}
//<<----------------------
