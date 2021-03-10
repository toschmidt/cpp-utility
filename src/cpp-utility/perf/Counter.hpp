#pragma once

#include "PerfEvent.hpp"
#include <cpp-utility/perf/definition/DurationCounterDefinition.hpp>
#include <cpp-utility/perf/definition/ExtendedCounterDefinition.hpp>
#include <cpp-utility/perf/definition/PerfCounterDefinition.hpp>
#include <cpp-utility/std/New.hpp>

namespace utility::perf {

   // Duration Counters
   static const Counter DURATION = std::new_nothrow<definition::DurationCounterDefinition<std::nano>>("duration_ms");
   static const Counter DURATION_NS = std::new_nothrow<definition::DurationCounterDefinition<std::nano>>("duration_ns");
   static const Counter DURATION_MS =
      std::new_nothrow<definition::DurationCounterDefinition<std::milli>>("duration_ms");
   static const Counter DURATION_S =
      std::new_nothrow<definition::DurationCounterDefinition<std::ratio<1, 1>>>("duration_s");

   // Perf Counters
   static const Counter CYCLES =
      std::new_nothrow<definition::PerfCounterDefinition>("cycles", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CPU_CYCLES);

   static const Counter INSTRUCTIONS =
      std::new_nothrow<definition::PerfCounterDefinition>("instructions", PERF_TYPE_HARDWARE,
                                                          PERF_COUNT_HW_INSTRUCTIONS);

   static const Counter L1D_MISSES =
      std::new_nothrow<definition::PerfCounterDefinition>("l1d-misses", PERF_TYPE_HW_CACHE,
                                                          PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) |
                                                             (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));

   static const Counter L1I_MISSES =
      std::new_nothrow<definition::PerfCounterDefinition>("l1i-misses", PERF_TYPE_HW_CACHE,
                                                          PERF_COUNT_HW_CACHE_L1I | (PERF_COUNT_HW_CACHE_OP_READ << 8) |
                                                             (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));

   static const Counter DTLB_MISSES = std::new_nothrow<definition::PerfCounterDefinition>(
      "dtlb-misses", PERF_TYPE_HW_CACHE,
      PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));

   static const Counter ITLB_MISSES = std::new_nothrow<definition::PerfCounterDefinition>(
      "itlb-misses", PERF_TYPE_HW_CACHE,
      PERF_COUNT_HW_CACHE_ITLB | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));

   static const Counter LLC_MISSES =
      std::new_nothrow<definition::PerfCounterDefinition>("llc-misses", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CACHE_MISSES);

   static const Counter BRANCH_MISSES =
      std::new_nothrow<definition::PerfCounterDefinition>("branch-misses", PERF_TYPE_HARDWARE,
                                                          PERF_COUNT_HW_BRANCH_MISSES);

   static const Counter TASK_CLOCK =
      std::new_nothrow<definition::PerfCounterDefinition>("task-clock", PERF_TYPE_SOFTWARE, PERF_COUNT_SW_TASK_CLOCK);

   // Extended Counters, dividing two existing counters;
   static const Counter IPC =
      std::new_nothrow<definition::DivCounterDefinition>("ipc", std::array<Counter, 2>{INSTRUCTIONS, CYCLES});
   static const Counter CPUS =
      std::new_nothrow<definition::DivCounterDefinition>("cpus", std::array<Counter, 2>{TASK_CLOCK, DURATION});
   static const Counter GHZ =
      std::new_nothrow<definition::DivCounterDefinition>("ghz", std::array<Counter, 2>{CYCLES, TASK_CLOCK});

} // namespace utility::perf
