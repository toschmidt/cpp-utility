#pragma once

namespace std {

   template<class T, class... Args>
   inline T* new_nothrow(Args&&... args) noexcept(noexcept(T(std::forward<Args>(args)...))) {
      return new (std::nothrow) T(std::forward<Args>(args)...);
   }

} // namespace std
