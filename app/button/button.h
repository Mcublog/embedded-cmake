
#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "common_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void button_init(app_t_gpio_irq_handler_t irg_handler);
    bool button_get_state(void);
    void button_led_on(bool on);
    bool button_led_is_on(void);

    app_t_gpio_irq_handler_t button_get_irq_handler(void);

#ifdef __cplusplus
}
#endif

#endif // BUTTON_H