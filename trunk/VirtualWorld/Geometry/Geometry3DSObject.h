#pragma once
#include "..\include\virtualworld.h"

namespace VirtualWorld
{
	class CGeometry3DSObject :	public IGeometryModelObject
	{
	public:
		CGeometry3DSObject(void);
		virtual ~CGeometry3DSObject(void);

		virtual bool		LoadModel(const CString& a_FileName);
		virtual void		Draw();

	protected:
		virtual void		UpdateBoundingBox();
		void				DrawModel();
		void				UpdateCamera(Lib3dsCamera *c);
		void				UpdateLight(Lib3dsLight *l);
		void				RenderNode(Lib3dsNode *n);

		Lib3dsFile*			m_pModel;
		unsigned			m_uDisplayList;

		bool				m_bAntiAlias;
		bool				m_bShowBounds;
		float				m_fCurrentFrame;
		Lib3dsVector*		m_pCamera;
	};
}
