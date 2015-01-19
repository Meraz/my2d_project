#pragma once
#include <Jamgine/Include/Jamgine.h>

namespace Jamgine {

	class JamgineImplementation : public JamgineEngine {

	public:
		JamgineImplementation();
		virtual ~JamgineImplementation();

		// If Jamgine/Include/'API'Shared has been included, a definition of the struct exists.
		virtual ErrorMessage Initialize(Data_Send p_data) override;

	};
}