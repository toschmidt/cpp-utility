#pragma once

#include <utility>

namespace utility::perf::definition {

   class PerfCounterDefinition : public CounterDefinition {
     private:
      PerfConfig perfConfig;

     public:
      PerfCounterDefinition(const std::string_view& name, uint64_t perfTypeId, uint64_t perfEventId) noexcept
         : CounterDefinition(name), perfConfig(std::make_pair(perfTypeId, perfEventId)) {}

      bool isPerfCounter() const override {
         return true;
      }

      PerfConfig getPerfConfig() const override {
         return perfConfig;
      }

      std::vector<Counter> dependsOn() const override {
         return {};
      }

      double compute(PerfEvent& event) const override {
         return event.readPerfCounter(perfConfig);
      }
   };

} // namespace utility::perf::definition
