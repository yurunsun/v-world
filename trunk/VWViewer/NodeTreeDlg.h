#pragma once

#include "resource.h"

namespace VirtualWorld
{
	class ISceneGroupNode;
	class ISceneBaseNode;
}

class CNodetreeDlg : public CDialogImpl<CNodetreeDlg>
{
public:
	enum { IDD = IDD_DLG_NODETREE };

	CNodetreeDlg(void);
	~CNodetreeDlg(void);

	BEGIN_MSG_MAP(CNodetreeDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void BindRootNode(VirtualWorld::ISceneGroupNode* pRoot);
	void UpdateNodetree();
	VirtualWorld::ISceneBaseNode* GetSelection();

protected:
	void AddGroupNode(VirtualWorld::ISceneGroupNode* pNode, HTREEITEM pParent);

protected:
	CTreeViewCtrl m_Tree;
	VirtualWorld::ISceneGroupNode* m_pRoot;
};

