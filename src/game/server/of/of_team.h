// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFTeam slots into the g_Teams vector,
//      keeps track of a CBasePlayer *m_hLeader,
//      and reports some player-related events to COFGameRules
// Author(s): Nopey, Cherry!
//
#pragma once
#include "utlvector.h"
#include "team.h"

class COFTeam: public CTeam
{
public:
    DECLARE_CLASS(COFTeam, CTeam);
    DECLARE_SERVERCLASS();

    COFTeam();
    virtual ~COFTeam();

	virtual void AddObject(CBaseEntity *pObject); // When buildings are implemented, change this to CBaseObject
	virtual bool IsObjectOnTeam(CBaseEntity *pObject); // When buildings are implemented, change this to CBaseObject
	virtual void RemoveObject(CBaseEntity *pObject); // When buildings are implemented, change this to CBaseObject

	virtual void AddPlayer( CBasePlayer *pPlayer ) override;
	virtual void RemovePlayer( CBasePlayer *pPlayer ) override;

	virtual void SetColor(color32 Color);
	virtual int GetFlagCaptures() { return m_nFlagCaptures; };
	virtual void IncrementFlagCaptures() { m_nFlagCaptures++; };
	virtual void SetFlagCaptures(int iFlags) { m_nFlagCaptures = iFlags; };

private:
	CNetworkVar( int, m_nFlagCaptures );
	CNetworkVar( unsigned int, m_iRole );

public:
	CUtlVector< CBaseEntity* > m_aObjects; // When buildings are implemented, change this to CBaseObject

	color32 m_TeamColor;

};

COFTeam *GetGlobalOFTeam( int iIndex );

class COFTeamManager
{
public:

	bool Init();
	void Shutdown();

	int Create(const char *TeamName, color32 TeamColor);
	bool IsTeamValid(int iTeam);
	int GetFlagCaptures(int iTeam);
	void IncrementFlagCaptures(int iTeam);
	void AddTeamScore(int iTeam, int iAmount);
	int GetTeamCount();
	COFTeam *GetTeam(int iTeam);
};

extern COFTeamManager *OFTeamMgr();