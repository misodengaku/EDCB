#pragma once

#include "ParseText.h"
#include "StructDef.h"

//�`�����l�����t�@�C���uChSet4.txt�v�̓ǂݍ��݂ƕۑ��������s��
//�L�[�͓ǂݍ��ݏ��ԍ�
class CParseChText4 : public CParseText<DWORD, CH_DATA4>
{
public:
	using CParseText<DWORD, CH_DATA4>::SaveText;
	//�`�����l�����̓����f�[�^�𒼐ڎ擾����B�߂�l�͎��̔�const����܂ŗL��
	vector<CH_DATA4*> GetChDataList();
	//�`�����l������ǉ�����(���s���Ȃ�)�B�߂�l�͒ǉ����ꂽ�L�[
	DWORD AddCh(const CH_DATA4& item);
	//�`�����l�������폜����
	void DelChService(int space, int ch, WORD serviceID);
protected:
	bool ParseLine(const wstring& parseLine, pair<DWORD, CH_DATA4>& item);
	bool SaveLine(const pair<DWORD, CH_DATA4>& item, wstring& saveLine) const;
	bool SelectIDToSave(vector<DWORD>& sortList) const;
};

//�`�����l�����t�@�C���uChSet5.txt�v�̓ǂݍ��݂ƕۑ��������s��
//�L�[��ONID<<32|TSID<<16|SID
class CParseChText5 : public CParseText<LONGLONG, CH_DATA5>
{
public:
	using CParseText<LONGLONG, CH_DATA5>::SaveText;
	LONGLONG AddCh(const CH_DATA5& item);
	//EPG�f�[�^�̎擾�Ώۂ���ݒ肷��
	bool SetEpgCapMode(WORD originalNetworkID, WORD transportStreamID, WORD serviceID, BOOL epgCapFlag);
protected:
	bool ParseLine(const wstring& parseLine, pair<LONGLONG, CH_DATA5>& item);
	bool SaveLine(const pair<LONGLONG, CH_DATA5>& item, wstring& saveLine) const;
	bool SelectIDToSave(vector<LONGLONG>& sortList) const;
};

//�g���q��Content-Type�̑Ή��t�@�C���uContentTypeText.txt�v�̓ǂݍ��݂��s��
class CParseContentTypeText : public CParseText<wstring, wstring>
{
public:
	void GetMimeType(wstring ext, wstring& mimeType) const;
protected:
	bool ParseLine(const wstring& parseLine, pair<wstring, wstring>& item);
};

//�T�[�r�X���Ƃ���ڂ��J�����_�[�����ǖ��̑Ή��t�@�C���uSyoboiCh.txt�v�̓ǂݍ��݂��s��
class CParseServiceChgText : public CParseText<wstring, wstring>
{
public:
	void ChgText(wstring& chgText) const;
protected:
	bool ParseLine(const wstring& parseLine, pair<wstring, wstring>& item);
};

//�^��ςݏ��t�@�C���uRecInfo.txt�v�̓ǂݍ��݂ƕۑ��������s��
//�L�[��REC_FILE_INFO::id(��0)
class CParseRecInfoText : public CParseText<DWORD, REC_FILE_INFO>
{
public:
	CParseRecInfoText() : keepCount(UINT_MAX) {}
	using CParseText<DWORD, REC_FILE_INFO>::SaveText;
	//�^��ςݏ���ǉ�����
	DWORD AddRecInfo(const REC_FILE_INFO& item);
	//�^��ςݏ����폜����
	bool DelRecInfo(DWORD id);
	//�v���e�N�g����ύX����
	bool ChgProtectRecInfo(DWORD id, BYTE flag);
	void GetProtectFiles(map<wstring, wstring>* fileMap) const;
	//AddRecInfo����Ɏc���Ă�����v���e�N�g�̘^��ςݏ��̌���ݒ肷��
	void SetKeepCount(DWORD keepCount = UINT_MAX) { this->keepCount = keepCount; }
	void SetRecInfoDelFile(bool recInfoDelFile) { this->recInfoDelFile = recInfoDelFile; }
	void SetRecInfoFolder(LPCWSTR recInfoFolder) { ChkFolderPath(this->recInfoFolder = recInfoFolder); }
protected:
	bool ParseLine(const wstring& parseLine, pair<DWORD, REC_FILE_INFO>& item);
	bool SaveLine(const pair<DWORD, REC_FILE_INFO>& item, wstring& saveLine) const;
	bool SelectIDToSave(vector<DWORD>& sortList) const;
	//��񂪒ǉ�����钼�O�̕⑫���
	void OnAddRecInfo(REC_FILE_INFO& item);
	//��񂪍폜����钼�O�̕⑫���
	void OnDelRecInfo(const REC_FILE_INFO& item);
	DWORD keepCount;
	bool recInfoDelFile;
	wstring recInfoFolder;
};

struct PARSE_REC_INFO2_ITEM
{
	WORD originalNetworkID;
	WORD transportStreamID;
	WORD serviceID;
	SYSTEMTIME startTime;
	wstring eventName;
};

