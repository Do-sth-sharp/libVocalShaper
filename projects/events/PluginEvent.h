#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Plugin.h"

namespace vocalshaper {
	class VSAPI PluginEvent : public ProjectEventStructure
	{
	public:
		PluginEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Plugin, cType)
		{};
		~PluginEvent() override;

		struct Target {
			int track;
			int plugin;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(PluginEvent)
	};
}