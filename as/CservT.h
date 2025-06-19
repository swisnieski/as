#pragma once
#include "StdAfx.h"
#include "Log.h"

using namespace System;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections;

namespace As
{
	// THREAD class TCPIP server ==============================================
	// TCPIP client in remote node talks to server in local node
	//=========================================================================

	ref class CCserv
	{
	public:
		CCserv(All^ pAll)	//, CBufs^ poBufsIn, COps^ poOpsIn, COps2^ poOpsIn2)
		{
			//poBufs = poBufsIn;
			//poOps = poOpsIn;
			//poOps2 = poOpsIn2;
			poLog = gcnew CLog(pAll);
		}
		CCserv(void)
		{
		}

	private: 
		//static CBufs^ poBufs;
		static CLog^ poLog;
		//static COps^ poOps;			// ops class 1
		//static COps2^ poOps2;		// ops class 2

		//-------------------------------------------------------------------------
		//-------------------------------------------------------------------------
	public:
		static void ThreadProc(Object^ pAllIn)
		{
			All^ pAll = (All^) pAllIn;
			INI *psIni = pAll->psIni;
//			OPS *psOps = pAll->psOps;
			//RTIME sTime;

			//String^ stFile;
			MemoryStream^ ms;
			//FileStream^ fs;
			BinaryFormatter^ formatter = gcnew BinaryFormatter;
			Generic::List<Job^>^  lJobs50 = gcnew Generic::List<Job^>();

			uchar *pcT;
			int nLen;
			int nLen2;
			int nLinkIdx;
			int nData;
			int i;
			//int nBin;
			//int nRCnt;				//DC

			//double dMultD;
			//double dAdxD;

			bool bRun;
			bool bLogin;
			uchar cSum;

			// Buffers for ulink messages.
			cli::array<Byte>^cmd = gcnew cli::array<Byte>(CMD_LEN);		// 12
			cli::array<Byte>^hdr = gcnew cli::array<Byte>(HDR_LEN);		//  6
			cli::array<Byte>^data;
			//Job^ pJob;

			DateTime	Date; 
			DateTime	Date2; 
			//DateTime^	pStartDate;
			//DateTime^	pEndDate;

			// Create a Tcpserver.
			TcpListener^ server = gcnew TcpListener(IPAddress::Any, pAll->psIni->nRlinkPort);
			Socket^ client = nullptr;

			//---------------------------------------------------------
			while(true)
			{	
				try
				{
					pAll->nCservOk = 2;	
					bRun = true;

					// Start listening for client requests.
					server->Start();
					client = server->AcceptSocket();

					//---------------------------------------------------------
					while(bRun)
					{
						// Loop to receive all the data sent by the client.
						nLen = client->Receive(cmd, CMD_LEN, static_cast<SocketFlags>(0));
						
						if (cmd[0] == 1 && nLen == 11)					//DC For old Version Remote login update
						{
							cSum = 0;
							for(i=0; i<11-1; i++)
								cSum += cmd[i];

							if(cSum != cmd[10])							// command checksum failed
							{
								pAll->nClinkErr++;
								goto respond;
							}
							if(cmd[2] == 0)
								cmd[2] = cmd [1];
							nData = (cmd[6]<<16)+(cmd[7]<<8)+cmd[8];
						}
						else
						{
							if(nLen != CMD_LEN)							// command length failed
							{
								pAll->nClinkErr++;
								goto respond;
							}
							cSum = 0;
							for(i=0; i<CMD_LEN-1; i++)
								cSum += cmd[i];

							if(cSum != cmd[11])							// command checksum failed
							{
								pAll->nClinkErr++;
								goto respond;
							}
							nData = (cmd[7]<<16)+(cmd[8]<<8)+cmd[9];
						}
						
						if(nData > 0)
						{
							data = gcnew cli::array<Byte>(nData); 
							nLen = 0;
							int j=0;

							while(nLen < nData && j++ < REM_CNT)
							{
								nLen += client->Receive( data, nLen, nData-nLen, static_cast<SocketFlags>(0));
								Thread::Sleep(100);
							}
							if(nLen != nData)					// data length failed
							{
								pAll->nClinkErr++;
								goto respond;
							}
							cSum = 0;
							for(i=0; i<nData; i++)
								cSum += data[i];

							if(cSum != cmd[10])					// data checksum failed
							{
								pAll->nClinkErr++;
								goto respond;
							}
						}

						nLen2 = nLen;
						pAll->nSlinkCnt++;
						pAll->nCservOk = 1;
						hdr[0] = 0;
						nLen = 0;
						bLogin = false;

						//---------------------------------------------------------
						switch(cmd[0])
						{
							case CL_LOGIN:
								//if(pAll->cRemote == 0)
								{	
									hdr[0] = cmd[2];
									//pAll->cRemote = 3;
									
								}
								//	if(bLogin)
								{
									nLen = pAll->stRemVersion->Length;
									data =  gcnew cli::array<Byte>(nLen);
									for(i=0; i<nLen; i++)
										data[i] = (char)pAll->stRemVersion[i];
								}
								break;

							/*case CL_ALL:
								hdr[0] = 1;
								nLen = sizeof(ALL);
								data =  gcnew cli::array<Byte>(nLen);
								pcT = (uchar *)pAll;
								for(i=0; i<nLen; i++)
									data[i] = pcT[i];
								break;*/
							
							case CL_INI:
								hdr[0] = 1;
								nLen = sizeof(INI);
								data =  gcnew cli::array<Byte>(nLen);
								pcT = (uchar *)psIni;
								for(i=0; i<nLen; i++)
									data[i] = pcT[i];
								break;

							case CL_JOB:
								hdr[0] = 1;
								ms = gcnew MemoryStream();
								formatter->Serialize( ms, pAll->lJob );
								nLen = (int)ms->Length;
								data = ms->ToArray();
								break;

							case CL_OLD:
								hdr[0] = 1;
								ms = gcnew MemoryStream();
								formatter->Serialize( ms, pAll->lOld );
								nLen = (int)ms->Length;
								data = ms->ToArray();
								break;

							case CL_TRUCKS:
								hdr[0] = 1;
								ms = gcnew MemoryStream();
								formatter->Serialize( ms, pAll->lTruck);
								nLen = (int)ms->Length;
								data = ms->ToArray();
								break;

							case CL_STAT:
								hdr[0] = 1;
								ms = gcnew MemoryStream();
								formatter->Serialize( ms, pAll->lStat );
								nLen = (int)ms->Length;
								data = ms->ToArray();
								break;

							//case CL_JOBS_NEW:				// get first 25 new jobs
							//	hdr[0] = 1;
							//	lJobs50->Clear();
							//	for(i=0; i<min(REM_JOBS, pAll->lJob->Count); i++)
							//		lJobs50->Add(pAll->lJobs[i]);

							//	ms = gcnew MemoryStream();
							//	formatter->Serialize( ms, lJobs50 );
							//	nLen = (int)ms->Length;
							//	data = ms->ToArray();
							//	break;

						//case CL_JOBS_OLD:				// get last 25 done jobs
						//	hdr[0] = 1;
						//	lJobs50->Clear();
						//	for(i=0; i<min(REM_JOBS, pAll->lOld->Count); i++)
						//		lJobs50->Add(pAll->lJobsOld[i]);

						//	ms = gcnew MemoryStream();
						//	formatter->Serialize( ms, lJobs50 );
						//	nLen = (int)ms->Length;
						//	data = ms->ToArray();
						//	break;

							case CL_LOG4:
								switch(cmd[1])
								{
								case C_READ:   
									nLinkIdx = (cmd[3] << 24) + (cmd[4]<<16) + (cmd[5]<<8) +cmd[6];
									hdr[0] = (uchar)poLog->log(C_READ, pAll->psLog, nLinkIdx); 
									nLen = sizeof(LOG_REC);
									data =  gcnew cli::array<Byte>(nLen);
									pcT = (uchar *)pAll->psLog;
									for(i=0; i<nLen; i++)
										data[i] = pcT[i];
									break;

								/*case C_APPEND:   
									hdr[0] = poLog->log(C_APPEND, pAll->psLog, 0); 
									nLen = sizeof(LOG_REC);
									data =  gcnew cli::array<Byte>(nLen);
									pcT = (uchar *)pAll->psLog;
									for(i=0; i<nLen; i++)
										data[i] = pcT[i];
									break;

								case C_READX:   
									nLinkIdx = (cmd[3] << 24) + (cmd[4]<<16) + (cmd[5]<<8) +cmd[6];
									hdr[0] = poLog->log(C_READX, pAll->psLog, nLinkIdx); 
									nLen = sizeof(LOG_REC);
									data =  gcnew cli::array<Byte>(nLen);
									pcT = (uchar *)pAll->psLog;
									for(i=0; i<nLen; i++)
										data[i] = pcT[i];
									break;

								case C_OPENX:   
									hdr[0] = poLog->log(C_OPENX, nullptr, 0); 
									break;

								case C_CLOSEX:   
									hdr[0] = poLog->log(C_CLOSEX, nullptr, 0); 
									break;*/
								}
								break;

							case CL_ABORT4:
								hdr[0] = 1;
								pAll->nKey = (cmd[1]<<8) + cmd[2];
								pAll->nLinkIdx = (cmd[3] << 24) + (cmd[4]<<16) + (cmd[5]<<8) +cmd[6];
								break;

							case CL_KEY:
								hdr[0] = 1;
								pAll->nKey = (cmd[1]<<8) + cmd[2];
								pAll->nLinkIdx = (cmd[3] << 24) + (cmd[4]<<16) + (cmd[5]<<8) +cmd[6];
								break;

							case CL_MAN:
								hdr[0] = 1;
								pAll->nManKey = (cmd[1]<<8) + cmd[2];
								break;

								//-----------------------------------------------------	
							//case CL_FLOW:
							//	hdr[0] = 1;
							//	psOps->nRate = (cmd[3] << 24) + (cmd[4]<<16) + (cmd[5]<<8) +cmd[6];
							//	break;

							//	//-----------------------------------------------------	
							//case CL_CLIMIT:
							//	hdr[0] = 1;
							//	psOps->nClimit = (cmd[3] << 24) + (cmd[4]<<16) + (cmd[5]<<8) +cmd[6];
							//	break;

							//-----------------------------------------------------------------------------
							/*case CL_CBC:
								stFile = gcnew String("\\Keystone Batch\\Cbc.exe");
								if ( File::Exists(stFile))
								{
									FileStream^ fs = gcnew FileStream(stFile, FileMode::Open, FileAccess::Read);
									data =  gcnew cli::array<Byte>((int)fs->Length);
									nLen = (int)fs->Length;
									fs->Read(data, 0 , (int)fs->Length);
									fs->Close();
								}
								break;*/
								
								/*-----------------------------------------------------------------------------
								case CL_FILE:
								stFile = gcnew String(pAll->pcLog);
								if ( File::Exists(stFile))
								{
								FileStream^ fs = gcnew FileStream(stFile, FileMode::Open );
								data =  gcnew cli::array<Byte>((int)fs->Length);
								fs->Read(data, 0 , (int)fs->Length);
								fs->Close();
								}
								break;
								*/
								//-----------------------------------------------------
							/*case CL_SJOB4:
								nLen = sizeof(LOG_REC);
								pcT = (uchar *)pAll->pJob4;
								for(i=0; i<nLen; i++)
									pcT[i] = data[i];
								hdr[0] = 1;
								break;*/
							case CL_SJOB4:
								hdr[0] = 1;
								ms = gcnew MemoryStream(nLen2);
								try
								{
									//nLen = nData - sizeof(LOG_REC);
									ms->Write(data, 0, nLen2);
									ms->Seek(0, SeekOrigin::Begin);
									pAll->pJob4 = (Job^)(formatter->Deserialize( ms ));

									//pJob->psLog = poBufs->nextBuf();
									//LOG_REC *psLog = pJob->psLog;
									////
									//pJob->psLog2 = poBufs->nextBuf();
									//poLog->log(C_READ, pJob->psLog2, pJob->nIndex);
									//
									/*pcT = (uchar *)pAll->pJob4;
									for(i=0; i<nLen; i++)
										pcT[i] = data[nLen + i];*/

									//if(pJob->bUserTic)			// not appended yet
									//{
									//	if(pJob->nState == J_WASH)
									//		++psOps->nWashTic;
									//	else
									//		++psOps->nUserTicket;
									//	pAll->lJobs->Insert(0, pJob);
									//	psOps->bChange = !psOps->bChange;
									//}
									//else
										/*for(i=0; i<pAll->lJob->Count; i++)
										{
											if(pJob->nTicket == pAll->lJob[i]->nTicket)
											{
												pAll->lJob[i] = pJob;
												break;
											}
										}
										pAll->lJobsRdy->Add(pJob);*/
									nLen2 = 0;
								}
								catch ( SerializationException^ ex ) 
								{
									pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
									hdr[0] = 0;
								}
								finally
							   {
								   ms->Close();
							   }
								nLen = 0;
								break;

							case CL_SJOB:
								hdr[0] = 1;
								ms = gcnew MemoryStream(nLen2);
								try
								{
									ms->Write(data, 0, nLen2);
									ms->Seek(0, SeekOrigin::Begin);
									pAll->pJob = (Job^)(formatter->Deserialize( ms ));
									nLen2 = 0;
								}
								catch ( SerializationException^ ex ) 
								{
									pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
									hdr[0] = 0;
								}
								finally
							   {
								   ms->Close();
							   }
								nLen = 0;
								break;

							//case CL_STRUCK:
							//	//----------------------------------------------------- 
							//	ms = gcnew MemoryStream(nData);
							//	try
							//	{
							//		ms->Write(data, 0, nData);
							//		ms->Seek(0, SeekOrigin::Begin);
							//		pAll->lTrkn = (List<Trkn^>^)(formatter->Deserialize( ms ));
							//		hdr[0] = 1;

							//		fs = gcnew FileStream( pAll->stTrkn, FileMode::Create );
							//		try
							//		{
							//			formatter->Serialize( fs, pAll->lTrkn );
							//		}
							//		catch ( SerializationException^ ex ) 
							//		{
							//			pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//			throw;
							//		}
							//		finally
							//		{
							//			fs->Close();
							//		}
							//	}
							//	catch ( SerializationException^ ex ) 
							//	{
							//		pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//		hdr[0] = 0;
							//	}
							//	finally
					  // {
						 //  ms->Close();
					  // }
							//	break;

							//case CL_SMIX:
							//	ms = gcnew MemoryStream(nData);
							//	try
							//	{
							//		ms->Write(data, 0, nData);
							//		ms->Seek(0, SeekOrigin::Begin);
							//		pAll->lMix = (List<Mixx^>^)(formatter->Deserialize( ms ));
							//		hdr[0] = 1;

							//		//-------------------------------------------------
							//		fs = gcnew FileStream( pAll->stMix, FileMode::Create );
							//		try
							//		{
							//			formatter->Serialize( fs, pAll->lMix );
							//		}
							//		catch ( SerializationException^ ex ) 
							//		{
							//			pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//			throw;
							//		}
							//		finally
							//		{
							//			fs->Close();
							//		}
							//	}
							//	catch ( SerializationException^ ex ) 
							//	{
							//		pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//		hdr[0] = 0;
							//	}
							//	finally
							//   {
							//	   ms->Close();
							//   }
							//	break;

							//case CL_SJOBX:
							//	ms = gcnew MemoryStream(nData);
							//	try
							//	{
							//		ms->Write(data, 0, nData);
							//		ms->Seek(0, SeekOrigin::Begin);
							//		pAll->lJobx = (List<Jobx^>^)(formatter->Deserialize( ms ));
							//		hdr[0] = 1;

							//		//-------------------------------------------------
							//		fs = gcnew FileStream( pAll->stJobx, FileMode::Create );
							//		try
							//		{
							//			formatter->Serialize( fs, pAll->lJobx );
							//		}
							//		catch ( SerializationException^ ex ) 
							//		{
							//			pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//			throw;
							//		}
							//		finally
							//		{
							//			fs->Close();
							//		}
							//	}
							//	catch ( SerializationException^ ex ) 
							//	{
							//		pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//		hdr[0] = 0;
							//	}
							//	finally
							//   {
							//	   ms->Close();
							//   }
							//	break;

								//-----------------------------------------------------
							//case CL_SARMED:
							//	hdr[0] = 1;
							//	ms = gcnew MemoryStream(nData - sizeof(LOG_REC));
							//	try
							//	{
							//		nLen = nData - sizeof(LOG_REC);
							//		ms->Write(data, 0, nLen);
							//		ms->Seek(0, SeekOrigin::Begin);
							//		pJob = (Job^)(formatter->Deserialize( ms ));

							//		pJob->psLog = poBufs->nextBuf();
							//		LOG_REC *psLog = pJob->psLog;
							//		//
							//		pJob->psLog2 = poBufs->nextBuf();
							//		poLog->log(C_READ, pJob->psLog2, pJob->nIndex);
							//		//
							//		pcT = (uchar *)psLog;
							//		for(i=0; i<sizeof(LOG_REC); i++)
							//			pcT[i] = data[nLen + i];

							//		pAll->pJob = pJob;
							//	}
							//	catch ( SerializationException^ ex ) 
							//	{
							//		pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//		hdr[0] = 0;
							//	}
							//	finally
							//   {
							//	   ms->Close();
							//   }
							//	nLen = 0;
							//	break;

							//case CL_SADP:
							//	nLen = ADP_LEN;
							//	pcT = (uchar *)pAll->psAdp;
							//	for(i=0; i<nLen; i++)
							//		pcT[i] = data[i];
							//	hdr[0] = 1;
							//	break;

							//case CL_SHAUL:
							//	ms = gcnew MemoryStream(nData);
							//	try
							//	{
							//		ms->Write(data, 0, nData);
							//		ms->Seek(0, SeekOrigin::Begin);
							//		pAll->lHaul = (List<Haul^>^)(formatter->Deserialize( ms ));
							//		hdr[0] = 1;

							//		//-------------------------------------------------
							//		fs = gcnew FileStream( pAll->stHaul, FileMode::Create );
							//		try
							//		{
							//			formatter->Serialize( fs, pAll->lHaul );
							//		}
							//		catch ( SerializationException^ ex ) 
							//		{
							//			pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//			throw;
							//		}
							//		finally
							//		{
							//			fs->Close();
							//		}
							//	}
							//	catch ( SerializationException^ ex ) 
							//	{
							//		pAll->stExc += "\nCSERV Serialization Exception: " + ex->Message;
							//		hdr[0] = 0;
							//	}
							//	finally
					  // {
						 //  ms->Close();
					  // }
							//	break;

								//--------------------------------------------------------
							default:
								MessageBox::Show("received cmd "+cmd[0].ToString(), "CLINK SERVER ERROR", 
									MessageBoxButtons::OK, MessageBoxIcon::Error);
								break;
						}

respond:				cSum = 0;
						if(nLen > 0)
						{
							for(i=0; i<nLen; i++)
								cSum += data[i];
						}
						hdr[1] = (nLen >> 16) & 0xff;
						hdr[2] = (nLen >>  8) & 0xff;
						hdr[3] =  nLen        & 0xff;
						hdr[4] = cSum;										// data checksum
						hdr[5] = hdr[0]+hdr[1]+hdr[2]+hdr[3]+hdr[4];		// header checsum
						client->Send( hdr );

						if(nLen > 0)
							client->Send( data );
					}	// while bRun

				}
				//-----------------------------------------------------------------
				catch ( Exception^ ex ) 
				{
					pAll->pExc += "\nCSERV: Exception: " + ex->Message;
				}

				// Shutdown and end connection
				if(client) client->Close();
				server->Stop();

				// logoff remote
				//pAll->cRemote = C_NONE;

				pAll->nCservOk = 0;					// red
				Thread::Sleep(1000);
			}
		}
	};
}
