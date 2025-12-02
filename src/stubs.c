#include "global.h"
#include "trade.h"
#include "mail.h"
#include "window.h"
#include "event_data.h"
#include "contest_effect.h"
#include "party_menu.h"
#include "wild_encounter.h"
#include "constants/species.h"
#include "constants/trade.h"
#include "constants/party_menu.h"

// Trade-related globals
EWRAM_DATA struct Mail gTradeMail[PARTY_SIZE] = {0};
EWRAM_DATA u8 gSelectedTradeMonPositions[2] = {0};
const u16 gTradePlatform_Tilemap[1] = {0};
const struct WindowTemplate gTradeEvolutionSceneYesNoWindowTemplate = {0};

// Contest data stubs
const struct ContestEffect gContestEffects[1] = { {0} };
void (*const gContestEffectFuncs[])(void) = { NULL };

// Tutor/encounter stubs
const u16 gTutorMoves[TUTOR_MOVE_COUNT] = {0};
const struct WildPokemonHeader gWildMonHeaders[] = { {0} };

// Gender symbol text
const u8 gText_MaleSymbol4[] = "M";
const u8 gText_FemaleSymbol4[] = "F";
const u8 gText_GenderlessSymbol[] = "-";

// Script-exposed helpers
void RockSmashWildEncounter(void) { gSpecialVar_Result = FALSE; }
u16 GetTradeSpecies(void) { return SPECIES_NONE; }
u16 GetInGameTradeSpeciesInfo(void) { return SPECIES_NONE; }
void CreateInGameTradePokemon(void) {}
bool8 DoInGameTradeScene(void) { return FALSE; }
