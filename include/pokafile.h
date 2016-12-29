#ifndef _POKA_FILE_H
#define _POKA_FILE_H
#include <time.h>
#include "allcommon.h"
#include "pokalog.h"
#include "db/dbmoneydata.h"
#include "db/dbbusinesslistatm.h"
#include "db/dbrouterule.h"
#include "db/dbroute.h"

#define  FTP_SUCESS                	"sucess"
#define  FTP_ERROR                  "error"
#define  TMP_FILE_STRING          	"tmp"
#define  START_FILE_STRING          "START"
#define  FSN_FILE_STRING			"FSN"					//���ֺ��ļ���׺
#define  ZIP_FILE_STRING			"zip"
#define  BF_FILE_STRING				"BF"					//�ӳ��ļ���׺
#define  BK_FILE_STRING				"BK"					//������Ϣ�ļ���׺
#define  CT_FILE_STRING				"CT"					//��ȡ����Ϣ�ļ���׺
#define  ATM_FILE_STRING            "ATM"
#define  CRS_FILE_STRING            "CRS"
#define  DK_FILE_STRING             "DK"

#define  FSN_FILE_TYPE				0
#define  ZIP_FILE_TYPE				1
#define  BF_FILE_TYPE				2
#define  BK_FILE_TYPE	            3
#define  CT_FILE_TYPE	            4
#define  ATM_FILE_TYPE              5
#define  DK_FILE_TYPE               6
#define  START_FILE_TYPE            7
#define  CRS_FILE_TYPE            7

#define  MONVER_01_STRING				"1990"
#define  MONVER_02_STRING				"1999"
#define  MONVER_03_STRING				"2005"
#define  MONVER_04_STRING				"2015"


#define  SERVER_CODE_0                   0
#define  SERVER_CODE_1                   1
#define  SERVER_CODE_2                   2
#define  SERVER_CODE_3                   3

typedef unsigned short WORD;  //16λ�޷�������
typedef unsigned int LONG;   //32λ�޷�������

typedef struct t_FileName
{
	char BankNo[BANKNO_LEN+1];			//���к�
	char AgencyNo[AGENCYNO_LEN + 1];	//�����
	char CounterNo[DESKNO_LEN + 1];		//��̨��/һ������
	char BoxNo[BOXNO_LEN+1];			//����ID
	char Date[DATE_LEN+1];				//����
	char PackageId[KUNID_LEN + 1];		//��ID
	char DateTime[DATE_LEN+TIME_LEN+1];	//����ʱ��
	char Operator[USERID_LEN + 1]; 		//����Ա
	char BusinessType[5];
	char Percode[24+1];
	unsigned int OneRecordSize;
	DataType *df;
}FILENAME,*pFileName;

//������Ϣ�ṹ
typedef struct t_BundleBobInfo
{
	char BundleId[25];//��ID
	char BundleDate[20];//����ʱ��
	char OperatorId[25];//����Ա
	char Checker[25];//�������Ա
	char BobId[ONEBUNDLE_BOBNUM][25];//��ID

}BUNDLEBOBINFO,*pBundleBobInfo;


//�ļ�ͷ�ṹ��
typedef struct T_FileHead
{
	WORD HeadStart[4];	//USHORT:16λ�޷�������
	WORD HeadString[6];
	LONG  Counter;			//ULONG:32λ�޷�������
	WORD HeadEnd[4];

}FILEHEAD, *pFileHead;

//����ͼ�����ṹ
typedef struct T_ImageSNoData
{
	LONG Data[32];

}IMAGESNODATA, *pImageSNoData;

//ͼ����ֺŽṹ
typedef struct T_ImageSNo
{
	WORD Num;
	WORD height;
	WORD width;
	WORD Reserve2;
	IMAGESNODATA SNo[12];

}IMAGESNO, *pImageSNo;