//�^��ς݃C�x���g���t�@�C���uRecInfo2.txt�v�̓ǂݍ��݂ƕۑ��������s��
//�L�[�͓ǂݍ��ݏ��ԍ�
class CParseRecInfo2Text : public CParseText<DWORD, PARSE_REC_INFO2_ITEM>
{
public:
	CParseRecInfo2Text() : keepCount(UINT_MAX) {}
	using CParseText<DWORD, PARSE_REC_INFO2_ITEM>::SaveText;
	DWORD Add(const PARSE_REC_INFO2_ITEM& item);
	void SetKeepCount(DWORD keepCount = UINT_MAX) { this->keepCount = keepCount; }
protected:
	bool ParseLine(const wstring& parseLine, pair<DWORD, PARSE_REC_INFO2_ITEM>& item);
	bool SaveLine(const pair<DWORD, PARSE_REC_INFO2_ITEM>& item, wstring& saveLine) const;
	bool SelectIDToSave(vector<DWORD>& sortList) const;
	DWORD keepCount;
};

//�\����t�@�C���uReserve.txt�v�̓ǂݍ��݂ƕۑ��������s��
//�L�[��reserveID(��0,�i���I)
class CParseReserveText : public CParseText<DWORD, RESERVE_DATA>
{
public:
	CParseReserveText() : nextID(1), saveNextID(1) {}
	using CParseText<DWORD, RESERVE_DATA>::SaveText;
	//�\�����ǉ�����
	DWORD AddReserve(const RESERVE_DATA& item);
	//�\�����ύX����
	bool ChgReserve(const RESERVE_DATA& item);
	//�\������폜����
	bool DelReserve(DWORD id);
	//�^��J�n�����Ń\�[�g���ꂽ�\��ꗗ���擾����
	vector<pair<LONGLONG, const RESERVE_DATA*>> GetReserveList(BOOL calcMargin = FALSE, int defStartMargin = 0) const;
protected:
	bool ParseLine(const wstring& parseLine, pair<DWORD, RESERVE_DATA>& item);
	bool SaveLine(const pair<DWORD, RESERVE_DATA>& item, wstring& saveLine) const;
	bool SaveFooterLine(wstring& saveLine) const;
	bool SelectIDToSave(vector<DWORD>& sortList) const;
	//�ߋ��ɒǉ�����ID�����傫�Ȓl�B100000000(1��)ID�ŏ��񂷂�(������1����1000ID����Ă�200�N�ȏォ����̂ōl���邾������)
	DWORD nextID;
	DWORD saveNextID;
};

//�\����t�@�C���uEpgAutoAdd.txt�v�̓ǂݍ��݂ƕۑ��������s��
//�L�[��dataID(��0,�i���I)
class CParseEpgAutoAddText : public CParseText<DWORD, EPG_AUTO_ADD_DATA>
{
public:
	CParseEpgAutoAddText() : nextID(1), saveNextID(1) {}
	using CParseText<DWORD, EPG_AUTO_ADD_DATA>::SaveText;
	DWORD AddData(const EPG_AUTO_ADD_DATA& item);
	bool ChgData(const EPG_AUTO_ADD_DATA& item);
	//�\��o�^����ύX����(�C�e���[�^�ɉe�����Ȃ�)
	bool SetAddCount(DWORD id, DWORD addCount);
	bool DelData(DWORD id);
protected:
	bool ParseLine(const wstring& parseLine, pair<DWORD, EPG_AUTO_ADD_DATA>& item);
	bool SaveLine(const pair<DWORD, EPG_AUTO_ADD_DATA>& item, wstring& saveLine) const;
	bool SaveFooterLine(wstring& saveLine) const;
	bool SelectIDToSave(vector<DWORD>& sortList) const;
	DWORD nextID;
	DWORD saveNextID;
};

//�\����t�@�C���uManualAutoAdd.txt�v�̓ǂݍ��݂ƕۑ��������s��
//�L�[��dataID(��0,�i���I)
class CParseManualAutoAddText : public CParseText<DWORD, MANUAL_AUTO_ADD_DATA>
{
public:
	CParseManualAutoAddText() : nextID(1), saveNextID(1) {}
	using CParseText<DWORD, MANUAL_AUTO_ADD_DATA>::SaveText;
	DWORD AddData(const MANUAL_AUTO_ADD_DATA& item);
	bool ChgData(const MANUAL_AUTO_ADD_DATA& item);
	bool DelData(DWORD id);
protected:
	bool ParseLine(const wstring& parseLine, pair<DWORD, MANUAL_AUTO_ADD_DATA>& item);
	bool SaveLine(const pair<DWORD, MANUAL_AUTO_ADD_DATA>& item, wstring& saveLine) const;
	bool SaveFooterLine(wstring& saveLine) const;
	bool SelectIDToSave(vector<DWORD>& sortList) const;
	DWORD nextID;
	DWORD saveNextID;
};
