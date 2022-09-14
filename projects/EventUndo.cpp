#include "EventUndo.h"

#include "events/Events.h"
#include "daos/ProjectDAO.h"

/*
* 我知道这里的几个方法的代码质量不太行
* 不过比起一大团弯弯绕绕的模板和函数调用
* 这样写有一种简单粗暴的美
* 反正这些方法能跑，而且跑得很快
*/

namespace vocalshaper {
	bool EventUndo::undo(ProjectEventStructure* event, ProjectProxy* proxy)
	{
		if (!event || !proxy) {
			return false;
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
			auto ptrNew = ptrEvent->ptr.release();
			ptrEvent->ptr.reset(proxy->ptrData.release());
			proxy->ptrData.reset(dynamic_cast<Project*>(ptrNew));
			break;
		}
		case ProjectEventStructure::Type::Track:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<TrackEvent*>(event);
			auto target = ptrEvent->target;

			Track* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Track*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertTrack(project, target.track, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseTrack(project, target.track))) {
					return false;
				}
				if (!ProjectDAO::insertTrack(project, target.track, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseTrack(project, target.track))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::MasterTrack:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<MasterTrackEvent*>(event);
			auto target = ptrEvent->target;

			Track* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Track*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				return false;
			case ProjectEventStructure::ChangeType::Edit:
			{
				juce::ScopedWriteLock pLocker(project->lock);
				ptrOld = project->masterTrack.release();
				project->masterTrack.reset(ptrNew);
				break;
			}
			case ProjectEventStructure::ChangeType::Remove:
				return false;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Note:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<NoteEvent*>(event);
			auto target = ptrEvent->target;

			Note* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Note*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertNote(
					ProjectDAO::getTrack(project, target.track), target.note, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseNote(
					ProjectDAO::getTrack(project, target.track), target.note))) {
					return false;
				}
				if (!TrackDAO::insertNote(
					ProjectDAO::getTrack(project, target.track), target.note, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseNote(
					ProjectDAO::getTrack(project, target.track), target.note))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Phoneme:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PhonemeEvent*>(event);
			auto target = ptrEvent->target;

			Phoneme* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Phoneme*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!NoteDAO::insertPhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = NoteDAO::releasePhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme))) {
					return false;
				}
				if (!NoteDAO::insertPhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = NoteDAO::releasePhoneme(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.phoneme))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::InstrParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<InstrParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Param*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!InstrDAO::insertParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = InstrDAO::releaseParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param))) {
					return false;
				}
				if (!InstrDAO::insertParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = InstrDAO::releaseParam(
					TrackDAO::getInstrument(
						ProjectDAO::getTrack(project, target.track)), target.param))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::NoteParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<NoteParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Param*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!NoteDAO::insertParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = NoteDAO::releaseParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param))) {
					return false;
				}
				if (!NoteDAO::insertParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = NoteDAO::releaseParam(
					TrackDAO::getNote(
						ProjectDAO::getTrack(project, target.track), target.note), target.param))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::PluginParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PluginParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Param*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!PluginDAO::insertParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = PluginDAO::releaseParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param))) {
					return false;
				}
				if (!PluginDAO::insertParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = PluginDAO::releaseParam(
					TrackDAO::getPlugin(
						ProjectDAO::getTrack(project, target.track), target.plugin), target.param))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::TrackParam:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<TrackParamEvent*>(event);
			auto target = ptrEvent->target;

			Param* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Param*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertParam(
					ProjectDAO::getTrack(project, target.track), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseParam(
					ProjectDAO::getTrack(project, target.track), target.param))) {
					return false;
				}
				if (!TrackDAO::insertParam(
					ProjectDAO::getTrack(project, target.track), target.param, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseParam(
					ProjectDAO::getTrack(project, target.track), target.param))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Point:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PointEvent*>(event);
			auto target = ptrEvent->target;

			Point* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Point*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!PhonemeDAO::insertTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = PhonemeDAO::releaseTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point))) {
					return false;
				}
				if (!PhonemeDAO::insertTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = PhonemeDAO::releaseTimePoint(
					NoteDAO::getPhoneme(
						TrackDAO::getNote(
							ProjectDAO::getTrack(project, target.track), target.note), target.phoneme), target.point))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Curve:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<CurveEvent*>(event);
			auto target = ptrEvent->target;

			Curve* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Curve*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertCurve(
					ProjectDAO::getTrack(project, target.track), target.curve, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseCurve(
					ProjectDAO::getTrack(project, target.track), target.curve))) {
					return false;
				}
				if (!TrackDAO::insertCurve(
					ProjectDAO::getTrack(project, target.track), target.curve, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseCurve(
					ProjectDAO::getTrack(project, target.track), target.curve))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::DPoint:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<DPointEvent*>(event);
			auto target = ptrEvent->target;

			DPoint* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<DPoint*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!CurveDAO::insertPoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = CurveDAO::releasePoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point))) {
					return false;
				}
				if (!CurveDAO::insertPoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = CurveDAO::releasePoint(
					TrackDAO::getCurve(
						ProjectDAO::getTrack(project, target.track), target.curve), target.point))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Script:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<ScriptEvent*>(event);
			auto target = ptrEvent->target;

			Script* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Script*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertScript(project, target.script, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseScript(project, target.script))) {
					return false;
				}
				if (!ProjectDAO::insertScript(project, target.script, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseScript(project, target.script))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Wave:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<WaveEvent*>(event);
			auto target = ptrEvent->target;

			Wave* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Wave*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertWave(
					ProjectDAO::getTrack(project, target.track), target.wave, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseWave(
					ProjectDAO::getTrack(project, target.track), target.wave))) {
					return false;
				}
				if (!TrackDAO::insertWave(
					ProjectDAO::getTrack(project, target.track), target.wave, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseWave(
					ProjectDAO::getTrack(project, target.track), target.wave))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Plugin:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<PluginEvent*>(event);
			auto target = ptrEvent->target;

			Plugin* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Plugin*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::insertPlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releasePlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin))) {
					return false;
				}
				if (!TrackDAO::insertPlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releasePlugin(
					ProjectDAO::getTrack(project, target.track), target.plugin))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Json:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<JsonEvent*>(event);
			auto target = ptrEvent->target;

			Json* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Json*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertAddition(project, target.addition, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseAddition(project, target.addition))) {
					return false;
				}
				if (!ProjectDAO::insertAddition(project, target.addition, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseAddition(project, target.addition))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Label:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<LabelEvent*>(event);
			auto target = ptrEvent->target;

			Label* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Label*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!ProjectDAO::insertLabel(project, target.label, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = ProjectDAO::releaseLabel(project, target.label))) {
					return false;
				}
				if (!ProjectDAO::insertLabel(project, target.label, ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = ProjectDAO::releaseLabel(project, target.label))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		case ProjectEventStructure::Type::Instr:
		{
			juce::ScopedWriteLock locker(proxy->lock);
			auto ptrEvent = dynamic_cast<InstrEvent*>(event);
			auto target = ptrEvent->target;

			Instr* ptrOld = nullptr;
			auto ptrNew = dynamic_cast<Instr*>(ptrEvent->ptr.release());
			switch (event->cType)
			{
			case ProjectEventStructure::ChangeType::Add:
				if (!TrackDAO::setInstrument(
					ProjectDAO::getTrack(project, target.track), ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Edit:
				if (!(ptrOld = TrackDAO::releaseInstrument(
					ProjectDAO::getTrack(project, target.track)))) {
					return false;
				}
				if (!TrackDAO::setInstrument(
					ProjectDAO::getTrack(project, target.track), ptrNew)) {
					return false;
				}
				break;
			case ProjectEventStructure::ChangeType::Remove:
				if (!(ptrOld = TrackDAO::releaseInstrument(
					ProjectDAO::getTrack(project, target.track)))) {
					return false;
				}
				break;
			}

			ptrEvent->ptr.reset(ptrOld);
			break;
		}
		}

		return true;
	}
}