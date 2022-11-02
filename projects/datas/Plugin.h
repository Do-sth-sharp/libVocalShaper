#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Param.h"

namespace vocalshaper {
	class VSAPI Plugin : public SerializableProjectStructure
	{
	public:
		enum class PluginType {
			Unknown,
			VST,
			VST3,
			AU,
			LADSPA,
			BuildIn
		}pluginType = PluginType::Unknown;					//效果器类型

	public:
		Plugin(PluginType type)
			:SerializableProjectStructure(SerializableProjectStructure::Type::Plugin),
			pluginType(type)
		{};

	private:
		int uniqueId = 0;									//效果器唯一标识
		bool enabled = false;								//效果器开启

		juce::OwnedArray<Param> params;						//参数

	private:
		friend class PluginDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plugin)
	};
}
