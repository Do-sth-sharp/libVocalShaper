#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Param.h"

namespace vocalshaper {
	class VSAPI PluginParamEvent : public ProjectEventStructure
	{
	public:
		PluginParamEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::PluginParam, cType)
		{};
		~PluginParamEvent() override;

		struct Target {
			int track;
			int plugin;
			int param;
		};

		void setPtr(Param* ptr);
		Param* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		std::unique_ptr<Param> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(PluginParamEvent)
	};
}