#pragma once





class GraphicalUserInterface
{

public:
	virtual GraphicalUserInterface* Startup() = 0; // This returns 
	virtual void Init() = 0;
	virtual void Shutdown() = 0;
	
	
	virtual void Render() = 0;
	
	

private:
}: