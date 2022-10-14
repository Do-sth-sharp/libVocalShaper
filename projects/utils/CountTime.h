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
		inline static ProjectTime count(const Project* ptr, uint32_t curveQuantification);
		inline static ProjectTime count(const Track* ptr, uint32_t curveQuantification);
		inline static ProjectTime count(const Label* ptr, uint32_t curveQuantification);
		inline static ProjectTime count(const Curve* ptr, uint32_t curveQuantification);
		inline static ProjectTime count(const Note* ptr, uint32_t curveQuantification);
		inline static ProjectTime count(const Wave* ptr, uint32_t curveQuantification);
		inline static ProjectTime count(const DPoint* ptr, uint32_t curveQuantification);
	};
}