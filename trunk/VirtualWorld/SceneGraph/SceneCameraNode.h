#pragma once
#include "..\include\virtualworld.h"

namespace VirtualWorld
{
	class CSceneCameraNode : public ISceneCameraNode
	{
	public:
		virtual void				Draw();
		virtual void				Apply();
		virtual void				UpdateViewPort();
	};
}


