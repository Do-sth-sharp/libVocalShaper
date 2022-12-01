#include "SingerHub.h"

namespace vocalshaper {
	std::map<juce::String, SingerInfo> SingerHub::list;
	juce::String SingerHub::defaultID;
	juce::ReadWriteLock SingerHub::lock;

	bool SingerHub::add(const juce::String& path)
	{
		juce::String infoPath = path + "/singer.json";
		juce::File infoFile(infoPath);
		if (!infoFile.existsAsFile()) {
			return false;
		}

		juce::var jsonData = juce::JSON::parse(infoFile);

		SingerInfo info;
		info.id = jsonData["id"].toString();
		info.name = jsonData["name"].toString();
		info.color = juce::Colour::fromString(jsonData["color"].toString());
		info.portrait = jsonData["portrait"].toString();
		auto styleArray = jsonData["styles"].getArray();
		for (auto& i : *styleArray) {
			info.styles.add(i.toString());
		}
		info.engine = std::make_tuple(jsonData["engine"]["id"].toString(),
			jsonData["engine"]["minVersion"].toString());
		auto languageArray = jsonData["languages"].getArray();
		for (auto& i : *languageArray) {
			info.languages.add(i.toString());
		}
		info.description = jsonData["description"].toString();
		info.license = jsonData["license"].toString();

		{
			juce::ScopedWriteLock locker(SingerHub::lock);
			SingerHub::list.insert(std::make_pair(info.id, info));
		}

		return true;
	}

	void SingerHub::clear()
	{
		juce::ScopedWriteLock locker(SingerHub::lock);
		SingerHub::list.clear();
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