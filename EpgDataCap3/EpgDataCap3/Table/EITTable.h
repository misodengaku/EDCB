#pragma once

/*
5.2.7 �C�x���g���e�[�u���iEIT�j�iEvent Information Table�j
EIT�i�\5�|7 �Q�Ɓj�́A�e�T�[�r�X�Ɋ܂܂��C�x���g�Ɋւ��鎞�n����ł���BEIT
��4 �N���X�ɕ������A�e�[�u�����ʁi�\5�|2 �Q�Ɓj�ŋ�ʂ����B
1) ���g�����X�|�[�g�X�g���[���A���݁^���̃C�x���g��񁁃e�[�u�����ʁ��u0x4E�v
2) ���g�����X�|�[�g�X�g���[���A���݁^���̃C�x���g��񁁃e�[�u�����ʁ��u0x4F�v
3) ���g�����X�|�[�g�X�g���[���A�C�x���g�̃X�P�W���[�����
���e�[�u�����ʁ��u0x50�`0x5F�v
4) ���g�����X�|�[�g�X�g���[���A�C�x���g�̃X�P�W���[�����
���e�[�u�����ʁ��u0x60�`0x6F�v
�C�x���g�m���݁^���n�e�[�u���́A���g�����X�|�[�g�X�g���[�����邢�͑��g�����X�|
�[�g�X�g���[����̗^����ꂽ�T�[�r�X�ɂ���ē`�������A���݂̃C�x���g����ю���
�I�ɂ��̎��̃C�x���g�Ɋ֌W���������܂ށB�������A�C�x���g�L�q�q��2 �ȏ㑶�݂�
��ꍇ������NVOD ��T�[�r�X�̏ꍇ�͂��̌���ł͂Ȃ��B�܂��A���̃C�x���g����
�̃C�x���g�̏���C�ӂɊ܂܂��邱�Ƃ��ł���B���g�����X�|�[�g�X�g���[�����邢��
���g�����X�|�[�g�X�g���[���̃C�x���g�m�X�P�W���[���n�e�[�u���́A�X�P�W���[���`��
�ŃC�x���g�̕\�A���Ȃ킿���̃C�x���g����̃C�x���g���܂�ł���BEIT�m�X�P�W��
�[���n�e�[�u���̓`���͔C�ӂł���B�C�x���g���͎��n��ɕ��ׂȂ���΂Ȃ�Ȃ��B
EIT �͕\5�|7 �Ɏ����f�[�^�\���ɂ��A�C�x���g���Z�N�V�����ɕ��������BEIT ��
�ꕔ���ƂȂ�Z�N�V�����͑S�āAPID �l0x0012 �̃g�����X�|�[�g�X�g���[���p�P�b�g��
���`�������B

event_information_section(){
	table_id						8 uimsbf
	section_syntax_indicator		1 bslbf
	reserved_future_use				1 bslbf
	reserved						2 bslbf
	section_length					12
	service_id						16 uimsbf
	reserved						2 bslbf
	version_number					5 uimsbf
	current_next_indicator			1 bslbf
	section_number					8 uimsbf
	last_section_number				8 uimsbf
	transport_stream_id				16 uimsbf
	original_network_id				16 uimsbf
	segment_last_section_number		8 uimsbf
	last_table_id					8 uimsbf
	for(i=0;i<N;i++){
		event_id						16 uimsbf
		start_time						40 bslbf
		duration						24 uimsbf
		running_status					3 uimsbf
		free_CA_mode					1 bslbf
		descriptors_loop_length			12 uimsbf
		for(i=0;i<N;i++){
			descriptor()
		}
	}
	CRC_32							32 rpchof
}

table_id�i�e�[�u�����ʁj�F�\5�|2 �ɂ��B
section_syntax_indicator�i�Z�N�V�����V���^�N�X�w���j�F�Z�N�V�����V���^�N�X�w����1
�r�b�g�̃t�B�[���h�ŁA���1 �Ƃ���B
section_length�i�Z�N�V�������j�F�����12 �r�b�g�̃t�B�[���h�ł���B����́A�Z�N�V
�������t�B�[���h�̒��ォ��CRC ���܂ރZ�N�V�����̍Ō�܂ł̃Z�N�V�����̃o�C�g��
���K�肷��B�S�Z�N�V�����̒�����4096 �o�C�g�𒴂��Ȃ��悤�ɂ��邽�߁A�Z�N�V������
��4093 �𒴂��Ă͂Ȃ�Ȃ��B
service_id�i�T�[�r�X���ʁj�F�����16 �r�b�g�̃t�B�[���h�ŁA���̃g�����X�|�[�g�X�g
���[�����̑��̃T�[�r�X���炱�̃T�[�r�X�����ʂ��邽�߂̃��x���̖���������B�T�[�r
�X���ʂ́A�Ή�����v���O�����}�b�v�Z�N�V�������̕����ԑg�ԍ�����
�iprogram_number�j�ɓ������B
version_number�i�o�[�W�����ԍ��j�F����5 �r�b�g�̃t�B�[���h�̓T�u�e�[�u���̃o�[�W
�����ԍ��ł���B�o�[�W�����ԍ��̓T�u�e�[�u�����̏��ɕω����������ꍇ��1 ���Z��
���B���̒l��31 �ɂȂ����ꍇ�́A���̎���0 �ɖ߂�B�J�����g�l�N�X�g�w�����u1�v��
�ꍇ�́A�o�[�W�����ԍ��̓e�[�u�����ʂƃT�[�r�X���ʂŒ�`����錻�ݗL���ȃT�u�e�[
�u���̃o�[�W�����ԍ��ɂȂ�B�J�����g�l�N�X�g�w�����u0�v�̏ꍇ�́A�o�[�W�����ԍ���
�e�[�u�����ʂƃT�[�r�X���ʂŒ�`����鎟�ɗL���ȃT�u�e�[�u���̃o�[�W�����ԍ��ɂ�
��B
current_next_indicator�i�J�����g�l�N�X�g�w���j�F����1 �r�b�g�̎w���́A���ꂪ�u1�v
�̏ꍇ�̓T�u�e�[�u�������݂̃T�u�e�[�u���ł��邱�Ƃ������B�u0�v�̏ꍇ�́A������
�T�u�e�[�u���͂܂��K�p���ꂸ�A���̃T�u�e�[�u���Ƃ��Ďg�p����邱�Ƃ������B
section_number�i�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�̓Z�N�V�����̔ԍ���\
���B�T�u�e�[�u�����̍ŏ��̃Z�N�V�����̃Z�N�V�����ԍ��́A0x00 �ł���B�Z�N�V������
���́A����̃e�[�u�����ʁA�T�[�r�X���ʁA�g�����X�|�[�g�X�g���[�����ʁA�I���W�i��
�l�b�g���[�N���ʂ����Z�N�V�����̒ǉ����Ƃ�1 ���Z�����B���̏ꍇ�A�T�u�e�[�u��
�͂������̃Z�O�����g�Ƃ��č\�z���Ă��悢�B�e�Z�O�����g���ł́A�Z�N�V�����̒ǉ�
���ƂɃZ�N�V�����ԍ���1 ���Z�����邪�A�Z�O�����g�̍ŏI�Z�N�V�����Ɨאڂ���Z�O��
���g�̍ŏ��̃Z�N�V�����Ƃ̊Ԃł́A�ԍ��̌��Ԃ������Ă��悢�B
last_section_number�i�ŏI�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�́A���̃Z�N�V
������������T�u�e�[�u���̍Ō�̃Z�N�V�����i���Ȃ킿�A�ő�̃Z�N�V�����ԍ�������
�Z�N�V�����j�̔ԍ����K�肷��B
transport_stream_id�i�g�����X�|�[�g�X�g���[�����ʁj�F�����16 �r�b�g�̃t�B�[���h
�ŁAEIT ���������̃g�����X�|�[�g�X�g���[�������̕��z�V�X�e�����̑��̑��d���环��
���郉�x���̖���������B
original_network_id�i�I���W�i���l�b�g���[�N���ʁj�F����16 �r�b�g�̃t�B�[���h�́A
���̕��z�V�X�e���̃l�b�g���[�N���ʂ��K�肷�郉�x���̖���������B
segment_last_section_number�i�Z�O�����g�ŏI�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B
�[���h�́A�T�u�e�[�u���̂��̃Z�O�����g�̍Ō�̃Z�N�V�����̔ԍ����K�肷��B������
��Ȃ��T�u�e�[�u���ł́A���̃t�B�[���h�͍ŏI�Z�N�V�����ԍ��ilast_section_number�j
�t�B�[���h�Ɠ���̒l�ɐݒ肵�Ȃ���΂Ȃ�Ȃ��B
last_table_id�i�ŏI�e�[�u�����ʁj�F����8 �r�b�g�̃t�B�[���h�́A�g�p����Ă���ŏI
�̃e�[�u�����ʂ������B�g�p�����e�[�u����1 �݂̂̏ꍇ�́A���̃t�B�[���h�ɂ͂�
�̃e�[�u���̃e�[�u�����ʂ�ݒ肷��B�A�������e�[�u�����ʒl�ɓn���ď��͎��n��
�łȂ���΂Ȃ�Ȃ��B
event_id�i�C�x���g���ʁj�F����16 �r�b�g�̃t�B�[���h�́A�L�ڂ���Ă���C�x���g�̎�
�ʔԍ��i1 �T�[�r�X���ň�ӓI�Ɋ��蓖�Ă���j�������B
start_time�i�J�n���ԁj�F����40 �r�b�g�̃t�B�[���h�́A�C�x���g�̊J�n���Ԃ���{�W��
���iJST�j�ƏC�������E�X���iMJD�j�i�t�^C �Q�Ɓj�Ŏ����B���̃t�B�[���h�́AMJD
�̉���16 �r�b�g��16 �r�b�g�ŕ��������A����24 �r�b�g��6 ��4 �r�b�g2 �i��10 �i��
�iBCD�j�ŕ���������B�J�n���Ԃ���`����Ȃ��ꍇ�i�Ⴆ��NVOD ��T�[�r�X�Ȃǁj
�ɂ́A���̃t�B�[���h�̑S�Ẵr�b�g�́u1�v�ɐݒ肷��B
��P�F93/10/13 12:45:00 �́u0xC079124500�v�ƕ����������B
duration�i�p�����ԁj�F24 �r�b�g�̃t�B�[���h�ŁA�C�x���g�̌p�����Ԃ����A���A�b�ŕ\
���B�p�����Ԃ���`����Ȃ��ꍇ�i�Ⴆ�΋ً}�j���[�X�ŏI������������Ȃǁj�ɂ́A��
�̃t�B�[���h�̂��ׂẴr�b�g���u1�v�ɐݒ肷��B
�`���F6 ��4 �r�b�gBCD ���� = 24 �r�b�g
��2�F01:45:30 �́u0x014530�v�ƕ����������B
running_status�i�i�s��ԁj�F����3 �r�b�g�t�B�[���h�́A�\5�|6 �ɒ�`�����C�x��
�g�̏�Ԃ������B
free_CA_mode�i�X�N�����u���j�F����1 �r�b�g�̃t�B�[���h�́A���ꂪ�u0�v�̏ꍇ�͂�
�̃C�x���g���̑S�ẴR���|�[�l���g�X�g���[�����X�N�����u������Ă��Ȃ����Ƃ������B
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

class CEITTable : public CPSITable
{
public:
	typedef struct _EVENT_INFO_DATA{
		WORD event_id;
		BYTE StartTimeFlag;	//start_time�̒l���L�����ǂ���
		SYSTEMTIME start_time;
		BYTE DurationFlag; //duration�̒l���L�����ǂ���
		WORD durationHH;
		WORD durationMM;
		WORD durationSS;
		BYTE running_status;
		BYTE free_CA_mode;
		WORD descriptors_loop_length;
		vector<AribDescriptor::CDescriptor*> descriptorList;
		~_EVENT_INFO_DATA(void){
			for( size_t i=0; i<descriptorList.size(); i++ ){
				SAFE_DELETE(descriptorList[i]);
			}
			descriptorList.clear();
		};
	} EVENT_INFO_DATA;
	WORD service_id;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD transport_stream_id;
	WORD original_network_id;
	BYTE segment_last_section_number;
	BYTE last_table_id;
	vector<EVENT_INFO_DATA*> eventInfoList;

public:
	CEITTable(void);
	~CEITTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();

	BOOL SDDecode( BYTE* data, DWORD dataSize, vector<AribDescriptor::CDescriptor*>* descriptorList, DWORD* decodeReadSize );

};