//�ļ���¼�ṹ
typedef struct t_FileRecord
{
	char Date[10 + 1];		//���ڣ���+1��Ȼ���뱨ora01480��
	char Time[8];			//ʱ��
	char tfFlag[1 + 1];		//��ٱ�ʶ
	char ErrorCode[6+1];		//������
	char MoneyFlag[4+1];		//����
	char Ver[5+1];			//���
	char Valuta[5+1];			//��ֵ
	char CharNUM[2];		//���ֺ��ַ���
	char SNo[12+1];			//���ֺ�
	char MachineSNo[24 + 1];//���ߺ�
	char Reserve1[50+1];		//������
	IMAGESNO ImageSNo;		//���ֺ�ͼ��
	char ImageSNoChar[2500];
	unsigned char str[10*32*4 + 62 + 1];
	char ImageFilePath[FILE_PATH_CHARNUM];

	//����ҵ��
	char BundleID[24 + 1];	//������
	char PackageId[KUNID_LEN + 1];	//��ID
	char AgencyID[8+1];		//�����
	char Operator[20 + 1];  //����Ա
	char Monitor[20 + 1];	//�ලԱ

	//÷��ɢװ�ӳ�ҵ��
	char MonBoxID[24 + 1];		//����ID
	char AtmID[24 + 1];			//ATM��ID
	char AddMonOperator[8 + 1];	//�ӳ�Ա
	char AddMonChecker[8 + 1];	//�ӳ����Ա
	//int BusinessType;			//ҵ������
	char BusinessType[5+1];

	char DateTime[20+1];
	char Quanlity[5+1];
	char BankNo[BANKNO_LEN+1];
	char AgencyNo[AGENCYNO_LEN+1];
	char FileName[FILE_PATH_CHARNUM+1];
	unsigned int iFailInsRecordNum;
}FILERECORD, *pFileRecord;

typedef struct t_FileMoveInfo
{
	char FileBaseName[FILE_NAME_CHARNUM];
	char FilePth[MAX_STRING_SIZE];
	char LocalDesBaseName[FILE_NAME_CHARNUM];
	char LocalDesFilePath[MAX_STRING_SIZE];
	char ReFileBaseName[FILE_NAME_CHARNUM];
	char ReFilePath[MAX_STRING_SIZE];
	char ReBankNO[5];
	char ReIp[20];
	char RePort[10];
    int  isRemote;
    int  isCompress;
}FILEMOVEINFO,*pFileMoveInfo;


int FSNFile(DataType *df);
int DKFile(DataType *df);
int CTFile(DataType *df);
int BKFile(DataType *df);
int BFFile(DataType *df);
int ATMFile(DataType *df);
int ZIPFile(DataType *df);
char *CompressFile(char *srcFile,char *zipFile);
int CheckDirEmpty(char *dir);
int ReadFSNOrBKFileName(const char *szFileName, FILENAME *pfilename);
int	WriteToSnoTable(FILENAME *fsnFile);
void CheckDoubtMon(FILERECORD *fileRecord);
int CheckFSNRecode(FILERECORD *fileRecord);
void *ListDirThread(void *pt);
void *SwitchFileThread(void *pt);
void *HandleFileThread(void *pt);
int CheckFileType(char *type);
void CheckResult(DataType *df,int result);
int StartFile(DataType *df);
int StopFile(DataType *df);
void CoverFiles();
char *GetErrorLocalDir(char *dir,const  FILENAME *fn);
int MoveFiles(FILEMOVEINFO *pInfo);
int CopyFiles(FILEMOVEINFO *pInfo);
char *GetSucInsLocalDir(char *dir,const  FILENAME *fn);
int MoveFSNFile(FILENAME *fn,int result);
void *SendFileThread();
char *GetPercode(const char *src,char *des);
int ReadAtmFileName(const char *szFileName, FILENAME *fn,ATMBUSINESSLIST *business);
int UploadFile(ROUTE *route);
int DownFile(ROUTE *route);
int Start_service(ROUTE *route);
int Stop_service(ROUTE *route);
#endif