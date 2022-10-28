#include "CountTime.h"
#include "../daos/ProjectDAO.h"

namespace vocalshaper {
	double CountTime::count(const Project* ptr)
	{
		auto result = 0.;
		if (!ptr) {
			return result;
		}

		//计算轨道
		for (int i = 0; i < ProjectDAO::trackSize(ptr); i++) {
			auto track = ProjectDAO::getTrack(ptr, i);
			result = std::max(CountTime::count(track), result);
		}

		//计算标签
		for (int i = 0; i < ProjectDAO::labelSize(ptr); i++) {
			auto label = ProjectDAO::getLabel(ptr, i);
			result = std::max(CountTime::count(label), result);
		}

		return result;
	}

	double CountTime::count(const Track* ptr)
	{
		auto result = 0.;
		if (!ptr) {
			return result;
		}

		//计算曲线
		for (int i = 0; i < TrackDAO::curveSize(ptr); i++) {
			auto curve = TrackDAO::getCurve(ptr, i);
			result = std::max(CountTime::count(curve), result);
		}

		//计算音符
		for (int i = 0; i < TrackDAO::noteSize(ptr); i++) {
			auto note = TrackDAO::getNote(ptr, i);
			result = std::max(CountTime::count(note), result);
		}

		//计算波形
		for (int i = 0; i < TrackDAO::waveSize(ptr); i++) {
			auto wave = TrackDAO::getWave(ptr, i);
			result = std::max(CountTime::count(wave), result);
		}

		return result;
	}

	double CountTime::count(const Label* ptr)
	{
		if (!ptr) {
			return 0.;
		}
		return LabelDAO::getPosition(ptr);
	}

	double CountTime::count(const Curve* ptr)
	{
		auto result = 0.;
		if (!ptr) {
			return result;
		}

		//计算导数点
		for (int i = 0; i < CurveDAO::pointSize(ptr); i++) {
			auto dpoint = CurveDAO::getPoint(ptr, i);
			result = std::max(CountTime::count(dpoint), result);
		}

		return result;
	}

	double CountTime::count(const Note* ptr)
	{
		if (!ptr) {
			return 0.;
		}
		return NoteDAO::getSt(ptr) + NoteDAO::getLength(ptr);
	}

	double CountTime::count(const Wave* ptr)
	{
		if (!ptr) {
			return 0.;
		}
		return WaveDAO::getSt(ptr) + WaveDAO::getLength(ptr);
	}

	double CountTime::count(const DPoint* ptr)
	{
		if (!ptr) {
			return 0.;
		}
		return DPointDAO::getTime(ptr);
	}
}