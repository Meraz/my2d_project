#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{
	struct Camera
	{
		Point position;
		Camera() : position(0, 0) {}

		Camera(float x, float y) : position(x, y) {}

		Camera(Point l_position): position(l_position) {}
	};
}