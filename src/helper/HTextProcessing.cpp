//
// Purpur Tentakel
// 25.09.2022
//

#include "HTextProcessing.h"
#include "AppContext.hpp"
#include "CustomRaylib.hpp"
#include "ui_lib/Alignment.h"
#include <cassert>

[[nodiscard]] std::vector<std::string> GetSerializedText(std::string const& text) {
    size_t lhs{ 0 };
    size_t rhs{ 0 };
    std::vector<std::string> toReturn;

    while (true) {
        rhs = text.find_first_of('\n', rhs + 1);
        if (rhs == std::string::npos) {
            toReturn.push_back(text.substr(lhs));
            break;
        }

        toReturn.push_back(text.substr(lhs, rhs - lhs));
        lhs = rhs + 1;
    }

    return toReturn;
}
[[nodiscard]] std::string GetStringFromVector(std::vector<std::string> const& slicedText) {

    std::string toReturn;

    for (auto const& s : slicedText) {
        toReturn += s;
        toReturn += '\n';
    }
    toReturn.pop_back();

    return toReturn;
}


void BreakText(std::string& toBreak, float fontSize, float length, AppContext_ty_c appContext) {
    size_t lhs{ 0 };
    size_t rhs{ 0 };

    while (true) {
        rhs = toBreak.find_first_of(' ', rhs + 1);
        if (rhs == std::string::npos) {
            break;
        }

        std::string line{ toBreak.c_str() + lhs, rhs - lhs };
        Vector2 textSize{ MeasureTextEx(*(appContext.assetManager.GetFont()), line.data(), fontSize, 0.0f) };

        if (textSize.x > length) {
            rhs = toBreak.find_last_of(' ', rhs - 1);
            if (rhs == std::string::npos) {
                rhs = toBreak.find_first_of(' ');
                if (rhs == std::string::npos) {
                    break;
                }
            }
            toBreak.at(rhs) = '\n';
            lhs = rhs + 1;
        }
    }
}

std::vector<std::string> BreakTextInVector(std::string const& toBreak, float fontSize, float length) {
    auto getTextLength = [fontSize](std::string const& text) -> float {
        Vector2 textSize =
                MeasureTextEx(*(AppContext::GetInstance().assetManager.GetFont()), text.c_str(), fontSize, 0.0f);
        return textSize.x;
    };

    size_t lhs{ 0 };
    size_t rhs{ 0 };
    std::vector<std::string> toReturn;


    while (true) {
        rhs = toBreak.find_first_of(' ', rhs + 1);


        if (rhs == std::string::npos) {
            toReturn.push_back(toBreak.substr(lhs, rhs - lhs));
            break;
        }

        std::string line{ toBreak.c_str() + lhs, rhs + 1 - lhs };
        auto const textLength{ getTextLength(line) };

        if (textLength >= length) {
            rhs = toBreak.find_last_of(' ', rhs - 1);
            if (rhs == std::string::npos) {
                rhs = toBreak.find_first_of(' ');
                if (rhs == std::string::npos) {
                    toReturn.push_back(toBreak.substr(lhs, rhs - lhs));
                    break;
                }
            }
            toReturn.push_back(toBreak.substr(lhs, rhs - lhs));
            lhs = rhs + 1;
        }
    }

    return toReturn;
}

float GetElementTextHeight(Vector2 const& relativeSize, float absoluteHeight) {
    return { relativeSize.y * absoluteHeight };
}

std::string
GetPrintableTextInCollider(std::string const& text, float fontSize, Rectangle collider, AppContext_ty_c appContext) {
    auto constants = appContext.constants.textProcessing;
    Vector2 textSize{
        MeasureTextEx(*(appContext.assetManager.GetFont()), (text + constants.cursor).c_str(), fontSize, 0.0f)
    };
    if ((textSize.x + constants.cursorOffset) < collider.width) {
        return text;
    }

    std::string toReturn{ text };
    std::string toCheck{ constants.prefix + text + constants.cursor };

    do {
        if (toReturn.size() == 0) {
            break;
        }
        toReturn = toReturn.substr(1, toReturn.size());
        toCheck = constants.prefix + toReturn + constants.cursor;
        textSize = MeasureTextEx(*(appContext.assetManager.GetFont()), toCheck.c_str(), fontSize, 0.0f);
    } while (textSize.x + constants.cursorOffset >= collider.width);

    return { constants.prefix + toReturn };
}
std::string GetPrintablePlaceholderTextInCollider(
        std::string const& text,
        float fontSize,
        Rectangle collider,
        AppContext_ty_c appContext
) {
    auto const constants{ appContext.constants.textProcessing };
    Vector2 textSize{ MeasureTextEx(*(appContext.assetManager.GetFont()), text.c_str(), fontSize, 0.0f) };
    if ((textSize.x + constants.cursorOffset) < collider.width) {
        return text;
    }

    std::string toReturn{ text };
    std::string toCheck{ constants.prefix + text };

    do {
        toReturn = toReturn.substr(0, toReturn.size() - 1);
        toCheck = constants.prefix + toReturn;
        textSize = MeasureTextEx(*(appContext.assetManager.GetFont()), toCheck.c_str(), fontSize, 0.0f);
    } while (textSize.x + constants.cursorOffset >= collider.width);

    return { toReturn + constants.prefix };
}

