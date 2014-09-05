#pragma once

/*
5.2.3 �v���O�����}�b�v�e�[�u���iPMT�j�iProgram Map Table�j
PMT �́A�����ԑg���\������e�������M����`������TS �p�P�b�g�̃p�P�b�g���ʎq��
�w�肷��B
�ڍׂ�ISO/IEC 13818-1(21)��2.4.4 ���Œ�`����B

TS_program_map_section(){
	table_id						8 uimsbf
	section_syntax_indicator		1 bslbf
	�e0�f							1 bslbf
	reserved						2 bslbf
	section_length					12 uimsbf
	program_number					16 uimsbf
	reserved						2 bslbf
	version_number					5 uimsbf
	current_next_indicator			1 bslbf
	section_number					8 uimsbf
	last_section_number				8 uimsbf
	reserved						3 bslbf
	PCR_PID							13 uimsbf
	reserved						4 bslbf
	program_info_length				12 uimsbf
	for (i=0;i<N;i++){
		descriptor()
	}
	for (i=0;i<N1;i++){
		stream_type						8 uimsbf
		reserved						3 bslbf
		elementary_PID					13 uimsnf
		reserved						4 bslbf
		ES_info_length					12 uimsbf
		for (i=0;i<N2;i++){
			descriptor()
		}
	}
	CRC_32 32 rpchof
}
*/

#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CPMTTable : public CPSITable
{
public:
	typedef struct _ES_INFO_DATA{
		BYTE stream_type;
		WORD elementary_PID;
		WORD ES_info_length;
		vector<AribDescriptor::CDescriptor*> descriptorList;
		~_ES_INFO_DATA(void){
			for( size_t i=0; i<descriptorList.size(); i++ ){
				SAFE_DELETE(descriptorList[i]);
			}
			descriptorList.clear();
		};
	} ES_INFO_DATA;
	WORD program_number;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD PCR_PID;
	WORD program_info_length;
	vector<AribDescriptor::CDescriptor*> descriptorList;
	vector<ES_INFO_DATA*> ESInfoList;

public:
	CPMTTable(void);
	~CPMTTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();
};
