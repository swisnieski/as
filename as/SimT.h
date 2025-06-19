#pragma once
#include "StdAfx.h"

using namespace System;
using namespace System::Threading;

namespace As
{
	// THREAD class simulating inputs ==============================================
	ref class CSim
	{
	private:
		CSim()
		{
		}

	public:
		//-------------------------------------------------------------------------
		static void ThreadProc(Object^ pInp)
		{
			All^ pAll = (All^)pInp;
			INI *psIni = pAll->psIni;
			int nFillCnt = 0;
			int nDelay1 = 0;
			int nDelay2 = 0;
			int nDelay3 = 0;
			int nDelay4 = 0;

			if(pAll->eAsType == A_DEMO)
			{
				psIni->nOptoOk = true;
				psIni->bPrinterOk1 = true;
				psIni->bPrinterOk2 = true;
				psIni->bPrinterOk3 = true;
				psIni->bPrinterOk4 = true;
				psIni->sScale1.bSerial = true;
				psIni->sScale2.bSerial = true;
				psIni->sScale3.bSerial = true;
				psIni->sScale4.bSerial = true;
			}
			//-----------------------------------------------------------------
			while(true)
			{
				 if(psIni->bBotScale)
				 {
					 if(psIni->bTickAddress)
					 {
						 switch(nFillCnt/10)
						 {
						 case  0: 
							 psIni->nRpoints |=  J_FILL1; 
							 psIni->nRpoints &= ~J_FILL2;
							 psIni->nRpoints &= ~J_FILL3; 
							 psIni->nRpoints &= ~J_FILL4;
							 psIni->nRpoints &= ~J_FILL5; 
							 psIni->nRpoints &= ~J_FILL6;
							 psIni->nRpoints &= ~J_FILL7;
							 psIni->nRpoints &= ~J_FILL8; 
							 psIni->nRpoints &= ~J_FILL9;
							 psIni->nRpoints &= ~J_FILL10;
							 psIni->nRpoints &= ~J_FILL11; 
							 psIni->nRpoints &= ~J_FILL12;
							 break; 
						 case  1: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case  2: 
							 if(psIni->fSiloMax2 > 0) 
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints |=  J_FILL2; 
							 }
							 break;
						 case  3: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case  4: 
							 if(psIni->fSiloMax3 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL2;
								 psIni->nRpoints |=  J_FILL3; 
							 }
							 break;
						 case  5: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;

							 //---------------------------------------------------------------------
						 case  6: 
							 if(psIni->fSiloMax4 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL3;
								 psIni->nRpoints |=  J_FILL4; 
							 }
							 break; 
						 case  7: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case  8: 
							 if(psIni->fSiloMax5 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL4; 
								 psIni->nRpoints |=  J_FILL5; 
							 }
							 break;
						 case  9: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case 10: 
							 if(psIni->fSiloMax6 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL5;
								 psIni->nRpoints |=  J_FILL6; 
							 }
							 break;
						 case 11: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;

							 //---------------------------------------------------------------------
						 case 12: 
							 psIni->nRpoints |=  J_FILL1; 
							 psIni->nRpoints &= ~J_FILL6; 
							 psIni->nRpoints |=  J_FILL7; 
							 break; 
						 case 13: psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case 14: 
							 if(psIni->fSiloMax8 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL7; 
								 psIni->nRpoints |=  J_FILL8; 
							 }
							 break;
						 case 15: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case 16: 
							 if(psIni->fSiloMax9 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL8; 
								 psIni->nRpoints |=  J_FILL9; 
							 }
							 break;
						 case 17: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;

							 //DC 3.3.0 ---------------------------------------------------------------------
						 case 18: 
							 psIni->nRpoints |=  J_FILL1; 
							 psIni->nRpoints &= ~J_FILL9; 
							 psIni->nRpoints |=  J_FILL10; 
							 break; 
						 case 19: psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case 20: 
							 if(psIni->fSiloMax10 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL10; 
								 psIni->nRpoints |=  J_FILL11; 
							 }
							 break;
						 case 21: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;
						 case 22: 
							 if(psIni->fSiloMax11 > 0)
							 {
								 psIni->nRpoints |=  J_FILL1; 
								 psIni->nRpoints &= ~J_FILL11; 
								 psIni->nRpoints |=  J_FILL12; 
							 }
							 break;
						 case 23: 
							 psIni->nRpoints &= ~J_FILL1; 
							 break;
						 default: nFillCnt = -1; break;
						 }

					 }
					 else if (!psIni->bSendTarget && !psIni->bSendBitWise)
					 {
						 switch(nFillCnt/10)
						 {
						 case  0: psIni->nRpoints |=  J_FILL1; break; 
						 case  1: psIni->nRpoints &= ~J_FILL1; break;
						 case  2: if(psIni->fSiloMax2 > 0 && psIni->nL1SilosNum > 1) psIni->nRpoints |=  J_FILL2; break;
						 case  3: if(psIni->fSiloMax2 > 0 && psIni->nL1SilosNum > 1) psIni->nRpoints &= ~J_FILL2; break;
						 case  4: if(psIni->fSiloMax3 > 0 && psIni->nL1SilosNum > 2)psIni->nRpoints |=  J_FILL3; break;
						 case  5: if(psIni->fSiloMax3 > 0 && psIni->nL1SilosNum > 2)psIni->nRpoints &= ~J_FILL3; break;
						 case  6: psIni->nRpoints |=  J_FILL4; break; 
						 case  7: psIni->nRpoints &= ~J_FILL4; break;
						 case  8: if(psIni->fSiloMax5 > 0 && psIni->nL2SilosNum > 1)psIni->nRpoints |=  J_FILL5; break;
						 case  9: if(psIni->fSiloMax5 > 0 && psIni->nL2SilosNum > 1)psIni->nRpoints &= ~J_FILL5; break;
						 case 10: if(psIni->fSiloMax6 > 0 && psIni->nL2SilosNum > 2)psIni->nRpoints |=  J_FILL6; break;
						 case 11: if(psIni->fSiloMax6 > 0 && psIni->nL2SilosNum > 2)psIni->nRpoints &= ~J_FILL6; break;
						 case 12: psIni->nRpoints |=  J_FILL7; break; 
						 case 13: psIni->nRpoints &= ~J_FILL7; break;
						 case 14: if(psIni->fSiloMax8 > 0 && psIni->nL3SilosNum > 1)psIni->nRpoints |=  J_FILL8; break;
						 case 15: if(psIni->fSiloMax8 > 0 && psIni->nL3SilosNum > 1)psIni->nRpoints &= ~J_FILL8; break;
						 case 16: if(psIni->fSiloMax9 > 0 && psIni->nL3SilosNum > 2)psIni->nRpoints |=  J_FILL9; break;
						 case 17: if(psIni->fSiloMax9 > 0 && psIni->nL3SilosNum > 2)psIni->nRpoints &= ~J_FILL9; break;
						 case 18: psIni->nRpoints |=  J_FILL10; break; 
						 case 19: psIni->nRpoints &= ~J_FILL10; break;
						 case 20: if(psIni->fSiloMax11 > 0 && psIni->nL4SilosNum > 1)psIni->nRpoints |=  J_FILL11; break;
						 case 21: if(psIni->fSiloMax11 > 0 && psIni->nL4SilosNum > 1)psIni->nRpoints &= ~J_FILL11; break;
						 case 22: if(psIni->fSiloMax12 > 0 && psIni->nL4SilosNum > 2)psIni->nRpoints |=  J_FILL12; break;
						 case 23: if(psIni->fSiloMax12 > 0 && psIni->nL4SilosNum > 2)psIni->nRpoints &= ~J_FILL12; break;
						 default: nFillCnt = -1; break;
						 }
					}

					if(pAll->eAsType == A_DEMO)
					{
						if(!psIni->bPdmPlc)
						{
							 //drops ------------------------------------------------------
							 if(((psIni->nWpoints & P_DROP1) > 0)
							 || ((psIni->nWpoints & P_DROP2) > 0)
							 || ((psIni->nWpoints & P_DROP3) > 0))
								 psIni->sScale1.dValue += 0.1;

							 if(((psIni->nWpoints & P_DROP4) > 0)
							 || ((psIni->nWpoints & P_DROP5) > 0)
							 || ((psIni->nWpoints & P_DROP6) > 0))
								 psIni->sScale2.dValue += 0.1;

							 if(((psIni->nWpoints & P_DROP7) > 0)
							 || ((psIni->nWpoints & P_DROP8) > 0)
							 || ((psIni->nWpoints & P_DROP9) > 0))
								 psIni->sScale3.dValue += 0.1;

							 if(((psIni->nWpoints & P_DROP10) > 0)
							 || ((psIni->nWpoints & P_DROP11) > 0)
							 || ((psIni->nWpoints & P_DROP12) > 0))
								 psIni->sScale4.dValue += 0.1;
						}
						else if(psIni->bSendBitWise)
						{
							//ready------------------------------------------------------
							/*if(psIni->sLog1.eState == S_READY)
							{
								if(nDelay1 < 50)
									nDelay1++;
								else
									psIni->nRpoints |= psIni->asSilos[psIni->sLog1.nSilo-1].uDropReadyI;
							}
							else
							{
								nDelay1 = 0;
								psIni->nRpoints &= ~psIni->asSilos[psIni->sLog1.nSilo-1].uDropReadyI;
							}

							if(psIni->sLog2.eState == S_READY)
							{
								if(nDelay2 < 50)
									nDelay2++;
								else
									psIni->nRpoints |= psIni->asSilos[psIni->sLog2.nSilo-1].uDropReadyI;
							}
							else
							{
								nDelay2 = 0;
								psIni->nRpoints &= ~psIni->asSilos[psIni->sLog2.nSilo-1].uDropReadyI;
							}

							if(psIni->sLog3.eState == S_READY)
							{
								if(nDelay3 < 50)
									nDelay3++;
								else
									psIni->nRpoints |= psIni->asSilos[psIni->sLog3.nSilo-1].uDropReadyI;
							}
							else
							{
								nDelay3 = 0;
								psIni->nRpoints &= ~psIni->asSilos[psIni->sLog3.nSilo-1].uDropReadyI;
							}

							if(psIni->sLog4.eState == S_READY)
							{
								if(nDelay4 < 50)
									nDelay4++;
								else
									psIni->nRpoints |= psIni->asSilos[psIni->sLog4.nSilo-1].uDropReadyI;
							}
							else
							{
								nDelay4 = 0;
								psIni->nRpoints &= ~psIni->asSilos[psIni->sLog4.nSilo-1].uDropReadyI;
							}*/
							//drops ------------------------------------------------------
							if(((psIni->nWpoints & psIni->asSilos[0].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[1].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[2].uDropO) > 0))
							{
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog1.nSilo-1].uFlowRate1O) > 0)
									psIni->sScale1.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog1.nSilo-1].uFlowRate2O) > 0)
									psIni->sScale1.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog1.nSilo-1].uFlowRate3O) > 0)
									psIni->sScale1.dValue += 0.1;
								else
									psIni->sScale1.dValue += 0.1;
							}

							 if(((psIni->nWpoints & psIni->asSilos[3].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[4].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[5].uDropO) > 0))
							{
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog2.nSilo-1].uFlowRate1O) > 0)
									psIni->sScale2.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog2.nSilo-1].uFlowRate2O) > 0)
									psIni->sScale2.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog2.nSilo-1].uFlowRate3O) > 0)
									psIni->sScale2.dValue += 0.1;
								else
									psIni->sScale2.dValue += 0.1;
							}

							 if(((psIni->nWpoints & psIni->asSilos[6].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[7].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[8].uDropO) > 0))
							{
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog3.nSilo-1].uFlowRate1O) > 0)
									psIni->sScale3.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog3.nSilo-1].uFlowRate2O) > 0)
									psIni->sScale3.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog3.nSilo-1].uFlowRate3O) > 0)
									psIni->sScale3.dValue += 0.1;
								else
									psIni->sScale3.dValue += 0.1;
							}

							 if(((psIni->nWpoints & psIni->asSilos[9].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[10].uDropO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[11].uDropO) > 0))
							{
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog4.nSilo-1].uFlowRate1O) > 0)
									psIni->sScale4.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog4.nSilo-1].uFlowRate2O) > 0)
									psIni->sScale4.dValue += 0.1;
								if((psIni->nWpoints & psIni->asSilos[psIni->sLog4.nSilo-1].uFlowRate3O) > 0)
									psIni->sScale4.dValue += 0.1;
								else
									psIni->sScale4.dValue += 0.5;
							}
						}
						else
						{
							//drops ------------------------------------------------------
							if(((psIni->nWpoints & psIni->asSilos[0].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[1].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[2].uReadyO) > 0))
							{
								psIni->sScale1.dValue += 0.1;
							}

							 if(((psIni->nWpoints & psIni->asSilos[3].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[4].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[5].uReadyO) > 0))
							{
								psIni->sScale2.dValue += 0.1;
							}

							 if(((psIni->nWpoints & psIni->asSilos[6].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[7].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[8].uReadyO) > 0))
							{
								psIni->sScale3.dValue += 0.1;
							}

							 if(((psIni->nWpoints & psIni->asSilos[9].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[10].uReadyO) > 0)
							 || ((psIni->nWpoints & psIni->asSilos[11].uReadyO) > 0))
							{
								psIni->sScale4.dValue += 0.1;
							}
						}
					}
				 }
				 else
				 {
					 switch(nFillCnt/10)
					 {
					 case 0: psIni->nRpoints |=  I_FILL1; break; 
					 case 1: psIni->nRpoints &= ~I_FILL1; break;
					 case 2: psIni->nRpoints |=  I_FILL2; break;
					 case 3: psIni->nRpoints &= ~I_FILL2; break;
					 case 4: psIni->nRpoints |=  I_FILL3; break;
					 case 5: psIni->nRpoints &= ~I_FILL3; break;
					 case 6: psIni->nRpoints |=  I_FILL4; break;
					 case 7: psIni->nRpoints &= ~I_FILL4; break;
					 default: nFillCnt = -1; break;
					 }
					if(pAll->eAsType == A_DEMO)
					{
						 //drops ------------------------------------------------------
						 if((psIni->nWpoints & O_DROP1) > 0)
							 psIni->sScale1.dValue += 0.1;
						 if((psIni->nWpoints & O_DROP2) > 0)
							 psIni->sScale2.dValue += 0.1;
						 if((psIni->nWpoints & O_DROP3) > 0)
							 psIni->sScale3.dValue += 0.1;
						 if((psIni->nWpoints & O_DROP4) > 0)
							 psIni->sScale4.dValue += 2.1;
						 //disch ------------------------------------------------------
						 if((psIni->nWpoints & O_DISCH1) > 0)
							 psIni->sScale1.dValue -= 0.2;
						 if((psIni->nWpoints & O_DISCH2) > 0)
							 psIni->sScale2.dValue -= 0.2;
						 if((psIni->nWpoints & O_DISCH3) > 0)
							 psIni->sScale3.dValue -= 0.2;
						 if((psIni->nWpoints & O_DISCH4) > 0)
							 psIni->sScale4.dValue -= 2.2;
					}
				 }
				 ++nFillCnt;

				Thread::Sleep(100);
			}
		}
	};
}
