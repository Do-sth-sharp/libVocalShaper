#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	namespace utils {
		namespace system {
			class VSAPI MemLimit final
			{
				MemLimit() = delete;

				static uint64_t freeSizeLimit;
				static juce::ReadWriteLock lock;

			public:
				//设置限制
				static void setLimitFreeSize(uint64_t freeSizeLimit);
				//检查容量是否触发限制
				static bool sizeIsNotReachedLimit();

				//内存使用情况
				struct MemState final
				{
					uint64_t ram = 0;			//内存大小(MB)
					uint64_t total = 0;			//总内存量(Byte)
					uint64_t used = 0;			//已使用(Byte)
					uint64_t free = 0;			//剩余(Byte)
					uint64_t actual_used = 0;	//实际使用(Byte)
					uint64_t actual_free = 0;	//实际剩余(Byte)
					double used_percent = 0.;	//使用百分比
					double free_percent = 0.;	//剩余百分比
				};

				//获取内存状态
				static MemState getMemoryState();
			};
		}
	}
}