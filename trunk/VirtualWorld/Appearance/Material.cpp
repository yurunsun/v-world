#include "StdAfx.h"
#include "Material.h"

using namespace VirtualWorld;

void CMaterial::Apply() const
{
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->m_Specular.m_Values);
	glMaterialfv(GL_FRONT, GL_AMBIENT , this->m_Ambient.m_Values);
	glMaterialfv(GL_FRONT, GL_DIFFUSE , this->m_Diffuse.m_Values);
	glMaterialfv(GL_FRONT, GL_EMISSION, this->m_Emission.m_Values);
	glMaterialf(GL_FRONT, GL_SHININESS, this->m_Shine);
}
