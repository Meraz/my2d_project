#include <TestGame/Include/Node.h>
#include <TestGame/Include/Entity/CollisionEntity.h>


#define BUCKET_CAPACITY 32
#define CHILD_CAPACITY 4 // should always be 4

Node::Node(Jamgine::Rectangle p_rectangle)
	: m_rectangle(), m_entity(), m_leaf(true)
{
	m_rectangle = p_rectangle;
	m_child[0] = nullptr;
	m_child[1] = nullptr;
	m_child[2] = nullptr;
	m_child[3] = nullptr;
}

Node::~Node()
{

}

void Node::AddEntity(CollisionEntity* p_entity)
{
	if(m_rectangle.Intersect(p_entity->GetRectangle()) == true)
	{
		if(m_leaf == false)
		{
			MoveOneEntityDown(p_entity);
		}
		if(m_leaf == true)
		{
			if(m_entity.size() >= BUCKET_CAPACITY)
			{				
				Subdivide();
				MoveOneEntityDown(p_entity);		
			}
			else
				m_entity.push_back(p_entity);
		}
	}
}

bool Node::Collide(Rectangle p_rectangle)
{
	if(m_rectangle.Intersect(p_rectangle) == true)
	{
		if(m_leaf == false)
		{
			for(unsigned int i = 0; i < CHILD_CAPACITY; i++)
			{
				if(m_child[i]->Collide(p_rectangle) == true)
					return true;
			}
		}
	}
	return false;
}

void Node::Render(Jamgine::Rectangle p_rectangle)
{
	if(m_rectangle.Intersect(p_rectangle) == true)
	{
		for(int i = 0; i < m_entity.size(); i++)
		{
			if(p_rectangle.Intersect(m_entity[i]->GetRectangle()))
			{
				m_entity[i]->Render();
			}
		}

		if(m_leaf == false)
		{
			for(unsigned int i = 0; i < CHILD_CAPACITY; i++)
			{
				if(p_rectangle.Intersect(m_entity[i]->GetRectangle()))
				{
					m_entity[i]->Render();
				}
			}
		}
	}
}

void Node::Subdivide()
{
	// Make sure everythings already initalized when you start
	for(unsigned int i = 0; i < CHILD_CAPACITY; i++)
	{
		if(m_child[i] == nullptr)
		{
			m_child[i] = new Node(CalculateRectangleForchild(i));
		}
	}
	m_leaf = false;
}

void Node::MoveOneEntityDown(CollisionEntity* p_entity)
{
	for(unsigned int i = 0; i < CHILD_CAPACITY; i++)
	{
		m_child[i]->AddEntity(p_entity);
	}
}

Rectangle Node::CalculateRectangleForchild(unsigned int p_index)
{
	Rectangle l_returnRectangle = m_rectangle;

	// All subrectangles are half size in both width and height
	l_returnRectangle.width /= 2;
	l_returnRectangle.height /= 2;

	if(p_index == 0) // BotLeft
	{
		return l_returnRectangle; // No other movements are required
	}
	else if(p_index == 1) // BotRight
	{
		l_returnRectangle.position.x += l_returnRectangle.width; // Move to right
	}
	else if(p_index == 2) // topleft
	{
		l_returnRectangle.position.y += l_returnRectangle.height; // Move up
	}
	else if(p_index == 3) // Top right
	{
		l_returnRectangle.position.x += l_returnRectangle.width; // Move to right
		l_returnRectangle.position.y += l_returnRectangle.height; // Move up
	}
	else
	{
		// Something is wrong, should not be able to enter here
		l_returnRectangle.width = 0;
		l_returnRectangle.height = 0;
	}
	return l_returnRectangle;
}

