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

#include "gpiopin.h"
#include "gpioport.h"
#include "rcc.h"
#include "stm32types.h"

#include <cstdint>

using namespace ecpp::stm32;

typedef GpioPort<gpioport::pd> ledPort;
typedef GpioPort<gpioport::pa> buttonPort;

typedef GpioPin<gpioport::pd, gpiopin::p12> led1Pin;
typedef GpioPin<gpioport::pd, gpiopin::p13> led2Pin;
typedef GpioPin<gpioport::pd, gpiopin::p14> led3Pin;
typedef GpioPin<gpioport::pd, gpiopin::p15> led4Pin;
typedef GpioPin<gpioport::pa, gpiopin::p0> buttonPin;

int main() {

    ledPort::enable();
    buttonPort::enable();

    led1Pin::configure(gpiomode::output_pushpull);
    led2Pin::configure(gpiomode::output_pushpull);
    led3Pin::configure(gpiomode::output_pushpull);
    led4Pin::configure(gpiomode::output_pushpull);

    ledPort::high<gpiopin::p12, gpiopin::p13, gpiopin::p14, gpiopin::p15>();

	while(true) {
        if (buttonPin::value()) {
            led4Pin::high();
        } else {
            led4Pin::low();
        }
	}
}
