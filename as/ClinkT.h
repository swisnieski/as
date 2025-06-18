#pragma once
#include <ostream>
#include "StdAfx.h"
#using<system.dll>

using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Runtime::Serialization;

namespace As
{
	// THREAD class for cbc TCPIP communication ===================================
	// TCPIP client in remote node talks to server in local node
	//=============================================================================
	ref class CClink
	{
	private: 
		CClink(void)
		{
		}
		//-------------------------------------------------------------------------
	public:
		static void ThreadProc(Object^ pAllIn)
		{
			All^ pAll = (All^) pAllIn;
			MemoryStream^ ms;
			BinaryFormatter^ formatter = gcnew BinaryFormatter;
			NetworkStream^ stream; 
			FileStream^ fs;
			String^ stFile;
			clock_t tOld = clock(), tNew;
			Cmd^	pCmd;
			uchar	*pcT;
			int		nLen;
			int		nData;
			uchar   cSum;
			int     nRepeat;
			int j;

			Generic::List<Job^>^  lJobs50 = gcnew Generic::List<Job^>();

			// Buffers for clink messages.
			cli::array<Byte>^ cmd = gcnew cli::array<Byte>(CMD_LEN);
			cli::array<Byte>^ hdr = gcnew cli::array<Byte>(HDR_LEN);
			cli::array<Byte>^ data;
			cli::array<Byte>^ job;

			pAll->nCmd = 0;
			TcpClient^ client;

			//-----------------------------------------------------------------
			while(true)
			{	
				try
				{
					pAll->nClinkOk = 2;							// blue

					// Connect TcpClient.
					client = gcnew TcpClient();
					client->Connect(gcnew IPEndPoint(pAll->pRem->pIp, pAll->pRem->nPort));

					// Get a client stream for reading and writing.
					stream = client->GetStream();
					stream->Flush();

					pAll->nClinkOk = 1;							// white
					
					//---------------------------------------------------------
					while(true)
					{
						nRepeat = 0;
						pCmd = nullptr;

						if(pAll->qCmd->Count > 0)	
						{
							pCmd = pAll->qCmd->Dequeue();
						}
						else if(pAll->bIni)
						{
							pAll->bIni = false;
							pCmd = gcnew Cmd();
							pCmd->cId = CL_INI;
						}
						else
						{
							Thread::Sleep(100);
							continue;
						}

						 tNew = clock();
						 pAll->tClinkClock = tNew - tOld;
						 tOld = tNew;

						 pAll->nClinkOk = pAll->tClinkClock > 500 ? 3 : 1;    // yellow
						//-------------------------------------------------
loopX:					switch(pCmd->cId)
						{
						//case CL_LOGIN:			// 1
						//	nData = 0;
						//	if(pAll->stPass != nullptr)
						//	{
						//		nData = pAll->stPass->Length;
						//		data = gcnew array<Byte>(nData);
						//		for(int i=0; i< nData; i++)
						//			data[i] = (uchar)pAll->stPass[i];
						//	}
						//	break;

						case CL_LOGIN:

						case CL_INI:			// 2

						case CL_JOB:
						case CL_OLD:									
						case CL_TRUCKS:			// 6						
						case CL_JOBS_NEW:		// 10
						case CL_JOBS_OLD:		// 11
						
						
						
						case CL_ABORT4:
						case CL_KEY:			// 17
						
						case CL_FLOW:			// 19
						case CL_LOG:			// 20
						case CL_MAN:			// 21
						case CL_INV:			// 22
						case CL_GRA:			// 23
						case CL_JOB_ARMED:		// 26
						case CL_JOBXS:			// 27
						case CL_CLIMIT:			// 19
							nData = 0;
							break;

						case CL_YARD:			// 23				
						case CL_MATS:			// 24				
							nData = sizeof(RTIME);
							data = gcnew cli::array<Byte>(nData);
							pcT = (uchar *)pAll->psTime;
							for(int i=0; i<nData; i++)
								data[i] = pcT[i];
							break;

						// send data commands
						//----------------------------------------------------
						case CL_SARMED:	
						case CL_SJOB4:	
							pAll->bJob4 = true;
							ms = gcnew MemoryStream();
							try
							{
								formatter->Serialize( ms, pAll->pJob4 );
								nData = (int)ms->Length;
								data = ms->ToArray();
								/*job = ms->ToArray();
								nData = (int)ms->Length + sizeof(LOG_REC);
								data = gcnew array<Byte>(nData);
								job->CopyTo(data, 0);
								pcT = (uchar *)(psIni->sLog4);
								for(int i=0; i<sizeof(LOG_REC); i++)
									data[(int)ms->Length+ i]= pcT[i];*/
							}
							catch ( SerializationException^ ex ) 
							{
								pAll->stExc += "\nCLINK Serialization Exception: " + ex->Message;
								stream->Flush();
								continue;
							}
							finally
							{
								ms->Close();
							}
							break;

						case CL_SJOB:	
							pAll->bJob4 = true;
							ms = gcnew MemoryStream();
							try
							{
								formatter->Serialize( ms, pAll->pJob );
								nData = (int)ms->Length;
								data = ms->ToArray();
							}
							catch ( SerializationException^ ex ) 
							{
								pAll->stExc += "\nCLINK Serialization Exception: " + ex->Message;
								stream->Flush();
								continue;
							}
							finally
							{
								ms->Close();
							}
							break;

						case CL_STRUCK:
							ms = gcnew MemoryStream();
							formatter->Serialize( ms, pAll->lTruck );
							nData = (int)ms->Length;
							data = ms->ToArray();
							break;

						/*case CL_SMIX:
							ms = gcnew MemoryStream();
							formatter->Serialize( ms,  pAll->lMix);
							nData = (int)ms->Length;
							data = ms->ToArray();
							break;*/

						/*case CL_SJOBX:
							ms = gcnew MemoryStream();
							formatter->Serialize( ms,  pAll->lJobx);
							nData = (int)ms->Length;
							data = ms->ToArray();
							break;

						case CL_SADX:
							ms = gcnew MemoryStream();
							formatter->Serialize( ms, pAll->lAdmix );
							nData = (int)ms->Length;
							data = ms->ToArray();
							break;*/

						/*case CL_SMOIST:
							for(int i = 0; i<BINS; i++)
							{
								sMoist.abMoist[i] = pAll->psAdp->asAggs[i].bMoistProbe;
								sMoist.adMoist[i] = pAll->psAdp->asAggs[i].dMoist;
							}
							nData = sizeof(RMOIST);
							data = gcnew array<Byte>(nData);
							pcT = (uchar *)&sMoist;
							for(int i=0; i<nData; i++)
								data[i] = pcT[i];
							break;*/

						/*case CL_SINV:
							ms = gcnew MemoryStream();
							formatter->Serialize( ms,  pAll->pInv);
							nData = (int)ms->Length;
							data = ms->ToArray();
							break;*/

						//case CL_SADP:			// 
						//	nData = ADP_LEN;
						//	data = gcnew array<Byte>(nData);
						//	pcT = (uchar *)pAll->psAdp;
						//	for(int i=0; i<nData; i++)
						//		data[i] = pcT[i];
						//	break;

						/*case CL_SHAUL:
							ms = gcnew MemoryStream();
							formatter->Serialize( ms,  pAll->lHaul);
							nData = (int)ms->Length;
							data = ms->ToArray();
							break;*/
						}

						cSum = 0;
						if(nData > 0)
							for(int i=0; i<nData; i++)
								cSum += data[i];

						cmd[0] = pCmd->cId;
						cmd[1] = (pCmd->nKey >> 8);
						cmd[2] = (pCmd->nKey & 0xff);
						cmd[3] = (pCmd->nIdx >> 24) &0xff;
						cmd[4] = (pCmd->nIdx >> 16) &0xff;
						cmd[5] = (pCmd->nIdx >>  8) &0xff;
						cmd[6] = (pCmd->nIdx >>  0) &0xff;
						cmd[7] = (nData >> 16) & 0xff;
						cmd[8] = (nData >> 8) & 0xff;
						cmd[9] =  nData      & 0xff;
						cmd[10] = cSum;					// checksum of data
						cmd[11] = cmd[0]+cmd[1]+cmd[2]+cmd[3]+cmd[4]+cmd[5]+cmd[6]+cmd[7]+cmd[8]+cmd[9]+cmd[10];
						//-------------------------------------------------
						stream->Write( cmd, 0, CMD_LEN);

						if(nData > 0)
							stream->Write( data, 0, nData);
						
						int n = stream->Read( hdr, 0, HDR_LEN);	// wrong header size

						if(n < HDR_LEN)	// wrong header size						
						{
							stream->Flush();
							pAll->nClinkErr++;
							if(++nRepeat >= LIMIT)continue;
							else goto loopX;
						}

						cSum = hdr[0]+hdr[1]+hdr[2]+hdr[3]+hdr[4];
						
						if(hdr[5] != cSum)							// wrong hdr checksum
						{
							pAll->nClinkErr++;
							stream->Flush();
							if(++nRepeat > LIMIT) continue;
							else goto loopX;
						}
						nData = (hdr[1] << 16) +(hdr[2] << 8) +hdr[3]; 
						j=0;
						nLen = 0;
						
						//////////////////////////////////////////////////////////////////////////////
						// Read the data bytes.
						if(nData > 0)
						{
							data = gcnew cli::array<Byte>(nData); 

							while(nLen < nData && j++ < REM_CNT)
							{
								nLen += stream->Read( data, nLen, nData-nLen);
								Thread::Sleep(100);
							}
							if(nLen != nData)						// wrong data size
							{
								stream->Flush();
								pAll->nClinkErr++;
								if(++nRepeat >= LIMIT)continue;
								else goto loopX;
							}
							cSum = 0;
							for(int i=0; i<nLen; i++)
								cSum += data[i];

							if(hdr[4] != cSum)					// wrong data checksum
							{
								pAll->nClinkErr++;
								stream->Flush();
								if(++nRepeat > LIMIT) continue;
								else goto loopX;
							}
						}
						pAll->nCmd++;
						pAll->nMax = max(nLen, pAll->nMax);

						//---------------------------------------------
						switch(pCmd->cId)
						{
						case CL_LOGIN:
							pAll->cLogin = hdr[0];
							pAll->nLen = nLen;
							if(nLen >= 5)
							{
								char acTmp[10] = {0};
								for(int i=0; i<nLen; i++)
									acTmp[i] = data[i];								
								pAll->stRemVersion = gcnew String(acTmp);
							}
							break;

						case CL_INI:
							if(nLen == sizeof(INI))
							{
								pcT = (uchar *)pAll->psIni;
								for(int i=0; i<nLen; i++)
									pcT[i] = data[i];
							}
							else
							{
								stream->Flush();
								if(++nRepeat > LIMIT) continue;
								else goto loopX;
							}
							break;

						/*case CL_OPS:
							if(nLen == sizeof(OPS))
							{
								pcT = (uchar *)pAll->psOps;
								for(int i=0; i<nLen; i++)
									pcT[i] = data[i];
							}
							else
							{
								stream->Flush();
								if(++nRepeat > LIMIT) continue;
								else goto loopX;
							}
							break;*/

						/*case CL_TIC:
							if(nLen == sizeof(TIC))
							{
								pcT = (uchar *)pAll->psTic;
								for(int i=0; i<nLen; i++)
									pcT[i] = data[i];
							}
							else
							{
								stream->Flush();
								if(++nRepeat > LIMIT) continue;
								else goto loopX;
							}
							break;*/

						case CL_TRUCKS:
							ms = gcnew MemoryStream(nLen);
							try
							{
								ms->Write(data, 0, nLen);
								ms->Seek(0, SeekOrigin::Begin);
								pAll->lTruck = (Generic::List<Truck^>^)(formatter->Deserialize( ms ));
							}
							catch ( SerializationException^ ex ) 
							{
								pAll->stExc += "\nCLINK Serialization Exception: " + ex->Message;
								stream->Flush();
								if(++nRepeat >= LIMIT)continue;
								else	goto loopX;
							}
							finally
							{
								ms->Close();
							}
							break;

						case CL_JOB:
							ms = gcnew MemoryStream(nLen);
							try
							{
								ms->Write(data, 0, nLen);
								ms->Seek(0, SeekOrigin::Begin);
								pAll->lJob = (Generic::List<Job^>^)(formatter->Deserialize( ms ));
							}
							catch ( SerializationException^ ex ) 
							{
								pAll->stExc += "\nCLINK Serialization Exception: " + ex->Message;
								stream->Flush();
								if(++nRepeat >= LIMIT)continue;
								else	goto loopX;
							}
							finally
							{
								ms->Close();
							}
							break;

						case CL_OLD:
							ms = gcnew MemoryStream(nLen);
							try
							{
								ms->Write(data, 0, nLen);
								ms->Seek(0, SeekOrigin::Begin);
								pAll->lOld = (Generic::List<Job^>^)(formatter->Deserialize( ms ));
							}
							catch ( SerializationException^ ex ) 
							{
								pAll->stExc += "\nCLINK Serialization Exception: " + ex->Message;
								stream->Flush();
								if(++nRepeat >= LIMIT)continue;
								else	goto loopX;
							}
							finally
							{
								ms->Close();
							}
							break;

						
						/*case CL_JOBS_NEW:
							ms = gcnew MemoryStream(nLen);
							try
							{
								ms->Write(data, 0, nLen);
								ms->Seek(0, SeekOrigin::Begin);
								pAll->lJobs = (Generic::List<Job^>^)(formatter->Deserialize( ms ));
							}
							catch ( SerializationException^ ex ) 
							{
								pAll->stExc += "\nCLINK Serialization Exception: " + ex->Message;
								stream->Flush();
								if(++nRepeat >= LIMIT)continue;
								else	goto loopX;
							}
							finally
							{
								ms->Close();
							}
							pAll->bRefresh = true;									
							break;

						case CL_JOBS_OLD:
							ms = gcnew MemoryStream(nLen);
							try
							{
								ms->Write(data, 0, nLen);
								ms->Seek(0, SeekOrigin::Begin);
								pAll->lJobsOld = (Generic::List<Job^>^)(formatter->Deserialize( ms ));
							}
							catch ( SerializationException^ ex ) 
							{
								pAll->stExc += "\nCLINK Serialization Exception: " + ex->Message;
								stream->Flush();
								if(++nRepeat >= LIMIT)continue;
								else	goto loopX;
							}
							finally
							{
								ms->Close();
							}
							pAll->bRefresh = true;									
							break;*/

						case CL_LOG4:
							switch(pCmd->nKey)
							{
							case C_READ:
								pcT = (uchar *)pAll->psLog;
								for(int i=0; i<nLen; i++)
									pcT[i] = data[i];
								break;
							}
							break;

						case CL_ABORT4:
							break;

						case CL_KEY:
							break;

						case CL_FLOW:
							break;

						case CL_CLIMIT:
							break;

						case CL_MAN:
							break;

						
						case CL_CBC:
							stFile = gcnew String("\\Keystone Batch\\Cbc.new");
							fs = gcnew FileStream(stFile, FileMode::Create );
							fs->Write(data, 0 , nLen);
							fs->Close();
							pAll->bRemCbc = true;
							break;

							/*
						case CL_FILE:
							stFile = gcnew String("cbc.log");
							fs = gcnew FileStream(stFile, FileMode::Create );
							fs->Write(data, 0 , nLen);
							fs->Close();							
							break;
*/
						case CL_SJOB4:
						case CL_SJOB:
						case CL_STRUCK:	
						case CL_SMIX:	
						case CL_SADX:	
						case CL_SMOIST:	
						case CL_SARMED:	
						case CL_SJOBX:	
						case CL_SINV:	
						case CL_SADP:	
						case CL_SHAUL:	
							break;

						default:
							MessageBox::Show("cmd "+cmd[0].ToString(), "CLINK CLIENT ERROR"
								, MessageBoxButtons::OK, MessageBoxIcon::Error);
							break;
						}
						//---------------------------------------------------------
						if(j >= REM_CNT)
							pAll->nKey = -2;
						else if(hdr[0] == 0)
							pAll->nKey = -1;
						/*else if(pCmd->cId != CL_OPS)
							pAll->nKey = 0;*/
						Thread::Sleep(100);
					}
				}
				//-------------------------------------------------------------
				catch ( Exception^ ex ) 
				{
					pAll->pExc += "\nCLINK Exception: " + ex->Message;
					pAll->nKey = -3;
				}

				// Shutdown and end connection
				if(stream) stream->Close(0);
				if(client) client->Close();

				pAll->nClinkOk = 0;				// red
				Thread::Sleep(1000);
			}
		}
		///////////////////////////////////////////////////////////////////////
	};
}

