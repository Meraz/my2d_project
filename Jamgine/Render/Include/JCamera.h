#pragma once
#include <Jamgine/Include/Shared.h>
#include <Jamgine/Include/JFloat4.h>
#include <DirectXMath.h> // Only for the matrices

namespace Jamgine
{
	namespace Render
	{
		class JCamera
		{
		public:
			virtual void setLens(const float &fovY, const float &aspect, const float &zn, const float &zf) = 0;
			virtual void setPosition(const JFloat4 &p_pos) = 0;

			virtual void strafe(const float &p_deltaStep) = 0;
			virtual void walk(const float &p_deltaStep) = 0;
			virtual void setYPosition(const float &p_y) = 0;
			virtual void pitch(const float &p_DeltaAngle) = 0;
			virtual void rotateY(const float &p_DeltaAngle) = 0;
			virtual void rebuildView() = 0;
			virtual void update(const float &p_deltaJaw, const float &p_deltaPitch) = 0;
			virtual void moveY(const float &p_step) = 0;

			virtual JFloat4 getPosition() = 0;
			virtual JFloat4 getLookAtMatrix() = 0;
			virtual JFloat4 getUpVector() = 0;
			virtual JFloat4 getRightVector() = 0;
			virtual DirectX::XMFLOAT4X4 getViewMatrix() const  = 0;
			virtual DirectX::XMFLOAT4X4 getProjectionMatrix() const = 0;
		};
	}
}