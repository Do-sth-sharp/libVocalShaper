#include "CountTime.h"
#include "../daos/ProjectDAO.h"

namespace vocalshaper {
	ProjectTime CountTime::count(const Project* ptr, uint32_t curveQuantification)
	{
		auto result = make_time(0, 0);
		if (!ptr) {
			return result;
		}

		//计算轨道
		for (int i = 0; i < ProjectDAO::trackSize(ptr); i++) {
			auto track = ProjectDAO::getTrack(ptr, i);
			result = max(CountTime::count(track, curveQuantification), result, curveQuantification);
		}

		//计算标签
		for (int i = 0; i < ProjectDAO::labelSize(ptr); i++) {
			auto label = ProjectDAO::getLabel(ptr, i);
			result = max(CountTime::count(label, curveQuantification), result, curveQuantification);
		}

		return result;
	}

	ProjectTime CountTime::count(const Track* ptr, uint32_t curveQuantification)
	{
		auto result = make_time(0, 0);
		if (!ptr) {
			return result;
		}

		//计算曲线
		for (int i = 0; i < TrackDAO::curveSize(ptr); i++) {
			auto curve = TrackDAO::getCurve(ptr, i);
			result = max(CountTime::count(curve, curveQuantification), result, curveQuantification);
		}

		//计算音符
		for (int i = 0; i < TrackDAO::noteSize(ptr); i++) {
			auto note = TrackDAO::getNote(ptr, i);
			result = max(CountTime::count(note, curveQuantification), result, curveQuantification);
		}

		//计算波形
		for (int i = 0; i < TrackDAO::waveSize(ptr); i++) {
			auto wave = TrackDAO::getWave(ptr, i);
			result = max(CountTime::count(wave, curveQuantification), result, curveQuantification);
		}

		return result;
	}

	ProjectTime CountTime::count(const Label* ptr, uint32_t curveQuantification)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		return LabelDAO::getPosition(ptr);
	}

	ProjectTime CountTime::count(const Curve* ptr, uint32_t curveQuantification)
	{
		auto result = make_time(0, 0);
		if (!ptr) {
			return result;
		}

		//计算导数点
		for (int i = 0; i < CurveDAO::pointSize(ptr); i++) {
			auto dpoint = CurveDAO::getPoint(ptr, i);
			result = max(CountTime::count(dpoint, curveQuantification), result, curveQuantification);
		}

		return result;
	}

	ProjectTime CountTime::count(const Note* ptr, uint32_t curveQuantification)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		return getTail(NoteDAO::getSt(ptr), NoteDAO::getLength(ptr), curveQuantification);
	}

	ProjectTime CountTime::count(const Wave* ptr, uint32_t curveQuantification)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		return getTail(WaveDAO::getSt(ptr), WaveDAO::getLength(ptr), curveQuantification);
	}

	ProjectTime CountTime::count(const DPoint* ptr, uint32_t curveQuantification)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		return DPointDAO::getTime(ptr);
	}
}