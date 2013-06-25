#include "StdAfx.h"
#include "GeometryObjObject.h"


using namespace VirtualWorld;

CGeometryOBJObject::CGeometryOBJObject(void)
	: m_pModel(NULL)
	, m_ScaleFactor(1.0f)
	, m_uDisplayList(0)
{
}

CGeometryOBJObject::~CGeometryOBJObject(void)
{
	if( m_pModel != NULL ) {
		glmDelete(m_pModel);
		m_pModel = NULL;
	}
	if(m_uDisplayList != 0) {
		glDeleteLists(m_uDisplayList, 1);
	}
}

bool CGeometryOBJObject::LoadModel( const CString& a_FileName )
{
	char* pstr = CUtility::CStringToPChar(a_FileName);
	if (pstr == NULL) {
		return false;
	}
	if (m_pModel != NULL) {
		glmDelete(m_pModel);
	}
	m_pModel = glmReadOBJ(pstr);
	if (m_pModel == NULL) {
		return false;
	}
	m_ScaleFactor = glmUnitize(m_pModel);
	glmFacetNormals(m_pModel);
	glmVertexNormals(m_pModel, 90.0f);
	m_NeedRedraw = true;
	return true;
}

void CGeometryOBJObject::Draw()
{
	if(m_pModel == NULL) {
		return;
	}
	if(m_NeedRedraw == true) {
		if(m_uDisplayList != 0) {
			glDeleteLists(m_uDisplayList, 1);
		}
		m_uDisplayList = glGenLists(1);
		glNewList(m_uDisplayList, GL_COMPILE_AND_EXECUTE );
		DrawModel();
		glEndList();
		m_NeedRedraw = false;
	} else {
		glCallList(m_uDisplayList);
	}
}

void VirtualWorld::CGeometryOBJObject::DrawModel()
{
	if(m_pModel == NULL) {
		return;
	}

	static GLuint i;
	static GLMgroup* group;
	static GLMtriangle* triangle;
	static GLMmaterial* material;

	assert(m_pModel->vertices);

#define T(x) (m_pModel->triangles[(x)])
	
	group = m_pModel->groups;
	while (group != NULL) {
		if(m_pModel->materials != NULL) {
			material = &m_pModel->materials[group->material];
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess);
		}
		GLenum drawMode = (m_DrawMode == GEOMETRY_DRAW_SOLID) ? GL_TRIANGLES : GL_LINE_LOOP;
		glBegin(drawMode);
		for (i = 0; i < group->numtriangles; i++) {
			triangle = &T(group->triangles[i]);
			
			if(m_NormalMode == GEOMETRY_NORMAL_FACET) {		// Vertex #1
				glNormal3fv(&m_pModel->facetnorms[3 * triangle->findex]);
			} else if (m_NormalMode == GEOMETRY_NORMAL_VERTEX) {
				glNormal3fv(&m_pModel->normals[3 * triangle->nindices[0]]);
			}
			glVertex3fv(&m_pModel->vertices[3 * triangle->vindices[0]]);
			
			if(m_NormalMode == GEOMETRY_NORMAL_VERTEX)	{	// Vertex #2
				glNormal3fv(&m_pModel->normals[3 * triangle->nindices[1]]);
			}
			glVertex3fv(&m_pModel->vertices[3 * triangle->vindices[1]]);

			if(m_NormalMode == GEOMETRY_NORMAL_VERTEX) {	// Vertex #3
				glNormal3fv(&m_pModel->normals[3 * triangle->nindices[2]]);
			}
			glVertex3fv(&m_pModel->vertices[3 * triangle->vindices[2]]);
		}
		glEnd();
		group = group->next;
	}// end of While

}

void VirtualWorld::CGeometryOBJObject::UpdateBoundingBox()
{
	if (m_BoundingBox != NULL) {
		CVector3f bmin;
		CVector3f bmax;
		glmBoundingBox(m_pModel, bmin, bmax);
		m_BoundingBox->SetMin(bmin);
		m_BoundingBox->SetMax(bmax);
	}
}
