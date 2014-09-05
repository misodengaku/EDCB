#include "stdafx.h"
#include "BonDriverUtil.h"

CBonDriverUtil::CBonDriverUtil(void)
{
	this->lockEvent = CreateEvent(NULL, FALSE, TRUE, NULL );

	this->loadDllPath = L"";
	this->loadTunerName = L"";
	this->initChSetFlag = FALSE;
	this->bonIF = NULL;
	this->bon2IF = NULL;
	this->module = NULL;
}

CBonDriverUtil::~CBonDriverUtil(void)
{
	_CloseBonDriver();

	if( this->lockEvent != NULL ){
		UnLock();
		CloseHandle(this->lockEvent);
		this->lockEvent = NULL;
	}
}

BOOL CBonDriverUtil::Lock(LPCWSTR log, DWORD timeOut)
{
	if( this->lockEvent == NULL ){
		return FALSE;
	}
	if( log != NULL ){
		OutputDebugString(log);
	}
	DWORD dwRet = WaitForSingleObject(this->lockEvent, timeOut);
	if( dwRet == WAIT_ABANDONED || 
		dwRet == WAIT_FAILED){
		return FALSE;
	}
	return TRUE;
}

void CBonDriverUtil::UnLock(LPCWSTR log)
{
	if( this->lockEvent != NULL ){
		SetEvent(this->lockEvent);
	}
	if( log != NULL ){
		OutputDebugString(log);
	}
}

//BonDriver�t�H���_���w��
//�����F
// bonDriverFolderPath		[IN]BonDriver�t�H���_�p�X
void CBonDriverUtil::SetBonDriverFolder(
	LPCWSTR bonDriverFolderPath
)
{
	if( Lock() == FALSE ) return ;

	wstring strBonDriverFolderPath = bonDriverFolderPath;

	ChkFolderPath(strBonDriverFolderPath);

	this->bonDllList.clear();

	WIN32_FIND_DATA findData;
	HANDLE find;

	//�w��t�H���_�̃t�@�C���ꗗ�擾
	find = FindFirstFile( (strBonDriverFolderPath + L"\\BonDriver*.dll").c_str(), &findData);
	if ( find == INVALID_HANDLE_VALUE ) {
		UnLock();
		return ;
	}
	do{
		if( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ){
			//��������DLL���ꗗ�ɒǉ�
			this->bonDllList.push_back(strBonDriverFolderPath + L"\\" + findData.cFileName);
		}
	}while(FindNextFile(find, &findData));

	FindClose(find);

	UnLock();
}

//BonDriver�t�H���_��BonDriver_*.dll���
//�߂�l�F
// �G���[�R�[�h
//�����F
// bonList			[OUT]�����ł���BonDriver�ꗗ
DWORD CBonDriverUtil::EnumBonDriver(
	vector<wstring>* bonList
)
{
	if( Lock() == FALSE ) return ERR_FALSE;

	for( size_t i = 0; i < this->bonDllList.size(); i++ ){
		bonList->push_back(L"");
		GetFileName(this->bonDllList[i], bonList->back());
	}

	UnLock();

	return NO_ERR;
}

//BonDriver�����[�h���ă`�����l�����Ȃǂ��擾�i�t�@�C�����Ŏw��j
//�߂�l�F
// �G���[�R�[�h
//�����F
// bonDriverFile	[IN]EnumBonDriver�Ŏ擾���ꂽBonDriver�̃t�@�C����
DWORD CBonDriverUtil::OpenBonDriver(
	LPCWSTR bonDriverFile,
	int openWait
	)
{
	if( Lock() == FALSE ) return ERR_OPEN_TUNER;
	DWORD err = ERR_FIND_TUNER;
	for( size_t i = 0; i < this->bonDllList.size(); i++ ){
		wstring fileName;
		GetFileName(this->bonDllList[i], fileName);
		if( CompareNoCase(bonDriverFile, fileName) == 0 ){
			err = _OpenBonDriver(this->bonDllList[i].c_str(), openWait);
			break;
		}
	}
	if( err == ERR_FIND_TUNER ){
		_OutputDebugString(L"��Open����BonDriver��������܂���");
		OutputDebugString(bonDriverFile);
	}

	UnLock();
	return err;
}

