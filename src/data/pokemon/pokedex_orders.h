// Stubbed Pokédex ordering.
#include "global.h"
#include "constants/pokedex.h"
#include "constants/pokemon.h"

const u16 gHoennToNationalOrder[HOENN_DEX_COUNT + 1] = { [0 ... HOENN_DEX_COUNT] = NATIONAL_DEX_NONE };
const u16 gNationalToHoennOrder[NATIONAL_DEX_COUNT + 1] = { [0 ... NATIONAL_DEX_COUNT] = HOENN_DEX_NONE };
const u16 gRegionalDexCount[] = { 0 };

const u16 gPokedexOrder_Alphabetical[NUM_SPECIES - 1] = { [0 ... (NUM_SPECIES - 2)] = NATIONAL_DEX_NONE };
const u16 gPokedexOrder_Weight[NATIONAL_DEX_COUNT] = { [0 ... (NATIONAL_DEX_COUNT - 1)] = NATIONAL_DEX_NONE };
const u16 gPokedexOrder_Height[NATIONAL_DEX_COUNT] = { [0 ... (NATIONAL_DEX_COUNT - 1)] = NATIONAL_DEX_NONE };
