

#pragma once

#include "../libCarEyePlayer/libCarEyePlayerAPI.h"

#pragma comment(lib,"../libCarEyePlayer/libCarEyePlayer.lib")

#define KEY "6A59754D6A3469576B5A73414D433158714E4C4F6B76464659584E3555477868655756794C6D56345A536C58444661672F704C67523246326157346D516D466962334E68514449774D545A4659584E355247467964326C75564756686257566863336B3D"

//Gavin's Source Struct流信息结构
typedef struct __CarEye_LOCAL_SOURCE_T
{	
	int		rtspSourceId;
	void*	pusherHandle;

	char	pushServerAddr[128];
	int		pushServerPort;
	char	sdpName[64];
	void* pMaster;
}CarEye_LOCAL_SOURCE_T;

class CarEyePlayerManager
{
public:
	CarEyePlayerManager(void);
	~CarEyePlayerManager(void);

	//Member Function
public:
	//初始化
	static int Init()
	{
		return CarEyePlayer_Init(KEY);
	}

	// 释放
	static void UnInit()
	{
		CarEyePlayer_Release();
	}

	//打开流
	int Start(char* szURL, HWND hShowWnd, RENDER_FORMAT eRenderFormat, int rtpovertcp, const char *username, const char *password, int bHardDecode, MediaSourceCallBack callback=NULL, void *userPtr=NULL) ;
	//设置参数
	void Config(int nFrameCache,  BOOL bPlaySound, BOOL bShowToScale = TRUE, BOOL  bShowStatisticInfo = FALSE);
	//关闭流
	void	Close();
	void SetOSD(int show, CAREYE_PALYER_OSD osd);
	int InRunning();

	//Member Var
private:
	//接收的流信息
	CarEye_LOCAL_SOURCE_T		m_sSourceInfo;

};

