#include <TestGame/Include/Entity/EnemyEntity.h>

#include <LuaModule/Include/LuaManager.h>

namespace
{
	LuaManager* g_luaManager;
}

EnemyEntity::EnemyEntity(LuaManager* p_luaManager, Point p_spawnPosition)
	: m_totalMovement(0)
{
	m_luaManager = p_luaManager;
	m_entity = ENTITY::ENENMY;
	g_luaManager = m_luaManager;
	m_totalMovement = 0;
	m_spawnPosition = p_spawnPosition;
}

EnemyEntity::~EnemyEntity()
{

}

#include <iostream>
#include <Windows.h>

static int Err(lua_State* l_luaState)
{
	OutputDebugStringA("This is not going well");
		
	return 0;
}

static Point Move(Point p_spawnPosition, float p_speed, float p_deltaTime, float p_rotation, float& p_totalMovement)
{

	lua_State* l_luaState = g_luaManager->GetLuaState();

//	g_luaManager->RegisterFunction("Err", Err);
//	g_luaManager->RunSpecificFuntionInScriptWithParameters("Move.lua", "Move", 4);

	std::string MoveAA = "Move";
	//int a = luaL_dofile(l_luaState, "Move.lua");
	lua_getglobal(l_luaState, MoveAA.c_str());
	
	lua_pushnumber(l_luaState, p_spawnPosition.x);		
	lua_pushnumber(l_luaState, p_spawnPosition.y);		
	lua_pushnumber(l_luaState, p_speed);				
   lua_pushnumber(l_luaState, p_deltaTime);	
	lua_pushnumber(l_luaState, p_rotation);		
	lua_pushnumber(l_luaState, p_totalMovement);

	lua_call(l_luaState, 6, 3);



	float x = lua_tonumber(l_luaState, 1);
	float y = lua_tonumber(l_luaState, 2);
	p_totalMovement = lua_tonumber(l_luaState, 3);


	int argc = lua_gettop(l_luaState);
	lua_pop(l_luaState, argc);

	return Point(x,y);
}

void EnemyEntity::Update(double p_deltaTime)
{
	m_position = Move(m_spawnPosition, 50.0f, (float)p_deltaTime, m_rotation, m_totalMovement);
	RenderEntity::Update(p_deltaTime);
}

bool EnemyEntity::OutsideBounds(float p_left, float p_right, float p_bot, float p_top)
{
	Jamgine::Rectangle a = Jamgine::Rectangle(p_left, p_bot, abs(p_left-p_right), abs(p_top-p_bot));

	if(m_rectangle.Intersect(a) == false)
		return true;
	return false;
}
