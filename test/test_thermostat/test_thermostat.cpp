#include <runner.h>
#include <unity_runner.h>
#include <fff.h>
DEFINE_FFF_GLOBALS;

#include <thermostat.h>

FAKE_VOID_FUNC(toggle_relay_mock, bool);

void setUp(void)
{
    RESET_FAKE(toggle_relay_mock);
    FFF_RESET_HISTORY();
}

void tearDown(void)
{
    // clean stuff up here
}

TEST(on_change_whenHeaterAndTemperatureLowerThanSet_turnOnHeater)
{
    struct thermostat_t thermostat;
    thermostat.current_temperature = 10;
    thermostat.hysteresis = 0;
    thermostat.set_temperature = 20;
    thermostat.mode = THERMOSTAT_MODE_HEATER;
    thermostat.toggle_relay = toggle_relay_mock;

    thermostat_on_change(&thermostat);

    TEST_ASSERT_EQUAL_MESSAGE(1, toggle_relay_mock_fake.call_count, "toggle_relay");
    TEST_ASSERT_EQUAL_MESSAGE(true, toggle_relay_mock_fake.arg0_val, "toggle_relay on");
}

TEST(on_change_whenHeaterAndTemperatureLowerThanSetAndInRangeOfHysteresisAndHeaterOff_dontTurnOnHeater)
{
    struct thermostat_t thermostat;
    thermostat.current_temperature = 19;
    thermostat.hysteresis = 1;
    thermostat.set_temperature = 20;
    thermostat.mode = THERMOSTAT_MODE_HEATER;
    thermostat.last_state = false;
    thermostat.toggle_relay = toggle_relay_mock;

    thermostat_on_change(&thermostat);

    TEST_ASSERT_EQUAL_MESSAGE(0, toggle_relay_mock_fake.call_count, "toggle_relay");
}

TEST(on_change_whenHeaterAndTemperatureHigherThanSetAndHeaterIsOn_turnOffHeater)
{
    struct thermostat_t thermostat;
    thermostat.current_temperature = 30;
    thermostat.hysteresis = 0;
    thermostat.set_temperature = 20;
    thermostat.mode = THERMOSTAT_MODE_HEATER;
    thermostat.last_state = true;
    thermostat.toggle_relay = toggle_relay_mock;

    thermostat_on_change(&thermostat);

    TEST_ASSERT_EQUAL_MESSAGE(1, toggle_relay_mock_fake.call_count, "toggle_relay");
    TEST_ASSERT_EQUAL_MESSAGE(false, toggle_relay_mock_fake.arg0_val, "toggle_relay on");
}

TEST(on_change_whenCoolerAndTemperatureLowerThanSetAndCoolerIsOff_turnOnCooler)
{
    struct thermostat_t thermostat;
    thermostat.current_temperature = 20;
    thermostat.hysteresis = 0;
    thermostat.set_temperature = 10;
    thermostat.mode = THERMOSTAT_MODE_COOLER;
    thermostat.last_state = false;
    thermostat.toggle_relay = toggle_relay_mock;

    thermostat_on_change(&thermostat);

    TEST_ASSERT_EQUAL_MESSAGE(1, toggle_relay_mock_fake.call_count, "toggle_relay");
    TEST_ASSERT_EQUAL_MESSAGE(true, toggle_relay_mock_fake.arg0_val, "toggle_relay on");
}

TEST(on_change_whenCoolerAndTemperatureHigherThanSetAndInRangeOfHysteresisAndCoolerIsOff_dontTurnOnCooler)
{
    struct thermostat_t thermostat;
    thermostat.current_temperature = 21;
    thermostat.hysteresis = 1;
    thermostat.set_temperature = 20;
    thermostat.mode = THERMOSTAT_MODE_COOLER;
    thermostat.last_state = false;
    thermostat.toggle_relay = toggle_relay_mock;

    thermostat_on_change(&thermostat);

    TEST_ASSERT_EQUAL_MESSAGE(0, toggle_relay_mock_fake.call_count, "toggle_relay");
}

TEST(on_change_whenCoolerAndTemperatureHigherThanSetAndCoolerIsOn_turnOffCooler)
{
    struct thermostat_t thermostat;
    thermostat.current_temperature = 20;
    thermostat.hysteresis = 0;
    thermostat.set_temperature = 30;
    thermostat.mode = THERMOSTAT_MODE_COOLER;
    thermostat.last_state = true;
    thermostat.toggle_relay = toggle_relay_mock;

    thermostat_on_change(&thermostat);

    TEST_ASSERT_EQUAL_MESSAGE(1, toggle_relay_mock_fake.call_count, "toggle_relay");
    TEST_ASSERT_EQUAL_MESSAGE(false, toggle_relay_mock_fake.arg0_val, "toggle_relay on");
}


void process()
{
    UNITY_BEGIN();
    RunAllUnityTests();
    UNITY_END();
}

MAIN()
{
    process();
    return 0;
}
