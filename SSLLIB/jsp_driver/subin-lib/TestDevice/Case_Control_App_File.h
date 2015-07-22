#ifndef _CASE_CONTROL_APP_FILE_H_
#define _CASE_CONTROL_APP_FILE_H_


/*

INT8	�з���8λ����	
INT16	�з���16λ����	
INT32	�з���32λ����	
UINT8	�޷���8λ����	
UINT16	�޷���16λ����	
UINT32	�޷���32λ����	
BOOL	�������ͣ�ȡֵΪTRUE��FALSE	
BYTE	�ֽ����ͣ��޷���8λ����	typedef UINT8 BYTE
CHAR	�ַ����ͣ��޷���8λ����	typedef UINT8 CHAR
SHORT	���������з���16λ	typedef INT16 SHORT
USHORT	�޷���16λ����	typedef UINT16 USHORT
LONG 	���������з���32λ����	typedef INT32 LONG
ULONG	���������޷���32λ����	typedef UINT32 ULONG
UINT	�޷���32λ����	typedef UINT32 UINT
WORD	�����ͣ��޷���16λ����	typedef UINT16 WORD
DWORD	˫�����ͣ��޷���32λ����	typedef UINT32 DWORD
FLAGS	��־���ͣ��޷���32λ����	typedef UINT32 FLAGS
LPSTR	8λ�ַ���ָ�룬����UTF8��ʽ�洢������	typedef CHAR * LPSTR
HANDLE 	�����ָ���������ݶ������ʼ��ַ	typedef  void * HANDLE
DEVHANDLE	�豸���	typedef HANDLE DEVHANDLE
HAPPLICATION	Ӧ�þ��	typedef HANDLE HAPPLICATION
HCONTAINER	�������	typedef HANDLE HCONTAINER
*/

#if 0

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

typedef char			INT8;
typedef short			INT16;
typedef int				INT32;
typedef unsigned char	UINT8;
typedef unsigned short	UINT16;
typedef unsigned int	UINT32;

typedef long				BOOL;

typedef	UINT8			BYTE;
typedef UINT8			CHAR;

typedef INT16			SHORT;
typedef UINT16			USHORT;
typedef INT32			LONG;
typedef UINT32			ULONG;
typedef UINT32			UINT;
typedef UINT16			WORD;
typedef UINT32			DWORD;
typedef UINT32			FLAGS;
typedef CHAR *			LPSTR;
typedef void *			HANDLE;
typedef HANDLE			DEVHANDLE;
typedef HANDLE			HAPPLICATION;
typedef HANDLE			HCONTAINER;

typedef struct Struct_Version{
	BYTE major;
	BYTE minor;
}VERSION;

typedef struct Struct_DEVINFO{
	VERSION		Version;
	CHAR		Manufacturer[64];
	CHAR		Issuer[64];
	CHAR		Label[32];
	CHAR		SerialNumber[32];
	VERSION		HWVersion;
	VERSION		FirmwareVersion;
	ULONG		AlgSymCap;
	ULONG		AlgAsymCap;
	ULONG		AlgHashCap;
	ULONG		DevAuthAlgId;
	ULONG		TotalSpace;
	ULONG		FreeSpace;
	BYTE  		Reserved[64];
}DEVINFO,*PDEVINFO;




#define SAR_OK							0x00000000	 //�ɹ�
#define SAR_FAIL						0x0A000001	 //ʧ��
#define SAR_UNKNOWNERR					0x0A000002	 //�쳣����
#define SAR_NOTSUPPORTYETERR			0x0A000003	 //��֧�ֵķ���
#define SAR_FILEERR						0x0A000004	 //�ļ���������
#define SAR_INVALIDHANDLEERR			0x0A000005	 //��Ч�ľ��
#define SAR_INVALIDPARAMERR				0x0A000006	 //��Ч�Ĳ���
#define SAR_READFILEERR					0x0A000007	 //���ļ�����
#define SAR_WRITEFILEERR				0x0A000008	 //д�ļ�����
#define SAR_NAMELENERR					0x0A000009	 //���Ƴ��ȴ���
#define SAR_KEYUSAGEERR					0x0A00000A	 //��Կ��;����
#define SAR_MODULUSLENERR				0x0A00000B	 //ģ�ĳ��ȴ���
#define SAR_NOTINITIALIZEERR			0x0A00000C	 //δ��ʼ��
#define SAR_OBJERR						0x0A00000D	 //�������
#define SAR_MEMORYERR					0x0A00000E	 //�ڴ����
#define SAR_TIMEOUTERR					0x0A00000F	 //��ʱ
#define SAR_INDATALENERR				0x0A000010	 //�������ݳ��ȴ���
#define SAR_INDATAERR					0x0A000011	 //�������ݴ���
#define SAR_GENRANDERR					0x0A000012	 //�������������
#define SAR_HASHOBJERR					0x0A000013	 //HASH�����
#define SAR_HASHERR						0x0A000014	 //HASH�������
#define SAR_GENRSAKEYERR				0x0A000015	 //����RSA��Կ��
#define SAR_RSAMODULUSLENERR			0x0A000016	 //RSA��Կģ������
#define SAR_CSPIMPRTPUBKEYERR			0x0A000017	 //CSP�����빫Կ����
#define SAR_RSAENCERR					0x0A000018	 //RSA���ܴ���
#define SAR_RSADECERR					0x0A000019	 //RSA���ܴ���
#define SAR_HASHNOTEQUALERR				0x0A00001A	 //HASHֵ�����
#define SAR_KEYNOTFOUNTERR				0x0A00001B	 //��Կδ����
#define SAR_CERTNOTFOUNTERR				0x0A00001C	 //֤��δ����
#define SAR_NOTEXPORTERR				0x0A00001D	 //����δ����
#define SAR_DECRYPTPADERR				0x0A00001E	 //����ʱ����������
#define SAR_MACLENERR					0x0A00001F	 //MAC���ȴ���
#define SAR_BUFFER_TOO_SMALL			0x0A000020	 //����������
#define SAR_KEYINFOTYPEERR				0x0A000021	 //��Կ���ʹ���
#define SAR_NOT_EVENTERR				0x0A000022	 //���¼�����
#define SAR_DEVICE_REMOVED				0x0A000023	 //�豸���Ƴ�
#define SAR_PIN_INCORRECT				0x0A000024	 //PIN����ȷ
#define SAR_PIN_LOCKED					0x0A000025	 //PIN������
#define SAR_PIN_INVALID					0x0A000026	 //PIN��Ч
#define SAR_PIN_LEN_RANGE				0x0A000027	 //PIN���ȴ���
#define SAR_USER_ALREADY_LOGGED_IN		0x0A000028	 //�û��Ѿ���¼
#define SAR_USER_PIN_NOT_INITIALIZED	0x0A000029	 //û�г�ʼ���û�����
#define SAR_USER_TYPE_INVALID			0x0A00002A	 //PIN���ʹ���
#define SAR_APPLICATION_NAME_INVALID	0x0A00002B	 //Ӧ��������Ч
#define SAR_APPLICATION_EXISTS			0x0A00002C	 //Ӧ���Ѿ�����
#define SAR_USER_NOT_LOGGED_IN			0x0A00002D	 //�û�û�е�¼
#define SAR_APPLICATION_NOT_EXISTS		0x0A00002E	 //Ӧ�ò�����
#define SAR_FILE_ALREADY_EXIST			0x0A00002F	 //�ļ��Ѿ�����
#define SAR_NO_ROOM						0x0A000030	 //�ռ䲻��
#define SAR_FILE_NOT_EXIST				0x0A000031	 //�ļ�������
#define SAR_REACH_MAX_CONTAINER_COUNT	0x0A000032	 //�Ѵﵽ���ɹ���������


