// Stubbed TM/HM learnsets.
#include "global.h"
#include "constants/species.h"
#include "constants/pokemon.h"

#ifndef TMHM_LEARNSET_SIZE
#define TMHM_LEARNSET_SIZE 8
#endif

struct TMHMLearnset
{
    u32 as_u32s[TMHM_LEARNSET_SIZE];
};

const struct TMHMLearnset gTMHMLearnsets[NUM_SPECIES] = { { {0} } };
