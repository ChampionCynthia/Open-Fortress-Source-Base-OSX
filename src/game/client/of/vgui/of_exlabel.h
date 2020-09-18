// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExLabel implementation, currently a placeholder that acts the same as vgui::Label
// Author(s): Ms
//
#pragma once

#include "vgui_controls/Label.h"

class COFExLabel : public vgui::Label
{
public:
	DECLARE_CLASS_SIMPLE( COFExLabel, vgui::Label );

	COFExLabel( Panel* parent, const char* panelName, const char* text );
};

typedef COFExLabel CExButton;