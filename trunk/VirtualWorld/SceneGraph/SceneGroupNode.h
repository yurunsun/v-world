#pragma once

#include "../Include/VirtualWorld.h"
#include <map>

namespace VirtualWorld
{
	class CSceneGroupNode : public ISceneGroupNode
	{
	public:
		virtual void				Draw();
	};

}