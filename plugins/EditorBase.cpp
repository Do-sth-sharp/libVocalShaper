#include "EditorBase.h"
#include "../projects/ProjectProxy.h"

namespace vocalshaper {
	EditorBase::EditorBase()
		:Component("Editor")
	{
	}

	EditorBase::~EditorBase()
	{
		while (this->childEditorList.size() > 0) {
			this->removeChildEditor(this->childEditorList.getLast());
		}
		if (this->parentEditor != nullptr) {
			this->parentEditor->removeChildEditor(this);
		}
	}

	void EditorBase::addChildEditor(EditorBase* editor, int zOrder)
	{
		jassert(this != editor);

		if (editor->parentEditor != this) {
			if (editor->parentEditor != nullptr)
				editor->parentEditor->removeChildEditor(editor);

			editor->parentEditor = this;
			this->childEditorList.insert(zOrder, editor);

			this->addChildComponent(editor, zOrder);
		}
	}

	void EditorBase::addChildEditorAndMakeVisible(EditorBase* editor, int zOrder)
	{
		this->addChildEditor(editor, zOrder);
		editor->setVisible(true);
	}

	void EditorBase::removeChildEditor(EditorBase* editor)
	{
		int index = this->childEditorList.indexOf(editor);
		if (index >= 0) {
			this->childEditorList.remove(index);
			editor->parentEditor = nullptr;

			this->removeChildComponent(editor);
		}
	}

	ProjectProxy* EditorBase::getProject() const
	{
		return this->project;
	}

	bool EditorBase::getEditMode() const
	{
		return this->editMode;
	}

	uint8_t EditorBase::getToolID() const
	{
		return this->toolID;
	}

	int EditorBase::getTrackID() const
	{
		return this->trackID;
	}

	juce::ReadWriteLock& EditorBase::getProjLock() const
	{
		return this->projLock;
	}

	std::tuple<double, double> EditorBase::getHorizontalViewPort() const
	{
		return std::make_tuple(this->mixStartTime, this->mixEndTime);
	}

	std::tuple<double, double> EditorBase::getVerticalViewPort() const
	{
		return std::make_tuple(this->bottomPitch, this->topPitch);
	}

	std::tuple<double, double> EditorBase::getHViewPort() const
	{
		return std::make_tuple(this->trackStartTime, this->trackEndTime);
	}

	std::tuple<double, double> EditorBase::getVViewPort() const
	{
		return std::make_tuple(this->bottomTrack, this->topTrack);
	}

	double EditorBase::getTotalLength() const
	{
		return this->totalLength;
	}

	double EditorBase::getCurrentPosition() const
	{
		return this->currentTime;
	}

	double EditorBase::getFollowState() const
	{
		return this->follow;
	}

	std::tuple<double, double> EditorBase::getLoopRange() const
	{
		return std::make_tuple(this->loopStartTime, this->loopEndTime);
	}

	AdsorbState EditorBase::getAdsorb() const
	{
		return this->adsorb;
	}

	GridState EditorBase::getGrid() const
	{
		return this->grid;
	}

	void EditorBase::projectChanged(const ProjectProxy* ptr)
	{
		{
			juce::ScopedWriteLock locker(this->projLock);
			this->project = const_cast<ProjectProxy*>(ptr);
		}
		for (auto child : this->childEditorList) {
			if (child) {
				child->projectChanged(ptr);
			}
		}
	}

