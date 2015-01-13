#pragma once
#if defined(_WINDLL)
#define MATH1_TEST_NAME __declspec(dllexport)
#else
#define MATH1_TEST_NAME __declspec(dllimport)
#endif

namespace Jamgine 
{

	class MathInterface {
		virtual float floatAdd(float left, float right) = 0;
	};

	class Math1 : public MathInterface
	{
	public:
		Math1() {

		}
		virtual float floatAdd(float left, float right) override;
		
	};
}

extern "C"
{
	typedef Jamgine::MathInterface* (*CREATEMATHINTERFACE) (void);
	MATH1_TEST_NAME Jamgine::MathInterface* CreateMathInterface(void);
}