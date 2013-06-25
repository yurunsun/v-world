#pragma once

#include "..\Include\VirtualWorld.h"

namespace VirtualWorld
{
	class CMaterial : public IMaterial
	{
	public:
		virtual void		Apply() const;
	};

}

