﻿#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
    class VSAPI IniTokeniser final : public juce::CodeTokeniser
    {
    public:
        IniTokeniser();
        ~IniTokeniser() override;

        int readNextToken(juce::CodeDocument::Iterator&) override;
        juce::CodeEditorComponent::ColourScheme getDefaultColourScheme() override;

        enum TokenType
        {
            tokenType_error = 0,
            tokenType_comment,
            tokenType_keyword,
            tokenType_operator,
            tokenType_identifier,
            tokenType_integer,
            tokenType_float,
            tokenType_string,
            tokenType_bracket,
            tokenType_punctuation
        };

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IniTokeniser)
    };
}