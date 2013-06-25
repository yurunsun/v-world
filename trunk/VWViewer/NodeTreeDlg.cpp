#include "StdAfx.h"
#include "NodeTreeDlg.h"

#include "../Include/VirtualWorld.h"

using namespace VirtualWorld;

CNodetreeDlg::CNodetreeDlg(void)
	: m_pRoot(NULL)
{
}

CNodetreeDlg::~CNodetreeDlg(void)
{
}

LRESULT CNodetreeDlg::OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_Tree = GetDlgItem(IDC_NODETREE);
	BOOL hr = this->ModifyStyleEx(0, WS_EX_LAYERED);
	if (hr == TRUE) {
		SetLayeredWindowAttributes(this->m_hWnd, RGB(255, 0, 255), 128, LWA_ALPHA | LWA_COLORKEY);
	}
	return 0;
}

LRESULT CNodetreeDlg::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	this->ShowWindow(SW_HIDE);
	return 0;
}

void CNodetreeDlg::BindRootNode( ISceneGroupNode* pRoot )
{
	m_pRoot = pRoot;
}

inline CString ConcateNodename( ISceneBaseNode* pNode )
{
	CString ret;
	if (pNode != NULL) {
		ret.Format(_T("[%s]%s"), pNode->GetNodeTypeString(), pNode->GetName());
	}
	return ret;
}

void CNodetreeDlg::UpdateNodetree()
{
	m_Tree.DeleteAllItems();
	if (m_pRoot != NULL) {
		AddGroupNode(m_pRoot, TVI_ROOT);
		m_Tree.SelectItem(m_Tree.GetRootItem());
	}
}

void CNodetreeDlg::AddGroupNode( ISceneGroupNode* pNode, HTREEITEM pParent )
{
	if (pNode != NULL) {
		HTREEITEM r = m_Tree.InsertItem(ConcateNodename(pNode), pParent, TVI_LAST);
		ISceneGroupNode::NodeTable children = pNode->GetChildren();
		for (auto it = children.begin(); it != children.end(); ++it) {
			if (it->second->GetNodeType() == ISceneBaseNode::SCENE_GROUP_NODE) {
				ISceneGroupNode* p = dynamic_cast<ISceneGroupNode*>(it->second);
				if (p != NULL) {
					AddGroupNode(p, r);
				}
			} else {
				m_Tree.InsertItem(ConcateNodename(it->second), r, TVI_LAST);
			}
		}
		m_Tree.Expand(r);
	}
}

ISceneBaseNode* CNodetreeDlg::GetSelection()
{
	if (m_pRoot != NULL) {
		CString name;
		BOOL hr = m_Tree.GetItemText(m_Tree.GetSelectedItem(), name);
		if (hr == TRUE) {
			name = name.Right(name.GetLength() - name.Find(_T(']')) - 1);
			if (m_pRoot->GetName() == name) {
				return m_pRoot;
			} else {
				return m_pRoot->GetChild(name);
			}
		}
	}
	return NULL;
}

