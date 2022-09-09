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

		void setPtr(Plugin* ptr);
		Plugin* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<Plugin> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(PluginEvent)
	};
}