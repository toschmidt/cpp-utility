#include <utility>

#pragma once

namespace utility::perf {

   class PerfEvent;

   namespace definition {

      class CounterDefinition {
         friend PerfEvent;

        private:
         const std::string_view name;

         virtual bool isPerfCounter() const = 0;

         virtual PerfConfig getPerfConfig() const = 0;

         virtual std::vector<CounterDefinition*> dependsOn() const = 0;

         virtual double compute(PerfEvent&) const = 0;

        protected:
         explicit CounterDefinition(const std::string_view& name) noexcept : name(name) {}

        public:
         std::string getName() const {
            return std::string(name);
         }
      };

      using Counter = CounterDefinition*;

   } // namespace definition
} // namespace utility::perf
