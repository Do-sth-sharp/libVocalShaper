#include "JsonTokeniser.h"

namespace vocalshaper {
    struct JsonTokeniserFunctions
    {
        static bool isReservedKeyword(juce::String::CharPointerType token, const int tokenLength) noexcept
        {
            static const char* const keywords2Char[] =
            { nullptr };

            static const char* const keywords3Char[] =
            { nullptr };

            static const char* const keywords4Char[] =
            { "null", "true", nullptr };

            static const char* const keywords5Char[] =
            { "false", nullptr };

            static const char* const keywords6Char[] =
            { nullptr };

            static const char* const keywordsOther[] =
            { nullptr };

            const char* const* k;

            switch (tokenLength)
            {
            case 2:   k = keywords2Char; break;
            case 3:   k = keywords3Char; break;
            case 4:   k = keywords4Char; break;
            case 5:   k = keywords5Char; break;
            case 6:   k = keywords6Char; break;

            default:
                if (tokenLength < 2 || tokenLength > 16)
                    return false;

                k = keywordsOther;
                break;
            }

            for (int i = 0; k[i] != nullptr; ++i)
                if (token.compare(juce::CharPointer_ASCII(k[i])) == 0)
                    return true;

            return false;
        }

        template <typename Iterator>
        static int parseIdentifier(Iterator& source) noexcept
        {
            int tokenLength = 0;
            juce::String::CharPointerType::CharType possibleIdentifier[100] = {};
            juce::String::CharPointerType possible(possibleIdentifier);

            while (juce::CppTokeniserFunctions::isIdentifierBody(source.peekNextChar()))
            {
                auto c = source.nextChar();

                if (tokenLength < 20)
                    possible.write(c);

                ++tokenLength;
            }

            if (tokenLength > 1 && tokenLength <= 16)
            {
                possible.writeNull();

                if (isReservedKeyword(juce::String::CharPointerType(possibleIdentifier), tokenLength))
                    return JsonTokeniser::tokenType_keyword;
            }

            return JsonTokeniser::tokenType_identifier;
        }

        template <typename Iterator>
        static void skipComment(Iterator& source) noexcept
        {
            bool lastWasStar = false;

            for (;;)
            {
                auto c = source.nextChar();

                if (c == 0 || (c == '/' && lastWasStar))
                    break;

                lastWasStar = (c == '*');
            }
        }

        template <typename Iterator>
        static int readNextToken(Iterator& source)
        {
            source.skipWhitespace();

            auto firstChar = source.peekNextChar();

            switch (firstChar)
            {
            case 0:
                break;

            case '0':   case '1':   case '2':   case '3':   case '4':
            case '5':   case '6':   case '7':   case '8':   case '9':
            case '.':
            {
                auto result = juce::CppTokeniserFunctions::parseNumber(source);

                if (result == JsonTokeniser::tokenType_error)
                {
                    source.skip();

                    if (firstChar == '.')
                        return JsonTokeniser::tokenType_punctuation;
                }

                return result;
            }

            case ',':
            case ':':
                source.skip();
                return JsonTokeniser::tokenType_punctuation;

            case '{':   case '}':
            case '[':   case ']':
                source.skip();
                return JsonTokeniser::tokenType_bracket;

            case '"':
            case '\'':
                juce::CppTokeniserFunctions::skipQuotedString(source);
                return JsonTokeniser::tokenType_string;

            case '/':
            {
                source.skip();
                auto nextChar = source.peekNextChar();

                if (nextChar == '/')
                {
                    source.skipToEndOfLine();
                    return JsonTokeniser::tokenType_comment;
                }
                if (nextChar == '*')
                {
                    source.skip();
                    skipComment(source);
                    return JsonTokeniser::tokenType_comment;
                }

                return JsonTokeniser::tokenType_error;
            }

            default:
                if (juce::CppTokeniserFunctions::isIdentifierStart(firstChar))
                    return parseIdentifier(source);

                source.skip();
                break;
            }

            return JsonTokeniser::tokenType_error;
        }
    };

    //==============================================================================
    JsonTokeniser::JsonTokeniser() {}
    JsonTokeniser::~JsonTokeniser() {}

    int JsonTokeniser::readNextToken(juce::CodeDocument::Iterator& source)
    {
        return JsonTokeniserFunctions::readNextToken(source);
    }

    juce::CodeEditorComponent::ColourScheme JsonTokeniser::getDefaultColourScheme()
    {
        static const juce::CodeEditorComponent::ColourScheme::TokenType types[] =
        {
            { "Error",          juce::Colour(0xffcc0000) },
            { "Comment",        juce::Colour(0xff3c3c3c) },
            { "Keyword",        juce::Colour(0xff0000cc) },
            { "Operator",       juce::Colour(0xff225500) },
            { "Identifier",     juce::Colour(0xff000000) },
            { "Integer",        juce::Colour(0xff880000) },
            { "Float",          juce::Colour(0xff885500) },
            { "String",         juce::Colour(0xff990099) },
            { "Bracket",        juce::Colour(0xff000055) },
            { "Punctuation",    juce::Colour(0xff004400) }
        };

        juce::CodeEditorComponent::ColourScheme cs;

        for (auto& t : types)
            cs.set(t.name, juce::Colour(t.colour));

        return cs;
    }
}