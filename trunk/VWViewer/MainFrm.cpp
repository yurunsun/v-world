// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainFrm.h"
#include "aboutdlg.h"
#include "CameraDlg.h"
#include "NodeTreeDlg.h"

using namespace VirtualWorld;
using namespace std;

stack<CString> g_filePaths;

DWORD WINAPI ThreadFuncWrapper(LPVOID lpParam) 
{
	if (lpParam != NULL) {
		CMainFrame* pThis = reinterpret_cast<CMainFrame*>(lpParam);
		if (pThis != NULL) {
			bool ret =  pThis->DoFileOpen();
			return (ret == true) ? S_OK : S_FALSE;
		}
	}
	return S_FALSE;
}

CMainFrame::CMainFrame()
	: m_LastTickCount(GetTickCount())
	, m_ModelName(_T(""))
	, m_EnableAnimation(false)
	, m_EnableShading(false)
	, m_pView(NULL)
	, m_pCameraDlg(NULL)
	, m_pNodetreeDlg(NULL)
{
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	if (m_pView != NULL) {
		return m_pView->PreTranslateMessage(pMsg);
	}
	return FALSE;
}

BOOL CMainFrame::OnIdle()
{
	return m_pView->OnIdle();
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CFactory* pFac = CFactory::GetInstance();

	m_pView = pFac->CreateWindow32();
	m_hWndClient = m_pView->CreateWin(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
	m_pView->SetGUIEventHandler(this);
	m_pCameraDlg = new CCameraDlg();
	m_pCameraDlg->Create(m_hWnd);
	m_pNodetreeDlg = new CNodetreeDlg();
	m_pNodetreeDlg->Create(m_hWnd);
	
	ISceneGroupNode* rootNode = pFac->CreateSceneGroupNode();
	ISceneCameraNode* cameraNode = pFac->CreateSceneCameraNode();
	/*ISceneGeometryNode* cubeNode = pFac->CreateSceneGeometryNode();
	ISceneGeometryNode* sphereNode = pFac->CreateSceneGeometryNode();
	ISceneGeometryNode* cylinderNode = pFac->CreateSceneGeometryNode();*/
	ISceneLightNode* lightNode = pFac->CreateSceneLightNode();

	/*IGeometryCubeObject* cubeObj = pFac->CreateGeometryBoxObject();
	IGeometrySphereObject* sphereObj = pFac->CreateGeometrySphereObject();
	IGeometryCylinderObject* cylinderObj = pFac->CreateGeometryCylinderObject();

	IMaterial* material = pFac->CreateMaterial();
	material->SetAmbient(CVector4f(0.000f, 0.50f, 0.000f, 1.0f));
	material->SetDiffuse(CVector4f(0.000f, 0.300f, 0.000f, 1.0f));
	material->SetSpecular(CVector4f(1.000f, 1.000f, 1.000f, 1.0f));
	material->SetEmmision(CVector4f(0.000f, 0.000f, 0.000f, 1.0f));
	material->SetShine(128.000f);

	cubeObj->SetMaterial(material);
	cubeObj->SetRadius(0.3f);
	cubeObj->SetDrawMode(IGeometryBaseObject::GEOMETRY_DRAW_SOLID);
	cubeNode->SetName(_T("Box1"));
	cubeNode->SetGeometryObject(cubeObj);
	cubeNode->Translate(CVector3f(1.0f, 0.0f, 0.0f));
	rootNode->AddChild(cubeNode);

	sphereObj->SetMaterial(material);
	sphereObj->SetRadius(0.4f);
	sphereObj->SetDrawMode(IGeometryBaseObject::GEOMETRY_DRAW_SOLID);
	sphereObj->SetNormalMode(IGeometryBaseObject::GEOMETRY_NORMAL_VERTEX);
	sphereNode->SetName(_T("Sphere1"));
	sphereNode->SetGeometryObject(sphereObj);
	sphereNode->Translate(CVector3f(-1.0f, 0.0f, 0.0f));
	rootNode->AddChild(sphereNode);

	cylinderObj->SetMaterial(material);
	cylinderObj->SetDrawMode(IGeometryBaseObject::GEOMETRY_DRAW_SOLID);
	cylinderObj->SetNormalMode(IGeometryBaseObject::GEOMETRY_NORMAL_VERTEX);
	cylinderObj->SetBaseRadius(0.3f);
	cylinderNode->SetName(_T("Cylinder1"));
	cylinderNode->SetGeometryObject(cylinderObj);
	cylinderNode->Translate(CVector3f(0.0f, 0.0f, -1.0f));
	cylinderNode->Rotate(0.1f, CVector3f(1.0f, 0.0f, 0.0f));
	rootNode->AddChild(cylinderNode);*/

	lightNode->SetName(_T("light0"));
	lightNode->SetAmbient(CVector4f(0.5f, 0.8f, 0.5f, 1.0f));
	lightNode->SetPosition(CVector4f(0.0f, 0.0f, 1.0f, 0.0f));
	rootNode->AddChild(lightNode);

	cameraNode->SetName(_T("Camera"));
	cameraNode->SetFovy(30.0f);
	cameraNode->SetZNear(1.0f);
	cameraNode->SetZFar(1000.0f);
	cameraNode->Translate(CVector3f(0.0f, 0.0f, 5.0f));

	rootNode->SetName(_T("Root"));
	m_pView->SetActiveCameraNode(cameraNode);
	m_pView->SetRootSGNode(rootNode);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document
	return 0;
}

LRESULT CMainFrame::OnFileOpen( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	static COMDLG_FILTERSPEC filterSpecs[] = {
		{_T("3ds(*.3ds)"),_T("*.3ds")},
		{_T("obj(*.obj)"),_T("*.obj")},
		{_T("3dxml(*.3dxml)"),_T("*.3dxml")},
		{_T("dae(*.dae)"),_T("*.dae")},
		{_T("gsm(*.gsm)"),_T("*.gsm")},
		{_T("gts(*.gts)"),_T("*.gts")},
		{_T("max(*.max)"),_T("*.max")},
		{_T("ply(*.ply)"),_T("*.ply")},
		{_T("pts(*.pts)"),_T("*.pts")},
		{_T("stl(*.stl)"),_T("*.stl")},
		{_T("All documents(*.*)"),_T("*.*")}
	};
	CShellFileOpenDialog fileOpenDlg(
		NULL,
		FOS_FORCEFILESYSTEM|FOS_FILEMUSTEXIST|FOS_PATHMUSTEXIST,
		_T("3d model"),
		filterSpecs,
		_countof(filterSpecs));
	fileOpenDlg.DoModal(m_hWnd);

	CString filePath;
	fileOpenDlg.GetFilePath(filePath);
	OutputDebugString(filePath);

	if (!filePath.IsEmpty()) {
		g_filePaths.push(filePath);
		HANDLE hr = CreateThread(NULL, 0, ThreadFuncWrapper, this, 0, NULL);
		CloseHandle(hr);
	}
	return 0;
}

LRESULT CMainFrame::OnEditAnimation( WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled )
{
	m_EnableAnimation = !m_EnableAnimation;
	UISetCheck(wID, m_EnableAnimation);
	if (m_EnableAnimation) {
		SetTimer(ID_EDIT_ANIMATION, 30);
	} else {
		KillTimer(ID_EDIT_ANIMATION);
	}
	return 0;
}

LRESULT CMainFrame::OnEditShading( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	m_EnableShading = !m_EnableShading;
	UISetCheck(wID, m_EnableShading);
	DoShading();
	return 0;
}

LRESULT CMainFrame::OnEditCamera( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	if (m_pView != NULL) {
		m_pCameraDlg->BindCamera(m_pView->GetActiveCameraNode());
		m_pCameraDlg->BindTarget(m_pView->GetRootSGNode());
		m_pCameraDlg->UpdateCameraProperty();
	}
	m_pCameraDlg->ShowWindow(SW_SHOW);
	this->SetActiveWindow();
	return 0;
}

LRESULT CMainFrame::OnEditNodetree(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your command handler code here
	if (m_pView != NULL) {
		m_pNodetreeDlg->BindRootNode(m_pView->GetRootSGNode());
		m_pNodetreeDlg->UpdateNodetree();
	}
	m_pNodetreeDlg->ShowWindow(SW_SHOW);
	this->SetActiveWindow();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

bool CMainFrame::DoAnimate(unsigned a_PerMilliSecond)
{
	DWORD dwTickCount = ::GetTickCount();
	if (dwTickCount - m_LastTickCount > a_PerMilliSecond) {
		ISceneGroupNode* root = m_pView->GetRootSGNode();
		if (root != NULL) {
			root->Rotate(0.1f, CVector3f(0.0f, 1.0f, 0.0f));
			m_LastTickCount = dwTickCount;
			return true;
		}
	} 
	return false;
}

bool CMainFrame::DoShading()
{
	if (m_pView != NULL) {
		if (m_pView->GetRootSGNode() != NULL) {
			ISceneGeometryNode* modelNode = dynamic_cast<ISceneGeometryNode*>(m_pView->GetRootSGNode()->GetChild(m_ModelName));
			if (modelNode != NULL) {
				int drawMode = m_EnableShading ? IGeometryBaseObject::GEOMETRY_DRAW_SOLID : IGeometryBaseObject::GEOMETRY_DRAW_WIRE;
				modelNode->GetGeometryObject()->SetDrawMode(drawMode);
				m_pView->RedrawWin();
				return true;
			}
		}
	}
	return false;
}

LRESULT CMainFrame::OnTimer( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled )
{
	if ((UINT_PTR)wParam == ID_EDIT_ANIMATION) {
		if (m_EnableAnimation && this->IsWindowVisible() && (m_pView != NULL) && DoAnimate(10)) {
			m_pView->RedrawWin();
		}
	}
	MSG msg;
	while(::PeekMessage(&msg, this->m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE)) {}
	return 0;
}

bool CMainFrame::DoFileOpen()
{
	if (g_filePaths.empty()) {
		return false;
	}
	CString filePath = g_filePaths.top();
	CString modelType = CUtility::GetFileSuffix(filePath);
	IGeometryModelObject* objModel = CFactory::GetInstance()->CreateGeometryModelObject(modelType);
	if (objModel != NULL) {
		bool hr = objModel->LoadModel(filePath);
		if (hr == true)  {
			objModel->SetDrawMode(IGeometryBaseObject::GEOMETRY_DRAW_SOLID);
			ISceneGeometryNode* gunNode = CFactory::GetInstance()->CreateSceneGeometryNode();
			gunNode->SetGeometryObject(objModel);
			m_ModelName = CUtility::GetFileName(filePath);
			gunNode->SetName(m_ModelName);

			IBoundingBox* box = objModel->GetBoundingBox();
			CVector3f radiusVec = box->GetMax() - box->GetMin();
			CVector3f center = (box->GetMax() + box->GetMin()) / 2;
			gunNode->Translate(CVector3f(-center.x, -center.y, -center.z));

			float radius = radiusVec.Length();
			ISceneCameraNode* camera = m_pView->GetActiveCameraNode();
			camera->LookAt(CVector3f(0.0f, 0.0f, radius*2), CVector3f(0.0f, 0.0f, 0.0f), CVector3f(0.0f, 1.0f, 0.0f));

			m_pView->GetRootSGNode()->AddChild(gunNode);
			m_pView->RedrawWin();
		}
	}
	return false;
}

void CMainFrame::OnMove( const CPoint& ptPos )
{
	UNREFERENCED_PARAMETER(ptPos);
}

void CMainFrame::OnSize( const CSize& size )
{
	UNREFERENCED_PARAMETER(size);

	ISceneCameraNode* cameraNode = m_pView->GetActiveCameraNode();
	if (cameraNode != NULL) {
		RECT rc;
		::GetClientRect(m_pView->GetHwnd(), &rc);
		cameraNode->SetRect(rc);
		cameraNode->UpdateViewPort();
	}
}

void CMainFrame::OnLButtonDown( unsigned nFlags, const CPoint& point )
{
	CString msg;
	msg.Format(_T("OnLButtonDown with nFlags %u pointx %d pointy %d"), nFlags, point.x, point.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}

void CMainFrame::OnLButtonUp( unsigned nFlags, const CPoint& point )
{
	CString msg;
	msg.Format(_T("OnLButtonUp with nFlags %u pointx %d pointy %d"), nFlags, point.x, point.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}

void CMainFrame::OnLButtonDblClk( unsigned nFlags, const CPoint& point )
{
	CString msg;
	msg.Format(_T("OnLButtonDblClk with nFlags %u pointx %d pointy %d"), nFlags, point.x, point.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}

void CMainFrame::OnRButtonDown( unsigned nFlags, const CPoint& point )
{
	CString msg;
	msg.Format(_T("OnRButtonDown with nFlags %u pointx %d pointy %d"), nFlags, point.x, point.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}

void CMainFrame::OnRButtonUp( unsigned nFlags, const CPoint& point )
{
	CString msg;
	msg.Format(_T("OnRButtonUp with nFlags %u pointx %d pointy %d"), nFlags, point.x, point.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}

void CMainFrame::OnRButtonDblClk( unsigned nFlags, const CPoint& point )
{
	CString msg;
	msg.Format(_T("OnRButtonDblClk with nFlags %u pointx %d pointy %d"), nFlags, point.x, point.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}

void CMainFrame::OnMouseMove( unsigned nFlags, const CPoint& point )
{
	CString msg;
	msg.Format(_T("OnMouseMove with nFlags %u pointx %d pointy %d"), nFlags, point.x, point.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}

BOOL CMainFrame::OnMouseWheel( unsigned nFlags, short zDelta, const CPoint& pt )
{
	CString msg;
	msg.Format(_T("OnMouseWheel with nFlags %u zDelta %u pointx %d pointy %d"), nFlags, zDelta, pt.x, pt.y);
	//MessageBox(msg, _T("Not Implemented!"), 0);
	return TRUE;
}

void CMainFrame::OnKeyDown( unsigned nChar, unsigned nRepCnt, unsigned nFlags )
{
	ISceneCameraNode* cameraNode = m_pView->GetActiveCameraNode();
	if (cameraNode == NULL || m_pView == NULL) {
		return;
	}
	float speed = 0.2f;
	ISceneBaseNode* obj = m_pNodetreeDlg->GetSelection();
	if (obj == NULL) {
		return;
	}
	switch (nChar)
	{
	case VK_UP: {
			obj->Translate(CVector3f(0.0f, 0.0f, -speed));
		} break;
	case VK_DOWN: {
			obj->Translate(CVector3f(0.0f, 0.0f, speed));
		} break;
	case VK_LEFT: {
			obj->Translate(CVector3f(-speed, 0.0f, 0.0f));
		} break;
	case VK_RIGHT: {
			obj->Translate(CVector3f(speed, 0.0f, 0.0f));
		} break;
	case VK_PRIOR: {
			obj->Translate(CVector3f(0.0f, speed, 0.0f));
		} break;
	case VK_NEXT: {
			obj->Translate(CVector3f(0.0f, -speed, 0.0f));
		} break;
	case 'X': {
			obj->Rotate(speed, CVector3f(1.0f, 0.0f, 0.0f));
		} break;
	case 'Y': {
			obj->Rotate(speed, CVector3f(0.0f, 1.0f, 0.0f));
		} break;
	case 'Z': {
			obj->Rotate(speed, CVector3f(0.0f, 0.0f, 0.1f));
		} break;
	case 'I': {
			obj->GotoLocalOrigin();
		} break;
	}
	m_pCameraDlg->UpdateCameraProperty();
	m_pView->RedrawWin();
}

void CMainFrame::OnKeyUp( unsigned nChar, unsigned nRepCnt, unsigned nFlags )
{
	CString msg;
	msg.Format(_T("OnKeyUp with nChar %u nRepCnt %u nFlags %u"), nChar, nRepCnt, nFlags);
	//MessageBox(msg, _T("Not Implemented!"), 0);
}