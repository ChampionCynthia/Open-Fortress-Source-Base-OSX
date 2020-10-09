// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFObjectiveResource becomes the g_pObjectiveResource global,
//      communicates # of control points client<->server.
// Author(s): Nopey
//
// The following issue describes the Live TF2 contents of this class
// https://github.com/openfortress/Open-Fortress-Source-Base/issues/10
// TL;DR: It's all MvM.
//OFSTATUS: INCOMPLETE. Missing MvM, and some graphic/audio things.

#pragma once
#include "dbg.h"

#ifdef CLIENT_DLL
#include "c_team_objectiveresource.h"
#define CBaseTeamObjectiveResource C_BaseTeamObjectiveResource
#else
#include "team_objectiveresource.h"
#endif

class COFObjectiveResource: public CBaseTeamObjectiveResource {
public:
    DECLARE_CLASS(COFObjectiveResource, CBaseTeamObjectiveResource);
    DECLARE_NETWORKCLASS();
#ifdef CLIENT_DLL
    //OFTODO: Reverse engineer C_TFObjectiveResource::GetGameSpecificCPCappingSwipe & co
    // (addresses 0006f136-006f151d of client.dylib)
#else
	DECLARE_DATADESC();
#endif
};

// Grabs the one from team_objectiveresource.h, downcast it.
inline COFObjectiveResource *OFTeamObjectiveResource()
{
    return assert_cast<COFObjectiveResource *>(ObjectiveResource());
}
