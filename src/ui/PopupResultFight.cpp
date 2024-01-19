//
// Purpur Tentakel
// 06.07.2023
//

#include "PopupResultFight.hpp"
#include <app/AppContext.hpp>
#include <helper/HTextProcessing.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/CountingNumber.hpp>
#include <ui_lib/Text.hpp>


namespace ui {
    void FightResultPopup::Initialize() {
        // constants
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        auto constexpr leftX{ 0.25f };
        auto constexpr rightX{ 0.75f };
        auto Y{ 0.35f };
        auto const textSize{ hlp::GetElementTextHeight(m_size, 0.07f) };

        // subtitle
        std::string fightText{ "invalid" };
        auto const& object{ m_result.GetSpaceObjects().first };
        if (object.type == utl::SpaceObjectType::PLANET) {
            fightText = { appContext.languageManager.Text("ui_popup_fight_result_fight_at_planet", object.ID) };
        } else {
            fightText = { appContext.languageManager.Text(
                    "ui_popup_fight_result_fight_at_coordinates", object.position.x, object.position.y) };
        }

        auto const subtitle = std::make_shared<uil::Text>(hlp::GetElementPosition(m_pos, m_size, 0.6f, Y),
                                                          hlp::GetElementSize(m_size, 0.7f, textSize * 1.2f),
                                                          uil::Alignment::MID_MID,
                                                          uil::Alignment::MID_MID,
                                                          textSize * 1.2f,
                                                          fightText);
        m_elements.push_back(subtitle);

        Y += 0.15f;

        // player names
        auto player{ appContext.playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().first.ID) };
        auto playerName = std::make_shared<uil::Text>(hlp::GetElementPosition(m_pos, m_size, leftX, Y),
                                                      hlp::GetElementSize(m_size, 0.5f, textSize),
                                                      uil::Alignment::MID_MID,
                                                      uil::Alignment::MID_MID,
                                                      textSize,
                                                      player.GetName());
        playerName->SetColor(player.color);
        playerName->SetRenderBackground(true);
        m_elements.push_back(playerName);

