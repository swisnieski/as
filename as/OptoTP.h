#pragma once
#include "StdAfx.h"
#include <limits.h>
#include <iostream>
#include <math.h>
#include <bitset>

using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Runtime::Serialization;

namespace As
{
#define PUC_ADDR 0xf0380000
#define DOG_ADDR 0xf0380010

#define CFG_ADDR 0xf0100004
#define DOG_ENA  0xf0100028

#define BLK_ADDR  0xf0500000
#define READ_ADDR 0xf1808004
#define READ_4_1  0xf0800f00
#define READ_4_2  0xf0800f40
#define READ_4_3  0xf0800f80
#define READ_4_4  0xf0800fc0
#define	ANA_ADDR  0xf01d4000		//DC 4.0.0 Analog Point R/W set Min/Max
#define ANAW_ADDR 0xf02a0000		//DC 4.0.0 Analog Point Write
//#define MOD_11	  0xf18082c4
//#define MOD_15	  0xf18083c4

// Transaction code used by the I/O unit
#define WRITE_QUAD_REQUEST   0
#define WRITE_BLOCK_REQUEST  1
#define WRITE_RESPONSE       2
#define READ_QUAD_REQUEST    4
#define READ_BLOCK_REQUEST   5
#define READ_QUAD_RESPONSE   6
#define READ_BLOCK_RESPONSE  7


