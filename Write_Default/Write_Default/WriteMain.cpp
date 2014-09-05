#include "StdAfx.h"
#include "WriteMain.h"

extern HINSTANCE g_instance;

CWriteMain::CWriteMain(void)
{
	this->file = NULL;
	this->writeBuff = NULL;
	this->writeBuffSize = 0;
	this->writeBuffPos = 0;

	WCHAR dllPath[512] = L"";
	GetModuleFileName(g_instance, dllPath, 512);

	wstring iniPath = dllPath;
	iniPath += L".ini";

	this->writeBuffSize = (DWORD)GetPrivateProfileIntW(L"SET", L"Size", 770048, iniPath.c_str());
	SAFE_DELETE_ARRAY(this->writeBuff);
	if( this->writeBuffSize > 0 ){
		this->writeBuff = new BYTE[this->writeBuffSize];
	}
	this->writeBuffPos = 0;
}


CWriteMain::~CWriteMain(void)
{
	if( this->file != NULL ){
		_StopSave();
	}

	SAFE_DELETE_ARRAY(this->writeBuff);
	this->writeBuffSize = 0;
	this->writeBuffPos = 0;
}

//�t�@�C���ۑ����J�n����
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// fileName				[IN]�ۑ��t�@�C���t���p�X�i�K�v�ɉ����Ċg���q�ς�����ȂǍs���j
// overWriteFlag		[IN]����t�@�C�������ݎ��ɏ㏑�����邩�ǂ����iTRUE�F����AFALSE�F���Ȃ��j
// createSize			[IN]���͗\�z�e�ʁi188�o�C�gTS�ł̗e�ʁB�����^�掞�ȂǑ����Ԗ���̏ꍇ��0�B�����Ȃǂ̉\��������̂Ŗڈ����x�j
BOOL CWriteMain::_StartSave(
	LPCWSTR fileName,
	BOOL overWriteFlag,
	ULONGLONG createSize
	)
{
	this->savePath = L"";

	wstring errMsg = L"";
	DWORD err = 0;

	wstring recFilePath = fileName;
	if( overWriteFlag == TRUE ){
		_OutputDebugString(L"��_StartSave CreateFile:%s", recFilePath.c_str());
		this->file = _CreateDirectoryAndFile( recFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
		if( this->file == INVALID_HANDLE_VALUE ){
			err = GetLastError();
			GetLastErrMsg(err, errMsg);
			_OutputDebugString(L"��_StartSave Err:0x%08X %s", err, errMsg.c_str());
			if( GetNextFileName(fileName, recFilePath) == TRUE ){
				_OutputDebugString(L"��_StartSave CreateFile:%s", recFilePath.c_str());
				this->file = _CreateDirectoryAndFile( recFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
			}
		}
	}else{
		_OutputDebugString(L"��_StartSave CreateFile:%s", recFilePath.c_str());
		this->file = _CreateDirectoryAndFile( recFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL );
		if( this->file == INVALID_HANDLE_VALUE ){
			err = GetLastError();
			GetLastErrMsg(err, errMsg);
			_OutputDebugString(L"��_StartSave Err:0x%08X %s", err, errMsg.c_str());
			if( GetNextFileName(fileName, recFilePath) == TRUE ){
				_OutputDebugString(L"��_StartSave CreateFile:%s", recFilePath.c_str());
				this->file = _CreateDirectoryAndFile( recFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL );
			}
		}
	}
	if( this->file == INVALID_HANDLE_VALUE ){
		err = GetLastError();
		GetLastErrMsg(err, errMsg);
		_OutputDebugString(L"��_StartSave Err:0x%08X %s", err, errMsg.c_str());
		this->file = NULL;
		return FALSE;
	}

	//�f�B�X�N�ɗe�ʂ��m��
	if( createSize > 0 ){
		LARGE_INTEGER stPos;
		stPos.QuadPart = createSize;
		SetFilePointerEx( this->file, stPos, NULL, FILE_BEGIN );
		SetEndOfFile( this->file );
		FlushFileBuffers( this->file );
		SetFilePointer( this->file, 0, NULL, FILE_BEGIN );
	}

	this->savePath = recFilePath;

	return TRUE;
}

//�t�@�C���ۑ����I������
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
BOOL CWriteMain::_StopSave(
	)
{
	if( this->file != NULL ){
		if( this->writeBuffPos > 0 ){
			DWORD writeSize = 0;
			DWORD err = 0;
			wstring errMsg = L"";
			if( WriteFile(this->file, this->writeBuff, this->writeBuffPos, &writeSize, NULL) == FALSE ){
				err = GetLastError();
				GetLastErrMsg(err, errMsg);
				_OutputDebugString(L"��_StopSave WriteFile Err:0x%08X %s", err, errMsg.c_str());
			}else{
				this->writeBuffPos = 0;
			}
		}
		SetEndOfFile(this->file);
		CloseHandle(this->file);
		this->file = NULL;
	}

	return TRUE;
}

//���ۂɕۑ����Ă���t�@�C���p�X���擾����i�Đ���o�b�`�����ɗ��p�����j
//filePath��NULL���͕K�v�ȃT�C�Y��filePathSize�ŕԂ�
//�ʏ�filePathSize=512�ŌĂяo��
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// filePath				[OUT]�ۑ��t�@�C���t���p�X
// filePathSize			[IN/OUT]filePath�̃T�C�Y(WCHAR�P��)
BOOL CWriteMain::_GetSaveFilePath(
	WCHAR* filePath,
	DWORD* filePathSize
	)
{
	if( filePath == NULL ){
		if( filePathSize == NULL ){
			return FALSE;
		}else{
			*filePathSize = (DWORD)this->savePath.size()+1;
		}
	}else{
		if( filePathSize == NULL ){
			return FALSE;
		}else{
			if( *filePathSize < (DWORD)this->savePath.size()+1 ){
				*filePathSize = (DWORD)this->savePath.size()+1;
				return FALSE;
			}else{
				wcscpy_s(filePath, *filePathSize, this->savePath.c_str());
			}
		}
	}
	return TRUE;
}

//�ۑ��pTS�f�[�^�𑗂�
//�󂫗e�ʕs���Ȃǂŏ����o�����s�����ꍇ�AwriteSize�̒l������
//�ēx�ۑ���������Ƃ��̑��M�J�n�n�_�����߂�
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// data					[IN]TS�f�[�^
// size					[IN]data�̃T�C�Y
// writeSize			[OUT]�ۑ��ɗ��p�����T�C�Y
BOOL CWriteMain::_AddTSBuff(
	BYTE* data,
	DWORD size,
	DWORD* writeSize
	)
{
	BOOL ret = FALSE;
	wstring errMsg = L"";
	DWORD err = 0;
	if( this->file != NULL && data != NULL && size > 0 ){
		if( this->writeBuffSize > 0 && this->writeBuff != NULL){
			if( size > this->writeBuffSize ){
				//�o�b�t�@�T�C�Y���傫���̂ł��̂܂܏o��
				if( this->writeBuffPos > 0 ){
					//�O��̃o�b�t�@����̂Ő�ɏo��
					DWORD write = 0;
					wstring errMsg = L"";
					if( WriteFile(this->file, this->writeBuff, this->writeBuffPos, &write, NULL) == FALSE ){
						//�G���[���o��
						err = GetLastError();
						GetLastErrMsg(err, errMsg);
						_OutputDebugString(L"��_StopSave WriteFile Err:0x%08X %s", err, errMsg.c_str());
						*writeSize = 0;
						//�������߂Ȃ������������o�b�t�@�̐擪�փR�s�[
						DWORD tempBuffSize = this->writeBuffPos-write;
						if( tempBuffSize > 0 ){
							BYTE* tempBuff = new BYTE[tempBuffSize];
							memcpy( tempBuff, this->writeBuff+write, tempBuffSize);
							this->writeBuffPos = tempBuffSize;
							memcpy(this->writeBuff, tempBuff, tempBuffSize);
							SAFE_DELETE_ARRAY(tempBuff);
						}

						SetEndOfFile(this->file);
						CloseHandle(this->file);
						this->file = NULL;

						return FALSE;
					}else{
						this->writeBuffPos = 0;
					}
				}
				//�t�@�C���o��
				if( WriteFile(this->file, data, size, writeSize, NULL) == FALSE ){
					//�G���[���o��
					err = GetLastError();
					GetLastErrMsg(err, errMsg);
					_OutputDebugString(L"��WriteFile Err:0x%08X %s", err, errMsg.c_str());

					SetEndOfFile(this->file);
					CloseHandle(this->file);
					this->file = NULL;

					return FALSE;
				}else{
					ret = TRUE;
				}
			}else{
				if(this->writeBuffSize < this->writeBuffPos + size){
					//�o�b�t�@���܂�̂ŏo��
					DWORD tempSize = this->writeBuffSize - this->writeBuffPos;
					memcpy( this->writeBuff+this->writeBuffPos, data, tempSize );
					DWORD tempWriteSize = 0;
					if( WriteFile(this->file, this->writeBuff, this->writeBuffSize, &tempWriteSize, NULL) == FALSE ){
						//�G���[
						err = GetLastError();
						GetLastErrMsg(err, errMsg);
						_OutputDebugString(L"��_StopSave WriteFile Err:0x%08X %s", err, errMsg.c_str());
						*writeSize = 0;
						//�t�@�C���|�C���^�߂�
						LONG lpos = (LONG)tempWriteSize;
						SetFilePointer(this->file, -lpos, NULL, FILE_CURRENT);

						SetEndOfFile(this->file);
						CloseHandle(this->file);
						this->file = NULL;

						return FALSE;
					}else{
						//�o�b�t�@�ɃR�s�[
						memcpy( this->writeBuff, data+tempSize, size-tempSize );
						this->writeBuffPos = size-tempSize;
						*writeSize = size;
						ret = TRUE;
					}
				}else{
					//�o�b�t�@�ɃR�s�[
					memcpy( this->writeBuff+this->writeBuffPos, data, size );
					this->writeBuffPos += size;
					*writeSize = size;
					ret = TRUE;
				}
			}
		}else{
			ret = WriteFile(this->file, data, size, writeSize, NULL);
			if( ret == FALSE ){
				err = GetLastError();
				GetLastErrMsg(err, errMsg);
				_OutputDebugString(L"��WriteFile Err:0x%08X %s", err, errMsg.c_str());

				SetEndOfFile(this->file);
				CloseHandle(this->file);
				this->file = NULL;
			}
		}
	}
	return ret;
}

BOOL CWriteMain::GetNextFileName(wstring filePath, wstring& newPath)
{
	WCHAR szPath[_MAX_PATH];
	WCHAR szDrive[_MAX_DRIVE];
	WCHAR szDir[_MAX_DIR];
	WCHAR szFname[_MAX_FNAME];
	WCHAR szExt[_MAX_EXT];
	_wsplitpath_s( filePath.c_str(), szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFname, _MAX_FNAME, szExt, _MAX_EXT );
	_wmakepath_s(  szPath, _MAX_PATH, szDrive, szDir, NULL, NULL );

	BOOL findFlag = FALSE;
	for( int i=1; i<1000; i++ ){
		WIN32_FIND_DATA findData;
		HANDLE find;

		wstring name;
		Format(name, L"%s%s-(%d)%s", szPath, szFname, i, szExt);
		newPath = name;
		
		find = FindFirstFile( newPath.c_str(), &findData);
		if ( find == INVALID_HANDLE_VALUE ) {
			findFlag = TRUE;
			break;
		}
		FindClose(find);
	}
	return findFlag;
}
