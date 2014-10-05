#pragma once

#include <Jamgine/Include/DirectX/JDirectXShared.h>
#include <DirectXMath.h>
#include <vector>

namespace Jamgine {

	namespace JDirectX {

		class Camera2
		{
		public:
			static Camera2* GetCamera(int index);

			void setLens(float fovY, float aspect, float zn, float zf);
			void SetPosition(DirectX::XMFLOAT4 lPos);

			void strafe(float d);
			void walk(float d);
			void setYPosition(float y);
			void pitch(float angle);
			void rotateY(float angle);
			void rebuildView();
			void update(float jaw, float pitch);

			void MoveY(float p_step);

			DirectX::XMFLOAT4 GetPosition()		const { return DirectX::XMFLOAT4(mPosition.x, mPosition.y, mPosition.z, 1); };
			DirectX::XMFLOAT4 GetLookAt()		const { return DirectX::XMFLOAT4(mLook.x, mLook.y, mLook.z, 1); };
			DirectX::XMFLOAT4 GetUp()			const { return DirectX::XMFLOAT4(mUp.x, mUp.y, mUp.z, 1); };
			DirectX::XMFLOAT4 GetRight()		const { return DirectX::XMFLOAT4(mRight.x, mRight.y, mRight.z, 1); };

			//	XMMATRIX GetView()		const{ return mView; }
			//	XMMATRIX GetProj()		const{ return mProj;}

			DirectX::XMFLOAT4X4 GetView()		const{ return m_view; }
			DirectX::XMFLOAT4X4 GetProj()		const{ return m_proj; }

		private:
			float mYaw;
			float mPitch;

			static std::vector<Camera2*> m_camera;

			Camera2();
			~Camera2();

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