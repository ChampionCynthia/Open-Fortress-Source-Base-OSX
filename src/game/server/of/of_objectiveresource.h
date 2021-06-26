// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFObjectiveResource
// Author(s): Cherry!
//

#pragma once

#include "team_objectiveresource.h"

class COFObjectiveResource : public CBaseTeamObjectiveResource
{
public:
	DECLARE_CLASS(COFObjectiveResource, CBaseTeamObjectiveResource);
	DECLARE_SERVERCLASS();

	virtual void Spawn();
};