// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "VirtualWorld.h"


class CCameraDlg;
class CNodetreeDlg;
class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, 
	public CIdleHandler,
	public VirtualWorld::IGUIEventHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CMainFrame();
	~CMainFrame();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(ID_EDIT_ANIMATION, OnEditAnimation)
		COMMAND_ID_HANDLER(ID_EDIT_SHADING, OnEditShading);
		COMMAND_ID_HANDLER(ID_EDIT_CAMERA, OnEditCamera);
		COMMAND_ID_HANDLER(ID_EDIT_NODETREE, OnEditNodetree)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes			(uncomment arguments if needed):
//	LRESULT						MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT						CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT						NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT						OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT						OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT						OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT						OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT						OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT						OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT						OnEditAnimation(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT						OnEditShading(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT						OnEditCamera(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT						OnEditNodetree(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT						OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	virtual void				OnMove(const CPoint& ptPos);
	virtual	void				OnSize(const CSize& size);
	virtual void				OnLButtonDown(unsigned nFlags, const CPoint& point);
	virtual void				OnLButtonUp(unsigned nFlags, const CPoint& point);
	virtual void				OnLButtonDblClk(unsigned nFlags, const CPoint& point);
	virtual void				OnRButtonDown(unsigned nFlags, const CPoint& point);
	virtual void				OnRButtonUp(unsigned nFlags, const CPoint& point);
	virtual void				OnRButtonDblClk(unsigned nFlags, const CPoint& point);
	virtual void				OnMouseMove(unsigned nFlags, const CPoint& point);
	virtual BOOL				OnMouseWheel(unsigned nFlags, short zDelta, const CPoint& pt);
	virtual void				OnKeyDown(unsigned nChar, unsigned nRepCnt, unsigned nFlags);
	virtual void				OnKeyUp(unsigned nChar, unsigned nRepCnt, unsigned nFlags);

protected:
	bool						DoFileOpen(const CString& a_FilePath);
	bool						DoAnimate(unsigned a_PerMilliSecond);
	bool						DoShading();
	
protected:
	DWORD						m_LastTickCount;
	CString						m_ModelName;
	bool						m_EnableAnimation;
	bool						m_EnableShading;
	VirtualWorld::IWindow32*	m_pView;
	CCameraDlg*					m_pCameraDlg;
	CNodetreeDlg*				m_pNodetreeDlg;
};
