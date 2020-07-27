
// OpenglView.cpp : implementation of the OpenglView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Opengl.h"
#endif

#include "OpenglDoc.h"
#include "OpenglView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// OpenglView

IMPLEMENT_DYNCREATE(OpenglView, CView)

BEGIN_MESSAGE_MAP(OpenglView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &OpenglView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// OpenglView construction/destruction

OpenglView::OpenglView() noexcept
{
	// TODO: add construction code here
	is_draw_ = FALSE;
	zNear = .01f;
	zFar = 200.0f;
	forvy = 45.0f;
}

OpenglView::~OpenglView()
{
}

BOOL OpenglView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// OpenglView drawing

void OpenglView::OnDraw(CDC* pDC)
{
	OpenglDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// Clear out the color & depth buffers
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*
	if (is_cube_==TRUE) {
		UpdateData(TRUE);
		shape = "cube";
	}
	if (&FormView::is_teapot) {
		UpdateData(TRUE);
		shape = "teapot";
	}
	if (&FormView::OnBnClickedWheele) {
		UpdateData(TRUE);
		shape = "wheele";
	}
	*/
	
	if (is_draw_) {
		shape = "teapot";
	}
	
	//shape = GetShape();
	RenderScene(shape, type);

	// Tell OpenGL to flush its pipeline
	::glFinish();
	// Now Swap the buffers
	::SwapBuffers(m_pDC->GetSafeHdc());
	
}


// OpenglView printing


void OpenglView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL OpenglView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void OpenglView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void OpenglView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void OpenglView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void OpenglView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// OpenglView diagnostics

#ifdef _DEBUG
void OpenglView::AssertValid() const
{
	CView::AssertValid();
}

void OpenglView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

OpenglDoc* OpenglView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(OpenglDoc)));
	return (OpenglDoc*)m_pDocument;
}
#endif //_DEBUG


// OpenglView message handlers

void OpenglView::RenderScene(string shape, string type)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(5.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	//DrawCoodinate();
	glPushMatrix();
	//glTranslatef(m_xPos, m_yPos, 1.0f);
	//glTranslatef(m_xPos, m_yPos, -5.0f);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);

	//glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0, 0.5, 0.5);

	if (type == "none") {
		if (shape == "Cylinder") {
			g_box = MakeCylinder(1.5, 3.0);
			glCallList(g_box);
		}
		if (shape == "TruncatedCone") {
			g_box = MakeTruncatedCone(1.0, 2.0, 1.5);
			glCallList(g_box);
		}
		if (shape == "box") {
			g_box = MakeBox(1.0, 2.0, 2.5);
			glCallList(g_box);
		}
		if (shape == "FrustumShape") {
			g_box = MakeFrustumShape(1.0, 2.0, 2.5);
			glCallList(g_box);
		}

	}

	if (type == "wired") {
		if (shape == "teapot") {
			glutWireTeapot(1.0);
		}
		if (shape == "cone") {
			glutWireCone(1., 1.0, 10.0, 10.0);
		}
		if (shape == "cube") {
			glutWireCube(1.5);
		}
		if (shape == "sphere") {
			glutWireSphere(1.0, 3.0, 5.0);
		}
		if (shape == "wheele") {
			glutWireTorus(0.5, 2.0, 10.0, 10.0);
		}
	}
	if (type == "solid") {
		if (shape == "teapot") {
			glutSolidTeapot(1.0);
		}
		if (shape == "cone") {
			glutSolidCone(0.1, 1.0, 2.0, 2.0);
		}
		if (shape == "cube") {
			glutWireCube(3.0);
		}
		if (shape == "sphere") {
			glutSolidSphere(1.0, 3.0, 5.0);
		}
		if (shape == "wheele") {
			glutSolidTorus(0.5, 2.0, 10.0, 10.0);
		}
	}
	glPopMatrix();

	//glutSwapBuffers();
	glFlush();
}

