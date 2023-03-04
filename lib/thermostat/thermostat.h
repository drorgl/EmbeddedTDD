#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (*toggle_relay_t)(bool on);

    enum THERMOSTAT_MODE
    {
        THERMOSTAT_MODE_HEATER,
        THERMOSTAT_MODE_COOLER
    };

    struct thermostat_t
    {
        float current_temperature;
        int hysteresis;
        float set_temperature;
        enum THERMOSTAT_MODE mode;
        toggle_relay_t toggle_relay;
        bool last_state;
    };

    void thermostat_on_change(struct thermostat_t *thermostat);

#ifdef __cplusplus
}
#endif