#pragma once

/*
5.2.1 �v���O�����A�\�V�G�[�V�����e�[�u���iPAT�j�iProgram Association Table�j
PAT �́A�����ԑg�Ɋ֘A����PMT ��`������TS �p�P�b�g�̃p�P�b�g���ʎq���w�肷��B
�ڍׂ�ISO/IEC 13818-1(21)��2.4.4 ���Œ�`����B

program_association_section(){
	table_id					8 uimsbf
	section_syntax_indicator	1 bslbf
	�e0�f						1 bslbf
	reserved					2 bslbf
	section_length				12 uimsbf
	transport_stream_id			16 uimsbf
	reserved					2 bslbf
	version_number				5 uimsbf
	current_next_indicator		1 bslbf
	section_number				8 uimsbf
	last_section_number			8 uimsbf
	for(i=0;i<N;i++){
		program_number				16 uimsbf
		reserved					3 bslbf
		if (program_number = = �e0�f){
			network_PID					13 uimsbf
		}else{
			program_map_PID				13 uimsbf
		}
	}
	CRC_32						32 rpchof
}
*/

#include "../../../Common/Util.h"
#include "PSITable.h"

class CPATTable : public CPSITable
{
public:
	typedef struct _PMT_DATA{
		WORD program_number;
		WORD PID;
	} PMT_DATA;
	WORD transport_stream_id;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	map<WORD, PMT_DATA> pmtMap;	//�L�[program_number(ServiceID)

public:
	CPATTable(void);
	~CPATTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