//BonDriver�����[�h���̖{��
//�߂�l�F
// �G���[�R�[�h
//�����F
// bonDriverFilePath		[IN] ���[�h����BonDriver�̃t�@�C���p�X
DWORD CBonDriverUtil::_OpenBonDriver(
	LPCWSTR bonDriverFilePath,
	int openWait
	)
{
	_CloseBonDriver();

	this->module = ::LoadLibrary(bonDriverFilePath);
	if( this->module == NULL ){
		OutputDebugString(L"��BonDriver�����[�h�ł��܂���");
		OutputDebugString(bonDriverFilePath);
		return ERR_LOAD_MODULE;
	}
	IBonDriver* (*func)();
	func = (IBonDriver* (*)())::GetProcAddress( this->module , "CreateBonDriver");
	if( !func ){
		OutputDebugString(L"��GetProcAddress�Ɏ��s���܂���");
		_CloseBonDriver();
		return ERR_INIT;
	}
	this->bonIF = func();
	try{
		this->bon2IF = dynamic_cast<IBonDriver2 *>(bonIF);
		BOOL open = this->bonIF->OpenTuner();
		if( open == FALSE ){
			Sleep(1000);
			open = this->bonIF->OpenTuner();
		}

		if( open == FALSE ){
			//Open���s
			OutputDebugString(L"��OpenTuner�Ɏ��s���܂���");
			_CloseBonDriver();
			return ERR_OPEN_TUNER;
		}else{
			//Open����
			//�`���[�i�[���̎擾
			this->loadTunerName = this->bon2IF->GetTunerName();
			Replace(this->loadTunerName, L"(",L"�i");
			Replace(this->loadTunerName, L")",L"�j");
			//�`�����l���ꗗ�̎擾
			DWORD countSpace = 0;
			while(1){
				if( this->bon2IF->EnumTuningSpace(countSpace) != NULL ){
					BON_SPACE_INFO spaceItem;
					spaceItem.spaceName = this->bon2IF->EnumTuningSpace(countSpace);
					DWORD countCh = 0;

					while(1){
						LPCWSTR chName = this->bon2IF->EnumChannelName(countSpace, countCh);
						if( chName != NULL ){
							if( chName[0] != L'\0' ){
								spaceItem.chMap.insert(pair<DWORD,wstring>(countCh, chName));
							}
						}else{
							break;
						}
						countCh++;
					}
					this->loadChMap.insert(pair<DWORD, BON_SPACE_INFO>(countSpace, spaceItem));
				}else{
					break;
				}
				countSpace++;
			}
			Sleep(openWait);
			this->loadDllPath = bonDriverFilePath;
		}
	}catch(...){
		_CloseBonDriver();
		return ERR_OPEN_TUNER;
	}

	return NO_ERR;
}

//���[�h���Ă���BonDriver�̊J��
//�߂�l�F
// �G���[�R�[�h
DWORD CBonDriverUtil::CloseBonDriver()
{
	if( Lock() == FALSE ) return ERR_FALSE;
	DWORD err = NO_ERR;
	err = _CloseBonDriver();
	UnLock();
	return err;
}

DWORD CBonDriverUtil::_CloseBonDriver()
{
	DWORD err = NO_ERR;
	if( this->bonIF != NULL ){
		this->bonIF->CloseTuner();
		this->bonIF->Release();
		this->bonIF = NULL;
		this->bon2IF = NULL;
	}
	if( this->module != NULL ){
		::FreeLibrary( this->module );
		this->module = NULL;
	}
	this->loadDllPath = L"";
	this->loadTunerName = L"";
	this->loadChMap.clear();
	this->initChSetFlag = FALSE;
	return err;
}

