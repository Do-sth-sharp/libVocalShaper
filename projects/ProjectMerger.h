#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "events/Events.h"
#include "ProjectProxy.h"

namespace vocalshaper {
	class VSAPI ProjectMerger
	{
		ProjectMerger() = delete;

	public:
		static const ProjectEventStructure* merge(ProjectEventStructure* event, ProjectProxy* proxy);
		static ProjectEventStructure* reverse(ProjectEventStructure* event);

	private:
		template<class EventType, class DAOType>
		static void eventReverse(ProjectEventStructure* event);
	};
}