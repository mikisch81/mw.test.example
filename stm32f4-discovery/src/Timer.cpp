//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include <Timer.hpp>
#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

#if defined(USE_HAL_DRIVER)
extern "C" void __attribute__((no_instrument_function)) HAL_IncTick(void);
#endif

// ----------------------------------------------------------------------------

volatile Timer::ticks_t Timer::ms_delayCount;

// ----------------------------------------------------------------------------

void
Timer::sleep(ticks_t ticks)
{
  ms_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (ms_delayCount != 0u)
    ;
}

void Timer::tick(void)
{
  // Decrement to zero the counter used by the delay routine.
  if (ms_delayCount != 0u)
    {
      --ms_delayCount;
    }
}


// ----- SysTick_Handler() ----------------------------------------------------


extern "C" void SysTick_Handler(void) __attribute__((no_instrument_function));
void SysTick_Handler(void)
{
#if defined(USE_HAL_DRIVER)
  HAL_IncTick();
#endif
  Timer::tick();
}

// ----------------------------------------------------------------------------