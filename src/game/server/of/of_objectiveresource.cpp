// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFObjectiveResource
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_objectiveresource.h"

IMPLEMENT_SERVERCLASS_ST(COFObjectiveResource, DT_OFObjectiveResource)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(tf_objective_resource, COFObjectiveResource);

void COFObjectiveResource::Spawn()
{
	BaseClass::Spawn();
}