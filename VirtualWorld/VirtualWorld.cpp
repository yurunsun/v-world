// VirtualWorld.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Include/VirtualWorld.h"
#include "Window/Window32.h"
#include "SceneGraph/SceneGeometryNode.h"
#include "SceneGraph/SceneGroupNode.h"
#include "SceneGraph/SceneCameraNode.h"
#include "SceneGraph/SceneLightNode.h"
#include "Geometry/GeometryCommonObject.h"
#include "Geometry/GeometryOBJObject.h"
#include "Geometry/Geometry3DSObject.h"
#include "Appearance/Material.h"

using namespace VirtualWorld;

//-----------------------------------------------------------------------//
IWindow32::~IWindow32()
{
	if (m_RootSGNode != NULL) {
		m_RootSGNode->Release();
	}
}
//-----------------------------------------------------------------------//
IWindow32* CFactory::CreateWindow32()
{
	return new CWindow32();
}
//-----------------------------------------------------------------------//
ISceneGroupNode* CFactory::CreateSceneGroupNode()
{
	return new CSceneGroupNode();
}
//-----------------------------------------------------------------------//
ISceneGeometryNode* CFactory::CreateSceneGeometryNode()
{
	return new CSceneGeometryNode();
}
//-----------------------------------------------------------------------//
ISceneCameraNode* CFactory::CreateSceneCameraNode()
{
	return new CSceneCameraNode();
}
//-----------------------------------------------------------------------//
ISceneLightNode* CFactory::CreateSceneLightNode()
{
	return new CSceneLightNode();
}
//-----------------------------------------------------------------------//
IGeometryCubeObject* CFactory::CreateGeometryBoxObject()
{
	return new CGeometryCubeObject();
}
//-----------------------------------------------------------------------//
IGeometrySphereObject* CFactory::CreateGeometrySphereObject()
{
	return new CGeometrySphereObject();
}
//-----------------------------------------------------------------------//
IGeometryCylinderObject* CFactory::CreateGeometryCylinderObject()
{
	return new CGeometryCylinderObject();
}
//-----------------------------------------------------------------------//
IGeometryModelObject* CFactory::CreateGeometryModelObject( const CString& a_FileType )
{
	if (a_FileType.CompareNoCase(_T("OBJ")) == 0) {
		return new CGeometryOBJObject();	
	} else if (a_FileType.CompareNoCase(_T("3DS")) == 0) {
		return new CGeometry3DSObject();
	}
	return NULL;
}
//-----------------------------------------------------------------------//
IMaterial* CFactory::CreateMaterial()
{
	return new CMaterial();
}
//-----------------------------------------------------------------------//
char* VirtualWorld::CUtility::CStringToPChar( const CString& str )
{
	int n = str.GetLength();
	if (n <= 0) {
		return NULL;
	}
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	char* lpstr = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength() + 1, lpstr, len + 1, NULL, NULL);
	lpstr[len] = '\0';
	return lpstr;
}
//-----------------------------------------------------------------------//
CString VirtualWorld::CUtility::GetFileSuffix( const CString& str )
{
	return str.Right(str.GetLength() - str.ReverseFind(_T('.')) - 1);
}
//-----------------------------------------------------------------------//
CString VirtualWorld::CUtility::GetFileName( const CString& str )
{
	return str.Right(str.GetLength() - str.ReverseFind(_T('\\')) - 1);
}
//-----------------------------------------------------------------------//
