#pragma once

#include "../Include/VirtualWorld.h"

namespace VirtualWorld
{
	class CSceneGeometryNode
		: public ISceneGeometryNode
	{
	public:
		CSceneGeometryNode(void);
		virtual ~CSceneGeometryNode(void);

		virtual void				SetGeometryObject(IGeometryBaseObject* a_Object);
		virtual IGeometryBaseObject* GetGeometryObject() const;
		virtual void				Draw();

	protected:
		IGeometryBaseObject*		m_GeometryObject;
	};

}