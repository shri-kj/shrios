#include "global.h"
#include "trade.h"
#include "constants/trade.h"

int GetGameProgressForLinkTrade(void)
{
    return TRADE_BOTH_PLAYERS_READY;
}

void CB2_StartCreateTradeMenu(void)
{
}

void CB2_LinkTrade(void)
{
}

int CanRegisterMonForTradingBoard(struct RfuGameCompatibilityData player, u16 species2, u16 species, bool8 isModernFatefulEncounter)
{
    return CANT_TRADE_INVALID_MON;
}

int GetUnionRoomTradeMessageId(struct RfuGameCompatibilityData player, struct RfuGameCompatibilityData partner, u16 playerSpecies2, u16 partnerSpecies, u8 requestedType, u16 playerSpecies, bool8 isModernFatefulEncounter)
{
    return UR_TRADE_MSG_NONE;
}

int CanSpinTradeMon(struct Pokemon *mon, u16 monIdx)
{
    return CANT_TRADE_INVALID_MON;
}

void InitTradeSequenceBgGpuRegs(void)
{
}

void LinkTradeDrawWindow(void)
{
}

void LoadTradeAnimGfx(void)
{
}

void DrawTextOnTradeWindow(u8 windowId, const u8 *str, u8 speed)
{
}
