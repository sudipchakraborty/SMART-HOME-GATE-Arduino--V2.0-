#include "PWM.h"

uint8_t PWM::nextChannel = 0;

/**
 * @brief Constructor
 */
PWM::PWM(uint8_t gpio,
         uint32_t freq,
         uint8_t res)
{
    pin = gpio;

    frequency = freq;

    resolution = res;

    maxDuty = (1UL << resolution) - 1;

    duty = 0;

    channel = nextChannel++;

    status.configured = 0;
    status.enabled = 0;
    status.running = 0;

    // Initialize hardware explicitly in setup() with begin().
}

/**
 * @brief Initialize PWM
 */
void PWM::begin()
{
    if (!ledcAttachChannel(pin, frequency, resolution, channel)) return;

    ledcWrite(pin, 0);

    status.configured = 1;
}

/**
 * @brief Enable output
 */
void PWM::enable()
{
    status.enabled = 1;
    ledcWrite(pin, duty);
}

/**
 * @brief Disable output
 */
void PWM::disable()
{
    status.enabled = 0;
    ledcWrite(pin, 0);
}

/**
 * @brief Full ON
 */
void PWM::on()
{
    setDuty(100);
}

/**
 * @brief OFF
 */
void PWM::off()
{
    setDuty(0);
}

/**
 * @brief Set duty percentage
 */
void PWM::setDuty(uint8_t percent)
{
    if(percent > 100)
        percent = 100;

    duty = map(percent,0,100,0,maxDuty);

    if(status.enabled)
        ledcWrite(pin,duty);

    status.running = (percent > 0);
}

/**
 * @brief Set raw duty
 */
void PWM::setDutyRaw(uint32_t raw)
{
    if(raw > maxDuty)
        raw = maxDuty;

    duty = raw;

    if(status.enabled)
        ledcWrite(pin,duty);

    status.running = (raw != 0);
}

/**
 * @brief Get duty %
 */
uint8_t PWM::getDuty()
{
    return (duty * 100UL) / maxDuty;
}

/**
 * @brief Get raw duty
 */
uint32_t PWM::getDutyRaw()
{
    return duty;
}

/**
 * @brief Change frequency
 */
void PWM::setFrequency(uint32_t freq)
{
    frequency = freq;

    ledcChangeFrequency(pin, frequency, resolution);

    ledcWrite(pin,duty);
}

/**
 * @brief Change resolution
 */
void PWM::setResolution(uint8_t bits)
{
    resolution = bits;

    maxDuty = (1UL << resolution) - 1;

    ledcChangeFrequency(pin, frequency, resolution);

    ledcWrite(pin,duty);
}

/**
 * @brief Get frequency
 */
uint32_t PWM::getFrequency()
{
    return frequency;
}

/**
 * @brief Get GPIO
 */
uint8_t PWM::getPin()
{
    return pin;
}

/**
 * @brief Get Channel
 */
uint8_t PWM::getChannel()
{
    return channel;
}

/**
 * @brief Get status
 */
PWM_STATUS PWM::getStatus()
{
    return status;
}

/**
 * @brief PWM Test
 *
 * Fades from 0 to 100% and back.
 */
void PWM::test()
{
    for(int i=0;i<=100;i++)
    {
        setDuty(i);
        delay(10);
    }

    for(int i=100;i>=0;i--)
    {
        setDuty(i);
        delay(10);
    }
}