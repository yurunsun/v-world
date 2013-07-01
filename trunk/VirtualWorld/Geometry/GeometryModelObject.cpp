#include "StdAfx.h"
#include "GeometryModelObject.h"

using namespace VirtualWorld;

CGeometryModelObject::CGeometryModelObject()
	: m_uDisplayList(0)
	, m_scene(NULL)
{
}

CGeometryModelObject::~CGeometryModelObject(void)
{
	if (m_scene != NULL) {
		//delete m_scene;
		//m_scene = NULL;
	}
	if(m_uDisplayList != 0) {
		glDeleteLists(m_uDisplayList, 1);
	}
}

bool CGeometryModelObject::LoadModel( const CString& a_FileName )
{
	CString unixPath = CUtility::PathToUnixStyle(a_FileName);
	char* pstr = CUtility::CStringToPChar(unixPath);
	if (pstr == NULL) {
		return false;
	}
	const aiScene* cscene = aiImportFile(pstr, aiProcessPreset_TargetRealtime_MaxQuality);
	m_scene = const_cast<aiScene*>(cscene);
	if (m_scene == NULL) {
		return false;
	}
	UpdateBoundingBox();
	m_NeedRedraw = true;
	return true;
}

void CGeometryModelObject::Draw()
{
	if(m_scene == NULL) {
		return;
	}
	if(m_NeedRedraw == true) {
		if(m_uDisplayList != 0) {
			glDeleteLists(m_uDisplayList, 1);
		}
		m_uDisplayList = glGenLists(1);
		glNewList(m_uDisplayList, GL_COMPILE_AND_EXECUTE );
		DrawNode(m_scene->mRootNode);
		glEndList();
		m_NeedRedraw = false;
	} else {
		glCallList(m_uDisplayList);
	}
}

void CGeometryModelObject::UpdateBoundingBox()
{
	if (m_BoundingBox != NULL) {
		CVector3f minpt(1e10f, 1e10f, 1e10f);
		CVector3f maxpt(-1e10f, -1e10f, -1e10f);
		aiMatrix4x4 trafo;
		GetBounding(m_scene->mRootNode, minpt, maxpt, trafo);
		m_BoundingBox->SetMax(minpt);
		m_BoundingBox->SetMin(maxpt);
	}
}

void CGeometryModelObject::GetBounding( const struct aiNode* nd, CVector3f& minpt, CVector3f& maxpt, aiMatrix4x4& trafo )
{
	aiMatrix4x4 prev;
	unsigned int n = 0, t;
	prev = trafo;
	aiMultiplyMatrix4(&trafo, &nd->mTransformation);
	aiMultiplyMatrix4(&trafo, &nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = m_scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {
			aiVector3D tempt = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tempt, &trafo);
			minpt.x = min(minpt.x, tempt.x);
			minpt.y = min(minpt.y, tempt.y);
			minpt.z = min(minpt.z, tempt.z);

			maxpt.x = max(maxpt.x, tempt.x);
			maxpt.y = max(maxpt.y, tempt.y);
			maxpt.z = max(maxpt.z, tempt.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		GetBounding(nd->mChildren[n], minpt ,maxpt, trafo);
	}
	trafo = prev;
}


void CGeometryModelObject::DrawNode( const struct aiNode* nd )
{
	if(m_scene == NULL) {
		return;
	}
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;

	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = m_scene->mMeshes[nd->mMeshes[n]];

		//apply_material(sc->mMaterials[mesh->mMaterialIndex]);
		for (t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];
			GLenum face_mode = (m_DrawMode == GEOMETRY_DRAW_SOLID) ? GL_POLYGON : GL_LINES;
			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if(mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if(mesh->mNormals != NULL) 
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		DrawNode(nd->mChildren[n]);
	}

	glPopMatrix();
	
}

