#pragma once

/*
5.2.9 �������t�I�t�Z�b�g�e�[�u���iTOT�j�iTime Offset Table�j
TOT�i�\5�|9 �Q�Ɓj�́AJST �����Ɠ��t�i�C�������E�X���j���A����уT�}�[�^�C
�����{���̎��ԃI�t�Z�b�g�l��`������BTOT �͕\5�|9 �̃f�[�^�\�����g�p�����P��Z
�N�V��������\�������B����TOT �Z�N�V�����́APID �l0x0014 �̃g�����X�|�[�g�X�g
���[���p�P�b�g�ɂ��`������A�܂��A�e�[�u�����ʒl��0x73 �Ƃ���B

time_offset_section(){
	table_id					8 uimsbf
	section_syntax_indicator	1 bslbf
	reserved_future_use			1 bslbf
	reserved					2 bslbf
	section_length				12 uimsbf
	JST_time					40 bslbf
	reserved					4 bslbf
	descriptors_loop_length		12 uimsbf
	for (i=0;i<N;i++){
		descriptor()
	}
	CRC_32						32 rpchof
}

table_id�i�e�[�u�����ʁj�F�\5�|2 �ɂ��B
section_syntax_indicator�i�Z�N�V�����V���^�N�X�w���j�F����͂P�r�b�g�̎w���Łu0�v
�ɐݒ肷��B
section_length�i�Z�N�V�������j�F�����12 �r�b�g�̃t�B�[���h�ŁA�擪��2 �r�b�g��
��Ɂu00�v�Ƃ���B����́A�Z�N�V�������t�B�[���h�̒��ォ��CRC ���܂ރZ�N�V����
�̍Ō�܂ł̃Z�N�V�����̃o�C�g�����K�肷��B
JST_time�i���ݓ��t�A���ݎ����j�F����40 �r�b�g�̃t�B�[���h�́A���{�W�����iJST�j
�ƏC�������E�X���iMJD�j�i�t�^C �Q�Ɓj�ɂ�錻�ݓ��t�ƌ��ݎ������܂ށB���̃t�B�[
���h�́AMJD �̉���16 �r�b�g��16 �r�b�g�ŕ��������A����24 �r�b�g��6 ��4 �r�b�g
2 �i��10 �i���iBCD�j�ŕ���������B
descriptors_loop_length�i�L�q�q���[�v���j�F����́A12 �r�b�g�̃t�B�[���h�ŁA��
���̋L�q�q�̑S�o�C�g�����K�肷��B
CRC_32�iCRC�j�F����͕t�^B �Œ�`����f�R�[�_�ɂ����āA�Z�N�V�����S�̂�����
������Ƀ��W�X�^�o�͂��[���ɂȂ�悤��CRC�l���܂ށA32 �r�b�g�̃t�B�[���h�ł���B


*/

#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CTOTTable : public CPSITable
{
public:
	SYSTEMTIME jst_time;
	WORD descriptors_loop_length;
	vector<AribDescriptor::CDescriptor*> descriptorList;
public:
	CTOTTable(void);
	~CTOTTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();
};
