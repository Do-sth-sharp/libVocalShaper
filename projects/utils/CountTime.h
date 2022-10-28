#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Project.h"

namespace vocalshaper {
	class VSAPI CountTime final
	{
		CountTime() = delete;
		~CountTime() = delete;

	public:
		static double count(const Project* ptr);
		static double count(const Track* ptr);
		static double count(const Label* ptr);
		static double count(const Curve* ptr);
		static double count(const Note* ptr);
		static double count(const Wave* ptr);
		static double count(const DPoint* ptr);
	};


}