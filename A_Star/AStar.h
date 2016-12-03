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
	CAStar();//���캯��
	CAStar(int nColumn, int nRow);//���ι��캯��
	~CAStar(void);//��������
	void SetRange(int nColumn, int nRow);//���÷�Χ
	void SetStartAndEnd(NODE startNode, NODE endNode);//���ÿ�ʼ�ͽ����ڵ�λ��
	void SetBlock(vector<NODE> &vecBlock);//�����ϰ���
	void FindPath();//·��Ѱ��
	int SetCallBack(int(*pFun)(void *), void *pThis);//���ûص�����
	bool IsFindPath();//�Ƿ��ҵ��յ�

	const vector<NODE>* GetPathVector()//��ȡ·������ڵ�
	{
		return &m_path;
	}
	const vector<NODE>* GetOpenVector()//��ȡopen����ڵ�
	{
		return &m_open;
	}
	const vector<NODE>* GetCloseVector()//��ȡclose����ڵ�
	{
		return &m_close;
	}

	bool InOpen(int x, int y, NODE **pNode = NULL);//�ж��Ƿ���open����
	bool InClose(int x, int y, NODE **pNode = NULL);//�ж��Ƿ���Close����
	bool InBarrier(int x, int y, NODE **pNode = NULL);//�ж��Ƿ����ϰ������

	void ClearAllList();//�����������

private:
	void CalcValue(NODE &node);//����f��g��hֵ
	int GetDistance(NODE &node1, NODE &node2);//��ȡ���ڵ�֮��ľ���
	void GetMinFromOpen(vector<NODE> &minVec);//��Open���л�ȡ��Сֵ
	void DoNeighbors(NODE &node);//Ѱ��node�ڵ���Χ�Ľڵ�
	void DoNeighborNode(int gValue, DIRECTION *direct, NODE &node);//���ڽӵĽڵ���в���
	bool IsValid(DIRECTION *direct, NODE &node);//�жϽڵ��Ƿ���Ч�����磬���ϰ����غϣ�б���Ƿ����
	void GetFinalShortestPath();//Ѱ�����·��

	int m_nColumn;//��
	int m_nRow;//��

	NODE m_startNode;//��ʼ�ڵ�
	NODE m_endNode;//�����ڵ�

	vector<NODE> m_open;//Open����
	vector<NODE> m_close;//Close����
	vector<NODE> m_barrier;//�ϰ�����
	vector<NODE> m_path;//·������

	static int m_moveCostHorizontal;//ˮƽ����
	static int m_moveCostDiagonal;//б������

	bool m_bFind;//�ж��Ƿ��ҵ�·��
	bool m_haveNeighbor;//�ж��Ƿ����ڽӵ㣬��DoNeighborNode�õ�

	int(*m_CallBack)(void *);//����int���͵��β�Ϊvoid *���͵ĺ���ָ��
	void *m_pArg;
};
