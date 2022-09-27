#pragma once
#include "../../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI ProjectProxy;

	namespace files {
		namespace vsp3 {
			void VSAPI shutDownProtobufLibrary();

			bool VSAPI readProject(
				::vocalshaper::ProjectProxy* project, juce::FileInputStream& stream);
			bool VSAPI writeProject(
				::vocalshaper::ProjectProxy* project, juce::FileOutputStream& stream);
		}
	}
}