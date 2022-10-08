#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace mINI {
	template<typename T>
	class VSAPI INIMap;

	using INIStructure = INIMap<INIMap<std::string>>;
}

namespace vocalshaper {
	namespace utils {
		namespace ini {
			class VSAPI IniObject
			{
			public:
				IniObject() noexcept;
				IniObject(const juce::String& data) noexcept;
				~IniObject();

				IniObject(IniObject& dst) noexcept;
				IniObject(IniObject&& dst) noexcept;

				IniObject& operator=(IniObject& dst) noexcept;
				IniObject& operator=(IniObject&& dst) noexcept;

				bool parse(const juce::String& data);
				bool has(const juce::String& section, const juce::String& key);
				const juce::String get(const juce::String& section, const juce::String& key);
			private:
				::mINI::INIStructure* ptrData = nullptr;

				JUCE_LEAK_DETECTOR(IniObject)
			};
		}
	}
}