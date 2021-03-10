#include <catch2/catch.hpp>
#include <cpp-utility/task/TaskQueue.hpp>

using namespace utility::task;

int atomic_add(size_t n_threads, size_t n_tasks) {
   std::atomic_int counter{0};
   TaskQueue queue(n_threads);

   auto f = [&counter](size_t) { counter++; };

   for (size_t i = 0; i < n_tasks; i++) {
      queue.add_task(f);
   }
   queue.execute_tasks();

   return counter;
}

TEST_CASE("Task Queue") {
   SECTION("no threads") {
      REQUIRE(atomic_add(0, 0) == 0);
      REQUIRE(atomic_add(0, 1) == 0);
   }
   SECTION("one thread") {
      REQUIRE(atomic_add(1, 0) == 0);
      REQUIRE(atomic_add(1, 1) == 1);
   }
   SECTION("multiple threads") {
      REQUIRE(atomic_add(2, 2) == 2);
      REQUIRE(atomic_add(2, 8) == 8);
      REQUIRE(atomic_add(64, 16) == 16);
   }
}
