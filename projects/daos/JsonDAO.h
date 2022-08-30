#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Json.h"

namespace vocalshaper {
	class VSAPI JsonDAO
	{
		JsonDAO() = default;

	public:
		static const juce::var* getData(const Json* ptr);
		static juce::var* getDataMutable(Json* ptr);//注意：这会影响对象的保存符号，非必要不调用

	public:
		static bool isSaved(const Json* ptr);
		static void save(Json* ptr);

	public:
		static Json* create();
		static void destory(Json* ptr);
	};
}