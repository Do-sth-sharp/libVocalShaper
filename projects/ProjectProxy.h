#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

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
		// name:��Ŀ�ļ���
		// path:��Ŀ·��
		const juce::String name;
		const juce::String path;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectProxy)
	};
}