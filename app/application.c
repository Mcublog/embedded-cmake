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
#include "FreeRTOSConfig.h"
#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>

#include "application.h"
#include "button/button.h"
#include "SoftTimers.h"
#include "utils/app_utils.h"
#include "utils/timer.h"
#include "version.h"
#include "timer.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME app
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (4)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local defines
/* Priorities at which the tasks are created. */
#define mainQUEUE_SEND_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

#define BUTTON_DEBOUNCE_TIME_MS (5)
#define BUTTON_MAX_LEVEL_CHECK_NUMBER (5)

typedef struct
{
    uint8_t checking_cnt;
    uint8_t timer_id;
} gpio_t;

static gpio_t _btn = {0};
static void _btn_irq_handler(app_t_irq_edge_t edge);
static void _btn_timeout_hander(uint8_t id);

static void DummyTask(void *pvParameters);
//<<----------------------

//>>---------------------- Local definitions

/**
 * @brief Btn irq handler function
 *
 * @param edge
 */
static void _btn_irq_handler(app_t_irq_edge_t edge)
{
    LOG_DEBUG("btn %s detected", cm_irq_edge_stringify(edge));
    if (edge == APP_GPIO_IRQ_RISING)
    {
        _btn.checking_cnt = 0; // set level checking
        Timer_Start(_btn.timer_id, BUTTON_DEBOUNCE_TIME_MS);
        return;
    }
}

/**
 * @brief Call this function with 1ms period
 *
 */
static void _sys_tick_handler(void)
{
    Timer_Update();
}

/**
 * @brief
 *
 * @param pvParameters
 */
static void DummyTask(void *pvParameters)
{
    const char *name = (const char *)pvParameters;
    static const int MAX_BUFFER_SIZE = 32;
    char buff[MAX_BUFFER_SIZE];
    for (;;)
    {
        // time_t t = time(NULL);
        // strftime(buff, MAX_BUFFER_SIZE, "%T", localtime(&t));
        LOG_INFO("%s: %s pin state: %s", buff, name,
                 cm_stringify_bool(button_get_state()));
        vTaskDelay(1000);
    }
}
//<<----------------------

//>>---------------------- Global

/**
 * @brief
 *
 */
void application(void)
{
    printf("Dummy test v%s\r\n", VERSION);

    stimer_init_ctx_t stimer_ctx = {
        .disable_irq = &timer_irq_disable,
        .enable_irq = &timer_irq_enable
    };

    Timer_Init(&stimer_ctx);
    timer_init((timer_systick_callback_t)&_sys_tick_handler);

    button_init((app_t_gpio_irq_handler_t)&_btn_irq_handler);

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
