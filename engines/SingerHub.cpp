#include "SingerHub.h"

namespace vocalshaper {
	std::map<juce::String, SingerInfo> SingerHub::list;
	juce::String SingerHub::defaultID;
	juce::ReadWriteLock SingerHub::lock;

	bool SingerHub::add(const juce::String& path)
	{
		//TODO 加载声库信息表
		return true;
	}

	void SingerHub::setDefault(const juce::String& id)
	{
		SingerHub::defaultID = id;
	}

	const SingerInfo SingerHub::getInfoDefault()
	{
		return SingerHub::getInfo(SingerHub::defaultID);
	}

	const SingerInfo SingerHub::getInfo(const juce::String& id)
	{
		juce::ScopedReadLock locker(SingerHub::lock);

		auto it = SingerHub::list.find(id);
		if (it != SingerHub::list.end()) {
			return it->second;
		}

		return SingerInfo();
	}
}