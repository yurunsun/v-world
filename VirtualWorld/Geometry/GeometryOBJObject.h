#pragma once
#include "..\include\virtualworld.h"

namespace VirtualWorld
{
	class CGeometryOBJObject : public IGeometryModelObject
	{
	public:
		CGeometryOBJObject(void);
		virtual ~CGeometryOBJObject(void);

		virtual bool			LoadModel(const CString& a_FileName);
		virtual void			Draw();

	protected:
		virtual	void			UpdateBoundingBox();
		void					DrawModel();
		GLMmodel*				m_pModel;
		float					m_ScaleFactor;
		unsigned				m_uDisplayList;
	};

}