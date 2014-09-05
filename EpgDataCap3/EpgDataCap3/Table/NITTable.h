#pragma once

/*
5.2.4 �l�b�g���[�N���e�[�u���iNIT�j�iNetwork Information Table�j
�m���n�{���ڂ́A�����ȍ����� 21 ��88 ��(8)�ł���������Ă���B
NIT�i�\5�|3 �Q�Ɓj�́A�l�b�g���[�N�ɂ��^�΂�鑽�d�^�g�����X�|�[�g�X�g���[��
�̕����I�\���Ɋւ�����A����уl�b�g���[�N���g�̓�����\�킷�B�I���W�i���l�b�g
���[�N���ʂƃg�����X�|�[�g�X�g���[�����ʂ̑g�ݍ��킹�ɂ��A�e�g�����X�|�[�g�X�g
���[����{�K�i�̓K�p�͈͑S�̂ɂ����ėB��ɒ�`���邱�Ƃ��\�ł���B�l�b�g���[�N
�͌ŗL�̃l�b�g���[�N���ʂ����蓖�Ă��A���ꂪ�l�b�g���[�N�̌ŗL���ʕ����Ƃ��ċ@
�\����B�l�b�g���[�N���ʂ̒l�͕W�����@�ւ̋K��ɂ��B�܂��A�g�����X�|�[�g���ʂ�
�l�͎��Ǝ҂��Ǝ��ɑI�肷�邱�Ƃ��ł���B�g�����X�|�[�g�X�g���[�������������l�b�g
���[�N�ɂ�����NIT ���`�����ꂽ�ꍇ�ɂ́A�l�b�g���[�N���ʂƃI���W�i���l�b�g���[�N
���ʂ͓���l�ł���B
�Ⴆ�Ήq������P�[�u���ւ̊ԂȂǁA�`���}�̂̋��E�ɂ�����ԑg�z����̏����ɂ�
���ẴK�C�h���C���͕ʓr��߂�B
��M�@��NIT ����s�������������ɋL�����邱�Ƃɂ��A�`�����l���Ԃ̐؂�ւ�
�i�u�`�����l���z�b�s���O�v�j���̃A�N�Z�X���Ԃ��ŏ��ɂ��邱�Ƃ��ł���B���l�b�g��
�[�N�����łȂ��A����ɕt�������đ��l�b�g���[�N��NIT �𑗐M���邱�Ƃ��\�ł���B
���l�b�g���[�N��NIT �Ƒ��l�b�g���[�N��NIT �Ƃ̋�ʂ́A�e�[�u�����ʒl�̈Ⴂ��
�p���čs����B�i�\5�|2 �Q�Ɓj
NIT �́A�\5�|3 �̃f�[�^�\�����g�p���āA�l�b�g���[�N���Z�N�V�����ɕ��������B
NIT �̈ꕔ���ƂȂ�Z�N�V�����͑S�āAPID �l0x0010 �̃g�����X�|�[�g�X�g���[���p�P
�b�g�ɂ��`�������B���l�b�g���[�N�i���Ȃ킿NIT ���܂ރg�����X�|�[�g�X�g���[��
�����̈ꕔ���Ȃ��l�b�g���[�N�j���L�q����NIT �̃Z�N�V�����͑S�ăe�[�u�����ʒl��
0x40 �Ƃ��A�l�b�g���[�N���ʃt�B�[���h�͕W�����@�ւ̋K��ɂ�莩�l�b�g���[�N�Ɋ���
���Ă��Ă���l�Ƃ��Ȃ���΂Ȃ�Ȃ��B���l�b�g���[�N�ȊO�̃l�b�g���[�N�Ɋւ���
NIT �̃Z�N�V�����́A�e�[�u�����ʒl0x41 ����ѕW�����@�ւ̋K��ɂ�葼�l�b�g���[
�N�Ɋ��蓖�Ă��Ă���l�b�g���[�N���ʒl�������Ȃ���΂Ȃ�Ȃ��B

network_information_section(){
	table_id						8 uimsbf
	section_syntax_indicator		1 bslbf
	reserved_future_use				1 bslbf
	reserved						2 bslbf
	section_length					12 uimsbf
	network_id						16 uimsbf
	reserved						2 bslbf
	version_number					5 uimsbf
	current_next_indicator			1 bslbf
	section_number					8 uimsbf
	last_section_number				8 uimsbf
	reserved_future_use				4 bslbf
	network_descriptors_length		12 uimsbf
	for(i=0;i<N;i++){
		descriptor()
	}
	reserved_future_use				4 bslbf
	transport_stream_loop_length	12 uimsbf
	for(i=0;i<N;i++){
		transport_stream_id				16 uimsbf
		original_network_id				16 uimsbf
		reserved_future_use				4 bslbf
		transport_descriptors_length	12 uimsbf
		for(j=0;j<N;j++)
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
network_id�i�l�b�g���[�N���ʁj�F�����16 �r�b�g�̃t�B�[���h�ŁANIT ���������z�V
�X�e���𑼂̕��z�V�X�e���Ƌ�ʂ��Ď��ʂ��郉�x���̖���������B���̃t�B�[���h�l��
���蓖�Ă͕W�����@�ւ̋K��ɂ��B�i�t�^�m�Q�Ɓj
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
���́A����̃e�[�u�����ʂƃl�b�g���[�N���ʂ����Z�N�V�����̒ǉ����Ƃ�1 ���Z����
��B
last_section_number�i�ŏI�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�́A���̃Z�N�V
������������T�u�e�[�u���̍Ō�̃Z�N�V�����i���Ȃ킿�A�ő�̃Z�N�V�����ԍ�������
�Z�N�V�����j�̔ԍ����K�肷��B
network_descriptors_length�i�l�b�g���[�N�L�q�q���j�F����12 �r�b�g�̃t�B�[���h�́A
��ɑ����l�b�g���[�N�L�q�q�̑S�o�C�g����\���B
transport_stream_loop_length�i�g�����X�|�[�g�X�g���[�����[�v���j�F����́ACRC_32
�̍ŏ��̃o�C�g�̒��O�ɏI���g�����X�|�[�g�X�g���[�����[�v�̑S�o�C�g�����K�肷��
12 �r�b�g�̃t�B�[���h�ł���B
transport_stream_id�i�g�����X�|�[�g�X�g���[�����ʁj�F����́A���̃g�����X�|�[�g�X
�g���[���𕪔z�V�X�e�����̑��̑��d���环�ʂ��邽�߂̃��x���̖���������16 �r�b�g
�̃t�B�[���h�ł���B
original_network_id�i�I���W�i���l�b�g���[�N���ʁj�F����16 �r�b�g�̃t�B�[���h�́A
���̕��z�V�X�e���̃l�b�g���[�N���ʂ��K�肷�郉�x���̖���������B
transport_descriptors_length�i�g�����X�|�[�g�L�q�q���j�F�����12 �r�b�g�̃t�B�[��
�h�ŁA�ȉ��ɑ����g�����X�|�[�g�X�g���[���L�q�q�̑S�̂̃o�C�g�����K�肷��B
CRC_32�iCRC�j�F����͕t�^B �Œ�`����f�R�[�_�ɂ����āA�Z�N�V�����S�̂�������
����Ƀ��W�X�^�o�͂��[���ɂȂ�悤��CRC �l���܂ށA32 �r�b�g�̃t�B�[���h�ł���B


*/

#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CNITTable : public CPSITable
{
public:
	typedef struct _TS_INFO_DATA{
		WORD transport_stream_id;
		WORD original_network_id;
		WORD transport_descriptors_length;
		vector<AribDescriptor::CDescriptor*> descriptorList;
		~_TS_INFO_DATA(void){
			for( size_t i=0; i<descriptorList.size(); i++ ){
				SAFE_DELETE(descriptorList[i]);
			}
			descriptorList.clear();
		};
	} TS_INFO_DATA;
	WORD network_id;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD network_descriptors_length;
	vector<AribDescriptor::CDescriptor*> descriptorList;
	WORD transport_stream_loop_length;
	vector<TS_INFO_DATA*> TSInfoList;

public:
	CNITTable(void);
	~CNITTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();

	BOOL SDDecode( BYTE* data, DWORD dataSize, vector<AribDescriptor::CDescriptor*>* descriptorList, DWORD* decodeReadSize );
};
