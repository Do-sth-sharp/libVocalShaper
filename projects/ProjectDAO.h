#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "Project.h"

namespace vocalshaper {
	class VSAPI ProjectDAO
	{
	public:
		ProjectDAO() = delete;
		ProjectDAO(const juce::String& name, const juce::String& path);
		~ProjectDAO() = default;

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

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectDAO)
	};
}