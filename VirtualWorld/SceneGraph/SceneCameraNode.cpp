#include "StdAfx.h"
#include "SceneCameraNode.h"

using namespace VirtualWorld;

void VirtualWorld::CSceneCameraNode::Draw()
{
}

void VirtualWorld::CSceneCameraNode::UpdateViewPort()
{
	int width = (int)(m_Rect.right - m_Rect.left);
	int height = (int)(m_Rect.bottom - m_Rect.top);
	double aspect = (double)(width / height);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_Fovy, aspect, m_ZNear, m_ZFar);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
}

void VirtualWorld::CSceneCameraNode::Apply()
{
	const CMatrix4f& world = GetWorldMatrix();
	CVector3f eye = world.TranslationVector();
	CVector3f center = eye - world.ForwardVector();
	CVector3f up = world.UpVector();		
	
	// TODO: Actually we almost finished all the job of gluLookAt. Just simply add inverse
	// Maybe later CMatrix.LookAt can replace gluLookAt
	// Of cause need to calculate and test carefully.
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

	CString log;
	log.Format(_T("(%f %f %f) (%f %f %f) (%f %f %f)"), eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
	OutputDebugString(log);
}
