#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI Project
	{
	public:
		Project() = delete;
		Project(const juce::String& name, const juce::String& path);
		~Project() = default;

	public:
		const juce::String& getName() const;
		const juce::String& getPath() const;

		bool getSaved() const;

	private:
		// name:项目文件名
		// path:项目路径
		const juce::String name;
		const juce::String path;

		// saved:已保存
		bool saved = true;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Project)
	};
}
