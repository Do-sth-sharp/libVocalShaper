#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Json : public SerializableProjectStructure
	{
	public:
		Json()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Json)
		{};
		~Json() override = default;

	private:
		juce::var data = new juce::DynamicObject;			//数据

	private:
		friend class JsonDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Json)
	};
}
