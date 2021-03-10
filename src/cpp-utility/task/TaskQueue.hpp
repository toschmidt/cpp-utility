#pragma once

#include "Barrier.hpp"
#include <cpp-utility/compiler/CompilerHints.hpp>
#include <functional>
#include <thread>
#include <vector>

namespace utility::task {

   class TaskQueue {
     private:
      std::vector<std::function<void(size_t)>> tasks;
      std::atomic<size_t> pos{0};
      size_t n_threads;
      Barrier barrier;
      std::vector<std::thread> threads;

      forceinline static void set_cpu_affinity(int cpu_id) {
         cpu_set_t mask;
         CPU_ZERO(&mask);
         CPU_SET(cpu_id % std::thread::hardware_concurrency(), &mask);
         pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask);
      }

      forceinline bool execute_next_task(size_t thread_id) {
         size_t p = pos++;

         if (p >= tasks.size()) {
            return false;
         }

         tasks.at(p)(thread_id);
         return true;
      }

      forceinline void reset() {
         tasks.clear();
         barrier.reset();
         threads.clear();
         pos = 0;
      }

     public:
      explicit TaskQueue(size_t n_threads) : n_threads(n_threads), barrier(n_threads) {}

      forceinline size_t get_n_threads() const {
         return n_threads;
      }

      forceinline void add_task(const std::function<void(size_t)>& f) {
         tasks.push_back(f);
      }

      forceinline void add_barrier() {
         for (size_t i = 0; i < n_threads; i++) {
            tasks.emplace_back([&](size_t) { barrier.wait(); });
         }
      }

      forceinline void execute_tasks() {
         for (size_t i = 0; i < n_threads; i++) {
            threads.emplace_back([i, this] {
               set_cpu_affinity(i);
               while (this->execute_next_task(i)) {}
            });
         }

         for (auto& thread : threads) {
            thread.join();
         }

         reset();
      }
   };

} // namespace utility::task
