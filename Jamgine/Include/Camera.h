#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{

	struct Camera
	{
		Position position;
		Camera()
		{
			position = Position(-1, -1);
		}
		Camera(Position l_position): position(l_position){};
	};
}