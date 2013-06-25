#include "StdAfx.h"
#include "SceneGroupNode.h"

using namespace VirtualWorld;

void CSceneGroupNode::Draw()
{
	glPushMatrix();
	glMultMatrixf(m_LocalMatrix);
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it) {
		it->second->Draw();
	}
	glPopMatrix();
}
