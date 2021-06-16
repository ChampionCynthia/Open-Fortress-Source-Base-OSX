// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExLabel implementation
// Author(s): Ms, Cherry!
//
#pragma once

#include "vgui_controls/Label.h"

class COFLabel : public vgui::Label
{
public:
	DECLARE_CLASS_SIMPLE(COFLabel, vgui::Label);

	COFLabel(Panel* parent, const char* panelName, const char* text);
	COFLabel(Panel* parent, const char* panelName, const wchar_t* text);

	void ApplySettings(KeyValues *pKey);
	void ApplySchemeSettings(vgui::IScheme *pScheme);
	void SetColorStr(const char *pchar);
	void SetColorStr(Color pColor);

private:
	char m_szColor[64];
};