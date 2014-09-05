// twitter.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "twitter.h"
#include "../../Common/Util.h"
#include "TwitterMain.h"
#include "../../Common/InstanceManager.h"

CInstanceManager<CTwitterMain> g_instMng;

//DLL�̏�����
//�߂�l�F
// �G���[�R�[�h
//�����F
// id				[OUT]����ID
DWORD WINAPI InitializeTW(
	DWORD* id
	)
{
	if( id == NULL ){
		return ERR_INVALID_ARG;
	}

	DWORD err = ERR_FALSE;

	try{
		std::shared_ptr<CTwitterMain> ptr = std::make_shared<CTwitterMain>();
		err = ptr->Initialize();
		if( err == NO_ERR ){
			*id = g_instMng.push(ptr);
		}
	}catch( std::bad_alloc& ){
		err = ERR_FALSE;
	}
	return err;
}

//DLL�̊J��
//�߂�l�F
// �G���[�R�[�h
//�����F
// id		[IN]����ID InitializeEP�̖߂�l
DWORD WINAPI UnInitializeTW(
	DWORD id
	)
{
	DWORD err = ERR_NOT_INIT;
	{
		std::shared_ptr<CTwitterMain> ptr = g_instMng.pop(id);
		if( ptr != NULL ){
			err = ptr->UnInitialize();
		}
	}

	return err;
}


//IE��Proxy�ݒ���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// proxyConfig		[OUT]IE��Proxy�ݒ�̏��i����API�ďo���܂Ń������m�ہj
BOOL WINAPI GetIEProxyConfigTW(
	DWORD id,
	CURRENT_USER_IE_PROXY_CONFIG** proxyConfig
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->GetIEProxyConfig(proxyConfig);
}

//�����I�Ɍ��o��Proxy�̃A�h���X���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// proxyConfig		[OUT]Proxy�̏��i����API�ďo���܂Ń������m�ہj
BOOL WINAPI GetProxyAutoDetectTW(
	DWORD id,
	PROXY_CONFIG** proxyConfig
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->GetProxyAutoDetect(proxyConfig);
}

//�����\���X�N���v�g��Proxy�̃A�h���X���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// scriptURL		[IN]�����\���X�N���v�g��URL
// proxyConfig		[OUT]Proxy�̏��i����API�ďo���܂Ń������m�ہj
BOOL WINAPI GetProxyAutoScriptTW(
	DWORD id,
	LPCWSTR scriptURL,
	PROXY_CONFIG** proxyConfig
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->GetProxyAutoScript(scriptURL, proxyConfig);
}

//Proxy�g�p��ݒ�
//�߂�l�F
// �G���[�R�[�h
//�����F
// useProxy			[IN]Proxy�g�����ǂ����iTRUE:Proxy�g���j
// proxyInfo		[IN]Proxy�g���ꍇ�̐ݒ���
void WINAPI SetProxyTW(
	DWORD id,
	BOOL useProxy,
	USE_PROXY_INFO* proxyInfo
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return ;
	}

	ptr->SetProxy(useProxy, proxyInfo);
}

//�F�ؗp���O�C��URL���擾����
//�߂�l�F
// �G���[�R�[�h
//�����F
// url			[OUT]�F�ؗp���O�C��URL�i����API�ďo���܂Ń������m�ہj
DWORD WINAPI GetAuthorizationUrlTW(
	DWORD id,
	WCHAR** url
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->GetAuthorizationUrl(url);
}

//�F�،��ʂ̈Ïؔԍ���ݒ肷��
//������GetAuthorizationUrl�Ŏ擾�����l���g�p����̂ŁA��A�̗���Őݒ肷��K�v����
//�߂�l�F
// �G���[�R�[�h
//�����F
// password		[IN]�Ïؔԍ�
DWORD WINAPI SetAuthorizationPWDTW(
	DWORD id,
	LPCWSTR password
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->SetAuthorizationPWD(password);
}

//�c�C�[�g����
//�߂�l�F
// �G���[�R�[�h
//�����F
// asyncMode	[IN]�񓯊��ő��M
// text			[IN]�c�C�[�g���e
DWORD WINAPI SendTweetTW(
	DWORD id,
	BOOL asyncMode,
	LPCWSTR text
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->SendTweet(asyncMode, text);
}

//�񓯊��c�C�[�g�̎c����擾����
//�߂�l�F
// ��
//�����F
DWORD WINAPI GetTweetQueTW(
	DWORD id
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->GetTweetQue();
}

//�X�g���[�~���O���J�n����
//�߂�l�F
// �G���[�R�[�h
//�����F
// track		[IN]filter��track
// streamingID	[OUT]�X�g���[�~���O����ID
DWORD WINAPI StartTweetStreamingTW(
	DWORD id,
	LPCWSTR track,
	TW_CALLBACK_Streaming callbackFunc,
	void* callbackFuncParam,
	DWORD* streamingID
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->StartTweetStreaming(track, callbackFunc, callbackFuncParam, streamingID);
}

//�X�g���[�~���O���~����
//�߂�l�F
// �G���[�R�[�h
//�����F
// streamingID	[IN]�X�g���[�~���O����ID
DWORD WINAPI StopTweetStreamingTW(
	DWORD id,
	DWORD streamingID
	)
{
	std::shared_ptr<CTwitterMain> ptr = g_instMng.find(id);
	if( ptr == NULL ){
		return FALSE;
	}

	return ptr->StopTweetStreaming(streamingID);
}
