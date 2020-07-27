
// OpenglView.h : interface of the OpenglView class
//

#pragma once
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
#include "OpenglDoc.h"

using namespace std;

class OpenglView : public CView
{
protected: // create from serialization only
	OpenglView() noexcept;
	DECLARE_DYNCREATE(OpenglView)

protected:
	bool is_draw_;
// Attributes
public:
	OpenglDoc* GetDocument() const;
	HGLRC m_hRC; //Rendering Context
	CDC* m_pDC; //Device Context

	//option shape and type of object
	string shape;
	string type;
	// View information variables
	GLfloat m_xAngle;
	GLfloat m_yAngle;
	GLfloat m_xPos;
	GLfloat m_yPos;
	GLfloat g_box;
	CPoint m_MouseDownPoint;

	GLdouble forvy;
	GLdouble zNear;
	GLdouble zFar;
// Operations
public:
	
	void RenderScene(string, string);
	//void Fustrum(float x, float y, float z, float top, float n, float f);
	BOOL InitializeOpenGL();
	BOOL SetupPixelFormat();
	//GLuint MakeCube();
	GLuint MakeBox(const float length, const float width, const float height);
	GLuint MakeFrustumShape(const float& bottom_size, const float& top_size, const float& height);
	GLuint MakePyramid(const float& size, const float& height);
	GLuint MakeTruncatedCone(const float& base_rad, const float& top_rad, const float& length);
	GLuint MakeCylinder(const float& radius, const float& length);
	
	void set_draw(bool is_draw) { is_draw_ = is_draw; };
	void set_shape(string obj) { shape = obj; };
	void set_type(string ty) { type = ty; };
	void set_forvy(double ed_forvy) { forvy = ed_forvy; };
	void set_zNear(double ed_Near) { zNear = ed_Near; };
	void set_zFar(double ed_far) { zFar = ed_far; };
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~OpenglView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in OpenglView.cpp
inline OpenglDoc* OpenglView::GetDocument() const
   { return reinterpret_cast<OpenglDoc*>(m_pDocument); }
#endif

