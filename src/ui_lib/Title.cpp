//
// Purpur Tentakel
// 19.09.2022
//

#include "Title.hpp"
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>
#include <helper/HRandom.hpp>

void Title::RenderTitle(app::AppContext_ty_c appContext) {
    for (size_t i = 0; i < m_title->size(); ++i) {
        DrawTextEx(
                *(appContext.assetManager.GetFont()),
                m_title->at(i).c_str(),
                Vector2(m_collider.x, m_collider.y + m_fontSize * static_cast<float>(i)),
                m_fontSize,
                0.0f,
                WHITE
        );
    }
}

void Title::RenderTitleSequence(app::AppContext_ty_c appContext) {
    size_t localCharCount{ 0 };
    std::string dummyText{};
    size_t i{ 0 };
    for (; i < m_title->size(); ++i) {
        dummyText = m_title->at(i);
        if (localCharCount + dummyText.size() > m_charCount) {
            dummyText = dummyText.substr(0, m_charCount - localCharCount);
        }

        DrawTextEx(
                *(appContext.assetManager.GetFont()),
                dummyText.c_str(),
                Vector2(m_collider.x, m_collider.y + m_fontSize * static_cast<float>(i)),
                m_fontSize,
                0.0f,
                WHITE
        );
        localCharCount += dummyText.size();
        if (localCharCount >= m_charCount) {
            break;
        }
    }

    auto& random = hlp::Random::GetInstance();
    float const prefixPosition{ m_collider.x
                                + (static_cast<float>(dummyText.size())
                                   * MeasureTextEx(*(appContext.assetManager.GetFont()), "a", m_fontSize, 0.0f).x) };

    DrawTextEx(
            *(appContext.assetManager.GetFont()),
            m_postFixes.at(random.random(m_postFixes.size())).c_str(),
            Vector2(prefixPosition, m_collider.y + m_fontSize * static_cast<float>(i)),
            m_fontSize,
            0.0f,
            WHITE
    );

    if (not dummyText.empty()) {
        if (dummyText.at(dummyText.size() - 1) != ' ') {
            eve::PlaySoundEvent event{ SoundType::TEXT };
            appContext.eventManager.InvokeEvent(event);
        }
    }

    ++m_charCount;
    if (m_charCount >= m_maxCharCount) {
        TitleFinish(appContext);
    }
}

void Title::MeasureTitleLength() {
    m_maxCharCount = 0;
    for (auto const& s : *m_title) {
        m_maxCharCount += s.size();
    }
}

void Title::RecalculateCollider(app::AppContext_ty_c appContext) {
    Resolution_ty_c resolution{ appContext.GetResolution() };
    m_fontSize = resolution.y * m_size.y / static_cast<float>(m_title->size());

    std::string title{};
    for (auto const& line : *m_title) {
        title += line + '\n';
    }
    title.pop_back();

    Vector2 textSize = MeasureTextEx(*(appContext.assetManager.GetFont()), title.c_str(), m_fontSize, 0.0f);
    float size{ textSize.x / resolution.x };

    while (m_size.x < size) {
        --m_fontSize;
        textSize = MeasureTextEx(*(appContext.assetManager.GetFont()), title.c_str(), m_fontSize, 0.0f);
        size = textSize.x / resolution.x;
    }

    m_size.x = size;
}

void Title::TitleFinish(app::AppContext_ty_c appContext) {
    m_titleFinish = true;
    eve::PlaySoundEvent event{ SoundType::ACCEPTED };
    appContext.eventManager.InvokeEvent(event);
}

Title::Title(Vector2 const pos, Vector2 const size, Alignment const alignment, bool const drawTitle)
    : UIElement{ pos, size, alignment },
      m_titleFinish{ !drawTitle } {

    app::AppContext_ty appContext{ app::AppContext::GetInstance() };
    m_title = appContext.assetManager.GetTitle();
    MeasureTitleLength();
    RecalculateCollider(appContext);
}

void Title::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    bool const skipTitle{ hlp::IsBackInputPressed() and !m_titleFinish };
    if (skipTitle) {
        TitleFinish(appContext);
        return;
    }
}

void Title::Render(app::AppContext_ty_c appContext) {
    // Update here to make sure the value ist correct
    m_lastFinishedTitle = m_titleFinish;

    if (!m_titleFinish) {
        RenderTitleSequence(appContext);
    } else {
        RenderTitle(appContext);
    }
}

void Title::Resize(app::AppContext_ty_c appContext) {

    RecalculateCollider(appContext);
    UIElement::Resize(appContext);
}

bool Title::HasFinishedTitle() const {
    return m_titleFinish;
}

bool Title::IsTitleFinished() const {
    return m_lastFinishedTitle != m_titleFinish;
}
