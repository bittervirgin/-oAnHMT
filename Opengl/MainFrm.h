
// MainFrm.h : interface of the MainFrame class
//

#pragma once
#include "FormView.h"
#include "OpenglView.h"

class MainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	MainFrame() noexcept;
	DECLARE_DYNCREATE(MainFrame)

// Attributes
public:

// Operations
public:
	OpenglView* GetMainView() { return app_view_; };
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);

	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
// Implementation
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	CSplitterWnd	m_wndSplitter;

	//FormView* form_view_;
	OpenglView* app_view_;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

};


