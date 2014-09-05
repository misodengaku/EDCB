#pragma once

/*
12.2.1 ���m���̓`������
12.2.1.1 �\�t�g�E�F�A�_�E�����[�h�g���K�[�e�[�u���iSoftware Donwload Trigger Table�j
�_�E�����[�h�̍��m���ʒm�̂��߂ɁA�\�t�g�E�F�A�_�E�����[�h�g���K�[�e�[�u��(Software
Donwload Trigger Table)��p����B�A���A12.2.2.2 �߂̃Z�N�V�����`���ő��o�����_�E�����[
�h�R���e���c�ɂ̓\�t�g�E�F�A�_�E�����[�h�g���K�[�e�[�u���͎g�p���Ȃ��B

software_download_trigger_section(){
	table_id						8 uimsbf
	section_syntax_indicator		1 bslbf
	reserved_future_use				1 bslbf
	reserved						2 bslbf
	section_length					12 uimsbf
	table_id_ext					16 uimsbf
	reserved						2 bslbf
	version_number					5 uimsbf
	current_next_indicator			1 uimsbf
	section_number					8 uimsbf
	last_section_number				8 uimsbf
	transport_stream_id				16 uimsbf
	original_network_id				16 uimsbf
	service_id						16 uimsbf
	num_of_contents					8 uimsbf
	for(i=0;i<num_of_contents;i++){
		group							4 bslbf
		target_version					12 uimsbf
		new_version						12 uimsbf
		download_level					2 bslbf
		version_indicator				2 bslbf
		content_description_length		12 uimsbf
		reserved						4 bslbf
		schedule_description_length		12 uimsbf
		schedule_time-shift_information	4 uimsbf
		for(i=0;i<N;i++){
			start_time						40 uimsbf
			duration						24 uimsbf
		}
		for(j=0;j<N2;j++){
			descriptors()
		}
	}
	CRC_32							32 rpchof
}

table_id�i�e�[�u�����ʁj�F0xC3
section_syntax_indicator�i�Z�N�V�����V���^�N�X�w���j�F�P
section_length�i�Z�N�V�������j�F�Z�N�V�������t�B�[���h�̒��ォ��CRC ���܂ރZ�N�V�����̍�
��܂ł̃Z�N�V�����̃o�C�g�����K�肷��B�Z�N�V��������4093 �𒴂��Ă͂Ȃ�Ȃ��B
table_id_ext�F
 maker_id	8 uimsbf
 model_id	8 uimsbf
version_number�i�o�[�W�����ԍ��j�F�T�u�e�[�u���̃o�[�W�����ԍ��ł���B�o�[�W�����ԍ��̓T
�u�e�[�u�����̏��ɕω����������ꍇ�ɂP���Z�����B���̒l��31 �ɂȂ����ꍇ�A0 �ɖ߂�B
current_next_indicator�i�J�����g�l�N�X�g�w���j�F1
section_number�i�Z�N�V�����ԍ��j�F�Z�N�V�����̔ԍ���\���B
last_section_number�i�ŏI�Z�N�V�����ԍ��j�F�Z�N�V������������T�u�e�[�u���̍Ō�̃Z�N�V��
���̔ԍ����K�肷��B
transport_stream_id�i�g�����X�|�[�g�X�g���[�����ʁj�F�g�����X�|�[�g�X�g���[���𕪔z�V�X�e
�����̑��̑��d���环�ʂ��郉�x���B
original_network_id�i�I���W�i���l�b�g���[�N���ʁj�F���̕��z�V�X�e���̃l�b�g���[�N���ʂ��K
�肷�郉�x���B
service_id�i�T�[�r�X���ʁj�F�_�E�����[�h�̍ۂɁA�_�E�����[�h�R���e���c���`�������T�[�r�X
�����ʂ��邽�߂̃��x���B
num_of_contents�F���̃e�[�u���ō��m����Ă���_�E�����[�h�R���e���c�̐��������B
group�Fgroup_id ���i�[�����B
target_version�F�_�E�����[�h�̍ۂɁA�A�b�v�f�[�g�ΏۂƂȂ�R���e���c�̃o�[�W�����ԍ��������B
new_version�F�_�E�����[�h�̍ۂɁA����_�E�����[�h�����R���e���c�̃o�[�W�����ԍ�������
download_level�i�_�E�����[�h���x���j�F01 �̏ꍇ�͋����_�E�����[�h�A00 �̏ꍇ�͔C�Ӄ_�E����
�[�h�B
version_indicator�i�o�[�W�����w���j�F�ȉ��̒ʂ�
00�F �S�o�[�W�������Ώہi�o�[�W�����w��͖����j�B
01�F �w�肳�ꂽ�o�[�W�����ȍ~���ΏہB
02�F �w�肳�ꂽ�o�[�W�����ȑO���ΏہB
03�F �w�肳�ꂽ�o�[�W�����݂̂��ΏہB
content_description_length()�F�X�P�W���[�����[�v�ƋL�q�q���[�v�̍��v�̃o�C�g���B
schedule_description_length�i�X�P�W���[���L�q���j�F�X�P�W���[�����[�v�̃o�C�g���B�S��M�@
���ʃf�[�^�ŁA���̒l��0 �̏ꍇ�́A�ΏۂƂȂ�_�E�����[�h�R���e���c���`������Ă��邱�Ƃ�
�����B
schedule_time-shift_information(�X�P�W���[�����ԃV�t�g���)�F�ȉ��̒ʂ�
0�F ������service_id �œ���_�E�����[�h�R���e���c�𓯈�X�P�W���[���ő��o
1~12�F ������service_id �œ���_�E�����[�h�R���e���c���eserice_id ����1~12 ���Ԃ�
���ԃV�t�g���s���đ��o
13~14�F ���U�[�u
15�F �P���service_id �Ń_�E�����[�h�R���e���c�𑗏o
�Ȃ��A������service_id �Ń_�E�����[�h�R���e���c�𑗏o����ꍇ��service_id �̓�����@�ȂǏ�
�׉^�p�͖{���t��-3�u�_�E�����[�h�@�\�v�A�y�ѕ������Ǝ҉^�p�K�����Q�Ƃ̂��ƁB
start_time�i�J�n���ԁj�F�_�E�����[�h�̔z�M�̊J�n���Ԃ���{�W����(JST)�ƏC�������E�X��(MJD)
�Ŏ����B
duration�i�p�����ԁj�F�z�M�p������

*/


