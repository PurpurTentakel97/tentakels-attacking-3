//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include <event/EventListener.hpp>
#include <helper/HLayeredVector.hpp>
#include <helper/HUIAlias.hpp>
#include <vector>


class Focus final : public eve::EventListener {
private:
    Focusable_ty_raw m_currentFocus{ nullptr };
    HLayeredVector<Focusable> m_focus;
    std::vector<Focusable_ty_raw> m_lastFocus;
    bool m_renderFocus{ false };

    size_t m_PopUpLayerCounter{ 0 };
    HLayeredVector<Focusable> m_addElementRequest;
    HLayeredVector<Focusable> m_removeElementRequest;
    HLayeredVector<Focusable> m_toSelectRequest;
    std::vector<bool> m_toAddOrDelete;

    [[nodiscard]] bool HasAnyEnabledElements() const;

    void UnFocusAllAtTopLayer();

    [[nodiscard]] Focusable_ty_raw GetFirstFocus();

    [[nodiscard]] Focusable_ty_raw GetLastFocus();

    [[nodiscard]] Focusable_ty_raw GetNextFocus();

    [[nodiscard]] Focusable_ty_raw GetPreviousFocus();

    void SetInitialFocus();

    void SetNextFocus();

    void SetPreviousFocus();

    [[nodiscard]] bool IsExistingFocus(Focusable_ty_raw focusable);

    void SetSpecificFocus(Focusable_ty_raw focusable);

    void SetSpecificNormalFocus(Focusable_ty_raw focusable);

    void SetSpecificPopUpFocus(Focusable_ty_raw focusable);

    void AddLayer();

    void AddNormalLayer();

    void AddPopUpLayer();

    void DeleteLayer(bool setNewFocus = true);

    void DeleteNormalLayer();

    void DeletePopUpLayer();

    void Clear();

    void AddElement(Focusable_ty_raw focusable, bool setNewFocus = true);

    void AddNormalElement(Focusable_ty_raw focusable);

    void AddPopUpElement(Focusable_ty_raw focusable);

    void DeleteElement(Focusable_ty_raw focusable, bool setNewFocus = true);

    void DeleteNormalElement(Focusable_ty_raw focusable);

    void DeletePopUpElement(Focusable_ty_raw focusable);

    void SetLayerAfterPopUp();

    void CheckNewID(unsigned int newID);

public:
    Focus();

    void OnEvent(eve::Event const& event) override;

    void CheckAndUpdate();

    void Render();
};
