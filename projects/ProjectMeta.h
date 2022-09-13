#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI ProjectMeta
	{
	public:
		ProjectMeta();
		~ProjectMeta() = default;

	public:
		struct MetaObject
		{
			juce::String createEditor;
			juce::String saveEditor;
			uint64_t timeSpent;
			uint64_t createTime;
			uint64_t saveTime;
			uint32_t version;
		};

	public:
		void resetMeta(const MetaObject& meta);
		void wannaSave();
		const MetaObject& toMeta() const;

		uint64_t getOpenTime() const;

		using MetaBackupData = std::pair<MetaObject, uint64_t>;
		MetaBackupData backup() const;
		void recover(MetaBackupData data);

	private:
		MetaObject meta;
		uint64_t openTime;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectMeta)
	};
}