#define SECURE_NEVER_ACCOUNT	0x00000000	//������
#define SECURE_ADM_ACCOUNT		0x00000001	//����ԱȨ��
#define SECURE_USER_ACCOUNT		0x00000010	//�û�Ȩ��
#define SECURE_ANYONE_ACCOUNT	0x000000FF	//�κ���



typedef struct  
{
	int id;
	char error[64];
}ErrorInfo;



typedef struct Struct_FILEATTRIBUTE{
	CHAR	FileName[32];
	ULONG	FileSize;
	ULONG	ReadRights;
	ULONG	WriteRights; 
} FILEATTRIBUTE, *PFILEATTRIBUTE;

#endif


void Init();


void Test_SKF_DevAuth();
void Test_SKF_ChangePIN();
void Test_SKF_VerifyPIN();
void Test_SKF_UnblockPIN();
void Test_SKF_ChangeDevAuthKey();
void Test_SKF_ClearSecueState();
void Test_SKF_GetPINInfo();


void Test_SKF_CreateApplication();
void Test_SKF_EnumApplication();
void Test_SKF_DeleteApplication();
//void Test_SKF_OpenApplication();
//void Test_SKF_CloseApplication();
void Test_SKF_OpenClose_Application();

void Test_SKF_CreateFile();
void Test_SKF_DeleteFile();
void Test_SKF_ReadFile();
void Test_SKF_WriteFile();
void Test_SKF_EnumFiles();
void Test_SKF_GetFileInfo();



//==========================//
void Test_SKF_EnumDev();
//void Test_SKF_ConnectDev();
//void Test_SKF_DisConnectDev();
void Test_SKF_ConnectDev_DisconnectDev();
void Test_SKF_GetDevState();
void Test_SKF_GetDevInfo();
void Test_SKF_SetLabel();
void Test_SKF_LockDev();
void Test_SKF_UnlockDev();
void Test_SKF_Transmit();

void Test_SKF_CreateContainer();
void Test_SKF_DeleteContainer();
void Test_SKF_EnumContainer();
//void Test_SKF_OpenContainer();
//void Test_SKF_CloseContainer();
void Test_SKF_OpenContainer_CloseContainer();
void Test_SKF_GetContianerType();
void Test_SKF_ImportCertificate();
void Test_SKF_ExportCertificate();

void Test_SKF_GenRSAKeyPair();
void Test_SKF_GenECCKeyPair();
void Test_SKF_SetSymmKey();
void Test_SKF_RSAExportSessionKey();
void Test_SKF_ECCExportSessionKey();


//=============================//
void Test_Flow_EnumOpenCloseDev();
void Test_Flow_GetDevInfo();
void Test_Flow_EnumApp();
void Test_Flow_OpenSM2AppCont();
void Test_Flow_OpenRSA2048appCont();
void Test_Flow_OpenRSA1024appCont();
void Test_Flow_VerifyPIN();
void Test_Flow_ChangeUserPIN();
void Test_Flow_ExportPublickey();
void Test_Flow_ExportCertificate();
void Test_Flow_RsaSignData();
void Test_Flow_RSAVerify();
void Test_Flow_ECCSignData();
void Test_Flow_ECCVerify();
void Test_Flow_ExtRSAOperatDecrypt();
void Test_Flow_ExtECCEncryptDecrypt();
void Test_Flow_ExitTest();

void Test_Flow_EncryptwithSymKey();
void Test_Flow_DecryptwithSymKey();
#endif

