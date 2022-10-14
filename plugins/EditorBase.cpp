#include "EditorBase.h"
#include "../projects/ProjectProxy.h"

namespace vocalshaper {
	EditorBase::EditorBase()
		:Component("Editor")
	{
	}

	void EditorBase::projectChanged(const vocalshaper::ProjectProxy* ptr)
	{
	}

	void EditorBase::setEditMode(bool editMode)
	{
	}

	void EditorBase::setToolID(uint8_t toolID)
	{
	}

	void EditorBase::trackChanged(int trackID)
	{
	}

	void EditorBase::setHorizontalViewPort(ProjectTime startTime, ProjectTime endTime)
	{

	}

	void EditorBase::setVerticalViewPort(double bottomPitch, double topPitch)
	{

	}

	void EditorBase::setTotalLength(ProjectTime totalLength)
	{

	}

	void EditorBase::setCurrentPosition(ProjectTime currentTime)
	{

	}

	bool EditorBase::isActive()
	{
		return this->isVisible() && this->hasKeyboardFocus(true);
	}

	juce::OwnedArray<vocalshaper::SerializableProjectStructure> EditorBase::getCopy()
	{
		return juce::OwnedArray<vocalshaper::SerializableProjectStructure>();
	}

	juce::OwnedArray<vocalshaper::SerializableProjectStructure> EditorBase::getCut()
	{
		return juce::OwnedArray<vocalshaper::SerializableProjectStructure>();
	}

	bool EditorBase::wannaDelete()
	{
		return false;
	}

	bool EditorBase::wannaCopy()
	{
		return false;
	}

	bool EditorBase::wannaSelectAll()
	{
		return false;
	}

	bool EditorBase::wannaPaste(juce::OwnedArray<vocalshaper::SerializableProjectStructure> list)
	{
		return false;
	}

	bool EditorBase::wannaPaste(const juce::StringArray& list)
	{
		return false;
	}

	int EditorBase::showClipBoard(const juce::StringArray& list)
	{
		return -1;
	}
}