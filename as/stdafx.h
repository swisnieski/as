	// AS  silo-load-out
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <time.h>
#include "logrec.h"
//#include "DbaseT.h"
#include <queue>

using namespace System;
using namespace System::Net;
using namespace System::Collections::Generic;

#define VERSION "4.1.2"

#define NEW
//#define ASCII
//#define PRINT_SER

///////////////////////////////////////////////////////////////////////////////
namespace As
{
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned __int32  ulong;
typedef unsigned __int64  ulong64;

//#define min(a, b)  (((a) > (b)) ? (b) : (a)) 
#define max(a, b)  (((a) > (b)) ? (a) : (b)) 

#define SPLASH		4		//  4 sec
#define PATH_LEN	80
#define NAME_LEN	32
#define PRINT_LEN	6800

#define UPPER_MAX	11.9	// upper scale max load
#define BOTTOM_MAX	45		//DC 3.2.4 Change from 23.9 // bottom scale max load
#define BOTTOM_MAXL4 145	//DC 4.0.0

#define LOAD_MAX	24		// free fall and adapt load range
#define SAMPLE_NBR  8		// auto fall and adapt samples
#define SCALE_MSG	18		//DC 3.2.0

#define TEXT_FIELDS  40		//DC 3.2.7
#define TEXT_LEN     90		//DC 3.2.7
#define SILOS		 12				//DC 3.3.0 total silo
#define	MIN_WEIGHT	 0		//DC 4.0.0 min target Rail cart weight
#define MAX_WEIGHT   120	//DC 4.0.0 max target Rail cart weight
#define MIN_T_WEIGHT 0		//DC 4.0.0 min target truck weight
#define MAX_T_WEIGHT 45		//DC 4.0.0 max target truck weight
#define SCL_MIN		 0		//DC 4.0.0 min analogy output point raw value
#define SCL_MAX      4095	//DC 4.0.0 max analogy output point raw value

//DC 4.1.0
#define HDR_LEN		6					// remote message header length
#define CMD_LEN		12
#define CMD_LEN11	11					//DC
#define LIMIT		4
#define REM_CNT     500					// wait time for remote command * 100msec = 50 sec
#define REM_JOBS    25					// max size of remote jobs list

typedef enum		
{ A_PROD
, A_SIM			// 1
, A_DEMO		// 2
, A_REMOTE		//DC 4.1.0 3
} AS_TYPE;

typedef enum		
{ I_SER
, I_TP			// 3
} IF_TYPE;

#ifndef NEW
// upper scale IO layout
typedef enum
{ O_NONE
, O_DROP1	
, O_DISCH1  
, O_LIGHT1  = 0x0004
, O_CLEARA  = 0x0007
, O_DROP2	= 0x0008
, O_DISCH2  = 0x0010
, O_LIGHT2  = 0x0020
, O_CLEARB  = 0x0038
, O_DROP3	= 0x0040
, O_DISCH3  = 0x0080
, O_LIGHT3  = 0x0100
, O_CLEARC  = 0x01c0
, O_SAFE1   = 0x0200
, I_FILL1   = 0x0400			
, I_OPEN1   = 0x0800
, I_FILL2   = 0x1000
, I_OPEN2   = 0x2000
, I_FILL3   = 0x4000
, I_OPEN3   = 0x8000
} OPTO_TOP;				


// bottom scale IO layout
typedef enum
{ P_NONE
, P_DROP1	= 0x0001
, P_DROP2   = 0x0002
, P_DROP3   = 0x0004
, P_LIGHTA  = 0x0008
, P_CLRDRP_A  = 0x000f
, P_DROP4	= 0x0010
, P_DROP5   = 0x0020
, P_DROP6   = 0x0040
, P_LIGHTB  = 0x0080
, P_CLRDRP_B  = 0x00f0
, P_SPARE1  = 0x0100
, P_SPARE2  = 0x0200
, J_FILL1   = 0x0400			
, J_FILL2   = 0x0800
, J_FILL3   = 0x1000
, J_FILL4   = 0x2000
, J_FILL5   = 0x4000
, J_FILL6   = 0x8000
// TBD
, P_DROP7	= 0x00010000
, P_DROP8   = 0x00020000
, P_DROP9   = 0x00040000
, P_LIGHTC  = 0x00080000
, P_CLRDRP_C  = 0x000f0000
, J_FILL7   = 0x00100000
, J_FILL8   = 0x00200000
, J_FILL9   = 0x00400000
} OPTO_BOT;		
#else
typedef enum
{ O_NONE
, O_DROP1				// lane A
, O_DISCH1  = 0x0002
, O_LIGHT1  = 0x0004
, O_SAFE1   = 0x0008
, O_CLEARA  = 0x0007
, O_CLEARAA = 0x000f

, O_DROP2	= 0x0010	// lane B
, O_DISCH2  = 0x0020
, O_LIGHT2  = 0x0040
, O_SAFE2   = 0x0080
, O_CLEARB  = 0x0070
, O_CLEARBB = 0x00f0

, O_DROP3	= 0x0100	// lane C
, O_DISCH3  = 0x0200
, O_LIGHT3  = 0x0400
, O_SAFE3   = 0x0800
, O_CLEARC  = 0x0700
, O_CLEARCC = 0x0f00

, O_DROP4	= 0x1000	//DC 3.3.0 lane D
, O_DISCH4  = 0x2000
, O_LIGHT4  = 0x4000
, O_SAFE4   = 0x8000
, O_CLEARD  = 0x7000
, O_CLEARDD = 0xf000

} OPTO_TOPO;	

typedef enum
{ I_NONE
, I_FILL1   		
, I_OPEN1   = 0x02
, I_FILL2   = 0x04
, I_OPEN2   = 0x08
, I_FILL3   = 0x10
, I_OPEN3   = 0x20
, I_FILL4   = 0x40		//DC 3.3.0
, I_OPEN4   = 0x80
} OPTO_TOPI;				

// bottom scale IO layout
typedef enum
{ P_NONE
, P_DROP1	= 0x00000001
, P_DROP2   = 0x00000002
, P_DROP3   = 0x00000004
, P_LIGHTA  = 0x00000008
, P_SAFE1	= 0x00000010
, P_SAFE2   = 0x00000020
, P_SAFE3   = 0x00000040
, P_SPAREA  = 0x00000080
, P_CLRDRP_A =0x0000000f		// clear drops
, P_CLRSV_A = 0x000000f0		// clear safe valves
, P_CLEAR_A = 0x000000ff		// clear all

, P_DROP4	= 0x00000100
, P_DROP5   = 0x00000200
, P_DROP6   = 0x00000400
, P_LIGHTB  = 0x00000800
, P_SAFE4	= 0x00001000
, P_SAFE5   = 0x00002000
, P_SAFE6   = 0x00004000
, P_SPAREB  = 0x00008000
, P_CLRDRP_B =0x00000f00
, P_CLRSV_B = 0x0000f000
, P_CLEAR_B = 0x0000ff00

, P_DROP7	= 0x00010000
, P_DROP8   = 0x00020000
, P_DROP9   = 0x00040000
, P_LIGHTC  = 0x00080000
, P_SAFE7	= 0x00100000
, P_SAFE8   = 0x00200000
, P_SAFE9   = 0x00400000
, P_SPAREC  = 0x00800000
, P_CLRDRP_C =0x000f0000
, P_CLRSV_C = 0x00f00000
, P_CLEAR_C = 0x00ff0000

, P_DROP10	= 0x01000000	//DC 3.3.0
, P_DROP11   = 0x02000000
, P_DROP12   = 0x04000000
, P_LIGHTD  = 0x08000000
, P_SAFE10	= 0x10000000
, P_SAFE11   = 0x20000000
, P_SAFE12   = 0x40000000
, P_SPARED  = 0x80000000
, P_CLRDRP_D =0x0f000000
, P_CLRSV_D = 0xf0000000
, P_CLEAR_D = 0xff000000
} OPTO_OUT;		

typedef enum
{ J_NONE
, J_FILL1   
, J_FILL2   
, J_FILL3   = 0x004
, J_FILL4   = 0x008
, J_FILL5   = 0x010
, J_FILL6   = 0x020
, J_FILL7   = 0x040
, J_FILL8   = 0x080
, J_FILL9   = 0x100
, J_FILL10   = 0x200	//DC 3.3.0
, J_FILL11   = 0x400
, J_FILL12   = 0x800
} OPTO_INP;

//DC 4.1.0 Remote
typedef enum
	{ CL_NONE
	// receive data commands
	, CL_LOGIN			// 1
	, CL_INI			// 2			
	, CL_JOB			// 4			
	, CL_OLD			// 5
	, CL_CBC
	, CL_TRUCKS			// 6
	, CL_STAT			// 7
	, CL_JOBS_NEW		// 10
	, CL_JOBS_OLD		// 11
	, CL_LOG			// 20
	, CL_LOG4			//
	, CL_KEY			//
	, CL_FLOW			//
	, CL_MAN			// 21
	, CL_INV			// 22
	, CL_GRA			// 23
	, CL_YARD			// 24
	, CL_MATS			// 25
	, CL_JOB_ARMED		// 26
	, CL_JOBXS			// 27
	, CL_HAULERS		// 28
	, CL_CLIMIT			// 29
	, CL_ABORT4			
	// send data commands
	, CL_SJOB4	
	, CL_SJOB			// 30
	, CL_STRUCK			// 31
	, CL_SMIX			// 32
	, CL_SADX			// 33
	, CL_SMOIST			// 34
	, CL_SARMED			// 35
	, CL_SJOBX			// 36
	, CL_SCOLOR			// 37
	, CL_SINV			// 38
	, CL_SADP			// 39
	, CL_SHAUL			// 40
	} CLINK_CMD;

typedef enum
	{ K_NONE			
	, K_WAT				// MANUAL OFF
	, K_DIS				// MANUAL ON
	, K_RUN				// BLOWER
	, K_HOLD
	, K_ABORT
	, K_DBL				// mixer
	, K_TILT			// mixer
	, K_RIGHT			// mixer
	, K_DBL2			// mixer2
	, K_TILT2			// mixer2
	, K_RIGHT2			// mixer2
	, K_WET				// diverter
	, K_DRY				// diverter
	, K_HOP_DIS			// hopper
	, K_HOP_HOLD		// hopper
//
	, K_SBAR4			// Silo 4 Bar
	, K_NEXT4			// Silo 4 Next
	, K_RESET4			// Silo 4 Reset
	, K_READY4			// Silo 4 Ready
	, K_HOLD4			// Silo 4 HOLD
	, K_VOIDYES4		// Silo 4 VOID Yes
	, K_VOIDNO4			// Silo 4 VOID No
	, K_SJOB4			// Silo 4 Select Job
	, K_PRINT4			// Silo 4 Print Only
	, K_RPRINT4			// Silo 4 R-Print 
	, K_NEXTCONYES4		// Silo 4 Continue Yes
	, K_NEXTCONNO4		// Silo 4 Continue No
	, K_RESETTON4		// Silo 4 Reset Tonnage

	, K_SOUND0
	, K_FW1			
	, K_FW0
	, K_FRUN1			
	, K_FRUN0
	, K_FDIS1			
	, K_FDIS0
	, K_LOOP1
	, K_LOOP0
	, K_WARN3
	, K_WARN2
	, K_WARN1
	, K_WARN0
	, K_REMOVE			// batch form
	, K_DELETE			// batch form

	, K_BELTON
	, K_BELTOFF
	, K_HORN
	, K_HORNEND
	, K_BOOTDN
	, K_BOOTUP
	, K_WBOOTDN
	, K_WBOOTUP
	, K_WBOOTDN2	//DC 7.0.20
	, K_WBOOTUP2	//DC 7.0.20
	} CLINK_KEY;		// remote keys


#endif

typedef struct
	{
		int		nOffs;
		char    acText[TEXT_LEN];
		char    cParms;
	} TEXT;

typedef struct 
{
	int nLineLen;
	int nLineNum;
	int nPlantNum;
	int nSiloNum;
	int nLaneNum;	//DC 4.1.2
	int nTicket;
	int nTruck;
	int nDrops;
	int nCustomer;
	int nMixCode;
	int nTarget;
	int nLoad;
	int nTruckTare;
	int nGross;
	int nDate;
	int nTime;
	int nTax;
	int nUnit;
	int nMixPrice;
	int nTotal;
	int nDelAddr1;
	int nDelAddr2;
	int nDelInst1;
	int nDelInst2;
	int nDelInst3;	
	int nDelInst4;	
	int  nMixDesc;
	int  nZone;
	int  nProjCode;
	int  nLotNum;
	int  nPoNum;
	int	 nLoadsDlvrd;
	int  nJobName;
	int  nOrderNum;
	int  nOrderNumTotal;
	int  nCumQty;
	int  nSubtotal;
	int  nCustCode;
	int  nOrderId;
	int  nLoadTax;
	int  nGrandTotal;
	int  nDriverName;		//DC 4.0.7 Driver Name
	//---------------------TN to LB
	int nGrossTNtoLB;
	int nTruckTareTNtoLB;
	int nLoadTNtoLB;
	int nOrderNumTotalTNtoLB;
	//---------------------extra
	int nExtraLine;		// extra offsets
	int nExtraMax;
	int nExLoad;
	int nExName;
	int nExDesc;
	int nExUnit;
	int nExPrice;
	int nExAmount;
	int nExOrder;
	int nExCum;
	int nExLong;
	int nExPriceUm;
	
	TEXT asText[TEXT_FIELDS];	//DC 3.2.7

} TIC;

typedef struct
{
	char   acCom[NAME_LEN];
	int    nBaud;
	int    nClock;
	double dValue;
	double fTolerance;
    double dFlow;
	char   acData[20];
	char   cGo;
	bool   bSerial;
	bool   bSample;
	bool   bSerTP;			//DC 3.2.0
	int	   nFlow;			//DC 3.2.0
	int    nErrCnt;			//DC 3.2.0
	clock_t  tSample;		//DC 3.2.0	
} SCALE;

// INV ------------------------------------------------------------------------
typedef struct
{
	double fFall;
	double afFall[SAMPLE_NBR];
	int    nIdx;
} FALL;

typedef struct
{
	double fAdapt;
	double afAdapt[SAMPLE_NBR];
	int    nIdx;
} ADAPT;

typedef struct
{
	double fTon1;		// tonnage
	double fTon2;
	double fTon3;
	double fTon4;		//DC 3.3.0

	double fInv1;		// inventory
	double fInv2;
	double fInv3;	
	double fInv4;		// inventory
	double fInv5;
	double fInv6;	
	double fInv7;		// inventory
	double fInv8;
	double fInv9;
	double fInv10;		//DC 3.3.0 inventory
	double fInv11;
	double fInv12;

	FALL   asFall1[LOAD_MAX];		// auto free fall data
	FALL   asFall2[LOAD_MAX];
	FALL   asFall3[LOAD_MAX];
	FALL   asFall4[LOAD_MAX];
	FALL   asFall5[LOAD_MAX];
	FALL   asFall6[LOAD_MAX];
	FALL   asFall7[LOAD_MAX];
	FALL   asFall8[LOAD_MAX];
	FALL   asFall9[LOAD_MAX];
	FALL   asFall10[LOAD_MAX];		//DC 3.3.0
	FALL   asFall11[LOAD_MAX];		//DC 3.3.0
	FALL   asFall12[LOAD_MAX];		//DC 3.3.0

	ADAPT   asAdapt1[LOAD_MAX];		// adaptive data
	ADAPT   asAdapt2[LOAD_MAX];
	ADAPT   asAdapt3[LOAD_MAX];
	ADAPT   asAdapt4[LOAD_MAX];
	ADAPT   asAdapt5[LOAD_MAX];
	ADAPT   asAdapt6[LOAD_MAX];
	ADAPT   asAdapt7[LOAD_MAX];
	ADAPT   asAdapt8[LOAD_MAX];
	ADAPT   asAdapt9[LOAD_MAX];
	ADAPT   asAdapt10[LOAD_MAX];	//DC 3.3.0
	ADAPT   asAdapt11[LOAD_MAX];	//DC 3.3.0
	ADAPT   asAdapt12[LOAD_MAX];	//DC 3.3.0

	bool   bAutoFall1;
	bool   bAdapt1;
	bool   bJog1;
	bool   bAutoDisch1;

	bool   bAutoFall2;
	bool   bAdapt2;
	bool   bJog2;
	bool   bAutoDisch2;

	bool   bAutoFall3;
	bool   bAdapt3;
	bool   bJog3;
	bool   bAutoDisch3;

	bool   bAutoFall4;		//DC 3.3.0
	bool   bAdapt4;
	bool   bJog4;
	bool   bAutoDisch4;

	int	   nLastTicket;

} INV;

//DC 3.3.0 silo --------------------------------------------------------------
typedef struct
{
	char	acMat[11];		// material name
	char	acProduct[11];	//DC 4.0.2 product name
	bool	bUsed;			// used
	int		nFlowRatePct1;	// flow rate percentage 1
	int		nFlowRatePct2;	// flow rate percentage 2
	int		nFlowRatePct3;	// flow rate percentage 3
	int		nFlowRatePct4;	// flow rate percentage 4
	int		nDelayPct;		// delay percentage
	int		nDelayTime;		// delay time
	int		nFlowRate1O;	// flow rate 1 Output
	int 	nFlowRate2O;	// flow rate 2 Output
	int 	nFlowRate3O;	// flow rate 3 Output
	int		nFlowRate4O;	// flow rate 4 Output
	int 	nDoneI;			// Done Input
	int 	nReadyO;		// when the ready bottom click
	int 	nDropO;			// when the drop bottom click
	int		nDoneO;			// when load complete
	int		nHoldO;			// on hold
	int		nAddO;			// add more
	int		nDropReadyI;	// ready to drop
	int		nHoldI;			// hold Input
	double  fFall;			// Free Fall
	int		nSiloNum;		// Silo Number
	int		nSiloJog;		// Silo Add Jog Pulse Time in 100msec
	double  dAddTol;		// Silo Add Tolerance

	ulong64	uFlowRate1O;	// flow rate 1 Output
	ulong64	uFlowRate2O;	// flow rate 2 Output
	ulong64	uFlowRate3O;	// flow rate 3 Output
	ulong64	uFlowRate4O;	// flow rate 4 Output
	ulong64	uDoneI;			// Done Input
	ulong64	uReadyO;		// when the ready bottom click
	ulong64	uDropO;			// when the drop bottom click
	ulong64 uDoneO;			// when load complete
	ulong64 uHoldO;			// on hold
	ulong64 uAddO;			// add more
	ulong64 uDropReadyI;	// ready to drop
	ulong64 uHoldI;			// hold Input
} SILO;

// INI ------------------------------------------------------------------------
typedef struct
{
	// operational section
	SILO	asSilos[SILOS];
	INV     sInv;

	LOG_REC sLog1;
	LOG_REC sLog2;
	LOG_REC sLog3;
	LOG_REC sLog4;				//DC 3.3.0
	
	SCALE sScale1;
	SCALE sScale2;
	SCALE sScale3;
	SCALE sScale4;				//DC 3.3.0

	ulong64	nInpMask;			// bitmap of mixed IO inputs
	ulong64	nMask;				// assigned Output bit map
	ulong64 nMask64;			//assign outputs bit map > 63

	ulong	nReady1O;			//DC 3.2.0 when the ready bottom click
	ulong   nDrop1O;			//DC 3.2.0 when the drop bottom click
	ulong	nReady2O;			//DC 3.2.0 when the ready bottom click
	ulong   nDrop2O;			//DC 3.2.0 when the drop bottom click
	ulong	nReady3O;			//DC 3.2.0 when the ready bottom click
	ulong   nDrop3O;			//DC 3.2.0 when the drop bottom click
	ulong	nReady4O;			//DC 3.3.0 when the ready bottom click
	ulong   nDrop4O;			//DC 3.3.0 when the drop bottom click

	ulong64  nRpoints;			//DC 4.0.0	uint
	ulong64  nWpoints;			//DC 4.0.0	uint
	ulong64  uBitWiseO[19];		//DC 4.0.0 Target Binary
	ulong64  uBitCheckI[19];	//DC 4.0.0 Target Bit Check
	ulong64  uSendTargetO;		//DC 4.0.0 Send output
	ulong64  uReceivedTargetI;	//DC 4.0.0 Received Input
	ulong64  uKeepAliveO;		//DC 4.0.0 send to PDM KeepALive
	ulong64  uKeepAliveI;		//DC 4.0.0 received from PDM KeepALive
	ulong64  uSiloBitO[4];		//DC 4.0.0 Silo Bits
	ulong64  uSiloBitCheckI[4];	//DC 4.0.0 Silo Bits Check
	ulong64  uLaneTareI[4];		//DC 4.0.1 Lane Tare Input 

	char cOptoInputs;			//DC 4.0.0
	char cOptoAnalog;			//DC 4.0.0
	char cOptoSlot;				//DC 4.0.0

	int  nUlinkOk;
	int  nOptoOk;
	int  nDbaseOk;
	int	 nSafeTime;
	int  nRlinkOk;				//DC 4.1.0
	
	// configuration section
	FILE *pfDbe;
	FILE *pfDbs;					//DC 4.1.1
	TIC	  sTic;
//	char  acPath[PATH_LEN];

	int  nPlantNum1;
	int  nPlantNum2;
	int  nNumLanes;
	int  nL1SilosNum;
	int  nL2SilosNum;
	int  nL3SilosNum;
	int	 nL4SilosNum;		//DC 3.3.0
	int  nUlinkPort;
	int  nHornTime;
	int  nScaleSettle;
	int  nScaleDisSettle;
//	int  nScaleAdd;
	int  nScaleIdle;
	int  nRlinkPort;		//DC 4.1.0
	int  nOldDone4;			//DC 4.1.0
	
	double dAddQty;
	double fTarTolAbs;				
	double fTarTolPerc;	

	double fTaxRate;				
	double fTonPrice;				
	double fDropMax;
	double fDropMaxL2;			//DC 4.1.2
	double fDropMaxL3;			//DC 4.1.2
	double fDropMaxL4;			//DC 4.0.0
	double fTopScaleMax;
	double fBotScaleMax;
	double fBotScaleMaxL2;		//DC 4.1.2
	double fBotScaleMaxL3;		//DC 4.1.2
	double fBotScaleMaxL4;		//DC 4.0.0
	double fBotScaleTruck;

	double afManFall1[LOAD_MAX];
	double afManFall2[LOAD_MAX];
	double afManFall3[LOAD_MAX];
	double afManFall4[LOAD_MAX];
	double afManFall5[LOAD_MAX];
	double afManFall6[LOAD_MAX];
	double afManFall7[LOAD_MAX];
	double afManFall8[LOAD_MAX];
	double afManFall9[LOAD_MAX];
	double afManFall10[LOAD_MAX];	//DC 3.3.0
	double afManFall11[LOAD_MAX];	//DC 3.3.0
	double afManFall12[LOAD_MAX];	//DC 3.3.0
	
	double afAdapt1[LOAD_MAX];
	double afAdapt2[LOAD_MAX];
	double afAdapt3[LOAD_MAX];
	double afAdapt4[LOAD_MAX];
	double afAdapt5[LOAD_MAX];
	double afAdapt6[LOAD_MAX];
	double afAdapt7[LOAD_MAX];
	double afAdapt8[LOAD_MAX];
	double afAdapt9[LOAD_MAX];
	double afAdapt10[LOAD_MAX];		//DC 3.3.0
	double afAdapt11[LOAD_MAX];		//DC 3.3.0
	double afAdapt12[LOAD_MAX];		//DC 3.3.0
	
	double fSiloMax1;
	double fSiloMax2;
	double fSiloMax3;
	double fSiloMax4;
	double fSiloMax5;
	double fSiloMax6;
	double fSiloMax7;
	double fSiloMax8;
	double fSiloMax9;
	double fSiloMax10;				//DC 3.3.0
	double fSiloMax11;				//DC 3.3.0
	double fSiloMax12;				//DC 3.3.0

	double fSiloFill1;
	double fSiloFill2;
	double fSiloFill3;
	double fSiloFill4;
	double fSiloFill5;
	double fSiloFill6;
	double fSiloFill7;
	double fSiloFill8;
	double fSiloFill9;
	double fSiloFill10;				//DC 3.3.0
	double fSiloFill11;				//DC 3.3.0
	double fSiloFill12;				//DC 3.3.0
	
	int nSiloJog1;
	int nSiloJog2;
	int nSiloJog3;
	int nSiloJog4;
	int nSiloJog5;
	int nSiloJog6;
	int nSiloJog7;
	int nSiloJog8;
	int nSiloJog9;
	int nSiloJog10;					//DC 3.3.0
	int nSiloJog11;					//DC 3.3.0
	int nSiloJog12;					//DC 3.3.0

	//DC 4.1.0
	int		nTickets1;	// # of new tickets
	int		nTickets2;
	int		nTickets3;
	int		nTickets4;	//DC 3.3.0

	int     nTicketCopy4;
	int		nDone4;

	int  nPrinterBaud;
	int  nOptoBaud;
	int  nOptoDelay;
	int  nFirstTicket;

	char cSclFrame;
	char cSclSchar;
	int  nSclLen;
	int  nSclSign;
	int  nScl1000;
	int  nScl100;
	int  nScl10;
	int  nScl1;
	int  nScl01;
	int  nScl001;
	int  nScaleRedLo;
	int  nScaleRedHi;
	int	 nTruckMin;			//DC 4.0.0
	int  nTruckMax;			//DC 4.0.0
	int  nCartMin;			//DC 4.0.0
	int  nCartMax;			//DC 4.0.0
	double  nSclOutEU[4];	//DC 4.0.0
	int  nBitWise[19];		//DC 4.0.0
	int  nBinaryNumber[19];	//DC 4.0.0
	int  nBitCheckI[19];	//DC 4.0.0
	int  nBinaryNumCheck[19]; //DC 4.0.0
	int  nSendTargetO;		//DC 4.0.0
	int  nReceivedTargetI;	//DC 4.0.0
	int  nKeepAliveO;		//DC 4.0.0
	int  nKeepAliveI;		//DC 4.0.0
	int  nSiloBit[4];		//DC 4.0.0
	int  nSiloBitNum[4];	//DC 4.0.0
	int  nSiloBitCheck[4];	//DC 4.0.0
	int  nKeepOnTime;		//DC 4.0.0
	int  nKeepOffTime;		//DC 4.0.0
	int  nLaneTareI[4];		//DC 4.0.1

	bool bSaveInv;
	bool bPrinterOk1;
	bool bPrinterOk2;
	bool bPrinterOk3;
	bool bPrinterOk4;		//DC 4.0.0
	bool b2ndPrinterOk1;	//DC 4.0.2
	bool b2ndPrinterOk2;	//DC 4.0.2
	bool b2ndPrinterOk3;	//DC 4.0.2
	bool b2ndPrinterOk4;	//DC 4.0.2
	bool bBotScale;
	bool bDailyLog;
	bool bTickAddress;
	bool bTest;
	bool bSafeJob;
	bool bRevPlant;
	bool bUseTrkMax;		//DC 3.2.0
	bool bDisableManual;	//DC 3.2.0
	bool bScaleInLB;		//DC 3.2.0
	bool bPdmPlc;			//DC 4.0.0
	bool bHold1;			//DC 4.0.0
	bool bHold2;			//DC 4.0.0
	bool bHold3;			//DC 4.0.0
	bool bHold4;			//DC 4.0.0
	bool bAutoAdd;			//DC 4.0.0
	bool bSendTarget;		//DC 4.0.0
	bool bSendBitWise;		//DC 4.0.0
	bool bDisableInv;		//DC 4.0.1
	bool bData;				//DC 4.1.0 run as demo or data

} INI;

public ref struct PrintQ
{
	LOG_REC* psLog;
	//LOG_REC11* psLog11;
	System::Collections::Generic::Queue<String^>^ qRep;
	String^ stTic;		// whole ticket
	String^ stTop;		// top only
	String^ stBot;		// bot only
	String^ stDest;		// for mail only
	bool		bReprint;
	bool		bOldLog11;	//DC 7.2.0 Print Old Log2
	//PRINT_TYPE	eType;
};





public ref struct Dbase
	{
		long       nTicket;
		int	       nPlant;
		double     fGross;
		double     fTare;
		char       cUnit0;
		char       cUnit1;
		bool       bVoid;
		int		   nRetry;
		String^	   pstCustCode;
		String^    pstTruck;			//DC 4.1.1
	};

#pragma region JOB
	//-------------------------------------------------------------------------
	[Serializable]
	public ref struct Job
	{
	public: Job(void)
		{
		}
	public: Job(Job^ pJob)
	{
		nnPlant = pJob->nnPlant;
	}

	private:
		long long ttTime;
		long      nnLogIdx;
		int		nnPlant;
		int     nnSilo;
		int     nnTicket;
		double  ffGross;		//DC 4.1.0
		double  ffTare;			//DC 4.1.0
		double  ffLoad;
		char   ccStatus;
		String^	pstCustomer;
		String^	pstStatus;
		String^ pstMaterial;	//DC 4.0.1
		String^ pstTruck;		//DC 4.0.1
		String^ pstLane;		//DC 4.1.2
		String^ pstSilo;		//DC 4.1.2
		int		nnCopy;			//DC 4.0.3

	public:
		property long long tTime
		{
			// This is a property 
			long long get()
			{
				return this->ttTime;
			}
			void set( long long value )
			{
				this->ttTime = value;
			}
		}
		property long nLogIdx
		{
			// This is a property 
			long get()
			{
				return this->nnLogIdx;
			}
			void set( long value )
			{
				this->nnLogIdx = value;
			}
		}
		property int nTicket
		{
			// This is a property 
			int get()
			{
				return this->nnTicket;
			}
			void set( int value )
			{
				this->nnTicket = value;
			}
		}
		property double fGross
		{
			// This is a property 
			double get()
			{
				return this->ffGross;
			}
			void set( double value )
			{
				this->ffGross = value;
			}
		}
		property double fTare
		{
			// This is a property 
			double get()
			{
				return this->ffTare;
			}
			void set( double value )
			{
				this->ffTare = value;
			}
		}
		property double fLoad
		{
			// This is a property 
			double get()
			{
				return this->ffLoad;
			}
			void set( double value )
			{
				this->ffLoad = value;
			}
		}
		property int nPlant
		{
			// This is a property 
			int get()
			{
				return this->nnPlant;
			}
			void set( int value )
			{
				this->nnPlant = value;
			}
		}
		property int nSilo
		{
			// This is a property 
			int get()
			{
				return this->nnSilo;
			}
			void set( int value )
			{
				this->nnSilo = value;
			}
		}

		property uchar eStatus
		{
			// This is a property 
			uchar get()
			{
				return this->ccStatus;
			}
			void set( uchar value )
			{
				this->ccStatus = value;
			}
		}

		property String^ stCustomer
		{
			// This is a property 
			String^ get()
			{
				return this->pstCustomer;
			}
			void set( String^ value )
			{
				this->pstCustomer = value;
			}
		}
		property String^ stStatus
		{
			// This is a property 
			String^ get()
			{
				return this->pstStatus;
			}
			void set( String^ value )
			{
				this->pstStatus = value;
			}
		}
		//DC 4.0.1
		property String^ stMaterial
		{
			// This is a property 
			String^ get()
			{
				return this->pstMaterial;
			}
			void set( String^ value )
			{
				this->pstMaterial = value;
			}
		}
		//DC 4.0.1
		property String^ stTruck
		{
			// This is a property 
			String^ get()
			{
				return this->pstTruck;
			}
			void set( String^ value )
			{
				this->pstTruck = value;
			}
		}
		//DC 4.1.2
		property String^ stLane
		{
			// This is a property 
			String^ get()
			{
				return this->pstLane;
			}
			void set( String^ value )
			{
				this->pstLane = value;
			}
		}
		//DC 4.1.2
		property String^ stSilo
		{
			// This is a property 
			String^ get()
			{
				return this->pstSilo;
			}
			void set( String^ value )
			{
				this->pstSilo = value;
			}
		}
		property String^ stTime
		{
			// This is a property 
			String^ get()
			{
				return (DateTime::FromBinary(this->ttTime)).ToString("MM/dd hh:mm");
//								pJob->stTime = pDate->ToShortDateString();

			}
		}
		//DC 4.0.3
		property int nCopy
		{
			// This is a property 
			int get()
			{
				return this->nnCopy;
			}
			void set( int value )
			{
				this->nnCopy = value;
			}
		}
		
	};

#pragma endregion

