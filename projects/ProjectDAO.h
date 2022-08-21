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
		// name:��Ŀ�ļ���
		// path:��Ŀ·��
		const juce::String name;
		const juce::String path;

		// saved:�ѱ���
		bool saved = true;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectDAO)
	};
}