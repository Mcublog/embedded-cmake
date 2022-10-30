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

#define DUMMY_TASK_MAX_NUMBER (2)

typedef struct
{
    uint8_t checking_cnt;
    uint8_t timer_id;
} gpio_t;

static gpio_t _btn = {0};
static void _btn_irq_handler(app_t_irq_edge_t edge);
static void _btn_timeout_hander(uint8_t id);

static TaskHandle_t DummyHandlers[DUMMY_TASK_MAX_NUMBER];
static void DummyTask(void *pvParameters);
void FrtosGetTaskInfo(TaskHandle_t task);
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
    int number = (int)*((int *)pvParameters);
    LOG_INFO("read: %d", number);
    for (;;)
    {
        // time_t t = time(NULL);
        // strftime(buff, MAX_BUFFER_SIZE, "%T", localtime(&t));
        FrtosGetTaskInfo(DummyHandlers[number]);
        // LOG_INFO("%s: %s pin state: %s", buff, name,
        //          cm_stringify_bool(button_get_state()));
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

    static int numbers[DUMMY_TASK_MAX_NUMBER] = {0};

    stimer_init_ctx_t stimer_ctx = {.disable_irq = &timer_irq_disable,
                                    .enable_irq = &timer_irq_enable};

    Timer_Init(&stimer_ctx);
    timer_init((timer_systick_callback_t)&_sys_tick_handler);

    button_init((app_t_gpio_irq_handler_t)&_btn_irq_handler);

    for (int i = 0; i < DUMMY_TASK_MAX_NUMBER; i++)
    {
        numbers[i] = i;
        xTaskCreate(DummyTask, "DummyTask", configMINIMAL_STACK_SIZE, (void *)&numbers[i],
                    mainQUEUE_SEND_TASK_PRIORITY, &DummyHandlers[i]);
    }

    vTaskStartScheduler();
    for (;;)
    {
        LOG_ERROR("Critacal error");
    }
}

void FrtosGetTaskInfo(TaskHandle_t task)
{
    if (!task)
        return;
    TaskStatus_t status;
    eTaskState state = eInvalid;
    vTaskGetInfo(task, &status, true, state);
    LOG_INFO("%s #%d, stack: %d, prio: %d", status.pcTaskName, status.xTaskNumber,
             status.usStackHighWaterMark, status.uxCurrentPriority);
}
//<<----------------------
