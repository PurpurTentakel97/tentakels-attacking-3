//
// Purpur Tentakel
// 02.09.2022
//

#pragma once
#include <algorithm> // for std::remove
#include <vector>
#include <stdexcept>
#include <string>
#include <memory>

/**
 * deploys a vector where you can only access the last layer.
 * you can add and remove layer.
 * the other behavior ist similar so the std::vector.
 */
template<class T>
class LayeredVector final {
private:
	std::vector<std::vector<T*>> m_elements; ///< contains all elements in layers
	size_t m_layer{ 0 }; ///< contains the layer count as index

	/**
	 * checks if the index is in range of the vector.
	 */
	[[nodiscard]] bool IsValidIndex(int index) const {
		return { 
			index >= 0 && index < m_elements.at(m_layer).size() 
		};
	}
	/**
	 * returns the current layer auf the vector.
	 * always use this for accessing data in this vector.
	 */
	[[nodiscard]] std::vector<T*>& CurrentLayer() {
		return m_elements.at(m_layer);
	}
	/**
	 * same as CurrentLayer only in const.
	 */
	[[nodiscard]] std::vector<T*> const& CurrentLayer() const {
		return m_elements.at(m_layer);
	}

public:
	/**
	 * ctor.
	 * ass the first layer.
	 * the complete vector is only working with pointers.
	 */
	LayeredVector(){
		AddLayer();
	}
	LayeredVector(LayeredVector const&) = default;
	LayeredVector(LayeredVector&&) = default;
	LayeredVector& operator=(LayeredVector const&) = default;
	LayeredVector& operator=(LayeredVector&&) = default;

	/**
	 * adds a new layer to the vector.
	 * the previous layer can be accessed again if this layer was deleted.
	 * updates the layer count.
	 */
	void AddLayer() {
		std::vector<T*> newVector{ };
		m_elements.push_back(newVector);
		m_layer = m_elements.size()-1;
	}
	/**
	 * removes the current layer.
	 * the previous layer is now avaliere.
	 * if no layer is left: a default layer is generated.
	 */
	void RemoveLayer() {
		m_elements.pop_back();

		if (m_elements.size() <= 0) {
			AddLayer();
		}

		m_layer = m_elements.size() - 1;
	}
	/**
	 * clears all layers.
	 * generates a default layer.
	 */
	void Clear() {
		m_elements.clear();
		AddLayer();
	}

	/**
	 * add an element input the current layer.
	 */
	void AddElement(T* element) {
		CurrentLayer().push_back(element);
	}
	/**
	 * removes an element by element* from the current layer if it exists.
	 * else nothing happens.
	 */
	void RemoveElement(T* element) {
		auto& currentLayer{ CurrentLayer() };
		currentLayer.erase(std::remove(currentLayer.begin(), currentLayer.end(), element),
			currentLayer.end());
	}
	/**
	 * removes an element id from the current layer if it exists.
	 * else an exception is thrown.
	 */
	void RemoveElement(int index) {
		if (!IsValidIndex(index)) { throw std::out_of_range(std::to_string(index) + " out of Range"); }
		CurrentLayer().erase(CurrentLayer().begin() + index);
	}

	/**
	 * returns a pointer const of the current layer for interrating.
	 */
	[[nodiscard]] T const* const* begin() const {
		return CurrentLayer().data();
	}
	/**
	 * returns a pointer mut of the current layer for interrating.
	 */
	[[nodiscard]] T** begin() {
		return CurrentLayer().data();
	}
	/**
	 * returns a pointer const of the current layer for interrating.
	 */
	[[nodiscard]] T const* const* end() const {
		return CurrentLayer().data() + CurrentLayer().size();
	}
	/**
	 * returns a pointer mut of the current layer for interrating.
	 */
	[[nodiscard]] T** end() {
		return CurrentLayer().data() + CurrentLayer().size();
	}

	/**
	 * returns the size const of the current layer.
	 */
	[[nodiscard]] size_t size() const {
		return CurrentLayer().size();
	}
	/**
	 * returns the size mut of the current layer.
	 */
	[[nodiscard]] size_t size() {
		return CurrentLayer().size();
	}

	/**
	 * returns an element* by id of the current layer.
	 * else throws an exception.
	 */
	[[nodiscard]] T* At(int index) {
		if (!IsValidIndex(index)) { throw std::out_of_range(std::to_string(index) + " out of Range"); }

		return CurrentLayer().at(index);
	}
	/**
	 * returns an element* by id of the current layer without validating the index.
	 */
	[[nodiscard]] T* operator[](int index) {
		return At(index);
	}
};
