#include "Project.h"

namespace vocalshaper {
	Project::Project(const juce::String& name, const juce::String& path)
		:name(name),path(path)
	{}

	const juce::String& Project::getName() const
	{
		return this->name;
	}

	const juce::String& Project::getPath() const
	{
		return this->path;
	}

	bool Project::getSaved() const
	{
		return this->saved;
	}
}
