#pragma once

#include "EpgDBManager.h"
#include "ReserveManager.h"
#include "FileStreamingManager.h"
#include "NotifyManager.h"

#include "../../Common/ParseTextInstances.h"
#include "../../Common/PipeServer.h"
#include "../../Common/TCPServer.h"
#include "../../Common/HttpServer.h"
#include "../../Common/TCPServerUtil.h"

#include "DLNAManager.h"

class CEpgTimerSrvMain
{
public:
	CEpgTimerSrvMain(void);
	~CEpgTimerSrvMain(void);

	//���C�����[�v����
	//�����F
	// serviceFlag			[IN]�T�[�r�X�Ƃ��Ă̋N�����ǂ���
	void StartMain(
		BOOL serviceFlag
		);

	//���C��������~
	void StopMain();

	//�x�~�^�X�^���o�C�ڍs���������ǂ���
	//�߂�l�F
	// TRUE�i�ڍs���j�AFALSE
	BOOL IsSuspending();

	//�x�~�^�X�^���o�C�Ɉڍs���č\��Ȃ��󋵂��ǂ���
	//�߂�l�F
	// TRUE�i�\��Ȃ��j�AFALSE�i�ڍs���Ă͑ʖځj
	BOOL ChkSuspend();

	//���[�U�[��PC���g�p�����ǂ���
	//�߂�l�F
	// TRUE�i�g�p���j�AFALSE�i�g�p���Ă��Ȃ��j
	BOOL IsUserWorking();

protected:
	CEpgDBManager epgDB;
	CReserveManager reserveManager;
	CFileStreamingManager streamingManager;
	CNotifyManager notifyManager;

	CParseEpgAutoAddText epgAutoAdd;
	CParseManualAutoAddText manualAutoAdd;

	CDLNAManager* dlnaManager;

	HANDLE stopEvent;
	HANDLE sleepEvent;
	HANDLE resetServerEvent;
	HANDLE reloadEpgChkEvent;

	//map<DWORD,DWORD> registGUI; //PID,PID
	//map<wstring,REGIST_TCP_INFO> registTCP; //IP:Port

	BYTE suspendModeWork;
	BYTE rebootFlagWork;

	int wakeMargin;
	BOOL enableTCPSrv;
	DWORD tcpPort;
	int autoAddDays;
	int autoAddHour;
	BOOL chkGroupEvent;
	BYTE rebootDef;
	BOOL ngUsePC;
	DWORD ngUsePCTime;
	BOOL ngFileStreaming;
	BOOL ngEpgFileSrvCoop;
	BOOL enableHttpSrv;
	DWORD httpPort;
	BOOL enableDMS;

	BOOL enableHttpPublic;
	wstring httpPublicFolder;

	BOOL awayMode;

	vector<OLD_EVENT_INFO_DATA3> oldSearchList;

	//���̃I�u�W�F�N�g�����ݒ�ϐ���ی삷�郍�b�N
	//�Ǝ��ɃA�g�~�b�N�����m�ۂ���I�u�W�F�N�g�͑ΏۊO
	CRITICAL_SECTION settingLock;
protected:
	BOOL CheckTuijyu();

	BOOL AutoAddReserveEPG(int targetSize = -1, EPG_AUTO_ADD_DATA* target = NULL);
	BOOL AutoAddReserveProgram();

	static void SetShutdown(BYTE shutdownMode);
	BOOL QuerySleep(BYTE rebootFlag, BYTE suspendMode);
	BOOL QueryReboot(BYTE rebootFlag);

	BOOL SetResumeTimer(HANDLE* resumeTimer, LONGLONG* resumeTime, BOOL rebootFlag);
	void ResetServer(CTCPServer& tcpServer, CHttpServer& httpServer, CTCPServerUtil& tcpSrvUtil);
	void ReloadSetting();

	void AddRecFileDMS();

	//�O������R�}���h�֌W
	static int CALLBACK CtrlCmdCallback(void* param, CMD_STREAM* cmdParam, CMD_STREAM* resParam);
	static int CALLBACK HttpCallback(void* param, HTTP_STREAM* recvParam, HTTP_STREAM* sendParam);
	static int CALLBACK TcpAcceptCallback(void* param, SOCKET clientSock, struct sockaddr_in* client, HANDLE stopEvent);


};

