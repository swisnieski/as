#pragma once
#include "StdAfx.h"

using namespace System;
using namespace System::Threading;

namespace As
{
// THREAD class interfacing OPTO card==========================================
ref class COptoT
{
private:
	COptoT(void)
	{
	}

	//-------------------------------------------------------------------------
private:
	static int nDelay;

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
		port->Parity = Parity::Mark;
		port->Write(wdata, 0, 1);				 
		port->Parity = Parity::Space;
		port->Write(wdata, 1, cmdLen-1);				 

		while(port->BytesToWrite > 0)
			;
		port->RtsEnable = false;
		Thread::Sleep(nDelay);

		respCnt = port->Read(rdata, 0, port->BytesToRead);
		return (respCnt > 0);
	}

	//---------------------------------------------------------------------------
	// store Config       E                                                        
	//---------------------------------------------------------------------------
private: 
	static bool storeConfig( SerialPort^   port
		, cli::array<Byte>^ wdata
		, cli::array<Byte>^ rdata

		)
	{
		wdata[0] = 0;						//  address
		wdata[1] = 0x2;						// length
		wdata[2] = 0x45;					//  {E}
		wdata[3] = checkSum(wdata, 3);		// csum
		return sendOpto(port, wdata, rdata, 4, 3);
	}

	//---------------------------------------------------------------------------
	// set Watchdog         D                                                          
	//---------------------------------------------------------------------------
private: 
	static bool setWatchdog( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		, ushort timeout)					// in 10ms units
	{
		wdata[0] = 0;						//  {address}
		wdata[1] = 0x8;						// length
		wdata[2] = 0x44;					//  {D}
		// mmmm	
		wdata[3] = 0;
		wdata[4] = 0;			
		// nnnn	
		wdata[5]  = 0xff;
		wdata[6]  = 0xff;			
		// tttt
		wdata[7] = (timeout >> 8) & 0xff;
		wdata[8] =  timeout       & 0xff;			

		wdata[9] = checkSum(wdata, 9);
		return sendOpto(port, wdata, rdata, 10, 4);
	}

	//---------------------------------------------------------------------------
	// clear    A                                                                 
	//---------------------------------------------------------------------------
private: 
	static bool sendClear( SerialPort^   port
		, cli::array<Byte>^ wdata
		, cli::array<Byte>^ rdata

		)
	{
		wdata[0] = 0;						//  address
		wdata[1] = 0x2;						//  length
		wdata[2] = 0x41;					//  CLEAR
		wdata[3] = checkSum(wdata, 3);		//  csum
		return sendOpto(port, wdata, rdata, 4, 3);
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
		wdata[0] = 0;						//  address
		wdata[1] = 0x2;						//  length
		wdata[2] = 0x42;					//  RESET
		wdata[3] = checkSum(wdata, 3);		//  csum
		return sendOpto(port, wdata, rdata, 4, 3);
	}

	//---------------------------------------------------------------------------
	// send Wpoints    J                                                               
	//---------------------------------------------------------------------------
private: 
	static bool setWpoints( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		, ushort wpts
		)
	{
		wdata[0] = 0;						//  address
		wdata[1] = 0x6;						//  length
		wdata[2] = 0x4A;					//  SET WPOINTS
		wdata[3] = (wpts >> 8 ) & 0x3;		//  MMMM
		wdata[4] =  wpts & 0xff;		    //  MMMM
		wdata[5] = (~wpts >> 8 ) & 0x3;		//  NNNN
		wdata[6] = ~wpts & 0xff;			//  NNNN
		wdata[7] = checkSum(wdata, 7);		//  csum

		if(sendOpto(port, wdata, rdata, 8, 3))
			return ((rdata[0] == 2) && (rdata[1] == 0));
		else
			return false;
	}		

