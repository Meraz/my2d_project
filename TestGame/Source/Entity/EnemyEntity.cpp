#include <TestGame/Include/Entity/EnemyEntity.h>

#include <LuaModule/Include/LuaManager.h>

namespace
{
	LuaManager* g_luaManager;
}

/*
EnemyEntity::EnemyEntity()
{
//	m_entity = ENTITY::ENENMY;
}
*/

EnemyEntity::EnemyEntity(LuaManager* p_luaManager)
	: m_totalMovement(0)
{
	m_luaManager = p_luaManager;
	m_entity = ENTITY::ENENMY;
	g_luaManager = m_luaManager;
	m_totalMovement = 0;
}

EnemyEntity::~EnemyEntity()
{

}

#include <iostream>
#include <Windows.h>

static int Err(lua_State* l_luaState)
{
	OutputDebugStringA("FUCK THE WORLD");
		
	return 0;
}// float x, float y, float width, float height
static Point Move(float p_speed, float p_deltaTime, float p_rotation, float& p_totalMovement)
{

	lua_State* l_luaState = g_luaManager->GetLuaState();

	g_luaManager->RegisterFunction("Err", Err);
//	g_luaManager->RunSpecificFuntionInScriptWithParameters("Move.lua", "Move", 4);

	std::string MoveAA = "MoveAA";
	int a = luaL_dofile(l_luaState, "Move.lua");
	lua_getglobal(l_luaState, MoveAA.c_str());
	
	lua_pushnumber(l_luaState, p_speed);			/* push 1st argument */
    lua_pushnumber(l_luaState, p_deltaTime);		/* push 2nd argument */
	lua_pushnumber(l_luaState, p_rotation);			/* push 3nd argument */
	lua_pushnumber(l_luaState, p_totalMovement);	/* push 4nd argument */

	int b = lua_pcall(l_luaState, 4, 3, 0);

	if(b)
	{
		OutputDebugStringA(lua_tostring(l_luaState, -1));
	}

	float x = lua_tonumber(l_luaState, 1);
	float y = lua_tonumber(l_luaState, 2);
	p_totalMovement = lua_tonumber(l_luaState, 3);


	int argc = lua_gettop(l_luaState);
	lua_pop(l_luaState, argc);

	return Point(x,y);
}

void EnemyEntity::Update(double deltaTime)
{
	m_position = Move(50.0f, (float)deltaTime, m_rotation, m_totalMovement);
}

