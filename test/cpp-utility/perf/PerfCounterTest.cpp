#include "PerfTest.hpp"
#include <catch2/catch.hpp>
#include <cpp-utility/perf/PerfCounter.hpp>

using namespace utility::perf;

TEST_CASE("Perf Counter", "[!mayfail]") {
   perf_hw_id eventId = PERF_COUNT_HW_MAX;

   SECTION("instructions") {
      eventId = PERF_COUNT_HW_INSTRUCTIONS;
   }
   SECTION("cycles") {
      eventId = PERF_COUNT_HW_CPU_CYCLES;
   }

   PerfCounter counter(std::make_pair(PERF_TYPE_HARDWARE, eventId));
   counter.start();
   work(1e6);
   counter.stop();
   REQUIRE(counter.get() > 1e6);
}
