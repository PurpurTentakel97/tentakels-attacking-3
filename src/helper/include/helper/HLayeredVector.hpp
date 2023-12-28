//
// Purpur Tentakel
// 02.09.2022
//

#pragma once
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


template<class T>
class HLayeredVector final {
private:
    std::vector<std::vector<T*>> m_elements;
    size_t m_layer{ 0 };

    [[nodiscard]] bool IsValidIndex(int const index) const {
        return { index >= 0 && index < m_elements.at(m_layer).size() };
    }

    [[nodiscard]] std::vector<T*>& CurrentLayer() {
        return m_elements.at(m_layer);
    }

    [[nodiscard]] std::vector<T*> const& CurrentLayer() const {
        return m_elements.at(m_layer);
    }

public:
    HLayeredVector() {
        AddLayer();
    }
    HLayeredVector(HLayeredVector const&) = default;
    HLayeredVector(HLayeredVector&&) = default;
    HLayeredVector& operator=(HLayeredVector const&) = default;
    HLayeredVector& operator=(HLayeredVector&&) = default;


    void AddLayer() {
        std::vector<T*> newVector{};
        m_elements.push_back(newVector);
        m_layer = m_elements.size() - 1;
    }

    void RemoveLayer() {
        m_elements.pop_back();

        if (m_elements.size() <= 0) {
            AddLayer();
        }

        m_layer = m_elements.size() - 1;
    }

    void Clear() {
        m_elements.clear();
        AddLayer();
    }


    void AddElement(T* const element) {
        CurrentLayer().push_back(element);
    }

    void RemoveElement(T* const element) {
        auto& currentLayer{ CurrentLayer() };
        currentLayer.erase(std::remove(currentLayer.begin(), currentLayer.end(), element), currentLayer.end());
    }

    void RemoveElement(int const index) {
        if (!IsValidIndex(index)) {
            throw std::out_of_range(std::to_string(index) + " out of Range");
        }
        CurrentLayer().erase(CurrentLayer().begin() + index);
    }

    [[nodiscard]] T const* const* begin() const {
        return CurrentLayer().data();
    }

    [[nodiscard]] T** begin() {
        return CurrentLayer().data();
    }

    [[nodiscard]] T const* const* end() const {
        return CurrentLayer().data() + CurrentLayer().size();
    }

    [[nodiscard]] T** end() {
        return CurrentLayer().data() + CurrentLayer().size();
    }

    [[nodiscard]] size_t size() const {
        return CurrentLayer().size();
    }

    [[nodiscard]] size_t size() {
        return CurrentLayer().size();
    }

    [[nodiscard]] T* At(int const index) {
        if (!IsValidIndex(index)) {
            throw std::out_of_range(std::to_string(index) + " out of Range");
        }

        return CurrentLayer().at(index);
    }

    [[nodiscard]] T* operator[](int const index) {
        return At(index);
    }
};
