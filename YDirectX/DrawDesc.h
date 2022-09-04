#pragma once
#include "Viewport.h"
#include "ScissorRect.h"

namespace DX
{
	class DrawDesc
	{
	public:
		Viewport viewport;
		ScissorRect scissorRect;
	public:
		void Set();
		void SetCommand();
	};
}
