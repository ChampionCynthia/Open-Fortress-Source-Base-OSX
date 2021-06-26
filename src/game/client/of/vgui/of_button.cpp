// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExButton implementation, currently a placeholder that acts the same as vgui::Button
// Author(s): Ms, Cherry!
//
#include "cbase.h"
#include "of_button.h"

DECLARE_BUILD_FACTORY_DEFAULT_TEXT(COFButton, COFButton);

COFButton::COFButton(Panel* parent, const char* panelName, const char* text) : BaseClass(parent, panelName, text)
{
	m_szFont[0] = '\0';
	m_szColor[0] = '\0';
	m_pBorderDefault = NULL;
	m_pBorderArmed = NULL;
	m_pBorderDisabled = NULL;
	m_pBorderSelected = NULL;
}

COFButton::COFButton(Panel* parent, const char* panelName, const wchar_t* text) : BaseClass(parent, panelName, text)
{
	m_szFont[0] = '\0'; // 0x200
	m_szColor[0] = '\0';
	m_pBorderDefault = NULL;
	m_pBorderArmed = NULL;
	m_pBorderDisabled = NULL;
	m_pBorderSelected = NULL;
}

void COFButton::ApplySettings(KeyValues *pKey)
{
	BaseClass::ApplySettings(pKey);

	SetFontStr(pKey->GetString("font", "Default"));
	SetColorStr(pKey->GetString("fgcolor", "Button.TextColor"));

	vgui::IScheme *pScheme = g_pVGuiSchemeManager->GetIScheme(GetScheme());

	const char *szBorderDefault = pKey->GetString("border_default");
	if (szBorderDefault)
	{
		m_pBorderDefault = pScheme->GetBorder(szBorderDefault); // field_0x288
	}

	const char *szBorderArmed = pKey->GetString("border_armed");
	if (szBorderArmed)
	{
		m_pBorderArmed = pScheme->GetBorder(szBorderArmed);
	}

	const char *szBorderDisabled = pKey->GetString("border_disabled");
	if (szBorderDisabled)
	{
		m_pBorderDisabled = pScheme->GetBorder(szBorderDisabled);
	}

	const char *szBorderSelected = pKey->GetString("border_selected");
	if (szBorderSelected)
	{
		m_pBorderSelected = pScheme->GetBorder(szBorderSelected);
	}
}

void COFButton::SetFontStr(const char *pchar)
{
	vgui::IScheme *pScheme = g_pVGuiSchemeManager->GetIScheme(GetScheme());
	V_snprintf(m_szFont, sizeof(m_szFont), pchar);
	SetFont(pScheme->GetFont(pchar, true));
}

void COFButton::SetColorStr(const char *pchar)
{
	vgui::IScheme *pScheme = g_pVGuiSchemeManager->GetIScheme(GetScheme());
	Color pColor = pScheme->GetColor(pchar, Color(255, 255, 255, 255));
	V_snprintf(m_szColor, sizeof(m_szColor), "%d %d %d %d", pColor.r(), pColor.g(), pColor.b(), pColor.a());
	SetFgColor(pColor);
}

vgui::IBorder *COFButton::GetBorder(bool depressed, bool armed, bool selected, bool keyfocus)
{
	if (!IsEnabled() && m_pBorderDisabled)
		return m_pBorderDisabled;

	if (selected && m_pBorderSelected)
		return m_pBorderSelected;

	if (armed && m_pBorderArmed)
		return m_pBorderArmed;

	if (m_pBorderDefault)
		return m_pBorderDefault;

	return BaseClass::GetBorder(depressed, armed, selected, keyfocus);
}