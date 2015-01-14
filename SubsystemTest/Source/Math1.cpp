#include <SubsystemTest/Include/Math1.h>

namespace Jamgine {
	namespace MathSpace {

		float Math1::floatAdd(float left, float right) {
			return left + right;
		}

	}
}

Jamgine::MathSpace::MathInterface* CreateMathInterface(void)
{
	return new Jamgine::MathSpace::Math1;
}