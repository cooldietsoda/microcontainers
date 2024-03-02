#pragma once
#include <cstdint>

namespace microcontainers {

template<typename T, typename SIZE_T, SIZE_T SIZE>
class FixedSizeSerialAlignedSet {

public:
  bool insert(const T& element) {
    for (SIZE_T i=0; i<SIZE; i++) {
      if (!m_usedElements[i]) {
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
  
private:
  T m_elements[SIZE];
  bool m_usedElements[SIZE];
};

}