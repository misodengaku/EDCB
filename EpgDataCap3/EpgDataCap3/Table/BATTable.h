#pragma once

/*
5.2.5 �u�[�P�A�\�V�G�[�V�����e�[�u���iBAT�j�iBouquet Association Table�j
BAT�i�\5�|4 �Q�Ɓj�̓u�[�P�Ɋւ������񋟂���B�u�[�P�̓T�[�r�X�̏W���ł���
�l�b�g���[�N�̋��E���z���邱�Ƃ�����B
BAT �͕\5�|4 �Ɏ����f�[�^�\���ɂ��A�u�[�P�A�\�V�G�[�V�����Z�N�V�����ɕ�����
���BBAT �̈ꕔ���ƂȂ�Z�N�V�����͑S�āAPID �l0x0011 �̃g�����X�|�[�g�X�g���[
���p�P�b�g�ɂ��`�������B����̃u�[�P��\��BAT �T�u�e�[�u���̃Z�N�V�����́A��
�r�K�肳���u�[�P�Ɋ��蓖�Ă�ꂽ�l�̃u�[�P���ʃt�B�[���h�����B�S�Ă�BAT �Z�N
�V�����̓e�[�u�����ʒl��0x4A �ł���B

bouquet_association_section(){
	table_id						8 uimsbf
	section_syntax_indicator		1 bslbf
	reserved_future_use				1 bslbf
	reserved						2 bslbf
	section_length					12 uimsbf
	bouquet_id						16 uimsbf
	reserved						2 bslbf
	version_number					5 uimsbf
	current_next_indicator			1 bslbf
	section_number					8 uimsbf
	last_section_number				8 uimsbf
	reserved_future_use				4 bslbf
	bouquet_descriptors_length		12 uimsbf
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
		for(j=0;j<N;j++){
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
bouquet_id�i�u�[�P���ʁj�F�����16 �r�b�g�̃t�B�[���h�ŁA�u�[�P�����ʂ��郉�x����
����������B���̃t�B�[���h�l�̊��蓖�Ă͕ʓr�K�肷��B
version_number�i�o�[�W�����ԍ��j�F����5 �r�b�g�̃t�B�[���h�̓T�u�e�[�u���̃o�[�W
�����ԍ��ł���B�o�[�W�����ԍ��̓T�u�e�[�u�����̏��ɕω����������ꍇ��1 ���Z��
���B���̒l��31 �ɂȂ����ꍇ�́A���̎���0 �ɖ߂�B�J�����g�l�N�X�g�w�����u1�v��
�ꍇ�́A�o�[�W�����ԍ��̓e�[�u�����ʂƃu�[�P���ʂŒ�`����錻�݂̃T�u�e�[�u����
�o�[�W�����ԍ��ɂȂ�B�J�����g�l�N�X�g�w�����u0�v�̏ꍇ�́A�o�[�W�����ԍ��̓e�[�u
�����ʂƃu�[�P���ʂŒ�`����鎟�̃T�u�e�[�u���̃o�[�W�����ԍ��ɂȂ�B
current_next_indicator�i�J�����g�l�N�X�g�w���j�F����1 �r�b�g�̎w���́A���ꂪ�u1�v
�̏ꍇ�̓T�u�e�[�u�������݂̃T�u�e�[�u���ł��邱�Ƃ������B�u0�v�̏ꍇ�́A������
�T�u�e�[�u���͂܂��K�p���ꂸ�A���̃T�u�e�[�u���Ƃ��Ďg�p����邱�Ƃ������B
section_number�i�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�̓Z�N�V�����̔ԍ���\
���B�T�u�e�[�u�����̍ŏ��̃Z�N�V�����̃Z�N�V�����ԍ��́A0x00 �ł���B�Z�N�V������
���͓���̃e�[�u�����ʂƃu�[�P���ʂ����Z�N�V�����̒ǉ����Ƃ�1 ���Z�����B
last_section_number�i�ŏI�Z�N�V�����ԍ��j�F����8 �r�b�g�̃t�B�[���h�́A���̃Z�N�V
������������T�u�e�[�u���̍Ō�̃Z�N�V�����i���Ȃ킿�A�ő�̃Z�N�V�����ԍ�������
�Z�N�V�����j�̔ԍ����K�肷��B
bouquet_descriptors_length�i�u�[�P�L�q�q���j�F����12 �r�b�g�̃t�B�[���h�́A��ɑ�
���L�q�q�̑S�o�C�g����\���B
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

class CBATTable : public CPSITable
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
	WORD bouquet_id;
	BYTE version_number;
	BYTE current_next_indicator;
	BYTE section_number;
	BYTE last_section_number;
	WORD bouquet_descriptors_length;
	vector<AribDescriptor::CDescriptor*> descriptorList;
	WORD transport_stream_loop_length;
	vector<TS_INFO_DATA*> TSInfoList;

public:
	CBATTable(void);
	~CBATTable(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();
};
