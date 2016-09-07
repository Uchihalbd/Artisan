#ifndef ART_RUNTIME_TWODROID_UNPACK_DIAOS_UNPACK_H_
#define ART_RUNTIME_TWODROID_UNPACK_DIAOS_UNPACK_H_

#include <list>
#include <string>
#include <vector>

#include "interpreter/interpreter_common.h"

namespace gossip {

	void dexbuild(const art::DexFile*  df, const char* filename);
}

#endif