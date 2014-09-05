#pragma once

/*
5.2.6 �T�[�r�X�L�q�e�[�u���iSDT�j�iService Description Table�j
SDT�i�\5�|5 �Q�Ɓj�̊e�T�u�e�[�u���́A����̃g�����X�|�[�g�X�g���[���Ɋ܂܂��
�T�[�r�X��\���B�T�[�r�X�͎��g�����X�|�[�g�X�g���[���̈ꕔ�ł��邩�A���g�����X�|
�[�g�X�g���[���̈ꕔ�ł��邩�̂����ꂩ�ł���A�����́A�e�[�u�����ʁi�\5�|2 �Q�Ɓj
�Ŏ��ʂ����B
SDT �͕\5�|5 �̃f�[�^�\�����g�p���āA�T�[�r�X�L�q�Z�N�V�����ɕ��������BSDT
�̈ꕔ���ƂȂ�Z�N�V�����͑S�āAPID �l0x0011 �̃g�����X�|�[�g�X�g���[���p�P�b�g
�ɂ��`�������B���g�����X�|�[�g�X�g���[���i�܂肻��SDT ���܂ރg�����X�|�[�g
�X�g���[���j�̓��e���L�q����SDT �̃Z�N�V�����͑S�ăe�[�u�����ʒl��0x42 �Ƃ��A��
���A���g�����X�|�[�g�X�g���[���ȊO�̃g�����X�|�[�g�X�g���[����SDT �Z�N�V�����̃e
�[�u�����ʒl��0x46 �Ƃ���B

service description section(){
	table_id						8 uimsbf
	section_syntax_indicator		1 bslbf
	reserved_future_use				1 bslbf
	reserved						2 bslbf
	section_length					12 uimsbf
	transport_stream_id				16 uimsbf
	reserved						2 bslbf
	version_number					5 uimsbf
	current_next_indicator			1 bslbf
	section_number					8 uimsbf
	last_section_number				8 uimsbf
	original_network_id				16 uimsbf
	reserved_future_use				8 bslbf
	for (i=0;i<N;i++){
		service_id						16 uimsbf
		reserved_future_use				3 bslbf
		EIT_user_defined_flags			3 bslbf
		EIT_schedule_flag				1 bslbf
		EIT_present_following_flag		1 bslbf
		running_status					3 uimsbf
		free_CA_mode					1 bslbf
		descriptors_loop_length			12 uimsbf
		for (j=0;j<N;j++){
			descriptor()
		}
	}
	CRC_32							32 rpchof
}

table_id�i�e�[�u�����ʁj�F�\5�|2 �ɂ��B
section_syntax_indicator�i�Z�N�V�����V���^�N�X�w���j�F�Z�N�V�����V���^�N�X�w����1
�r�b�g�̃t�B�[���h�ŁA���1 �Ƃ���B
section_length�i�Z�N�V�������j�F�����12 �r�b�g�̃t�B�[���h�ŁA�擪��2 �r�b�g�͏�
�Ɂu00�v�Ƃ���B����́A�Z�N�V�������t�B�[���h�̒��ォ��CRC ���܂ރZ�N�V������
�Ō�܂ł̃Z�N�V�����̃o�C�g�����K�肷��B�S�Z�N�V�����̒�����1024 �o�C�g�𒴂���
���悤�ɂ��邽�߁A�Z�N�V��������1021 �𒴂��Ă͂Ȃ�Ȃ��B
transport_stream_id�i�g�����X�|�[�g�X�g���[�����ʁj�F�����16 �r�b�g�̃t�B�[���h
�ŁASDT �������g�����X�|�[�g�X�g���[�������̕��z�V�X�e�����̑��̑��d���环�ʂ���
���x���̖���������B
version_number�i�o�[�W�����ԍ��j�F����5 �r�b�g�̃t�B�[���h�̓T�u�e�[�u���̃o�[�W
�����ԍ��ł���B�o�[�W�����ԍ��̓T�u�e�[�u�����̏��ɕω����������ꍇ��1 ���Z��
���B���̒l��31 �ɂȂ����ꍇ�́A���̎���0 �ɖ߂�B�J�����g�l�N�X�g�w�����u1�v��
�ꍇ�́A�o�[�W�����ԍ��̓e�[�u�����ʂƃl�b�g���[�N���ʂŒ�`����錻�݂̃T�u�e�[
�u���̃o�[�W�����ԍ��ɂȂ�B�J�����g�l�N�X�g�w�����u0�v�̏ꍇ�́A�o�[�W�����ԍ���
�e�[�u�����ʂƃl�b�g���[�N���ʂŒ�`����鎟�̃T�u�e�[�u���̃o�[�W�����ԍ��ɂȂ�B
current_next_indicator�i�J�����g�l�N�X�g�w���j�F����1 �r�b�g�̎w���́A���ꂪ�u1�v
�̏ꍇ�̓T�u�e�[�u�������݂̃T�u�e�[�u���ł��邱�Ƃ������B�u0�v�̏ꍇ�́A������
�T�u�e�[�u���͂܂��K�p���ꂸ�A���̃T�u�e�[�u���Ƃ��Ďg�p����邱�Ƃ������B
section_number�i�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�̓Z�N�V�����̔ԍ���\
���B�T�u�e�[�u�����̍ŏ��̃Z�N�V�����̃Z�N�V�����ԍ��́A0x00 �ł���B�Z�N�V������
���́A����̃e�[�u�����ʁA�g�����X�|�[�g�X�g���[�����ʁA�I���W�i���l�b�g���[�N��
�ʂ����Z�N�V�����̒ǉ����Ƃ�1 ���Z�����B
last_section_number�i�ŏI�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�́A���̃Z�N�V
������������T�u�e�[�u���̍Ō�̃Z�N�V�����i���Ȃ킿�A�ő�̃Z�N�V�����ԍ�������
�Z�N�V�����j�̔ԍ����K�肷��B
original_network_id�i�I���W�i���l�b�g���[�N���ʁj�F����16 �r�b�g�̃t�B�[���h�́A
���̕��z�V�X�e���̃l�b�g���[�N���ʂ��K�肷�郉�x���̖���������B
service_id�i�T�[�r�X���ʁj�F�����16 �r�b�g�̃t�B�[���h�ŁA���̃g�����X�|�[�g�X�g
���[�����̑��̃T�[�r�X���炱�̃T�[�r�X�����ʂ��邽�߂̃��x���̖���������B�T�[�r
�X���ʂ́A�Ή�����v���O�����}�b�v�Z�N�V�������̕����ԑg�ԍ�����
�iprogram_number�j�ɓ������B
EIT_user_defined_flags�iEIT ���ƎҒ�`�t���O�j�F���̂R�r�b�g�̃t�B�[���h�́AEIT
�̑��o�L���������g���Ƃ��āA�������Ǝ҂��Ǝ��ɒ�`���邱�Ƃ��ł���B�g�p���Ȃ���
���́A�f111�f�Ƃ���B
EIT_schedule_flag�iEIT�m�X�P�W���[���n�t���O�j�F����1 �r�b�g�̃t�B�[���h�́A����
���u1�v�̏ꍇ�͂��̃T�[�r�X��EIT�m�X�P�W���[���n��񂪌��݂̃g�����X�|�[�g�X�g��
�[�����ɂ��邱�Ƃ������B�iEIT�m�X�P�W���[���n�T�u�e�[�u���̍ő呗�o�Ԋu�ɂ���
�́u�K�C�h���C���v���Q�ƁB�j���̃t���O���u0�v�̏ꍇ�́A���̃T�[�r�X��EIT�m�X�P�W
���[���n��񂪌��݂̃g�����X�|�[�g�X�g���[�����ɂ͑��݂��Ȃ����Ƃ�\���B
EIT_present_following_flag�iEIT�m���݁^���n�t���O�j�F����1 �r�b�g�̃t�B�[���h�́A
���ꂪ�u1�v�̏ꍇ�͂��̃T�[�r�X��EIT�m���݁^���n��񂪌��݂̃g�����X�|�[�g�X�g��
�[�����ɂ��邱�Ƃ������B�iEIT�m���݁^���n�T�u�e�[�u���̍ő呗�o�Ԋu�ɂ��Ắu�K
�C�h���C���v���Q�ƁB�j���̃t���O���u0�v�̏ꍇ�́A���̃T�[�r�X��EIT�m���݁^���n��
�񂪌��݂̃g�����X�|�[�g�X�g���[�����ɂ͑��݂��Ȃ����Ƃ�\���B
running_status�i�i�s��ԁj�F����3 �r�b�g�t�B�[���h�́A�\5�|6 �ɒ�`�����T�[�r
�X�̏�Ԃ������B
free_CA_mode�i�X�N�����u���j�F����1 �r�b�g�̃t�B�[���h�́A���ꂪ�u0�v�̏ꍇ�͂�
�̃T�[�r�X���̑S�ẴR���|�[�l���g�X�g���[�����X�N�����u������Ă��Ȃ����Ƃ������B
�u1�v�̏ꍇ�́A��ȏ�̃X�g���[���ւ̃A�N�Z�X��CA �V�X�e���ɂ�萧�䂳��Ă���
���Ƃ������B
descriptors_loop_length�i�L�q�q���[�v���j�F����́A12 �r�b�g�̃t�B�[���h�ŁA�㑱��
�L�q�q�̑S�o�C�g�����K�肷��B
CRC_32�iCRC�j�F����͕t�^B �Œ�`����f�R�[�_�ɂ����āA�Z�N�V�����S�̂�������
����Ƀ��W�X�^�o�͂��[���ɂȂ�悤��CRC �l���܂ށA32 �r�b�g�̃t�B�[���h�ł���B

*/

#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CSDTTable : public CPSITable
{
public:
	typedef struct _SERVICE_INFO_DATA{
		WORD service_id;
		BYTE EIT_user_defined_flags;
		BYTE EIT_schedule_flag;
		BYTE EIT_present_following_flag;
		BYTE running_status;
		BYTE free_CA_mode;
		WORD descriptors_loop_length;
		vector<AribDescriptor::CDescriptor*> descriptorList;
		~_SERVICE_INFO_DATA(void){
			for( size_t i=0; i<descriptorList.size(); i++ ){
				SAFE_DELETE(descriptorList[i]);
			}
			descriptorList.clear();
		};
	} SERVICE_INFO_DATA;
	WORD transport_stream_id;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD original_network_id;
	vector<SERVICE_INFO_DATA*> serviceInfoList;

public:
	CSDTTable(void);
	~CSDTTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();

	BOOL SDDecode( BYTE* data, DWORD dataSize, vector<AribDescriptor::CDescriptor*>* descriptorList, DWORD* decodeReadSize );
};
