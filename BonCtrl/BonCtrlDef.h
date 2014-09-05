#ifndef __BON_CTRL_DEF_H__
#define __BON_CTRL_DEF_H__

#include "../Common/Util.h"

#define MUTEX_UDP_PORT_NAME			TEXT("Global\\EpgDataCap_Bon_UDP_PORT_")
#define MUTEX_TCP_PORT_NAME			TEXT("Global\\EpgDataCap_Bon_TCP_PORT_")
#define CHSET_SAVE_EVENT_WAIT		 _T("Global\\EpgTimer_ChSet")


//BonDriver�̃`���[�i�[��ԏ��
typedef struct _BON_SPACE_INFO{
	wstring spaceName;					//�`���[�i�[��Ԗ�
	map<DWORD, wstring> chMap;			//�`�����l�����X�g�i�L�[ CH�j
}BON_SPACE_INFO;

//��M�f�[�^�̃o�b�t�@�����O�p
typedef struct _TS_DATA{
	BYTE* data;				//TS�f�[�^
	DWORD size;				//data�̃T�C�Y
	_TS_DATA(void){
		data = NULL;
		size = 0;
	}
	~_TS_DATA(void){
		SAFE_DELETE_ARRAY(data);
	}
} TS_DATA;

//�l�b�g���[�N���M�p�ݒ�
typedef struct _NW_SEND_INFO{
	wstring ipString;
	DWORD ip;
	DWORD port;
	BOOL broadcastFlag;
}NW_SEND_INFO;

//�T�[�r�X���
typedef struct _TS_SERVICE_INFO{
	WORD ONID;
	WORD TSID;
	WORD SID;
	BYTE serviceType;
	BOOL partialFlag;
	wstring serviceName;
	wstring networkName;
	BYTE remoteControlKeyID;
}TS_SERVICE_INFO;

//EPG�擾�p�T�[�r�X���
typedef struct _EPGCAP_SERVICE_INFO{
	WORD ONID;
	WORD TSID;
	WORD SID;
}EPGCAP_SERVICE_INFO;


#endif
