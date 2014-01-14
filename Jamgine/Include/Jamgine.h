#pragma once

namespace Jamgine
{
	namespace GraphicalSystem
	{
		enum GraphicalSystem
		{
			DIRECTX,
			OPENGL
		};
	}
	
	namespace ErrorMessage
	{
		enum ErrorMessage
		{
			OK,
			FAILED
		};
	}
	
	namespace SpriteEffect
	{
		enum SpriteEffect
		{
			FLIPHORIZONTALLY,	// Rotate 180 degrees about the Y axis before rendering.
			FLIPVERTICALLY,		// Rotate 180 degrees about the X axis before rendering.
			NONE				// No rotations specified.
		};
	}
	

	class JamgineEngine
	{
	public:		
		virtual void Render() = 0;
	
	/*template<typename T> void Safe_Delete(T*& a) 
	{
		delete a;
		a = nullptr;
	}*/
	
	private:
		
	
	protected:
	//	virtual EngineMain() = 0;
	//	virtual ~EngineMain() = 0;
	};

	static JamgineEngine* m_jamgineEngine = nullptr;
	ErrorMessage::ErrorMessage CreateEngine(JamgineEngine* p_jamgineEngine, GraphicalSystem::GraphicalSystem p_graphicalSystem);
	ErrorMessage::ErrorMessage ReleaseEngine();
}