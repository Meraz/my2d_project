#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{
	struct CameraStruct
	{
		Point position;

		CameraStruct() : position(0, 0) {}

		CameraStruct(float x, float y) : position(x, y) {}

		CameraStruct(Point l_position) : position(l_position) {}
	};
}