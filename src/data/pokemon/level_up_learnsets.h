// Stubbed level-up learnsets.
#include "global.h"
#include "constants/pokemon.h"

#define LEVEL_UP_MOVE(lvl, move) ((lvl << 9) | move)
#define LEVEL_UP_END 0xFFFF

static const u16 sEmptyLevelUpLearnset[] = { LEVEL_UP_END };
