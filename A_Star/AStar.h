#pragma once

#include <vector>
using namespace std;

struct DIRECTION
{
	int x;
	int y;
};

typedef struct _NODE
{
	int nX;
	int nY;
	DIRECTION parent;
	int f;
	int g;
	int h;
	_NODE(int x, int y)
	{
		nX = x;
		nY = y;
		f = g = h = 0;
	}
	_NODE() { nX = nY = f = g = h = 0; }
}NODE, *PNODE;

class CAStar
{
public:
	CAStar();//构造函数
	CAStar(int nColumn, int nRow);//带参构造函数
	~CAStar(void);//析构函数
	void SetRange(int nColumn, int nRow);//设置范围
	void SetStartAndEnd(NODE startNode, NODE endNode);//设置开始和结束节点位置
	void SetBlock(vector<NODE> &vecBlock);//设置障碍物
	void FindPath();//路径寻找
	int SetCallBack(int(*pFun)(void *), void *pThis);//设置回调函数
	bool IsFindPath();//是否找到终点

	const vector<NODE>* GetPathVector()//获取路径链表节点
	{
		return &m_path;
	}
	const vector<NODE>* GetOpenVector()//获取open链表节点
	{
		return &m_open;
	}
	const vector<NODE>* GetCloseVector()//获取close链表节点
	{
		return &m_close;
	}

	bool InOpen(int x, int y, NODE **pNode = NULL);//判断是否在open表中
	bool InClose(int x, int y, NODE **pNode = NULL);//判断是否在Close表中
	bool InBarrier(int x, int y, NODE **pNode = NULL);//判断是否在障碍物表中

	void ClearAllList();//清空所有链表

private:
	void CalcValue(NODE &node);//计算f，g，h值
	int GetDistance(NODE &node1, NODE &node2);//获取两节点之间的距离
	void GetMinFromOpen(vector<NODE> &minVec);//从Open表中获取最小值
	void DoNeighbors(NODE &node);//寻找node节点周围的节点
	void DoNeighborNode(int gValue, DIRECTION *direct, NODE &node);//对邻接的节点进行操作
	bool IsValid(DIRECTION *direct, NODE &node);//判断节点是否无效，出界，与障碍物重合，斜线是否可以
	void GetFinalShortestPath();//寻找最短路径

	int m_nColumn;//列
	int m_nRow;//行

	NODE m_startNode;//开始节点
	NODE m_endNode;//结束节点

	vector<NODE> m_open;//Open链表
	vector<NODE> m_close;//Close链表
	vector<NODE> m_barrier;//障碍链表
	vector<NODE> m_path;//路径链表

	static int m_moveCostHorizontal;//水平消耗
	static int m_moveCostDiagonal;//斜线消耗

	bool m_bFind;//判断是否找到路径
	bool m_haveNeighbor;//判断是否有邻接点，在DoNeighborNode用到

	int(*m_CallBack)(void *);//返回int类型的形参为void *类型的函数指针
	void *m_pArg;
};
