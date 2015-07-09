#ifndef GPIOPIN_H
#define GPIOPIN_H

#include "stm32types.h"

#include "stm32f4xx.h"

#include <cstdint>

namespace ecpp {
    namespace stm32 {

        class GpioPinBase {
        protected:

            static void configureImpl(GPIO_TypeDef &port, unsigned int mode, unsigned int pin) {
                port.MODER  &= ~(3 << (pin * 2));
                port.OTYPER &= ~(1 << pin);
                port.PUPDR  &= ~(3 << (pin * 2));

                port.MODER  |= (mode >> 3) << (pin * 2);
                port.OTYPER |= ((mode >> 2) & 1) << pin;
                port.PUPDR  |= (mode & 3) << (pin * 2);
            }

            static void alternateImpl(GPIO_TypeDef &port, unsigned int af, unsigned int pin) {

                if(pin < 8) {
                    port.AFR[0] &= ~(0xf << (pin * 4));
                    port.AFR[0] |= af << (pin * 4);
                } else {
                    pin -= 8;
                    port.AFR[1] &= ~(0xf << (pin * 4));
                    port.AFR[1] |= af << (pin * 4);
                }
            }

        private:
            GpioPinBase() = delete;
        };

        template<gpioport Port, gpiopin Pin>
        class GpioPin final : public GpioPinBase {
        public:

            static void configure(gpiomode mode) {
                constexpr unsigned int pin = bitPosition(static_cast<uint32_t>(Pin));
                configureImpl(*_gpio, static_cast<unsigned int>(mode), pin);
            }

            static void alternate(alternatefunction af) {
                constexpr unsigned int pin = bitPosition(static_cast<uint32_t>(Pin));
                alternateImpl(*_gpio, static_cast<unsigned int>(af), pin);
            }

            static bool value() {
                return _gpio->IDR & static_cast<std::uint32_t>(Pin);
            }

            static void high() {
                _gpio->ODR |= static_cast<std::uint32_t>(Pin);
            }

            static void low() {
                _gpio->ODR &= ~static_cast<std::uint32_t>(Pin);
            }

        private:
            static constexpr GPIO_TypeDef *_gpio = reinterpret_cast<GPIO_TypeDef *>(Port);

            GpioPin() = delete;
        };
    }
}

#endif // GPIOPIN_H
