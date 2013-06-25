#include "StdAfx.h"
#include "CameraDlg.h"
#include "../Include/VirtualWorld.h"

using namespace VirtualWorld;

CCameraDlg::CCameraDlg()
	: m_pCamera(NULL)
	, m_pTarget(NULL)
{
	
}

LRESULT CCameraDlg::OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_Eye[0] = GetDlgItem(IDC_EDIT_CAMERA_EYE_X);
	m_Eye[1] = GetDlgItem(IDC_EDIT_CAMERA_EYE_Y);
	m_Eye[2] = GetDlgItem(IDC_EDIT_CAMERA_EYE_Z);
	m_FV[0] = GetDlgItem(IDC_EDIT_CAMERA_FV_X);
	m_FV[1] = GetDlgItem(IDC_EDIT_CAMERA_FV_Y);
	m_FV[2] = GetDlgItem(IDC_EDIT_CAMERA_FV_Z);
	m_UV[0] = GetDlgItem(IDC_EDIT_CAMERA_UV_X);
	m_UV[1] = GetDlgItem(IDC_EDIT_CAMERA_UV_Y);
	m_UV[2] = GetDlgItem(IDC_EDIT_CAMERA_UV_Z);
	m_Target[0] = GetDlgItem(IDC_EDIT_CAMERA_TARGET_X);
	m_Target[1] = GetDlgItem(IDC_EDIT_CAMERA_TARGET_Y);
	m_Target[2] = GetDlgItem(IDC_EDIT_CAMERA_TARGET_Z);
	m_Distance = GetDlgItem(IDC_EDIT_CAMERA_DISTANCE);

	//this->CenterWindow(GetParent());
	BOOL hr = this->ModifyStyleEx(0, WS_EX_LAYERED);
	if (hr == TRUE) {
		SetLayeredWindowAttributes(this->m_hWnd, RGB(255, 0, 255), 128, LWA_ALPHA | LWA_COLORKEY);
	}
	return 0;
}

LRESULT CCameraDlg::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	this->ShowWindow(SW_HIDE);
	return 0;
}

void CCameraDlg::BindCamera( ISceneCameraNode* pCamera )
{
	m_pCamera = pCamera;	// Do not need to take the ownership of pointer pCamera
}

void CCameraDlg::BindTarget( VirtualWorld::ISceneBaseNode* pTarget )
{
	m_pTarget = pTarget;
}

void CCameraDlg::UpdateCameraProperty()
{
	if (m_pCamera != NULL) {
		const CMatrix4f camera = m_pCamera->GetWorldMatrix();
		CVector3f eye = camera.TranslationVector();
		CVector3f fv = camera.ForwardVector().Normalize();
		CVector3f uv = camera.UpVector().Normalize();

		struct EditValue {
			CEdit edit;
			float num;
		} pairs[] = {  
			{m_Eye[0], eye.x}, {m_Eye[1], eye.y}, {m_Eye[2], eye.z},
			{m_FV[0], fv.x}, {m_FV[1], fv.y}, {m_FV[2], fv.z},
			{m_UV[0], uv.x}, {m_UV[1], uv.y}, {m_UV[2], uv.z}
		};
		int size = sizeof(pairs)/sizeof(EditValue);
		CString numstr;
		for (int i = 0; i < size; ++i) {
			numstr.Format(_T("%f"), pairs[i].num);
			pairs[i].edit.SetWindowText(numstr);
		}

		if (m_pTarget != NULL) {
			CVector3f tgt = m_pTarget->GetWorldMatrix().TranslationVector();
			float dst = (eye - tgt).Length();
			CString numstr;
			numstr.Format(_T("%f"), tgt.x); m_Target[0].SetWindowText(numstr);
			numstr.Format(_T("%f"), tgt.y); m_Target[1].SetWindowText(numstr);
			numstr.Format(_T("%f"), tgt.z); m_Target[2].SetWindowText(numstr);
			numstr.Format(_T("%f"), dst  ); m_Distance.SetWindowText(numstr);
		}
	}
}

