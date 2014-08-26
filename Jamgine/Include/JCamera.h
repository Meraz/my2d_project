#pragma once
#include <Jamgine/Include/Shared.h>

namespace Jamgine
{
	class JCamera
	{
	public:
	//	JCamera();
	//	virtual ~JCamera();

		// copy constructor?

		
		virtual int setCameraPosition(float x, float y) = 0;
		virtual int setCameraPosition(float x, float y, float z) = 0;

		virtual int setZoom(float z) = 0;
	};
}