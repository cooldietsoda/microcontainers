#include <microcontainers/set.h>
#include <DamnTest/damntest.h>
#include <cstdio>
#include <cstdlib>

void insertOverflow() {
  using namespace microcontainers::set::unordered;
  const int capacity = 4;
  FixedSizeInPlaceAllocated<char, int, capacity> set;
  DAMN_ASSERT(set.insert('a'));
  DAMN_ASSERT(set.insert('b'));
  DAMN_ASSERT(set.insert('c'));
  DAMN_ASSERT(set.insert('d'));

  DAMN_ASSERT(!set.insert('e'));
}

void valuePresent() {
  using namespace microcontainers::set::unordered;
  const int capacity = 4;
  FixedSizeInPlaceAllocated<char, int, capacity> set;
  DAMN_ASSERT(set.insert('a'));
  DAMN_ASSERT(set.insert('b'));
  DAMN_ASSERT(set.insert('c'));
  DAMN_ASSERT(set.insert('d'));

  DAMN_ASSERT(set.hasValue('b'));
  DAMN_ASSERT(set.hasValue('c'));
}

void iteratorIncrement() {
  using namespace microcontainers::set::unordered;
  const int capacity = 4;
  FixedSizeInPlaceAllocated<char, int, capacity> set;
  DAMN_ASSERT(set.insert('a'));
  DAMN_ASSERT(set.insert('b'));
  DAMN_ASSERT(set.insert('c'));
  DAMN_ASSERT(set.insert('d'));

  auto itBegin = set.begin();
  auto itEnd = set.end();

  DAMN_ASSERT(*itBegin == 'a'); ++itBegin;
  DAMN_ASSERT(*itBegin == 'b'); ++itBegin;
  DAMN_ASSERT(*itBegin == 'c'); ++itBegin;
  DAMN_ASSERT(*itBegin == 'd'); ++itBegin;
  DAMN_ASSERT(itBegin == itEnd);
}

namespace DamnTest {
const char* getTestSuiteName() {
  return "FixedSizeSerialAlignedSet";
}

void puts(const char* msg) {
  printf("%s", msg);
}

void exit(int status) {
  ::exit(status);
}

void putTestCases() {
  addTestCase("insertOverflow", insertOverflow);
  addTestCase("valuePresent", valuePresent);
  addTestCase("iteratorIncrement", iteratorIncrement);
}

bool preTestCase() {
  return true;
}

bool postTestCase() {
  return true;
}

bool preTestSuite() {
  return true;
}

bool postTestSuite() {
  return true;
}
}
