//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include <event/EventListener.hpp>
#include <helper/HLayeredVector.hpp>
#include <helper/HUIAlias.hpp>
#include <vector>

/**
 * provides a focus system that can handle Focusable_ty_raw.
 */
class Focus final : public EventListener {
private:
    Focusable_ty_raw m_currentFocus{ nullptr }; ///< contains the current focus
    HLayeredVector<Focusable> m_focus;          ///< contains all focusable elements in layer
    std::vector<Focusable_ty_raw> m_lastFocus;  ///< stores the correct focus of the underlaying layers
    bool m_renderFocus{ false };                ///< contains if the focus gets rendered

    size_t m_PopUpLayerCounter{ 0 };               ///< contains the mount of popups that are in the focus layers
    HLayeredVector<Focusable> m_addElementRequest; ///< contains the elements to add if a popup ist currently active
    HLayeredVector<Focusable>
            m_removeElementRequest;              ///< contains the elements to remove if a popup ist currently active
    HLayeredVector<Focusable> m_toSelectRequest; ///< contains the elements to select if a popup ist currently active
    std::vector<bool>
            m_toAddOrDelete; ///< contains if the layer should be added or delete if a popup is currently active

    /**
	 * returns if the current layer has any enabled elements.
	 */
    [[nodiscard]] bool HasAnyEnabledElements() const;

    /**
	 * sets all focus elements at the top layer to false.
	 * sets the current focus to nullptr.
	 */
    void UnfocusAllAtTopLayer();
    /**
	 * calculates and returns the focus element with the smallest id.
	 */
    [[nodiscard]] Focusable_ty_raw GetFirstFocus();
    /**
	 * calculates and returns the focus element with the highest id.
	 */
    [[nodiscard]] Focusable_ty_raw GetLastFocus();
    /**
	 * calculates and returns the focus element with the next id.
	 */
    [[nodiscard]] Focusable_ty_raw GetNextFocus();
    /**
	 * calculates and returns the focus element with the previous id.
	 */
    [[nodiscard]] Focusable_ty_raw GetPreviousFocus();
    /**
	 * sets the initial focus.
	 */
    void SetInitialFocus();
    /**
	 * sets the next focus.
	 */
    void SetNextFocus();
    /**
	 * sets the previous focus.
	 */
    void SetPreviousFocus();
    /**
	 * checks and returns if the provided focus element is existing in the top layer.
	 */
    [[nodiscard]] bool IsExistingFocus(Focusable_ty_raw focusable);

    /**
	 * sets the provided focus active and the previous focus inactive.
	 */
    void SetSpecificFocus(Focusable_ty_raw focusable);
    /**
	 * sets the provided focus active and the previous focus inactive if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
    void SetSpecificNormalFocus(Focusable_ty_raw focusable);
    /**
	 * sets the provided focus active and the previous focus inactive.
	 */
    void SetSpecificPopUpFocus(Focusable_ty_raw focusable);

    /**
	 * adds a new layer to the focus vector.
	 * sets the current focus to nullptr.
	 * sets the render to false.
	 */
    void AddLayer();
    /**
	 * adds a new layer to the focus vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
    void AddNormalLayer();
    /**
	 * adds a new layer to the focus vector.
	 * increment the popup counter.
	 */
    void AddPopUpLayer();
    /**
	 * sets all elements to false.
	 * removed the current layer.
	 * sets a new focus if provided.
	 */
    void DeleteLayer(bool setNewFocus = true);
    /**
	 * deletes the current layer to the focus vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
    void DeleteNormalLayer();
    /**
	 * deletes the current layer to the focus vector.
	 * decrement the popup counter.
	 */
    void DeletePopUpLayer();
    /**
	 * clears the complete focus class.
	 * no data are remaining.
	 */
    void Clear();

    /**
	 * adds the provided focus element to the vector.
	 * sets a new active focus if provided. 
	 */
    void AddElement(Focusable_ty_raw focusable, bool setNewFocus = true);
    /**
	 * adds the provided focus element to the vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
    void AddNormalElement(Focusable_ty_raw focusable);
    /**
	 * adds the provided focus element always to the vector.
	 */
    void AddPopUpElement(Focusable_ty_raw focusable);
    /**
	 * deletes the provided focus element from the vector.
	 * sets a new active focus if provided.
	 */
    void DeleteElement(Focusable_ty_raw focusable, bool setNewFocus = true);
    /**
	 * deletes the provided focus element from the vector if no popup is active.
	 * otherwise the request is held back and executed when all popups are closed.
	 */
    void DeleteNormalElement(Focusable_ty_raw focusable);
    /**
	 * deletes the provided focus element always from the vector.
	 */
    void DeletePopUpElement(Focusable_ty_raw focusable);

    /**
	 * executes all requests that are hold back while a popup was active.
	 */
    void SetLayerAfterPopUp();

    /**
	 * check if the provided ID is already existing in the current layer.
	 * throw's an exception if so.
	 */
    void CheckNewID(unsigned int newID);

public:
    /**
	 * ctor.
	 * adds listener to the event system.
	 */
    Focus();

    /**
	 * receives all the events and calls the member functions.
	 */
    void OnEvent(Event const& event) override;

    /**
	 * focus logic.
	 */
    void CheckAndUpdate();
    /**
	 * render the focus.
	 */
    void Render();
};
