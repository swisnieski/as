#pragma once
#include "stdafx.h"

namespace As 
{

//-----------------------------------------------------------------------------
int readConfig(All^ pAll)
{
INI *psIni = pAll->psIni;
TIC *psTic = &psIni->sTic;
FILE *pfCfg;
errno_t err;
char *pcCfg;
int size;
int len;
char *pcTmp1, *pcTmp2, *pcTmp3 = 0, * pcTmp4, * pcTmp5, * pcTmp6, * pcTmp7, * pcTmp8, * pcTmp9, * pcTmpA, * pcTmpB, * pcTmpC, * pcTmpD;  //3.3.0
char acCfgFile[64];
char acData[32];
char acUser[32];
char acPass[32];
char acTmp[132];
int line, col;
int baud;
//int port;				//DC 3.2.0
char *pcPort;
//char *pcIp;				//DC 3.2.0
ulong nBit = 0;			//DC 3.2.0
ulong nBit64 = 0;		//DC 4.0.0

	sprintf_s(acCfgFile, 64, "%sas.cfg", pAll->pcPath);
	
	err = fopen_s(&pfCfg, acCfgFile, "r");
	if(err != 0)
	{
		perror("config file missing. exit ...\n");
		return(-1);
	}
	size = _filelength(_fileno(pfCfg));
	
	pcCfg = (char *)malloc(size);
	if(pcCfg == NULL)
	{
		perror("config memory missing. exit ...\n");
		return(-2);
	}
	len = fread(pcCfg, 1, size, pfCfg);
	if(len <= 0)
	{
		perror("config file read error. exit ...\n");
		return(-3);	
	}

	//-------------------------------------------------------------------------
	if(((pcTmp1 = strstr(pcCfg, "ready1BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+10) != ',')
		{
			if(atoi(pcTmp1+10) > 63)			//DC 6.1.2
			{
				nBit64 = ((ulong64)1L << atoi(pcTmp1+10)-64);
				if((psIni->nMask64 & nBit64) == 0)
				{
					psIni->nReady1O = nBit64;
					psIni->nMask64 |= nBit64;
				}
			}
			else
			{
				nBit = ((ulong)1L << atoi(pcTmp1+10));
				if((psIni->nMask & nBit) == 0)
				{
					psIni->nReady1O = nBit;
					psIni->nMask |= nBit;
				}
			}
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "drop1BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+9) != ',')
		{
			nBit = ((ulong)1L << atoi(pcTmp1+9));
			if((psIni->nMask & nBit) == 0)
			{
				psIni->nDrop1O = nBit;
				psIni->nMask |= nBit;
			}
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "ready2BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+10) != ',')
		{
			nBit = ((ulong)1L << atoi(pcTmp1+10));
			if((psIni->nMask & nBit) == 0)
			{
				psIni->nReady2O = nBit;
				psIni->nMask |= nBit;
			}
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "drop2BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+9) != ',')
		{
			nBit = ((ulong)1L << atoi(pcTmp1+9));
			if((psIni->nMask & nBit) == 0)
			{
				psIni->nDrop2O = nBit;
				psIni->nMask |= nBit;
			}
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "ready3BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+10) != ',')
		{
			nBit = ((ulong)1L << atoi(pcTmp1+10));
			if((psIni->nMask & nBit) == 0)
			{
				psIni->nReady3O = nBit;
				psIni->nMask |= nBit;
			}
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "drop3BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+9) != ',')
		{
			nBit = ((ulong)1L << atoi(pcTmp1+9));
			if((psIni->nMask & nBit) == 0)
			{
				psIni->nDrop3O = nBit;
				psIni->nMask |= nBit;
			}
		}
	}
	//DC 3.3.0
	if(((pcTmp1 = strstr(pcCfg, "ready4BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+10) != ',')
		{
			nBit = ((ulong)1L << atoi(pcTmp1+10));
			if((psIni->nMask & nBit) == 0)
			{
				psIni->nReady4O = nBit;
				psIni->nMask |= nBit;
			}
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "drop4BtO=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		if(*(pcTmp1+9) != ',')
		{
			nBit = ((ulong)1L << atoi(pcTmp1+9));
			if((psIni->nMask & nBit) == 0)
			{
				psIni->nDrop4O = nBit;
				psIni->nMask |= nBit;
			}
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "serialNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		pAll->pSerialNum = gcnew String(pcTmp1+10);
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "plantNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->nPlantNum1 = atoi(pcTmp1+9);
		psIni->nPlantNum2 = atoi(pcTmp2+1);
	}	
	if(((pcTmp1 = strstr(pcCfg, "silosNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nNumLanes = atoi(pcTmp1+9);
	}
	if(((pcTmp1 = strstr(pcCfg, "line1SilosNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nL1SilosNum = atoi(pcTmp1+14);
	}
	if(((pcTmp1 = strstr(pcCfg, "line2SilosNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nL2SilosNum = atoi(pcTmp1+14);
	}
	if(((pcTmp1 = strstr(pcCfg, "line3SilosNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nL3SilosNum = atoi(pcTmp1+14);
	}
	if(((pcTmp1 = strstr(pcCfg, "line4SilosNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nL4SilosNum = atoi(pcTmp1+14);
	}
	if(((pcTmp1 = strstr(pcCfg, "tonPrice=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fTonPrice = atoi(pcTmp1+9);
	}
	if(((pcTmp1 = strstr(pcCfg, "addQty=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->dAddQty = atoi(pcTmp1+7);
	}
	if(((pcTmp1 = strstr(pcCfg, "taxRate=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fTaxRate = atoi(pcTmp1+8);
	}
	if(((pcTmp1 = strstr(pcCfg, "bottomScale=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bBotScale = (*(pcTmp1+12) == '1');
	}
	if(((pcTmp1 = strstr(pcCfg, "disableManual=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bDisableManual = (*(pcTmp1+14) == '1');
	}
	if(((pcTmp1 = strstr(pcCfg, "scaleInLB=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bScaleInLB = (*(pcTmp1+10) == '1');
	}
	if(((pcTmp1 = strstr(pcCfg, "useTrkMaxCap=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bUseTrkMax = (*(pcTmp1+13) == '1');
	}
	if(((pcTmp1 = strstr(pcCfg, "dailyLog=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bDailyLog = (*(pcTmp1+9) == '1');
	}
	if(((pcTmp1 = strstr(pcCfg, "firstTicket=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nFirstTicket = atoi(pcTmp1+12);
	}
	if(((pcTmp1 = strstr(pcCfg, "plantReverse=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bRevPlant = (*(pcTmp1+13) == '1');
	}
	if(((pcTmp1 = strstr(pcCfg, "disableInv=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bDisableInv = (*(pcTmp1+11) == '1');
	}

	//----------------------------------------------safety valve
	if(((pcTmp1 = strstr(pcCfg, "safeTime=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nSafeTime = atoi(pcTmp1+9);
	}
	if(((pcTmp1 = strstr(pcCfg, "safeJob=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->bSafeJob = (*(pcTmp1+8) == '1');
	}

	//---------------------------------------------- Database
	if(((pcTmp1 = strstr(pcCfg, "dbName=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		strncpy_s(acData, pcTmp1+7, pcTmp2-pcTmp1-7);
	}
	if(((pcTmp1 = strstr(pcCfg, "dbUser=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		strncpy_s(acUser, pcTmp1+7, pcTmp2-pcTmp1-7);
	}
	if(((pcTmp1 = strstr(pcCfg, "dbPass=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		strncpy_s(acPass, pcTmp1+7, pcTmp2-pcTmp1-7);
	}
	sprintf_s(acTmp, "DSN=%s;User ID=%s;Password=%s;", acData, acUser, acPass);
	pAll->pOdbc = gcnew String(acTmp);

	if(((pcTmp1 = strstr(pcCfg, "hornTime=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nHornTime = atoi(pcTmp1+9);
	}
	
	if(((pcTmp1 = strstr(pcCfg, "optoDelay=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nOptoDelay = atoi(pcTmp1+10);
	}
	
	//-------------------------------------------------------------------------PORTS
	if(((pcTmp1 = strstr(pcCfg, "optoServer=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+12) < pcTmp2)
		{
			pAll->pIp = IPAddress::Parse(gcnew String(pcTmp1+11));
			pAll->nPort = atoi(pcTmp2+1);
		}
		*pcTmp2 = ',';
	}

	if((pcTmp1 = strstr(pcCfg, "optoInputs=")) != NULL)
		{
			psIni->cOptoInputs = atoi(pcTmp1+11);

			switch(psIni->cOptoInputs)
			{
			case 16:	psIni->cOptoSlot = 15;  break;
			case 20:	psIni->cOptoSlot = 14;	break;
			case 32:	psIni->cOptoSlot = 14;	break;
			case 48:	psIni->cOptoSlot = 13;	break;
			case 64:	psIni->cOptoSlot = 12;	break;
			}
		}

	if((pcTmp1 = strstr(pcCfg, "optoAnalog=")) != NULL)
		{
			psIni->cOptoAnalog = atoi(pcTmp1+11);

			//switch(psIni->cOptoAnalog)
			//{
			//case 1:	psIni->cOptoSlot = 13;  break;
			//case 2:	psIni->cOptoSlot = 12;	break;
			//case 3:	psIni->cOptoSlot = 11;	break;
			//case 4:	psIni->cOptoSlot = 10;	break;
			//}
		}
		
	if(((pcTmp1 = strstr(pcCfg, "ulinkPort=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nUlinkPort = atoi(pcTmp1+10);
	}

	if(((pcTmp1 = strstr(pcCfg, "rlinkPort=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nRlinkPort = atoi(pcTmp1+10);
	}
	//DC 4.1.0---------------------------------------------------------------------
	if(((pcTmp1 = strstr(pcCfg, "remServer=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+11) < pcTmp2)
		{
			pAll->pRemIp = IPAddress::Parse(gcnew String(pcTmp1+10));
			pAll->nRemPort = atoi(pcTmp2+1);
		}
		*pcTmp2 = ',';
	}

	if(((pcTmp1 = strstr(pcCfg, "printerOne=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->pPrinter1 = gcnew String(pcTmp1+11);
		*pcTmp2 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "printerTwo=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->pPrinter2 = gcnew String(pcTmp1+11);
		*pcTmp2 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "printerThree=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->pPrinter3 = gcnew String(pcTmp1+13);
		*pcTmp2 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "printerFour=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->pPrinter4 = gcnew String(pcTmp1+12);
		*pcTmp2 = ',';	
	}
	//DC 4.0.2
	if(((pcTmp1 = strstr(pcCfg, "2ndCopyLane1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->p2ndPrinter1 = gcnew String(pcTmp1+13);
		*pcTmp2 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "2ndCopyLane2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->p2ndPrinter2 = gcnew String(pcTmp1+13);
		*pcTmp2 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "2ndCopyLane3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->p2ndPrinter3 = gcnew String(pcTmp1+13);
		*pcTmp2 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "2ndCopyLane4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
		pAll->p2ndPrinter4 = gcnew String(pcTmp1+13);
		*pcTmp2 = ',';	
	}
	
	if(((pcTmp1 = strstr(pcCfg, "numCopyLane1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		pAll->nTicketCopy1 = atoi(pcTmp1+13);
	}

	if(((pcTmp1 = strstr(pcCfg, "numCopyLane2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		pAll->nTicketCopy2 = atoi(pcTmp1+13);
	}

	if(((pcTmp1 = strstr(pcCfg, "numCopyLane3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		pAll->nTicketCopy3 = atoi(pcTmp1+13);
	}

	if(((pcTmp1 = strstr(pcCfg, "numCopyLane4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		pAll->nTicketCopy4 = atoi(pcTmp1+13);
		psIni->nTicketCopy4 = atoi(pcTmp1+13);	//DC 4.1.0
	}


	if(((pcTmp1 = strstr(pcCfg, "scalePort1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		pcPort = pcTmp1+11;
		baud = atoi(pcTmp2+1);
		if(strlen(pcPort) > 0)
		{
			strcpy_s(psIni->sScale1.acCom, pcPort);
			psIni->sScale1.nBaud = baud;
		}
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
//DC 3.2.0
	if(((pcTmp1 = strstr(pcCfg, "scaleIP1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+9) < pcTmp2)
		{
			pAll->sScale1.pIp = IPAddress::Parse(gcnew String(pcTmp1+9));
			pAll->sScale1.nPort= atoi(pcTmp2+1);
		}
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "scaleIPS1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale1.bSerTP = (*(pcTmp1+10) == '1');
	}

	if(((pcTmp1 = strstr(pcCfg, "scalePort2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		pcPort = pcTmp1+11;
		baud = atoi(pcTmp2+1);
		if(strlen(pcPort) > 0)
		{
			strcpy_s(psIni->sScale2.acCom, pcPort);
			psIni->sScale2.nBaud = baud;
		}
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
//DC 3.2.0
	if(((pcTmp1 = strstr(pcCfg, "scaleIP2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+9) < pcTmp2)
		{
			pAll->sScale2.pIp = IPAddress::Parse(gcnew String(pcTmp1+9));
			pAll->sScale2.nPort= atoi(pcTmp2+1);
		}
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "scaleIPS2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale2.bSerTP = (*(pcTmp1+10) == '1');
	}

	if(((pcTmp1 = strstr(pcCfg, "scalePort3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		pcPort = pcTmp1+11;
		baud = atoi(pcTmp2+1);
		if(strlen(pcPort) > 0)
		{
			strcpy_s(psIni->sScale3.acCom, pcPort);
			psIni->sScale3.nBaud = baud;
		}
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
//DC 3.2.0
	if(((pcTmp1 = strstr(pcCfg, "scaleIP3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+9) < pcTmp2)
		{
			pAll->sScale3.pIp = IPAddress::Parse(gcnew String(pcTmp1+9));
			pAll->sScale3.nPort= atoi(pcTmp2+1);
		}
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "scaleIPS3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale3.bSerTP = (*(pcTmp1+10) == '1');
	}

	//DC 3.3.0 Scale 4
	if(((pcTmp1 = strstr(pcCfg, "scalePort4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		pcPort = pcTmp1+11;
		baud = atoi(pcTmp2+1);
		if(strlen(pcPort) > 0)
		{
			strcpy_s(psIni->sScale4.acCom, pcPort);
			psIni->sScale4.nBaud = baud;
		}
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
//DC 3.2.0
	if(((pcTmp1 = strstr(pcCfg, "scaleIP4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+9) < pcTmp2)
		{
			pAll->sScale4.pIp = IPAddress::Parse(gcnew String(pcTmp1+9));
			pAll->sScale4.nPort= atoi(pcTmp2+1);
		}
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "scaleIPS4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale4.bSerTP = (*(pcTmp1+10) == '1');
	}

	if(((pcTmp1 = strstr(pcCfg, "optoPort=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		
		if(strlen(pcTmp1+9) > 0)
		{
			pAll->pOptoCom = gcnew String(pcTmp1+9);
			psIni->nOptoBaud = atoi(pcTmp2+1);
		}
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}	

	//------------------------------------------------SCALE
	if(((pcTmp1 = strstr(pcCfg, "targetTolAbs=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fTarTolAbs = atoi(pcTmp1+13);
	}
	if(((pcTmp1 = strstr(pcCfg, "targetTolPerc=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fTarTolPerc = atoi(pcTmp1+14);
	}

	if(((pcTmp1 = strstr(pcCfg, "topScaleMax=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fTopScaleMax = atoi(pcTmp1+12);
	}

	if(((pcTmp1 = strstr(pcCfg, "botScaleMax=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fBotScaleMax = atoi(pcTmp1+12);
	}

	if(((pcTmp1 = strstr(pcCfg, "botScaleMaxL2=")) != NULL)		//DC 4.1.2
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fBotScaleMaxL2 = atoi(pcTmp1+14);
	}

	if(((pcTmp1 = strstr(pcCfg, "botScaleMaxL3=")) != NULL)		//DC 4.1.2
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fBotScaleMaxL3 = atoi(pcTmp1+14);
	}

	if(((pcTmp1 = strstr(pcCfg, "botScaleMaxL4=")) != NULL)		//DC 4.0.0
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fBotScaleMaxL4 = atoi(pcTmp1+14);
	}

	if(((pcTmp1 = strstr(pcCfg, "botScaleTruck=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fBotScaleTruck = atoi(pcTmp1+14);
	}

	if(((pcTmp1 = strstr(pcCfg, "scaleSettle=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScaleSettle = atoi(pcTmp1+12);
	}
	
	if(((pcTmp1 = strstr(pcCfg, "scaleDisSettle=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScaleDisSettle = atoi(pcTmp1+15);
	}
	
	if(((pcTmp1 = strstr(pcCfg, "scaleIdle=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScaleIdle = atoi(pcTmp1+10);
	}
	
	if(((pcTmp1 = strstr(pcCfg, "scaleTolerance1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale1.fTolerance = atoi(pcTmp1+16);
	}
	if(((pcTmp1 = strstr(pcCfg, "scaleTolerance2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale2.fTolerance = atoi(pcTmp1+16);
	}
	if(((pcTmp1 = strstr(pcCfg, "scaleTolerance3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale3.fTolerance = atoi(pcTmp1+16);
	}
	//DC 3.3.0
	if(((pcTmp1 = strstr(pcCfg, "scaleTolerance4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sScale4.fTolerance = atoi(pcTmp1+16);
	}

	// --------------------------------------------  free fall
	if(((pcTmp1 = strstr(pcCfg, "freeFall0=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[0] = atoi(pcTmp1+10);
		psIni->afManFall2[0] = atoi(pcTmp2+1);
		psIni->afManFall3[0] = atoi(pcTmp3+1);
		psIni->afManFall4[0] = atoi(pcTmp4+1);
		psIni->afManFall5[0] = atoi(pcTmp5+1);
		psIni->afManFall6[0] = atoi(pcTmp6+1);
		psIni->afManFall7[0] = atoi(pcTmp7+1);
		psIni->afManFall8[0] = atoi(pcTmp8+1);
		psIni->afManFall9[0] = atoi(pcTmp9+1);
		psIni->afManFall10[0] = atoi(pcTmpA+1);
		psIni->afManFall11[0] = atoi(pcTmpB+1);
		psIni->afManFall12[0] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)	
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[1] = atoi(pcTmp1+10);
		psIni->afManFall2[1] = atoi(pcTmp2+1);
		psIni->afManFall3[1] = atoi(pcTmp3+1);
		psIni->afManFall4[1] = atoi(pcTmp4+1);
		psIni->afManFall5[1] = atoi(pcTmp5+1);
		psIni->afManFall6[1] = atoi(pcTmp6+1);
		psIni->afManFall7[1] = atoi(pcTmp7+1);
		psIni->afManFall8[1] = atoi(pcTmp8+1);
		psIni->afManFall9[1] = atoi(pcTmp9+1);
		psIni->afManFall10[1] = atoi(pcTmpA+1);
		psIni->afManFall11[1] = atoi(pcTmpB+1);
		psIni->afManFall12[1] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[2] = atoi(pcTmp1+10);
		psIni->afManFall2[2] = atoi(pcTmp2+1);
		psIni->afManFall3[2] = atoi(pcTmp3+1);
		psIni->afManFall4[2] = atoi(pcTmp4+1);
		psIni->afManFall5[2] = atoi(pcTmp5+1);
		psIni->afManFall6[2] = atoi(pcTmp6+1);
		psIni->afManFall7[2] = atoi(pcTmp7+1);
		psIni->afManFall8[2] = atoi(pcTmp8+1);
		psIni->afManFall9[2] = atoi(pcTmp9+1);
		psIni->afManFall10[2] = atoi(pcTmpA+1);
		psIni->afManFall11[2] = atoi(pcTmpB+1);
		psIni->afManFall12[2] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[3] = atoi(pcTmp1+10);
		psIni->afManFall2[3] = atoi(pcTmp2+1);
		psIni->afManFall3[3] = atoi(pcTmp3+1);
		psIni->afManFall4[3] = atoi(pcTmp4+1);
		psIni->afManFall5[3] = atoi(pcTmp5+1);
		psIni->afManFall6[3] = atoi(pcTmp6+1);
		psIni->afManFall7[3] = atoi(pcTmp7+1);
		psIni->afManFall8[3] = atoi(pcTmp8+1);
		psIni->afManFall9[3] = atoi(pcTmp9+1);
		psIni->afManFall10[3] = atoi(pcTmpA+1);
		psIni->afManFall11[3] = atoi(pcTmpB+1);
		psIni->afManFall12[3] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[4] = atoi(pcTmp1+10);
		psIni->afManFall2[4] = atoi(pcTmp2+1);
		psIni->afManFall3[4] = atoi(pcTmp3+1);
		psIni->afManFall4[4] = atoi(pcTmp4+1);
		psIni->afManFall5[4] = atoi(pcTmp5+1);
		psIni->afManFall6[4] = atoi(pcTmp6+1);
		psIni->afManFall7[4] = atoi(pcTmp7+1);
		psIni->afManFall8[4] = atoi(pcTmp8+1);
		psIni->afManFall9[4] = atoi(pcTmp9+1);
		psIni->afManFall10[4] = atoi(pcTmpA+1);
		psIni->afManFall11[4] = atoi(pcTmpB+1);
		psIni->afManFall12[4] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall5=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[5] = atoi(pcTmp1+10);
		psIni->afManFall2[5] = atoi(pcTmp2+1);
		psIni->afManFall3[5] = atoi(pcTmp3+1);
		psIni->afManFall4[5] = atoi(pcTmp4+1);
		psIni->afManFall5[5] = atoi(pcTmp5+1);
		psIni->afManFall6[5] = atoi(pcTmp6+1);
		psIni->afManFall7[5] = atoi(pcTmp7+1);
		psIni->afManFall8[5] = atoi(pcTmp8+1);
		psIni->afManFall9[5] = atoi(pcTmp9+1);
		psIni->afManFall10[5] = atoi(pcTmpA+1);
		psIni->afManFall11[5] = atoi(pcTmpB+1);
		psIni->afManFall12[5] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall6=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[6] = atoi(pcTmp1+10);
		psIni->afManFall2[6] = atoi(pcTmp2+1);
		psIni->afManFall3[6] = atoi(pcTmp3+1);
		psIni->afManFall4[6] = atoi(pcTmp4+1);
		psIni->afManFall5[6] = atoi(pcTmp5+1);
		psIni->afManFall6[6] = atoi(pcTmp6+1);
		psIni->afManFall7[6] = atoi(pcTmp7+1);
		psIni->afManFall8[6] = atoi(pcTmp8+1);
		psIni->afManFall9[6] = atoi(pcTmp9+1);
		psIni->afManFall10[6] = atoi(pcTmpA+1);
		psIni->afManFall11[6] = atoi(pcTmpB+1);
		psIni->afManFall12[6] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall7=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[7] = atoi(pcTmp1+10);
		psIni->afManFall2[7] = atoi(pcTmp2+1);
		psIni->afManFall3[7] = atoi(pcTmp3+1);
		psIni->afManFall4[7] = atoi(pcTmp4+1);
		psIni->afManFall5[7] = atoi(pcTmp5+1);
		psIni->afManFall6[7] = atoi(pcTmp6+1);
		psIni->afManFall7[7] = atoi(pcTmp7+1);
		psIni->afManFall8[7] = atoi(pcTmp8+1);
		psIni->afManFall9[7] = atoi(pcTmp9+1);
		psIni->afManFall10[7] = atoi(pcTmpA+1);
		psIni->afManFall11[7] = atoi(pcTmpB+1);
		psIni->afManFall12[7] = atoi(pcTmpC+1);
	}	
	if(((pcTmp1 = strstr(pcCfg, "freeFall8=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[8] = atoi(pcTmp1+10);
		psIni->afManFall2[8] = atoi(pcTmp2+1);
		psIni->afManFall3[8] = atoi(pcTmp3+1);
		psIni->afManFall4[8] = atoi(pcTmp4+1);
		psIni->afManFall5[8] = atoi(pcTmp5+1);
		psIni->afManFall6[8] = atoi(pcTmp6+1);
		psIni->afManFall7[8] = atoi(pcTmp7+1);
		psIni->afManFall8[8] = atoi(pcTmp8+1);
		psIni->afManFall9[8] = atoi(pcTmp9+1);
		psIni->afManFall10[8] = atoi(pcTmpA+1);
		psIni->afManFall11[8] = atoi(pcTmpB+1);
		psIni->afManFall12[8] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall9=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[9] = atoi(pcTmp1+10);
		psIni->afManFall2[9] = atoi(pcTmp2+1);
		psIni->afManFall3[9] = atoi(pcTmp3+1);
		psIni->afManFall4[9] = atoi(pcTmp4+1);
		psIni->afManFall5[9] = atoi(pcTmp5+1);
		psIni->afManFall6[9] = atoi(pcTmp6+1);
		psIni->afManFall7[9] = atoi(pcTmp7+1);
		psIni->afManFall8[9] = atoi(pcTmp8+1);
		psIni->afManFall9[9] = atoi(pcTmp9+1);
		psIni->afManFall10[9] = atoi(pcTmpA+1);
		psIni->afManFall11[9] = atoi(pcTmpB+1);
		psIni->afManFall12[9] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFallA=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[10] = atoi(pcTmp1+10);
		psIni->afManFall2[10] = atoi(pcTmp2+1);
		psIni->afManFall3[10] = atoi(pcTmp3+1);
		psIni->afManFall4[10] = atoi(pcTmp4+1);
		psIni->afManFall5[10] = atoi(pcTmp5+1);
		psIni->afManFall6[10] = atoi(pcTmp6+1);
		psIni->afManFall7[10] = atoi(pcTmp7+1);
		psIni->afManFall8[10] = atoi(pcTmp8+1);
		psIni->afManFall9[10] = atoi(pcTmp9+1);
		psIni->afManFall10[10] = atoi(pcTmpA+1);
		psIni->afManFall11[10] = atoi(pcTmpB+1);
		psIni->afManFall12[10] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFallB=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[11] = atoi(pcTmp1+10);
		psIni->afManFall2[11] = atoi(pcTmp2+1);
		psIni->afManFall3[11] = atoi(pcTmp3+1);
		psIni->afManFall4[11] = atoi(pcTmp4+1);
		psIni->afManFall5[11] = atoi(pcTmp5+1);
		psIni->afManFall6[11] = atoi(pcTmp6+1);
		psIni->afManFall7[11] = atoi(pcTmp7+1);
		psIni->afManFall8[11] = atoi(pcTmp8+1);
		psIni->afManFall9[11] = atoi(pcTmp9+1);
		psIni->afManFall10[11] = atoi(pcTmpA+1);
		psIni->afManFall11[11] = atoi(pcTmpB+1);
		psIni->afManFall12[11] = atoi(pcTmpC+1);
	}
	// --------------------------------------------  free fall extended
	if(((pcTmp1 = strstr(pcCfg, "freeFall12=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[12] = atoi(pcTmp1+11);
		psIni->afManFall2[12] = atoi(pcTmp2+1);
		psIni->afManFall3[12] = atoi(pcTmp3+1);
		psIni->afManFall4[12] = atoi(pcTmp4+1);
		psIni->afManFall5[12] = atoi(pcTmp5+1);
		psIni->afManFall6[12] = atoi(pcTmp6+1);
		psIni->afManFall7[12] = atoi(pcTmp7+1);
		psIni->afManFall8[12] = atoi(pcTmp8+1);
		psIni->afManFall9[12] = atoi(pcTmp9+1);
		psIni->afManFall10[12] = atoi(pcTmpA+1);
		psIni->afManFall11[12] = atoi(pcTmpB+1);
		psIni->afManFall12[12] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall13=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[13] = atoi(pcTmp1+11);
		psIni->afManFall2[13] = atoi(pcTmp2+1);
		psIni->afManFall3[13] = atoi(pcTmp3+1);
		psIni->afManFall4[13] = atoi(pcTmp4+1);
		psIni->afManFall5[13] = atoi(pcTmp5+1);
		psIni->afManFall6[13] = atoi(pcTmp6+1);
		psIni->afManFall7[13] = atoi(pcTmp7+1);
		psIni->afManFall8[13] = atoi(pcTmp8+1);
		psIni->afManFall9[13] = atoi(pcTmp9+1);
		psIni->afManFall10[13] = atoi(pcTmpA+1);
		psIni->afManFall11[13] = atoi(pcTmpB+1);
		psIni->afManFall12[13] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall14=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[14] = atoi(pcTmp1+11);
		psIni->afManFall2[14] = atoi(pcTmp2+1);
		psIni->afManFall3[14] = atoi(pcTmp3+1);
		psIni->afManFall4[14] = atoi(pcTmp4+1);
		psIni->afManFall5[14] = atoi(pcTmp5+1);
		psIni->afManFall6[14] = atoi(pcTmp6+1);
		psIni->afManFall7[14] = atoi(pcTmp7+1);
		psIni->afManFall8[14] = atoi(pcTmp8+1);
		psIni->afManFall9[14] = atoi(pcTmp9+1);
		psIni->afManFall10[14] = atoi(pcTmpA+1);
		psIni->afManFall11[14] = atoi(pcTmpB+1);
		psIni->afManFall12[14] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall15=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[15] = atoi(pcTmp1+11);
		psIni->afManFall2[15] = atoi(pcTmp2+1);
		psIni->afManFall3[15] = atoi(pcTmp3+1);
		psIni->afManFall4[15] = atoi(pcTmp4+1);
		psIni->afManFall5[15] = atoi(pcTmp5+1);
		psIni->afManFall6[15] = atoi(pcTmp6+1);
		psIni->afManFall7[15] = atoi(pcTmp7+1);
		psIni->afManFall8[15] = atoi(pcTmp8+1);
		psIni->afManFall9[15] = atoi(pcTmp9+1);
		psIni->afManFall10[15] = atoi(pcTmpA+1);
		psIni->afManFall11[15] = atoi(pcTmpB+1);
		psIni->afManFall12[15] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall16=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[16] = atoi(pcTmp1+11);
		psIni->afManFall2[16] = atoi(pcTmp2+1);
		psIni->afManFall3[16] = atoi(pcTmp3+1);
		psIni->afManFall4[16] = atoi(pcTmp4+1);
		psIni->afManFall5[16] = atoi(pcTmp5+1);
		psIni->afManFall6[16] = atoi(pcTmp6+1);
		psIni->afManFall7[16] = atoi(pcTmp7+1);
		psIni->afManFall8[16] = atoi(pcTmp8+1);
		psIni->afManFall9[16] = atoi(pcTmp9+1);
		psIni->afManFall10[16] = atoi(pcTmpA+1);
		psIni->afManFall11[16] = atoi(pcTmpB+1);
		psIni->afManFall12[16] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall17=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[17] = atoi(pcTmp1+11);
		psIni->afManFall2[17] = atoi(pcTmp2+1);
		psIni->afManFall3[17] = atoi(pcTmp3+1);
		psIni->afManFall4[17] = atoi(pcTmp4+1);
		psIni->afManFall5[17] = atoi(pcTmp5+1);
		psIni->afManFall6[17] = atoi(pcTmp6+1);
		psIni->afManFall7[17] = atoi(pcTmp7+1);
		psIni->afManFall8[17] = atoi(pcTmp8+1);
		psIni->afManFall9[17] = atoi(pcTmp9+1);
		psIni->afManFall10[17] = atoi(pcTmpA+1);
		psIni->afManFall11[17] = atoi(pcTmpB+1);
		psIni->afManFall12[17] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall18=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[18] = atoi(pcTmp1+11);
		psIni->afManFall2[18] = atoi(pcTmp2+1);
		psIni->afManFall3[18] = atoi(pcTmp3+1);
		psIni->afManFall4[18] = atoi(pcTmp4+1);
		psIni->afManFall5[18] = atoi(pcTmp5+1);
		psIni->afManFall6[18] = atoi(pcTmp6+1);
		psIni->afManFall7[18] = atoi(pcTmp7+1);
		psIni->afManFall8[18] = atoi(pcTmp8+1);
		psIni->afManFall9[18] = atoi(pcTmp9+1);
		psIni->afManFall10[18] = atoi(pcTmpA+1);
		psIni->afManFall11[18] = atoi(pcTmpB+1);
		psIni->afManFall12[18] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall19=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[19] = atoi(pcTmp1+11);
		psIni->afManFall2[19] = atoi(pcTmp2+1);
		psIni->afManFall3[19] = atoi(pcTmp3+1);
		psIni->afManFall4[19] = atoi(pcTmp4+1);
		psIni->afManFall5[19] = atoi(pcTmp5+1);
		psIni->afManFall6[19] = atoi(pcTmp6+1);
		psIni->afManFall7[19] = atoi(pcTmp7+1);
		psIni->afManFall8[19] = atoi(pcTmp8+1);
		psIni->afManFall9[19] = atoi(pcTmp9+1);
		psIni->afManFall10[19] = atoi(pcTmpA+1);
		psIni->afManFall11[19] = atoi(pcTmpB+1);
		psIni->afManFall12[19] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall20=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[20] = atoi(pcTmp1+11);
		psIni->afManFall2[20] = atoi(pcTmp2+1);
		psIni->afManFall3[20] = atoi(pcTmp3+1);
		psIni->afManFall4[20] = atoi(pcTmp4+1);
		psIni->afManFall5[20] = atoi(pcTmp5+1);
		psIni->afManFall6[20] = atoi(pcTmp6+1);
		psIni->afManFall7[20] = atoi(pcTmp7+1);
		psIni->afManFall8[20] = atoi(pcTmp8+1);
		psIni->afManFall9[20] = atoi(pcTmp9+1);
		psIni->afManFall10[20] = atoi(pcTmpA+1);
		psIni->afManFall11[20] = atoi(pcTmpB+1);
		psIni->afManFall12[20] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall21=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[21] = atoi(pcTmp1+11);
		psIni->afManFall2[21] = atoi(pcTmp2+1);
		psIni->afManFall3[21] = atoi(pcTmp3+1);
		psIni->afManFall4[21] = atoi(pcTmp4+1);
		psIni->afManFall5[21] = atoi(pcTmp5+1);
		psIni->afManFall6[21] = atoi(pcTmp6+1);
		psIni->afManFall7[21] = atoi(pcTmp7+1);
		psIni->afManFall8[21] = atoi(pcTmp8+1);
		psIni->afManFall9[21] = atoi(pcTmp9+1);
		psIni->afManFall10[21] = atoi(pcTmpA+1);
		psIni->afManFall11[21] = atoi(pcTmpB+1);
		psIni->afManFall12[21] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall22=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[22] = atoi(pcTmp1+11);
		psIni->afManFall2[22] = atoi(pcTmp2+1);
		psIni->afManFall3[22] = atoi(pcTmp3+1);
		psIni->afManFall4[22] = atoi(pcTmp4+1);
		psIni->afManFall5[22] = atoi(pcTmp5+1);
		psIni->afManFall6[22] = atoi(pcTmp6+1);
		psIni->afManFall7[22] = atoi(pcTmp7+1);
		psIni->afManFall8[22] = atoi(pcTmp8+1);
		psIni->afManFall9[22] = atoi(pcTmp9+1);
		psIni->afManFall10[22] = atoi(pcTmpA+1);
		psIni->afManFall11[22] = atoi(pcTmpB+1);
		psIni->afManFall12[22] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "freeFall23=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afManFall1[23] = atoi(pcTmp1+11);
		psIni->afManFall2[23] = atoi(pcTmp2+1);
		psIni->afManFall3[23] = atoi(pcTmp3+1);
		psIni->afManFall4[23] = atoi(pcTmp4+1);
		psIni->afManFall5[23] = atoi(pcTmp5+1);
		psIni->afManFall6[23] = atoi(pcTmp6+1);
		psIni->afManFall7[23] = atoi(pcTmp7+1);
		psIni->afManFall8[23] = atoi(pcTmp8+1);
		psIni->afManFall9[23] = atoi(pcTmp9+1);
		psIni->afManFall10[23] = atoi(pcTmpA+1);
		psIni->afManFall11[23] = atoi(pcTmpB+1);
		psIni->afManFall12[23] = atoi(pcTmpC+1);
	}
	
	// --------------------------------------------  adapt
	if(((pcTmp1 = strstr(pcCfg, "adapt0=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[0] = atoi(pcTmp1+7);
		psIni->afAdapt2[0] = atoi(pcTmp2+1);
		psIni->afAdapt3[0] = atoi(pcTmp3+1);
		psIni->afAdapt4[0] = atoi(pcTmp4+1);
		psIni->afAdapt5[0] = atoi(pcTmp5+1);
		psIni->afAdapt6[0] = atoi(pcTmp6+1);
		psIni->afAdapt7[0] = atoi(pcTmp7+1);
		psIni->afAdapt8[0] = atoi(pcTmp8+1);
		psIni->afAdapt9[0] = atoi(pcTmp9+1);
		psIni->afAdapt10[0] = atoi(pcTmpA+1);
		psIni->afAdapt11[0] = atoi(pcTmpB+1);
		psIni->afAdapt12[0] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[1] = atoi(pcTmp1+7);
		psIni->afAdapt2[1] = atoi(pcTmp2+1);
		psIni->afAdapt3[1] = atoi(pcTmp3+1);
		psIni->afAdapt4[1] = atoi(pcTmp4+1);
		psIni->afAdapt5[1] = atoi(pcTmp5+1);
		psIni->afAdapt6[1] = atoi(pcTmp6+1);
		psIni->afAdapt7[1] = atoi(pcTmp7+1);
		psIni->afAdapt8[1] = atoi(pcTmp8+1);
		psIni->afAdapt9[1] = atoi(pcTmp9+1);
		psIni->afAdapt10[1] = atoi(pcTmpA+1);
		psIni->afAdapt11[1] = atoi(pcTmpB+1);
		psIni->afAdapt12[1] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[2] = atoi(pcTmp1+7);
		psIni->afAdapt2[2] = atoi(pcTmp2+1);
		psIni->afAdapt3[2] = atoi(pcTmp3+1);
		psIni->afAdapt4[2] = atoi(pcTmp4+1);
		psIni->afAdapt5[2] = atoi(pcTmp5+1);
		psIni->afAdapt6[2] = atoi(pcTmp6+1);
		psIni->afAdapt7[2] = atoi(pcTmp7+1);
		psIni->afAdapt8[2] = atoi(pcTmp8+1);
		psIni->afAdapt9[2] = atoi(pcTmp9+1);
		psIni->afAdapt10[2] = atoi(pcTmpA+1);
		psIni->afAdapt11[2] = atoi(pcTmpB+1);
		psIni->afAdapt12[2] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[3] = atoi(pcTmp1+7);
		psIni->afAdapt2[3] = atoi(pcTmp2+1);
		psIni->afAdapt3[3] = atoi(pcTmp3+1);
		psIni->afAdapt4[3] = atoi(pcTmp4+1);
		psIni->afAdapt5[3] = atoi(pcTmp5+1);
		psIni->afAdapt6[3] = atoi(pcTmp6+1);
		psIni->afAdapt7[3] = atoi(pcTmp7+1);
		psIni->afAdapt8[3] = atoi(pcTmp8+1);
		psIni->afAdapt9[3] = atoi(pcTmp9+1);
		psIni->afAdapt10[3] = atoi(pcTmpA+1);
		psIni->afAdapt11[3] = atoi(pcTmpB+1);
		psIni->afAdapt12[3] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[4] = atoi(pcTmp1+7);
		psIni->afAdapt2[4] = atoi(pcTmp2+1);
		psIni->afAdapt3[4] = atoi(pcTmp3+1);
		psIni->afAdapt4[4] = atoi(pcTmp4+1);
		psIni->afAdapt5[4] = atoi(pcTmp5+1);
		psIni->afAdapt6[4] = atoi(pcTmp6+1);
		psIni->afAdapt7[4] = atoi(pcTmp7+1);
		psIni->afAdapt8[4] = atoi(pcTmp8+1);
		psIni->afAdapt9[4] = atoi(pcTmp9+1);
		psIni->afAdapt10[4] = atoi(pcTmpA+1);
		psIni->afAdapt11[4] = atoi(pcTmpB+1);
		psIni->afAdapt12[4] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt5=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[5] = atoi(pcTmp1+7);
		psIni->afAdapt2[5] = atoi(pcTmp2+1);
		psIni->afAdapt3[5] = atoi(pcTmp3+1);
		psIni->afAdapt4[5] = atoi(pcTmp4+1);
		psIni->afAdapt5[5] = atoi(pcTmp5+1);
		psIni->afAdapt6[5] = atoi(pcTmp6+1);
		psIni->afAdapt7[5] = atoi(pcTmp7+1);
		psIni->afAdapt8[5] = atoi(pcTmp8+1);
		psIni->afAdapt9[5] = atoi(pcTmp9+1);
		psIni->afAdapt10[5] = atoi(pcTmpA+1);
		psIni->afAdapt11[5] = atoi(pcTmpB+1);
		psIni->afAdapt12[5] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt6=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[6] = atoi(pcTmp1+7);
		psIni->afAdapt2[6] = atoi(pcTmp2+1);
		psIni->afAdapt3[6] = atoi(pcTmp3+1);
		psIni->afAdapt4[6] = atoi(pcTmp4+1);
		psIni->afAdapt5[6] = atoi(pcTmp5+1);
		psIni->afAdapt6[6] = atoi(pcTmp6+1);
		psIni->afAdapt7[6] = atoi(pcTmp7+1);
		psIni->afAdapt8[6] = atoi(pcTmp8+1);
		psIni->afAdapt9[6] = atoi(pcTmp9+1);
		psIni->afAdapt10[6] = atoi(pcTmpA+1);
		psIni->afAdapt11[6] = atoi(pcTmpB+1);
		psIni->afAdapt12[6] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt7=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[7] = atoi(pcTmp1+7);
		psIni->afAdapt2[7] = atoi(pcTmp2+1);
		psIni->afAdapt3[7] = atoi(pcTmp3+1);
		psIni->afAdapt4[7] = atoi(pcTmp4+1);
		psIni->afAdapt5[7] = atoi(pcTmp5+1);
		psIni->afAdapt6[7] = atoi(pcTmp6+1);
		psIni->afAdapt7[7] = atoi(pcTmp7+1);
		psIni->afAdapt8[7] = atoi(pcTmp8+1);
		psIni->afAdapt9[7] = atoi(pcTmp9+1);
		psIni->afAdapt10[7] = atoi(pcTmpA+1);
		psIni->afAdapt11[7] = atoi(pcTmpB+1);
		psIni->afAdapt12[7] = atoi(pcTmpC+1);
	}	
	if(((pcTmp1 = strstr(pcCfg, "adapt8=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[8] = atoi(pcTmp1+7);
		psIni->afAdapt2[8] = atoi(pcTmp2+1);
		psIni->afAdapt3[8] = atoi(pcTmp3+1);
		psIni->afAdapt4[8] = atoi(pcTmp4+1);
		psIni->afAdapt5[8] = atoi(pcTmp5+1);
		psIni->afAdapt6[8] = atoi(pcTmp6+1);
		psIni->afAdapt7[8] = atoi(pcTmp7+1);
		psIni->afAdapt8[8] = atoi(pcTmp8+1);
		psIni->afAdapt9[8] = atoi(pcTmp9+1);
		psIni->afAdapt10[8] = atoi(pcTmpA+1);
		psIni->afAdapt11[8] = atoi(pcTmpB+1);
		psIni->afAdapt12[8] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt9=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[9] = atoi(pcTmp1+7);
		psIni->afAdapt2[9] = atoi(pcTmp2+1);
		psIni->afAdapt3[9] = atoi(pcTmp3+1);
		psIni->afAdapt4[9] = atoi(pcTmp4+1);
		psIni->afAdapt5[9] = atoi(pcTmp5+1);
		psIni->afAdapt6[9] = atoi(pcTmp6+1);
		psIni->afAdapt7[9] = atoi(pcTmp7+1);
		psIni->afAdapt8[9] = atoi(pcTmp8+1);
		psIni->afAdapt9[9] = atoi(pcTmp9+1);
		psIni->afAdapt10[9] = atoi(pcTmpA+1);
		psIni->afAdapt11[9] = atoi(pcTmpB+1);
		psIni->afAdapt12[9] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adaptA=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[10] = atoi(pcTmp1+7);
		psIni->afAdapt2[10] = atoi(pcTmp2+1);
		psIni->afAdapt3[10] = atoi(pcTmp3+1);
		psIni->afAdapt4[10] = atoi(pcTmp4+1);
		psIni->afAdapt5[10] = atoi(pcTmp5+1);
		psIni->afAdapt6[10] = atoi(pcTmp6+1);
		psIni->afAdapt7[10] = atoi(pcTmp7+1);
		psIni->afAdapt8[10] = atoi(pcTmp8+1);
		psIni->afAdapt9[10] = atoi(pcTmp9+1);
		psIni->afAdapt10[10] = atoi(pcTmpA+1);
		psIni->afAdapt11[10] = atoi(pcTmpB+1);
		psIni->afAdapt12[10] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adaptB=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[11] = atoi(pcTmp1+7);
		psIni->afAdapt2[11] = atoi(pcTmp2+1);
		psIni->afAdapt3[11] = atoi(pcTmp3+1);
		psIni->afAdapt4[11] = atoi(pcTmp4+1);
		psIni->afAdapt5[11] = atoi(pcTmp5+1);
		psIni->afAdapt6[11] = atoi(pcTmp6+1);
		psIni->afAdapt7[11] = atoi(pcTmp7+1);
		psIni->afAdapt8[11] = atoi(pcTmp8+1);
		psIni->afAdapt9[11] = atoi(pcTmp9+1);
		psIni->afAdapt10[11] = atoi(pcTmpA+1);
		psIni->afAdapt11[11] = atoi(pcTmpB+1);
		psIni->afAdapt12[11] = atoi(pcTmpC+1);
	}
	// --------------------------------------------  free fall extended
	if(((pcTmp1 = strstr(pcCfg, "adapt12=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[12] = atoi(pcTmp1+8);
		psIni->afAdapt2[12] = atoi(pcTmp2+1);
		psIni->afAdapt3[12] = atoi(pcTmp3+1);
		psIni->afAdapt4[12] = atoi(pcTmp4+1);
		psIni->afAdapt5[12] = atoi(pcTmp5+1);
		psIni->afAdapt6[12] = atoi(pcTmp6+1);
		psIni->afAdapt7[12] = atoi(pcTmp7+1);
		psIni->afAdapt8[12] = atoi(pcTmp8+1);
		psIni->afAdapt9[12] = atoi(pcTmp9+1);
		psIni->afAdapt10[12] = atoi(pcTmpA+1);
		psIni->afAdapt11[12] = atoi(pcTmpB+1);
		psIni->afAdapt12[12] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt13=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[13] = atoi(pcTmp1+8);
		psIni->afAdapt2[13] = atoi(pcTmp2+1);
		psIni->afAdapt3[13] = atoi(pcTmp3+1);
		psIni->afAdapt4[13] = atoi(pcTmp4+1);
		psIni->afAdapt5[13] = atoi(pcTmp5+1);
		psIni->afAdapt6[13] = atoi(pcTmp6+1);
		psIni->afAdapt7[13] = atoi(pcTmp7+1);
		psIni->afAdapt8[13] = atoi(pcTmp8+1);
		psIni->afAdapt9[13] = atoi(pcTmp9+1);
		psIni->afAdapt10[13] = atoi(pcTmpA+1);
		psIni->afAdapt11[13] = atoi(pcTmpB+1);
		psIni->afAdapt12[13] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt14=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[14] = atoi(pcTmp1+8);
		psIni->afAdapt2[14] = atoi(pcTmp2+1);
		psIni->afAdapt3[14] = atoi(pcTmp3+1);
		psIni->afAdapt4[14] = atoi(pcTmp4+1);
		psIni->afAdapt5[14] = atoi(pcTmp5+1);
		psIni->afAdapt6[14] = atoi(pcTmp6+1);
		psIni->afAdapt7[14] = atoi(pcTmp7+1);
		psIni->afAdapt8[14] = atoi(pcTmp8+1);
		psIni->afAdapt9[14] = atoi(pcTmp9+1);
		psIni->afAdapt10[14] = atoi(pcTmpA+1);
		psIni->afAdapt11[14] = atoi(pcTmpB+1);
		psIni->afAdapt12[14] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt15=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[15] = atoi(pcTmp1+8);
		psIni->afAdapt2[15] = atoi(pcTmp2+1);
		psIni->afAdapt3[15] = atoi(pcTmp3+1);
		psIni->afAdapt4[15] = atoi(pcTmp4+1);
		psIni->afAdapt5[15] = atoi(pcTmp5+1);
		psIni->afAdapt6[15] = atoi(pcTmp6+1);
		psIni->afAdapt7[15] = atoi(pcTmp7+1);
		psIni->afAdapt8[15] = atoi(pcTmp8+1);
		psIni->afAdapt9[15] = atoi(pcTmp9+1);
		psIni->afAdapt10[15] = atoi(pcTmpA+1);
		psIni->afAdapt11[15] = atoi(pcTmpB+1);
		psIni->afAdapt12[15] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt16=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[16] = atoi(pcTmp1+8);
		psIni->afAdapt2[16] = atoi(pcTmp2+1);
		psIni->afAdapt3[16] = atoi(pcTmp3+1);
		psIni->afAdapt4[16] = atoi(pcTmp4+1);
		psIni->afAdapt5[16] = atoi(pcTmp5+1);
		psIni->afAdapt6[16] = atoi(pcTmp6+1);
		psIni->afAdapt7[16] = atoi(pcTmp7+1);
		psIni->afAdapt8[16] = atoi(pcTmp8+1);
		psIni->afAdapt9[16] = atoi(pcTmp9+1);
		psIni->afAdapt10[16] = atoi(pcTmpA+1);
		psIni->afAdapt11[16] = atoi(pcTmpB+1);
		psIni->afAdapt12[16] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt17=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[17] = atoi(pcTmp1+8);
		psIni->afAdapt2[17] = atoi(pcTmp2+1);
		psIni->afAdapt3[17] = atoi(pcTmp3+1);
		psIni->afAdapt4[17] = atoi(pcTmp4+1);
		psIni->afAdapt5[17] = atoi(pcTmp5+1);
		psIni->afAdapt6[17] = atoi(pcTmp6+1);
		psIni->afAdapt7[17] = atoi(pcTmp7+1);
		psIni->afAdapt8[17] = atoi(pcTmp8+1);
		psIni->afAdapt9[17] = atoi(pcTmp9+1);
		psIni->afAdapt10[17] = atoi(pcTmpA+1);
		psIni->afAdapt11[17] = atoi(pcTmpB+1);
		psIni->afAdapt12[17] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt18=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[18] = atoi(pcTmp1+8);
		psIni->afAdapt2[18] = atoi(pcTmp2+1);
		psIni->afAdapt3[18] = atoi(pcTmp3+1);
		psIni->afAdapt4[18] = atoi(pcTmp4+1);
		psIni->afAdapt5[18] = atoi(pcTmp5+1);
		psIni->afAdapt6[18] = atoi(pcTmp6+1);
		psIni->afAdapt7[18] = atoi(pcTmp7+1);
		psIni->afAdapt8[18] = atoi(pcTmp8+1);
		psIni->afAdapt9[18] = atoi(pcTmp9+1);
		psIni->afAdapt10[18] = atoi(pcTmpA+1);
		psIni->afAdapt11[18] = atoi(pcTmpB+1);
		psIni->afAdapt12[18] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt19=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[19] = atoi(pcTmp1+8);
		psIni->afAdapt2[19] = atoi(pcTmp2+1);
		psIni->afAdapt3[19] = atoi(pcTmp3+1);
		psIni->afAdapt4[19] = atoi(pcTmp4+1);
		psIni->afAdapt5[19] = atoi(pcTmp5+1);
		psIni->afAdapt6[19] = atoi(pcTmp6+1);
		psIni->afAdapt7[19] = atoi(pcTmp7+1);
		psIni->afAdapt8[19] = atoi(pcTmp8+1);
		psIni->afAdapt9[19] = atoi(pcTmp9+1);
		psIni->afAdapt10[19] = atoi(pcTmpA+1);
		psIni->afAdapt11[19] = atoi(pcTmpB+1);
		psIni->afAdapt12[19] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt20=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[20] = atoi(pcTmp1+8);
		psIni->afAdapt2[20] = atoi(pcTmp2+1);
		psIni->afAdapt3[20] = atoi(pcTmp3+1);
		psIni->afAdapt4[20] = atoi(pcTmp4+1);
		psIni->afAdapt5[20] = atoi(pcTmp5+1);
		psIni->afAdapt6[20] = atoi(pcTmp6+1);
		psIni->afAdapt7[20] = atoi(pcTmp7+1);
		psIni->afAdapt8[20] = atoi(pcTmp8+1);
		psIni->afAdapt9[20] = atoi(pcTmp9+1);
		psIni->afAdapt10[20] = atoi(pcTmpA+1);
		psIni->afAdapt11[20] = atoi(pcTmpB+1);
		psIni->afAdapt12[20] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt21=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[21] = atoi(pcTmp1+8);
		psIni->afAdapt2[21] = atoi(pcTmp2+1);
		psIni->afAdapt3[21] = atoi(pcTmp3+1);
		psIni->afAdapt4[21] = atoi(pcTmp4+1);
		psIni->afAdapt5[21] = atoi(pcTmp5+1);
		psIni->afAdapt6[21] = atoi(pcTmp6+1);
		psIni->afAdapt7[21] = atoi(pcTmp7+1);
		psIni->afAdapt8[21] = atoi(pcTmp8+1);
		psIni->afAdapt9[21] = atoi(pcTmp9+1);
		psIni->afAdapt10[21] = atoi(pcTmpA+1);
		psIni->afAdapt11[21] = atoi(pcTmpB+1);
		psIni->afAdapt12[21] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt22=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[22] = atoi(pcTmp1+8);
		psIni->afAdapt2[22] = atoi(pcTmp2+1);
		psIni->afAdapt3[22] = atoi(pcTmp3+1);
		psIni->afAdapt4[22] = atoi(pcTmp4+1);
		psIni->afAdapt5[22] = atoi(pcTmp5+1);
		psIni->afAdapt6[22] = atoi(pcTmp6+1);
		psIni->afAdapt7[22] = atoi(pcTmp7+1);
		psIni->afAdapt8[22] = atoi(pcTmp8+1);
		psIni->afAdapt9[22] = atoi(pcTmp9+1);
		psIni->afAdapt10[22] = atoi(pcTmpA+1);
		psIni->afAdapt11[22] = atoi(pcTmpB+1);
		psIni->afAdapt12[22] = atoi(pcTmpC+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "adapt23=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
	&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
	&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
	&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
	&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
	&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
	&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
	&& ((pcTmpA = strchr(pcTmp9+1, ',')) != NULL)
	&& ((pcTmpB = strchr(pcTmpA+1, ',')) != NULL)
	&& ((pcTmpC = strchr(pcTmpB+1, ',')) != NULL)
	&& ((pcTmpD = strchr(pcTmpC+1, ',')) != NULL)
	)
	{
		psIni->afAdapt1[23] = atoi(pcTmp1+8);
		psIni->afAdapt2[23] = atoi(pcTmp2+1);
		psIni->afAdapt3[23] = atoi(pcTmp3+1);
		psIni->afAdapt4[23] = atoi(pcTmp4+1);
		psIni->afAdapt5[23] = atoi(pcTmp5+1);
		psIni->afAdapt6[23] = atoi(pcTmp6+1);
		psIni->afAdapt7[23] = atoi(pcTmp7+1);
		psIni->afAdapt8[23] = atoi(pcTmp8+1);
		psIni->afAdapt9[23] = atoi(pcTmp9+1);
		psIni->afAdapt10[23] = atoi(pcTmpA+1);
		psIni->afAdapt11[23] = atoi(pcTmpB+1);
		psIni->afAdapt12[23] = atoi(pcTmpC+1);
	}
	
	//---------------------------------------------- CAMs
	if(((pcTmp1 = strstr(pcCfg, "cam1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+5) < pcTmp2)
			pAll->pCam1 = gcnew Uri(gcnew String(pcTmp1+5));
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "cam2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+5) < pcTmp2)
			pAll->pCam2 = gcnew Uri(gcnew String(pcTmp1+5));
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "cam3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+5) < pcTmp2)
			pAll->pCam3 = gcnew Uri(gcnew String(pcTmp1+5));
		*pcTmp2 = ',';
	}
	
	if(((pcTmp1 = strstr(pcCfg, "cam4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+5) < pcTmp2)
			pAll->pCam4 = gcnew Uri(gcnew String(pcTmp1+5));
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "cam5=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+5) < pcTmp2)
			pAll->pCam5 = gcnew Uri(gcnew String(pcTmp1+5));
		*pcTmp2 = ',';
	}
	if(((pcTmp1 = strstr(pcCfg, "cam6=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		*pcTmp2 = 0;
		if((pcTmp1+5) < pcTmp2)
			pAll->pCam6 = gcnew Uri(gcnew String(pcTmp1+5));
		*pcTmp2 = ',';
	}
	
	//------------------------------------------------silos max
	if(((pcTmp1 = strstr(pcCfg, "silo1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax1 = atoi(pcTmp1+6);
	}
	if(((pcTmp1 = strstr(pcCfg, "silo2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax2 = atoi(pcTmp1+6);
	}
	if(((pcTmp1 = strstr(pcCfg, "silo3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax3 = atoi(pcTmp1+6);
	}
	
	if(((pcTmp1 = strstr(pcCfg, "silo4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax4 = atoi(pcTmp1+6);
	}
	if(((pcTmp1 = strstr(pcCfg, "silo5=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax5 = atoi(pcTmp1+6);
	}
	if(((pcTmp1 = strstr(pcCfg, "silo6=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax6 = atoi(pcTmp1+6);
	}
	if(((pcTmp1 = strstr(pcCfg, "silo7=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax7 = atoi(pcTmp1+6);
	}
	if(((pcTmp1 = strstr(pcCfg, "silo8=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax8 = atoi(pcTmp1+6);
	}

	if(((pcTmp1 = strstr(pcCfg, "silo9=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax9 = atoi(pcTmp1+6);
	}
	//DC 3.3.0
	if(((pcTmp1 = strstr(pcCfg, "silo10=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax10 = atoi(pcTmp1+7);
	}
	if(((pcTmp1 = strstr(pcCfg, "silo11=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax11 = atoi(pcTmp1+7);
	}

	if(((pcTmp1 = strstr(pcCfg, "silo12=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->fSiloMax12 = atoi(pcTmp1+7);
	}
	
		//---------------------------------------------silos fill
	if(((pcTmp1 = strstr(pcCfg, "fill1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill1 = atoi(pcTmp1+6);
		psIni->nSiloJog1 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill2 = atoi(pcTmp1+6);
		psIni->nSiloJog2 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill3 = atoi(pcTmp1+6);
		psIni->nSiloJog3 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill4 = atoi(pcTmp1+6);
		psIni->nSiloJog4 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill5=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill5 = atoi(pcTmp1+6);
		psIni->nSiloJog5 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill6=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill6 = atoi(pcTmp1+6);
		psIni->nSiloJog6 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill7=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill7 = atoi(pcTmp1+6);
		psIni->nSiloJog7 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill8=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill8 = atoi(pcTmp1+6);
		psIni->nSiloJog8 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill9=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill9 = atoi(pcTmp1+6);
		psIni->nSiloJog9 = atoi(pcTmp2+1);
	}
	//DC 3.3.0
	if(((pcTmp1 = strstr(pcCfg, "fill10=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill10 = atoi(pcTmp1+7);
		psIni->nSiloJog10 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill11=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill11 = atoi(pcTmp1+7);
		psIni->nSiloJog11 = atoi(pcTmp2+1);
	}
	if(((pcTmp1 = strstr(pcCfg, "fill12=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		psIni->fSiloFill12 = atoi(pcTmp1+7);
		psIni->nSiloJog12 = atoi(pcTmp2+1);
	}
	
	//------------------------------------------------print ticket
	if(((pcTmp1 = strstr(pcCfg, "lineLen=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sTic.nLineLen = atoi(pcTmp1+8);
		if(psIni->sTic.nLineLen > 80) psIni->sTic.nLineLen = 80;
	}	
	if(((pcTmp1 = strstr(pcCfg, "lineNum=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->sTic.nLineNum = atoi(pcTmp1+8);
		if(psIni->sTic.nLineNum > 66) psIni->sTic.nLineNum = 66;
	}
	//------------------------------------------------ticket layout
	if(((pcTmp1 = strstr(pcCfg, "plant_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nPlantNum = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}	
	if(((pcTmp1 = strstr(pcCfg, "silo_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nSiloNum = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}	
	//DC 4.1.2
	if(((pcTmp1 = strstr(pcCfg, "lane_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nLaneNum = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "ticket_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTicket = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "truck_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTruck = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "drops_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDrops = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "customer_name_1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+16);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nCustomer = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "mix_code=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nMixCode = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "load_size=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTarget = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "load=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+5);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nLoad = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "tare=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+5);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTruckTare = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "gross=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+6);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nGross = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "date=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+5);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDate = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "time=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+5);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTime = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "tic_tax=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+8);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTax = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "mix_price=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nMixPrice = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "total_price=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+12);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTotal = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	
	if(((pcTmp1 = strstr(pcCfg, "subtotal=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nSubtotal = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "del_addr_1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDelAddr1 = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}	
	if(((pcTmp1 = strstr(pcCfg, "del_addr_2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDelAddr2 = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}	
	if(((pcTmp1 = strstr(pcCfg, "del_inst_1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDelInst1 = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}	
	if(((pcTmp1 = strstr(pcCfg, "del_inst_2=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDelInst2 = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "del_inst_3=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDelInst3 = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "del_inst_4=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDelInst4 = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "mix_desc=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nMixDesc = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "po_number=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nPoNum = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "order_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nOrderNum = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	//DC 4.0.7
	if(((pcTmp1 = strstr(pcCfg, "driver_name=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+12);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nDriverName = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "zone=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+5);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nZone = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "project_code=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+13);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nProjCode = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "lot_num=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+8);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nLotNum = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "loads_delivered=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+16);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nLoadsDlvrd = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "job_name=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nJobName = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "unit=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+5);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nUnit = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "order_cum_total=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+16);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nOrderNumTotal = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}
	if(((pcTmp1 = strstr(pcCfg, "cum_qty=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+8);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nCumQty = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "cust_code=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+10);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nCustCode = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "order_id=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nOrderId = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "load_tax=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+9);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nLoadTax = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "grand_total=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+12);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nGrandTotal = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	//DC 3.2.8 ----------------------------------------------------------------
	if(((pcTmp1 = strstr(pcCfg, "gross_tn_lb=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+12);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nGrossTNtoLB = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "tare_tn_lb=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nTruckTareTNtoLB = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "load_tn_lb=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+11);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nLoadTNtoLB = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	if(((pcTmp1 = strstr(pcCfg, "order_cum_total_tn_lb=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
	&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
	    *pcTmp2 = 0;
	    *pcTmp3 = 0;
		line = atoi(pcTmp1+22);
		col = atoi(pcTmp2+1);
		if(line > 0)
			psIni->sTic.nOrderNumTotalTNtoLB = (line-1)*psIni->sTic.nLineLen + col-1;
		*pcTmp2 = ',';	
		*pcTmp3 = ',';	
	}

	//-------------------------------------------------------------------------
	if(((pcTmp1 = strstr(pcCfg, "extra_line=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL))
	{
		line = atoi(pcTmp1+11);
		if(line > 0)
		{
			psTic->nExtraLine = ((int)line-1)*psTic->nLineLen;
		}
	}
	if(((pcTmp1 = strstr(pcCfg, "extra_max=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExtraMax = atoi(pcTmp1+10);
	}
	//--------------------------------------------------
	if(((pcTmp1 = strstr(pcCfg, "ex_load=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExLoad = atoi(pcTmp1+8);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_name=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExName = atoi(pcTmp1+8);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_desc=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExDesc = atoi(pcTmp1+8);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_unit=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExUnit = atoi(pcTmp1+8);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_price=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExPrice = atoi(pcTmp1+9);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_amount=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExAmount = atoi(pcTmp1+10);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_order=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExOrder = atoi(pcTmp1+9);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_cum=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExCum = atoi(pcTmp1+7);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_long=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExLong = atoi(pcTmp1+8);
	}
	if(((pcTmp1 = strstr(pcCfg, "ex_price_um=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psTic->nExPriceUm = atoi(pcTmp1+12);
	}

	//---------------------------------------------scale data layout-----------
	if(((pcTmp1 = strstr(pcCfg, "scaleSchar=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->cSclSchar = *(pcTmp1+11);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scaleFrame=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->cSclFrame = atoi(pcTmp1+11);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scaleLen=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nSclLen = atoi(pcTmp1+9);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scaleSign=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nSclSign = atoi(pcTmp1+10);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scale1000=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScl1000 = atoi(pcTmp1+10);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scale100=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScl100 = atoi(pcTmp1+9);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scale10=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScl10 = atoi(pcTmp1+8);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scale1=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScl1 = atoi(pcTmp1+7);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scale01=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScl01 = atoi(pcTmp1+8);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scale001=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScl001 = atoi(pcTmp1+9);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scaleRedLo=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScaleRedLo = atoi(pcTmp1+11);
	}	
	if(((pcTmp1 = strstr(pcCfg, "scaleRedHi=")) != NULL)
	&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
	{
		psIni->nScaleRedHi = atoi(pcTmp1+11);
	}	

	// text fields ------------------------------------------------------------
		if(((pcTmp1 = strstr(pcCfg, "text00=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[0].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[0].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[0].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[0].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text01=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[1].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[1].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[1].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[1].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text02=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[2].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[2].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[2].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[2].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text03=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[3].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[3].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[3].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[3].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text04=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[4].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[4].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[4].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[4].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text05=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[5].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[5].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[5].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[5].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text06=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[6].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[6].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[6].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[6].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text07=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[7].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[7].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[7].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[7].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text08=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[8].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[8].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[8].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[8].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text09=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[9].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[9].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[9].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[9].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text10=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[10].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[10].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[10].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[10].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text11=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[11].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[11].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[11].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[11].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text12=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[12].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[12].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[12].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[12].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text13=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[13].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[13].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[13].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[13].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text14=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[14].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[14].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[14].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[14].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text15=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[15].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[15].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[15].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[15].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text16=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[16].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[16].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[16].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[16].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text17=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[17].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[17].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[17].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[17].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text18=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[18].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[18].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[18].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[18].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text19=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[19].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[19].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[19].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[19].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text20=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[20].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[20].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[20].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[20].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text21=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[21].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[21].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[21].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[21].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text22=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[22].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[22].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[22].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[22].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text23=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[23].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[23].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[23].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[23].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text24=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[24].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[24].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[24].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[24].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text25=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[25].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[25].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[25].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[25].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text26=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[26].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[26].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[26].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[26].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text27=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[27].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[27].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[27].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[27].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text28=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[28].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[28].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[28].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[28].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text29=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[29].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[29].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[29].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[29].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text30=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[30].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[30].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[30].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[30].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text31=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[31].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[31].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[31].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[31].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text32=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[32].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[32].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[32].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[32].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text33=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[33].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[33].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[33].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[33].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text34=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[34].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[34].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[34].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[34].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text35=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[35].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[35].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[35].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[35].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text36=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[36].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[36].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[36].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[36].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text37=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[37].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[37].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[37].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[37].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text38=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[38].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[38].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[38].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[38].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}

		if(((pcTmp1 = strstr(pcCfg, "text39=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL))
		{
			line = atoi(pcTmp1+7);
			col = atoi(pcTmp2+1);
			if(line > 0 && col > 0)
			{
				strncpy_s(psIni->sTic.asText[39].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
				psIni->sTic.asText[39].nOffs = ((int)line-1)*psTic->nLineLen + (int)col-1;
				strncpy_s(psIni->sTic.asText[39].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
			}
			else
				strncpy_s(psIni->sTic.asText[39].acText, pcTmp3+1, pcTmp4-pcTmp3-1);
		}
	//-------------------------------------------------------------------------
	fclose(pfCfg);
	free(pcCfg);
	return 0;
}
#pragma region CFX
	//-----------------------------------------------------------------------------
	bool readCfgEx(All^ pAll)			//DC 4.0.0  , char* pcFile)
	{
		FILE *pfCfg;
		INI  *psIni = pAll->psIni;
		errno_t err;
		char *pcCfg;
		char acCfgFile[64];
		int size;
		int len;
		char *pcTmp1, *pcTmp2, *pcTmp3, *pcTmp4, *pcTmp5, *pcTmp6, *pcTmp7, *pcTmp8, *pcTmp9, *pcTmp10, *pcTmp11;
		char *pcTmp12, *pcTmp13, *pcTmp14, *pcTmp15, *pcTmp16, *pcTmp17, *pcTmp18, *pcTmp19, *pcTmp20, *pcTmp21;
		char* pcTmp22, * pcTmp23, * pcTmp24, * pcTmp25, * pcTmp26;// , * pcTmp27;
		//double dTmp;
		bool bRet = true;
		ulong64 nBit = 0;
		ulong64 nInp = 0;


		//printf("as: reading config file\n");
		sprintf_s(acCfgFile, "%sas.cfx", pAll->pcPath);
		
		try
		{

		err = fopen_s(&pfCfg, acCfgFile, "r");
		if(err != 0)
		{
			perror("config file missing. exit ...\n");
			return false;
		}
		size = _filelength(_fileno(pfCfg));
		
		pcCfg = (char *)malloc(size);
		if(pcCfg == NULL)
		{
			perror("config memory missing. exit ...\n");
			return false;
		}
		len = fread(pcCfg, 1, size, pfCfg);
		if(len <= 0)
		{
			perror("config file read error. exit ...\n");
			return false;	
		}

		/*try
		{
		if(fopen_s(&pfCfg, pcFile, "r") != 0)
		{
			pAll->stExc += "CFX file open error. exit ...";
			return false;   
		}
		size = _filelength(_fileno(pfCfg));

		pcCfg = (char *)malloc(size);
		if(pcCfg == NULL)
		{
			pAll->stExc += "CFX file memory error. exit ...";
			return false;   
		}
		len = (int)fread(pcCfg, 1, size, pfCfg);
		if(len == 0)
		{
			pAll->stExc += "CFX file read error. exit ...";
			free(pcCfg);
			return false;  
		}*/
		//------------------------------------ Silos
		if(((pcTmp1 = strstr(pcCfg, "silo1=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[0].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[0].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[0].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[0].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[0].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[0].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[0].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[0].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[0].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[0].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[0].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[0].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[0].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[0].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[0].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[0].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[0].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[0].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[0].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[0].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[0].fFall= atoi(pcTmp21+1);
			psIni->asSilos[0].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[0].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[0].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[0].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[0].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[0].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[0].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[0].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[0].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[0].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[0].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[0].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[0].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[0].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[0].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[0].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo2=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[1].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[1].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[1].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[1].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[1].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[1].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[1].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[1].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[1].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[1].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[1].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[1].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[1].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[1].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[1].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[1].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[1].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[1].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[1].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[1].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[1].fFall= atoi(pcTmp21+1);
			psIni->asSilos[1].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[1].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[1].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[1].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[1].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[1].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[1].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[1].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[1].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[1].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[1].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[1].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[1].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[1].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[1].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[1].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo3=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[2].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[2].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[2].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[2].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[2].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[2].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[2].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[2].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[2].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[2].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[2].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[2].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[2].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[2].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[2].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[2].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[2].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[2].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[2].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[2].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[2].fFall= atoi(pcTmp21+1);
			psIni->asSilos[2].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[2].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[2].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[2].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[2].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[2].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[2].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[2].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[2].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[2].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[2].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[2].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[2].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[2].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[2].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[2].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo4=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[3].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[3].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[3].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[3].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[3].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[3].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[3].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[3].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[3].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[3].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[3].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[3].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[3].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[3].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[3].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[3].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[3].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[3].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[3].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[3].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[3].fFall= atoi(pcTmp21+1);
			psIni->asSilos[3].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[3].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[3].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[3].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[3].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[3].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[3].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[3].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[3].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[3].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[3].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[3].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[3].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[3].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[3].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[3].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo5=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[4].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[4].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[4].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[4].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[4].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[4].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[4].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[4].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[4].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[4].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[4].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[4].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[4].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[4].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[4].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[4].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[4].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[4].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[4].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[4].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[4].fFall= atoi(pcTmp21+1);
			psIni->asSilos[4].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[4].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[4].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[4].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[4].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[4].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[4].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[4].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[4].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[4].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[4].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[4].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[4].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[4].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[4].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[4].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo6=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[5].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[5].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[5].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[5].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[5].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[5].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[5].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[5].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[5].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[5].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[5].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[5].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[5].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[5].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[5].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[5].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[5].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[5].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[5].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[5].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[5].fFall= atoi(pcTmp21+1);
			psIni->asSilos[5].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[5].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[5].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[5].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[5].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[5].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[5].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[5].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[5].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[5].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[5].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[5].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[5].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[5].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[5].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[5].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo7=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[6].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[6].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[6].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[6].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[6].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[6].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[6].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[6].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[6].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[6].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[6].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[6].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[6].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[6].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[6].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[6].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[6].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[6].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[6].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[6].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[6].fFall= atoi(pcTmp21+1);
			psIni->asSilos[6].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[6].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[6].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[6].acProduct, pcTmp25 + 1, pcTmp26 - pcTmp25 - 1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[6].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[6].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[6].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[6].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[6].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[6].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[6].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[6].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[6].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[6].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[6].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[6].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo8=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[7].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[7].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[7].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[7].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[7].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[7].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[7].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[7].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[7].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[7].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[7].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[7].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[7].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[7].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[7].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[7].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[7].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[7].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[7].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[7].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[7].fFall= atoi(pcTmp21+1);
			psIni->asSilos[7].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[7].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[7].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[7].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[7].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[7].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[7].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[7].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[7].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[7].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[7].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[7].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[7].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[7].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[7].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[7].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo9=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+6) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[8].acMat, pcTmp1+6, pcTmp2-pcTmp1-6);
			psIni->asSilos[8].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[8].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[8].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[8].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[8].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[8].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[8].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[8].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[8].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[8].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[8].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[8].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[8].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[8].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[8].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[8].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[8].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[8].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[8].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[8].fFall= atoi(pcTmp21+1);
			psIni->asSilos[8].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[8].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[8].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[8].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[8].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[8].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[8].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[8].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[8].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[8].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[8].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[8].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[8].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[8].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[8].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[8].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo10=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+7) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[9].acMat, pcTmp1+7, pcTmp2-pcTmp1-7);
			psIni->asSilos[9].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[9].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[9].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[9].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[9].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[9].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[9].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[9].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[9].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[9].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[9].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[9].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[9].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[9].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[9].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[9].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[9].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[9].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[9].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[9].fFall= atoi(pcTmp21+1);
			psIni->asSilos[9].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[9].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[9].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[9].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[9].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[9].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[9].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[9].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[9].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[9].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[9].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[9].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[9].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[9].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[9].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[9].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo11=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+7) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[10].acMat, pcTmp1+7, pcTmp2-pcTmp1-7);
			psIni->asSilos[10].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[10].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[10].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[10].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[10].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[10].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[10].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[10].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[10].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[10].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[10].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[10].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[10].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[10].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[10].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[10].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[10].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[10].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[10].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[10].fFall= atoi(pcTmp21+1);
			psIni->asSilos[10].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[10].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[10].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[10].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[10].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[10].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[10].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[10].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[10].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[10].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[10].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[10].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[10].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[10].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[10].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[10].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "silo12=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
			&& ((pcTmp3 = strchr(pcTmp2+1, ',')) != NULL)
			&& ((pcTmp4 = strchr(pcTmp3+1, ',')) != NULL)
			&& ((pcTmp5 = strchr(pcTmp4+1, ',')) != NULL)
			&& ((pcTmp6 = strchr(pcTmp5+1, ',')) != NULL)
			&& ((pcTmp7 = strchr(pcTmp6+1, ',')) != NULL)
			&& ((pcTmp8 = strchr(pcTmp7+1, ',')) != NULL)
			&& ((pcTmp9 = strchr(pcTmp8+1, ',')) != NULL)
			&& ((pcTmp10 = strchr(pcTmp9+1, ',')) != NULL)
			&& ((pcTmp11 = strchr(pcTmp10+1, ',')) != NULL)
			&& ((pcTmp12 = strchr(pcTmp11+1, ',')) != NULL)
			&& ((pcTmp13 = strchr(pcTmp12+1, ',')) != NULL)
			&& ((pcTmp14 = strchr(pcTmp13+1, ',')) != NULL)
			&& ((pcTmp15 = strchr(pcTmp14+1, ',')) != NULL)
			&& ((pcTmp16 = strchr(pcTmp15+1, ',')) != NULL)
			&& ((pcTmp17 = strchr(pcTmp16+1, ',')) != NULL)
			&& ((pcTmp18 = strchr(pcTmp17+1, ',')) != NULL)
			&& ((pcTmp19 = strchr(pcTmp18+1, ',')) != NULL)
			&& ((pcTmp20 = strchr(pcTmp19+1, ',')) != NULL)
			&& ((pcTmp21 = strchr(pcTmp20+1, ',')) != NULL)
			&& ((pcTmp22 = strchr(pcTmp21+1, ',')) != NULL)
			&& ((pcTmp23 = strchr(pcTmp22+1, ',')) != NULL)
			&& ((pcTmp24 = strchr(pcTmp23+1, ',')) != NULL)
			&& ((pcTmp25 = strchr(pcTmp24+1, ',')) != NULL)
			&& ((pcTmp26 = strchr(pcTmp25+1, ',')) != NULL)
			&& (*(pcTmp1+7) != ' ')
			)
		{
			strncpy_s(psIni->asSilos[11].acMat, pcTmp1+7, pcTmp2-pcTmp1-7);
			psIni->asSilos[11].bUsed = *(pcTmp2+1) == '1';
			psIni->asSilos[11].nFlowRatePct1= atoi(pcTmp3+1);
			psIni->asSilos[11].nFlowRatePct2= atoi(pcTmp4+1);
			psIni->asSilos[11].nFlowRatePct3= atoi(pcTmp5+1);
			psIni->asSilos[11].nFlowRatePct4= atoi(pcTmp6+1);
			psIni->asSilos[11].nDelayPct= atoi(pcTmp7+1);
			psIni->asSilos[11].nDelayTime= atoi(pcTmp8+1);
			psIni->asSilos[11].nFlowRate1O= atoi(pcTmp9+1);
			psIni->asSilos[11].nFlowRate2O= atoi(pcTmp10+1);
			psIni->asSilos[11].nFlowRate3O= atoi(pcTmp11+1);
			psIni->asSilos[11].nFlowRate4O= atoi(pcTmp12+1);
			psIni->asSilos[11].nDoneI= atoi(pcTmp13+1);
			psIni->asSilos[11].nReadyO= atoi(pcTmp14+1);
			psIni->asSilos[11].nDropO= atoi(pcTmp15+1);
			psIni->asSilos[11].nDoneO= atoi(pcTmp16+1);
			psIni->asSilos[11].nHoldO= atoi(pcTmp17+1);
			psIni->asSilos[11].nAddO= atoi(pcTmp18+1);
			psIni->asSilos[11].nDropReadyI= atoi(pcTmp19+1);
			psIni->asSilos[11].nHoldI= atoi(pcTmp20+1);
			psIni->asSilos[11].fFall= atoi(pcTmp21+1);
			psIni->asSilos[11].nSiloNum= atoi(pcTmp22+1);
			psIni->asSilos[11].nSiloJog= atoi(pcTmp23+1);
			psIni->asSilos[11].dAddTol= atoi(pcTmp24+1);
			strncpy_s(psIni->asSilos[11].acProduct, pcTmp25+1, pcTmp26-pcTmp25-1);
			if(*(pcTmp9+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp9+1));
				psIni->asSilos[11].uFlowRate1O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp10+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp10+1));
				psIni->asSilos[11].uFlowRate2O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp11+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp11+1));
				psIni->asSilos[11].uFlowRate3O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp12+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp12+1));
				psIni->asSilos[11].uFlowRate4O = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp13+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp13+1));
				psIni->asSilos[11].uDoneI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp14+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp14+1));
				psIni->asSilos[11].uReadyO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp15+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp15+1));
				psIni->asSilos[11].uDropO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp16+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp16+1));
				psIni->asSilos[11].uDoneO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp17+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp17+1));
				psIni->asSilos[11].uHoldO = nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp18+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp18+1));
				psIni->asSilos[11].uAddO= nBit;
				psIni->nMask |= nBit;
			}
			if(*(pcTmp19+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp19+1));
				psIni->asSilos[11].uDropReadyI = nBit;
				psIni->nInpMask |= nBit;
			}
			if(*(pcTmp20+1) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp20+1));
				psIni->asSilos[11].uHoldI = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "pdmPlc=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+7) != ' ')
		)
		{
			psIni->bPdmPlc = *(pcTmp1+7) == '1';
		}
		if(((pcTmp1 = strstr(pcCfg, "autoAdd=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+8) != ' ')
		)
		{
			psIni->bAutoAdd = *(pcTmp1+8) == '1';
		}
		if(((pcTmp1 = strstr(pcCfg, "sendTarget=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+11) != ' ')
		)
		{
			psIni->bSendTarget = *(pcTmp1+11) == '1';
		}
		if(((pcTmp1 = strstr(pcCfg, "sendBitWise=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+11) != ' ')
		)
		{
			psIni->bSendBitWise = *(pcTmp1+12) == '1';
		}
		if(((pcTmp1 = strstr(pcCfg, "truckMin=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+9) != ' ')
		)
		{
			psIni->nTruckMin = atoi(pcTmp1+9);
		}
		if(((pcTmp1 = strstr(pcCfg, "truckMax=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+9) != ' ')
		)
		{
			psIni->nTruckMax = atoi(pcTmp1+9);
		}
		if(((pcTmp1 = strstr(pcCfg, "cartMin=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+8) != ' ')
		)
		{
			psIni->nCartMin = atoi(pcTmp1+8);
		}
		if(((pcTmp1 = strstr(pcCfg, "cartMax=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+8) != ' ')
		)
		{
			psIni->nCartMax= atoi(pcTmp1+8);
		}

		if(((pcTmp1 = strstr(pcCfg, "sendTargetO=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+12) != ' ')
		)
		{
			psIni->nSendTargetO= atoi(pcTmp1+12);
			if(*(pcTmp1+12) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+12));
				psIni->uSendTargetO = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "receivedTargetI=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+16) != ' ')
		)
		{
			psIni->nReceivedTargetI= atoi(pcTmp1+16);
			if(*(pcTmp1+16) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+16));
				psIni->uReceivedTargetI= nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "keepAliveO=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+11) != ' ')
		)
		{
			psIni->nKeepAliveO= atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uKeepAliveO = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "keepAliveI=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+11) != ' ')
		)
		{
			psIni->nKeepAliveI= atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uKeepAliveI= nBit;
				psIni->nInpMask |= nBit;
			}
		}

		if(((pcTmp1 = strstr(pcCfg, "keepOnTime=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+11) != ' ')
		)
		{
			psIni->nKeepOnTime= atoi(pcTmp1+11);
		}

		if(((pcTmp1 = strstr(pcCfg, "keepOffTime=")) != NULL)
		&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL)
		&& (*(pcTmp1+12) != ' ')
		)
		{
			psIni->nKeepOffTime= atoi(pcTmp1+12);
		}

		//DC 4.0.0 silo bit output
		if(((pcTmp1 = strstr(pcCfg, "siloBit0=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBit[0] = atoi(pcTmp1+9);
			if(*(pcTmp1+9) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+9));
				psIni->uSiloBitO[0] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "siloBit1=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBit[1] = atoi(pcTmp1+9);
			if(*(pcTmp1+9) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+9));
				psIni->uSiloBitO[01] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "siloBit2=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBit[2] = atoi(pcTmp1+9);
			if(*(pcTmp1+9) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+9));
				psIni->uSiloBitO[2] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "siloBit3=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBit[3] = atoi(pcTmp1+9);
			if(*(pcTmp1+9) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+9));
				psIni->uSiloBitO[3] = nBit;
				psIni->nMask |= nBit;
			}
		}
		//DC 4.0.0 bitwise output
		if(((pcTmp1 = strstr(pcCfg, "bitWise00=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[0] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[0] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise01=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[1] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[1] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise02=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[2] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[2] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise03=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[3] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[3] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise04=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[4] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[4] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise05=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[5] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[5] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise06=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[6] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[6] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise07=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[7] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[7] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise08=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[8] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[8] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise09=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[9] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[9] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise10=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[10] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[10] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise11=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[11] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[11] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise12=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[12] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[12] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise13=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[13] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[13] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise14=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[14] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[14] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise15=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[15] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[15] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise16=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[16] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[16] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise17=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[17] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[17] = nBit;
				psIni->nMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitWise18=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitWise[18] = atoi(pcTmp1+10);
			if(*(pcTmp1+10) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+10));
				psIni->uBitWiseO[18] = nBit;
				psIni->nMask |= nBit;
			}
		}
		//DC 4.0.0 silo bit check input
		if(((pcTmp1 = strstr(pcCfg, "siloCheck0=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBitCheck[0] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uSiloBitCheckI[0] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "siloCheck1=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBitCheck[1] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uSiloBitCheckI[1] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "siloCheck2=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBitCheck[2] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uSiloBitCheckI[2] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "siloCheck3=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nSiloBitCheck[3] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uSiloBitCheckI[3] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		//DC 4.0.0 bit check input
		if(((pcTmp1 = strstr(pcCfg, "bitCheck00=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[0] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[0] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck01=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[1] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[1] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck02=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[2] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[2] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck03=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[3] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[3] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck04=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[4] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[4] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck05=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[5] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[5] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck06=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[6] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[6] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck07=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[7] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[7] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck08=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[8] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[8] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck09=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[9] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[9] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck10=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[10] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[10] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck11=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[11] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[11] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck12=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[12] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[12] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck13=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[13] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[13] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck14=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[14] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[14] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck15=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[15] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[15] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck16=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[16] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[16] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck17=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[17] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[17] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "bitCheck18=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nBitCheckI[18] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uBitCheckI[18] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		//DC 4.0.1 Lane Tare Input
		if(((pcTmp1 = strstr(pcCfg, "laneTareI0=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nLaneTareI[0] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uLaneTareI[0] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "laneTareI1=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nLaneTareI[1] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uLaneTareI[1] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "laneTareI2=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nLaneTareI[2] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uLaneTareI[2] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
		if(((pcTmp1 = strstr(pcCfg, "laneTareI3=")) != NULL)
			&& ((pcTmp2 = strchr(pcTmp1+1, ',')) != NULL))
		{
			psIni->nLaneTareI[3] = atoi(pcTmp1+11);
			if(*(pcTmp1+11) != ',')
			{
				nBit = ((ulong64)1L << atoi(pcTmp1+11));
				psIni->uLaneTareI[3] = nBit;
				psIni->nInpMask |= nBit;
			}
		}
	}
	//-------------------------------------------------------------
	catch ( Exception^ ex ) 
	{
//		pAll->stExc += "CFX: Exception: " + ex->Message;
		bRet = false;
	}
		//-------------------------------------------------------------------------
	fclose(pfCfg);
	free(pcCfg);
	return bRet;
	}
	
#pragma endregion
///////////////////////////////////////////////////////////////////////////////
}