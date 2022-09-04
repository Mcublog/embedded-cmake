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
#define mainQUEUE_SEND_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

static void DummyTask(void *pvParameters);

int main(void)
{
    LOG_INFO("Hello");

    static char *name = "DummyTask0";

    xTaskCreate(DummyTask, name, configMINIMAL_STACK_SIZE, name,
                mainQUEUE_SEND_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
    for (;;)
    {
        LOG_ERROR("Critacal error");
    }
}

static void DummyTask(void *pvParameters)
{
    const char *name = (const char*)pvParameters;
    for (;;)
    {
        LOG_INFO("Hello from %s", name);
        vTaskDelay(1000);
    }
}
