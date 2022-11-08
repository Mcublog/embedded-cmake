#include <assert.h>
#include <stdbool.h>

#include <button/button.h>
//>>---------------------- Log control
#define LOG_MODULE_NAME test_1
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

bool gpio_irq_handler(app_t_irq_edge_t edge)
{
    LOG_INFO("edge: %s", cm_irq_edge_stringify(edge));
}

int main()
{
    button_init(&gpio_irq_handler);
    button_led_on(true);
    bool led_state = button_led_is_on();
    if (led_state == false)
    {
        LOG_ERROR("led state is not true");
        exit(1);
    }
    return 0;
}
