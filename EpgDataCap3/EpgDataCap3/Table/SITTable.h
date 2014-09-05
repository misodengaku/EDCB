#pragma once

/*
8.2.8.2.2.2 �I�����e�[�u��(SIT)
SIT �̓p�[�V�����g�����X�|�[�g�X�g���[���œ`�������T�[�r�X�ƃC�x���g��\���B
SIT �͕\8-2-9 �̃f�[�^�\�����g�p���đI�����Z�N�V�����ɕ��������BSIT �̈ꕔ
���ƂȂ�Z�N�V�����͂��ׂāAPID �l0x001F �̃g�����X�|�[�g�p�P�b�g�ɂ��`������A
�܂��A�e�[�u�����ʒl��0x7F �Ƃ���B

selection_information_section(){
	table_id					8 uimsbf
	section_syntax_indicator	1 bslbf
	reserved_future_use			1 bslbf
	ISO_reserved				2 bslbf
	section_length				12 uimsbf
	reserved_future_use			16 bslbf
	ISO_reserved				2 bslbf
	version_number				5 uimsbf
	current_next_indicator		1 bslbf
	section_number				8 uimsbf
	last_section_number			8 uimsbf
	reserved_future_use			4 uimsbf
	transmission_info_loop_length	12 uimsbf
	for(i=0;i<N;i++){
		descriptor()
	}
	for(i=0;i<N;i++){
		service_id					16 uimsbf
		reserved_future_use			1 uimsbf
		running_status				3 bslbf
		service_loop_length			12 uimsbf
		for(j=0;j<N;j++){
			descriptor()
		}
	}
	CRC_32 32 rpchof
}

table_id (�e�[�u������)�F�\8-2-7 �ɂ��B
section_syntax_indicator (�Z�N�V�����V���^�N�X�w��)�F�Z�N�V�����V���^�N�X�w����1
�r�b�g�̃t�B�[���h�ŁA���"1"�Ƃ���B
section_length (�Z�N�V������)�F�����12 �r�b�g�t�B�[���h�Ƃ���Bsection_length ��
���̃t�B�[���h�̒��ォ��CRC ���܂ރZ�N�V�����̍Ō�܂ł̃Z�N�V�����̃o�C�g����
�K�肷��B�S�Z�N�V���������ő�4096 �o�C�g���z���Ȃ����߂ɁA�Z�N�V��������4093
�o�C�g���z���Ă͂Ȃ�Ȃ��B
version_number (�o�[�W�����ԍ�)�F����5 �r�b�g�t�B�[���h�̓e�[�u���̃o�[�W������
���ł���B�o�[�W�����ԍ��̓e�[�u�����̏��ɕω����������ꍇ�ɂP���Z�����B����
�l��31 �ɂȂ����ꍇ�́A0 �ɖ߂�B�J�����g�l�N�X�g�w����"1"�̏ꍇ�́A�o�[�W������
���͌��݂̃e�[�u���̃o�[�W�����ԍ��ɂȂ�B�J�����g�l�N�X�g�w����"0"�̏ꍇ�́A�o�[
�W�����ԍ��͎��̃e�[�u���̃o�[�W�����ԍ��ɂȂ�B
current_next_indicator (�J�����g�l�N�X�g�w��)�F����1 �r�b�g�̎w����"1"�̏ꍇ�A�e
�[�u�������݂̃e�[�u���ł��邱�Ƃ������A"0"�̏ꍇ�́A������e�[�u���͂܂��K����
�ꂸ�A���̃e�[�u���Ƃ��Ďg�p����邱�Ƃ������B
section_number (�Z�N�V�����ԍ�)�F����8 �r�b�g�t�B�[���h�̓Z�N�V�����̔ԍ��������B
�Z�N�V�����ԍ��́A0x00 �ł���B
last_section_number (�ŏI�Z�N�V�����ԍ�)�F����8 �r�b�g�t�B�[���h�͍ŏI�̃Z�N�V��
���ԍ��������B�ŏI�Z�N�V�����ԍ��́A0x00 �ł���B
transmission_info_loop_length (�`����񃋁[�v��)�F����12 �r�b�g�t�B�[���h�̓p�[
�V�����g�����X�|�[�g�X�g���[���̓`���p�����[�^���L�q����f�X�N���v�^�̑S�o�C�g��
��\�킷�B
service_id (�T�[�r�X����)�F�����16 �r�b�g�t�B�[���h�ŁA�g�����X�|�[�g�X�g���[��
���̑��̃T�[�r�X���炱�̃T�[�r�X�����ʂ��邽�߂̃��x���̖���������B�T�[�r�X����
�̓v���O�����}�b�v�Z�N�V�������̕����ԑg�ԍ����� (program_number)�ɓ������B
running_status (�i�s���)�F����3 �r�b�g�t�B�[���h�͌��̃X�g���[���̃C�x���g�̐i
�s��Ԃ�\���B����́A���̌��݂̃C�x���g�̐i�s��Ԃł���B�������̃X�g���[���Ɍ�
�݂̃C�x���g�����݂��Ȃ���΁A��Ԃ͔���s���ƍl������B���s��Ԃ̒l�̈Ӗ���
ARIB STD-B10 �ɒ�`����Ă���B
service_loop_length (�T�[�r�X���[�v��)�F����12 �r�b�g�t�B�[���h�͈ȉ��ɑ����p�[
�V�����g�����X�|�[�g�X�g���[���Ɋ܂܂��T�[�r�X�ƃC�x���g��SI �֘A�����܂ރf
�X�N���v�^���[�v�̑S�o�C�g�����K�肷��B
CRC_32 (CRC)�F�����ARIB STD-B10 �̕t�^B �Œ�`����f�R�[�_�ɂ����āA�Z�N
�V�����S�̂�����������Ƀ��W�X�^�o�͂��[���ɂȂ�悤��CRC �l���܂ށA32 �r�b�g�t
�B�[���h�ł���B

*/

#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CSITTable : public CPSITable
{
public:
	typedef struct _SERVICE_LOOP_DATA{
		WORD service_id;
		BYTE running_status;
		WORD service_loop_length;
		vector<AribDescriptor::CDescriptor*> descriptorList;
		~_SERVICE_LOOP_DATA(void){
			for( size_t i=0; i<descriptorList.size(); i++ ){
				SAFE_DELETE(descriptorList[i]);
			}
			descriptorList.clear();
		};
	} SERVICE_LOOP_DATA;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD transmission_info_loop_length;
	vector<AribDescriptor::CDescriptor*> descriptorList;
	vector<SERVICE_LOOP_DATA*> serviceLoopList;

public:
	CSITTable(void);
	~CSITTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();
};

