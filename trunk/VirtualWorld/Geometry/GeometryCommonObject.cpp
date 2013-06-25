#include "StdAfx.h"
#include "GeometryCommonObject.h"
#include "../Include/VirtualWorld.h"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

using namespace VirtualWorld;

VirtualWorld::CGeometryCubeObject::CGeometryCubeObject()
	: m_DisplayListID(0)
{
}


VirtualWorld::CGeometryCubeObject::~CGeometryCubeObject()
{
	if (m_DisplayListID != 0) {
		glDeleteLists(m_DisplayListID, 0);
	}
}

void VirtualWorld::CGeometryCubeObject::Draw()
{
	if (m_NeedRedraw == true) {
		this->UpdateBoundingBox();

		// Create m_DisplayListID
		if (m_DisplayListID != 0) {
			glDeleteLists(m_DisplayListID, 1);
		}
		m_DisplayListID = glGenLists(1);
		glNewList(m_DisplayListID, GL_COMPILE_AND_EXECUTE);

		if (m_Material != NULL) {
			m_Material->Apply();
		}
		static int faces[6][4] = {
			{0, 1, 2, 3}, {1, 5, 6, 2}, {5, 4, 7, 6},
			{4, 0, 3, 7}, {2, 6, 7, 3}, {0, 4, 5, 1}
		};
		static float normals[6][3] = {
			{-1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0},
			{0.0, 0.0, -1.0}, {0.0, 1.0, 0.0}, {0.0, -1.0, 0.0}
		};

		float v[8][3];
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -m_Radius;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = m_Radius;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = -m_Radius;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = m_Radius;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = -m_Radius;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = m_Radius;
		glBegin( GL_QUADS );
		for (int i = 0; i < 6; ++i) {
			glNormal3fv(&normals[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
		}
		glEnd();

		// End of m_DisplayListID
		glEndList();
		m_NeedRedraw = false;
	} else {
		glCallList(m_DisplayListID);
	}
}

void VirtualWorld::CGeometryCubeObject::UpdateBoundingBox()
{
	if (m_BoundingBox != NULL) {
		float r = (float)(m_Radius * 1.2);
		m_BoundingBox->SetMax(CVector3f(r, r, r));
		m_BoundingBox->SetMin(CVector3f(-r, -r, -r));
	}
}

VirtualWorld::CGeometrySphereObject::CGeometrySphereObject()
	: m_GLUquadricObj(NULL)
	, m_DisplayListID(0)
{
}

VirtualWorld::CGeometrySphereObject::~CGeometrySphereObject()
{
	if (m_GLUquadricObj != NULL) {
		gluDeleteQuadric(m_GLUquadricObj);
		m_GLUquadricObj = NULL;
	}
	if (m_DisplayListID != 0) {
		glDeleteLists(m_DisplayListID, 0);
	}
}

void VirtualWorld::CGeometrySphereObject::Draw()
{
	if (m_NeedRedraw == true) {
		this->UpdateBoundingBox();

		// Create m_GLUquadricObj
		if (m_GLUquadricObj != NULL) {
			gluDeleteQuadric(m_GLUquadricObj);
		}
		m_GLUquadricObj = gluNewQuadric();

		GLenum drawStyle = (m_DrawMode == GEOMETRY_DRAW_SOLID) ? GLU_FILL : GLU_LINE;
		GLenum normal = (m_NormalMode == GEOMETRY_NORMAL_VERTEX) ? GLU_SMOOTH : GLU_FLAT;
		gluQuadricDrawStyle(m_GLUquadricObj, drawStyle); 
		gluQuadricNormals(m_GLUquadricObj, normal);

		// Create m_DisplayListID
		if (m_DisplayListID != 0) {
			glDeleteLists(m_DisplayListID, 1);
		}
		m_DisplayListID = glGenLists(1);
		glNewList(m_DisplayListID, GL_COMPILE_AND_EXECUTE);

		// Call OpenGL commands
		if (m_Material != NULL) {
			m_Material->Apply();
		}
		gluSphere(m_GLUquadricObj, m_Radius, m_Slices, m_Stacks);

		// End of m_DisplayListID
		glEndList();
		m_NeedRedraw = false;
	} else {
		glCallList(m_DisplayListID);
	}
}

void VirtualWorld::CGeometrySphereObject::UpdateBoundingBox()
{
	if (m_BoundingBox != NULL) {
		m_BoundingBox->SetMax(CVector3f(m_Radius, m_Radius, m_Radius));
		m_BoundingBox->SetMin(CVector3f(-m_Radius, -m_Radius, -m_Radius));
	}
}

VirtualWorld::CGeometryCylinderObject::CGeometryCylinderObject()
	: m_GLUquadricObj(NULL)
	, m_DisplayListID(0)
{
}

VirtualWorld::CGeometryCylinderObject::~CGeometryCylinderObject()
{
	if (m_GLUquadricObj != NULL) {
		gluDeleteQuadric(m_GLUquadricObj);
		m_GLUquadricObj = NULL;
	}
	if (m_DisplayListID != 0) {
		glDeleteLists(m_DisplayListID, 0);
	}
}

void VirtualWorld::CGeometryCylinderObject::Draw()
{
	if (m_NeedRedraw == true) {
		this->UpdateBoundingBox();

		// Create m_GLUquadricObj
		if (m_GLUquadricObj != NULL) {
			gluDeleteQuadric(m_GLUquadricObj);
		}
		m_GLUquadricObj = gluNewQuadric();

		GLenum drawStyle = (m_DrawMode == GEOMETRY_DRAW_SOLID) ? GLU_FILL : GLU_LINE;
		GLenum normal = (m_NormalMode == GEOMETRY_NORMAL_VERTEX) ? GLU_SMOOTH : GLU_FLAT;
		gluQuadricDrawStyle(m_GLUquadricObj, drawStyle); 
		gluQuadricNormals(m_GLUquadricObj, normal);

		// Create m_DisplayListID
		if (m_DisplayListID != 0) {
			glDeleteLists(m_DisplayListID, 1);
		}
		m_DisplayListID = glGenLists(1);
		glNewList(m_DisplayListID, GL_COMPILE_AND_EXECUTE);

		// Call OpenGL commands
		if (m_Material != NULL) {
			m_Material->Apply();
		}
		gluCylinder(m_GLUquadricObj, m_BaseRadius, m_TopRadius, m_Height, m_Slices, m_Stacks);

		// End of m_DisplayListID
		glEndList();
		m_NeedRedraw = false;
	} else {
		glCallList(m_DisplayListID);
	}
}

void VirtualWorld::CGeometryCylinderObject::UpdateBoundingBox()
{
	if (m_BoundingBox != NULL) {
		// TODO: calculate this bounding box of cylinder
	}
}
