#pragma once

namespace utility::perf::definition {

   template<size_t n_dependencies>
   class ExtendedCounterDefinition : public CounterDefinition {
     protected:
      const std::array<Counter, n_dependencies> dependencies;

     public:
      ExtendedCounterDefinition(const std::string_view& name,
                                const std::array<Counter, n_dependencies>& dependencies) noexcept
         : CounterDefinition(name), dependencies(std::move(dependencies)) {}

      bool isPerfCounter() const override {
         return false;
      }

      PerfConfig getPerfConfig() const override {
         throw std::runtime_error{"no perf config available!"};
      }

      std::vector<Counter> dependsOn() const override {
         return std::vector(std::begin(dependencies), std::end(dependencies));
      }
   };

   class DivCounterDefinition : public ExtendedCounterDefinition<2> {
     public:
      DivCounterDefinition(const std::string_view& name, const std::array<Counter, 2>& dependencies) noexcept
         : ExtendedCounterDefinition(name, dependencies) {}

      double compute(PerfEvent& event) const override {
         return event.get(dependencies[0]) / event.get(dependencies[1]);
      }
   };

} // namespace utility::perf::definition
