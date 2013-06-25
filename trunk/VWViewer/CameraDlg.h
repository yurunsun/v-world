#pragma once

#include "resource.h"

namespace VirtualWorld
{
	class ISceneCameraNode;
	class ISceneBaseNode;
}

class CCameraDlg : public CDialogImpl<CCameraDlg>
{
public:
	enum { IDD = IDD_DLG_CAMERA };

	CCameraDlg();

	BEGIN_MSG_MAP(CCameraDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void BindCamera(VirtualWorld::ISceneCameraNode* pCamera);
	void BindTarget(VirtualWorld::ISceneBaseNode* pTarget);
	void UpdateCameraProperty();

protected:
	VirtualWorld::ISceneCameraNode* m_pCamera;
	VirtualWorld::ISceneBaseNode* m_pTarget;
	CEdit m_Eye[3];
	CEdit m_FV[3];
	CEdit m_UV[3];
	CEdit m_Target[3];
	CEdit m_Distance;
};