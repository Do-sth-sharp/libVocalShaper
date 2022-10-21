#include "EditorBase.h"
#include "../projects/ProjectProxy.h"

namespace vocalshaper {
	EditorBase::EditorBase()
		:Component("Editor")
	{
	}

	void EditorBase::projectChanged(const ProjectProxy* ptr)
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

	void EditorBase::setHViewPort(ProjectTime startTime, ProjectTime endTime)
	{

	}

	void EditorBase::setVViewPort(double bottomPer, double topPer)
	{

	}

	void EditorBase::setTotalLength(ProjectTime totalLength)
	{

	}

	void EditorBase::setCurrentPosition(ProjectTime currentTime)
	{

	}

	void EditorBase::setFollowState(bool follow)
	{

	}

	void EditorBase::setLoopRange(ProjectTime startTime, ProjectTime endTime)
	{

	}

	void EditorBase::setAdsorb(AdsorbState state)
	{

	}

	void EditorBase::setGrid(GridState state)
	{

	}

	bool EditorBase::isActive()
	{
		return this->isVisible() && this->hasKeyboardFocus(true);
	}

	juce::OwnedArray<SerializableProjectStructure> EditorBase::getCopy()
	{
		return juce::OwnedArray<SerializableProjectStructure>();
	}

	juce::OwnedArray<SerializableProjectStructure> EditorBase::getCut()
	{
		return juce::OwnedArray<SerializableProjectStructure>();
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

	bool EditorBase::wannaPaste(juce::OwnedArray<SerializableProjectStructure> list)
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

	void EditorBase::setMethods(
		const std::function<void(int)>& setCurrentTrackFunc,
		const std::function<void(void)>& refreshTotalTimeFunc,
		const std::function<void(ProjectTime)>& setCurrentPositionFunc,
		const std::function<void(ProjectTime, ProjectTime)>& setLoopRangeFunc,
		const std::function<void(ProjectTime, ProjectTime)>& setHorizontalViewPortFunc,
		const std::function<void(double, double)>& setVerticalViewPortFunc
	)
	{
		this->setCurrentTrackFunc = setCurrentTrackFunc;
		this->refreshTotalTimeFunc = refreshTotalTimeFunc;
		this->setCurrentPositionFunc = setCurrentPositionFunc;
		this->setLoopRangeFunc = setLoopRangeFunc;
		this->setHorizontalViewPortFunc = setHorizontalViewPortFunc;
		this->setVerticalViewPortFunc = setVerticalViewPortFunc;
	}

	void EditorBase::setTrackViewMethods(
		std::function<void(ProjectTime, ProjectTime)> setHViewPortFunc,
		std::function<void(double, double)> setVViewPortFunc
	)
	{
		this->setHViewPortFunc = setHViewPortFunc;
		this->setVViewPortFunc = setVViewPortFunc;
	}

	void EditorBase::setCurrentTrackMethod(int trackID) const
	{
		if (this->setCurrentTrackFunc) {
			this->setCurrentTrackFunc(trackID);
		}
	}

	void EditorBase::refreshTotalTimeMethod() const
	{
		if (this->refreshTotalTimeFunc) {
			this->refreshTotalTimeFunc();
		}
	}

	void EditorBase::setCurrentPositionMethod(ProjectTime currentTime) const
	{
		if (this->setCurrentPositionFunc) {
			this->setCurrentPositionFunc(currentTime);
		}
	}

	void EditorBase::setLoopRangeMethod(ProjectTime startTime, ProjectTime endTime) const
	{
		if (this->setLoopRangeFunc) {
			this->setLoopRangeFunc(startTime, endTime);
		}
	}

	void EditorBase::setHorizontalViewPortMethod(ProjectTime startTime, ProjectTime endTime) const
	{
		if (this->setHorizontalViewPortFunc) {
			this->setHorizontalViewPortFunc(startTime, endTime);
		}
	}

	void EditorBase::setVerticalViewPortMethod(double bottomPitch, double topPitch) const
	{
		if (this->setVerticalViewPortFunc) {
			this->setVerticalViewPortFunc(bottomPitch, topPitch);
		}
	}

	void EditorBase::setHViewPortMethod(ProjectTime startTime, ProjectTime endTime) const
	{
		if (this->setHViewPortFunc) {
			this->setHViewPortFunc(startTime, endTime);
		}
	}

	void EditorBase::setVViewPortMethod(double bottomPer, double topPer) const
	{
		if (this->setVViewPortFunc) {
			this->setVViewPortFunc(bottomPer, topPer);
		}
	}
}