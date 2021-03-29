#pragma once

#include <iostream>
#include <utility>
#include <vector>

namespace std {

   inline ostream& operator<<(ostream& out, const uint8_t& v) {
      // print 8-bit numbers as numbers and not as chars
      out << static_cast<int>(v);
      return out;
   }

   inline ostream& operator<<(ostream& out, const int8_t& v) {
      // print 8-bit numbers as numbers and not as chars
      out << static_cast<int>(v);
      return out;
   }

   template<typename T1, typename T2>
   inline ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
      out << "(" << p.first << ", " << p.second << ")";
      return out;
   }

   template<typename T>
   inline ostream& operator<<(ostream& out, const vector<T>& v) {
      out << '[';
      for (size_t i = 0; i < v.size(); i++) {
         if (i != 0) {
            out << ", ";
         }
         out << v[i];
      }
      out << "]";
      return out;
   }

} // namespace std
