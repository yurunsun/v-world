#include "StdAfx.h"
#include "Window32.h"

using namespace VirtualWorld;

int CWindow32::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	UNREFERENCED_PARAMETER(lpCreateStruct);
	SetMsgHandled(FALSE);
	return 0;
}

void CWindow32::OnDestroy()
{
	PostQuitMessage(0);
}

HWND CWindow32::CreateWin(
	HWND hWndParent, 
	_U_RECT rect /* = NULL */, 
	LPCTSTR szWindowName /* = NULL */, 
	DWORD dwStyle /* = 0 */, 
	DWORD dwExStyle /* = 0 */, 
	_U_MENUorID MenuOrID /* = 0U */, 
	LPVOID lpCreateParam /* = NULL */)
{
	return this->Create(hWndParent, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
}

HWND CWindow32::GetHwnd() const 
{
	return this->m_hWnd;
}

BOOL VirtualWorld::CWindow32::OnIdle()
{
	return FALSE;
}

BOOL VirtualWorld::CWindow32::RedrawWin( 
	CONST RECT *lprcUpdate /*= NULL*/, 
	HRGN hrgnUpdate /*= NULL*/, 
	UINT flags /*= RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE*/ )
{
	return this->RedrawWindow(lprcUpdate, hrgnUpdate, flags);
}

void VirtualWorld::CWindow32::OnMove( const CPoint& ptPos )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnMove(ptPos);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnLButtonDown( unsigned nFlags, const CPoint& point )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnLButtonDown(nFlags, point);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnLButtonUp( unsigned nFlags, const CPoint& point )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnLButtonUp(nFlags, point);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnLButtonDblClk( unsigned nFlags, const CPoint& point )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnLButtonDblClk(nFlags, point);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnRButtonDown( unsigned nFlags, const CPoint& point )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnRButtonDown(nFlags, point);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnRButtonUp( unsigned nFlags, const CPoint& point )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnRButtonUp(nFlags, point);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnRButtonDblClk( unsigned nFlags, const CPoint& point )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnRButtonDblClk(nFlags, point);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnMouseMove( unsigned nFlags, const CPoint& point )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnMouseMove(nFlags, point);
	}
	SetMsgHandled(FALSE);
}

BOOL VirtualWorld::CWindow32::OnMouseWheel( unsigned nFlags, short zDelta, const CPoint& pt )
{
	if (m_GUIEventHandler != NULL) {
		return m_GUIEventHandler->OnMouseWheel(nFlags, zDelta, pt);
	}
	SetMsgHandled(FALSE);
	return FALSE;
}

void VirtualWorld::CWindow32::OnKeyDown( unsigned nChar, unsigned nRepCnt, unsigned nFlags )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnKeyDown(nChar, nRepCnt, nFlags);
	}
	SetMsgHandled(FALSE);
}

void VirtualWorld::CWindow32::OnKeyUp( unsigned nChar, unsigned nRepCnt, unsigned nFlags )
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnKeyUp(nChar, nRepCnt, nFlags);
	}
	SetMsgHandled(FALSE);
}

BOOL CWindow32::PreTranslateMessage( MSG* pMsg )
{
	UNREFERENCED_PARAMETER(pMsg);
	return FALSE;
}

void CWindow32::OnInit()
{
	glClearColor(0.200f, 0.200f, 0.200f, 1.0f); //Background color
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CWindow32::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
	glLoadIdentity(); // Load identity matrix

	if (m_ActiveCameraNode != NULL) {
		m_ActiveCameraNode->Apply();
	}
	if (m_RootSGNode != NULL) {
		m_RootSGNode->Draw();
	}
	glFlush();
}

void CWindow32::OnResize(const CSize& a_Size)
{
	if (m_GUIEventHandler != NULL) {
		m_GUIEventHandler->OnSize(a_Size);
	}
}


