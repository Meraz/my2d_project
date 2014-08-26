#pragma once

#include <Jamgine/Include/JCamera.h>

#include <DirectXMath.h>	// TODO

namespace Jamgine
{
	class JDirectXCamera : public JCamera
	{
	public:
		JDirectXCamera();
		virtual  ~JDirectXCamera();

		DirectX::XMMATRIX m_worldMatrix;

		int setCameraPosition(float x, float y) override;
		int setCameraPosition(float x, float y, float z) override;

		int setZoom(float z) override;
	};

}