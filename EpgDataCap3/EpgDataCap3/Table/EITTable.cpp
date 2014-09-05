#include "StdAfx.h"
#include "EITTable.h"

#include "../../../Common/EpgTimerUtil.h"

CEITTable::CEITTable(void)
{
}

CEITTable::~CEITTable(void)
{
	Clear();
}

void CEITTable::Clear()
{
	for( size_t i=0 ;i<eventInfoList.size(); i++ ){
		SAFE_DELETE(eventInfoList[i]);
	}
	eventInfoList.clear();
}

BOOL CEITTable::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( InitDecode(data, dataSize, decodeReadSize, TRUE) == FALSE ){
		return FALSE;
	}
	Clear();

	if( section_syntax_indicator != 1 ){
		//�Œ�l����������
		_OutputDebugString( L"++CEITTable:: section_syntax err" );
		return FALSE;
	}
	if( table_id < 0x4E || table_id > 0x6F ){
		//table_id����������
		_OutputDebugString( L"++CEITTable:: table_id err 0x%02X", table_id );
		return FALSE;
	}

	if( section_length - 4 > 10 ){
		service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		version_number = (data[readSize+2]&0x3E)>>1;
		current_next_indicator = data[readSize+2]&0x01;
		section_number = data[readSize+3];
		last_section_number = data[readSize+4];
		transport_stream_id = ((WORD)data[readSize+5])<<8 | data[readSize+6];
		original_network_id = ((WORD)data[readSize+7])<<8 | data[readSize+8];
		segment_last_section_number = data[readSize+9];
		last_table_id = data[readSize+10];
		readSize += 11;
		while( readSize+11 < (DWORD)section_length+3-4 ){
			EVENT_INFO_DATA* item = new EVENT_INFO_DATA;
			item->event_id = ((WORD)data[readSize])<<8 | data[readSize+1];
			if( data[readSize+2] == 0xFF && data[readSize+3] == 0xFF && data[readSize+4] == 0xFF &&
				data[readSize+5] == 0xFF && data[readSize+6] == 0xFF )
			{
				item->StartTimeFlag = FALSE;
			}else{
				item->StartTimeFlag = TRUE;
				DWORD mjd = ((DWORD)data[readSize+2])<<8 | data[readSize+3];
				_MJDtoSYSTEMTIME(mjd, &(item->start_time));
				item->start_time.wHour = (WORD)_BCDtoDWORD(data+readSize+4, 1, 2);
				item->start_time.wMinute = (WORD)_BCDtoDWORD(data+readSize+5, 1, 2);
				item->start_time.wSecond = (WORD)_BCDtoDWORD(data+readSize+6, 1, 2);
			}
			readSize+=7;
			if( data[readSize] == 0xFF && data[readSize+1] == 0xFF && data[readSize+2] == 0xFF)
			{
				item->DurationFlag = FALSE;
			}else{
				item->DurationFlag = TRUE;
				item->durationHH = (WORD)_BCDtoDWORD(data+readSize, 1, 2);
				item->durationMM = (WORD)_BCDtoDWORD(data+readSize+1, 1, 2);
				item->durationSS = (WORD)_BCDtoDWORD(data+readSize+2, 1, 2);
			}
			readSize+=3;
			item->running_status = (data[readSize]&0xE0)>>5;
			item->free_CA_mode = (data[readSize]&0x10)>>4;
			item->descriptors_loop_length = ((WORD)data[readSize]&0x0F)<<8 | data[readSize+1];
			readSize += 2;
			if( readSize+item->descriptors_loop_length <= (DWORD)section_length+3-4 && item->descriptors_loop_length > 0){
				if( original_network_id == 0x0001 || original_network_id == 0x0003 ){
					SDDecode( data+readSize, item->descriptors_loop_length, &(item->descriptorList), NULL );
				}else{
					if( AribDescriptor::CreateDescriptors( data+readSize, item->descriptors_loop_length, &(item->descriptorList), NULL ) == FALSE ){
						_OutputDebugString( L"++CEITTable:: descriptor2 err" );
						SAFE_DELETE(item);
						return FALSE;
					}
				}
			}

			readSize+=item->descriptors_loop_length;

			eventInfoList.push_back(item);
		}
	}else{
		return FALSE;
	}

	return TRUE;
}

