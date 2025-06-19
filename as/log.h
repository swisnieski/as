#pragma once
#include "stdafx.h"
#include "share.h"
#include <string>

using namespace System::Threading;

namespace As 
{
	//-----------------------------------------------------------------------------
	public ref class CLog 
	{
	public:
		CLog(All^ pAllIn)
		{
			pAll = pAllIn;
			psIni = pAll->psIni;
			poMutex = gcnew Mutex;
		}
		~CLog(void)
		{
		}
	private:  
		INI  *psIni;
		All^  pAll;
		static Mutex^ poMutex;

		//-----------------------------------------------------------------------------
		// find LOG record with ticket number
		//-----------------------------------------------------------------------------
		long findIndex(int nTicket)
		{
			long nIdx = -1;

			for(int i=0; i < pAll->lJob->Count; i++)
			{
				if(pAll->lJob[i]->nTicket == nTicket)
				{
					nIdx = pAll->lJob[i]->nLogIdx;
					return nIdx;
				}
			}
			for(int i=0; i < pAll->lOld->Count; i++)
			{
				if(pAll->lOld[i]->nTicket == nTicket)
				{
					nIdx = pAll->lOld[i]->nLogIdx;
					return nIdx;
				}
			}
			return nIdx;
		}

		//-----------------------------------------------------------------------------
		// find LOG record with ticket number
		//-----------------------------------------------------------------------------
	public:
		int findTicket(int nTicket, LOG_REC *psLog)
		{
			int nRet = -1;
			long nIdx;

			if((nIdx = findIndex(nTicket)) >= 0)
			{
				nRet = log(C_READ, psLog, nIdx);
			}

			return nRet;
		}

		//-----------------------------------------------------------------------------
		// print list of manual tickets
		//-----------------------------------------------------------------------------
		void printManual(void)
		{
			String^ printBuf;
			LOG_REC sLog;
			char acBuf[228];

			strcpy_s(acBuf, "ticket#   truck#     customer                          load\n\r\
--------  ---------  --------------------------------  ------\n\r");
			printBuf = gcnew String(acBuf);

#if 1
			// find manual tickets
			for(int i=0; i < pAll->lJob->Count; i++)
			{
				if((pAll->lJob[i]->nTicket > psIni->nFirstTicket)
					&& (log(C_READ, &sLog, pAll->lJob[i]->nLogIdx) > 0))
				{
					sprintf_s(acBuf, "%8d  %-9s  %-32s  %6.2f\n\r", 
						sLog.sT.ticket_num, sLog.sT.truck_id, sLog.sT.customer_name_1, sLog.fLoad);
					printBuf = printBuf->Concat(printBuf, gcnew String(acBuf));
				}
			}	
#else
			// print all tickets
			for(int i=0; i < pAll->lJob->Count; i++)
			{
				if(log(C_READ, &sLog, pAll->lJob[i]->nLogIdx) > 0)
				{
					sprintf_s(acBuf, "%02x %d %8d  %-9s  %-32s  %6.2f\n\r",  sLog.eJobStatus, sLog.nSilo,
						sLog.sT.ticket_num, sLog.sT.truck_id, sLog.acCustomer, sLog.fLoad);
					printBuf = printBuf->Concat(printBuf, gcnew String(acBuf));
				}
			}	
#endif
			strcpy_s(acBuf, "--------  ---------  --------------------------------  ------\n\r");		

			printBuf = printBuf->Concat(printBuf, gcnew String(acBuf));
			//SRW pAll->qPrint1->Enqueue(printBuf);
		}

		//-----------------------------------------------------------------------------
		long log(LOG_CMD eCmd, LOG_REC *psLog, long nIdx)
		{
			FILE *pfLog;
			long ret = -1;
			//Cmd^ pCmd;
			bool bCopy = false;

			/*if(pAll->eAsType == A_REMOTE)
			{
				pCmd = gcnew Cmd();
				pCmd->cId = CL_LOG4;

				switch(eCmd)
				{
				case C_READ: 
					pCmd->nIdx = nIdx;
					pCmd->nKey = C_READ;
					bCopy = true;
					break;
				}
			}
			else*/
			{

				//Wait until it is OK to enter.
				poMutex->WaitOne();

				switch(eCmd)
				{
				case C_READ: 
					if ((pfLog = _fsopen(pAll->pcLog, "rb", _SH_DENYNO)) != NULL )
					{
						if(fseek(pfLog, nIdx*sizeof(LOG_REC), SEEK_SET) == 0)
							ret = (int)fread(psLog, sizeof(LOG_REC), 1, pfLog);
						fclose(pfLog);
					}
					break;

				case C_UPDATE:
					if ((pfLog = _fsopen(pAll->pcLog, "r+b", _SH_DENYWR)) != NULL )
					{
						if(fseek(pfLog, nIdx*sizeof(LOG_REC), SEEK_SET) == 0)	
							ret = (int)fwrite(psLog, sizeof(LOG_REC), 1, pfLog);
						fclose(pfLog);
					}
					break;

				case C_APPEND:
					if ((pfLog = _fsopen(pAll->pcLog, "ab", _SH_DENYWR)) != NULL )
					{
						if(fwrite(psLog, sizeof(LOG_REC), 1, pfLog) > 0)
							ret = pAll->gnIndex++;
						fclose(pfLog);
					}	
					break;
	/*
				case C_CANCEL:
					if ((pfLog = _fsopen(pAll->pcLog, "r+b", _SH_DENYWR)) != NULL )
					{
						if(((nIdx = findIndex(psLog->sT.ticket_num)) >= 0)
						&& (fseek(pfLog, nIdx*sizeof(LOG_REC), SEEK_SET) == 0))
						{
							ret = (int)fwrite(psLog, sizeof(LOG_REC), 1, pfLog);
						}
						fclose(pfLog);
					}
	*/
					break;
				}
				// Release the Mutex.
				poMutex->ReleaseMutex();
				return ret;
			}
		}

		// copy data from sLog to pcBuf according to TIC
		//-----------------------------------------------------------------------------
static	void calcTicket(LOG_REC *psLog)
		{
			double dLoad = psLog->bPrintTarget ? psLog->sT.load_size : psLog->fLoad;

			psLog->sT.subtotal = dLoad * psLog->sT.mix_price;
			psLog->fLoadTax = psLog->sT.subtotal * psLog->fTax;
			psLog->fTotal = psLog->sT.subtotal + psLog->fLoadTax;
			psLog->fGross = psLog->fTruckTare + dLoad;
		}

		// copy data from sLog to pcBuf according to TIC
		//-----------------------------------------------------------------------------
static	void calcLoad(LOG_REC *psLog)
		{
			psLog->bPrintTarget = false;
			psLog->sT.subtotal = psLog->fLoad * psLog->sT.mix_price;
			psLog->fLoadTax = psLog->sT.subtotal * psLog->fTax;
			psLog->fTotal = psLog->sT.subtotal + psLog->fLoadTax;
		}

		// copy data from sLog to pcBuf according to TIC
		//-----------------------------------------------------------------------------
static	void calcTarget(LOG_REC *psLog)
		{
			psLog->bPrintTarget = true;
			psLog->sT.subtotal = psLog->sT.load_size * psLog->sT.mix_price;
			psLog->fLoadTax = psLog->sT.subtotal * psLog->fTax;
			psLog->fTotal = psLog->sT.subtotal + psLog->fLoadTax;
			psLog->fGross = psLog->fTruckTare + psLog->sT.load_size;
		}

		// copy data from sLog to pcBuf according to TIC
		//-----------------------------------------------------------------------------
		void printTicket(LOG_REC *psLog, int nPrinter, bool bReprint)
		{
#define CR  0x0D
#define LF  0x0A
#define DATE_LEN 12
#define TIME_LEN  8
			TIC *psTic = &psIni->sTic;
			TICKET_PRODUCT *psProd;
			char acBuf[PRINT_LEN];
			int nLen = psTic->nLineNum * psTic->nLineLen;
			int ii;
			int nOffs;
			char acDate[DATE_LEN] = {};
			char acTime[TIME_LEN] = {};
//			struct tm sTm;
//			time_t tTime = time(NULL);
//			localtime_s(&sTm, &tTime);
//			sprintf_s(acDate, DATE_LEN, "%02d/%02d/%04d", sTm.tm_mon+1, sTm.tm_mday, sTm.tm_year+1900);
//			sprintf_s(acTime, TIME_LEN, "%02d:%02d", sTm.tm_hour, sTm.tm_min);

			String^ stDate = (DateTime::FromBinary(psLog->tTimeSent)).ToString("MM/dd/yyyy");
			String^ stTime = (DateTime::FromBinary(psLog->tTimeSent)).ToString("hh:mm");

			if(bReprint)
				stTime += " R";

			for(int i=0; i<stDate->Length; i++)
				acDate[i] = (char)stDate[i];
			for(int i=0; i<stTime->Length; i++)
				acTime[i] = (char)stTime[i];

			memset(acBuf, 0, PRINT_LEN);
			memset(acBuf, ' ', nLen);

////				if(pAll->eAsType != A_PROD)
////			strcpy(acBuf, "\
//.silo_num................................................plant_num.............\n\
//.customer_name_1.........................................cust_code.............\n\
//.order_num...............................................order_id..............\n\
//.project_code............................................load_tax..............\n\
//.truck_id................................................grand_total...........\n\
//.date....................................................gross.................\n\
//.ticket_num..............................................tare..................\n\
//.del_addr_1..............................................load..................\n\
//.del_addr_2..............................................mix_price.............\n\
//.lot_num.................................................subtotal..............\n\
//.po_num..................................................tic_tax...............\n\
//.zone....................................................total.................\n\
//.time................................................... order_cum_total.......\n\
//.job_name................................................load_size.............\n\
//.mix_code................................................drops_num.............\n\
//.mix_desc......................................................................\n\
//.unit..........................................................................\n\
//.loads_delivered...............................................................\n\
//.cum_qty.......................................................................\n\
//.del_inst_1....................................................................\n\
//.del_inst_2....................................................................\n\
//.del_inst_3....................................................................\n\
//.del_inst_4....................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//...............................................................................\n\
//");

			acBuf[0] = CR;

			for(ii=0; ii<=psTic->nLineNum; ii++)
				acBuf[ii*psTic->nLineLen-1] = LF;

			//-print text fields-----------------------------------------------
			for(int i=0; i<TEXT_FIELDS; i++)
			{
				if(psTic->asText[i].nOffs > 0)
					strcpy_s(&acBuf[psTic->asText[i].nOffs], 40, psTic->asText[i].acText);	
			}

			if(psTic->nPlantNum > 0) sprintf_s(&acBuf[psTic->nPlantNum],20, "%d", psLog->sT.plant_num);
			if(psTic->nTicket > 0) sprintf_s(&acBuf[psTic->nTicket], 10,"%d", psLog->sT.ticket_num);
			if(psTic->nMixCode > 0)strncpy_s(&acBuf[psTic->nMixCode], 11,psLog->sT.mix_code, strlen(psLog->sT.mix_code));	
			if(psTic->nMixDesc > 0)strncpy_s(&acBuf[psTic->nMixDesc], 25,psLog->sT.mix_desc, strlen(psLog->sT.mix_desc));	

			if(psTic->nCustCode > 0)strncpy_s(&acBuf[psTic->nCustCode], 9, psLog->sT.customer_code, strlen(psLog->sT.customer_code));	
			if(psTic->nCustomer > 0)strncpy_s(&acBuf[psTic->nCustomer], 33,psLog->sT.customer_name_1, strlen(psLog->sT.customer_name_1));	

			if(psTic->nPoNum > 0)strncpy_s(&acBuf[psTic->nPoNum], 17,psLog->sT.po_number, strlen(psLog->sT.po_number));	
			if(psTic->nOrderNum > 0) sprintf_s(&acBuf[psTic->nOrderNum], 10,"%d", psLog->sT.order_num);

			if(psTic->nDelAddr1 > 0)strncpy_s(&acBuf[psTic->nDelAddr1], 33,psLog->sT.del_addr_1, strlen(psLog->sT.del_addr_1));	
			if(psTic->nDelAddr2 > 0)strncpy_s(&acBuf[psTic->nDelAddr2], 33,psLog->sT.del_addr_2, strlen(psLog->sT.del_addr_2));	

			if(psTic->nDelInst1 > 0)strncpy_s(&acBuf[psTic->nDelInst1], 33,psLog->sT.del_inst_1, strlen(psLog->sT.del_inst_1));	
			if(psTic->nDelInst2 > 0)strncpy_s(&acBuf[psTic->nDelInst2],33, psLog->sT.del_inst_2, strlen(psLog->sT.del_inst_2));	
			if(psTic->nDelInst3 > 0)strncpy_s(&acBuf[psTic->nDelInst3],33, psLog->sT.del_inst_3, strlen(psLog->sT.del_inst_3));	
			if(psTic->nDelInst4 > 0)strncpy_s(&acBuf[psTic->nDelInst4],33, psLog->sT.del_inst_4, strlen(psLog->sT.del_inst_4));	

			if(psTic->nUnit > 0)strncpy_s(&acBuf[psTic->nUnit], 5,psLog->sT.unit, strlen(psLog->sT.unit));	

			if(psTic->nDriverName > 0)strncpy_s(&acBuf[psTic->nDriverName],33, psLog->sT.driver_name, strlen(psLog->sT.driver_name));	//DC 4.0.7

			if(psTic->nZone > 0)strncpy_s(&acBuf[psTic->nZone], 9,psLog->sT.zone, strlen(psLog->sT.zone));	
			if(psTic->nProjCode > 0)strncpy_s(&acBuf[psTic->nProjCode], 17,psLog->sT.project_code, strlen(psLog->sT.project_code));	
			if(psTic->nLotNum > 0)strncpy_s(&acBuf[psTic->nLotNum], 9,psLog->sT.lot_num, strlen(psLog->sT.lot_num));	
			if(psTic->nLoadsDlvrd > 0) sprintf_s(&acBuf[psTic->nLoadsDlvrd], 8,"%d", psLog->sT.loads_delivered);
			if(psTic->nJobName > 0)strncpy_s(&acBuf[psTic->nJobName], 17,psLog->sT.job_name, strlen(psLog->sT.job_name));	
	
			if(psTic->nCumQty > 0)sprintf_s(&acBuf[psTic->nCumQty], 8,"%6.2f", psLog->sT.cum_qty);

			//if(psTic->nSiloNum > 0) sprintf_s(&acBuf[psTic->nSiloNum], "%d", psLog->nSilo);				// silo
			if(psTic->nDrops > 0) sprintf_s(&acBuf[psTic->nDrops], 8,"%d", psLog->nDrops);					// nDrops
			
			if(psTic->nLaneNum > 0) strncpy_s(&acBuf[psTic->nLaneNum], 33,psLog->sT.user_defined_46, strlen(psLog->sT.user_defined_46));				// lane
			if(psTic->nSiloNum > 0) strncpy_s(&acBuf[psTic->nSiloNum], 33,psLog->sT.user_defined_47, strlen(psLog->sT.user_defined_47));				// silo
			

			if(psTic->nTax > 0)sprintf_s(&acBuf[psTic->nTax], 8,"%6.4f", psLog->fTax);						// fTax
			if(psTic->nTruck > 0) strncpy_s(&acBuf[psTic->nTruck], 33, psLog->sT.truck_id, strlen(psLog->sT.truck_id)); // truck id
			if(psTic->nOrderId > 0)strncpy_s(&acBuf[psTic->nOrderId],33, psLog->sT.order_id, strlen(psLog->sT.order_id)); // order id

			if(psTic->nTarget > 0) sprintf_s(&acBuf[psTic->nTarget], 10,"%6.2f", psLog->sT.load_size);
			
			if(!psIni->bScaleInLB)
			{
				if(psTic->nLoad > 0)
				{
					if(psLog->bPrintTarget)
						sprintf_s(&acBuf[psTic->nLoad], 8,"%6.2f", psLog->sT.load_size);
					else
						sprintf_s(&acBuf[psTic->nLoad], 8,"%6.2f", psLog->fLoad);
				}
				if(psTic->nTruckTare > 0) sprintf_s(&acBuf[psTic->nTruckTare], 8,"%6.2f", psLog->fTruckTare);	//fTruckTare
				if(psTic->nGross > 0) sprintf_s(&acBuf[psTic->nGross], 8,"%6.2f", psLog->fGross);
				if(psTic->nOrderNumTotal > 0)sprintf_s(&acBuf[psTic->nOrderNumTotal], 8,"%6.2f", psLog->sT.order_cum_total);

				if(psTic->nOrderNumTotalTNtoLB > 0)sprintf_s(&acBuf[psTic->nOrderNumTotalTNtoLB], 8, "%6.0f", psLog->sT.order_cum_total*2000);	//DC 3.2.8
				if(psTic->nTruckTareTNtoLB > 0) sprintf_s(&acBuf[psTic->nTruckTareTNtoLB], 8,"%6.0f", psLog->fTruckTare*2000);	//DC 3.2.8 fTruckTare TN to LB
				if(psTic->nGrossTNtoLB > 0) sprintf_s(&acBuf[psTic->nGrossTNtoLB], 8,"%6.0f", psLog->fGross*2000);		//DC 3.2.8 TN to LB
				if(psTic->nLoadTNtoLB > 0)		//DC 3.2.8 TN to LB
				{
					if(psLog->bPrintTarget)
						sprintf_s(&acBuf[psTic->nLoadTNtoLB], 8, "%6.0f", psLog->sT.load_size*2000);
					else
						sprintf_s(&acBuf[psTic->nLoadTNtoLB], 8,"%6.0f", psLog->fLoad*2000);
				}
			}
			else
			{
				if(psTic->nLoad > 0)
				{
					if(psLog->bPrintTarget)
						sprintf_s(&acBuf[psTic->nLoad], 8,"%6.0f", psLog->sT.load_size);
					else
						sprintf_s(&acBuf[psTic->nLoad], 8,"%6.0f", psLog->fLoad);
				}
				if(psTic->nTruckTare > 0) sprintf_s(&acBuf[psTic->nTruckTare], 8,"%6.0f", psLog->fTruckTare);	//fTruckTare
				if(psTic->nGross > 0) sprintf_s(&acBuf[psTic->nGross], 8, "%6.0f", psLog->fGross);
				if(psTic->nOrderNumTotal > 0)sprintf_s(&acBuf[psTic->nOrderNumTotal], 8, "%6.0f", psLog->sT.order_cum_total);
			}

			if(psTic->nSubtotal > 0)sprintf_s(&acBuf[psTic->nSubtotal], 8, "%6.2f", psLog->sT.subtotal);
			if(psTic->nGrandTotal > 0) sprintf_s(&acBuf[psTic->nGrandTotal], 8, "%6.2f", psLog->sT.grand_total);

			if(psTic->nLoadTax > 0)sprintf_s(&acBuf[psTic->nLoadTax], 8, "%6.2f", psLog->fLoadTax);

			if((psTic->nMixPrice > 0) && (psLog->sT.mix_price > 0.0))
				sprintf_s(&acBuf[psTic->nMixPrice], 8, "%6.2f", psLog->sT.mix_price);
			if(psTic->nTotal > 0) sprintf_s(&acBuf[psTic->nTotal], 8, "%6.2f", psLog->fTotal);

//DC 3.2.9			if(psTic->nDate > 0)sprintf_s(&acBuf[psTic->nDate], "%s", acDate);
//DC 3.2.9			if(psTic->nTime > 0)sprintf_s(&acBuf[psTic->nTime], "%s", acTime);
			DateTime^ pDate = DateTime::FromBinary(psLog->tTimeSent);				//DC 3.2.9
			if (psTic->nDate > 0)
			{
				std::string strNativeString;

				MarshalStr(pDate->ToString("MM/dd/yyyy"), strNativeString);

				sprintf_s(&acBuf[psTic->nDate], 20, "%s", strNativeString.c_str());
			}
			if (psTic->nTime > 0)
			{
				std::string strNativeString;

				MarshalStr(pDate->ToString("HH:mm"), strNativeString);

				sprintf_s(&acBuf[psTic->nTime], 20, "%s", strNativeString.c_str());
			}

			// print extra products -------------------------------------------
			if(psTic->nExtraLine > 0)
			{
				nOffs = psTic->nExtraLine;
				psProd = psLog->sT.prods;
				int nCount = 0;

				while((nCount < psTic->nExtraMax) && (psProd->name[0] != 0))
				{
					if(psProd->load_qty > 0.0)
					{
						if(psTic->nExLoad>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExLoad], 8, "%6.2f"   , psProd->load_qty);
						if(psTic->nExName>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExName], 9,"%s"		, psProd->name);
						if(psTic->nExDesc>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExDesc], 17,"%s"		, psProd->desc);
						if(psTic->nExUnit>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExUnit], 5,"%s"		, psProd->um);
						if((psTic->nExPrice>0) && (psProd->price>0)) 
							sprintf_s(&acBuf[nOffs+psTic->nExPrice], 8, "%6.2f"	, psProd->price);
						if(psTic->nExAmount>0 && psProd->amount>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExAmount], 8, "%6.2f"	, psProd->amount);
						if(psTic->nExOrder>0 && psProd->order_qty>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExOrder], 8, "%6.2f"	, psProd->order_qty);
						if(psTic->nExCum>0 && psProd->cum_qty>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExCum], 8, "%6.2f"	, psProd->cum_qty);
						if(psTic->nExLong>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExLong], 41,"%s"		, psProd->long_desc);
						if(psTic->nExPriceUm>0) 
							sprintf_s(&acBuf[nOffs+psTic->nExPriceUm], 13,"%s"	, psProd->price_um);
						nCount++;
						nOffs += psTic->nLineLen;
					}
					psProd++;
				}
			}
			// print acBuf -------------------------------------------------------------
			for(ii=1; ii<=nLen; ii++)
				if(acBuf[ii] == NULL) 
					acBuf[ii] = ' ';

			switch(nPrinter)
			{
				//case 1: pAll->qPrint1->Enqueue(gcnew String(acBuf)); break;
				//case 2: pAll->qPrint2->Enqueue(gcnew String(acBuf)); break;
				//case 3: pAll->qPrint3->Enqueue(gcnew String(acBuf)); break;
				case 4: 
					pAll->qPrint4->Enqueue(gcnew String(acBuf)); 
					break;
				//case 5: pAll->q2ndPrint1->Enqueue(gcnew String(acBuf)); break;	//DC 4.0.2
				//case 6: pAll->q2ndPrint2->Enqueue(gcnew String(acBuf)); break;	//DC 4.0.2
				//case 7: pAll->q2ndPrint3->Enqueue(gcnew String(acBuf)); break;	//DC 4.0.2
				//case 8: pAll->q2ndPrint4->Enqueue(gcnew String(acBuf)); break;	//DC 4.0.2
				default:
					break;
			}

			return;
		}
		/// <summary>
		/// MarshalString
		/// </summary>
		/// <param name="s"></param>
		/// <param name="outputstring"></param>
		void MarshalStr(String^ s, std::string& outputstring)
		{
			const char* kPtoC = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
			outputstring = kPtoC;
			System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)kPtoC));
		}
	};
}