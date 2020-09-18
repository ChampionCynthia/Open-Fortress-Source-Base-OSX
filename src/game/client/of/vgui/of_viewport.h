// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Clientside viewport
// Author(s): ficool2
//

#ifndef OF_VIEWPORT_H
#define OF_VIEWPORT_H

#include "baseviewport.h"

using namespace vgui;

namespace vgui 
{
	class Panel;
}

class OFViewport : public CBaseViewport
{
	DECLARE_CLASS_SIMPLE( OFViewport, CBaseViewport );

public:
	IViewPortPanel* CreatePanelByName(const char *szPanelName);
	virtual void ApplySchemeSettings( vgui::IScheme *pScheme );

	virtual void CreateDefaultPanels( void );
};


#endif