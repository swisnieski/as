#pragma once
#include "stdafx.h"
#include <string.h>

namespace As {

	using namespace System::Windows::Forms;

	//-------------------------------------------------------------------------
	void writeCfx(All^ pAllIn)
	{
		char acBufA[5000] = {0};
		char acBufB[5000] = {0};
		char acFile[80];
		FILE *pfCfg;
		All^ pAll = pAllIn;
		INI *psIni = pAll->psIni;

		int nRetA = sprintf_s(acBufA, "\
#////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\
# Silo: name, Used, flowrate1, flowrate2, flowrate3, flowrate4, delayPct, delayTime, flowrate1O, flowrate2O, flowrate3O, flowrate4O, delayO, readyO, dropO, doneO, holdO, addO, dropreadyI\n\
#/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\
silo1=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo2=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo3=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo4=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo5=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo6=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo7=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo8=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo9=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo10=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo11=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
silo12=%s,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%f,%s,\n\
pdmPlc=%c,\n\
autoAdd=%c,\n\
sendTarget=%c,\n\
sendBitWise=%c,\n\
truckMin=%d,\n\
truckMax=%d,\n\
cartMin=%d,\n\
cartMax=%d,\n\
sendTargetO=%d,\n\
receivedTargetI=%d,\n\
keepAliveO=%d,\n\
keepAliveI=%d,\n\
keepOnTime=%d,\n\
keepOffTime=%d,\n\
siloBit0=%d,\n\
siloBit1=%d,\n\
siloBit2=%d,\n\
siloBit3=%d,\n\
bitWise00=%d,\n\
bitWise01=%d,\n\
bitWise02=%d,\n\
bitWise03=%d,\n\
bitWise04=%d,\n\
bitWise05=%d,\n\
bitWise06=%d,\n\
bitWise07=%d,\n\
bitWise08=%d,\n\
bitWise09=%d,\n\
bitWise10=%d,\n\
bitWise11=%d,\n\
bitWise12=%d,\n\
bitWise13=%d,\n\
bitWise14=%d,\n\
bitWise15=%d,\n\
bitWise16=%d,\n\
bitWise17=%d,\n\
bitWise18=%d,\n\
siloCheck0=%d,\n\
siloCheck1=%d,\n\
siloCheck2=%d,\n\
siloCheck3=%d,\n\
bitCheck00=%d,\n\
bitCheck01=%d,\n\
bitCheck02=%d,\n\
bitCheck03=%d,\n\
bitCheck04=%d,\n\
bitCheck05=%d,\n\
bitCheck06=%d,\n\
bitCheck07=%d,\n\
bitCheck08=%d,\n\
bitCheck09=%d,\n\
bitCheck10=%d,\n\
bitCheck11=%d,\n\
bitCheck12=%d,\n\
bitCheck13=%d,\n\
bitCheck14=%d,\n\
bitCheck15=%d,\n\
bitCheck16=%d,\n\
bitCheck17=%d,\n\
bitCheck18=%d,\n\
laneTareI0=%d,\n\
laneTareI1=%d,\n\
laneTareI2=%d,\n\
laneTareI3=%d,\n\
#\n"
	   , psIni->asSilos[0].acMat
	   , psIni->asSilos[0].bUsed ? '1' : '0'
	   , psIni->asSilos[0].nFlowRatePct1
	   , psIni->asSilos[0].nFlowRatePct2
	   , psIni->asSilos[0].nFlowRatePct3
	   , psIni->asSilos[0].nFlowRatePct4
	   , psIni->asSilos[0].nDelayPct
	   , psIni->asSilos[0].nDelayTime
	   , psIni->asSilos[0].nFlowRate1O
	   , psIni->asSilos[0].nFlowRate2O
	   , psIni->asSilos[0].nFlowRate3O
	   , psIni->asSilos[0].nFlowRate4O
	   , psIni->asSilos[0].nDoneI
	   , psIni->asSilos[0].nReadyO
	   , psIni->asSilos[0].nDropO
	   , psIni->asSilos[0].nDoneO
	   , psIni->asSilos[0].nHoldO
	   , psIni->asSilos[0].nAddO
	   , psIni->asSilos[0].nDropReadyI
	   , psIni->asSilos[0].nHoldI
	   , psIni->asSilos[0].fFall
	   , psIni->asSilos[0].nSiloNum
	   , psIni->asSilos[0].nSiloJog
	   , psIni->asSilos[0].dAddTol
	   , psIni->asSilos[0].acProduct

	   , psIni->asSilos[1].acMat
	   , psIni->asSilos[1].bUsed ? '1' : '0'
	   , psIni->asSilos[1].nFlowRatePct1
	   , psIni->asSilos[1].nFlowRatePct2
	   , psIni->asSilos[1].nFlowRatePct3
	   , psIni->asSilos[1].nFlowRatePct4
	   , psIni->asSilos[1].nDelayPct
	   , psIni->asSilos[1].nDelayTime
	   , psIni->asSilos[1].nFlowRate1O
	   , psIni->asSilos[1].nFlowRate2O
	   , psIni->asSilos[1].nFlowRate3O
	   , psIni->asSilos[1].nFlowRate4O
	   , psIni->asSilos[1].nDoneI
	   , psIni->asSilos[1].nReadyO
	   , psIni->asSilos[1].nDropO
	   , psIni->asSilos[1].nDoneO
	   , psIni->asSilos[1].nHoldO
	   , psIni->asSilos[1].nAddO
	   , psIni->asSilos[1].nDropReadyI
	   , psIni->asSilos[1].nHoldI
	   , psIni->asSilos[1].fFall
	   , psIni->asSilos[1].nSiloNum
	   , psIni->asSilos[1].nSiloJog
	   , psIni->asSilos[1].dAddTol
	   , psIni->asSilos[1].acProduct

	   , psIni->asSilos[2].acMat
	   , psIni->asSilos[2].bUsed ? '1' : '0'
	   , psIni->asSilos[2].nFlowRatePct1
	   , psIni->asSilos[2].nFlowRatePct2
	   , psIni->asSilos[2].nFlowRatePct3
	   , psIni->asSilos[2].nFlowRatePct4
	   , psIni->asSilos[2].nDelayPct
	   , psIni->asSilos[2].nDelayTime
	   , psIni->asSilos[2].nFlowRate1O
	   , psIni->asSilos[2].nFlowRate2O
	   , psIni->asSilos[2].nFlowRate3O
	   , psIni->asSilos[2].nFlowRate4O
	   , psIni->asSilos[2].nDoneI
	   , psIni->asSilos[2].nReadyO
	   , psIni->asSilos[2].nDropO
	   , psIni->asSilos[2].nDoneO
	   , psIni->asSilos[2].nHoldO
	   , psIni->asSilos[2].nAddO
	   , psIni->asSilos[2].nDropReadyI
	   , psIni->asSilos[2].nHoldI
	   , psIni->asSilos[2].fFall
	   , psIni->asSilos[2].nSiloNum
	   , psIni->asSilos[2].nSiloJog
	   , psIni->asSilos[2].dAddTol
	   , psIni->asSilos[2].acProduct

	   , psIni->asSilos[3].acMat
	   , psIni->asSilos[3].bUsed ? '1' : '0'
	   , psIni->asSilos[3].nFlowRatePct1
	   , psIni->asSilos[3].nFlowRatePct2
	   , psIni->asSilos[3].nFlowRatePct3
	   , psIni->asSilos[3].nFlowRatePct4
	   , psIni->asSilos[3].nDelayPct
	   , psIni->asSilos[3].nDelayTime
	   , psIni->asSilos[3].nFlowRate1O
	   , psIni->asSilos[3].nFlowRate2O
	   , psIni->asSilos[3].nFlowRate3O
	   , psIni->asSilos[3].nFlowRate4O
	   , psIni->asSilos[3].nDoneI
	   , psIni->asSilos[3].nReadyO
	   , psIni->asSilos[3].nDropO
	   , psIni->asSilos[3].nDoneO
	   , psIni->asSilos[3].nHoldO
	   , psIni->asSilos[3].nAddO
	   , psIni->asSilos[3].nDropReadyI
	   , psIni->asSilos[3].nHoldI
	   , psIni->asSilos[3].fFall
	   , psIni->asSilos[3].nSiloNum
	   , psIni->asSilos[3].nSiloJog
	   , psIni->asSilos[3].dAddTol
	   , psIni->asSilos[3].acProduct

	   , psIni->asSilos[4].acMat
	   , psIni->asSilos[4].bUsed ? '1' : '0'
	   , psIni->asSilos[4].nFlowRatePct1
	   , psIni->asSilos[4].nFlowRatePct2
	   , psIni->asSilos[4].nFlowRatePct3
	   , psIni->asSilos[4].nFlowRatePct4
	   , psIni->asSilos[4].nDelayPct
	   , psIni->asSilos[4].nDelayTime
	   , psIni->asSilos[4].nFlowRate1O
	   , psIni->asSilos[4].nFlowRate2O
	   , psIni->asSilos[4].nFlowRate3O
	   , psIni->asSilos[4].nFlowRate4O
	   , psIni->asSilos[4].nDoneI
	   , psIni->asSilos[4].nReadyO
	   , psIni->asSilos[4].nDropO
	   , psIni->asSilos[4].nDoneO
	   , psIni->asSilos[4].nHoldO
	   , psIni->asSilos[4].nAddO
	   , psIni->asSilos[4].nDropReadyI
	   , psIni->asSilos[4].nHoldI
	   , psIni->asSilos[4].fFall
	   , psIni->asSilos[4].nSiloNum
	   , psIni->asSilos[4].nSiloJog
	   , psIni->asSilos[4].dAddTol
	   , psIni->asSilos[4].acProduct

	   , psIni->asSilos[5].acMat
	   , psIni->asSilos[5].bUsed ? '1' : '0'
	   , psIni->asSilos[5].nFlowRatePct1
	   , psIni->asSilos[5].nFlowRatePct2
	   , psIni->asSilos[5].nFlowRatePct3
	   , psIni->asSilos[5].nFlowRatePct4
	   , psIni->asSilos[5].nDelayPct
	   , psIni->asSilos[5].nDelayTime
	   , psIni->asSilos[5].nFlowRate1O
	   , psIni->asSilos[5].nFlowRate2O
	   , psIni->asSilos[5].nFlowRate3O
	   , psIni->asSilos[5].nFlowRate4O
	   , psIni->asSilos[5].nDoneI
	   , psIni->asSilos[5].nReadyO
	   , psIni->asSilos[5].nDropO
	   , psIni->asSilos[5].nDoneO
	   , psIni->asSilos[5].nHoldO
	   , psIni->asSilos[5].nAddO
	   , psIni->asSilos[5].nDropReadyI
	   , psIni->asSilos[5].nHoldI
	   , psIni->asSilos[5].fFall
	   , psIni->asSilos[5].nSiloNum
	   , psIni->asSilos[5].nSiloJog
	   , psIni->asSilos[5].dAddTol
	   , psIni->asSilos[5].acProduct

	   , psIni->asSilos[6].acMat
	   , psIni->asSilos[6].bUsed ? '1' : '0'
	   , psIni->asSilos[6].nFlowRatePct1
	   , psIni->asSilos[6].nFlowRatePct2
	   , psIni->asSilos[6].nFlowRatePct3
	   , psIni->asSilos[6].nFlowRatePct4
	   , psIni->asSilos[6].nDelayPct
	   , psIni->asSilos[6].nDelayTime
	   , psIni->asSilos[6].nFlowRate1O
	   , psIni->asSilos[6].nFlowRate2O
	   , psIni->asSilos[6].nFlowRate3O
	   , psIni->asSilos[6].nFlowRate4O
	   , psIni->asSilos[6].nDoneI
	   , psIni->asSilos[6].nReadyO
	   , psIni->asSilos[6].nDropO
	   , psIni->asSilos[6].nDoneO
	   , psIni->asSilos[6].nHoldO
	   , psIni->asSilos[6].nAddO
	   , psIni->asSilos[6].nDropReadyI
	   , psIni->asSilos[6].nHoldI
	   , psIni->asSilos[6].fFall
	   , psIni->asSilos[6].nSiloNum
	   , psIni->asSilos[6].nSiloJog
	   , psIni->asSilos[6].dAddTol
	   , psIni->asSilos[6].acProduct

	   , psIni->asSilos[7].acMat
	   , psIni->asSilos[7].bUsed ? '1' : '0'
	   , psIni->asSilos[7].nFlowRatePct1
	   , psIni->asSilos[7].nFlowRatePct2
	   , psIni->asSilos[7].nFlowRatePct3
	   , psIni->asSilos[7].nFlowRatePct4
	   , psIni->asSilos[7].nDelayPct
	   , psIni->asSilos[7].nDelayTime
	   , psIni->asSilos[7].nFlowRate1O
	   , psIni->asSilos[7].nFlowRate2O
	   , psIni->asSilos[7].nFlowRate3O
	   , psIni->asSilos[7].nFlowRate4O
	   , psIni->asSilos[7].nDoneI
	   , psIni->asSilos[7].nReadyO
	   , psIni->asSilos[7].nDropO
	   , psIni->asSilos[7].nDoneO
	   , psIni->asSilos[7].nHoldO
	   , psIni->asSilos[7].nAddO
	   , psIni->asSilos[7].nDropReadyI
	   , psIni->asSilos[7].nHoldI
	   , psIni->asSilos[7].fFall
	   , psIni->asSilos[7].nSiloNum
	   , psIni->asSilos[7].nSiloJog
	   , psIni->asSilos[7].dAddTol
	   , psIni->asSilos[7].acProduct

	   , psIni->asSilos[8].acMat
	   , psIni->asSilos[8].bUsed ? '1' : '0'
	   , psIni->asSilos[8].nFlowRatePct1
	   , psIni->asSilos[8].nFlowRatePct2
	   , psIni->asSilos[8].nFlowRatePct3
	   , psIni->asSilos[8].nFlowRatePct4
	   , psIni->asSilos[8].nDelayPct
	   , psIni->asSilos[8].nDelayTime
	   , psIni->asSilos[8].nFlowRate1O
	   , psIni->asSilos[8].nFlowRate2O
	   , psIni->asSilos[8].nFlowRate3O
	   , psIni->asSilos[8].nFlowRate4O
	   , psIni->asSilos[8].nDoneI
	   , psIni->asSilos[8].nReadyO
	   , psIni->asSilos[8].nDropO
	   , psIni->asSilos[8].nDoneO
	   , psIni->asSilos[8].nHoldO
	   , psIni->asSilos[8].nAddO
	   , psIni->asSilos[8].nDropReadyI
	   , psIni->asSilos[8].nHoldI
	   , psIni->asSilos[8].fFall
	   , psIni->asSilos[8].nSiloNum
	   , psIni->asSilos[8].nSiloJog
	   , psIni->asSilos[8].dAddTol
	   , psIni->asSilos[8].acProduct

	   , psIni->asSilos[9].acMat
	   , psIni->asSilos[9].bUsed ? '1' : '0'
	   , psIni->asSilos[9].nFlowRatePct1
	   , psIni->asSilos[9].nFlowRatePct2
	   , psIni->asSilos[9].nFlowRatePct3
	   , psIni->asSilos[9].nFlowRatePct4
	   , psIni->asSilos[9].nDelayPct
	   , psIni->asSilos[9].nDelayTime
	   , psIni->asSilos[9].nFlowRate1O
	   , psIni->asSilos[9].nFlowRate2O
	   , psIni->asSilos[9].nFlowRate3O
	   , psIni->asSilos[9].nFlowRate4O
	   , psIni->asSilos[9].nDoneI
	   , psIni->asSilos[9].nReadyO
	   , psIni->asSilos[9].nDropO
	   , psIni->asSilos[9].nDoneO
	   , psIni->asSilos[9].nHoldO
	   , psIni->asSilos[9].nAddO
	   , psIni->asSilos[9].nDropReadyI
	   , psIni->asSilos[9].nHoldI
	   , psIni->asSilos[9].fFall
	   , psIni->asSilos[9].nSiloNum
	   , psIni->asSilos[9].nSiloJog
	   , psIni->asSilos[9].dAddTol
	   , psIni->asSilos[9].acProduct

	   , psIni->asSilos[10].acMat
	   , psIni->asSilos[10].bUsed ? '1' : '0'
	   , psIni->asSilos[10].nFlowRatePct1
	   , psIni->asSilos[10].nFlowRatePct2
	   , psIni->asSilos[10].nFlowRatePct3
	   , psIni->asSilos[10].nFlowRatePct4
	   , psIni->asSilos[10].nDelayPct
	   , psIni->asSilos[10].nDelayTime
	   , psIni->asSilos[10].nFlowRate1O
	   , psIni->asSilos[10].nFlowRate2O
	   , psIni->asSilos[10].nFlowRate3O
	   , psIni->asSilos[10].nFlowRate4O
	   , psIni->asSilos[10].nDoneI
	   , psIni->asSilos[10].nReadyO
	   , psIni->asSilos[10].nDropO
	   , psIni->asSilos[10].nDoneO
	   , psIni->asSilos[10].nHoldO
	   , psIni->asSilos[10].nAddO
	   , psIni->asSilos[10].nDropReadyI
	   , psIni->asSilos[10].nHoldI
	   , psIni->asSilos[10].fFall
	   , psIni->asSilos[10].nSiloNum
	   , psIni->asSilos[10].nSiloJog
	   , psIni->asSilos[10].dAddTol
	   , psIni->asSilos[10].acProduct

	   , psIni->asSilos[11].acMat
	   , psIni->asSilos[11].bUsed ? '1' : '0'
	   , psIni->asSilos[11].nFlowRatePct1
	   , psIni->asSilos[11].nFlowRatePct2
	   , psIni->asSilos[11].nFlowRatePct3
	   , psIni->asSilos[11].nFlowRatePct4
	   , psIni->asSilos[11].nDelayPct
	   , psIni->asSilos[11].nDelayTime
	   , psIni->asSilos[11].nFlowRate1O
	   , psIni->asSilos[11].nFlowRate2O
	   , psIni->asSilos[11].nFlowRate3O
	   , psIni->asSilos[11].nFlowRate4O
	   , psIni->asSilos[11].nDoneI
	   , psIni->asSilos[11].nReadyO
	   , psIni->asSilos[11].nDropO
	   , psIni->asSilos[11].nDoneO
	   , psIni->asSilos[11].nHoldO
	   , psIni->asSilos[11].nAddO
	   , psIni->asSilos[11].nDropReadyI
	   , psIni->asSilos[11].nHoldI
	   , psIni->asSilos[11].fFall
	   , psIni->asSilos[11].nSiloNum
	   , psIni->asSilos[11].nSiloJog
	   , psIni->asSilos[11].dAddTol
	   , psIni->asSilos[11].acProduct

	   , psIni->bPdmPlc ? '1' : '0'
	   , psIni->bAutoAdd ? '1' : '0'
	   , psIni->bSendTarget ? '1' : '0'
	   , psIni->bSendBitWise ? '1' : '0'
	   , psIni->nTruckMin
	   , psIni->nTruckMax
	   , psIni->nCartMin
	   , psIni->nCartMax
	   , psIni->nSendTargetO
	   , psIni->nReceivedTargetI
	   , psIni->nKeepAliveO
	   , psIni->nKeepAliveI
	   , psIni->nKeepOnTime
	   , psIni->nKeepOffTime

	   , psIni->nSiloBit[0]
	   , psIni->nSiloBit[1]
	   , psIni->nSiloBit[2]
	   , psIni->nSiloBit[3]

	   , psIni->nBitWise[0]
	   , psIni->nBitWise[1]
	   , psIni->nBitWise[2]
	   , psIni->nBitWise[3]
	   , psIni->nBitWise[4]
	   , psIni->nBitWise[5]
	   , psIni->nBitWise[6]
	   , psIni->nBitWise[7]
	   , psIni->nBitWise[8]
	   , psIni->nBitWise[9]
	   , psIni->nBitWise[10]
	   , psIni->nBitWise[11]
	   , psIni->nBitWise[12]
	   , psIni->nBitWise[13]
	   , psIni->nBitWise[14]
	   , psIni->nBitWise[15]
	   , psIni->nBitWise[16]
	   , psIni->nBitWise[17]
	   , psIni->nBitWise[18]

	   ,psIni->nSiloBitCheck[0]
	   ,psIni->nSiloBitCheck[1]
	   ,psIni->nSiloBitCheck[2]
	   ,psIni->nSiloBitCheck[3]

	   , psIni->nBitCheckI[0]
	   , psIni->nBitCheckI[1]
	   , psIni->nBitCheckI[2]
	   , psIni->nBitCheckI[3]
	   , psIni->nBitCheckI[4]
	   , psIni->nBitCheckI[5]
	   , psIni->nBitCheckI[6]
	   , psIni->nBitCheckI[7]
	   , psIni->nBitCheckI[8]
	   , psIni->nBitCheckI[9]
	   , psIni->nBitCheckI[10]
	   , psIni->nBitCheckI[11]
	   , psIni->nBitCheckI[12]
	   , psIni->nBitCheckI[13]
	   , psIni->nBitCheckI[14]
	   , psIni->nBitCheckI[15]
	   , psIni->nBitCheckI[16]
	   , psIni->nBitCheckI[17]
	   , psIni->nBitCheckI[18]

	   , psIni->nLaneTareI[0]
	   , psIni->nLaneTareI[1]
	   , psIni->nLaneTareI[2]
	   , psIni->nLaneTareI[3]
	   );

	   // save file -------------------------------------------------------------
		strcpy_s(acFile, 80, pAll->pcPath);
		strcat_s(acFile, 80, "as.cfx");

	   if(nRetA <= 0)
	   {
		   MessageBox::Show(gcnew String(acFile)
			, "sprintf ERROR "+nRetA.ToString()
			, MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
	   }

		if(fopen_s(&pfCfg, acFile, "w") == 0)
		{
			fwrite(acBufA, strlen(acBufA), 1, pfCfg);
			fclose(pfCfg);
		}
		else
			MessageBox::Show(gcnew String(acFile), "Write ERROR"
			, MessageBoxButtons::OK
			, MessageBoxIcon::Error);

	}

}