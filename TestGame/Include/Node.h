#pragma once
#include <Jamgine/Include/Shared/Rectangle.h>
#include <vector>

class Entity;

class Node
{
public:
	Node(Jamgine::Rectangle p_rectangle);
	virtual ~Node();
	void AddEntity(Entity* p_entity);
	bool Collide(Jamgine::Rectangle p_rectangle);
	void Render(Jamgine::Rectangle p_rectangle);

private:
	void Subdivide();
	void MoveOneEntityDown(Entity* p_entity);

	Jamgine::Rectangle CalculateRectangleForchild(unsigned int p_index);

private:
	Jamgine::Rectangle m_rectangle;

	std::vector<Entity*> m_entity;
	Node* m_child[4];
	bool m_leaf;
};