#include "EditorBase.h"

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

	void EditorBase::addChildEditorToDesktop(EditorBase* editor, int flag)
	{
		jassert(this != editor);

		if (editor->parentEditor != this) {
			if (editor->parentEditor != nullptr)
				editor->parentEditor->removeChildEditor(editor);

			editor->parentEditor = this;
			this->childEditorList.insert(-1, editor);

			editor->addToDesktop(flag);
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

	void EditorBase::setProjectCallback(const ProjectProxy* ptr)
	{
	}

	void EditorBase::setEditModeCallback(bool editMode)
	{
	}

	void EditorBase::setToolIDCallback(uint8_t toolID)
	{
	}

	void EditorBase::setTrackIDCallback(int trackID)
	{
	}

	void EditorBase::setHorizontalViewPortCallback(double startTime, double endTime)
	{
	}

	void EditorBase::setVerticalViewPortCallback(double bottomPitch, double topPitch)
	{
	}

	void EditorBase::setHViewPortCallback(double startTime, double endTime)
	{
	}

	void EditorBase::setVViewPortCallback(double bottomTrack, double topTrack)
	{
	}

	void EditorBase::setTotalLengthCallback(double totalLength)
	{
	}

	void EditorBase::setCurrentPositionCallback(double currentTime)
	{
	}

	void EditorBase::setFollowStateCallback(bool follow)
	{
	}

	void EditorBase::setLoopRangeCallback(double startTime, double endTime)
	{
	}

	void EditorBase::setAdsorbCallback(AdsorbState state)
	{
	}

	void EditorBase::setGridCallback(GridState state)
	{
	}

	void EditorBase::setProject(const ProjectProxy* ptr)
	{
		{
			juce::ScopedWriteLock locker(this->projLock);
			this->project = const_cast<ProjectProxy*>(ptr);
		}
		for (auto child : this->childEditorList) {
			if (child) {
				child->setProject(ptr);
			}
		}
		this->setProjectCallback(ptr);
	}

	void EditorBase::setEditMode(bool editMode)
	{
		this->editMode = editMode;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setEditMode(editMode);
			}
		}
		this->setEditModeCallback(editMode);
	}

	void EditorBase::setToolID(uint8_t toolID)
	{
		this->toolID = toolID;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setToolID(toolID);
			}
		}
		this->setToolIDCallback(toolID);
	}

	void EditorBase::setTrackID(int trackID)
	{
		{
			juce::ScopedWriteLock locker(this->projLock);
			this->trackID = trackID;
		}
		for (auto child : this->childEditorList) {
			if (child) {
				child->setTrackID(trackID);
			}
		}
		this->setTrackIDCallback(trackID);
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
		this->setHorizontalViewPortCallback(startTime, endTime);
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
		this->setVerticalViewPortCallback(bottomPitch, topPitch);
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
		this->setHViewPortCallback(startTime, endTime);
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
		this->setVViewPortCallback(bottomTrack, topTrack);
	}

	void EditorBase::setTotalLength(double totalLength)
	{
		this->totalLength = totalLength;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setTotalLength(totalLength);
			}
		}
		this->setTotalLengthCallback(totalLength);
	}

	void EditorBase::setCurrentPosition(double currentTime)
	{
		this->currentTime = currentTime;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setCurrentPosition(currentTime);
			}
		}
		this->setCurrentPositionCallback(currentTime);
	}

	void EditorBase::setFollowState(bool follow)
	{
		this->follow = follow;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setFollowState(follow);
			}
		}
		this->setFollowStateCallback(follow);
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
		this->setLoopRangeCallback(startTime, endTime);
	}

	void EditorBase::setAdsorb(AdsorbState state)
	{
		this->adsorb = state;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setAdsorb(state);
			}
		}
		this->setAdsorbCallback(state);
	}

	void EditorBase::setGrid(GridState state)
	{
		this->grid = state;
		for (auto child : this->childEditorList) {
			if (child) {
				child->setGrid(state);
			}
		}
		this->setGridCallback(state);
	}

	void EditorBase::refreshSelectedArea()
	{
	}

	juce::OwnedArray<SerializableProjectStructure>&& EditorBase::onCopy()
	{
		return std::move(juce::OwnedArray<SerializableProjectStructure>());
	}

	void EditorBase::onDelete()
	{
	}

	void EditorBase::onSelectAll()
	{
	}

	void EditorBase::onPaste(juce::OwnedArray<SerializableProjectStructure>&& objects)
	{
	}

	void EditorBase::activeThis()
	{
		this->sendActiveMessage(this);
	}

	void EditorBase::unactiveThis()
	{
		this->sendActiveMessage(nullptr);
	}

	bool EditorBase::isActive()
	{
		return checkForActiveWithChildren();
	}

	void EditorBase::select(
		SerializableProjectStructure::Type type, int startIndex, int endIndex,
		bool withoutActive)
	{
		{
			static juce::CriticalSection lock;
			juce::GenericScopedLock<juce::CriticalSection> locker(lock);

			this->selectType = type;
			this->selectStartIndex = startIndex;
			this->selectEndIndex = endIndex;
			this->refreshSelectedArea();
		}

		if (!withoutActive) {
			this->activeThis();
		}
	}

	void EditorBase::unselect()
	{
		this->select(SerializableProjectStructure::Type::Empty, -1, -1, true);
	}

	SerializableProjectStructure::Type EditorBase::getSelectType()
	{
		return this->selectType;
	}

	std::tuple<int, int> EditorBase::getSelectRange()
	{
		return std::make_tuple(this->selectStartIndex, this->selectEndIndex);
	}

	bool EditorBase::isThisActive()
	{
		return this->activeFlag && this->isVisible();
	}

	void EditorBase::setThisActive(bool active)
	{
		this->activeFlag = active;
		if (!active) {
			this->unselect();
		}
	}

	bool EditorBase::checkForActiveWithChildren()
	{
		return this->getActiveEditorRecursive();
	}

	void EditorBase::unactive(const EditorBase* editorWithout)
	{
		this->setThisActive(this == editorWithout);
		for (auto child : this->childEditorList) {
			if (child) {
				child->unactive(editorWithout);
			}
		}
	}

	void EditorBase::sendActiveMessage(const EditorBase* currentEditor)
	{
		if (this->parentEditor) {
			this->parentEditor->sendActiveMessage(currentEditor);
		}
		else {
			this->unactive(currentEditor);
		}
	}

	EditorBase* EditorBase::getActiveEditorRecursive()
	{
		if (this->isThisActive()) {
			return this;
		}
		for (auto child : this->childEditorList) {
			if (child) {
				if (auto ptr = child->getActiveEditorRecursive()) {
					return ptr;
				}
			}
		}
		return nullptr;
	}

	juce::OwnedArray<SerializableProjectStructure>&& EditorBase::sendCopy()
	{
		if (auto ptr = this->getActiveEditorRecursive()) {
			return std::move(ptr->onCopy());
		}
		return std::move(juce::OwnedArray<SerializableProjectStructure>());
	}

	void EditorBase::sendDelete()
	{
		if (auto ptr = this->getActiveEditorRecursive()) {
			ptr->onDelete();
		}
	}

	void EditorBase::sendSelectAll()
	{
		if (auto ptr = this->getActiveEditorRecursive()) {
			ptr->onSelectAll();
		}
	}

	void EditorBase::sendPaste(juce::OwnedArray<SerializableProjectStructure>&& objects)
	{
		if (auto ptr = this->getActiveEditorRecursive()) {
			ptr->onPaste(std::move(objects));
		}
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