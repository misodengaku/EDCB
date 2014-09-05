#include "StdAfx.h"
#include "PacketInit.h"

CPacketInit::CPacketInit(void)
{
	this->nextStartSize = 0;
	this->nextStartBuff = new BYTE[256];
	this->packetSize = 0;
}

CPacketInit::~CPacketInit(void)
{
	SAFE_DELETE_ARRAY(this->nextStartBuff);
}

void CPacketInit::ClearBuff()
{
	this->nextStartSize = 0;
	this->packetSize = 0;
}

//���̓o�b�t�@��188�o�C�g�P�ʂ�TS�ɕϊ����A188�̔{���ɂȂ�悤�ɂ��낦��
//�߂�l�F
// TRUE�i�����j�AFALSE�i���s�j
//�����F
// inData			[IN]����TS�f�[�^
// inSize			[IN]inData�̃T�C�Y�iBYTE�P�ʁj
// outData			[OUT]188�o�C�g�ɐ��񂵂��o�b�t�@�i�Ăяo������delete����K�v����j
// outSize			[OUT]outData�̃T�C�Y�iBYTE�P�ʁj
BOOL CPacketInit::GetTSData(
	BYTE* inData,
	DWORD inSize,
	BYTE** outData,
	DWORD* outSize
)
{
	if( inData == NULL || inSize == 0 || outData == NULL || outSize == NULL ){
		return FALSE;
	}

	if( this->packetSize != 0 ){
		//�����ς�
		for( DWORD i = this->packetSize - this->nextStartSize; i < inSize; i += this->packetSize ){
			if( inData[i] != 0x47 ){
				//�ē������K�v
				this->packetSize = 0;
				break;
			}
		}
		if( this->packetSize != 0 ){
			*outSize = 188 * ((this->nextStartSize + inSize) / this->packetSize);
			*outData = new BYTE[*outSize];
			if( *outSize == 0 ){
				//�J��z������
				memcpy( this->nextStartBuff + this->nextStartSize, inData, inSize );
				this->nextStartSize += inSize;
			}else{
				if( this->nextStartSize >= 188 ){
					memcpy(*outData, this->nextStartBuff, 188);
				}else{
					memcpy(*outData, this->nextStartBuff, this->nextStartSize);
					memcpy(*outData + this->nextStartSize, inData, 188 - this->nextStartSize);
				}
				DWORD inPos = this->packetSize - this->nextStartSize;
				DWORD outPos = 188;
				for( ; inPos + this->packetSize <= inSize; inPos += this->packetSize, outPos += 188 ){
					memcpy(*outData + outPos, inData + inPos, 188);
				}
				//�J��z��
				memcpy(this->nextStartBuff, inData + inPos, inSize - inPos);
				this->nextStartSize = inSize - inPos;
			}
			return TRUE;
		}
	}

	DWORD nss = this->nextStartSize;

	for( DWORD pos = 0; pos + 188 < nss + inSize; pos++ ){
		if( pos < nss && this->nextStartBuff[pos] == 0x47 || pos >= nss && inData[pos - nss] == 0x47 ){
			for( int i = 0; i < 3; i++ ){
				this->packetSize = (i == 0 ? 188 : i == 1 ? 192 : 204);
				BOOL syncOK = FALSE;
				for( DWORD j = pos + this->packetSize; j < nss + inSize; j += this->packetSize ){
					if( j < nss && this->nextStartBuff[j] != 0x47 || j >= nss && inData[j - nss] != 0x47 ){
						syncOK = FALSE;
						break;
					}
					syncOK = TRUE;
				}
				if( syncOK == FALSE ){
					this->packetSize = 0;
				}else if( pos < nss ){
					this->nextStartSize -= pos;
					memmove(this->nextStartBuff, this->nextStartBuff + pos, this->nextStartSize);
					//�����ς݂̂Ƃ��̌J��z���T�C�Y�̓p�P�b�g�T�C�Y�����łȂ���΂Ȃ�Ȃ�
					if( this->nextStartSize >= this->packetSize ){
						this->nextStartSize -= this->packetSize;
						memmove(this->nextStartBuff, this->nextStartBuff + this->packetSize, this->nextStartSize);
					}
					return GetTSData(inData, inSize, outData, outSize);
				}else{
					this->nextStartSize = 0;
					return GetTSData(inData + (pos - nss), inSize - (pos - nss), outData, outSize);
				}
			}
		}
	}

	//�ē����Ɏ��s�B�\�Ȃ����J��z���Ă���
	if( inSize >= 256 ){
		memcpy(this->nextStartBuff, inData + (inSize - 256), 256);
		this->nextStartSize = 256;
	}else if( this->nextStartSize + inSize <= 256 ){
		memcpy(this->nextStartBuff + this->nextStartSize, inData, inSize);
		this->nextStartSize += inSize;
	}else{
		memmove(this->nextStartBuff, this->nextStartBuff + (this->nextStartSize + inSize - 256), 256 - inSize);
		memcpy(this->nextStartBuff + (256 - inSize), inData, inSize);
		this->nextStartSize = 256;
	}
	return FALSE;
}
