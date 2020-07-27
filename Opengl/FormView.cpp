// FormView.cpp : implementation file
//

#include "pch.h"
#include "Opengl.h"
#include "FormView.h"


// FormView

IMPLEMENT_DYNCREATE(FormView, CFormView)

FormView::FormView()
	: CFormView(IDD_FormView)
	
	, obj_ind(0)
	, forvy_(0)
	, zNear_(0)
	, zFar_(0)
{
	is_draw = FALSE;
}

FormView::~FormView()
{
}

OpenglView* FormView::GetAppView()
{
	OpenglApp* pApp = (OpenglApp*)AfxGetApp();
	MainFrame* pMainFrame = (MainFrame*)pApp->m_pMainWnd;
	OpenglView* pView = pMainFrame->GetMainView();
	return pView;
}

void FormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_CBIndex(pDX, IDC_ListObj, obj_ind);
	DDX_Text(pDX, IDC_Pers_Forvy, forvy_);
	DDX_Text(pDX, IDC_Pers_Near, zNear_);
	DDX_Text(pDX, IDC_Pers_Far, zFar_);
}

BEGIN_MESSAGE_MAP(FormView, CFormView)
	ON_CBN_SELCHANGE(IDC_ListObj, &FormView::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(ID_TypeChoice, &FormView::OnBnClickedTypechoice)
	ON_EN_CHANGE(IDC_Pers_Far, &FormView::OnEnChangePersFar)
	ON_BN_CLICKED(IDC_TypeWired, &FormView::OnBnClickedTypewired)
	ON_BN_CLICKED(IDC_TypeSolid, &FormView::OnBnClickedTypesolid)
	ON_EN_CHANGE(IDC_Pers_Forvy, &FormView::OnEnChangePersForvy)
	ON_EN_CHANGE(IDC_Pers_Near, &FormView::OnEnChangePersNear)
END_MESSAGE_MAP()


// FormView diagnostics

#ifdef _DEBUG
void FormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// FormView message handlers


void FormView::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (GetAppView() != NULL) {
		if (obj_ind == 0) {
			GetAppView()->set_shape("box");
			GetAppView()->set_type("none");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 1) {
			GetAppView()->set_shape("cone");
			GetAppView()->set_type("wired");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 2) {
			GetAppView()->set_shape("cube");
			GetAppView()->set_type("wired");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 3) {
			GetAppView()->set_shape("Cylinder");
			GetAppView()->set_type("none");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 4) {
			GetAppView()->set_shape("FrustumShape");
			GetAppView()->set_type("none");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 5) {
			GetAppView()->set_shape("sphere");
			GetAppView()->set_type("wired");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 6) {
			GetAppView()->set_shape("teapot");
			GetAppView()->set_type("wired");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 7) {
			GetAppView()->set_shape("wheele");
			GetAppView()->set_type("wired");
			GetAppView()->Invalidate();
		}
		if (obj_ind == 8) {
			GetAppView()->set_shape("TruncatedCone");
			GetAppView()->set_type("none");
			GetAppView()->Invalidate();
		}
	}
	
}


void FormView::OnBnClickedButton1()
{
	is_draw = !is_draw;
	if (GetAppView() != NULL) {
		GetAppView()->set_draw(is_draw);
		GetAppView()->Invalidate();
	}
	
	// TODO: Add your control notification handler code here
}


void FormView::OnBnClickedTypechoice()
{
	// TODO: Add your control notification handler code here
}


void FormView::OnEnChangePersFar()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if (GetAppView() != NULL) {
		GetAppView()->set_zFar(zFar_);
		GetAppView()->Invalidate();
	}
	// TODO:  Add your control notification handler code here
}


void FormView::OnBnClickedTypewired()
{
	// TODO: Add your control notification handler code here
	if (GetAppView() != NULL) {
		GetAppView()->set_type("wired");
		GetAppView()->Invalidate();
	}
	
}


void FormView::OnBnClickedTypesolid()
{
	// TODO: Add your control notification handler code here
	if (GetAppView() != NULL) {
		GetAppView()->set_type("solid");
		GetAppView()->Invalidate();
	}
}


void FormView::OnEnChangePersForvy()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if (GetAppView() != NULL) {
		GetAppView()->set_forvy(forvy_);
		GetAppView()->Invalidate();
	}
	// TODO:  Add your control notification handler code here
}


void FormView::OnEnChangePersNear()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if (GetAppView() != NULL) {
		GetAppView()->set_zNear(zNear_);
		GetAppView()->Invalidate();
	}
	// TODO:  Add your control notification handler code here
}
