#pragma once
#include "stdafx.h"

using namespace System::Windows::Forms;

#if 0
//-----------------------------------------------------------------------------
public ref class CSilo 
{
public:
	CSilo( Ops^ pOpsIn)
	{
		pOps = pOpsIn;
		psIni = pOps->psIni;

	}
	~CSilo(void)
	{
	}
private:  
	INI  *psIni;
	Ops^  pOps;
	private: As::ColorProgressBar^  scaleBar1;
private: System::Windows::Forms::Button^  readyBt1;
As::ColorProgressBar^  siloBar1;
private: System::Windows::Forms::CheckBox^  autoFall1;
private: System::Windows::Forms::Label^  flow1;
private: System::Windows::Forms::CheckBox^  checkBoxJog1;
	private: System::Windows::Forms::PictureBox^  truckPic1;
	private: System::Windows::Forms::Label^  man1;
	private: System::Windows::Forms::TextBox^  tic_num1;
	private: System::Windows::Forms::Button^  addBt1;
	private: System::Windows::Forms::Label^  trackLb1;
	private: System::Windows::Forms::Button^  dischBt1;
	private: As::ColorProgressBar^  truckBar1;
	private: System::Windows::Forms::PictureBox^  scaleOpen1;
	private: System::Windows::Forms::Label^  ticketNum1;
	private: System::Windows::Forms::Button^  nextBt1;
	private: System::Windows::Forms::Label^  dropsLb1;
	private: System::Windows::Forms::Button^  pauseBt1;
	private: System::Windows::Forms::Button^  stopBt1;
	private: System::Windows::Forms::Button^  dropBt1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  scale1;
	private: System::Windows::Forms::Label^  scaleLb1;
	private: System::Windows::Forms::Label^  matLb1;
	private: System::Windows::Forms::Label^  custLb1;
	private: System::Windows::Forms::Label^  targetLb1;
	private: System::Windows::Forms::TextBox^  customer1;
	private: System::Windows::Forms::TextBox^  Job1;
	private: System::Windows::Forms::TextBox^  target1;
	private: System::Windows::Forms::TextBox^  truck1;
	private: System::Windows::Forms::TextBox^  material1;
	private: System::Windows::Forms::Button^  autoBt1;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Windows::Forms::CheckBox^  printTarget1;
	private: System::Windows::Forms::Button^  printOnly1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::RadioButton^  drops14;
	private: System::Windows::Forms::RadioButton^  drops13;
	private: System::Windows::Forms::RadioButton^  drops12;
	private: System::Windows::Forms::RadioButton^  drops11;
	private: System::Windows::Forms::Label^  tonnage1;
	private: System::Windows::Forms::Label^  tonLb1;
	private: System::Windows::Forms::PictureBox^  siloOpen1;
private: System::Windows::Forms::Label^  flow1;
	private: System::Windows::Forms::Label^  load1;
	private: System::Windows::Forms::PictureBox^  fill1;

		// plant 1 ------------------------------------------------------------
		bool  bAuto1;
		bool  bFill1;
		bool  bFillOld1;
		bool  bScale1;		// type of display data
		bool  bFirstDrop1;	// first drop

		int	  nTmpCnt1;
		int   nBlink1;
		int   nSettle1;      // scale settle timout
		int   nFallCnt1;      // scale free fall timout

		double fTarget1;       // drop size
		double fNewTarget1;    // drop size - tare
		double fTmpScale1;    
		double fManFall1;
		double fLoad1;
		double fCumTarget1; // cumulative target
		double fTare1;

		Queue^ qJob1;
		Job^ psJob1;

	//-------------------------------------------------------------------------
private: System::Void setStateA(Astate eNew)
		 {
			 switch(psIni->sLog1.eState = eNew)
			 {
			 case S_IDLE:
				 psIni->nWpoints &= ~O_CLEAR1;
				 siloBar1->Target = 0;

				 // clear display
				 customer1->Text = nullptr;
				 Job1->Text = nullptr;
				 material1->Text = nullptr;
				 tic_num1->Text = nullptr;
				 truck1->Text = nullptr;
				 target1->Text = nullptr;
				 truckPic1->Visible = false;

				 // setup buttons
				 nextBt1->Enabled = true;		
				 nextBt1->BackColor = Color::LightSteelBlue;
				 autoBt1->Enabled = true;
				 autoBt1->BackColor = Color::WhiteSmoke;
				 printTarget1->Checked = false;

				 printOnly1->Enabled = false;
				 printOnly1->BackColor = Color::Gray;
				 readyBt1->Enabled = false;
				 readyBt1->BackColor = Color::Gray;

				 dropBt1->Enabled = false;
				 dropBt1->BackColor = Color::Gray;
				 pauseBt1->Enabled = false;
				 pauseBt1->BackColor = Color::Gray;
				 stopBt1->Enabled = false;
				 stopBt1->BackColor = Color::Gray;
				 drops11->Checked = false;
				 drops12->Checked = false;
				 drops13->Checked = false;
				 drops14->Checked = false;

				 if(!psIni->bBotScale)
				 {
					 dischBt1->Enabled = false;
					 dischBt1->BackColor = Color::Gray;		
				 }
#ifdef SIM
				 psIni->sScale1.cGo = 'I';		// idle
#endif					 
				 break;

			 case S_NEXT:
				 nextBt1->Enabled = false;
				 nextBt1->BackColor = Color::Gray;
				 autoBt1->Enabled = false;
				 autoBt1->BackColor = Color::Gray;

				 readyBt1->Enabled = true;
				 readyBt1->BackColor = Color::PaleGreen;

				 dropBt1->Enabled = false;
				 dropBt1->BackColor = Color::Gray;
				 pauseBt1->Enabled = false;
				 pauseBt1->BackColor = Color::Gray;
				 stopBt1->Enabled = false;
				 stopBt1->BackColor = Color::Gray;

				 if(!psIni->bBotScale)
				 {
					 dischBt1->Enabled = false;
					 dischBt1->BackColor = Color::Gray;		
				 }
#ifdef SIM
				 if(!psIni->bBotScale)
					 psIni->sScale1.cGo = 'I';		// idle
				 else					
					 psIni->sScale1.cGo = 'E';		// enter						 
#endif					 
				 break;

			 case S_READY:			 
				 psIni->nWpoints &= ~O_DROP1;
				 psIni->sLog1.eStop = A_NOT;
				 truckBar1->Maximum = psIni->sLog1.fTarget;

				 printOnly1->Enabled = true;
				 printOnly1->BackColor = Color::WhiteSmoke;

				 dropBt1->Enabled = true;
				 dropBt1->BackColor = Color::PaleGreen;
				 pauseBt1->Enabled = false;
				 pauseBt1->BackColor = Color::Gray;
				 stopBt1->Enabled = true;
				 stopBt1->BackColor = Color::Tomato;

				 if(!psIni->bBotScale)
				 {
					 dischBt1->Enabled = false;
					 dischBt1->BackColor = Color::Gray;							 
				 }
				 truckPic1->Visible = true;
#ifdef SIM
				 if(!psIni->bBotScale)
					 psIni->sScale1.cGo = 'I';	// idle
				 else	
					 psIni->sScale1.cGo = 'S';	// stop							 	
#endif					 
				 break;

			 case S_DROP:
				 psIni->nWpoints |= O_DROP1;

				 fTmpScale1 = psIni->sScale1.fScale;
				 nTmpCnt1 = 0;
				 nSettle1 = 0;
				 nFallCnt1 = 0;

				 dropBt1->Enabled = false;
				 dropBt1->BackColor = Color::PaleGreen;							 
				 pauseBt1->Enabled = true;
				 pauseBt1->BackColor = Color::Yellow;
				 stopBt1->Enabled = true;
				 stopBt1->BackColor = Color::Tomato;

				 if(!psIni->bBotScale)
				 {
					 dischBt1->Enabled = false;
					 dischBt1->BackColor = Color::Gray;							 
				 }
#ifdef SIM
				 psIni->sScale1.cGo = 'G';		// go	
#endif					 
				 break;

			 case S_SETTLE:
				 psIni->nWpoints &= ~O_DROP1;

				 dropBt1->Enabled = false;
				 dropBt1->BackColor = Color::YellowGreen;
#ifdef SIM
				 psIni->sScale1.cGo = 'S';		// stop	
#endif						
				 break;

			 case S_ADD:
				 fTmpScale1 = psIni->sScale1.fScale;	
				 nTmpCnt1 = 0;
				 addBt1->BackColor = Color::Green;
				 break;

			 case S_ASETTLE:
				 psIni->nWpoints &= ~O_DROP1;

				 nTmpCnt1 = 0;
				 addBt1->BackColor = Color::YellowGreen;
#ifdef SIM
				 psIni->sScale1.cGo = 'S';		// stop	
#endif						 
				 break;

			 case S_DISCH_WAIT:
				 dropBt1->BackColor = Color::Gray;
				 dischBt1->Enabled = true;
				 dischBt1->BackColor = Color::PaleGreen;	
				 break;

			 case S_DISCH:
				 psIni->nWpoints |= O_DISCH1;
				 dropBt1->BackColor = Color::Gray;
				 dischBt1->Enabled = false;
				 dischBt1->BackColor = Color::PaleGreen;	
				 pauseBt1->Enabled = true;
				 pauseBt1->BackColor = Color::Yellow;
				 nSettle1 = 0;      // scale settle timout

#ifdef SIM
				 psIni->sScale1.cGo = 'L';		// leave
#endif					

				 break;

			 case S_DSETTLE:
				 psIni->nWpoints &= ~O_DISCH1;
#ifdef SIM
				 psIni->sScale1.cGo = 'P';		// pause
#endif					 					
				 break;

			 case S_HOLD_DROP:
				 psIni->nWpoints &= ~O_DROP1;
				 dropBt1->Enabled = false;
				 dropBt1->BackColor = Color::PaleGreen;		
#ifdef SIM
				 psIni->sScale1.cGo = 'P';		// pause
#endif					 
				 break;				 

			 case S_HOLD_DISCH:
				 psIni->nWpoints &= ~O_DISCH1;

				 if(!psIni->bBotScale)
				 {
					 dischBt1->Enabled = false;
					 dischBt1->BackColor = Color::PaleGreen;							 
				 }
#ifdef SIM
				 psIni->sScale1.cGo = 'P';		// pause
#endif					 
				 break;

			 case S_UPDATE:
				 break;

			 case S_HORN:
				 psIni->nWpoints |= O_LIGHT1;
				 nTmpCnt1 = 0;
				 break;
			 }
		 }


		 //-------------------------------------------------------------------------
private:
	System::Void timer1_Tick(System::Object^  sender, ElapsedEventArgs^  e)
	{
		Dbase^ pDbase; 
		double fTarget;
#ifndef PROD
		++nFillCnt;
		if(nFillCnt < 10) psIni->nRpoints |= I_FILL1; else psIni->nRpoints &= ~I_FILL1;
		if(nFillCnt > 10 && nFillCnt < 20)psIni->nRpoints |= I_FILL2; else psIni->nRpoints &= ~I_FILL2;
		if(nFillCnt > 20) psIni->nRpoints |= I_FILL3; else psIni->nRpoints &= ~I_FILL3;
		if(nFillCnt > 30) nFillCnt = 0;
#endif

		// plant 1 ///////////////////////////////////////////////////
		switch(psIni->sLog1.eState)
		{
		case S_IDLE: 
			fTare1 = fLoad1 = 0.0;
			truckBar1->Value = 0.0;
#ifdef DEMO
			psIni->sScale1.fScale = 0.0;
#endif
			break;

		case S_NEXT:
			break;

		case S_READY:
			if(psIni->bBotScale)
				fLoad1 = psIni->sScale1.fScale - fTare1;
			break;

			//------------------------------------------------------------------------
		case S_DROP:
			// pulse drop button
			nBlink1 = ++nBlink1 & 3;
			if(nBlink1 > 1)
				dropBt1->BackColor = Color::Green;
			else
				dropBt1->BackColor = Color::PaleGreen;	
#ifdef DEMO
			psIni->sScale1.fScale += 0.1;
#endif
			if(psIni->sScale1.fScale == fTmpScale1)
				nTmpCnt1++;
			else
			{
				fTmpScale1 = psIni->sScale1.fScale;
				nTmpCnt1 = 0; 
			}

			if(!psIni->bBotScale)
			{
				if(nTmpCnt1 > psIni->nScaleIdle)
				{
					setStateA(S_HOLD_DROP);
					MessageBox::Show("Scale is IDLE, pause", "Silo 1", 
						System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			}
			else	
			{
				fLoad1 = psIni->sScale1.fScale - fTare1;
				truckBar1->Value = fLoad1; 
			}

			if(!psIni->bBotScale)
			{
				// final test
				if(psIni->sScale1.fScale > (fNewTarget1 - fManFall1))
				{
					fCumTarget1 += fTarget1;
					setStateA(S_SETTLE);
				}	
			}
			else	
			{
				// final test
				if(fLoad1 >= fCumTarget1)
					setStateA(S_SETTLE);
			}						
			break;

			//------------------------------------------------------------------------
		case S_SETTLE:
			if(nSettle1 < psIni->nScaleSettle)
				nSettle1++;
			else
			{
				if(!psIni->bBotScale)					// upper scale
				{
					// update fall diff --------------------------------
					FALL *psF = &psIni->sInv.afFall1[(int)fTarget1];
					//							 double fMan = psIni->afManFall[(int)fTarget1];
					double fFall = fManFall1 + (psIni->sScale1.fScale - fTarget1);

					psF->fFall -=  psF->afFall[psF->nIdx];
					psF->fFall += fFall;
					psF->afFall[psF->nIdx] = fFall;
					psF->nIdx = ++psF->nIdx & (FALL_NBR-1);

					flow1->Text = fFall.ToString("F2");

					//--------------------------------------------------
					fLoad1 += psIni->sScale1.fScale;
					//							 if(psIni->nAutoDisch == 1)						 
					//								 setStateA(S_DISCH);	
					//							 else
					setStateA(S_DISCH_WAIT);
				}
				else	
				{
					if(fCumTarget1 < psIni->sLog1.fTarget)
						setStateA(S_READY);
					else		
						setStateA(S_UPDATE);
				}						
			}
			break;

			//------------------------------------------------------------------------
		case S_ADD:
			if(nTmpCnt1 == 0)
			{
				psIni->nWpoints |= O_DROP1;
#ifdef SIM
				psIni->sScale1.cGo ='G';		// go
#endif						
				nTmpCnt1++;
			}
			else if(nTmpCnt1 < psIni->nScaleAdd)
				nTmpCnt1++;
			else
				setStateA(S_ASETTLE);
			break;

		case S_ASETTLE:
			if(nTmpCnt1 < psIni->nScaleSettle)
				nTmpCnt1++;
			else
			{
				fLoad1 += psIni->sScale1.fScale - fTmpScale1; 
				addBt1->Enabled = false;
				addBt1->Visible = false;
				setStateA(S_DISCH_WAIT);
			}
			break;

		case S_DISCH_WAIT:
			if(/*(psIni->nAutoDisch == 0) 
			   && */(fCumTarget1 == psIni->sLog1.fTarget)
			   && ((fLoad1 + psIni->sScale1.fTolerance) < psIni->sLog1.fTarget)
			   )
			{
				if(this->checkBoxJog1->Checked == false)
				{
					addBt1->BackColor = Color::PaleGreen;
					addBt1->Enabled = true;
					addBt1->Visible = true;
				}
				else
					setStateA(S_ADD);	
			}
			else if(psIni->nAutoDisch == 1)						 
				setStateA(S_DISCH);	
			break;

		case S_DISCH:
			// pulse
			nBlink1 = ++nBlink1 & 3;
			if(nBlink1 > 1)
				dischBt1->BackColor = Color::Green;
			else
				dischBt1->BackColor = Color::PaleGreen;	
#ifdef DEMO
			psIni->sScale1.fScale -= 0.2;
#endif
			addBt1->Enabled = false;
			addBt1->Visible = false;
			truckBar1->Value = fLoad1-psIni->sScale1.fScale;

			if(psIni->sScale1.fScale < psIni->sScale1.fTolerance)
				setStateA(S_DSETTLE);	
			break;

		case S_DSETTLE:	 
			truckBar1->Value = fLoad1-psIni->sScale1.fScale;

			if(nSettle1 > psIni->nScaleDisSettle)
			{
				if(psIni->sLog1.eStop != A_NOT)
					setStateA(S_ABORT);
				else if(fCumTarget1 < psIni->sLog1.fTarget)
					setStateA(S_READY);
				else		
					setStateA(S_UPDATE);
			}		
			else
				nSettle1++;
			break;

		case S_ABORT:
			if(!psIni->bBotScale)
			{
				fLoad1 += psIni->sScale1.fScale;
				setStateA(S_UPDATE);	
			}
			break;

		case S_UPDATE:
			psIni->sLog1.bPrintTarget = printTarget1->Checked || (psIni->sLog1.eStop == A_TARGET);

			psIni->sInv.fTon1 += fLoad1;					// update tonnage
			psIni->sInv.fInv1 -= fLoad1;					// update silo
			psIni->sLog1.eStatus |= S_LOAD;

			if(psIni->sLog1.bPrintTarget == true)
				fLoad1 = psIni->sLog1.fTarget;

			psIni->sLog1.fLoad = fLoad1;
			psIni->sLog1.fGross = fLoad1 + psIni->sLog1.fTruckTare;
			psIni->sLog1.fSubtotal = fLoad1 * psIni->sLog1.fMixPrice;
			psIni->sLog1.fLoadTax = psIni->sLog1.fSubtotal * psIni->sLog1.fTax;
			psIni->sLog1.fTotal = psIni->sLog1.fSubtotal + psIni->sLog1.fLoadTax;
			psIni->sLog1.fInventory = psIni->sInv.fInv1;

			fTarget = psIni->sLog1.fTarget * psIni->sLog1.fMixPrice;
			fTarget += fTarget * psIni->sLog1.fTax;
			psIni->sLog1.fOrderCumTotal += (psIni->sLog1.fTotal - fTarget);

			psIni->sLog1.fCumQty += psIni->sLog1.fLoad - psIni->sLog1.fTarget;

			poInv->set(&psIni->sInv);

			if(bAuto1)
			{
				pDbase = gcnew Dbase();
				pDbase->nLogIdx = psJob1->nLogIdx;
				pDbase->nPlantNumber = psJob1->nPlantNumber;
				pDbase->nTicket = psJob1->nTicket;
				pDbase->fLoad = psIni->sLog1.fLoad;
				pDbase->fTare = fTare1;
				pDbase->cUnit0 = psIni->sLog1.acUnit[0];
				pDbase->cUnit1 = psIni->sLog1.acUnit[1];
				pDbase->bVoid = (psIni->sLog1.eStatus & S_VOID) > 0;

				if(psIni->nDbaseOk > 0)
					qDbase->Enqueue(pDbase);
				else
					qDbaseBad->Enqueue(pDbase);
				psIni->sLog1.eStatus |= S_DB;
			}
			else
				psIni->nManual1++;

			poLog->printTicket(&psIni->sLog1);
			psIni->sLog1.eStatus |= S_PRINT;
			poLog->log(C_UPDATE, &psIni->sLog1, psJob1->nLogIdx);

			fLoad1 = 0.0;

			if((psIni->sLog1.eStop == A_TARGET) || (psIni->sLog1.eStop == A_VOID))
				setStateA(S_IDLE);	
			else
				setStateA(S_HORN);	 
			break;

		case S_HORN:
			if(nTmpCnt1 < psIni->nHornTime)
				++nTmpCnt1;
			else
				setStateA(S_IDLE);	 
			break;

		case S_HOLD_DROP:
		case S_HOLD_DISCH:
			// pulse
			nBlink1 = ++nBlink1 & 3;
			if(nBlink1 > 1)
				pauseBt1->BackColor = Color::Yellow;
			else
				pauseBt1->BackColor = Color::LightYellow;	
			break;

		default:							// PAUSE
			if(!psIni->bBotScale)
				fLoad1 = psIni->sScale1.fScale + fCumTarget1;
			else		
				fLoad1 = psIni->sScale1.fScale - fTare1;
			break;
		}

		//-----------------------------------------------------------
		if(bFill1 & !bFillOld1)
		{ 
			psIni->sInv.fInv1 += psIni->fSiloFill1;
		}
		bFillOld1 = bFill1;	
		siloBar1->Value = psIni->sInv.fInv1;
		siloBar1->Inventory = psIni->sInv.fInv1;

		scaleBar1->Value = psIni->sScale1.fScale;
		scaleBar1->Target = psIni->sScale1.fScale;
		if(bScale1)
			scale1->Text = gcnew String((char *)psIni->sScale1.acData);
		else
			scale1->Text = psIni->sScale1.fScale.ToString("F02");	

		load1->Text = fLoad1.ToString("F02");			
		tonnage1->Text = psIni->sInv.fTon1.ToString("F01");
		ticketNum1->Text = qJob1->Count.ToString();
		man1->Text = psIni->nManual1.ToString();

		fill1->Visible = (psIni->nRpoints & I_FILL1) > 0;
		siloOpen1->Visible = (psIni->nWpoints & O_DROP1) > 0;
		scaleOpen1->Visible = (psIni->nWpoints & O_DISCH1) > 0;
#ifndef DEMO				 
		if (psIni->sScale1.bSerial) 
			scale1->BackColor = Color::PaleGreen;
		else
			scale1->BackColor = Color::Red;	
#endif	
		}

	};
#endif