	//-------------------------------------------------------------------------
public ref struct Fall
	{
	private:
		int        nnLoad;
		double     ffMan;
		double     ffAuto;
		double     ffAdapt;

	public:
		property int nLoad
		{
			// This is a property 
			int get()
			{
				return this->nnLoad;
			}
			void set( int value )
			{
				this->nnLoad = value;
			}
		}
		property double dMan
		{
			// This is a property 
			double get()
			{
				return this->ffMan;
			}
			void set( double value )
			{
				this->ffMan = value;
			}
		}
		property double dAuto
		{
			// This is a property 
			double get()
			{
				return this->ffAuto;
			}
			void set( double value )
			{
				this->ffAuto = value;
			}
		}		
		
		property double dAdapt
		{
			// This is a property 
			double get()
			{
				return this->ffAdapt;
			}
			void set( double value )
			{
				this->ffAdapt = value;
			}
		}
	};
//----------------------------------------------------------
public ref struct Rem
	{
	private:
		String^		Name;
		IPAddress^	Ip;
		int			Port;

	public:	
		// This is a property 
		property String^ stName
		{
			String^  get()
			{
				return this->Name;
			}
			void set(String^   value )
			{
				this->Name = value;
			}
		}
		
		// This is a property 
		property IPAddress^ pIp
		{
			IPAddress^ get()
			{
				return this->Ip;
			}
			void set(IPAddress^ value )
			{
				this->Ip = value;
			}
		}
		// This is a property 
		property int nPort
		{
			int get()
			{
				return this->Port;
			}
			void set( int value )
			{
				this->Port = value;
			}
		}
	};

#pragma region TRUCK
	//-managed--------------------------------------------------------------------
	[Serializable]
	public ref class Truck
	{
	public: Truck(void)
		{
		}

	private:
		int			nnTruck;
		String^		pstName;
		int			nnRate;
		int			nnCapacity;

	public:
		/*
		property int nTruck
		{
			// This is a property 
			int get()
			{
				return this->nnTruck;
			}

			void set( int value )
			{
				this->nnTruck = value;
			}
		}
		*/
		property String^ stName
		{
			// This is a property 
			String^ get()
			{
				return this->pstName;
			}

			void set( String^ value )
			{
				this->pstName = value;
			}
		}
		property int nRate
		{
			// This is a property 
			int get()
			{
				return this->nnRate;
			}

			void set( int value )
			{
				this->nnRate = value;
			}
		}		
		property int nCapacity
		{
			// This is a property 
			int get()
			{
				return this->nnCapacity;
			}

			void set( int value )
			{
				this->nnCapacity = value;
			}
		}		
	};

#pragma endregion

//DC 3.3.0
#pragma region CFG
	// - managed----------------------------
	public ref struct Cfg
	{
	private:
		String^ pstLbl;
		String^ pstProduct;		//DC 4.0.2
		bool	bbUsed;
		int		nnFlowRatePct1;
		int		nnFlowRatePct2;
		int		nnFlowRatePct3;
		int		nnFlowRatePct4;
		int		nnDelayPct;		// delay percentage
		int		nnDelayTime;		// delay time
		int		nnFlowRate1O;	// flow rate 1 Output
		int 	nnFlowRate2O;	// flow rate 2 Output
		int 	nnFlowRate3O;	// flow rate 3 Output
		int		nnFlowRate4O;	// flow rate 4 Output
		int 	nnDoneI;		// delay output
		int 	nnReadyO;		// when the ready bottom click
		int 	nnDropO;			// when the drop bottom click
		int		nnDoneO;			// when load complete
		int		nnHoldO;			// on hold
		int		nnAddO;			// add more
		int		nnDropReadyI;	// ready to drop
		int		nnHoldI;		// hold input
		double	ffFall;			// Free Fall
		int		nnSiloNum;		// silo number
		int		nnSiloJog;		// Silo Add Jog Pulse Time in 100msec
		double	ddAddTol;		// Silo Add Tolerance
		int	    nnBitWise;		// Target Weight Binary
		int	    nnBitCheckI;		// Target Weight Binary Check Input
		

	public:
		//------------------------------------
		property String^ stLbl
		{
			//This is a property
			String^ get()
			{
				return this->pstLbl;
			}
			void set ( String^ value )
			{
				this->pstLbl = value;
			}
		}
		//DC 4.0.2
		property String^ stProduct
		{
			//This is a property
			String^ get()
			{
				return this->pstProduct;
			}
			void set ( String^ value )
			{
				this->pstProduct = value;
			}
		}
		property bool bUsed
		{
			//This is a property
			bool get()
			{
				return this->bbUsed;
			}
			void set ( bool value )
			{
				this->bbUsed = value;
			}
		}
		property int nFlowRatePct1
		{
			//This is a property
			int get()
			{
				return this->nnFlowRatePct1;
			}
			void set ( int value )
			{
				this->nnFlowRatePct1 = value;
			}
		}
		property int nFlowRatePct2
		{
			//This is a property
			int get()
			{
				return this->nnFlowRatePct2;
			}
			void set ( int value )
			{
				this->nnFlowRatePct2 = value;
			}
		}
		property int nFlowRatePct3
		{
			//This is a property
			int get()
			{
				return this->nnFlowRatePct3;
			}
			void set ( int value )
			{
				this->nnFlowRatePct3 = value;
			}
		}
		property int nFlowRatePct4
		{
			//This is a property
			int get()
			{
				return this->nnFlowRatePct4;
			}
			void set ( int value )
			{
				this->nnFlowRatePct4 = value;
			}
		}
		property int nDelayPct
		{
			//This is a property
			int get()
			{
				return this->nnDelayPct;
			}
			void set ( int value )
			{
				this->nnDelayPct = value;
			}
		}
		property int nDelayTime
		{
			//This is a property
			int get()
			{
				return this->nnDelayTime;
			}
			void set ( int value )
			{
				this->nnDelayTime = value;
			}
		}
		property int nFlowRate1O
		{
			//This is a property
			int get()
			{
				return this->nnFlowRate1O;
			}
			void set ( int value )
			{
				this->nnFlowRate1O = value;
			}
		}
		property int nFlowRate2O
		{
			//This is a property
			int get()
			{
				return this->nnFlowRate2O;
			}
			void set ( int value )
			{
				this->nnFlowRate2O= value;
			}
		}
		property int nFlowRate3O
		{
			//This is a property
			int get()
			{
				return this->nnFlowRate3O;
			}
			void set ( int value )
			{
				this->nnFlowRate3O= value;
			}
		}
		property int nFlowRate4O
		{
			//This is a property
			int get()
			{
				return this->nnFlowRate4O;
			}
			void set ( int value )
			{
				this->nnFlowRate4O= value;
			}
		}
		property int nDoneI
		{
			//This is a property
			int get()
			{
				return this->nnDoneI;
			}
			void set ( int value )
			{
				this->nnDoneI= value;
			}
		}
		property int nReadyO
		{
			//This is a property
			int get()
			{
				return this->nnReadyO;
			}
			void set ( int value )
			{
				this->nnReadyO= value;
			}
		}
		property int nDropO
		{
			//This is a property
			int get()
			{
				return this->nnDropO;
			}
			void set ( int value )
			{
				this->nnDropO= value;
			}
		}
		property int nDoneO
		{
			//This is a property
			int get()
			{
				return this->nnDoneO;
			}
			void set ( int value )
			{
				this->nnDoneO= value;
			}
		}
		property int nHoldO
		{
			//This is a property
			int get()
			{
				return this->nnHoldO;
			}
			void set ( int value )
			{
				this->nnHoldO= value;
			}
		}
		property int nAddO
		{
			//This is a property
			int get()
			{
				return this->nnAddO;
			}
			void set ( int value )
			{
				this->nnAddO= value;
			}
		}
		property int nDropReadyI
		{
			//This is a property
			int get()
			{
				return this->nnDropReadyI;
			}
			void set ( int value )
			{
				this->nnDropReadyI= value;
			}
		}
		property int nHoldI
		{
			//This is a property
			int get()
			{
				return this->nnHoldI;
			}
			void set ( int value )
			{
				this->nnHoldI= value;
			}
		}
		property double fFall
		{
			//This is a property
			double get()
			{
				return this->ffFall;
			}
			void set ( double value )
			{
				this->ffFall= value;
			}
		}
		property int nSiloNum
		{
			//This is a property
			int get()
			{
				return this->nnSiloNum;
			}
			void set ( int value )
			{
				this->nnSiloNum= value;
			}
		}
		property int nSiloJog
		{
			//This is a property
			int get()
			{
				return this->nnSiloJog;
			}
			void set ( int value )
			{
				this->nnSiloJog= value;
			}
		}
		property double dAddTol
		{
			//This is a property
			double get()
			{
				return this->ddAddTol;
			}
			void set ( double value )
			{
				this->ddAddTol= value;
			}
		}
		property int nBitWise
		{
			//This is a property
			int get()
			{
				return this->nnBitWise;
			}
			void set ( int value )
			{
				this->nnBitWise= value;
			}
		}
		property int nBitCheckI
		{
			//This is a property
			int get()
			{
				return this->nnBitCheckI;
			}
			void set ( int value )
			{
				this->nnBitCheckI= value;
			}
		}
	};
#pragma endregion

#pragma region CMD
	//-------------------------------------------------------------------------
	public ref struct Cmd
	{
	private:
		uchar  Id;	
		ushort Key;	
		int	   nnIdx;
		int	   nnIdx2;

	public:
		// This is a property 
		property uchar cId
		{
			uchar get()
			{
				return this->Id;
			}
			void set( uchar value )
			{
				this->Id = value;
			}
		}
		// This is a property 
		property ushort nKey
		{
			ushort get()
			{
				return this->Key;
			}
			void set( ushort value )
			{
				this->Key = value;
			}
		}
		// This is a property 
		property int nIdx
		{
			int get()
			{
				return this->nnIdx;
			}
			void set( int value )
			{
				this->nnIdx = value;
			}
		}
		
		// This is a property 
		property int nIdx2
		{
			int get()
			{
				return this->nnIdx2;
			}
			void set( int value )
			{
				this->nnIdx2 = value;
			}
		}

	};
#pragma endregion

#pragma region REM

