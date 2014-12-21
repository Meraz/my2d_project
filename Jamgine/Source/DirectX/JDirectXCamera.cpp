#include <Jamgine/Include/DirectX/JDirectXCamera.h>

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

		JDirectXCamera::JDirectXCamera()
		{
			mPosition = XMFLOAT4(0.0f, 0.0f, -1000.0f, 1.0f);
			mRight = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
			mDefaultRight = mRight;
			mUp = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
			mDefaultUp = mUp;
			mLook = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
			mDefaultLook = mLook;
			
			XMStoreFloat4x4(&m_view, XMMatrixIdentity());
			XMStoreFloat4x4(&m_proj, XMMatrixIdentity());
			setLens(3.1415f/4.0f, 1.0f, 1.0f, 10000.0f );

			mYaw = 3.1415f;
			mPitch = 3.1415f;
		}

		JDirectXCamera::~JDirectXCamera()
		{

		}

		void JDirectXCamera::setPosition(const JFloat4 &p_pos)
		{
			mPosition = XMFLOAT4(p_pos.x, p_pos.y, p_pos.z, p_pos.w);
		}

		void JDirectXCamera::setYPosition(const float & p_y)
		{
			mPosition.y = p_y;
		}

		void JDirectXCamera::setLens(const float &fovY, const float &aspect, const float &zn, const float &zf)
		{
			XMMATRIX temp = XMMatrixPerspectiveFovLH(fovY, aspect, zn, zf);
			XMStoreFloat4x4(&m_proj, temp);
		}

		void JDirectXCamera::strafe(const float &p_deltaSteo)
		{
			mPosition = mPosition + -p_deltaSteo * mRight;
		}

		void JDirectXCamera::walk(const float &p_deltaStep)
		{
			mPosition = mPosition + p_deltaStep * mLook;
		}

		void JDirectXCamera::pitch(const float &p_DeltaAngle)
		{
			XMMATRIX R;

			R = XMMatrixRotationX(p_DeltaAngle);

			XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mLook), R));
		}

		void JDirectXCamera::rotateY(const float &p_DeltaAngle)
		{
			XMMATRIX R;
			R = XMMatrixRotationY(p_DeltaAngle);

			XMStoreFloat4(&mLook, XMVector4Transform(XMLoadFloat4(&mLook), R));
		}

		void JDirectXCamera::update(const float &p_deltaJaw, const float &p_deltaPitch)
		{
			mYaw += p_deltaJaw;
			/*
			if (mYaw > 360)
			mYaw = 0.0f;
			if (mYaw < 0)
			mYaw = 360.0f;
			*/


			mPitch += -p_deltaPitch;

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

		void JDirectXCamera::rebuildView()
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

		void JDirectXCamera::moveY(const float &p_step)
		{
			mPosition.y = mPosition.y + p_step;
		}

		JFloat4 JDirectXCamera::getPosition()
		{ 
			return JFloat4(mPosition.x, mPosition.y, mPosition.z, 1.0f);
		}

		JFloat4 JDirectXCamera::getLookAtMatrix()
		{
			return JFloat4(mLook.x, mLook.y, mLook.z, 1);
		}

		JFloat4 JDirectXCamera::getUpVector()
		{
			return JFloat4(mUp.x, mUp.y, mUp.z, 1);
		}

		JFloat4 JDirectXCamera::getRightVector()
		{
			return JFloat4(mRight.x, mRight.y, mRight.z, 1);
		}
	}
}
