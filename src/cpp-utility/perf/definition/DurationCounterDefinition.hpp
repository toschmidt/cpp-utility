#pragma once

namespace utility::perf::definition {

   template<typename Ratio = std::nano>
   class DurationCounterDefinition : public CounterDefinition {
     public:
      explicit DurationCounterDefinition(const std::string_view& name) noexcept : CounterDefinition(name){};

      bool isPerfCounter() const override {
         return false;
      }

      PerfConfig getPerfConfig() const override {
         throw std::runtime_error{"no perf config available!"};
      }

      std::vector<Counter> dependsOn() const override {
         return {};
      }

      double compute(PerfEvent& event) const override {
         return std::chrono::duration<double, Ratio>(event.stopTime - event.startTime).count();
      }
   };

} // namespace utility::perf::definition
