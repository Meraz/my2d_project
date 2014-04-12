#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{

	struct Camera
	{
		Position position;
		Camera() : position(0, 0) {}

		Camera(float x, float y) : position(x, y) {}

		Camera(Position l_position): position(l_position) {}
	};
}