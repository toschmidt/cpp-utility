#pragma once

#include "PerfCounter.hpp"
#include <chrono>
#include <cpp-utility/perf/definition/CounterDefinition.hpp>
#include <cpp-utility/std/Hash.hpp>
#include <stdexcept>

namespace utility::perf {

   using Counter = definition::Counter;

   namespace definition {
      class PerfCounterDefinition;
      template<typename>
      class DurationCounterDefinition;
   } // namespace definition

   class PerfEvent {
      friend class definition::PerfCounterDefinition;
      template<typename>
      friend class definition::DurationCounterDefinition;

     private:
      std::vector<PerfCounter> perfCounters;
      std::chrono::time_point<std::chrono::steady_clock> startTime;
      std::chrono::time_point<std::chrono::steady_clock> stopTime;
      std::unordered_map<PerfConfig, size_t> perfCounterMap;

      double readPerfCounter(PerfConfig perfConfig) {
         if (perfCounterMap.contains(perfConfig)) {
            return perfCounters[perfCounterMap[perfConfig]].get();
         } else {
            return NAN;
         };
      }

      void addCounter(Counter counter) {
         // if creating the counter definition failed, the pointer will be null
         if (not counter) {
            throw std::runtime_error{"cannot add an invalid counter!"};
         }

         // we only have to take of perf counters, duration is always measured
         if (counter->isPerfCounter() and not perfCounterMap.contains(counter->getPerfConfig())) {
            perfCounterMap[counter->getPerfConfig()] = perfCounters.size();
            perfCounters.emplace_back(counter->getPerfConfig());
         }

         // add additional counters needed to compute extended counters
         for (auto* dependency : counter->dependsOn()) {
            addCounter(dependency);
         }
      }

     public:
      explicit PerfEvent(const std::vector<Counter>& counters) {
         for (auto* counter : counters) {
            addCounter(counter);
         }
      }

      forceinline void start() {
         for (auto& counters : perfCounters) {
            counters.start();
         }
         startTime = std::chrono::steady_clock::now();
      }

      forceinline void stop() {
         stopTime = std::chrono::steady_clock::now();
         for (auto& counters : perfCounters) {
            counters.stop();
         }
      }

      double get(Counter counter) {
         return counter->compute(*this);
      }
   };

} // namespace utility::perf
