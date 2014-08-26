#include <Jamgine/Include/DirectX/JDirectXCamera.h>

namespace Jamgine
{
	JDirectXCamera::JDirectXCamera()
		: m_worldMatrix(0)
	{
		DirectX::XMMatrixIsIdentity(m_worldMatrix);
	}

	JDirectXCamera::~JDirectXCamera()
	{
	
	}


	int JDirectXCamera::setCameraPosition(float x, float y)
	{
		return 0;
	}

	int setCameraPosition(float x, float y, float z)
	{
		return 0;
	}

	int setZoom(float z)
	{
		return 0;
	}

}