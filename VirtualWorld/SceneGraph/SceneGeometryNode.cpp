#include "StdAfx.h"
#include "SceneGeometryNode.h"

using namespace VirtualWorld;

CSceneGeometryNode::CSceneGeometryNode(void)
	: m_GeometryObject(NULL)
{
}

CSceneGeometryNode::~CSceneGeometryNode(void)
{
}

void VirtualWorld::CSceneGeometryNode::Draw()
{
	if (m_GeometryObject != NULL) {
		glPushMatrix();
		glMultMatrixf(m_LocalMatrix);
		m_GeometryObject->Draw();
		glPopMatrix();
	}
}

void VirtualWorld::CSceneGeometryNode::SetGeometryObject( IGeometryBaseObject* a_Object )
{
	if (m_GeometryObject != NULL) {
		m_GeometryObject->Release();
	}
	m_GeometryObject = a_Object;
	if (m_GeometryObject != NULL) {
		m_GeometryObject->AddRef();
	}
}

IGeometryBaseObject* VirtualWorld::CSceneGeometryNode::GetGeometryObject() const
{
	return m_GeometryObject;
}
