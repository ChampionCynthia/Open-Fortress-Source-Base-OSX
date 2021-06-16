// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFImagePanel
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_imagepanel.h"

DECLARE_BUILD_FACTORY(COFImagePanel);

COFImagePanel::COFImagePanel(Panel* parent, const char* panelName) : BaseClass(parent, panelName)
{
	for (int i = 0; i < OF_TEAM_COUNT; i++)
	{
		m_szTeamImage[i][0] = '\0';
	}

	CBasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();
	m_iPlayerTeam = pPlayer ? pPlayer->GetTeamNumber() : TEAM_UNASSIGNED;

	ListenForGameEvent("localplayer_changeteam");
}

void COFImagePanel::ApplySettings(KeyValues *pKey)
{
	for (int i = 0; i < OF_TEAM_COUNT; i++)
	{
		const char *pString = pKey->GetString(VarArgs("teambg_%d"));
		V_strncpy(m_szTeamImage[i], pString, sizeof(m_szTeamImage[i]));
		if (m_szTeamImage[i][0] != '\0')
		{
			PrecacheMaterial(VarArgs("vgui/%s", m_szTeamImage[i]));
		}
	}

	BaseClass::ApplySettings(pKey);

	UpdateBGImage();
}

void COFImagePanel::UpdateBGImage()
{
	if (m_iPlayerTeam < OF_TEAM_COUNT && m_szTeamImage[m_iPlayerTeam][0])
	{
		SetImage(m_szTeamImage[m_iPlayerTeam]);
	}
}

void COFImagePanel::FireGameEvent(IGameEvent *pEvent)
{
	if (V_stricmp("localplayer_changeteam", pEvent->GetName()) == 0)
	{
		CBasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();
		m_iPlayerTeam = pPlayer ? pPlayer->GetTeamNumber() : TEAM_UNASSIGNED;
		UpdateBGImage();
	}
}