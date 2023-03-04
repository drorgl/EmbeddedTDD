#include <runner.h>
#include <unity_runner.h>
#include <fakeit.h>

// using namespace fakeit;

class Thermostat{
public:
    virtual int calculate() = 0;
};

class Thermostat_ : public Thermostat {
    public:
    virtual int calculate(){return 0;}
};

void setUp(void)
{
}

void tearDown(void)
{
}

TEST(example){
    fakeit::Mock<Thermostat> mock;
    fakeit::When(Method(mock, calculate)).Return(10);

    Thermostat &instance = mock.get();
    int result = instance.calculate();

    TEST_ASSERT_EQUAL(10, result);

    fakeit::Verify(Method(mock,calculate)).Once();
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
