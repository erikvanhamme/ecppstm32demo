/*
 * Copyright 2015 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "basictimer.h"
#include "gpio.h"
#include "stm32types.h"
#include "utils.h"

#include <cstdint>

using namespace ecpp::stm32;

// button is on PA0 for both boards
typedef GpioPort<gpioport::pa> buttonPort;
typedef GpioPin<gpioport::pa, gpiopin::p0> buttonPin;

#ifdef stm32f4
typedef GpioPort<gpioport::pd> ledPort;

typedef GpioPin<gpioport::pd, gpiopin::p12> led1Pin;
typedef GpioPin<gpioport::pd, gpiopin::p13> led2Pin;
typedef GpioPin<gpioport::pd, gpiopin::p14> led3Pin;
typedef GpioPin<gpioport::pd, gpiopin::p15> led4Pin;
#endif

#ifdef stm32f3
typedef GpioPort<gpioport::pe> ledPort;

typedef GpioPin<gpioport::pe, gpiopin::p12> led1Pin;
typedef GpioPin<gpioport::pe, gpiopin::p13> led2Pin;
typedef GpioPin<gpioport::pe, gpiopin::p14> led3Pin;
typedef GpioPin<gpioport::pe, gpiopin::p15> led4Pin;
#endif

typedef GpioPin<gpioport::pd, gpiopin::p11> tPin;
typedef BasicTimer<basictimer::tim6> tTim;

int main() {

    ledPort::enable();
    buttonPort::enable();

    led1Pin::configure(gpiomode::output_pushpull);
    led2Pin::configure(gpiomode::output_pushpull);
    led3Pin::configure(gpiomode::output_pushpull);
    led4Pin::configure(gpiomode::output_pushpull);

    ledPort::high(gpiopin::p12 | gpiopin::p13 | gpiopin::p14 | gpiopin::p15);

    tPin::configure(gpiomode::output_pushpull);

    tTim::enable(); // clock start
    tTim::configure(25000u, (SystemCoreClock / 50000) - 1); // 1000u period
    tTim::setUpdateInterruptEvent(true); // we want interrupts
    tTim::setPeriodBuffered(true);
    tTim::start(); // start counter

	while(true) {
        if (buttonPin::value()) {
            led4Pin::high();
            tTim::updatePeriod(2500);
        } else {
            led4Pin::low();
            tTim::updatePeriod(25000);
        }

        if (tTim::isUpdateInterruptFlag()) {
            tTim::clearUpdateInterruptFlag();

            tPin::toggle();
            led1Pin::toggle();
        }
	}
}
