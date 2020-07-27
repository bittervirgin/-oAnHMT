#pragma once
#include "OpenglView.h"
#include "Opengl.h"
#include "MainFrm.h"
#include <string>
using namespace std;
// FormView form view

class FormView : public CFormView
{
	DECLARE_DYNCREATE(FormView)

protected:
	FormView();           // protected constructor used by dynamic creation
	virtual ~FormView();

private:
	bool is_draw;
public:
	OpenglView* GetAppView();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FormView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	int obj_ind;
	afx_msg void OnBnClickedTypechoice();
	afx_msg void OnEnChangePersFar();
	afx_msg void OnBnClickedTypewired();
	afx_msg void OnBnClickedTypesolid();
	afx_msg void OnEnChangePersForvy();
	double forvy_;
	double zNear_;
	afx_msg void OnEnChangePersNear();
	double zFar_;
};


