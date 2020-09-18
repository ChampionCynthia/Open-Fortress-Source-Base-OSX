// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExLabel implementation, currently a placeholder that acts the same as vgui::Label
// Author(s): Ms
//
#include "cbase.h"
#include "of_exlabel.h"

static vgui::Panel * Create_COFExLabel( void )							
{																		
	return new COFExLabel( NULL, NULL, "COFExLabel" );					
};																		\
static vgui::CBuildFactoryHelper g_COFExLabel_Helper( "CExLabel", Create_COFExLabel );\
COFExLabel *g_COFExLabelLinkerHack = NULL;

COFExLabel::COFExLabel( Panel* parent, const char* panelName, const char* text ) : BaseClass( parent, panelName, text )
{
}