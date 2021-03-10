#pragma once

#include <cpp-utility/compiler/CompilerHints.hpp>

namespace utility::math {

   template<typename T>
   forceinline constexpr bool is_power_of_two(T x) {
      return (x == 1) | (x && ((x & (x - 1)) == 0));
   }

   template<typename T>
   forceinline constexpr T next_power_of_two(T value) {
      if (unlikely(value == 0)) {
         return 0;
      } else if (unlikely(value == 1)) {
         return 1;
      } else {
         if constexpr (sizeof(T) == 4) {
            return 1ull << ((sizeof(T) << 3) - __builtin_clz(value - 1));
         } else {
            return 1ull << ((sizeof(T) << 3) - __builtin_clzll(value - 1));
         }
      }
   }

   template<typename T>
   forceinline constexpr T prev_power_of_two(T value) {
      return next_power_of_two(value) >> 1;
   }

   template<typename T>
   forceinline constexpr T get_number_of_bits(T value) {
      if (value == 0) {
         return 0;
      } else if (value == 1) {
         return 1;
      } else {
         if constexpr (sizeof(T) == 4) {
            return (sizeof(T) << 3) - __builtin_clz(value - 1);
         } else {
            return (sizeof(T) << 3) - __builtin_clzll(value - 1);
         }
      }
   }

   template<typename T>
   forceinline constexpr T align_number(const T& value, const T& align) {
      return ((value + align - 1) / align) * align;
   }

   template<typename T>
   forceinline constexpr T const_log2(const T n) {
      return (n < 2) ? 0 : 1 + const_log2(n / 2);
   }

} // namespace utility::math
