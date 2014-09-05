#include "StdAfx.h"
#include "WriteMain.h"


CWriteMain::CWriteMain(void)
{

}


CWriteMain::~CWriteMain(void)
{

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
	ULONGLONG createSize,
	HINSTANCE hInstance
	)
{
	if( fileName == NULL ){
		return FALSE;
	}
	this->savePath = L"";

	this->savePath = fileName;

	WCHAR filePath[512] = L"";
	GetModuleFileName(hInstance, filePath, 512);

	wstring folder = L"";
	wstring fileTitle = L"";
	wstring iniPath = L"";

	GetFileFolder(filePath, folder);
	GetFileTitle(filePath, fileTitle);

	wstring grfPath = L"";
	Format(grfPath, L"%s\\%s.grf", folder.c_str(), fileTitle.c_str());
	Format(iniPath, L"%s\\%s.ini", folder.c_str(), fileTitle.c_str());

	WCHAR buff[256] = L"";
	GetPrivateProfileString(L"SET", L"ext", L"ts", buff, 256, iniPath.c_str());
	wstring ext = buff;
	if( ext.find(L".") == string::npos ){
		Format(ext, L".%s", buff);
	}

	HANDLE file = _CreateDirectoryAndFile( grfPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( file == INVALID_HANDLE_VALUE ){
		//�ݒ�t�@�C���Ȃ��̂ŐV�K�쐬
		dshowCtrl.CreateNewGraph();
	}else{
		CloseHandle(file);
		//�ݒ�t�@�C������̂Ń��[�h
		dshowCtrl.LoadGraph(grfPath.c_str());
	}

	wstring saveFileName = L"";
	wstring saveFolder = L"";
	GetFileFolder(fileName, saveFolder);
	GetFileTitle(fileName, saveFileName);
	wstring savePath = L"";
	Format(savePath, L"%s\\%s%s", saveFolder.c_str(), saveFileName.c_str(), ext.c_str());

	BOOL ret = dshowCtrl.CreateRunGraph(savePath.c_str());
	if( ret == TRUE ){
		this->savePath = savePath;
		//dshowCtrl.ConnectRunGraph();
	}
	return ret;
}

//�t�@�C���ۑ����I������
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
BOOL CWriteMain::_StopSave(
	)
{
	if( dshowCtrl.IsRun() == TRUE ){
		dshowCtrl.StopGraph();
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

	if( dshowCtrl.IsRun() == FALSE ){
		dshowCtrl.RunGraph();
	}
	ret = dshowCtrl.AddTS(data, size);
	if( writeSize != NULL ){
		*writeSize = 0;
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
