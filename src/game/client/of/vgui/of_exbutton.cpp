// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExButton implementation, currently a placeholder that acts the same as vgui::Button
// Author(s): Ms
//
#include "cbase.h"
#include "of_exbutton.h"

static vgui::Panel* Create_COFExButton( void )
{
	return new COFExButton( NULL, NULL, "COFExButton" );
};																		\
static vgui::CBuildFactoryHelper g_COFExLabel_Helper( "CExButton", Create_COFExButton ); \
COFExButton* g_COFExButtonLinkerHack = NULL;

COFExButton::COFExButton( Panel* parent, const char* panelName, const char* text ) : BaseClass( parent, panelName, text )
{
}