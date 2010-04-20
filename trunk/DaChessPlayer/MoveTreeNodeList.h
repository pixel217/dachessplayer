#pragma once
#include "MoveTreeNode.h"
#include <vector>

class MoveTreeNodeList
{
public:
    MoveTreeNodeList(void);
    ~MoveTreeNodeList(void);
    std::vector<MoveTreeNode*> m_moveNodeList;
    void DetachMove(const Move & m);
	void DetachMove(std::vector<MoveTreeNode*>::iterator iter);
};
