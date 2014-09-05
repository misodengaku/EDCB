#pragma once

#include <windows.h>

#include "../Common/Util.h"
#include "../Common/PathUtil.h"
#include "../Common/StringUtil.h"
#include "../Common/ErrDef.h"

#include "IBonDriver.h"
#include "IBonDriver2.h"
#include "BonCtrlDef.h"

class CBonDriverUtil
{
public:
	CBonDriverUtil(void);
	~CBonDriverUtil(void);

	//BonDriver�t�H���_���w��
	//�����F
	// bonDriverFolderPath		[IN]BonDriver�t�H���_�p�X
	void SetBonDriverFolder(
		LPCWSTR bonDriverFolderPath
		);

	//BonDriver�t�H���_��BonDriver_*.dll���
	//�߂�l�F
	// �G���[�R�[�h
	//�����F
	// bonList			[OUT]�����ł���BonDriver�ꗗ
	DWORD EnumBonDriver(
		vector<wstring>* bonList
		);

	//BonDriver�����[�h���ă`�����l�����Ȃǂ��擾�i�t�@�C�����Ŏw��j
	//�߂�l�F
	// �G���[�R�[�h
	//�����F
	// bonDriverFile	[IN]EnumBonDriver�Ŏ擾���ꂽBonDriver�̃t�@�C����
	DWORD OpenBonDriver(
		LPCWSTR bonDriverFile,
		int openWait = 200
		);

	//���[�h���Ă���BonDriver�̊J��
	//�߂�l�F
	// �G���[�R�[�h
	DWORD CloseBonDriver();

	//���[�h����BonDriver�̏��擾
	//Space��Ch�̈ꗗ���擾����
	//�߂�l�F
	// �G���[�R�[�h
	//�����F
	// spaceMap			[OUT] Space��Ch�̈ꗗ�imap�̃L�[ Space�j
	DWORD GetOriginalChList(
		map<DWORD, BON_SPACE_INFO>* spaceMap
	);

	//BonDriver�̃`���[�i�[�����擾
	//�߂�l�F
	// �`���[�i�[��
	wstring GetTunerName();

	//�`�����l���ύX
	//�߂�l�F
	// �G���[�R�[�h
	//�����F
	// space			[IN]�ύX�`�����l����Space
	// ch				[IN]�ύX�`�����l���̕���Ch
	DWORD SetCh(
		DWORD space,
		DWORD ch
		);

	//���݂̃`�����l���擾
	//�߂�l�F
	// �G���[�R�[�h
	//�����F
	// space			[IN]���݂̃`�����l����Space
	// ch				[IN]���݂̃`�����l���̕���Ch
	DWORD GetNowCh(
		DWORD* space,
		DWORD* ch
		);

	//TS�X�g���[�����擾
	//�߂�l�F
	// TRUE�i�����j�AFALSE�i���s�j
	//�����F
	// data				[OUT]BonDriver�����o�b�t�@�̃|�C���^
	// size				[OUT]�擾�o�b�t�@�̃T�C�Y
	// remain			[OUT]���擾�o�b�t�@�̃T�C�Y
	BOOL GetTsStream(
		BYTE **data,
		DWORD *size,
		DWORD *remain
		);

	//�V�O�i�����x���̎擾
	//�߂�l�F
	// �V�O�i�����x��
	float GetSignalLevel();

	//Open����BonDriver�̃t�@�C�������擾
	//�߂�l�F
	// BonDriver�̃t�@�C�����i�g���q�܂ށj�iempty�Ŗ�Open�j
	wstring GetOpenBonDriverFileName();

protected:
	HANDLE lockEvent;

	vector<wstring> bonDllList;

	wstring loadDllPath;
	wstring loadTunerName;
	map<DWORD, BON_SPACE_INFO> loadChMap;
	BOOL initChSetFlag;
	IBonDriver* bonIF;
	IBonDriver2* bon2IF;
	HMODULE module;
protected:
	//PublicAPI�r������p
	BOOL Lock(LPCWSTR log = NULL, DWORD timeOut = 5*1000);
	void UnLock(LPCWSTR log = NULL);

	//BonDriver�����[�h���̖{��
	//�߂�l�F
	// �G���[�R�[�h
	//�����F
	// bonDriverFilePath		[IN] ���[�h����BonDriver�̃t�@�C���p�X
	DWORD _OpenBonDriver(
		LPCWSTR bonDriverFilePath,
		int openWait
		);

	//���[�h���Ă���BonDriver�̊J���̖{��
	//�߂�l�F
	// �G���[�R�[�h
	DWORD _CloseBonDriver();
};

