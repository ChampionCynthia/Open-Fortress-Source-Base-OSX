// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExButton implementation, currently a placeholder that acts the same as vgui::Button
// Author(s): Ms
//
#pragma once

#include "vgui_controls/Button.h"

class COFExButton : public vgui::Button
{
public:
	DECLARE_CLASS_SIMPLE( COFExButton, vgui::Button );

	COFExButton( Panel* parent, const char* panelName, const char* text );
};

typedef COFExButton CExButton;