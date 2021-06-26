// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of Building info
// Author(s): KaydemonLP
//

#pragma once

struct CObjectInfo
{
public:
	CObjectInfo( const char *pObjectName );
	~CObjectInfo();

public:
	const char	*m_szObjectName;
	char	*m_szClassName;
	char	*m_szStatusName;
	float	m_flBuildTime;
	int		m_iMaxObjects;
	int		m_iCost;
	float	m_flCostMultiplier;
	int		m_iUpgradeCost;
	int		m_iMaxUpgradeLevel;
	char	*m_szBuilderWeaponName;
	char	*m_szBuilderPlacementString;
	int		m_iSlot;
	int		m_iPosition;
	bool	m_bSolidToPlayerMovement;
	bool	m_bUseItemInfo;

	char	*m_szViewmodel;
	char	*m_szPlayermodel;
	int		m_iDisplayPriority;
	bool	m_bVisibleInWeaponSelection;

	char	*m_szExplodeSound;
	char	*m_szExplodeEffect;
	bool	m_bAutoswitchTo;

	char	*m_szUpgradeSound;
	float	m_flUpgradeDuration;
	int		m_iBuildCount;
	int		m_iAltModeCount;

	struct object_mode_t
	{
		char	*m_szStatusName1;
		char	*m_szModelName1;
		char	*m_szIconMenu1;
	};

	object_mode_t m_ObjectModes[3];

	char	*m_szIconActive;
	char	*m_szIconInactive;
	char	*m_szIconMenu;
	char	*m_szHudStatusIcon;
	int		m_iMetalToDropInGibs;
	bool	m_bRequiresOwnBuilder;
};

extern CObjectInfo g_ObjectInfos[];