void StripString(std::string& toStrip) {
    size_t const pos1{ toStrip.find_first_not_of(' ') };

    if (pos1 == std::string::npos) {
        toStrip = std::string();
        return;
    }

    size_t const pos2{ toStrip.find_last_not_of(' ') };
    toStrip = toStrip.substr(pos1, pos2 - pos1 + 1);
}

Vector2
GetVerticalAlignedTextPosition(std::string const& text, float fontSize, Rectangle collider, Alignment alignment) {

    TextAlignment const textAlignment{ GetVerticalTextAlignment(alignment) };

    if (textAlignment == TextAlignment::TOP) {
        return { collider.x, collider.y };
    }

    AppContext_ty_c appContext{ AppContext::GetInstance() };
    Vector2 const textSize{ MeasureTextEx(*(appContext.assetManager.GetFont()), text.c_str(), fontSize, 0.0f) };

    if (collider.height < textSize.y) {
        return { collider.x, collider.y };
    }

    float difference{ collider.height - textSize.y };
    difference = textAlignment == TextAlignment::MID ? difference / 2 : difference;

    return { collider.x, collider.y + difference };
}

std::vector<float>
GetVerticalAlignedOffset(std::vector<std::string> text, float fontSize, Rectangle collider, Alignment alignment) {

    AppContext_ty_c appContext{ AppContext::GetInstance() };
    TextAlignment const textAlignment{ GetVerticalTextAlignment(alignment) };
    std::vector<float> toReturn;

    assert(text.size() > 0);

    float value{ 0.0 };
    Vector2 const textSize{ MeasureTextEx(*(appContext.assetManager.GetFont()), text.at(0).c_str(), fontSize, 0.0f) };

    if (textAlignment == TextAlignment::TOP) {
        value = 0.0f;
    } else {

        float const offset{ collider.height - (textSize.y * static_cast<float>(text.size())) };

        if (textAlignment == TextAlignment::MID) {
            value = offset / 2;
        } else {
            value = offset;
        }
    }

    for (size_t i = 0; i < text.size(); ++i) {
        toReturn.push_back(value);
        value += textSize.y;
    }

    return toReturn;
}

std::string GetHorizontalAlignedText(std::string const& text, Rectangle collider, float fontSize, Alignment alignment) {

    TextAlignment const textAlignment{ GetHorizontalTextAlignment(alignment) };

    if (textAlignment == TextAlignment::LEFT) {
        return text;
    }

    AppContext_ty_c appContext{ AppContext::GetInstance() };

    Vector2 const spaceSize{ MeasureTextEx(*(appContext.assetManager.GetFont()), " ", fontSize, 0.0f) };

    std::vector<std::string> const slicedText{ GetSerializedText(text) };
    std::vector<std::string> alignedSlicedText;

    for (auto const& t : slicedText) {
        Vector2 const textSize{ MeasureTextEx(*(appContext.assetManager.GetFont()), t.c_str(), fontSize, 0.0f) };

        if (collider.width < textSize.x) {
            alignedSlicedText.push_back(t);
            continue;
        }

        float difference{ collider.width - textSize.x };
        difference = textAlignment == TextAlignment::MID ? difference / 2 : difference;

        char const spaceCount{ static_cast<char>(difference / spaceSize.x) };

        std::string entry{ spaceCount, ' ' };
        entry += t;
        alignedSlicedText.push_back(entry);
    }


    std::string const toReturn{ GetStringFromVector(alignedSlicedText) };
    return toReturn;
}

std::vector<float>
GetHorizontalAlignedOffset(std::vector<std::string> text, Rectangle collider, float fontSize, Alignment alignment) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    TextAlignment const textAlignment{ GetHorizontalTextAlignment(alignment) };

    std::vector<float> toReturn;

    if (textAlignment == TextAlignment::LEFT) {
        for (size_t i = 0; i < text.size(); ++i) {
            toReturn.push_back(0.0f);
        }
        return toReturn;
    }

    for (auto const& line : text) {

        Vector2 const textSize{ MeasureTextEx(*(appContext.assetManager.GetFont()), line.c_str(), fontSize, 0.0f) };

        if (collider.width < textSize.x) {
            toReturn.push_back(0.0f);
            continue;
        }

        float difference{ collider.width - textSize.x };
        difference = textAlignment == TextAlignment::MID ? difference / 2 : difference;

        toReturn.push_back(difference);
    }

    return toReturn;
}

void DrawTextWithOutline(std::string const& text, Vector2 position, float size, Color color, bool background) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    // background text
    if (Colors::NeedBackground(color) and background) {
        DrawTextEx(
                *(appContext.assetManager.GetFont()),
                text.c_str(),
                {
                        position.x - 1,
                        position.y - 1,
                },
                size,
                0.0f,
                TEXT_WHITE
        );
        DrawTextEx(
                *(appContext.assetManager.GetFont()),
                text.c_str(),
                {
                        position.x + 1,
                        position.y - 1,
                },
                size,
                0.0f,
                TEXT_WHITE
        );
        DrawTextEx(
                *(appContext.assetManager.GetFont()),
                text.c_str(),
                {
                        position.x - 1,
                        position.y + 1,
                },
                size,
                0.0f,
                TEXT_WHITE
        );
        DrawTextEx(
                *(appContext.assetManager.GetFont()),
                text.c_str(),
                {
                        position.x + 1,
                        position.y + 1,
                },
                size,
                0.0f,
                TEXT_WHITE
        );
    }
    // text
    DrawTextEx(*(appContext.assetManager.GetFont()), text.c_str(), position, size, 0.0f, color);
}
