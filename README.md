# embedded-cmake

Test Embedded Cmake Project

Some testing project for Embedded purpose.

## Brief

The Programm can work on a desktop PC with mocking HW. All GPIO is files.
*List of files and it GPIO:*

```c
#define BUTTON_FILE "/tmp/button"
#define LED_OF_BUTTON "/tmp/led_button"
```

*Usefull commands:*

```bash
# button pressed
echo 1 > /tmp/button && sleep 0.5 && echo 0 > /tmp/button
```

*Requirements*:

* cmake version 3.22.1
* gcc version 11.2.0
* GNU gdb (GDB) 12.1 (*lower version gdb has pthread bug*)

## Links

* [FreeRtosLib](https://github.com/Mcublog/FreeRTOS-CMake)
* [SoftwareTimer](https://github.com/Mcublog/SoftwareTimer)
