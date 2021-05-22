// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFObjectiveResource
// Author(s): Cherry!
//

#include "cbase.h"
#include "c_of_objectiveresource.h"
#include "of_shareddefs.h"

IMPLEMENT_CLIENTCLASS_DT(C_OFObjectiveResource, DT_OFObjectiveResource, COFObjectiveResource)
END_RECV_TABLE()

const char *C_OFObjectiveResource::GetGameSpecificCPCappingSwipe(int index, int iCappingTeam)
{
	switch (iCappingTeam)
	{
	default:
		return "sprites/obj_icons/icon_obj_cap_red";
		break;
	case OF_TEAM_RED:
		return "sprites/obj_icons/icon_obj_cap_red";
		break;
	case OF_TEAM_BLUE:
		return "sprites/obj_icons/icon_obj_cap_blu";
		break;
	}
}

const char *C_OFObjectiveResource::GetGameSpecificCPBarFG(int index, int iOwningTeam)
{
	switch (iOwningTeam)
	{
	default:
		return "progress_bar";
		break;
	case OF_TEAM_RED:
		return "progress_bar_red";
		break;
	case OF_TEAM_BLUE:
		return "progress_bar_blu";
		break;
	}
}

const char *C_OFObjectiveResource::GetGameSpecificCPBarBG(int index, int iCappingTeam)
{
	switch (iCappingTeam)
	{
	default:
		return "progress_bar";
		break;
	case OF_TEAM_RED:
		return "progress_bar_red";
		break;
	case OF_TEAM_BLUE:
		return "progress_bar_blu";
		break;
	}
}