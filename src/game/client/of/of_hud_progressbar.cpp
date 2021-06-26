// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFProgressBar
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_hud_progressbar.h"
#include "vgui/ISurface.h"

DECLARE_BUILD_FACTORY(COFProgressBar);

COFProgressBar::COFProgressBar(Panel *parent, const char *pName) : vgui::ImagePanel(parent, pName)
{
	m_flRemainingTimePercentage = 0.0;
	m_iTextureID = g_pVGuiSurface->DrawGetTextureId("hud/objectives_timepanel_progressbar");
	if (m_iTextureID == -1)
	{
		m_iTextureID = g_pVGuiSurface->CreateNewTextureID();
		g_pVGuiSurface->DrawSetTextureFile(m_iTextureID, "hud/objectives_timepanel_progressbar", true, false);
	}
}

typedef struct
{
	float minProgressRadians;

	float vert1x;
	float vert1y;
	float vert2x;
	float vert2y;

	int swipe_dir_x;
	int swipe_dir_y;
} circular_progress_segment_t;

// This defines the properties of the 8 circle segments
// in the circular progress bar.
circular_progress_segment_t Segments[8] =
{
	{ 0.0, 0.5, 0.0, 1.0, 0.0, 1, 0 },
	{ M_PI * 0.25, 1.0, 0.0, 1.0, 0.5, 0, 1 },
	{ M_PI * 0.5, 1.0, 0.5, 1.0, 1.0, 0, 1 },
	{ M_PI * 0.75, 1.0, 1.0, 0.5, 1.0, -1, 0 },
	{ M_PI, 0.5, 1.0, 0.0, 1.0, -1, 0 },
	{ M_PI * 1.25, 0.0, 1.0, 0.0, 0.5, 0, -1 },
	{ M_PI * 1.5, 0.0, 0.5, 0.0, 0.0, 0, -1 },
	{ M_PI * 1.75, 0.0, 0.0, 0.5, 0.0, 1, 0 },
};

#define SEGMENT_ANGLE	( M_PI / 4 )

void COFProgressBar::Paint()
{
	int x, y;
	GetPos(x, y);

	int wide, tall;
	GetSize(wide, tall);

	float flWide = (float)wide;
	float flTall = (float)tall;

	float flHalfWide = (float)wide / 2;
	float flHalfTall = (float)tall / 2;

	vgui::surface()->DrawSetTexture(m_iTextureID);

	// inactive background
	vgui::surface()->DrawSetColor(m_ColorInActive);
	vgui::surface()->DrawTexturedRect(0, 0, wide, tall);

	// set normal color or if we're in the warning range, set the warning color
	Color setColor = m_ColorActive;
	if (m_flPercentWarning < m_flRemainingTimePercentage) setColor = m_ColorWarning;
	vgui::surface()->DrawSetColor(setColor);

	float flEndProgressRadians = (1 - m_flRemainingTimePercentage) * M_PI * 2;

	int cur_wedge = 0;
	for (int i = 0; i<8; i++)
	{
		if (flEndProgressRadians > Segments[cur_wedge].minProgressRadians)
		{
			vgui::Vertex_t v[3];

			// vert 0 is ( 0.5, 0.5 )
			v[0].m_Position.Init(flHalfWide, flHalfTall);
			v[0].m_TexCoord.Init(0.5f, 0.5f);

			float flInternalProgress = flEndProgressRadians - Segments[cur_wedge].minProgressRadians;

			if (flInternalProgress < SEGMENT_ANGLE)
			{
				// Calc how much of this slice we should be drawing

				if (i % 2 == 1)
				{
					flInternalProgress = SEGMENT_ANGLE - flInternalProgress;
				}

				float flTan = tan(flInternalProgress);

				float flDeltaX, flDeltaY;

				if (i % 2 == 1)
				{
					flDeltaX = (flHalfWide - flHalfTall * flTan) * Segments[i].swipe_dir_x;
					flDeltaY = (flHalfTall - flHalfWide * flTan) * Segments[i].swipe_dir_y;
				}
				else
				{
					flDeltaX = flHalfTall * flTan * Segments[i].swipe_dir_x;
					flDeltaY = flHalfWide * flTan * Segments[i].swipe_dir_y;
				}

				v[2].m_Position.Init(Segments[i].vert1x * flWide + flDeltaX, Segments[i].vert1y * flTall + flDeltaY);
				v[2].m_TexCoord.Init(Segments[i].vert1x + (flDeltaX / flHalfWide) * 0.5, Segments[i].vert1y + (flDeltaY / flHalfTall) * 0.5);
			}
			else
			{
				// full segment, easy calculation
				v[2].m_Position.Init(flHalfWide + flWide * (Segments[i].vert2x - 0.5), flHalfTall + flTall * (Segments[i].vert2y - 0.5));
				v[2].m_TexCoord.Init(Segments[i].vert2x, Segments[i].vert2y);
			}

			// vert 2 is ( Segments[i].vert1x, Segments[i].vert1y )
			v[1].m_Position.Init(flHalfWide + flWide * (Segments[i].vert1x - 0.5), flHalfTall + flTall * (Segments[i].vert1y - 0.5));
			v[1].m_TexCoord.Init(Segments[i].vert1x, Segments[i].vert1y);

			vgui::surface()->DrawTexturedPolygon(3, v);
		}

		cur_wedge++;
		if (cur_wedge >= 8)
			cur_wedge = 0;
	}
}