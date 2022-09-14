#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "ProjectProxy.h"
#include "events/ProjectEventStructure.h"

namespace vocalshaper {
	class EventUndo
	{
		EventUndo() = delete;

	public:
		static bool undo(ProjectEventStructure* event, ProjectProxy* proxy);
	};
}