#pragma once
#include "StdAfx.h"

using namespace System;
using namespace System::Threading;
using namespace System::Data::Odbc;
using namespace System::Data::SqlClient;

namespace As
{
	// THREAD class interfacing database ==========================================
	ref class CDbase
	{
	private:
		CDbase(void)
		{
		}
	public:
		//-------------------------------------------------------------------------
		static void ThreadProc(Object^ pAllIn)
		{
			All^ pAll = (All^)pAllIn;
			System::Collections::Generic::Queue<Dbase^>^ qDbase = pAll->qDbase;	//DC 4.0.2//Queue^ qDbase;
			//System::Collections::Generic::Queue<Dbase^>^ qDbaseBad;	//DC 4.0.2//Queue^ qDbase;

			INI* psIni = pAll->psIni;
			char acCmd[128];
			Dbase^ pDbase = nullptr;
			int nRows = 0;
			char acLine[128];

			OdbcDataReader^ pReader;
			OdbcConnection^ pConn = gcnew OdbcConnection(pAll->pOdbc);
			OdbcCommand^ pCmd = gcnew OdbcCommand();
			pCmd->Connection = pConn;
			//pCmd->CommandType = CommandType::StoredProcedure;

			while (true)
			{
				try
				{
					pConn->Open();
					psIni->nDbaseOk = 1;

					// loop ----------------------------------------------
					while (true)
					{
						if (qDbase->Count > 0)
						{
							psIni->nDbaseOk = 5;	//	DbaseLb->BackColor = Color::PaleGreen;
							pDbase = (Dbase^)qDbase->Dequeue();

							if (pDbase->bVoid == false)
								sprintf_s(acCmd, "{call EXP_LOADOUT_WEIGHTS('%02d',%d,%6.2f,%6.2f,'%c%c')}",
									pDbase->nPlant, pDbase->nTicket, pDbase->fGross, pDbase->fTare, pDbase->cUnit0, pDbase->cUnit1);
							else
								sprintf_s(acCmd, "{call EXP_LOADOUT_VOIDTICKET('%02d',%d,'CANCELLED')}",
									pDbase->nPlant, pDbase->nTicket);

							pCmd->CommandText = gcnew String(acCmd);
							pCmd->ExecuteNonQuery();
							if (psIni->bTest)
							{
								pAll->pDbCmd = pCmd->CommandText;
							}
							// test data -----------------------------------------
							sprintf_s(acCmd, "{call EXP_LOADOUT_WEIGHTS_RET('%02d',%d)}", pDbase->nPlant, pDbase->nTicket);	//DC 3.2.2
							pCmd->CommandText = gcnew String(acCmd);
							pReader = pCmd->ExecuteReader();

							if (pReader->Read())
							{
								pAll->nTicket = pReader->GetInt32(0);
								pAll->dSold = pReader->GetDouble(1);
							}
							pReader->Close();
							String^ stSold = (pDbase->fGross - pDbase->fTare).ToString("f2");

							// requeue the ticket to watchdog queue
							if (pAll->nTicket != pDbase->nTicket || !pAll->dSold.ToString("f2")->Equals(stSold))
							{
								pAll->qDbaseBad->Enqueue(pDbase);
								pDbase = nullptr;
							}
							else
							{
								sprintf(acLine, "%10d,%14s,%12s,%8.2f,%8.2f,%8.2f\n"
									, pDbase->nTicket
									, MarshalStr1(pDbase->pstCustCode).c_str()
									, MarshalStr1(pDbase->pstTruck).c_str()
									, pDbase->fGross
									, pDbase->fTare
									, pDbase->fGross - pDbase->fTare);
								fputs(acLine, pAll->psIni->pfDbs);
							}
						}
						else
						{
							Thread::Sleep(500);
							psIni->nDbaseOk = 1;
						}
					}
				}
				catch (NullReferenceException^ ex)
				{
					pAll->pExc += "\nDBASE NULL Exception: " + ex->Message;
				}
				catch (OdbcException^ ex)
				{
					// reque the ticket to watchdog queue
					if (pDbase != nullptr)
					{
						pAll->qDbaseBad->Enqueue(pDbase);
						pDbase = nullptr;
					}
					pAll->pExc += "\nDBASE ODBC Exception: " + ex->Message;
				}
				catch (SqlException^ ex)
				{
					pAll->pExc += "\nDBASE SQL Exception: " + ex->Message;
				}

				// Shutdown and end connection`
				if (pConn)pConn->Close();

				psIni->nDbaseOk = 0;
				Thread::Sleep(1000);
			}
		}

		/// <summary>
		/// MarshalString
		/// </summary>
		/// <param name="s"></param>
		/// <param name="outputstring"></param>
		static string MarshalStr1(String^ s)
		{
			const char* kPtoC = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
			string outputstring = kPtoC;
			System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)kPtoC));
			return(outputstring);
		}
	
	};
}
