#ifndef __CTRL_CMD_UTIL2_H__
#define __CTRL_CMD_UTIL2_H__

#include "StructDef.h"
#include "CtrlCmdUtil.h"

template<class T> DWORD CCUTIL2_GetVectorVALUESize2_( WORD ver, vector<T>* val );
template<class T> DWORD CCUTIL2_GetPtrVectorVALUESize2_( WORD ver, vector<T>* val );
template<class T> BOOL CCUTIL2_WriteVectorVALUE2_( WORD ver, vector<T>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
template<class T> BOOL CCUTIL2_WritePtrVectorVALUE2_( WORD ver, vector<T>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
template<class T> BOOL CCUTIL2_ReadVectorVALUE2_( WORD ver, vector<T>* val, BYTE* buff, DWORD buffSize, DWORD* readSize );
template<class T> BOOL CCUTIL2_ReadAndNewVectorVALUE2_( WORD ver, vector<T*>* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

#define CCUTIL2_INHERIT_GET_SIZE_		{ ver; return GetVALUESize(val); }
#define CCUTIL2_INHERIT_WRITE_			{ ver; return WriteVALUE(val, buff, buffSize, writeSize); }
#define CCUTIL2_INHERIT_READ_			{ ver; return ReadVALUE(val, buff, buffSize, readSize); }
#define CCUTIL2_VECTOR_GET_SIZE_		return CCUTIL2_GetVectorVALUESize2_(ver, val)
#define CCUTIL2_VECTOR_GET_SIZE_PTR_	return CCUTIL2_GetPtrVectorVALUESize2_(ver, val)
#define CCUTIL2_VECTOR_WRITE_			return CCUTIL2_WriteVectorVALUE2_(ver, val, buff, buffSize, writeSize)
#define CCUTIL2_VECTOR_WRITE_PTR_		return CCUTIL2_WritePtrVectorVALUE2_(ver, val, buff, buffSize, writeSize)
#define CCUTIL2_VECTOR_READ_			return CCUTIL2_ReadVectorVALUE2_(ver, val, buff, buffSize, readSize)
#define CCUTIL2_VECTOR_READ_AND_NEW_	return CCUTIL2_ReadAndNewVectorVALUE2_(ver, val, buff, buffSize, readSize)

////////////////////////////////////////////////////////////////////////////////////////////
//コマンド送信用バイナリ作成関数

inline DWORD GetVALUESize2(WORD ver, char val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, char val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, char* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }
inline DWORD GetVALUESize2(WORD ver, unsigned char val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, unsigned char val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, unsigned char* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, short val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, short val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, short* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }
inline DWORD GetVALUESize2(WORD ver, unsigned short val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, unsigned short val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, unsigned short* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, int val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, int val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, int* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }
inline DWORD GetVALUESize2(WORD ver, unsigned int val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, unsigned int val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, unsigned int* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, long val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, long val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, long* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }
inline DWORD GetVALUESize2(WORD ver, unsigned long val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, unsigned long val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, unsigned long* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, __int64 val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, __int64 val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, __int64* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }
inline DWORD GetVALUESize2(WORD ver, unsigned __int64 val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, unsigned __int64 val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, unsigned __int64* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, vector<unsigned short>* val){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<unsigned short>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<unsigned short>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, vector<unsigned long>* val){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<unsigned long>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<unsigned long>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, vector<__int64>* val){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<__int64>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<__int64>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, const wstring& val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, const wstring& val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, wstring* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, vector<wstring>* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<wstring>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<wstring>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, SYSTEMTIME* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, SYSTEMTIME* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, SYSTEMTIME* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, REC_FILE_SET_INFO* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, REC_FILE_SET_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, REC_FILE_SET_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, vector<REC_FILE_SET_INFO>* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<REC_FILE_SET_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<REC_FILE_SET_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

DWORD GetVALUESize2(WORD ver, REC_SETTING_DATA* val );
BOOL WriteVALUE2(WORD ver, REC_SETTING_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
BOOL ReadVALUE2(WORD ver, REC_SETTING_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

DWORD GetVALUESize2(WORD ver, RESERVE_DATA* val );
BOOL WriteVALUE2(WORD ver, RESERVE_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
BOOL ReadVALUE2(WORD ver, RESERVE_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

inline DWORD GetVALUESize2(WORD ver, vector<RESERVE_DATA>* val ){ CCUTIL2_VECTOR_GET_SIZE_PTR_; }
inline BOOL WriteVALUE2(WORD ver, vector<RESERVE_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_VECTOR_WRITE_PTR_; }
inline BOOL ReadVALUE2(WORD ver, vector<RESERVE_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_VECTOR_READ_; }
inline DWORD GetVALUESize2(WORD ver, vector<RESERVE_DATA*>* val ){ CCUTIL2_VECTOR_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<RESERVE_DATA*>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_VECTOR_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<RESERVE_DATA*>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_VECTOR_READ_AND_NEW_; }

DWORD GetVALUESize2(WORD ver, NOTIFY_SRV_INFO* val );
BOOL WriteVALUE2(WORD ver, NOTIFY_SRV_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
BOOL ReadVALUE2(WORD ver, NOTIFY_SRV_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

inline DWORD GetVALUESize2(WORD ver, EPGDB_CONTENT_DATA* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, EPGDB_CONTENT_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, EPGDB_CONTENT_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, vector<EPGDB_CONTENT_DATA>* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<EPGDB_CONTENT_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<EPGDB_CONTENT_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, EPGDB_SEARCH_DATE_INFO* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, EPGDB_SEARCH_DATE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, EPGDB_SEARCH_DATE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

inline DWORD GetVALUESize2(WORD ver, vector<EPGDB_SEARCH_DATE_INFO>* val ){ CCUTIL2_INHERIT_GET_SIZE_; }
inline BOOL WriteVALUE2(WORD ver, vector<EPGDB_SEARCH_DATE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_INHERIT_WRITE_; }
inline BOOL ReadVALUE2(WORD ver, vector<EPGDB_SEARCH_DATE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_INHERIT_READ_; }

DWORD GetVALUESize2(WORD ver, EPGDB_SEARCH_KEY_INFO* val );
BOOL WriteVALUE2(WORD ver, EPGDB_SEARCH_KEY_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
BOOL ReadVALUE2(WORD ver, EPGDB_SEARCH_KEY_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

DWORD GetVALUESize2(WORD ver, EPG_AUTO_ADD_DATA* val );
BOOL WriteVALUE2(WORD ver, EPG_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
BOOL ReadVALUE2(WORD ver, EPG_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

inline DWORD GetVALUESize2(WORD ver, vector<EPG_AUTO_ADD_DATA>* val ){ CCUTIL2_VECTOR_GET_SIZE_PTR_; }
inline BOOL WriteVALUE2(WORD ver, vector<EPG_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_VECTOR_WRITE_PTR_; }
inline BOOL ReadVALUE2(WORD ver, vector<EPG_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_VECTOR_READ_; }

DWORD GetVALUESize2(WORD ver, MANUAL_AUTO_ADD_DATA* val );
BOOL WriteVALUE2(WORD ver, MANUAL_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
BOOL ReadVALUE2(WORD ver, MANUAL_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

inline DWORD GetVALUESize2(WORD ver, vector<MANUAL_AUTO_ADD_DATA>* val ){ CCUTIL2_VECTOR_GET_SIZE_PTR_; }
inline BOOL WriteVALUE2(WORD ver, vector<MANUAL_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_VECTOR_WRITE_PTR_; }
inline BOOL ReadVALUE2(WORD ver, vector<MANUAL_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_VECTOR_READ_; }

DWORD GetVALUESize2(WORD ver, REC_FILE_INFO* val );
BOOL WriteVALUE2(WORD ver, REC_FILE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize );
BOOL ReadVALUE2(WORD ver, REC_FILE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize );

inline DWORD GetVALUESize2(WORD ver, vector<REC_FILE_INFO>* val ){ CCUTIL2_VECTOR_GET_SIZE_PTR_; }
inline BOOL WriteVALUE2(WORD ver, vector<REC_FILE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize ){ CCUTIL2_VECTOR_WRITE_PTR_; }
inline BOOL ReadVALUE2(WORD ver, vector<REC_FILE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* readSize ){ CCUTIL2_VECTOR_READ_; }

////////////////////////////////////////////////////////////////////////////////////////////
//テンプレート定義

template<class T>
DWORD CCUTIL2_GetVectorVALUESize2_( WORD ver, vector<T>* val )
{
	DWORD size = sizeof(DWORD) * 2;
	if( val != NULL ){
		for( size_t i=0; i < val->size(); i++ ){
			size += GetVALUESize2(ver, (*val)[i]);
		}
	}
	return size;
}

template<class T>
DWORD CCUTIL2_GetPtrVectorVALUESize2_( WORD ver, vector<T>* val )
{
	DWORD size = sizeof(DWORD) * 2;
	if( val != NULL ){
		for( size_t i=0; i < val->size(); i++ ){
			size += GetVALUESize2(ver, &(*val)[i]);
		}
	}
	return size;
}

template<class T>
BOOL CCUTIL2_WriteVectorVALUE2_( WORD ver, vector<T>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD pos = sizeof(DWORD) * 2;
	DWORD count = 0;
	if( val == NULL || buff == NULL || buffSize < pos ){
		return FALSE;
	}
	//リストの中身
	DWORD size = 0;
	for( ; count < (DWORD)val->size(); count++ ){
		if( WriteVALUE2(ver, (*val)[count], buff + pos, buffSize - pos, &size) == FALSE ){
			return FALSE;
		}
		pos += size;
	}
	//全体のサイズ
	WriteVALUE(pos, buff, sizeof(pos), NULL);
	//リストの個数
	WriteVALUE(count, buff + sizeof(pos), sizeof(count), NULL);

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

template<class T>
BOOL CCUTIL2_WritePtrVectorVALUE2_( WORD ver, vector<T>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD pos = sizeof(DWORD) * 2;
	DWORD count = 0;
	if( val == NULL || buff == NULL || buffSize < pos ){
		return FALSE;
	}
	//リストの中身
	DWORD size = 0;
	for( ; count < (DWORD)val->size(); count++ ){
		if( WriteVALUE2(ver, &(*val)[count], buff + pos, buffSize - pos, &size) == FALSE ){
			return FALSE;
		}
		pos += size;
	}
	//全体のサイズ
	WriteVALUE(pos, buff, sizeof(pos), NULL);
	//リストの個数
	WriteVALUE(count, buff + sizeof(pos), sizeof(count), NULL);

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

template<class T>
BOOL CCUTIL2_ReadVectorVALUE2_( WORD ver, vector<T>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	ReadVALUE(&valSize, buff + pos, buffSize - pos, &size);
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	ReadVALUE(&valCount, buff + pos, buffSize - pos, &size);
	pos += size;

	for( DWORD i=0; i < valCount; i++ ){
		T data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back(data);
	}
	if( readSize != NULL ){
		*readSize = pos;
	}
	return TRUE;
}

template<class T>
BOOL CCUTIL2_ReadAndNewVectorVALUE2_( WORD ver, vector<T*>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	ReadVALUE(&valSize, buff + pos, buffSize - pos, &size);
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	ReadVALUE(&valCount, buff + pos, buffSize - pos, &size);
	pos += size;

	for( DWORD i=0; i < valCount; i++ ){
		T* data = new T;
		if( ReadVALUE2(ver, data, buff + pos, buffSize - pos, &size) == FALSE ){
			delete data;
			return FALSE;
		}
		pos += size;
		val->push_back(data);
	}
	if( readSize != NULL ){
		*readSize = pos;
	}
	return TRUE;
}

#endif