        player     = { appContext.playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().second.ID) };
        playerName = std::make_shared<uil::Text>(hlp::GetElementPosition(m_pos, m_size, rightX, Y),
                                                 hlp::GetElementSize(m_size, 0.5f, textSize),
                                                 uil::Alignment::MID_MID,
                                                 uil::Alignment::MID_MID,
                                                 textSize,
                                                 player.GetName());
        playerName->SetColor(player.color);
        playerName->SetRenderBackground(true);
        m_elements.push_back(playerName);

        Y += 0.1f;

        // numbers
        auto firstNumber{ m_result.GetRounds().at(0).first };
        m_leftNumber = std::make_shared<uil::CountingNumber>(hlp::GetElementPosition(m_pos, m_size, leftX, Y),
                                                             hlp::GetElementSize(m_size, 0.5f, textSize * 1.5f),
                                                             uil::Alignment::MID_MID,
                                                             uil::Alignment::MID_MID,
                                                             textSize * 1.5f,
                                                             static_cast<int>(firstNumber));
        m_leftNumber->SetCallback([this](uil::CountingNumber::Type type, int from, int to, double time) {
            this->NextNumber(type, from, to, time, false);
        });
        m_elements.push_back(m_leftNumber);

        firstNumber   = { m_result.GetRounds().at(0).second };
        m_rightNumber = std::make_shared<uil::CountingNumber>(hlp::GetElementPosition(m_pos, m_size, rightX, Y),
                                                              hlp::GetElementSize(m_size, 0.5f, textSize * 1.5f),
                                                              uil::Alignment::MID_MID,
                                                              uil::Alignment::MID_MID,
                                                              textSize * 1.5f,
                                                              static_cast<int>(firstNumber));
        m_rightNumber->SetCallback([this](uil::CountingNumber::Type type, int from, int to, double time) {
            this->NextNumber(type, from, to, time, true);
        });
        m_elements.push_back(m_rightNumber);

        Y += 0.1f;

        // win text
        m_winText = std::make_shared<uil::Text>(hlp::GetElementPosition(m_pos, m_size, 0.5f, Y),
                                                hlp::GetElementSize(m_size, 0.8f, textSize * 1.5f),
                                                uil::Alignment::MID_MID,
                                                uil::Alignment::MID_MID,
                                                textSize * 1.5f,
                                                "");
        m_elements.push_back(m_winText);

        // button
        m_closeBtn = std::make_shared<uil::ClassicButton>(1,
                                                          hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.95f),
                                                          hlp::GetElementSize(m_size, 0.2f, 0.15f),
                                                          uil::Alignment::BOTTOM_MID,
                                                          appContext.languageManager.Text("helper_skip_big"),
                                                          app::SoundType::CLICKED_RELEASE_STD);
        m_closeBtn->SetOnClick([this]() { this->HandleButton(); });
        m_elements.push_back(m_closeBtn);
    }

    void FightResultPopup::NextNumber(bool const left) {
        if (m_finishedCounting) {
            return;
        }
        if (m_leftNumber->IsCounting() or m_rightNumber->IsCounting()) {
            return;
        }
        if (m_index >= m_result.GetRounds().size()) {
            m_finishedCounting = true;
            SetEnd();
            return;
        }

        auto constexpr time{ 1.5 };
        if (left) {
            m_leftNumber->CountTo(
                    uil::CountingNumber::ASYMPTOTIC, static_cast<int>(m_result.GetRounds().at(m_index).first), time);
        } else {
            m_rightNumber->CountTo(
                    uil::CountingNumber::ASYMPTOTIC, static_cast<int>(m_result.GetRounds().at(m_index).second), time);
        }

        ++m_index;
    }

    void FightResultPopup::NextNumber(uil::CountingNumber::Type, int, int, double, bool const left) {
        NextNumber(left);
    }

    void FightResultPopup::SetLastStep() {
        m_index = m_result.GetRounds().size() - 1;
        m_leftNumber->SetTo(static_cast<int>(m_result.GetRounds().at(m_index).first));
        m_rightNumber->SetTo(static_cast<int>(m_result.GetRounds().at(m_index).second));
        SetEnd();
    }

    void FightResultPopup::SetEnd() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        m_closeBtn->SetText(appContext.languageManager.Text("helper_next_big"));

        std::string dummy;
        if (m_result.GetRounds().at(m_result.GetRounds().size() - 1).first == 0) {
            dummy = app::AppContext::GetInstance()
                            .playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().second.ID)
                            .GetName();
            m_leftNumber->SetDefaultColor(RED);
        } else {
            dummy = app::AppContext::GetInstance()
                            .playerCollection.GetPlayerOrNpcByID(m_result.GetPlayer().first.ID)
                            .GetName();
            m_rightNumber->SetDefaultColor(RED);
        }

        m_winText->SetText(appContext.languageManager.Text("ui_popup_fight_result_win_text", dummy));
    }

    void FightResultPopup::HandleButton() {
        if (not m_finishedCounting) {
            m_finishedCounting = true;
            SetLastStep();
            return;
        }
        m_shouldClose = true;
        m_callback();
    }

    FightResultPopup::FightResultPopup(Vector2 const pos,
                                       Vector2 const size,
                                       uil::Alignment const alignment,
                                       utl::ResultFight result,
                                       callback_ty callback)
        : PopUp{ pos,           size,
                 alignment,     app::AppContext::GetInstance().languageManager.Text("helper_fight_big"),
                 s_emptyString, app::AssetType::EXCLAMATION_MARK },
          m_result{ std::move(result) },
          m_callback{ std::move(callback) } {

        Initialize();
        NextNumber(false);
    }
} // namespace ui