//���[�h����BonDriver�̏��擾
//Space��Ch�̈ꗗ���擾����
//�߂�l�F
// �G���[�R�[�h
//�����F
// spaceMap			[OUT] Space��Ch�̈ꗗ�imap�̃L�[ Space�j
DWORD CBonDriverUtil::GetOriginalChList(
	map<DWORD, BON_SPACE_INFO>* spaceMap
)
{
	if( Lock() == FALSE ) return ERR_FALSE;

	if( spaceMap == NULL || this->bon2IF == NULL ){
		UnLock();
		return ERR_INVALID_ARG;
	}

	*spaceMap = this->loadChMap;

	UnLock();
	return NO_ERR;
}

//BonDriver�̃`���[�i�[�����擾
//�߂�l�F
// �`���[�i�[��
wstring CBonDriverUtil::GetTunerName()
{
	wstring name = L"";
	if( Lock() == FALSE ) return name;

	name = this->loadTunerName;

	UnLock();
	return name;
}

//�`�����l���ύX
//�߂�l�F
// �G���[�R�[�h
//�����F
// space			[IN]�ύX�`�����l����Space
// ch				[IN]�ύX�`�����l���̕���Ch
DWORD CBonDriverUtil::SetCh(
	DWORD space,
	DWORD ch
	)
{
	if( Lock() == FALSE ) return FALSE;
	if( this->bon2IF == NULL ){
		UnLock();
		return ERR_NOT_INIT;
	}
	//����͏�Ƀ`�����l���ݒ�s��
	if( this->initChSetFlag == TRUE ){
		//�Q��ڈȍ~�͕ύX�������ꍇ�ɍs��
		if( space == this->bon2IF->GetCurSpace() &&
			ch == this->bon2IF->GetCurChannel() )
		{
			UnLock();
			return NO_ERR;
		}
	}
	if( this->bon2IF->SetChannel(space, ch) == FALSE ){
		Sleep(500);
		if( this->bon2IF->SetChannel(space, ch) == FALSE ){
			UnLock();
			return ERR_FALSE;
		}
	}
	this->initChSetFlag = TRUE;
	UnLock();
	return NO_ERR;
}

//���݂̃`�����l���擾
//�߂�l�F
// �G���[�R�[�h
//�����F
// space			[IN]���݂̃`�����l����Space
// ch				[IN]���݂̃`�����l���̕���Ch
DWORD CBonDriverUtil::GetNowCh(
	DWORD* space,
	DWORD* ch
	)
{
	if( Lock() == FALSE ) return FALSE;
	if( this->bon2IF == NULL || this->initChSetFlag == FALSE ){
		UnLock();
		return FALSE;
	}
	*space = this->bon2IF->GetCurSpace();
	*ch = this->bon2IF->GetCurChannel();
	UnLock();
	return TRUE;
}

//TS�X�g���[�����擾
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// data				[OUT]BonDriver�����o�b�t�@�̃|�C���^
// size				[OUT]�擾�o�b�t�@�̃T�C�Y
// remain			[OUT]���擾�o�b�t�@�̃T�C�Y
BOOL CBonDriverUtil::GetTsStream(
	BYTE **data,
	DWORD *size,
	DWORD *remain
	)
{
	if( Lock() == FALSE ) return FALSE;

	BOOL ret = FALSE;
	if( this->bonIF == NULL ){
		UnLock();
		return FALSE;
	}
	try{
		ret = this->bonIF->GetTsStream(data, size, remain);
	}catch(...){
		ret = FALSE;
	}
	UnLock();
	return ret;
}

//�V�O�i�����x���̎擾
//�߂�l�F
// �V�O�i�����x��
float CBonDriverUtil::GetSignalLevel()
{
	if( Lock() == FALSE ) return 0;
	if( this->bonIF == NULL ){
		UnLock();
		return 0;
	}
	float fLevel = this->bonIF->GetSignalLevel();
	UnLock();
	return fLevel;
}

//Open����BonDriver�̃t�@�C�������擾
//�߂�l�F
// BonDriver�̃t�@�C�����i�g���q�܂ށj�iempty�Ŗ�Open�j
wstring CBonDriverUtil::GetOpenBonDriverFileName()
{
	wstring ret = L"";
	if( Lock() == FALSE ) return ret;

	GetFileName(this->loadDllPath, ret);

	UnLock();
	return ret;
}
