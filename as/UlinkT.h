#pragma once
#include "StdAfx.h"
#include "ticket.h"

using namespace System;
using namespace System::Threading;

namespace As
{
#define NUL 0x00
#define SOH 0x01
#define STX 0x02 
#define ETX 0x03
#define EOT 0x04
#define ENQ 0x05
#define ACK 0x06
#define BEL 0x07
#define BS  0x08
#define HT  0x09
#define LF  0x0A
#define VT  0x0B
#define FF  0x0C
#define CR  0x0D
#define SO  0x0E
#define SI  0x0F
#define DLE 0x10
#define DC1 0x11
#define DC2 0x12
#define DC3 0x13
#define DC4 0x14
#define NAK 0x15
#define SYN 0x16
#define ETB 0x17
#define CAN 0x18
#define EM  0x19
#define SUB 0x1A
#define ESC 0x1B
#define FS  0x1C
#define GS  0x1D
#define RS  0x1E
#define US  0x1F
#define SP  0x20

// THREAD class receiving ULINK tickets  ======================================
ref class CUlink
{
public:
	CUlink(All^ pAllIn)
	{
		pAll = pAllIn;
		psIni = pAll->psIni;		//DC 3.2.3
		poLog = gcnew CLog(pAll);
	}
private: 
	static	All^ pAll;
	static  INI *psIni;		//DC 3.2.3
	static CLog^ poLog;

		//-------------------------------------------------------------------------
static void findAddTruck(All^ pAll, LOG_REC *psLog)
		 {
			 Truck^	pTruck;
			 String^ stId = gcnew String(psLog->sT.truck_id);

			 for(int nIdx=0; nIdx<pAll->lTruck->Count; nIdx++)
			 {
				 pTruck = pAll->lTruck[nIdx];

				 if(pTruck->stName->Equals(stId))
				 {
					return;
				 }
			 }

			 // add truck--------------------------------------------------
			 pTruck = gcnew Truck();
			 pTruck->stName = gcnew String(psLog->sT.truck_id);
			 pTruck->nRate = 200;
			 if(psIni->bUseTrkMax)
				 pTruck->nCapacity = (int)psLog->sT.load_size;	//DC 3.2.3
			 else
				pTruck->nCapacity = 26;
			 pAll->lTruck->Add(pTruck);

			// save new truck
			FileStream^ fs = gcnew FileStream(pAll->pAcPath + gcnew String("as.truck"), FileMode::Create );

			 // Construct a BinaryFormatter and use it to serialize the data to the stream.
			 BinaryFormatter^ formatter = gcnew BinaryFormatter;
			 try
			 {
				 formatter->Serialize( fs, pAll->lTruck );
			 }
			 catch ( SerializationException^ e ) 
			 {
				 Console::WriteLine( "Failed to serialize. Reason: {0}", e->Message );
				 throw;
			 }
			 finally
			 {
				 fs->Close();
			 }
			 return;
		 }

	 //-------------------------------------------------------------------------
	 // reads unprocessed tickets from log file and enqueues Jobs
	 //		to respective plant queue.
	 // starts TCP server. 
	 //	loop:
	 //   receives ULINK message:
	 //		WAKE 
	 //			responds with ACK
	 //		IDLE 
	 //			no response
	 //		TICKET 
	 //			passes messages to Ticket class for processing
	 //			enqueues ticket to respective plant queue.
	 //			responds with T017 status
	 //		TIME
	 //			responds with W017 status
	 //		OTHERS 
	 //			ignore
	 //  endloop;
	 //-------------------------------------------------------------------------
public:
	static void ThreadProc(Object^ pAllIn)
	{
		All^ pAll = (All^) pAllIn;
		INI *psIni = pAll->psIni;
		 bool	bAwake;
		 LOG_REC sLog;
		 Job^	pJob;
		 DateTime^ pDate; 
		 CTicket oTicket;
		 TcpListener^ server;
		 Socket^ client = nullptr;
		 Int32 len;
//		 char cId0, cId1, cId2;
		 TICKET_STATUS eStatus;
		 // Buffers for ulink messages.
		 cli::array<Byte>^data = gcnew cli::array<Byte>(2500);

		 // Buffer for short response to ulink.
		 cli::array<Byte>^respS = gcnew cli::array<Byte>(5);
		 respS[0] = SYN;
		 respS[1] = ACK;
		 respS[2] = 'A';				// status code
		 respS[3] = EOT;
		 respS[4] = CR;

		 // Buffer for long response to ulink.
		 cli::array<Byte>^respL = gcnew cli::array<Byte>(12);
		 respL[0] = SYN;
		 respL[1] = SYN;
		 respL[2] = STX;
		 respL[3] = 'T';				
		 respL[4] = '0';			
		 respL[5] = '1';				
		 respL[6] = '7';				
		 respL[7] = 'A';				// status code
		 respL[8] = CR;
		 respL[9] = ETX;				
		 respL[10] = EOT;
		 respL[11] = CR;

		// Buffer for TIME OK response to ulink.
		cli::array<Byte>^respTime = gcnew cli::array<Byte>(12);
		respTime[0] = SYN;
		respTime[1] = SYN;
		respTime[2] = STX;
		respTime[3] = 'W';				
		respTime[4] = '0';			
		respTime[5] = '1';				
		respTime[6] = '7';				
		respTime[7] = 'A';				// status code
		respTime[8] = CR;
		respTime[9] = ETX;				
		respTime[10] = EOT;
		respTime[11] = CR;

		 // Create a Tcpserver.
		 server = gcnew TcpListener(IPAddress::Any, psIni->nUlinkPort);

		 //---------------------------------------------------------
		while(true)
		{	
			 try
			 {
				 // Start listening for client requests.
				 server->Start();

				 //---------------------------------------------------------
				 while(true)
				 {
					 // Perform a blocking call to accept requests.
					 // You could also user server.AcceptSocket() here.
					 psIni->nUlinkOk = 2;
					 client = server->AcceptSocket();

					 // Loop to receive all the data sent by the client.
					 while ( len = client->Receive(data, data->Length, static_cast<SocketFlags>(0)  ) )
					 {
						 if(data[0] == SYN && data[1] == SYN)
						 {
							 switch(data[2])
							 {
							 case ENQ:
								 bAwake = true;
								 psIni->nUlinkOk = 1;
//								 cId0 = data[3];
//								 cId1 = data[4];
//								 cId2 = data[5];
								 client->Send( respS );
								 break;

							 case ESC:
								 bAwake = false;
								 psIni->nUlinkOk = 2;
								 break;
/*
							case ACK:
								if(bResult)
								{
									bResult = false;
									respOk[7] = 'A';
									client->Send( respOk );
								}
								break;
*/
							case STX:
								 if(bAwake)
								 {
									 memset(&sLog, 0, sizeof(LOG_REC));
									 eStatus = oTicket.processTicket(data, len, &sLog, psIni);	// status code

									 //--------------------------------------------------
									 switch(eStatus)
									 {
									 case T_TIME:
										client->Send( respTime );
										break;

									 case T_TICKET:
										 sLog.eJobStatus = S_NEW;
										 
										 findAddTruck(pAll, &sLog);
										 pDate = DateTime::Now;
										 sLog.tTimeSent = pDate->ToBinary();
										 
										 //------------------------------------------
										 pJob = gcnew Job();
										 pJob->tTime = sLog.tTimeSent;
										 //DC 4.0.3
										 for(int i=0; i < 12; i++)
										 {
										    if(sLog.nSilo == psIni->asSilos[i].nSiloNum)
											{
												pJob->nSilo = i+1;
												sLog.nSilo = i+1;
												break;
											}
										 }
										 if(pJob->nSilo == 0)
										 {
											pJob->nSilo = 1;
											sLog.nSilo = 1;
										 }

										 pJob->nLogIdx = poLog->log(C_APPEND, &sLog, 0);
										 pJob->nPlant = sLog.sT.plant_num;
										 pJob->nTicket = sLog.sT.ticket_num;
										 pJob->stCustomer = gcnew String(sLog.sT.customer_name_1);
										 pJob->fLoad = sLog.sT.load_size;
										 pJob->eStatus = sLog.eJobStatus;
										 pJob->stMaterial = gcnew String(sLog.sT.mix_code);		//DC 4.0.3
										 pJob->stTruck = gcnew String(sLog.sT.truck_id);		//DC 4.0.3
										 pJob->nCopy = sLog.nCopy;								//DC 4.0.3
										 pJob->stLane = gcnew String(sLog.sT.user_defined_46);	//DC 4.1.2
										 pJob->stSilo = gcnew String(sLog.sT.user_defined_47);	//DC 4.1.2

										 pAll->lJob->Add(pJob);

										 if(psIni->bBotScale)
										 {
											 switch(sLog.nSilo)
											 {
											 case 1:
											 case 2:  
											 case 3:  pAll->nTickets1++; break;
											 case 4:  
											 case 5:  
											 case 6:  pAll->nTickets2++; break;
											 case 7:  
											 case 8:  
											 case 9:  pAll->nTickets3++; break;
											 case 10:  
											 case 11:  
											 case 12:  psIni->nTickets4++; break;
											 default:  pAll->nTickets1++; break;
											 }	
										 }
										 else
										 {
											 switch(sLog.nSilo)
											 {
											 case 1:  pAll->nTickets1++; break;
											 case 2:  pAll->nTickets2++; break;
											 case 3:  pAll->nTickets3++; break;
											 case 4:  pJob->nSilo = 1; pAll->nTickets1++; break;
											 case 5:  pJob->nSilo = 2; pAll->nTickets2++; break;
											 case 6:  pJob->nSilo = 3; pAll->nTickets3++; break;
											 case 7:  pJob->nSilo = 1; pAll->nTickets1++; break;
											 case 8:  pJob->nSilo = 2; pAll->nTickets2++; break;
											 case 9:  pJob->nSilo = 3; pAll->nTickets3++; break;
											 case 10:  pJob->nSilo = 1; pAll->nTickets1++; break;
											 case 11:  pJob->nSilo = 2; pAll->nTickets2++; break;
											 case 12:  pJob->nSilo = 3; pAll->nTickets3++; break;
											 default:  pJob->nSilo = 1; pAll->nTickets1++; break;
											 }	
										 }
										 respL[7] = 'A';
										 client->Send( respL );

										 if(pAll->bUlink)
											 pAll->pTestBox = System::Text::Encoding::ASCII->GetString(data);

									 break;

									 case T_VOID:
										 respL[7] = 'B';

										for(int i=0; i < pAll->lJob->Count; i++)
										{
											Job^pJob = pAll->lJob[i];

											// transfer job from NEW to OLD list
											if(pJob->nTicket == sLog.sT.ticket_num)
											{
												poLog->log(C_READ, &sLog, pJob->nLogIdx);
												sLog.eJobStatus = S_VOIDED;
												pJob->eStatus = sLog.eJobStatus;
												//4.0.3
												for(int i=0; i < 12; i++)
												{
													if(sLog.nSilo == psIni->asSilos[i].nSiloNum)
													{
														pJob->nSilo = i+1;
														sLog.nSilo = i+1;
														break;
													}
												}
												if(pJob->nSilo == 0)
												{
													pJob->nSilo = sLog.nSilo;
												}
												poLog->log(C_UPDATE, &sLog, pJob->nLogIdx);

												pAll->lJob->Remove(pJob);
												pJob->stStatus = pAll->lStat[pJob->eStatus];
												pAll->lOld->Add(pJob);
												respL[7] = 'A';

												if(psIni->bBotScale)
												 {
													 switch(sLog.nSilo)
													 {
													 case 1:
													 case 2:  
													 case 3:  pAll->nTickets1--; pAll->nDone1++; break;
													 case 4:  
													 case 5:  
													 case 6:  pAll->nTickets2--; pAll->nDone2++; break;
													 case 7:  
													 case 8:  
													 case 9:  pAll->nTickets3--; pAll->nDone3++; break;
													 case 10:  
													 case 11:  
													 case 12:  psIni->nTickets4--; psIni->nOldDone4++; break;
													 default:  pAll->nTickets1--; pAll->nDone1++; break;
													 }	
												 }
												 else
												 {
													 switch(sLog.nSilo)
													 {
													 case 1:  pAll->nTickets1--; pAll->nDone1++; break;
													 case 2:  pAll->nTickets2--; pAll->nDone2++; break;
													 case 3:  pAll->nTickets3--; pAll->nDone3++; break;
													 case 4:  pAll->nTickets1--; pAll->nDone1++; break;
													 case 5:  pAll->nTickets2--; pAll->nDone2++; break;
													 case 6:  pAll->nTickets3--; pAll->nDone3++; break;
													 case 7:  pAll->nTickets1--; pAll->nDone1++; break;
													 case 8:  pAll->nTickets2--; pAll->nDone2++; break;
													 case 9:  pAll->nTickets3--; pAll->nDone3++; break;
													 case 10:  pAll->nTickets1--; pAll->nDone1++; break;
													 case 11:  pAll->nTickets2--; pAll->nDone2++; break;
													 case 12:  pAll->nTickets3--; pAll->nDone3++; break;
													 default: pAll->nTickets1--; pAll->nDone1++; break;
													 }	
												 }
												break;
											}
										}
										
										 client->Send( respL );
										 if(pAll->bUlink)
											 pAll->pTestBox = System::Text::Encoding::ASCII->GetString(data);
//											 pAll->pTestBox += (respL[7] == 'A') ? "Ticket voided\n" : "Ticket NOT voided\n";
										 
									 break;

									 default:
										 sLog.eJobStatus = S_NONE;
										 respL[7] = 'B';
										 client->Send( respL );
										 if(pAll->bUlink)
											 pAll->pTestBox += "Ticket ignored, wrong plant number: "+ sLog.sT.plant_num.ToString()+"\n";
									 break;
									 }
								 }
								 break;

							 default:
								 // ignore
								 break;
							 }
						 }
					 }
					 // Shutdown and end connection
					 if(client)client->Close();
					 psIni->nUlinkOk = 2;
				 }
			 }
			 //----------------------------------------------------------------
			 catch ( NullReferenceException^ ex ) 
			 {
				  pAll->pExc += "\nULINK NULL Exception: " + ex->Message;
			 }
			 catch ( SocketException^ ex ) 
			 {
				  pAll->pExc += "\nULINK SOCKET Exception: " + ex->Message;
			 }
			 catch ( IO::IOException^ ex ) 
			 {
				  pAll->pExc += "\nULINK IO Exception: " + ex->Message;
			 }
			 // Shutdown and end connection
			 if(client)client->Close();
			 server->Stop();
			 psIni->nUlinkOk = 0;
			 Thread::Sleep(1000);
		}
	}


};
}