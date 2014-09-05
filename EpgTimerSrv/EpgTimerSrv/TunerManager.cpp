#include "StdAfx.h"
#include "TunerManager.h"


CTunerManager::CTunerManager(void)
{
}


CTunerManager::~CTunerManager(void)
{
}

BOOL CTunerManager::FindBonFileName(wstring src, wstring& dllName)
{
	size_t pos = src.rfind(L')');
	if( pos == string::npos ){
		return FALSE;
	}

	int count = 1;
	for( int i=(int)pos-1; i>=0; i-- ){
		if( src[i] == L')' ){
			count++;
		}else if( src[i] == L'(' ){
			count--;
		}
		if( count == 0 ){
			dllName = src.substr(0, i);
			return TRUE;
		}
	}

	return FALSE;
}

//�`���[�i�[�ꗗ�̓ǂݍ��݂��s��
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
BOOL CTunerManager::ReloadTuner()
{
	this->tunerMap.clear();

	wstring path = L"";
	GetSettingPath(path);

	wstring srvIniPath = L"";
	GetEpgTimerSrvIniPath(srvIniPath);

	wstring searchKey = path;
	searchKey += L"\\*.ChSet4.txt";

	WIN32_FIND_DATA findData;
	HANDLE find;

	//�w��t�H���_�̃t�@�C���ꗗ�擾
	find = FindFirstFile( searchKey.c_str(), &findData);
	if ( find == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	do{
		if( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ){
			wstring bonFileName;
			if( FindBonFileName(findData.cFileName, bonFileName) != FALSE ){
				wstring chSetPath = L"";
				Format(chSetPath, L"%s\\%s", path.c_str(), findData.cFileName);

				bonFileName += L".dll";

				WORD count = (WORD)GetPrivateProfileInt(bonFileName.c_str(), L"Count", 0, srvIniPath.c_str());
				if( count != 0 ){
					//�J�E���g0�ȏ�̂��̂������p
					WORD priority = (WORD)GetPrivateProfileInt(bonFileName.c_str(), L"Priority", 0, srvIniPath.c_str());
					BOOL epgCapFlag = (BOOL)GetPrivateProfileInt(bonFileName.c_str(), L"GetEpg", 1, srvIniPath.c_str());
					WORD EPGcount = (WORD)GetPrivateProfileInt(bonFileName.c_str(), L"EPGCount", count, srvIniPath.c_str());
					if(EPGcount==0)	EPGcount = count;

					if( this->tunerMap.find((DWORD)priority<<16 | 1) != this->tunerMap.end() ){
						OutputDebugString(L"CTunerManager::ReloadTuner(): Duplicate bonID\r\n");
						count = 0;
					}
					for( WORD i=1; i<=count; i++ ){
						TUNER_INFO item;
						item.epgCapMaxOfThisBon = min(epgCapFlag == FALSE ? 0 : EPGcount, count);
						item.bonFileName = bonFileName;
						item.chSet4FilePath = chSetPath;
						CParseChText4 chUtil;
						chUtil.ParseText(chSetPath.c_str());
						map<DWORD, CH_DATA4>::const_iterator itr;
						for( itr = chUtil.GetMap().begin(); itr != chUtil.GetMap().end(); itr++ ){
							item.chList.push_back(itr->second);
						}
						this->tunerMap.insert(pair<DWORD, TUNER_INFO>((DWORD)priority<<16 | i, item));
					}
				}
			}
		}
	}while(FindNextFile(find, &findData));

	FindClose(find);

	return TRUE;
}


//�`���[�i�[��ID�ꗗ���擾����B
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// idList			[OUT]�`���[�i�[��ID�ꗗ
BOOL CTunerManager::GetEnumID(
	vector<DWORD>* idList
	) const
{
	if( idList == NULL ){
		return FALSE;
	}
	map<DWORD, TUNER_INFO>::const_iterator itr;
	for( itr = this->tunerMap.begin(); itr != this->tunerMap.end(); itr++ ){
		idList->push_back(itr->first);
	}
	return TRUE;
}

//�`���[�i�[�\�񐧌���擾����
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// ctrlMap			[OUT]�`���[�i�[�\�񐧌�̈ꗗ
BOOL CTunerManager::GetEnumTunerBank(
	map<DWORD, CTunerBankCtrl*>* ctrlMap
	) const
{
	if( ctrlMap == NULL ){
		return FALSE;
	}
	map<DWORD, TUNER_INFO>::const_iterator itr;
	for( itr = this->tunerMap.begin(); itr != this->tunerMap.end(); itr++ ){
		CTunerBankCtrl* ctrl = new CTunerBankCtrl;
		ctrl->SetTunerInfo( itr->first >> 16, itr->first & 0xFFFF, itr->second.bonFileName, itr->second.chSet4FilePath);
		ctrlMap->insert(pair<DWORD, CTunerBankCtrl*>(itr->first, ctrl));
	}
	return TRUE;
}

//�w��T�[�r�X���T�|�[�g���Ă��Ȃ��`���[�i�[�ꗗ���擾����
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// ONID				[IN]�m�F�������T�[�r�X��ONID
// TSID				[IN]�m�F�������T�[�r�X��TSID
// SID				[IN]�m�F�������T�[�r�X��SID
// idList			[OUT]�`���[�i�[��ID�ꗗ
BOOL CTunerManager::GetNotSupportServiceTuner(
	WORD ONID,
	WORD TSID,
	WORD SID,
	vector<DWORD>* idList
	) const
{
	if( idList == NULL ){
		return FALSE;
	}
	map<DWORD, TUNER_INFO>::const_iterator itr;
	for( itr = this->tunerMap.begin(); itr != this->tunerMap.end(); itr++ ){
		vector<CH_DATA4>::const_iterator itrCh;
		for( itrCh = itr->second.chList.begin(); itrCh != itr->second.chList.end(); itrCh++ ){
			if( itrCh->originalNetworkID == ONID && itrCh->transportStreamID == TSID && itrCh->serviceID == SID ){
				break;
			}
		}
		if( itrCh == itr->second.chList.end() ){
			idList->push_back(itr->first);
		}

	}
	return TRUE;
}

BOOL CTunerManager::GetSupportServiceTuner(
	WORD ONID,
	WORD TSID,
	WORD SID,
	vector<DWORD>* idList
	) const
{
	if( idList == NULL ){
		return FALSE;
	}
	map<DWORD, TUNER_INFO>::const_iterator itr;
	for( itr = this->tunerMap.begin(); itr != this->tunerMap.end(); itr++ ){
		vector<CH_DATA4>::const_iterator itrCh;
		for( itrCh = itr->second.chList.begin(); itrCh != itr->second.chList.end(); itrCh++ ){
			if( itrCh->originalNetworkID == ONID && itrCh->transportStreamID == TSID && itrCh->serviceID == SID ){
				idList->push_back(itr->first);
				break;
			}
		}

	}
	return TRUE;
}

BOOL CTunerManager::GetCh(
	DWORD tunerID,
	WORD ONID,
	WORD TSID,
	WORD SID,
	DWORD* space,
	DWORD* ch
	) const
{
	map<DWORD, TUNER_INFO>::const_iterator itr;
	for( itr = this->tunerMap.begin(); itr != this->tunerMap.end(); itr++ ){
		vector<CH_DATA4>::const_iterator itrCh;
		for( itrCh = itr->second.chList.begin(); itrCh != itr->second.chList.end(); itrCh++ ){
			if( itrCh->originalNetworkID == ONID && itrCh->transportStreamID == TSID && itrCh->serviceID == SID ){
				if( space != NULL ){
					*space = itrCh->space;
				}
				if( ch != NULL ){
					*ch = itrCh->ch;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

//�h���C�o���̃`���[�i�[�ꗗ��EPG�擾�Ɏg�p�ł���`���[�i�[���̃y�A���擾����
BOOL CTunerManager::GetEnumEpgCapTuner(
	vector<pair<vector<DWORD>, WORD>>* idList
	) const
{
	if( idList == NULL ){
		return FALSE;
	}
	map<DWORD, TUNER_INFO>::const_iterator itr;
	for( itr = this->tunerMap.begin(); itr != this->tunerMap.end(); itr++ ){
		if( idList->empty() || idList->back().first.back() >> 16 != itr->first >> 16 ){
			idList->push_back(pair<vector<DWORD>, WORD>(vector<DWORD>(), itr->second.epgCapMaxOfThisBon));
		}
		idList->back().first.push_back(itr->first);
	}
	return TRUE;
}

BOOL CTunerManager::IsSupportService(
	DWORD tunerID,
	WORD ONID,
	WORD TSID,
	WORD SID
	) const
{
	map<DWORD, TUNER_INFO>::const_iterator itr;
	itr = this->tunerMap.find(tunerID);
	if( itr == this->tunerMap.end() ){
		return FALSE;
	}

	vector<CH_DATA4>::const_iterator itrCh;
	for( itrCh = itr->second.chList.begin(); itrCh != itr->second.chList.end(); itrCh++ ){
		if( itrCh->originalNetworkID == ONID && itrCh->transportStreamID == TSID && itrCh->serviceID == SID ){
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTunerManager::GetBonFileName(
	DWORD tunerID,
	wstring& bonFileName
	) const
{
	map<DWORD, TUNER_INFO>::const_iterator itr;
	itr = this->tunerMap.find(tunerID);
	if( itr == this->tunerMap.end() ){
		return FALSE;
	}
	bonFileName = itr->second.bonFileName;

	return TRUE;
}