	// THREAD class for OPTO TCPIP communication =================================
	// TCPIP client in remote node talks to server in local node
	//=============================================================================
	ref class COptoTP
	{
	private: 
		COptoTP(void)
		{
		}
		//---------------------------------------------------------------------
	private: 
		static bool readQ(NetworkStream^ stream, ulong64 nOffs, ulong *pnInp)
		{
			cli::array<Byte>^ cmd = gcnew cli::array<Byte>(12);
			cli::array<Byte>^ resp = gcnew cli::array<Byte>(16);
			bool bOk;

			cmd[0]  = 0x00;
			cmd[1]  = 0x00;
			cmd[2]  = 0; //byTransactionLabel << 2;
			cmd[3]  = READ_QUAD_REQUEST << 4;
			cmd[4]  = 0x00;
			cmd[5]  = 0x00;
			cmd[6]  = 0xFF;
			cmd[7]  = 0xFF;
			cmd[8]  = (uchar)((nOffs >> 24) & 0xff);
			cmd[9]  = (uchar)((nOffs >> 16) & 0xff);
			cmd[10] = (uchar)((nOffs >>  8) & 0xff);
			cmd[11] = (uchar)((nOffs >>  0) & 0xff);
			stream->Write( cmd, 0, 12);

			bOk = stream->Read( resp, 0, 16) == 16;

			*pnInp = (resp[12] << 24) + (resp[13] << 16) + (resp[14] << 8) + resp[15];
			return bOk;
		}
		//---------------------------------------------------------------------
	private: 
		static ulong writeQ(NetworkStream^ stream, ulong nOffs, ulong nCmd)
		{
			cli::array<Byte>^ cmd = gcnew cli::array<Byte>(16);
			cli::array<Byte>^ resp = gcnew cli::array<Byte>(12);
			ulong nResp = 0;

			cmd[0]  = 0x00;
			cmd[1]  = 0x00;
			cmd[2]  = 4; //byTransactionLabel << 2;
			cmd[3]  = WRITE_QUAD_REQUEST << 4;
			cmd[4]  = 0;
			cmd[5]  = 0;
			cmd[6]  = 0xFF;
			cmd[7]  = 0xFF;
			cmd[8]  = (uchar) ((nOffs >> 24) & 0xff);
			cmd[9]  = (uchar) ((nOffs >> 16) & 0xff);
			cmd[10] = (uchar) ((nOffs >>  8) & 0xff);
			cmd[11] = (uchar) ((nOffs >>  0) & 0xff);
			cmd[12] = (uchar) ((nCmd >> 24) & 0xff);
			cmd[13] = (uchar) ((nCmd >> 16) & 0xff);
			cmd[14] = (uchar) ((nCmd >>  8) & 0xff);
			cmd[15] = (uchar) ((nCmd >>  0) & 0xff);
			stream->Write( cmd, 0, 16);

			stream->Read( resp, 0, 12);	// wrong header size

			nResp = resp[6] >> 4;
			return nResp;
		}

		//DC 4.0.0---------------------------------------------------------------------
	private: 
		static ulong writeQW(NetworkStream^ stream, ulong nOffs, ulong nCmd)
		{
			cli::array<Byte>^ cmd = gcnew cli::array<Byte>(16);
			cli::array<Byte>^ resp = gcnew cli::array<Byte>(12);
			ulong nResp = 0;

			cmd[0]  = 0x00;
			cmd[1]  = 0x00;
			cmd[2]  = 4; //byTransactionLabel << 2;
			cmd[3]  = WRITE_QUAD_REQUEST << 4;
			cmd[4]  = 0;
			cmd[5]  = 0;
			cmd[6]  = 0xFF;
			cmd[7]  = 0xFF;
			cmd[8]  = (uchar) ((nOffs >> 24) & 0xff);
			cmd[9]  = (uchar) ((nOffs >> 16) & 0xff);
			cmd[10] = (uchar) ((nOffs >>  8) & 0xff);
			cmd[11] = (uchar) ((nOffs >>  0) & 0xff);
			cmd[12] = (uchar) ((nCmd >> 24) & 0xff);
			cmd[13] = (uchar) ((nCmd >> 16) & 0xff);
			cmd[14] = (uchar) ((nCmd >>  8) & 0xff);
			cmd[15] = (uchar) ((nCmd >>  0) & 0xff);
			stream->Write( cmd, 0, 16);

			stream->Read( resp, 0, 12);	// wrong header size

			nResp = resp[6] >> 4;
			return nResp;
		}


		//---------------------------------------------------------------------
	private: 
		static ulong writeB(NetworkStream^ stream, ulong64 nData)
		{
			cli::array<Byte>^ cmd = gcnew cli::array<Byte>(32);
			cli::array<Byte>^ resp = gcnew cli::array<Byte>(12);
			ulong nResp = 0;

			cmd[0]  = 0x00;
			cmd[1]  = 0x00;
			cmd[2]  = 4; //byTransactionLabel << 2;
			cmd[3]  = WRITE_BLOCK_REQUEST << 4;
			cmd[4]  = 0;
			cmd[5]  = 0;
			cmd[6]  = 0xFF;
			cmd[7]  = 0xFF;
			cmd[8]  = 0xf0;
			cmd[9]  = 0x50;
			cmd[10] = 0;
			cmd[11] = 0;

			cmd[12] = 1;
			cmd[13] = 0;
			cmd[14] = 0;
			cmd[15] = 0;

			cmd[16] = (uchar) ((nData >> 56) & 0xff);
			cmd[17] = (uchar) ((nData >> 48) & 0xff);
			cmd[18] = (uchar) ((nData >> 40) & 0xff);
			cmd[19] = (uchar) ((nData >> 32) & 0xff);

			cmd[20] = (uchar) ((nData >> 24) & 0xff);
			cmd[21] = (uchar) ((nData >> 16) & 0xff);
			cmd[22] = (uchar) ((nData >>  8) & 0xff);
			cmd[23] = (uchar) ((nData >>  0) & 0xff);

			cmd[24] = ~cmd[16];
			cmd[25] = ~cmd[17];
			cmd[26] = ~cmd[18];
			cmd[27] = ~cmd[19];
			cmd[28] = ~cmd[20];
			cmd[29] = ~cmd[21];
			cmd[30] = ~cmd[22];
			cmd[31] = ~cmd[23];

			stream->Write( cmd, 0, 32);
			stream->Read( resp, 0, 12);	// wrong header size

			nResp = (resp[6] >> 4);
			return nResp;
		}

		//---------------------------------------------------------------------
	private: 
		static bool readB(NetworkStream^ stream, ulong64 nOffs, ulong *pnInp)
		{
			cli::array<Byte>^ cmd = gcnew cli::array<Byte>(16);
			cli::array<Byte>^ resp = gcnew cli::array<Byte>(20);
			int nLen;

			cmd[0]  = 0x00;
			cmd[1]  = 0x00;
			cmd[2]  = 0; //byTransactionLabel << 2;
			cmd[3]  = READ_BLOCK_REQUEST << 4;
			cmd[4]  = 0x00;
			cmd[5]  = 0x00;
			cmd[6]  = 0xFF;
			cmd[7]  = 0xFF;
			cmd[8]  = (uchar)((nOffs >> 24) & 0xff);
			cmd[9]  = (uchar)((nOffs >> 16) & 0xff);
			cmd[10] = (uchar)((nOffs >>  8) & 0xff);
			cmd[11] = (uchar)((nOffs >>  0) & 0xff);
			cmd[12]  = 0x00;
			cmd[13]  = 0x10;
			cmd[14]  = 0x00;
			cmd[15]  = 0x00;
			stream->Write( cmd, 0, 16);

			nLen = stream->Read( resp, 0, 20);

			*pnInp = (resp[16] << 24) + (resp[17] << 16) + (resp[18] << 8) + resp[19];
			return nLen == 20;
		}
		//DC 4.0.0 ---------------------------------------------------------------
	private:
		// Get 32-bit IEEE 754 format of the decimal value
		static std::string GetBinary32( float value )
		{
			union
			{
				 float input;   // assumes sizeof(float) == sizeof(int)
				 int   output;
			}    data;
		 
			data.input = value;
		 
			std::bitset<sizeof(float) * CHAR_BIT>   bits(data.output);
		 
			std::string mystring = bits.to_string<char, 
												  std::char_traits<char>,
												  std::allocator<char> >();
		 
			return mystring;
		}
	private:
		// Convert the 32-bit binary encoding into hexadecimal
		static int Binary2Hex( std::string Binary )
		{
			std::bitset<32> set(Binary);      
			int hex = set.to_ulong();
		     
			return hex;
		}
		//-------------------------------------------------------------------------
	public:
		static void ThreadProc(Object^ pAllIn)
		{
			All^ pAll = (All^)pAllIn;
			INI *psIni = pAll->psIni;
			clock_t tOld = clock(), tNew;
			int			nResp;
//DC 4.0.0			psIni->cOptoSlot = psIni->cOptoInputs - psIni->cOptoAnalog;
			ulong64	nData;
			ulong	nData1;
			ulong	nData2;
			ulong	nData3;
			ulong	nData4;
			ulong	nData5;
			ulong	nAddr;
			ulong	nAddr1;
			ulong	nInpAddr = READ_ADDR + psIni->cOptoSlot * 0x40;	//DC 4.0.0 psIni->cOptoInputs * 0x40;
			ulong   nAnaAddr = ANA_ADDR; //+ psIni->cOptoAnalog * 0x300;	//DC
			ulong   nAnaWAddr = ANAW_ADDR + psIni->cOptoSlot * 0x1000;	//DC
			TcpClient^ client;
			NetworkStream^ stream; 
			bool bInOk;
			int  nMinTruckEU;	//DC 4.0.0 Min Truck Weight EU
			int  nMaxTruckEU;	//DC 4.0.0 Max Truck Weight EU
			int  nMinCartEU;	//DC 4.0.0 Max Rail cart Weight EU
			int  nMaxCartEU;	//DC 4.0.0 Max Rail cart Weight EU

			// IO points.
			ulong64  rtmps = 0;			//DC 4.0.0 int
			ulong64  wtmps = 0;			//DC 4.0.0 int
			//DC 4.0.0 convert to 32-bit IEEE 754 format hex
			std::string strMinTruck = GetBinary32((float) psIni->nTruckMin);
			std::string strMaxTruck = GetBinary32((float) psIni->nTruckMax);
			std::string strMinCart = GetBinary32((float) psIni->nCartMin);
			std::string strMaxCart = GetBinary32((float) psIni->nCartMax);
			nMinTruckEU = Binary2Hex(strMinTruck);
			nMaxTruckEU = Binary2Hex(strMaxTruck);
			nMinCartEU = Binary2Hex(strMinCart);
			nMaxCartEU = Binary2Hex(strMaxCart);

			//-----------------------------------------------------------------
			while(true)
			{	
				try
				{
					psIni->nOptoOk = 2;							// blue

					// Connect TcpClient.
					client = gcnew TcpClient();
					client->Connect(gcnew IPEndPoint(pAll->pIp, pAll->nPort));

					// Get a client stream for reading and writing.
					stream = client->GetStream();
					stream->Flush();

					// test PUC
					if(readQ(stream, PUC_ADDR, &nData1) && nData1 == 0)
						nResp = writeQ(stream, PUC_ADDR, 1);

					// set watchdog
					nResp = writeQ(stream, DOG_ADDR, 1000);

					// make 9,10,11 or 12 modules OUTPUT type
					nAddr = CFG_ADDR;
					for(int i=0; i < psIni->cOptoSlot ;i++)		//DC 4.0.0		15
					{
						nAddr1 = nAddr;
						for(int j=0; j<4;j++)
						{
							// digital output module
							nResp = writeQ(stream, nAddr1, 0x180); 
							// watchdog on
							nResp = writeQ(stream, nAddr1+0x24, 1); 
							nAddr1 += 0xc0;
						}
						nAddr += 0x3000;
					}

					//Set analogy output for snap-aoa-28
//					for(int i=psIni->cOptoSlot ; i < psIni->cOptoInputs ;i++)		//DC 4.0.0		15
					if(psIni->bSendTarget && !psIni->bSendBitWise)		//DC 4.0.0 set analog output
					{
						nAddr1 = nAddr;
					//	for(int j=0; j<2;j++)
						{
							// analogy output module 1 point 0
							nResp = writeQ(stream, nAddr1, 0x168);
							//// set high scale (EU)
							nResp = writeQ(stream, nAddr1+0x10, nMaxTruckEU);		//MAX_WEIGHT);
							////set low scale (EU)
							nResp = writeQ(stream, nAddr1+0x14, nMinTruckEU);			//MIN_WEIGHT);
							// watchdog on
							nResp = writeQ(stream, nAddr1+0x24, 1); 
							nAddr1 += 0xc0;
						}
						if(psIni->cOptoAnalog > 1)
						{
							// analogy output module 1 point 1
							nResp = writeQ(stream, nAddr1, 0x168);
							//// set high scale (EU)
							nResp = writeQ(stream, nAddr1+0x10, nMaxTruckEU);		//MAX_WEIGHT);
							////set low scale (EU)
							nResp = writeQ(stream, nAddr1+0x14, nMinTruckEU);			//MIN_WEIGHT);
							// watchdog on
							nResp = writeQ(stream, nAddr1+0x24, 1); 
//							nAddr1 += 0xc0;
							nAddr += 0x3000;

							// analogy output module 2 point 0
							nResp = writeQ(stream, nAddr1, 0x168);
							//// set high scale (EU)
							nResp = writeQ(stream, nAddr1+0x10, nMaxTruckEU);		//MAX_WEIGHT);
							////set low scale (EU)
							nResp = writeQ(stream, nAddr1+0x14, nMinTruckEU);			//MIN_WEIGHT);
							// watchdog on
							nResp = writeQ(stream, nAddr1+0x24, 1); 
							nAddr1 += 0xc0;

							// analogy output module 2 point 1
							nResp = writeQ(stream, nAddr1, 0x168);
							//// set high scale (EU)
							nResp = writeQ(stream, nAddr1+0x10, nMaxCartEU);		//MAX_WEIGHT);
							////set low scale (EU)
							nResp = writeQ(stream, nAddr1+0x14, nMinCartEU);			//MIN_WEIGHT);
							// watchdog on
							nResp = writeQ(stream, nAddr1+0x24, 1);

						}
						else
						{
							// analogy output module 1 point 1
							nResp = writeQ(stream, nAddr1, 0x168);
							//// set high scale (EU)
							nResp = writeQ(stream, nAddr1+0x10, nMaxCartEU);		//MAX_WEIGHT);
							////set low scale (EU)
							nResp = writeQ(stream, nAddr1+0x14, nMinCartEU);			//MIN_WEIGHT);
							// watchdog on
							nResp = writeQ(stream, nAddr1+0x24, 1); 
//							nAddr1 += 0xc0;
						}
//						nAddr += 0x3000;
					}

					//Set analogy output for snap-aoa-28 MAX and MIN
					//for(int i=0 ; i < psIni->cOptoAnalog ;i++)		//DC 4.0.0		15
					//{
					//	nAddr1 = nAnaAddr;
					//	for(int j=0; j<2;j++)
					//	{
					//		// set MIN value
					//		nResp = writeQ(stream, nAddr1, 21);	//MIN_WEIGHT);
					//		//set MAX value
					//		nResp = writeQ(stream, nAddr1+0x04, 35);	//MAX_WEIGHT);
					//		nAddr1 += 0x04;
					//	}
					//	nAnaAddr += 0x300;
					//}

					////Set analogy output for snap-aoa-28 value
					//int z=0;
					//for(int i=0 ; i < psIni->cOptoAnalog ;i++)		//DC 4.0.0		15
					//{
					//	z += 1;
					//	nAddr1 = nAnaWAddr;
					//	for(int j=0; j<2;j++)
					//	{
					//		// set output analogy value
					//		nResp = writeQ(stream, nAddr1, psIni->nSclOutEU[z+j]);
					//	}
					//	nAnaAddr += 0x1000;
					//}

					psIni->nOptoOk = 1;							// white
					pAll->pExc += "\nOPTO " + pAll->pIp->ToString() +":"+pAll->nPort.ToString();

					//---------------------------------------------------------
					while(true)
					{
						bInOk = readQ(stream, nInpAddr, &nData1);
						
						//DC 4.0.0
						switch(psIni->cOptoInputs)
						{
						case 16: 
							if(bInOk)
								psIni->nRpoints = nData1;
						break;

						case 20: 
							bInOk &= readQ(stream, READ_4_1, &nData2);	
							bInOk &= readQ(stream, READ_4_2, &nData3);	
							bInOk &= readQ(stream, READ_4_3, &nData4);	
							bInOk &= readQ(stream, READ_4_4, &nData5);

							if(bInOk)
							{
								nData2 &= 1;
								nData2 += (nData3 << 1) & 0x2;
								nData2 += (nData4 << 2) & 0x4;
								nData2 += (nData5 << 3) & 0x8;
								psIni->nRpoints = nData1 + (nData2 << 16);
							}
						break;

						case 32: 
							bInOk &= readQ(stream, nInpAddr+0x40, &nData2); 
							if(bInOk)
								psIni->nRpoints = nData1 + (nData2 << 16);
						break;

						case 48: 
							bInOk &= readQ(stream, nInpAddr+0x40, &nData2); 
							bInOk &= readQ(stream, nInpAddr+0x80, &nData3);		//DC 6.1.4
							if(bInOk)
							{
								nData = nData3;
								nData <<= 32;
								nData += nData1 + (nData2 << 16);
								psIni->nRpoints = nData;					// Read Point INPUT
							}
						break;

						case 64: 
							bInOk &= readQ(stream, nInpAddr+0x40,  &nData2); 
							bInOk &= readQ(stream, nInpAddr+0x80,  &nData3);	//DC 6.1.4
							bInOk &= readQ(stream, nInpAddr+0xC0,  &nData4);	//DC 6.1.4
							if(bInOk)
							{
								nData = nData3 + (nData4 << 16);
								nData <<= 32;
								nData += nData1 + (nData2 << 16);
								psIni->nRpoints = nData;
							}
						break;
						}

						if(bInOk)
						{
//DC 4.0.0							psIni->nRpoints = nData;

							// process data ///////////////////////////////////
//							oPlantR.tick();
//DC 4.0.0							if(wtmps != psIni->nWpoints)
//DC 4.0.0							{
//DC 4.0.0								wtmps = psIni->nWpoints;

								// set OUT points =================================
								nResp = writeB(stream, psIni->nWpoints); 
//DC 4.0.0							}

							//Set analogy output for snap-aoa-28 value
							if(psIni->bSendTarget && !psIni->bSendBitWise)		//DC 4.0.0 set analog output
							{
								int z=0;
								ulong   nAnaWAddr1 = ANAW_ADDR + psIni->cOptoSlot * 0x1000;	//DC
								for(int i=0 ; i < psIni->cOptoAnalog ;i++)		//DC 4.0.0		15
								{
									
									nAddr1 = nAnaWAddr1;
									for(int j=0; j<2;j++)
									{
										// set output analogy value
										//ulong nCmd = (psIni->nSclOutEU[z+j] << 20);
										std::string strTruckTarget = GetBinary32((float) psIni->nSclOutEU[z+j]);
										int nTruckTargetEU = Binary2Hex(strTruckTarget);
										nResp = writeQW(stream, nAddr1+0x40*j, nTruckTargetEU);
									}
									nAnaWAddr1 += 0x1000;
								}
								z += 1;
							}

						}
						tNew = clock(); 
//						psOps->nOptoDel = tNew - tOld;
						tOld = tNew;
//						psOps->nOptoDelMax = max(psOps->nOptoDel, psOps->nOptoDelMax);
						Thread::Sleep(100);
					}
				}
				//-------------------------------------------------------------
				catch ( Exception^ ex ) 
				{
					pAll->pExc += "\nOPTP Exception: " + ex->Message;
				}

				// Shutdown and end connection
				if(stream) stream->Close(0);
				if(client) client->Close();

				psIni->nOptoOk = 0;				// red
				Thread::Sleep(5000);
			}
		}
		///////////////////////////////////////////////////////////////////////
	};
}

