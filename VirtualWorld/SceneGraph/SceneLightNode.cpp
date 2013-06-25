#include "StdAfx.h"
#include "SceneLightNode.h"

using namespace VirtualWorld;

int CSceneLightNode::m_NoOfLights = 0;

CSceneLightNode::CSceneLightNode()
	: m_DisplayListID(0)
	, m_NeedRedraw(true)
{
	if (this->m_NoOfLights < 8) {
		switch(this->m_NoOfLights)
		{
		case 0: this->m_ID = GL_LIGHT0; break;
		case 1: this->m_ID = GL_LIGHT1; break;
		case 2: this->m_ID = GL_LIGHT2; break;
		case 3: this->m_ID = GL_LIGHT3; break;
		case 4: this->m_ID = GL_LIGHT4; break;
		case 5: this->m_ID = GL_LIGHT5; break;
		case 6: this->m_ID = GL_LIGHT6; break;
		case 7: this->m_ID = GL_LIGHT7; break;
		}
		if(this->m_ID) {
			this->m_NoOfLights++;
		}
	}
}

VirtualWorld::CSceneLightNode::~CSceneLightNode()
{
	if (m_DisplayListID != 0) {
		glDeleteLists(m_DisplayListID, 1);
	}
}

void CSceneLightNode::Draw()
{
	if (m_Visibility == true) {
		glEnable(this->m_ID);
		glPushMatrix();
		DrawLight();
		glPopMatrix();
	} else {
		glDisable(this->m_ID);
	}
}

void CSceneLightNode::DrawLight()
{
	if (m_NeedRedraw == true) {
		if (m_DisplayListID != 0) {
			glDeleteLists(m_DisplayListID, 1);
		}
		m_DisplayListID = glGenLists(1);
		glNewList(m_DisplayListID, GL_COMPILE_AND_EXECUTE);

		glLightfv(this->m_ID, GL_AMBIENT, m_Ambient);
		glLightfv(this->m_ID, GL_DIFFUSE, m_Diffuse);
		glLightfv(this->m_ID, GL_SPECULAR, m_Specular);
		glLightfv(this->m_ID, GL_POSITION, m_Position);

		glLightf(this->m_ID, GL_CONSTANT_ATTENUATION, m_Attenuation.x);
		glLightf(this->m_ID, GL_LINEAR_ATTENUATION, m_Attenuation.y);
		glLightf(this->m_ID, GL_QUADRATIC_ATTENUATION, m_Attenuation.z);

		glLightf(this->m_ID, GL_SPOT_CUTOFF, m_SpotCutoff);
		glLightfv(this->m_ID, GL_SPOT_DIRECTION, m_SpotDirection);
		glLightf(this->m_ID, GL_SPOT_EXPONENT, m_SpotExponent);

		// End of m_DisplayListID
		glEndList();
		m_NeedRedraw = false;
	} else {
		glCallList(m_DisplayListID);
	}
}
