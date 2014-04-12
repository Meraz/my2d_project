#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{

	struct Camera
	{
		Position position;
		Camera() : position(0, 0) {};

		Camera(int x, int y) : position(x, y) {};

		Camera(Position l_position): position(l_position) {};
	};
}