#include "../../../Common/Util.h"
#include "../AribDescriptor.h"
#include "PSITable.h"

class CSDTTTable : public CPSITable
{
public:
	typedef struct _SCHEDULE_INFO_DATA{
		SYSTEMTIME start_time;
		DWORD duration;	//�b��
	}SCHEDULE_INFO_DATA;
	typedef struct _CONTENT_INFO_DATA{
		BYTE group;
		WORD target_version;
		WORD new_version;
		BYTE download_level;
		BYTE version_indicator;
		WORD content_description_length;
		WORD schedule_description_length;
		BYTE schedule_time_shift_information;
		vector<SCHEDULE_INFO_DATA> scheduleList;
		vector<AribDescriptor::CDescriptor*> descriptorList;
		~_CONTENT_INFO_DATA(void){
			for( size_t i=0; i<descriptorList.size(); i++ ){
				SAFE_DELETE(descriptorList[i]);
			}
			descriptorList.clear();
		};
	} CONTENT_INFO_DATA;
	BYTE maker_id;
	BYTE model_id;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD transport_stream_id;
	WORD original_network_id;
	WORD service_id;
	BYTE num_of_contents;
	vector<CONTENT_INFO_DATA*> contentInfoList;

public:
	CSDTTTable(void);
	~CSDTTTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
