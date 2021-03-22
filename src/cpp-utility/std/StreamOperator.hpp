#pragma once

namespace std {

   ostream& operator<<(ostream& out, const uint8_t& v) {
      // print 8-bit numbers as numbers and not as chars
      out << static_cast<int>(v);
      return out;
   }

   ostream& operator<<(ostream& out, const int8_t& v) {
      // print 8-bit numbers as numbers and not as chars
      out << static_cast<int>(v);
      return out;
   }

   template<typename T>
   ostream& operator<<(ostream& out, const vector<T>& v) {
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
