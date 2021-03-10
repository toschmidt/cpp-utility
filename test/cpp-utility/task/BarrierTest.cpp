#include <catch2/catch.hpp>
#include <cpp-utility/task/TaskQueue.hpp>
#include <unistd.h>

using namespace utility::task;

TEST_CASE("Barrier") {
   std::atomic_int counter{0};
   TaskQueue queue(2);

   queue.add_task([&counter](size_t) { counter += 10; });
   queue.add_task([&counter](size_t) {
      usleep(1000);
      if (counter == 10) {
         counter += 10;
      }
   });
   auto func = [&counter](size_t) { counter--; };

   SECTION("with barrier [correct result]") {
      queue.add_barrier();
      queue.add_task(func);
      queue.add_task(func);
      queue.execute_tasks();
      REQUIRE(counter == 18);
   }
   SECTION("without barrier [incorrect result]") {
      queue.add_task(func);
      queue.add_task(func);
      queue.execute_tasks();
      REQUIRE(counter == 8);
   }
}
