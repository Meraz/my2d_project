#pragma once
#if defined(_WINDLL)
#define MATH1_TEST_NAME __declspec(dllexport)
#else
#define MATH1_TEST_NAME __declspec(dllimport)
#endif
#include <string>

namespace Jamgine 
{
	namespace MathSpace {


		class MathInterface {
		public:
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
}

extern "C"
{
	typedef Jamgine::MathSpace::MathInterface* (*CREATEMATHINTERFACE) (void);
	MATH1_TEST_NAME Jamgine::MathSpace::MathInterface* CreateMathInterface(void);
}