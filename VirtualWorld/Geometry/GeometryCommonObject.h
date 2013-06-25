#pragma once
#include "..\include\virtualworld.h"

namespace VirtualWorld
{
	class CGeometryCubeObject : public IGeometryCubeObject
	{
	public:
								CGeometryCubeObject();
		virtual					~CGeometryCubeObject();
		virtual void			Draw();

	protected:
		virtual void			UpdateBoundingBox();

	protected:
		unsigned				m_DisplayListID;
		
	};

	class CGeometrySphereObject : public IGeometrySphereObject
	{
	public:
								CGeometrySphereObject();
		virtual					~CGeometrySphereObject();
		virtual void			Draw();

	protected:
		virtual void			UpdateBoundingBox();

	protected:
		GLUquadricObj*			m_GLUquadricObj;
		unsigned				m_DisplayListID;
	};

	class CGeometryCylinderObject : public IGeometryCylinderObject
	{
	public:
								CGeometryCylinderObject();
		virtual					~CGeometryCylinderObject();
		virtual void			Draw();

	protected:
		virtual void			UpdateBoundingBox();

	protected:
		GLUquadricObj*			m_GLUquadricObj;
		unsigned				m_DisplayListID;
	};
}