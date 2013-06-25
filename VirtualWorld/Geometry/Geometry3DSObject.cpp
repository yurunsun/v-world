#include "stdafx.h"
#include "Geometry3DSObject.h"

using namespace VirtualWorld;

VirtualWorld::CGeometry3DSObject::CGeometry3DSObject(void)
	: m_pModel(NULL)
	, m_uDisplayList(0)
	, m_bAntiAlias(false)
{
}


VirtualWorld::CGeometry3DSObject::~CGeometry3DSObject(void)
{
	if(m_pModel != NULL) {
		lib3ds_file_free(m_pModel);
		m_pModel = NULL;
	}
	if(m_uDisplayList != 0) {
		glDeleteLists(m_uDisplayList, 1);
	}
}

bool VirtualWorld::CGeometry3DSObject::LoadModel(const CString& a_FileName)
{
	char * pstr = CUtility::CStringToPChar(a_FileName);
	if (pstr != NULL) {
		if (m_pModel != NULL) {
			lib3ds_file_free(m_pModel);
		}
		m_pModel = lib3ds_file_load(pstr);
		if (m_pModel != NULL) {
			lib3ds_file_eval(m_pModel,0.0f);
			m_NeedRedraw = true;
			return true;
		}
	}
	return false;
}

void VirtualWorld::CGeometry3DSObject::Draw()
{
	if(m_pModel != NULL) {
		if(m_NeedRedraw == true) {
			if(m_uDisplayList != 0) {
				glDeleteLists(m_uDisplayList,1);
			}
			m_NeedRedraw=false;
			m_uDisplayList = glGenLists(1);
			glNewList(m_uDisplayList,GL_COMPILE_AND_EXECUTE);
			DrawModel();
			glEndList();
		} else {
			glCallList(m_uDisplayList);
		}
	}
}

void VirtualWorld::CGeometry3DSObject::UpdateCamera(Lib3dsCamera *c)
{

}

void VirtualWorld::CGeometry3DSObject::UpdateLight(Lib3dsLight *light)
{
	Lib3dsNode* ln = lib3ds_file_node_by_name(m_pModel, light->name, LIB3DS_LIGHT_NODE);
	Lib3dsNode* sn = lib3ds_file_node_by_name(m_pModel, light->name, LIB3DS_SPOT_NODE);

	if( ln != NULL ) {
		memcpy(light->color, ln->data.light.col, sizeof(Lib3dsRgb));
		memcpy(light->position, ln->data.light.pos, sizeof(Lib3dsVector));
	}
	if( sn != NULL ) {
		memcpy(light->spot, sn->data.spot.pos, sizeof(Lib3dsVector));
	}
}

