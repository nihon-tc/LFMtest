/** @file
 * LFM�e�[�u���g��API
 *
 * (C)2009 Turbo Data Laboratories, Inc.
 */

#ifndef _RDI5APIEXT_H
#define _RDI5APIEXT_H

#include "di5api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * �o�[�W���������擾���܂��B
 * @param[out]	anVersion	�o�[�W�����z��
 * @retval	0	���0
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * anVersion�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetVersionR1(int* anVersion);

/**
 * �R�s�[���C�g���b�Z�[�W���擾���܂��B
 * @retval	�R�s�[���C�g���b�Z�[�W
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetCopyRightR1();

/**
 * ���[�N�X�y�[�X�̃p�X���擾���܂��B
 * @retval	���[�N�X�y�[�X�̃p�X
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetDBPathR1();

/**
 * ���[�N�X�y�[�X�̖��̂��擾���܂��B
 * @retval	���[�N�X�y�[�X�̖���
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetDBNameR1();

/**
 * �o�^�\�ȃe�[�u�����̂𐶐����܂��B
 * @param[in]	szSeedName	���������e�[�u�����̂̌��ƂȂ镶����
 * @retval	�o�^�\�ȃe�[�u������
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GenerateTableNameR1(char *szSeedName);

/* */
char*	D5APICALL RD5GenTableNameR1(char *szSeedName);

/**
 * �e�[�u�����̂��擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @retval	�e�[�u������
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetTableNameR1(int nTableID);

/**
 * �w�肵������(������)�̃f�[�^�ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	szX			1�Ԗڂ̌��������f�[�^
 * @param[in]	szY			2�Ԗڂ̌��������f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5SearchByFieldStrR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, char *szX, char *szY);

/**
 * �w�肵������(����)�̃f�[�^�ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID	�Z�b�gID
 * @param[in]	nOpeNo	����������
 * @param[in]	nX		1�Ԗڂ̌��������f�[�^
 * @param[in]	nY		2�Ԗڂ̌��������f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5SearchByFieldIntR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, int nX, int nY);

/**
 * �w�肵������(��������)�̃f�[�^�ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID	�Z�b�gID
 * @param[in]	nOpeNo	����������
 * @param[in]	dX		1�Ԗڂ̌��������f�[�^
 * @param[in]	dY		2�Ԗڂ̌��������f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5SearchByFieldDblR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, double dX, double dY);

/**
 * �w�肵������(Numeric)�̃f�[�^�ɂ�錟�����s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	pNumericX	1�Ԗڂ̌��������f�[�^
 * @param[in]	pNumericY	2�Ԗڂ̌��������f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pcX,pcY�́Alfmutil��{@link CNumeric}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5SearchByFieldNumericR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, Numeric *pNumericX, Numeric *pNumericY);

/**
 * �w�肵�����ڂ́A�}���`�o�C�g�����R�[�h���g�����������s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	szX			1�Ԗڂ̌��������f�[�^
 * @param[in]	szY			2�Ԗڂ̌��������f�[�^
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5SearchByFieldSJISR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, char *szX, char *szY);

/**
 * �w�肵�����ڂ́A�}���`�o�C�g�����R�[�h���g�����������s���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nOpeNo		����������
 * @param[in]	szX			1�Ԗڂ̌��������f�[�^
 * @param[in]	szY			2�Ԗڂ̌��������f�[�^
 * @param[in]	nLocaleID	�����R�[�hID
 * @retval	1�ȏ�	�������ʂŐV�K�ɐ������ꂽ�Z�b�gID
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5SearchByFieldLocaleR1(int nTableID, int nFilterID, int nSetID, int nOpeNo, char *szX, char *szY, int nLocaleID);

/* */
int		D5APICALL RD5GetDataIntR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/* */
double	D5APICALL RD5GetDataDblR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/* */
char*	D5APICALL RD5GetDataStrR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/* */
int		D5APICALL RD5GetDataNumericR1(int nTableID, int nFilterID, int nSetID, int nRowNo, Numeric *pNumeric);

/**
 * NUMERIC���ڏ����擾���܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nFilterID		�t�B���^ID
 * @param[out]	pNumericInfo	NUMERIC���ڏ��
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pNumericInfo�́Alfmutil��{@link CNumericInfo}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetNumericInfoR1(int nTableID, int nFilterID, NumericInfo *pNumericInfo);

/**
 * �P��f�[�^(����)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @retval	�擾�����f�[�^
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5GetData1IntR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * �P��f�[�^(��������)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @retval	�擾�����f�[�^
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
double	D5APICALL RD5GetData1DblR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * �P��f�[�^(������)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @retval	�擾�����f�[�^
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetData1StrR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * �P��f�[�^(Numeric)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @param[out]	pNumeric	�擾�����f�[�^
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pNumeric�́Alfmutil��{@link CNumeric}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetData1NumericR1(int nTableID, int nFilterID, int nSetID, int nRowNo, Numeric *pNumeric);

/**
 * ����ID���獀�ږ��̂��擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @retval	���ږ���
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetFilterNameR1(int nTableID, int nFilterID);

/* */
char*	D5APICALL RD5GetSerialR1();

/* */
char*	D5APICALL RD5CategoryReadR1(int nSumHandle, int nDimNo, int nCatNo);

/**
 * �f�[�^(����)���㏑�����܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nFilterID	����ID
 * @param[in]	nWritePos	�������݈ʒu
 * @param[in]	nWriteData	�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5OverwriteRealExIntR1(int nTableID, int nSetID, int nFilterID, int nWritePos, int nWriteData);

/**
 * �f�[�^(��������)���㏑�����܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWritePos	�������݈ʒu
 * @param[in]	dWriteData	�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5OverwriteRealExDblR1(int nTableID, int nSetID, int nFilterID, int nWritePos, double dWriteData);

/**
 * �f�[�^(Numeric)���㏑�����܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nFilterID	����ID
 * @param[in]	nWritePos	�������݈ʒu
 * @param[in]	pWriteData	�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pWriteData�́Alfmutil��{@link CNumeric}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5OverwriteRealExNumericR1(int nTableID, int nSetID, int nFilterID, int nWritePos, Numeric *pWriteData);

/**
 * �f�[�^(������)���㏑�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWritePos		�������݈ʒu
 * @param[in]	szWriteData		�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5OverwriteRealExStrR1(int nTableID, int nSetID, int nFilterID, int nWritePos, char *szWriteData);

/**
 * �f�[�^(����)���㏑�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWriteStart		�������݊J�n�ʒu
 * @param[in]	nWriteCount		�������ݐ�
 * @param[in]	nWriteData		�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5FillRealExIntR1(int nTableID, int nSetID, int nFilterID, int nWriteStart, int nWriteCount, int nWriteData);

/**
 * �f�[�^(��������)���㏑�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWriteStart		�������݊J�n�ʒu
 * @param[in]	nWriteCount		�������ݐ�
 * @param[in]	dWriteData		�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5FillRealExDblR1(int nTableID, int nSetID, int nFilterID, int nWriteStart, int nWriteCount, double dWriteData);

/**
 * �f�[�^(Numeric)���㏑�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWriteStart		�������݊J�n�ʒu
 * @param[in]	nWriteCount		�������ݐ�
 * @param[in]	pWriteData		�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pWriteData�́Alfmutil��{@link CNumeric}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5FillRealExNumericR1(int nTableID, int nSetID, int  nFilterID, int nWriteStart, int nWriteCount, Numeric *pWriteData);

/**
 * �f�[�^(������)���㏑�����܂��B
 * @param[in]	nTableID		�e�[�u��ID
 * @param[in]	nSetID			�Z�b�gID
 * @param[in]	nFilterID		����ID
 * @param[in]	nWriteStart		�������݊J�n�ʒu
 * @param[in]	nWriteCount		�������ݐ�
 * @param[in]	szWriteData		�������݃f�[�^
 * @retval	0�ȏ�	�������݂ɐ��������f�[�^��
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
int		D5APICALL RD5FillRealExStrR1(int nTableID, int nSetID, int nFilterID, int nWriteStart, int nWriteCount, char *szWriteData);

/**
 * �P��f�[�^�𕶎���ɕϊ����Ď擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @retval	�擾�����f�[�^
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetData1Cnv2StrR1(int nTableID, int nFilterID, int nSetID, int nRowNo);

/**
 * ���������f�[�^�𕶎���(���t)�ɕϊ����Ď擾���܂��B
 * @param[in]	dData	���������f�[�^
 * @retval	�ϊ���̕�����
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5Double2DateStrR1(double dData);

/**
 * ���������f�[�^�𕶎���(����)�ɕϊ����Ď擾���܂��B
 * @param[in]	dData	���������f�[�^
 * @retval	�ϊ���̕�����
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5Double2TimeStrR1(double dData);

/**
 * ���������f�[�^�𕶎���(���t����)�ɕϊ����Ď擾���܂��B
 * @param[in]	dData	���������f�[�^
 * @retval	�ϊ���̕�����
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5Double2DateTimeStrR1(double dData);

/**
 * Numeric�f�[�^�𕶎���ɕϊ����܂��B
 * @param[in]	pNumeric		Numeric�f�[�^
 * @param[in]	pNumericInfo	Numeric���ڏ��
 * @param[in]	nScale			�X�P�[���i�����_�ȉ������j
 * @param[in]	nPrec			���x
 * @retval	�ϊ���̕�����
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pNumeric�́Alfmutil��{@link CNumeric}���g�p���ă|�C���^���w�肵�Ă��������B
 * pNumericInfo�́Alfmutil��{@link CNumericInfo}���g�p���ă|�C���^���w�肵�Ă��������B
 */
char*	D5APICALL RD5NumericNum2StrR1(const Numeric *pNumeric, const NumericInfo *pNumericInfo, int nScale, int nPrec);

/**
 * ������(���t)�𕂓������ɕϊ����Ď擾���܂��B
 * @param[in]	szData	������f�[�^
 * @retval	�ϊ���̕��������f�[�^
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
double	D5APICALL RD5Str2DateR1(char *szData);

/**
 * ������(����)�𕂓������ɕϊ����Ď擾���܂��B
 * @param[in]	szData	������f�[�^
 * @retval	�ϊ���̕��������f�[�^
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
double	D5APICALL RD5Str2TimeR1(char *szData);

/**
 * ������(���t����)�𕂓������ɕϊ����Ď擾���܂��B
 * @param[in]	szData	������f�[�^
 * @retval	�ϊ���̕��������f�[�^
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
double	D5APICALL RD5Str2DateTimeR1(char *szData);

/**
 * �����f�[�^(����)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @param[out]	pnGotCount	�擾�����f�[�^��
 * @param[out]	pnBuf		�擾�����f�[�^�i�[�̈�ւ̃|�C���^
 * @retval	0�ȏ�	�擾�����s�̂����A�P��ōő�̃f�[�^�T�C�Y(byte)
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnGotCount,pnBuf�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetData1MIntR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int *pnGotCount, int *pnBuf);

/**
 * �����f�[�^(��������)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @param[out]	pnGotCount	�擾�����f�[�^��
 * @param[out]	pdBuf		�擾�����f�[�^�i�[�̈�ւ̃|�C���^
 * @retval	0�ȏ�	�擾�����s�̂����A�P��ōő�̃f�[�^�T�C�Y(byte)
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnGotCount�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 * pdBuf�́Alfmutil��{@link CTypeDblAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetData1MDblR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int *pnGotCount, double *pdBuf);

/**
 * �����f�[�^(Numeric)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @param[out]	pnGotCount	�擾�����f�[�^��
 * @param[out]	pNumericBuf	�擾�����f�[�^�i�[�̈�ւ̃|�C���^
 * @retval	0�ȏ�	�擾�����s�̂����A�P��ōő�̃f�[�^�T�C�Y(byte)
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnGotCount�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 * pNumericBuf�́Alfmutil��{@link CTypeNumAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetData1MNumericR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int *pnGotCount, Numeric *pNumericBuf);

/**
 * �����f�[�^(������)���擾���܂��B
 * @param[in]	nTableID	�e�[�u��ID
 * @param[in]	nFilterID	����ID
 * @param[in]	nSetID		�Z�b�gID
 * @param[in]	nRowNo		�Z�b�g�������ԍ�
 * @param[out]	pnGotCount	�擾�����f�[�^��
 * @param[out]	pnOffset	buf���ł̒P��f�[�^�̊J�n�ʒu(4�o�C�g)�̔z��
 * @param[out]	pvBuf		�擾�����f�[�^�i�[�̈�ւ̃|�C���^
 * @retval	0�ȏ�	NULL�I�[���܂܂Ȃ��ŏI�s�̃f�[�^�T�C�Y(byte)
 * @retval	��		�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnGotCount�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 * pnOffset�́Alfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 * pvBuf�́Alfmutil��{@link CTypeCharAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetData1MStrR1(int nTableID, int nFilterID, int nSetID, int nRowNo, int*pnGotCount, int *pnOffset, void *pvBuf);

/**
 * �Z�b�g���̂��擾���܂��B
 * @param[in]	nTableID	�Z�b�g�̑�����e�[�u��ID
 * @param[in]	nSetID		�Z�b�gID
 * @retval	�Z�b�g����
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * ���ɂȂ�
 */
char*	D5APICALL RD5GetSetNameR1(int nTableID, int nSetID);

/* */
int		D5APICALL RD5GetJoinInfoR1(int nTableID,
					   int	*pnMasterTableID,	//  OUT:�w��̃e�[�u���̃}�X�^�[�e�[�u��ID
					   int	*pnMasterSetID,		//  OUT:�w��̃e�[�u���̃}�X�^�[�W��ID
					   int	*pnMasterFilterID,	//  OUT:�ŏ���JOINKEY��ID
					   int	*pnSlaveTableID,	//  OUT:�w��̃e�[�u���̃X���[�u�e�[�u��ID
					   int	*pnSlaveSetID,		//  OUT:�w��̃e�[�u���̃X���[�u�W��ID
					   int	*pnSlaveFilterID	//  OUT:�ŏ���JOINKEY��ID
						);

/**
 * JOIN�e�[�u���̏����擾���܂��B
 * @param[in]	nTableID			�����擾����JOIN�e�[�u��ID
 * @param[out]	pnIsOuter			JOIN�e�[�u���̎��
 * @param[out]	pnJoinKeyCount		JOIN�L�[�̐�
 * @param[out]	pnMasterTableID		�}�X�^�e�[�u��ID
 * @param[out]	pnMasterSetID		�}�X�^�e�[�u���Z�b�gID
 * @param[out]	anMasterFilterIDs	�}�X�^�e�[�u����JOIN�L�[�̈ꗗ
 * @param[out]	pnSlaveTableID		�X���[�u�e�[�u��ID
 * @param[out]	pnSlaveSetID		�X���[�u�e�[�u���Z�b�gID
 * @param[out]	anSlaveFilterIDs	�X���[�u�e�[�u����JOIN�L�[�̈ꗗ
 * @retval	0	����
 * @retval	��	�G���[�R�[�h
 * 
 * @par	�X�N���v�g���ꂩ��g�p����ۂ̒��ӎ���:
 * pnIsOuter,pnJoinKeyCount,pnMasterTableID,pnMasterSetID,anMasterFilterIDs,pnSlaveTableID,pnSlaveSetID,anSlaveFilterIDs�́A
*  lfmutil��{@link CTypeIntAr}���g�p���ă|�C���^���w�肵�Ă��������B
 */
int		D5APICALL RD5GetJoinInfoExR1(
         int nTableID,				//    IN:�w��̃e�[�u���̃e�[�u��ID
         int	*pnIsOuter,			//    OUT:OuterJoin=1, InnerJoin=0
         int	*pnJoinKeyCount,	//   OUT:JoinKey's count
         int	*pnMasterTableID,	//    OUT:�w��̃e�[�u���̃}�X�^�[�e�[�u��ID
         int	*pnMasterSetID,		//    OUT:�w��̃e�[�u���̃}�X�^�[�W��ID
         int    anMasterFilterIDs[D5_MAX_JOIN_KEY],	//  OUT:JOINKEY��Filter-ID�z��i�̈�͌Ăяo�����Łj
         int	*pnSlaveTableID,	//    OUT:�w��̃e�[�u���̃X���[�u�e�[�u��ID
         int	*pnSlaveSetID,		//    OUT:�w��̃e�[�u���̃X���[�u�W��ID
         int    anSlaveFilterIDs[D5_MAX_JOIN_KEY]	//   OUT:JOINKEY��Filter-ID�z��i�̈�͌Ăяo�����Łj
        );							//  0:Success, �|�̎��A�G���[�R�[�h


/* */
int		D5APICALL RD5Connect2LFMServer(int nOpt, char *szIdentity);

/* */
int		D5APICALL RD5DisconnectFromLFMServer();

/* */
char*	D5APICALL RD5GetNamingServiceIdentity();

#ifdef __cplusplus
}
#endif

#endif