BOOL CEITTable::SDDecode( BYTE* data, DWORD dataSize, vector<AribDescriptor::CDescriptor*>* descriptorList, DWORD* decodeReadSize )
{
	BOOL ret = TRUE;
	if( data == NULL || dataSize == 0 || descriptorList == NULL ){
		return FALSE;
	}
	DWORD decodeSize = 0;

	AribDescriptor::CDescriptor* shortItem = NULL;

	static const short parser0x82[] = {
		AribDescriptor::descriptor_tag, 8,
		AribDescriptor::descriptor_length, AribDescriptor::D_LOCAL, 8,
		AribDescriptor::D_BEGIN, AribDescriptor::descriptor_length,
			AribDescriptor::reserved, AribDescriptor::D_LOCAL, 8,
			AribDescriptor::event_name_char, AribDescriptor::D_STRING_TO_END,
		AribDescriptor::D_END,
		AribDescriptor::D_FIN,
	};
	static const short parser0x83[] = {
		AribDescriptor::descriptor_tag, 8,
		AribDescriptor::descriptor_length, AribDescriptor::D_LOCAL, 8,
		AribDescriptor::D_BEGIN, AribDescriptor::descriptor_length,
			AribDescriptor::reserved, AribDescriptor::D_LOCAL, 8,
			AribDescriptor::D_BEGIN_FOR, 8,
				AribDescriptor::item_description_char, AribDescriptor::D_STRING_TO_END,
			AribDescriptor::D_END,
		AribDescriptor::D_END,
		AribDescriptor::D_FIN,
	};
	static const short parser0x85[] = {
		AribDescriptor::descriptor_tag, 8,
		AribDescriptor::descriptor_length, AribDescriptor::D_LOCAL, 8,
		AribDescriptor::D_BEGIN, AribDescriptor::descriptor_length,
			AribDescriptor::reserved, AribDescriptor::D_LOCAL, 4,
			AribDescriptor::stream_content, 4,
			AribDescriptor::component_type, 8,
			AribDescriptor::component_tag, 8,
			AribDescriptor::reserved, AribDescriptor::D_LOCAL, 8,
			AribDescriptor::text_char, AribDescriptor::D_STRING_TO_END,
		AribDescriptor::D_END,
		AribDescriptor::D_FIN,
	};
	AribDescriptor::PARSER_PAIR parserList[] = {{0x82, parser0x82}, {0x83, parser0x83}, {0x85, parser0x85}, {0, NULL}};

	while( decodeSize + 2 < dataSize ){
		BYTE* readPos = data+decodeSize;

		if( readPos[0] == 0x54 ){
			AribDescriptor::CDescriptor* item = new AribDescriptor::CDescriptor;
			if( item->Decode(readPos, dataSize - decodeSize, NULL) == false ){
				delete item;
			}else{
				if( item->EnterLoop() ){
					for( DWORD i = 0; item->SetLoopIndex(i); i++ ){
						switch( item->GetNumber(AribDescriptor::user_nibble_1) ){
						case 0x00:
							//�f��H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x06);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x02:
							//�X�|�[�c�H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x01);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x04:
							//���y�H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x04);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x05:
							//�h���}�H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x03);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x06:
							//�j���[�X�H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x00);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x07:
							//�o���G�e�B�H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x05);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x08:
							//��^����H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x0A);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x09:
							//�A�j���H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x07);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						case 0x0A:
							//�h�L�������^���[�^���{�H
							item->SetNumber(AribDescriptor::content_nibble_level_1, 0x08);
							item->SetNumber(AribDescriptor::content_nibble_level_2, 0x0F);
							break;
						default:
							break;
						}
					}
					item->LeaveLoop();
				}
				descriptorList->push_back(item);
			}

			decodeSize += readPos[1]+2;
		}else
		if( readPos[0] == 0x85 ){
			//�R���|�[�l���g
			AribDescriptor::CDescriptor* item = new AribDescriptor::CDescriptor;
			if( item->Decode(readPos, dataSize - decodeSize, NULL, parserList) == false ){
				delete item;
			}else{
				if( item->GetNumber(AribDescriptor::stream_content) == 0x01 ){
					//�f���B�R���|�[�l���g�L�q�q�ɃL���X�g
					item->SetNumber(AribDescriptor::descriptor_tag, AribDescriptor::component_descriptor);
					descriptorList->push_back(item);
				}else
				if( item->GetNumber(AribDescriptor::stream_content) == 0x02 ){
					//�����B�����R���|�[�l���g�L�q�q�ɃL���X�g
					item->SetNumber(AribDescriptor::descriptor_tag, AribDescriptor::audio_component_descriptor);
					descriptorList->push_back(item);
				}else{
					delete item;
				}
			}
			decodeSize += readPos[1]+2;
		}else
		if( readPos[0] == 0x82 ){
			//�ԑg��
			if( readPos[2] == 0x01 ){
				if( shortItem == NULL ){
					shortItem = new AribDescriptor::CDescriptor;
				}
				if( shortItem->Decode(readPos, dataSize - decodeSize, NULL, parserList) == false ){
					delete shortItem;
					shortItem = NULL;
				}else{
					//���{��ŁH
					//�Z�`���C�x���g�L�q�q�ɃL���X�g
					shortItem->SetNumber(AribDescriptor::descriptor_tag, AribDescriptor::short_event_descriptor);
				}
			}else if( readPos[2] == 0x02 && shortItem == NULL){
				shortItem = new AribDescriptor::CDescriptor;
				if( shortItem->Decode(readPos, dataSize - decodeSize, NULL, parserList) == false ){
					delete shortItem;
					shortItem = NULL;
				}else{
					//�p��ŁH
					//�Z�`���C�x���g�L�q�q�ɃL���X�g
					shortItem->SetNumber(AribDescriptor::descriptor_tag, AribDescriptor::short_event_descriptor);
				}
			}
			decodeSize += readPos[1]+2;
		}else
		if( readPos[0] == 0x83 ){
			//�ڍ׏��
			AribDescriptor::CDescriptor* item = new AribDescriptor::CDescriptor;
			if( item->Decode(readPos, dataSize - decodeSize, NULL, parserList) == false ){
				delete item;
			}else{
				//�g���`���C�x���g�L�q�q�ɃL���X�g
				//TODO: �{����descriptor_number���������ׂ������A�㑱�̏����ň�ؗ��p����Ȃ��̂ŏȗ�����
				item->SetNumber(AribDescriptor::descriptor_tag, AribDescriptor::extended_event_descriptor);
				descriptorList->push_back(item);
			}

			decodeSize += readPos[1]+2;
		}else{
			decodeSize += readPos[1]+2;
		}
	}
	if( shortItem != NULL ){
		descriptorList->push_back(shortItem);
	}

	if( descriptorList->size() == 0 ){
		ret = FALSE;
	}

	if( decodeReadSize != NULL ){
		*decodeReadSize = dataSize;
	}
	return ret;
}

