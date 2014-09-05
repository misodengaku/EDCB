#pragma once

#include <windows.h>

#include "../Common/Util.h"

class CPacketInit
{
public:
	CPacketInit(void);
	~CPacketInit(void);

	//���̓o�b�t�@��188�o�C�g�P�ʂ�TS�ɕϊ����A188�̔{���ɂȂ�悤�ɂ��낦��
	//�߂�l�F
	// TRUE�i�����j�AFALSE�i���s�j
	//�����F
	// inData			[IN]����TS�f�[�^
	// inSize			[IN]inData�̃T�C�Y�iBYTE�P�ʁj
	// outData			[OUT]188�o�C�g�ɐ��񂵂��o�b�t�@�i�Ăяo������delete����K�v����j
	// outSize			[OUT]outData�̃T�C�Y�iBYTE�P�ʁj
	BOOL GetTSData(
		BYTE* inData,
		DWORD inSize,
		BYTE** outData,
		DWORD* outSize
		);

	//�����o�b�t�@�̃N���A
	void ClearBuff();

protected:
	BYTE* nextStartBuff;
	DWORD nextStartSize;

	DWORD packetSize;
};
