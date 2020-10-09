// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFObjectiveResource implementation
// Author(s): Nopey
//

#include "cbase.h"
#include "of_objectiveresource.h"

IMPLEMENT_NETWORKCLASS_DT( COFObjectiveResource, DT_OFObjectiveResource )
END_NETWORK_TABLE()

#ifndef CLIENT_DLL
BEGIN_DATADESC( COFObjectiveResource )
END_DATADESC( )

LINK_ENTITY_TO_CLASS( tf_objective_resource, COFObjectiveResource );
#endif
