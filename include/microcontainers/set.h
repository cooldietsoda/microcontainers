#pragma once
#include <cstdint>
#include <cstring>

namespace microcontainers::set::unordered {

template<typename T, typename SIZE_T, SIZE_T CAPACITY>
class FixedSizeInPlaceAllocated {
public:
  struct Iterator {
    Iterator(FixedSizeInPlaceAllocated<T, SIZE_T, CAPACITY> &set, SIZE_T index) 
      : m_set(set), m_currentIndex(index) {
    }

    T& operator*() const {
      return m_set.m_elements[m_currentIndex];
    }

    T* operator->() {
      return &m_set.m_elements[m_currentIndex];
    }

    Iterator& operator++() { 
      if (m_currentIndex == CAPACITY-1) {
        m_currentIndex = CAPACITY;
        return *this;
      }

      for (SIZE_T i=m_currentIndex+1; i<CAPACITY; i++) {
        if (m_set.m_usedElements[i]) {
          m_currentIndex = i;
          return *this;
        }
      }

      return *this;
    }

    friend bool operator==(const Iterator& left, const Iterator& right) {
      return left.m_currentIndex == right.m_currentIndex;
    }

    friend bool operator!=(const Iterator& left, const Iterator& right) {
      return left.m_currentIndex != right.m_currentIndex;
    }  

  private:
      FixedSizeInPlaceAllocated& m_set;
      SIZE_T m_currentIndex;
  };

  Iterator begin() {
    SIZE_T startIndex = 0;

    for (SIZE_T i=0; i<CAPACITY; i++) {
      if (m_usedElements[i]) {
        startIndex = i;
        break;
      }
    }

    return Iterator(*this, startIndex);
  }

  Iterator end() {
    return Iterator(*this, CAPACITY);
  }

public:
  FixedSizeInPlaceAllocated() {
    memset(m_usedElements, 0, sizeof(m_usedElements));
  }

  bool insert(const T& element) {
    for (SIZE_T i=0; i<CAPACITY; i++) {
      if (!m_usedElements[i] && m_elements[i] != element) {
        m_elements[i] = element;
        m_usedElements[i] = true;
        return true;
      }
    }

    return false;
  }

  bool remove(SIZE_T index) {
    if (!m_usedElements[index]) {
      return false;
    }

    m_usedElements[index] = false;
    return true;
  }

  T& at(SIZE_T index) {
    return m_elements[index];
  }

  SIZE_T size() {
    SIZE_T n = 0;
    for (SIZE_T i=0; i<CAPACITY; i++) {
      if (m_usedElements[i]) {
        n++;
      }
    }

    return n;
  }

  SIZE_T capacity() {
    return CAPACITY;
  }

  bool hasValue(const T& value) {
    for (SIZE_T i=0; i<CAPACITY; i++) {
      if (m_usedElements[i] && m_elements[i] == value) {
        return true;
      }
    }

    return false;
  }
  
private:
  T m_elements[CAPACITY];
  bool m_usedElements[CAPACITY];

  friend struct Iterator;
};

}