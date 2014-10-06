#include <Jamgine/Include/DirectX/JDirectXCamera2.h>

#include <windows.h>
#include <D3D11.h>

using namespace DirectX;

XMFLOAT4 operator*(const XMFLOAT4 &l, const XMFLOAT4 &r)
{
	XMVECTOR lvec(XMLoadFloat4(&l));
	XMVECTOR rvec(XMLoadFloat4(&r));

	lvec *= rvec;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);

	return a;
}

XMFLOAT4 operator*(const XMFLOAT4 &l, const float &r) {

	XMVECTOR lvec(XMLoadFloat4(&l));

	lvec *= r;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}

XMFLOAT4 operator*(const float &l, const XMFLOAT4 &r)
{
	XMVECTOR lvec(XMLoadFloat4(&r));

	lvec *= l;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}


XMFLOAT4 operator+(const XMFLOAT4 &l, const XMFLOAT4 &r)
{
	XMVECTOR lvec(XMLoadFloat4(&l));
	XMVECTOR rvec(XMLoadFloat4(&r));

	lvec += rvec;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}

XMFLOAT4 operator+=(const XMFLOAT4 &l, const XMFLOAT4 &r)
{
	XMVECTOR lvec(XMLoadFloat4(&l));
	XMVECTOR rvec(XMLoadFloat4(&r));

	lvec += rvec;

	XMFLOAT4 a;
	XMStoreFloat4(&a, lvec);
	return a;
}

namespace Jamgine {

	namespace JDirectX {

		std::vector<Camera2*> Camera2::m_camera = std::vector<Camera2*>(10);

		Camera2* Camera2::GetCamera(int index)				// Quite the awful multiton here. Easy, not very good if getting cameras above 10.
		{
			if (m_camera.at(index) == nullptr)
				m_camera.at(index) = new Camera2();
			return m_camera.at(index);
		}

		Camera2::Camera2()
		{
			mPosition = XMFLOAT4(0.0f, 0.0f, 250.0f, 1.0f);
			mRight = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
			mDefaultRight = mRight;
			mUp = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
			mDefaultUp = mUp;
			mLook = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
			mDefaultLook = mLook;


			XMStoreFloat4x4(&m_view, XMMatrixIdentity());
			XMStoreFloat4x4(&m_proj, XMMatrixIdentity());
			setLens(3.1415f/4.0f, 1.0f, 1.0f, 1000.0f );

			mYaw = 3.1415f;
			mPitch = 3.1415f;
		}

		Camera2::~Camera2()
		{
		}

		void Camera2::SetPosition(XMFLOAT4 lPos)
		{
			mPosition = lPos;
		}

		void Camera2::setYPosition(float y)
		{
			mPosition.y = y;
		}

		void Camera2::setLens(float fovY, float aspect, float zn, float zf)
		{
			XMMATRIX temp = XMMatrixPerspectiveFovLH(fovY, aspect, zn, zf);
			XMStoreFloat4x4(&m_proj, temp);
		}

		void Camera2::strafe(float d)
		{
			mPosition = mPosition + -d * mRight;
		}

		void Camera2::walk(float d)
		{
			mPosition = mPosition + d * mLook;
		}

		void Camera2::pitch(float angle)
		{
			XMMATRIX R;

			R = XMMatrixRotationX(angle);

			XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mLook), R));
		}

		void Camera2::rotateY(float angle)
		{
			XMMATRIX R;
			R = XMMatrixRotationY(angle);

			XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mLook), R));
		}

		void Camera2::update(float jaw, float pitch)
		{
			mYaw += jaw;

			/*
			if (mYaw > 360)
			mYaw = 0.0f;
			if (mYaw < 0)
			mYaw = 360.0f;
			*/


			mPitch += -pitch;

			//	if (mPitch > PI/2)
			//		mPitch = PI / 2;
			//	if (mPitch < PI * 0.05 )
			//		mPitch = PI * 0.05;

			XMMATRIX R;
			R = XMMatrixRotationRollPitchYaw(mPitch, mYaw, 0.0f);

			XMStoreFloat4(&mRight, XMVector4Transform(XMLoadFloat4(&mDefaultRight), R));
			//	XMStoreFloat4(&mUp, XMVector4Transform(XMLoadFloat4(&mUp), R));
			XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mDefaultLook), R));
		}

		void Camera2::rebuildView()
		{
			// Not sure which one to use. I would pressume that I'd use "LookAt", however, "LookTo" is the one to give the right results

			/* Definitions on both functions
			// XMMatrixLookAtLH method
			// Builds a view matrix for a left-handed coordinate system using a camera position, an up direction, and a focal point.

			// XMMatrixLookToLH method
			// Builds a view matrix for a left-handed coordinate system using a camera position, an up direction, and a camera direction.
			*/
			XMMATRIX temp = XMMatrixLookToLH(XMLoadFloat4(&mPosition), XMLoadFloat4(&mLook), XMLoadFloat4(&mUp));
			XMStoreFloat4x4(&m_view, temp);
		}

		void Camera2::MoveY(float p_step)
		{
			mPosition.y = mPosition.y + p_step;
		}
	}
}
