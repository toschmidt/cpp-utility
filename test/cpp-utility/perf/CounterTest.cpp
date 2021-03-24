#include "PerfTest.hpp"
#include <catch2/catch.hpp>
#include <cpp-utility/perf/Counter.hpp>
#include <cpp-utility/perf/PerfEvent.hpp>

using namespace utility::perf;

TEST_CASE("Perf Event", "[!mayfail]") {
   const size_t n = 1e6;

   std::unordered_map<Counter, double> oracle{{INSTRUCTIONS, NAN}, {CYCLES, NAN}, {BRANCH_MISSES, NAN},
                                              {IPC, NAN},          {DURATION, 0}, {CPUS, NAN}};
   std::vector<Counter> counters{};

   SECTION("instructions") {
      counters = {INSTRUCTIONS};
      oracle[INSTRUCTIONS] = n;
   }
   SECTION("instructions, cycles") {
      counters = {INSTRUCTIONS, CYCLES};
      oracle[INSTRUCTIONS] = n;
      oracle[CYCLES] = n;
      oracle[IPC] = 0;
   }
   SECTION("ipc") {
      counters = {INSTRUCTIONS, CYCLES};
      oracle[INSTRUCTIONS] = n;
      oracle[CYCLES] = n;
      oracle[IPC] = 0;
   }
   SECTION("duration") {
      counters = {DURATION};
      oracle[DURATION] = n;
   }
   SECTION("cpus") {
      counters = {CPUS};
      oracle[DURATION] = n;
      oracle[CPUS] = 0;
   }

   PerfEvent event(counters);
   event.start();
   work(1e6);
   event.stop();

   for (auto value : oracle) {
      auto result = event.get(value.first);
      REQUIRE(((std::isnan(result) and std::isnan(value.second)) or result > value.second));
   }
}
