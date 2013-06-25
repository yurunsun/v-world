#pragma once
#include "..\Include\VirtualWorld.h"

namespace VirtualWorld
{
	class CSceneLightNode : public ISceneLightNode
	{
	public:
									CSceneLightNode();
		virtual						~CSceneLightNode();
		virtual void				Draw();

	protected:
		void						DrawLight();

	protected:
		unsigned					m_DisplayListID;
		bool						m_NeedRedraw;
		static int					m_NoOfLights;
	};
}

