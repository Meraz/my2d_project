#pragma once

#include <Jamgine/Include/Shared/Spritedata.h>
#include <vector>

namespace Jamgine{
	
	struct Node
	{
	public:
		Node();
		virtual ~Node();

		void AddItem(SpriteData* m_item);

		SpriteData* m_item;

		Node* m_left;
		Node* m_right;
		Node* m_child;
	};
}