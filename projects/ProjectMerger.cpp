#include "ProjectMerger.h"
#include "daos/ProjectDAO.h"

/*
* 我知道这里的几个方法的代码质量不太行
* 不过比起一大团弯弯绕绕的模板和函数调用
* 这样写有一种简单粗暴的美
* 反正这些方法能跑，而且跑得很快
*/

namespace vocalshaper {
	const ProjectEventStructure* ProjectMerger::merge(ProjectEventStructure* event, ProjectProxy* proxy)
	{
		if (!event || !proxy) {
			return nullptr;
		}

		auto project = proxy->ptrData.get();

		switch (event->type)
		{
		case ProjectEventStructure::Type::Empty:
			break;
		case ProjectEventStructure::Type::Project:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<ProjectEvent*>(event);
			auto target = ptrEvent->target;
			auto ptrOld = proxy->ptrData.release();
			auto ptrNew = ptrEvent->ptr1.release();

			proxy->ptrData.reset(ptrNew);
			if (ptrEvent->ptr2) {
				ProjectDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Track:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<TrackEvent*>(event);
			auto target = ptrEvent->target;

			Track* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertTrack(project, target.track, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseTrack(project, target.track))) {
					return nullptr;
				}
				if (!ProjectDAO::insertTrack(project, target.track, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseTrack(project, target.track))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				TrackDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::MasterTrack:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<MasterTrackEvent*>(event);
			auto target = ptrEvent->target;

			Track* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				return nullptr;
			case ProjectEventStructure::ChangeType::Edit:
			{
				juce::ScopedWriteLock pLocker(project->lock);
				ptrOld = project->masterTrack.release();
				project->masterTrack.reset(ptrNew);
				break;
			}
			case ProjectEventStructure::ChangeType::Remove:
				return nullptr;
			}

			if (ptrEvent->ptr2) {
				TrackDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Note:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<NoteEvent*>(event);
			auto target = ptrEvent->target;

			Note* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertNote(
					ProjectDAO::getTrack(project, target.track), target.note, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseNote(
					ProjectDAO::getTrack(project, target.track), target.note))) {
					return nullptr;
				}
				if (!TrackDAO::insertNote(
					ProjectDAO::getTrack(project, target.track), target.note, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseNote(
					ProjectDAO::getTrack(project, target.track), target.note))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				NoteDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Phoneme:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PhonemeEvent*>(event);
			auto target = ptrEvent->target;

			Phoneme* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!NoteDAO::insertPhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme,  ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = NoteDAO::releasePhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme))) {
					return nullptr;
				}
				if (!NoteDAO::insertPhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = NoteDAO::releasePhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				PhonemeDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::InstrParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<InstrParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!InstrDAO::insertParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = InstrDAO::releaseParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param))) {
					return nullptr;
				}
				if (!InstrDAO::insertParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = InstrDAO::releaseParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				ParamDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::NoteParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<NoteParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!NoteDAO::insertParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = NoteDAO::releaseParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param))) {
					return nullptr;
				}
				if (!NoteDAO::insertParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = NoteDAO::releaseParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				ParamDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::PluginParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PluginParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!PluginDAO::insertParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = PluginDAO::releaseParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param))) {
					return nullptr;
				}
				if (!PluginDAO::insertParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = PluginDAO::releaseParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				ParamDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::TrackParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<TrackParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertParam(
						ProjectDAO::getTrack(project, target.track), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseParam(
					ProjectDAO::getTrack(project, target.track), target.param))) {
					return nullptr;
				}
				if (!TrackDAO::insertParam(
					ProjectDAO::getTrack(project, target.track), target.param, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseParam(
						ProjectDAO::getTrack(project, target.track), target.param))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				ParamDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Point:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PointEvent*>(event);
			auto target = ptrEvent->target;

			Point* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!PhonemeDAO::insertTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = PhonemeDAO::releaseTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point))) {
					return nullptr;
				}
				if (!PhonemeDAO::insertTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = PhonemeDAO::releaseTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				PointDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Curve:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<CurveEvent*>(event);
			auto target = ptrEvent->target;

			Curve* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertCurve(
					ProjectDAO::getTrack(project, target.track), target.curve, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseCurve(
					ProjectDAO::getTrack(project, target.track), target.curve))) {
					return nullptr;
				}
				if (!TrackDAO::insertCurve(
					ProjectDAO::getTrack(project, target.track), target.curve, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseCurve(
					ProjectDAO::getTrack(project, target.track), target.curve))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				CurveDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::DPoint:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<DPointEvent*>(event);
			auto target = ptrEvent->target;

			DPoint* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!CurveDAO::insertPoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = CurveDAO::releasePoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point))) {
					return nullptr;
				}
				if (!CurveDAO::insertPoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = CurveDAO::releasePoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				DPointDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Script:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<ScriptEvent*>(event);
			auto target = ptrEvent->target;

			Script* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertScript(project, target.script, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseScript(project, target.script))) {
					return nullptr;
				}
				if (!ProjectDAO::insertScript(project, target.script, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseScript(project, target.script))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				ScriptDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Wave:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<WaveEvent*>(event);
			auto target = ptrEvent->target;

			Wave* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertWave(
					ProjectDAO::getTrack(project, target.track), target.wave, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseWave(
					ProjectDAO::getTrack(project, target.track), target.wave))) {
					return nullptr;
				}
				if (!TrackDAO::insertWave(
					ProjectDAO::getTrack(project, target.track), target.wave, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseWave(
					ProjectDAO::getTrack(project, target.track), target.wave))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				WaveDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Plugin:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PluginEvent*>(event);
			auto target = ptrEvent->target;

			Plugin* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertPlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releasePlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin))) {
					return nullptr;
				}
				if (!TrackDAO::insertPlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releasePlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				PluginDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Json:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<JsonEvent*>(event);
			auto target = ptrEvent->target;

			Json* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertAddition(project, target.addition, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseAddition(project, target.addition))) {
					return nullptr;
				}
				if (!ProjectDAO::insertAddition(project, target.addition, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseAddition(project, target.addition))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				JsonDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Label:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<LabelEvent*>(event);
			auto target = ptrEvent->target;

			Label* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertLabel(project, target.label, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseLabel(project, target.label))) {
					return nullptr;
				}
				if (!ProjectDAO::insertLabel(project, target.label, ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseLabel(project, target.label))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				LabelDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Instr:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<InstrEvent*>(event);
			auto target = ptrEvent->target;

			Instr* ptrOld = nullptr;
			auto ptrNew = ptrEvent->ptr1.release();
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::setInstrument(
					ProjectDAO::getTrack(project, target.track), ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseInstrument(
					ProjectDAO::getTrack(project, target.track)))) {
					return nullptr;
				}
				if (!TrackDAO::setInstrument(
					ProjectDAO::getTrack(project, target.track), ptrNew)) {
					return nullptr;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseInstrument(
					ProjectDAO::getTrack(project, target.track)))) {
					return nullptr;
				}
				break;
			}

			if (ptrEvent->ptr2) {
				InstrDAO::destory(ptrEvent->ptr2.get());
			}
			ptrEvent->ptr2.reset(ptrOld);
			break;
		}
		}

		return event;
	}

	ProjectEventStructure* ProjectMerger::reverse(ProjectEventStructure* event)
	{
		if (!event) {
			return nullptr;
		}

		switch (event->cType)
		{
		case ProjectEventStructure::ChangeType::Add:
			event->cType = ProjectEventStructure::ChangeType::Remove;
			break;
		case ProjectEventStructure::ChangeType::Edit:
			break;
		case ProjectEventStructure::ChangeType::Remove:
			event->cType = ProjectEventStructure::ChangeType::Add;
			break;
		}

		switch (event->type)
		{
		case ProjectEventStructure::Type::Empty:
			break;
		case ProjectEventStructure::Type::Project:
		{
			ProjectMerger::eventReverse<ProjectEvent, ProjectDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Track:
		{
			ProjectMerger::eventReverse<TrackEvent, TrackDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::MasterTrack:
		{
			ProjectMerger::eventReverse<MasterTrackEvent, TrackDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Note:
		{
			ProjectMerger::eventReverse<NoteEvent, NoteDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Phoneme:
		{
			ProjectMerger::eventReverse<PhonemeEvent, PhonemeDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::InstrParam:
		{
			ProjectMerger::eventReverse<InstrParamEvent, ParamDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::NoteParam:
		{
			ProjectMerger::eventReverse<NoteParamEvent, ParamDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::PluginParam:
		{
			ProjectMerger::eventReverse<PluginParamEvent, ParamDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::TrackParam:
		{
			ProjectMerger::eventReverse<TrackParamEvent, ParamDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Point:
		{
			ProjectMerger::eventReverse<PointEvent, PointDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Curve:
		{
			ProjectMerger::eventReverse<CurveEvent, CurveDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::DPoint:
		{
			ProjectMerger::eventReverse<DPointEvent, DPointDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Script:
		{
			ProjectMerger::eventReverse<ScriptEvent, ScriptDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Wave:
		{
			ProjectMerger::eventReverse<WaveEvent, WaveDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Plugin:
		{
			ProjectMerger::eventReverse<PluginEvent, PluginDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Json:
		{
			ProjectMerger::eventReverse<JsonEvent, JsonDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Label:
		{
			ProjectMerger::eventReverse<LabelEvent, LabelDAO>(event);
			break;
		}
		case ProjectEventStructure::Type::Instr:
		{
			ProjectMerger::eventReverse<InstrEvent, InstrDAO>(event);
			break;
		}
		}

		return event;
	}

	template<class EventType, class DAOType>
	void ProjectMerger::eventReverse(ProjectEventStructure* event)
	{
		auto ptr = dynamic_cast<EventType*>(event);
		if (ptr->ptr1) {
			DAOType::destory(ptr->ptr1.get());
		}
		ptr->ptr1.reset(ptr->ptr2.release());
	}
}