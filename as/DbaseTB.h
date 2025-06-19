#pragma once
#include "StdAfx.h"

using namespace System;
using namespace System::Threading;

namespace As
{
// THREAD class to database ===================================================
ref class CDbaseB
{
private:
	CDbaseB(void)
	{
	}
public:
	//-------------------------------------------------------------------------
	static void ThreadProc(Object^ pAllIn)
	{
		All^ pAll = (All^)pAllIn;
		//Queue^ qBad = pAll->qDbaseBad;
		//Dbase^ pDbase;
		//int nCount;
		//char acLine[128];


		// // loop ----------------------------------------------
		// while(true)
		// {
		//	 if((nCount = qBad->Count) > 0)
		//	 {
		//		// reque the dbrecord
		//		for(int i=0; i<nCount; i++)
		//		{
		//			 pDbase = (Dbase^)qBad->Dequeue();
 	//				 pDbase->nRetry++;

		//			 if(pDbase->nRetry < 5)
		//			 {
		//				if(pAll->psIni->nDbaseOk > 0)				//DC 4.1.1
		//					pAll->qDbase->Enqueue(pDbase);
		//				else
		//					qBad->Enqueue(pDbase);
		//			 }
		//			 else
		//			 {
		//				 sprintf(acLine, "%10d,%14s,%12s,%8.2f,%8.2f,%8.2f\n"
		//					 , pDbase->nTicket
		//					 , pDbase->pstCustCode
		//					 , pDbase->pstTruck
		//					 , pDbase->fGross
		//					 , pDbase->fTare
		//					 , pDbase->fGross - pDbase->fTare);
		//				 fputs(acLine, pAll->psIni->pfDbe);
		//			 }
		//		}
		//		Thread::Sleep(60000);
		//	 }
		//	 else
		//	 {
		//		 Thread::Sleep(30000);
		//	 }
		// }

	}
};
}
