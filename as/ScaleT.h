#pragma once
#include "StdAfx.h"

using namespace System;
using namespace System::Threading;
using namespace System::IO::Ports;

namespace As
{
// THREAD class interfacing scale =============================================
ref class CScale
{
private:
	CScale(void)
	{
	}
public:
	//-------------------------------------------------------------------------
	static void ThreadProc(Object^ pSca)
	{
#define SCALE_BUF 4096
#define VAL_NBR  	8
#define VAL_MASK    VAL_NBR-1

		Scale^ pS = (Scale^) pSca;
		INI *psIni = pS->psIni;
		SCALE *psScale = pS->psScale;
		All^	pAll = pS->pAll;

		clock_t nOld, nNew;
		double adVals[VAL_NBR] = {0};
		int nValIdx = 0;
		 int nCnt;
		 int nIdx;
		 double fValue;
		 double fOldVal = 0;
		 double fOldCnt = 0;
		 bool bSign;
		 char cChar;

		 // Buffer to store the serial bytes.
		 cli::array<Byte>^data = gcnew cli::array<Byte>(SCALE_BUF);
		 cli::array<Byte>^go = gcnew cli::array<Byte>(4);


		//---------------------------------------------------------------------------
		while(true)
		{	
			 // Create a SerialPort.
			 SerialPort port(gcnew String(psScale->acCom), psScale->nBaud);

			 try
			 {
				 port.Open();
				 nCnt = 0;

				 while(true)
				 {
					 nCnt +=  port.Read(data, nCnt, SCALE_BUF-nCnt-1);

					 //DC 3.2.0  LB
					 if(psIni->bScaleInLB)
					 {
						 if(nCnt >= SCALE_MSG)
						 {
							 nIdx = 0;
							 while((nIdx < nCnt) && (data[nIdx] != 0xd))
								 nIdx++;

							 if((nCnt-nIdx) >= SCALE_MSG)
							 {
								 nCnt = 0;							 

								 fValue = (data[2]-'0')*100000
									 + (data[3]-'0')*10000
									 + (data[4]-'0')*1000
									 + (data[5]-'0')*100
									 + (data[6]-'0')*10
									 + (data[7]-'0');	

								 if(data[1] == '-')
									 fValue *= -1;

								 if((abs(fOldVal - fValue) > (fOldVal/2))
								 && (fOldCnt < 5))
								 {
									 fOldCnt++;
									 fValue = fOldVal;
									 psScale->nErrCnt++;
								 }
								 else
								 {
									fOldCnt = 0;
									fOldVal = fValue;
								 }
								 
								 /*if(pAll->psIni->bMetric)
									 fValue = (int)(fValue * KG2LB);*/

								 psScale->dValue = fValue;

								 if(psIni->bTest)
								 {
									 for(int ii = 0; ii<SCALE_MSG-3; ii++)
										 psScale->acData[ii] = data[ii+1];
									 psScale->acData[SCALE_MSG-4] = 0;
								 }
								 // update flow rate
								 psScale->dFlow =  adVals[nValIdx] - fValue;
								 adVals[nValIdx] = fValue;
								 nValIdx = ++nValIdx & VAL_MASK;

								 nNew = clock();
								 psScale->nClock = nNew - nOld;
								 nOld = nNew;

								 psScale->bSample = true;
							 }
						 }
					 }
					 else
					 {
						 if(nCnt >= psIni->nSclLen)
						 {
							 nIdx = 0;
							 while((nIdx < nCnt) && (data[nIdx] != psIni->cSclFrame))
								 nIdx++;

							 if((nCnt-nIdx) >= psIni->nSclLen)
							 {
								nCnt = 0;		
								bSign = false;

								if(nIdx == 0)
								{
									fValue = (data[psIni->nScl001]-'0')*0.01
										   + (data[psIni->nScl01]-'0')*0.1
										   // decimal point
										   + (data[psIni->nScl1]-'0')*1.0;

									if(psIni->nScl10>0)
									{
										cChar = data[psIni->nScl10];
										if(cChar >= '0')
											fValue += (cChar-'0')*10.0;
										else if(cChar == psIni->cSclSchar)
											bSign = true;
									}
									if(psIni->nScl100>0)
									{
										cChar = data[psIni->nScl100];
										if(cChar >= '0')
											fValue += (cChar-'0')*100.0;
										else if(cChar == psIni->cSclSchar)
											bSign = true;
									}
									if(psIni->nScl1000>0)
									{
										cChar = data[psIni->nScl1000];
										if(cChar >= '0')
											fValue += (cChar-'0')*1000.0;
										else if(cChar == psIni->cSclSchar)
											bSign = true;
									}
									 if((psIni->nSclSign>0) && (data[psIni->nSclSign] == psIni->cSclSchar))
										 bSign = true;

									 if(bSign)
										 fValue *= -1.0;

									 psScale->dValue = fValue;

									 if(psIni->bTest)
									 {
										 for(int ii = 0; ii<psIni->nSclLen; ii++)
											 psScale->acData[ii] = data[ii+1];
										 psScale->acData[psIni->nSclLen] = 0;
	//									 for(int ii = 0; ii<psIni->nScl001+1; ii++)
	//										 psScale->acData[ii] = data[ii+1];
	//									 psScale->acData[psIni->nScl001+1] = 0;
									 }
									 // update flow rate
									 psScale->dFlow =  adVals[nValIdx] - fValue;
									 adVals[nValIdx] = fValue;
									 nValIdx = ++nValIdx & VAL_MASK;

									 nNew = clock();
									 psScale->nClock = nNew - nOld;
									 nOld = nNew;

									 psScale->bSample = true;
								}
							 }
						 }
						 if(pAll->eAsType == A_SIM)
						 {
							 go[0] = go[1] = go[2] = go[3] = psScale->cGo;
							 port.Write(go, 0, 4);
						 }
					 }
				 }
			 }
			 catch ( System::UnauthorizedAccessException^ ex ) 
			 {
				  pAll->pExc += "\nSCALE ACCESS Exception: " + ex->Message;
			 }
			 catch ( IO::IOException^ ex ) 
			 {
				  pAll->pExc += "\nSCALE IO Exception: " + ex->Message;
			 }

			 // Close everything.
			 port.Close();
			 Thread::Sleep(1000);
		}
	}
	//----------------------------------------------------------------------------
};
}