	typedef struct                // reports - time span
	{
		long long tStart;
		long long tEnd;
	} RTIME;

#pragma endregion

//-------------------------------------------------------------------------
	public ref struct Scl
	{
	private:
		IPAddress^	Ip;
		int			Port;

	public:	
		// This is a property 
		property IPAddress^ pIp
		{
			IPAddress^ get()
			{
				return this->Ip;
			}
			void set(IPAddress^ value )
			{
				this->Ip = value;
			}
		}
		// This is a property 
		property int nPort
		{
			int get()
			{
				return this->Port;
			}
			void set( int value )
			{
				this->Port = value;
			}
		}
	};


// ------------------------------------------
	public ref struct All
	{
		INI		*psIni;
		char	*pcPath;
		char	*pcLog;

		char    cLogin;		//DC 4.1.0
		char    cRemote;	//DC 4.1.0 remote login state

		System::Collections::Generic::Queue<String^>^ qPrint1;
		System::Collections::Generic::Queue<String^>^ qPrint2;
		System::Collections::Generic::Queue<String^>^ qPrint3;
		//System::Collections::Generic::Queue<PrintQ^>^ qPrint4;
		System::Collections::Generic::Queue<String^>^ qPrint4;
		System::Collections::Generic::Queue<PrintQ^>^  q2ndPrint1;	//DC 4.0.2
		System::Collections::Generic::Queue<PrintQ^>^  q2ndPrint2;	//DC 4.0.2
		System::Collections::Generic::Queue<PrintQ^>^  q2ndPrint3;	//DC 4.0.2
		System::Collections::Generic::Queue<PrintQ^>^  q2ndPrint4;	//DC 4.0.2
		
		System::Collections::Generic::Queue<Dbase^>^ qDbase;
		System::Collections::Generic::Queue<Dbase^>^ qDbaseBad;


		System::Collections::Generic::Queue<Cmd^>^ qCmd;	//DC 4.1.0

		List<Job^>^ lJob;
		List<Job^>^ lOld;
		List<Truck^>^ lTruck;
		List<String^>^ lStat;
		List<Job^>^ lJobsOld;
		List<Job^>^ lJobs;

		Rem^    pRem;		//DC 4.1.0

		Uri^ pCam1;
		Uri^ pCam2;
		Uri^ pCam3;
		Uri^ pCam4;
		Uri^ pCam5;
		Uri^ pCam6;

		Scl  sScale1;
		Scl  sScale2;
		Scl  sScale3;
		Scl  sScale4;			//DC 3.3.0

		String^ pOdbc;
		String^ pPrinter1;
		String^ pPrinter2;
		String^ pPrinter3;
		String^ pPrinter4;		//DC 3.3.0
		String^ p2ndPrinter1;
		String^ p2ndPrinter2;
		String^ p2ndPrinter3;
		String^ p2ndPrinter4;		//DC 4.0.2
		String^ pOptoCom;
		String^ pDbCmd;
		String^ pSerialNum;
		String^ pExc;
		String^ pAcPath;	//DC 3.2.3
		String^ stExc;		//DC 4.1.0
		String^ stRemVersion;//DC 4.1.0

		//DC 4.1.0
		LOG_REC *psLog;		// remote and GUI thread only
		ulong	nLinkIdx;
		char	cWaitT;		// wait for tlink
		int		nCmd;
		bool	bRemCbc;
		bool	bRemLogin;
		bool	bRemoteCall;
		bool	bRemoteVoid;
		bool    bRemContinue;
		bool	bIni;
		bool	bJob4;
		int		nSlinkCnt;
		int		nMax;
		clock_t tClinkClock;
		clock_t tTlinkClock;
		RTIME	*psTime;
		Job^	pJob4;
		Job^    pJob;

		long	gnIndex;

		double	dSold;

		int		nCservOk;	//DC 4.1.0
		int		nClinkOk;	//DC 4.1.0

		int		nLen;		//DC 4.1.0

		int		nKey;		//DC 4.1.0 clink keystroke
		int		nManKey;

		int		nTicket;
		int	    nOptoError;
		int		nClinkErr;	//DC 4.1.0

		int		nTickets1;	// # of new tickets
		int		nTickets2;
		int		nTickets3;
		int		nTickets4;	//DC 3.3.0

		int		nDone1;		 // # of done tickets
		int		nDone2;
		int		nDone3;
		int		nDone4;		//DC 3.3.0

		int		nTicketCopy1;	//DC 4.0.2
		int		nTicketCopy2;	//DC 4.0.2
		int		nTicketCopy3;	//DC 4.0.2
		int		nTicketCopy4;	//DC 4.0.2

		bool	bUlink;
		bool	bExcept;
		String^ pTestBox;

		IPAddress^	pIp;
		int			nPort;

		IPAddress^	pRemIp;
		int			nRemPort;

		AS_TYPE eAsType;	// program type
		IF_TYPE eIfType;	// interfasce type
	};


	public ref struct Scale
	{
		Scl^  pScl;		//DC 3.2.0
		INI   *psIni;
		SCALE *psScale;
		All^	pAll;
	};


///////////////////////////////////////////////////////////////////////////////
}