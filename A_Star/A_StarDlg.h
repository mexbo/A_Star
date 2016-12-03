
// A_StarDlg.h : header file
//

#pragma once

#include "AStar.h"
#include "afxwin.h"

// CA_StarDlg dialog
class CA_StarDlg : public CDialog
{
// Construction
public:
	CA_StarDlg(CWnd* pParent = NULL);	// standard constructor
    ~CA_StarDlg();
    void FindCallback();

// Dialog Data
	enum { IDD = IDD_A_STAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
    BOOL PreTranslateMessage( MSG* pMsg );

    struct MAPINFO //界面地图信息，与内部算法进行信息交换
    {
        int nRow;
        int nColumn;
        NODE start;
        NODE end;
        vector<NODE> vecBlock;//障碍物 m_barrier
    };
	//地图信息
    MAPINFO m_mapinfo;
	//画刷
    COLORREF m_brush_background;
    COLORREF m_brush_barrier;
    COLORREF m_brush_start;
    COLORREF m_brush_end;
    COLORREF m_brush_open;
    COLORREF m_brush_close;
    COLORREF m_brush_path;

    int m_nBaseX;
    int m_nBaseY;
    int m_nWidth;
    int m_nHeight;
    int m_deltaX;
    int m_deltaY;
    CDC * m_pdc;
    HDC m_hdc;
    
    bool m_bFirstShowMap;//是否是第一次显示地图
    bool m_bPause;//是否暂停

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CAStar m_AStar;//CAStar 对象
	CStatic m_picCtrl;//地图显示
    afx_msg void OnClickedButton();//开始按钮
	afx_msg void OnClickedPause();//暂停按钮
	afx_msg void OnClickedPicture();//点击地图响应事件
    void DrawSquare(COLORREF &m_brush_normal, const NODE *node);//画正方形
    void PointToCoord(CPoint &point, int &x, int &y);//屏幕坐标 → 客户端坐标 → 方块阵的坐标
    void SetSquareProperty(int x, int y);//配置方块的属性，是障碍物还是其他方块
    void ShowMap();//显示地图
    void DrawBackGround();//画背景
    void DrawBarrier();//画障碍物
    void DrawStartSquare();//画开始方块
    void DrawEndSquare();//画结束方块
};
