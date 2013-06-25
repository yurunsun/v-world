#pragma once
#include "..\include\virtualworld.h"

#include "atlopengl.h"

namespace VirtualWorld
{
	/**
	 * class: CWindow32 
	 * function: Implement the interface IWindow32
	 */
	class CWindow32 
		: public CWindowImpl<CWindow32>
		, public COpenGL<CWindow32>
		, public IWindow32

	{
	public:
		BEGIN_MSG_MAP_EX( CWindow32 )
			MSG_WM_CREATE(OnCreate)
			MSG_WM_DESTROY(OnDestroy)
			MSG_WM_MOVE(OnMove)
			MSG_WM_LBUTTONDOWN(OnLButtonDown)
			MSG_WM_LBUTTONUP(OnLButtonUp)
			MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
			MSG_WM_RBUTTONDOWN(OnRButtonDown)
			MSG_WM_RBUTTONUP(OnRButtonUp)
			MSG_WM_LBUTTONDBLCLK(OnRButtonDblClk)
			MSG_WM_MOUSEMOVE(OnMouseMove)
			MSG_WM_MOUSEWHEEL(OnMouseWheel)
			MSG_WM_KEYDOWN(OnKeyDown)
			MSG_WM_KEYUP(OnKeyUp)
			CHAIN_MSG_MAP(COpenGL<CWindow32>)
		END_MSG_MAP()

		int							OnCreate(LPCREATESTRUCT lpCreateStruct);
		void						OnDestroy();
		void						OnMove(const CPoint& ptPos);
		void						OnLButtonDown(unsigned nFlags, const CPoint& point);
		void						OnLButtonUp(unsigned nFlags, const CPoint& point);
		void						OnLButtonDblClk(unsigned nFlags, const CPoint& point);
		void						OnRButtonDown(unsigned nFlags, const CPoint& point);
		void						OnRButtonUp(unsigned nFlags, const CPoint& point);
		void						OnRButtonDblClk(unsigned nFlags, const CPoint& point);
		void						OnMouseMove(unsigned nFlags, const CPoint& point);
		BOOL						OnMouseWheel(unsigned nFlags, short zDelta, const CPoint& pt);
		void						OnKeyDown(unsigned nChar, unsigned nRepCnt, unsigned nFlags);
		void						OnKeyUp(unsigned nChar, unsigned nRepCnt, unsigned nFlags);

		/* Implementation of interface IWindow32 */
		virtual HWND				CreateWin (HWND hWndParent, 
										_U_RECT rect = NULL, 
										LPCTSTR szWindowName = NULL,
										DWORD dwStyle = 0,
										DWORD dwExStyle = 0,
										_U_MENUorID MenuOrID = 0U,
										LPVOID lpCreateParam = NULL);
		virtual HWND				GetHwnd() const;
		virtual BOOL				OnIdle();
		virtual BOOL				RedrawWin(CONST RECT *lprcUpdate = NULL, 
										HRGN hrgnUpdate = NULL, 
										UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
		virtual BOOL				PreTranslateMessage(MSG* pMsg);

		/* Implementation of COpenGL */
		void OnInit();
		void OnRender();
		void OnResize(const CSize& a_Size);
	};

}
