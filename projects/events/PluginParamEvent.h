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

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(PluginParamEvent)
	};
}