#pragma once

/*
12.2.2.2 �_�E�����[�h�R���e���c�E�Z�N�V�����`������
�_�E�����[�h�R���e���c���Z�N�V�����`���œ`������ꍇ��CDT�iCommon Data Table�j��p
����B
(1) �S��M�@���ʃf�[�^�e�[�u���iCDT�j�iCommon Data Table�j
CDT �́A���̃e�[�u������M����S�Ă̎�M�@��ΏۂƂ��āA�s�������������Ɋi�[���ׂ�����
�f�[�^���Z�N�V�����`���œ`�����邽�߂ɗp����B�n��f�W�^���e���r�W���������ł́A���Ǝ҂�
�T�[�r�X���S�f�[�^��CDT ����data_module_byte �Ƀ��S�f�[�^��z�u���ē`������B���S�f�[
�^�t�H�[�}�b�g�́u�t��(�_�E�����[�h�@�\)�v��Appendix.A ���Q�Ƃ̂��ƁB
CDT �ɂ��ẮAARIB STD-B10 ���Q�Ƃ̂��ƁB
CDT �̃f�[�^�\����\12-6 �Ɏ����B

common_data_section(){
	table_id					8 uimsbf
	section_syntax_indicator	1 bslbf
	reserved_future_use			1 bslbf
	reserved					2 bslbf
	section_length				12 uimsbf
	download_data_id			16 uimsbf
	reserved					2 bslbf
	version_number				5 uimsbf
	current_next_indicator		1 bslbf
	section_number				8 uimsbf
	last_section_number			8 uimsbf
	original_network_id			16 uimsbf
	data_type					8 uimsbf
	reserved_future_use			4 bslbf
	descriptors_loop_length		12 uimsbf
	for(i=0;i<n;i++){
		descriptor()
	}
	for(j=0;j<m;j++){
		data_module_byte			8 uimsbf
	}
	CRC_32						32 rpchof
}

table_id�i�e�[�u�����ʁj�F0xC8
section_syntax_indicator�i�Z�N�V�����V���^�N�X�w���j�F�Z�N�V�����V���^�N�X�w����1 �r�b�g��
�t�B�[���h�ŁA���1 �Ƃ���B
section_length�i�Z�N�V�������j�F�����12 �r�b�g�̃t�B�[���h�ł���B����́A�Z�N�V�������t
�B�[���h�̒��ォ��CRC ���܂ރZ�N�V�����̍Ō�܂ł̃Z�N�V�����̃o�C�g�����K�肷��B�S�Z
�N�V�����̒�����4096 �o�C�g�𒴂��Ȃ��悤�ɂ��邽�߁A�Z�N�V��������4093 �𒴂��Ă͂Ȃ��
���B
download_data_id�i�_�E�����[�h�f�[�^���ʁj�F �����16 �r�b�g�̃t�B�[���h�ŁA�S��M�@��
�ʃf�[�^�̃_�E�����[�h�f�[�^���ʂ��w�肷��B�_�E�����[�h�f�[�^���ʂ́A�I���W�i���l�b�g��
�[�N���ʁioriginal_network_id�j���Ƀ��j�[�N�Ƃ���B�T�[�r�X���S�̏ꍇ�́A���̒l��SDT ��
�z�u������q�̃��S�`���L�q�q�ɋL�ڂ�download_data_id �̒l�ƈ�v����B
version_number�i�o�[�W�����ԍ��j�F����5 �r�b�g�̃t�B�[���h�̓T�u�e�[�u���̃o�[�W�����ԍ�
�ł���B�o�[�W�����ԍ��̓T�u�e�[�u�����̏��ɕω����������ꍇ��1 ���Z�����B���̒l��31
�ɂȂ����ꍇ�́A���̎���0 �ɖ߂�B�J�����g�l�N�X�g�w�����u1�v�̏ꍇ�́A�o�[�W�����ԍ���
�e�[�u�����ʂƃl�b�g���[�N���ʂŒ�`����錻�݂̃T�u�e�[�u���̃o�[�W�����ԍ��ɂȂ�B�J��
���g�l�N�X�g�w�����u0�v�̏ꍇ�́A�o�[�W�����ԍ��̓e�[�u�����ʂƃl�b�g���[�N���ʂŒ�`��
��鎟�̃T�u�e�[�u���̃o�[�W�����ԍ��ɂȂ�B
current_next_indicator�i�J�����g�l�N�X�g�w���j�F����1 �r�b�g�̎w���́A���ꂪ�u1�v�̏ꍇ��
�T�u�e�[�u�������݂̃T�u�e�[�u���ł��邱�Ƃ������B�u0�v�̏ꍇ�́A������T�u�e�[�u���͂�
���K�p���ꂸ�A���̃T�u�e�[�u���Ƃ��Ďg�p����邱�Ƃ������B
section_number�i�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�̓Z�N�V�����̔ԍ���\���B�T�u
�e�[�u�����̍ŏ��̃Z�N�V�����̃Z�N�V�����ԍ��́A0x00 �ł���B�Z�N�V�����ԍ��́A����̃e�[
�u�����ʂƃl�b�g���[�N���ʂ����Z�N�V�����̒ǉ����Ƃ�1 ���Z�����B
last_section_number�i�ŏI�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�́A���̃Z�N�V��������
����T�u�e�[�u���̍Ō�̃Z�N�V�����i���Ȃ킿�A�ő�̃Z�N�V�����ԍ������Z�N�V�����j�̔�
�����K�肷��B
original_network_id�i�I���W�i���l�b�g���[�N���ʁj�F����16 �r�b�g�̃t�B�[���h�́A���̕��z�V
�X�e���̃l�b�g���[�N���ʂ��K�肷�郉�x���̖���������B
data_type�i�f�[�^�����j�F����8 �r�b�g�̃t�B�[���h�́A�`������Ă���_�E�����[�h�f�[�^�̎�
�ނ������B0x01 �̓��S�f�[�^�Ƃ��A�^�p�ڍׂ͖{���t��-3�u�_�E�����[�h�@�\�v�A�y�ѕ������Ǝ�
�K�����Q�Ƃ̂��ƁB����ȊO�͏����g���Ƃ���B
descriptors_length�i�L�q�q���j�F����́A12 �r�b�g�̃t�B�[���h�ŁA�㑱�̋L�q�q�̑S�o�C�g����
�K�肷��B
data_module_byte�i�f�[�^���W���[���o�C�g�j�Fdata_type ���ɒ�`�����V���^�b�N�X�ɂ��_
�E�����[�h�f�[�^���L�ڂ���B�T�[�r�X���S�̏ꍇ�͖{���t��-3�u�_�E�����[�h�@�\�v�A�y�ѕ�����
�ƎҋK�����Q�Ƃ̂��ƁB
CRC_32�iCRC�j�F�����ARIB STD-B10 �̕t�^B �Œ�`����f�R�[�_�ɂ����āA�Z�N�V�����S��
������������Ƀ��W�X�^�o�͂��[���ɂȂ�悤��CRC �l���܂ށA32 �r�b�g�̃t�B�[���h�ł���B


*/

#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CCDTTable : public CPSITable
{
public:
	WORD download_data_id;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD original_network_id;
	BYTE data_type;
	WORD descriptors_loop_length;
	vector<AribDescriptor::CDescriptor*> descriptorList;
	WORD data_module_byteSize;
	BYTE* data_module_byte;

public:
	CCDTTable(void);
	~CCDTTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
