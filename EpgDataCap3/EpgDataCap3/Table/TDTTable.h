#pragma once

/*
5.2.8 �������t�e�[�u���iTDT�j�iTime and Date Table�j
TDT�i�\5�|8 �Q�Ɓj�́AJST �����Ɠ��t���݂̂�`������B
TDT �͕\5�|8 �̃f�[�^�\�����g�p�����P��Z�N�V��������\�������B����TDT �Z�N
�V�����́APID �l0x0014 �̃g�����X�|�[�g�X�g���[���p�P�b�g�ɂ��`������A�܂��A
�e�[�u�����ʒl��0x70 �Ƃ���B

time_date_section(){
	table_id					8 uimsbf
	section_syntax_indicator	1 bslbf
	reserved_future_use			1 bslbf
	reserved					2 bslbf
	section_length				12 uimsbf
	JST_time					40 bslbf
}

table_id�i�e�[�u�����ʁj�F�\5�|2 �ɂ��B
section_syntax_indicator�i�Z�N�V�����V���^�N�X�w���j�F�����1 �r�b�g�̎w���Łu0�v
�ɐݒ肷��B
section_length�i�Z�N�V�������j�F�����12 �r�b�g�̃t�B�[���h�ŁA���̒l�͏�Ɂu0x005�v
�Ƃ���B����́A�Z�N�V�������t�B�[���h�̒��ォ��Z�N�V�����̍Ō�܂ł̃Z�N�V����
�̃o�C�g�����K�肷��B
JST_time�i���ݓ��t�A���ݎ����j�F����40 �r�b�g�̃t�B�[���h�́A���{�W�����iJST�j
�ƏC�������E�X���iMJD�j�i�t�^C �Q�Ɓj�ɂ�錻�ݓ��t�ƌ��ݎ������܂ށB���̃t�B�[
���h�́AMJD �̉���16 �r�b�g��16 �r�b�g�ŕ��������A����24 �r�b�g��6 ��4 �r�b�g
2 �i��10 �i���iBCD�j�ŕ���������B
��F93/10/13 12:45:00 ��0xC079124500 �ƕ����������B
�m���nMJD �̃t�B�[���h��16 �r�b�g�̂��߁A���ݓ��t��2038 �N4 ��22 ���܂ŕ\���\�B

*/

#include "../../../Common/Util.h"
#include "PSITable.h"

class CTDTTable : public CPSITable
{
public:
	SYSTEMTIME jst_time;
public:
	CTDTTable(void);
	~CTDTTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
