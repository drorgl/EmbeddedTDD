#include "thermostat.h"
#include <math.h>

static int get_temperature_difference(struct thermostat_t *thermostat)
{
    return abs(thermostat->current_temperature - thermostat->set_temperature);
}

void thermostat_on_change(struct thermostat_t *thermostat)
{
    int temperature_difference = get_temperature_difference(thermostat);
    bool toggle_value;

    switch (thermostat->mode)
    {
    case THERMOSTAT_MODE_HEATER:
    {

        if (thermostat->current_temperature < thermostat->set_temperature)
        {
            toggle_value = true;
        }
        else
        {
            toggle_value = false;
        }
    }
    break;
    case THERMOSTAT_MODE_COOLER:
    {
        if (thermostat->current_temperature > thermostat->set_temperature)
        {
            toggle_value = true;
        }
        else
        {
            toggle_value = false;
        }
    }
    break;
    }

    if ((temperature_difference > thermostat->hysteresis) &&
        (toggle_value != thermostat->last_state))
    {
        if (toggle_value == true)
        {
            thermostat->toggle_relay(true);
            thermostat->last_state = true;
        }
        else
        {
            thermostat->toggle_relay(false);
            thermostat->last_state = false;
        }
    }
}