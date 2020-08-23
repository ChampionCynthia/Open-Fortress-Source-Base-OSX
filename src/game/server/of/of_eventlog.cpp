// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: 
// Author(s): Kaydemon, Nopey
//

//OFTODO: move player.h and usercmd.h includes into EventLog.h, because that's where they're used.
#include "cbase.h"
#include "player.h"
#include "usercmd.h"
#include "EventLog.h"

CEventLog g_OFEventLog;

IGameSystem* GameLogSystem()
{
	return &g_OFEventLog;
}