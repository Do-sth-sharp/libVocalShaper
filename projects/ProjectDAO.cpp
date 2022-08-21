#include "ProjectDAO.h"

namespace vocalshaper {
	ProjectDAO::ProjectDAO(const juce::String& name, const juce::String& path)
		:name(name), path(path)
	{}

	const juce::String& ProjectDAO::getName() const
	{
		return this->name;
	}

	const juce::String& ProjectDAO::getPath() const
	{
		return this->path;
	}

	bool ProjectDAO::getSaved() const
	{
		return this->saved;
	}
}