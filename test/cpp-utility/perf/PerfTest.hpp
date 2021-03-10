#pragma once

#include <cstddef>

namespace utility::perf {

   static int work(size_t n) {
      volatile int counter = 0;
      for (size_t i = 0; i < n; i++) {
         counter = counter + 1;
      }
      return counter;
   }

} // namespace utility::perf
