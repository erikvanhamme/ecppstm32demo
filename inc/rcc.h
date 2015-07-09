#ifndef RCC_H
#define RCC_H

#include "stm32types.h"

#include "stm32f4xx.h"

#include <cstdint>

namespace ecpp {
    namespace stm32 {
        namespace rcc {

            template<ahb1enr... M>
            static void enableClock() {
                RCC->AHB1ENR |= ahb1enr_mask<M...>::value;
            }

            template<ahb1enr... M>
            static void disableClock() {
                RCC->AHB1ENR &= ~ahb1enr_mask<M...>::value;
            }
        }
    }
}
#endif // RCC_H
