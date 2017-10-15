//===-- Timer.cpp ---------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <chrono>

#include "klee/Config/Version.h"
#include "klee/Internal/Support/Timer.h"

#include "klee/Internal/System/Time.h"

using namespace klee;
using namespace llvm;

#if LLVM_VERSION_CODE >= LLVM_VERSION(4, 0)

WallTimer::WallTimer() {
  start = util::getWallTimeVal();
}

uint64_t WallTimer::check() {
  sys::TimePoint<> now = util::getWallTimeVal();
  return std::chrono::duration_cast<std::chrono::microseconds>(now -
    start).count();
}

#else

WallTimer::WallTimer() {
  start = util::getWallTimeVal();
}

uint64_t WallTimer::check() {
  std::chrono::duration<uint64_t> delta =
    std::chrono::duration_cast<std::chrono::duration<uint64_t>>(
        util::getWallTimeVal() - start);
  return delta.count();
}

#endif
