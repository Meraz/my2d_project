#include <Jamgine/Render/Include/JRenderSubSystem.h>
#include <Jamgine/Render/Include/Implementation/DirectX/JDirectXRender.h>

Jamgine::Render::JRenderSubsystem* CreateRenderSubsystem(void)
{
	return new Jamgine::Render::JDirectXRender;
}