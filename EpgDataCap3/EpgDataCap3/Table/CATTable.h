#pragma once

/*
5.2.2 �����M�e�[�u���iCAT�j�iConditional Access Table�j
CAT �́A�L�������̊֘A����`������TS �p�P�b�g�̃p�P�b�g���ʎq���w�肷��B
�ڍׂ�ISO/IEC 13818-1(21)��2.4.4 ���Œ�`����B

CA_section(){
	table_id					8 uimsbf
	section_syntax_indicator	1 bslbf
	�e0�f						1 bslbf
	reserved					2 bslbf
	section_length				12 uimsbf
	reserved					18 bslbf
	version_number				5 uimsbf
	current_next_indicator		1 bslbf
	section_number				8 uimsbf
	last_section_number			8 uimsbf
	for (i=0;i<N;i++){
		descriptor()
	}
	CRC_32						32 rpchof
}
*/

#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CCATTable : public CPSITable
{
public:
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	vector<AribDescriptor::CDescriptor*> descriptorList;

public:
	CCATTable(void);
	~CCATTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();
};
