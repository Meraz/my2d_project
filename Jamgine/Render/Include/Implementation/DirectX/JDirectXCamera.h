#pragma once

#include <Jamgine/Render/Include/JCamera.h>

namespace Jamgine {

	namespace Render {

		class JDirectXCamera : public JCamera
		{
		public:
			JDirectXCamera();
			virtual ~JDirectXCamera();

			virtual void setLens(const float &fovY, const float &aspect, const float &zn, const float &zf) override;
			virtual void setPosition(const JFloat4 &p_pos) override;

			virtual void strafe(const float &p_deltaStep) override;
			virtual void walk(const float &p_deltaStep) override;
			virtual void setYPosition(const float &p_y) override;
			virtual void pitch(const float &p_DeltaAngle) override;
			virtual void rotateY(const float &p_DeltaAngle) override;
			virtual void rebuildView() override;
			virtual void update(const float &p_deltaJaw, const float &p_deltaPitch) override;
			virtual void moveY(const float &p_step) override;

			virtual JFloat4 getPosition()		override;	//	const { return DirectX::XMFLOAT4(mPosition.x, mPosition.y, mPosition.z, 1); };
			virtual JFloat4 getLookAtMatrix()	override;	//	const { return DirectX::XMFLOAT4(mLook.x, mLook.y, mLook.z, 1); };
			virtual JFloat4 getUpVector()		override;	//	const { return DirectX::XMFLOAT4(mUp.x, mUp.y, mUp.z, 1); };
			virtual JFloat4 getRightVector()	override;	//	const { return DirectX::XMFLOAT4(mRight.x, mRight.y, mRight.z, 1); };

			DirectX::XMFLOAT4X4 getViewMatrix()			const override { return m_view; }
			DirectX::XMFLOAT4X4 getProjectionMatrix()	const override { return m_proj; }

		private:
			float mYaw;
			float mPitch;


			DirectX::XMFLOAT4 mPosition;
			DirectX::XMFLOAT4 mRight;
			DirectX::XMFLOAT4 mDefaultRight;

			DirectX::XMFLOAT4 mUp;
			DirectX::XMFLOAT4 mDefaultUp;
			DirectX::XMFLOAT4 mLook;
			DirectX::XMFLOAT4 mDefaultLook;

			DirectX::XMFLOAT4X4 m_view;
			DirectX::XMFLOAT4X4 m_proj;
		};
	}
}