#include "MoveTreeNodeList.h"

MoveTreeNodeList::MoveTreeNodeList(void)
{

}

MoveTreeNodeList::~MoveTreeNodeList(void)
{
	for(unsigned int i=0;i<m_moveNodeList.size();++i)
		delete m_moveNodeList[i];
}

void MoveTreeNodeList::DetachMove( const Move & m )
{
    for(std::vector<MoveTreeNode*>::iterator iter = m_moveNodeList.begin(); iter != m_moveNodeList.end(); ++iter)
    {
        if((*iter)->m_move==m)
        {
            m_moveNodeList.erase(iter);
            return;
        }
    }
}

void MoveTreeNodeList::DetachMove(std::vector<MoveTreeNode*>::iterator iter)
{
    m_moveNodeList.erase(iter);
}