#include <microcontainers/set.h>

int main() {
  microcontainers::FixedSizeSerialAlignedSet<char, int, 10> set;
  set.insert('a');
  return 0;
}