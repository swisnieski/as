#pragma once
#include "StdAfx.h"

using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Runtime::Serialization;

namespace As
{
	// THREAD class reading IP->SERIAL scales  ===================================
	// TCP client talks to scale server 
	ref class CScaleTPS
	{
	private:
		CScaleTPS(void)
		{
		}
	public:
		//-------------------------------------------------------------------------
		static void ThreadProc(Object^ pScaIn)
		{
#define SCALET_BUF 256			//DC 3.2.6
			Scale^ pSca = (Scale^) pScaIn;
			INI *psIni = pSca->psIni;
			All^ pAll = pSca->pAll;
			SCALE *psScale = pSca->psScale;
//			SCALOC *psScaloc = pSca->psScaloc;
			clock_t nNew;
			//clock_t nOld, nNew;
			double adVals[VAL_NBR] = {0};
			int anVals[VAL_NBR] = {0};
			int nValIdx = 0;
			int nOldVal = 0;
			int nOldCnt = 0;
			int nCnt;
			int nIdx;
			//int nValue;
			bool bSign;
			double fValue;
			double fOldVal = 0;
			double fOldCnt = 0;
			double fLastGoodVal = 0;		//DC 4.0.6
			char cChar;

			// Buffer to store the serial bytes.
			cli::array<Byte>^data = gcnew cli::array<Byte>(SCALET_BUF);
			cli::array<Byte>^cmd = gcnew cli::array<Byte>(2);

			NetworkStream^ stream; 
			TcpClient^ client;
			IPEndPoint^ endPoint = gcnew IPEndPoint(pSca->pScl->pIp, pSca->pScl->nPort);

			cmd[0] = 'q';
			cmd[1] = '\r';

			//---------------------------------------------------------------------------
			while(true)
			{	
				try
				{
					 // Create a TcpClient.
					 client = gcnew TcpClient();
					 client->Connect(endPoint);

					 // Get a client stream for reading and writing.
					 stream = client->GetStream();
					 stream->ReadTimeout = 10000;
					 stream->Flush();

					//---------------------------------------------------------
					while(true)
					{
//						 nCnt = stream->Read( data, 0, SCALE_BUF);
						 nCnt +=  stream->Read(data, nCnt, SCALET_BUF-nCnt);
						 
						 //DC 3.2.0  LB
						 if(psIni->bScaleInLB)
						 {
							 if(nCnt >= psIni->nSclLen)		//DC 3.2.5
							 {
								 nIdx = 0;
								 while((nIdx < nCnt) && (data[nIdx] != psIni->cSclFrame)) //DC 3.2.5
									 nIdx++;

								 if((nCnt-nIdx) >= psIni->nSclLen)		//DC 3.2.5
								 {
									 nCnt = 0;							 


	//						 if(nCnt >= 16 && (data[0] == ' ' || data[0] == '-') )
	//						 {
								 psScale->nErrCnt = 0;
								 fValue = 0;

								 if(data[2] >= '0' && data[2] <= '9')  
									 fValue += (data[2]-'0')*100000;

								 if(data[3] >= '0' && data[3] <= '9')  
									 fValue += (data[3]-'0')*10000;

								 if(data[4] >= '0' && data[4] <= '9') 
									 fValue += (data[4]-'0')*1000;

								 if(data[5] >= '0' && data[5] <= '9') 
									 fValue += (data[5]-'0')*100;

								 if(data[6] >= '0' && data[6] <= '9') 
									 fValue += (data[6]-'0')*10;

								 if(data[7] >= '0' && data[7] <= '9') 
									 fValue += (data[7]-'0');

								 if(data[1] == '-')
									 fValue *= -1;

								 if((abs(fOldVal - fValue) > (fOldVal/2))
									 && (nOldCnt < 5))
								 {
									 nOldCnt++;
									 fValue = fOldVal;
									 psScale->nErrCnt++;
								 }
								 else
								 {
									 nOldCnt = 0;
									 fOldVal = fValue;
								 }

	//							 if(pAll->psIni->bMetric)
	//								 nValue = (int)(nValue * KG2LB);

								 psScale->dValue = fValue;

								 if(psIni->bTest)
								 {
									 for(int ii = 0; ii<nCnt; ii++)
										 psScale->acData[ii] = data[ii];
									 psScale->acData[nCnt] = 0;
								 }
								 // update flow rate
								 psScale->dFlow =  adVals[nValIdx] - fValue;
								 adVals[nValIdx] = fValue;
								 nValIdx = ++nValIdx & VAL_MASK;

								 nNew = clock();
								 psScale->nClock = nNew - psScale->tSample;
								 psScale->tSample = nNew;	
								 psScale->bSample = true;
								}
							 }
						 }
						 else
						 {
							 if(nCnt >= psIni->nSclLen)		//DC 3.2.5
							 {
								 nIdx = 0;
								 while((nIdx < nCnt) && (data[nIdx] != psIni->cSclFrame)) //DC 3.2.5
									 nIdx++;

								 if((nCnt-nIdx) >= psIni->nSclLen)		//DC 3.2.5
								 {
									 nCnt = 0;
									 bSign = false;
									 psScale->nErrCnt = 0;
									 fValue = 0;

//									 if(nIdx == 0)
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

										 if((abs(fOldVal - fValue) > (fOldVal/2))
											 && (nOldCnt < 5))
										 {
											 nOldCnt++;
											 fValue = fOldVal;
											 psScale->nErrCnt++;
										 }
										 else
										 {
											 nOldCnt = 0;
											 fOldVal = fValue;
										 }
										 
										 if(fValue > 0)						//DC 4.0.6
										 {
										   psScale->dValue = fValue;
										   fLastGoodVal = fValue;
										 }
										 else if( fValue < 0 && fLastGoodVal > 0)
										 {
											psScale->dValue = fLastGoodVal;
										 }
										 else
											 psScale->dValue = fValue;

										 if(psIni->bTest)
										 {
											 for(int ii = 0; ii<nCnt; ii++)
												 psScale->acData[ii] = data[ii+1];
											 psScale->acData[nCnt] = 0;
		//									 for(int ii = 0; ii<psIni->nScl001+1; ii++)
		//										 psScale->acData[ii] = data[ii+1];
		//									 psScale->acData[psIni->nScl001+1] = 0;
										 }
										 // update flow rate
										 psScale->dFlow =  adVals[nValIdx] - fValue;
										 adVals[nValIdx] = fValue;
										 nValIdx = ++nValIdx & VAL_MASK;

										 nNew = clock();
										 psScale->nClock = nNew - psScale->tSample;
										 psScale->tSample = nNew;

										 psScale->bSample = true;
									 }
								 }
							 }
						 }
					}
				}
				//-----------------------------------------------------------------
				catch ( Exception^ ex ) 
				 {
					 pAll->pExc += "\nSCALS: Exception: " + ex->Message;
				 }

				// Shutdown and end connection
				if(stream) stream->Close(0);
				if(client) client->Close();

				Thread::Sleep(1000);
			}
		}
		///////////////////////////////////////////////////////////////////////
	};
}