	void EditorBase::setEditMode(bool editMode)
	{
		this->editMode = editMode;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setEditMode(editMode);
			}
		}
	}

	void EditorBase::setToolID(uint8_t toolID)
	{
		this->toolID = toolID;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setToolID(toolID);
			}
		}
	}

	void EditorBase::trackChanged(int trackID)
	{
		{
			juce::ScopedWriteLock locker(this->projLock);
			this->trackID = trackID;
		}
		for (auto child : this->childEditorList) {
			if (child) {
				child->trackChanged(trackID);
			}
		}
	}

	void EditorBase::setHorizontalViewPort(double startTime, double endTime)
	{
		this->mixStartTime = startTime;
		this->mixEndTime = endTime;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setHorizontalViewPort(startTime, endTime);
			}
		}
	}

	void EditorBase::setVerticalViewPort(double bottomPitch, double topPitch)
	{
		this->bottomPitch = bottomPitch;
		this->topPitch = topPitch;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setVerticalViewPort(bottomPitch, topPitch);
			}
		}
	}

	void EditorBase::setHViewPort(double startTime, double endTime)
	{
		this->trackStartTime = startTime;
		this->trackEndTime = endTime;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setHViewPort(startTime, endTime);
			}
		}
	}

	void EditorBase::setVViewPort(double bottomTrack, double topTrack)
	{
		this->bottomTrack = bottomTrack;
		this->topTrack = topTrack;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setVViewPort(bottomTrack, topTrack);
			}
		}
	}

	void EditorBase::setTotalLength(double totalLength)
	{
		this->totalLength = totalLength;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setTotalLength(totalLength);
			}
		}
	}

	void EditorBase::setCurrentPosition(double currentTime)
	{
		this->currentTime = currentTime;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setCurrentPosition(currentTime);
			}
		}
	}

	void EditorBase::setFollowState(bool follow)
	{
		this->follow = follow;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setFollowState(follow);
			}
		}
	}

	void EditorBase::setLoopRange(double startTime, double endTime)
	{
		this->loopStartTime = startTime;
		this->loopEndTime = endTime;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setLoopRange(startTime, endTime);
			}
		}
	}

	void EditorBase::setAdsorb(AdsorbState state)
	{
		this->adsorb = state;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setAdsorb(state);
			}
		}
	}

	void EditorBase::setGrid(GridState state)
	{
		this->grid = state;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setGrid(state);
			}
		}
	}

	bool EditorBase::isActive()
	{
		//TODO
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
		const std::function<void(double)>& setCurrentPositionFunc,
		const std::function<void(double, double)>& setLoopRangeFunc,
		const std::function<void(double, double)>& setHorizontalViewPortFunc,
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
		std::function<void(double, double)> setHViewPortFunc,
		std::function<void(double, double)> setVViewPortFunc
	)
	{
		this->setHViewPortFunc = setHViewPortFunc;
		this->setVViewPortFunc = setVViewPortFunc;
	}

	void EditorBase::setCurrentTrackMethod(int trackID) const
	{
		if (this->parentEditor) {
			this->parentEditor->setCurrentTrackMethod(trackID);
		}
		if (this->setCurrentTrackFunc) {
			this->setCurrentTrackFunc(trackID);
		}
	}

	void EditorBase::refreshTotalTimeMethod() const
	{
		if (this->parentEditor) {
			this->parentEditor->refreshTotalTimeMethod();
		}
		if (this->refreshTotalTimeFunc) {
			this->refreshTotalTimeFunc();
		}
	}

	void EditorBase::setCurrentPositionMethod(double currentTime) const
	{
		if (this->parentEditor) {
			this->parentEditor->setCurrentPositionMethod(currentTime);
		}
		if (this->setCurrentPositionFunc) {
			this->setCurrentPositionFunc(currentTime);
		}
	}

	void EditorBase::setLoopRangeMethod(double startTime, double endTime) const
	{
		if (this->parentEditor) {
			this->parentEditor->setLoopRangeMethod(startTime, endTime);
		}
		if (this->setLoopRangeFunc) {
			this->setLoopRangeFunc(startTime, endTime);
		}
	}

	void EditorBase::setHorizontalViewPortMethod(double startTime, double endTime) const
	{
		if (this->parentEditor) {
			this->parentEditor->setHorizontalViewPortMethod(startTime, endTime);
		}
		if (this->setHorizontalViewPortFunc) {
			this->setHorizontalViewPortFunc(startTime, endTime);
		}
	}

	void EditorBase::setVerticalViewPortMethod(double bottomPitch, double topPitch) const
	{
		if (this->parentEditor) {
			this->parentEditor->setVerticalViewPortMethod(bottomPitch, topPitch);
		}
		if (this->setVerticalViewPortFunc) {
			this->setVerticalViewPortFunc(bottomPitch, topPitch);
		}
	}

	void EditorBase::setHViewPortMethod(double startTime, double endTime) const
	{
		if (this->parentEditor) {
			this->parentEditor->setHViewPortMethod(startTime, endTime);
		}
		if (this->setHViewPortFunc) {
			this->setHViewPortFunc(startTime, endTime);
		}
	}

	void EditorBase::setVViewPortMethod(double bottomTrack, double topTrack) const
	{
		if (this->parentEditor) {
			this->parentEditor->setVViewPortMethod(bottomTrack, topTrack);
		}
		if (this->setVViewPortFunc) {
			this->setVViewPortFunc(bottomTrack, topTrack);
		}
	}
}