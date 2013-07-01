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
	m_modelPath = CUtility::PathToUnixStyle(a_FileName);
	/*HANDLE hr = CreateThread(NULL, 0, ThreadFuncWrapper, this, 0, NULL);
	CloseHandle(hr);*/
	return ProcessModel();
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
		ProcessNode(m_scene->mRootNode);
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
		ProcessBound(m_scene->mRootNode, minpt, maxpt, trafo);
		m_BoundingBox->SetMin(minpt);
		m_BoundingBox->SetMax(maxpt);
	}
}

bool VirtualWorld::CGeometryModelObject::ProcessModel()
{
	char* pstr = CUtility::CStringToPChar(m_modelPath);
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

void CGeometryModelObject::ProcessBound( const aiNode* nd, CVector3f& minpt, CVector3f& maxpt, aiMatrix4x4& trafo )
{
	aiMatrix4x4 prev;
	unsigned int n = 0, t;
	prev = trafo;
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
		ProcessBound(nd->mChildren[n], minpt ,maxpt, trafo);
	}
	trafo = prev;
}


void CGeometryModelObject::ProcessNode( const aiNode* nd )
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

		ProcessMaterial(m_scene->mMaterials[mesh->mMaterialIndex]);
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
	for (n = 0; n < nd->mNumChildren; ++n) {
		ProcessNode(nd->mChildren[n]);
	}
	glPopMatrix();
}


void VirtualWorld::CGeometryModelObject::ProcessMaterial( const aiMaterial *mtl )
{
	CVector4f c;

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;

	//set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	c.Set(0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse)) {
		c.Set(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	c.Set(0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular)) {
		c.Set(specular.r, specular.g, specular.b, specular.a);
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	c.Set(0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient)) {
		c.Set(ambient.r, ambient.g, ambient.b, ambient.a);
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	c.Set(0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission)) {
		c.Set(emission.r, emission.g, emission.b, emission.a);
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	if(ret1 == AI_SUCCESS) {
		max = 1;
		ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if(ret2 == AI_SUCCESS)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
		else
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		c.Set(0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glDisable(GL_CULL_FACE);
	else 
		glEnable(GL_CULL_FACE);
}
