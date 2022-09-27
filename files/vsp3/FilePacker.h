#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProtoType.h"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			/*
			* vsp3文件结构
			* 
			* vsp3文件使用RIFF文件格式，一个vsp3文件应包含以下两个基础的RIFF块：fmt和data
			* fmt块数据长度为36字节（4字节protobuf版本+32字节SHA256校验值）
			* data块保存protobuf序列数据
			* vsp3文件使用小端字节序
			*/
			class VSAPI FilePacker
			{
				FilePacker() = delete;

			public:
				static bool unpackData(juce::InputStream& stream, Project* proto);
				static bool packData(const Project* proto, juce::OutputStream& stream);

			private:
				static inline bool checkHead(const char* p1, const char* p2);
				static inline juce::MemoryBlock getHash(const char* ptrData, const size_t size);
				static inline bool checkHash(const char* ptrData, const size_t size,
					const char* ptrHash);
			};
		}
	}
}