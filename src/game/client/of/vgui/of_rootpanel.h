// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Root Panel of VGUI elements
// Author(s): ficool2
//

#ifndef OF_ROOTPANEL_H
#define OF_ROOTPANEL_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Panel.h>
#include <vgui_controls/EditablePanel.h>
#include "utlvector.h"

class CPanelEffect;

// Serial under of effect, for safe lookup
typedef unsigned int EFFECT_HANDLE;

class C_OFRootPanel : public vgui::Panel
{
	typedef vgui::Panel BaseClass;
	
public:
						C_OFRootPanel( vgui::VPANEL parent );
	virtual				~C_OFRootPanel( void );
};


#endif