BOOL OpenglView::InitializeOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);

	//Failure to Get DC
	if (m_pDC == NULL)
	{
		MessageBox((LPCTSTR)"Error Obtaining DC");
		return FALSE;
	}
	//Failure to set the pixel format
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	//Create Rendering Context
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());

	//Failure to Create Rendering Context
	if (m_hRC == 0)
	{
		MessageBox((LPCTSTR)"Error Creating RC");
		return FALSE;
	}
	//Make the RC Current
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		MessageBox((LPCTSTR)"Error making RC Current");
		return FALSE;
	}
	//Specify Black as the clear color
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Specify the back of the buffer as clear depth
	::glClearDepth(1.0f);

	//Enable Depth Testing
	::glEnable(GL_DEPTH_TEST);
	return TRUE;
}

BOOL OpenglView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
		1,                                // version number
		PFD_DRAW_TO_WINDOW |              // support window
		PFD_SUPPORT_OPENGL |              // support OpenGL
		PFD_DOUBLEBUFFER,                 // double buffered
		PFD_TYPE_RGBA,                    // RGBA type
		24,                               // 24-bit color depth
		0, 0, 0, 0, 0, 0,                 // color bits ignored
		0,                                // no alpha buffer
		0,                                // shift bit ignored
		0,                                // no accumulation buffer
		0, 0, 0, 0,                       // accumulation bits ignored
		16,                               // 16-bit z-buffer
		0,                                // no stencil buffer
		0,                                // no auxiliary buffer
		PFD_MAIN_PLANE,                   // main layer
		0,                                // reserved
		0, 0, 0                           // layer masks ignored
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	if (m_nPixelFormat == 0)
	{
		return FALSE;
	}
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

GLuint OpenglView::MakeBox(const float length, const float width, const float height)
{
	GLuint dp_list;
	dp_list = glGenLists(2);
	glNewList(dp_list, GL_COMPILE);
	float x = length;
	float y = height;
	float z = width;

	//Back
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(0, y, 0);
	glEnd();

	// left
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, z);
	glVertex3f(0, y, z);
	glVertex3f(0, y, 0);
	glEnd();

	//front
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, z);
	glVertex3f(0, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, 0, z);
	glEnd();

	//// right
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, 0, z);
	glVertex3f(x, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x, y, z);
	glEnd();

	//Top
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, y, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x, y, z);
	glVertex3f(0, y, z);

	//Bottom
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, 0, z);
	glVertex3f(0, 0, z);

	glEnd();

	glEndList();
	return dp_list;
}

GLuint OpenglView::MakeFrustumShape(const float& bottom_size, const float& top_size, const float& height)
{
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	double half_bottom_size = 0.5 * bottom_size;
	double half_top_size = 0.5 * top_size;

	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-half_bottom_size, 0.0, half_bottom_size);
	glVertex3f(half_bottom_size, 0.0, half_bottom_size);
	glVertex3f(half_top_size, height, half_top_size);
	glVertex3f(-half_top_size, height, half_top_size);
	// Back Face
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-half_bottom_size, 0.0, -half_bottom_size);
	glVertex3f(half_bottom_size, 0.0, -half_bottom_size);
	glVertex3f(half_top_size, height, -half_top_size);
	glVertex3f(-half_top_size, height, -half_top_size);

	// Top Face
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-half_top_size, height, -half_top_size);
	glVertex3f(-half_top_size, height, half_top_size);
	glVertex3f(half_top_size, height, half_top_size);
	glVertex3f(half_top_size, height, -half_top_size);
	// Bottom Face
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-half_bottom_size, 0.0, -half_bottom_size);
	glVertex3f(half_bottom_size, 0.0, -half_bottom_size);
	glVertex3f(half_bottom_size, 0.0, half_bottom_size);
	glVertex3f(-half_bottom_size, 0.0, half_bottom_size);
	// Right face
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(half_bottom_size, 0.0, -half_bottom_size);
	glVertex3f(half_bottom_size, 0.0, half_bottom_size);
	glVertex3f(half_top_size, height, half_top_size);
	glVertex3f(half_top_size, height, -half_top_size);
	// Left Face
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-half_bottom_size, 0.0, -half_bottom_size);
	glVertex3f(-half_bottom_size, 0.0, half_bottom_size);
	glVertex3f(-half_top_size, height, half_top_size);
	glVertex3f(-half_top_size, height, -half_top_size);
	glEnd();

	glEndList();

	return dp_list;
}

