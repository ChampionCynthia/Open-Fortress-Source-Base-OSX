// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFObjectiveResource
// Author(s): Cherry!
//

#pragma once

#include "c_team_objectiveresource.h"

class C_OFObjectiveResource : public C_BaseTeamObjectiveResource
{
public:
	DECLARE_CLASS(C_OFObjectiveResource, C_BaseTeamObjectiveResource);
	DECLARE_CLIENTCLASS();

	virtual const char *GetGameSpecificCPCappingSwipe(int index, int iCappingTeam);
	virtual const char *GetGameSpecificCPBarFG(int index, int iOwningTeam);
	virtual const char *GetGameSpecificCPBarBG(int index, int iCappingTeam);
};