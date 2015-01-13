#include <SubsystemTest/Include/Math1.hpp>

namespace Jamgine
{
	float Math1::floatAdd(float left, float right) {
		return left + right;
	}
}

Jamgine::MathInterface* CreateSoundInterface()
{
	return new Jamgine::Math1();
}