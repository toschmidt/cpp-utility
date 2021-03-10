#pragma once

#include <cpp-utility/compiler/CompilerHints.hpp>
#include <cstring>
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <syscall.h>
#include <unistd.h>

namespace utility::perf {

   using PerfConfig = std::pair<uint64_t, uint64_t>;

   class PerfCounter {
     private:
      struct alignas(32) read_format {
         uint64_t value{};
         uint64_t time_enabled{};
         uint64_t time_running{};
      };

      perf_event_attr pe{};
      int fd;
      read_format prev;
      read_format data;

     public:
      explicit PerfCounter(PerfConfig config) : fd(0) {
         memset(&pe, 0, sizeof(perf_event_attr));
         pe.type = config.first;
         pe.size = sizeof(perf_event_attr);
         pe.config = config.second;
         pe.disabled = true;
         pe.inherit = 1;
         pe.inherit_stat = 0;
         pe.exclude_kernel = false;
         pe.exclude_hv = false;
         pe.read_format = PERF_FORMAT_TOTAL_TIME_ENABLED | PERF_FORMAT_TOTAL_TIME_RUNNING;

         fd = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0); // NOLINT
      }

      forceinline void start() {
         ioctl(fd, PERF_EVENT_IOC_RESET, 0);
         ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
         read(fd, &prev, sizeof(uint64_t) * 3);
      }

      forceinline void stop() {
         read(fd, &data, sizeof(uint64_t) * 3);
         ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
      }

      forceinline double get() const {
         return static_cast<double>(data.value - prev.value) *
            (static_cast<double>(data.time_enabled - prev.time_enabled) /
             static_cast<double>(data.time_running - prev.time_running));
      }
   };

} // namespace utility::perf