GLuint OpenglView::MakePyramid(const float& size, const float& height)
{
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	double half_size = size * 0.5;
	glBegin(GL_TRIANGLES);
	//Front face
	glNormal3f(0.0, 0.0, 1.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(-half_size, 0, half_size);
	glVertex3f(half_size, 0, half_size);

	//left face
	glNormal3f(-1.0, 0.0, 0.0f);
	glVertex3f(0.0, height, 0.0);
	glVertex3f(-half_size, 0.0, -half_size);
	glVertex3f(-half_size, 0.0, half_size);

	//back face
	glNormal3f(0.0, 0.0, -1.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(-half_size, 0, -half_size);
	glVertex3f(half_size, 0, -half_size);

	//Right face
	glNormal3f(1.0, 0.0, 0.0f);
	glVertex3f(0.0, height, 0.0);
	glVertex3f(half_size, 0.0, -half_size);
	glVertex3f(half_size, 0.0, half_size);
	glEnd();

	//Bottom face
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0f);
	glVertex3f(half_size, 0.0, half_size);
	glVertex3f(half_size, 0.0, -half_size);
	glVertex3f(-half_size, 0.0, -half_size);
	glVertex3f(-half_size, 0.0, half_size);
	glEnd();
	glEndList();

	return dp_list;
}

GLuint OpenglView::MakeTruncatedCone(const float& base_rad, const float& top_rad, const float& length)
{
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	GLUquadricObj* quadratic_obj;
	quadratic_obj = gluNewQuadric();
	gluCylinder(quadratic_obj, base_rad, top_rad, length, 32, 32);
	glEndList();

	return dp_list;
}

GLuint OpenglView::MakeCylinder(const float& radius, const float& length)
{
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	GLUquadricObj* quadratic_obj;
	quadratic_obj = gluNewQuadric();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(quadratic_obj, radius, radius, length, 32, 32);
	glEndList();
	return dp_list;
}


void OpenglView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	GLdouble aspect_ratio; // width/height ratio
	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	// select the full client area
	::glViewport(0, 0, cx, cy);

	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	// select the projection matrix and clear it
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	// select the viewing volume
	//glFrustum(-0.5, 0.5, -0.5, 0.5, 0.5, 3);

	::gluPerspective(forvy, aspect_ratio, zNear, zFar);

	// switch back to the modelview matrix and clear it
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


int OpenglView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//Initialize OpenGL Here
	InitializeOpenGL();

	return 0;
}


void OpenglView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	//Make the RC non-current
	if (::wglMakeCurrent(0, 0) == FALSE)
	{
		MessageBox((LPCTSTR)"Could not make RC non-current");
	}
	//Delete the rendering context
	if (::wglDeleteContext(m_hRC) == FALSE)
	{
		MessageBox((LPCTSTR)"Could not delete RC");
	}
	//Delete the DC
	if (m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;
}


BOOL OpenglView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//comment out the original call
	//return CView::OnEraseBkgnd(pDC);
	//Tell Windows not to erase the background
	return TRUE;
}


void OpenglView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_MouseDownPoint = point;
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void OpenglView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_MouseDownPoint = CPoint(0, 0);
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


void OpenglView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// Check if we have captured the mouse
	if (GetCapture() == this)
	{
		//Increment the object rotation angles
		m_xAngle += (point.y - m_MouseDownPoint.y) / 3.6;
		m_yAngle += (point.x - m_MouseDownPoint.x) / 3.6;
		//Redraw the view
		InvalidateRect(NULL, FALSE);
		//Set the mouse point
		m_MouseDownPoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}
