#include "JsonDAO.h"

namespace vocalshaper {
	const juce::var* JsonDAO::getData(const Json* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		return &(ptr->data);
	}

	juce::var* JsonDAO::getDataMutable(Json* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return &(ptr->data);
	}

	bool JsonDAO::isSaved(const Json* ptr)
	{
		return true;
	}

	void JsonDAO::save(Json* ptr)
	{

	}

	Json* JsonDAO::create()
	{
		return new Json;
	}

	void JsonDAO::destory(Json* ptr)
	{
		delete ptr;
	}
}