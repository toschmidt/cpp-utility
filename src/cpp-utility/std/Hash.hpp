#pragma once

#include<numeric>

namespace std {
   /// Partial specializations for pair types.
   template<typename T1, typename T2>
   struct hash<pair<T1, T2>> : public __hash_base<size_t, pair<T1, T2>> {
      inline size_t operator()(pair<T1, T2> p) const noexcept {
         return hash<T1>()(p.first) ^ hash<T2>()(p.second);
      }
   };

   /// Partial specializations for array types.
   template<typename T>
   struct hash<vector<T>> : public __hash_base<size_t, vector<T>> {
      inline size_t operator()(vector<T> v) const noexcept {
         return accumulate(v.begin(), v.end(), 0,
                           [](const size_t& hash, const T& value) { return hash ^ std::hash<T>()(value); });
      }
   };

} // namespace std
