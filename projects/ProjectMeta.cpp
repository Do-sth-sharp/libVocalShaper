#include "ProjectMeta.h"

namespace vocalshaper {
	ProjectMeta::ProjectMeta()
	{
		this->meta.saveEditor = this->meta.createEditor = VS_EDITOR_NAME;
		this->openTime = this->meta.saveTime = this->meta.createTime =
			juce::Time::getCurrentTime().toMilliseconds();
		this->meta.version = VS_PROJECT_VERSION;
	}

	void ProjectMeta::resetMeta(const ProjectMeta::MetaObject& meta)
	{
		this->meta = meta;
		this->openTime = juce::Time::getCurrentTime().toMilliseconds();
	}

	void ProjectMeta::wannaSave()
	{
		uint64_t currentTime = juce::Time::getCurrentTime().toMilliseconds();
		this->meta.saveEditor = VS_EDITOR_NAME;
		this->meta.version = VS_PROJECT_VERSION;
		this->meta.timeSpent += (currentTime - this->openTime);
		this->meta.saveTime = currentTime;
		this->openTime = currentTime;
	}

	const ProjectMeta::MetaObject& ProjectMeta::toMeta()
	{
		return this->meta;
	}
}