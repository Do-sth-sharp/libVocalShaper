#include "MemLimit.h"
#include <sigar.h>

namespace vocalshaper {
	namespace utils {
		namespace system {
			uint64_t MemLimit::freeSizeLimit = 0;
			juce::ReadWriteLock MemLimit::lock;

			void MemLimit::setLimitFreeSize(uint64_t freeSizeLimit)
			{
				juce::ScopedWriteLock locker(MemLimit::lock);
				MemLimit::freeSizeLimit = freeSizeLimit;
			}

			bool MemLimit::sizeIsNotReachedLimit()
			{
				juce::ScopedReadLock locker(MemLimit::lock);

				auto state = MemLimit::getMemoryState();

				return state.actual_free > MemLimit::freeSizeLimit;
			}

			MemLimit::MemState MemLimit::getMemoryState()
			{
				//sigar指针
				sigar_t* sigar_mem = nullptr;
				MemState result;

				//初始化指针
				sigar_open(&sigar_mem);
				if (sigar_mem) {
					//获取信息
					sigar_mem_t mem;
					sigar_mem_get(sigar_mem, &mem);

					//信息导出
					result.ram = mem.ram;
					result.total = mem.total;
					result.used = mem.used;
					result.free = mem.free;
					result.actual_used = mem.actual_used;
					result.actual_free = mem.actual_free;
					result.used_percent = mem.used_percent;
					result.free_percent = mem.free_percent;

					//释放指针
					sigar_close(sigar_mem);
					sigar_mem = nullptr;
				}
				
				return result;
			}
		}
	}
}