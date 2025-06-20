// as.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#include <sys\stat.h> 

#include "cfg.h"
#include "Form1.h"
#include "DbaseTB.h"
#include "DbaseT.h"
#include "OptoT.h"
#include "OptoTP.h"
#include "PrintT.h"
#include "ScaleT.h"
#include "ScaleTP.h"
#include "ScaleTPS.h"
#include "SimT.h"
#include "UlinkT.h"
#include "IOForm.h"
#include "PreView.h"
#include "CservT.h"		//DC 4.1.0
#include "ClinkT.h"		//DC 4.1.0

using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace Runtime::InteropServices;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::Serialization::Formatters::Binary;

namespace As
{
	//forward declarations
	void MarshalStr(String^ s, std::string& outputstring);
	string MarshalStr1(String^ s);
	bool readRem(All^ pAll, char* pcFile);
	int readLog(All^ pAll);
	FILE* openInv(All^ pAll);

	//had to move this out of stdafx becasue this conflicted with Windows
	#define min(a, b)  (((a) > (b)) ? (b) : (a)) 

	//moved these off the stack for memory
	char acPath[PATH_LEN];
	char acLog[PATH_LEN];
	char acDbe[PATH_LEN];		// data base errors
	char acDbs[PATH_LEN];		//DC 4.1.1 data base success
	char acTmp[80];
	char acFile1[128] = { 0 };		//DC 3.3.0
	char acFile[128] = { 0 };			//DC 4.1.0


	const char* cpcDbHeader = "DISPATCH DATABASE ERRORS:\n--------------------------------\n   ticket#, customer_code,      truck#,  gro_wt, tare_wt,  net_wt\n";
	const char* cpcDbsHeader = "DISPATCH DATABASE SUCCESS:\n--------------------------------\n   ticket#, customer_code,      truck#,  gro_wt, tare_wt,  net_wt\n";

