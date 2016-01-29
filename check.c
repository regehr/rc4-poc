#include <assert.h>

#include "check.h"

void check(int *addr, int val) {
  assert(*addr == val);
}
