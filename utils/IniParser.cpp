#include "IniParser.h"

#define MINI_CASE_SENSITIVE
#include "ini.h"

namespace vocalshaper {
	namespace utils {
		namespace ini {
			IniObject::IniObject() noexcept
				:ptrData(new(std::nothrow) mINI::INIStructure)
			{}

			IniObject::IniObject(const juce::String& data) noexcept
				:IniObject()
			{
				this->parse(data);
			}

			IniObject::~IniObject()
			{
				if (this->ptrData) {
					delete this->ptrData;
				}
			}

			IniObject::IniObject(IniObject& dst) noexcept
				:IniObject()
			{
				if (dst.ptrData && this->ptrData) {
					*(this->ptrData) = *(dst.ptrData);
				}
			}

			IniObject::IniObject(IniObject&& dst) noexcept
			{
				this->ptrData = dst.ptrData;
				dst.ptrData = nullptr;
			}

			IniObject& IniObject::operator=(IniObject& dst) noexcept
			{
				if (this != &dst) {
					if (!this->ptrData) {
						this->ptrData = new(std::nothrow) mINI::INIStructure;
					}
					if (dst.ptrData) {
						*(this->ptrData) = *(dst.ptrData);
					}
				}
				return *this;
			}

			IniObject& IniObject::operator=(IniObject&& dst) noexcept
			{
				if (this != &dst) {
					if (this->ptrData) {
						delete this->ptrData;
					}
					this->ptrData = dst.ptrData;
					dst.ptrData = nullptr;
				}
				return *this;
			}

			::mINI::INIReader::T_LineData splitString(const juce::String& data);

			bool IniObject::parse(const juce::String& data)
			{
				if (!this->ptrData) {
					return false;
				}

				::mINI::INIReader::T_LineData fileLines = splitString(data);
				std::string section;
				bool inSection = false;
				::mINI::INIParser::T_ParseValues parseData;
				for (auto const& line : fileLines)
				{
					auto parseResult = ::mINI::INIParser::parseLine(line, parseData);
					if (parseResult == ::mINI::INIParser::PDataType::PDATA_SECTION)
					{
						inSection = true;
						(*this->ptrData)[section = parseData.first];
					}
					else if (inSection && parseResult == ::mINI::INIParser::PDataType::PDATA_KEYVALUE)
					{
						auto const& key = parseData.first;
						auto const& value = parseData.second;
						(*this->ptrData)[section][key] = value;
					}
				}
				return true;
			}

			bool IniObject::has(const juce::String& section, const juce::String& key)
			{
				if (!this->ptrData) {
					return false;
				}
				return this->ptrData->get(section.toStdString()).has(key.toStdString());
			}

			const juce::String IniObject::get(const juce::String& section, const juce::String& key)
			{
				if (!this->ptrData) {
					return juce::String();
				}
				return this->ptrData->get(section.toStdString()).get(key.toStdString());
			}

			//
			::mINI::INIReader::T_LineData splitString(const juce::String& data)
			{
				auto stringArray = juce::StringArray::fromLines(data);
				::mINI::INIReader::T_LineData result;
				for (auto& i : stringArray) {
					result.push_back(i.toStdString());
				}
				return result;
			}
		}
	}
}