	/// <summary>
	/// main - propper c++/cli entry point
	/// </summary>
	/// <param name="args"></param>
	/// <returns></returns>
	[STAThreadAttribute]
	int main(cli::array<System::String^>^ args)
	{
		std::string strNativeString;
		int i, err;
		All^ pAll = gcnew All();
		Dbase^ pDbase;

		INI sIni = { 0 };
		Thread^ oScaleThread1 = nullptr;
		Thread^ oScaleThread2 = nullptr;
		Thread^ oScaleThread3 = nullptr;
		Thread^ oScaleThread4 = nullptr;
		Thread^ oClinkThread = nullptr;
		Thread^ oCservThread = nullptr;

		try
		{
			FILE* pfInv = NULL;
			pAll->psIni = &sIni;
			pAll->pcPath = acPath;
			pAll->pcLog = acLog;
			pAll->qPrint1 = gcnew System::Collections::Generic::Queue<String^>();
			pAll->qPrint2 = gcnew System::Collections::Generic::Queue<String^>();
			pAll->qPrint3 = gcnew System::Collections::Generic::Queue<String^>();
			pAll->qPrint4 = gcnew System::Collections::Generic::Queue<String^>();
			pAll->q2ndPrint1 = gcnew System::Collections::Generic::Queue<PrintQ^>();			//DC 4.0.2
			pAll->q2ndPrint2 = gcnew System::Collections::Generic::Queue<PrintQ^>();			//DC 4.0.2
			pAll->q2ndPrint3 = gcnew System::Collections::Generic::Queue<PrintQ^>();			//DC 4.0.2
			pAll->q2ndPrint4 = gcnew System::Collections::Generic::Queue<PrintQ^>();		//DC 4.0.2

			pAll->qDbase = gcnew System::Collections::Generic::Queue<Dbase^>();
			pAll->qDbaseBad = gcnew System::Collections::Generic::Queue<Dbase^>();

			pAll->lJob = gcnew List<Job^>(0);
			pAll->lOld = gcnew List<Job^>(0);
			pAll->lTruck = gcnew List<Truck^>(0);

			pAll->qCmd = gcnew System::Collections::Generic::Queue<Cmd^>();	//DC 4.1.0
			pAll->pRem = gcnew Rem();					//DC 4.1.0 

			pAll->lStat = gcnew List<String^>(0);
			pAll->lStat->Add(L"ERROR");
			pAll->lStat->Add(L"NEW");
			pAll->lStat->Add(L"OK");
			pAll->lStat->Add(L"VOIDED");
			pAll->lStat->Add(L"ABORTED");
			pAll->lStat->Add(L"PRINTED");

			pAll->pExc = gcnew String("EXCEPTIONS\n");

			// configuration ----------------------------------------------------------
			sIni.nOptoDelay = 30;				// 30 msec default value

			if (_getcwd(acPath, PATH_LEN) == NULL)
			{
				MessageBox::Show("PATH not found", "ERROR", MessageBoxButtons::OK);
				return -1;
			}

			//are there arguments?
			if (args->Length >= 1)
			{
				//this is how to convert the String^ to a "normal" string we can do things with
				MarshalStr(args[0], strNativeString);

				String^ stArgs = args[0];
				if (stArgs->Equals("demo"))
				{
					pAll->eAsType = A_DEMO;
					pAll->psIni->bData = false;
				}
				else if (args[0]->Contains(".rem"))	//DC 4.1.0
				{
					strcpy_s(acFile, 128, acPath);
					strcat_s(acFile, 128, "\\");
					strcat_s(acFile, 128, strNativeString.c_str());
					pAll->eAsType = A_REMOTE;

					if (readRem(pAll, acFile) == false)
					{
						MessageBox::Show(gcnew String(acFile), pAll->stExc
							, MessageBoxButtons::OK, MessageBoxIcon::Error);
						return -1;
					}
				}
				else
				{
					pAll->eAsType = A_SIM;
					pAll->psIni->bData = false;
				}
				strcat(acPath, "\\demo\\");
			}
			else
			{
				pAll->eAsType = A_PROD;
				pAll->psIni->bData = true;		//DC 4.1.0
				strcat(acPath, "\\data\\");
			}

			pAll->stRemVersion = gcnew String(VERSION);	//DC 4.1.0
			//int ast = (int)pAll->eAsType;
			//int sst = (int)A_REMOTE;

			//bool bSame = (int)pAll->eAsType == (int)A_REMOTE;

			if (pAll->eAsType != A_REMOTE)//DC 4.1.0 if not remote
			{
				if (readConfig(pAll) != 0)
				{
					MessageBox::Show("as.cfg not found", "ERROR",
						System::Windows::Forms::MessageBoxButtons::OK);
					return -1;
				}

				// as.cfx
				strcpy(acFile1, acPath);
				strcat(acFile1, "as.cfx");

				if (readCfgEx(pAll) == false)		//DC 4.0.0
				{
					MessageBox::Show("File not found", gcnew String(acFile1)
						, MessageBoxButtons::OK, MessageBoxIcon::Stop);
					return -1;
				}

				if (sIni.bBotScale)	//DC 4.1.2
				{
					sIni.fDropMax = min(sIni.fBotScaleMax, BOTTOM_MAXL4);
					sIni.fDropMaxL2 = min(sIni.fBotScaleMaxL2, BOTTOM_MAXL4);
					sIni.fDropMaxL3 = min(sIni.fBotScaleMaxL3, BOTTOM_MAXL4);
					sIni.fDropMaxL4 = min(sIni.fBotScaleMaxL4, BOTTOM_MAXL4);
				}
				else
					sIni.fDropMax = min(sIni.fTopScaleMax, UPPER_MAX);

				pAll->pAcPath = gcnew String(acPath);		//DC 3.2.3
				//------------------------------------------------------------get trucks----
				String^ truckName = gcnew String(acPath) + gcnew String("as.truck");

				if (File::Exists(truckName))
				{
					FileStream^ fs = gcnew FileStream(truckName, FileMode::Open);
					try
					{
						BinaryFormatter^ formatter = gcnew BinaryFormatter;
						pAll->lTruck = (List<Truck^>^)(formatter->Deserialize(fs));
					}
					catch (SerializationException^ e)
					{
						Console::WriteLine("Failed to deserialize. Reason: {0}", e->Message);
						throw;
					}
					finally
					{
						fs->Close();
					}
				}
				else
				{
					MessageBox::Show("cannot open Truck file", truckName, System::Windows::Forms::MessageBoxButtons::OK);
					return -1;
				}
				// inventory
				if ((pfInv = openInv(pAll)) == NULL)
				{
					MessageBox::Show("cannot open Inv file", "ERROR", System::Windows::Forms::MessageBoxButtons::OK);
					return -1;
				}

				// log --------------------------------------------------------------------
				if (sIni.bDailyLog)
				{
					i = 0;
					_strdate_s(acTmp, 12);

					while (acTmp[i] != 0)
					{
						if (acTmp[i] == '/')
							acTmp[i] = '-';
						i++;
					}
					sprintf_s(acLog, 80, "%s/as-%s.log", acPath, acTmp);
				}
				else
					sprintf_s(acLog, 80, "%sas.log", acPath);

				int nErr = readLog(pAll);

				if (nErr < -1)
				{
					MessageBox::Show("file missing", "as.log WARNING"
						, MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return -1;
				}
				else if (nErr < 0)
					nErr = readLog(pAll);

				// db errors---------------------------------------------------------------
				i = 0;
				_strdate_s(acTmp, 12);

				while (acTmp[i] != 0)
				{
					if (acTmp[i] == '/')
						acTmp[i] = '-';
					i++;
				}
				sprintf_s(acDbe, "%sas-%s.dbe", acPath, acTmp);
				if ((err = _access_s(acDbe, 0)) == 0)
					err = fopen_s(&sIni.pfDbe, acDbe, "a+");
				else
				{
					err = fopen_s(&sIni.pfDbe, acDbe, "w+");
					if( sIni.pfDbe!= 0)
						fputs(cpcDbHeader, sIni.pfDbe);
				}

				//DC 4.1.1
				sprintf_s(acDbs, "%sas-%s.dbs", acPath, acTmp);
				if ((err = _access_s(acDbs, 0)) == 0)
					err = fopen_s(&sIni.pfDbs, acDbs, "a+");
				else
				{
					err = fopen_s(&sIni.pfDbs, acDbs, "w+");
					if (sIni.pfDbs != 0)
						fputs(cpcDbsHeader, sIni.pfDbs);
				}
			}	//if not Remote

			// PRODUCTION ////////////////////////////////////////////////////////////////
			if (pAll->eAsType != A_DEMO && pAll->eAsType != A_REMOTE)
			{
				Thread^ oOptoThread;
				if (pAll->nPort > 0)
					oOptoThread = gcnew Thread(gcnew ParameterizedThreadStart(&COptoTP::ThreadProc));
				else
					oOptoThread = gcnew Thread(gcnew ParameterizedThreadStart(&COptoT::ThreadProc));
				oOptoThread->IsBackground = true;
				oOptoThread->Start(pAll);
				//oOptoThread->Join();

				if (sIni.nL2SilosNum > 0)	//DC 4.1.2
				{
					Scale^ sca2 = gcnew Scale();
					sca2->psIni = &sIni;
					sca2->psScale = &sIni.sScale2;
					sca2->pScl = % pAll->sScale2;
					sca2->pAll = pAll;
					if (pAll->psIni->sScale2.bSerTP)
						oScaleThread2 = gcnew Thread(gcnew ParameterizedThreadStart(&CScaleTPS::ThreadProc));
					else if (pAll->sScale2.nPort > 0)
						oScaleThread2 = gcnew Thread(gcnew ParameterizedThreadStart(&CScaleTP::ThreadProc));
					else
						oScaleThread2 = gcnew Thread(gcnew ParameterizedThreadStart(&CScale::ThreadProc));
					oScaleThread2->IsBackground = true;
					oScaleThread2->Start(sca2);
				}
				if (sIni.nL3SilosNum > 0)	//DC 4.1.2
				{
					Scale^ sca3 = gcnew Scale();
					sca3->psIni = &sIni;
					sca3->psScale = &sIni.sScale3;
					sca3->pScl = % pAll->sScale3;
					sca3->pAll = pAll;
					if (pAll->psIni->sScale3.bSerTP)
						oScaleThread3 = gcnew Thread(gcnew ParameterizedThreadStart(&CScaleTPS::ThreadProc));
					else if (pAll->sScale3.nPort > 0)
						oScaleThread3 = gcnew Thread(gcnew ParameterizedThreadStart(&CScaleTP::ThreadProc));
					else
						oScaleThread3 = gcnew Thread(gcnew ParameterizedThreadStart(&CScale::ThreadProc));
					oScaleThread3->IsBackground = true;
					oScaleThread3->Start(sca3);
				}
				if (sIni.nL4SilosNum > 0)
				{
					Scale^ sca4 = gcnew Scale();
					sca4->psIni = &sIni;
					sca4->psScale = &sIni.sScale4;
					sca4->pScl = % pAll->sScale4;
					sca4->pAll = pAll;
					if (pAll->psIni->sScale4.bSerTP)
						oScaleThread4 = gcnew Thread(gcnew ParameterizedThreadStart(&CScaleTPS::ThreadProc));
					else if (pAll->sScale4.nPort > 0)
						oScaleThread4 = gcnew Thread(gcnew ParameterizedThreadStart(&CScaleTP::ThreadProc));
					else
						oScaleThread4 = gcnew Thread(gcnew ParameterizedThreadStart(&CScale::ThreadProc));
					oScaleThread4->IsBackground = true;
					oScaleThread4->Start(sca4);
				}
			}	

			if (pAll->psIni->nRlinkPort > 0 && pAll->eAsType != A_REMOTE)
			{
				CCserv oSlink(pAll); //, poBufs, poOps, poOps2);
				oCservThread = gcnew Thread(gcnew ParameterizedThreadStart(&CCserv::ThreadProc));
				oCservThread->IsBackground = true;
				oCservThread->Start(pAll);
			}
			if (pAll->eAsType != A_REMOTE)
			{
				Thread^ oDbaseThread = gcnew Thread(gcnew ParameterizedThreadStart(&CDbase::ThreadProc));
				oDbaseThread->IsBackground = true;
				oDbaseThread->Start(pAll);

				Thread^ oDbaseThreadB = gcnew Thread(gcnew ParameterizedThreadStart(&CDbaseB::ThreadProc));
				oDbaseThreadB->IsBackground = true;
				oDbaseThreadB->Start(pAll);
			}
			if (pAll->eAsType != A_PROD && pAll->eAsType != A_REMOTE)
			{
				Thread^ oSimThread = gcnew Thread(gcnew ParameterizedThreadStart(&CSim::ThreadProc));
				oSimThread->IsBackground = true;
				oSimThread->Start(pAll);
			}
			//if (pAll->pPrinter1 != nullptr && pAll->eAsType != A_REMOTE)
			//{
			//	CPrint^ oPrint1 = gcnew CPrint(pAll, pAll->pPrinter1, &sIni.bPrinterOk1, 1);
			//	Thread^ oPrintThread1 = gcnew Thread(gcnew ParameterizedThreadStart(oPrint1, &CPrint::ThreadProc));
			//	oPrintThread1->IsBackground = true;
			//	oPrintThread1->Start(pAll->qPrint1);
			//}
			//if (pAll->pPrinter2 != nullptr && pAll->eAsType != A_REMOTE)
			//{
			//	CPrint^ oPrint2 = gcnew CPrint(pAll, pAll->pPrinter2, &sIni.bPrinterOk2, 2);
			//	Thread^ oPrintThread2 = gcnew Thread(gcnew ParameterizedThreadStart(oPrint2, &CPrint::ThreadProc));
			//	oPrintThread2->IsBackground = true;
			//	oPrintThread2->Start(pAll->qPrint2);
			//}
			//if (pAll->pPrinter3 != nullptr && pAll->eAsType != A_REMOTE)
			//{
			//	CPrint^ oPrint3 = gcnew CPrint(pAll, pAll->pPrinter3, &sIni.bPrinterOk3, 3);
			//	Thread^ oPrintThread3 = gcnew Thread(gcnew ParameterizedThreadStart(oPrint3, &CPrint::ThreadProc));
			//	oPrintThread3->IsBackground = true;
			//	oPrintThread3->Start(pAll->qPrint3);
			//}

			if (pAll->pPrinter4 != nullptr && pAll->eAsType != A_REMOTE)
			{
				CPrint^ oPrint4 = gcnew CPrint(pAll, pAll->pPrinter4, &sIni.bPrinterOk4, 4);
				Thread^ oPrintThread4 = gcnew Thread(gcnew ParameterizedThreadStart(oPrint4, &CPrint::ThreadProc));
				oPrintThread4->IsBackground = true;
				oPrintThread4->Start(pAll->qPrint4);
			}

			if (pAll->p2ndPrinter1 != nullptr && pAll->eAsType != A_REMOTE)	//DC 4.0.2
			{
				CPrint^ o2ndPrint1 = gcnew CPrint(pAll, pAll->p2ndPrinter1, &sIni.b2ndPrinterOk1, 1);
				Thread^ o2ndPrintThread1 = gcnew Thread(gcnew ParameterizedThreadStart(o2ndPrint1, &CPrint::ThreadProc));
				o2ndPrintThread1->IsBackground = true;
				o2ndPrintThread1->Start(pAll->q2ndPrint1);
			}

			if (pAll->p2ndPrinter2 != nullptr && pAll->eAsType != A_REMOTE)	//DC 4.0.2
			{
				CPrint^ o2ndPrint2 = gcnew CPrint(pAll, pAll->p2ndPrinter2, &sIni.b2ndPrinterOk2, 2);
				Thread^ o2ndPrintThread2 = gcnew Thread(gcnew ParameterizedThreadStart(o2ndPrint2, &CPrint::ThreadProc));
				o2ndPrintThread2->IsBackground = true;
				o2ndPrintThread2->Start(pAll->q2ndPrint2);
			}

			if (pAll->p2ndPrinter3 != nullptr && pAll->eAsType != A_REMOTE)	//DC 4.0.2
			{
				CPrint^ o2ndPrint3 = gcnew CPrint(pAll, pAll->p2ndPrinter3, &sIni.b2ndPrinterOk3, 3);
				Thread^ o2ndPrintThread3 = gcnew Thread(gcnew ParameterizedThreadStart(o2ndPrint3, &CPrint::ThreadProc));
				o2ndPrintThread3->IsBackground = true;
				o2ndPrintThread3->Start(pAll->q2ndPrint3);
			}

			if (pAll->p2ndPrinter4 != nullptr && pAll->eAsType != A_REMOTE)	//DC 4.0.2
			{
				CPrint^ o2ndPrint4 = gcnew CPrint(pAll, pAll->p2ndPrinter4, &sIni.b2ndPrinterOk4, 4);
				Thread^ o2ndPrintThread4 = gcnew Thread(gcnew ParameterizedThreadStart(o2ndPrint4, &CPrint::ThreadProc));
				o2ndPrintThread4->IsBackground = true;
				o2ndPrintThread4->Start(pAll->q2ndPrint4);
			}

			if (pAll->eAsType != A_REMOTE)
			{
				CUlink oUlink(pAll);
				Thread^ oUlinkThread = gcnew Thread(gcnew ParameterizedThreadStart(&CUlink::ThreadProc));
				oUlinkThread->IsBackground = true;
				oUlinkThread->Start(pAll);
			}

			// Enabling Windows XP visual effects before any controls are created
			Application::EnableVisualStyles();
			Application::SetCompatibleTextRenderingDefault(false);

			// Create the main window and run it
			Application::Run(gcnew Form1(pAll, pfInv));

			if (pAll->eAsType != A_REMOTE)
			{
				//	oInv.save(&sIni.sInv);
				if (fseek(pfInv, 0, SEEK_SET) == 0)
					fwrite(&sIni.sInv, sizeof(INV), 1, pfInv);
				fclose(pfInv);

				while (pAll->qDbaseBad->Count > 0)
				{
					pDbase = (Dbase^)pAll->qDbaseBad->Dequeue();
					sprintf(acTmp, "%10d,%14s,%12s,%8.2f,%8.2f,%8.2f\n"
						, pDbase->nTicket
						, MarshalStr1( pDbase->pstCustCode ).c_str()
						, MarshalStr1(pDbase->pstTruck).c_str()
						, pDbase->fGross
						, pDbase->fTare
						, pDbase->fGross - pDbase->fTare);
					fputs(acTmp, sIni.pfDbe);

				}
				if(sIni.pfDbe != 0)
					fclose(sIni.pfDbe);

				struct __stat64 fileStat;
				err = _stat64(acDbe, &fileStat);
				if (0 != err) return 0;

				if (fileStat.st_size > (int)strlen(cpcDbHeader) + 5)
				{
					strcpy(acPath, "notepad ");
					strcat(acPath, acDbe);
					system(acPath);
				}
				return 0;
			}
		}
		catch (Exception^ ex)
		{
			pAll->stExc += "CFX: Exception: " + ex->Message;
		}

		return 0;
	}

	/// <summary>
	/// readRem
	/// </summary>
	/// <param name="pAll"></param>
	/// <param name="pcFile"></param>
	/// <returns></returns>
	bool readRem(All^ pAll, char* pcFile)
	{
		FILE* pfRem;
		char acLine[128];
		char* pcT1, * pcT2;
		Rem^ pRem;

		if (fopen_s(&pfRem, pcFile, "r") != 0)
		{
			pAll->stExc += "REM file open error.";
			return false;
		}
		while (fgets(acLine, sizeof(acLine), pfRem) != NULL)
		{
			if (acLine[0] == '#')			// skip comments
				continue;

			// list of servers --------------------------------------------
			if ((pcT1 = strchr(acLine, ',')) && (pcT2 = strchr(pcT1 + 1, ',')))
			{
				*pcT1 = 0;
				pcT1++;
				*pcT2 = 0;
				pcT2++;

				pRem = gcnew Rem();
				pRem->stName = gcnew String(acLine);
				pRem->pIp = IPAddress::Parse(gcnew String(pcT1));
				pRem->nPort = atoi(pcT2);
			}
		}
		pAll->pRem->pIp = pRem->pIp;
		pAll->pRem->nPort = pRem->nPort;
		fclose(pfRem);
		return true;
	}

	/// <summary>
	/// readLog
	/// </summary>
	/// <param name="pAll"></param>
	/// <returns></returns>
	int readLog(All^ pAll)
	{
		errno_t err;
		//	char pAll->pcLog[80];
		char acErrFile[80];
		FILE* pfLog = NULL;
		FILE* pfErr;
		INI* psIni = pAll->psIni;
		LOG_REC sLog;
		Job^ pJob;
		bool bFix;
		DateTime^ pDate;
		int nRet;

	start:
		if ((err = _access_s(pAll->pcLog, 0)) == 0)
			err = fopen_s(&pfLog, pAll->pcLog, "r+b");
		else
			err = fopen_s(&pfLog, pAll->pcLog, "w+b");

		if (err != 0) return -2;				// log file missing

		// read log ---------------------------------------------------------------
		pAll->gnIndex = 0;
		bFix = false;

		while (fread(&sLog, sizeof(LOG_REC), 1, pfLog) > 0)
		{
			if (sLog.sT.ticket_num <= 0 && pAll->gnIndex > 0)
			{
				fclose(pfLog);
				bFix = true;
				break;
			}
			pDate = DateTime::FromBinary(sLog.tTimeSent);

			pJob = gcnew Job();
			pJob->tTime = sLog.tTimeSent;
			pJob->nLogIdx = pAll->gnIndex;		// sLog.nLogIdx;
			pJob->nPlant = sLog.sT.plant_num;
			//4.0.3
			for (int i = 0; i < 12; i++)
			{
				if (sLog.nSilo == psIni->asSilos[i].nSiloNum)
				{
					pJob->nSilo = i + 1;
					sLog.nSilo = i + 1;
					break;
				}
			}
			if (pJob->nSilo == 0)
			{
				pJob->nSilo = sLog.nSilo;
			}
			pJob->nSilo = sLog.nSilo;
			pJob->nTicket = sLog.sT.ticket_num;
			pJob->stCustomer = gcnew String(sLog.sT.customer_name_1);
			pJob->eStatus = sLog.eJobStatus;
			pJob->stMaterial = gcnew String(sLog.sT.mix_code);		//DC 4.0.1
			pJob->stTruck = gcnew String(sLog.sT.truck_id);			//DC 4.0.1
			pJob->nCopy = sLog.nCopy;								//DC 4.0.3
			pJob->stLane = gcnew String(sLog.sT.user_defined_46);	//DC 4.1.2
			pJob->stSilo = gcnew String(sLog.sT.user_defined_47);	//DC 4.1.2

			if (sLog.eJobStatus == S_NEW)			// not done yet
			{
				if (psIni->bBotScale)
				{
					switch (sLog.nSilo)
					{
					case 1:
						break;
					case 2:
						break;
					case 3:  pAll->nTickets1++;
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:  pAll->nTickets2++;
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:  pAll->nTickets3++;
						break;
					case 10:
						break;
					case 11:
						break;
					case 12:  psIni->nTickets4++;
						break;
					default:  pAll->nTickets1++;
						break;
					}
				}
				else
				{
					switch (sLog.nSilo)
					{
					case 1:  pAll->nTickets1++;
						break;
					case 2:  pAll->nTickets2++;
						break;
					case 3:  pAll->nTickets3++;
						break;
					case 4:  pJob->nSilo = 1;
						pAll->nTickets1++;
						break;
					case 5:  pJob->nSilo = 2;
						pAll->nTickets2++;
						break;
					case 6:  pJob->nSilo = 3;
						pAll->nTickets3++;
						break;
					case 7:  pJob->nSilo = 1;
						pAll->nTickets1++;
						break;
					case 8:  pJob->nSilo = 2;
						pAll->nTickets2++;
						break;
					case 9:  pJob->nSilo = 3;
						pAll->nTickets3++;
						break;
					case 10:  pJob->nSilo = 1;
						pAll->nTickets1++;
						break;
					case 11:  pJob->nSilo = 2;
						pAll->nTickets2++;
						break;
					case 12:  pJob->nSilo = 3;
						pAll->nTickets3++;
						break;
					default:  pJob->nSilo = 1;
						pAll->nTickets1++;
						break;
					}
				}
				pJob->fLoad = sLog.sT.load_size;
				pAll->lJob->Add(pJob);
			}
			// list old jobs --------------------------------------------------
			else
			{
				pJob->fLoad = sLog.fLoad;
				//pJob->stStatus = pAll->lStat[sLog.eJobStatus];
				pAll->lOld->Add(pJob);

				// count done tickets ------------------------------
				if (psIni->bBotScale)
				{
					switch (sLog.nSilo)
					{
					case 1:
						break;
					case 2:
						break;
					case 3:
						pAll->nDone1++;
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						pAll->nDone2++;
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						pAll->nDone3++;
						break;
					case 10:
						break;
					case 11:
						break;
					case 12:
						pAll->psIni->nOldDone4++;
						break;
					default:
						break;

					}
				}
				else
				{
					switch ((sLog.nSilo - 1) & 3)
					{
					case 0:
						pAll->nDone1++;
						break;
					case 1:
						pAll->nDone2++;
						break;
					case 2:
						pAll->nDone3++;
						break;
					case 3:
						pAll->psIni->nOldDone4++;
						break;
					}
				}
			}
			pAll->gnIndex++;
		}
		nRet = fclose(pfLog);

		// fix corrupted file ---------------------------------------------
		if (bFix)
		{
			strcpy_s(acErrFile, 80, pAll->pcLog);
			strcat_s(acErrFile, 80, "-err");

			if ((err = _access_s(acErrFile, 0)) == 0)
				remove(acErrFile);

			rename(pAll->pcLog, acErrFile);

			if ((fopen_s(&pfErr, acErrFile, "rb") == 0)
				&& (fopen_s(&pfLog, pAll->pcLog, "wb") == 0))
			{
				while (fread(&sLog, sizeof(LOG_REC), 1, pfErr) > 0)
				{
					if (sLog.sT.ticket_num > 0)
					{
						fwrite(&sLog, sizeof(LOG_REC), 1, pfLog);
					}
				}
				fclose(pfErr);
				fclose(pfLog);

				// log file fixed -----------------------------
				pAll->lJob->Clear();
				pAll->lOld->Clear();

				pAll->nTickets1 = 0;
				pAll->nTickets2 = 0;
				pAll->nTickets3 = 0;
				psIni->nTickets4 = 0;
				pAll->nDone1 = 0;
				pAll->nDone2 = 0;
				pAll->nDone3 = 0;
				pAll->psIni->nOldDone4 = 0;		//DC 4.1.0
				goto start;
			}
			else
				nRet = -2;			// log file missing
		}
		return nRet;
	}

	/// <summary>
	/// openInv
	/// </summary>
	/// <param name="pAll"></param>
	/// <returns></returns>
	FILE* openInv(All^ pAll)
	{
		INI* psIni = pAll->psIni;
		errno_t err;
		char acInvFile[64];
		FILE* pfInv = NULL;
		double fFall1;
		double fFall2;
		double fFall3;
		double fFall4;
		double fFall5;
		double fFall6;
		double fFall7;
		double fFall8;
		double fFall9;
		double fFall10;
		double fFall11;
		double fFall12;

		double fAdapt1;
		double fAdapt2;
		double fAdapt3;
		double fAdapt4;
		double fAdapt5;
		double fAdapt6;
		double fAdapt7;
		double fAdapt8;
		double fAdapt9;
		//double fAdapt10;
		//double fAdapt11;
		//double fAdapt12;

		sprintf_s(acInvFile, "%s/as.inv", pAll->pcPath);

		if ((err = _access_s(acInvFile, 0)) == 0)
		{
			err = fopen_s(&pfInv, acInvFile, "r+b");
			if(pfInv != 0)
				fread(&psIni->sInv, sizeof(INV), 1, pfInv);

			// test change of day
			DateTime oDate = File::GetLastWriteTime(gcnew String(acInvFile));
			if (oDate.DayOfYear != DateTime::Now.DayOfYear)
			{
				psIni->sInv.fTon1 = 0.0;
				psIni->sInv.fTon2 = 0.0;
				psIni->sInv.fTon3 = 0.0;
				psIni->sInv.fTon4 = 0.0;
			}
		}
		else
		{
			err = fopen_s(&pfInv, acInvFile, "w+b");

			// init auto falls from manual falls
			for (int i = 0; i < LOAD_MAX; i++)
			{
				fFall1 = psIni->afManFall1[i];
				psIni->sInv.asFall1[i].fFall = fFall1 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall1[i].afFall[j] = fFall1;

				fFall2 = psIni->afManFall2[i];
				psIni->sInv.asFall2[i].fFall = fFall2 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall2[i].afFall[j] = fFall2;

				fFall3 = psIni->afManFall3[i];
				psIni->sInv.asFall3[i].fFall = fFall3 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall3[i].afFall[j] = fFall3;

				fFall4 = psIni->afManFall4[i];
				psIni->sInv.asFall4[i].fFall = fFall4 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall4[i].afFall[j] = fFall4;

				fFall5 = psIni->afManFall5[i];
				psIni->sInv.asFall5[i].fFall = fFall5 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall5[i].afFall[j] = fFall5;

				fFall6 = psIni->afManFall6[i];
				psIni->sInv.asFall6[i].fFall = fFall6 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall6[i].afFall[j] = fFall6;

				fFall7 = psIni->afManFall7[i];
				psIni->sInv.asFall7[i].fFall = fFall7 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall7[i].afFall[j] = fFall7;

				fFall8 = psIni->afManFall8[i];
				psIni->sInv.asFall8[i].fFall = fFall8 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall8[i].afFall[j] = fFall8;

				fFall9 = psIni->afManFall9[i];
				psIni->sInv.asFall9[i].fFall = fFall9 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall9[i].afFall[j] = fFall9;

				//DC 3.3.0
				fFall10 = psIni->afManFall10[i];
				psIni->sInv.asFall10[i].fFall = fFall10 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall10[i].afFall[j] = fFall10;

				fFall11 = psIni->afManFall11[i];
				psIni->sInv.asFall11[i].fFall = fFall11 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall11[i].afFall[j] = fFall11;

				fFall12 = psIni->afManFall12[i];
				psIni->sInv.asFall12[i].fFall = fFall12 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asFall12[i].afFall[j] = fFall12;
			}
			// init adapts from manual adapts
			for (int i = 0; i < LOAD_MAX; i++)
			{
				fAdapt1 = psIni->afAdapt1[i];
				psIni->sInv.asAdapt1[i].fAdapt = fAdapt1 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt1[i].afAdapt[j] = fAdapt1;

				fAdapt2 = psIni->afAdapt2[i];
				psIni->sInv.asAdapt2[i].fAdapt = fAdapt2 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt2[i].afAdapt[j] = fAdapt2;

				fAdapt3 = psIni->afAdapt3[i];
				psIni->sInv.asAdapt3[i].fAdapt = fAdapt3 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt3[i].afAdapt[j] = fAdapt3;

				fAdapt4 = psIni->afAdapt4[i];
				psIni->sInv.asAdapt4[i].fAdapt = fAdapt4 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt4[i].afAdapt[j] = fAdapt4;

				fAdapt5 = psIni->afAdapt5[i];
				psIni->sInv.asAdapt5[i].fAdapt = fAdapt5 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt5[i].afAdapt[j] = fAdapt5;

				fAdapt6 = psIni->afAdapt6[i];
				psIni->sInv.asAdapt6[i].fAdapt = fAdapt6 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt6[i].afAdapt[j] = fAdapt6;

				fAdapt7 = psIni->afAdapt7[i];
				psIni->sInv.asAdapt7[i].fAdapt = fAdapt7 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt7[i].afAdapt[j] = fAdapt7;

				fAdapt8 = psIni->afAdapt8[i];
				psIni->sInv.asAdapt8[i].fAdapt = fAdapt8 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt8[i].afAdapt[j] = fAdapt8;

				fAdapt9 = psIni->afAdapt9[i];
				psIni->sInv.asAdapt9[i].fAdapt = fAdapt9 * SAMPLE_NBR;
				for (int j = 0; j < SAMPLE_NBR; j++)
					psIni->sInv.asAdapt9[i].afAdapt[j] = fAdapt9;

				////DC 3.3.0
				//fAdapt10 = psIni->afAdapt10[i];
				//psIni->sInv.asAdapt10[i].fAdapt = fAdapt10 * SAMPLE_NBR;
				//for(int j=0; j<SAMPLE_NBR; j++)
				//	psIni->sInv.asAdapt10[i].afAdapt[j] = fAdapt10;

				//fAdapt11 = psIni->afAdapt11[i];
				//psIni->sInv.asAdapt11[i].fAdapt = fAdapt11 * SAMPLE_NBR;
				//for(int j=0; j<SAMPLE_NBR; j++)
				//	psIni->sInv.asAdapt11[i].afAdapt[j] = fAdapt11;

				//fAdapt12 = psIni->afAdapt12[i];
				//psIni->sInv.asAdapt12[i].fAdapt = fAdapt12 * SAMPLE_NBR;
				//for(int j=0; j<SAMPLE_NBR; j++)
				//	psIni->sInv.asAdapt12[i].afAdapt[j] = fAdapt12;
			}
			psIni->sInv.nLastTicket = psIni->nFirstTicket;

			fwrite(&psIni->sInv, sizeof(INV), 1, pfInv);

		}
		return pfInv;
	}

	/// <summary>
	/// MarshalString
	/// </summary>
	/// <param name="s"></param>
	/// <param name="outputstring"></param>
	void MarshalStr(String^ s, std::string& outputstring)
	{
		const char* kPtoC = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		outputstring = kPtoC;
		Marshal::FreeHGlobal(IntPtr((void*)kPtoC));
	}

	/// <summary>
	/// MarshalString
	/// </summary>
	/// <param name="s"></param>
	/// <param name="outputstring"></param>
	string MarshalStr1(String^ s)
	{
		const char* kPtoC = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		string outputstring = kPtoC;
		Marshal::FreeHGlobal(IntPtr((void*)kPtoC));
		return(outputstring);
	}
}
