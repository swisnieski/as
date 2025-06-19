#pragma once
#include "StdAfx.h"


#ifdef  ASCII

using namespace System;
using namespace System::Threading;

const char hexb[17] = "0123456789ABCDEF";

namespace As
{
// THREAD class interfacing OPTO card==========================================
ref class COptoT
{
public:
	COptoT(void)
	{
	}

	//-------------------------------------------------------------------------
private:
	static System::Byte checkSum( cli::array<Byte>^cdata, int cnt) 
	{
		Byte cksum = 0;

		for( int i = 1; i < cnt; i++)
			cksum += cdata[i];
		return cksum;
	}

	//-------------------------------------------------------------------------
private: 
	static bool sendOpto( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		, int cmdLen
		, int respLen
		) 
	{
		int respCnt = 0;

		rdata[0] = ' ';
		rdata[1] = ' ';
		rdata[2] = ' ';
		rdata[3] = ' ';
		// send command
		// raise DTR, wait for reversal of line, read and lower DTR
		port->RtsEnable = true;
//		port->Parity = Parity::Mark;
//		port->Write(wdata, 0, 1);				 
//		port->Parity = Parity::Space;
		port->Write(wdata, 0, cmdLen);				 

		while(port->BytesToWrite > 0)
			;
		port->RtsEnable = false;
		Thread::Sleep(40);

		respCnt = port->Read(rdata, 0, port->BytesToRead);
		return (respCnt > 0);
	}

	//---------------------------------------------------------------------------
	// store Config                                                               
	//---------------------------------------------------------------------------
private: 
	static bool storeConfig( SerialPort^   port
		, cli::array<Byte>^ wdata
		, cli::array<Byte>^ rdata
		)
	{
		int respCnt = 0;
		rdata[0] = 'a';
		rdata[1] = 'b';
		rdata[2] = 'c';
		rdata[3] = 'd';

		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x45;						//  {E}

		uchar cksum = checkSum(wdata, 4);
		wdata[4] = hexb[cksum >> 4];
		wdata[5] = hexb[cksum & 0xf];			//  {cksum}
		wdata[6] = 0x0d;						//  {cr}

		// send command
		// raise RTS, wait for reversal of line, read and lower RTS
		port->RtsEnable = true;
		port->Write(wdata, 0, 7);				 

		while(port->BytesToWrite > 0)
			;
		port->RtsEnable = false;
		Thread::Sleep(4000);

		respCnt = port->Read(rdata, 0, port->BytesToRead);
		return (respCnt == 4);
	}
	/*
	//---------------------------------------------------------------------------
	// setIo                                                                
	//---------------------------------------------------------------------------
	private: bool setIo( SerialPort^   port
	, cli::array<Byte>^ wdata
	, cli::array<Byte>^ rdata
	, ushort		cmd)
	{
	wdata[0] = 0x3e;						//  {>}
	wdata[1] = '0';
	wdata[2] = '0';					    //  {address}

	if((cmd & O_CLEAR) == 0)
	wdata[3] = 0x64;					//  {d}   SET
	else
	wdata[3] = 0x65;					//  {e}  CLEAR

	wdata[4] = hexb[(cmd >> 4) & 0xf];
	wdata[5] = hexb[cmd & 0xf];			

	uchar cksum = checkSum(wdata, 6);
	wdata[6] = hexb[cksum >> 4];
	wdata[7] = hexb[cksum & 0xf];			//  {cksum}
	wdata[8] = 0x0d;						//  {cr}
	return sendOpto(port, wdata, rdata, 9, 4);
	}
	*/
	//---------------------------------------------------------------------------
	// clear    A                                                                 
	//---------------------------------------------------------------------------
private: 
	static bool sendClear( SerialPort^   port
		, cli::array<Byte>^ wdata
		, cli::array<Byte>^ rdata
		)
	{
		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x41;						//  {A}
		uchar cksum = checkSum(wdata, 4);
		wdata[4] = hexb[cksum >> 4];
		wdata[5] = hexb[cksum & 0xf];			//  {cksum}
		wdata[6] = 0x0d;						//  {cr}
		return sendOpto(port, wdata, rdata, 7, 4);
	}

	//---------------------------------------------------------------------------
	// reset     B                                                                
	//---------------------------------------------------------------------------
private: 
	static bool sendReset( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		)
	{
		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x42;						//  {B}
		uchar cksum = checkSum(wdata, 4);
		wdata[4] = hexb[cksum >> 4];
		wdata[5] = hexb[cksum & 0xf];			//  {cksum}
		wdata[6] = 0x0d;						//  {cr}
		return sendOpto(port, wdata, rdata, 7, 4);
	}

	//---------------------------------------------------------------------------
	// send Wpoints    J                                                               
	//---------------------------------------------------------------------------
private: 
	static bool setWpoints( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		, ushort wpts)
	{
		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x4a;						//  {J}
		// mmmm					
		wdata[4] = '0';						// input
		wdata[5] = hexb[(wpts >> 8 ) & 0x3];					
		wdata[6] = hexb[(wpts >> 4 ) & 0xf];
		wdata[7] = hexb[(wpts >> 0 ) & 0xf];			
		// nnnn	
		wdata[8]  = '0';						// input
		wdata[9]  = hexb[(~wpts >> 8 ) & 0x3];						
		wdata[10] = hexb[(~wpts >> 4 ) & 0xf];
		wdata[11] = hexb[(~wpts >> 0 ) & 0xf];			

		uchar cksum = checkSum(wdata, 12);
		wdata[12] = hexb[cksum >> 4];
		wdata[13] = hexb[cksum & 0xf];			//  {cksum}
		wdata[14] = 0x0d;						//  {cr}
		return sendOpto(port, wdata, rdata, 15, 4);
	}		

	//---------------------------------------------------------------------------
	// set Watchdog         D                                                          
	//---------------------------------------------------------------------------
private: 
	static bool setWatchdog( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		, ushort timeout)						// in 10ms units
	{
		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x44;						//  {D}
		// mmmm	
		wdata[4] = '0';
		wdata[5] = '0';			
		wdata[6] = '0';
		wdata[7] = '0';			
		// nnnn	
		wdata[8]  = 'F';
		wdata[9]  = 'F';			
		wdata[10] = 'F';
		wdata[11] = 'F';			
		// tttt
		wdata[12] = hexb[(timeout >> 12) & 0xf];
		wdata[13] = hexb[(timeout >> 8 ) & 0xf];			
		wdata[14] = hexb[(timeout >> 4 ) & 0xf];
		wdata[15] = hexb[(timeout >> 0 ) & 0xf];	

		uchar cksum = checkSum(wdata, 16);
		wdata[16] = hexb[cksum >> 4];
		wdata[17] = hexb[cksum & 0xf];			//  {cksum}
		wdata[18] = 0x0d;						//  {cr}
		return sendOpto(port, wdata, rdata, 19, 4);
	}
	//---------------------------------------------------------------------------	 
private: 
	static ushort a2b(char rpt)
	{
		ushort ret;

		if(rpt <= '9') ret = rpt - '0'; else ret = rpt - 'A' + 10; 
		return ret;
	}

	//---------------------------------------------------------------------------
	// get rpoints       R                                                             
	//---------------------------------------------------------------------------
private: 
	static bool getRpoints( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		, int *pnRpoints)
	{
		bool ret;
		*pnRpoints = 0;
		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x52;						//  {R}

		uchar cksum = checkSum(wdata, 4);
		wdata[4] = hexb[cksum >> 4];
		wdata[5] = hexb[cksum & 0xf];			//  {cksum}
		wdata[6] = 0x0d;						//  {cr}

		ret = sendOpto(port, wdata, rdata, 7, 7);
		if(ret)
		{
			*pnRpoints = (a2b(rdata[1]) << 12) 
				+ (a2b(rdata[2]) << 8) 
				+ (a2b(rdata[3]) << 4) 
				+ a2b(rdata[4]);
		}
		return ret;
	}

	//---------------------------------------------------------------------------
	// set Config     G                                                             
	//---------------------------------------------------------------------------
private: 
	static bool setConfig( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		)
	{
		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x47;						//  {G}
		// mmmm	
		wdata[4] = 'F';
		wdata[5] = 'F';			
		wdata[6] = 'F';
		wdata[7] = 'F';		
		// nnnn				 
		wdata[8] = '0';						// inputs
		wdata[9] = '0';			
		wdata[10] = '0';
		wdata[11] = '0';		
		wdata[12] = '0';
		wdata[13] = '0';			
		wdata[14] = '0';
		wdata[15] = '0';		
		wdata[16] = '0';
		wdata[17] = '0';			
		wdata[18] = '0';
		wdata[19] = '0';		
		wdata[20] = '8';						// outputs
		wdata[21] = '0';			
		wdata[22] = '8';
		wdata[23] = '0';		

		wdata[24] = '8';
		wdata[25] = '0';			
		wdata[26] = '8';
		wdata[27] = '0';		
		wdata[28] = '8';
		wdata[29] = '0';			
		wdata[30] = '8';
		wdata[31] = '0';		
		wdata[32] = '8';
		wdata[33] = '0';			
		wdata[34] = '8';
		wdata[35] = '0';		
		wdata[36] = '8';
		wdata[37] = '0';			
		wdata[38] = '8';
		wdata[39] = '0';		
		uchar cksum = checkSum(wdata, 40);
		wdata[40] = hexb[cksum >> 4];
		wdata[41] = hexb[cksum & 0xf];			//  {cksum}
		wdata[42] = 0x0d;						//  {cr}
		return sendOpto(port, wdata, rdata, 43, 4);
	}
	//---------------------------------------------------------------------------
	// read Config     Y                                                            
	//---------------------------------------------------------------------------
private: 
	static bool readConfig( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		)
	{
		wdata[0] = 0x3e;						//  {>}
		wdata[1] = '0';
		wdata[2] = '0';						//  {address}
		wdata[3] = 0x59;						//  {Y}

		uchar cksum = checkSum(wdata, 4);
		wdata[4] = hexb[cksum >> 4];
		wdata[5] = hexb[cksum & 0xf];			//  {cksum}
		wdata[6] = 0x0d;						//  {cr}
		return sendOpto(port, wdata, rdata, 7, 36);
	}
	///////////////////////////////////////////////////////////////////////////
public:	
	static void ThreadProc(Object^ pAll)
	{
		All^ pO = (All^)pAll;
		INI *psIni = pO->psIni;

		// Buffers to store the 485 serial command bytes.
		cli::array<Byte>^wdata = gcnew cli::array<Byte>(64);
		cli::array<Byte>^rdata = gcnew cli::array<Byte>(64);

		// IO points.
		int  rtmps = 0;
		int  wtmps = 0;
		bool bRet;
		int nError;

		//------------------------------------------------------------
		while(true)
		{			
			// Create a SerialPort.
			SerialPort^ port = gcnew SerialPort(gcnew String(psIni->acOptoCom), psIni->nOptoBaud);

			try
			{
				port->Open();
				port->RtsEnable = true;
				port->DtrEnable = true;

				// loop ----------------------------------------------
				while(true)
				{
					while(psIni->nOptoOk == 0)
					{
						// reset & clear -----------------------------
						psIni->nOptoOk = sendReset(port, wdata, rdata);
						Thread::Sleep(1000);

						if(psIni->nOptoOk)
							psIni->nOptoOk = sendClear(port, wdata, rdata);	

						if(psIni->nOptoOk)									 
							psIni->nOptoOk = readConfig(port, wdata, rdata);

						//------------------auto-configuration--------
						if(rdata[13] != '8' || rdata[15] != '8' 
							|| rdata[17] != '8' || rdata[19] != '8' 
							|| rdata[21] != '8' || rdata[23] != '8' 
							|| rdata[25] != '8' || rdata[27] != '8' 
							|| rdata[29] != '8' || rdata[31] != '8')
						{
							//					 optoLb->BackColor = Color::Blue;

							psIni->nOptoOk = setConfig(port, wdata, rdata);

							if(psIni->nOptoOk)
								bRet = setWatchdog(port, wdata, rdata, 100);
							if(psIni->nOptoOk)
								bRet = storeConfig(port, wdata, rdata);
						}	 
						nError = 0;		 	 
					}

					psIni->nOptoOk = 1;

					// Wait for timer method to signal.----------------
					//					 autoEvent->WaitOne();

					if(wtmps != psIni->nWpoints)
					{
						wtmps = psIni->nWpoints;
						bRet = setWpoints(port, wdata, rdata, wtmps);	
						if(bRet == false)
							nError ++;
					}

					bRet = getRpoints(port, wdata, rdata, &rtmps);

					if(bRet)
						psIni->nRpoints = rtmps;
					else
						nError++;

					if(nError > 10) psIni->nOptoOk = 0;
				}
			}
			catch ( NullReferenceException^ e ) 
			{
				Console::WriteLine( "NullReferenceException: {0}", e );
			}
			catch ( IO::IOException^ e ) 
			{
				Console::WriteLine( "IO Exception: {0}", e );
			}
			// Close everything.
			port->Close();
			psIni->nOptoOk = 0;
			Thread::Sleep(2000);

			psIni->nOptoOk = 1;
			Thread::Sleep(2000);	
		}
	}

};
}
#endif

