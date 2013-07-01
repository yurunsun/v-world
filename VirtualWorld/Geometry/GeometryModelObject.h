#pragma once
#include "..\include\virtualworld.h"


struct aiScene;
struct aiNode;
namespace VirtualWorld
{
	class CGeometryModelObject : public IGeometryModelObject
	{
	public:
								CGeometryModelObject();
								~CGeometryModelObject();
		virtual bool			LoadModel(const CString& a_FileName);
		virtual void			Draw();

	protected:
		virtual void			UpdateBoundingBox();
		bool					ProcessModel();
		void					ProcessNode(const aiNode* nd);
		void					ProcessBound(const aiNode* nd, CVector3f& minpt, CVector3f& maxpt, aiMatrix4x4& trafo);
		void					ProcessMaterial(const aiMaterial *mtl);

	protected:
		unsigned				m_uDisplayList;
		aiScene*				m_scene;
		CString					m_modelPath;
	};
}