void VirtualWorld::CGeometry3DSObject::RenderNode(Lib3dsNode *node)
{
	struct PlayerTexture
	{
		int valid; // was the loading attempt successful ? 
		void *bitmap;
		GLuint tex_id; //OpenGL texture ID
		float scale_x, scale_y; // scale the texcoords, as OpenGL thinks in TEX_XSIZE and TEX_YSIZE
	};

	PlayerTexture *pt=NULL;
	int tex_mode;

	for (Lib3dsNode *p = node->childs; p != 0; p = p->next) {
		RenderNode(p);
	}

	if (node->type == LIB3DS_OBJECT_NODE) {
		Lib3dsMesh *mesh;
		if (strcmp(node->name, "$$$DUMMY")==0) {
			return;
		}
		mesh = lib3ds_file_mesh_by_name(m_pModel, node->data.object.morph);
		if( mesh == NULL ) {
			mesh = lib3ds_file_mesh_by_name(m_pModel, node->name);
			if (mesh == NULL) {
				return;
			}
		}
		glPushMatrix();
		glMultMatrixf(&(node->matrix[0][0]));
		Lib3dsObjectData *d = &node->data.object;
		glTranslatef(-d->pivot[0], -d->pivot[1], -d->pivot[2]);
		{
			unsigned p;
			Lib3dsVector *normalL=(Lib3dsVector*)malloc(3*sizeof(Lib3dsVector)*mesh->faces);
			Lib3dsMaterial *oldmat = (Lib3dsMaterial *)-1;
			{
				Lib3dsMatrix M;
				lib3ds_matrix_copy(M, mesh->matrix);
				lib3ds_matrix_inv(M);
				glMultMatrixf(&M[0][0]);
			}
			lib3ds_mesh_calculate_normals(mesh, normalL);

			for (p = 0; p < mesh->faces; ++p) {
				Lib3dsFace *f = &mesh->faceL[p];
				Lib3dsMaterial *mat = 0;
				if (f->material[0]) {
					mat = lib3ds_file_material_by_name(m_pModel, f->material);
				}
				if(mat != oldmat) {
					if (mat) {
						if( mat->two_sided ) {
							glDisable(GL_CULL_FACE);
						} else {
							glEnable(GL_CULL_FACE);
						}

						if (mat->texture1_map.name[0]) {		
							Lib3dsTextureMap *tex = &mat->texture1_map;	/* texture map? */
							if (!tex->user.p) {		
								char texname[1024];	/* no player texture yet? */
								pt = (PlayerTexture *)malloc(sizeof(*pt));
								tex->user.p = pt;
								strcat_s(texname, "/");
								strcat_s(texname, tex->name);

								pt->bitmap = NULL;
								fputs("3dsplayer: Warning: No image loading support, skipping texture.\n", stderr);

								if (pt->bitmap) {	
									int upload_format = GL_RED; /* safe choice, shows errors */
									pt->valid = 1;
								} else {
									fprintf(stderr, "Load of texture %s did not succeed ", "(format not supported !)\n", texname);
									pt->valid = 0;
								}
							}
							else {
								pt = (PlayerTexture *)tex->user.p;
							}
							tex_mode = pt->valid;
						}
						else {
							tex_mode = 0;
						}
						glMaterialfv(GL_FRONT, GL_AMBIENT, mat->ambient);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, mat->diffuse);
						glMaterialfv(GL_FRONT, GL_SPECULAR, mat->specular);
						glMaterialf(GL_FRONT, GL_SHININESS, (float)pow(2, 10.0*mat->shininess));
					}
					else {
						static const Lib3dsRgba a={0.7f, 0.7f, 0.7f, 1.0f};
						static const Lib3dsRgba d={0.7f, 0.7f, 0.7f, 1.0f};
						static const Lib3dsRgba s={1.0f, 1.0f, 1.0f, 1.0f};
						glMaterialfv(GL_FRONT, GL_AMBIENT, a);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
						glMaterialfv(GL_FRONT, GL_SPECULAR, s);
						glMaterialf(GL_FRONT, GL_SHININESS, (float)pow(2, 10.0*0.5));
					}
					oldmat = mat;
				}
				else if (mat != NULL && mat->texture1_map.name[0]) {
					Lib3dsTextureMap *tex = &mat->texture1_map;
					if (tex != NULL && tex->user.p != NULL) {
						pt = (PlayerTexture *)tex->user.p;
						tex_mode = pt->valid;
					}
				}
				{
					if (tex_mode) {
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, pt->tex_id);
					}
					GLenum drawMode = (m_DrawMode == GEOMETRY_DRAW_SOLID) ? GL_TRIANGLES : GL_LINE_LOOP;
					glBegin(drawMode);
					glNormal3fv(f->normal);
					for (int i = 0; i < 3; ++i) {
						glNormal3fv(normalL[3*p+i]);

						if (tex_mode) {
							glTexCoord2f(mesh->texelL[f->points[i]][1]*pt->scale_x,
							pt->scale_y - mesh->texelL[f->points[i]][0]*pt->scale_y);
						}
						float x=mesh->pointL[f->points[i]].pos[0];
						float y=mesh->pointL[f->points[i]].pos[1];
						float z=mesh->pointL[f->points[i]].pos[2];
						glVertex3fv(mesh->pointL[f->points[i]].pos);
					}
					glEnd();

					if (tex_mode) {
						glDisable(GL_TEXTURE_2D);
					}
				}
			}
			free(normalL);
		}
		glPopMatrix();
	}
}

/*
 * Background, anti-alias are controlled globally. Ignore the property defined in model file
 */
void VirtualWorld::CGeometry3DSObject::DrawModel()
{
	if(m_pModel == NULL) {
		return;
	}
	Lib3dsNode *p;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, m_pModel->ambient);
	{
		static const GLfloat a[] = {0.0f, 0.0f, 0.0f, 1.0f};
		static GLfloat c[] = {1.0f, 1.0f, 1.0f, 1.0f};
		static GLfloat p[] = {0.0f, 0.0f, 0.0f, 1.0f};

		for (Lib3dsLight *l = m_pModel->lights; l != NULL; l = l->next) {
			UpdateLight(l);
			ISceneLightNode* light = CFactory::GetInstance()->CreateSceneLightNode();
			light->SetAmbient(CVector4f(0.0f, 0.0f, 0.0f, 1.0f));
			light->SetDiffuse(CVector4f(l->color[0], l->color[1], l->color[2], 1.0f));
			light->SetSpecular(CVector4f(l->color[0], l->color[1], l->color[2], 1.0f));
			light->SetPosition(CVector4f(l->position[0], l->position[1], l->position[2], 0.0f));

			if (l->spot_light) {
				light->SetSpotDirection(CVector3f(l->spot[0] - l->position[0], l->spot[1] - l->position[1], l->spot[2] - l->position[2]));
			}
			light->Draw();
		}
	}
	for (p = m_pModel->nodes; p != 0; p = p->next) {
		RenderNode(p);
	}
}

void VirtualWorld::CGeometry3DSObject::UpdateBoundingBox()
{
	if (m_BoundingBox != NULL) {
		CVector3f bmin;
		CVector3f bmax;
		lib3ds_file_eval(m_pModel, 0.0f);
		lib3ds_file_bounding_box_of_nodes(m_pModel, LIB3DS_TRUE, LIB3DS_FALSE, LIB3DS_FALSE, bmin, bmax);
		m_BoundingBox->SetMin(bmin);
		m_BoundingBox->SetMax(bmax);
	}
}
