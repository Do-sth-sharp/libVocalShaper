#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "datas/Project.h"

namespace vocalshaper {
	class VSAPI ProjectProxy
	{
	public:
		ProjectProxy() = delete;
		ProjectProxy(const juce::String& name, const juce::String& path);
		~ProjectProxy() = default;

	public:
		const juce::String& getName() const;
		const juce::String& getPath() const;

		bool getSaved() const;

	private:
		// name:项目文件名
		// path:项目路径
		const juce::String name;
		const juce::String path;

		std::unique_ptr<Project, std::function<void(Project*)>> ptrData;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectProxy)
	};
}