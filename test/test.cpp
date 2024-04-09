#include <AK/PublicMacros.h>

import AK;

IterationDecision foo() {
  return IterationDecision::Break;
}

int main() {
  return static_cast<RemoveConst<const int>>(foo());
}