	//---------------------------------------------------------------------------
	// get rpoints       R                                                             
	//---------------------------------------------------------------------------
private: 
	static bool getRpoints( SerialPort^ port
		, cli::array<Byte>^wdata
		, cli::array<Byte>^rdata
		, int *pnRpoints
		)
	{
		bool ret;

		wdata[0] = 0;						//  address
		wdata[1] = 0x2;						//  length
		wdata[2] = 0x52;					//  GET RPOINTS
		wdata[3] = checkSum(wdata, 3);		//  csum
		ret = sendOpto(port, wdata, rdata, 4, 5);
		if(ret)
			*pnRpoints = (rdata[2] << 8) + rdata[3]; 
		else
			*pnRpoints = 0;

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
		wdata[0] = 0;					//  {address}
		wdata[1] = 20;					// length
		wdata[2] = 0x47;				//  {G}
		// mmmm	
		wdata[3] = 0xff;
		wdata[4] = 0xff;			
		// nnnn				 
		wdata[5] = 0;				     // input 15
		wdata[6] = 0;
		wdata[7] = 0;
		wdata[8] = 0;
		wdata[9] = 0;
		wdata[10] = 0;
		wdata[11] = 0x80;				// output 9
		wdata[12] = 0x80;

		wdata[13] = 0x80;				// output 7
		wdata[14] = 0x80;
		wdata[15] = 0x80;				
		wdata[16] = 0x80;					
		wdata[17] = 0x80;
		wdata[18] = 0x80;
		wdata[19] = 0x80;
		wdata[20] = 0x80;				// output 0

		wdata[21] =  checkSum(wdata, 21);
		return sendOpto(port, wdata, rdata, 22, 4);
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
		wdata[0] = 0;						//  address
		wdata[1] = 0x2;						// length
		wdata[2] = 0x59;					//  {Y}
		wdata[3] = checkSum(wdata, 3);		// chksum
		return sendOpto(port, wdata, rdata, 4, 18);
	}
	///////////////////////////////////////////////////////////////////////////
public:	
	static void ThreadProc(Object^ pAllIn)
	{
		All^ pAll = (All^)pAllIn;
		INI *psIni = pAll->psIni;

		// Buffers to store the 485 serial command bytes.
		cli::array<Byte>^wdata = gcnew cli::array<Byte>(64);
		cli::array<Byte>^rdata = gcnew cli::array<Byte>(64);

		// IO points.
		int  rtmps = 0;
		int  wtmps = 0;
		bool bRet;

		nDelay = psIni->nOptoDelay;
		psIni->nOptoOk = 0;				// opto need initialization
		psIni->nWpoints = 0;

		// Create a SerialPort.
		SerialPort^ port = gcnew SerialPort(pAll->pOptoCom, psIni->nOptoBaud);

		//------------------------------------------------------------
		while(true)
		{			
			try
			{
				while(psIni->nOptoOk == 0)
				{
					// reset & clear -----------------------------
					psIni->nOptoOk = 2;			// hunt mode
					port->Open();
					port->RtsEnable = true;
					port->DtrEnable = true;
					Thread::Sleep(1000);

					psIni->nOptoOk = sendReset(port, wdata, rdata);
					Thread::Sleep(1000);

					if(psIni->nOptoOk)
						psIni->nOptoOk = sendClear(port, wdata, rdata);	

					if(psIni->nOptoOk)									 
						psIni->nOptoOk = readConfig(port, wdata, rdata);

					//------------------auto-configuration--------
					if(rdata[ 2] != 0 || rdata[ 3] != 0 
					|| rdata[ 4] != 0 || rdata[ 5] != 0 
					|| rdata[ 6] != 0 || rdata[ 7] != 0 
					|| rdata[ 8] != 0x80 || rdata[ 9] != 0x80 
					|| rdata[10] != 0x80 || rdata[11] != 0x80 
					|| rdata[12] != 0x80 || rdata[13] != 0x80 
					|| rdata[14] != 0x80 || rdata[15] != 0x80
					|| rdata[16] != 0x80 || rdata[17] != 0x80
					)
					{
						psIni->nOptoOk = setConfig(port, wdata, rdata);

						if(psIni->nOptoOk)
							bRet = setWatchdog(port, wdata, rdata, 100);
						if(psIni->nOptoOk)
							bRet = storeConfig(port, wdata, rdata);
					}

					if(psIni->nOptoOk == 0)
					{
						pAll->nOptoError++;
						port->Close();
						Thread::Sleep(1000);
					}
				}

				pAll->nOptoError = 0;		 	 
				psIni->nOptoOk = 1;

				// Wait for timer method to signal.----------------
				//					 autoEvent->WaitOne();

				if(wtmps != psIni->nWpoints)
				{
					wtmps = (int)psIni->nWpoints;
					bRet = setWpoints(port, wdata, rdata, wtmps);	
					if(bRet == false)
						pAll->nOptoError ++;
				}

				bRet = getRpoints(port, wdata, rdata, &rtmps);

				if(bRet)
					psIni->nRpoints = rtmps;
				else
					pAll->nOptoError++;

				if(pAll->nOptoError > 100) 
					psIni->nOptoOk = 0;
			}
			catch ( NullReferenceException^ ex ) 
			{
				psIni->nOptoOk = 0;
				pAll->pExc += "\nOPTO NULL Exception: " + ex->Message;
			}
			catch ( IO::IOException^ ex ) 
			{
				psIni->nOptoOk = 0;
				pAll->pExc += "\nOPTO IO Exception: " + ex->Message;
			}
			// Close everything.
			if(psIni->nOptoOk == 0)
			{
				port->Close();
				Thread::Sleep(2000);
			}
		}
	}

};
}
