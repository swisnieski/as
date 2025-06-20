#pragma once

#include "stdafx.h"
//#include "About.h"
#include "InvForm.h"
#include "StopForm.h"
//#include "TruckFm.h"
#include "FallFm.h"
#include "ReprintF.h"
#include "Log.h"
#include "IOForm.h"
#include "CfgForm.h"
#include <sys/stat.h>		//DC 4.0.8
#include <stdio.h>			//DC 4.0.8
#include <string.h>			//DC 4.0.8
#include "ClinkT.h"			//DC 4.1.0
#include <time.h>			//Dc 4.1.1
#include "DbaseT.h"

namespace As
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	//using namespace System::Data;
	//using namespace System::Data::Odbc;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Timers;
	using namespace System::IO::Ports;
	using namespace Runtime::InteropServices;

#define BAR 434
#define PIC 464
#define SCL 520

#pragma region Constructor
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	/// 
	/// 


	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(All^ pAllIn, FILE *pfInvIn)
		{
			InitializeComponent();
			//
			// constructor code here
			//
			pAll = pAllIn;
			psIni = pAll->psIni;
			pfInv = pfInvIn;
			poLog = gcnew CLog(pAll);

			System::Collections::Generic::Queue<Dbase^>^ qDbase;	//DC 4.0.2//Queue^ qDbase;
			System::Collections::Generic::Queue<Dbase^>^ qDbaseBad;	//DC 4.0.2//Queue^ qDbase;


			if (pAll->eAsType == A_REMOTE)	//DC 4.1.0
			{
				this->remLoginBt->Enabled = true;
				this->remLoginBt->Visible = true;
				this->remLoginBt->Location = System::Drawing::Point(599, 585);
				ipAddressLb->Text = pAll->pRem->pIp->ToString() + ":" + pAll->pRem->nPort.ToString();
				ipAddressLb->Visible = true;
				clinkLb->Visible = true;
			}
			else
				clinkLb->Visible = pAll->psIni->nRlinkPort > 0;	//DC 4.1.0 show remote ok LB

			truckBindingSource->DataSource = pAll->lTruck;
			jobBindingSource->DataSource = pAll->lJob;
			oldBindingSource->DataSource = pAll->lOld;

			COL_IDLE = System::Drawing::Color::WhiteSmoke;
			COL_CHARGE = System::Drawing::Color::LightBlue;
			COL_DISCH = System::Drawing::Color::PaleGreen;
			COL_SETTLE = System::Drawing::Color::Green;
			COL_HOLD = System::Drawing::Color::Yellow;
			COL_HOLDK = System::Drawing::Color::Gold;
			COL_TRANS = System::Drawing::Color::Transparent;
			COL_ERR = System::Drawing::Color::Red;

			COL_PGREEN = System::Drawing::Color::PaleGreen;
			COL_GREEN = System::Drawing::Color::Green;
			COL_LSB = System::Drawing::Color::LightSteelBlue;
			COL_LB = System::Drawing::Color::LightBlue;
			COL_W = System::Drawing::Color::White;
			COL_WS = System::Drawing::Color::WhiteSmoke;
			COL_R = System::Drawing::Color::Red;
			COL_YG = System::Drawing::Color::YellowGreen;
			COL_DG = System::Drawing::Color::DarkGray;
			COL_G = System::Drawing::Color::Gainsboro;
			COL_B = System::Drawing::Color::Blue;

			// queues ---------------------------------------------------------
			qDbase = pAll->qDbase;
			qDbaseBad = pAll->qDbaseBad;

			//			autoEvent = gcnew AutoResetEvent( false );
			//			b485Ok = true;
			nSplash = SPLASH;

			nOffs1 = 12;
			nOffs2 = 112;
			nOffs3 = 212;
			nOffs4 = 312;		//DC 3.3.0
								//DC 3.2.0			
			this->siloBar1->ScaleInLB = psIni->bScaleInLB;
			this->siloBar12->ScaleInLB = psIni->bScaleInLB;
			this->siloBar13->ScaleInLB = psIni->bScaleInLB;
			this->siloBar14->ScaleInLB = psIni->bScaleInLB;		//DC 4.2.0
			this->siloBar2->ScaleInLB = psIni->bScaleInLB;
			this->siloBar22->ScaleInLB = psIni->bScaleInLB;
			this->siloBar23->ScaleInLB = psIni->bScaleInLB;
			this->siloBar24->ScaleInLB = psIni->bScaleInLB;		//DC 4.2.0
			this->siloBar3->ScaleInLB = psIni->bScaleInLB;
			this->siloBar32->ScaleInLB = psIni->bScaleInLB;
			this->siloBar33->ScaleInLB = psIni->bScaleInLB;
			this->siloBar4->ScaleInLB = psIni->bScaleInLB;		//DC 3.3.0
			this->siloBar42->ScaleInLB = psIni->bScaleInLB;
			this->siloBar43->ScaleInLB = psIni->bScaleInLB;
			this->scaleBar1->ScaleInLB = psIni->bScaleInLB;
			this->scaleBar2->ScaleInLB = psIni->bScaleInLB;
			this->scaleBar3->ScaleInLB = psIni->bScaleInLB;
			this->scaleBar4->ScaleInLB = psIni->bScaleInLB;
			this->truckBar1->ScaleInLB = psIni->bScaleInLB;
			this->truckBar2->ScaleInLB = psIni->bScaleInLB;
			this->truckBar3->ScaleInLB = psIni->bScaleInLB;
			this->truckBar4->ScaleInLB = psIni->bScaleInLB;
			if (psIni->bScaleInLB)
			{
				this->label11->Text = L"Today\'s\r\nTotal LB";
				this->tonLb1->Text = L"Today\'s\r\nTotal LB";
				this->label9->Text = L"Today\'s\r\nTotal LB";
			}

			if (psIni->bRevPlant)
			{
				this->groupBox1->Location = System::Drawing::Point(860, 27);
				this->groupBox3->Location = System::Drawing::Point(8, 27);

				if (psIni->bBotScale)
				{
					//A
					this->siloBar13->Location = System::Drawing::Point(10, 196);
					this->siloBar1->Location = System::Drawing::Point(210, 196);

					this->safe3->Location = System::Drawing::Point(50, 190);
					this->safe1->Location = System::Drawing::Point(250, 190);

					this->fill13->Location = System::Drawing::Point(70, 190);
					this->fill1->Location = System::Drawing::Point(270, 190);

					//B
					this->siloBar23->Location = System::Drawing::Point(10, 196);
					this->siloBar2->Location = System::Drawing::Point(210, 196);

					this->safe6->Location = System::Drawing::Point(50, 190);
					this->safe4->Location = System::Drawing::Point(250, 190);

					this->fill23->Location = System::Drawing::Point(70, 190);
					this->fill2->Location = System::Drawing::Point(270, 190);

					//C
					this->siloBar33->Location = System::Drawing::Point(10, 196);
					this->siloBar3->Location = System::Drawing::Point(210, 196);

					this->safe9->Location = System::Drawing::Point(50, 190);
					this->safe7->Location = System::Drawing::Point(250, 190);

					this->fill33->Location = System::Drawing::Point(70, 190);
					this->fill3->Location = System::Drawing::Point(270, 190);
				}
				else
				{
					this->siloBar2->Number = 2;
					this->siloBar3->Number = 3;
				}
				nOffs1 = 212;
				nOffs3 = 12;

				this->testBox->Location = System::Drawing::Point(8, 30);
			}

			//-----------------------------------------------------------------
			if (psIni->bBotScale)
			{
				this->truckBar1->Location = System::Drawing::Point(nOffs1, BAR);
				this->truckBar2->Location = System::Drawing::Point(nOffs2, BAR);
				this->truckBar3->Location = System::Drawing::Point(nOffs3, BAR);
				this->truckBar4->Location = System::Drawing::Point(nOffs4, BAR);

				this->truckPic1->Location = System::Drawing::Point(nOffs1, PIC);
				this->truckPic2->Location = System::Drawing::Point(nOffs2, PIC);
				this->truckPic3->Location = System::Drawing::Point(nOffs3, PIC);
				this->truckPic4->Location = System::Drawing::Point(nOffs4, PIC);

				this->scaleBar1->Location = System::Drawing::Point(15, SCL);
				this->scaleBar2->Location = System::Drawing::Point(15, SCL);
				this->scaleBar3->Location = System::Drawing::Point(15, SCL);
				this->scaleBar4->Location = System::Drawing::Point(15, SCL);

				this->scaleBar1->Size = System::Drawing::Size(270, 58);
				this->scaleBar2->Size = System::Drawing::Size(270, 58);
				this->scaleBar3->Size = System::Drawing::Size(270, 58);
				this->scaleBar4->Size = System::Drawing::Size(270, 58);

				psIni->sInv.bAutoDisch1 = true;
				psIni->sInv.bAutoDisch2 = true;
				psIni->sInv.bAutoDisch3 = true;
				psIni->sInv.bAutoDisch4 = true;

				//				zoom1->Visible = pAll->pCam1 || pAll->pCam2 || pAll->pCam3;
				//				zoom2->Visible = pAll->pCam4 || pAll->pCam5 || pAll->pCam6;
				//				zoom3->Visible = false;
			}
			else
			{
				autoDisch1->Visible = true;
				autoDisch2->Visible = true;
				autoDisch3->Visible = true;
				autoDisch4->Visible = true;

				dischBt1->Visible = !psIni->sInv.bAutoDisch1;
				dischBt2->Visible = !psIni->sInv.bAutoDisch2;
				dischBt3->Visible = !psIni->sInv.bAutoDisch3;
				dischBt4->Visible = !psIni->sInv.bAutoDisch4;

				//				zoom1->Visible = pAll->pCam1 != nullptr;
				//				zoom2->Visible = pAll->pCam2 != nullptr;
				//				zoom3->Visible = pAll->pCam3 != nullptr;

				nJogA = psIni->nSiloJog1;
				nJogB = psIni->nSiloJog2;
				nJogC = psIni->nSiloJog3;
				nJogD = psIni->nSiloJog4;
			}
			// adjust form size -----------------------------------------------
			if (psIni->nNumLanes < 4)
			{
				this->Width = 1290;			//DC 3.2.6
				pictureSplash->Location = System::Drawing::Point(220, 200);

				groupBox4->Visible = false;
				zoom4->Visible = false;
				lite4->Visible = false;
				webBrowser4->Visible = false;
				printerLb4->Visible = false;	//DC 4.0.0
			}

			if (psIni->nNumLanes < 3)
			{
				//DC 4.0.0				this->Width = 860;			//DC 3.2.6
				//DC 4.0.0				pictureSplash->Location = System::Drawing::Point(1, 200);

				groupBox3->Visible = false;
				zoom3->Visible = false;
				lite3->Visible = false;
				webBrowser3->Visible = false;
				printerLb3->Visible = false;	//DC 4.0.0
			}
			if (psIni->nNumLanes < 2)
			{
				groupBox2->Visible = false;
				zoom2->Visible = false;
				lite2->Visible = false;
				webBrowser2->Visible = false;
				printerLb2->Visible = false;	//DC 4.0.0
			}

			//DC 4.0.3 ---- assign number to silos
			siloBar1->Number = psIni->asSilos[0].nSiloNum;
			siloBar12->Number = psIni->asSilos[1].nSiloNum;
			siloBar13->Number = psIni->asSilos[2].nSiloNum;

			siloBar2->Number = psIni->asSilos[3].nSiloNum;
			siloBar22->Number = psIni->asSilos[4].nSiloNum;
			siloBar23->Number = psIni->asSilos[5].nSiloNum;

			siloBar3->Number = psIni->asSilos[6].nSiloNum;
			siloBar32->Number = psIni->asSilos[7].nSiloNum;
			siloBar33->Number = psIni->asSilos[8].nSiloNum;

			siloBar4->Number = psIni->asSilos[9].nSiloNum;
			siloBar42->Number = psIni->asSilos[10].nSiloNum;
			siloBar43->Number = psIni->asSilos[11].nSiloNum;

			//DC 4.0.10 Disable Lanes -----------------------------------------
			if (psIni->nL1SilosNum == 0)
			{
				groupBox1->Visible = false;
				zoom1->Visible = false;
				lite1->Visible = false;
				webBrowser1->Visible = false;
				printerLb1->Visible = false;	//DC 4.0.0
				copyLane1Lb->Visible = false;
			}

			if (psIni->nL2SilosNum == 0)
			{
				groupBox2->Visible = false;
				zoom2->Visible = false;
				lite2->Visible = false;
				webBrowser2->Visible = false;
				printerLb2->Visible = false;	//DC 4.0.0
				copyLane2Lb->Visible = false;
			}

			if (psIni->nL3SilosNum == 0)
			{
				groupBox3->Visible = false;
				zoom3->Visible = false;
				lite3->Visible = false;
				webBrowser3->Visible = false;
				printerLb3->Visible = false;	//DC 4.0.0
				copyLane3Lb->Visible = false;
			}

			if (psIni->nL1SilosNum == 4)	//DC 4.1.2
			{
				groupBox1->Size = System::Drawing::Size(520, 840);
				gBoxLine1->Location = System::Drawing::Point(415, 4);
				siloBar14->Visible = true;
				siloBar14->Location = System::Drawing::Point(310, 196);
				scaleBar1->Size = System::Drawing::Size(370, 58);
			}

			if (psIni->nL1SilosNum == 0 && psIni->nL2SilosNum == 0 && psIni->nL3SilosNum == 0)
			{
				groupBox4->Location = System::Drawing::Point(435, 27);
				this->Width = 1290;			//DC 3.2.6
				pictureSplash->Location = System::Drawing::Point(220, 200);
				//pictureSplash->BringToFront();
			}

			// plant 1 --------------------------------------------------------

			if (pAll->eAsType == A_DEMO)
				psIni->sScale1.cGo = '0';			// idle

			if (psIni->bUseTrkMax)					//DC 3.2.0
				this->targetLb1->Text = L"TrkMax(TN)";

			siloBar1->Maximum = psIni->fSiloMax1;
			siloBar1->DisableInv = psIni->bDisableInv;		//DC 4.0.1
			siloBar1->Inventory = psIni->sInv.fInv1;
			siloBar1->Value = psIni->sInv.fInv1;

			numCopy1->Value = pAll->nTicketCopy1;			//DC 4.0.2

			if (psIni->bBotScale)
			{
				if (psIni->nL1SilosNum > 1)
				{
					siloBar12->Maximum = psIni->fSiloMax2;
					siloBar12->Visible = true;
					siloBar12->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar12->Inventory = psIni->fSiloMax2 > 0 ? psIni->sInv.fInv2 : 0;
					siloBar12->Enabled = psIni->fSiloMax2 > 0;
					//			siloBar12->Idle = psIni->fSiloMax2 == 0;
					siloBar12_Click(nullptr, nullptr);
				}
				if (psIni->nL1SilosNum > 2)
				{
					siloBar13->Maximum = psIni->fSiloMax3;
					siloBar13->Visible = true;
					siloBar13->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar13->Inventory = psIni->fSiloMax3 > 0 ? psIni->sInv.fInv3 : 0;
					siloBar13->Enabled = psIni->fSiloMax3 > 0;
					//			siloBar13->Idle = psIni->fSiloMax3 == 0;
					siloBar13_Click(nullptr, nullptr);
				}
			}
			else
			{
				siloBar1->Size = System::Drawing::Size(100, 230);
				scaleBar1->Size = System::Drawing::Size(100, 52);
				truckBar1->Size = System::Drawing::Size(100, 28);
			}
			tonnage1->Text = psIni->sInv.fTon1.ToString("F01");
			scaleBar1->Maximum = psIni->bBotScale ? psIni->fBotScaleMax : psIni->fTopScaleMax;

			siloBar1_Click(nullptr, nullptr);

			//			printTarget1->Checked = psIni->sInv.bPrintTarget1;
			autoFall1->Checked = psIni->sInv.bAutoFall1;
			adapt1->Checked = psIni->sInv.bAdapt1;
			jog1->Checked = psIni->sInv.bJog1;
			addBt1->Visible = !psIni->sInv.bJog1;
			autoDisch1->Checked = psIni->sInv.bAutoDisch1;

			if (pAll->pCam1 != nullptr)
			{
				webBrowser1->Visible = true;
				webBrowser1->Navigate(pAll->pCam1);
			}

			// plant 2 --------------------------------------------------------
			bSecond = psIni->nNumLanes > 1 && psIni->nL2SilosNum != 0;	//DC 4.0.10

			if (bSecond)
			{
				if (pAll->eAsType == A_DEMO)
					psIni->sScale2.cGo = '0';			// idle

				groupBox2->Visible = bSecond;

				if (psIni->bUseTrkMax)					//DC 3.2.0
					this->targetLb2->Text = L"TrkMax(TN)";

				numCopy2->Value = pAll->nTicketCopy2;			//DC 4.0.2

				if (psIni->bBotScale)
				{
					siloBar2->Maximum = psIni->fSiloMax4;
					siloBar2->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar2->Inventory = psIni->sInv.fInv4;
					siloBar2->Value = psIni->sInv.fInv4;
					if (psIni->nL2SilosNum > 1)
					{
						siloBar22->Maximum = psIni->fSiloMax5;
						siloBar22->Visible = true;
						siloBar22->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar22->Inventory = psIni->fSiloMax5 > 0 ? psIni->sInv.fInv5 : 0;
						siloBar22->Enabled = psIni->fSiloMax5 > 0;
						//				siloBar22->Idle = psIni->fSiloMax5 == 0;
						siloBar22_Click(nullptr, nullptr);
					}
					if (psIni->nL2SilosNum > 2)
					{
						siloBar23->Maximum = psIni->fSiloMax6;
						siloBar23->Visible = true;
						siloBar23->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar23->Inventory = psIni->fSiloMax6 > 0 ? psIni->sInv.fInv6 : 0;
						siloBar23->Enabled = psIni->fSiloMax6 > 0;
						//				siloBar23->Idle = psIni->fSiloMax6 == 0;
						siloBar23_Click(nullptr, nullptr);
					}

					scaleBar2->Maximum = psIni->fBotScaleMaxL2;		//DC 4.1.2

					if (pAll->pCam4 != nullptr)
					{
						webBrowser2->Visible = true;
						webBrowser2->Navigate(pAll->pCam4);
					}
				}
				else
				{
					siloBar2->Text = "Silo 2";
					siloBar2->Maximum = psIni->fSiloMax2;
					siloBar2->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar2->Inventory = psIni->sInv.fInv2;
					siloBar2->Value = psIni->sInv.fInv2;

					siloBar2->Size = System::Drawing::Size(100, 230);
					scaleBar2->Size = System::Drawing::Size(100, 52);
					truckBar2->Size = System::Drawing::Size(100, 28);

					scaleBar2->Maximum = psIni->fTopScaleMax;

					if (pAll->pCam2 != nullptr)
					{
						webBrowser2->Visible = true;
						webBrowser2->Navigate(pAll->pCam2);
					}
				}
				tonnage2->Text = psIni->sInv.fTon2.ToString("F01");
				siloBar2_Click(nullptr, nullptr);

				//			printTarget2->Checked = psIni->sInv.bPrintTarget2;
				autoFall2->Checked = psIni->sInv.bAutoFall2;
				adapt2->Checked = psIni->sInv.bAdapt2;
				jog2->Checked = psIni->sInv.bJog2;
				addBt2->Visible = !psIni->sInv.bJog2;
				autoDisch2->Checked = psIni->sInv.bAutoDisch2;
			}

			// plant 3 --------------------------------------------------------
			bThird = psIni->nNumLanes > 2 && psIni->nL3SilosNum != 0;	//DC 4.0.10

			if (bThird)
			{
				if (pAll->eAsType == A_DEMO)
					psIni->sScale3.cGo = '0';			// idle

				groupBox3->Visible = bThird;

				if (psIni->bUseTrkMax)					//DC 3.2.0
					this->targetLb3->Text = L"TrkMax(TN)";

				numCopy3->Value = pAll->nTicketCopy3;			//DC 4.0.2

				if (psIni->bBotScale)
				{
					siloBar3->Maximum = psIni->fSiloMax7;
					siloBar3->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar3->Inventory = psIni->sInv.fInv7;
					siloBar3->Value = psIni->sInv.fInv7;
					if (psIni->nL3SilosNum > 1)
					{
						siloBar32->Maximum = psIni->fSiloMax8;
						siloBar32->Visible = true;
						siloBar32->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar32->Inventory = psIni->fSiloMax8 > 0 ? psIni->sInv.fInv8 : 0;
						siloBar32->Enabled = psIni->fSiloMax8 > 0;
						//				siloBar32->Idle = psIni->fSiloMax8 == 0;
						siloBar32_Click(nullptr, nullptr);
					}
					if (psIni->nL3SilosNum > 2)
					{
						siloBar33->Maximum = psIni->fSiloMax9;
						siloBar33->Visible = true;
						siloBar33->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar33->Inventory = psIni->fSiloMax9 > 0 ? psIni->sInv.fInv9 : 0;
						siloBar33->Enabled = psIni->fSiloMax9 > 0;
						//				siloBar33->Idle = psIni->fSiloMax9 == 0;
						siloBar33_Click(nullptr, nullptr);
					}

					scaleBar3->Maximum = psIni->fBotScaleMaxL3;		//DC 7.1.2
				}
				else
				{
					siloBar3->Text = "Silo 3";
					siloBar3->Maximum = psIni->fSiloMax3;
					siloBar3->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar3->Inventory = psIni->sInv.fInv3;
					siloBar3->Value = psIni->sInv.fInv3;

					siloBar3->Size = System::Drawing::Size(100, 230);
					scaleBar3->Size = System::Drawing::Size(100, 52);
					truckBar3->Size = System::Drawing::Size(100, 28);
					scaleBar3->Maximum = psIni->fTopScaleMax;

					if (pAll->pCam3 != nullptr)
					{
						webBrowser3->Visible = true;
						webBrowser3->Navigate(pAll->pCam3);
					}
				}
				tonnage3->Text = psIni->sInv.fTon3.ToString("F01");
				siloBar3_Click(nullptr, nullptr);

				//			printTarget3->Checked = psIni->sInv.bPrintTarget3;
				autoFall3->Checked = psIni->sInv.bAutoFall3;
				adapt3->Checked = psIni->sInv.bAdapt3;
				jog3->Checked = psIni->sInv.bJog3;
				addBt3->Visible = !psIni->sInv.bJog3;
				autoDisch3->Checked = psIni->sInv.bAutoDisch3;
			}

			// plant 4 //DC 3.3.0 --------------------------------------------------------
			bForth = psIni->nNumLanes > 3;

			if (bForth)
			{
				if (pAll->eAsType == A_DEMO)
					psIni->sScale4.cGo = '0';			// idle

				groupBox4->Visible = bForth;

				if (psIni->bUseTrkMax)					//DC 3.2.0
					this->targetLb4->Text = L"TrkMax(TN)";

				numCopy4->Value = pAll->nTicketCopy4;			//DC 4.0.2

				if (psIni->bBotScale)
				{
					siloBar4->Maximum = psIni->fSiloMax10;
					siloBar4->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar4->Inventory = psIni->sInv.fInv10;
					siloBar4->Value = psIni->sInv.fInv10;
					if (psIni->nL4SilosNum > 1)
					{
						siloBar42->Maximum = psIni->fSiloMax11;
						siloBar42->Visible = true;
						siloBar42->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar42->Inventory = psIni->fSiloMax11 > 0 ? psIni->sInv.fInv11 : 0;
						siloBar42->Enabled = psIni->fSiloMax11 > 0;
						//				siloBar32->Idle = psIni->fSiloMax8 == 0;
						siloBar42_Click(nullptr, nullptr);
					}
					if (psIni->nL4SilosNum > 2)
					{
						siloBar43->Maximum = psIni->fSiloMax12;
						siloBar43->Visible = true;
						siloBar43->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar43->Inventory = psIni->fSiloMax12 > 0 ? psIni->sInv.fInv12 : 0;
						siloBar43->Enabled = psIni->fSiloMax12 > 0;
						//				siloBar33->Idle = psIni->fSiloMax9 == 0;
						siloBar43_Click(nullptr, nullptr);
					}

					scaleBar4->Maximum = psIni->fBotScaleMaxL4;		//DC 4.0.0
				}
				else
				{
					siloBar4->Text = "Silo 4";
					siloBar4->Maximum = psIni->fSiloMax4;
					siloBar4->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar4->Inventory = psIni->sInv.fInv4;
					siloBar4->Value = psIni->sInv.fInv4;

					siloBar4->Size = System::Drawing::Size(100, 230);
					scaleBar4->Size = System::Drawing::Size(100, 52);
					truckBar4->Size = System::Drawing::Size(100, 28);
					scaleBar4->Maximum = psIni->fTopScaleMax;

					if (pAll->pCam4 != nullptr)
					{
						webBrowser4->Visible = true;
						webBrowser4->Navigate(pAll->pCam4);
					}
				}
				tonnage4->Text = psIni->sInv.fTon4.ToString("F01");
				siloBar4_Click(nullptr, nullptr);

				//			printTarget3->Checked = psIni->sInv.bPrintTarget3;
				autoFall4->Checked = psIni->sInv.bAutoFall4;
				adapt4->Checked = psIni->sInv.bAdapt4;
				jog4->Checked = psIni->sInv.bJog4;
				addBt4->Visible = !psIni->sInv.bJog4;
				autoDisch4->Checked = psIni->sInv.bAutoDisch4;
			}

			if (psIni->bPdmPlc)		//DC 4.0.0
			{
				this->siloBar1->Text = gcnew String(psIni->asSilos[0].acMat);
				this->siloBar12->Text = gcnew String(psIni->asSilos[1].acMat);
				this->siloBar13->Text = gcnew String(psIni->asSilos[2].acMat);
				this->siloBar2->Text = gcnew String(psIni->asSilos[3].acMat);
				this->siloBar22->Text = gcnew String(psIni->asSilos[4].acMat);
				this->siloBar23->Text = gcnew String(psIni->asSilos[5].acMat);
				this->siloBar3->Text = gcnew String(psIni->asSilos[6].acMat);
				this->siloBar32->Text = gcnew String(psIni->asSilos[7].acMat);
				this->siloBar33->Text = gcnew String(psIni->asSilos[8].acMat);
				this->siloBar4->Text = gcnew String(psIni->asSilos[9].acMat);
				this->siloBar42->Text = gcnew String(psIni->asSilos[10].acMat);
				this->siloBar43->Text = gcnew String(psIni->asSilos[11].acMat);

				this->prod01Lb->Visible = psIni->asSilos[0].bUsed;
				this->prod02Lb->Visible = psIni->asSilos[1].bUsed;
				this->prod03Lb->Visible = psIni->asSilos[2].bUsed;
				this->prod04Lb->Visible = psIni->asSilos[3].bUsed;
				this->prod05Lb->Visible = psIni->asSilos[4].bUsed;
				this->prod06Lb->Visible = psIni->asSilos[5].bUsed;
				this->prod07Lb->Visible = psIni->asSilos[6].bUsed;
				this->prod08Lb->Visible = psIni->asSilos[7].bUsed;
				this->prod09Lb->Visible = psIni->asSilos[8].bUsed;
				this->prod10Lb->Visible = psIni->asSilos[9].bUsed;
				this->prod11Lb->Visible = psIni->asSilos[10].bUsed;
				this->prod12Lb->Visible = psIni->asSilos[11].bUsed;

				this->prod01Lb->Text = gcnew String(psIni->asSilos[0].acProduct);
				this->prod02Lb->Text = gcnew String(psIni->asSilos[1].acProduct);
				this->prod03Lb->Text = gcnew String(psIni->asSilos[2].acProduct);
				this->prod04Lb->Text = gcnew String(psIni->asSilos[3].acProduct);
				this->prod05Lb->Text = gcnew String(psIni->asSilos[4].acProduct);
				this->prod06Lb->Text = gcnew String(psIni->asSilos[5].acProduct);
				this->prod07Lb->Text = gcnew String(psIni->asSilos[6].acProduct);
				this->prod08Lb->Text = gcnew String(psIni->asSilos[7].acProduct);
				this->prod09Lb->Text = gcnew String(psIni->asSilos[8].acProduct);
				this->prod10Lb->Text = gcnew String(psIni->asSilos[9].acProduct);
				this->prod11Lb->Text = gcnew String(psIni->asSilos[10].acProduct);
				this->prod12Lb->Text = gcnew String(psIni->asSilos[11].acProduct);

				this->printTarget1->Visible = false; this->printTarget2->Visible = false;
				this->printTarget3->Visible = false; this->printTarget4->Visible = false;
				this->taxExempt1->Visible = false; this->taxExempt2->Visible = false;
				this->taxExempt3->Visible = false; this->taxExempt4->Visible = false;
				this->autoFall1->Visible = false; this->autoFall2->Visible = false;
				this->autoFall3->Visible = false; this->autoFall4->Visible = false;
				this->adapt1->Visible = false; this->adapt2->Visible = false;
				this->adapt3->Visible = false; this->adapt4->Visible = false;
				this->jog1->Visible = false; this->jog2->Visible = false;
				this->jog3->Visible = false; this->jog4->Visible = false;
				this->autoBt1->Visible = false; this->autoBt2->Visible = false;
				this->autoBt3->Visible = false; this->autoBt4->Visible = false;
			}

			//--------------------------------------------------------------------------
			switch (pAll->eAsType)
			{
			case A_DEMO:
				this->Text += "DEMO " + VERSION;
				ulinkLb->BackColor = Color::White;
				printerLb1->BackColor = Color::White;
				//				DbaseLb->BackColor = Color::White;
				optoLb->BackColor = Color::White;
				break;

			case A_SIM:
				this->Text += "SIMULA " + VERSION;
				break;

			case A_PROD:
				this->Text += "VERSION " + VERSION;
				break;

			case A_REMOTE:
				this->Text += "REMOTE " + VERSION;
				break;
			}
			this->Text += "                                 GivenHansco Inc.";
			versionLb->Text = "Plants " + psIni->nPlantNum1.ToString() + "," + psIni->nPlantNum2.ToString();

			//-----------------------------------------------------------------
			setState1(S_IDLE);
			setState2(S_IDLE);
			setState3(S_IDLE);
			setState4(S_IDLE);		//DC 3.3.0
			timer1->Enabled = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			poLog->~CLog();
		}
#pragma endregion

#pragma region Variables
		///////////////////////////////////////////////////////////////////////////
	private:
		All^ pAll;
		INI *psIni;			// configuration and common data
		CLog^ poLog;		// log file manager
		FILE *pfInv;		// inventory file 

							// OPTO, dbase, printer
							//System::Collections::Generic::Queue^ qDbase;
							//System::Collections::Generic::Queue^ qDbaseBad;

		bool bShowInv;
		//		bool b485Ok;		// RS485 tester
		int  nSplash;
		int  nOneSec;
		int	 nLane;

		int	 nOffs1;
		int	 nOffs2;
		int	 nOffs3;
		int  nOffs4;			//DC 3.3.0
		int  nKeepAliveTimeOn;	//DC 4.0.1
		int  nKeepAliveTimeOff;	//DC 4.0.1

		Color COL_IDLE;
		Color COL_CHARGE;
		Color COL_DISCH;
		Color COL_SETTLE;
		Color COL_HOLD;
		Color COL_HOLDK;
		Color COL_TRANS;
		Color COL_ERR;

		Color COL_GREEN;
		Color COL_PGREEN;
		Color COL_LSB;
		Color COL_LB;
		Color COL_W;
		Color COL_WS;
		Color COL_R;
		Color COL_YG;
		Color COL_DG;			//DC 4.1.0
		Color COL_G;
		Color COL_B;

		// plant 1 ------------------------------------------------------------
		bool  bAuto1;
		bool  bFill1;
		bool  bFill2;
		bool  bFill3;
		bool  bFirstDrop1;	// first drop
		bool  bZoom1;
		bool  bTruck1;		// truck present
		bool  bStopAdd1;	//DC 4.0.0

		int	  nTmpCnt1;
		int   nBlink1;
		int   nSettle1;      // scale settle timout
		int   nJogA;         // silo jog timout
		int	  nDelay1;		 //DC 4.0.0 silo delay then continue

		double fTol1;		   // target tolerance
		double fTarget1;       // drop size
		double fNewTarget1;    // drop size - tare
		double fTmpScale1;
		double fFall1;
		double fLoad1;
		double fCumTarget1; // cumulative target
		double fAdapt1;
		double fScaleVal1;

		Job^	pJob1;
		Truck^	pTruck1;
		clock_t	tSafeA;		// safe valve timeout 
		STATE	ePrevHold1;	//DC 4.0.0

							// plant 2 ------------------------------------------------------------------
		bool  bAuto2;
		bool  bSecond;
		bool  bFill4;
		bool  bFill5;
		bool  bFill6;
		bool  bFirstDrop2;	// first drop
		bool  bZoom2;
		bool  bTruck2;
		bool  bStopAdd2;	//DC 4.0.0

		int	  nTmpCnt2;
		int   nBlink2;
		int   nSettle2;     // scale settle timout
		int   nJogB;         // silo jog timout
		int	  nDelay2;		 //DC 4.0.0 silo delay then continue

		double fTol2;		   // target tolerance
		double fTarget2;       // drop size
		double fNewTarget2;    // drop size - tare 
		double fTmpScale2;
		double fLoad2;
		double fFall2;
		double fCumTarget2;  // partial target
		double fAdapt2;
		double fScaleVal2;

		Job^	pJob2;
		Truck^	pTruck2;
		clock_t	tSafeB;		// safe valve timeout
		STATE	ePrevHold2;	//DC 4.0.0

							// plant 3 ------------------------------------------------------------------
		bool  bAuto3;
		bool  bThird;
		bool  bFill7;
		bool  bFill8;
		bool  bFill9;
		bool  bFirstDrop3;	// first drop
		bool  bZoom3;
		bool  bTruck3;
		bool  bStopAdd3;	//DC 4.0.0

		int	  nTmpCnt3;
		int   nBlink3;
		int   nSettle3;      // scale settle timout
		int   nJogC;         // silo jog timout
		int	  nDelay3;		 //DC 4.0.0 silo delay then continue

		double fTol3;		   // target tolerance
		double fTarget3;       // drop size
		double fNewTarget3;    // drop size - tare 
		double fTmpScale3;
		double fFall3;
		double fLoad3;
		double fCumTarget3;  // partial target
		double fAdapt3;
		double fScaleVal3;

		Job^	pJob3;
		Truck^	pTruck3;
		clock_t	tSafeC;		// safe valve timeout
		STATE	ePrevHold3;	//DC 4.0.0

							//DC 3.3.0 plant 4 ------------------------------------------------------------------
		bool  bAuto4;
		bool  bForth;
		bool  bFill10;
		bool  bFill11;
		bool  bFill12;
		bool  bFirstDrop4;	// first drop
		bool  bZoom4;
		bool  bTruck4;
		bool  bStopAdd4;	//DC 4.0.0

		int	  nTmpCnt4;
		int   nBlink4;
		int   nSettle4;      // scale settle timout
		int   nJogD;         // silo jog timout
		int	  nDelay4;		 //DC 4.0.0 silo delay then continue

		double fTol4;		   // target tolerance
		double fTarget4;       // drop size
		double fNewTarget4;    // drop size - tare 
		double fTmpScale4;
		double fFall4;
		double fLoad4;
		double fCumTarget4;  // partial target
		double fAdapt4;
		double fScaleVal4;
		double fAddLoad4;	//DC 4.0.0

		Job^	pJob4;
		Truck^	pTruck4;
		clock_t	tSafeD;		// safe valve timeout
		STATE	ePrevHold4;	//DC 4.0.0

		time_t	tDiff;		//DC 3.2.6

		bool	bWrongMet;	//DC 4.0.1
		bool	bRemLogin;	//DC 4.1.0

		Thread^	oClinkThread; //DC 4.1.0
		int		nTicketsOld4; //DC 4.1.0
		int		nCounts;	//DC 4.1.0

							/// <summary>
							/// Required designer variable.
							/// </summary>
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  matLb3;
	private: System::Windows::Forms::Label^  custLb3;
	private: System::Windows::Forms::Label^  targetLb3;
	private: System::Windows::Forms::Label^  ticketNum3;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Button^  nextBt3;
	private: System::Windows::Forms::Label^  dropsLb3;
	private: System::Windows::Forms::Button^  pauseBt3;
	private: System::Windows::Forms::Button^  stopBt3;
	private: System::Windows::Forms::Button^  dropBt3;
	private: System::Windows::Forms::Label^  scale3;
	private: System::Windows::Forms::Label^  ticketNum1;
	private: System::Windows::Forms::Button^  nextBt1;
	private: System::Windows::Forms::Label^  dropsLb1;
	private: System::Windows::Forms::Button^  pauseBt1;
	private: System::Windows::Forms::Button^  stopBt1;
	private: System::Windows::Forms::Button^  dropBt1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  scale1;
	private: System::Windows::Forms::Label^  matLb1;
	private: System::Windows::Forms::Label^  custLb1;
	private: System::Windows::Forms::Label^  targetLb1;
	private: System::Windows::Forms::PictureBox^  truckPic1;
	private: System::Windows::Forms::PictureBox^  truckPic3;
	private: System::Windows::Forms::Label^  ticLb1;
	private: System::Windows::Forms::Label^  ticLb3;
	private: System::Windows::Forms::Label^  ulinkLb;
	private: System::Windows::Forms::Label^  optoLb;
	private: System::Windows::Forms::Label^  JobLb3;
	private: System::Windows::Forms::Label^  JobLb1;
	private: System::Windows::Forms::RadioButton^  drops11;
	private: System::Windows::Forms::Button^  pauseBt2;
	private: System::Windows::Forms::Button^  stopBt2;
	private: System::Windows::Forms::Button^  dropBt2;
	private: System::Windows::Forms::Label^  custLb2;
	private: System::Windows::Forms::Label^  dropsLb2;
	private: System::Windows::Forms::Label^  scale2;
	private: System::Windows::Forms::Button^  nextBt2;
	private: System::Windows::Forms::Label^  matLb2;
	private: System::Windows::Forms::Label^  targetLb2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  ticketNum2;
	private: System::Windows::Forms::PictureBox^  truckPic2;
	private: System::Windows::Forms::Label^  ticLb2;
	private: System::Windows::Forms::Label^  JobLb2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  drops14;
	private: System::Windows::Forms::RadioButton^  drops13;
	private: System::Windows::Forms::RadioButton^  drops12;
	private: System::Windows::Forms::RadioButton^  drops24;
	private: System::Windows::Forms::RadioButton^  drops23;
	private: System::Windows::Forms::RadioButton^  drops22;
	private: System::Windows::Forms::RadioButton^  drops21;
	private: System::Windows::Forms::RadioButton^  drops34;
	private: System::Windows::Forms::RadioButton^  drops33;
	private: System::Windows::Forms::RadioButton^  drops32;
	private: System::Windows::Forms::RadioButton^  drops31;
	private: System::Windows::Forms::Label^  trackLb1;
	private: System::Windows::Forms::Label^  truckLb2;
	private: System::Windows::Forms::Label^  truckLb3;
	private: System::Windows::Forms::Button^  dischBt3;
	private: System::Windows::Forms::Button^  dischBt1;
	private: System::Windows::Forms::Button^  dischBt2;
	private: System::Windows::Forms::Label^  DbaseLb;
	private: System::Windows::Forms::Label^  of1;
	private: System::Windows::Forms::Button^  addBt3;
	private: System::Windows::Forms::Button^  addBt1;
	private: System::Windows::Forms::Button^  addBt2;
	private: System::Windows::Forms::TextBox^  customer1;
	private: System::Windows::Forms::TextBox^  customer3;
	private: System::Windows::Forms::TextBox^  customer2;
	private: System::Windows::Forms::TextBox^  Job1;
	private: System::Windows::Forms::TextBox^  Job3;
	private: System::Windows::Forms::TextBox^  Job2;
	private: System::Windows::Forms::TextBox^  truck3;
	private: System::Windows::Forms::TextBox^  target1;
	private: System::Windows::Forms::TextBox^  truck1;
	private: System::Windows::Forms::TextBox^  truck2;
	private: System::Windows::Forms::TextBox^  target3;
	private: System::Windows::Forms::TextBox^  target2;
	private: System::Windows::Forms::TextBox^  tic_num3;
	private: System::Windows::Forms::TextBox^  material1;
	private: System::Windows::Forms::TextBox^  tic_num1;
	private: System::Windows::Forms::TextBox^  tic_num2;
	private: System::Windows::Forms::TextBox^  material3;
	private: System::Windows::Forms::TextBox^  material2;
	private: System::Windows::Forms::Button^  autoBt1;
	private: System::Windows::Forms::Button^  autoBt3;
	private: System::Windows::Forms::Button^  autoBt2;
	private: System::Windows::Forms::Label^  man1;
	private: System::Windows::Forms::Label^  man3;
	private: System::Windows::Forms::Label^  man2;
	private: System::Windows::Forms::WebBrowser^  webBrowser2;
	private: System::Windows::Forms::WebBrowser^  webBrowser3;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Timers::Timer^  timer1;
	private: System::Windows::Forms::MenuStrip^  menu;
	private: System::Windows::Forms::ToolStripMenuItem^  fileMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  printManualJobs;
	private: System::Windows::Forms::ToolStripMenuItem^  exitMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutMenuItem;
	private: System::Windows::Forms::Label^  printerLb1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  versionLb;
	private: System::Windows::Forms::Label^  tonnage1;
	private: System::Windows::Forms::Label^  tonLb1;
	private: System::Windows::Forms::Label^  tonnage3;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  tonnage2;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::ToolStripMenuItem^  inventoryMenuItem;
	private: System::Windows::Forms::CheckBox^  printTarget3;
	private: System::Windows::Forms::CheckBox^  printTarget1;
	private: System::Windows::Forms::CheckBox^  printTarget2;
	private: System::Windows::Forms::Button^  printOnly1;
	private: System::Windows::Forms::Button^  printOnly3;
	private: System::Windows::Forms::Button^  printOnly2;
	private: System::Windows::Forms::Label^  dbaseBadLb;
	private: System::Windows::Forms::Label^  flow1;
	private: System::Windows::Forms::Label^  flow3;
	private: System::Windows::Forms::Label^  flow2;
	private: System::Windows::Forms::CheckBox^  autoFall1;
	private: System::Windows::Forms::CheckBox^  autoFall2;
	private: System::Windows::Forms::CheckBox^  autoFall3;
	private: System::Windows::Forms::Button^  readyBt1;
	private: System::Windows::Forms::Button^  readyBt2;
	private: System::Windows::Forms::Button^  readyBt3;
	private: System::Windows::Forms::CheckBox^  jog3;
	private: System::Windows::Forms::CheckBox^  jog1;
	private: System::Windows::Forms::CheckBox^  jog2;
	private: As::BinCtl^  siloBar1;
	private: As::BinCtl^  siloBar13;
	private: As::BinCtl^  siloBar12;
	private: As::BinCtl^  siloBar23;
	private: As::BinCtl^  siloBar22;
	private: As::BinCtl^  siloBar2;
	private: As::BinCtl^  siloBar33;
	private: As::BinCtl^  siloBar32;
	private: As::BinCtl^  siloBar3;
	private: As::ScaleCtl^  scaleBar1;
	private: As::ScaleCtl^  scaleBar2;
	private: As::ScaleCtl^  scaleBar3;
	private: As::BarCtl^  truckBar1;
	private: As::BarCtl^  truckBar2;
	private: As::BarCtl^  truckBar3;
	private: System::Windows::Forms::Label^  fill1;
	private: System::Windows::Forms::Label^  fill3;
	private: System::Windows::Forms::Label^  fill2;
	private: System::Windows::Forms::Label^  fill13;
	private: System::Windows::Forms::Label^  fill12;
	private: System::Windows::Forms::Label^  fill22;
	private: System::Windows::Forms::Label^  fill33;
	private: System::Windows::Forms::Label^  fill32;
	private: System::Windows::Forms::Label^  fill23;
	private: System::Windows::Forms::Label^  cnt3;
	private: System::Windows::Forms::Label^  cnt1;
	private: System::Windows::Forms::Label^  cnt2;
	private: System::Windows::Forms::Label^  silo1;
	private: System::Windows::Forms::Label^  silo2;
	private: System::Windows::Forms::Label^  silo3;
	private: System::Windows::Forms::CheckBox^  autoDisch3;
	private: System::Windows::Forms::CheckBox^  autoDisch1;
	private: System::Windows::Forms::CheckBox^  autoDisch2;
	private: System::Windows::Forms::Button^  zoom1;
	private: System::Windows::Forms::Button^  zoom2;
	private: System::Windows::Forms::Button^  zoom3;
	private: System::Windows::Forms::ToolStripMenuItem^  trucksToolStripMenuItem;
	private: System::Windows::Forms::DataGridView^  dataGridTruck;
	private: System::Windows::Forms::BindingSource^  truckBindingSource;
	private: System::Windows::Forms::Button^  all3;
	private: System::Windows::Forms::Button^  all1;
	private: System::Windows::Forms::Button^  all2;
	private: System::Windows::Forms::DataGridView^  dataGridJob;
	private: System::Windows::Forms::BindingSource^  jobBindingSource;
	private: System::Windows::Forms::Label^  lite3;
	private: System::Windows::Forms::Label^  lite1;
	private: System::Windows::Forms::Label^  lite2;
	private: System::Windows::Forms::Label^  optoErr;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::CheckBox^  adapt3;
	private: System::Windows::Forms::CheckBox^  adapt1;
	private: System::Windows::Forms::CheckBox^  adapt2;
	private: System::Windows::Forms::BindingSource^  oldBindingSource;
	private: System::Windows::Forms::Label^  printerLb2;
	private: System::Windows::Forms::CheckBox^  laneBCb3;

	private: System::Windows::Forms::CheckBox^  laneACb2;



	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stNameDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nRateDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nCapacityDataGridViewTextBoxColumn;
	private: System::Windows::Forms::Label^  plant1;
	private: System::Windows::Forms::Label^  plant3;
	private: System::Windows::Forms::Label^  plant2;
	private: System::Windows::Forms::Label^  printerLb3;
	private: System::Windows::Forms::ToolStripMenuItem^  testStripMenuItem;






	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureSplash;
	private: System::Windows::Forms::Label^  dbLb;
	private: System::Windows::Forms::GroupBox^  groupBoxC;
	private: System::Windows::Forms::Button^  okC;
	private: System::Windows::Forms::TextBox^  grossC;
	private: System::Windows::Forms::TextBox^  tareC;
	private: System::Windows::Forms::GroupBox^  groupBoxA;
	private: System::Windows::Forms::Button^  okA;
	private: System::Windows::Forms::TextBox^  grossA;
	private: System::Windows::Forms::TextBox^  tareA;
	private: System::Windows::Forms::GroupBox^  groupBoxB;
	private: System::Windows::Forms::Button^  okB;
	private: System::Windows::Forms::TextBox^  grossB;
	private: System::Windows::Forms::TextBox^  tareB;
	private: System::Windows::Forms::CheckBox^  taxExempt3;
	private: System::Windows::Forms::CheckBox^  taxExempt1;
	private: System::Windows::Forms::CheckBox^  taxExempt2;
	private: System::Windows::Forms::CheckBox^  laneACb3;
	private: System::Windows::Forms::CheckBox^  laneBCb1;
	private: System::Windows::Forms::CheckBox^  laneCCb1;
	private: System::Windows::Forms::CheckBox^  laneCCb2;
	private: System::Windows::Forms::RichTextBox^  testBox;
	private: System::Windows::Forms::ToolStripMenuItem^  ulinkMsgToolStripMenuItem;
	private: System::Windows::Forms::Label^  dbLb1;
	private: System::Windows::Forms::Label^  dbLb2;
	private: System::Windows::Forms::ToolStripMenuItem^  exceptionsToolStripMenuItem;
	private: System::Windows::Forms::Label^  safe7;

	private: System::Windows::Forms::Label^  safe3;
	private: System::Windows::Forms::Label^  safe2;
	private: System::Windows::Forms::Label^  safe1;
	private: System::Windows::Forms::Label^  safe6;
	private: System::Windows::Forms::Label^  safe5;
	private: System::Windows::Forms::Label^  safe4;
	private: System::Windows::Forms::Label^  safe9;
	private: System::Windows::Forms::Label^  safe8;
	private: System::Windows::Forms::Label^  wrLb;

	private: System::Windows::Forms::Label^  rdLb;
	private: System::Windows::Forms::ToolStripMenuItem^  iOTestToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  lite4;

	private: System::Windows::Forms::WebBrowser^  webBrowser4;
	private: System::Windows::Forms::Label^  safe12;

	private: System::Windows::Forms::Label^  safe11;

	private: System::Windows::Forms::Label^  safe10;

	private: System::Windows::Forms::CheckBox^  laneDCb1;
	private: System::Windows::Forms::CheckBox^  laneDCb2;


	private: System::Windows::Forms::CheckBox^  taxExempt4;

	private: System::Windows::Forms::GroupBox^  groupBoxD;
	private: System::Windows::Forms::Button^  okD;


	private: System::Windows::Forms::TextBox^  grossD;

	private: System::Windows::Forms::TextBox^  tareD;

	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  plant4;
	private: System::Windows::Forms::CheckBox^  adapt4;


	private: System::Windows::Forms::Button^  all4;
	private: System::Windows::Forms::CheckBox^  autoDisch4;


	private: System::Windows::Forms::Label^  silo4;
	private: System::Windows::Forms::Label^  fill43;


	private: System::Windows::Forms::Label^  fill42;

	private: System::Windows::Forms::Label^  fill4;

	private: As::BarCtl^  truckBar4;

	private: As::ScaleCtl^  scaleBar4;

	private: As::BinCtl^  siloBar43;

	private: As::BinCtl^  siloBar42;

	private: As::BinCtl^  siloBar4;
	private: System::Windows::Forms::CheckBox^  jog4;


	private: System::Windows::Forms::Button^  readyBt4;
	private: System::Windows::Forms::CheckBox^  autoFall4;


	private: System::Windows::Forms::Label^  flow4;
	private: System::Windows::Forms::Button^  printOnly4;
	private: System::Windows::Forms::CheckBox^  printTarget4;



	private: System::Windows::Forms::Label^  tonnage4;

	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  man4;

	private: System::Windows::Forms::Button^  autoBt4;

	private: System::Windows::Forms::TextBox^  material4;
	private: System::Windows::Forms::TextBox^  tic_num4;
	private: System::Windows::Forms::TextBox^  target4;



	private: System::Windows::Forms::TextBox^  truck4;

	private: System::Windows::Forms::TextBox^  Job4;

	private: System::Windows::Forms::TextBox^  customer4;
	private: System::Windows::Forms::Button^  addBt4;
	private: System::Windows::Forms::Button^  dischBt4;



	private: System::Windows::Forms::Label^  truckLb4;
	private: System::Windows::Forms::RadioButton^  drops44;


	private: System::Windows::Forms::RadioButton^  drops43;

	private: System::Windows::Forms::RadioButton^  drops42;

	private: System::Windows::Forms::RadioButton^  drops41;

	private: System::Windows::Forms::Label^  JobLb4;
	private: System::Windows::Forms::Label^  cnt4;


	private: System::Windows::Forms::Label^  ticLb4;
	private: System::Windows::Forms::PictureBox^  truckPic4;


	private: System::Windows::Forms::Label^  ticketNum4;

	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Label^  targetLb4;

	private: System::Windows::Forms::Label^  matLb4;

	private: System::Windows::Forms::Button^  nextBt4;
	private: System::Windows::Forms::Label^  dropsLb4;


	private: System::Windows::Forms::Label^  scale4;

	private: System::Windows::Forms::Label^  custLb4;
	private: System::Windows::Forms::Button^  pauseBt4;


	private: System::Windows::Forms::Button^  stopBt4;
	private: System::Windows::Forms::Button^  dropBt4;
	private: System::Windows::Forms::Button^  zoom4;
	private: System::Windows::Forms::ToolStripMenuItem^  configToolStripMenuItem;
	private: System::Windows::Forms::Label^  lane1StatLB;
	private: System::Windows::Forms::Label^  lane3StatLB;
	private: System::Windows::Forms::Label^  lane2StatLB;
	private: System::Windows::Forms::Label^  lane4StatLB;
	private: System::Windows::Forms::Label^  printerLb4;
	private: System::Windows::Forms::Label^  matrixPDMLb;
	private: System::Windows::Forms::Label^  prod01Lb;
	private: System::Windows::Forms::Label^  prod02Lb;
	private: System::Windows::Forms::Label^  prod03Lb;
	private: System::Windows::Forms::Label^  prod09Lb;

	private: System::Windows::Forms::Label^  prod08Lb;

	private: System::Windows::Forms::Label^  prod07Lb;
	private: System::Windows::Forms::Label^  prod06Lb;
	private: System::Windows::Forms::Label^  prod05Lb;
	private: System::Windows::Forms::Label^  prod04Lb;
	private: System::Windows::Forms::Label^  prod12Lb;

	private: System::Windows::Forms::Label^  prod11Lb;

	private: System::Windows::Forms::Label^  prod10Lb;








	private: System::Windows::Forms::NumericUpDown^  numCopy1;
	private: System::Windows::Forms::CheckBox^  laneA2ndCB;




	private: System::Windows::Forms::Label^  copyLb1;
	private: System::Windows::Forms::Label^  copyLane1Lb;
	private: System::Windows::Forms::Label^  copyLane4Lb;
	private: System::Windows::Forms::Label^  copyLane3Lb;
	private: System::Windows::Forms::Label^  copyLane2Lb;
	private: System::Windows::Forms::CheckBox^  laneC2ndCB;

	private: System::Windows::Forms::Label^  copyLb3;

	private: System::Windows::Forms::NumericUpDown^  numCopy3;
	private: System::Windows::Forms::CheckBox^  laneB2ndCB;


	private: System::Windows::Forms::Label^  copyLb2;

	private: System::Windows::Forms::NumericUpDown^  numCopy2;
	private: System::Windows::Forms::CheckBox^  laneD2ndCB;

	private: System::Windows::Forms::Label^  copyLb4;

	private: System::Windows::Forms::NumericUpDown^  numCopy4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nSilo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nTicketDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stTruck;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stMaterial;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stCustomer;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  fLoad;
	private: System::Windows::Forms::Button^  resetBt3;
	private: System::Windows::Forms::Button^  resetBt1;
	private: System::Windows::Forms::Button^  resetBt2;
	private: System::Windows::Forms::Button^  resetBt4;
	private: System::Windows::Forms::Button^  remLoginBt;
	private: System::Windows::Forms::Label^  loginErrLb;
	private: System::Windows::Forms::Label^  clinkLb;
	private: System::Windows::Forms::Label^  remoteLb;
	private: System::Windows::Forms::Label^  ipAddressLb;
	private: System::Windows::Forms::GroupBox^  gBoxLine1;
	private: As::BinCtl^  siloBar14;
	private: As::BinCtl^  siloBar24;





















































































	private: System::Windows::Forms::ToolStripMenuItem^  reprintToolStripMenuItem;

#pragma endregion

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				 this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
				 this->laneC2ndCB = (gcnew System::Windows::Forms::CheckBox());
				 this->testBox = (gcnew System::Windows::Forms::RichTextBox());
				 this->copyLb3 = (gcnew System::Windows::Forms::Label());
				 this->numCopy3 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->prod08Lb = (gcnew System::Windows::Forms::Label());
				 this->prod07Lb = (gcnew System::Windows::Forms::Label());
				 this->lane3StatLB = (gcnew System::Windows::Forms::Label());
				 this->lite3 = (gcnew System::Windows::Forms::Label());
				 this->webBrowser3 = (gcnew System::Windows::Forms::WebBrowser());
				 this->safe9 = (gcnew System::Windows::Forms::Label());
				 this->safe8 = (gcnew System::Windows::Forms::Label());
				 this->safe7 = (gcnew System::Windows::Forms::Label());
				 this->laneCCb1 = (gcnew System::Windows::Forms::CheckBox());
				 this->laneCCb2 = (gcnew System::Windows::Forms::CheckBox());
				 this->taxExempt3 = (gcnew System::Windows::Forms::CheckBox());
				 this->groupBoxC = (gcnew System::Windows::Forms::GroupBox());
				 this->okC = (gcnew System::Windows::Forms::Button());
				 this->grossC = (gcnew System::Windows::Forms::TextBox());
				 this->tareC = (gcnew System::Windows::Forms::TextBox());
				 this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->plant3 = (gcnew System::Windows::Forms::Label());
				 this->adapt3 = (gcnew System::Windows::Forms::CheckBox());
				 this->all3 = (gcnew System::Windows::Forms::Button());
				 this->autoDisch3 = (gcnew System::Windows::Forms::CheckBox());
				 this->silo3 = (gcnew System::Windows::Forms::Label());
				 this->fill33 = (gcnew System::Windows::Forms::Label());
				 this->fill32 = (gcnew System::Windows::Forms::Label());
				 this->fill3 = (gcnew System::Windows::Forms::Label());
				 this->truckBar3 = (gcnew As::BarCtl());
				 this->scaleBar3 = (gcnew As::ScaleCtl());
				 this->siloBar33 = (gcnew As::BinCtl());
				 this->siloBar32 = (gcnew As::BinCtl());
				 this->siloBar3 = (gcnew As::BinCtl());
				 this->jog3 = (gcnew System::Windows::Forms::CheckBox());
				 this->readyBt3 = (gcnew System::Windows::Forms::Button());
				 this->autoFall3 = (gcnew System::Windows::Forms::CheckBox());
				 this->flow3 = (gcnew System::Windows::Forms::Label());
				 this->printOnly3 = (gcnew System::Windows::Forms::Button());
				 this->printTarget3 = (gcnew System::Windows::Forms::CheckBox());
				 this->tonnage3 = (gcnew System::Windows::Forms::Label());
				 this->label11 = (gcnew System::Windows::Forms::Label());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->man3 = (gcnew System::Windows::Forms::Label());
				 this->material3 = (gcnew System::Windows::Forms::TextBox());
				 this->tic_num3 = (gcnew System::Windows::Forms::TextBox());
				 this->target3 = (gcnew System::Windows::Forms::TextBox());
				 this->truck3 = (gcnew System::Windows::Forms::TextBox());
				 this->Job3 = (gcnew System::Windows::Forms::TextBox());
				 this->customer3 = (gcnew System::Windows::Forms::TextBox());
				 this->addBt3 = (gcnew System::Windows::Forms::Button());
				 this->dischBt3 = (gcnew System::Windows::Forms::Button());
				 this->truckLb3 = (gcnew System::Windows::Forms::Label());
				 this->drops34 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops33 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops32 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops31 = (gcnew System::Windows::Forms::RadioButton());
				 this->JobLb3 = (gcnew System::Windows::Forms::Label());
				 this->cnt3 = (gcnew System::Windows::Forms::Label());
				 this->ticLb3 = (gcnew System::Windows::Forms::Label());
				 this->truckPic3 = (gcnew System::Windows::Forms::PictureBox());
				 this->ticketNum3 = (gcnew System::Windows::Forms::Label());
				 this->label13 = (gcnew System::Windows::Forms::Label());
				 this->targetLb3 = (gcnew System::Windows::Forms::Label());
				 this->matLb3 = (gcnew System::Windows::Forms::Label());
				 this->nextBt3 = (gcnew System::Windows::Forms::Button());
				 this->dropsLb3 = (gcnew System::Windows::Forms::Label());
				 this->scale3 = (gcnew System::Windows::Forms::Label());
				 this->custLb3 = (gcnew System::Windows::Forms::Label());
				 this->pauseBt3 = (gcnew System::Windows::Forms::Button());
				 this->stopBt3 = (gcnew System::Windows::Forms::Button());
				 this->dropBt3 = (gcnew System::Windows::Forms::Button());
				 this->prod09Lb = (gcnew System::Windows::Forms::Label());
				 this->resetBt3 = (gcnew System::Windows::Forms::Button());
				 this->autoBt3 = (gcnew System::Windows::Forms::Button());
				 this->zoom3 = (gcnew System::Windows::Forms::Button());
				 this->ticketNum1 = (gcnew System::Windows::Forms::Label());
				 this->nextBt1 = (gcnew System::Windows::Forms::Button());
				 this->dropsLb1 = (gcnew System::Windows::Forms::Label());
				 this->pauseBt1 = (gcnew System::Windows::Forms::Button());
				 this->stopBt1 = (gcnew System::Windows::Forms::Button());
				 this->dropBt1 = (gcnew System::Windows::Forms::Button());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->siloBar14 = (gcnew As::BinCtl());
				 this->prod03Lb = (gcnew System::Windows::Forms::Label());
				 this->prod02Lb = (gcnew System::Windows::Forms::Label());
				 this->prod01Lb = (gcnew System::Windows::Forms::Label());
				 this->lane1StatLB = (gcnew System::Windows::Forms::Label());
				 this->lite1 = (gcnew System::Windows::Forms::Label());
				 this->safe3 = (gcnew System::Windows::Forms::Label());
				 this->safe2 = (gcnew System::Windows::Forms::Label());
				 this->safe1 = (gcnew System::Windows::Forms::Label());
				 this->dbLb2 = (gcnew System::Windows::Forms::Label());
				 this->dbLb1 = (gcnew System::Windows::Forms::Label());
				 this->groupBoxA = (gcnew System::Windows::Forms::GroupBox());
				 this->okA = (gcnew System::Windows::Forms::Button());
				 this->grossA = (gcnew System::Windows::Forms::TextBox());
				 this->tareA = (gcnew System::Windows::Forms::TextBox());
				 this->dbLb = (gcnew System::Windows::Forms::Label());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
				 this->plant1 = (gcnew System::Windows::Forms::Label());
				 this->silo1 = (gcnew System::Windows::Forms::Label());
				 this->fill13 = (gcnew System::Windows::Forms::Label());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->fill12 = (gcnew System::Windows::Forms::Label());
				 this->fill1 = (gcnew System::Windows::Forms::Label());
				 this->truckBar1 = (gcnew As::BarCtl());
				 this->scaleBar1 = (gcnew As::ScaleCtl());
				 this->siloBar1 = (gcnew As::BinCtl());
				 this->siloBar13 = (gcnew As::BinCtl());
				 this->siloBar12 = (gcnew As::BinCtl());
				 this->flow1 = (gcnew System::Windows::Forms::Label());
				 this->tonnage1 = (gcnew System::Windows::Forms::Label());
				 this->tonLb1 = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->man1 = (gcnew System::Windows::Forms::Label());
				 this->material1 = (gcnew System::Windows::Forms::TextBox());
				 this->tic_num1 = (gcnew System::Windows::Forms::TextBox());
				 this->target1 = (gcnew System::Windows::Forms::TextBox());
				 this->truck1 = (gcnew System::Windows::Forms::TextBox());
				 this->Job1 = (gcnew System::Windows::Forms::TextBox());
				 this->customer1 = (gcnew System::Windows::Forms::TextBox());
				 this->dischBt1 = (gcnew System::Windows::Forms::Button());
				 this->trackLb1 = (gcnew System::Windows::Forms::Label());
				 this->JobLb1 = (gcnew System::Windows::Forms::Label());
				 this->cnt1 = (gcnew System::Windows::Forms::Label());
				 this->ticLb1 = (gcnew System::Windows::Forms::Label());
				 this->of1 = (gcnew System::Windows::Forms::Label());
				 this->targetLb1 = (gcnew System::Windows::Forms::Label());
				 this->matLb1 = (gcnew System::Windows::Forms::Label());
				 this->scale1 = (gcnew System::Windows::Forms::Label());
				 this->custLb1 = (gcnew System::Windows::Forms::Label());
				 this->truckPic1 = (gcnew System::Windows::Forms::PictureBox());
				 this->gBoxLine1 = (gcnew System::Windows::Forms::GroupBox());
				 this->resetBt1 = (gcnew System::Windows::Forms::Button());
				 this->laneA2ndCB = (gcnew System::Windows::Forms::CheckBox());
				 this->copyLb1 = (gcnew System::Windows::Forms::Label());
				 this->numCopy1 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->drops11 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops12 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops13 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops14 = (gcnew System::Windows::Forms::RadioButton());
				 this->addBt1 = (gcnew System::Windows::Forms::Button());
				 this->autoBt1 = (gcnew System::Windows::Forms::Button());
				 this->printTarget1 = (gcnew System::Windows::Forms::CheckBox());
				 this->printOnly1 = (gcnew System::Windows::Forms::Button());
				 this->autoFall1 = (gcnew System::Windows::Forms::CheckBox());
				 this->readyBt1 = (gcnew System::Windows::Forms::Button());
				 this->laneACb3 = (gcnew System::Windows::Forms::CheckBox());
				 this->jog1 = (gcnew System::Windows::Forms::CheckBox());
				 this->taxExempt1 = (gcnew System::Windows::Forms::CheckBox());
				 this->autoDisch1 = (gcnew System::Windows::Forms::CheckBox());
				 this->all1 = (gcnew System::Windows::Forms::Button());
				 this->laneACb2 = (gcnew System::Windows::Forms::CheckBox());
				 this->adapt1 = (gcnew System::Windows::Forms::CheckBox());
				 this->dataGridTruck = (gcnew System::Windows::Forms::DataGridView());
				 this->stNameDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->nRateDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->nCapacityDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->truckBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
				 this->zoom1 = (gcnew System::Windows::Forms::Button());
				 this->ulinkLb = (gcnew System::Windows::Forms::Label());
				 this->optoLb = (gcnew System::Windows::Forms::Label());
				 this->pauseBt2 = (gcnew System::Windows::Forms::Button());
				 this->stopBt2 = (gcnew System::Windows::Forms::Button());
				 this->dropBt2 = (gcnew System::Windows::Forms::Button());
				 this->custLb2 = (gcnew System::Windows::Forms::Label());
				 this->dropsLb2 = (gcnew System::Windows::Forms::Label());
				 this->scale2 = (gcnew System::Windows::Forms::Label());
				 this->nextBt2 = (gcnew System::Windows::Forms::Button());
				 this->matLb2 = (gcnew System::Windows::Forms::Label());
				 this->targetLb2 = (gcnew System::Windows::Forms::Label());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->ticketNum2 = (gcnew System::Windows::Forms::Label());
				 this->truckPic2 = (gcnew System::Windows::Forms::PictureBox());
				 this->ticLb2 = (gcnew System::Windows::Forms::Label());
				 this->JobLb2 = (gcnew System::Windows::Forms::Label());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->siloBar24 = (gcnew As::BinCtl());
				 this->resetBt2 = (gcnew System::Windows::Forms::Button());
				 this->laneB2ndCB = (gcnew System::Windows::Forms::CheckBox());
				 this->prod06Lb = (gcnew System::Windows::Forms::Label());
				 this->copyLb2 = (gcnew System::Windows::Forms::Label());
				 this->numCopy2 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->prod05Lb = (gcnew System::Windows::Forms::Label());
				 this->prod04Lb = (gcnew System::Windows::Forms::Label());
				 this->lane2StatLB = (gcnew System::Windows::Forms::Label());
				 this->lite2 = (gcnew System::Windows::Forms::Label());
				 this->wrLb = (gcnew System::Windows::Forms::Label());
				 this->rdLb = (gcnew System::Windows::Forms::Label());
				 this->safe6 = (gcnew System::Windows::Forms::Label());
				 this->safe5 = (gcnew System::Windows::Forms::Label());
				 this->safe4 = (gcnew System::Windows::Forms::Label());
				 this->laneBCb1 = (gcnew System::Windows::Forms::CheckBox());
				 this->webBrowser2 = (gcnew System::Windows::Forms::WebBrowser());
				 this->taxExempt2 = (gcnew System::Windows::Forms::CheckBox());
				 this->groupBoxB = (gcnew System::Windows::Forms::GroupBox());
				 this->okB = (gcnew System::Windows::Forms::Button());
				 this->grossB = (gcnew System::Windows::Forms::TextBox());
				 this->tareB = (gcnew System::Windows::Forms::TextBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->plant2 = (gcnew System::Windows::Forms::Label());
				 this->laneBCb3 = (gcnew System::Windows::Forms::CheckBox());
				 this->adapt2 = (gcnew System::Windows::Forms::CheckBox());
				 this->all2 = (gcnew System::Windows::Forms::Button());
				 this->autoDisch2 = (gcnew System::Windows::Forms::CheckBox());
				 this->silo2 = (gcnew System::Windows::Forms::Label());
				 this->fill23 = (gcnew System::Windows::Forms::Label());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 this->fill22 = (gcnew System::Windows::Forms::Label());
				 this->fill2 = (gcnew System::Windows::Forms::Label());
				 this->truckBar2 = (gcnew As::BarCtl());
				 this->scaleBar2 = (gcnew As::ScaleCtl());
				 this->siloBar23 = (gcnew As::BinCtl());
				 this->siloBar22 = (gcnew As::BinCtl());
				 this->siloBar2 = (gcnew As::BinCtl());
				 this->jog2 = (gcnew System::Windows::Forms::CheckBox());
				 this->readyBt2 = (gcnew System::Windows::Forms::Button());
				 this->autoFall2 = (gcnew System::Windows::Forms::CheckBox());
				 this->flow2 = (gcnew System::Windows::Forms::Label());
				 this->printOnly2 = (gcnew System::Windows::Forms::Button());
				 this->printTarget2 = (gcnew System::Windows::Forms::CheckBox());
				 this->tonnage2 = (gcnew System::Windows::Forms::Label());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->man2 = (gcnew System::Windows::Forms::Label());
				 this->autoBt2 = (gcnew System::Windows::Forms::Button());
				 this->material2 = (gcnew System::Windows::Forms::TextBox());
				 this->tic_num2 = (gcnew System::Windows::Forms::TextBox());
				 this->target2 = (gcnew System::Windows::Forms::TextBox());
				 this->truck2 = (gcnew System::Windows::Forms::TextBox());
				 this->Job2 = (gcnew System::Windows::Forms::TextBox());
				 this->customer2 = (gcnew System::Windows::Forms::TextBox());
				 this->addBt2 = (gcnew System::Windows::Forms::Button());
				 this->dischBt2 = (gcnew System::Windows::Forms::Button());
				 this->truckLb2 = (gcnew System::Windows::Forms::Label());
				 this->drops24 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops23 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops22 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops21 = (gcnew System::Windows::Forms::RadioButton());
				 this->cnt2 = (gcnew System::Windows::Forms::Label());
				 this->zoom2 = (gcnew System::Windows::Forms::Button());
				 this->DbaseLb = (gcnew System::Windows::Forms::Label());
				 this->timer1 = (gcnew System::Timers::Timer());
				 this->fileMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->printManualJobs = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->configToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->exitMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->helpMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->aboutMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->testStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ulinkMsgToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->exceptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->iOTestToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->menu = (gcnew System::Windows::Forms::MenuStrip());
				 this->inventoryMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->trucksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->reprintToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->printerLb1 = (gcnew System::Windows::Forms::Label());
				 this->versionLb = (gcnew System::Windows::Forms::Label());
				 this->dbaseBadLb = (gcnew System::Windows::Forms::Label());
				 this->dataGridJob = (gcnew System::Windows::Forms::DataGridView());
				 this->stTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->nSilo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->nTicketDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->stTruck = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->stMaterial = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->stCustomer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->fLoad = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				 this->jobBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
				 this->optoErr = (gcnew System::Windows::Forms::Label());
				 this->printerLb2 = (gcnew System::Windows::Forms::Label());
				 this->printerLb3 = (gcnew System::Windows::Forms::Label());
				 this->pictureSplash = (gcnew System::Windows::Forms::PictureBox());
				 this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
				 this->remoteLb = (gcnew System::Windows::Forms::Label());
				 this->resetBt4 = (gcnew System::Windows::Forms::Button());
				 this->laneD2ndCB = (gcnew System::Windows::Forms::CheckBox());
				 this->copyLb4 = (gcnew System::Windows::Forms::Label());
				 this->numCopy4 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->prod12Lb = (gcnew System::Windows::Forms::Label());
				 this->prod11Lb = (gcnew System::Windows::Forms::Label());
				 this->prod10Lb = (gcnew System::Windows::Forms::Label());
				 this->lane4StatLB = (gcnew System::Windows::Forms::Label());
				 this->zoom4 = (gcnew System::Windows::Forms::Button());
				 this->lite4 = (gcnew System::Windows::Forms::Label());
				 this->webBrowser4 = (gcnew System::Windows::Forms::WebBrowser());
				 this->safe12 = (gcnew System::Windows::Forms::Label());
				 this->safe11 = (gcnew System::Windows::Forms::Label());
				 this->safe10 = (gcnew System::Windows::Forms::Label());
				 this->laneDCb1 = (gcnew System::Windows::Forms::CheckBox());
				 this->laneDCb2 = (gcnew System::Windows::Forms::CheckBox());
				 this->taxExempt4 = (gcnew System::Windows::Forms::CheckBox());
				 this->groupBoxD = (gcnew System::Windows::Forms::GroupBox());
				 this->okD = (gcnew System::Windows::Forms::Button());
				 this->grossD = (gcnew System::Windows::Forms::TextBox());
				 this->tareD = (gcnew System::Windows::Forms::TextBox());
				 this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
				 this->label15 = (gcnew System::Windows::Forms::Label());
				 this->plant4 = (gcnew System::Windows::Forms::Label());
				 this->adapt4 = (gcnew System::Windows::Forms::CheckBox());
				 this->all4 = (gcnew System::Windows::Forms::Button());
				 this->autoDisch4 = (gcnew System::Windows::Forms::CheckBox());
				 this->silo4 = (gcnew System::Windows::Forms::Label());
				 this->fill43 = (gcnew System::Windows::Forms::Label());
				 this->fill42 = (gcnew System::Windows::Forms::Label());
				 this->fill4 = (gcnew System::Windows::Forms::Label());
				 this->truckBar4 = (gcnew As::BarCtl());
				 this->scaleBar4 = (gcnew As::ScaleCtl());
				 this->siloBar43 = (gcnew As::BinCtl());
				 this->siloBar42 = (gcnew As::BinCtl());
				 this->siloBar4 = (gcnew As::BinCtl());
				 this->jog4 = (gcnew System::Windows::Forms::CheckBox());
				 this->readyBt4 = (gcnew System::Windows::Forms::Button());
				 this->autoFall4 = (gcnew System::Windows::Forms::CheckBox());
				 this->flow4 = (gcnew System::Windows::Forms::Label());
				 this->printOnly4 = (gcnew System::Windows::Forms::Button());
				 this->printTarget4 = (gcnew System::Windows::Forms::CheckBox());
				 this->tonnage4 = (gcnew System::Windows::Forms::Label());
				 this->label23 = (gcnew System::Windows::Forms::Label());
				 this->label24 = (gcnew System::Windows::Forms::Label());
				 this->man4 = (gcnew System::Windows::Forms::Label());
				 this->autoBt4 = (gcnew System::Windows::Forms::Button());
				 this->material4 = (gcnew System::Windows::Forms::TextBox());
				 this->tic_num4 = (gcnew System::Windows::Forms::TextBox());
				 this->target4 = (gcnew System::Windows::Forms::TextBox());
				 this->truck4 = (gcnew System::Windows::Forms::TextBox());
				 this->Job4 = (gcnew System::Windows::Forms::TextBox());
				 this->customer4 = (gcnew System::Windows::Forms::TextBox());
				 this->addBt4 = (gcnew System::Windows::Forms::Button());
				 this->dischBt4 = (gcnew System::Windows::Forms::Button());
				 this->truckLb4 = (gcnew System::Windows::Forms::Label());
				 this->drops44 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops43 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops42 = (gcnew System::Windows::Forms::RadioButton());
				 this->drops41 = (gcnew System::Windows::Forms::RadioButton());
				 this->JobLb4 = (gcnew System::Windows::Forms::Label());
				 this->cnt4 = (gcnew System::Windows::Forms::Label());
				 this->ticLb4 = (gcnew System::Windows::Forms::Label());
				 this->truckPic4 = (gcnew System::Windows::Forms::PictureBox());
				 this->ticketNum4 = (gcnew System::Windows::Forms::Label());
				 this->label31 = (gcnew System::Windows::Forms::Label());
				 this->targetLb4 = (gcnew System::Windows::Forms::Label());
				 this->matLb4 = (gcnew System::Windows::Forms::Label());
				 this->nextBt4 = (gcnew System::Windows::Forms::Button());
				 this->dropsLb4 = (gcnew System::Windows::Forms::Label());
				 this->scale4 = (gcnew System::Windows::Forms::Label());
				 this->custLb4 = (gcnew System::Windows::Forms::Label());
				 this->pauseBt4 = (gcnew System::Windows::Forms::Button());
				 this->stopBt4 = (gcnew System::Windows::Forms::Button());
				 this->dropBt4 = (gcnew System::Windows::Forms::Button());
				 this->printerLb4 = (gcnew System::Windows::Forms::Label());
				 this->matrixPDMLb = (gcnew System::Windows::Forms::Label());
				 this->copyLane1Lb = (gcnew System::Windows::Forms::Label());
				 this->copyLane2Lb = (gcnew System::Windows::Forms::Label());
				 this->copyLane4Lb = (gcnew System::Windows::Forms::Label());
				 this->copyLane3Lb = (gcnew System::Windows::Forms::Label());
				 this->remLoginBt = (gcnew System::Windows::Forms::Button());
				 this->loginErrLb = (gcnew System::Windows::Forms::Label());
				 this->clinkLb = (gcnew System::Windows::Forms::Label());
				 this->ipAddressLb = (gcnew System::Windows::Forms::Label());
				 this->oldBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
				 this->groupBox3->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy3))->BeginInit();
				 this->groupBoxC->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic3))->BeginInit();
				 this->groupBox1->SuspendLayout();
				 this->groupBoxA->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic1))->BeginInit();
				 this->gBoxLine1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridTruck))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckBindingSource))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic2))->BeginInit();
				 this->groupBox2->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy2))->BeginInit();
				 this->groupBoxB->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer1))->BeginInit();
				 this->menu->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridJob))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->jobBindingSource))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureSplash))->BeginInit();
				 this->groupBox4->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy4))->BeginInit();
				 this->groupBoxD->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic4))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->oldBindingSource))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // groupBox3
				 // 
				 this->groupBox3->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->groupBox3->Controls->Add(this->laneC2ndCB);
				 this->groupBox3->Controls->Add(this->testBox);
				 this->groupBox3->Controls->Add(this->copyLb3);
				 this->groupBox3->Controls->Add(this->numCopy3);
				 this->groupBox3->Controls->Add(this->prod08Lb);
				 this->groupBox3->Controls->Add(this->prod07Lb);
				 this->groupBox3->Controls->Add(this->lane3StatLB);
				 this->groupBox3->Controls->Add(this->lite3);
				 this->groupBox3->Controls->Add(this->webBrowser3);
				 this->groupBox3->Controls->Add(this->safe9);
				 this->groupBox3->Controls->Add(this->safe8);
				 this->groupBox3->Controls->Add(this->safe7);
				 this->groupBox3->Controls->Add(this->laneCCb1);
				 this->groupBox3->Controls->Add(this->laneCCb2);
				 this->groupBox3->Controls->Add(this->taxExempt3);
				 this->groupBox3->Controls->Add(this->groupBoxC);
				 this->groupBox3->Controls->Add(this->pictureBox3);
				 this->groupBox3->Controls->Add(this->label7);
				 this->groupBox3->Controls->Add(this->plant3);
				 this->groupBox3->Controls->Add(this->adapt3);
				 this->groupBox3->Controls->Add(this->all3);
				 this->groupBox3->Controls->Add(this->autoDisch3);
				 this->groupBox3->Controls->Add(this->silo3);
				 this->groupBox3->Controls->Add(this->fill33);
				 this->groupBox3->Controls->Add(this->fill32);
				 this->groupBox3->Controls->Add(this->fill3);
				 this->groupBox3->Controls->Add(this->truckBar3);
				 this->groupBox3->Controls->Add(this->scaleBar3);
				 this->groupBox3->Controls->Add(this->siloBar33);
				 this->groupBox3->Controls->Add(this->siloBar32);
				 this->groupBox3->Controls->Add(this->siloBar3);
				 this->groupBox3->Controls->Add(this->jog3);
				 this->groupBox3->Controls->Add(this->readyBt3);
				 this->groupBox3->Controls->Add(this->autoFall3);
				 this->groupBox3->Controls->Add(this->flow3);
				 this->groupBox3->Controls->Add(this->printOnly3);
				 this->groupBox3->Controls->Add(this->printTarget3);
				 this->groupBox3->Controls->Add(this->tonnage3);
				 this->groupBox3->Controls->Add(this->label11);
				 this->groupBox3->Controls->Add(this->label5);
				 this->groupBox3->Controls->Add(this->man3);
				 this->groupBox3->Controls->Add(this->material3);
				 this->groupBox3->Controls->Add(this->tic_num3);
				 this->groupBox3->Controls->Add(this->target3);
				 this->groupBox3->Controls->Add(this->truck3);
				 this->groupBox3->Controls->Add(this->Job3);
				 this->groupBox3->Controls->Add(this->customer3);
				 this->groupBox3->Controls->Add(this->addBt3);
				 this->groupBox3->Controls->Add(this->dischBt3);
				 this->groupBox3->Controls->Add(this->truckLb3);
				 this->groupBox3->Controls->Add(this->drops34);
				 this->groupBox3->Controls->Add(this->drops33);
				 this->groupBox3->Controls->Add(this->drops32);
				 this->groupBox3->Controls->Add(this->drops31);
				 this->groupBox3->Controls->Add(this->JobLb3);
				 this->groupBox3->Controls->Add(this->cnt3);
				 this->groupBox3->Controls->Add(this->ticLb3);
				 this->groupBox3->Controls->Add(this->truckPic3);
				 this->groupBox3->Controls->Add(this->ticketNum3);
				 this->groupBox3->Controls->Add(this->label13);
				 this->groupBox3->Controls->Add(this->targetLb3);
				 this->groupBox3->Controls->Add(this->matLb3);
				 this->groupBox3->Controls->Add(this->nextBt3);
				 this->groupBox3->Controls->Add(this->dropsLb3);
				 this->groupBox3->Controls->Add(this->scale3);
				 this->groupBox3->Controls->Add(this->custLb3);
				 this->groupBox3->Controls->Add(this->pauseBt3);
				 this->groupBox3->Controls->Add(this->stopBt3);
				 this->groupBox3->Controls->Add(this->dropBt3);
				 this->groupBox3->Controls->Add(this->prod09Lb);
				 this->groupBox3->Controls->Add(this->resetBt3);
				 this->groupBox3->Controls->Add(this->autoBt3);
				 this->groupBox3->Cursor = System::Windows::Forms::Cursors::Default;
				 this->groupBox3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->groupBox3->ForeColor = System::Drawing::Color::DarkRed;
				 this->groupBox3->Location = System::Drawing::Point(860, 27);
				 this->groupBox3->Name = L"groupBox3";
				 this->groupBox3->Size = System::Drawing::Size(400, 840);
				 this->groupBox3->TabIndex = 0;
				 this->groupBox3->TabStop = false;
				 this->groupBox3->Text = L"Lane C";
				 // 
				 // laneC2ndCB
				 // 
				 this->laneC2ndCB->AutoSize = true;
				 this->laneC2ndCB->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneC2ndCB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneC2ndCB->Location = System::Drawing::Point(304, 232);
				 this->laneC2ndCB->Name = L"laneC2ndCB";
				 this->laneC2ndCB->Size = System::Drawing::Size(79, 17);
				 this->laneC2ndCB->TabIndex = 61;
				 this->laneC2ndCB->Text = L"2nd Copy";
				 this->laneC2ndCB->UseVisualStyleBackColor = false;
				 // 
				 // testBox
				 // 
				 this->testBox->BackColor = System::Drawing::Color::Honeydew;
				 this->testBox->Location = System::Drawing::Point(-5, 15);
				 this->testBox->Name = L"testBox";
				 this->testBox->Size = System::Drawing::Size(420, 836);
				 this->testBox->TabIndex = 47;
				 this->testBox->Text = L"";
				 this->testBox->Visible = false;
				 this->testBox->DoubleClick += gcnew System::EventHandler(this, &Form1::testBox_DoubleClick);
				 // 
				 // copyLb3
				 // 
				 this->copyLb3->AutoSize = true;
				 this->copyLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->copyLb3->Location = System::Drawing::Point(338, 202);
				 this->copyLb3->Name = L"copyLb3";
				 this->copyLb3->Size = System::Drawing::Size(49, 13);
				 this->copyLb3->TabIndex = 60;
				 this->copyLb3->Text = L"Tickets";
				 // 
				 // numCopy3
				 // 
				 this->numCopy3->Location = System::Drawing::Point(304, 197);
				 this->numCopy3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
				 this->numCopy3->Name = L"numCopy3";
				 this->numCopy3->Size = System::Drawing::Size(30, 23);
				 this->numCopy3->TabIndex = 59;
				 this->numCopy3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numCopy3->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown2_ValueChanged);
				 // 
				 // prod08Lb
				 // 
				 this->prod08Lb->AutoSize = true;
				 this->prod08Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod08Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod08Lb->ForeColor = System::Drawing::Color::White;
				 this->prod08Lb->Location = System::Drawing::Point(113, 225);
				 this->prod08Lb->Name = L"prod08Lb";
				 this->prod08Lb->Size = System::Drawing::Size(81, 13);
				 this->prod08Lb->TabIndex = 56;
				 this->prod08Lb->Text = L"ABCDABCDA";
				 this->prod08Lb->Visible = false;
				 // 
				 // prod07Lb
				 // 
				 this->prod07Lb->AutoSize = true;
				 this->prod07Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod07Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod07Lb->ForeColor = System::Drawing::Color::White;
				 this->prod07Lb->Location = System::Drawing::Point(11, 225);
				 this->prod07Lb->Name = L"prod07Lb";
				 this->prod07Lb->Size = System::Drawing::Size(81, 13);
				 this->prod07Lb->TabIndex = 56;
				 this->prod07Lb->Text = L"ABCDABCDA";
				 this->prod07Lb->Visible = false;
				 // 
				 // lane3StatLB
				 // 
				 this->lane3StatLB->BackColor = System::Drawing::Color::Gainsboro;
				 this->lane3StatLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->lane3StatLB->ForeColor = System::Drawing::Color::Black;
				 this->lane3StatLB->Location = System::Drawing::Point(68, 1);
				 this->lane3StatLB->Name = L"lane3StatLB";
				 this->lane3StatLB->Size = System::Drawing::Size(50, 13);
				 this->lane3StatLB->TabIndex = 54;
				 this->lane3StatLB->Text = L"S-00";
				 this->lane3StatLB->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->lane3StatLB->Visible = false;
				 // 
				 // lite3
				 // 
				 this->lite3->BackColor = System::Drawing::Color::Transparent;
				 this->lite3->Cursor = System::Windows::Forms::Cursors::No;
				 this->lite3->Enabled = false;
				 this->lite3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->lite3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"lite3.Image")));
				 this->lite3->Location = System::Drawing::Point(6, 592);
				 this->lite3->Name = L"lite3";
				 this->lite3->Size = System::Drawing::Size(48, 48);
				 this->lite3->TabIndex = 33;
				 // 
				 // webBrowser3
				 // 
				 this->webBrowser3->AllowWebBrowserDrop = false;
				 this->webBrowser3->IsWebBrowserContextMenuEnabled = false;
				 this->webBrowser3->Location = System::Drawing::Point(6, 592);
				 this->webBrowser3->MaximumSize = System::Drawing::Size(800, 600);
				 this->webBrowser3->MinimumSize = System::Drawing::Size(20, 20);
				 this->webBrowser3->Name = L"webBrowser3";
				 this->webBrowser3->ScriptErrorsSuppressed = true;
				 this->webBrowser3->Size = System::Drawing::Size(389, 240);
				 this->webBrowser3->TabIndex = 0;
				 this->webBrowser3->TabStop = false;
				 this->webBrowser3->Visible = false;
				 this->webBrowser3->WebBrowserShortcutsEnabled = false;
				 this->webBrowser3->DocumentCompleted += gcnew System::Windows::Forms::WebBrowserDocumentCompletedEventHandler(this, &Form1::webBrowser3_DocumentCompleted);
				 // 
				 // safe9
				 // 
				 this->safe9->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe9.Image")));
				 this->safe9->Location = System::Drawing::Point(250, 190);
				 this->safe9->Name = L"safe9";
				 this->safe9->Size = System::Drawing::Size(24, 24);
				 this->safe9->TabIndex = 53;
				 this->safe9->Visible = false;
				 // 
				 // safe8
				 // 
				 this->safe8->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe8.Image")));
				 this->safe8->Location = System::Drawing::Point(150, 190);
				 this->safe8->Name = L"safe8";
				 this->safe8->Size = System::Drawing::Size(24, 24);
				 this->safe8->TabIndex = 52;
				 this->safe8->Visible = false;
				 // 
				 // safe7
				 // 
				 this->safe7->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe7.Image")));
				 this->safe7->Location = System::Drawing::Point(50, 190);
				 this->safe7->Name = L"safe7";
				 this->safe7->Size = System::Drawing::Size(24, 24);
				 this->safe7->TabIndex = 51;
				 this->safe7->Visible = false;
				 // 
				 // laneCCb1
				 // 
				 this->laneCCb1->AutoSize = true;
				 this->laneCCb1->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneCCb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneCCb1->Location = System::Drawing::Point(303, 170);
				 this->laneCCb1->Name = L"laneCCb1";
				 this->laneCCb1->Size = System::Drawing::Size(41, 17);
				 this->laneCCb1->TabIndex = 50;
				 this->laneCCb1->Text = L"P1";
				 this->laneCCb1->UseVisualStyleBackColor = false;
				 // 
				 // laneCCb2
				 // 
				 this->laneCCb2->AutoSize = true;
				 this->laneCCb2->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneCCb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneCCb2->Location = System::Drawing::Point(351, 170);
				 this->laneCCb2->Name = L"laneCCb2";
				 this->laneCCb2->Size = System::Drawing::Size(41, 17);
				 this->laneCCb2->TabIndex = 49;
				 this->laneCCb2->Text = L"P2";
				 this->laneCCb2->UseVisualStyleBackColor = false;
				 // 
				 // taxExempt3
				 // 
				 this->taxExempt3->AutoSize = true;
				 this->taxExempt3->BackColor = System::Drawing::Color::Gainsboro;
				 this->taxExempt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->taxExempt3->Location = System::Drawing::Point(304, 150);
				 this->taxExempt3->Name = L"taxExempt3";
				 this->taxExempt3->Size = System::Drawing::Size(92, 17);
				 this->taxExempt3->TabIndex = 47;
				 this->taxExempt3->Text = L"Tax Exempt";
				 this->taxExempt3->UseVisualStyleBackColor = false;
				 this->taxExempt3->CheckedChanged += gcnew System::EventHandler(this, &Form1::taxExempt3_CheckedChanged);
				 // 
				 // groupBoxC
				 // 
				 this->groupBoxC->BackColor = System::Drawing::Color::Silver;
				 this->groupBoxC->Controls->Add(this->okC);
				 this->groupBoxC->Controls->Add(this->grossC);
				 this->groupBoxC->Controls->Add(this->tareC);
				 this->groupBoxC->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBoxC->ForeColor = System::Drawing::Color::DarkRed;
				 this->groupBoxC->Location = System::Drawing::Point(98, 306);
				 this->groupBoxC->Name = L"groupBoxC";
				 this->groupBoxC->Size = System::Drawing::Size(204, 60);
				 this->groupBoxC->TabIndex = 46;
				 this->groupBoxC->TabStop = false;
				 this->groupBoxC->Text = L"Tare       Gross";
				 this->groupBoxC->Visible = false;
				 // 
				 // okC
				 // 
				 this->okC->BackColor = System::Drawing::Color::PaleGreen;
				 this->okC->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->okC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->okC->Location = System::Drawing::Point(137, 22);
				 this->okC->Name = L"okC";
				 this->okC->Size = System::Drawing::Size(50, 26);
				 this->okC->TabIndex = 2;
				 this->okC->Text = L"OK";
				 this->okC->UseVisualStyleBackColor = false;
				 this->okC->Click += gcnew System::EventHandler(this, &Form1::okC_Click);
				 // 
				 // grossC
				 // 
				 this->grossC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->grossC->Location = System::Drawing::Point(74, 22);
				 this->grossC->Name = L"grossC";
				 this->grossC->Size = System::Drawing::Size(54, 26);
				 this->grossC->TabIndex = 1;
				 this->grossC->Text = L"xx.xx";
				 this->grossC->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 this->grossC->TextChanged += gcnew System::EventHandler(this, &Form1::grossC_TextChanged);
				 // 
				 // tareC
				 // 
				 this->tareC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tareC->Location = System::Drawing::Point(6, 22);
				 this->tareC->Name = L"tareC";
				 this->tareC->Size = System::Drawing::Size(57, 26);
				 this->tareC->TabIndex = 0;
				 this->tareC->Text = L"xx.xx";
				 this->tareC->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 // 
				 // pictureBox3
				 // 
				 this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox3.Image")));
				 this->pictureBox3->Location = System::Drawing::Point(66, 591);
				 this->pictureBox3->Name = L"pictureBox3";
				 this->pictureBox3->Size = System::Drawing::Size(320, 240);
				 this->pictureBox3->TabIndex = 37;
				 this->pictureBox3->TabStop = false;
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->BackColor = System::Drawing::Color::Transparent;
				 this->label7->Cursor = System::Windows::Forms::Cursors::No;
				 this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label7->ForeColor = System::Drawing::Color::DarkRed;
				 this->label7->Location = System::Drawing::Point(142, 104);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(36, 13);
				 this->label7->TabIndex = 34;
				 this->label7->Text = L"Plant";
				 this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->label7->Click += gcnew System::EventHandler(this, &Form1::label7_Click);
				 // 
				 // plant3
				 // 
				 this->plant3->BackColor = System::Drawing::Color::Gainsboro;
				 this->plant3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->plant3->Cursor = System::Windows::Forms::Cursors::No;
				 this->plant3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->plant3->ForeColor = System::Drawing::Color::Black;
				 this->plant3->Location = System::Drawing::Point(178, 100);
				 this->plant3->Name = L"plant3";
				 this->plant3->Size = System::Drawing::Size(30, 24);
				 this->plant3->TabIndex = 33;
				 this->plant3->Text = L"00";
				 this->plant3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // adapt3
				 // 
				 this->adapt3->AutoSize = true;
				 this->adapt3->BackColor = System::Drawing::Color::Gainsboro;
				 this->adapt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->adapt3->Location = System::Drawing::Point(304, 230);
				 this->adapt3->Name = L"adapt3";
				 this->adapt3->Size = System::Drawing::Size(76, 17);
				 this->adapt3->TabIndex = 32;
				 this->adapt3->Text = L"Adaptive";
				 this->adapt3->UseVisualStyleBackColor = false;
				 this->adapt3->CheckedChanged += gcnew System::EventHandler(this, &Form1::adapt3_CheckedChanged);
				 // 
				 // all3
				 // 
				 this->all3->BackColor = System::Drawing::Color::Transparent;
				 this->all3->Enabled = false;
				 this->all3->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->all3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->all3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->all3->ForeColor = System::Drawing::Color::Black;
				 this->all3->Location = System::Drawing::Point(339, 16);
				 this->all3->Name = L"all3";
				 this->all3->Size = System::Drawing::Size(46, 30);
				 this->all3->TabIndex = 31;
				 this->all3->Text = L"ALL";
				 this->all3->UseVisualStyleBackColor = false;
				 this->all3->Click += gcnew System::EventHandler(this, &Form1::all3_Click);
				 // 
				 // autoDisch3
				 // 
				 this->autoDisch3->AutoSize = true;
				 this->autoDisch3->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoDisch3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoDisch3->Location = System::Drawing::Point(304, 190);
				 this->autoDisch3->Name = L"autoDisch3";
				 this->autoDisch3->Size = System::Drawing::Size(88, 17);
				 this->autoDisch3->TabIndex = 29;
				 this->autoDisch3->Text = L"Auto Disch";
				 this->autoDisch3->UseVisualStyleBackColor = false;
				 this->autoDisch3->Visible = false;
				 this->autoDisch3->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoDisch3_CheckedChanged);
				 // 
				 // silo3
				 // 
				 this->silo3->BackColor = System::Drawing::Color::Gainsboro;
				 this->silo3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->silo3->ForeColor = System::Drawing::Color::Black;
				 this->silo3->Location = System::Drawing::Point(116, 476);
				 this->silo3->Name = L"silo3";
				 this->silo3->Size = System::Drawing::Size(38, 20);
				 this->silo3->TabIndex = 28;
				 this->silo3->Text = L"0000";
				 this->silo3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->silo3->Visible = false;
				 // 
				 // fill33
				 // 
				 this->fill33->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill33.Image")));
				 this->fill33->Location = System::Drawing::Point(270, 190);
				 this->fill33->Name = L"fill33";
				 this->fill33->Size = System::Drawing::Size(24, 24);
				 this->fill33->TabIndex = 27;
				 this->fill33->Visible = false;
				 // 
				 // fill32
				 // 
				 this->fill32->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill32.Image")));
				 this->fill32->Location = System::Drawing::Point(170, 190);
				 this->fill32->Name = L"fill32";
				 this->fill32->Size = System::Drawing::Size(24, 24);
				 this->fill32->TabIndex = 26;
				 this->fill32->Visible = false;
				 // 
				 // fill3
				 // 
				 this->fill3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill3.Image")));
				 this->fill3->Location = System::Drawing::Point(70, 190);
				 this->fill3->Name = L"fill3";
				 this->fill3->Size = System::Drawing::Size(24, 24);
				 this->fill3->TabIndex = 22;
				 this->fill3->Visible = false;
				 // 
				 // truckBar3
				 // 
				 this->truckBar3->BarColor = System::Drawing::Color::MistyRose;
				 this->truckBar3->BorderColor = System::Drawing::Color::Black;
				 this->truckBar3->FillStyle = As::BarCtl::FillStyles::Dashed;
				 this->truckBar3->Flow = 0;
				 this->truckBar3->Location = System::Drawing::Point(12, 496);
				 this->truckBar3->Maximum = 100;
				 this->truckBar3->Name = L"truckBar3";
				 this->truckBar3->Pct = 0;
				 this->truckBar3->ScaleInLB = false;
				 this->truckBar3->Separators = 0;
				 this->truckBar3->Size = System::Drawing::Size(80, 28);
				 this->truckBar3->TabIndex = 21;
				 this->truckBar3->Target = 10;
				 this->truckBar3->Text = L"barCtl1";
				 this->truckBar3->Value = 0;
				 this->truckBar3->Vertical = false;
				 // 
				 // scaleBar3
				 // 
				 this->scaleBar3->BackColor = System::Drawing::Color::LightGray;
				 this->scaleBar3->BarColor = System::Drawing::Color::Gainsboro;
				 this->scaleBar3->BorderColor = System::Drawing::Color::Black;
				 this->scaleBar3->Flow = 0;
				 this->scaleBar3->Idle = false;
				 this->scaleBar3->Label = 0;
				 this->scaleBar3->Location = System::Drawing::Point(12, 436);
				 this->scaleBar3->Maximum = 100;
				 this->scaleBar3->Metric = false;
				 this->scaleBar3->Name = L"scaleBar3";
				 this->scaleBar3->Open = false;
				 this->scaleBar3->ScaleInLB = false;
				 this->scaleBar3->Size = System::Drawing::Size(100, 52);
				 this->scaleBar3->TabIndex = 20;
				 this->scaleBar3->Target = 0;
				 this->scaleBar3->Topl = 0;
				 this->scaleBar3->Value = 0;
				 // 
				 // siloBar33
				 // 
				 this->siloBar33->Add = false;
				 this->siloBar33->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar33->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar33->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar33->Count = 0;
				 this->siloBar33->Delay = false;
				 this->siloBar33->DisableInv = false;
				 this->siloBar33->Empty = false;
				 this->siloBar33->Idle = true;
				 this->siloBar33->Inventory = 100;
				 this->siloBar33->Location = System::Drawing::Point(210, 196);
				 this->siloBar33->Maximum = 100;
				 this->siloBar33->Metric = false;
				 this->siloBar33->Name = L"siloBar33";
				 this->siloBar33->Number = 9;
				 this->siloBar33->Open = false;
				 this->siloBar33->ScaleInLB = false;
				 this->siloBar33->Separators = 4;
				 this->siloBar33->Size = System::Drawing::Size(88, 230);
				 this->siloBar33->TabIndex = 19;
				 this->siloBar33->Target = 0;
				 this->siloBar33->Text = L"Silo9";
				 this->siloBar33->Tol = false;
				 this->siloBar33->ValMan = 0;
				 this->siloBar33->Value = 0;
				 this->siloBar33->Visible = false;
				 this->siloBar33->DoubleClick += gcnew System::EventHandler(this, &Form1::flow9_Click);
				 this->siloBar33->Click += gcnew System::EventHandler(this, &Form1::siloBar33_Click);
				 // 
				 // siloBar32
				 // 
				 this->siloBar32->Add = false;
				 this->siloBar32->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar32->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar32->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar32->Count = 0;
				 this->siloBar32->Delay = false;
				 this->siloBar32->DisableInv = false;
				 this->siloBar32->Empty = false;
				 this->siloBar32->Idle = true;
				 this->siloBar32->Inventory = 100;
				 this->siloBar32->Location = System::Drawing::Point(110, 196);
				 this->siloBar32->Maximum = 100;
				 this->siloBar32->Metric = false;
				 this->siloBar32->Name = L"siloBar32";
				 this->siloBar32->Number = 8;
				 this->siloBar32->Open = false;
				 this->siloBar32->ScaleInLB = false;
				 this->siloBar32->Separators = 4;
				 this->siloBar32->Size = System::Drawing::Size(88, 230);
				 this->siloBar32->TabIndex = 18;
				 this->siloBar32->Target = 0;
				 this->siloBar32->Text = L"Silo8";
				 this->siloBar32->Tol = false;
				 this->siloBar32->ValMan = 0;
				 this->siloBar32->Value = 0;
				 this->siloBar32->Visible = false;
				 this->siloBar32->DoubleClick += gcnew System::EventHandler(this, &Form1::flow8_Click);
				 this->siloBar32->Click += gcnew System::EventHandler(this, &Form1::siloBar32_Click);
				 // 
				 // siloBar3
				 // 
				 this->siloBar3->Add = false;
				 this->siloBar3->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar3->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar3->BorderColor = System::Drawing::Color::Black;
				 this->siloBar3->Count = 0;
				 this->siloBar3->Delay = false;
				 this->siloBar3->DisableInv = false;
				 this->siloBar3->Empty = false;
				 this->siloBar3->Idle = false;
				 this->siloBar3->Inventory = 100;
				 this->siloBar3->Location = System::Drawing::Point(10, 196);
				 this->siloBar3->Maximum = 100;
				 this->siloBar3->Metric = false;
				 this->siloBar3->Name = L"siloBar3";
				 this->siloBar3->Number = 7;
				 this->siloBar3->Open = false;
				 this->siloBar3->ScaleInLB = false;
				 this->siloBar3->Separators = 4;
				 this->siloBar3->Size = System::Drawing::Size(88, 230);
				 this->siloBar3->TabIndex = 17;
				 this->siloBar3->Target = 0;
				 this->siloBar3->Text = L"Silo7";
				 this->siloBar3->Tol = false;
				 this->siloBar3->ValMan = 0;
				 this->siloBar3->Value = 0;
				 this->siloBar3->DoubleClick += gcnew System::EventHandler(this, &Form1::flow7_Click);
				 this->siloBar3->Click += gcnew System::EventHandler(this, &Form1::siloBar3_Click);
				 // 
				 // jog3
				 // 
				 this->jog3->AutoSize = true;
				 this->jog3->BackColor = System::Drawing::Color::Gainsboro;
				 this->jog3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->jog3->Location = System::Drawing::Point(304, 250);
				 this->jog3->Name = L"jog3";
				 this->jog3->Size = System::Drawing::Size(46, 17);
				 this->jog3->TabIndex = 11;
				 this->jog3->Text = L"Jog";
				 this->jog3->UseVisualStyleBackColor = false;
				 this->jog3->CheckedChanged += gcnew System::EventHandler(this, &Form1::jog3_CheckedChanged);
				 // 
				 // readyBt3
				 // 
				 this->readyBt3->BackColor = System::Drawing::Color::Transparent;
				 this->readyBt3->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->readyBt3->Enabled = false;
				 this->readyBt3->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->readyBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->readyBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->readyBt3->ForeColor = System::Drawing::Color::Black;
				 this->readyBt3->Location = System::Drawing::Point(310, 270);
				 this->readyBt3->Name = L"readyBt3";
				 this->readyBt3->Size = System::Drawing::Size(75, 30);
				 this->readyBt3->TabIndex = 10;
				 this->readyBt3->Text = L"READY";
				 this->readyBt3->UseVisualStyleBackColor = false;
				 this->readyBt3->Click += gcnew System::EventHandler(this, &Form1::readyBt3_Click);
				 // 
				 // autoFall3
				 // 
				 this->autoFall3->AutoSize = true;
				 this->autoFall3->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoFall3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoFall3->Location = System::Drawing::Point(304, 210);
				 this->autoFall3->Name = L"autoFall3";
				 this->autoFall3->Size = System::Drawing::Size(76, 17);
				 this->autoFall3->TabIndex = 9;
				 this->autoFall3->Text = L"Auto Fall";
				 this->autoFall3->UseVisualStyleBackColor = false;
				 this->autoFall3->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoFall3_CheckedChanged);
				 // 
				 // flow3
				 // 
				 this->flow3->BackColor = System::Drawing::Color::PaleGreen;
				 this->flow3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->flow3->ForeColor = System::Drawing::Color::Black;
				 this->flow3->Location = System::Drawing::Point(157, 476);
				 this->flow3->Name = L"flow3";
				 this->flow3->Size = System::Drawing::Size(38, 20);
				 this->flow3->TabIndex = 8;
				 this->flow3->Text = L"0000";
				 this->flow3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->flow3->Visible = false;
				 this->flow3->Click += gcnew System::EventHandler(this, &Form1::flow3_Click);
				 // 
				 // printOnly3
				 // 
				 this->printOnly3->BackColor = System::Drawing::Color::Transparent;
				 this->printOnly3->Cursor = System::Windows::Forms::Cursors::Default;
				 this->printOnly3->Enabled = false;
				 this->printOnly3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->printOnly3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printOnly3->ForeColor = System::Drawing::Color::Black;
				 this->printOnly3->Location = System::Drawing::Point(310, 308);
				 this->printOnly3->Name = L"printOnly3";
				 this->printOnly3->Size = System::Drawing::Size(75, 30);
				 this->printOnly3->TabIndex = 0;
				 this->printOnly3->Text = L"PrintOnly";
				 this->printOnly3->UseVisualStyleBackColor = false;
				 this->printOnly3->Click += gcnew System::EventHandler(this, &Form1::printOnly3_Click);
				 // 
				 // printTarget3
				 // 
				 this->printTarget3->AutoSize = true;
				 this->printTarget3->BackColor = System::Drawing::Color::Gainsboro;
				 this->printTarget3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printTarget3->Location = System::Drawing::Point(304, 130);
				 this->printTarget3->Name = L"printTarget3";
				 this->printTarget3->Size = System::Drawing::Size(93, 17);
				 this->printTarget3->TabIndex = 0;
				 this->printTarget3->Text = L"Print Target";
				 this->printTarget3->UseVisualStyleBackColor = false;
				 this->printTarget3->CheckedChanged += gcnew System::EventHandler(this, &Form1::printTarget3_CheckedChanged);
				 // 
				 // tonnage3
				 // 
				 this->tonnage3->BackColor = System::Drawing::Color::MistyRose;
				 this->tonnage3->Cursor = System::Windows::Forms::Cursors::No;
				 this->tonnage3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tonnage3->ForeColor = System::Drawing::Color::Black;
				 this->tonnage3->Location = System::Drawing::Point(206, 147);
				 this->tonnage3->Name = L"tonnage3";
				 this->tonnage3->Size = System::Drawing::Size(84, 32);
				 this->tonnage3->TabIndex = 0;
				 this->tonnage3->Text = L"1234.0";
				 this->tonnage3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->tonnage3->Click += gcnew System::EventHandler(this, &Form1::tonnage3_Click);
				 // 
				 // label11
				 // 
				 this->label11->AutoEllipsis = true;
				 this->label11->AutoSize = true;
				 this->label11->Cursor = System::Windows::Forms::Cursors::No;
				 this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label11->Location = System::Drawing::Point(148, 150);
				 this->label11->Name = L"label11";
				 this->label11->Size = System::Drawing::Size(57, 26);
				 this->label11->TabIndex = 0;
				 this->label11->Text = L"Today\'s\r\nTonnage";
				 this->label11->Click += gcnew System::EventHandler(this, &Form1::label11_Click);
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->BackColor = System::Drawing::Color::Transparent;
				 this->label5->Cursor = System::Windows::Forms::Cursors::No;
				 this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label5->ForeColor = System::Drawing::Color::DarkRed;
				 this->label5->Location = System::Drawing::Point(216, 88);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(37, 13);
				 this->label5->TabIndex = 0;
				 this->label5->Text = L"Done";
				 // 
				 // man3
				 // 
				 this->man3->BackColor = System::Drawing::Color::MistyRose;
				 this->man3->Cursor = System::Windows::Forms::Cursors::No;
				 this->man3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->man3->ForeColor = System::Drawing::Color::Black;
				 this->man3->Location = System::Drawing::Point(220, 104);
				 this->man3->Name = L"man3";
				 this->man3->Size = System::Drawing::Size(70, 28);
				 this->man3->TabIndex = 0;
				 this->man3->Text = L"000";
				 this->man3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // material3
				 // 
				 this->material3->BackColor = System::Drawing::Color::Gainsboro;
				 this->material3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->material3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->material3->Location = System::Drawing::Point(68, 72);
				 this->material3->MaxLength = 10;
				 this->material3->Name = L"material3";
				 this->material3->ReadOnly = true;
				 this->material3->Size = System::Drawing::Size(92, 23);
				 this->material3->TabIndex = 3;
				 this->material3->Text = L"1234567890";
				 this->material3->TextChanged += gcnew System::EventHandler(this, &Form1::material3_TextChanged);
				 // 
				 // tic_num3
				 // 
				 this->tic_num3->BackColor = System::Drawing::Color::Gainsboro;
				 this->tic_num3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->tic_num3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tic_num3->Location = System::Drawing::Point(68, 100);
				 this->tic_num3->MaxLength = 8;
				 this->tic_num3->Name = L"tic_num3";
				 this->tic_num3->ReadOnly = true;
				 this->tic_num3->Size = System::Drawing::Size(72, 23);
				 this->tic_num3->TabIndex = 4;
				 this->tic_num3->TabStop = false;
				 this->tic_num3->Text = L"12345678";
				 // 
				 // target3
				 // 
				 this->target3->BackColor = System::Drawing::Color::White;
				 this->target3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->target3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->target3->Location = System::Drawing::Point(82, 156);
				 this->target3->MaxLength = 6;
				 this->target3->Name = L"target3";
				 this->target3->Size = System::Drawing::Size(50, 23);
				 this->target3->TabIndex = 6;
				 this->target3->Text = L"00.00";
				 this->target3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 // 
				 // truck3
				 // 
				 this->truck3->BackColor = System::Drawing::Color::White;
				 this->truck3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->truck3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->truck3->Location = System::Drawing::Point(68, 128);
				 this->truck3->MaxLength = 9;
				 this->truck3->Name = L"truck3";
				 this->truck3->Size = System::Drawing::Size(78, 23);
				 this->truck3->TabIndex = 5;
				 this->truck3->Text = L"012345678";
				 this->truck3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::truckNum3_MouseDoubleClick);
				 // 
				 // Job3
				 // 
				 this->Job3->BackColor = System::Drawing::Color::Gainsboro;
				 this->Job3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->Job3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->Job3->Location = System::Drawing::Point(68, 44);
				 this->Job3->MaxLength = 16;
				 this->Job3->Name = L"Job3";
				 this->Job3->ReadOnly = true;
				 this->Job3->Size = System::Drawing::Size(136, 23);
				 this->Job3->TabIndex = 2;
				 this->Job3->Text = L"0123456789abcdef";
				 // 
				 // customer3
				 // 
				 this->customer3->BackColor = System::Drawing::Color::Gainsboro;
				 this->customer3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->customer3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->customer3->Location = System::Drawing::Point(68, 16);
				 this->customer3->MaxLength = 32;
				 this->customer3->Name = L"customer3";
				 this->customer3->ReadOnly = true;
				 this->customer3->Size = System::Drawing::Size(264, 23);
				 this->customer3->TabIndex = 1;
				 this->customer3->Text = L"0123456789abcdef0123456789abcdef";
				 this->customer3->TextChanged += gcnew System::EventHandler(this, &Form1::customer3_TextChanged);
				 // 
				 // addBt3
				 // 
				 this->addBt3->BackColor = System::Drawing::Color::Transparent;
				 this->addBt3->Enabled = false;
				 this->addBt3->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->addBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->addBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->addBt3->ForeColor = System::Drawing::Color::Black;
				 this->addBt3->Location = System::Drawing::Point(310, 474);
				 this->addBt3->Name = L"addBt3";
				 this->addBt3->Size = System::Drawing::Size(75, 30);
				 this->addBt3->TabIndex = 0;
				 this->addBt3->Text = L"ADD";
				 this->addBt3->UseVisualStyleBackColor = false;
				 this->addBt3->Visible = false;
				 this->addBt3->Click += gcnew System::EventHandler(this, &Form1::addBt3_Click);
				 // 
				 // dischBt3
				 // 
				 this->dischBt3->BackColor = System::Drawing::Color::Transparent;
				 this->dischBt3->Enabled = false;
				 this->dischBt3->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dischBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dischBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dischBt3->ForeColor = System::Drawing::Color::Black;
				 this->dischBt3->Location = System::Drawing::Point(226, 438);
				 this->dischBt3->Name = L"dischBt3";
				 this->dischBt3->Size = System::Drawing::Size(75, 30);
				 this->dischBt3->TabIndex = 0;
				 this->dischBt3->Text = L"DISCH";
				 this->dischBt3->UseVisualStyleBackColor = false;
				 this->dischBt3->Visible = false;
				 this->dischBt3->Click += gcnew System::EventHandler(this, &Form1::dischBt3_Click);
				 // 
				 // truckLb3
				 // 
				 this->truckLb3->AutoSize = true;
				 this->truckLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->truckLb3->Location = System::Drawing::Point(6, 133);
				 this->truckLb3->Name = L"truckLb3";
				 this->truckLb3->Size = System::Drawing::Size(55, 13);
				 this->truckLb3->TabIndex = 0;
				 this->truckLb3->Text = L"Truck Id";
				 // 
				 // drops34
				 // 
				 this->drops34->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops34->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops34->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops34->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops34->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops34->ForeColor = System::Drawing::Color::Black;
				 this->drops34->Location = System::Drawing::Point(351, 397);
				 this->drops34->Name = L"drops34";
				 this->drops34->Size = System::Drawing::Size(32, 32);
				 this->drops34->TabIndex = 0;
				 this->drops34->Text = L"4";
				 this->drops34->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops34->UseVisualStyleBackColor = true;
				 this->drops34->Click += gcnew System::EventHandler(this, &Form1::drops34_Click);
				 // 
				 // drops33
				 // 
				 this->drops33->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops33->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops33->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops33->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops33->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops33->ForeColor = System::Drawing::Color::Black;
				 this->drops33->Location = System::Drawing::Point(315, 397);
				 this->drops33->Name = L"drops33";
				 this->drops33->Size = System::Drawing::Size(32, 32);
				 this->drops33->TabIndex = 0;
				 this->drops33->Text = L"3";
				 this->drops33->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops33->UseVisualStyleBackColor = true;
				 this->drops33->Click += gcnew System::EventHandler(this, &Form1::drops33_Click);
				 // 
				 // drops32
				 // 
				 this->drops32->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops32->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops32->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops32->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops32->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops32->ForeColor = System::Drawing::Color::Black;
				 this->drops32->Location = System::Drawing::Point(351, 362);
				 this->drops32->Name = L"drops32";
				 this->drops32->Size = System::Drawing::Size(32, 32);
				 this->drops32->TabIndex = 0;
				 this->drops32->Text = L"2";
				 this->drops32->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops32->UseVisualStyleBackColor = true;
				 this->drops32->Click += gcnew System::EventHandler(this, &Form1::drops32_Click);
				 // 
				 // drops31
				 // 
				 this->drops31->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops31->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops31->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops31->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops31->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops31->ForeColor = System::Drawing::Color::Black;
				 this->drops31->Location = System::Drawing::Point(315, 362);
				 this->drops31->Name = L"drops31";
				 this->drops31->Size = System::Drawing::Size(32, 32);
				 this->drops31->TabIndex = 0;
				 this->drops31->Text = L"1";
				 this->drops31->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops31->UseVisualStyleBackColor = true;
				 this->drops31->Click += gcnew System::EventHandler(this, &Form1::drops31_Click);
				 // 
				 // JobLb3
				 // 
				 this->JobLb3->AutoSize = true;
				 this->JobLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->JobLb3->Location = System::Drawing::Point(6, 48);
				 this->JobLb3->Name = L"JobLb3";
				 this->JobLb3->Size = System::Drawing::Size(27, 13);
				 this->JobLb3->TabIndex = 0;
				 this->JobLb3->Text = L"Job";
				 // 
				 // cnt3
				 // 
				 this->cnt3->BackColor = System::Drawing::Color::Aquamarine;
				 this->cnt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->cnt3->ForeColor = System::Drawing::Color::Black;
				 this->cnt3->Location = System::Drawing::Point(199, 476);
				 this->cnt3->Name = L"cnt3";
				 this->cnt3->Size = System::Drawing::Size(50, 20);
				 this->cnt3->TabIndex = 0;
				 this->cnt3->Text = L"012345";
				 this->cnt3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->cnt3->Visible = false;
				 // 
				 // ticLb3
				 // 
				 this->ticLb3->AutoSize = true;
				 this->ticLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticLb3->Location = System::Drawing::Point(6, 104);
				 this->ticLb3->Name = L"ticLb3";
				 this->ticLb3->Size = System::Drawing::Size(55, 13);
				 this->ticLb3->TabIndex = 0;
				 this->ticLb3->Text = L"Ticket #";
				 // 
				 // truckPic3
				 // 
				 this->truckPic3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"truckPic3.BackgroundImage")));
				 this->truckPic3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->truckPic3->Location = System::Drawing::Point(23, 528);
				 this->truckPic3->Name = L"truckPic3";
				 this->truckPic3->Size = System::Drawing::Size(78, 57);
				 this->truckPic3->TabIndex = 0;
				 this->truckPic3->TabStop = false;
				 // 
				 // ticketNum3
				 // 
				 this->ticketNum3->BackColor = System::Drawing::Color::MistyRose;
				 this->ticketNum3->Cursor = System::Windows::Forms::Cursors::No;
				 this->ticketNum3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticketNum3->ForeColor = System::Drawing::Color::Black;
				 this->ticketNum3->Location = System::Drawing::Point(249, 55);
				 this->ticketNum3->Name = L"ticketNum3";
				 this->ticketNum3->Size = System::Drawing::Size(40, 28);
				 this->ticketNum3->TabIndex = 0;
				 this->ticketNum3->Text = L"000";
				 this->ticketNum3->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // label13
				 // 
				 this->label13->AutoSize = true;
				 this->label13->BackColor = System::Drawing::Color::Transparent;
				 this->label13->Cursor = System::Windows::Forms::Cursors::No;
				 this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label13->ForeColor = System::Drawing::Color::DarkRed;
				 this->label13->Location = System::Drawing::Point(215, 59);
				 this->label13->Name = L"label13";
				 this->label13->Size = System::Drawing::Size(32, 13);
				 this->label13->TabIndex = 0;
				 this->label13->Text = L"New";
				 this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 // 
				 // targetLb3
				 // 
				 this->targetLb3->AutoSize = true;
				 this->targetLb3->BackColor = System::Drawing::Color::Transparent;
				 this->targetLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->targetLb3->ForeColor = System::Drawing::Color::DarkRed;
				 this->targetLb3->Location = System::Drawing::Point(6, 160);
				 this->targetLb3->Name = L"targetLb3";
				 this->targetLb3->Size = System::Drawing::Size(44, 13);
				 this->targetLb3->TabIndex = 0;
				 this->targetLb3->Text = L"Target";
				 // 
				 // matLb3
				 // 
				 this->matLb3->AutoSize = true;
				 this->matLb3->BackColor = System::Drawing::Color::Transparent;
				 this->matLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->matLb3->ForeColor = System::Drawing::Color::DarkRed;
				 this->matLb3->Location = System::Drawing::Point(6, 76);
				 this->matLb3->Name = L"matLb3";
				 this->matLb3->Size = System::Drawing::Size(52, 13);
				 this->matLb3->TabIndex = 0;
				 this->matLb3->Text = L"Material";
				 // 
				 // nextBt3
				 // 
				 this->nextBt3->BackColor = System::Drawing::Color::Transparent;
				 this->nextBt3->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->nextBt3->Enabled = false;
				 this->nextBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->nextBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->nextBt3->ForeColor = System::Drawing::Color::Black;
				 this->nextBt3->Location = System::Drawing::Point(303, 55);
				 this->nextBt3->Name = L"nextBt3";
				 this->nextBt3->Size = System::Drawing::Size(82, 30);
				 this->nextBt3->TabIndex = 0;
				 this->nextBt3->Text = L"NEXT ";
				 this->nextBt3->UseVisualStyleBackColor = false;
				 this->nextBt3->Click += gcnew System::EventHandler(this, &Form1::nextBt3_Click);
				 // 
				 // dropsLb3
				 // 
				 this->dropsLb3->AutoSize = true;
				 this->dropsLb3->BackColor = System::Drawing::Color::Transparent;
				 this->dropsLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropsLb3->ForeColor = System::Drawing::Color::DarkRed;
				 this->dropsLb3->Location = System::Drawing::Point(325, 344);
				 this->dropsLb3->Name = L"dropsLb3";
				 this->dropsLb3->Size = System::Drawing::Size(40, 13);
				 this->dropsLb3->TabIndex = 0;
				 this->dropsLb3->Text = L"Drops";
				 // 
				 // scale3
				 // 
				 this->scale3->BackColor = System::Drawing::Color::PaleGreen;
				 this->scale3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->scale3->ForeColor = System::Drawing::Color::Black;
				 this->scale3->Location = System::Drawing::Point(116, 440);
				 this->scale3->Name = L"scale3";
				 this->scale3->Size = System::Drawing::Size(100, 20);
				 this->scale3->TabIndex = 0;
				 this->scale3->Text = L"0123456789012";
				 this->scale3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->scale3->Visible = false;
				 // 
				 // custLb3
				 // 
				 this->custLb3->AutoSize = true;
				 this->custLb3->BackColor = System::Drawing::Color::Transparent;
				 this->custLb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->custLb3->ForeColor = System::Drawing::Color::DarkRed;
				 this->custLb3->Location = System::Drawing::Point(6, 23);
				 this->custLb3->Name = L"custLb3";
				 this->custLb3->Size = System::Drawing::Size(59, 13);
				 this->custLb3->TabIndex = 0;
				 this->custLb3->Text = L"Customer";
				 // 
				 // pauseBt3
				 // 
				 this->pauseBt3->BackColor = System::Drawing::Color::Gold;
				 this->pauseBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->pauseBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->pauseBt3->ForeColor = System::Drawing::Color::Black;
				 this->pauseBt3->Location = System::Drawing::Point(310, 511);
				 this->pauseBt3->Name = L"pauseBt3";
				 this->pauseBt3->Size = System::Drawing::Size(75, 30);
				 this->pauseBt3->TabIndex = 0;
				 this->pauseBt3->Text = L"HOLD";
				 this->pauseBt3->UseVisualStyleBackColor = false;
				 this->pauseBt3->Click += gcnew System::EventHandler(this, &Form1::pause3_Click);
				 // 
				 // stopBt3
				 // 
				 this->stopBt3->BackColor = System::Drawing::Color::Red;
				 this->stopBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->stopBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->stopBt3->ForeColor = System::Drawing::Color::Black;
				 this->stopBt3->Location = System::Drawing::Point(310, 547);
				 this->stopBt3->Name = L"stopBt3";
				 this->stopBt3->Size = System::Drawing::Size(75, 30);
				 this->stopBt3->TabIndex = 0;
				 this->stopBt3->Text = L"ABORT";
				 this->stopBt3->UseVisualStyleBackColor = false;
				 this->stopBt3->Click += gcnew System::EventHandler(this, &Form1::stopBt3_Click);
				 // 
				 // dropBt3
				 // 
				 this->dropBt3->BackColor = System::Drawing::Color::Transparent;
				 this->dropBt3->Enabled = false;
				 this->dropBt3->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dropBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dropBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropBt3->ForeColor = System::Drawing::Color::Black;
				 this->dropBt3->Location = System::Drawing::Point(310, 438);
				 this->dropBt3->Name = L"dropBt3";
				 this->dropBt3->Size = System::Drawing::Size(75, 30);
				 this->dropBt3->TabIndex = 0;
				 this->dropBt3->Text = L"DROP";
				 this->dropBt3->UseVisualStyleBackColor = false;
				 this->dropBt3->Click += gcnew System::EventHandler(this, &Form1::dropBt3_Click);
				 // 
				 // prod09Lb
				 // 
				 this->prod09Lb->AutoSize = true;
				 this->prod09Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod09Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod09Lb->ForeColor = System::Drawing::Color::White;
				 this->prod09Lb->Location = System::Drawing::Point(213, 225);
				 this->prod09Lb->Name = L"prod09Lb";
				 this->prod09Lb->Size = System::Drawing::Size(81, 13);
				 this->prod09Lb->TabIndex = 56;
				 this->prod09Lb->Text = L"ABCDABCDA";
				 this->prod09Lb->Visible = false;
				 // 
				 // resetBt3
				 // 
				 this->resetBt3->BackColor = System::Drawing::Color::Red;
				 this->resetBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->resetBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->resetBt3->ForeColor = System::Drawing::Color::Black;
				 this->resetBt3->Location = System::Drawing::Point(306, 94);
				 this->resetBt3->Name = L"resetBt3";
				 this->resetBt3->Size = System::Drawing::Size(75, 30);
				 this->resetBt3->TabIndex = 63;
				 this->resetBt3->Text = L"RESET";
				 this->resetBt3->UseVisualStyleBackColor = false;
				 this->resetBt3->Click += gcnew System::EventHandler(this, &Form1::resetBt3_Click);
				 // 
				 // autoBt3
				 // 
				 this->autoBt3->BackColor = System::Drawing::Color::Transparent;
				 this->autoBt3->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->autoBt3->Enabled = false;
				 this->autoBt3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->autoBt3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoBt3->ForeColor = System::Drawing::Color::DarkRed;
				 this->autoBt3->Location = System::Drawing::Point(303, 94);
				 this->autoBt3->Name = L"autoBt3";
				 this->autoBt3->Size = System::Drawing::Size(82, 30);
				 this->autoBt3->TabIndex = 0;
				 this->autoBt3->Text = L"MANUAL";
				 this->autoBt3->UseVisualStyleBackColor = false;
				 this->autoBt3->Click += gcnew System::EventHandler(this, &Form1::autoBt3_Click);
				 // 
				 // zoom3
				 // 
				 this->zoom3->BackColor = System::Drawing::Color::Gainsboro;
				 this->zoom3->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->zoom3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->zoom3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->zoom3->ForeColor = System::Drawing::Color::Black;
				 this->zoom3->Location = System::Drawing::Point(866, 828);
				 this->zoom3->Name = L"zoom3";
				 this->zoom3->Size = System::Drawing::Size(48, 30);
				 this->zoom3->TabIndex = 30;
				 this->zoom3->Text = L"Zoom";
				 this->zoom3->UseVisualStyleBackColor = false;
				 this->zoom3->Visible = false;
				 this->zoom3->Click += gcnew System::EventHandler(this, &Form1::zoom3_Click);
				 // 
				 // ticketNum1
				 // 
				 this->ticketNum1->BackColor = System::Drawing::Color::LightBlue;
				 this->ticketNum1->Cursor = System::Windows::Forms::Cursors::No;
				 this->ticketNum1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->ticketNum1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticketNum1->ForeColor = System::Drawing::Color::Black;
				 this->ticketNum1->Location = System::Drawing::Point(249, 55);
				 this->ticketNum1->Name = L"ticketNum1";
				 this->ticketNum1->Size = System::Drawing::Size(40, 28);
				 this->ticketNum1->TabIndex = 0;
				 this->ticketNum1->Text = L"000";
				 this->ticketNum1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // nextBt1
				 // 
				 this->nextBt1->BackColor = System::Drawing::Color::Transparent;
				 this->nextBt1->Enabled = false;
				 this->nextBt1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->nextBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->nextBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->nextBt1->ForeColor = System::Drawing::Color::Black;
				 this->nextBt1->Location = System::Drawing::Point(6, 51);
				 this->nextBt1->Name = L"nextBt1";
				 this->nextBt1->Size = System::Drawing::Size(82, 30);
				 this->nextBt1->TabIndex = 0;
				 this->nextBt1->Text = L"NEXT ";
				 this->nextBt1->UseVisualStyleBackColor = false;
				 this->nextBt1->Click += gcnew System::EventHandler(this, &Form1::nextBt1_Click);
				 // 
				 // dropsLb1
				 // 
				 this->dropsLb1->AutoSize = true;
				 this->dropsLb1->BackColor = System::Drawing::Color::Transparent;
				 this->dropsLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropsLb1->ForeColor = System::Drawing::Color::MediumBlue;
				 this->dropsLb1->Location = System::Drawing::Point(28, 340);
				 this->dropsLb1->Name = L"dropsLb1";
				 this->dropsLb1->Size = System::Drawing::Size(45, 15);
				 this->dropsLb1->TabIndex = 0;
				 this->dropsLb1->Text = L"Drops";
				 // 
				 // pauseBt1
				 // 
				 this->pauseBt1->BackColor = System::Drawing::Color::Transparent;
				 this->pauseBt1->Enabled = false;
				 this->pauseBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->pauseBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->pauseBt1->ForeColor = System::Drawing::Color::Black;
				 this->pauseBt1->Location = System::Drawing::Point(13, 507);
				 this->pauseBt1->Name = L"pauseBt1";
				 this->pauseBt1->Size = System::Drawing::Size(75, 30);
				 this->pauseBt1->TabIndex = 0;
				 this->pauseBt1->Text = L"HOLD";
				 this->pauseBt1->UseVisualStyleBackColor = false;
				 this->pauseBt1->Click += gcnew System::EventHandler(this, &Form1::pauseBt1_Click);
				 // 
				 // stopBt1
				 // 
				 this->stopBt1->BackColor = System::Drawing::Color::Red;
				 this->stopBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->stopBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->stopBt1->ForeColor = System::Drawing::Color::Black;
				 this->stopBt1->Location = System::Drawing::Point(13, 543);
				 this->stopBt1->Name = L"stopBt1";
				 this->stopBt1->Size = System::Drawing::Size(75, 30);
				 this->stopBt1->TabIndex = 0;
				 this->stopBt1->Text = L"ABORT";
				 this->stopBt1->UseVisualStyleBackColor = false;
				 this->stopBt1->Click += gcnew System::EventHandler(this, &Form1::stopBt1_Click);
				 // 
				 // dropBt1
				 // 
				 this->dropBt1->BackColor = System::Drawing::Color::Transparent;
				 this->dropBt1->Enabled = false;
				 this->dropBt1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dropBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dropBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropBt1->ForeColor = System::Drawing::Color::Black;
				 this->dropBt1->Location = System::Drawing::Point(13, 434);
				 this->dropBt1->Name = L"dropBt1";
				 this->dropBt1->Size = System::Drawing::Size(75, 30);
				 this->dropBt1->TabIndex = 0;
				 this->dropBt1->Text = L"DROP";
				 this->dropBt1->UseVisualStyleBackColor = false;
				 this->dropBt1->Click += gcnew System::EventHandler(this, &Form1::dropBt1_Click);
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
				 this->groupBox1->Controls->Add(this->siloBar14);
				 this->groupBox1->Controls->Add(this->prod03Lb);
				 this->groupBox1->Controls->Add(this->prod02Lb);
				 this->groupBox1->Controls->Add(this->prod01Lb);
				 this->groupBox1->Controls->Add(this->lane1StatLB);
				 this->groupBox1->Controls->Add(this->lite1);
				 this->groupBox1->Controls->Add(this->safe3);
				 this->groupBox1->Controls->Add(this->safe2);
				 this->groupBox1->Controls->Add(this->safe1);
				 this->groupBox1->Controls->Add(this->dbLb2);
				 this->groupBox1->Controls->Add(this->dbLb1);
				 this->groupBox1->Controls->Add(this->groupBoxA);
				 this->groupBox1->Controls->Add(this->dbLb);
				 this->groupBox1->Controls->Add(this->label1);
				 this->groupBox1->Controls->Add(this->webBrowser1);
				 this->groupBox1->Controls->Add(this->plant1);
				 this->groupBox1->Controls->Add(this->silo1);
				 this->groupBox1->Controls->Add(this->fill13);
				 this->groupBox1->Controls->Add(this->pictureBox1);
				 this->groupBox1->Controls->Add(this->fill12);
				 this->groupBox1->Controls->Add(this->fill1);
				 this->groupBox1->Controls->Add(this->truckBar1);
				 this->groupBox1->Controls->Add(this->scaleBar1);
				 this->groupBox1->Controls->Add(this->siloBar1);
				 this->groupBox1->Controls->Add(this->siloBar13);
				 this->groupBox1->Controls->Add(this->siloBar12);
				 this->groupBox1->Controls->Add(this->flow1);
				 this->groupBox1->Controls->Add(this->tonnage1);
				 this->groupBox1->Controls->Add(this->tonLb1);
				 this->groupBox1->Controls->Add(this->label3);
				 this->groupBox1->Controls->Add(this->man1);
				 this->groupBox1->Controls->Add(this->material1);
				 this->groupBox1->Controls->Add(this->tic_num1);
				 this->groupBox1->Controls->Add(this->target1);
				 this->groupBox1->Controls->Add(this->truck1);
				 this->groupBox1->Controls->Add(this->Job1);
				 this->groupBox1->Controls->Add(this->customer1);
				 this->groupBox1->Controls->Add(this->dischBt1);
				 this->groupBox1->Controls->Add(this->trackLb1);
				 this->groupBox1->Controls->Add(this->JobLb1);
				 this->groupBox1->Controls->Add(this->cnt1);
				 this->groupBox1->Controls->Add(this->ticLb1);
				 this->groupBox1->Controls->Add(this->ticketNum1);
				 this->groupBox1->Controls->Add(this->of1);
				 this->groupBox1->Controls->Add(this->targetLb1);
				 this->groupBox1->Controls->Add(this->matLb1);
				 this->groupBox1->Controls->Add(this->scale1);
				 this->groupBox1->Controls->Add(this->custLb1);
				 this->groupBox1->Controls->Add(this->truckPic1);
				 this->groupBox1->Controls->Add(this->gBoxLine1);
				 this->groupBox1->Cursor = System::Windows::Forms::Cursors::Default;
				 this->groupBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->groupBox1->ForeColor = System::Drawing::Color::MediumBlue;
				 this->groupBox1->Location = System::Drawing::Point(8, 27);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(400, 840);
				 this->groupBox1->TabIndex = 0;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Lane A";
				 // 
				 // siloBar14
				 // 
				 this->siloBar14->Add = false;
				 this->siloBar14->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar14->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar14->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar14->Count = 0;
				 this->siloBar14->Delay = false;
				 this->siloBar14->DisableInv = false;
				 this->siloBar14->Empty = false;
				 this->siloBar14->ForeColor = System::Drawing::Color::Blue;
				 this->siloBar14->Idle = true;
				 this->siloBar14->Inventory = 100;
				 this->siloBar14->Location = System::Drawing::Point(156, 305);
				 this->siloBar14->Maximum = 100;
				 this->siloBar14->Metric = false;
				 this->siloBar14->Name = L"siloBar14";
				 this->siloBar14->Number = 4;
				 this->siloBar14->Open = false;
				 this->siloBar14->ScaleInLB = false;
				 this->siloBar14->Separators = 4;
				 this->siloBar14->Size = System::Drawing::Size(88, 230);
				 this->siloBar14->TabIndex = 61;
				 this->siloBar14->Target = 0;
				 this->siloBar14->Text = L"Silo4";
				 this->siloBar14->Tol = false;
				 this->siloBar14->ValMan = 0;
				 this->siloBar14->Value = 0;
				 this->siloBar14->Visible = false;
				 // 
				 // prod03Lb
				 // 
				 this->prod03Lb->AutoSize = true;
				 this->prod03Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod03Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod03Lb->ForeColor = System::Drawing::Color::White;
				 this->prod03Lb->Location = System::Drawing::Point(215, 225);
				 this->prod03Lb->Name = L"prod03Lb";
				 this->prod03Lb->Size = System::Drawing::Size(81, 13);
				 this->prod03Lb->TabIndex = 55;
				 this->prod03Lb->Text = L"ABCDABCDA";
				 this->prod03Lb->Visible = false;
				 // 
				 // prod02Lb
				 // 
				 this->prod02Lb->AutoSize = true;
				 this->prod02Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod02Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod02Lb->ForeColor = System::Drawing::Color::White;
				 this->prod02Lb->Location = System::Drawing::Point(113, 225);
				 this->prod02Lb->Name = L"prod02Lb";
				 this->prod02Lb->Size = System::Drawing::Size(81, 13);
				 this->prod02Lb->TabIndex = 55;
				 this->prod02Lb->Text = L"ABCDABCDA";
				 this->prod02Lb->Visible = false;
				 // 
				 // prod01Lb
				 // 
				 this->prod01Lb->AutoSize = true;
				 this->prod01Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod01Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod01Lb->ForeColor = System::Drawing::Color::White;
				 this->prod01Lb->Location = System::Drawing::Point(14, 225);
				 this->prod01Lb->Name = L"prod01Lb";
				 this->prod01Lb->Size = System::Drawing::Size(81, 13);
				 this->prod01Lb->TabIndex = 54;
				 this->prod01Lb->Text = L"ABCDABCDA";
				 this->prod01Lb->Visible = false;
				 // 
				 // lane1StatLB
				 // 
				 this->lane1StatLB->BackColor = System::Drawing::Color::Gainsboro;
				 this->lane1StatLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->lane1StatLB->ForeColor = System::Drawing::Color::Black;
				 this->lane1StatLB->Location = System::Drawing::Point(71, 1);
				 this->lane1StatLB->Name = L"lane1StatLB";
				 this->lane1StatLB->Size = System::Drawing::Size(50, 13);
				 this->lane1StatLB->TabIndex = 53;
				 this->lane1StatLB->Text = L"S-00";
				 this->lane1StatLB->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->lane1StatLB->Visible = false;
				 // 
				 // lite1
				 // 
				 this->lite1->BackColor = System::Drawing::Color::Transparent;
				 this->lite1->Cursor = System::Windows::Forms::Cursors::No;
				 this->lite1->Enabled = false;
				 this->lite1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->lite1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"lite1.Image")));
				 this->lite1->Location = System::Drawing::Point(6, 592);
				 this->lite1->Name = L"lite1";
				 this->lite1->Size = System::Drawing::Size(48, 48);
				 this->lite1->TabIndex = 35;
				 // 
				 // safe3
				 // 
				 this->safe3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe3.Image")));
				 this->safe3->Location = System::Drawing::Point(250, 190);
				 this->safe3->Name = L"safe3";
				 this->safe3->Size = System::Drawing::Size(24, 24);
				 this->safe3->TabIndex = 52;
				 this->safe3->Visible = false;
				 // 
				 // safe2
				 // 
				 this->safe2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe2.Image")));
				 this->safe2->Location = System::Drawing::Point(150, 190);
				 this->safe2->Name = L"safe2";
				 this->safe2->Size = System::Drawing::Size(24, 24);
				 this->safe2->TabIndex = 51;
				 this->safe2->Visible = false;
				 // 
				 // safe1
				 // 
				 this->safe1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe1.Image")));
				 this->safe1->Location = System::Drawing::Point(50, 190);
				 this->safe1->Name = L"safe1";
				 this->safe1->Size = System::Drawing::Size(24, 24);
				 this->safe1->TabIndex = 50;
				 this->safe1->Visible = false;
				 // 
				 // dbLb2
				 // 
				 this->dbLb2->AutoSize = true;
				 this->dbLb2->BackColor = System::Drawing::Color::Yellow;
				 this->dbLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dbLb2->Location = System::Drawing::Point(233, 547);
				 this->dbLb2->Name = L"dbLb2";
				 this->dbLb2->Size = System::Drawing::Size(39, 13);
				 this->dbLb2->TabIndex = 49;
				 this->dbLb2->Text = L"00.00";
				 this->dbLb2->Visible = false;
				 // 
				 // dbLb1
				 // 
				 this->dbLb1->AutoSize = true;
				 this->dbLb1->BackColor = System::Drawing::Color::White;
				 this->dbLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dbLb1->Location = System::Drawing::Point(232, 528);
				 this->dbLb1->Name = L"dbLb1";
				 this->dbLb1->Size = System::Drawing::Size(63, 13);
				 this->dbLb1->TabIndex = 48;
				 this->dbLb1->Text = L"00000000";
				 this->dbLb1->Visible = false;
				 // 
				 // groupBoxA
				 // 
				 this->groupBoxA->BackColor = System::Drawing::Color::Silver;
				 this->groupBoxA->Controls->Add(this->okA);
				 this->groupBoxA->Controls->Add(this->grossA);
				 this->groupBoxA->Controls->Add(this->tareA);
				 this->groupBoxA->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBoxA->Location = System::Drawing::Point(98, 306);
				 this->groupBoxA->Name = L"groupBoxA";
				 this->groupBoxA->Size = System::Drawing::Size(204, 60);
				 this->groupBoxA->TabIndex = 45;
				 this->groupBoxA->TabStop = false;
				 this->groupBoxA->Text = L"Tare       Gross";
				 this->groupBoxA->Visible = false;
				 // 
				 // okA
				 // 
				 this->okA->BackColor = System::Drawing::Color::PaleGreen;
				 this->okA->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->okA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->okA->Location = System::Drawing::Point(137, 22);
				 this->okA->Name = L"okA";
				 this->okA->Size = System::Drawing::Size(50, 26);
				 this->okA->TabIndex = 2;
				 this->okA->Text = L"OK";
				 this->okA->UseVisualStyleBackColor = false;
				 this->okA->Click += gcnew System::EventHandler(this, &Form1::okA_Click);
				 // 
				 // grossA
				 // 
				 this->grossA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->grossA->Location = System::Drawing::Point(74, 22);
				 this->grossA->Name = L"grossA";
				 this->grossA->Size = System::Drawing::Size(54, 26);
				 this->grossA->TabIndex = 1;
				 this->grossA->Text = L"xx.xx";
				 this->grossA->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 // 
				 // tareA
				 // 
				 this->tareA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tareA->Location = System::Drawing::Point(6, 22);
				 this->tareA->Name = L"tareA";
				 this->tareA->Size = System::Drawing::Size(57, 26);
				 this->tareA->TabIndex = 0;
				 this->tareA->Text = L"xx.xx";
				 this->tareA->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 // 
				 // dbLb
				 // 
				 this->dbLb->BackColor = System::Drawing::Color::WhiteSmoke;
				 this->dbLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dbLb->ForeColor = System::Drawing::Color::Black;
				 this->dbLb->Location = System::Drawing::Point(1, 496);
				 this->dbLb->Name = L"dbLb";
				 this->dbLb->Size = System::Drawing::Size(303, 20);
				 this->dbLb->TabIndex = 44;
				 this->dbLb->Text = L"012345678901234567890";
				 this->dbLb->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->dbLb->Visible = false;
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label1->Location = System::Drawing::Point(142, 104);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(36, 13);
				 this->label1->TabIndex = 43;
				 this->label1->Text = L"Plant";
				 // 
				 // webBrowser1
				 // 
				 this->webBrowser1->AllowWebBrowserDrop = false;
				 this->webBrowser1->CausesValidation = false;
				 this->webBrowser1->Location = System::Drawing::Point(6, 592);
				 this->webBrowser1->MaximumSize = System::Drawing::Size(800, 600);
				 this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
				 this->webBrowser1->Name = L"webBrowser1";
				 this->webBrowser1->ScriptErrorsSuppressed = true;
				 this->webBrowser1->Size = System::Drawing::Size(386, 240);
				 this->webBrowser1->TabIndex = 0;
				 this->webBrowser1->TabStop = false;
				 this->webBrowser1->Visible = false;
				 this->webBrowser1->WebBrowserShortcutsEnabled = false;
				 // 
				 // plant1
				 // 
				 this->plant1->BackColor = System::Drawing::Color::Gainsboro;
				 this->plant1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->plant1->Cursor = System::Windows::Forms::Cursors::No;
				 this->plant1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->plant1->ForeColor = System::Drawing::Color::Black;
				 this->plant1->Location = System::Drawing::Point(178, 100);
				 this->plant1->Name = L"plant1";
				 this->plant1->Size = System::Drawing::Size(30, 23);
				 this->plant1->TabIndex = 42;
				 this->plant1->Text = L"00";
				 this->plant1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // silo1
				 // 
				 this->silo1->BackColor = System::Drawing::Color::Gainsboro;
				 this->silo1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->silo1->ForeColor = System::Drawing::Color::Black;
				 this->silo1->Location = System::Drawing::Point(114, 471);
				 this->silo1->Name = L"silo1";
				 this->silo1->Size = System::Drawing::Size(60, 20);
				 this->silo1->TabIndex = 21;
				 this->silo1->Text = L"000";
				 this->silo1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->silo1->Visible = false;
				 // 
				 // fill13
				 // 
				 this->fill13->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill13.Image")));
				 this->fill13->Location = System::Drawing::Point(270, 190);
				 this->fill13->Name = L"fill13";
				 this->fill13->Size = System::Drawing::Size(24, 24);
				 this->fill13->TabIndex = 20;
				 this->fill13->Visible = false;
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
				 this->pictureBox1->Location = System::Drawing::Point(67, 592);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(320, 240);
				 this->pictureBox1->TabIndex = 38;
				 this->pictureBox1->TabStop = false;
				 // 
				 // fill12
				 // 
				 this->fill12->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill12.Image")));
				 this->fill12->Location = System::Drawing::Point(170, 190);
				 this->fill12->Name = L"fill12";
				 this->fill12->Size = System::Drawing::Size(24, 24);
				 this->fill12->TabIndex = 19;
				 this->fill12->Visible = false;
				 this->fill12->Click += gcnew System::EventHandler(this, &Form1::fill12_Click);
				 // 
				 // fill1
				 // 
				 this->fill1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill1.Image")));
				 this->fill1->Location = System::Drawing::Point(70, 190);
				 this->fill1->Name = L"fill1";
				 this->fill1->Size = System::Drawing::Size(24, 24);
				 this->fill1->TabIndex = 0;
				 this->fill1->Visible = false;
				 // 
				 // truckBar1
				 // 
				 this->truckBar1->BarColor = System::Drawing::Color::LightBlue;
				 this->truckBar1->BorderColor = System::Drawing::Color::Black;
				 this->truckBar1->FillStyle = As::BarCtl::FillStyles::Dashed;
				 this->truckBar1->Flow = 0;
				 this->truckBar1->Location = System::Drawing::Point(10, 496);
				 this->truckBar1->Maximum = 100;
				 this->truckBar1->Name = L"truckBar1";
				 this->truckBar1->Pct = 0;
				 this->truckBar1->ScaleInLB = false;
				 this->truckBar1->Separators = 0;
				 this->truckBar1->Size = System::Drawing::Size(80, 28);
				 this->truckBar1->TabIndex = 17;
				 this->truckBar1->Target = 10;
				 this->truckBar1->Text = L"barCtl1";
				 this->truckBar1->Value = 0;
				 this->truckBar1->Vertical = false;
				 // 
				 // scaleBar1
				 // 
				 this->scaleBar1->BackColor = System::Drawing::Color::LightGray;
				 this->scaleBar1->BarColor = System::Drawing::Color::Gainsboro;
				 this->scaleBar1->BorderColor = System::Drawing::Color::Black;
				 this->scaleBar1->Flow = 0;
				 this->scaleBar1->Idle = false;
				 this->scaleBar1->Label = 0;
				 this->scaleBar1->Location = System::Drawing::Point(10, 436);
				 this->scaleBar1->Maximum = 100;
				 this->scaleBar1->Metric = false;
				 this->scaleBar1->Name = L"scaleBar1";
				 this->scaleBar1->Open = false;
				 this->scaleBar1->ScaleInLB = false;
				 this->scaleBar1->Size = System::Drawing::Size(100, 52);
				 this->scaleBar1->TabIndex = 16;
				 this->scaleBar1->Target = 0;
				 this->scaleBar1->Topl = 0;
				 this->scaleBar1->Value = 0;
				 // 
				 // siloBar1
				 // 
				 this->siloBar1->Add = false;
				 this->siloBar1->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar1->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar1->BorderColor = System::Drawing::Color::Black;
				 this->siloBar1->Count = 0;
				 this->siloBar1->Delay = false;
				 this->siloBar1->DisableInv = false;
				 this->siloBar1->Empty = false;
				 this->siloBar1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->siloBar1->ForeColor = System::Drawing::Color::Blue;
				 this->siloBar1->Idle = false;
				 this->siloBar1->Inventory = 100;
				 this->siloBar1->Location = System::Drawing::Point(10, 196);
				 this->siloBar1->Maximum = 100;
				 this->siloBar1->Metric = false;
				 this->siloBar1->Name = L"siloBar1";
				 this->siloBar1->Number = 1;
				 this->siloBar1->Open = false;
				 this->siloBar1->ScaleInLB = false;
				 this->siloBar1->Separators = 4;
				 this->siloBar1->Size = System::Drawing::Size(88, 230);
				 this->siloBar1->TabIndex = 15;
				 this->siloBar1->Target = 0;
				 this->siloBar1->Text = L"Silo1";
				 this->siloBar1->Tol = false;
				 this->siloBar1->ValMan = 0;
				 this->siloBar1->Value = 0;
				 this->siloBar1->DoubleClick += gcnew System::EventHandler(this, &Form1::flow1_Click);
				 this->siloBar1->Click += gcnew System::EventHandler(this, &Form1::siloBar1_Click);
				 // 
				 // siloBar13
				 // 
				 this->siloBar13->Add = false;
				 this->siloBar13->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar13->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar13->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar13->Count = 0;
				 this->siloBar13->Delay = false;
				 this->siloBar13->DisableInv = false;
				 this->siloBar13->Empty = false;
				 this->siloBar13->ForeColor = System::Drawing::Color::Blue;
				 this->siloBar13->Idle = true;
				 this->siloBar13->Inventory = 100;
				 this->siloBar13->Location = System::Drawing::Point(210, 196);
				 this->siloBar13->Maximum = 100;
				 this->siloBar13->Metric = false;
				 this->siloBar13->Name = L"siloBar13";
				 this->siloBar13->Number = 3;
				 this->siloBar13->Open = false;
				 this->siloBar13->ScaleInLB = false;
				 this->siloBar13->Separators = 4;
				 this->siloBar13->Size = System::Drawing::Size(88, 230);
				 this->siloBar13->TabIndex = 14;
				 this->siloBar13->Target = 0;
				 this->siloBar13->Text = L"Silo3";
				 this->siloBar13->Tol = false;
				 this->siloBar13->ValMan = 0;
				 this->siloBar13->Value = 0;
				 this->siloBar13->Visible = false;
				 this->siloBar13->DoubleClick += gcnew System::EventHandler(this, &Form1::flow3_Click);
				 this->siloBar13->Click += gcnew System::EventHandler(this, &Form1::siloBar13_Click);
				 // 
				 // siloBar12
				 // 
				 this->siloBar12->Add = false;
				 this->siloBar12->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar12->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar12->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar12->Count = 0;
				 this->siloBar12->Delay = false;
				 this->siloBar12->DisableInv = false;
				 this->siloBar12->Empty = false;
				 this->siloBar12->ForeColor = System::Drawing::Color::Blue;
				 this->siloBar12->Idle = true;
				 this->siloBar12->Inventory = 100;
				 this->siloBar12->Location = System::Drawing::Point(110, 196);
				 this->siloBar12->Maximum = 100;
				 this->siloBar12->Metric = false;
				 this->siloBar12->Name = L"siloBar12";
				 this->siloBar12->Number = 2;
				 this->siloBar12->Open = false;
				 this->siloBar12->ScaleInLB = false;
				 this->siloBar12->Separators = 4;
				 this->siloBar12->Size = System::Drawing::Size(88, 230);
				 this->siloBar12->TabIndex = 13;
				 this->siloBar12->Target = 0;
				 this->siloBar12->Text = L"Silo2";
				 this->siloBar12->Tol = false;
				 this->siloBar12->ValMan = 0;
				 this->siloBar12->Value = 0;
				 this->siloBar12->Visible = false;
				 this->siloBar12->DoubleClick += gcnew System::EventHandler(this, &Form1::flow2_Click);
				 this->siloBar12->Click += gcnew System::EventHandler(this, &Form1::siloBar12_Click);
				 // 
				 // flow1
				 // 
				 this->flow1->BackColor = System::Drawing::Color::PaleGreen;
				 this->flow1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->flow1->ForeColor = System::Drawing::Color::Black;
				 this->flow1->Location = System::Drawing::Point(181, 471);
				 this->flow1->Name = L"flow1";
				 this->flow1->Size = System::Drawing::Size(59, 20);
				 this->flow1->TabIndex = 7;
				 this->flow1->Text = L"000";
				 this->flow1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->flow1->Visible = false;
				 this->flow1->Click += gcnew System::EventHandler(this, &Form1::flow1_Click);
				 // 
				 // tonnage1
				 // 
				 this->tonnage1->BackColor = System::Drawing::Color::LightBlue;
				 this->tonnage1->Cursor = System::Windows::Forms::Cursors::No;
				 this->tonnage1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->tonnage1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tonnage1->ForeColor = System::Drawing::Color::Black;
				 this->tonnage1->Location = System::Drawing::Point(206, 147);
				 this->tonnage1->Name = L"tonnage1";
				 this->tonnage1->Size = System::Drawing::Size(84, 32);
				 this->tonnage1->TabIndex = 0;
				 this->tonnage1->Text = L"9999.0";
				 this->tonnage1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->tonnage1->Click += gcnew System::EventHandler(this, &Form1::tonnage1_Click);
				 // 
				 // tonLb1
				 // 
				 this->tonLb1->AutoEllipsis = true;
				 this->tonLb1->AutoSize = true;
				 this->tonLb1->Cursor = System::Windows::Forms::Cursors::No;
				 this->tonLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tonLb1->Location = System::Drawing::Point(148, 150);
				 this->tonLb1->Name = L"tonLb1";
				 this->tonLb1->Size = System::Drawing::Size(57, 26);
				 this->tonLb1->TabIndex = 0;
				 this->tonLb1->Text = L"Today\'s\r\nTonnage";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->BackColor = System::Drawing::Color::Transparent;
				 this->label3->Cursor = System::Windows::Forms::Cursors::No;
				 this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label3->ForeColor = System::Drawing::Color::MediumBlue;
				 this->label3->Location = System::Drawing::Point(216, 88);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(37, 13);
				 this->label3->TabIndex = 0;
				 this->label3->Text = L"Done";
				 // 
				 // man1
				 // 
				 this->man1->BackColor = System::Drawing::Color::LightBlue;
				 this->man1->Cursor = System::Windows::Forms::Cursors::No;
				 this->man1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->man1->ForeColor = System::Drawing::Color::Black;
				 this->man1->Location = System::Drawing::Point(220, 104);
				 this->man1->Name = L"man1";
				 this->man1->Size = System::Drawing::Size(70, 28);
				 this->man1->TabIndex = 0;
				 this->man1->Text = L"000";
				 this->man1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // material1
				 // 
				 this->material1->BackColor = System::Drawing::Color::Gainsboro;
				 this->material1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->material1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->material1->Location = System::Drawing::Point(68, 72);
				 this->material1->MaxLength = 8;
				 this->material1->Name = L"material1";
				 this->material1->ReadOnly = true;
				 this->material1->Size = System::Drawing::Size(92, 23);
				 this->material1->TabIndex = 3;
				 this->material1->Text = L"1234567890";
				 // 
				 // tic_num1
				 // 
				 this->tic_num1->BackColor = System::Drawing::Color::Gainsboro;
				 this->tic_num1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->tic_num1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tic_num1->Location = System::Drawing::Point(68, 100);
				 this->tic_num1->MaxLength = 8;
				 this->tic_num1->Name = L"tic_num1";
				 this->tic_num1->ReadOnly = true;
				 this->tic_num1->Size = System::Drawing::Size(72, 23);
				 this->tic_num1->TabIndex = 4;
				 this->tic_num1->TabStop = false;
				 this->tic_num1->Text = L"12345678";
				 this->tic_num1->WordWrap = false;
				 // 
				 // target1
				 // 
				 this->target1->BackColor = System::Drawing::Color::White;
				 this->target1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->target1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->target1->Location = System::Drawing::Point(82, 156);
				 this->target1->MaxLength = 6;
				 this->target1->Name = L"target1";
				 this->target1->Size = System::Drawing::Size(50, 23);
				 this->target1->TabIndex = 6;
				 this->target1->Text = L"00.00";
				 this->target1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->target1->WordWrap = false;
				 // 
				 // truck1
				 // 
				 this->truck1->BackColor = System::Drawing::Color::White;
				 this->truck1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->truck1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->truck1->Location = System::Drawing::Point(68, 128);
				 this->truck1->MaxLength = 9;
				 this->truck1->Name = L"truck1";
				 this->truck1->Size = System::Drawing::Size(78, 23);
				 this->truck1->TabIndex = 5;
				 this->truck1->Text = L"012345678";
				 this->truck1->WordWrap = false;
				 this->truck1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::truckNum1_MouseDoubleClick);
				 // 
				 // Job1
				 // 
				 this->Job1->BackColor = System::Drawing::Color::Gainsboro;
				 this->Job1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->Job1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->Job1->Location = System::Drawing::Point(68, 44);
				 this->Job1->MaxLength = 16;
				 this->Job1->Name = L"Job1";
				 this->Job1->ReadOnly = true;
				 this->Job1->Size = System::Drawing::Size(137, 23);
				 this->Job1->TabIndex = 2;
				 this->Job1->Text = L"0123456789abcdef";
				 // 
				 // customer1
				 // 
				 this->customer1->BackColor = System::Drawing::Color::Gainsboro;
				 this->customer1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->customer1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->customer1->Location = System::Drawing::Point(68, 16);
				 this->customer1->MaxLength = 32;
				 this->customer1->Name = L"customer1";
				 this->customer1->ReadOnly = true;
				 this->customer1->Size = System::Drawing::Size(264, 23);
				 this->customer1->TabIndex = 1;
				 this->customer1->Text = L"0123456789abcdef0123456789abcdef";
				 // 
				 // dischBt1
				 // 
				 this->dischBt1->BackColor = System::Drawing::Color::Transparent;
				 this->dischBt1->Enabled = false;
				 this->dischBt1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dischBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dischBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dischBt1->ForeColor = System::Drawing::Color::Black;
				 this->dischBt1->Location = System::Drawing::Point(226, 438);
				 this->dischBt1->Name = L"dischBt1";
				 this->dischBt1->Size = System::Drawing::Size(75, 30);
				 this->dischBt1->TabIndex = 0;
				 this->dischBt1->Text = L"DISCH";
				 this->dischBt1->UseVisualStyleBackColor = false;
				 this->dischBt1->Visible = false;
				 this->dischBt1->Click += gcnew System::EventHandler(this, &Form1::dischBt1_Click);
				 // 
				 // trackLb1
				 // 
				 this->trackLb1->AutoSize = true;
				 this->trackLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->trackLb1->Location = System::Drawing::Point(6, 133);
				 this->trackLb1->Name = L"trackLb1";
				 this->trackLb1->Size = System::Drawing::Size(55, 13);
				 this->trackLb1->TabIndex = 0;
				 this->trackLb1->Text = L"Truck Id";
				 // 
				 // JobLb1
				 // 
				 this->JobLb1->AutoSize = true;
				 this->JobLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->JobLb1->Location = System::Drawing::Point(6, 48);
				 this->JobLb1->Name = L"JobLb1";
				 this->JobLb1->Size = System::Drawing::Size(27, 13);
				 this->JobLb1->TabIndex = 0;
				 this->JobLb1->Text = L"Job";
				 // 
				 // cnt1
				 // 
				 this->cnt1->BackColor = System::Drawing::Color::Aquamarine;
				 this->cnt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->cnt1->ForeColor = System::Drawing::Color::Black;
				 this->cnt1->Location = System::Drawing::Point(246, 471);
				 this->cnt1->Name = L"cnt1";
				 this->cnt1->Size = System::Drawing::Size(50, 20);
				 this->cnt1->TabIndex = 0;
				 this->cnt1->Text = L"000.00";
				 this->cnt1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->cnt1->Visible = false;
				 // 
				 // ticLb1
				 // 
				 this->ticLb1->AutoSize = true;
				 this->ticLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticLb1->Location = System::Drawing::Point(6, 104);
				 this->ticLb1->Name = L"ticLb1";
				 this->ticLb1->Size = System::Drawing::Size(55, 13);
				 this->ticLb1->TabIndex = 0;
				 this->ticLb1->Text = L"Ticket #";
				 // 
				 // of1
				 // 
				 this->of1->AutoSize = true;
				 this->of1->BackColor = System::Drawing::Color::Transparent;
				 this->of1->Cursor = System::Windows::Forms::Cursors::No;
				 this->of1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->of1->ForeColor = System::Drawing::Color::MediumBlue;
				 this->of1->Location = System::Drawing::Point(215, 59);
				 this->of1->Name = L"of1";
				 this->of1->Size = System::Drawing::Size(32, 13);
				 this->of1->TabIndex = 0;
				 this->of1->Text = L"New";
				 this->of1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 // 
				 // targetLb1
				 // 
				 this->targetLb1->AutoSize = true;
				 this->targetLb1->BackColor = System::Drawing::Color::Transparent;
				 this->targetLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->targetLb1->ForeColor = System::Drawing::Color::MediumBlue;
				 this->targetLb1->Location = System::Drawing::Point(6, 160);
				 this->targetLb1->Name = L"targetLb1";
				 this->targetLb1->Size = System::Drawing::Size(44, 13);
				 this->targetLb1->TabIndex = 0;
				 this->targetLb1->Text = L"Target";
				 // 
				 // matLb1
				 // 
				 this->matLb1->AutoSize = true;
				 this->matLb1->BackColor = System::Drawing::Color::Transparent;
				 this->matLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->matLb1->ForeColor = System::Drawing::Color::MediumBlue;
				 this->matLb1->Location = System::Drawing::Point(6, 76);
				 this->matLb1->Name = L"matLb1";
				 this->matLb1->Size = System::Drawing::Size(52, 13);
				 this->matLb1->TabIndex = 0;
				 this->matLb1->Text = L"Material";
				 // 
				 // scale1
				 // 
				 this->scale1->BackColor = System::Drawing::Color::PaleGreen;
				 this->scale1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->scale1->ForeColor = System::Drawing::Color::Black;
				 this->scale1->Location = System::Drawing::Point(117, 440);
				 this->scale1->Name = L"scale1";
				 this->scale1->Size = System::Drawing::Size(100, 20);
				 this->scale1->TabIndex = 0;
				 this->scale1->Text = L" 0000.00  xx x";
				 this->scale1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->scale1->Visible = false;
				 // 
				 // custLb1
				 // 
				 this->custLb1->AutoSize = true;
				 this->custLb1->BackColor = System::Drawing::Color::Transparent;
				 this->custLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->custLb1->ForeColor = System::Drawing::Color::MediumBlue;
				 this->custLb1->Location = System::Drawing::Point(6, 23);
				 this->custLb1->Name = L"custLb1";
				 this->custLb1->Size = System::Drawing::Size(59, 13);
				 this->custLb1->TabIndex = 0;
				 this->custLb1->Text = L"Customer";
				 // 
				 // truckPic1
				 // 
				 this->truckPic1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"truckPic1.BackgroundImage")));
				 this->truckPic1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->truckPic1->Location = System::Drawing::Point(23, 528);
				 this->truckPic1->Name = L"truckPic1";
				 this->truckPic1->Size = System::Drawing::Size(78, 57);
				 this->truckPic1->TabIndex = 0;
				 this->truckPic1->TabStop = false;
				 // 
				 // gBoxLine1
				 // 
				 this->gBoxLine1->Controls->Add(this->nextBt1);
				 this->gBoxLine1->Controls->Add(this->resetBt1);
				 this->gBoxLine1->Controls->Add(this->pauseBt1);
				 this->gBoxLine1->Controls->Add(this->laneA2ndCB);
				 this->gBoxLine1->Controls->Add(this->stopBt1);
				 this->gBoxLine1->Controls->Add(this->copyLb1);
				 this->gBoxLine1->Controls->Add(this->dropBt1);
				 this->gBoxLine1->Controls->Add(this->numCopy1);
				 this->gBoxLine1->Controls->Add(this->dropsLb1);
				 this->gBoxLine1->Controls->Add(this->drops11);
				 this->gBoxLine1->Controls->Add(this->drops12);
				 this->gBoxLine1->Controls->Add(this->drops13);
				 this->gBoxLine1->Controls->Add(this->drops14);
				 this->gBoxLine1->Controls->Add(this->addBt1);
				 this->gBoxLine1->Controls->Add(this->autoBt1);
				 this->gBoxLine1->Controls->Add(this->printTarget1);
				 this->gBoxLine1->Controls->Add(this->printOnly1);
				 this->gBoxLine1->Controls->Add(this->autoFall1);
				 this->gBoxLine1->Controls->Add(this->readyBt1);
				 this->gBoxLine1->Controls->Add(this->laneACb3);
				 this->gBoxLine1->Controls->Add(this->jog1);
				 this->gBoxLine1->Controls->Add(this->taxExempt1);
				 this->gBoxLine1->Controls->Add(this->autoDisch1);
				 this->gBoxLine1->Controls->Add(this->all1);
				 this->gBoxLine1->Controls->Add(this->laneACb2);
				 this->gBoxLine1->Controls->Add(this->adapt1);
				 this->gBoxLine1->Location = System::Drawing::Point(295, 4);
				 this->gBoxLine1->Name = L"gBoxLine1";
				 this->gBoxLine1->Size = System::Drawing::Size(95, 583);
				 this->gBoxLine1->TabIndex = 60;
				 this->gBoxLine1->TabStop = false;
				 // 
				 // resetBt1
				 // 
				 this->resetBt1->BackColor = System::Drawing::Color::Red;
				 this->resetBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->resetBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->resetBt1->ForeColor = System::Drawing::Color::Black;
				 this->resetBt1->Location = System::Drawing::Point(9, 90);
				 this->resetBt1->Name = L"resetBt1";
				 this->resetBt1->Size = System::Drawing::Size(75, 30);
				 this->resetBt1->TabIndex = 59;
				 this->resetBt1->Text = L"RESET";
				 this->resetBt1->UseVisualStyleBackColor = false;
				 this->resetBt1->Click += gcnew System::EventHandler(this, &Form1::resetBt1_Click);
				 // 
				 // laneA2ndCB
				 // 
				 this->laneA2ndCB->AutoSize = true;
				 this->laneA2ndCB->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneA2ndCB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneA2ndCB->Location = System::Drawing::Point(7, 228);
				 this->laneA2ndCB->Name = L"laneA2ndCB";
				 this->laneA2ndCB->Size = System::Drawing::Size(79, 17);
				 this->laneA2ndCB->TabIndex = 58;
				 this->laneA2ndCB->Text = L"2nd Copy";
				 this->laneA2ndCB->UseVisualStyleBackColor = false;
				 // 
				 // copyLb1
				 // 
				 this->copyLb1->AutoSize = true;
				 this->copyLb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->copyLb1->Location = System::Drawing::Point(41, 198);
				 this->copyLb1->Name = L"copyLb1";
				 this->copyLb1->Size = System::Drawing::Size(49, 13);
				 this->copyLb1->TabIndex = 57;
				 this->copyLb1->Text = L"Tickets";
				 // 
				 // numCopy1
				 // 
				 this->numCopy1->Location = System::Drawing::Point(7, 193);
				 this->numCopy1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
				 this->numCopy1->Name = L"numCopy1";
				 this->numCopy1->Size = System::Drawing::Size(30, 23);
				 this->numCopy1->TabIndex = 56;
				 this->numCopy1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // drops11
				 // 
				 this->drops11->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops11->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops11->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops11->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops11->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops11->ForeColor = System::Drawing::Color::Black;
				 this->drops11->Location = System::Drawing::Point(18, 358);
				 this->drops11->Name = L"drops11";
				 this->drops11->Size = System::Drawing::Size(32, 32);
				 this->drops11->TabIndex = 0;
				 this->drops11->Text = L"1";
				 this->drops11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops11->UseVisualStyleBackColor = true;
				 this->drops11->Click += gcnew System::EventHandler(this, &Form1::drops11_Click);
				 // 
				 // drops12
				 // 
				 this->drops12->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops12->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops12->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops12->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops12->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops12->ForeColor = System::Drawing::Color::Black;
				 this->drops12->Location = System::Drawing::Point(54, 358);
				 this->drops12->Name = L"drops12";
				 this->drops12->Size = System::Drawing::Size(32, 32);
				 this->drops12->TabIndex = 0;
				 this->drops12->Text = L"2";
				 this->drops12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops12->UseVisualStyleBackColor = true;
				 this->drops12->Click += gcnew System::EventHandler(this, &Form1::drops12_Click);
				 // 
				 // drops13
				 // 
				 this->drops13->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops13->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops13->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops13->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops13->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops13->ForeColor = System::Drawing::Color::Black;
				 this->drops13->Location = System::Drawing::Point(18, 393);
				 this->drops13->Name = L"drops13";
				 this->drops13->Size = System::Drawing::Size(32, 32);
				 this->drops13->TabIndex = 0;
				 this->drops13->Text = L"3";
				 this->drops13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops13->UseVisualStyleBackColor = true;
				 this->drops13->Click += gcnew System::EventHandler(this, &Form1::drops13_Click);
				 // 
				 // drops14
				 // 
				 this->drops14->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops14->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops14->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops14->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops14->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops14->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops14->ForeColor = System::Drawing::Color::Black;
				 this->drops14->Location = System::Drawing::Point(54, 393);
				 this->drops14->Name = L"drops14";
				 this->drops14->Size = System::Drawing::Size(32, 32);
				 this->drops14->TabIndex = 0;
				 this->drops14->Text = L"4";
				 this->drops14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops14->UseVisualStyleBackColor = true;
				 this->drops14->Click += gcnew System::EventHandler(this, &Form1::drops14_Click);
				 // 
				 // addBt1
				 // 
				 this->addBt1->BackColor = System::Drawing::Color::Transparent;
				 this->addBt1->Enabled = false;
				 this->addBt1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->addBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->addBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->addBt1->ForeColor = System::Drawing::Color::Black;
				 this->addBt1->Location = System::Drawing::Point(13, 470);
				 this->addBt1->Name = L"addBt1";
				 this->addBt1->Size = System::Drawing::Size(75, 30);
				 this->addBt1->TabIndex = 0;
				 this->addBt1->Text = L"ADD";
				 this->addBt1->UseVisualStyleBackColor = false;
				 this->addBt1->Visible = false;
				 this->addBt1->Click += gcnew System::EventHandler(this, &Form1::addBt1_Click);
				 // 
				 // autoBt1
				 // 
				 this->autoBt1->BackColor = System::Drawing::Color::Transparent;
				 this->autoBt1->Enabled = false;
				 this->autoBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->autoBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoBt1->ForeColor = System::Drawing::Color::MediumBlue;
				 this->autoBt1->Location = System::Drawing::Point(6, 90);
				 this->autoBt1->Name = L"autoBt1";
				 this->autoBt1->Size = System::Drawing::Size(82, 30);
				 this->autoBt1->TabIndex = 0;
				 this->autoBt1->Text = L"MANUAL";
				 this->autoBt1->UseVisualStyleBackColor = false;
				 this->autoBt1->Click += gcnew System::EventHandler(this, &Form1::autoBt1_Click);
				 // 
				 // printTarget1
				 // 
				 this->printTarget1->AutoSize = true;
				 this->printTarget1->BackColor = System::Drawing::Color::Gainsboro;
				 this->printTarget1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printTarget1->Location = System::Drawing::Point(7, 126);
				 this->printTarget1->Name = L"printTarget1";
				 this->printTarget1->Size = System::Drawing::Size(93, 17);
				 this->printTarget1->TabIndex = 0;
				 this->printTarget1->Text = L"Print Target";
				 this->printTarget1->UseVisualStyleBackColor = false;
				 this->printTarget1->CheckedChanged += gcnew System::EventHandler(this, &Form1::printTarget1_CheckedChanged);
				 // 
				 // printOnly1
				 // 
				 this->printOnly1->BackColor = System::Drawing::Color::Transparent;
				 this->printOnly1->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->printOnly1->Enabled = false;
				 this->printOnly1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->printOnly1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printOnly1->ForeColor = System::Drawing::Color::Black;
				 this->printOnly1->Location = System::Drawing::Point(13, 304);
				 this->printOnly1->Name = L"printOnly1";
				 this->printOnly1->Size = System::Drawing::Size(75, 30);
				 this->printOnly1->TabIndex = 0;
				 this->printOnly1->Text = L"PrintOnly";
				 this->printOnly1->UseVisualStyleBackColor = false;
				 this->printOnly1->Click += gcnew System::EventHandler(this, &Form1::printOnly1_Click);
				 // 
				 // autoFall1
				 // 
				 this->autoFall1->AutoSize = true;
				 this->autoFall1->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoFall1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoFall1->Location = System::Drawing::Point(7, 206);
				 this->autoFall1->Name = L"autoFall1";
				 this->autoFall1->Size = System::Drawing::Size(76, 17);
				 this->autoFall1->TabIndex = 8;
				 this->autoFall1->Text = L"Auto Fall";
				 this->autoFall1->UseVisualStyleBackColor = false;
				 this->autoFall1->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoFall1_CheckedChanged);
				 // 
				 // readyBt1
				 // 
				 this->readyBt1->BackColor = System::Drawing::Color::Transparent;
				 this->readyBt1->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->readyBt1->Enabled = false;
				 this->readyBt1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->readyBt1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->readyBt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->readyBt1->ForeColor = System::Drawing::Color::Black;
				 this->readyBt1->Location = System::Drawing::Point(13, 266);
				 this->readyBt1->Name = L"readyBt1";
				 this->readyBt1->Size = System::Drawing::Size(75, 30);
				 this->readyBt1->TabIndex = 9;
				 this->readyBt1->Text = L"READY";
				 this->readyBt1->UseVisualStyleBackColor = false;
				 this->readyBt1->Click += gcnew System::EventHandler(this, &Form1::readyBt1_Click);
				 // 
				 // laneACb3
				 // 
				 this->laneACb3->AutoSize = true;
				 this->laneACb3->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneACb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneACb3->Location = System::Drawing::Point(53, 166);
				 this->laneACb3->Name = L"laneACb3";
				 this->laneACb3->Size = System::Drawing::Size(41, 17);
				 this->laneACb3->TabIndex = 47;
				 this->laneACb3->Text = L"P3";
				 this->laneACb3->UseVisualStyleBackColor = false;
				 // 
				 // jog1
				 // 
				 this->jog1->AutoSize = true;
				 this->jog1->BackColor = System::Drawing::Color::Gainsboro;
				 this->jog1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->jog1->Location = System::Drawing::Point(7, 246);
				 this->jog1->Name = L"jog1";
				 this->jog1->Size = System::Drawing::Size(46, 17);
				 this->jog1->TabIndex = 10;
				 this->jog1->Text = L"Jog";
				 this->jog1->UseVisualStyleBackColor = false;
				 this->jog1->CheckedChanged += gcnew System::EventHandler(this, &Form1::jog1_CheckedChanged);
				 // 
				 // taxExempt1
				 // 
				 this->taxExempt1->AutoSize = true;
				 this->taxExempt1->BackColor = System::Drawing::Color::Gainsboro;
				 this->taxExempt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->taxExempt1->Location = System::Drawing::Point(7, 146);
				 this->taxExempt1->Name = L"taxExempt1";
				 this->taxExempt1->Size = System::Drawing::Size(92, 17);
				 this->taxExempt1->TabIndex = 46;
				 this->taxExempt1->Text = L"Tax Exempt";
				 this->taxExempt1->UseVisualStyleBackColor = false;
				 // 
				 // autoDisch1
				 // 
				 this->autoDisch1->AutoSize = true;
				 this->autoDisch1->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoDisch1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoDisch1->Location = System::Drawing::Point(7, 186);
				 this->autoDisch1->Name = L"autoDisch1";
				 this->autoDisch1->Size = System::Drawing::Size(88, 17);
				 this->autoDisch1->TabIndex = 22;
				 this->autoDisch1->Text = L"Auto Disch";
				 this->autoDisch1->UseVisualStyleBackColor = false;
				 this->autoDisch1->Visible = false;
				 this->autoDisch1->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoDisch1_CheckedChanged);
				 // 
				 // all1
				 // 
				 this->all1->BackColor = System::Drawing::Color::Transparent;
				 this->all1->Enabled = false;
				 this->all1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->all1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->all1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->all1->ForeColor = System::Drawing::Color::Black;
				 this->all1->Location = System::Drawing::Point(42, 12);
				 this->all1->Name = L"all1";
				 this->all1->Size = System::Drawing::Size(46, 30);
				 this->all1->TabIndex = 24;
				 this->all1->Text = L"ALL";
				 this->all1->UseVisualStyleBackColor = false;
				 this->all1->Click += gcnew System::EventHandler(this, &Form1::all1_Click);
				 // 
				 // laneACb2
				 // 
				 this->laneACb2->AutoSize = true;
				 this->laneACb2->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneACb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneACb2->Location = System::Drawing::Point(7, 166);
				 this->laneACb2->Name = L"laneACb2";
				 this->laneACb2->Size = System::Drawing::Size(41, 17);
				 this->laneACb2->TabIndex = 41;
				 this->laneACb2->Text = L"P2";
				 this->laneACb2->UseVisualStyleBackColor = false;
				 // 
				 // adapt1
				 // 
				 this->adapt1->AutoSize = true;
				 this->adapt1->BackColor = System::Drawing::Color::Gainsboro;
				 this->adapt1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->adapt1->Location = System::Drawing::Point(7, 226);
				 this->adapt1->Name = L"adapt1";
				 this->adapt1->Size = System::Drawing::Size(76, 17);
				 this->adapt1->TabIndex = 25;
				 this->adapt1->Text = L"Adaptive";
				 this->adapt1->UseVisualStyleBackColor = false;
				 this->adapt1->CheckedChanged += gcnew System::EventHandler(this, &Form1::adapt1_CheckedChanged);
				 // 
				 // dataGridTruck
				 // 
				 this->dataGridTruck->AllowUserToAddRows = false;
				 this->dataGridTruck->AllowUserToDeleteRows = false;
				 this->dataGridTruck->AutoGenerateColumns = false;
				 this->dataGridTruck->BackgroundColor = System::Drawing::Color::Gainsboro;
				 this->dataGridTruck->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->dataGridTruck->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
					 this->stNameDataGridViewTextBoxColumn,
						 this->nRateDataGridViewTextBoxColumn, this->nCapacityDataGridViewTextBoxColumn
				 });
				 this->dataGridTruck->DataSource = this->truckBindingSource;
				 this->dataGridTruck->Location = System::Drawing::Point(66, 620);
				 this->dataGridTruck->MultiSelect = false;
				 this->dataGridTruck->Name = L"dataGridTruck";
				 this->dataGridTruck->ReadOnly = true;
				 this->dataGridTruck->RowHeadersVisible = false;
				 this->dataGridTruck->RowHeadersWidth = 30;
				 this->dataGridTruck->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->dataGridTruck->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
				 this->dataGridTruck->Size = System::Drawing::Size(260, 240);
				 this->dataGridTruck->TabIndex = 31;
				 this->dataGridTruck->Visible = false;
				 this->dataGridTruck->CellMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &Form1::dataGridTruck_RowHeaderMouseDoubleClick);
				 this->dataGridTruck->ColumnHeaderMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &Form1::dataGridTruck_ColumnHeaderMouseClick);
				 // 
				 // stNameDataGridViewTextBoxColumn
				 // 
				 this->stNameDataGridViewTextBoxColumn->DataPropertyName = L"stName";
				 dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->stNameDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle1;
				 this->stNameDataGridViewTextBoxColumn->HeaderText = L"Name";
				 this->stNameDataGridViewTextBoxColumn->Name = L"stNameDataGridViewTextBoxColumn";
				 this->stNameDataGridViewTextBoxColumn->ReadOnly = true;
				 // 
				 // nRateDataGridViewTextBoxColumn
				 // 
				 this->nRateDataGridViewTextBoxColumn->DataPropertyName = L"nRate";
				 dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->nRateDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle2;
				 this->nRateDataGridViewTextBoxColumn->HeaderText = L"Rate";
				 this->nRateDataGridViewTextBoxColumn->Name = L"nRateDataGridViewTextBoxColumn";
				 this->nRateDataGridViewTextBoxColumn->ReadOnly = true;
				 this->nRateDataGridViewTextBoxColumn->Width = 70;
				 // 
				 // nCapacityDataGridViewTextBoxColumn
				 // 
				 this->nCapacityDataGridViewTextBoxColumn->DataPropertyName = L"nCapacity";
				 dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->nCapacityDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle3;
				 this->nCapacityDataGridViewTextBoxColumn->HeaderText = L"Capacity";
				 this->nCapacityDataGridViewTextBoxColumn->Name = L"nCapacityDataGridViewTextBoxColumn";
				 this->nCapacityDataGridViewTextBoxColumn->ReadOnly = true;
				 this->nCapacityDataGridViewTextBoxColumn->Width = 70;
				 // 
				 // truckBindingSource
				 // 
				 this->truckBindingSource->DataSource = As::Truck::typeid;
				 // 
				 // zoom1
				 // 
				 this->zoom1->BackColor = System::Drawing::Color::Gainsboro;
				 this->zoom1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->zoom1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->zoom1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->zoom1->ForeColor = System::Drawing::Color::Black;
				 this->zoom1->Location = System::Drawing::Point(14, 828);
				 this->zoom1->Name = L"zoom1";
				 this->zoom1->Size = System::Drawing::Size(48, 30);
				 this->zoom1->TabIndex = 23;
				 this->zoom1->Text = L"Zoom";
				 this->zoom1->UseVisualStyleBackColor = false;
				 this->zoom1->Visible = false;
				 this->zoom1->Click += gcnew System::EventHandler(this, &Form1::zoom1_Click);
				 // 
				 // ulinkLb
				 // 
				 this->ulinkLb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->ulinkLb->AutoSize = true;
				 this->ulinkLb->BackColor = System::Drawing::Color::Red;
				 this->ulinkLb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->ulinkLb->Cursor = System::Windows::Forms::Cursors::No;
				 this->ulinkLb->ForeColor = System::Drawing::Color::Black;
				 this->ulinkLb->Location = System::Drawing::Point(1116, 5);
				 this->ulinkLb->Name = L"ulinkLb";
				 this->ulinkLb->Size = System::Drawing::Size(46, 15);
				 this->ulinkLb->TabIndex = 0;
				 this->ulinkLb->Text = L"ULINK";
				 // 
				 // optoLb
				 // 
				 this->optoLb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->optoLb->AutoSize = true;
				 this->optoLb->BackColor = System::Drawing::Color::Red;
				 this->optoLb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->optoLb->Cursor = System::Windows::Forms::Cursors::No;
				 this->optoLb->ForeColor = System::Drawing::Color::Black;
				 this->optoLb->Location = System::Drawing::Point(1170, 5);
				 this->optoLb->Name = L"optoLb";
				 this->optoLb->Size = System::Drawing::Size(43, 15);
				 this->optoLb->TabIndex = 0;
				 this->optoLb->Text = L"OPTO";
				 this->optoLb->Click += gcnew System::EventHandler(this, &Form1::optoLb_Click);
				 // 
				 // pauseBt2
				 // 
				 this->pauseBt2->BackColor = System::Drawing::Color::Gold;
				 this->pauseBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->pauseBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->pauseBt2->ForeColor = System::Drawing::Color::Black;
				 this->pauseBt2->Location = System::Drawing::Point(310, 511);
				 this->pauseBt2->Name = L"pauseBt2";
				 this->pauseBt2->Size = System::Drawing::Size(75, 30);
				 this->pauseBt2->TabIndex = 0;
				 this->pauseBt2->Text = L"HOLD";
				 this->pauseBt2->UseVisualStyleBackColor = false;
				 this->pauseBt2->Click += gcnew System::EventHandler(this, &Form1::pause2_Click);
				 // 
				 // stopBt2
				 // 
				 this->stopBt2->BackColor = System::Drawing::Color::Red;
				 this->stopBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->stopBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->stopBt2->ForeColor = System::Drawing::Color::Black;
				 this->stopBt2->Location = System::Drawing::Point(310, 547);
				 this->stopBt2->Name = L"stopBt2";
				 this->stopBt2->Size = System::Drawing::Size(75, 30);
				 this->stopBt2->TabIndex = 0;
				 this->stopBt2->Text = L"ABORT";
				 this->stopBt2->UseVisualStyleBackColor = false;
				 this->stopBt2->Click += gcnew System::EventHandler(this, &Form1::stopBt2_Click);
				 // 
				 // dropBt2
				 // 
				 this->dropBt2->BackColor = System::Drawing::Color::Transparent;
				 this->dropBt2->Enabled = false;
				 this->dropBt2->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dropBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dropBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropBt2->ForeColor = System::Drawing::Color::Black;
				 this->dropBt2->Location = System::Drawing::Point(310, 438);
				 this->dropBt2->Name = L"dropBt2";
				 this->dropBt2->Size = System::Drawing::Size(75, 30);
				 this->dropBt2->TabIndex = 0;
				 this->dropBt2->Text = L"DROP";
				 this->dropBt2->UseVisualStyleBackColor = false;
				 this->dropBt2->Click += gcnew System::EventHandler(this, &Form1::dropBt2_Click);
				 // 
				 // custLb2
				 // 
				 this->custLb2->AutoSize = true;
				 this->custLb2->BackColor = System::Drawing::Color::Transparent;
				 this->custLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->custLb2->ForeColor = System::Drawing::Color::DarkGreen;
				 this->custLb2->Location = System::Drawing::Point(6, 23);
				 this->custLb2->Name = L"custLb2";
				 this->custLb2->Size = System::Drawing::Size(59, 13);
				 this->custLb2->TabIndex = 0;
				 this->custLb2->Text = L"Customer";
				 // 
				 // dropsLb2
				 // 
				 this->dropsLb2->AutoSize = true;
				 this->dropsLb2->BackColor = System::Drawing::Color::Transparent;
				 this->dropsLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropsLb2->ForeColor = System::Drawing::Color::DarkGreen;
				 this->dropsLb2->Location = System::Drawing::Point(325, 344);
				 this->dropsLb2->Name = L"dropsLb2";
				 this->dropsLb2->Size = System::Drawing::Size(45, 15);
				 this->dropsLb2->TabIndex = 0;
				 this->dropsLb2->Text = L"Drops";
				 // 
				 // scale2
				 // 
				 this->scale2->BackColor = System::Drawing::Color::PaleGreen;
				 this->scale2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->scale2->ForeColor = System::Drawing::Color::Black;
				 this->scale2->Location = System::Drawing::Point(120, 440);
				 this->scale2->Name = L"scale2";
				 this->scale2->Size = System::Drawing::Size(100, 20);
				 this->scale2->TabIndex = 0;
				 this->scale2->Text = L"1111111111";
				 this->scale2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->scale2->Visible = false;
				 // 
				 // nextBt2
				 // 
				 this->nextBt2->BackColor = System::Drawing::Color::Transparent;
				 this->nextBt2->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->nextBt2->Enabled = false;
				 this->nextBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->nextBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->nextBt2->ForeColor = System::Drawing::Color::Black;
				 this->nextBt2->Location = System::Drawing::Point(303, 55);
				 this->nextBt2->Name = L"nextBt2";
				 this->nextBt2->Size = System::Drawing::Size(82, 30);
				 this->nextBt2->TabIndex = 0;
				 this->nextBt2->Text = L"NEXT ";
				 this->nextBt2->UseVisualStyleBackColor = false;
				 this->nextBt2->Click += gcnew System::EventHandler(this, &Form1::nextBt2_Click);
				 // 
				 // matLb2
				 // 
				 this->matLb2->AutoSize = true;
				 this->matLb2->BackColor = System::Drawing::Color::Transparent;
				 this->matLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->matLb2->ForeColor = System::Drawing::Color::DarkGreen;
				 this->matLb2->Location = System::Drawing::Point(6, 76);
				 this->matLb2->Name = L"matLb2";
				 this->matLb2->Size = System::Drawing::Size(52, 13);
				 this->matLb2->TabIndex = 0;
				 this->matLb2->Text = L"Material";
				 // 
				 // targetLb2
				 // 
				 this->targetLb2->AutoSize = true;
				 this->targetLb2->BackColor = System::Drawing::Color::Transparent;
				 this->targetLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->targetLb2->ForeColor = System::Drawing::Color::DarkGreen;
				 this->targetLb2->Location = System::Drawing::Point(6, 160);
				 this->targetLb2->Name = L"targetLb2";
				 this->targetLb2->Size = System::Drawing::Size(44, 13);
				 this->targetLb2->TabIndex = 0;
				 this->targetLb2->Text = L"Target";
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->BackColor = System::Drawing::Color::Transparent;
				 this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label6->ForeColor = System::Drawing::Color::DarkGreen;
				 this->label6->Location = System::Drawing::Point(215, 59);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(32, 13);
				 this->label6->TabIndex = 0;
				 this->label6->Text = L"New";
				 this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 // 
				 // ticketNum2
				 // 
				 this->ticketNum2->BackColor = System::Drawing::Color::PaleGreen;
				 this->ticketNum2->Cursor = System::Windows::Forms::Cursors::No;
				 this->ticketNum2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticketNum2->ForeColor = System::Drawing::Color::Black;
				 this->ticketNum2->Location = System::Drawing::Point(249, 55);
				 this->ticketNum2->Name = L"ticketNum2";
				 this->ticketNum2->Size = System::Drawing::Size(40, 28);
				 this->ticketNum2->TabIndex = 0;
				 this->ticketNum2->Text = L"000";
				 this->ticketNum2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // truckPic2
				 // 
				 this->truckPic2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"truckPic2.BackgroundImage")));
				 this->truckPic2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->truckPic2->Location = System::Drawing::Point(23, 528);
				 this->truckPic2->Name = L"truckPic2";
				 this->truckPic2->Size = System::Drawing::Size(78, 57);
				 this->truckPic2->TabIndex = 0;
				 this->truckPic2->TabStop = false;
				 // 
				 // ticLb2
				 // 
				 this->ticLb2->AutoSize = true;
				 this->ticLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticLb2->Location = System::Drawing::Point(6, 104);
				 this->ticLb2->Name = L"ticLb2";
				 this->ticLb2->Size = System::Drawing::Size(55, 13);
				 this->ticLb2->TabIndex = 0;
				 this->ticLb2->Text = L"Ticket #";
				 // 
				 // JobLb2
				 // 
				 this->JobLb2->AutoSize = true;
				 this->JobLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->JobLb2->Location = System::Drawing::Point(6, 48);
				 this->JobLb2->Name = L"JobLb2";
				 this->JobLb2->Size = System::Drawing::Size(27, 13);
				 this->JobLb2->TabIndex = 0;
				 this->JobLb2->Text = L"Job";
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->groupBox2->Controls->Add(this->siloBar24);
				 this->groupBox2->Controls->Add(this->resetBt2);
				 this->groupBox2->Controls->Add(this->laneB2ndCB);
				 this->groupBox2->Controls->Add(this->prod06Lb);
				 this->groupBox2->Controls->Add(this->copyLb2);
				 this->groupBox2->Controls->Add(this->numCopy2);
				 this->groupBox2->Controls->Add(this->prod05Lb);
				 this->groupBox2->Controls->Add(this->prod04Lb);
				 this->groupBox2->Controls->Add(this->lane2StatLB);
				 this->groupBox2->Controls->Add(this->lite2);
				 this->groupBox2->Controls->Add(this->wrLb);
				 this->groupBox2->Controls->Add(this->rdLb);
				 this->groupBox2->Controls->Add(this->safe6);
				 this->groupBox2->Controls->Add(this->safe5);
				 this->groupBox2->Controls->Add(this->safe4);
				 this->groupBox2->Controls->Add(this->laneBCb1);
				 this->groupBox2->Controls->Add(this->webBrowser2);
				 this->groupBox2->Controls->Add(this->taxExempt2);
				 this->groupBox2->Controls->Add(this->groupBoxB);
				 this->groupBox2->Controls->Add(this->label2);
				 this->groupBox2->Controls->Add(this->plant2);
				 this->groupBox2->Controls->Add(this->laneBCb3);
				 this->groupBox2->Controls->Add(this->adapt2);
				 this->groupBox2->Controls->Add(this->all2);
				 this->groupBox2->Controls->Add(this->autoDisch2);
				 this->groupBox2->Controls->Add(this->silo2);
				 this->groupBox2->Controls->Add(this->fill23);
				 this->groupBox2->Controls->Add(this->pictureBox2);
				 this->groupBox2->Controls->Add(this->fill22);
				 this->groupBox2->Controls->Add(this->fill2);
				 this->groupBox2->Controls->Add(this->truckBar2);
				 this->groupBox2->Controls->Add(this->scaleBar2);
				 this->groupBox2->Controls->Add(this->siloBar23);
				 this->groupBox2->Controls->Add(this->siloBar22);
				 this->groupBox2->Controls->Add(this->siloBar2);
				 this->groupBox2->Controls->Add(this->jog2);
				 this->groupBox2->Controls->Add(this->readyBt2);
				 this->groupBox2->Controls->Add(this->autoFall2);
				 this->groupBox2->Controls->Add(this->flow2);
				 this->groupBox2->Controls->Add(this->printOnly2);
				 this->groupBox2->Controls->Add(this->printTarget2);
				 this->groupBox2->Controls->Add(this->tonnage2);
				 this->groupBox2->Controls->Add(this->label9);
				 this->groupBox2->Controls->Add(this->label4);
				 this->groupBox2->Controls->Add(this->man2);
				 this->groupBox2->Controls->Add(this->autoBt2);
				 this->groupBox2->Controls->Add(this->material2);
				 this->groupBox2->Controls->Add(this->tic_num2);
				 this->groupBox2->Controls->Add(this->target2);
				 this->groupBox2->Controls->Add(this->truck2);
				 this->groupBox2->Controls->Add(this->Job2);
				 this->groupBox2->Controls->Add(this->customer2);
				 this->groupBox2->Controls->Add(this->addBt2);
				 this->groupBox2->Controls->Add(this->dischBt2);
				 this->groupBox2->Controls->Add(this->truckLb2);
				 this->groupBox2->Controls->Add(this->drops24);
				 this->groupBox2->Controls->Add(this->drops23);
				 this->groupBox2->Controls->Add(this->drops22);
				 this->groupBox2->Controls->Add(this->drops21);
				 this->groupBox2->Controls->Add(this->JobLb2);
				 this->groupBox2->Controls->Add(this->cnt2);
				 this->groupBox2->Controls->Add(this->ticLb2);
				 this->groupBox2->Controls->Add(this->truckPic2);
				 this->groupBox2->Controls->Add(this->ticketNum2);
				 this->groupBox2->Controls->Add(this->label6);
				 this->groupBox2->Controls->Add(this->targetLb2);
				 this->groupBox2->Controls->Add(this->matLb2);
				 this->groupBox2->Controls->Add(this->nextBt2);
				 this->groupBox2->Controls->Add(this->scale2);
				 this->groupBox2->Controls->Add(this->dropsLb2);
				 this->groupBox2->Controls->Add(this->custLb2);
				 this->groupBox2->Controls->Add(this->dropBt2);
				 this->groupBox2->Controls->Add(this->stopBt2);
				 this->groupBox2->Controls->Add(this->pauseBt2);
				 this->groupBox2->Cursor = System::Windows::Forms::Cursors::Default;
				 this->groupBox2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->groupBox2->ForeColor = System::Drawing::Color::DarkGreen;
				 this->groupBox2->Location = System::Drawing::Point(435, 27);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(400, 840);
				 this->groupBox2->TabIndex = 0;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"Lane B";
				 // 
				 // siloBar24
				 // 
				 this->siloBar24->Add = false;
				 this->siloBar24->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar24->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar24->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar24->Count = 0;
				 this->siloBar24->Delay = false;
				 this->siloBar24->DisableInv = false;
				 this->siloBar24->Empty = false;
				 this->siloBar24->Idle = true;
				 this->siloBar24->Inventory = 100;
				 this->siloBar24->Location = System::Drawing::Point(156, 305);
				 this->siloBar24->Maximum = 100;
				 this->siloBar24->Metric = false;
				 this->siloBar24->Name = L"siloBar24";
				 this->siloBar24->Number = 6;
				 this->siloBar24->Open = false;
				 this->siloBar24->ScaleInLB = false;
				 this->siloBar24->Separators = 4;
				 this->siloBar24->Size = System::Drawing::Size(88, 230);
				 this->siloBar24->TabIndex = 62;
				 this->siloBar24->Target = 0;
				 this->siloBar24->Text = L"Silo6";
				 this->siloBar24->Tol = false;
				 this->siloBar24->ValMan = 0;
				 this->siloBar24->Value = 0;
				 this->siloBar24->Visible = false;
				 // 
				 // resetBt2
				 // 
				 this->resetBt2->BackColor = System::Drawing::Color::Red;
				 this->resetBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->resetBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->resetBt2->ForeColor = System::Drawing::Color::Black;
				 this->resetBt2->Location = System::Drawing::Point(307, 94);
				 this->resetBt2->Name = L"resetBt2";
				 this->resetBt2->Size = System::Drawing::Size(75, 30);
				 this->resetBt2->TabIndex = 60;
				 this->resetBt2->Text = L"RESET";
				 this->resetBt2->UseVisualStyleBackColor = false;
				 this->resetBt2->Click += gcnew System::EventHandler(this, &Form1::resetBt2_Click);
				 // 
				 // laneB2ndCB
				 // 
				 this->laneB2ndCB->AutoSize = true;
				 this->laneB2ndCB->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneB2ndCB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneB2ndCB->Location = System::Drawing::Point(304, 232);
				 this->laneB2ndCB->Name = L"laneB2ndCB";
				 this->laneB2ndCB->Size = System::Drawing::Size(79, 17);
				 this->laneB2ndCB->TabIndex = 61;
				 this->laneB2ndCB->Text = L"2nd Copy";
				 this->laneB2ndCB->UseVisualStyleBackColor = false;
				 // 
				 // prod06Lb
				 // 
				 this->prod06Lb->AutoSize = true;
				 this->prod06Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod06Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod06Lb->ForeColor = System::Drawing::Color::White;
				 this->prod06Lb->Location = System::Drawing::Point(213, 225);
				 this->prod06Lb->Name = L"prod06Lb";
				 this->prod06Lb->Size = System::Drawing::Size(81, 13);
				 this->prod06Lb->TabIndex = 56;
				 this->prod06Lb->Text = L"ABCDABCDA";
				 this->prod06Lb->Visible = false;
				 // 
				 // copyLb2
				 // 
				 this->copyLb2->AutoSize = true;
				 this->copyLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->copyLb2->Location = System::Drawing::Point(338, 202);
				 this->copyLb2->Name = L"copyLb2";
				 this->copyLb2->Size = System::Drawing::Size(49, 13);
				 this->copyLb2->TabIndex = 60;
				 this->copyLb2->Text = L"Tickets";
				 // 
				 // numCopy2
				 // 
				 this->numCopy2->Location = System::Drawing::Point(304, 197);
				 this->numCopy2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
				 this->numCopy2->Name = L"numCopy2";
				 this->numCopy2->Size = System::Drawing::Size(30, 23);
				 this->numCopy2->TabIndex = 59;
				 this->numCopy2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // prod05Lb
				 // 
				 this->prod05Lb->AutoSize = true;
				 this->prod05Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod05Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod05Lb->ForeColor = System::Drawing::Color::White;
				 this->prod05Lb->Location = System::Drawing::Point(114, 225);
				 this->prod05Lb->Name = L"prod05Lb";
				 this->prod05Lb->Size = System::Drawing::Size(81, 13);
				 this->prod05Lb->TabIndex = 56;
				 this->prod05Lb->Text = L"ABCDABCDA";
				 this->prod05Lb->Visible = false;
				 // 
				 // prod04Lb
				 // 
				 this->prod04Lb->AutoSize = true;
				 this->prod04Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod04Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod04Lb->ForeColor = System::Drawing::Color::White;
				 this->prod04Lb->Location = System::Drawing::Point(14, 225);
				 this->prod04Lb->Name = L"prod04Lb";
				 this->prod04Lb->Size = System::Drawing::Size(81, 13);
				 this->prod04Lb->TabIndex = 56;
				 this->prod04Lb->Text = L"ABCDABCDA";
				 this->prod04Lb->Visible = false;
				 // 
				 // lane2StatLB
				 // 
				 this->lane2StatLB->BackColor = System::Drawing::Color::Gainsboro;
				 this->lane2StatLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->lane2StatLB->ForeColor = System::Drawing::Color::Black;
				 this->lane2StatLB->Location = System::Drawing::Point(69, 1);
				 this->lane2StatLB->Name = L"lane2StatLB";
				 this->lane2StatLB->Size = System::Drawing::Size(50, 13);
				 this->lane2StatLB->TabIndex = 54;
				 this->lane2StatLB->Text = L"S-00";
				 this->lane2StatLB->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->lane2StatLB->Visible = false;
				 // 
				 // lite2
				 // 
				 this->lite2->BackColor = System::Drawing::Color::Transparent;
				 this->lite2->Cursor = System::Windows::Forms::Cursors::No;
				 this->lite2->Enabled = false;
				 this->lite2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->lite2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"lite2.Image")));
				 this->lite2->Location = System::Drawing::Point(6, 592);
				 this->lite2->Name = L"lite2";
				 this->lite2->Size = System::Drawing::Size(48, 48);
				 this->lite2->TabIndex = 34;
				 // 
				 // wrLb
				 // 
				 this->wrLb->BackColor = System::Drawing::Color::PaleGreen;
				 this->wrLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->wrLb->ForeColor = System::Drawing::Color::Black;
				 this->wrLb->Location = System::Drawing::Point(148, 542);
				 this->wrLb->Name = L"wrLb";
				 this->wrLb->Size = System::Drawing::Size(100, 20);
				 this->wrLb->TabIndex = 55;
				 this->wrLb->Text = L"1111111111";
				 this->wrLb->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->wrLb->Visible = false;
				 // 
				 // rdLb
				 // 
				 this->rdLb->BackColor = System::Drawing::Color::MediumTurquoise;
				 this->rdLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->rdLb->ForeColor = System::Drawing::Color::Black;
				 this->rdLb->Location = System::Drawing::Point(150, 511);
				 this->rdLb->Name = L"rdLb";
				 this->rdLb->Size = System::Drawing::Size(100, 20);
				 this->rdLb->TabIndex = 54;
				 this->rdLb->Text = L"abcd";
				 this->rdLb->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->rdLb->Visible = false;
				 // 
				 // safe6
				 // 
				 this->safe6->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe6.Image")));
				 this->safe6->Location = System::Drawing::Point(250, 190);
				 this->safe6->Name = L"safe6";
				 this->safe6->Size = System::Drawing::Size(24, 24);
				 this->safe6->TabIndex = 53;
				 this->safe6->Visible = false;
				 // 
				 // safe5
				 // 
				 this->safe5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe5.Image")));
				 this->safe5->Location = System::Drawing::Point(150, 190);
				 this->safe5->Name = L"safe5";
				 this->safe5->Size = System::Drawing::Size(24, 24);
				 this->safe5->TabIndex = 52;
				 this->safe5->Visible = false;
				 // 
				 // safe4
				 // 
				 this->safe4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe4.Image")));
				 this->safe4->Location = System::Drawing::Point(50, 190);
				 this->safe4->Name = L"safe4";
				 this->safe4->Size = System::Drawing::Size(24, 24);
				 this->safe4->TabIndex = 51;
				 this->safe4->Visible = false;
				 // 
				 // laneBCb1
				 // 
				 this->laneBCb1->AutoSize = true;
				 this->laneBCb1->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneBCb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneBCb1->Location = System::Drawing::Point(303, 170);
				 this->laneBCb1->Name = L"laneBCb1";
				 this->laneBCb1->Size = System::Drawing::Size(41, 17);
				 this->laneBCb1->TabIndex = 48;
				 this->laneBCb1->Text = L"P1";
				 this->laneBCb1->UseVisualStyleBackColor = false;
				 // 
				 // webBrowser2
				 // 
				 this->webBrowser2->AllowWebBrowserDrop = false;
				 this->webBrowser2->IsWebBrowserContextMenuEnabled = false;
				 this->webBrowser2->Location = System::Drawing::Point(6, 592);
				 this->webBrowser2->MaximumSize = System::Drawing::Size(800, 600);
				 this->webBrowser2->MinimumSize = System::Drawing::Size(20, 20);
				 this->webBrowser2->Name = L"webBrowser2";
				 this->webBrowser2->ScriptErrorsSuppressed = true;
				 this->webBrowser2->Size = System::Drawing::Size(386, 240);
				 this->webBrowser2->TabIndex = 0;
				 this->webBrowser2->TabStop = false;
				 this->webBrowser2->Visible = false;
				 this->webBrowser2->WebBrowserShortcutsEnabled = false;
				 // 
				 // taxExempt2
				 // 
				 this->taxExempt2->AutoSize = true;
				 this->taxExempt2->BackColor = System::Drawing::Color::Gainsboro;
				 this->taxExempt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->taxExempt2->Location = System::Drawing::Point(304, 150);
				 this->taxExempt2->Name = L"taxExempt2";
				 this->taxExempt2->Size = System::Drawing::Size(92, 17);
				 this->taxExempt2->TabIndex = 47;
				 this->taxExempt2->Text = L"Tax Exempt";
				 this->taxExempt2->UseVisualStyleBackColor = false;
				 // 
				 // groupBoxB
				 // 
				 this->groupBoxB->BackColor = System::Drawing::Color::Silver;
				 this->groupBoxB->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->groupBoxB->Controls->Add(this->okB);
				 this->groupBoxB->Controls->Add(this->grossB);
				 this->groupBoxB->Controls->Add(this->tareB);
				 this->groupBoxB->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBoxB->ForeColor = System::Drawing::Color::DarkGreen;
				 this->groupBoxB->Location = System::Drawing::Point(98, 306);
				 this->groupBoxB->Name = L"groupBoxB";
				 this->groupBoxB->Size = System::Drawing::Size(204, 60);
				 this->groupBoxB->TabIndex = 46;
				 this->groupBoxB->TabStop = false;
				 this->groupBoxB->Text = L"Tare       Gross";
				 this->groupBoxB->Visible = false;
				 // 
				 // okB
				 // 
				 this->okB->BackColor = System::Drawing::Color::PaleGreen;
				 this->okB->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->okB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->okB->Location = System::Drawing::Point(137, 22);
				 this->okB->Name = L"okB";
				 this->okB->Size = System::Drawing::Size(50, 26);
				 this->okB->TabIndex = 2;
				 this->okB->Text = L"OK";
				 this->okB->UseVisualStyleBackColor = false;
				 this->okB->Click += gcnew System::EventHandler(this, &Form1::okB_Click);
				 // 
				 // grossB
				 // 
				 this->grossB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->grossB->Location = System::Drawing::Point(74, 22);
				 this->grossB->Name = L"grossB";
				 this->grossB->Size = System::Drawing::Size(54, 26);
				 this->grossB->TabIndex = 1;
				 this->grossB->Text = L"xx.xx";
				 this->grossB->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 // 
				 // tareB
				 // 
				 this->tareB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tareB->Location = System::Drawing::Point(6, 22);
				 this->tareB->Name = L"tareB";
				 this->tareB->Size = System::Drawing::Size(57, 26);
				 this->tareB->TabIndex = 0;
				 this->tareB->Text = L"xx.xx";
				 this->tareB->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->BackColor = System::Drawing::Color::Transparent;
				 this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label2->ForeColor = System::Drawing::Color::DarkGreen;
				 this->label2->Location = System::Drawing::Point(142, 104);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(36, 13);
				 this->label2->TabIndex = 45;
				 this->label2->Text = L"Plant";
				 this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 // 
				 // plant2
				 // 
				 this->plant2->BackColor = System::Drawing::Color::Gainsboro;
				 this->plant2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->plant2->Cursor = System::Windows::Forms::Cursors::No;
				 this->plant2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->plant2->ForeColor = System::Drawing::Color::Black;
				 this->plant2->Location = System::Drawing::Point(178, 100);
				 this->plant2->Name = L"plant2";
				 this->plant2->Size = System::Drawing::Size(30, 24);
				 this->plant2->TabIndex = 44;
				 this->plant2->Text = L"00";
				 this->plant2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // laneBCb3
				 // 
				 this->laneBCb3->AutoSize = true;
				 this->laneBCb3->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneBCb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneBCb3->Location = System::Drawing::Point(351, 170);
				 this->laneBCb3->Name = L"laneBCb3";
				 this->laneBCb3->Size = System::Drawing::Size(41, 17);
				 this->laneBCb3->TabIndex = 42;
				 this->laneBCb3->Text = L"P3";
				 this->laneBCb3->UseVisualStyleBackColor = false;
				 // 
				 // adapt2
				 // 
				 this->adapt2->AutoSize = true;
				 this->adapt2->BackColor = System::Drawing::Color::Gainsboro;
				 this->adapt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->adapt2->Location = System::Drawing::Point(304, 230);
				 this->adapt2->Name = L"adapt2";
				 this->adapt2->Size = System::Drawing::Size(76, 17);
				 this->adapt2->TabIndex = 31;
				 this->adapt2->Text = L"Adaptive";
				 this->adapt2->UseVisualStyleBackColor = false;
				 this->adapt2->CheckedChanged += gcnew System::EventHandler(this, &Form1::adapt2_CheckedChanged);
				 // 
				 // all2
				 // 
				 this->all2->BackColor = System::Drawing::Color::Transparent;
				 this->all2->Enabled = false;
				 this->all2->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->all2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->all2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->all2->ForeColor = System::Drawing::Color::Black;
				 this->all2->Location = System::Drawing::Point(339, 16);
				 this->all2->Name = L"all2";
				 this->all2->Size = System::Drawing::Size(46, 30);
				 this->all2->TabIndex = 30;
				 this->all2->Text = L"ALL";
				 this->all2->UseVisualStyleBackColor = false;
				 this->all2->Click += gcnew System::EventHandler(this, &Form1::all2_Click);
				 // 
				 // autoDisch2
				 // 
				 this->autoDisch2->AutoSize = true;
				 this->autoDisch2->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoDisch2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoDisch2->Location = System::Drawing::Point(304, 190);
				 this->autoDisch2->Name = L"autoDisch2";
				 this->autoDisch2->Size = System::Drawing::Size(88, 17);
				 this->autoDisch2->TabIndex = 28;
				 this->autoDisch2->Text = L"Auto Disch";
				 this->autoDisch2->UseVisualStyleBackColor = false;
				 this->autoDisch2->Visible = false;
				 this->autoDisch2->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoDisch2_CheckedChanged);
				 // 
				 // silo2
				 // 
				 this->silo2->BackColor = System::Drawing::Color::Gainsboro;
				 this->silo2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->silo2->ForeColor = System::Drawing::Color::Black;
				 this->silo2->Location = System::Drawing::Point(119, 476);
				 this->silo2->Name = L"silo2";
				 this->silo2->Size = System::Drawing::Size(38, 20);
				 this->silo2->TabIndex = 27;
				 this->silo2->Text = L"0000";
				 this->silo2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->silo2->Visible = false;
				 // 
				 // fill23
				 // 
				 this->fill23->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill23.Image")));
				 this->fill23->Location = System::Drawing::Point(270, 190);
				 this->fill23->Name = L"fill23";
				 this->fill23->Size = System::Drawing::Size(24, 24);
				 this->fill23->TabIndex = 26;
				 this->fill23->Visible = false;
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
				 this->pictureBox2->Location = System::Drawing::Point(65, 592);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(320, 240);
				 this->pictureBox2->TabIndex = 39;
				 this->pictureBox2->TabStop = false;
				 // 
				 // fill22
				 // 
				 this->fill22->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill22.Image")));
				 this->fill22->Location = System::Drawing::Point(171, 190);
				 this->fill22->Name = L"fill22";
				 this->fill22->Size = System::Drawing::Size(24, 24);
				 this->fill22->TabIndex = 25;
				 this->fill22->Visible = false;
				 // 
				 // fill2
				 // 
				 this->fill2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill2.Image")));
				 this->fill2->Location = System::Drawing::Point(70, 190);
				 this->fill2->Name = L"fill2";
				 this->fill2->Size = System::Drawing::Size(24, 24);
				 this->fill2->TabIndex = 23;
				 this->fill2->Visible = false;
				 // 
				 // truckBar2
				 // 
				 this->truckBar2->BarColor = System::Drawing::Color::PaleGreen;
				 this->truckBar2->BorderColor = System::Drawing::Color::Black;
				 this->truckBar2->FillStyle = As::BarCtl::FillStyles::Dashed;
				 this->truckBar2->Flow = 0;
				 this->truckBar2->Location = System::Drawing::Point(12, 496);
				 this->truckBar2->Maximum = 100;
				 this->truckBar2->Name = L"truckBar2";
				 this->truckBar2->Pct = 0;
				 this->truckBar2->ScaleInLB = false;
				 this->truckBar2->Separators = 0;
				 this->truckBar2->Size = System::Drawing::Size(80, 28);
				 this->truckBar2->TabIndex = 20;
				 this->truckBar2->Target = 10;
				 this->truckBar2->Text = L"barCtl1";
				 this->truckBar2->Value = 0;
				 this->truckBar2->Vertical = false;
				 // 
				 // scaleBar2
				 // 
				 this->scaleBar2->BackColor = System::Drawing::Color::LightGray;
				 this->scaleBar2->BarColor = System::Drawing::Color::Gainsboro;
				 this->scaleBar2->BorderColor = System::Drawing::Color::Black;
				 this->scaleBar2->Flow = 0;
				 this->scaleBar2->Idle = false;
				 this->scaleBar2->Label = 0;
				 this->scaleBar2->Location = System::Drawing::Point(12, 436);
				 this->scaleBar2->Maximum = 100;
				 this->scaleBar2->Metric = false;
				 this->scaleBar2->Name = L"scaleBar2";
				 this->scaleBar2->Open = false;
				 this->scaleBar2->ScaleInLB = false;
				 this->scaleBar2->Size = System::Drawing::Size(100, 52);
				 this->scaleBar2->TabIndex = 19;
				 this->scaleBar2->Target = 0;
				 this->scaleBar2->Topl = 0;
				 this->scaleBar2->Value = 0;
				 // 
				 // siloBar23
				 // 
				 this->siloBar23->Add = false;
				 this->siloBar23->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar23->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar23->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar23->Count = 0;
				 this->siloBar23->Delay = false;
				 this->siloBar23->DisableInv = false;
				 this->siloBar23->Empty = false;
				 this->siloBar23->Idle = true;
				 this->siloBar23->Inventory = 100;
				 this->siloBar23->Location = System::Drawing::Point(210, 196);
				 this->siloBar23->Maximum = 100;
				 this->siloBar23->Metric = false;
				 this->siloBar23->Name = L"siloBar23";
				 this->siloBar23->Number = 6;
				 this->siloBar23->Open = false;
				 this->siloBar23->ScaleInLB = false;
				 this->siloBar23->Separators = 4;
				 this->siloBar23->Size = System::Drawing::Size(88, 230);
				 this->siloBar23->TabIndex = 18;
				 this->siloBar23->Target = 0;
				 this->siloBar23->Text = L"Silo6";
				 this->siloBar23->Tol = false;
				 this->siloBar23->ValMan = 0;
				 this->siloBar23->Value = 0;
				 this->siloBar23->Visible = false;
				 this->siloBar23->DoubleClick += gcnew System::EventHandler(this, &Form1::flow6_Click);
				 this->siloBar23->Click += gcnew System::EventHandler(this, &Form1::siloBar23_Click);
				 // 
				 // siloBar22
				 // 
				 this->siloBar22->Add = false;
				 this->siloBar22->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar22->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar22->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar22->Count = 0;
				 this->siloBar22->Delay = false;
				 this->siloBar22->DisableInv = false;
				 this->siloBar22->Empty = false;
				 this->siloBar22->Idle = true;
				 this->siloBar22->Inventory = 100;
				 this->siloBar22->Location = System::Drawing::Point(110, 196);
				 this->siloBar22->Maximum = 100;
				 this->siloBar22->Metric = false;
				 this->siloBar22->Name = L"siloBar22";
				 this->siloBar22->Number = 5;
				 this->siloBar22->Open = false;
				 this->siloBar22->ScaleInLB = false;
				 this->siloBar22->Separators = 4;
				 this->siloBar22->Size = System::Drawing::Size(88, 230);
				 this->siloBar22->TabIndex = 17;
				 this->siloBar22->Target = 0;
				 this->siloBar22->Text = L"Silo5";
				 this->siloBar22->Tol = false;
				 this->siloBar22->ValMan = 0;
				 this->siloBar22->Value = 0;
				 this->siloBar22->Visible = false;
				 this->siloBar22->DoubleClick += gcnew System::EventHandler(this, &Form1::flow5_Click);
				 this->siloBar22->Click += gcnew System::EventHandler(this, &Form1::siloBar22_Click);
				 // 
				 // siloBar2
				 // 
				 this->siloBar2->Add = false;
				 this->siloBar2->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar2->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar2->BorderColor = System::Drawing::Color::Black;
				 this->siloBar2->Count = 0;
				 this->siloBar2->Delay = false;
				 this->siloBar2->DisableInv = false;
				 this->siloBar2->Empty = false;
				 this->siloBar2->Idle = false;
				 this->siloBar2->Inventory = 100;
				 this->siloBar2->Location = System::Drawing::Point(10, 196);
				 this->siloBar2->Maximum = 100;
				 this->siloBar2->Metric = false;
				 this->siloBar2->Name = L"siloBar2";
				 this->siloBar2->Number = 4;
				 this->siloBar2->Open = false;
				 this->siloBar2->ScaleInLB = false;
				 this->siloBar2->Separators = 4;
				 this->siloBar2->Size = System::Drawing::Size(88, 230);
				 this->siloBar2->TabIndex = 16;
				 this->siloBar2->Target = 0;
				 this->siloBar2->Text = L"Silo4";
				 this->siloBar2->Tol = false;
				 this->siloBar2->ValMan = 0;
				 this->siloBar2->Value = 0;
				 this->siloBar2->DoubleClick += gcnew System::EventHandler(this, &Form1::flow4_Click);
				 this->siloBar2->Click += gcnew System::EventHandler(this, &Form1::siloBar2_Click);
				 // 
				 // jog2
				 // 
				 this->jog2->AutoSize = true;
				 this->jog2->BackColor = System::Drawing::Color::Gainsboro;
				 this->jog2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->jog2->Location = System::Drawing::Point(304, 250);
				 this->jog2->Name = L"jog2";
				 this->jog2->Size = System::Drawing::Size(46, 17);
				 this->jog2->TabIndex = 11;
				 this->jog2->Text = L"Jog";
				 this->jog2->UseVisualStyleBackColor = false;
				 this->jog2->CheckedChanged += gcnew System::EventHandler(this, &Form1::jog2_CheckedChanged);
				 // 
				 // readyBt2
				 // 
				 this->readyBt2->BackColor = System::Drawing::Color::Transparent;
				 this->readyBt2->Enabled = false;
				 this->readyBt2->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->readyBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->readyBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->readyBt2->ForeColor = System::Drawing::Color::Black;
				 this->readyBt2->Location = System::Drawing::Point(310, 270);
				 this->readyBt2->Name = L"readyBt2";
				 this->readyBt2->Size = System::Drawing::Size(75, 30);
				 this->readyBt2->TabIndex = 10;
				 this->readyBt2->Text = L"READY";
				 this->readyBt2->UseVisualStyleBackColor = false;
				 this->readyBt2->Click += gcnew System::EventHandler(this, &Form1::readyBt2_Click);
				 // 
				 // autoFall2
				 // 
				 this->autoFall2->AutoSize = true;
				 this->autoFall2->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoFall2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoFall2->Location = System::Drawing::Point(304, 210);
				 this->autoFall2->Name = L"autoFall2";
				 this->autoFall2->Size = System::Drawing::Size(76, 17);
				 this->autoFall2->TabIndex = 9;
				 this->autoFall2->Text = L"Auto Fall";
				 this->autoFall2->UseVisualStyleBackColor = false;
				 this->autoFall2->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoFall2_CheckedChanged);
				 // 
				 // flow2
				 // 
				 this->flow2->BackColor = System::Drawing::Color::PaleGreen;
				 this->flow2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->flow2->ForeColor = System::Drawing::Color::Black;
				 this->flow2->Location = System::Drawing::Point(158, 476);
				 this->flow2->Name = L"flow2";
				 this->flow2->Size = System::Drawing::Size(38, 20);
				 this->flow2->TabIndex = 8;
				 this->flow2->Text = L"0000";
				 this->flow2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->flow2->Visible = false;
				 this->flow2->Click += gcnew System::EventHandler(this, &Form1::flow2_Click);
				 // 
				 // printOnly2
				 // 
				 this->printOnly2->BackColor = System::Drawing::Color::Transparent;
				 this->printOnly2->Enabled = false;
				 this->printOnly2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->printOnly2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printOnly2->ForeColor = System::Drawing::Color::Black;
				 this->printOnly2->Location = System::Drawing::Point(310, 308);
				 this->printOnly2->Name = L"printOnly2";
				 this->printOnly2->Size = System::Drawing::Size(75, 30);
				 this->printOnly2->TabIndex = 0;
				 this->printOnly2->Text = L"PrintOnly";
				 this->printOnly2->UseVisualStyleBackColor = false;
				 this->printOnly2->Click += gcnew System::EventHandler(this, &Form1::printOnly2_Click);
				 // 
				 // printTarget2
				 // 
				 this->printTarget2->AutoSize = true;
				 this->printTarget2->BackColor = System::Drawing::Color::Gainsboro;
				 this->printTarget2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printTarget2->Location = System::Drawing::Point(304, 130);
				 this->printTarget2->Name = L"printTarget2";
				 this->printTarget2->Size = System::Drawing::Size(93, 17);
				 this->printTarget2->TabIndex = 0;
				 this->printTarget2->Text = L"Print Target";
				 this->printTarget2->UseVisualStyleBackColor = false;
				 this->printTarget2->CheckedChanged += gcnew System::EventHandler(this, &Form1::printTarget2_CheckedChanged);
				 // 
				 // tonnage2
				 // 
				 this->tonnage2->BackColor = System::Drawing::Color::PaleGreen;
				 this->tonnage2->Cursor = System::Windows::Forms::Cursors::No;
				 this->tonnage2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tonnage2->ForeColor = System::Drawing::Color::Black;
				 this->tonnage2->Location = System::Drawing::Point(206, 147);
				 this->tonnage2->Name = L"tonnage2";
				 this->tonnage2->Size = System::Drawing::Size(84, 32);
				 this->tonnage2->TabIndex = 0;
				 this->tonnage2->Text = L"1234.0";
				 this->tonnage2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->tonnage2->Click += gcnew System::EventHandler(this, &Form1::tonnage2_Click);
				 // 
				 // label9
				 // 
				 this->label9->AutoEllipsis = true;
				 this->label9->AutoSize = true;
				 this->label9->Cursor = System::Windows::Forms::Cursors::No;
				 this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label9->Location = System::Drawing::Point(148, 150);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(57, 26);
				 this->label9->TabIndex = 0;
				 this->label9->Text = L"Today\'s\r\nTonnage";
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->BackColor = System::Drawing::Color::Transparent;
				 this->label4->Cursor = System::Windows::Forms::Cursors::No;
				 this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label4->ForeColor = System::Drawing::Color::DarkGreen;
				 this->label4->Location = System::Drawing::Point(216, 88);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(37, 13);
				 this->label4->TabIndex = 0;
				 this->label4->Text = L"Done";
				 // 
				 // man2
				 // 
				 this->man2->BackColor = System::Drawing::Color::PaleGreen;
				 this->man2->Cursor = System::Windows::Forms::Cursors::No;
				 this->man2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->man2->ForeColor = System::Drawing::Color::Black;
				 this->man2->Location = System::Drawing::Point(220, 104);
				 this->man2->Name = L"man2";
				 this->man2->Size = System::Drawing::Size(70, 28);
				 this->man2->TabIndex = 0;
				 this->man2->Text = L"000";
				 this->man2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // autoBt2
				 // 
				 this->autoBt2->BackColor = System::Drawing::Color::Transparent;
				 this->autoBt2->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->autoBt2->Enabled = false;
				 this->autoBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->autoBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoBt2->ForeColor = System::Drawing::Color::DarkGreen;
				 this->autoBt2->Location = System::Drawing::Point(303, 94);
				 this->autoBt2->Name = L"autoBt2";
				 this->autoBt2->Size = System::Drawing::Size(82, 30);
				 this->autoBt2->TabIndex = 0;
				 this->autoBt2->Text = L"MANUAL";
				 this->autoBt2->UseVisualStyleBackColor = false;
				 this->autoBt2->Click += gcnew System::EventHandler(this, &Form1::autoBt2_Click);
				 // 
				 // material2
				 // 
				 this->material2->BackColor = System::Drawing::Color::Gainsboro;
				 this->material2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->material2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->material2->Location = System::Drawing::Point(68, 72);
				 this->material2->MaxLength = 8;
				 this->material2->Name = L"material2";
				 this->material2->ReadOnly = true;
				 this->material2->Size = System::Drawing::Size(92, 23);
				 this->material2->TabIndex = 3;
				 this->material2->Text = L"1234567890";
				 // 
				 // tic_num2
				 // 
				 this->tic_num2->BackColor = System::Drawing::Color::Gainsboro;
				 this->tic_num2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->tic_num2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tic_num2->Location = System::Drawing::Point(68, 100);
				 this->tic_num2->MaxLength = 8;
				 this->tic_num2->Name = L"tic_num2";
				 this->tic_num2->ReadOnly = true;
				 this->tic_num2->Size = System::Drawing::Size(72, 23);
				 this->tic_num2->TabIndex = 4;
				 this->tic_num2->TabStop = false;
				 this->tic_num2->Text = L"12345678";
				 // 
				 // target2
				 // 
				 this->target2->BackColor = System::Drawing::Color::White;
				 this->target2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->target2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->target2->Location = System::Drawing::Point(82, 156);
				 this->target2->MaxLength = 6;
				 this->target2->Name = L"target2";
				 this->target2->Size = System::Drawing::Size(50, 23);
				 this->target2->TabIndex = 6;
				 this->target2->Text = L"00.00";
				 this->target2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 // 
				 // truck2
				 // 
				 this->truck2->BackColor = System::Drawing::Color::White;
				 this->truck2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->truck2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->truck2->Location = System::Drawing::Point(68, 128);
				 this->truck2->MaxLength = 9;
				 this->truck2->Name = L"truck2";
				 this->truck2->Size = System::Drawing::Size(78, 23);
				 this->truck2->TabIndex = 5;
				 this->truck2->Text = L"012345678";
				 this->truck2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::truckNum2_MouseDoubleClick);
				 // 
				 // Job2
				 // 
				 this->Job2->BackColor = System::Drawing::Color::Gainsboro;
				 this->Job2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->Job2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->Job2->Location = System::Drawing::Point(68, 44);
				 this->Job2->MaxLength = 16;
				 this->Job2->Name = L"Job2";
				 this->Job2->ReadOnly = true;
				 this->Job2->Size = System::Drawing::Size(137, 23);
				 this->Job2->TabIndex = 2;
				 this->Job2->Text = L"0123456789abcdef";
				 // 
				 // customer2
				 // 
				 this->customer2->BackColor = System::Drawing::Color::Gainsboro;
				 this->customer2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->customer2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->customer2->Location = System::Drawing::Point(68, 16);
				 this->customer2->MaxLength = 32;
				 this->customer2->Name = L"customer2";
				 this->customer2->ReadOnly = true;
				 this->customer2->Size = System::Drawing::Size(264, 23);
				 this->customer2->TabIndex = 1;
				 this->customer2->Text = L"0123456789abcdef0123456789abcdef";
				 // 
				 // addBt2
				 // 
				 this->addBt2->BackColor = System::Drawing::Color::Transparent;
				 this->addBt2->Enabled = false;
				 this->addBt2->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->addBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->addBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->addBt2->ForeColor = System::Drawing::Color::Black;
				 this->addBt2->Location = System::Drawing::Point(310, 474);
				 this->addBt2->Name = L"addBt2";
				 this->addBt2->Size = System::Drawing::Size(75, 30);
				 this->addBt2->TabIndex = 0;
				 this->addBt2->Text = L"ADD";
				 this->addBt2->UseVisualStyleBackColor = false;
				 this->addBt2->Visible = false;
				 this->addBt2->Click += gcnew System::EventHandler(this, &Form1::addBt2_Click);
				 // 
				 // dischBt2
				 // 
				 this->dischBt2->BackColor = System::Drawing::Color::Transparent;
				 this->dischBt2->Enabled = false;
				 this->dischBt2->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dischBt2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dischBt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dischBt2->ForeColor = System::Drawing::Color::Black;
				 this->dischBt2->Location = System::Drawing::Point(226, 438);
				 this->dischBt2->Name = L"dischBt2";
				 this->dischBt2->Size = System::Drawing::Size(75, 30);
				 this->dischBt2->TabIndex = 0;
				 this->dischBt2->Text = L"DISCH";
				 this->dischBt2->UseVisualStyleBackColor = false;
				 this->dischBt2->Visible = false;
				 this->dischBt2->Click += gcnew System::EventHandler(this, &Form1::dischBt2_Click);
				 // 
				 // truckLb2
				 // 
				 this->truckLb2->AutoSize = true;
				 this->truckLb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->truckLb2->Location = System::Drawing::Point(6, 133);
				 this->truckLb2->Name = L"truckLb2";
				 this->truckLb2->Size = System::Drawing::Size(55, 13);
				 this->truckLb2->TabIndex = 0;
				 this->truckLb2->Text = L"Truck Id";
				 // 
				 // drops24
				 // 
				 this->drops24->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops24->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops24->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops24->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops24->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops24->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops24->ForeColor = System::Drawing::Color::Black;
				 this->drops24->Location = System::Drawing::Point(351, 397);
				 this->drops24->Name = L"drops24";
				 this->drops24->Size = System::Drawing::Size(32, 32);
				 this->drops24->TabIndex = 0;
				 this->drops24->Text = L"4";
				 this->drops24->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops24->UseVisualStyleBackColor = true;
				 this->drops24->Click += gcnew System::EventHandler(this, &Form1::drops24_Click);
				 // 
				 // drops23
				 // 
				 this->drops23->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops23->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops23->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops23->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops23->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops23->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops23->ForeColor = System::Drawing::Color::Black;
				 this->drops23->Location = System::Drawing::Point(315, 397);
				 this->drops23->Name = L"drops23";
				 this->drops23->Size = System::Drawing::Size(32, 32);
				 this->drops23->TabIndex = 0;
				 this->drops23->Text = L"3";
				 this->drops23->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops23->UseVisualStyleBackColor = true;
				 this->drops23->Click += gcnew System::EventHandler(this, &Form1::drops23_Click);
				 // 
				 // drops22
				 // 
				 this->drops22->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops22->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops22->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops22->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops22->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops22->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops22->ForeColor = System::Drawing::Color::Black;
				 this->drops22->Location = System::Drawing::Point(351, 362);
				 this->drops22->Name = L"drops22";
				 this->drops22->Size = System::Drawing::Size(32, 32);
				 this->drops22->TabIndex = 0;
				 this->drops22->Text = L"2";
				 this->drops22->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops22->UseVisualStyleBackColor = true;
				 this->drops22->Click += gcnew System::EventHandler(this, &Form1::drops22_Click);
				 // 
				 // drops21
				 // 
				 this->drops21->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops21->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops21->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops21->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->drops21->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops21->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops21->ForeColor = System::Drawing::Color::Black;
				 this->drops21->Location = System::Drawing::Point(315, 362);
				 this->drops21->Name = L"drops21";
				 this->drops21->Size = System::Drawing::Size(32, 32);
				 this->drops21->TabIndex = 0;
				 this->drops21->Text = L"1";
				 this->drops21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops21->UseVisualStyleBackColor = true;
				 this->drops21->Click += gcnew System::EventHandler(this, &Form1::drops21_Click);
				 // 
				 // cnt2
				 // 
				 this->cnt2->BackColor = System::Drawing::Color::Aquamarine;
				 this->cnt2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->cnt2->ForeColor = System::Drawing::Color::Black;
				 this->cnt2->Location = System::Drawing::Point(202, 476);
				 this->cnt2->Name = L"cnt2";
				 this->cnt2->Size = System::Drawing::Size(50, 20);
				 this->cnt2->TabIndex = 0;
				 this->cnt2->Text = L"012345";
				 this->cnt2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->cnt2->Visible = false;
				 // 
				 // zoom2
				 // 
				 this->zoom2->BackColor = System::Drawing::Color::Gainsboro;
				 this->zoom2->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->zoom2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->zoom2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->zoom2->ForeColor = System::Drawing::Color::Black;
				 this->zoom2->Location = System::Drawing::Point(441, 828);
				 this->zoom2->Name = L"zoom2";
				 this->zoom2->Size = System::Drawing::Size(48, 30);
				 this->zoom2->TabIndex = 29;
				 this->zoom2->Text = L"Zoom";
				 this->zoom2->UseVisualStyleBackColor = false;
				 this->zoom2->Visible = false;
				 this->zoom2->Click += gcnew System::EventHandler(this, &Form1::zoom2_Click);
				 // 
				 // DbaseLb
				 // 
				 this->DbaseLb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->DbaseLb->AutoSize = true;
				 this->DbaseLb->BackColor = System::Drawing::Color::Red;
				 this->DbaseLb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->DbaseLb->Cursor = System::Windows::Forms::Cursors::No;
				 this->DbaseLb->ForeColor = System::Drawing::Color::Black;
				 this->DbaseLb->Location = System::Drawing::Point(1062, 5);
				 this->DbaseLb->Name = L"DbaseLb";
				 this->DbaseLb->Size = System::Drawing::Size(50, 15);
				 this->DbaseLb->TabIndex = 0;
				 this->DbaseLb->Text = L"DBASE";
				 // 
				 // timer1
				 // 
				 this->timer1->SynchronizingObject = this;
				 this->timer1->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &Form1::timer1_Tick);
				 // 
				 // fileMenuItem
				 // 
				 this->fileMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->toolStripSeparator1,
						 this->printManualJobs, this->configToolStripMenuItem, this->exitMenuItem
				 });
				 this->fileMenuItem->Name = L"fileMenuItem";
				 this->fileMenuItem->Size = System::Drawing::Size(35, 20);
				 this->fileMenuItem->Text = L"File";
				 // 
				 // toolStripSeparator1
				 // 
				 this->toolStripSeparator1->Name = L"toolStripSeparator1";
				 this->toolStripSeparator1->Size = System::Drawing::Size(155, 6);
				 // 
				 // printManualJobs
				 // 
				 this->printManualJobs->Name = L"printManualJobs";
				 this->printManualJobs->Size = System::Drawing::Size(158, 22);
				 this->printManualJobs->Text = L"Print Manual Jobs";
				 this->printManualJobs->Click += gcnew System::EventHandler(this, &Form1::printManualJobs_Click);
				 // 
				 // configToolStripMenuItem
				 // 
				 this->configToolStripMenuItem->Name = L"configToolStripMenuItem";
				 this->configToolStripMenuItem->Size = System::Drawing::Size(158, 22);
				 this->configToolStripMenuItem->Text = L"Config";
				 this->configToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::configToolStripMenuItem_Click);
				 // 
				 // exitMenuItem
				 // 
				 this->exitMenuItem->Name = L"exitMenuItem";
				 this->exitMenuItem->Size = System::Drawing::Size(158, 22);
				 this->exitMenuItem->Text = L"Exit";
				 this->exitMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitMenuItem_Click);
				 // 
				 // helpMenuItem
				 // 
				 this->helpMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
					 this->aboutMenuItem,
						 this->testStripMenuItem, this->ulinkMsgToolStripMenuItem, this->exceptionsToolStripMenuItem, this->iOTestToolStripMenuItem
				 });
				 this->helpMenuItem->Name = L"helpMenuItem";
				 this->helpMenuItem->Size = System::Drawing::Size(40, 20);
				 this->helpMenuItem->Text = L"Help";
				 // 
				 // aboutMenuItem
				 // 
				 this->aboutMenuItem->Name = L"aboutMenuItem";
				 this->aboutMenuItem->Size = System::Drawing::Size(126, 22);
				 this->aboutMenuItem->Text = L"About";
				 this->aboutMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutMenuItem_Click);
				 // 
				 // testStripMenuItem
				 // 
				 this->testStripMenuItem->Name = L"testStripMenuItem";
				 this->testStripMenuItem->Size = System::Drawing::Size(126, 22);
				 this->testStripMenuItem->Text = L"Test";
				 this->testStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::testToolStripMenuItem_Click);
				 // 
				 // ulinkMsgToolStripMenuItem
				 // 
				 this->ulinkMsgToolStripMenuItem->Name = L"ulinkMsgToolStripMenuItem";
				 this->ulinkMsgToolStripMenuItem->Size = System::Drawing::Size(126, 22);
				 this->ulinkMsgToolStripMenuItem->Text = L"Ulink Msg";
				 this->ulinkMsgToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ulinkMsgToolStripMenuItem_Click);
				 // 
				 // exceptionsToolStripMenuItem
				 // 
				 this->exceptionsToolStripMenuItem->Name = L"exceptionsToolStripMenuItem";
				 this->exceptionsToolStripMenuItem->Size = System::Drawing::Size(126, 22);
				 this->exceptionsToolStripMenuItem->Text = L"Exceptions";
				 this->exceptionsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exceptionsToolStripMenuItem_Click);
				 // 
				 // iOTestToolStripMenuItem
				 // 
				 this->iOTestToolStripMenuItem->Name = L"iOTestToolStripMenuItem";
				 this->iOTestToolStripMenuItem->Size = System::Drawing::Size(126, 22);
				 this->iOTestToolStripMenuItem->Text = L"IO Test";
				 this->iOTestToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::iOTestToolStripMenuItem_Click);
				 // 
				 // menu
				 // 
				 this->menu->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
				 this->menu->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F));
				 this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
					 this->fileMenuItem, this->inventoryMenuItem,
						 this->trucksToolStripMenuItem, this->reprintToolStripMenuItem, this->helpMenuItem
				 });
				 this->menu->Location = System::Drawing::Point(0, 0);
				 this->menu->Name = L"menu";
				 this->menu->Size = System::Drawing::Size(1701, 24);
				 this->menu->TabIndex = 0;
				 this->menu->Text = L"menuStrip1";
				 // 
				 // inventoryMenuItem
				 // 
				 this->inventoryMenuItem->Name = L"inventoryMenuItem";
				 this->inventoryMenuItem->Size = System::Drawing::Size(67, 20);
				 this->inventoryMenuItem->Text = L"Inventory";
				 this->inventoryMenuItem->Click += gcnew System::EventHandler(this, &Form1::inventoryMenuItem_Click);
				 // 
				 // trucksToolStripMenuItem
				 // 
				 this->trucksToolStripMenuItem->Name = L"trucksToolStripMenuItem";
				 this->trucksToolStripMenuItem->Size = System::Drawing::Size(50, 20);
				 this->trucksToolStripMenuItem->Text = L"Trucks";
				 this->trucksToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::trucksToolStripMenuItem_Click);
				 // 
				 // reprintToolStripMenuItem
				 // 
				 this->reprintToolStripMenuItem->Name = L"reprintToolStripMenuItem";
				 this->reprintToolStripMenuItem->Size = System::Drawing::Size(54, 20);
				 this->reprintToolStripMenuItem->Text = L"Reprint";
				 this->reprintToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::reprintToolStripMenuItem_Click);
				 // 
				 // printerLb1
				 // 
				 this->printerLb1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->printerLb1->AutoSize = true;
				 this->printerLb1->BackColor = System::Drawing::Color::Red;
				 this->printerLb1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->printerLb1->Cursor = System::Windows::Forms::Cursors::No;
				 this->printerLb1->ForeColor = System::Drawing::Color::Black;
				 this->printerLb1->Location = System::Drawing::Point(1220, 5);
				 this->printerLb1->Name = L"printerLb1";
				 this->printerLb1->Size = System::Drawing::Size(54, 15);
				 this->printerLb1->TabIndex = 0;
				 this->printerLb1->Text = L"PRINT1";
				 // 
				 // versionLb
				 // 
				 this->versionLb->AutoSize = true;
				 this->versionLb->BackColor = System::Drawing::Color::White;
				 this->versionLb->Cursor = System::Windows::Forms::Cursors::No;
				 this->versionLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->versionLb->ForeColor = System::Drawing::Color::RoyalBlue;
				 this->versionLb->Location = System::Drawing::Point(392, 3);
				 this->versionLb->Name = L"versionLb";
				 this->versionLb->Size = System::Drawing::Size(53, 17);
				 this->versionLb->TabIndex = 0;
				 this->versionLb->Text = L"DEMO";
				 // 
				 // dbaseBadLb
				 // 
				 this->dbaseBadLb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->dbaseBadLb->BackColor = System::Drawing::Color::White;
				 this->dbaseBadLb->Cursor = System::Windows::Forms::Cursors::No;
				 this->dbaseBadLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dbaseBadLb->ForeColor = System::Drawing::Color::Red;
				 this->dbaseBadLb->Location = System::Drawing::Point(1020, 4);
				 this->dbaseBadLb->Name = L"dbaseBadLb";
				 this->dbaseBadLb->Size = System::Drawing::Size(35, 17);
				 this->dbaseBadLb->TabIndex = 0;
				 this->dbaseBadLb->Text = L"0";
				 this->dbaseBadLb->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // dataGridJob
				 // 
				 this->dataGridJob->AllowUserToAddRows = false;
				 this->dataGridJob->AllowUserToDeleteRows = false;
				 this->dataGridJob->AutoGenerateColumns = false;
				 this->dataGridJob->BackgroundColor = System::Drawing::Color::Gainsboro;
				 this->dataGridJob->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->dataGridJob->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
					 this->stTime, this->Column1,
						 this->nSilo, this->nTicketDataGridViewTextBoxColumn, this->stTruck, this->stMaterial, this->stCustomer, this->fLoad
				 });
				 this->dataGridJob->DataSource = this->jobBindingSource;
				 this->dataGridJob->Location = System::Drawing::Point(334, 618);
				 this->dataGridJob->MultiSelect = false;
				 this->dataGridJob->Name = L"dataGridJob";
				 this->dataGridJob->ReadOnly = true;
				 this->dataGridJob->RowHeadersWidth = 30;
				 this->dataGridJob->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
				 this->dataGridJob->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->dataGridJob->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
				 this->dataGridJob->Size = System::Drawing::Size(800, 242);
				 this->dataGridJob->TabIndex = 32;
				 this->dataGridJob->Visible = false;
				 this->dataGridJob->CellMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &Form1::dataGridJob_RowHeaderMouseDoubleClick);
				 this->dataGridJob->ColumnHeaderMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &Form1::dataGridJob_ColumnHeaderMouseClick);
				 // 
				 // stTime
				 // 
				 this->stTime->DataPropertyName = L"stTime";
				 dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->stTime->DefaultCellStyle = dataGridViewCellStyle4;
				 this->stTime->HeaderText = L"Time Sent";
				 this->stTime->Name = L"stTime";
				 this->stTime->ReadOnly = true;
				 this->stTime->Resizable = System::Windows::Forms::DataGridViewTriState::False;
				 this->stTime->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
				 // 
				 // Column1
				 // 
				 this->Column1->DataPropertyName = L"nPlant";
				 dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->Column1->DefaultCellStyle = dataGridViewCellStyle5;
				 this->Column1->HeaderText = L"Plant";
				 this->Column1->Name = L"Column1";
				 this->Column1->ReadOnly = true;
				 this->Column1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
				 this->Column1->Width = 60;
				 // 
				 // nSilo
				 // 
				 this->nSilo->DataPropertyName = L"nSilo";
				 dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->nSilo->DefaultCellStyle = dataGridViewCellStyle6;
				 this->nSilo->HeaderText = L"Silo";
				 this->nSilo->Name = L"nSilo";
				 this->nSilo->ReadOnly = true;
				 this->nSilo->Resizable = System::Windows::Forms::DataGridViewTriState::False;
				 this->nSilo->Width = 50;
				 // 
				 // nTicketDataGridViewTextBoxColumn
				 // 
				 this->nTicketDataGridViewTextBoxColumn->DataPropertyName = L"nTicket";
				 dataGridViewCellStyle7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->nTicketDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle7;
				 this->nTicketDataGridViewTextBoxColumn->HeaderText = L"Ticket #";
				 this->nTicketDataGridViewTextBoxColumn->Name = L"nTicketDataGridViewTextBoxColumn";
				 this->nTicketDataGridViewTextBoxColumn->ReadOnly = true;
				 this->nTicketDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
				 this->nTicketDataGridViewTextBoxColumn->Width = 80;
				 // 
				 // stTruck
				 // 
				 this->stTruck->DataPropertyName = L"stTruck";
				 this->stTruck->HeaderText = L"Truck";
				 this->stTruck->Name = L"stTruck";
				 this->stTruck->ReadOnly = true;
				 this->stTruck->Width = 80;
				 // 
				 // stMaterial
				 // 
				 this->stMaterial->DataPropertyName = L"stMaterial";
				 this->stMaterial->HeaderText = L"Material";
				 this->stMaterial->Name = L"stMaterial";
				 this->stMaterial->ReadOnly = true;
				 // 
				 // stCustomer
				 // 
				 this->stCustomer->DataPropertyName = L"stCustomer";
				 dataGridViewCellStyle8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->stCustomer->DefaultCellStyle = dataGridViewCellStyle8;
				 this->stCustomer->HeaderText = L"Customer";
				 this->stCustomer->Name = L"stCustomer";
				 this->stCustomer->ReadOnly = true;
				 this->stCustomer->Resizable = System::Windows::Forms::DataGridViewTriState::False;
				 this->stCustomer->Width = 240;
				 // 
				 // fLoad
				 // 
				 this->fLoad->DataPropertyName = L"fLoad";
				 dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
				 dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 dataGridViewCellStyle9->Format = L"n2";
				 this->fLoad->DefaultCellStyle = dataGridViewCellStyle9;
				 this->fLoad->HeaderText = L"Load";
				 this->fLoad->Name = L"fLoad";
				 this->fLoad->ReadOnly = true;
				 this->fLoad->Resizable = System::Windows::Forms::DataGridViewTriState::False;
				 this->fLoad->Width = 60;
				 // 
				 // jobBindingSource
				 // 
				 this->jobBindingSource->DataSource = As::Job::typeid;
				 // 
				 // optoErr
				 // 
				 this->optoErr->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->optoErr->BackColor = System::Drawing::Color::White;
				 this->optoErr->Cursor = System::Windows::Forms::Cursors::No;
				 this->optoErr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->optoErr->ForeColor = System::Drawing::Color::Red;
				 this->optoErr->Location = System::Drawing::Point(982, 4);
				 this->optoErr->Name = L"optoErr";
				 this->optoErr->Size = System::Drawing::Size(35, 17);
				 this->optoErr->TabIndex = 36;
				 this->optoErr->Text = L"0";
				 this->optoErr->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->optoErr->Visible = false;
				 // 
				 // printerLb2
				 // 
				 this->printerLb2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->printerLb2->AutoSize = true;
				 this->printerLb2->BackColor = System::Drawing::Color::Red;
				 this->printerLb2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->printerLb2->Cursor = System::Windows::Forms::Cursors::No;
				 this->printerLb2->ForeColor = System::Drawing::Color::Black;
				 this->printerLb2->Location = System::Drawing::Point(1280, 5);
				 this->printerLb2->Name = L"printerLb2";
				 this->printerLb2->Size = System::Drawing::Size(54, 15);
				 this->printerLb2->TabIndex = 40;
				 this->printerLb2->Text = L"PRINT2";
				 // 
				 // printerLb3
				 // 
				 this->printerLb3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->printerLb3->AutoSize = true;
				 this->printerLb3->BackColor = System::Drawing::Color::Red;
				 this->printerLb3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->printerLb3->Cursor = System::Windows::Forms::Cursors::No;
				 this->printerLb3->ForeColor = System::Drawing::Color::Black;
				 this->printerLb3->Location = System::Drawing::Point(1340, 5);
				 this->printerLb3->Name = L"printerLb3";
				 this->printerLb3->Size = System::Drawing::Size(54, 15);
				 this->printerLb3->TabIndex = 45;
				 this->printerLb3->Text = L"PRINT3";
				 // 
				 // pictureSplash
				 // 
				 this->pictureSplash->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->pictureSplash->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureSplash.Image")));
				 this->pictureSplash->Location = System::Drawing::Point(415, 183);
				 this->pictureSplash->Name = L"pictureSplash";
				 this->pictureSplash->Size = System::Drawing::Size(798, 475);
				 this->pictureSplash->TabIndex = 46;
				 this->pictureSplash->TabStop = false;
				 this->pictureSplash->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
				 // 
				 // groupBox4
				 // 
				 this->groupBox4->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->groupBox4->Controls->Add(this->remoteLb);
				 this->groupBox4->Controls->Add(this->resetBt4);
				 this->groupBox4->Controls->Add(this->laneD2ndCB);
				 this->groupBox4->Controls->Add(this->copyLb4);
				 this->groupBox4->Controls->Add(this->numCopy4);
				 this->groupBox4->Controls->Add(this->prod12Lb);
				 this->groupBox4->Controls->Add(this->prod11Lb);
				 this->groupBox4->Controls->Add(this->prod10Lb);
				 this->groupBox4->Controls->Add(this->lane4StatLB);
				 this->groupBox4->Controls->Add(this->zoom4);
				 this->groupBox4->Controls->Add(this->lite4);
				 this->groupBox4->Controls->Add(this->webBrowser4);
				 this->groupBox4->Controls->Add(this->safe12);
				 this->groupBox4->Controls->Add(this->safe11);
				 this->groupBox4->Controls->Add(this->safe10);
				 this->groupBox4->Controls->Add(this->laneDCb1);
				 this->groupBox4->Controls->Add(this->laneDCb2);
				 this->groupBox4->Controls->Add(this->taxExempt4);
				 this->groupBox4->Controls->Add(this->groupBoxD);
				 this->groupBox4->Controls->Add(this->pictureBox4);
				 this->groupBox4->Controls->Add(this->label15);
				 this->groupBox4->Controls->Add(this->plant4);
				 this->groupBox4->Controls->Add(this->adapt4);
				 this->groupBox4->Controls->Add(this->all4);
				 this->groupBox4->Controls->Add(this->autoDisch4);
				 this->groupBox4->Controls->Add(this->silo4);
				 this->groupBox4->Controls->Add(this->fill43);
				 this->groupBox4->Controls->Add(this->fill42);
				 this->groupBox4->Controls->Add(this->fill4);
				 this->groupBox4->Controls->Add(this->truckBar4);
				 this->groupBox4->Controls->Add(this->scaleBar4);
				 this->groupBox4->Controls->Add(this->siloBar43);
				 this->groupBox4->Controls->Add(this->siloBar42);
				 this->groupBox4->Controls->Add(this->siloBar4);
				 this->groupBox4->Controls->Add(this->jog4);
				 this->groupBox4->Controls->Add(this->readyBt4);
				 this->groupBox4->Controls->Add(this->autoFall4);
				 this->groupBox4->Controls->Add(this->flow4);
				 this->groupBox4->Controls->Add(this->printOnly4);
				 this->groupBox4->Controls->Add(this->printTarget4);
				 this->groupBox4->Controls->Add(this->tonnage4);
				 this->groupBox4->Controls->Add(this->label23);
				 this->groupBox4->Controls->Add(this->label24);
				 this->groupBox4->Controls->Add(this->man4);
				 this->groupBox4->Controls->Add(this->autoBt4);
				 this->groupBox4->Controls->Add(this->material4);
				 this->groupBox4->Controls->Add(this->tic_num4);
				 this->groupBox4->Controls->Add(this->target4);
				 this->groupBox4->Controls->Add(this->truck4);
				 this->groupBox4->Controls->Add(this->Job4);
				 this->groupBox4->Controls->Add(this->customer4);
				 this->groupBox4->Controls->Add(this->addBt4);
				 this->groupBox4->Controls->Add(this->dischBt4);
				 this->groupBox4->Controls->Add(this->truckLb4);
				 this->groupBox4->Controls->Add(this->drops44);
				 this->groupBox4->Controls->Add(this->drops43);
				 this->groupBox4->Controls->Add(this->drops42);
				 this->groupBox4->Controls->Add(this->drops41);
				 this->groupBox4->Controls->Add(this->JobLb4);
				 this->groupBox4->Controls->Add(this->cnt4);
				 this->groupBox4->Controls->Add(this->ticLb4);
				 this->groupBox4->Controls->Add(this->truckPic4);
				 this->groupBox4->Controls->Add(this->ticketNum4);
				 this->groupBox4->Controls->Add(this->label31);
				 this->groupBox4->Controls->Add(this->targetLb4);
				 this->groupBox4->Controls->Add(this->matLb4);
				 this->groupBox4->Controls->Add(this->nextBt4);
				 this->groupBox4->Controls->Add(this->dropsLb4);
				 this->groupBox4->Controls->Add(this->scale4);
				 this->groupBox4->Controls->Add(this->custLb4);
				 this->groupBox4->Controls->Add(this->pauseBt4);
				 this->groupBox4->Controls->Add(this->stopBt4);
				 this->groupBox4->Controls->Add(this->dropBt4);
				 this->groupBox4->Cursor = System::Windows::Forms::Cursors::Default;
				 this->groupBox4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->groupBox4->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->groupBox4->Location = System::Drawing::Point(1284, 27);
				 this->groupBox4->Name = L"groupBox4";
				 this->groupBox4->Size = System::Drawing::Size(400, 840);
				 this->groupBox4->TabIndex = 47;
				 this->groupBox4->TabStop = false;
				 this->groupBox4->Text = L"Lane R";
				 this->groupBox4->Enter += gcnew System::EventHandler(this, &Form1::groupBox4_Enter);
				 // 
				 // remoteLb
				 // 
				 this->remoteLb->AutoSize = true;
				 this->remoteLb->BackColor = System::Drawing::Color::DarkGray;
				 this->remoteLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->remoteLb->ForeColor = System::Drawing::Color::Red;
				 this->remoteLb->Location = System::Drawing::Point(102, 301);
				 this->remoteLb->Name = L"remoteLb";
				 this->remoteLb->Size = System::Drawing::Size(205, 25);
				 this->remoteLb->TabIndex = 63;
				 this->remoteLb->Text = L"LOAD REMOTELY";
				 this->remoteLb->Visible = false;
				 // 
				 // resetBt4
				 // 
				 this->resetBt4->BackColor = System::Drawing::Color::Red;
				 this->resetBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->resetBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->resetBt4->ForeColor = System::Drawing::Color::Black;
				 this->resetBt4->Location = System::Drawing::Point(307, 94);
				 this->resetBt4->Name = L"resetBt4";
				 this->resetBt4->Size = System::Drawing::Size(75, 30);
				 this->resetBt4->TabIndex = 62;
				 this->resetBt4->Text = L"RESET";
				 this->resetBt4->UseVisualStyleBackColor = false;
				 this->resetBt4->Click += gcnew System::EventHandler(this, &Form1::resetBt4_Click);
				 // 
				 // laneD2ndCB
				 // 
				 this->laneD2ndCB->AutoSize = true;
				 this->laneD2ndCB->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneD2ndCB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneD2ndCB->Location = System::Drawing::Point(304, 232);
				 this->laneD2ndCB->Name = L"laneD2ndCB";
				 this->laneD2ndCB->Size = System::Drawing::Size(79, 17);
				 this->laneD2ndCB->TabIndex = 61;
				 this->laneD2ndCB->Text = L"2nd Copy";
				 this->laneD2ndCB->UseVisualStyleBackColor = false;
				 // 
				 // copyLb4
				 // 
				 this->copyLb4->AutoSize = true;
				 this->copyLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->copyLb4->Location = System::Drawing::Point(338, 202);
				 this->copyLb4->Name = L"copyLb4";
				 this->copyLb4->Size = System::Drawing::Size(49, 13);
				 this->copyLb4->TabIndex = 60;
				 this->copyLb4->Text = L"Tickets";
				 // 
				 // numCopy4
				 // 
				 this->numCopy4->Location = System::Drawing::Point(304, 197);
				 this->numCopy4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
				 this->numCopy4->Name = L"numCopy4";
				 this->numCopy4->Size = System::Drawing::Size(30, 23);
				 this->numCopy4->TabIndex = 59;
				 this->numCopy4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numCopy4->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown3_ValueChanged);
				 // 
				 // prod12Lb
				 // 
				 this->prod12Lb->AutoSize = true;
				 this->prod12Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod12Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod12Lb->ForeColor = System::Drawing::Color::White;
				 this->prod12Lb->Location = System::Drawing::Point(213, 225);
				 this->prod12Lb->Name = L"prod12Lb";
				 this->prod12Lb->Size = System::Drawing::Size(81, 13);
				 this->prod12Lb->TabIndex = 56;
				 this->prod12Lb->Text = L"ABCDABCDA";
				 this->prod12Lb->Visible = false;
				 // 
				 // prod11Lb
				 // 
				 this->prod11Lb->AutoSize = true;
				 this->prod11Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod11Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod11Lb->ForeColor = System::Drawing::Color::White;
				 this->prod11Lb->Location = System::Drawing::Point(113, 225);
				 this->prod11Lb->Name = L"prod11Lb";
				 this->prod11Lb->Size = System::Drawing::Size(81, 13);
				 this->prod11Lb->TabIndex = 56;
				 this->prod11Lb->Text = L"ABCDABCDA";
				 this->prod11Lb->Visible = false;
				 // 
				 // prod10Lb
				 // 
				 this->prod10Lb->AutoSize = true;
				 this->prod10Lb->BackColor = System::Drawing::SystemColors::ControlDarkDark;
				 this->prod10Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->prod10Lb->ForeColor = System::Drawing::Color::White;
				 this->prod10Lb->Location = System::Drawing::Point(14, 225);
				 this->prod10Lb->Name = L"prod10Lb";
				 this->prod10Lb->Size = System::Drawing::Size(81, 13);
				 this->prod10Lb->TabIndex = 56;
				 this->prod10Lb->Text = L"ABCDABCDA";
				 this->prod10Lb->Visible = false;
				 // 
				 // lane4StatLB
				 // 
				 this->lane4StatLB->BackColor = System::Drawing::Color::Gainsboro;
				 this->lane4StatLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->lane4StatLB->ForeColor = System::Drawing::Color::Black;
				 this->lane4StatLB->Location = System::Drawing::Point(70, 1);
				 this->lane4StatLB->Name = L"lane4StatLB";
				 this->lane4StatLB->Size = System::Drawing::Size(50, 13);
				 this->lane4StatLB->TabIndex = 55;
				 this->lane4StatLB->Text = L"S-00";
				 this->lane4StatLB->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->lane4StatLB->Visible = false;
				 // 
				 // zoom4
				 // 
				 this->zoom4->BackColor = System::Drawing::Color::Gainsboro;
				 this->zoom4->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->zoom4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->zoom4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->zoom4->ForeColor = System::Drawing::Color::Black;
				 this->zoom4->Location = System::Drawing::Point(0, 801);
				 this->zoom4->Name = L"zoom4";
				 this->zoom4->Size = System::Drawing::Size(48, 30);
				 this->zoom4->TabIndex = 54;
				 this->zoom4->Text = L"Zoom";
				 this->zoom4->UseVisualStyleBackColor = false;
				 this->zoom4->Visible = false;
				 this->zoom4->Click += gcnew System::EventHandler(this, &Form1::zoom4_Click);
				 // 
				 // lite4
				 // 
				 this->lite4->BackColor = System::Drawing::Color::Transparent;
				 this->lite4->Cursor = System::Windows::Forms::Cursors::No;
				 this->lite4->Enabled = false;
				 this->lite4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->lite4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"lite4.Image")));
				 this->lite4->Location = System::Drawing::Point(6, 592);
				 this->lite4->Name = L"lite4";
				 this->lite4->Size = System::Drawing::Size(48, 48);
				 this->lite4->TabIndex = 33;
				 // 
				 // webBrowser4
				 // 
				 this->webBrowser4->AllowWebBrowserDrop = false;
				 this->webBrowser4->IsWebBrowserContextMenuEnabled = false;
				 this->webBrowser4->Location = System::Drawing::Point(6, 592);
				 this->webBrowser4->MaximumSize = System::Drawing::Size(800, 600);
				 this->webBrowser4->MinimumSize = System::Drawing::Size(20, 20);
				 this->webBrowser4->Name = L"webBrowser4";
				 this->webBrowser4->ScriptErrorsSuppressed = true;
				 this->webBrowser4->Size = System::Drawing::Size(389, 240);
				 this->webBrowser4->TabIndex = 0;
				 this->webBrowser4->TabStop = false;
				 this->webBrowser4->Visible = false;
				 this->webBrowser4->WebBrowserShortcutsEnabled = false;
				 this->webBrowser4->DocumentCompleted += gcnew System::Windows::Forms::WebBrowserDocumentCompletedEventHandler(this, &Form1::webBrowser4_DocumentCompleted);
				 // 
				 // safe12
				 // 
				 this->safe12->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe12.Image")));
				 this->safe12->Location = System::Drawing::Point(250, 190);
				 this->safe12->Name = L"safe12";
				 this->safe12->Size = System::Drawing::Size(24, 24);
				 this->safe12->TabIndex = 53;
				 this->safe12->Visible = false;
				 // 
				 // safe11
				 // 
				 this->safe11->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe11.Image")));
				 this->safe11->Location = System::Drawing::Point(150, 190);
				 this->safe11->Name = L"safe11";
				 this->safe11->Size = System::Drawing::Size(24, 24);
				 this->safe11->TabIndex = 52;
				 this->safe11->Visible = false;
				 // 
				 // safe10
				 // 
				 this->safe10->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"safe10.Image")));
				 this->safe10->Location = System::Drawing::Point(50, 190);
				 this->safe10->Name = L"safe10";
				 this->safe10->Size = System::Drawing::Size(24, 24);
				 this->safe10->TabIndex = 51;
				 this->safe10->Visible = false;
				 // 
				 // laneDCb1
				 // 
				 this->laneDCb1->AutoSize = true;
				 this->laneDCb1->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneDCb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneDCb1->Location = System::Drawing::Point(303, 170);
				 this->laneDCb1->Name = L"laneDCb1";
				 this->laneDCb1->Size = System::Drawing::Size(41, 17);
				 this->laneDCb1->TabIndex = 50;
				 this->laneDCb1->Text = L"P1";
				 this->laneDCb1->UseVisualStyleBackColor = false;
				 // 
				 // laneDCb2
				 // 
				 this->laneDCb2->AutoSize = true;
				 this->laneDCb2->BackColor = System::Drawing::Color::Gainsboro;
				 this->laneDCb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->laneDCb2->Location = System::Drawing::Point(351, 170);
				 this->laneDCb2->Name = L"laneDCb2";
				 this->laneDCb2->Size = System::Drawing::Size(41, 17);
				 this->laneDCb2->TabIndex = 49;
				 this->laneDCb2->Text = L"P2";
				 this->laneDCb2->UseVisualStyleBackColor = false;
				 // 
				 // taxExempt4
				 // 
				 this->taxExempt4->AutoSize = true;
				 this->taxExempt4->BackColor = System::Drawing::Color::Gainsboro;
				 this->taxExempt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->taxExempt4->Location = System::Drawing::Point(304, 150);
				 this->taxExempt4->Name = L"taxExempt4";
				 this->taxExempt4->Size = System::Drawing::Size(92, 17);
				 this->taxExempt4->TabIndex = 47;
				 this->taxExempt4->Text = L"Tax Exempt";
				 this->taxExempt4->UseVisualStyleBackColor = false;
				 // 
				 // groupBoxD
				 // 
				 this->groupBoxD->BackColor = System::Drawing::Color::Silver;
				 this->groupBoxD->Controls->Add(this->okD);
				 this->groupBoxD->Controls->Add(this->grossD);
				 this->groupBoxD->Controls->Add(this->tareD);
				 this->groupBoxD->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->groupBoxD->ForeColor = System::Drawing::Color::DarkRed;
				 this->groupBoxD->Location = System::Drawing::Point(87, 306);
				 this->groupBoxD->Name = L"groupBoxD";
				 this->groupBoxD->Size = System::Drawing::Size(208, 60);
				 this->groupBoxD->TabIndex = 46;
				 this->groupBoxD->TabStop = false;
				 this->groupBoxD->Text = L"Tare       Gross";
				 this->groupBoxD->Visible = false;
				 // 
				 // okD
				 // 
				 this->okD->BackColor = System::Drawing::Color::PaleGreen;
				 this->okD->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->okD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->okD->Location = System::Drawing::Point(147, 22);
				 this->okD->Name = L"okD";
				 this->okD->Size = System::Drawing::Size(50, 26);
				 this->okD->TabIndex = 2;
				 this->okD->Text = L"OK";
				 this->okD->UseVisualStyleBackColor = false;
				 this->okD->Click += gcnew System::EventHandler(this, &Form1::okD_Click);
				 // 
				 // grossD
				 // 
				 this->grossD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->grossD->Location = System::Drawing::Point(74, 22);
				 this->grossD->Name = L"grossD";
				 this->grossD->Size = System::Drawing::Size(60, 26);
				 this->grossD->TabIndex = 1;
				 this->grossD->Text = L"xx.xx";
				 this->grossD->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 // 
				 // tareD
				 // 
				 this->tareD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tareD->Location = System::Drawing::Point(6, 22);
				 this->tareD->Name = L"tareD";
				 this->tareD->Size = System::Drawing::Size(61, 26);
				 this->tareD->TabIndex = 0;
				 this->tareD->Text = L"xx.xx";
				 this->tareD->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
				 // 
				 // pictureBox4
				 // 
				 this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox4.Image")));
				 this->pictureBox4->Location = System::Drawing::Point(66, 591);
				 this->pictureBox4->Name = L"pictureBox4";
				 this->pictureBox4->Size = System::Drawing::Size(320, 240);
				 this->pictureBox4->TabIndex = 37;
				 this->pictureBox4->TabStop = false;
				 // 
				 // label15
				 // 
				 this->label15->AutoSize = true;
				 this->label15->BackColor = System::Drawing::Color::Transparent;
				 this->label15->Cursor = System::Windows::Forms::Cursors::No;
				 this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label15->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->label15->Location = System::Drawing::Point(142, 104);
				 this->label15->Name = L"label15";
				 this->label15->Size = System::Drawing::Size(36, 13);
				 this->label15->TabIndex = 34;
				 this->label15->Text = L"Plant";
				 this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 // 
				 // plant4
				 // 
				 this->plant4->BackColor = System::Drawing::Color::Gainsboro;
				 this->plant4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->plant4->Cursor = System::Windows::Forms::Cursors::No;
				 this->plant4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->plant4->ForeColor = System::Drawing::Color::Black;
				 this->plant4->Location = System::Drawing::Point(178, 100);
				 this->plant4->Name = L"plant4";
				 this->plant4->Size = System::Drawing::Size(30, 24);
				 this->plant4->TabIndex = 33;
				 this->plant4->Text = L"00";
				 this->plant4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // adapt4
				 // 
				 this->adapt4->AutoSize = true;
				 this->adapt4->BackColor = System::Drawing::Color::Gainsboro;
				 this->adapt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->adapt4->Location = System::Drawing::Point(304, 230);
				 this->adapt4->Name = L"adapt4";
				 this->adapt4->Size = System::Drawing::Size(76, 17);
				 this->adapt4->TabIndex = 32;
				 this->adapt4->Text = L"Adaptive";
				 this->adapt4->UseVisualStyleBackColor = false;
				 this->adapt4->CheckedChanged += gcnew System::EventHandler(this, &Form1::adapt4_CheckedChanged);
				 // 
				 // all4
				 // 
				 this->all4->BackColor = System::Drawing::Color::Transparent;
				 this->all4->Enabled = false;
				 this->all4->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->all4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->all4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->all4->ForeColor = System::Drawing::Color::Black;
				 this->all4->Location = System::Drawing::Point(339, 16);
				 this->all4->Name = L"all4";
				 this->all4->Size = System::Drawing::Size(46, 30);
				 this->all4->TabIndex = 31;
				 this->all4->Text = L"ALL";
				 this->all4->UseVisualStyleBackColor = false;
				 this->all4->Click += gcnew System::EventHandler(this, &Form1::all4_Click);
				 // 
				 // autoDisch4
				 // 
				 this->autoDisch4->AutoSize = true;
				 this->autoDisch4->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoDisch4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoDisch4->Location = System::Drawing::Point(304, 190);
				 this->autoDisch4->Name = L"autoDisch4";
				 this->autoDisch4->Size = System::Drawing::Size(88, 17);
				 this->autoDisch4->TabIndex = 29;
				 this->autoDisch4->Text = L"Auto Disch";
				 this->autoDisch4->UseVisualStyleBackColor = false;
				 this->autoDisch4->Visible = false;
				 this->autoDisch4->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoDisch4_CheckedChanged);
				 // 
				 // silo4
				 // 
				 this->silo4->BackColor = System::Drawing::Color::Gainsboro;
				 this->silo4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->silo4->ForeColor = System::Drawing::Color::Black;
				 this->silo4->Location = System::Drawing::Point(116, 476);
				 this->silo4->Name = L"silo4";
				 this->silo4->Size = System::Drawing::Size(38, 20);
				 this->silo4->TabIndex = 28;
				 this->silo4->Text = L"0000";
				 this->silo4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->silo4->Visible = false;
				 // 
				 // fill43
				 // 
				 this->fill43->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill43.Image")));
				 this->fill43->Location = System::Drawing::Point(270, 190);
				 this->fill43->Name = L"fill43";
				 this->fill43->Size = System::Drawing::Size(24, 24);
				 this->fill43->TabIndex = 27;
				 this->fill43->Visible = false;
				 // 
				 // fill42
				 // 
				 this->fill42->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill42.Image")));
				 this->fill42->Location = System::Drawing::Point(170, 190);
				 this->fill42->Name = L"fill42";
				 this->fill42->Size = System::Drawing::Size(24, 24);
				 this->fill42->TabIndex = 26;
				 this->fill42->Visible = false;
				 // 
				 // fill4
				 // 
				 this->fill4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fill4.Image")));
				 this->fill4->Location = System::Drawing::Point(70, 190);
				 this->fill4->Name = L"fill4";
				 this->fill4->Size = System::Drawing::Size(24, 24);
				 this->fill4->TabIndex = 22;
				 this->fill4->Visible = false;
				 // 
				 // truckBar4
				 // 
				 this->truckBar4->BarColor = System::Drawing::Color::MistyRose;
				 this->truckBar4->BorderColor = System::Drawing::Color::Black;
				 this->truckBar4->FillStyle = As::BarCtl::FillStyles::Dashed;
				 this->truckBar4->Flow = 0;
				 this->truckBar4->Location = System::Drawing::Point(12, 496);
				 this->truckBar4->Maximum = 100;
				 this->truckBar4->Name = L"truckBar4";
				 this->truckBar4->Pct = 35;
				 this->truckBar4->ScaleInLB = false;
				 this->truckBar4->Separators = 0;
				 this->truckBar4->Size = System::Drawing::Size(80, 28);
				 this->truckBar4->TabIndex = 21;
				 this->truckBar4->Target = 9;
				 this->truckBar4->Text = L"barCtl1";
				 this->truckBar4->Value = 50;
				 this->truckBar4->Vertical = false;
				 // 
				 // scaleBar4
				 // 
				 this->scaleBar4->BackColor = System::Drawing::Color::LightGray;
				 this->scaleBar4->BarColor = System::Drawing::Color::Gainsboro;
				 this->scaleBar4->BorderColor = System::Drawing::Color::Black;
				 this->scaleBar4->Flow = 0;
				 this->scaleBar4->Idle = false;
				 this->scaleBar4->Label = 0;
				 this->scaleBar4->Location = System::Drawing::Point(12, 436);
				 this->scaleBar4->Maximum = 100;
				 this->scaleBar4->Metric = false;
				 this->scaleBar4->Name = L"scaleBar4";
				 this->scaleBar4->Open = false;
				 this->scaleBar4->ScaleInLB = false;
				 this->scaleBar4->Size = System::Drawing::Size(100, 52);
				 this->scaleBar4->TabIndex = 20;
				 this->scaleBar4->Target = 0;
				 this->scaleBar4->Topl = 0;
				 this->scaleBar4->Value = 0;
				 // 
				 // siloBar43
				 // 
				 this->siloBar43->Add = false;
				 this->siloBar43->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar43->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar43->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar43->Count = 0;
				 this->siloBar43->Delay = false;
				 this->siloBar43->DisableInv = false;
				 this->siloBar43->Empty = false;
				 this->siloBar43->Idle = true;
				 this->siloBar43->Inventory = 100;
				 this->siloBar43->Location = System::Drawing::Point(210, 196);
				 this->siloBar43->Maximum = 100;
				 this->siloBar43->Metric = false;
				 this->siloBar43->Name = L"siloBar43";
				 this->siloBar43->Number = 12;
				 this->siloBar43->Open = false;
				 this->siloBar43->ScaleInLB = false;
				 this->siloBar43->Separators = 4;
				 this->siloBar43->Size = System::Drawing::Size(88, 230);
				 this->siloBar43->TabIndex = 19;
				 this->siloBar43->Target = 0;
				 this->siloBar43->Text = L"Silo12";
				 this->siloBar43->Tol = false;
				 this->siloBar43->ValMan = 0;
				 this->siloBar43->Value = 0;
				 this->siloBar43->Visible = false;
				 this->siloBar43->DoubleClick += gcnew System::EventHandler(this, &Form1::flow12_Click);
				 this->siloBar43->Click += gcnew System::EventHandler(this, &Form1::siloBar43_Click);
				 // 
				 // siloBar42
				 // 
				 this->siloBar42->Add = false;
				 this->siloBar42->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar42->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar42->BorderColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar42->Count = 0;
				 this->siloBar42->Delay = false;
				 this->siloBar42->DisableInv = false;
				 this->siloBar42->Empty = false;
				 this->siloBar42->Idle = true;
				 this->siloBar42->Inventory = 100;
				 this->siloBar42->Location = System::Drawing::Point(110, 196);
				 this->siloBar42->Maximum = 100;
				 this->siloBar42->Metric = false;
				 this->siloBar42->Name = L"siloBar42";
				 this->siloBar42->Number = 11;
				 this->siloBar42->Open = false;
				 this->siloBar42->ScaleInLB = false;
				 this->siloBar42->Separators = 4;
				 this->siloBar42->Size = System::Drawing::Size(88, 230);
				 this->siloBar42->TabIndex = 18;
				 this->siloBar42->Target = 0;
				 this->siloBar42->Text = L"Silo11";
				 this->siloBar42->Tol = false;
				 this->siloBar42->ValMan = 0;
				 this->siloBar42->Value = 0;
				 this->siloBar42->Visible = false;
				 this->siloBar42->DoubleClick += gcnew System::EventHandler(this, &Form1::flow11_Click);
				 this->siloBar42->Click += gcnew System::EventHandler(this, &Form1::siloBar42_Click);
				 // 
				 // siloBar4
				 // 
				 this->siloBar4->Add = false;
				 this->siloBar4->BackColor = System::Drawing::Color::Gainsboro;
				 this->siloBar4->BarColor = System::Drawing::Color::WhiteSmoke;
				 this->siloBar4->BorderColor = System::Drawing::Color::Black;
				 this->siloBar4->Count = 0;
				 this->siloBar4->Delay = false;
				 this->siloBar4->DisableInv = false;
				 this->siloBar4->Empty = false;
				 this->siloBar4->Idle = false;
				 this->siloBar4->Inventory = 100;
				 this->siloBar4->Location = System::Drawing::Point(10, 196);
				 this->siloBar4->Maximum = 100;
				 this->siloBar4->Metric = false;
				 this->siloBar4->Name = L"siloBar4";
				 this->siloBar4->Number = 10;
				 this->siloBar4->Open = false;
				 this->siloBar4->ScaleInLB = false;
				 this->siloBar4->Separators = 4;
				 this->siloBar4->Size = System::Drawing::Size(88, 230);
				 this->siloBar4->TabIndex = 17;
				 this->siloBar4->Target = 11;
				 this->siloBar4->Text = L"Silo10";
				 this->siloBar4->Tol = false;
				 this->siloBar4->ValMan = 0;
				 this->siloBar4->Value = 30;
				 this->siloBar4->DoubleClick += gcnew System::EventHandler(this, &Form1::flow10_Click);
				 this->siloBar4->Click += gcnew System::EventHandler(this, &Form1::siloBar4_Click);
				 // 
				 // jog4
				 // 
				 this->jog4->AutoSize = true;
				 this->jog4->BackColor = System::Drawing::Color::Gainsboro;
				 this->jog4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->jog4->Location = System::Drawing::Point(304, 250);
				 this->jog4->Name = L"jog4";
				 this->jog4->Size = System::Drawing::Size(46, 17);
				 this->jog4->TabIndex = 11;
				 this->jog4->Text = L"Jog";
				 this->jog4->UseVisualStyleBackColor = false;
				 this->jog4->CheckedChanged += gcnew System::EventHandler(this, &Form1::jog4_CheckedChanged);
				 // 
				 // readyBt4
				 // 
				 this->readyBt4->BackColor = System::Drawing::Color::Transparent;
				 this->readyBt4->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->readyBt4->Enabled = false;
				 this->readyBt4->FlatAppearance->CheckedBackColor = System::Drawing::Color::Blue;
				 this->readyBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->readyBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->readyBt4->ForeColor = System::Drawing::Color::Black;
				 this->readyBt4->Location = System::Drawing::Point(310, 270);
				 this->readyBt4->Name = L"readyBt4";
				 this->readyBt4->Size = System::Drawing::Size(75, 30);
				 this->readyBt4->TabIndex = 10;
				 this->readyBt4->Text = L"READY";
				 this->readyBt4->UseVisualStyleBackColor = false;
				 this->readyBt4->Click += gcnew System::EventHandler(this, &Form1::readyBt4_Click);
				 // 
				 // autoFall4
				 // 
				 this->autoFall4->AutoSize = true;
				 this->autoFall4->BackColor = System::Drawing::Color::Gainsboro;
				 this->autoFall4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoFall4->Location = System::Drawing::Point(304, 210);
				 this->autoFall4->Name = L"autoFall4";
				 this->autoFall4->Size = System::Drawing::Size(76, 17);
				 this->autoFall4->TabIndex = 9;
				 this->autoFall4->Text = L"Auto Fall";
				 this->autoFall4->UseVisualStyleBackColor = false;
				 this->autoFall4->CheckedChanged += gcnew System::EventHandler(this, &Form1::autoFall4_CheckedChanged);
				 // 
				 // flow4
				 // 
				 this->flow4->BackColor = System::Drawing::Color::PaleGreen;
				 this->flow4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->flow4->ForeColor = System::Drawing::Color::Black;
				 this->flow4->Location = System::Drawing::Point(157, 476);
				 this->flow4->Name = L"flow4";
				 this->flow4->Size = System::Drawing::Size(38, 20);
				 this->flow4->TabIndex = 8;
				 this->flow4->Text = L"0000";
				 this->flow4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->flow4->Visible = false;
				 this->flow4->Click += gcnew System::EventHandler(this, &Form1::flow4_Click);
				 // 
				 // printOnly4
				 // 
				 this->printOnly4->BackColor = System::Drawing::Color::Transparent;
				 this->printOnly4->Cursor = System::Windows::Forms::Cursors::Default;
				 this->printOnly4->Enabled = false;
				 this->printOnly4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->printOnly4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printOnly4->ForeColor = System::Drawing::Color::Black;
				 this->printOnly4->Location = System::Drawing::Point(310, 308);
				 this->printOnly4->Name = L"printOnly4";
				 this->printOnly4->Size = System::Drawing::Size(75, 30);
				 this->printOnly4->TabIndex = 0;
				 this->printOnly4->Text = L"PrintOnly";
				 this->printOnly4->UseVisualStyleBackColor = false;
				 this->printOnly4->Click += gcnew System::EventHandler(this, &Form1::printOnly4_Click);
				 // 
				 // printTarget4
				 // 
				 this->printTarget4->AutoSize = true;
				 this->printTarget4->BackColor = System::Drawing::Color::Gainsboro;
				 this->printTarget4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->printTarget4->Location = System::Drawing::Point(304, 130);
				 this->printTarget4->Name = L"printTarget4";
				 this->printTarget4->Size = System::Drawing::Size(93, 17);
				 this->printTarget4->TabIndex = 0;
				 this->printTarget4->Text = L"Print Target";
				 this->printTarget4->UseVisualStyleBackColor = false;
				 this->printTarget4->CheckedChanged += gcnew System::EventHandler(this, &Form1::printTarget4_CheckedChanged);
				 // 
				 // tonnage4
				 // 
				 this->tonnage4->BackColor = System::Drawing::Color::MistyRose;
				 this->tonnage4->Cursor = System::Windows::Forms::Cursors::No;
				 this->tonnage4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tonnage4->ForeColor = System::Drawing::Color::Black;
				 this->tonnage4->Location = System::Drawing::Point(206, 147);
				 this->tonnage4->Name = L"tonnage4";
				 this->tonnage4->Size = System::Drawing::Size(84, 32);
				 this->tonnage4->TabIndex = 0;
				 this->tonnage4->Text = L"1234.0";
				 this->tonnage4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->tonnage4->Click += gcnew System::EventHandler(this, &Form1::tonnage4_Click);
				 // 
				 // label23
				 // 
				 this->label23->AutoEllipsis = true;
				 this->label23->AutoSize = true;
				 this->label23->Cursor = System::Windows::Forms::Cursors::No;
				 this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label23->Location = System::Drawing::Point(148, 150);
				 this->label23->Name = L"label23";
				 this->label23->Size = System::Drawing::Size(57, 26);
				 this->label23->TabIndex = 0;
				 this->label23->Text = L"Today\'s\r\nTonnage";
				 // 
				 // label24
				 // 
				 this->label24->AutoSize = true;
				 this->label24->BackColor = System::Drawing::Color::Transparent;
				 this->label24->Cursor = System::Windows::Forms::Cursors::No;
				 this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label24->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->label24->Location = System::Drawing::Point(216, 88);
				 this->label24->Name = L"label24";
				 this->label24->Size = System::Drawing::Size(37, 13);
				 this->label24->TabIndex = 0;
				 this->label24->Text = L"Done";
				 // 
				 // man4
				 // 
				 this->man4->BackColor = System::Drawing::Color::MistyRose;
				 this->man4->Cursor = System::Windows::Forms::Cursors::No;
				 this->man4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->man4->ForeColor = System::Drawing::Color::Black;
				 this->man4->Location = System::Drawing::Point(220, 104);
				 this->man4->Name = L"man4";
				 this->man4->Size = System::Drawing::Size(70, 28);
				 this->man4->TabIndex = 0;
				 this->man4->Text = L"000";
				 this->man4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // autoBt4
				 // 
				 this->autoBt4->BackColor = System::Drawing::Color::Transparent;
				 this->autoBt4->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->autoBt4->Enabled = false;
				 this->autoBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->autoBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->autoBt4->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->autoBt4->Location = System::Drawing::Point(303, 94);
				 this->autoBt4->Name = L"autoBt4";
				 this->autoBt4->Size = System::Drawing::Size(82, 30);
				 this->autoBt4->TabIndex = 0;
				 this->autoBt4->Text = L"MANUAL";
				 this->autoBt4->UseVisualStyleBackColor = false;
				 this->autoBt4->Click += gcnew System::EventHandler(this, &Form1::autoBt4_Click);
				 // 
				 // material4
				 // 
				 this->material4->BackColor = System::Drawing::Color::Gainsboro;
				 this->material4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->material4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->material4->Location = System::Drawing::Point(68, 72);
				 this->material4->MaxLength = 10;
				 this->material4->Name = L"material4";
				 this->material4->ReadOnly = true;
				 this->material4->Size = System::Drawing::Size(92, 23);
				 this->material4->TabIndex = 3;
				 this->material4->Text = L"1234567890";
				 // 
				 // tic_num4
				 // 
				 this->tic_num4->BackColor = System::Drawing::Color::Gainsboro;
				 this->tic_num4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->tic_num4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->tic_num4->Location = System::Drawing::Point(68, 100);
				 this->tic_num4->MaxLength = 8;
				 this->tic_num4->Name = L"tic_num4";
				 this->tic_num4->ReadOnly = true;
				 this->tic_num4->Size = System::Drawing::Size(72, 23);
				 this->tic_num4->TabIndex = 4;
				 this->tic_num4->TabStop = false;
				 this->tic_num4->Text = L"12345678";
				 // 
				 // target4
				 // 
				 this->target4->BackColor = System::Drawing::Color::White;
				 this->target4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->target4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->target4->Location = System::Drawing::Point(82, 156);
				 this->target4->MaxLength = 6;
				 this->target4->Name = L"target4";
				 this->target4->Size = System::Drawing::Size(62, 23);
				 this->target4->TabIndex = 6;
				 this->target4->Text = L"00.00";
				 this->target4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->target4->TextChanged += gcnew System::EventHandler(this, &Form1::target4_TextChanged);
				 // 
				 // truck4
				 // 
				 this->truck4->BackColor = System::Drawing::Color::White;
				 this->truck4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->truck4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->truck4->Location = System::Drawing::Point(68, 128);
				 this->truck4->MaxLength = 9;
				 this->truck4->Name = L"truck4";
				 this->truck4->Size = System::Drawing::Size(78, 23);
				 this->truck4->TabIndex = 5;
				 this->truck4->Text = L"012345678";
				 this->truck4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::truckNum4_MouseDoubleClick);
				 // 
				 // Job4
				 // 
				 this->Job4->BackColor = System::Drawing::Color::Gainsboro;
				 this->Job4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->Job4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->Job4->Location = System::Drawing::Point(68, 44);
				 this->Job4->MaxLength = 16;
				 this->Job4->Name = L"Job4";
				 this->Job4->ReadOnly = true;
				 this->Job4->Size = System::Drawing::Size(136, 23);
				 this->Job4->TabIndex = 2;
				 this->Job4->Text = L"0123456789abcdef";
				 // 
				 // customer4
				 // 
				 this->customer4->BackColor = System::Drawing::Color::Gainsboro;
				 this->customer4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->customer4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->customer4->Location = System::Drawing::Point(68, 16);
				 this->customer4->MaxLength = 32;
				 this->customer4->Name = L"customer4";
				 this->customer4->ReadOnly = true;
				 this->customer4->Size = System::Drawing::Size(264, 23);
				 this->customer4->TabIndex = 1;
				 this->customer4->Text = L"0123456789abcdef0123456789abcdef";
				 // 
				 // addBt4
				 // 
				 this->addBt4->BackColor = System::Drawing::Color::Transparent;
				 this->addBt4->Enabled = false;
				 this->addBt4->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->addBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->addBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->addBt4->ForeColor = System::Drawing::Color::Black;
				 this->addBt4->Location = System::Drawing::Point(310, 474);
				 this->addBt4->Name = L"addBt4";
				 this->addBt4->Size = System::Drawing::Size(75, 30);
				 this->addBt4->TabIndex = 0;
				 this->addBt4->Text = L"ADD";
				 this->addBt4->UseVisualStyleBackColor = false;
				 this->addBt4->Visible = false;
				 this->addBt4->Click += gcnew System::EventHandler(this, &Form1::addBt4_Click);
				 // 
				 // dischBt4
				 // 
				 this->dischBt4->BackColor = System::Drawing::Color::Transparent;
				 this->dischBt4->Enabled = false;
				 this->dischBt4->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dischBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dischBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dischBt4->ForeColor = System::Drawing::Color::Black;
				 this->dischBt4->Location = System::Drawing::Point(226, 438);
				 this->dischBt4->Name = L"dischBt4";
				 this->dischBt4->Size = System::Drawing::Size(75, 30);
				 this->dischBt4->TabIndex = 0;
				 this->dischBt4->Text = L"DISCH";
				 this->dischBt4->UseVisualStyleBackColor = false;
				 this->dischBt4->Visible = false;
				 this->dischBt4->Click += gcnew System::EventHandler(this, &Form1::dischBt4_Click);
				 // 
				 // truckLb4
				 // 
				 this->truckLb4->AutoSize = true;
				 this->truckLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->truckLb4->Location = System::Drawing::Point(6, 133);
				 this->truckLb4->Name = L"truckLb4";
				 this->truckLb4->Size = System::Drawing::Size(55, 13);
				 this->truckLb4->TabIndex = 0;
				 this->truckLb4->Text = L"Truck Id";
				 // 
				 // drops44
				 // 
				 this->drops44->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops44->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops44->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops44->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops44->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops44->ForeColor = System::Drawing::Color::Black;
				 this->drops44->Location = System::Drawing::Point(351, 397);
				 this->drops44->Name = L"drops44";
				 this->drops44->Size = System::Drawing::Size(32, 32);
				 this->drops44->TabIndex = 0;
				 this->drops44->Text = L"4";
				 this->drops44->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops44->UseVisualStyleBackColor = true;
				 this->drops44->Click += gcnew System::EventHandler(this, &Form1::drops44_Click);
				 this->drops44->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
				 // 
				 // drops43
				 // 
				 this->drops43->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops43->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops43->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops43->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops43->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops43->ForeColor = System::Drawing::Color::Black;
				 this->drops43->Location = System::Drawing::Point(315, 397);
				 this->drops43->Name = L"drops43";
				 this->drops43->Size = System::Drawing::Size(32, 32);
				 this->drops43->TabIndex = 0;
				 this->drops43->Text = L"3";
				 this->drops43->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops43->UseVisualStyleBackColor = true;
				 this->drops43->Click += gcnew System::EventHandler(this, &Form1::drops43_Click);
				 // 
				 // drops42
				 // 
				 this->drops42->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops42->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops42->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops42->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops42->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops42->ForeColor = System::Drawing::Color::Black;
				 this->drops42->Location = System::Drawing::Point(351, 362);
				 this->drops42->Name = L"drops42";
				 this->drops42->Size = System::Drawing::Size(32, 32);
				 this->drops42->TabIndex = 0;
				 this->drops42->Text = L"2";
				 this->drops42->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops42->UseVisualStyleBackColor = true;
				 this->drops42->Click += gcnew System::EventHandler(this, &Form1::drops42_Click);
				 // 
				 // drops41
				 // 
				 this->drops41->Appearance = System::Windows::Forms::Appearance::Button;
				 this->drops41->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->drops41->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops41->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
				 this->drops41->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->drops41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->drops41->ForeColor = System::Drawing::Color::Black;
				 this->drops41->Location = System::Drawing::Point(315, 362);
				 this->drops41->Name = L"drops41";
				 this->drops41->Size = System::Drawing::Size(32, 32);
				 this->drops41->TabIndex = 0;
				 this->drops41->Text = L"1";
				 this->drops41->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->drops41->UseVisualStyleBackColor = true;
				 this->drops41->Click += gcnew System::EventHandler(this, &Form1::drops41_Click);
				 // 
				 // JobLb4
				 // 
				 this->JobLb4->AutoSize = true;
				 this->JobLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->JobLb4->Location = System::Drawing::Point(6, 48);
				 this->JobLb4->Name = L"JobLb4";
				 this->JobLb4->Size = System::Drawing::Size(27, 13);
				 this->JobLb4->TabIndex = 0;
				 this->JobLb4->Text = L"Job";
				 // 
				 // cnt4
				 // 
				 this->cnt4->BackColor = System::Drawing::Color::Aquamarine;
				 this->cnt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->cnt4->ForeColor = System::Drawing::Color::Black;
				 this->cnt4->Location = System::Drawing::Point(199, 476);
				 this->cnt4->Name = L"cnt4";
				 this->cnt4->Size = System::Drawing::Size(50, 20);
				 this->cnt4->TabIndex = 0;
				 this->cnt4->Text = L"012345";
				 this->cnt4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->cnt4->Visible = false;
				 // 
				 // ticLb4
				 // 
				 this->ticLb4->AutoSize = true;
				 this->ticLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticLb4->Location = System::Drawing::Point(6, 104);
				 this->ticLb4->Name = L"ticLb4";
				 this->ticLb4->Size = System::Drawing::Size(55, 13);
				 this->ticLb4->TabIndex = 0;
				 this->ticLb4->Text = L"Ticket #";
				 // 
				 // truckPic4
				 // 
				 this->truckPic4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"truckPic4.BackgroundImage")));
				 this->truckPic4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->truckPic4->Location = System::Drawing::Point(23, 528);
				 this->truckPic4->Name = L"truckPic4";
				 this->truckPic4->Size = System::Drawing::Size(78, 57);
				 this->truckPic4->TabIndex = 0;
				 this->truckPic4->TabStop = false;
				 // 
				 // ticketNum4
				 // 
				 this->ticketNum4->BackColor = System::Drawing::Color::MistyRose;
				 this->ticketNum4->Cursor = System::Windows::Forms::Cursors::No;
				 this->ticketNum4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ticketNum4->ForeColor = System::Drawing::Color::Black;
				 this->ticketNum4->Location = System::Drawing::Point(249, 55);
				 this->ticketNum4->Name = L"ticketNum4";
				 this->ticketNum4->Size = System::Drawing::Size(40, 28);
				 this->ticketNum4->TabIndex = 0;
				 this->ticketNum4->Text = L"000";
				 this->ticketNum4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 // 
				 // label31
				 // 
				 this->label31->AutoSize = true;
				 this->label31->BackColor = System::Drawing::Color::Transparent;
				 this->label31->Cursor = System::Windows::Forms::Cursors::No;
				 this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label31->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->label31->Location = System::Drawing::Point(215, 59);
				 this->label31->Name = L"label31";
				 this->label31->Size = System::Drawing::Size(32, 13);
				 this->label31->TabIndex = 0;
				 this->label31->Text = L"New";
				 this->label31->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 // 
				 // targetLb4
				 // 
				 this->targetLb4->AutoSize = true;
				 this->targetLb4->BackColor = System::Drawing::Color::Transparent;
				 this->targetLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->targetLb4->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->targetLb4->Location = System::Drawing::Point(6, 160);
				 this->targetLb4->Name = L"targetLb4";
				 this->targetLb4->Size = System::Drawing::Size(44, 13);
				 this->targetLb4->TabIndex = 0;
				 this->targetLb4->Text = L"Target";
				 // 
				 // matLb4
				 // 
				 this->matLb4->AutoSize = true;
				 this->matLb4->BackColor = System::Drawing::Color::Transparent;
				 this->matLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->matLb4->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->matLb4->Location = System::Drawing::Point(6, 76);
				 this->matLb4->Name = L"matLb4";
				 this->matLb4->Size = System::Drawing::Size(52, 13);
				 this->matLb4->TabIndex = 0;
				 this->matLb4->Text = L"Material";
				 // 
				 // nextBt4
				 // 
				 this->nextBt4->BackColor = System::Drawing::Color::Transparent;
				 this->nextBt4->Cursor = System::Windows::Forms::Cursors::Arrow;
				 this->nextBt4->Enabled = false;
				 this->nextBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->nextBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->nextBt4->ForeColor = System::Drawing::Color::Black;
				 this->nextBt4->Location = System::Drawing::Point(303, 55);
				 this->nextBt4->Name = L"nextBt4";
				 this->nextBt4->Size = System::Drawing::Size(82, 30);
				 this->nextBt4->TabIndex = 0;
				 this->nextBt4->Text = L"NEXT ";
				 this->nextBt4->UseVisualStyleBackColor = false;
				 this->nextBt4->Click += gcnew System::EventHandler(this, &Form1::nextBt4_Click);
				 // 
				 // dropsLb4
				 // 
				 this->dropsLb4->AutoSize = true;
				 this->dropsLb4->BackColor = System::Drawing::Color::Transparent;
				 this->dropsLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropsLb4->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->dropsLb4->Location = System::Drawing::Point(325, 344);
				 this->dropsLb4->Name = L"dropsLb4";
				 this->dropsLb4->Size = System::Drawing::Size(40, 13);
				 this->dropsLb4->TabIndex = 0;
				 this->dropsLb4->Text = L"Drops";
				 // 
				 // scale4
				 // 
				 this->scale4->BackColor = System::Drawing::Color::PaleGreen;
				 this->scale4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->scale4->ForeColor = System::Drawing::Color::Black;
				 this->scale4->Location = System::Drawing::Point(116, 440);
				 this->scale4->Name = L"scale4";
				 this->scale4->Size = System::Drawing::Size(100, 20);
				 this->scale4->TabIndex = 0;
				 this->scale4->Text = L"0123456789012";
				 this->scale4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
				 this->scale4->Visible = false;
				 // 
				 // custLb4
				 // 
				 this->custLb4->AutoSize = true;
				 this->custLb4->BackColor = System::Drawing::Color::Transparent;
				 this->custLb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->custLb4->ForeColor = System::Drawing::Color::MidnightBlue;
				 this->custLb4->Location = System::Drawing::Point(6, 23);
				 this->custLb4->Name = L"custLb4";
				 this->custLb4->Size = System::Drawing::Size(59, 13);
				 this->custLb4->TabIndex = 0;
				 this->custLb4->Text = L"Customer";
				 // 
				 // pauseBt4
				 // 
				 this->pauseBt4->BackColor = System::Drawing::Color::Gold;
				 this->pauseBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->pauseBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->pauseBt4->ForeColor = System::Drawing::Color::Black;
				 this->pauseBt4->Location = System::Drawing::Point(310, 511);
				 this->pauseBt4->Name = L"pauseBt4";
				 this->pauseBt4->Size = System::Drawing::Size(75, 30);
				 this->pauseBt4->TabIndex = 0;
				 this->pauseBt4->Text = L"HOLD";
				 this->pauseBt4->UseVisualStyleBackColor = false;
				 this->pauseBt4->Click += gcnew System::EventHandler(this, &Form1::pause4_Click);
				 // 
				 // stopBt4
				 // 
				 this->stopBt4->BackColor = System::Drawing::Color::Red;
				 this->stopBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->stopBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->stopBt4->ForeColor = System::Drawing::Color::Black;
				 this->stopBt4->Location = System::Drawing::Point(310, 547);
				 this->stopBt4->Name = L"stopBt4";
				 this->stopBt4->Size = System::Drawing::Size(75, 30);
				 this->stopBt4->TabIndex = 0;
				 this->stopBt4->Text = L"ABORT";
				 this->stopBt4->UseVisualStyleBackColor = false;
				 this->stopBt4->Click += gcnew System::EventHandler(this, &Form1::stopBt4_Click);
				 // 
				 // dropBt4
				 // 
				 this->dropBt4->BackColor = System::Drawing::Color::Transparent;
				 this->dropBt4->Enabled = false;
				 this->dropBt4->FlatAppearance->CheckedBackColor = System::Drawing::Color::Lime;
				 this->dropBt4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->dropBt4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dropBt4->ForeColor = System::Drawing::Color::Black;
				 this->dropBt4->Location = System::Drawing::Point(310, 438);
				 this->dropBt4->Name = L"dropBt4";
				 this->dropBt4->Size = System::Drawing::Size(75, 30);
				 this->dropBt4->TabIndex = 0;
				 this->dropBt4->Text = L"DROP";
				 this->dropBt4->UseVisualStyleBackColor = false;
				 this->dropBt4->Click += gcnew System::EventHandler(this, &Form1::dropBt4_Click);
				 // 
				 // printerLb4
				 // 
				 this->printerLb4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->printerLb4->AutoSize = true;
				 this->printerLb4->BackColor = System::Drawing::Color::Red;
				 this->printerLb4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->printerLb4->Cursor = System::Windows::Forms::Cursors::No;
				 this->printerLb4->ForeColor = System::Drawing::Color::Black;
				 this->printerLb4->Location = System::Drawing::Point(1400, 5);
				 this->printerLb4->Name = L"printerLb4";
				 this->printerLb4->Size = System::Drawing::Size(54, 15);
				 this->printerLb4->TabIndex = 48;
				 this->printerLb4->Text = L"PRINT4";
				 // 
				 // matrixPDMLb
				 // 
				 this->matrixPDMLb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->matrixPDMLb->AutoSize = true;
				 this->matrixPDMLb->BackColor = System::Drawing::Color::Red;
				 this->matrixPDMLb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->matrixPDMLb->Cursor = System::Windows::Forms::Cursors::No;
				 this->matrixPDMLb->ForeColor = System::Drawing::Color::Black;
				 this->matrixPDMLb->Location = System::Drawing::Point(905, 5);
				 this->matrixPDMLb->Name = L"matrixPDMLb";
				 this->matrixPDMLb->Size = System::Drawing::Size(70, 15);
				 this->matrixPDMLb->TabIndex = 49;
				 this->matrixPDMLb->Text = L"MatrixPDM";
				 // 
				 // copyLane1Lb
				 // 
				 this->copyLane1Lb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->copyLane1Lb->AutoSize = true;
				 this->copyLane1Lb->BackColor = System::Drawing::Color::Red;
				 this->copyLane1Lb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->copyLane1Lb->Cursor = System::Windows::Forms::Cursors::No;
				 this->copyLane1Lb->ForeColor = System::Drawing::Color::Black;
				 this->copyLane1Lb->Location = System::Drawing::Point(1460, 5);
				 this->copyLane1Lb->Name = L"copyLane1Lb";
				 this->copyLane1Lb->Size = System::Drawing::Size(45, 15);
				 this->copyLane1Lb->TabIndex = 50;
				 this->copyLane1Lb->Text = L"2ndP1";
				 // 
				 // copyLane2Lb
				 // 
				 this->copyLane2Lb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->copyLane2Lb->AutoSize = true;
				 this->copyLane2Lb->BackColor = System::Drawing::Color::Red;
				 this->copyLane2Lb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->copyLane2Lb->Cursor = System::Windows::Forms::Cursors::No;
				 this->copyLane2Lb->ForeColor = System::Drawing::Color::Black;
				 this->copyLane2Lb->Location = System::Drawing::Point(1511, 5);
				 this->copyLane2Lb->Name = L"copyLane2Lb";
				 this->copyLane2Lb->Size = System::Drawing::Size(45, 15);
				 this->copyLane2Lb->TabIndex = 51;
				 this->copyLane2Lb->Text = L"2ndP2";
				 // 
				 // copyLane4Lb
				 // 
				 this->copyLane4Lb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->copyLane4Lb->AutoSize = true;
				 this->copyLane4Lb->BackColor = System::Drawing::Color::Red;
				 this->copyLane4Lb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->copyLane4Lb->Cursor = System::Windows::Forms::Cursors::No;
				 this->copyLane4Lb->ForeColor = System::Drawing::Color::Black;
				 this->copyLane4Lb->Location = System::Drawing::Point(1612, 5);
				 this->copyLane4Lb->Name = L"copyLane4Lb";
				 this->copyLane4Lb->Size = System::Drawing::Size(45, 15);
				 this->copyLane4Lb->TabIndex = 53;
				 this->copyLane4Lb->Text = L"2ndP4";
				 // 
				 // copyLane3Lb
				 // 
				 this->copyLane3Lb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->copyLane3Lb->AutoSize = true;
				 this->copyLane3Lb->BackColor = System::Drawing::Color::Red;
				 this->copyLane3Lb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->copyLane3Lb->Cursor = System::Windows::Forms::Cursors::No;
				 this->copyLane3Lb->ForeColor = System::Drawing::Color::Black;
				 this->copyLane3Lb->Location = System::Drawing::Point(1562, 5);
				 this->copyLane3Lb->Name = L"copyLane3Lb";
				 this->copyLane3Lb->Size = System::Drawing::Size(45, 15);
				 this->copyLane3Lb->TabIndex = 52;
				 this->copyLane3Lb->Text = L"2ndP3";
				 // 
				 // remLoginBt
				 // 
				 this->remLoginBt->Enabled = false;
				 this->remLoginBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->remLoginBt->Location = System::Drawing::Point(599, 585);
				 this->remLoginBt->Name = L"remLoginBt";
				 this->remLoginBt->Size = System::Drawing::Size(129, 38);
				 this->remLoginBt->TabIndex = 54;
				 this->remLoginBt->Text = L"Remote Login";
				 this->remLoginBt->UseVisualStyleBackColor = true;
				 this->remLoginBt->Visible = false;
				 this->remLoginBt->Click += gcnew System::EventHandler(this, &Form1::remLoginBt_Click);
				 // 
				 // loginErrLb
				 // 
				 this->loginErrLb->AutoSize = true;
				 this->loginErrLb->BackColor = System::Drawing::Color::Yellow;
				 this->loginErrLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->loginErrLb->Location = System::Drawing::Point(599, 630);
				 this->loginErrLb->Name = L"loginErrLb";
				 this->loginErrLb->Size = System::Drawing::Size(130, 20);
				 this->loginErrLb->TabIndex = 55;
				 this->loginErrLb->Text = L"Connecting......";
				 this->loginErrLb->Visible = false;
				 // 
				 // clinkLb
				 // 
				 this->clinkLb->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->clinkLb->AutoSize = true;
				 this->clinkLb->BackColor = System::Drawing::Color::Red;
				 this->clinkLb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->clinkLb->Cursor = System::Windows::Forms::Cursors::No;
				 this->clinkLb->ForeColor = System::Drawing::Color::Black;
				 this->clinkLb->Location = System::Drawing::Point(722, 5);
				 this->clinkLb->Name = L"clinkLb";
				 this->clinkLb->Size = System::Drawing::Size(68, 15);
				 this->clinkLb->TabIndex = 56;
				 this->clinkLb->Text = L"RemoteOk";
				 this->clinkLb->Visible = false;
				 // 
				 // ipAddressLb
				 // 
				 this->ipAddressLb->BackColor = System::Drawing::Color::Gray;
				 this->ipAddressLb->Enabled = false;
				 this->ipAddressLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ipAddressLb->Location = System::Drawing::Point(594, 562);
				 this->ipAddressLb->Name = L"ipAddressLb";
				 this->ipAddressLb->Size = System::Drawing::Size(140, 15);
				 this->ipAddressLb->TabIndex = 57;
				 this->ipAddressLb->Text = L"192.192.192.192:7010";
				 this->ipAddressLb->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->ipAddressLb->Visible = false;
				 // 
				 // oldBindingSource
				 // 
				 this->oldBindingSource->DataSource = As::Job::typeid;
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(7, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
				 this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
				 this->ClientSize = System::Drawing::Size(1701, 872);
				 this->Controls->Add(this->ipAddressLb);
				 this->Controls->Add(this->clinkLb);
				 this->Controls->Add(this->loginErrLb);
				 this->Controls->Add(this->remLoginBt);
				 this->Controls->Add(this->pictureSplash);
				 this->Controls->Add(this->dataGridJob);
				 this->Controls->Add(this->copyLane4Lb);
				 this->Controls->Add(this->copyLane3Lb);
				 this->Controls->Add(this->copyLane2Lb);
				 this->Controls->Add(this->copyLane1Lb);
				 this->Controls->Add(this->matrixPDMLb);
				 this->Controls->Add(this->printerLb4);
				 this->Controls->Add(this->groupBox4);
				 this->Controls->Add(this->dataGridTruck);
				 this->Controls->Add(this->printerLb3);
				 this->Controls->Add(this->printerLb2);
				 this->Controls->Add(this->optoErr);
				 this->Controls->Add(this->zoom3);
				 this->Controls->Add(this->zoom2);
				 this->Controls->Add(this->zoom1);
				 this->Controls->Add(this->dbaseBadLb);
				 this->Controls->Add(this->versionLb);
				 this->Controls->Add(this->printerLb1);
				 this->Controls->Add(this->DbaseLb);
				 this->Controls->Add(this->optoLb);
				 this->Controls->Add(this->ulinkLb);
				 this->Controls->Add(this->menu);
				 this->Controls->Add(this->groupBox3);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->groupBox2);
				 this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				 this->MainMenuStrip = this->menu;
				 this->Name = L"Form1";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"KEYSTONE Silo Load Out  ";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->groupBox3->ResumeLayout(false);
				 this->groupBox3->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy3))->EndInit();
				 this->groupBoxC->ResumeLayout(false);
				 this->groupBoxC->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic3))->EndInit();
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->groupBoxA->ResumeLayout(false);
				 this->groupBoxA->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic1))->EndInit();
				 this->gBoxLine1->ResumeLayout(false);
				 this->gBoxLine1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridTruck))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckBindingSource))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic2))->EndInit();
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy2))->EndInit();
				 this->groupBoxB->ResumeLayout(false);
				 this->groupBoxB->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer1))->EndInit();
				 this->menu->ResumeLayout(false);
				 this->menu->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridJob))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->jobBindingSource))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureSplash))->EndInit();
				 this->groupBox4->ResumeLayout(false);
				 this->groupBox4->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCopy4))->EndInit();
				 this->groupBoxD->ResumeLayout(false);
				 this->groupBoxD->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckPic4))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->oldBindingSource))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

#pragma region STATE1
			 //-------------------------------------------------------------------------
	private: void idleBar(As::BinCtl^ siloBar)
	{
		siloBar->Idle = true;
		siloBar->Target = 0;
		siloBar->BarColor = COL_IDLE;
	}

			 //-------------------------------------------------------------------------
	private: void zeroBar(As::BinCtl^ siloBar)
	{
		siloBar->Target = 0;
		siloBar->BarColor = COL_IDLE;
	}

			 //-------------------------------------------------------------------------
	private: System::Void setState1(STATE eNew)
	{
		switch (psIni->sLog1.eState = eNew)
		{
		case S_IDLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLEAR_A;
					zeroBar(siloBar12);
					zeroBar(siloBar13);
				}
				else
					psIni->nWpoints &= ~O_CLEARAA;
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[0].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[1].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[2].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[0].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[1].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[2].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[0].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[1].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[2].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[0].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[1].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[2].uHoldO;		// turn off Hold
				zeroBar(siloBar12);
				zeroBar(siloBar13);
			}

			zeroBar(siloBar1);
			scaleBar1->Target = 0;
			bTruck1 = false;

			// clear display
			customer1->Text = nullptr;
			Job1->Text = nullptr;
			material1->Text = nullptr;
			tic_num1->Text = nullptr;
			truck1->Text = nullptr;
			target1->Text = nullptr;

			truck1->BackColor = COL_W;
			target1->BackColor = COL_W;

			// setup buttons
			all1->Enabled = true;
			all1->BackColor = COL_LSB;
			nextBt1->Enabled = true;
			nextBt1->BackColor = COL_LSB;
			autoBt1->Enabled = !psIni->bDisableManual;		//DC 3.2.0 true;
			autoBt1->BackColor = COL_WS;

			printOnly1->Enabled = false;
			printOnly1->BackColor = COL_TRANS;
			readyBt1->Enabled = false;
			readyBt1->BackColor = COL_TRANS;

			printTarget1->Checked = false;
			taxExempt1->Checked = false;

			drops11->Checked = false;
			drops12->Checked = false;
			drops13->Checked = false;
			drops14->Checked = false;

			dropBt1->Enabled = false;
			dropBt1->BackColor = COL_TRANS;

			addBt1->Enabled = false;
			addBt1->BackColor = COL_TRANS;

			dischBt1->Enabled = false;
			dischBt1->BackColor = COL_TRANS;
			dischBt1->Visible = !psIni->sInv.bAutoDisch1;

			pauseBt1->Enabled = false;
			pauseBt1->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'I';		// idle

			if (pAll->eAsType == A_DEMO)
			{
				if (psIni->bBotScale)
					psIni->sScale1.dValue = 10.0;				// truck on scale
				else
					psIni->sScale1.dValue = 0.0;
			}
			break;

		case S_NEXT:
			all1->Enabled = false;
			all1->BackColor = COL_TRANS;
			nextBt1->Enabled = false;
			nextBt1->BackColor = COL_TRANS;
			autoBt1->Enabled = false;
			autoBt1->BackColor = COL_TRANS;

			readyBt1->Enabled = true;
			readyBt1->BackColor = COL_PGREEN;

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale1.cGo = 'I';		// idle
				else
					psIni->sScale1.cGo = 'E';		// enter						 
			}
			bFirstDrop1 = true;
			break;

		case S_READY:
			bTruck1 = true;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nReady1O;	//DC 3.2.0
			}
			else if (!psIni->bSendBitWise)			//DC 4.0.1
			{
				switch (psIni->sLog1.nSilo)
				{
				case 1: psIni->nWpoints |= psIni->asSilos[0].uReadyO; break;
				case 2: psIni->nWpoints |= psIni->asSilos[1].uReadyO; break;
				case 3: psIni->nWpoints |= psIni->asSilos[2].uReadyO; break;
				}
			}
			else if (psIni->bSendBitWise)			//DC 4.0.1
			{
				psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn on Hold
			}

			//					 psIni->nWpoints &= ~O_DROP1;
			psIni->sLog1.eStop = A_NOT;

			bool bCheckIOk;		//DC 4.0.1
			if (psIni->bUseTrkMax)						//DC 3.2.0
			{
				truckBar1->Maximum = pJob1->fLoad;
				truckBar1->Target = pJob1->fLoad - psIni->sLog1.fTruckTare;

				if (psIni->bSendBitWise)
				{
					bCheckIOk = DecimalToBinaryIO(int(truckBar1->Maximum * 2000), psIni->sLog1.nSilo);	//DC 4.0.0 send BitWise
				}
				else if (psIni->bSendTarget)
					psIni->nSclOutEU[0] = truckBar1->Maximum;		//DC 4.0.0 set analog output value
			}
			else
			{
				truckBar1->Maximum = pTruck1->nCapacity;
				truckBar1->Target = pJob1->fLoad;
			}

			if (psIni->bBotScale)
			{
				if (psIni->bUseTrkMax)					//DC 3.2.0
					scaleBar1->Target = pJob1->fLoad;
				else
					scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
			}
			else
				scaleBar1->Target = fTarget1;

			readyBt1->Enabled = false;
			readyBt1->BackColor = COL_TRANS;

			printOnly1->Enabled = true;
			printOnly1->BackColor = COL_LB;

			if (!psIni->bPdmPlc)		//DC 4.0.0
			{
				dropBt1->Enabled = true;
				dropBt1->BackColor = COL_PGREEN;
			}

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale1.cGo = 'I';	// idle
				else
					psIni->sScale1.cGo = 'S';	// stop							 	
			}
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog1.nSilo)
					{
					case 1: psIni->nWpoints |= P_SAFE1; break;
					case 2: psIni->nWpoints |= P_SAFE2; break;
					case 3: psIni->nWpoints |= P_SAFE3; break;
					}
					//						 scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
				else
				{
					psIni->nWpoints |= O_SAFE1;
					scaleBar1->Target = fTarget1;
				}
			}
			tSafeA = clock();		// safe valve timeout 

									//DC 4.0.1 Check send target IO
			if (!bCheckIOk)
			{
				bCheckIOk = checkTargetIO();
			}

			if (bCheckIOk)
				psIni->nWpoints |= psIni->uSendTargetO;		//DC 4.0.1 turn on send target output
			else
			{
				setState1(S_NEXT);
				psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
				MessageBox::Show("Target Send Error Check IO", "Lane A",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
			break;

		case S_SAFE:
			break;

		case S_DROP:
			fScaleVal1 = psIni->sScale1.dValue;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nDrop1O;		//DC 3.2.0
			}
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog1.nSilo)
					{
					case 1: psIni->nWpoints |= P_DROP1; siloBar1->BarColor = COL_DISCH; break;
					case 2: psIni->nWpoints |= P_DROP2; siloBar12->BarColor = COL_DISCH; break;
					case 3: psIni->nWpoints |= P_DROP3; siloBar13->BarColor = COL_DISCH; break;
					}
					scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
				else if (!psIni->bSendTarget && !psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uReadyO;	// turn off ready
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn off Hold
					switch (psIni->sLog1.nSilo)
					{
					case 1: psIni->nWpoints |= psIni->asSilos[0].uDropO; siloBar1->BarColor = COL_DISCH; break;
					case 2: psIni->nWpoints |= psIni->asSilos[1].uDropO; siloBar12->BarColor = COL_DISCH; break;
					case 3: psIni->nWpoints |= psIni->asSilos[2].uDropO; siloBar13->BarColor = COL_DISCH; break;
					}
					scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
				else if (psIni->bSendBitWise)		//DC 4.0.1
				{
					psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn on drop  //DC 4.0.1
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDoneO;	// turn off Done
					psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn on Hold
					switch (psIni->sLog1.nSilo)			//DC 4.0.0
					{
					case 1: siloBar1->BarColor = COL_DISCH; break;
					case 2: siloBar12->BarColor = COL_DISCH; break;
					case 3: siloBar13->BarColor = COL_DISCH; break;
					}
					scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP1;
				siloBar1->BarColor = COL_DISCH;
				scaleBar1->Target = fTarget1;
			}
			scaleBar1->BarColor = COL_CHARGE;
			fTmpScale1 = psIni->sScale1.dValue;
			nTmpCnt1 = 0;
			nSettle1 = 0;

			printOnly1->Enabled = false;
			printOnly1->BackColor = COL_TRANS;

			//					 printOnly1->Enabled = true;		//DC 4.0.8
			//					 printOnly1->BackColor = COL_LB;	//DC 4.0.8

			dropBt1->Enabled = false;
			dropBt1->BackColor = COL_TRANS;

			pauseBt1->Enabled = true;
			pauseBt1->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'G';		// go	
			break;

		case S_DELAY_PLC:
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;

			psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn on Hold
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn off Drop

			switch (psIni->sLog1.nSilo)
			{
			case 1: siloBar1->BarColor = COL_IDLE;	break;
			case 2: siloBar12->BarColor = COL_IDLE; 	break;
			case 3: siloBar13->BarColor = COL_IDLE; 	break;
			}

			dropBt1->Enabled = false;
			dropBt1->BackColor = COL_YG;

			pauseBt1->Enabled = false;
			pauseBt1->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'S';	// go
			break;

		case S_SETTLE_PLC:
			if (!psIni->bSendBitWise)	//DC 4.0.1
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn off Drop
			}
			else
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn off drop	//DC 4.0.1

			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn off Hold		//DC 4.0.1

			switch (psIni->sLog1.nSilo)
			{
			case 1: siloBar1->BarColor = COL_SETTLE;	break;
			case 2: siloBar12->BarColor = COL_SETTLE;	break;
			case 3: siloBar13->BarColor = COL_SETTLE;	break;
			}

			dropBt1->Enabled = false;
			dropBt1->BackColor = COL_YG;

			pauseBt1->Enabled = false;
			pauseBt1->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'S';		// stop
			break;

		case S_SETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_A;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~P_CLRSV_A;
				switch (psIni->sLog1.nSilo)
				{
				case 1: siloBar1->BarColor = COL_SETTLE;	break;
				case 2: siloBar12->BarColor = COL_SETTLE;	break;
				case 3: siloBar13->BarColor = COL_SETTLE;	break;
				}
				fAdapt1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;
			}
			else
			{
				psIni->nWpoints &= ~O_DROP1;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~O_SAFE1;
				siloBar1->BarColor = COL_SETTLE;
				fAdapt1 = psIni->sScale1.dValue;
			}
			dropBt1->Enabled = false;
			dropBt1->BackColor = COL_YG;

			pauseBt1->Enabled = false;
			pauseBt1->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'S';		// stop						
			break;

		case S_ADD_WAIT:
			break;

		case S_ADD:
			fScaleVal1 = psIni->sScale1.dValue;
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog1.nSilo)
					{
					case 1: psIni->nWpoints |= P_DROP1; siloBar1->BarColor = COL_DISCH; break;
					case 2: psIni->nWpoints |= P_DROP2; siloBar12->BarColor = COL_DISCH; break;
					case 3: psIni->nWpoints |= P_DROP3; siloBar13->BarColor = COL_DISCH; break;
					}
					scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
				else
				{
					switch (psIni->sLog1.nSilo)
					{
					case 1: psIni->nWpoints |= psIni->asSilos[0].uDropO; siloBar1->BarColor = COL_DISCH; break;
					case 2: psIni->nWpoints |= psIni->asSilos[1].uDropO; siloBar12->BarColor = COL_DISCH; break;
					case 3: psIni->nWpoints |= psIni->asSilos[2].uDropO; siloBar13->BarColor = COL_DISCH; break;
					}
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;

					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn off Hold

					scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP1;
				siloBar1->BarColor = COL_DISCH;
			}

			scaleBar1->BarColor = COL_CHARGE;
			addBt1->BackColor = COL_CHARGE;
			fTmpScale1 = psIni->sScale1.dValue;
			nTmpCnt1 = 0;

			pauseBt1->Enabled = true;			//DC 4.0.0
			pauseBt1->BackColor = COL_HOLDK;	//DC 4.0.0

			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'G';		// go					 
			break;

		case S_ASETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_A;
				switch (psIni->sLog1.nSilo)
				{
				case 1: siloBar1->BarColor = COL_SETTLE;	break;
				case 2: siloBar12->BarColor = COL_SETTLE;	break;
				case 3: siloBar13->BarColor = COL_SETTLE;	break;
				}
			}
			else
			{
				psIni->nWpoints &= ~O_DROP1;
				siloBar1->BarColor = COL_SETTLE;
			}
			nTmpCnt1 = 0;
			addBt1->BackColor = COL_SETTLE;
			pauseBt1->Enabled = true;
			pauseBt1->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'S';		// stop							 
			break;

		case S_DISCH_WAIT:
			siloBar1->BarColor = COL_IDLE;
			dropBt1->BackColor = COL_TRANS;
			dischBt1->Enabled = true;
			dischBt1->BackColor = COL_PGREEN;
			dischBt1->Visible = !psIni->sInv.bAutoDisch1;
			pauseBt1->Enabled = false;
			pauseBt1->BackColor = COL_TRANS;
			break;

		case S_DISCH:
			psIni->nWpoints |= O_DISCH1;
			scaleBar1->BarColor = COL_DISCH;
			dropBt1->BackColor = COL_TRANS;
			dischBt1->Enabled = false;
			dischBt1->BackColor = COL_PGREEN;
			dischBt1->Visible = !psIni->sInv.bAutoDisch1;
			nSettle1 = 0;      // scale settle timout
			pauseBt1->Enabled = true;
			pauseBt1->BackColor = COL_HOLDK;
			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'L';		// leave					
			break;

		case S_DSETTLE:
			psIni->nWpoints &= ~O_DISCH1;
			scaleBar1->BarColor = COL_SETTLE;
			pauseBt1->Enabled = false;
			pauseBt1->BackColor = COL_TRANS;
			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'P';		// pause					 					
			break;

		case S_HOLD_ASETTLE:
		case S_HOLD_SETTLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLRDRP_A;
					switch (psIni->sLog1.nSilo)
					{
					case 1: siloBar1->BarColor = COL_SETTLE;	break;
					case 2: siloBar12->BarColor = COL_SETTLE;	break;
					case 3: siloBar13->BarColor = COL_SETTLE;	break;
					}
				}
				else
				{
					psIni->nWpoints &= ~O_DROP1;
					siloBar1->BarColor = COL_SETTLE;
				}
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;

				psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn on Hold
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn off Drop
				switch (psIni->sLog1.nSilo)
				{
				case 1: siloBar1->BarColor = COL_SETTLE;	break;
				case 2: siloBar12->BarColor = COL_SETTLE;	break;
				case 3: siloBar13->BarColor = COL_SETTLE;	break;
				}
			}
			nTmpCnt1 = 0;
			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'P';		// stop							 
			break;

		case S_HOLD_DROP:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog1.nSilo)
					{
					case 1: siloBar1->BarColor = COL_HOLD;		break;
					case 2: siloBar12->BarColor = COL_HOLD;	break;
					case 3: siloBar13->BarColor = COL_HOLD;	break;
					}
				}
				else
				{
					siloBar1->BarColor = COL_HOLD;
				}
				dropBt1->Enabled = false;
				dropBt1->BackColor = COL_PGREEN;
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
				}
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1

				switch (psIni->sLog1.nSilo)
				{
				case 1: siloBar1->BarColor = COL_HOLD;		break;
				case 2: siloBar12->BarColor = COL_HOLD;	break;
				case 3: siloBar13->BarColor = COL_HOLD;	break;
				}
				dropBt1->Enabled = false;
				dropBt1->BackColor = COL_PGREEN;
				if (pAll->eAsType == A_SIM)
					psIni->sScale1.cGo = 'P';		// stop
													//if (fLoad1 >= (fTarget1 + psIni->asSilos[psIni->sLog1.nSilo-1].dAddTol))
													//{
													//	if(MessageBox::Show("TRUCK CAPACITY WARNING, continue ?", "Lane A", 
													//	System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question) 
													//	== System::Windows::Forms::DialogResult::Yes)
													//		bConDrop = true;							//DC 4.0.0 Continue Drop
													//}
			}
			break;

		case S_HOLD_ADD:	//DC 4.0.0
		case S_HOLD:
			if (!psIni->bSendBitWise)
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn off Drop
			}
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1

			switch (psIni->sLog1.nSilo)
			{
			case 1: siloBar1->BarColor = COL_HOLD;		break;
			case 2: siloBar12->BarColor = COL_HOLD;	break;
			case 3: siloBar13->BarColor = COL_HOLD;	break;
			}
			dropBt1->Enabled = false;
			dropBt1->BackColor = COL_PGREEN;
			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'P';		// stop
			break;

		case S_HOLD_DISCH:
			if (!psIni->bPdmPlc)
				psIni->nWpoints &= ~O_DISCH1;
			dischBt1->Enabled = false;
			dischBt1->BackColor = COL_PGREEN;
			scaleBar1->BarColor = COL_HOLD;
			if (pAll->eAsType == A_SIM)
				psIni->sScale1.cGo = 'P';		// pause				 
			break;

		case S_UPDATE:
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints &= ~psIni->nReady1O;		//DC 3.2.0
				psIni->nWpoints &= ~psIni->nDrop1O;		//DC 3.2.0

				if (psIni->bSafeJob == false)
				{
					if (psIni->bBotScale)
						psIni->nWpoints &= ~P_CLRSV_A;
					else
						psIni->nWpoints &= ~O_SAFE1;
				}
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
				}
				psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldO;		// turn on Hold		//DC 4.0.1
				psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uDoneO;		// turn on Done
			}
			break;

		case S_HORN:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
					psIni->nWpoints |= P_LIGHTA;
				else
					psIni->nWpoints |= O_LIGHT1;
			}
			nTmpCnt1 = 0;
			break;
		}
	}
#pragma endregion

#pragma region STATE2
			 //-------------------------------------------------------------------------
	private: System::Void setState2(STATE eNew)
	{
		switch (psIni->sLog2.eState = eNew)
		{
		case S_IDLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLEAR_B;
					zeroBar(siloBar22);
					zeroBar(siloBar23);
				}
				else
					psIni->nWpoints &= ~O_CLEARBB;
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[3].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[4].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[5].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[3].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[4].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[5].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[3].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[4].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[5].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[3].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[4].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[5].uHoldO;		// turn off Hold
				zeroBar(siloBar22);
				zeroBar(siloBar23);
			}

			zeroBar(siloBar2);
			scaleBar2->Target = 0;
			bTruck2 = false;

			// clear display
			customer2->Text = nullptr;
			Job2->Text = nullptr;
			material2->Text = nullptr;
			tic_num2->Text = nullptr;
			truck2->Text = nullptr;
			target2->Text = nullptr;

			truck2->BackColor = COL_W;
			target2->BackColor = COL_W;

			// setup buttons
			all2->Enabled = true;
			all2->BackColor = COL_LSB;
			nextBt2->Enabled = true;
			nextBt2->BackColor = COL_LSB;
			autoBt2->Enabled = !psIni->bDisableManual;		//DC 3.2.0 true;
			autoBt2->BackColor = COL_WS;

			printOnly2->Enabled = false;
			printOnly2->BackColor = COL_TRANS;
			readyBt2->Enabled = false;
			readyBt2->BackColor = COL_TRANS;

			printTarget2->Checked = false;
			taxExempt2->Checked = false;

			drops21->Checked = false;
			drops22->Checked = false;
			drops23->Checked = false;
			drops24->Checked = false;

			dropBt2->Enabled = false;
			dropBt2->BackColor = COL_TRANS;

			addBt2->Enabled = false;
			addBt2->BackColor = COL_TRANS;

			dischBt2->Enabled = false;
			dischBt2->BackColor = COL_TRANS;
			dischBt2->Visible = !psIni->sInv.bAutoDisch2;

			pauseBt2->Enabled = false;
			pauseBt2->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'I';		// idle

			if (pAll->eAsType == A_DEMO)
			{
				if (psIni->bBotScale)
					psIni->sScale2.dValue = 10.0;
				else
					psIni->sScale2.dValue = 0.0;
			}
			break;

		case S_NEXT:
			all2->Enabled = false;
			all2->BackColor = COL_TRANS;
			nextBt2->Enabled = false;
			nextBt2->BackColor = COL_TRANS;
			autoBt2->Enabled = false;
			autoBt2->BackColor = COL_TRANS;

			readyBt2->Enabled = true;
			readyBt2->BackColor = COL_PGREEN;

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale2.cGo = 'I';		// idle
				else
					psIni->sScale2.cGo = 'E';		// enter	
			}
			bFirstDrop2 = true;
			break;

		case S_READY:
			bTruck2 = true;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nReady2O;	//DC 3.2.0
			}
			else if (!psIni->bSendBitWise)			//DC 4.0.1
			{
				switch (psIni->sLog2.nSilo)
				{
				case 4: psIni->nWpoints |= psIni->asSilos[3].uReadyO; break;
				case 5: psIni->nWpoints |= psIni->asSilos[4].uReadyO; break;
				case 6: psIni->nWpoints |= psIni->asSilos[5].uReadyO; break;
				}
			}
			else if (psIni->bSendBitWise)			//DC 4.0.1
			{
				psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn on Hold
			}

			//					 psIni->nWpoints &= ~O_DROP2;
			psIni->sLog2.eStop = A_NOT;

			bool bCheckIOk;		//DC 4.0.1
			if (psIni->bUseTrkMax)						//DC 3.2.0
			{
				truckBar2->Maximum = pJob2->fLoad;
				truckBar2->Target = pJob2->fLoad - psIni->sLog2.fTruckTare;

				if (psIni->bSendBitWise)
				{
					bCheckIOk = DecimalToBinaryIO(int(truckBar2->Maximum * 2000), psIni->sLog2.nSilo);	//DC 4.0.0 send BitWise
				}
				else if (psIni->bSendTarget)
					psIni->nSclOutEU[1] = truckBar2->Maximum;		//DC 4.0.0 set analog output value
			}
			else
			{
				truckBar2->Maximum = pTruck2->nCapacity;
				truckBar2->Target = pJob2->fLoad;
			}

			if (psIni->bBotScale)
			{
				if (psIni->bUseTrkMax)					//DC 3.2.0
					scaleBar2->Target = pJob2->fLoad;
				else
					scaleBar2->Target = pJob2->fLoad + psIni->sLog2.fTruckTare;
			}
			else
				scaleBar2->Target = fTarget2;

			readyBt2->Enabled = false;
			readyBt2->BackColor = COL_TRANS;

			printOnly2->Enabled = true;
			printOnly2->BackColor = COL_LB;

			if (!psIni->bPdmPlc)		//DC 4.0.0
			{
				dropBt2->Enabled = true;
				dropBt2->BackColor = COL_PGREEN;
			}

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale2.cGo = 'I';
				else
					psIni->sScale2.cGo = 'S';
			}
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog2.nSilo)
					{
					case 4: psIni->nWpoints |= P_SAFE4; break;
					case 5: psIni->nWpoints |= P_SAFE5; break;
					case 6: psIni->nWpoints |= P_SAFE6; break;
					}
					//						 scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
				else
				{
					psIni->nWpoints |= O_SAFE2;
					scaleBar2->Target = fTarget2;
				}
			}
			tSafeB = clock();		// safe valve timeout

									//DC 4.0.1 Check send target IO
			if (bCheckIOk)
				psIni->nWpoints |= psIni->uSendTargetO;		//DC 4.0.1 turn on send target output
			else
			{
				setState2(S_NEXT);
				psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
				MessageBox::Show("Target Send Error Check IO", "Lane B",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
			break;

		case S_SAFE:
			break;

		case S_DROP:
			fScaleVal2 = psIni->sScale2.dValue;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nDrop2O;		//DC 3.2.0
			}
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog2.nSilo)
					{
					case 4: psIni->nWpoints |= P_DROP4; siloBar2->BarColor = COL_DISCH; break;
					case 5: psIni->nWpoints |= P_DROP5; siloBar22->BarColor = COL_DISCH; break;
					case 6: psIni->nWpoints |= P_DROP6; siloBar23->BarColor = COL_DISCH; break;
					}
					scaleBar2->Target = pJob2->fLoad + psIni->sLog2.fTruckTare;
				}
				else if (!psIni->bSendBitWise)		//DC 4.0.1
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uReadyO;	// turn off ready
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn off Hold
					switch (psIni->sLog2.nSilo)
					{
					case 4: psIni->nWpoints |= psIni->asSilos[3].uDropO; siloBar2->BarColor = COL_DISCH; break;
					case 5: psIni->nWpoints |= psIni->asSilos[4].uDropO; siloBar22->BarColor = COL_DISCH; break;
					case 6: psIni->nWpoints |= psIni->asSilos[5].uDropO; siloBar23->BarColor = COL_DISCH; break;
					}
					scaleBar2->Target = pJob2->fLoad + psIni->sLog2.fTruckTare;
				}
				else if (psIni->bSendBitWise)		//DC 4.0.1
				{
					psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uDropO;	// turn on drop  //DC 4.0.1
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uDoneO;	// turn off Done
					psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn on Hold
					switch (psIni->sLog2.nSilo)			//DC 4.0.0
					{
					case 4: siloBar2->BarColor = COL_DISCH; break;
					case 5: siloBar22->BarColor = COL_DISCH; break;
					case 6: siloBar23->BarColor = COL_DISCH; break;
					}
					scaleBar2->Target = pJob2->fLoad + psIni->sLog2.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP2;
				siloBar2->BarColor = COL_DISCH;
				//						 dischBt2->Enabled = false;
				//						 dischBt2->BackColor = COL_TRANS;							 
				scaleBar2->Target = fTarget2;
			}
			scaleBar2->BarColor = COL_CHARGE;
			fTmpScale2 = psIni->sScale2.dValue;
			nSettle2 = 0;
			nTmpCnt2 = 0;

			printOnly2->Enabled = false;
			printOnly2->BackColor = COL_TRANS;
			dropBt2->Enabled = false;
			dropBt2->BackColor = COL_TRANS;

			pauseBt2->Enabled = true;
			pauseBt2->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'G';		// go						 
			break;

		case S_DELAY_PLC:
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;

			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn off Hold
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uDropO;	// turn off Drop

			switch (psIni->sLog2.nSilo)
			{
			case 4: siloBar2->BarColor = COL_IDLE;	break;
			case 5: siloBar22->BarColor = COL_IDLE; 	break;
			case 6: siloBar23->BarColor = COL_IDLE; 	break;
			}

			dropBt2->Enabled = false;
			dropBt2->BackColor = COL_YG;

			pauseBt2->Enabled = false;
			pauseBt2->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'S';	// go
			break;

		case S_SETTLE_PLC:
			if (!psIni->bSendBitWise)	//DC 4.0.1
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uDropO;	// turn off Drop

			}
			else
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uDropO;	// turn off drop	//DC 4.0.1

			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;		// turn off Hold		//DC 4.0.1

			switch (psIni->sLog2.nSilo)
			{
			case 4: siloBar2->BarColor = COL_SETTLE;	break;
			case 5: siloBar22->BarColor = COL_SETTLE;	break;
			case 6: siloBar23->BarColor = COL_SETTLE;	break;
			}

			dropBt2->Enabled = false;
			dropBt2->BackColor = COL_YG;

			pauseBt2->Enabled = false;
			pauseBt2->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'S';		// stop
			break;

		case S_SETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_B;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~P_CLRSV_B;
				switch (psIni->sLog2.nSilo)
				{
				case 4: siloBar2->BarColor = COL_SETTLE;	break;
				case 5: siloBar22->BarColor = COL_SETTLE;	break;
				case 6: siloBar23->BarColor = COL_SETTLE;	break;
				}
				fAdapt2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;
			}
			else
			{
				psIni->nWpoints &= ~O_DROP2;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~O_SAFE2;
				siloBar2->BarColor = COL_SETTLE;
				fAdapt2 = psIni->sScale2.dValue;
			}
			dropBt2->Enabled = false;
			dropBt2->BackColor = COL_YG;

			pauseBt2->Enabled = false;
			pauseBt2->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'S';		// stop						 
			break;

		case S_ADD_WAIT:
			break;

		case S_ADD:
			fScaleVal2 = psIni->sScale2.dValue;
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog2.nSilo)
					{
					case 4: psIni->nWpoints |= P_DROP4; siloBar2->BarColor = COL_DISCH; break;
					case 5: psIni->nWpoints |= P_DROP5; siloBar22->BarColor = COL_DISCH;  break;
					case 6: psIni->nWpoints |= P_DROP6; siloBar23->BarColor = COL_DISCH;  break;
					}
					scaleBar2->Target = pJob2->fLoad + psIni->sLog2.fTruckTare;
				}
				else
				{
					switch (psIni->sLog2.nSilo)
					{
					case 4: psIni->nWpoints |= psIni->asSilos[3].uDropO; siloBar2->BarColor = COL_DISCH; break;
					case 5: psIni->nWpoints |= psIni->asSilos[4].uDropO; siloBar22->BarColor = COL_DISCH; break;
					case 6: psIni->nWpoints |= psIni->asSilos[5].uDropO; siloBar23->BarColor = COL_DISCH; break;
					}
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;

					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn off Hold

					scaleBar2->Target = pJob2->fLoad + psIni->sLog2.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP2;
				siloBar2->BarColor = COL_DISCH;
			}

			scaleBar2->BarColor = COL_CHARGE;
			addBt2->BackColor = COL_CHARGE;
			fTmpScale2 = psIni->sScale2.dValue;
			nTmpCnt2 = 0;

			pauseBt2->Enabled = true;			//DC 4.0.0
			pauseBt2->BackColor = COL_HOLDK;	//DC 4.0.0

			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'G';		// go						 
			break;

		case S_ASETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_B;
				switch (psIni->sLog2.nSilo)
				{
				case 4: siloBar2->BarColor = COL_SETTLE;	break;
				case 5: siloBar22->BarColor = COL_SETTLE;	break;
				case 6: siloBar23->BarColor = COL_SETTLE;	break;
				}
			}
			else
			{
				psIni->nWpoints &= ~O_DROP2;
				siloBar2->BarColor = COL_SETTLE;
			}
			nTmpCnt2 = 0;
			addBt2->BackColor = COL_SETTLE;
			pauseBt2->Enabled = true;
			pauseBt2->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'S';		// stop						 
			break;

		case S_DISCH_WAIT:
			siloBar2->BarColor = COL_IDLE;
			dropBt2->BackColor = COL_TRANS;
			dischBt2->Enabled = true;
			dischBt2->BackColor = COL_PGREEN;
			dischBt2->Visible = !psIni->sInv.bAutoDisch2;
			pauseBt2->Enabled = false;
			pauseBt2->BackColor = COL_TRANS;
			break;

		case S_DISCH:
			psIni->nWpoints |= O_DISCH2;
			scaleBar2->BarColor = COL_DISCH;
			dropBt2->BackColor = COL_TRANS;
			dischBt2->Enabled = false;
			dischBt2->BackColor = COL_PGREEN;
			dischBt2->Visible = !psIni->sInv.bAutoDisch2;
			nSettle2 = 0;
			pauseBt2->Enabled = true;
			pauseBt2->BackColor = COL_HOLDK;
			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'L';		// leave				
			break;

		case S_DSETTLE:
			scaleBar2->BarColor = COL_SETTLE;
			psIni->nWpoints &= ~O_DISCH2;
			pauseBt2->Enabled = false;
			pauseBt2->BackColor = COL_TRANS;
			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'P';		// pause					 
			break;

		case S_HOLD_ASETTLE:
		case S_HOLD_SETTLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLRDRP_B;
					switch (psIni->sLog2.nSilo)
					{
					case 4: siloBar2->BarColor = COL_SETTLE;	break;
					case 5: siloBar22->BarColor = COL_SETTLE;	break;
					case 6: siloBar23->BarColor = COL_SETTLE;	break;
					}
				}
				else
				{
					psIni->nWpoints &= ~O_DROP2;
					siloBar2->BarColor = COL_SETTLE;
				}
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;

				psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn on Hold
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uDropO;	// turn off Drop
				switch (psIni->sLog2.nSilo)
				{
				case 4: siloBar2->BarColor = COL_SETTLE;	break;
				case 5: siloBar22->BarColor = COL_SETTLE;	break;
				case 6: siloBar23->BarColor = COL_SETTLE;	break;
				}
			}
			nTmpCnt2 = 0;
			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'P';		// pause						 
			break;

		case S_HOLD_DROP:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog2.nSilo)
					{
					case 4: siloBar2->BarColor = COL_HOLD;	break;
					case 5: siloBar22->BarColor = COL_HOLD;	break;
					case 6: siloBar23->BarColor = COL_HOLD;	break;
					}
				}
				else
				{
					siloBar2->BarColor = COL_HOLD;
				}
				dropBt2->Enabled = false;
				dropBt2->BackColor = COL_PGREEN;
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;

				}
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1

				switch (psIni->sLog2.nSilo)
				{
				case 4: siloBar2->BarColor = COL_HOLD;		break;
				case 5: siloBar22->BarColor = COL_HOLD;	break;
				case 6: siloBar23->BarColor = COL_HOLD;	break;
				}
				dropBt2->Enabled = false;
				dropBt2->BackColor = COL_PGREEN;
				if (pAll->eAsType == A_SIM)
					psIni->sScale2.cGo = 'P';		// stop
			}
			break;

		case S_HOLD_ADD:	//DC 4.0.0
		case S_HOLD:
			if (!psIni->bSendBitWise)
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
			}
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1

			switch (psIni->sLog2.nSilo)
			{
			case 4: siloBar2->BarColor = COL_HOLD;		break;
			case 5: siloBar22->BarColor = COL_HOLD;	break;
			case 6: siloBar23->BarColor = COL_HOLD;	break;
			}
			dropBt2->Enabled = false;
			dropBt2->BackColor = COL_PGREEN;
			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'P';		// stop
			break;

		case S_HOLD_DISCH:
			psIni->nWpoints &= ~O_DISCH2;
			scaleBar2->BarColor = COL_HOLD;
			dischBt2->Enabled = false;
			dischBt2->BackColor = COL_PGREEN;
			if (pAll->eAsType == A_SIM)
				psIni->sScale2.cGo = 'P';	// pause					 
			break;

		case S_UPDATE:
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints &= ~psIni->nReady2O;		//DC 3.2.0
				psIni->nWpoints &= ~psIni->nDrop2O;		//DC 3.2.0
				if (psIni->bSafeJob == false)
				{
					if (psIni->bBotScale)
						psIni->nWpoints &= ~P_CLRSV_B;
					else
						psIni->nWpoints &= ~O_SAFE2;
				}
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
				}
				psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldO;		// turn on Hold		//DC 4.0.1
				psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uDoneO;		// turn on Done
			}
			break;

		case S_HORN:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
					psIni->nWpoints |= P_LIGHTB;
				else
					psIni->nWpoints |= O_LIGHT2;
			}
			nTmpCnt2 = 0;
			break;
		}
	}
#pragma endregion

#pragma region STATE3
			 //-------------------------------------------------------------------------
	private: System::Void setState3(STATE eNew)
	{
		switch (psIni->sLog3.eState = eNew)
		{
		case S_IDLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLEAR_C;
					zeroBar(siloBar32);
					zeroBar(siloBar33);
				}
				else
					psIni->nWpoints &= ~O_CLEARCC;
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[6].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[7].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[8].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[6].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[7].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[8].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[6].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[7].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[8].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[6].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[7].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[8].uHoldO;		// turn off Hold
				zeroBar(siloBar32);
				zeroBar(siloBar33);
			}

			zeroBar(siloBar3);
			scaleBar3->Target = 0;
			bTruck3 = false;

			// clear display
			customer3->Text = nullptr;
			Job3->Text = nullptr;
			material3->Text = nullptr;
			tic_num3->Text = nullptr;
			truck3->Text = nullptr;
			target3->Text = nullptr;

			truck3->BackColor = COL_W;
			target3->BackColor = COL_W;

			// setup buttons
			all3->Enabled = true;
			all3->BackColor = COL_LSB;
			nextBt3->Enabled = true;		// enabled for manual
			nextBt3->BackColor = COL_LSB;
			autoBt3->Enabled = !psIni->bDisableManual;		//DC 3.2.0 true;
			autoBt3->BackColor = COL_WS;

			printOnly3->Enabled = false;
			printOnly3->BackColor = COL_TRANS;
			readyBt3->Enabled = false;
			readyBt3->BackColor = COL_TRANS;

			printTarget3->Checked = false;
			taxExempt3->Checked = false;

			drops31->Checked = false;
			drops32->Checked = false;
			drops33->Checked = false;
			drops34->Checked = false;

			dropBt3->Enabled = false;
			dropBt3->BackColor = COL_TRANS;

			addBt3->Enabled = false;
			addBt3->BackColor = COL_TRANS;

			dischBt3->Enabled = false;
			dischBt3->BackColor = COL_TRANS;
			dischBt3->Visible = !psIni->sInv.bAutoDisch3;

			pauseBt3->Enabled = false;
			pauseBt3->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'I';	// idle

			if (pAll->eAsType == A_DEMO)
			{
				if (psIni->bBotScale)
					psIni->sScale3.dValue = 10.0;
				else
					psIni->sScale3.dValue = 0.0;
			}
			break;

		case S_NEXT:
			all3->Enabled = false;
			all3->BackColor = COL_TRANS;
			nextBt3->Enabled = false;
			nextBt3->BackColor = COL_TRANS;
			autoBt3->Enabled = false;
			autoBt3->BackColor = COL_TRANS;

			readyBt3->Enabled = true;
			readyBt3->BackColor = COL_PGREEN;

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale3.cGo = 'I';
				else
					psIni->sScale3.cGo = 'E';
			}
			bFirstDrop3 = true;
			break;

		case S_READY:
			bTruck3 = true;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nReady3O;	//DC 3.2.0
			}
			else if (!psIni->bSendBitWise)			//DC 4.0.1
			{
				switch (psIni->sLog3.nSilo)
				{
				case 7: psIni->nWpoints |= psIni->asSilos[6].uReadyO; break;
				case 8: psIni->nWpoints |= psIni->asSilos[7].uReadyO; break;
				case 9: psIni->nWpoints |= psIni->asSilos[8].uReadyO; break;
				}
			}
			else if (psIni->bSendBitWise)			//DC 4.0.1
			{
				psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn on Hold
			}

			//					 psIni->nWpoints &= ~O_DROP3;
			psIni->sLog3.eStop = A_NOT;

			bool bCheckIOk;		//DC 4.0.1
			if (psIni->bUseTrkMax)						//DC 3.2.0
			{
				truckBar3->Maximum = pJob3->fLoad;
				truckBar3->Target = pJob3->fLoad - psIni->sLog3.fTruckTare;

				if (psIni->bSendBitWise)
				{
					bCheckIOk = DecimalToBinaryIO(int(truckBar3->Maximum * 2000), psIni->sLog3.nSilo);	//DC 4.0.0 send BitWise
				}
				else if (psIni->bSendTarget)
					psIni->nSclOutEU[2] = truckBar3->Maximum;		//DC 4.0.0 set analog output value
			}
			else
			{
				truckBar3->Maximum = pTruck3->nCapacity;
				truckBar3->Target = pJob3->fLoad;
			}

			if (psIni->bBotScale)
			{
				if (psIni->bUseTrkMax)					//DC 3.2.0
					scaleBar3->Target = pJob3->fLoad;
				else
					scaleBar3->Target = pJob3->fLoad + psIni->sLog3.fTruckTare;
			}
			else
				scaleBar3->Target = fTarget3;

			readyBt3->Enabled = false;
			readyBt3->BackColor = COL_TRANS;

			printOnly3->Enabled = true;
			printOnly3->BackColor = COL_LB;

			if (!psIni->bPdmPlc)		//DC 4.0.0
			{
				dropBt3->Enabled = true;
				dropBt3->BackColor = COL_PGREEN;
			}

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale3.cGo = 'I';
				else
					psIni->sScale3.cGo = 'S';	// stop
			}
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog3.nSilo)
					{
					case 7: psIni->nWpoints |= P_SAFE7; break;
					case 8: psIni->nWpoints |= P_SAFE8; break;
					case 9: psIni->nWpoints |= P_SAFE9; break;
					}
					//						 scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
				else
				{
					psIni->nWpoints |= O_SAFE3;
					scaleBar3->Target = fTarget3;
				}
			}
			tSafeC = clock();		// safe valve timeout 

									//DC 4.0.1 Check send target IO
			if (bCheckIOk)
				psIni->nWpoints |= psIni->uSendTargetO;		//DC 4.0.1 turn on send target output
			else
			{
				setState3(S_NEXT);
				psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
				MessageBox::Show("Target Send Error Check IO", "Lane C",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
			break;

		case S_SAFE:
			break;

		case S_DROP:
			fScaleVal3 = psIni->sScale3.dValue;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nDrop3O;		//DC 3.2.0
			}
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog3.nSilo)
					{
					case 7: psIni->nWpoints |= P_DROP7; siloBar3->BarColor = COL_DISCH; break;
					case 8: psIni->nWpoints |= P_DROP8; siloBar32->BarColor = COL_DISCH; break;
					case 9: psIni->nWpoints |= P_DROP9; siloBar33->BarColor = COL_DISCH; break;
					}
					scaleBar3->Target = pJob3->fLoad + psIni->sLog3.fTruckTare;
				}
				else if (!psIni->bSendBitWise)		//DC 4.0.1
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uReadyO;	// turn off ready
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn off Hold
					switch (psIni->sLog3.nSilo)
					{
					case 7: psIni->nWpoints |= psIni->asSilos[6].uDropO; siloBar3->BarColor = COL_DISCH; break;
					case 8: psIni->nWpoints |= psIni->asSilos[7].uDropO; siloBar32->BarColor = COL_DISCH; break;
					case 9: psIni->nWpoints |= psIni->asSilos[8].uDropO; siloBar33->BarColor = COL_DISCH; break;
					}
					scaleBar3->Target = pJob3->fLoad + psIni->sLog3.fTruckTare;
				}
				else if (psIni->bSendBitWise)		//DC 4.0.1
				{
					psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uDropO;	// turn on drop  //DC 4.0.1
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uDoneO;	// turn off Done
					psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn on Hold
					switch (psIni->sLog3.nSilo)			//DC 4.0.0
					{
					case 7: siloBar3->BarColor = COL_DISCH; break;
					case 8: siloBar32->BarColor = COL_DISCH; break;
					case 9: siloBar33->BarColor = COL_DISCH; break;
					}
					scaleBar3->Target = pJob3->fLoad + psIni->sLog3.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP3;
				siloBar3->BarColor = COL_DISCH;
				//						 dischBt3->Enabled = false;
				//						 dischBt3->BackColor = COL_TRANS;							 
				scaleBar3->Target = fTarget3;
			}
			scaleBar3->BarColor = COL_CHARGE;
			fTmpScale3 = psIni->sScale3.dValue;
			nSettle3 = 0;
			nTmpCnt3 = 0;

			printOnly3->Enabled = false;
			printOnly3->BackColor = COL_TRANS;
			dropBt3->Enabled = false;
			dropBt3->BackColor = COL_TRANS;

			pauseBt3->Enabled = true;
			pauseBt3->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'G';	// go					 
			break;

		case S_DELAY_PLC:
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;

			psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn on Hold
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uDropO;	// turn off Drop

			switch (psIni->sLog3.nSilo)
			{
			case 7: siloBar3->BarColor = COL_IDLE;	break;
			case 8: siloBar32->BarColor = COL_IDLE; 	break;
			case 9: siloBar33->BarColor = COL_IDLE; 	break;
			}

			dropBt3->Enabled = false;
			dropBt3->BackColor = COL_YG;

			pauseBt3->Enabled = false;
			pauseBt3->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'S';	// go
			break;

		case S_SETTLE_PLC:
			if (!psIni->bSendBitWise)	//DC 4.0.1
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uDropO;	// turn off Drop

			}
			else
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uDropO;	// turn off drop	//DC 4.0.1

			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;		// turn off Hold		//DC 4.0.1

			switch (psIni->sLog3.nSilo)
			{
			case 7: siloBar3->BarColor = COL_SETTLE;	break;
			case 8: siloBar32->BarColor = COL_SETTLE;	break;
			case 9: siloBar33->BarColor = COL_SETTLE;	break;
			}

			dropBt3->Enabled = false;
			dropBt3->BackColor = COL_YG;

			pauseBt3->Enabled = false;
			pauseBt3->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'S';		// stop
			break;

		case S_SETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_C;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~P_CLRSV_C;
				switch (psIni->sLog3.nSilo)
				{
				case 7: siloBar3->BarColor = COL_SETTLE;	break;
				case 8: siloBar32->BarColor = COL_SETTLE;	break;
				case 9: siloBar33->BarColor = COL_SETTLE;	break;
				}
				fAdapt3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;
			}
			else
			{
				psIni->nWpoints &= ~O_DROP3;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~O_SAFE3;
				siloBar3->BarColor = COL_SETTLE;
				fAdapt3 = psIni->sScale3.dValue;
			}
			dropBt3->Enabled = false;
			dropBt3->BackColor = COL_YG;

			pauseBt3->Enabled = false;
			pauseBt3->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'S';	// stop						 
			break;

		case S_ADD_WAIT:
			break;

		case S_ADD:
			fScaleVal3 = psIni->sScale3.dValue;
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog3.nSilo)
					{
					case 7: psIni->nWpoints |= P_DROP7; siloBar3->BarColor = COL_DISCH;  break;
					case 8: psIni->nWpoints |= P_DROP8; siloBar32->BarColor = COL_DISCH; break;
					case 9: psIni->nWpoints |= P_DROP9; siloBar33->BarColor = COL_DISCH; break;
					}
					scaleBar3->Target = pJob3->fLoad + psIni->sLog3.fTruckTare;
				}
				else
				{
					switch (psIni->sLog3.nSilo)
					{
					case 7: psIni->nWpoints |= psIni->asSilos[6].uDropO; siloBar3->BarColor = COL_DISCH; break;
					case 8: psIni->nWpoints |= psIni->asSilos[7].uDropO; siloBar32->BarColor = COL_DISCH; break;
					case 9: psIni->nWpoints |= psIni->asSilos[8].uDropO; siloBar33->BarColor = COL_DISCH; break;
					}
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;

					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn off Hold

					scaleBar3->Target = pJob3->fLoad + psIni->sLog3.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP3;
				siloBar3->BarColor = COL_DISCH;
			}

			scaleBar3->BarColor = COL_CHARGE;
			addBt3->BackColor = COL_CHARGE;
			fTmpScale3 = psIni->sScale3.dValue;
			nTmpCnt3 = 0;

			pauseBt3->Enabled = true;			//DC 4.0.0
			pauseBt3->BackColor = COL_HOLDK;	//DC 4.0.0

			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'G';	// go					 
			break;

		case S_ASETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_C;
				switch (psIni->sLog3.nSilo)
				{
				case 7: siloBar3->BarColor = COL_SETTLE;	break;
				case 8: siloBar32->BarColor = COL_SETTLE;	break;
				case 9: siloBar33->BarColor = COL_SETTLE;	break;
				}
			}
			else
			{
				psIni->nWpoints &= ~O_DROP3;
				siloBar3->BarColor = COL_SETTLE;
			}
			nTmpCnt3 = 0;
			addBt3->BackColor = COL_SETTLE;
			pauseBt3->Enabled = true;
			pauseBt3->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'S';	// stop						 
			break;

		case S_DISCH_WAIT:
			siloBar3->BarColor = COL_IDLE;
			dropBt3->BackColor = COL_TRANS;
			dischBt3->Enabled = true;
			dischBt3->BackColor = COL_PGREEN;
			dischBt3->Visible = !psIni->sInv.bAutoDisch3;
			pauseBt3->Enabled = false;
			pauseBt3->BackColor = COL_TRANS;
			break;

		case S_DISCH:
			psIni->nWpoints |= O_DISCH3;
			scaleBar3->BarColor = COL_DISCH;
			nSettle3 = 0;      // scale settle timout
			dropBt3->BackColor = COL_TRANS;
			dischBt3->Enabled = false;
			dischBt3->BackColor = COL_PGREEN;
			dischBt3->Visible = !psIni->sInv.bAutoDisch3;
			pauseBt3->Enabled = true;
			pauseBt3->BackColor = COL_HOLDK;
			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'L';	// leave					
			break;

		case S_DSETTLE:
			psIni->nWpoints &= ~O_DISCH3;
			scaleBar3->BarColor = COL_SETTLE;
			pauseBt3->Enabled = false;
			pauseBt3->BackColor = COL_TRANS;
			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'P';	// pause					 										 
			break;

		case S_HOLD_ASETTLE:
		case S_HOLD_SETTLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLRDRP_C;
					switch (psIni->sLog3.nSilo)
					{
					case 7: siloBar3->BarColor = COL_SETTLE;	break;
					case 8: siloBar32->BarColor = COL_SETTLE;	break;
					case 9: siloBar33->BarColor = COL_SETTLE;	break;
					}
				}
				else
				{
					psIni->nWpoints &= ~O_DROP3;
					siloBar3->BarColor = COL_SETTLE;
				}
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;

				psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn on Hold
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uDropO;	// turn off Drop
				switch (psIni->sLog3.nSilo)
				{
				case 7: siloBar3->BarColor = COL_SETTLE;	break;
				case 8: siloBar32->BarColor = COL_SETTLE;	break;
				case 9: siloBar33->BarColor = COL_SETTLE;	break;
				}
			}
			nTmpCnt3 = 0;
			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'P';	// pause						 
			break;

		case S_HOLD_DROP:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog3.nSilo)
					{
					case 7: siloBar3->BarColor = COL_HOLD;	break;
					case 8: siloBar32->BarColor = COL_HOLD;	break;
					case 9: siloBar33->BarColor = COL_HOLD;	break;
					}
				}
				else
				{
					siloBar3->BarColor = COL_HOLD;
				}
				dropBt3->Enabled = false;
				dropBt3->BackColor = COL_PGREEN;
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;

				}
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1

				switch (psIni->sLog3.nSilo)
				{
				case 7: siloBar3->BarColor = COL_HOLD;		break;
				case 8: siloBar32->BarColor = COL_HOLD;	break;
				case 9: siloBar33->BarColor = COL_HOLD;	break;
				}
				dropBt3->Enabled = false;
				dropBt3->BackColor = COL_PGREEN;
				if (pAll->eAsType == A_SIM)
					psIni->sScale3.cGo = 'P';		// stop
			}
			break;

		case S_HOLD_ADD:	//DC 4.0.0
		case S_HOLD:
			if (!psIni->bSendBitWise)
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
			}
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1

			switch (psIni->sLog3.nSilo)
			{
			case 7: siloBar3->BarColor = COL_HOLD;		break;
			case 8: siloBar32->BarColor = COL_HOLD;	break;
			case 9: siloBar33->BarColor = COL_HOLD;	break;
			}
			dropBt3->Enabled = false;
			dropBt3->BackColor = COL_PGREEN;
			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'P';		// stop
			break;

		case S_HOLD_DISCH:
			if (!psIni->bPdmPlc)
				psIni->nWpoints &= ~O_DISCH3;
			scaleBar3->BarColor = COL_HOLD;
			dischBt3->Enabled = true;
			dischBt3->BackColor = COL_PGREEN;
			if (pAll->eAsType == A_SIM)
				psIni->sScale3.cGo = 'P';	// pause					 
			break;

		case S_UPDATE:
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints &= ~psIni->nReady3O;		//DC 3.2.0
				psIni->nWpoints &= ~psIni->nDrop3O;		//DC 3.2.0
				if (psIni->bSafeJob == false)
				{
					if (psIni->bBotScale)
						psIni->nWpoints &= ~P_CLRSV_C;
					else
						psIni->nWpoints &= ~O_SAFE3;
				}
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
				}
				else
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uReadyO;		// turn off Ready

				psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldO;		// turn on Hold		//DC 4.0.1
				psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uDoneO;		// turn on Done
			}
			break;

		case S_HORN:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
					psIni->nWpoints |= P_LIGHTC;
				else
					psIni->nWpoints |= O_LIGHT3;
			}
			nTmpCnt3 = 0;
			break;
		}
	}
#pragma endregion

#pragma region STATE4		
			 //DC 3.3.0  -------------------------------------------------------------------------
	private: System::Void setState4(STATE eNew)
	{
		switch (psIni->sLog4.eState = eNew)
		{
		case S_IDLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLEAR_D;
					zeroBar(siloBar42);
					zeroBar(siloBar43);
				}
				else
					psIni->nWpoints &= ~O_CLEARDD;
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[9].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[10].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[11].uReadyO;		// turn off Ready
				psIni->nWpoints &= ~psIni->asSilos[9].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[10].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[11].uDropO;		// turn off Drop
				psIni->nWpoints &= ~psIni->asSilos[9].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[10].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[11].uDoneO;		// turn off Done
				psIni->nWpoints &= ~psIni->asSilos[9].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[10].uHoldO;		// turn off Hold
				psIni->nWpoints &= ~psIni->asSilos[11].uHoldO;		// turn off Hold
				zeroBar(siloBar42);
				zeroBar(siloBar43);
			}

			zeroBar(siloBar4);
			scaleBar4->Target = 0;
			bTruck4 = false;

			// clear display
			customer4->Text = nullptr;
			Job4->Text = nullptr;
			material4->Text = nullptr;
			tic_num4->Text = nullptr;
			truck4->Text = nullptr;
			target4->Text = nullptr;

			truck4->BackColor = COL_W;
			target4->BackColor = COL_W;

			// setup buttons
			all4->Enabled = true;
			all4->BackColor = COL_LSB;
			nextBt4->Enabled = true;		// enabled for manual
			nextBt4->BackColor = COL_LSB;
			autoBt4->Enabled = !psIni->bDisableManual;		//DC 3.2.0 true;
			autoBt4->BackColor = COL_WS;

			printOnly4->Enabled = false;
			printOnly4->BackColor = COL_TRANS;
			readyBt4->Enabled = false;
			readyBt4->BackColor = COL_TRANS;

			printTarget4->Checked = false;
			taxExempt4->Checked = false;

			drops41->Checked = false;
			drops42->Checked = false;
			drops43->Checked = false;
			drops44->Checked = false;

			dropBt4->Enabled = false;
			dropBt4->BackColor = COL_TRANS;

			addBt4->Enabled = false;
			addBt4->BackColor = COL_TRANS;

			dischBt4->Enabled = false;
			dischBt4->BackColor = COL_TRANS;
			dischBt4->Visible = !psIni->sInv.bAutoDisch4;

			pauseBt4->Enabled = false;
			pauseBt4->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'I';	// idle

			if (pAll->eAsType == A_DEMO)
			{
				if (psIni->bBotScale)
					psIni->sScale4.dValue = 10.0;
				else
					psIni->sScale4.dValue = 0.0;
			}
			break;

		case S_NEXT:
			all4->Enabled = false;
			all4->BackColor = COL_TRANS;
			nextBt4->Enabled = false;
			nextBt4->BackColor = COL_TRANS;
			autoBt4->Enabled = false;
			autoBt4->BackColor = COL_TRANS;

			if (!psIni->bSendBitWise)			//DC 4.1.0
			{
				readyBt4->Enabled = true;
				readyBt4->BackColor = COL_PGREEN;
			}

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale4.cGo = 'I';
				else
					psIni->sScale4.cGo = 'E';
			}
			bFirstDrop4 = true;
			break;

		case S_READY:
			bTruck4 = true;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nReady4O;	//DC 3.2.0
			}
			else if (!psIni->bSendBitWise)			//DC 4.0.1
			{
				switch (psIni->sLog4.nSilo)
				{
				case 10: psIni->nWpoints |= psIni->asSilos[9].uReadyO; break;
				case 11: psIni->nWpoints |= psIni->asSilos[10].uReadyO; break;
				case 12: psIni->nWpoints |= psIni->asSilos[11].uReadyO; break;
				}
			}
			else if (psIni->bSendBitWise)			//DC 4.0.1
			{
				psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn on Hold
			}

			//					 psIni->nWpoints &= ~O_DROP3;
			psIni->sLog4.eStop = A_NOT;

			bool bCheckIOk;							//DC 4.0.1
			if (psIni->bUseTrkMax)						//DC 3.2.0
			{
				truckBar4->Maximum = pJob4->fLoad;
				truckBar4->Target = pJob4->fLoad - psIni->sLog4.fTruckTare;

				if (psIni->bSendBitWise)
				{
					bCheckIOk = DecimalToBinaryIO(int(truckBar4->Maximum * 2000), psIni->sLog4.nSilo);	//DC 4.0.0 send BitWise
				}
				else if (psIni->bSendTarget)
					psIni->nSclOutEU[3] = truckBar4->Maximum;		//DC 4.0.0 set analog output value
			}
			else
			{
				truckBar4->Maximum = pTruck4->nCapacity;
				truckBar4->Target = pJob4->fLoad;
			}


			if (psIni->bBotScale)
			{
				if (psIni->bUseTrkMax)					//DC 3.2.0
					scaleBar4->Target = pJob4->fLoad;
				else
					scaleBar4->Target = pJob4->fLoad + psIni->sLog4.fTruckTare;
			}
			else
				scaleBar4->Target = fTarget4;

			readyBt4->Enabled = false;
			readyBt4->BackColor = COL_TRANS;

			printOnly4->Enabled = true;
			printOnly4->BackColor = COL_LB;

			if (!psIni->bPdmPlc)		//DC 4.0.0
			{
				dropBt4->Enabled = true;
				dropBt4->BackColor = COL_PGREEN;
			}

			if (pAll->eAsType == A_SIM)
			{
				if (!psIni->bBotScale)
					psIni->sScale4.cGo = 'I';
				else
					psIni->sScale4.cGo = 'S';	// stop
			}
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog4.nSilo)
					{
					case 10: psIni->nWpoints |= P_SAFE10; break;
					case 11: psIni->nWpoints |= P_SAFE11; break;
					case 12: psIni->nWpoints |= P_SAFE12; break;
					}
					//						 scaleBar1->Target = pJob1->fLoad + psIni->sLog1.fTruckTare;
				}
				else
				{
					psIni->nWpoints |= O_SAFE4;
					scaleBar4->Target = fTarget4;
				}
			}
			tSafeD = clock();		// safe valve timeout 

									//DC 4.0.1 Check send target IO
			if (bCheckIOk)
				psIni->nWpoints |= psIni->uSendTargetO;		//DC 4.0.1 turn on send target output
			else
			{
				truck4->BackColor = COL_W;
				target4->BackColor = COL_W;
				target4->ReadOnly = false;		//DC 3.2.4
				setState4(S_NEXT);
				psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output

				if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
				{
					MessageBox::Show("Target Send Error Check IO", "Lane R",
						System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
				else if (pAll->eAsType == A_REMOTE)
				{
					MessageBox::Show("Target Send Error Check IO", "Lane R",
						System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			}
			pAll->bRemoteCall = false;
			break;

		case S_SAFE:
			break;

		case S_DROP:
			fScaleVal4 = psIni->sScale4.dValue;
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints |= psIni->nDrop4O;		//DC 3.2.0
			}
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog4.nSilo)
					{
					case 10: psIni->nWpoints |= P_DROP10; siloBar4->BarColor = COL_DISCH; break;
					case 11: psIni->nWpoints |= P_DROP11; siloBar42->BarColor = COL_DISCH; break;
					case 12: psIni->nWpoints |= P_DROP12; siloBar43->BarColor = COL_DISCH; break;
					}
					scaleBar4->Target = pJob4->fLoad + psIni->sLog4.fTruckTare;
				}
				else if (!psIni->bSendBitWise)		//DC 4.0.1
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uReadyO;	// turn off ready
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn off Hold
					switch (psIni->sLog4.nSilo)
					{
					case 10: psIni->nWpoints |= psIni->asSilos[9].uDropO; siloBar4->BarColor = COL_DISCH; break;
					case 11: psIni->nWpoints |= psIni->asSilos[10].uDropO; siloBar42->BarColor = COL_DISCH; break;
					case 12: psIni->nWpoints |= psIni->asSilos[11].uDropO; siloBar43->BarColor = COL_DISCH; break;
					}
					scaleBar4->Target = pJob4->fLoad + psIni->sLog4.fTruckTare;
				}
				else if (psIni->bSendBitWise)		//DC 4.0.1
				{
					psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uDropO;	// turn on drop  //DC 4.0.1
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uDoneO;	// turn off Done
					psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn on Hold
					switch (psIni->sLog4.nSilo)			//DC 4.0.0
					{
					case 10: siloBar4->BarColor = COL_DISCH; break;
					case 11: siloBar42->BarColor = COL_DISCH; break;
					case 12: siloBar43->BarColor = COL_DISCH; break;
					}
					scaleBar4->Target = pJob4->fLoad + psIni->sLog4.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP4;
				siloBar4->BarColor = COL_DISCH;
				//						 dischBt4->Enabled = false;
				//						 dischBt4->BackColor = COL_TRANS;							 
				scaleBar4->Target = fTarget4;
			}
			scaleBar4->BarColor = COL_CHARGE;
			fTmpScale4 = psIni->sScale4.dValue;
			nSettle4 = 0;
			nTmpCnt4 = 0;

			printOnly4->Enabled = false;
			printOnly4->BackColor = COL_TRANS;
			dropBt4->Enabled = false;
			dropBt4->BackColor = COL_TRANS;

			pauseBt4->Enabled = true;
			pauseBt4->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'G';	// go					 
			break;

		case S_DELAY_PLC:
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;

			psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn on Hold
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uDropO;	// turn off Drop

			switch (psIni->sLog4.nSilo)
			{
			case 10: siloBar4->BarColor = COL_IDLE;	break;
			case 11: siloBar42->BarColor = COL_IDLE; 	break;
			case 12: siloBar43->BarColor = COL_IDLE; 	break;
			}

			dropBt4->Enabled = false;
			dropBt4->BackColor = COL_YG;

			pauseBt4->Enabled = false;
			pauseBt4->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'S';	// go
			break;

		case S_SETTLE_PLC:
			if (!psIni->bSendBitWise)	//DC 4.0.1
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uDropO;	// turn off Drop					 
			}
			else
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uDropO;	// turn off drop	//DC 4.0.1

			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;		// turn off Hold		//DC 4.0.1

			switch (psIni->sLog4.nSilo)
			{
			case 10: siloBar4->BarColor = COL_SETTLE;	break;
			case 11: siloBar42->BarColor = COL_SETTLE;	break;
			case 12: siloBar43->BarColor = COL_SETTLE;	break;
			}

			dropBt4->Enabled = false;
			dropBt4->BackColor = COL_YG;

			pauseBt4->Enabled = false;
			pauseBt4->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'S';		// stop
			break;

		case S_SETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_D;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~P_CLRSV_D;
				switch (psIni->sLog4.nSilo)
				{
				case 10: siloBar4->BarColor = COL_SETTLE;	break;
				case 11: siloBar42->BarColor = COL_SETTLE;	break;
				case 12: siloBar43->BarColor = COL_SETTLE;	break;
				}
				fAdapt4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;
			}
			else
			{
				psIni->nWpoints &= ~O_DROP4;
				if (psIni->bSafeJob == false)
					psIni->nWpoints &= ~O_SAFE4;
				siloBar4->BarColor = COL_SETTLE;
				fAdapt4 = psIni->sScale4.dValue;
			}
			dropBt4->Enabled = false;
			dropBt4->BackColor = COL_YG;

			pauseBt4->Enabled = false;
			pauseBt4->BackColor = COL_TRANS;

			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'S';	// stop						 
			break;

		case S_ADD_WAIT:
			break;

		case S_ADD:
			fScaleVal4 = psIni->sScale4.dValue;
			if (psIni->bBotScale)
			{
				if (!psIni->bPdmPlc)
				{
					switch (psIni->sLog4.nSilo)
					{
					case 10: psIni->nWpoints |= P_DROP10; siloBar4->BarColor = COL_DISCH;  break;
					case 11: psIni->nWpoints |= P_DROP11; siloBar42->BarColor = COL_DISCH; break;
					case 12: psIni->nWpoints |= P_DROP12; siloBar43->BarColor = COL_DISCH; break;
					}
					scaleBar4->Target = pJob4->fLoad + psIni->sLog4.fTruckTare;
				}
				else
				{
					switch (psIni->sLog4.nSilo)
					{
					case 10: psIni->nWpoints |= psIni->asSilos[9].uDropO; siloBar4->BarColor = COL_DISCH; break;
					case 11: psIni->nWpoints |= psIni->asSilos[10].uDropO; siloBar42->BarColor = COL_DISCH; break;
					case 12: psIni->nWpoints |= psIni->asSilos[11].uDropO; siloBar43->BarColor = COL_DISCH; break;
					}
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;

					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn off Hold

					scaleBar4->Target = pJob4->fLoad + psIni->sLog4.fTruckTare;
				}
			}
			else
			{
				psIni->nWpoints |= O_DROP4;
				siloBar4->BarColor = COL_DISCH;
			}

			scaleBar4->BarColor = COL_CHARGE;
			addBt4->BackColor = COL_CHARGE;
			fTmpScale4 = psIni->sScale4.dValue;
			nTmpCnt4 = 0;

			pauseBt4->Enabled = true;			//DC 4.0.0
			pauseBt4->BackColor = COL_HOLDK;	//DC 4.0.0

			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'G';	// go					 
			break;

		case S_ASETTLE:
			if (psIni->bBotScale)
			{
				psIni->nWpoints &= ~P_CLRDRP_D;
				switch (psIni->sLog4.nSilo)
				{
				case 10: siloBar4->BarColor = COL_SETTLE;	break;
				case 11: siloBar42->BarColor = COL_SETTLE;	break;
				case 12: siloBar43->BarColor = COL_SETTLE;	break;
				}
			}
			else
			{
				psIni->nWpoints &= ~O_DROP4;
				siloBar4->BarColor = COL_SETTLE;
			}
			nTmpCnt4 = 0;
			addBt4->BackColor = COL_SETTLE;
			pauseBt4->Enabled = true;
			pauseBt4->BackColor = COL_HOLDK;

			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'S';	// stop						 
			break;

		case S_DISCH_WAIT:
			siloBar4->BarColor = COL_IDLE;
			dropBt4->BackColor = COL_TRANS;
			dischBt4->Enabled = true;
			dischBt4->BackColor = COL_PGREEN;
			dischBt4->Visible = !psIni->sInv.bAutoDisch4;
			pauseBt4->Enabled = false;
			pauseBt4->BackColor = COL_TRANS;
			break;

		case S_DISCH:
			psIni->nWpoints |= O_DISCH4;
			scaleBar4->BarColor = COL_DISCH;
			nSettle4 = 0;      // scale settle timout
			dropBt4->BackColor = COL_TRANS;
			dischBt4->Enabled = false;
			dischBt4->BackColor = COL_PGREEN;
			dischBt4->Visible = !psIni->sInv.bAutoDisch4;
			pauseBt4->Enabled = true;
			pauseBt4->BackColor = COL_HOLDK;
			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'L';	// leave					
			break;

		case S_DSETTLE:
			if (!psIni->bPdmPlc)
				psIni->nWpoints &= ~O_DISCH4;
			scaleBar4->BarColor = COL_SETTLE;
			pauseBt4->Enabled = false;
			pauseBt4->BackColor = COL_TRANS;
			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'P';	// pause					 										 
			break;

		case S_HOLD_ASETTLE:
		case S_HOLD_SETTLE:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					psIni->nWpoints &= ~P_CLRDRP_D;
					switch (psIni->sLog4.nSilo)
					{
					case 10: siloBar4->BarColor = COL_SETTLE;	break;
					case 11: siloBar42->BarColor = COL_SETTLE;	break;
					case 12: siloBar43->BarColor = COL_SETTLE;	break;
					}
				}
				else
				{
					psIni->nWpoints &= ~O_DROP4;
					siloBar4->BarColor = COL_SETTLE;
				}
			}
			else
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;

				psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn on Hold
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uDropO;	// turn off Drop
				switch (psIni->sLog4.nSilo)
				{
				case 10: siloBar4->BarColor = COL_SETTLE;	break;
				case 11: siloBar42->BarColor = COL_SETTLE;	break;
				case 12: siloBar43->BarColor = COL_SETTLE;	break;
				}
			}
			nTmpCnt4 = 0;
			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'P';	// pause						 
			break;

		case S_HOLD_DROP:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
				{
					switch (psIni->sLog4.nSilo)
					{
					case 10: siloBar4->BarColor = COL_HOLD;	break;
					case 11: siloBar42->BarColor = COL_HOLD;	break;
					case 12: siloBar43->BarColor = COL_HOLD;	break;
					}
				}
				else
				{
					siloBar4->BarColor = COL_HOLD;
				}
				dropBt4->Enabled = false;
				dropBt4->BackColor = COL_PGREEN;
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
				}
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1
				switch (psIni->sLog4.nSilo)
				{
				case 10: siloBar4->BarColor = COL_HOLD;		break;
				case 11: siloBar42->BarColor = COL_HOLD;	break;
				case 12: siloBar43->BarColor = COL_HOLD;	break;
				}
				dropBt4->Enabled = false;
				dropBt4->BackColor = COL_PGREEN;
				if (pAll->eAsType == A_SIM)
					psIni->sScale4.cGo = 'P';		// stop
			}
			break;

		case S_HOLD_ADD:	//DC 4.0.0
		case S_HOLD:
			if (!psIni->bSendBitWise)
			{
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
				psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
			}
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uDropO;	// turn off Drop //DC 4.0.1
			psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;	// turn off Hold //DC 4.0.1

			switch (psIni->sLog4.nSilo)
			{
			case 10: siloBar4->BarColor = COL_HOLD;		break;
			case 11: siloBar42->BarColor = COL_HOLD;	break;
			case 12: siloBar43->BarColor = COL_HOLD;	break;
			}
			dropBt4->Enabled = false;
			dropBt4->BackColor = COL_PGREEN;
			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'P';		// stop
			break;

		case S_HOLD_DISCH:
			if (!psIni->bPdmPlc)
				psIni->nWpoints &= ~O_DISCH4;
			scaleBar4->BarColor = COL_HOLD;
			dischBt4->Enabled = true;
			dischBt4->BackColor = COL_PGREEN;
			if (pAll->eAsType == A_SIM)
				psIni->sScale4.cGo = 'P';	// pause					 
			break;

		case S_UPDATE:
			if (!psIni->bPdmPlc)
			{
				psIni->nWpoints &= ~psIni->nReady4O;		//DC 3.2.0
				psIni->nWpoints &= ~psIni->nDrop4O;		//DC 3.2.0
				if (psIni->bSafeJob == false)
				{
					if (psIni->bBotScale)
						psIni->nWpoints &= ~P_CLRSV_D;
					else
						psIni->nWpoints &= ~O_SAFE4;
				}
			}
			else
			{
				if (!psIni->bSendBitWise)
				{
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
					psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
				}
				psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldO;		// turn on Hold		//DC 4.0.1
				psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uDoneO;		// turn on Done
			}
			break;

		case S_HORN:
			if (!psIni->bPdmPlc)
			{
				if (psIni->bBotScale)
					psIni->nWpoints |= P_LIGHTD;
				else
					psIni->nWpoints |= O_LIGHT4;
			}
			nTmpCnt4 = 0;
			break;
		}
	}
#pragma endregion

#pragma region TIMER_UTI
			 //----------------------------------------------------------------
	private: void updateFall(uint nSilo, uint nIdx, double fFall)
	{
		FALL *psF = psIni->sInv.asFall1;

		if ((nIdx >= LOAD_MAX) || (fFall < 0.0))
			return;

		switch (nSilo)
		{
		case 1: psF = &psIni->sInv.asFall1[nIdx]; break;
		case 2: psF = &psIni->sInv.asFall2[nIdx]; break;
		case 3: psF = &psIni->sInv.asFall3[nIdx]; break;
		case 4: psF = &psIni->sInv.asFall4[nIdx]; break;
		case 5: psF = &psIni->sInv.asFall5[nIdx]; break;
		case 6: psF = &psIni->sInv.asFall6[nIdx]; break;
		case 7: psF = &psIni->sInv.asFall7[nIdx]; break;
		case 8: psF = &psIni->sInv.asFall8[nIdx]; break;
		case 9: psF = &psIni->sInv.asFall9[nIdx]; break;
		case 10: psF = &psIni->sInv.asFall10[nIdx]; break;	//DC 3.3.0
		case 11: psF = &psIni->sInv.asFall11[nIdx]; break;
		case 12: psF = &psIni->sInv.asFall12[nIdx]; break;
		}

		psF->fFall -= psF->afFall[psF->nIdx];
		psF->fFall += fFall;
		psF->afFall[psF->nIdx] = fFall;
		psF->nIdx = ++psF->nIdx & (SAMPLE_NBR - 1);
	}

			 //----------------------------------------------------------------
	private: void updateAdapt(uint nSilo, uint nIdx, double fAdapt)
	{
		ADAPT *psA = psIni->sInv.asAdapt1;

		if ((nIdx >= LOAD_MAX) || (fAdapt < 0.0)) return;

		switch (nSilo)
		{
		case 1: psA = &psIni->sInv.asAdapt1[nIdx]; break;
		case 2: psA = &psIni->sInv.asAdapt2[nIdx]; break;
		case 3: psA = &psIni->sInv.asAdapt3[nIdx]; break;
		case 4: psA = &psIni->sInv.asAdapt4[nIdx]; break;
		case 5: psA = &psIni->sInv.asAdapt5[nIdx]; break;
		case 6: psA = &psIni->sInv.asAdapt6[nIdx]; break;
		case 7: psA = &psIni->sInv.asAdapt7[nIdx]; break;
		case 8: psA = &psIni->sInv.asAdapt8[nIdx]; break;
		case 9: psA = &psIni->sInv.asAdapt9[nIdx]; break;
		case 10: psA = &psIni->sInv.asAdapt10[nIdx]; break;		//DC 3.3.0
		case 11: psA = &psIni->sInv.asAdapt11[nIdx]; break;
		case 12: psA = &psIni->sInv.asAdapt12[nIdx]; break;
		}

		psA->fAdapt -= psA->afAdapt[psA->nIdx];
		psA->fAdapt += fAdapt;
		psA->afAdapt[psA->nIdx] = fAdapt;
		psA->nIdx = ++psA->nIdx & (SAMPLE_NBR - 1);
	}

			 //----------------------------------------------------------------
	private: double getAdapt(uint nSilo, uint nIdx)
	{
		ADAPT *psA = psIni->sInv.asAdapt1;

		if (nIdx >= LOAD_MAX)
			return(0);

		switch (nSilo)
		{
		case 1: psA = &psIni->sInv.asAdapt1[nIdx]; break;
		case 2: psA = &psIni->sInv.asAdapt2[nIdx]; break;
		case 3: psA = &psIni->sInv.asAdapt3[nIdx]; break;
		case 4: psA = &psIni->sInv.asAdapt4[nIdx]; break;
		case 5: psA = &psIni->sInv.asAdapt5[nIdx]; break;
		case 6: psA = &psIni->sInv.asAdapt6[nIdx]; break;
		case 7: psA = &psIni->sInv.asAdapt7[nIdx]; break;
		case 8: psA = &psIni->sInv.asAdapt8[nIdx]; break;
		case 9: psA = &psIni->sInv.asAdapt9[nIdx]; break;
		case 10: psA = &psIni->sInv.asAdapt10[nIdx]; break;
		case 11: psA = &psIni->sInv.asAdapt11[nIdx]; break;
		case 12: psA = &psIni->sInv.asAdapt12[nIdx]; break;
		}
		return(psA->fAdapt / SAMPLE_NBR);
	}

			 //----------------------------------------------------------------
	private: void showInv()
	{
		if (psIni->bBotScale)
		{
			siloBar1->Value = psIni->sInv.fInv1;
			siloBar1->Inventory = psIni->sInv.fInv1;
			siloBar12->Value = psIni->sInv.fInv2;
			siloBar12->Inventory = psIni->sInv.fInv2;
			siloBar13->Value = psIni->sInv.fInv3;
			siloBar13->Inventory = psIni->sInv.fInv3;

			if (bSecond)
			{
				siloBar2->Value = psIni->sInv.fInv4;
				siloBar2->Inventory = psIni->sInv.fInv4;
				siloBar22->Value = psIni->sInv.fInv5;
				siloBar22->Inventory = psIni->sInv.fInv5;
				siloBar23->Value = psIni->sInv.fInv6;
				siloBar23->Inventory = psIni->sInv.fInv6;
			}
			if (bThird)
			{
				siloBar3->Value = psIni->sInv.fInv7;
				siloBar3->Inventory = psIni->sInv.fInv7;
				siloBar32->Value = psIni->sInv.fInv8;
				siloBar32->Inventory = psIni->sInv.fInv8;
				siloBar33->Value = psIni->sInv.fInv9;
				siloBar33->Inventory = psIni->sInv.fInv9;
			}
			if (bForth)	//DC 3.3.0
			{
				siloBar4->Value = psIni->sInv.fInv10;
				siloBar4->Inventory = psIni->sInv.fInv10;
				siloBar42->Value = psIni->sInv.fInv11;
				siloBar42->Inventory = psIni->sInv.fInv11;
				siloBar43->Value = psIni->sInv.fInv12;
				siloBar43->Inventory = psIni->sInv.fInv12;
			}
		}
		else
		{
			siloBar1->Value = psIni->sInv.fInv1;
			siloBar1->Inventory = psIni->sInv.fInv1;
			if (bSecond)
			{
				siloBar2->Value = psIni->sInv.fInv2;
				siloBar2->Inventory = psIni->sInv.fInv2;
			}
			if (bThird)
			{
				siloBar3->Value = psIni->sInv.fInv3;
				siloBar3->Inventory = psIni->sInv.fInv3;
			}
			if (bForth)
			{
				siloBar4->Value = psIni->sInv.fInv4;
				siloBar4->Inventory = psIni->sInv.fInv4;
			}
		}
	}

			 //-------------------------------------------------------------------------
			 void addInv(int nSilo)
			 {
				 switch (nSilo)
				 {
				 case 1: psIni->sInv.fInv1 += psIni->fSiloFill1; break;
				 case 2: psIni->sInv.fInv2 += psIni->fSiloFill2; break;
				 case 3: psIni->sInv.fInv3 += psIni->fSiloFill3; break;
				 case 4: psIni->sInv.fInv4 += psIni->fSiloFill4; break;
				 case 5: psIni->sInv.fInv5 += psIni->fSiloFill5; break;
				 case 6: psIni->sInv.fInv6 += psIni->fSiloFill6; break;
				 case 7: psIni->sInv.fInv7 += psIni->fSiloFill7; break;
				 case 8: psIni->sInv.fInv8 += psIni->fSiloFill8; break;
				 case 9: psIni->sInv.fInv9 += psIni->fSiloFill9; break;
				 case 10: psIni->sInv.fInv10 += psIni->fSiloFill10; break;
				 case 11: psIni->sInv.fInv11 += psIni->fSiloFill11; break;
				 case 12: psIni->sInv.fInv12 += psIni->fSiloFill12; break;
				 }
				 showInv();						// show inventory  
			 }

			 //-------------------------------------------------------------------------
			 void subInv(int nLane)
			 {
				 double dSub;

				 if (psIni->bBotScale)
				 {
					 switch (nLane)
					 {
					 case 1:
						 dSub = psIni->sScale1.dValue - fScaleVal1;
						 if (!psIni->bDisableInv)
						 {
							 switch (psIni->sLog1.nSilo)
							 {
							 case 1: psIni->sInv.fInv1 -= dSub; break;
							 case 2: psIni->sInv.fInv2 -= dSub; break;
							 case 3: psIni->sInv.fInv3 -= dSub; break;
							 }
						 }
						 psIni->sInv.fTon1 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage1->Text = psIni->sInv.fTon1.ToString("F00");
						 else
							 tonnage1->Text = psIni->sInv.fTon1.ToString("F01");
						 break;

					 case 2:
						 dSub = psIni->sScale2.dValue - fScaleVal2;
						 if (!psIni->bDisableInv)
						 {
							 switch (psIni->sLog2.nSilo)
							 {
							 case 4: psIni->sInv.fInv4 -= dSub; break;
							 case 5: psIni->sInv.fInv5 -= dSub; break;
							 case 6: psIni->sInv.fInv6 -= dSub; break;
							 }
						 }
						 psIni->sInv.fTon2 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage2->Text = psIni->sInv.fTon2.ToString("F00");
						 else
							 tonnage2->Text = psIni->sInv.fTon2.ToString("F01");
						 break;

					 case 3:
						 dSub = psIni->sScale3.dValue - fScaleVal3;
						 if (!psIni->bDisableInv)
						 {
							 switch (psIni->sLog3.nSilo)
							 {
							 case 7: psIni->sInv.fInv7 -= dSub; break;
							 case 8: psIni->sInv.fInv8 -= dSub; break;
							 case 9: psIni->sInv.fInv9 -= dSub; break;
							 }
						 }
						 psIni->sInv.fTon3 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage3->Text = psIni->sInv.fTon3.ToString("F00");
						 else
							 tonnage3->Text = psIni->sInv.fTon3.ToString("F01");
						 break;

					 case 4:										//DC 3.3.0
						 dSub = psIni->sScale4.dValue - fScaleVal4;
						 if (!psIni->bDisableInv)
						 {
							 switch (psIni->sLog4.nSilo)
							 {
							 case 10: psIni->sInv.fInv10 -= dSub; break;
							 case 11: psIni->sInv.fInv11 -= dSub; break;
							 case 12: psIni->sInv.fInv12 -= dSub; break;
							 }
						 }
						 psIni->sInv.fTon4 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage4->Text = psIni->sInv.fTon4.ToString("F00");
						 else
							 tonnage4->Text = psIni->sInv.fTon4.ToString("F01");
						 break;
					 }
				 }
				 else
				 {
					 switch (nLane)
					 {
					 case 1:
						 dSub = psIni->sScale1.dValue - fScaleVal1;
						 psIni->sInv.fInv1 -= dSub;
						 psIni->sInv.fTon1 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage1->Text = psIni->sInv.fTon1.ToString("F00");
						 else
							 tonnage1->Text = psIni->sInv.fTon1.ToString("F01");
						 break;
					 case 2:
						 dSub = psIni->sScale2.dValue - fScaleVal2;
						 psIni->sInv.fInv2 -= dSub;
						 psIni->sInv.fTon2 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage2->Text = psIni->sInv.fTon2.ToString("F00");
						 else
							 tonnage2->Text = psIni->sInv.fTon2.ToString("F01");
						 break;
					 case 3:
						 dSub = psIni->sScale3.dValue - fScaleVal3;
						 psIni->sInv.fInv3 -= dSub;
						 psIni->sInv.fTon3 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage3->Text = psIni->sInv.fTon3.ToString("F00");
						 else
							 tonnage3->Text = psIni->sInv.fTon3.ToString("F01");
						 break;

					 case 4:										//DC 3.3.0
						 dSub = psIni->sScale4.dValue - fScaleVal4;
						 psIni->sInv.fInv4 -= dSub;
						 psIni->sInv.fTon4 += dSub;					// update tonnage
						 if (psIni->bScaleInLB)
							 tonnage4->Text = psIni->sInv.fTon4.ToString("F00");
						 else
							 tonnage4->Text = psIni->sInv.fTon4.ToString("F01");
						 break;
					 }
				 }
				 showInv();						// show inventory  
			 }

			 //-------------------------------------------------------------------------
			 static void str2arr(String^ pStr, char *pcArr)
			 {
				 int ii;

				 for (ii = 0; ii < pStr->Length; ii++)
					 pcArr[ii] = (char)pStr[ii];
				 pcArr[ii] = 0;
			 }
#pragma endregion

	private:
		//DC 4.0.0 Convert Max Target Weight to Scaled Value
		double TruckMax2ScaledValue(double nTargetMax)
		{
			double ScaledOutput = (nTargetMax - psIni->nTruckMin) / (psIni->nTruckMax - psIni->nTruckMin) * 20;
			return ScaledOutput;
		}

		//DC 4.0.0 Convert Max Cart Weight to Scaled Value
		double CartMax2ScaledValue(double nTargetMax)
		{
			double ScaledOutput = (nTargetMax - psIni->nCartMin) / (psIni->nCartMax - psIni->nCartMin) * 20;
			return ScaledOutput;
		}

		//DC 4.0.0 Convert Target (LBS) Decimal to Binary and IO 
		bool DecimalToBinaryIO(int n, int s)
		{
			int binaryNumber[19] = { 0 };
			int siloBinary[4] = { 0 };
			int  i = 0;
			int  z = 0;
			while (n>0)
			{
				binaryNumber[i] = n % 2;
				n = n / 2;
				i++;
			}
			while (s>0)
			{
				siloBinary[z] = s % 2;
				s = s / 2;
				z++;
			}
			for (int j = 0; j < 19; j++)
			{
				if (binaryNumber[j] > 0)
				{
					psIni->nWpoints |= psIni->uBitWiseO[j];			// turn on bit
					psIni->nBinaryNumber[j] = 1;
				}
				else
				{
					psIni->nWpoints &= ~psIni->uBitWiseO[j];		// turn off bit
					psIni->nBinaryNumber[j] = 0;
				}
			}
			for (int j = 0; j < 4; j++)
			{
				if (siloBinary[j] > 0)
				{
					psIni->nWpoints |= psIni->uSiloBitO[j];			// turn on bit
					psIni->nSiloBitNum[j] = 1;
				}
				else
				{
					psIni->nWpoints &= ~psIni->uSiloBitO[j];		// turn off bit
					psIni->nSiloBitNum[j] = 0;
				}
			}

			Thread::Sleep(500);

			for (int j = 0; j < 19; j++)
			{
				if (binaryNumber[j] > 0)
				{
					if (!((psIni->nRpoints & psIni->uBitCheckI[j]) > 0))
						return false;
				}
				else
				{
					if ((psIni->nRpoints & psIni->uBitCheckI[j]) > 0)
						return false;
				}
			}
			for (int j = 0; j < 4; j++)
			{
				if (siloBinary[j] > 0)
				{
					if (!((psIni->nRpoints & psIni->uSiloBitCheckI[j]) > 0))
						return false;
				}
				else
				{
					if ((psIni->nRpoints & psIni->uSiloBitCheckI[j]) > 0)
						return false;
				}
			}
			return true;
		}

		void resetTargetOutput()
		{
			for (int j = 0; j < 19; j++)
			{
				psIni->nWpoints &= ~psIni->uBitWiseO[j];		// turn off bit
				psIni->nBinaryNumber[j] = 0;
			}
			for (int j = 0; j < 4; j++)
			{
				psIni->nWpoints &= ~psIni->uSiloBitO[j];		// turn off bit
				psIni->nSiloBitNum[j] = 0;
			}
			psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
		}

		bool checkTargetIO()
		{
			for (int j = 0; j < 19; j++)
			{
				if (psIni->nBinaryNumber[j] > 0)
				{
					if (!((psIni->nRpoints & psIni->uBitCheckI[j]) > 0))
						return false;
				}
				else
				{
					if ((psIni->nRpoints & psIni->uBitCheckI[j]) > 0)
						return false;
				}
			}
			for (int j = 0; j < 4; j++)
			{
				if (psIni->nSiloBitNum[j] > 0)
				{
					if (!((psIni->nRpoints & psIni->uSiloBitCheckI[j]) > 0))
						return false;
				}
				else
				{
					if ((psIni->nRpoints & psIni->uSiloBitCheckI[j]) > 0)
						return false;
				}
			}
			return true;
		}

		void init(void)
		{
			nOffs1 = 12;		//DC 3.3.0
			groupBox4->Location = System::Drawing::Point(435, 27);
			this->Width = 1290;			//DC 3.2.6

			groupBox4->Visible = true;
			//zoom4->Visible = true;
			lite4->Visible = true;
			//webBrowser4->Visible = true;
			printerLb4->Visible = true;	//DC 4.0.0


										//System::Collections::Generic::Queue<CDbase^>^ qDbase;	//DC 4.0.2//Queue^ qDbase;
										//System::Collections::Generic::Queue<CDbase^>^ qDbaseBad;	//DC 4.0.2//Queue^ qDbase;

			siloBar4->Number = psIni->asSilos[9].nSiloNum;
			siloBar42->Number = psIni->asSilos[10].nSiloNum;
			siloBar43->Number = psIni->asSilos[11].nSiloNum;

			// plant 4 //DC 3.3.0 --------------------------------------------------------
			bForth = psIni->nNumLanes > 3;

			if (bForth)
			{
				if (pAll->eAsType == A_DEMO)
					psIni->sScale4.cGo = '0';			// idle

				groupBox4->Visible = bForth;

				if (psIni->bUseTrkMax)					//DC 3.2.0
					this->targetLb4->Text = L"TrkMax(TN)";

				numCopy4->Value = psIni->nTicketCopy4;			//DC 4.0.2

				if (psIni->bBotScale)
				{
					this->truckBar4->Location = System::Drawing::Point(nOffs1, BAR);
					this->truckPic4->Location = System::Drawing::Point(nOffs1, PIC);
					this->scaleBar4->Location = System::Drawing::Point(15, SCL);
					this->scaleBar4->Size = System::Drawing::Size(270, 58);
					psIni->sInv.bAutoDisch4 = true;

					siloBar4->Maximum = psIni->fSiloMax10;
					siloBar4->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar4->Inventory = psIni->sInv.fInv10;
					siloBar4->Value = psIni->sInv.fInv10;
					if (psIni->nL4SilosNum > 1)
					{
						siloBar42->Maximum = psIni->fSiloMax11;
						siloBar42->Visible = true;
						siloBar42->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar42->Inventory = psIni->fSiloMax11 > 0 ? psIni->sInv.fInv11 : 0;
						siloBar42->Enabled = psIni->fSiloMax11 > 0;
						//				siloBar32->Idle = psIni->fSiloMax8 == 0;
						siloBar42_Click(nullptr, nullptr);
					}
					if (psIni->nL4SilosNum > 2)
					{
						siloBar43->Maximum = psIni->fSiloMax12;
						siloBar43->Visible = true;
						siloBar43->DisableInv = psIni->bDisableInv;		//DC 4.0.1
						siloBar43->Inventory = psIni->fSiloMax12 > 0 ? psIni->sInv.fInv12 : 0;
						siloBar43->Enabled = psIni->fSiloMax12 > 0;
						//				siloBar33->Idle = psIni->fSiloMax9 == 0;
						siloBar43_Click(nullptr, nullptr);
					}

					scaleBar4->Maximum = psIni->fBotScaleMaxL4;		//DC 4.0.0
				}
				else
				{
					siloBar4->Text = "Silo 4";
					siloBar4->Maximum = psIni->fSiloMax4;
					siloBar4->DisableInv = psIni->bDisableInv;		//DC 4.0.1
					siloBar4->Inventory = psIni->sInv.fInv4;
					siloBar4->Value = psIni->sInv.fInv4;

					siloBar4->Size = System::Drawing::Size(100, 230);
					scaleBar4->Size = System::Drawing::Size(100, 52);
					truckBar4->Size = System::Drawing::Size(100, 28);
					scaleBar4->Maximum = psIni->fTopScaleMax;

					if (pAll->pCam4 != nullptr)
					{
						webBrowser4->Visible = true;
						webBrowser4->Navigate(pAll->pCam4);
					}
				}
				tonnage4->Text = psIni->sInv.fTon4.ToString("F01");
				siloBar4_Click(nullptr, nullptr);

				//			printTarget3->Checked = psIni->sInv.bPrintTarget3;
				autoFall4->Checked = psIni->sInv.bAutoFall4;
				adapt4->Checked = psIni->sInv.bAdapt4;
				jog4->Checked = psIni->sInv.bJog4;
				addBt4->Visible = !psIni->sInv.bJog4;
				autoDisch4->Visible = false;
				autoDisch4->Checked = false;
				dischBt4->Visible = false;
			}

			if (psIni->bPdmPlc)		//DC 4.0.0
			{
				this->siloBar1->Text = gcnew String(psIni->asSilos[0].acMat);
				this->siloBar12->Text = gcnew String(psIni->asSilos[1].acMat);
				this->siloBar13->Text = gcnew String(psIni->asSilos[2].acMat);
				this->siloBar2->Text = gcnew String(psIni->asSilos[3].acMat);
				this->siloBar22->Text = gcnew String(psIni->asSilos[4].acMat);
				this->siloBar23->Text = gcnew String(psIni->asSilos[5].acMat);
				this->siloBar3->Text = gcnew String(psIni->asSilos[6].acMat);
				this->siloBar32->Text = gcnew String(psIni->asSilos[7].acMat);
				this->siloBar33->Text = gcnew String(psIni->asSilos[8].acMat);
				this->siloBar4->Text = gcnew String(psIni->asSilos[9].acMat);
				this->siloBar42->Text = gcnew String(psIni->asSilos[10].acMat);
				this->siloBar43->Text = gcnew String(psIni->asSilos[11].acMat);

				this->prod01Lb->Visible = psIni->asSilos[0].bUsed;
				this->prod02Lb->Visible = psIni->asSilos[1].bUsed;
				this->prod03Lb->Visible = psIni->asSilos[2].bUsed;
				this->prod04Lb->Visible = psIni->asSilos[3].bUsed;
				this->prod05Lb->Visible = psIni->asSilos[4].bUsed;
				this->prod06Lb->Visible = psIni->asSilos[5].bUsed;
				this->prod07Lb->Visible = psIni->asSilos[6].bUsed;
				this->prod08Lb->Visible = psIni->asSilos[7].bUsed;
				this->prod09Lb->Visible = psIni->asSilos[8].bUsed;
				this->prod10Lb->Visible = psIni->asSilos[9].bUsed;
				this->prod11Lb->Visible = psIni->asSilos[10].bUsed;
				this->prod12Lb->Visible = psIni->asSilos[11].bUsed;

				this->prod01Lb->Text = gcnew String(psIni->asSilos[0].acProduct);
				this->prod02Lb->Text = gcnew String(psIni->asSilos[1].acProduct);
				this->prod03Lb->Text = gcnew String(psIni->asSilos[2].acProduct);
				this->prod04Lb->Text = gcnew String(psIni->asSilos[3].acProduct);
				this->prod05Lb->Text = gcnew String(psIni->asSilos[4].acProduct);
				this->prod06Lb->Text = gcnew String(psIni->asSilos[5].acProduct);
				this->prod07Lb->Text = gcnew String(psIni->asSilos[6].acProduct);
				this->prod08Lb->Text = gcnew String(psIni->asSilos[7].acProduct);
				this->prod09Lb->Text = gcnew String(psIni->asSilos[8].acProduct);
				this->prod10Lb->Text = gcnew String(psIni->asSilos[9].acProduct);
				this->prod11Lb->Text = gcnew String(psIni->asSilos[10].acProduct);
				this->prod12Lb->Text = gcnew String(psIni->asSilos[11].acProduct);

				this->printTarget1->Visible = false; this->printTarget2->Visible = false;
				this->printTarget3->Visible = false; this->printTarget4->Visible = false;
				this->taxExempt1->Visible = false; this->taxExempt2->Visible = false;
				this->taxExempt3->Visible = false; this->taxExempt4->Visible = false;
				this->autoFall1->Visible = false; this->autoFall2->Visible = false;
				this->autoFall3->Visible = false; this->autoFall4->Visible = false;
				this->adapt1->Visible = false; this->adapt2->Visible = false;
				this->adapt3->Visible = false; this->adapt4->Visible = false;
				this->jog1->Visible = false; this->jog2->Visible = false;
				this->jog3->Visible = false; this->jog4->Visible = false;
				this->autoBt1->Visible = false; this->autoBt2->Visible = false;
				this->autoBt3->Visible = false; this->autoBt4->Visible = false;
			}
		}

#pragma region TIMER
		//////////////////////////////////////////////////////////////////////////////
	private:
		System::Void timer1_Tick(System::Object^  sender, ElapsedEventArgs^  e)
		{
			Dbase^ pDbase;
			double fTarget;
			double fFall;
			int nPrinterA = 1;
			int nPrinterB = 2;
			int nPrinterC = 3;
			int nPrinterD = 4;
			int n2ndPrinterA = 5;	//DC 4.0.2
			int n2ndPrinterB = 6;	//DC 4.0.2
			int n2ndPrinterC = 7;	//DC 4.0.2
			int n2ndPrinterD = 8;	//DC 4.0.2
			if (laneACb2->Checked)
				nPrinterA = 2;
			else if (laneACb3->Checked)
				nPrinterA = 3;

			if (laneBCb1->Checked)
				nPrinterB = 1;
			else if (laneBCb3->Checked)
				nPrinterB = 3;

			if (laneCCb1->Checked)
				nPrinterC = 1;
			else if (laneCCb2->Checked)
				nPrinterC = 2;

			if (laneDCb1->Checked)		//DC 3.3.0
				nPrinterD = 1;
			else if (laneDCb2->Checked)
				nPrinterD = 2;

			if (pAll->eAsType == A_REMOTE && bRemLogin)
			{
				pictureSplash->Enabled = false;
				pictureSplash->Visible = false;
			}

			if (pAll->eAsType != A_REMOTE && pAll->pExc != nullptr)		//Dc 4.1.1
			{
				time_t rawtime;
				struct tm * timeinfo;
				struct stat st;

				time(&rawtime);
				timeinfo = localtime(&rawtime);

				char acFile[128];
				strcpy_s(acFile, 128, pAll->pcPath);
				strcat_s(acFile, 128, "\\Exception.log");

				if (stat(acFile, &st) == 0)
				{
					System::IO::File::AppendAllText(gcnew String(acFile), "\r\n" + gcnew String(asctime(timeinfo)) + ": " + pAll->pExc);
				}
				else
				{
					System::IO::File::WriteAllText(gcnew String(acFile), "Exception Log:");
					System::IO::File::AppendAllText(gcnew String(acFile), "\r\n" + gcnew String(asctime(timeinfo)) + ": " + pAll->pExc);
				}
				pAll->pExc = nullptr;
			}

			if (nOneSec > 0)
				nOneSec--;
			else
			{
				nOneSec = 10;

				// one sec task ------------------------------------------
				if (nSplash > 0 && pAll->eAsType != A_REMOTE)
				{
					if (nSplash == 1)
					{
						pictureSplash->Enabled = false;
						pictureSplash->Visible = false;
					}
					--nSplash;
				}
				else
				{
					//if(qDbaseBad->Count > 0)
					//	dbaseBadLb->Text = qDbaseBad->Count.ToString();
					//else
					dbaseBadLb->Text = nullptr;
				}
				if (pAll->eAsType != A_DEMO)
				{
					// scales health ----------------------------------------------
					if (pAll->eAsType != A_REMOTE)
					{
						if (pAll->psIni->sScale1.bSerTP)		//DC 3.2.6
						{
							tDiff = clock() - psIni->sScale1.tSample;
							psIni->sScale1.bSerial = (psIni->sScale1.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale1.nClock < psIni->nScaleRedHi)
								&& psIni->sScale1.bSample;
							psIni->sScale1.bSample = false;
							scaleBar1->BarColor = psIni->sScale1.bSerial ? COL_IDLE : COL_ERR;
						}
						else
						{
							psIni->sScale1.bSerial = (psIni->sScale1.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale1.nClock < psIni->nScaleRedHi)
								&& psIni->sScale1.bSample;
							psIni->sScale1.bSample = false;
							scaleBar1->BarColor = psIni->sScale1.bSerial ? COL_IDLE : COL_ERR;
						}
					}

					if (bSecond && pAll->eAsType != A_REMOTE)
					{
						if (pAll->psIni->sScale2.bSerTP)		//DC 3.2.6
						{
							tDiff = clock() - psIni->sScale2.tSample;
							psIni->sScale2.bSerial = (psIni->sScale2.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale2.nClock < psIni->nScaleRedHi)
								&& psIni->sScale2.bSample;
							psIni->sScale2.bSample = false;
							scaleBar2->BarColor = psIni->sScale2.bSerial ? COL_IDLE : COL_ERR;
						}
						else
						{
							psIni->sScale2.bSerial = (psIni->sScale2.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale2.nClock < psIni->nScaleRedHi)
								&& psIni->sScale2.bSample;
							psIni->sScale2.bSample = false;
							scaleBar2->BarColor = psIni->sScale2.bSerial ? COL_IDLE : COL_ERR;
						}
					}
					if (bThird && pAll->eAsType != A_REMOTE)
					{
						if (pAll->psIni->sScale3.bSerTP)		//DC 3.2.6
						{
							tDiff = clock() - psIni->sScale3.tSample;
							psIni->sScale3.bSerial = (psIni->sScale3.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale3.nClock < psIni->nScaleRedHi)
								&& psIni->sScale3.bSample;
							psIni->sScale3.bSample = false;
							scaleBar3->BarColor = psIni->sScale3.bSerial ? COL_IDLE : COL_ERR;
						}
						else
						{
							psIni->sScale3.bSerial = (psIni->sScale3.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale3.nClock < psIni->nScaleRedHi)
								&& psIni->sScale3.bSample;
							psIni->sScale3.bSample = false;
							scaleBar3->BarColor = psIni->sScale3.bSerial ? COL_IDLE : COL_ERR;
						}
					}

					if (bForth && psIni->bData)		//DC 3.3.0
					{
						if (pAll->psIni->sScale4.bSerTP)		//DC 3.2.6
						{
							tDiff = clock() - psIni->sScale4.tSample;
							psIni->sScale4.bSerial = (psIni->sScale4.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale4.nClock < psIni->nScaleRedHi)
								&& psIni->sScale4.bSample;
							psIni->sScale4.bSample = false;
							scaleBar4->BarColor = psIni->sScale4.bSerial ? COL_IDLE : COL_ERR;
						}
						else
						{
							psIni->sScale4.bSerial = (psIni->sScale4.nClock > psIni->nScaleRedLo)
								&& (psIni->sScale4.nClock < psIni->nScaleRedHi)
								&& psIni->sScale4.bSample;
							psIni->sScale4.bSample = false;
							scaleBar4->BarColor = psIni->sScale4.bSerial ? COL_IDLE : COL_ERR;
						}
					}
					else if (pAll->eAsType == A_REMOTE && !psIni->bData)
					{
						scaleBar4->BarColor = psIni->sScale4.bSerial ? COL_IDLE : COL_ERR;
					}
					// opto error -------------------------------------------------------------
					if (psIni->bTest)
						optoErr->Text = pAll->nOptoError.ToString();
				}
				//------------------------------------------------------------------------
				if (bShowInv)
				{
					bShowInv = false;
					showInv();
				}
				if (pAll->eAsType != A_REMOTE)
				{
					if (psIni->bSaveInv)
					{
						psIni->bSaveInv = false;
						if (fseek(pfInv, 0, SEEK_SET) == 0)
							fwrite(&psIni->sInv, sizeof(INV), 1, pfInv);
						showInv();
					}
				}

				if (psIni->bTest)
				{
					dbLb->Text = pAll->pDbCmd;
					dbLb1->Text = pAll->nTicket.ToString();
					if (psIni->bScaleInLB)	//DC 3.2.0
						dbLb2->Text = pAll->dSold.ToString("f00");
					else
						dbLb2->Text = pAll->dSold.ToString("f02");
				}
				if (pAll->bUlink)
					testBox->Text = pAll->pTestBox;
				if (pAll->bExcept)
					testBox->Text = pAll->pExc;
			}
			//////////////////////////////////////////////////////////////

			if (psIni->bTest)
			{
				int a = psIni->sLog1.eState;
				int b = psIni->sLog2.eState;
				int c = psIni->sLog3.eState;
				int d = psIni->sLog4.eState;

				rdLb->Text = psIni->nRpoints.ToString("x");
				wrLb->Text = psIni->nWpoints.ToString("x");
				double nTruckTarget1;
				double nTruckTarget2;
				if (target1->Text != "" && target2->Text != "")
				{
					nTruckTarget1 = Convert::ToDouble(target1->Text);
					nTruckTarget2 = Convert::ToDouble(target2->Text);
				}

				//				silo1->Text = nTmpCnt1.ToString();
				//				silo1->Text = bFirstDrop1.ToString();
				//				silo1->Text = psIni->sScale1.nClock.ToString();
				//				flow1->Text = a.ToString();
				//				silo1->Text = TruckMax2ScaledValue(nTruckTarget1).ToString();
				cnt1->Text = fNewTarget1.ToString();
				flow1->Text = TruckMax2ScaledValue(nTruckTarget1).ToString();

				//				cnt1->Text = nJogA.ToString();
				//				silo1->Text = fFall1.ToString("F2");
				//				flow1->Text = psIni->sScale1.bSerial.ToString();

				//				silo2->Text = nTmpCnt2.ToString();
				//				silo2->Text = TruckMax2ScaledValue(nTruckTarget2).ToString();
				//				flow2->Text = b.ToString();
				cnt2->Text = psIni->sScale2.nClock.ToString();
				//				silo2->Text = fFall2.ToString("F2");
				flow2->Text = CartMax2ScaledValue(nTruckTarget2).ToString();

				//				silo3->Text = nTmpCnt3.ToString();
				silo3->Text = psIni->sScale3.nClock.ToString();
				//				flow3->Text = c.ToString();
				cnt3->Text = nJogC.ToString();
				//				silo3->Text = fFall3.ToString("F2");
				flow3->Text = psIni->sScale3.bSerial.ToString();
				//DC 3.3.0
				if (pJob4 != nullptr)
				{
					silo4->Text = pJob4->stTruck;
					flow4->Text = pJob4->nTicket.ToString();
				}
				else
				{
					silo4->Text = "null";
					flow4->Text = "null";
				}

				//flow4->Text = fLoad4.ToString();

				cnt4->Text = nDelay4.ToString();

				lane1StatLB->Text = "S - " + a.ToString();
				lane2StatLB->Text = "S - " + b.ToString();
				lane3StatLB->Text = "S - " + c.ToString();
				lane4StatLB->Text = "S - " + d.ToString();
				if (target1->Text != "")// || target2->Text != "")
				{
					nTruckTarget1 = Convert::ToDouble(target1->Text);
					//					nTruckTarget2 = Convert::ToDouble(target2->Text);
					//	Scl_Out_EU = int( nTruckTarget);
					//	Scl_Out_EU = int(((nTruckTarget - MIN_WEIGHT)/(MAX_WEIGHT - MIN_WEIGHT))*(SCL_MAX - SCL_MIN) + SCL_MIN);
					//					switch(psIni->sLog1.nSilo)

					if (psIni->bSendBitWise && nTruckTarget1 >0)

					{
						DecimalToBinaryIO(int(truckBar1->Maximum * 2000), psIni->sLog1.nSilo);	//DC 4.0.0 send BitWise
					}
					{
						//						psIni->nSclOutEU[0] = nTruckTarget1;//TruckMax2ScaledValue(nTruckTarget1);
						//						psIni->nSclOutEU[1] = nTruckTarget2;//CartMax2ScaledValue(nTruckTarget2);
					}
				}


			}

			//DC 4.0.1 monitor keep alive output from PDM system
			if (psIni->bSendBitWise)
			{
				if ((psIni->nWpoints & psIni->uKeepAliveO) > 0 && nKeepAliveTimeOn > psIni->nKeepOnTime)
				{
					psIni->nWpoints &= ~psIni->uKeepAliveO;		//turn off keep alive
					nKeepAliveTimeOff = 0;
				}
				else if (nKeepAliveTimeOff > psIni->nKeepOffTime)
				{
					psIni->nWpoints |= psIni->uKeepAliveO;		//turn on keep alive
					nKeepAliveTimeOff = 0;
					nKeepAliveTimeOn = 0;
				}
				nKeepAliveTimeOn++;
				nKeepAliveTimeOff++;
			}

			resetBt1->Enabled = target1->Text != "";	//DC 4.0.5
			resetBt2->Enabled = target2->Text != "";	//DC 4.0.5
			resetBt3->Enabled = target3->Text != "";	//DC 4.0.5
			resetBt4->Enabled = target4->Text != "";	//DC 4.0.5

														//DC 4.1.2			if(pAll->eAsType == A_REMOTE)				//DC 4.1.1
														//DC 4.1.2				target4->Enabled = false;


														//DC 4.1.0 plant1 start -------------------------------------------
			if (pAll->eAsType != A_REMOTE)
			{
				if (psIni->sLog1.nCopy > 0)					//DC 4.0.3
					numCopy1->Value = psIni->sLog1.nCopy;
				else
					numCopy1->Value = numCopy1->Value;		//DC 4.0.4

				int nCopies = (int)numCopy1->Value;		//DC 4.0.2

														// plant 1 ///////////////////////////////////////////////////
				if (psIni->bPdmPlc && ((psIni->nRpoints & psIni->asSilos[psIni->sLog1.nSilo - 1].uHoldI) > 0 || !((psIni->nRpoints & psIni->uKeepAliveI) > 0))) //DC 4.0.1 //DC 4.0.0
					psIni->bHold1 = true;
				else
					psIni->bHold1 = false;

				switch (psIni->sLog1.eState)
				{
				case S_IDLE:
					nDelay1 = 0;		// reset delay timer
					fLoad1 = 0.0;
					truckBar1->Value = 0.0;
					truckBar1->Pct = 0;	//DC 4.0.0
					fTarget1 = 0;		//DC 4.0.0
					bStopAdd1 = false;	//DC 4.0.0
					if (!psIni->bTest && !psIni->bSendBitWise)
						psIni->nSclOutEU[0] = 0;		//DC 4.0.0 set analog output value to 0
					break;

				case S_NEXT:
					if (!((psIni->nWpoints & psIni->uSendTargetO) > 0) && ((psIni->nRpoints & psIni->uLaneTareI[0]) > 0))	//DC 4.0.1
					{
						bTruck1 = true;											//DC 4.0.1
						if (readyBt1->Enabled != true)							//DC 4.0.8
							psIni->sLog1.fTruckTare = psIni->sScale1.dValue;	//DC 4.0.1
						readyBt1->Enabled = true;
						readyBt1->BackColor = COL_PGREEN;
					}
					else
					{
						readyBt1->Enabled = false;
						readyBt1->BackColor = COL_TRANS;
					}
					break;

				case S_READY:
					if (!psIni->bSendBitWise)
						psIni->nSclOutEU[0] = truckBar1->Maximum;		//DC 4.0.0 set analog output value

					if (psIni->bBotScale)
						fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;

					if (psIni->bPdmPlc && !psIni->bSendBitWise && (psIni->nRpoints & psIni->asSilos[psIni->sLog1.nSilo - 1].uDropReadyI) > 0)
					{
						dropBt1->Enabled = true;
						dropBt1->BackColor = COL_PGREEN;
					}
					else if (psIni->bPdmPlc && psIni->bSendBitWise && (psIni->nRpoints & psIni->uReceivedTargetI) > 0)		//DC 4.0.1
					{
						dropBt1_Click(nullptr, nullptr);
						psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
						resetTargetOutput();							//DC 4.0.1
					}
					break;

					//=========================================================================
				case S_SAFE:
					if ((clock() - tSafeA) >= psIni->nSafeTime)
						setState1(S_DROP);
					break;

					//------------------------------------------------------------------------
				case S_DROP:
					if (testHold1()) return;			//DC 4.0.0
														// pulse drop button
					nBlink1 = ++nBlink1 & 3;
					if (nBlink1 > 1)
						dropBt1->BackColor = COL_GREEN;
					else
						dropBt1->BackColor = COL_PGREEN;

					if (psIni->sScale1.dValue == fTmpScale1)
					{
						nTmpCnt1++;
						if (nTmpCnt1 > psIni->nScaleIdle)
						{
							setState1(S_HOLD_SETTLE);
							MessageBox::Show("Scale is IDLE, lane put on HOLD", "Lane A",
								MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
						}
					}
					else
					{
						fTmpScale1 = psIni->sScale1.dValue;
						nTmpCnt1 = 0;
					}

					if (!psIni->bBotScale)
					{
						// adapt -----------------------------------------------------------------
						if (adapt1->Checked)
							fFall1 = getAdapt(1, (uint)psIni->sScale1.dValue);

						// final test
						if (psIni->sScale1.dValue > (fNewTarget1 - fFall1 - fTol1))
						{
							fCumTarget1 += fTarget1;
							setState1(S_SETTLE);
						}
					}
					else
					{
						fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;
						truckBar1->Value = fLoad1;
						truckBar1->Pct = (int)((fTarget1 - fLoad1) / fTarget1) * 100;	//DC 4.0.0

						if (!psIni->bPdmPlc)
						{
							// adapt 
							if (adapt1->Checked)
								fFall1 = getAdapt(psIni->sLog1.nSilo, (uint)fLoad1);

							// final test
							if (fLoad1 >= (fCumTarget1 - fFall1 - fTol1))
								setState1(S_SETTLE);
						}
						else if (!psIni->bSendTarget && !psIni->bSendBitWise)
						{
							//						 switch(psIni->sLog1.nSilo)
							{
								if (fTarget1 - fLoad1 >= fTarget1 * psIni->asSilos[psIni->sLog1.nSilo - 1].nFlowRatePct1 / 100)
								{
									psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget1 - fLoad1 >= fTarget1 * psIni->asSilos[psIni->sLog1.nSilo - 1].nFlowRatePct2 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget1 - fLoad1 >= fTarget1 * psIni->asSilos[psIni->sLog1.nSilo - 1].nFlowRatePct3 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
								}
								else
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
								}

								if (fLoad1 >= (fTarget1 - psIni->asSilos[psIni->sLog1.nSilo - 1].fFall - fTol1))
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
									setState1(S_SETTLE_PLC);
								}

								if (nDelay1 == 0 && psIni->asSilos[psIni->sLog1.nSilo - 1].nDelayPct > 0 && psIni->asSilos[psIni->sLog1.nSilo - 1].nDelayTime > 0)
								{
									if (fTarget1 - fLoad1 <= fTarget1 * psIni->asSilos[psIni->sLog1.nSilo - 1].nDelayPct / 100)
									{
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate1O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate2O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog1.nSilo - 1].uFlowRate3O;
										setState1(S_DELAY_PLC);
									}
								}

							}

						}
					}


					if (psIni->bPdmPlc && psIni->bSendBitWise)
					{
						//DC 4.0.0 wait for complete input from PDM
						if ((psIni->nRpoints & psIni->asSilos[psIni->sLog1.nSilo - 1].uDoneI) > 0)
							setState1(S_SETTLE_PLC);
						//else if (fLoad1 >= (fTarget1 + psIni->asSilos[psIni->sLog1.nSilo-1].dAddTol))
						//	setState1(S_HOLD_DROP);
					}
					break;

					// delay ------------------------------------------------------
				case S_DELAY_PLC:
					if (nDelay1 < psIni->asSilos[psIni->sLog1.nSilo - 1].nDelayTime * 10)
					{
						nDelay1++;
						switch (psIni->sLog1.nSilo)
						{
						case 1: siloBar1->Delay = true; siloBar1->Count = psIni->asSilos[psIni->sLog1.nSilo - 1].nDelayTime - nDelay1 / 10;	break;
						case 2: siloBar12->Delay = true; siloBar12->Count = psIni->asSilos[psIni->sLog1.nSilo - 1].nDelayTime - nDelay1 / 10;	break;
						case 3: siloBar13->Delay = true; siloBar13->Count = psIni->asSilos[psIni->sLog1.nSilo - 1].nDelayTime - nDelay1 / 10;	break;
						}
					}
					else
					{
						switch (psIni->sLog1.nSilo)
						{
						case 1: siloBar1->Delay = false; siloBar1->Count = 0;	break;
						case 2: siloBar12->Delay = false; siloBar12->Count = 0;	break;
						case 3: siloBar13->Delay = false; siloBar13->Count = 0;	break;
						}
						setState1(S_DROP);
					}
					break;

					//-------------------------------------------------------------
				case S_SETTLE_PLC:
					if (nSettle1 < psIni->nScaleSettle)
						nSettle1++;
					else
					{
						if (!psIni->bSendBitWise)
						{
							fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;
							truckBar1->Value = fLoad1;
							truckBar1->Pct = (int)((fTarget1 - fLoad1) / fTarget1) * 100;	//DC 4.0.0
							if (fLoad1 >= psIni->sLog1.sT.load_size - fTol1)
								setState1(S_UPDATE);
							/*else if(fLoad1 < psIni->sLog1.sT.load_size - fTol1)
							{
							setState1(S_DROP);
							}*/
							else
							{
								if (psIni->sInv.bJog1)
									//							setState1(S_ADD);	
									addBt1_Click(nullptr, nullptr);
								else
								{
									addBt1->BackColor = COL_CHARGE;
									addBt1->Enabled = true;
									setState1(S_ADD_WAIT);
								}
							}
						}
						else
							setState1(S_UPDATE);
					}
					break;

					//-------------------------------------------------------------
				case S_SETTLE:
					if (nSettle1 < psIni->nScaleSettle)
						nSettle1++;
					else
					{
						subInv(1);
						if (!psIni->bBotScale)					// upper scale
						{
							// update fall diff --------------------------------
							fFall = fFall1 + psIni->sScale1.dValue - fTarget1;
							updateFall(1, (uint)fTarget1, fFall);
							updateAdapt(1, (uint)fAdapt1, psIni->sScale1.dValue - fAdapt1);

							fLoad1 += psIni->sScale1.dValue;
							setState1(S_DISCH_WAIT);
						}
						else									// bottom scale
						{
							fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;
							truckBar1->Value = fLoad1;
							truckBar1->Pct = (int)((fTarget1 - fLoad1) / fTarget1) * 100;	//DC 4.0.0

																							// update fall diff --------------------------------
							fFall = fFall1 + fLoad1 - fCumTarget1;
							updateFall(psIni->sLog1.nSilo, (uint)fTarget1, fFall);
							updateAdapt(psIni->sLog1.nSilo, (uint)fAdapt1, fLoad1 - fAdapt1);

							if (fLoad1 >= psIni->sLog1.sT.load_size - fTol1)
								setState1(S_UPDATE);
							else if (fCumTarget1 < psIni->sLog1.sT.load_size)
							{
								setState1(S_READY);
							}
							else
							{
								if (psIni->sInv.bJog1)
									//								setState1(S_ADD);	
									addBt1_Click(nullptr, nullptr);
								else
								{
									addBt1->BackColor = COL_CHARGE;
									addBt1->Enabled = true;
									setState1(S_ADD_WAIT);
								}
							}
						}
					}
					break;

					//------------------------------------------------------------------------
				case S_ADD_WAIT:
					if (psIni->bAutoAdd && !bStopAdd1)
						addBt1_Click(nullptr, nullptr);
					break;

				case S_ADD:
					if (testHold1()) return;			//DC 4.0.0
					fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;	//DC 4.0.0
					truckBar1->Value = fLoad1;									//DC 4.0.0
					truckBar1->Pct = (int)((fTarget1 - fLoad1) / fTarget1) * 100;			//DC 4.0.0
					switch (psIni->sLog1.nSilo)
					{
					case 1: siloBar1->Add = true;	break;
					case 2: siloBar12->Add = true;	break;
					case 3: siloBar13->Add = true;	break;
					}
					if (nTmpCnt1 < nJogA)
						nTmpCnt1++;
					else
					{
						switch (psIni->sLog1.nSilo)
						{
						case 1: siloBar1->Add = false;	break;
						case 2: siloBar12->Add = false;	break;
						case 3: siloBar13->Add = false;	break;
						}
						if (psIni->bPdmPlc)
							setState1(S_SETTLE_PLC);
						else
							setState1(S_ASETTLE);
					}
					break;

				case S_ASETTLE:
					if (nTmpCnt1 < psIni->nScaleSettle)
						nTmpCnt1++;
					else
					{
						subInv(1);
						if (!psIni->bBotScale)					// upper scale
						{
							fLoad1 += psIni->sScale1.dValue - fTmpScale1;
							addBt1->Enabled = false;
						}
						setState1(S_DISCH_WAIT);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH_WAIT:
					if (!psIni->bBotScale)
					{
						if ((fCumTarget1 == psIni->sLog1.sT.load_size)
							&& (fLoad1 < (psIni->sLog1.sT.load_size - fTol1)))
						{
							if (psIni->sInv.bJog1)
								setState1(S_ADD);
							else
							{
								addBt1->BackColor = COL_CHARGE;
								addBt1->Enabled = true;
							}
						}
						else if (psIni->sInv.bAutoDisch1)
							setState1(S_DISCH);
					}
					else
					{
						fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;
						truckBar1->Value = fLoad1;
						truckBar1->Pct = (int)((fTarget1 - fLoad1) / fTarget1) * 100;	//DC 4.0.0

						if (fLoad1 < (fCumTarget1 - fTol1))
						{
							if (psIni->sInv.bJog1)
								setState1(S_ADD);
							else
							{
								addBt1->BackColor = COL_CHARGE;
								addBt1->Enabled = true;
							}
						}
						else
							setState1(S_UPDATE);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH:
					// pulse
					nBlink1 = ++nBlink1 & 3;
					if (nBlink1 > 1)
						dischBt1->BackColor = COL_GREEN;
					else
						dischBt1->BackColor = COL_PGREEN;

					addBt1->Enabled = false;
					truckBar1->Value = fLoad1 - psIni->sScale1.dValue;

					if (psIni->sScale1.dValue <= psIni->sScale1.fTolerance)
						setState1(S_DSETTLE);
					break;

				case S_DSETTLE:
					truckBar1->Value = fLoad1 - psIni->sScale1.dValue;

					if (nSettle1 > psIni->nScaleDisSettle)
					{
						if (psIni->sLog1.eStop != A_NOT)
							setState1(S_ABORT);
						else if (fCumTarget1 < psIni->sLog1.sT.load_size)
							setState1(S_READY);
						else
							setState1(S_UPDATE);
					}
					else
						nSettle1++;
					break;

					//------------------------------------------------------------------------
				case S_ABORT:
					if (!psIni->bBotScale)
						fLoad1 += psIni->sScale1.dValue;
					else
						fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;

					setState1(S_UPDATE);
					break;

				case S_UPDATE:
					subInv(1);
					psIni->sLog1.bPrintTarget = printTarget1->Checked || (psIni->sLog1.eStop == A_TARGET);

					if (psIni->sLog1.eStop == A_NOT)
					{
						psIni->sLog1.eJobStatus = S_OK1;
						pJob1->eStatus = S_OK1;
					}
					pJob1->fLoad = fLoad1;
					pJob1->nSilo = psIni->sLog1.nSilo;

					if (psIni->sLog1.bPrintTarget == true)
						fLoad1 = psIni->sLog1.sT.load_size;

					if (taxExempt1->Checked)
						psIni->sLog1.fTax = 0;

					psIni->sLog1.tTimeDone = DateTime::Now.ToBinary();
					psIni->sLog1.fLoad = fLoad1;
					psIni->sLog1.fGross = fLoad1 + psIni->sLog1.fTruckTare;
					psIni->sLog1.sT.subtotal = fLoad1 * psIni->sLog1.sT.mix_price;
					psIni->sLog1.fLoadTax = psIni->sLog1.sT.subtotal * psIni->sLog1.fTax;
					psIni->sLog1.fTotal = psIni->sLog1.sT.subtotal + psIni->sLog1.fLoadTax;

					fTarget = psIni->sLog1.sT.load_size * psIni->sLog1.sT.mix_price;
					fTarget += fTarget * psIni->sLog1.fTax;

					psIni->sLog1.sT.order_cum_total += (psIni->sLog1.fTotal - fTarget);
					psIni->sLog1.sT.cum_qty += psIni->sLog1.fLoad - psIni->sLog1.sT.load_size;

					// fuel surcharge
					psIni->sLog1.fTotal += fLoad1 * psIni->sLog1.sT.prods[0].price;
					psIni->bSaveInv = true;

					// dbase ---------------------------------------------
					if (bAuto1)
					{
						pDbase = gcnew Dbase();
						pDbase->nPlant = pJob1->nPlant;
						pDbase->nTicket = pJob1->nTicket;
						pDbase->fGross = psIni->sLog1.fGross;
						pDbase->fTare = psIni->sLog1.fTruckTare;
						pDbase->cUnit0 = psIni->sLog1.sT.unit[0];
						pDbase->cUnit1 = psIni->sLog1.sT.unit[1];
						pDbase->bVoid = (psIni->sLog1.eJobStatus == S_VOIDED);
						pDbase->pstCustCode = gcnew String(psIni->sLog1.sT.customer_code);
						pDbase->pstTruck = gcnew String(pJob1->stTruck);					//DC 4.1.1

																							//if(psIni->nDbaseOk > 0) 
																							//	pAll->qDbase->Enqueue(pDbase);
																							//else
																							//	pAll->qDbaseBad->Enqueue(pDbase);
					}

					// printer --------------------------------------------
					while (nCopies > 0)									//DC 4.0.2
					{
						poLog->printTicket(&psIni->sLog1, nPrinterA, false);
						nCopies--;
					}

					if (psIni->b2ndPrinterOk1 && laneA2ndCB->Checked)	//DC 4.0.2
						poLog->printTicket(&psIni->sLog1, n2ndPrinterA, false);

					poLog->log(C_UPDATE, &psIni->sLog1, pJob1->nLogIdx);

					// old job list
					pJob1->stStatus = pAll->lStat[pJob1->eStatus];
					pAll->lOld->Add(pJob1);
					pAll->nDone1++;

					if ((psIni->sLog1.eStop == A_TARGET)
						|| (psIni->sLog1.eStop == A_VOID)
						|| (psIni->nHornTime == 0))
						setState1(S_IDLE);
					else
						setState1(S_HORN);
					break;

				case S_HORN:
					if (nTmpCnt1 < psIni->nHornTime)
						++nTmpCnt1;
					else
						setState1(S_IDLE);
					break;

				case S_HOLD_SETTLE:
					if (nTmpCnt1 < psIni->nScaleSettle)
						nTmpCnt1++;
					else
					{
						subInv(1);
						setState1(S_HOLD_DROP);
					}
					break;

				case S_HOLD_DROP:
					//if(psIni->bSendTarget)		//DC 4.0.0
					//{
					//	if(bConDrop)
					//	{
					//		bConDrop = false;
					//		setState1(S_DROP);
					//		pauseBt1->BackColor = COL_HOLDK;
					//	}
					//}
				case S_HOLD_ASETTLE:
				case S_HOLD_DISCH:
				case S_HOLD_ADD:		//DC 4.0.0
					break;

				case S_HOLD:
					if (psIni->bHold1 == false)
					{
						pauseBt1->BackColor = COL_HOLDK;
						setState1(ePrevHold1);
					}
					break;

				default:							// PAUSE
					if (!psIni->bBotScale)
						fLoad1 = psIni->sScale1.dValue + fCumTarget1;
					else
						fLoad1 = psIni->sScale1.dValue - psIni->sLog1.fTruckTare;
					break;
				}

				//-----------------------------------------------------------inventory
				if (psIni->bBotScale && !psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if (psIni->bTickAddress)
					{
						if ((psIni->nRpoints & J_FILL1) > 0)
						{
							if (!bFill1)
							{
								bFill1 = true;

								if ((psIni->nRpoints & J_FILL9) > 0)
								{
									addInv(9);					// update silo 9
								}
								else if ((psIni->nRpoints & J_FILL8) > 0)
								{
									addInv(8);					// update silo 8
								}
								else if ((psIni->nRpoints & J_FILL7) > 0)
								{
									addInv(7);					// update silo 7
								}
								else if ((psIni->nRpoints & J_FILL6) > 0)
								{
									addInv(6);					// update silo 6
								}
								else if ((psIni->nRpoints & J_FILL5) > 0)
								{
									addInv(5);					// update silo 5
								}
								else if ((psIni->nRpoints & J_FILL4) > 0)
								{
									addInv(4);					// update silo 4
								}
								else if ((psIni->nRpoints & J_FILL3) > 0)
								{
									addInv(3);					// update silo 3
								}
								else if ((psIni->nRpoints & J_FILL2) > 0)
								{
									addInv(2);					// update silo 2
								}
								else
								{
									addInv(1);					// update silo 1
								}
							}
						}
						else
							bFill1 = false;
					}
					else
					{
						if ((psIni->nRpoints & J_FILL1) > 0)
						{
							if (!bFill1)
							{
								bFill1 = true;
								addInv(1);						// update silo
							}
						}
						else
							bFill1 = false;

						if ((psIni->nRpoints & J_FILL2) > 0)
						{
							if (!bFill2)
							{
								bFill2 = true;
								addInv(2);						// update silo
							}
						}
						else
							bFill2 = false;

						if ((psIni->nRpoints & J_FILL3) > 0)
						{
							if (!bFill3)
							{
								bFill3 = true;
								addInv(3);						// update silo
							}
						}
						else
							bFill3 = false;
					}
				}
				else if (!psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if ((psIni->nRpoints & I_FILL1) > 0)
					{
						if (!bFill1)
						{
							bFill1 = true;
							addInv(1);						// update Silo 1
						}
					}
					else
						bFill1 = false;
				}
				//------------------------------------------------------------
				scaleBar1->Value = psIni->sScale1.dValue;
				scaleBar1->Flow = psIni->sScale1.dFlow;

				ticketNum1->Text = pAll->nTickets1.ToString();
				man1->Text = pAll->nDone1.ToString();

				if (psIni->bBotScale)
				{
					if (!psIni->bSendTarget && !psIni->bSendBitWise)
					{
						if (psIni->bTickAddress)
						{
							fill1->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL2) == 0)
								&& ((psIni->nRpoints & J_FILL3) == 0)
								&& ((psIni->nRpoints & J_FILL4) == 0)
								&& ((psIni->nRpoints & J_FILL5) == 0)
								&& ((psIni->nRpoints & J_FILL6) == 0)
								&& ((psIni->nRpoints & J_FILL7) == 0)
								&& ((psIni->nRpoints & J_FILL8) == 0)
								&& ((psIni->nRpoints & J_FILL9) == 0);
							fill12->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL2) > 0);
							fill13->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL3) > 0);
						}
						else
						{
							fill1->Visible = (psIni->nRpoints & J_FILL1) > 0;
							fill12->Visible = (psIni->nRpoints & J_FILL2) > 0;
							fill13->Visible = (psIni->nRpoints & J_FILL3) > 0;
						}

						siloBar1->Open = (psIni->nWpoints & P_DROP1) > 0;
						siloBar12->Open = (psIni->nWpoints & P_DROP2) > 0;
						siloBar13->Open = (psIni->nWpoints & P_DROP3) > 0;
						lite1->Enabled = (psIni->nWpoints & P_LIGHTA) > 0;
						safe1->Visible = (psIni->nWpoints & P_SAFE1) > 0;
						safe2->Visible = (psIni->nWpoints & P_SAFE2) > 0;
						safe3->Visible = (psIni->nWpoints & P_SAFE3) > 0;
					}
					else
					{
						siloBar1->Open = (psIni->nWpoints & psIni->asSilos[0].uDropO) > 0;
						siloBar12->Open = (psIni->nWpoints & psIni->asSilos[1].uDropO) > 0;
						siloBar13->Open = (psIni->nWpoints & psIni->asSilos[2].uDropO) > 0;
					}

					if (pAll->eAsType == A_PROD)
						bTruck1 = psIni->sScale1.dValue > psIni->fBotScaleTruck;
				}
				else
				{
					fill1->Visible = (psIni->nRpoints & I_FILL1) > 0;
					siloBar1->Open = (psIni->nWpoints & O_DROP1) > 0;
					scaleBar1->Open = (psIni->nWpoints & O_DISCH1) > 0;
					lite1->Enabled = (psIni->nWpoints & O_LIGHT1) > 0;
					safe1->Visible = (psIni->nWpoints & O_SAFE1) > 0;
				}
				truckBar1->Visible = bTruck1;
				truckPic1->Visible = bTruck1;

				if (psIni->bTest)
				{
					scale1->Text = gcnew String((char *)psIni->sScale1.acData);
					//				cnt1->Text = psIni->sScale1.nClock.ToString();
				}
			}	//DC 4.1.0 plant1 End

				// plant 2 ///////////////////////////////////////////////////
			if (bSecond && pAll->eAsType != A_REMOTE)
			{
				if (psIni->sLog2.nCopy > 0)					//DC 4.0.3
					numCopy2->Value = psIni->sLog2.nCopy;
				else
					numCopy2->Value = numCopy2->Value;		//DC 4.0.4

				int nCopies2 = (int)numCopy2->Value;		//DC 4.0.2

				if (psIni->bPdmPlc && ((psIni->nRpoints & psIni->asSilos[psIni->sLog2.nSilo - 1].uHoldI) > 0 || !((psIni->nRpoints & psIni->uKeepAliveI) > 0))) //DC 4.0.1 //DC 4.0.0
					psIni->bHold2 = true;
				else
					psIni->bHold2 = false;

				switch (psIni->sLog2.eState)
				{
				case S_IDLE:
					nDelay2 = 0;		// reset delay timer
					fLoad2 = 0.0;
					truckBar2->Value = 0.0;
					truckBar2->Pct = 0;	//DC 4.0.0
					fTarget2 = 0;		//DC 4.0.0
					bStopAdd2 = false;	//DC 4.0.0
					if (!psIni->bTest && !psIni->bSendBitWise)
						psIni->nSclOutEU[1] = 0;		//DC 4.0.0 set analog output value to 0
					break;

				case S_NEXT:
					if (!((psIni->nWpoints & psIni->uSendTargetO) > 0) && ((psIni->nRpoints & psIni->uLaneTareI[1]) > 0))	//DC 4.0.1
					{
						bTruck2 = true;											//DC 4.0.1
						if (readyBt2->Enabled != true)							//DC 4.0.8
							psIni->sLog2.fTruckTare = psIni->sScale2.dValue;		//DC 4.0.1
						readyBt2->Enabled = true;
						readyBt2->BackColor = COL_PGREEN;
					}
					else
					{
						readyBt2->Enabled = false;
						readyBt2->BackColor = COL_TRANS;
					}
					break;

				case S_READY:
					if (!psIni->bSendBitWise)
						psIni->nSclOutEU[1] = truckBar2->Maximum;		//DC 4.0.0 set analog output value

					if (psIni->bBotScale)
						fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;

					if (psIni->bPdmPlc && !psIni->bSendBitWise && (psIni->nRpoints & psIni->asSilos[psIni->sLog2.nSilo - 1].uDropReadyI) > 0)
					{
						dropBt2->Enabled = true;
						dropBt2->BackColor = COL_PGREEN;
					}
					else if (psIni->bPdmPlc && psIni->bSendBitWise && (psIni->nRpoints & psIni->uReceivedTargetI) > 0)		//DC 4.0.1
					{
						dropBt2_Click(nullptr, nullptr);
						psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
						resetTargetOutput();							//DC 4.0.1
					}
					break;

					//=========================================================================
				case S_SAFE:
					if ((clock() - tSafeB) >= psIni->nSafeTime)
						setState2(S_DROP);
					break;

					//------------------------------------------------------------------------
				case S_DROP:
					if (testHold2()) return;			//DC 4.0.0
														// pulse
					nBlink2 = ++nBlink2 & 3;
					if (nBlink2 > 1)
						dropBt2->BackColor = COL_GREEN;
					else
						dropBt2->BackColor = COL_PGREEN;

					if (psIni->sScale2.dValue == fTmpScale2)
					{
						nTmpCnt2++;
						if (nTmpCnt2 > psIni->nScaleIdle)
						{
							setState2(S_HOLD_SETTLE);
							MessageBox::Show("Scale is IDLE, put on HOLD", "Lane B",
								System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
						}
					}
					else
					{
						fTmpScale2 = psIni->sScale2.dValue;
						nTmpCnt2 = 0;
					}

					if (!psIni->bBotScale)
					{
						// adapt --------------------------------------------------
						if (adapt2->Checked)
							fFall2 = getAdapt(2, (uint)psIni->sScale2.dValue);

						// final test
						if (psIni->sScale2.dValue > (fNewTarget2 - fFall2 - fTol2))
						{
							fCumTarget2 += fTarget2;
							setState2(S_SETTLE);
						}
					}
					else
					{
						fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;
						truckBar2->Value = fLoad2;
						truckBar2->Pct = (int)((fTarget2 - fLoad2) / fTarget2) * 100;	//DC 4.0.0

						if (!psIni->bPdmPlc)
						{
							// adapt
							if (adapt2->Checked)
								fFall2 = getAdapt(pJob2->nSilo, (uint)fLoad2);

							// final test
							if (fLoad2 >= (fCumTarget2 - fFall2 - fTol2))
								setState2(S_SETTLE);
						}
						else if (!psIni->bSendTarget && !psIni->bSendBitWise)
						{
							//						 switch(psIni->sLog1.nSilo)
							{
								if (fTarget2 - fLoad2 >= fTarget2 * psIni->asSilos[psIni->sLog2.nSilo - 1].nFlowRatePct1 / 100)
								{
									psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget2 - fLoad2 >= fTarget2 * psIni->asSilos[psIni->sLog2.nSilo - 1].nFlowRatePct2 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget2 - fLoad2 >= fTarget2 * psIni->asSilos[psIni->sLog2.nSilo - 1].nFlowRatePct3 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
								}
								else
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
								}

								if (fLoad2 >= (fTarget2 - psIni->asSilos[psIni->sLog2.nSilo - 1].fFall - fTol2))
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
									setState2(S_SETTLE_PLC);
								}

								if (nDelay2 == 0 && psIni->asSilos[psIni->sLog2.nSilo - 1].nDelayPct > 0 && psIni->asSilos[psIni->sLog2.nSilo - 1].nDelayTime > 0)
								{
									if (fTarget2 - fLoad2 <= fTarget2 * psIni->asSilos[psIni->sLog2.nSilo - 1].nDelayPct / 100)
									{
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate1O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate2O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog2.nSilo - 1].uFlowRate3O;
										setState2(S_DELAY_PLC);
									}
								}

							}

						}
					}

					if (psIni->bPdmPlc && psIni->bSendBitWise)
					{
						//DC 4.0.0 wait for complete input from PDM
						if ((psIni->nRpoints & psIni->asSilos[psIni->sLog2.nSilo - 1].uDoneI) > 0)
							setState2(S_SETTLE_PLC);
						//else if (fLoad1 >= (fTarget1 + psIni->asSilos[psIni->sLog1.nSilo-1].dAddTol))
						//	setState1(S_HOLD_DROP);
					}
					break;

					// delay ------------------------------------------------------
				case S_DELAY_PLC:
					if (nDelay2 < psIni->asSilos[psIni->sLog2.nSilo - 1].nDelayTime * 10)
					{
						nDelay2++;
						switch (psIni->sLog2.nSilo)
						{
						case 4: siloBar2->Delay = true; siloBar2->Count = psIni->asSilos[psIni->sLog2.nSilo - 1].nDelayTime - nDelay2 / 10;	break;
						case 5: siloBar22->Delay = true; siloBar22->Count = psIni->asSilos[psIni->sLog2.nSilo - 1].nDelayTime - nDelay2 / 10;	break;
						case 6: siloBar23->Delay = true; siloBar23->Count = psIni->asSilos[psIni->sLog2.nSilo - 1].nDelayTime - nDelay2 / 10;	break;
						}
					}
					else
					{
						switch (psIni->sLog2.nSilo)
						{
						case 4: siloBar2->Delay = false; siloBar2->Count = 0;	break;
						case 5: siloBar22->Delay = false; siloBar22->Count = 0;	break;
						case 6: siloBar23->Delay = false; siloBar23->Count = 0;	break;
						}
						setState2(S_DROP);
					}
					break;

					//-------------------------------------------------------------
				case S_SETTLE_PLC:
					if (nSettle2 < psIni->nScaleSettle)
						nSettle2++;
					else
					{
						if (!psIni->bSendBitWise)
						{
							fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;
							truckBar2->Value = fLoad2;
							truckBar2->Pct = (int)((fTarget2 - fLoad2) / fTarget2) * 100;	//DC 4.0.0
							if (fLoad2 >= psIni->sLog2.sT.load_size - fTol2)
								setState2(S_UPDATE);
							/*else if(fLoad1 < psIni->sLog1.sT.load_size - fTol1)
							{
							setState1(S_DROP);
							}*/
							else
							{
								if (psIni->sInv.bJog2)
									//							setState1(S_ADD);	
									addBt2_Click(nullptr, nullptr);
								else
								{
									addBt2->BackColor = COL_CHARGE;
									addBt2->Enabled = true;
									setState2(S_ADD_WAIT);
								}
							}
						}
						else
							setState2(S_UPDATE);
					}
					break;

					//------------------------------------------------------------------------
				case S_SETTLE:
					if (nSettle2 < psIni->nScaleSettle)
						nSettle2++;
					else
					{
						subInv(2);
						if (!psIni->bBotScale)
						{
							// update fall --------------------------------
							fFall = fFall2 + (psIni->sScale2.dValue - fTarget2);
							updateFall(2, (uint)fTarget2, fFall);
							updateAdapt(2, (uint)fAdapt2, psIni->sScale2.dValue - fAdapt2);

							fLoad2 += psIni->sScale2.dValue;
							setState2(S_DISCH_WAIT);
						}
						else
						{
							fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;
							truckBar2->Value = fLoad2;
							truckBar2->Pct = (int)((fTarget2 - fLoad2) / fTarget2) * 100;	//DC 4.0.0

																							// update fall diff --------------------------------
							fFall = fFall2 + fLoad2 - fCumTarget2;
							updateFall(pJob2->nSilo, (uint)fTarget2, fFall);
							updateAdapt(psIni->sLog2.nSilo, (uint)fAdapt2, fLoad2 - fAdapt2);

							if (fLoad2 >= psIni->sLog2.sT.load_size - fTol2)
								setState2(S_UPDATE);
							else if (fCumTarget2 < psIni->sLog2.sT.load_size)
							{
								setState2(S_READY);
							}
							else
							{
								if (psIni->sInv.bJog2)
									//									setState2(S_ADD);	
									addBt2_Click(nullptr, nullptr);
								else
								{
									addBt2->BackColor = COL_CHARGE;
									addBt2->Enabled = true;
									setState2(S_ADD_WAIT);
								}
							}
						}
					}
					break;

					//------------------------------------------------------------------------
				case S_ADD_WAIT:
					if (psIni->bAutoAdd && !bStopAdd2)
						addBt2_Click(nullptr, nullptr);
					break;

				case S_ADD:
					if (testHold2()) return;			//DC 4.0.0
					fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;	//DC 4.0.0
					truckBar2->Value = fLoad2;									//DC 4.0.0
					truckBar2->Pct = (int)((fTarget2 - fLoad2) / fTarget2) * 100;			//DC 4.0.0
					switch (psIni->sLog2.nSilo)
					{
					case 4: siloBar2->Add = true;	break;
					case 5: siloBar22->Add = true;	break;
					case 6: siloBar23->Add = true;	break;
					}
					if (nTmpCnt2 < nJogB)
						nTmpCnt2++;
					else
					{
						switch (psIni->sLog2.nSilo)
						{
						case 4: siloBar2->Add = false;	break;
						case 5: siloBar22->Add = false;	break;
						case 6: siloBar23->Add = false;	break;
						}
						if (psIni->bPdmPlc)
							setState2(S_SETTLE_PLC);
						else
							setState2(S_ASETTLE);
					}
					break;

				case S_ASETTLE:
					if (nTmpCnt2 < psIni->nScaleSettle)
						nTmpCnt2++;
					else
					{
						subInv(2);
						if (!psIni->bBotScale)					// upper scale
						{
							fLoad2 += psIni->sScale2.dValue - fTmpScale2;
							addBt2->Enabled = false;
						}
						setState2(S_DISCH_WAIT);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH_WAIT:
					if (!psIni->bBotScale)
					{
						if ((fCumTarget2 == psIni->sLog2.sT.load_size)
							&& (fLoad2 < (psIni->sLog2.sT.load_size - fTol2)))
						{
							if (psIni->sInv.bJog2)
								setState2(S_ADD);
							else
							{
								addBt2->BackColor = COL_CHARGE;
								addBt2->Enabled = true;
							}
						}
						else if (psIni->sInv.bAutoDisch2)
							setState2(S_DISCH);
					}
					else
					{
						fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;
						truckBar2->Value = fLoad2;
						truckBar2->Pct = (int)((fTarget2 - fLoad2) / fTarget2) * 100;	//DC 4.0.0

						if (fLoad2 < (fCumTarget2 - fTol2))
						{
							if (psIni->sInv.bJog2)
								setState2(S_ADD);
							else
							{
								addBt2->BackColor = COL_CHARGE;
								addBt2->Enabled = true;
							}
						}
						else
							setState2(S_UPDATE);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH:
					// pulse
					nBlink2 = ++nBlink2 & 3;
					if (nBlink2 > 1)
						dischBt2->BackColor = COL_GREEN;
					else
						dischBt2->BackColor = COL_PGREEN;

					addBt2->Enabled = false;
					truckBar2->Value = fLoad2 - psIni->sScale2.dValue;

					if (psIni->sScale2.dValue < psIni->sScale2.fTolerance)
						setState2(S_DSETTLE);
					break;

				case S_DSETTLE:
					truckBar2->Value = fLoad2 - psIni->sScale2.dValue;

					if (nSettle2 > psIni->nScaleDisSettle)
					{
						if (psIni->sLog2.eStop != A_NOT)
							setState2(S_ABORT);
						else if (fCumTarget2 < psIni->sLog2.sT.load_size)
							setState2(S_READY);
						else
							setState2(S_UPDATE);
					}
					else
						nSettle2++;
					break;

					//------------------------------------------------------------------------
				case S_ABORT:
					if (!psIni->bBotScale)
						fLoad2 += psIni->sScale2.dValue;
					else
						fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;

					setState2(S_UPDATE);
					break;

				case S_UPDATE:
					subInv(2);				//DC 4.0.3 update tonnage
					psIni->sLog2.bPrintTarget = printTarget2->Checked || (psIni->sLog2.eStop == A_TARGET);

					if (psIni->sLog2.eStop == A_NOT)
					{
						psIni->sLog2.eJobStatus = S_OK1;
						pJob2->eStatus = S_OK1;
					}
					pJob2->fLoad = fLoad2;
					pJob2->nSilo = psIni->sLog2.nSilo;

					if (psIni->sLog2.bPrintTarget == true)
						fLoad2 = psIni->sLog2.sT.load_size;

					if (taxExempt2->Checked)
						psIni->sLog2.fTax = 0;

					psIni->sLog2.tTimeDone = DateTime::Now.ToBinary();
					psIni->sLog2.fLoad = fLoad2;
					psIni->sLog2.fGross = fLoad2 + psIni->sLog2.fTruckTare;
					psIni->sLog2.sT.subtotal = fLoad2 * psIni->sLog2.sT.mix_price;
					psIni->sLog2.fLoadTax = psIni->sLog2.sT.subtotal * psIni->sLog2.fTax;
					psIni->sLog2.fTotal = psIni->sLog2.sT.subtotal + psIni->sLog2.fLoadTax;

					fTarget = psIni->sLog2.sT.load_size * psIni->sLog2.sT.mix_price;
					fTarget += fTarget * psIni->sLog2.fTax;

					psIni->sLog2.sT.order_cum_total += psIni->sLog2.fTotal - fTarget;
					psIni->sLog2.sT.cum_qty += psIni->sLog2.fLoad - psIni->sLog2.sT.load_size;

					// fuel surcharge
					psIni->sLog2.fTotal += fLoad2 * psIni->sLog2.sT.prods[0].price;
					psIni->bSaveInv = true;

					// dbase ---------------------------------------------
					if (bAuto2)
					{
						pDbase = gcnew Dbase();
						pDbase->nPlant = pJob2->nPlant;
						pDbase->nTicket = pJob2->nTicket;
						pDbase->fGross = psIni->sLog2.fGross;
						pDbase->fTare = psIni->sLog2.fTruckTare;
						pDbase->cUnit0 = psIni->sLog2.sT.unit[0];
						pDbase->cUnit1 = psIni->sLog2.sT.unit[1];
						pDbase->bVoid = (psIni->sLog2.eJobStatus == S_VOIDED);
						pDbase->pstCustCode = gcnew String(psIni->sLog2.sT.customer_code);
						pDbase->pstTruck = gcnew String(pJob2->stTruck);					//DC 4.1.1

						if (psIni->nDbaseOk > 0)
							pAll->qDbase->Enqueue(pDbase);
						else
							pAll->qDbaseBad->Enqueue(pDbase);
					}

					// printer --------------------------------------------
					while (nCopies2 > 0)									//DC 4.0.2
					{
						poLog->printTicket(&psIni->sLog2, nPrinterB, false);
						nCopies2--;
					}

					if (psIni->b2ndPrinterOk2 && laneB2ndCB->Checked)	//DC 4.0.2
						poLog->printTicket(&psIni->sLog2, n2ndPrinterB, false);

					poLog->log(C_UPDATE, &psIni->sLog2, pJob2->nLogIdx);

					// old job list
					pJob2->stStatus = pAll->lStat[pJob2->eStatus];
					pAll->lOld->Add(pJob2);
					pAll->nDone2++;

					if ((psIni->sLog2.eStop == A_TARGET)
						|| (psIni->sLog2.eStop == A_VOID)
						|| (psIni->nHornTime == 0))
						setState2(S_IDLE);
					else
						setState2(S_HORN);
					break;

				case S_HORN:
					if (nTmpCnt2 < psIni->nHornTime)
						++nTmpCnt2;
					else
						setState2(S_IDLE);
					break;

				case S_HOLD_SETTLE:
					if (nTmpCnt2 < psIni->nScaleSettle)
						nTmpCnt2++;
					else
					{
						subInv(2);
						setState2(S_HOLD_DROP);
					}
					break;

				case S_HOLD_DROP:
				case S_HOLD_DISCH:
				case S_HOLD_ADD:		//DC 4.0.0
					break;

				case S_HOLD:
					if (psIni->bHold2 == false)
					{
						pauseBt2->BackColor = COL_HOLDK;
						setState2(ePrevHold2);
					}
					break;

				default:
					if (!psIni->bBotScale)
						fLoad2 = psIni->sScale2.dValue + fCumTarget2;
					else
						fLoad2 = psIni->sScale2.dValue - psIni->sLog2.fTruckTare;
					break;
				}

				//-----------------------------------------------------------inventory
				if (psIni->bBotScale && !psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if (!psIni->bTickAddress)
					{
						if ((psIni->nRpoints & J_FILL4) > 0)
						{
							if (!bFill4)
							{
								bFill4 = true;
								addInv(4);					// update silo
							}
						}
						else
							bFill4 = false;
						if ((psIni->nRpoints & J_FILL5) > 0)
						{
							if (!bFill5)
							{
								bFill5 = true;
								addInv(5);						// update silo
							}
						}
						else
							bFill5 = false;
						if ((psIni->nRpoints & J_FILL6) > 0)
						{
							if (!bFill6)
							{
								bFill6 = true;
								addInv(6);						// update silo
							}
						}
						else
							bFill6 = false;
					}
				}
				else if (!psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if ((psIni->nRpoints & I_FILL2) > 0)
					{
						if (!bFill2)
						{
							bFill2 = true;
							addInv(2);						// update Silo 2
						}
					}
					else
						bFill2 = false;
				}
				//-------------------------------------------------------------------------
				scaleBar2->Value = psIni->sScale2.dValue;
				scaleBar2->Flow = psIni->sScale2.dFlow;

				ticketNum2->Text = pAll->nTickets2.ToString();
				man2->Text = pAll->nDone2.ToString();

				if (psIni->bBotScale)
				{
					if (!psIni->bSendTarget && !psIni->bSendBitWise)
					{
						if (psIni->bTickAddress)
						{
							fill2->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL4) > 0);
							fill22->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL5) > 0);
							fill23->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL6) > 0);
						}
						else
						{
							fill2->Visible = (psIni->nRpoints & J_FILL4) > 0;
							fill22->Visible = (psIni->nRpoints & J_FILL5) > 0;
							fill23->Visible = (psIni->nRpoints & J_FILL6) > 0;
						}
						siloBar2->Open = (psIni->nWpoints & P_DROP4) > 0;
						siloBar22->Open = (psIni->nWpoints & P_DROP5) > 0;
						siloBar23->Open = (psIni->nWpoints & P_DROP6) > 0;
						lite2->Enabled = (psIni->nWpoints & P_LIGHTB) > 0;
						safe4->Visible = (psIni->nWpoints & P_SAFE4) > 0;
						safe5->Visible = (psIni->nWpoints & P_SAFE5) > 0;
						safe6->Visible = (psIni->nWpoints & P_SAFE6) > 0;
					}
					else
					{
						siloBar2->Open = (psIni->nWpoints & psIni->asSilos[3].uDropO) > 0;
						siloBar22->Open = (psIni->nWpoints & psIni->asSilos[4].uDropO) > 0;
						siloBar23->Open = (psIni->nWpoints & psIni->asSilos[5].uDropO) > 0;
					}

					if (pAll->eAsType == A_PROD)
						bTruck2 = psIni->sScale2.dValue > psIni->fBotScaleTruck;
				}
				else
				{
					fill2->Visible = (psIni->nRpoints & I_FILL2) > 0;
					siloBar2->Open = (psIni->nWpoints & O_DROP2) > 0;
					scaleBar2->Open = (psIni->nWpoints & O_DISCH2) > 0;
					lite2->Enabled = (psIni->nWpoints & O_LIGHT2) > 0;
					safe4->Visible = (psIni->nWpoints & O_SAFE2) > 0;
				}
				truckBar2->Visible = bTruck2;
				truckPic2->Visible = bTruck2;

				if (psIni->bTest)
				{
					scale2->Text = gcnew String((char *)psIni->sScale2.acData);
					cnt2->Text = psIni->sScale2.nClock.ToString();
				}
			}

			// plant 3 ///////////////////////////////////////////////////
			if (bThird  && pAll->eAsType != A_REMOTE)
			{
				if (psIni->sLog3.nCopy > 0)					//DC 4.0.3
					numCopy3->Value = psIni->sLog3.nCopy;
				else
					numCopy3->Value = numCopy3->Value;		//DC 4.0.4

				int nCopies3 = (int)numCopy3->Value;		//DC 4.0.2

				if (psIni->bPdmPlc && ((psIni->nRpoints & psIni->asSilos[psIni->sLog3.nSilo - 1].uHoldI) > 0 || !((psIni->nRpoints & psIni->uKeepAliveI) > 0))) //DC 4.0.1 //DC 4.0.0
					psIni->bHold3 = true;
				else
					psIni->bHold3 = false;

				switch (psIni->sLog3.eState)
				{
				case S_IDLE:
					nDelay3 = 0;		// reset delay timer
					fLoad3 = 0.0;
					truckBar3->Value = 0;
					truckBar3->Pct = 0;	//DC 4.0.0
					fTarget3 = 0;		//DC 4.0.0
					bStopAdd3 = false;	//DC 4.0.0
					psIni->nSclOutEU[2] = 0;		//DC 4.0.0 set analog output value to 0
					break;

				case S_NEXT:
					if (!((psIni->nWpoints & psIni->uSendTargetO) > 0) && ((psIni->nRpoints & psIni->uLaneTareI[2]) > 0))	//DC 4.0.1
					{
						bTruck3 = true;											//DC 4.0.1
						if (readyBt3->Enabled != true)							//DC 4.0.8
							psIni->sLog3.fTruckTare = psIni->sScale3.dValue;		//DC 4.0.1
						readyBt3->Enabled = true;
						readyBt3->BackColor = COL_PGREEN;
					}
					else
					{
						readyBt3->Enabled = false;
						readyBt3->BackColor = COL_TRANS;
					}
					break;

				case S_READY:
					psIni->nSclOutEU[2] = truckBar3->Maximum;		//DC 4.0.0 set analog output value
					if (psIni->bBotScale)
						fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;
					if (psIni->bPdmPlc && !psIni->bSendBitWise && (psIni->nRpoints & psIni->asSilos[psIni->sLog3.nSilo - 1].uDropReadyI) > 0)
					{
						dropBt3->Enabled = true;
						dropBt3->BackColor = COL_PGREEN;
					}
					else if (psIni->bPdmPlc && psIni->bSendBitWise && (psIni->nRpoints & psIni->uReceivedTargetI) > 0)		//DC 4.0.1
					{
						dropBt3_Click(nullptr, nullptr);
						psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
						resetTargetOutput();							//DC 4.0.1
					}
					break;

					//=========================================================================
				case S_SAFE:
					if ((clock() - tSafeC) >= psIni->nSafeTime)
						setState3(S_DROP);
					break;

					//------------------------------------------------------------------------
				case S_DROP:
					if (testHold3()) return;			//DC 4.0.0
														// pulse
					nBlink3 = ++nBlink3 & 3;
					if (nBlink3 > 1)
						dropBt3->BackColor = COL_GREEN;
					else
						dropBt3->BackColor = COL_PGREEN;

					if (psIni->sScale3.dValue == fTmpScale3)
					{
						nTmpCnt3++;
						if (nTmpCnt3 > psIni->nScaleIdle)
						{
							setState3(S_HOLD_SETTLE);
							MessageBox::Show("Scale is IDLE, pause", "Lane C",
								System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
						}
					}
					else
					{
						fTmpScale3 = psIni->sScale3.dValue;
						nTmpCnt3 = 0;
					}

					if (!psIni->bBotScale)
					{
						// adapt --------------------------------------------------
						if (adapt3->Checked)
							fFall3 = getAdapt(3, (uint)psIni->sScale3.dValue);

						// final test
						if (psIni->sScale3.dValue > (fNewTarget3 - fFall3 - fTol3))
						{
							fCumTarget3 += fTarget3;
							setState3(S_SETTLE);
						}
					}
					else
					{
						fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;
						truckBar3->Value = fLoad3;
						truckBar3->Pct = (int)((fTarget3 - fLoad3) / fTarget3) * 100;	//DC 4.0.0

						if (!psIni->bPdmPlc)
						{
							// adapt --------------------------------------------------
							if (adapt3->Checked)
								fFall3 = getAdapt(psIni->sLog3.nSilo, (uint)(fLoad3));

							// final test
							if (fLoad3 >= (fCumTarget3 - fFall3 - fTol3))
								setState3(S_SETTLE);
						}
						else if (!psIni->bSendTarget && !psIni->bSendBitWise)
						{
							//						 switch(psIni->sLog1.nSilo)
							{
								if (fTarget3 - fLoad3 >= fTarget3 * psIni->asSilos[psIni->sLog3.nSilo - 1].nFlowRatePct1 / 100)
								{
									psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget3 - fLoad3 >= fTarget3 * psIni->asSilos[psIni->sLog3.nSilo - 1].nFlowRatePct2 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget3 - fLoad3 >= fTarget3 * psIni->asSilos[psIni->sLog3.nSilo - 1].nFlowRatePct3 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
								}
								else
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
								}

								if (fLoad3 >= (fTarget3 - psIni->asSilos[psIni->sLog3.nSilo - 1].fFall - fTol3))
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
									setState3(S_SETTLE_PLC);
								}

								if (nDelay3 == 0 && psIni->asSilos[psIni->sLog3.nSilo - 1].nDelayPct > 0 && psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayTime > 0)
								{
									if (fTarget3 - fLoad3 <= fTarget3 * psIni->asSilos[psIni->sLog3.nSilo - 1].nDelayPct / 100)
									{
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate1O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate2O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog3.nSilo - 1].uFlowRate3O;
										setState3(S_DELAY_PLC);
									}
								}

							}

						}
					}

					if (psIni->bPdmPlc && psIni->bSendBitWise)
					{
						//DC 4.0.0 wait for complete input from PDM
						if ((psIni->nRpoints & psIni->asSilos[psIni->sLog3.nSilo - 1].uDoneI) > 0)
							setState3(S_SETTLE_PLC);
						//else if (fLoad1 >= (fTarget1 + psIni->asSilos[psIni->sLog1.nSilo-1].dAddTol))
						//	setState1(S_HOLD_DROP);
					}
					break;

					// delay ------------------------------------------------------
				case S_DELAY_PLC:
					if (nDelay3 < psIni->asSilos[psIni->sLog3.nSilo - 1].nDelayTime * 10)
					{
						nDelay3++;
						switch (psIni->sLog3.nSilo)
						{
						case 10: siloBar3->Delay = true; siloBar3->Count = psIni->asSilos[psIni->sLog3.nSilo - 1].nDelayTime - nDelay3 / 10;	break;
						case 11: siloBar32->Delay = true; siloBar32->Count = psIni->asSilos[psIni->sLog3.nSilo - 1].nDelayTime - nDelay3 / 10;	break;
						case 12: siloBar33->Delay = true; siloBar33->Count = psIni->asSilos[psIni->sLog3.nSilo - 1].nDelayTime - nDelay3 / 10;	break;
						}
					}
					else
					{
						switch (psIni->sLog3.nSilo)
						{
						case 10: siloBar3->Delay = false; siloBar3->Count = 0;	break;
						case 11: siloBar32->Delay = false; siloBar32->Count = 0;	break;
						case 12: siloBar33->Delay = false; siloBar33->Count = 0;	break;
						}
						setState3(S_DROP);
					}
					break;

					//-------------------------------------------------------------
				case S_SETTLE_PLC:
					if (nSettle3 < psIni->nScaleSettle)
						nSettle3++;
					else
					{
						if (!psIni->bSendBitWise)
						{
							fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;
							truckBar3->Value = fLoad3;
							truckBar3->Pct = (int)((fTarget3 - fLoad3) / fTarget3) * 100;	//DC 4.0.0
							if (fLoad3 >= psIni->sLog3.sT.load_size - fTol3)
								setState3(S_UPDATE);
							/*else if(fLoad1 < psIni->sLog1.sT.load_size - fTol1)
							{
							setState1(S_DROP);
							}*/
							else
							{
								if (psIni->sInv.bJog3)
									//							setState1(S_ADD);	
									addBt3_Click(nullptr, nullptr);
								else
								{
									addBt3->BackColor = COL_CHARGE;
									addBt3->Enabled = true;
									setState3(S_ADD_WAIT);
								}
							}
						}
						else
							setState3(S_UPDATE);
					}
					break;

					//------------------------------------------------------------------------
				case S_SETTLE:
					if (nSettle3 < psIni->nScaleSettle)
						nSettle3++;
					else
					{
						subInv(3);
						if (!psIni->bBotScale)
						{
							// update fall --------------------------------
							fFall = fFall3 + (psIni->sScale3.dValue - fTarget3);
							updateFall(3, (uint)fTarget3, fFall);
							updateAdapt(3, (uint)fAdapt3, psIni->sScale3.dValue - fAdapt3);

							fLoad3 += psIni->sScale3.dValue;
							setState3(S_DISCH_WAIT);
						}
						else
						{
							fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;
							truckBar3->Value = fLoad3;
							truckBar3->Pct = (int)((fTarget3 - fLoad3) / fTarget3) * 100;	//DC 4.0.0

																							// update fall diff --------------------------------
							fFall = fFall3 + fLoad3 - fCumTarget3;
							updateFall(psIni->sLog3.nSilo, (uint)fTarget3, fFall);
							updateAdapt(psIni->sLog3.nSilo, (uint)fAdapt3, fLoad3 - fAdapt3);

							if (fLoad3 >= psIni->sLog3.sT.load_size - fTol3)
								setState3(S_UPDATE);
							else if (fCumTarget3 < psIni->sLog3.sT.load_size)
							{
								setState3(S_READY);
							}
							else
							{
								if (psIni->sInv.bJog3)
									//									setState3(S_ADD);	
									addBt3_Click(nullptr, nullptr);
								else
								{
									addBt3->BackColor = COL_CHARGE;
									addBt3->Enabled = true;
									setState3(S_ADD_WAIT);
								}
							}
						}
					}
					break;

					//------------------------------------------------------------------------
				case S_ADD_WAIT:
					if (psIni->bAutoAdd && !bStopAdd3)
						addBt3_Click(nullptr, nullptr);
					break;

				case S_ADD:
					if (testHold3()) return;			//DC 4.0.0
					fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;	//DC 4.0.0
					truckBar3->Value = fLoad3;									//DC 4.0.0
					truckBar3->Pct = (int)((fTarget3 - fLoad3) / fTarget3) * 100;			//DC 4.0.0
					switch (psIni->sLog3.nSilo)
					{
					case 7: siloBar3->Add = true;	break;
					case 8: siloBar32->Add = true;	break;
					case 9: siloBar33->Add = true;	break;
					}
					if (nTmpCnt3 < nJogC)
						nTmpCnt3++;
					else
					{
						switch (psIni->sLog3.nSilo)
						{
						case 7: siloBar3->Add = false;	break;
						case 8: siloBar32->Add = false;	break;
						case 9: siloBar33->Add = false;	break;
						}
						if (psIni->bPdmPlc)
							setState3(S_SETTLE_PLC);
						else
							setState3(S_ASETTLE);
					}
					break;

				case S_ASETTLE:
					if (nTmpCnt3 < psIni->nScaleSettle)
						nTmpCnt3++;
					else
					{
						subInv(3);
						if (!psIni->bBotScale)					// upper scale
						{
							fLoad3 += psIni->sScale3.dValue - fTmpScale3;
							addBt3->Enabled = false;
						}
						setState3(S_DISCH_WAIT);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH_WAIT:
					if (!psIni->bBotScale)
					{
						if ((fCumTarget3 == psIni->sLog3.sT.load_size)
							&& (fLoad3 < (psIni->sLog3.sT.load_size - fTol3)))
						{
							if (psIni->sInv.bJog3)
								setState3(S_ADD);
							else
							{
								addBt3->BackColor = COL_CHARGE;
								addBt3->Enabled = true;
							}
						}
						else if (psIni->sInv.bAutoDisch3)
							setState3(S_DISCH);
					}
					else
					{
						fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;
						truckBar3->Value = fLoad3;
						truckBar3->Pct = (int)((fTarget3 - fLoad3) / fTarget3) * 100;	//DC 4.0.0

						if (fLoad3 < fCumTarget3 - fTol3)
						{
							if (psIni->sInv.bJog3)
								setState3(S_ADD);
							else
							{
								addBt3->BackColor = COL_CHARGE;
								addBt3->Enabled = true;
							}
						}
						else
							setState3(S_UPDATE);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH:
					// pulse
					nBlink3 = ++nBlink3 & 3;
					if (nBlink3 > 1)
						dischBt3->BackColor = COL_GREEN;
					else
						dischBt3->BackColor = COL_PGREEN;

					addBt3->Enabled = false;
					truckBar3->Value = fLoad3 - psIni->sScale3.dValue;

					if (psIni->sScale3.dValue < psIni->sScale3.fTolerance)
						setState3(S_DSETTLE);
					break;

				case S_DSETTLE:
					truckBar3->Value = fLoad3 - psIni->sScale3.dValue;

					if (nSettle3 > psIni->nScaleDisSettle)
					{
						if (psIni->sLog3.eStop != A_NOT)
							setState3(S_ABORT);
						else if (fCumTarget3 < psIni->sLog3.sT.load_size)
							setState3(S_READY);
						else
							setState3(S_UPDATE);
					}
					else
						nSettle3++;
					break;

					//------------------------------------------------------------------------
				case S_ABORT:
					if (!psIni->bBotScale)
						fLoad3 += psIni->sScale3.dValue;
					else
						fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;

					setState3(S_UPDATE);
					break;

				case S_UPDATE:
					subInv(3);				//DC 4.0.3 update tonnage
					psIni->sLog3.bPrintTarget = printTarget3->Checked || (psIni->sLog3.eStop == A_TARGET);

					if (psIni->sLog3.eStop == A_NOT)
					{
						psIni->sLog3.eJobStatus = S_OK1;
						pJob3->eStatus = S_OK1;
					}
					pJob3->fLoad = fLoad3;
					pJob3->nSilo = psIni->sLog3.nSilo;

					if (psIni->sLog3.bPrintTarget == true)
						fLoad3 = psIni->sLog3.sT.load_size;

					if (taxExempt3->Checked)
						psIni->sLog3.fTax = 0;

					psIni->sLog3.tTimeDone = DateTime::Now.ToBinary();
					psIni->sLog3.fLoad = fLoad3;
					psIni->sLog3.fGross = fLoad3 + psIni->sLog3.fTruckTare;
					psIni->sLog3.sT.subtotal = fLoad3 * psIni->sLog3.sT.mix_price;
					psIni->sLog3.fLoadTax = psIni->sLog3.sT.subtotal * psIni->sLog3.fTax;
					psIni->sLog3.fTotal = psIni->sLog3.sT.subtotal + psIni->sLog3.fLoadTax;

					fTarget = psIni->sLog3.sT.load_size * psIni->sLog3.sT.mix_price;
					fTarget += fTarget * psIni->sLog3.fTax;

					psIni->sLog3.sT.order_cum_total += psIni->sLog3.fTotal - fTarget;
					psIni->sLog3.sT.cum_qty += psIni->sLog3.fLoad - psIni->sLog3.sT.load_size;

					// fuel surcharge
					psIni->sLog3.fTotal += fLoad3 * psIni->sLog3.sT.prods[0].price;
					psIni->bSaveInv = true;

					// dbase ---------------------------------------------
					if (bAuto3)
					{
						pDbase = gcnew Dbase();
						pDbase->nPlant = pJob3->nPlant;
						pDbase->nTicket = pJob3->nTicket;
						pDbase->fGross = psIni->sLog3.fGross;
						pDbase->fTare = psIni->sLog3.fTruckTare;
						pDbase->cUnit0 = psIni->sLog3.sT.unit[0];
						pDbase->cUnit1 = psIni->sLog3.sT.unit[1];
						pDbase->bVoid = (psIni->sLog3.eJobStatus == S_VOIDED);
						pDbase->pstCustCode = gcnew String(psIni->sLog3.sT.customer_code);
						pDbase->pstTruck = gcnew String(pJob3->stTruck);					//DC 4.1.1

						if (psIni->nDbaseOk > 0)
							pAll->qDbase->Enqueue(pDbase);
						else
							pAll->qDbaseBad->Enqueue(pDbase);
					}

					// printer --------------------------------------------
					while (nCopies3 > 0)									//DC 4.0.2
					{
						poLog->printTicket(&psIni->sLog3, nPrinterC, false);
						nCopies3--;
					}

					if (psIni->b2ndPrinterOk3 && laneC2ndCB->Checked)	//DC 4.0.2
						poLog->printTicket(&psIni->sLog3, n2ndPrinterC, false);

					poLog->log(C_UPDATE, &psIni->sLog3, pJob3->nLogIdx);

					// old job list
					pJob3->stStatus = pAll->lStat[pJob3->eStatus];
					pAll->lOld->Add(pJob3);
					pAll->nDone3++;

					if ((psIni->sLog3.eStop == A_TARGET)
						|| (psIni->sLog3.eStop == A_VOID)
						|| (psIni->nHornTime == 0))
						setState3(S_IDLE);
					else
						setState3(S_HORN);
					break;

				case S_HORN:
					if (nTmpCnt3 < psIni->nHornTime)
						++nTmpCnt3;
					else
						setState3(S_IDLE);
					break;

				case S_HOLD_SETTLE:
					if (nTmpCnt3 < psIni->nScaleSettle)
						nTmpCnt3++;
					else
					{
						subInv(3);
						setState3(S_HOLD_DROP);
					}
					break;

				case S_HOLD_DROP:
				case S_HOLD_DISCH:
				case S_HOLD_ADD:		//DC 4.0.0
					break;

				case S_HOLD:
					if (psIni->bHold3 == false)
					{
						pauseBt3->BackColor = COL_HOLDK;
						setState3(ePrevHold3);
					}
					break;

				default:
					if (!psIni->bBotScale)
						fLoad3 = psIni->sScale3.dValue + fCumTarget3;
					else
						fLoad3 = psIni->sScale3.dValue - psIni->sLog3.fTruckTare;
					break;
				}

				//-----------------------------------------------------------inventory
				if (psIni->bBotScale && !psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if (!psIni->bTickAddress)
					{
						if ((psIni->nRpoints & J_FILL7) > 0)
						{
							if (!bFill7)
							{
								bFill7 = true;
								addInv(7);					// update silo
							}
						}
						else
							bFill7 = false;
						if ((psIni->nRpoints & J_FILL8) > 0)
						{
							if (!bFill8)
							{
								bFill8 = true;
								addInv(8);						// update silo
							}
						}
						else
							bFill8 = false;
						if ((psIni->nRpoints & J_FILL9) > 0)
						{
							if (!bFill9)
							{
								bFill9 = true;
								addInv(9);						// update silo
							}
						}
						else
							bFill9 = false;
					}
				}
				else if (!psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if ((psIni->nRpoints & I_FILL3) > 0)
					{
						if (!bFill3)
						{
							bFill3 = true;
							addInv(3);						// update Silo 3
						}
					}
					else
						bFill3 = false;
				}
				//------------------------------------------------------------	
				scaleBar3->Value = psIni->sScale3.dValue;
				scaleBar3->Flow = psIni->sScale3.dFlow;

				ticketNum3->Text = pAll->nTickets3.ToString();
				man3->Text = pAll->nDone3.ToString();

				if (psIni->bBotScale)
				{
					if (!psIni->bSendTarget && !psIni->bSendBitWise)
					{
						if (psIni->bTickAddress)
						{
							fill3->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL7) > 0);
							fill32->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL8) > 0);
							fill33->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL9) > 0);
						}
						else
						{
							fill3->Visible = (psIni->nRpoints & J_FILL7) > 0;
							fill32->Visible = (psIni->nRpoints & J_FILL8) > 0;
							fill33->Visible = (psIni->nRpoints & J_FILL9) > 0;
						}
						siloBar3->Open = (psIni->nWpoints & P_DROP7) > 0;
						siloBar32->Open = (psIni->nWpoints & P_DROP8) > 0;
						siloBar33->Open = (psIni->nWpoints & P_DROP9) > 0;
						lite3->Enabled = (psIni->nWpoints & P_LIGHTC) > 0;
						safe7->Visible = (psIni->nWpoints & P_SAFE7) > 0;
						safe8->Visible = (psIni->nWpoints & P_SAFE8) > 0;
						safe9->Visible = (psIni->nWpoints & P_SAFE9) > 0;
					}
					else
					{
						siloBar3->Open = (psIni->nWpoints & psIni->asSilos[6].uDropO) > 0;
						siloBar32->Open = (psIni->nWpoints & psIni->asSilos[7].uDropO) > 0;
						siloBar33->Open = (psIni->nWpoints & psIni->asSilos[8].uDropO) > 0;
					}

					if (pAll->eAsType == A_PROD)
						bTruck3 = psIni->sScale3.dValue > psIni->fBotScaleTruck;
				}
				else
				{
					fill3->Visible = (psIni->nRpoints & I_FILL3) > 0;
					siloBar3->Open = (psIni->nWpoints & O_DROP3) > 0;
					scaleBar3->Open = (psIni->nWpoints & O_DISCH3) > 0;
					lite3->Enabled = (psIni->nWpoints & O_LIGHT3) > 0;
					safe7->Visible = (psIni->nWpoints & O_SAFE3) > 0;
				}
				truckBar3->Visible = bTruck3;
				truckPic3->Visible = bTruck3;

				if (psIni->bTest)
				{
					scale3->Text = gcnew String((char *)psIni->sScale3.acData);
					cnt3->Text = psIni->sScale3.nClock.ToString();
				}
			}

			// plant 4 //DC 3.3.0 /////////////////////////////////////////////////
			if (bForth)
			{
				if (psIni->sLog4.nCopy > 0)					//DC 4.0.3
					numCopy4->Value = psIni->sLog4.nCopy;
				else
					numCopy4->Value = numCopy4->Value;		//DC 4.0.4

				int nCopies4 = (int)numCopy4->Value;		//DC 4.0.2

				if (psIni->bPdmPlc && ((psIni->nRpoints & psIni->asSilos[psIni->sLog4.nSilo - 1].uHoldI) > 0 || !((psIni->nRpoints & psIni->uKeepAliveI) > 0))) //DC 4.0.1 //DC 4.0.0
					psIni->bHold4 = true;
				else
					psIni->bHold4 = false;

				if (pAll->eAsType == A_REMOTE && bRemLogin)				//DC 4.1.0
				{
					pAll->bIni = true;
					if (psIni->nTickets4 != nTicketsOld4)// || psIni->sLog4.eState == S_NEXT)
					{
						nTicketsOld4 = psIni->nTickets4;
						int k = 0;
						Cmd^ pCmd = gcnew Cmd();
						pCmd->cId = CL_JOB;
						pAll->qCmd->Enqueue(pCmd);

						pCmd = gcnew Cmd();
						pCmd->cId = CL_TRUCKS;
						pAll->qCmd->Enqueue(pCmd);

						while (1 > 0 && k++ < 5)
							Thread::Sleep(100);
					}
					//this->groupBox4->Refresh();
				}

				if (pAll->eAsType != A_REMOTE && pAll->nCservOk == 1)
				{
					this->groupBox4->BackColor = COL_DG;
					this->siloBar4->BackColor = COL_DG;
					this->scaleBar4->BackColor = COL_DG;
					this->remoteLb->Visible = true;
				}
				else if (pAll->eAsType == A_REMOTE && pAll->nClinkOk == 0)
				{
					this->groupBox4->BackColor = COL_R;
					this->siloBar4->BackColor = COL_R;
					this->scaleBar4->BackColor = COL_R;
					this->remoteLb->Text = L"DISCONNECTED";
					this->remoteLb->ForeColor = System::Drawing::Color::Black;
					this->remoteLb->Visible = true;
				}
				else if (pAll->eAsType == A_REMOTE && pAll->nClinkOk == 2)
				{
					if (nCounts > 100)
					{
						this->groupBox4->BackColor = COL_R;
						this->siloBar4->BackColor = COL_R;
						this->scaleBar4->BackColor = COL_R;
						this->remoteLb->Text = L"DISCONNECTED";
						this->remoteLb->ForeColor = System::Drawing::Color::Black;
						this->remoteLb->Visible = true;
					}
					nCounts++;
				}
				else
				{
					nCounts = 0;
					this->groupBox4->BackColor = COL_G;
					this->siloBar4->BackColor = COL_G;
					this->scaleBar4->BackColor = COL_G;
					this->remoteLb->Visible = false;
				}

				switch (psIni->sLog4.eState)
				{
				case S_IDLE:
					nDelay4 = 0;		// reset delay timer
					fLoad4 = 0.0;
					truckBar4->Value = 0;
					truckBar4->Pct = 0;	//DC 4.0.0
					fTarget4 = 0;		//DC 4.0.0
					bStopAdd4 = false;	//DC 4.0.0
										//if(pAll->eAsType != A_REMOTE)	//DC 4.1.0
										//	tonnage4->Text = psIni->sInv.fTon4.ToString("F01");

					tonnage4->Text = psIni->sInv.fTon4.ToString("F01");
					if (!psIni->bTest && !psIni->bSendBitWise)
						psIni->nSclOutEU[3] = 0;		//DC 4.0.0 set analog output value to 0
					if (pAll->eAsType == A_REMOTE && bRemLogin && target4->Text != "")
						setState4(S_IDLE);
					break;

				case S_NEXT:
					if (!((psIni->nWpoints & psIni->uSendTargetO) > 0) && ((psIni->nRpoints & psIni->uLaneTareI[3]) > 0))	//DC 4.0.1
					{
						bTruck4 = true;											//DC 4.0.1
						if (readyBt4->Enabled != true)							//DC 4.0.8
							psIni->sLog4.fTruckTare = psIni->sScale4.dValue;		//DC 4.0.1
						readyBt4->Enabled = true;
						readyBt4->BackColor = COL_PGREEN;
					}
					else
					{
						readyBt4->Enabled = false;
						readyBt4->BackColor = COL_TRANS;
					}
					if (pAll->eAsType == A_REMOTE && bRemLogin && target4->Text == "")				//DC 4.1.0
					{
						customer4->Text = gcnew String(psIni->sLog4.sT.customer_name_1);
						Job4->Text = gcnew String(psIni->sLog4.sT.project_code);
						material4->Text = gcnew String(psIni->sLog4.sT.mix_code);
						tic_num4->Text = psIni->sLog4.sT.ticket_num.ToString();
						truck4->Text = gcnew String(psIni->sLog4.sT.truck_id);
						if (psIni->bScaleInLB)	//DC 3.2.0
							target4->Text = psIni->sLog4.sT.load_size.ToString("F00");
						else
							target4->Text = psIni->sLog4.sT.load_size.ToString("F02");
						plant4->Text = psIni->sLog4.sT.plant_num.ToString();

						pJob4 = gcnew Job();
						pJob4->nLogIdx = poLog->log(C_APPEND, &psIni->sLog4, 0);
						pJob4->nTicket = psIni->sLog4.sT.ticket_num;
						pJob4->nSilo = psIni->sLog4.nSilo;
						pJob4->stCustomer = gcnew String(psIni->sLog4.sT.customer_name_1);
						pJob4->eStatus = psIni->sLog4.eJobStatus;
						pJob4->fLoad = Convert::ToDouble(target4->Text);
						scaleBar4->Target = pJob4->fLoad;
					}
					if (pAll->eAsType == A_REMOTE && bRemLogin && nextBt4->Enabled == true)
					{
						all4->Enabled = false;
						all4->BackColor = COL_TRANS;

						nextBt4->Enabled = false;
						nextBt4->BackColor = COL_TRANS;
					}
					if (pAll->eAsType == A_REMOTE && bRemLogin && target4->ReadOnly == true)
					{
						truck4->BackColor = COL_W;
						target4->BackColor = COL_W;
						target4->ReadOnly = false;		//DC 3.2.4
					}
					break;

				case S_READY:
					if (!psIni->bSendBitWise)
						psIni->nSclOutEU[3] = truckBar4->Maximum;		//DC 4.0.0 set analog output value

					if (psIni->bBotScale)
						fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;

					if (psIni->bPdmPlc && !psIni->bSendBitWise && (psIni->nRpoints & psIni->asSilos[psIni->sLog4.nSilo - 1].uDropReadyI) > 0)
					{
						dropBt4->Enabled = true;
						dropBt4->BackColor = COL_PGREEN;
					}
					else if (psIni->bPdmPlc && psIni->bSendBitWise && (psIni->nRpoints & psIni->uReceivedTargetI) > 0)		//DC 4.0.1
					{
						dropBt4_Click(nullptr, nullptr);
						psIni->nWpoints &= ~psIni->uSendTargetO;		//DC 4.0.1 turn off send target output
						resetTargetOutput();							//DC 4.0.1
					}
					if (pAll->eAsType == A_REMOTE && bRemLogin && fTarget4 == 0)				//DC 4.1.0
					{
						setDrops4(psIni->sLog4.nDrops);
					}

					if (pAll->eAsType == A_REMOTE && bRemLogin && readyBt4->Enabled == true)
					{
						readyBt4->Enabled = false;
						readyBt4->BackColor = COL_TRANS;

						printOnly4->Enabled = true;
						printOnly4->BackColor = COL_LB;

						truck4->BackColor = COL_G;
						target4->BackColor = COL_G;
						target4->ReadOnly = true;		//DC 3.2.4
					}
					break;

					//=========================================================================
				case S_SAFE:
					if ((clock() - tSafeD) >= psIni->nSafeTime)
						setState4(S_DROP);
					break;

					//------------------------------------------------------------------------
				case S_DROP:
					if (testHold4()) return;			//DC 4.0.0
														// pulse
					nBlink4 = ++nBlink4 & 3;

					if (nBlink4 > 1)
						dropBt4->BackColor = COL_GREEN;
					else
						dropBt4->BackColor = COL_PGREEN;

					if (psIni->sScale4.dValue == fTmpScale4)
					{
						nTmpCnt4++;
						if (nTmpCnt4 > psIni->nScaleIdle)
						{
							setState4(S_HOLD_SETTLE);
							MessageBox::Show("Scale is IDLE, pause", "Lane D",
								System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
						}
					}
					else
					{
						fTmpScale4 = psIni->sScale4.dValue;
						nTmpCnt4 = 0;
					}

					if (!psIni->bBotScale)
					{
						// adapt --------------------------------------------------
						if (adapt4->Checked)
							fFall4 = getAdapt(4, (uint)psIni->sScale4.dValue);

						// final test
						if (psIni->sScale4.dValue > (fNewTarget4 - fFall4 - fTol4))
						{
							fCumTarget4 += fTarget4;
							setState4(S_SETTLE);
						}
					}
					else
					{
						fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;
						truckBar4->Value = fLoad4;
						truckBar4->Pct = (int)((fTarget4 - fLoad4) / fTarget4) * 100;	//DC 4.0.0

						if (!psIni->bPdmPlc)
						{
							// adapt --------------------------------------------------
							if (adapt4->Checked)
								fFall4 = getAdapt(psIni->sLog4.nSilo, (uint)(fLoad4));

							// final test
							if (fLoad4 >= (fCumTarget4 - fFall4 - fTol4))
								setState4(S_SETTLE);
						}
						else if (!psIni->bSendTarget && !psIni->bSendBitWise)
						{
							//						 switch(psIni->sLog1.nSilo)
							{
								if (fTarget4 - fLoad4 >= fTarget4 * psIni->asSilos[psIni->sLog4.nSilo - 1].nFlowRatePct1 / 100)
								{
									psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget4 - fLoad4 >= fTarget4 * psIni->asSilos[psIni->sLog4.nSilo - 1].nFlowRatePct2 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
								}
								else if (fTarget4 - fLoad4 >= fTarget4 * psIni->asSilos[psIni->sLog4.nSilo - 1].nFlowRatePct3 / 100)
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
									psIni->nWpoints |= psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
								}
								else
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
								}

								if (fLoad4 >= (fTarget4 - psIni->asSilos[psIni->sLog4.nSilo - 1].fFall - fTol4))
								{
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
									psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
									setState4(S_SETTLE_PLC);
								}

								if (nDelay4 == 0 && psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayPct > 0 && psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayTime > 0)
								{
									if (fTarget4 - fLoad4 <= fTarget4 * psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayPct / 100)
									{
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate1O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate2O;
										psIni->nWpoints &= ~psIni->asSilos[psIni->sLog4.nSilo - 1].uFlowRate3O;
										setState4(S_DELAY_PLC);
									}
								}
							}

						}
					}
					if (psIni->bPdmPlc && psIni->bSendBitWise)
					{
						//DC 4.0.0 wait for complete input from PDM
						if ((psIni->nRpoints & psIni->asSilos[psIni->sLog4.nSilo - 1].uDoneI) > 0)
							setState4(S_SETTLE_PLC);
						//else if (fLoad1 >= (fTarget1 + psIni->asSilos[psIni->sLog1.nSilo-1].dAddTol))
						//	setState1(S_HOLD_DROP);
					}
					if (pAll->eAsType == A_REMOTE && bRemLogin && pauseBt4->Enabled == false)
					{
						printOnly4->Enabled = false;
						printOnly4->BackColor = COL_TRANS;

						dropBt4->Enabled = false;
						dropBt4->BackColor = COL_TRANS;

						pauseBt4->Enabled = true;
						pauseBt4->BackColor = COL_HOLDK;

						siloBar4->BarColor = COL_DISCH;
					}
					break;

					// delay ------------------------------------------------------
				case S_DELAY_PLC:
					if (nDelay4 < psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayTime * 10)
					{
						nDelay4++;
						switch (psIni->sLog4.nSilo)
						{
						case 10: siloBar4->Delay = true; siloBar4->Count = psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayTime - nDelay4 / 10;	break;
						case 11: siloBar42->Delay = true; siloBar42->Count = psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayTime - nDelay4 / 10;	break;
						case 12: siloBar43->Delay = true; siloBar43->Count = psIni->asSilos[psIni->sLog4.nSilo - 1].nDelayTime - nDelay4 / 10;	break;
						}
					}
					else
					{
						switch (psIni->sLog4.nSilo)
						{
						case 10: siloBar4->Delay = false; siloBar4->Count = 0;	break;
						case 11: siloBar42->Delay = false; siloBar42->Count = 0;	break;
						case 12: siloBar43->Delay = false; siloBar43->Count = 0;	break;
						}
						setState4(S_DROP);
					}
					break;

					//-------------------------------------------------------------
				case S_SETTLE_PLC:
					if (nSettle4 < psIni->nScaleSettle)
						nSettle4++;
					else
					{
						if (!psIni->bSendBitWise)
						{
							fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;
							truckBar4->Value = fLoad4;
							truckBar4->Pct = (int)((fTarget4 - fLoad4) / fTarget4) * 100;	//DC 4.0.0
							if (fLoad4 >= psIni->sLog4.sT.load_size - fTol4)
								setState4(S_UPDATE);
							/*else if(fLoad1 < psIni->sLog1.sT.load_size - fTol1)
							{
							setState1(S_DROP);
							}*/
							else
							{
								if (psIni->sInv.bJog4)
									//							setState1(S_ADD);	
									addBt4_Click(nullptr, nullptr);
								else
								{
									addBt4->BackColor = COL_CHARGE;
									addBt4->Enabled = true;
									setState4(S_ADD_WAIT);
								}
							}
						}
						else
							setState4(S_UPDATE);
					}
					if (pAll->eAsType == A_REMOTE && bRemLogin && siloBar4->BarColor == COL_DISCH)
					{
						siloBar4->BarColor = COL_SETTLE;
					}
					break;

					//------------------------------------------------------------------------
				case S_SETTLE:
					if (nSettle4 < psIni->nScaleSettle)
						nSettle4++;
					else
					{
						subInv(4);
						if (!psIni->bBotScale)
						{
							// update fall --------------------------------
							fFall = fFall4 + (psIni->sScale4.dValue - fTarget4);
							updateFall(4, (uint)fTarget4, fFall);
							updateAdapt(4, (uint)fAdapt4, psIni->sScale4.dValue - fAdapt4);

							fLoad4 += psIni->sScale4.dValue;
							setState4(S_DISCH_WAIT);
						}
						else
						{
							fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;
							truckBar4->Value = fLoad4;
							truckBar4->Pct = (int)((fTarget4 - fLoad4) / fTarget4) * 100;	//DC 4.0.0

																							// update fall diff --------------------------------
							fFall = fFall4 + fLoad4 - fCumTarget4;
							updateFall(psIni->sLog4.nSilo, (uint)fTarget4, fFall);
							updateAdapt(psIni->sLog4.nSilo, (uint)fAdapt4, fLoad4 - fAdapt4);

							if (fLoad4 >= psIni->sLog4.sT.load_size - fTol4)
								setState4(S_UPDATE);
							else if (fCumTarget4 < psIni->sLog4.sT.load_size)
							{
								setState4(S_READY);
							}
							else
							{
								if (psIni->sInv.bJog4)
									//									setState4(S_ADD);	
									addBt4_Click(nullptr, nullptr);
								else
								{
									addBt4->BackColor = COL_CHARGE;
									addBt4->Enabled = true;
									setState4(S_ADD_WAIT);
								}
							}
						}
					}
					break;

					//------------------------------------------------------------------------
				case S_ADD_WAIT:
					if (psIni->bAutoAdd && !bStopAdd4)
						addBt4_Click(nullptr, nullptr);
					break;

				case S_ADD:
					if (testHold4()) return;			//DC 4.0.0
					fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;	//DC 4.0.0
					truckBar4->Value = fLoad4;									//DC 4.0.0
					truckBar4->Pct = (int)((fTarget4 - fLoad4) / fTarget4) * 100;			//DC 4.0.0
					switch (psIni->sLog4.nSilo)
					{
					case 10: siloBar4->Add = true;	break;
					case 11: siloBar42->Add = true;	break;
					case 12: siloBar43->Add = true;	break;
					}
					if (nTmpCnt4 < nJogD)
						nTmpCnt4++;
					else
					{
						switch (psIni->sLog4.nSilo)
						{
						case 10: siloBar4->Add = false;		break;
						case 11: siloBar42->Add = false;	break;
						case 12: siloBar43->Add = false;	break;
						}
						if (psIni->bPdmPlc)
							setState4(S_SETTLE_PLC);
						else
							setState4(S_ASETTLE);
					}
					break;

				case S_ASETTLE:
					if (nTmpCnt4 < psIni->nScaleSettle)
						nTmpCnt4++;
					else
					{
						subInv(4);
						if (!psIni->bBotScale)					// upper scale
						{
							fLoad4 += psIni->sScale4.dValue - fTmpScale4;
							addBt4->Enabled = false;
						}
						setState4(S_DISCH_WAIT);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH_WAIT:
					if (!psIni->bBotScale)
					{
						if ((fCumTarget4 == psIni->sLog4.sT.load_size)
							&& (fLoad4 < (psIni->sLog4.sT.load_size - fTol4)))
						{
							if (psIni->sInv.bJog4)
								setState4(S_ADD);
							else
							{
								addBt4->BackColor = COL_CHARGE;
								addBt4->Enabled = true;
							}
						}
						else if (psIni->sInv.bAutoDisch4)
							setState4(S_DISCH);
					}
					else
					{
						fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;
						truckBar4->Value = fLoad4;
						truckBar4->Pct = (int)((fTarget4 - fLoad4) / fTarget4) * 100;	//DC 4.0.0

						if (fLoad4 < fCumTarget4 - fTol4)
						{
							if (psIni->sInv.bJog4)
								setState4(S_ADD);
							else
							{
								addBt4->BackColor = COL_CHARGE;
								addBt4->Enabled = true;
							}
						}
						else
							setState4(S_UPDATE);
					}
					break;

					//------------------------------------------------------------------------
				case S_DISCH:
					// pulse
					nBlink4 = ++nBlink4 & 3;
					if (nBlink4 > 1)
						dischBt4->BackColor = COL_GREEN;
					else
						dischBt4->BackColor = COL_PGREEN;

					addBt4->Enabled = false;
					truckBar4->Value = fLoad4 - psIni->sScale4.dValue;

					if (psIni->sScale4.dValue < psIni->sScale4.fTolerance)
						setState4(S_DSETTLE);
					break;

				case S_DSETTLE:
					truckBar4->Value = fLoad4 - psIni->sScale4.dValue;

					if (nSettle4 > psIni->nScaleDisSettle)
					{
						if (psIni->sLog4.eStop != A_NOT)
							setState4(S_ABORT);
						else if (fCumTarget4 < psIni->sLog4.sT.load_size)
							setState4(S_READY);
						else
							setState4(S_UPDATE);
					}
					else
						nSettle4++;
					break;

					//------------------------------------------------------------------------
				case S_ABORT:
					if (!psIni->bBotScale)
						fLoad4 += psIni->sScale4.dValue;
					else
						fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;

					setState4(S_UPDATE);
					break;

				case S_UPDATE:
					if (pAll->eAsType != A_REMOTE)	//DC 4.1.0
						subInv(4);					//DC 4.0.3 update tonnage

					if (pAll->eAsType != A_REMOTE)	//DC 4.1.0
					{
						psIni->sLog4.bPrintTarget = printTarget4->Checked || (psIni->sLog4.eStop == A_TARGET);

						if (psIni->sLog4.eStop == A_NOT)
						{
							psIni->sLog4.eJobStatus = S_OK1;
							pJob4->eStatus = S_OK1;
						}
						pJob4->fLoad = fLoad4;
						pJob4->nSilo = psIni->sLog4.nSilo;

						if (psIni->sLog4.bPrintTarget == true)
							fLoad4 = psIni->sLog4.sT.load_size;

						if (taxExempt4->Checked)
							psIni->sLog4.fTax = 0;

						psIni->sLog4.tTimeDone = DateTime::Now.ToBinary();
						psIni->sLog4.fLoad = fLoad4;
						psIni->sLog4.fGross = fLoad4 + psIni->sLog4.fTruckTare;
						psIni->sLog4.sT.subtotal = fLoad4 * psIni->sLog4.sT.mix_price;
						psIni->sLog4.fLoadTax = psIni->sLog4.sT.subtotal * psIni->sLog4.fTax;
						psIni->sLog4.fTotal = psIni->sLog4.sT.subtotal + psIni->sLog4.fLoadTax;

						fTarget = psIni->sLog4.sT.load_size * psIni->sLog4.sT.mix_price;
						fTarget += fTarget * psIni->sLog4.fTax;

						psIni->sLog4.sT.order_cum_total += psIni->sLog4.fTotal - fTarget;
						psIni->sLog4.sT.cum_qty += psIni->sLog4.fLoad - psIni->sLog4.sT.load_size;

						// fuel surcharge
						psIni->sLog4.fTotal += fLoad4 * psIni->sLog4.sT.prods[0].price;
						psIni->bSaveInv = true;

						// dbase ---------------------------------------------
						if (bAuto4)
						{
							pDbase = gcnew Dbase();
							pDbase->nPlant = pJob4->nPlant;
							pDbase->nTicket = pJob4->nTicket;
							pDbase->fGross = psIni->sLog4.fGross;
							pDbase->fTare = psIni->sLog4.fTruckTare;
							pDbase->cUnit0 = psIni->sLog4.sT.unit[0];
							pDbase->cUnit1 = psIni->sLog4.sT.unit[1];
							pDbase->bVoid = (psIni->sLog4.eJobStatus == S_VOIDED);
							pDbase->pstCustCode = gcnew String(psIni->sLog4.sT.customer_code);
							pDbase->pstTruck = gcnew String(pJob4->stTruck);					//DC 4.1.1

																								//if(psIni->nDbaseOk > 0)  SRW
																								//	qDbase->Enqueue(pDbase);
																								//else
																								//	qDbaseBad->Enqueue(pDbase);
						}


						// printer --------------------------------------------
						while (nCopies4 > 0)									//DC 4.0.2
						{
							poLog->printTicket(&psIni->sLog4, nPrinterD, false);
							nCopies4--;
						}

						if (psIni->b2ndPrinterOk4 && laneD2ndCB->Checked)	//DC 4.0.2
							poLog->printTicket(&psIni->sLog4, n2ndPrinterD, false);

						poLog->log(C_UPDATE, &psIni->sLog4, pJob4->nLogIdx);


						// old job list
						pJob4->stStatus = pAll->lStat[pJob4->eStatus];
						pAll->lOld->Add(pJob4);

						psIni->nOldDone4++;
					}

					if ((psIni->sLog4.eStop == A_TARGET)
						|| (psIni->sLog4.eStop == A_VOID)
						|| (psIni->nHornTime == 0))
						setState4(S_IDLE);
					else
						setState4(S_HORN);
					break;

				case S_HORN:
					if (nTmpCnt4 < psIni->nHornTime)
						++nTmpCnt4;
					else
						setState4(S_IDLE);
					break;

				case S_HOLD_SETTLE:
					if (nTmpCnt4 < psIni->nScaleSettle)
						nTmpCnt4++;
					else
					{
						subInv(4);
						setState4(S_HOLD_DROP);
					}
					break;

				case S_HOLD_DROP:
				case S_HOLD_DISCH:
				case S_HOLD_ADD:		//DC 4.0.0
					break;

				case S_HOLD:
					if (psIni->bHold4 == false)
					{
						pauseBt4->BackColor = COL_HOLDK;
						setState4(ePrevHold4);
					}
					break;

				default:
					if (!psIni->bBotScale)
						fLoad4 = psIni->sScale4.dValue + fCumTarget4;
					else
						fLoad4 = psIni->sScale4.dValue - psIni->sLog4.fTruckTare;
					break;
				}

				//-----------------------------------------------------------inventory
				if (psIni->bBotScale && !psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if (!psIni->bTickAddress)
					{
						if ((psIni->nRpoints & J_FILL10) > 0)
						{
							if (!bFill10)
							{
								bFill10 = true;
								addInv(10);					// update silo
							}
						}
						else
							bFill10 = false;
						if ((psIni->nRpoints & J_FILL11) > 0)
						{
							if (!bFill11)
							{
								bFill11 = true;
								addInv(11);						// update silo
							}
						}
						else
							bFill11 = false;
						if ((psIni->nRpoints & J_FILL12) > 0)
						{
							if (!bFill12)
							{
								bFill12 = true;
								addInv(12);						// update silo
							}
						}
						else
							bFill12 = false;
					}
				}
				else if (!psIni->bSendTarget && !psIni->bSendBitWise)
				{
					if ((psIni->nRpoints & I_FILL4) > 0)
					{
						if (!bFill4)
						{
							bFill4 = true;
							addInv(4);						// update Silo 4
						}
					}
					else
						bFill4 = false;
				}
				//------------------------------------------------------------	
				scaleBar4->Value = psIni->sScale4.dValue;
				scaleBar4->Flow = psIni->sScale4.dFlow;

				ticketNum4->Text = psIni->nTickets4.ToString();
				man4->Text = psIni->nOldDone4.ToString();

				if (psIni->bBotScale)
				{
					if (!psIni->bSendTarget && !psIni->bSendBitWise)
					{
						if (psIni->bTickAddress)
						{
							fill4->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL10) > 0);
							fill42->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL11) > 0);
							fill43->Visible = ((psIni->nRpoints & J_FILL1) > 0)
								&& ((psIni->nRpoints & J_FILL12) > 0);
						}
						else
						{
							fill4->Visible = (psIni->nRpoints & J_FILL10) > 0;
							fill42->Visible = (psIni->nRpoints & J_FILL11) > 0;
							fill43->Visible = (psIni->nRpoints & J_FILL12) > 0;
						}
						siloBar4->Open = (psIni->nWpoints & P_DROP10) > 0;
						siloBar42->Open = (psIni->nWpoints & P_DROP11) > 0;
						siloBar43->Open = (psIni->nWpoints & P_DROP12) > 0;
						lite4->Enabled = (psIni->nWpoints & P_LIGHTD) > 0;
						safe10->Visible = (psIni->nWpoints & P_SAFE10) > 0;
						safe11->Visible = (psIni->nWpoints & P_SAFE11) > 0;
						safe12->Visible = (psIni->nWpoints & P_SAFE12) > 0;
					}
					else
					{
						siloBar4->Open = (psIni->nWpoints & psIni->asSilos[9].uDropO) > 0;
						siloBar42->Open = (psIni->nWpoints & psIni->asSilos[10].uDropO) > 0;
						siloBar43->Open = (psIni->nWpoints & psIni->asSilos[11].uDropO) > 0;
					}

					if (pAll->eAsType == A_PROD || (pAll->eAsType == A_REMOTE && psIni->bData))
						bTruck4 = psIni->sScale4.dValue > psIni->fBotScaleTruck;
				}
				else
				{
					fill4->Visible = (psIni->nRpoints & I_FILL4) > 0;
					siloBar4->Open = (psIni->nWpoints & O_DROP4) > 0;
					scaleBar4->Open = (psIni->nWpoints & O_DISCH4) > 0;
					lite4->Enabled = (psIni->nWpoints & O_LIGHT4) > 0;
					safe10->Visible = (psIni->nWpoints & O_SAFE4) > 0;
				}
				truckBar4->Visible = bTruck4;
				truckPic4->Visible = bTruck4;

				if (psIni->bTest)
				{
					scale4->Text = gcnew String((char *)psIni->sScale4.acData);
					cnt4->Text = psIni->sScale4.nClock.ToString();
				}
			}

			//////////////////////////////////////////////////////////////////////////
			if (psIni->nUlinkOk > 1)
				ulinkLb->BackColor = COL_LB;
			else if (psIni->nUlinkOk > 0)
				ulinkLb->BackColor = COL_W;
			else
				ulinkLb->BackColor = COL_R;

			if (psIni->nDbaseOk > 1)
			{
				DbaseLb->BackColor = COL_LB;
				psIni->nDbaseOk--;
			}
			else if (psIni->nDbaseOk == 1)
				DbaseLb->BackColor = COL_W;
			else
				DbaseLb->BackColor = COL_R;

			if (psIni->bPrinterOk1)
				printerLb1->BackColor = COL_W;
			else
				printerLb1->BackColor = COL_R;

			if (psIni->bPrinterOk2)
				printerLb2->BackColor = COL_W;
			else
				printerLb2->BackColor = COL_R;

			if (psIni->bPrinterOk3)
				printerLb3->BackColor = COL_W;
			else
				printerLb3->BackColor = COL_R;

			if (psIni->bPrinterOk4)
				printerLb4->BackColor = COL_W;
			else
				printerLb4->BackColor = COL_R;

			if (psIni->b2ndPrinterOk1)				//DC 4.0.2
			{
				copyLane1Lb->BackColor = COL_W;
				laneA2ndCB->Checked = true;
			}
			else
			{
				copyLane1Lb->BackColor = COL_R;
				laneA2ndCB->Checked = false;
			}

			if (psIni->b2ndPrinterOk2)				//DC 4.0.2
			{
				copyLane2Lb->BackColor = COL_W;
				laneB2ndCB->Checked = true;
			}
			else
			{
				copyLane2Lb->BackColor = COL_R;
				laneB2ndCB->Checked = false;
			}

			if (psIni->b2ndPrinterOk3)				//DC 4.0.2
			{
				copyLane3Lb->BackColor = COL_W;
				laneC2ndCB->Checked = true;
			}
			else
			{
				copyLane3Lb->BackColor = COL_R;
				laneC2ndCB->Checked = false;
			}

			if (psIni->b2ndPrinterOk4)				//DC 4.0.2
			{
				copyLane4Lb->BackColor = COL_W;
				laneD2ndCB->Checked = true;
			}
			else
			{
				copyLane4Lb->BackColor = COL_R;
				laneD2ndCB->Checked = false;
			}

			if (pAll->eAsType != A_DEMO)
			{
				if (psIni->nOptoOk > 1)
					optoLb->BackColor = COL_LB;
				else if (psIni->nOptoOk > 0)
					optoLb->BackColor = COL_W;
				else
					optoLb->BackColor = COL_R;
			}
			if ((psIni->nRpoints & psIni->uKeepAliveI) > 0)
				matrixPDMLb->BackColor = COL_W;
			else
				matrixPDMLb->BackColor = COL_R;

			if (pAll->eAsType == A_REMOTE)
			{
				if (pAll->nClinkOk > 2)
					clinkLb->BackColor = COL_YG;		// 3
				else if (pAll->nClinkOk > 1)
					clinkLb->BackColor = COL_LB;	// 2
				else if (pAll->nClinkOk > 0)
					clinkLb->BackColor = COL_W;		// 1
				else
					clinkLb->BackColor = COL_R;		// 0
			}

			if (pAll->eAsType != A_REMOTE)	//DC 4.1.0
			{
				if (pAll->nCservOk > 1)
					clinkLb->BackColor = COL_LB;
				else if (pAll->nCservOk > 0)
					clinkLb->BackColor = COL_W;
				else
					clinkLb->BackColor = COL_R;

				switch (pAll->nKey)
				{
				case K_SBAR4: siloBar4_Click(nullptr, nullptr); break;
				case K_NEXT4: pAll->bRemoteCall = true; nextBt4_Click(nullptr, nullptr); break;
				case K_NEXTCONYES4: pAll->bRemContinue = true; pAll->bRemoteCall = true; nextBt4_Click(nullptr, nullptr); break;
				case K_NEXTCONNO4: pAll->bRemContinue = false; pAll->bRemoteCall = true; nextBt4_Click(nullptr, nullptr); break;
				case K_RESET4: pAll->bRemoteCall = true; resetBt4_Click(nullptr, nullptr); break;
				case K_READY4: pAll->bRemoteCall = true; readyBt4_Click(nullptr, nullptr); break;
				case K_HOLD4: pause4_Click(nullptr, nullptr); break;
				case K_RESETTON4: pAll->bRemoteCall = true; tonnage4_Click(nullptr, nullptr); break;
				case K_VOIDYES4: pAll->bRemoteVoid = true; pAll->bRemoteCall = true; stopBt4_Click(nullptr, nullptr); break;
				case K_VOIDNO4: pAll->bRemoteVoid = false; pAll->bRemoteCall = true; stopBt4_Click(nullptr, nullptr); break;
				case K_SJOB4: pAll->bRemoteCall = true; dataGridJob_RowHeaderMouseDoubleClick(nullptr, nullptr); break;
				case K_PRINT4: pAll->bRemoteCall = true; okD_Click(nullptr, nullptr); break;
				case K_RPRINT4:
					LOG_REC sLog;
					Job^ pJob;
					pJob = pAll->pJob;
					if (pJob != nullptr)
					{
						if (poLog->findTicket(pJob->nTicket, &sLog) > 0)
						{
							poLog->calcTicket(&sLog);
							poLog->printTicket(&sLog, 4, true);
						}
					}
					break;
				default: pAll->bRemoteCall = false; break;
				}
				pAll->nKey = 0;
			}
#ifdef SIM			 
			//			if(b485Ok)
#endif			 
			{
				//				autoEvent->Set();
			}
		}
#pragma endregion

#pragma region COMMON
	private: Truck^ findTruck(char *pcId)
	{
		Truck^ pTruck;
		String^ stName = gcnew String(pcId);

		for (int i = 0; i<pAll->lTruck->Count; i++)
		{
			pTruck = pAll->lTruck[i];

			if (pTruck->stName->Equals(stName))
				return pTruck;
		}
		return nullptr;
	}

#pragma endregion

#pragma region SILO1
			 //================================================================
	private: System::Void nextBt1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bDone = false;
		int nIdx = 0;

		if (pAll->lJob->Count == 0)
			return;

		if (psIni->sScale1.bSerial == false)
		{
			if (MessageBox::Show("Scale ERROR, continue ?", "Lane A",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::No)
			{
				return;
			}
		}
		bAuto1 = true;

		customer1->BackColor = COL_G;
		customer1->ReadOnly = true;
		Job1->BackColor = COL_G;
		Job1->ReadOnly = true;
		material1->BackColor = COL_G;
		material1->ReadOnly = true;
		truck1->BackColor = COL_W;
		truck1->Select();
		target1->BackColor = COL_W;
		target1->ReadOnly = false;		//DC 3.2.4

										//---------------------------------------
		while (!bDone && (nIdx < pAll->lJob->Count))
		{
			pJob1 = pAll->lJob[nIdx++];

			if (psIni->bBotScale)
			{
				if ((pJob1->eStatus != S_NEW) || (pJob1->nSilo > 3))
					continue;
			}
			else
			{
				if ((pJob1->eStatus != S_NEW) || (pJob1->nSilo != 1))
					continue;
			}
			poLog->log(C_READ, &psIni->sLog1, pJob1->nLogIdx);
			if (gcnew String(psIni->sLog1.sT.mix_code) != ""
				&& (gcnew String(psIni->sLog1.sT.mix_code) != gcnew String(psIni->asSilos[psIni->sLog1.nSilo - 1].acProduct))) //DC 4.0.1
			{
				MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[psIni->sLog1.nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog1.sT.ticket_num
					+ " for Truck: " + gcnew String(psIni->sLog1.sT.truck_id)
					+ ", NEED Material: " + gcnew String(psIni->sLog1.sT.mix_code), "Lane A",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				//						 bWrongMet = true;	//DC 4.0.1
				return;
			}
			pAll->lJob->Remove(pJob1);
			pAll->nTickets1--;

			pTruck1 = findTruck(psIni->sLog1.sT.truck_id);

			customer1->Text = gcnew String(psIni->sLog1.sT.customer_name_1);
			Job1->Text = gcnew String(psIni->sLog1.sT.project_code);
			material1->Text = gcnew String(psIni->sLog1.sT.mix_code);
			tic_num1->Text = psIni->sLog1.sT.ticket_num.ToString();
			truck1->Text = gcnew String(psIni->sLog1.sT.truck_id);
			if (psIni->bScaleInLB)	//DC 3.2.0
				target1->Text = psIni->sLog1.sT.load_size.ToString("F00");
			else
				target1->Text = psIni->sLog1.sT.load_size.ToString("F02");
			plant1->Text = psIni->sLog1.sT.plant_num.ToString();

			if (psIni->bBotScale)
			{
				switch (psIni->sLog1.nSilo)
				{
				case 1:	siloBar1_Click(nullptr, nullptr);	break;
				case 2:	siloBar12_Click(nullptr, nullptr);	break;
				case 3:	siloBar13_Click(nullptr, nullptr);	break;
				}
			}
			bDone = true;
		}
		if (bDone)
			setState1(S_NEXT);
	}

			 //----------------------------------------------------------------
	private: System::Void autoBt1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bAuto1 = false;

		customer1->BackColor = COL_W;
		Job1->BackColor = COL_W;
		material1->BackColor = COL_W;
		truck1->BackColor = COL_W;
		target1->BackColor = COL_W;
		customer1->ReadOnly = false;
		Job1->ReadOnly = false;
		material1->ReadOnly = false;

		customer1->Text = nullptr;
		Job1->Text = nullptr;
		material1->Text = nullptr;
		truck1->Text = nullptr;
		target1->Text = nullptr;
		tic_num1->Text = psIni->sInv.nLastTicket.ToString();
		plant1->Text = psIni->nPlantNum1.ToString();

		memset(&psIni->sLog1, 0, sizeof(LOG_REC));
		psIni->sLog1.eJobStatus = S_NEW;
		psIni->sLog1.sT.mix_price = psIni->fTonPrice;
		psIni->sLog1.fTax = psIni->fTaxRate;
		psIni->sLog1.sT.ticket_num = psIni->sInv.nLastTicket++;
		psIni->sLog1.sT.plant_num = psIni->nPlantNum1;

		siloBar1_Click(nullptr, nullptr);
		setState1(S_NEXT);
	}

			 //================================================================
	private: System::Void readyBt1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!psIni->bBotScale)
		{
			if ((psIni->sScale1.dValue < 0.0)
				&& (MessageBox::Show("Scale under 0.0, continue ?", "Lane A",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
			else if ((psIni->sScale1.dValue > psIni->sScale1.fTolerance)
				&& (MessageBox::Show("Scale over 0.0, continue ?", "Lane A",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
		}

		try
		{
			psIni->sLog1.sT.load_size = Convert::ToDouble(target1->Text);
			pJob1->fLoad = Convert::ToDouble(target1->Text);				//DC 4.0.1
		}
		catch (System::FormatException^)
		{
			MessageBox::Show("Please correct numeric entry !", "Lane A",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// find truck
		/*
		if(psIni->sLog1.sT.truck_id == nullptr)			//DC 3.2.9
		{
		char truckChar1[33];
		strncpy(truckChar1, truck1->Text->s, strlen(truck1->Text));
		pTruck1 = findTruck(truckChar1);
		}
		else
		*/
		pTruck1 = findTruck(psIni->sLog1.sT.truck_id);

		if (pTruck1 == nullptr)
		{
			MessageBox::Show("Truck " + gcnew String(psIni->sLog1.sT.truck_id) + " not found !", "Lane A",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// test target versus truck capacity
		if (psIni->sLog1.sT.load_size > pTruck1->nCapacity) //DC 3.2.4 && !psIni->bUseTrkMax)		//DC 3.2.0
		{
			MessageBox::Show("Target exceeds truck capacity !", "Lane A",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!bAuto1)
		{
			str2arr(customer1->Text, psIni->sLog1.sT.customer_name_1);
			str2arr(Job1->Text, psIni->sLog1.sT.project_code);
			str2arr(material1->Text, psIni->sLog1.sT.mix_code);
			str2arr(truck1->Text, psIni->sLog1.sT.truck_id);

			pJob1 = gcnew Job();
			pJob1->nLogIdx = poLog->log(C_APPEND, &psIni->sLog1, 0);
			pJob1->nTicket = psIni->sLog1.sT.ticket_num;
			pJob1->nSilo = psIni->sLog1.nSilo;
			pJob1->stCustomer = gcnew String(psIni->sLog1.sT.customer_name_1);
			pJob1->eStatus = psIni->sLog1.eJobStatus;
			//					 psIni->sLog1.fTruckTare = psIni->sScale1.dValue;
		}

		// lock job record
		customer1->BackColor = COL_G;
		customer1->ReadOnly = true;
		Job1->BackColor = COL_G;
		Job1->ReadOnly = true;
		material1->BackColor = COL_G;
		material1->ReadOnly = true;
		truck1->BackColor = COL_G;
		target1->BackColor = COL_G;
		target1->ReadOnly = true;		//DC 3.2.4

		nextBt1->Enabled = true;
		nextBt1->BackColor = COL_TRANS;
		autoBt1->Enabled = true;
		autoBt1->BackColor = COL_TRANS;

		if (psIni->bBotScale)					// update truck tare
		{
			if (!psIni->bSendBitWise)			//DC 4.0.1
				psIni->sLog1.fTruckTare = psIni->sScale1.dValue;
			if (psIni->bUseTrkMax)				//DC 3.2.0
				psIni->sLog1.sT.load_size = psIni->sLog1.sT.load_size - psIni->sLog1.fTruckTare;
		}
		fCumTarget1 = 0.0;
		fFall1 = 0;
		setDrops1(psIni->sLog1.nDrops);
		setState1(S_READY);
	}

			 //================================================================
	private: System::Void printOnly1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (taxExempt1->Checked)
			psIni->sLog1.fTax = 0;
		poLog->calcTarget(&psIni->sLog1);

		if (psIni->bScaleInLB)	//DC 3.2.0
		{
			tareA->Text = psIni->sLog1.fTruckTare.ToString("F00");
			grossA->Text = psIni->sLog1.fGross.ToString("F00");
		}
		else
		{
			tareA->Text = psIni->sLog1.fTruckTare.ToString("F02");
			grossA->Text = psIni->sLog1.fGross.ToString("F02");
		}
		groupBoxA->Visible = true;
	}

			 //--------------------------------------------------------------------
	private: System::Void okA_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int nPrinter = 1;
		if (laneACb2->Checked)
			nPrinter = 2;
		else if (laneACb3->Checked)
			nPrinter = 3;
		try
		{
			psIni->sLog1.fTruckTare = Convert::ToDouble(tareA->Text);
			psIni->sLog1.fGross = Convert::ToDouble(grossA->Text);
			psIni->sLog1.fLoad = psIni->sLog1.fGross - psIni->sLog1.fTruckTare;
		}
		catch (System::FormatException^)
		{
			MessageBox::Show("Please correct numeric entry !", "Lane A",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		groupBoxA->Visible = false;

		poLog->calcLoad(&psIni->sLog1);
		poLog->printTicket(&psIni->sLog1, nPrinter, false);
		psIni->sLog1.eJobStatus = S_PRINTED;
		poLog->log(C_UPDATE, &psIni->sLog1, pJob1->nLogIdx);

		// add to old job list
		pJob1->stStatus = pAll->lStat[pJob1->eStatus];
		pAll->lOld->Add(pJob1);

		setState1(S_IDLE);
	}

			 //================================================================
	private: System::Void setDrops1(int nDropsIn)
	{
		int	nDropsMin = (int)(psIni->sLog1.sT.load_size / psIni->fDropMax) + 1;
		int nDrops = max(nDropsMin, nDropsIn);

		// test size of drop against scale capacity
		fTarget1 = psIni->sLog1.sT.load_size / nDrops;
		fTol1 = max(psIni->fTarTolAbs, psIni->fTarTolPerc * fTarget1 / 100);
		truckBar1->Separators = nDrops - 1;
		psIni->sLog1.nDrops = nDrops;

		if (psIni->bBotScale)
		{
			switch (psIni->sLog1.nSilo)
			{
			case 1:  siloBar1->Target = fTarget1;	break;
			case 2:  siloBar12->Target = fTarget1;	break;
			case 3:  siloBar13->Target = fTarget1;	break;
			}
			scaleBar1->Target = fTarget1 + psIni->sLog1.fTruckTare;
		}
		else
		{
			siloBar1->Target = fTarget1;
			scaleBar1->Target = fTarget1;
		}
		switch (psIni->sLog1.nDrops)
		{
		case 1: drops11->Checked = true; break;
		case 2: drops12->Checked = true; break;
		case 3: drops13->Checked = true; break;
		case 4: drops14->Checked = true; break;
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void drops11_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops1(1);
	}
	private: System::Void drops12_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops1(2);
	}
	private: System::Void drops13_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops1(3);
	}
	private: System::Void drops14_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops1(4);
	}

			 //----------------------------------------------------------------
	private: double getFall1(void)
	{
		double fFall;
		int nIdx = (int)fTarget1;

		if (!psIni->bBotScale)
		{
			if (autoFall1->Checked)
				fFall = psIni->sInv.asFall1[nIdx].fFall / SAMPLE_NBR;
			else
				fFall = psIni->afManFall1[nIdx];
		}
		else
		{
			switch (psIni->sLog1.nSilo)
			{
			case 1:
				if (autoFall1->Checked)
					fFall = psIni->sInv.asFall1[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall1[nIdx];
				break;
			case 2:
				if (autoFall1->Checked)
					fFall = psIni->sInv.asFall2[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall2[nIdx];
				break;
			case 3:
				if (autoFall1->Checked)
					fFall = psIni->sInv.asFall3[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall3[nIdx];
				break;
			}
		}
		return fFall;
	}

			 //-------------------------------------------------------------------------
	private: System::Void dropBt1_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		bool bSafe = psIni->nSafeTime > 0;
		readyBt1->Enabled = false;
		readyBt1->BackColor = COL_TRANS;

		str2arr(truck1->Text, psIni->sLog1.sT.truck_id);

		if (!psIni->bBotScale)				//#ifdef UPSCALE
		{
			fNewTarget1 = fTarget1;
		}
		else
		{
			if (pAll->eAsType == A_PROD)
				if (!bTruck1) return;

			if (bFirstDrop1 && !psIni->bSendBitWise)
				psIni->sLog1.fTruckTare = psIni->sScale1.dValue;
			fCumTarget1 += fTarget1;
		}
		fFall1 = getFall1();

		if (psIni->bSafeJob)
			bSafe = bFirstDrop1;

		if (bSafe)
			setState1(S_SAFE);
		else
			setState1(S_DROP);
		bFirstDrop1 = false;
	}

			 //----------------------------------------------------------------		
	private: System::Void dischBt1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		dischBt1->BackColor = COL_PGREEN;
		setState1(S_DISCH);
	}

			 //-------------------------------------------------------------------------
	private: System::Void pauseBt1_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		switch (psIni->sLog1.eState)
		{
		case S_DROP:			setState1(S_HOLD_DROP); //setState1(S_HOLD_SETTLE); 
			pauseBt1->BackColor = COL_HOLD;
			break;
		case S_ASETTLE:		setState1(S_HOLD_ASETTLE);
			pauseBt1->BackColor = COL_HOLD;
			break;
		case S_DISCH:			setState1(S_HOLD_DISCH);
			pauseBt1->BackColor = COL_HOLD;
			break;
		case S_ADD:			setState1(S_HOLD_ADD); //DC 4.0.0
			pauseBt1->BackColor = COL_HOLD;
			break;

		case S_HOLD_ADD:		setState1(S_ADD);		//DC 4.0.0
			pauseBt1->BackColor = COL_HOLDK;
			break;
		case S_HOLD_DROP:		setState1(S_DROP);
			pauseBt1->BackColor = COL_HOLDK;
			break;
		case S_HOLD_ASETTLE:	setState1(S_ASETTLE);
			pauseBt1->BackColor = COL_HOLDK;
			break;
		case S_HOLD_DISCH:		setState1(S_DISCH);
			pauseBt1->BackColor = COL_HOLDK;
			break;
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void stopBt1_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		switch (psIni->sLog1.eState)
		{
		case S_IDLE:
			return;
		case S_NEXT:
		case S_READY:
			if (bAuto1)
			{
				resetTargetOutput();		//DC 4.0.1

				if (MessageBox::Show("Void Ticket ?", "Lane A",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::Yes)
				{
					pJob1->eStatus = S_VOIDED;
					psIni->sLog1.eJobStatus = S_VOIDED;
					psIni->sLog1.eStop = A_VOID;
					psIni->sLog1.eState = S_ABORT;
				}
				else
				{
					pJob1->eStatus = S_NEW;
					pAll->lJob->Add(pJob1);

					if (!psIni->bBotScale)
						switch (psIni->sLog1.nSilo)
						{
						case 1: pAll->nTickets1++; break;
						case 2: pAll->nTickets2++; break;
						case 3: pAll->nTickets3++; break;
						case 4: psIni->nTickets4++; break;
						}
					else
						switch (psIni->sLog1.nSilo)
						{
						case 1:
						case 2:
						case 3: pAll->nTickets1++; break;
						case 4:
						case 5:
						case 6: pAll->nTickets2++; break;
						case 7:
						case 8:
						case 9: pAll->nTickets3++; break;
						case 10:
						case 11:
						case 12: psIni->nTickets4++; break;
						}
					setState1(S_IDLE);
				}
			}
			else
				setState1(S_IDLE);
			return;

		case S_DROP:      setState1(S_HOLD_SETTLE); break;
		case S_DISCH:     setState1(S_HOLD_DISCH); break;
		}
		StopForm^ pStop = gcnew StopForm(&psIni->sLog1, pJob1);
		pStop->Show();
	}

			 //-------------------------------------------------------------------------
	private: System::Void addBt1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bAdd = true;
		bool bAsk = false;
		addBt1->Enabled = false;

		if (!psIni->bBotScale)
		{
			bAsk = (fLoad1 + psIni->dAddQty) > psIni->sLog1.sT.load_size;
		}
		else
		{
			if (!psIni->bPdmPlc)
				bAsk = (fLoad1 + psIni->dAddQty) > fCumTarget1;
			else
				bAsk = (fLoad1 + psIni->asSilos[psIni->sLog1.nSilo - 1].dAddTol) > fCumTarget1;		//DC 4.0.0
		}

		if (bAsk)
		{
			bStopAdd1 = true;		//DC 4.0.0
			if (MessageBox::Show("TRUCK CAPACITY WARNING, continue ?", "Lane A",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::No)
				bAdd = false;
		}
		if (bAdd)
			setState1(S_ADD);
		else
			setState1(S_UPDATE);
	}

	private: bool testHold1(void)
	{
		if (psIni->bHold1 && psIni->sLog1.eState != S_HOLD)
		{
			ePrevHold1 = psIni->sLog1.eState;
			setState1(S_HOLD);
			pauseBt1->BackColor = COL_HOLD;
			return true;
		}
		return false;
	}

#pragma endregion

#pragma region SILO2	
			 //=========================================================================
	private: System::Void nextBt2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bDone = false;
		int nIdx = 0;

		if (pAll->lJob->Count == 0)
			return;

		if ((psIni->sScale2.bSerial == false)
			&& (MessageBox::Show("Scale ERROR, continue ?", "Lane B",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::No))
		{
			return;
		}

		bAuto2 = true;

		customer2->BackColor = COL_G;
		customer2->ReadOnly = true;
		Job2->BackColor = COL_G;
		Job2->ReadOnly = true;
		material2->BackColor = COL_G;
		material2->ReadOnly = true;
		truck2->BackColor = COL_W;
		truck2->Select();
		target2->BackColor = COL_W;
		target2->ReadOnly = false;		//DC 3.2.4

										//---------------------------------------
		while (!bDone && (nIdx < pAll->lJob->Count))
		{
			pJob2 = pAll->lJob[nIdx++];

			if (psIni->bBotScale)
			{
				if ((pJob2->eStatus != S_NEW) || (pJob2->nSilo < 4) || (pJob2->nSilo > 6))
					continue;
			}
			else
			{
				if ((pJob2->eStatus != S_NEW) || (pJob2->nSilo != 2))
					continue;
			}
			poLog->log(C_READ, &psIni->sLog2, pJob2->nLogIdx);
			if (gcnew String(psIni->sLog2.sT.mix_code) != ""
				&& (gcnew String(psIni->sLog2.sT.mix_code) != gcnew String(psIni->asSilos[psIni->sLog2.nSilo - 1].acProduct))) //DC 4.0.1
			{
				MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[psIni->sLog2.nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog2.sT.ticket_num
					+ " for Truck: " + gcnew String(psIni->sLog2.sT.truck_id)
					+ ", NEED Material: " + gcnew String(psIni->sLog2.sT.mix_code), "Lane A",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				//						 bWrongMet = true;	//DC 4.0.1
				return;
			}
			pAll->lJob->Remove(pJob2);
			pAll->nTickets2--;

			pTruck2 = findTruck(psIni->sLog2.sT.truck_id);

			customer2->Text = gcnew String(psIni->sLog2.sT.customer_name_1);
			Job2->Text = gcnew String(psIni->sLog2.sT.project_code);
			material2->Text = gcnew String(psIni->sLog2.sT.mix_code);
			tic_num2->Text = psIni->sLog2.sT.ticket_num.ToString();
			truck2->Text = gcnew String(psIni->sLog2.sT.truck_id);
			if (psIni->bScaleInLB)	//DC 3.2.0
				target2->Text = psIni->sLog2.sT.load_size.ToString("F00");
			else
				target2->Text = psIni->sLog2.sT.load_size.ToString("F02");
			plant2->Text = psIni->sLog2.sT.plant_num.ToString();

			if (psIni->bBotScale)
			{
				switch (psIni->sLog2.nSilo)
				{
				case 4:	siloBar2_Click(nullptr, nullptr);	break;
				case 5:	siloBar22_Click(nullptr, nullptr);	break;
				case 6:	siloBar23_Click(nullptr, nullptr);	break;
				}
			}
			bDone = true;
		}
		if (bDone)
			setState2(S_NEXT);
	}

			 //-----------------------------------------------------------------	 
	private: System::Void autoBt2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bAuto2 = false;

		customer2->BackColor = COL_W;
		customer2->ReadOnly = false;
		Job2->BackColor = COL_W;
		Job2->ReadOnly = false;
		material2->BackColor = COL_W;
		material2->ReadOnly = false;
		truck2->BackColor = COL_W;
		target2->BackColor = COL_W;

		customer2->Text = nullptr;
		Job2->Text = nullptr;
		material2->Text = nullptr;
		truck2->Text = nullptr;
		target2->Text = nullptr;
		tic_num2->Text = psIni->sInv.nLastTicket.ToString();
		plant2->Text = psIni->nPlantNum1.ToString();

		memset(&psIni->sLog2, 0, sizeof(LOG_REC));
		psIni->sLog2.eJobStatus = S_NEW;
		psIni->sLog2.sT.mix_price = psIni->fTonPrice;
		psIni->sLog2.fTax = psIni->fTaxRate;
		psIni->sLog2.sT.ticket_num = psIni->sInv.nLastTicket++;
		psIni->sLog2.sT.plant_num = psIni->nPlantNum1;

		siloBar2_Click(nullptr, nullptr);
		setState2(S_NEXT);
	}

			 //================================================================
	private: System::Void readyBt2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!psIni->bBotScale)
		{
			if ((psIni->sScale2.dValue < 0.0)
				&& (MessageBox::Show("Scale under 0.0, continue ?", "Lane B",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
			else if ((psIni->sScale2.dValue > psIni->sScale2.fTolerance)
				&& (MessageBox::Show("Scale over 0.0, continue ?", "Lane B",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
		}

		try
		{
			psIni->sLog2.sT.load_size = Convert::ToDouble(target2->Text);
			pJob2->fLoad = Convert::ToDouble(target2->Text);				//DC 4.0.1
		}
		catch (System::FormatException^)
		{
			MessageBox::Show("Please correct numeric entry !", "Lane B",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// find truck
		pTruck2 = findTruck(psIni->sLog2.sT.truck_id);
		if (pTruck2 == nullptr)
		{
			MessageBox::Show("Truck " + gcnew String(psIni->sLog2.sT.truck_id) + " not found !", "Lane B",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// test target versus truck capacity
		if (psIni->sLog2.sT.load_size > pTruck2->nCapacity)	//DC 3.2.4  && !psIni->bUseTrkMax)		//DC 3.2.0
		{
			MessageBox::Show("Target exceeds truck capacity !", "Lane B",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!bAuto2)
		{
			str2arr(customer2->Text, psIni->sLog2.sT.customer_name_1);
			str2arr(Job2->Text, psIni->sLog2.sT.project_code);
			str2arr(material2->Text, psIni->sLog2.sT.mix_code);
			str2arr(truck2->Text, psIni->sLog2.sT.truck_id);

			pJob2 = gcnew Job();
			pJob2->nLogIdx = poLog->log(C_APPEND, &psIni->sLog2, 0);
			pJob2->nTicket = psIni->sLog2.sT.ticket_num;
			pJob2->nSilo = psIni->sLog2.nSilo;
			pJob2->stCustomer = gcnew String(psIni->sLog2.sT.customer_name_1);
			pJob2->eStatus = psIni->sLog2.eJobStatus;
			//					 psIni->sLog2.fTruckTare = psIni->sScale2.dValue;
		}

		// lock job record
		customer2->BackColor = COL_G;
		customer2->ReadOnly = true;
		Job2->BackColor = COL_G;
		Job2->ReadOnly = true;
		material2->BackColor = COL_G;
		material2->ReadOnly = true;
		truck2->BackColor = COL_G;
		target2->BackColor = COL_G;
		target2->ReadOnly = true;		//DC 3.2.4

		nextBt2->Enabled = true;
		nextBt2->BackColor = COL_TRANS;
		autoBt2->Enabled = true;
		autoBt2->BackColor = COL_TRANS;

		if (psIni->bBotScale)
		{
			if (!psIni->bSendBitWise)			//DC 4.0.1
				psIni->sLog2.fTruckTare = psIni->sScale2.dValue;
			if (psIni->bUseTrkMax)				//DC 3.2.0
				psIni->sLog2.sT.load_size = psIni->sLog2.sT.load_size - psIni->sLog2.fTruckTare;
		}
		fCumTarget2 = 0.0;
		fFall2 = 0;
		setDrops2(psIni->sLog2.nDrops);
		setState2(S_READY);
	}

			 //--------------------------------------------------------------------
	private: System::Void printOnly2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (taxExempt2->Checked)
			psIni->sLog2.fTax = 0;
		poLog->calcTarget(&psIni->sLog2);

		if (psIni->bScaleInLB)	//DC 3.2.0
		{
			tareB->Text = psIni->sLog2.fTruckTare.ToString("F00");
			grossB->Text = psIni->sLog2.fGross.ToString("F00");
		}
		else
		{
			tareB->Text = psIni->sLog2.fTruckTare.ToString("F02");
			grossB->Text = psIni->sLog2.fGross.ToString("F02");
		}
		groupBoxB->Visible = true;
	}

			 //----------------------------------------------------------------
	private: System::Void okB_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int nPrinter = 2;
		if (laneBCb1->Checked)
			nPrinter = 1;
		else if (laneBCb3->Checked)
			nPrinter = 3;
		try
		{
			psIni->sLog2.fTruckTare = Convert::ToDouble(tareB->Text);
			psIni->sLog2.fGross = Convert::ToDouble(grossB->Text);
			psIni->sLog2.fLoad = psIni->sLog2.fGross - psIni->sLog2.fTruckTare;
		}
		catch (System::FormatException^)
		{
			MessageBox::Show("Please correct numeric entry !", "Lane B",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		groupBoxB->Visible = false;

		poLog->calcLoad(&psIni->sLog2);
		poLog->printTicket(&psIni->sLog2, nPrinter, false);
		psIni->sLog2.eJobStatus = S_PRINTED;
		poLog->log(C_UPDATE, &psIni->sLog2, pJob2->nLogIdx);

		// add to old job list
		pJob2->stStatus = pAll->lStat[pJob2->eStatus];
		pAll->lOld->Add(pJob2);

		setState2(S_IDLE);
	}

			 //================================================================
	private: System::Void setDrops2(int nDropsIn)
	{
		int	nDropsMin = (int)(psIni->sLog2.sT.load_size / psIni->fDropMaxL2) + 1;
		int nDrops = nDropsIn > nDropsMin ? nDropsIn : nDropsMin;

		// test size of drop against scale capacity
		fTarget2 = psIni->sLog2.sT.load_size / nDrops;
		fTol2 = max(psIni->fTarTolAbs, psIni->fTarTolPerc * fTarget2 / 100);
		truckBar2->Separators = nDrops - 1;
		psIni->sLog2.nDrops = nDrops;

		if (psIni->bBotScale)
		{
			switch (psIni->sLog2.nSilo)
			{
			case 4:  siloBar2->Target = fTarget2;	break;
			case 5:  siloBar22->Target = fTarget2;	break;
			case 6:  siloBar23->Target = fTarget2;	break;
			}
			scaleBar2->Target = fTarget2 + psIni->sLog2.fTruckTare;
		}
		else
		{
			siloBar2->Target = fTarget2;
			scaleBar2->Target = fTarget2;
		}
		switch (psIni->sLog2.nDrops)
		{
		case 1: drops21->Checked = true; break;
		case 2: drops22->Checked = true; break;
		case 3: drops23->Checked = true; break;
		case 4: drops24->Checked = true; break;
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void drops21_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops2(1);
	}
	private: System::Void drops22_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops2(2);
	}
	private: System::Void drops23_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops2(3);
	}
	private: System::Void drops24_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops2(4);
	}

			 //----------------------------------------------------------------
	private: double getFall2(void)
	{
		double fFall;
		int nIdx = (int)fTarget2;

		if (!psIni->bBotScale)
		{
			if (autoFall2->Checked)
				fFall = psIni->sInv.asFall2[nIdx].fFall / SAMPLE_NBR;
			else
				fFall = psIni->afManFall2[nIdx];
		}
		else
		{
			switch (psIni->sLog2.nSilo)
			{
			case 4:
				if (autoFall2->Checked)
					fFall = psIni->sInv.asFall4[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall4[nIdx];
				break;
			case 5:
				if (autoFall2->Checked)
					fFall = psIni->sInv.asFall5[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall5[nIdx];
				break;
			case 6:
				if (autoFall2->Checked)
					fFall = psIni->sInv.asFall6[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall6[nIdx];
				break;
			}
		}
		return fFall;
	}

			 //-------------------------------------------------------------------------
	private: System::Void dropBt2_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		bool bSafe = psIni->nSafeTime > 0;
		readyBt2->Enabled = false;
		readyBt2->BackColor = COL_TRANS;

		str2arr(truck2->Text, psIni->sLog2.sT.truck_id);

		if (!psIni->bBotScale)
		{
			fNewTarget2 = fTarget2;
		}
		else
		{
			if (pAll->eAsType == A_PROD)
				if (!bTruck2) return;

			if (bFirstDrop2 && !psIni->bSendBitWise)
				psIni->sLog2.fTruckTare = psIni->sScale2.dValue;
			fCumTarget2 += fTarget2;
		}
		fFall2 = getFall2();

		if (psIni->bSafeJob)
			bSafe = bFirstDrop2;

		if (bSafe)
			setState2(S_SAFE);
		else
			setState2(S_DROP);
		bFirstDrop2 = false;
	}

			 //-------------------------------------------------------------------------
	private: System::Void dischBt2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		dischBt2->BackColor = COL_PGREEN;
		setState2(S_DISCH);
	}

			 //-------------------------------------------------------------------------
	private: System::Void pause2_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		switch (psIni->sLog2.eState)
		{
		case S_DROP:			setState2(S_HOLD_DROP); //setState2(S_HOLD_SETTLE); 
			pauseBt2->BackColor = COL_HOLD;
			break;
		case S_ASETTLE:		setState2(S_HOLD_ASETTLE);
			pauseBt2->BackColor = COL_HOLD;
			break;
		case S_DISCH:			setState2(S_HOLD_DISCH);
			pauseBt2->BackColor = COL_HOLD;
			break;
		case S_ADD:			setState2(S_HOLD_ADD); //DC 4.0.0
			pauseBt2->BackColor = COL_HOLD;
			break;

		case S_HOLD_ADD:		setState2(S_ADD);		//DC 4.0.0
			pauseBt2->BackColor = COL_HOLDK;
			break;
		case S_HOLD_DROP:		setState2(S_DROP);
			pauseBt2->BackColor = COL_HOLDK;
			break;
		case S_HOLD_ASETTLE:	setState2(S_ASETTLE);
			pauseBt2->BackColor = COL_HOLDK;
			break;
		case S_HOLD_DISCH:		setState2(S_DISCH);
			pauseBt2->BackColor = COL_HOLDK;
			break;
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void stopBt2_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		switch (psIni->sLog2.eState)
		{
		case S_IDLE:
			return;
		case S_NEXT:
		case S_READY:
			if (bAuto2)
			{
				resetTargetOutput();		//DC 4.0.1

				if (MessageBox::Show("Void Ticket ?", "Lane B",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::Yes)
				{
					pJob2->eStatus = S_VOIDED;
					psIni->sLog2.eJobStatus = S_VOIDED;
					psIni->sLog2.eStop = A_VOID;
					psIni->sLog2.eState = S_ABORT;
				}
				else
				{
					pJob2->eStatus = S_NEW;
					pAll->lJob->Add(pJob2);

					if (!psIni->bBotScale)
						switch (psIni->sLog2.nSilo)
						{
						case 1: pAll->nTickets1++; break;
						case 2: pAll->nTickets2++; break;
						case 3: pAll->nTickets3++; break;
						case 4: psIni->nTickets4++; break;
						}
					else
						switch (psIni->sLog2.nSilo)
						{
						case 1:
						case 2:
						case 3: pAll->nTickets1++; break;
						case 4:
						case 5:
						case 6: pAll->nTickets2++; break;
						case 7:
						case 8:
						case 9: pAll->nTickets3++; break;
						case 10:
						case 11:
						case 12: psIni->nTickets4++; break;
						}
					setState2(S_IDLE);
				}
			}
			else
				setState2(S_IDLE);
			return;

		case S_DROP:      setState2(S_HOLD_SETTLE); break;
		case S_DISCH:     setState2(S_HOLD_DISCH); break;
		}
		StopForm^ pStop = gcnew StopForm(&psIni->sLog2, pJob2);
		pStop->Show();
	}

			 //-------------------------------------------------------------------------
	private: System::Void addBt2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bAdd = true;
		bool bAsk = false;
		addBt2->Enabled = false;

		if (!psIni->bBotScale)
		{
			bAsk = (fLoad2 + psIni->dAddQty) > psIni->sLog2.sT.load_size;
		}
		else
		{
			if (!psIni->bPdmPlc)
				bAsk = (fLoad2 + psIni->dAddQty) > fCumTarget2;
			else
				bAsk = (fLoad2 + psIni->asSilos[psIni->sLog2.nSilo - 1].dAddTol) > fCumTarget2;		//DC 4.0.0
		}

		if (bAsk)
		{
			bStopAdd2 = true;		//DC 4.0.0
			if (MessageBox::Show("TRUCK CAPACITY WARNING, continue ?", "Lane B",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::No)
				bAdd = false;
		}
		if (bAdd)
			setState2(S_ADD);
		else
			setState2(S_UPDATE);
	}

	private: bool testHold2(void)
	{
		if (psIni->bHold2 && psIni->sLog2.eState != S_HOLD)
		{
			ePrevHold2 = psIni->sLog2.eState;
			setState2(S_HOLD);
			pauseBt2->BackColor = COL_HOLD;
			return true;
		}
		return false;
	}

#pragma endregion

#pragma region SILO3	
			 //================================================================
	private: System::Void nextBt3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bDone = false;
		int nIdx = 0;

		if (pAll->lJob->Count == 0)
			return;

		if ((psIni->sScale3.bSerial == false)
			&& (MessageBox::Show("Scale ERROR, continue ?", "Lane C",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::No))
		{
			return;
		}
		bAuto3 = true;

		customer3->BackColor = COL_G;
		customer3->ReadOnly = true;
		Job3->BackColor = COL_G;
		Job3->ReadOnly = true;
		material3->BackColor = COL_G;
		material3->ReadOnly = true;
		truck3->BackColor = COL_W;
		truck3->Select();
		target3->BackColor = COL_W;
		target3->ReadOnly = false;		//DC 3.2.4

										//---------------------------------------
		while (!bDone && (nIdx < pAll->lJob->Count))
		{
			pJob3 = pAll->lJob[nIdx++];

			if (psIni->bBotScale)
			{
				if ((pJob3->eStatus != S_NEW) || (pJob3->nSilo < 7) || (pJob3->nSilo > 9))
					continue;
			}
			else
			{
				if ((pJob3->eStatus != S_NEW) || (pJob3->nSilo != 3))
					continue;
			}
			poLog->log(C_READ, &psIni->sLog3, pJob3->nLogIdx);
			if (gcnew String(psIni->sLog3.sT.mix_code) != ""
				&& (gcnew String(psIni->sLog3.sT.mix_code) != gcnew String(psIni->asSilos[psIni->sLog3.nSilo - 1].acProduct))) //DC 4.0.1
			{
				MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[psIni->sLog3.nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog3.sT.ticket_num
					+ " for Truck: " + gcnew String(psIni->sLog3.sT.truck_id)
					+ ", NEED Material: " + gcnew String(psIni->sLog3.sT.mix_code), "Lane A",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				//						 bWrongMet = true;	//DC 4.0.1
				return;
			}
			pAll->lJob->Remove(pJob3);
			pAll->nTickets3--;

			pTruck3 = findTruck(psIni->sLog3.sT.truck_id);

			customer3->Text = gcnew String(psIni->sLog3.sT.customer_name_1);
			Job3->Text = gcnew String(psIni->sLog3.sT.project_code);
			material3->Text = gcnew String(psIni->sLog3.sT.mix_code);
			tic_num3->Text = psIni->sLog3.sT.ticket_num.ToString();
			truck3->Text = gcnew String(psIni->sLog3.sT.truck_id);
			if (psIni->bScaleInLB)	//DC 3.2.0
				target3->Text = psIni->sLog3.sT.load_size.ToString("F00");
			else
				target3->Text = psIni->sLog3.sT.load_size.ToString("F02");
			plant3->Text = psIni->sLog3.sT.plant_num.ToString();

			if (psIni->bBotScale)
			{
				switch (psIni->sLog3.nSilo)
				{
				case 7:	siloBar3_Click(nullptr, nullptr);	break;
				case 8:	siloBar32_Click(nullptr, nullptr); 	break;
				case 9:	siloBar33_Click(nullptr, nullptr);  break;
				}
			}
			bDone = true;
		}
		if (bDone)
			setState3(S_NEXT);
	}

			 //-------------------------------------------------------------------------
	private: System::Void autoBt3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bAuto3 = false;

		customer3->BackColor = COL_W;
		customer3->ReadOnly = false;
		Job3->BackColor = COL_W;
		Job3->ReadOnly = false;
		material3->BackColor = COL_W;
		material3->ReadOnly = false;
		truck3->BackColor = COL_W;
		target3->BackColor = COL_W;

		customer3->Text = nullptr;
		Job3->Text = nullptr;
		material3->Text = nullptr;
		truck3->Text = nullptr;
		target3->Text = nullptr;
		tic_num3->Text = psIni->sInv.nLastTicket.ToString();
		plant3->Text = psIni->nPlantNum1.ToString();

		memset(&psIni->sLog3, 0, sizeof(LOG_REC));
		psIni->sLog3.eJobStatus = S_NEW;
		psIni->sLog3.sT.mix_price = psIni->fTonPrice;
		psIni->sLog3.fTax = psIni->fTaxRate;
		psIni->sLog3.sT.ticket_num = psIni->sInv.nLastTicket++;
		psIni->sLog3.sT.plant_num = psIni->nPlantNum1;

		siloBar3_Click(nullptr, nullptr);
		setState3(S_NEXT);
	}

			 //================================================================
	private: System::Void readyBt3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!psIni->bBotScale)
		{
			if ((psIni->sScale3.dValue < 0.0)
				&& (MessageBox::Show("Scale under 0.0, continue ?", "Lane C",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
			else if ((psIni->sScale3.dValue > psIni->sScale3.fTolerance)
				&& (MessageBox::Show("Scale over 0.0, continue ?", "Lane C",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
		}

		try
		{
			psIni->sLog3.sT.load_size = Convert::ToDouble(target3->Text);
			pJob3->fLoad = Convert::ToDouble(target3->Text);				//DC 4.0.1
		}
		catch (System::FormatException^)
		{
			MessageBox::Show("Please correct numeric entry !", "Lane C",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// find truck
		pTruck3 = findTruck(psIni->sLog3.sT.truck_id);
		if (pTruck3 == nullptr)
		{
			MessageBox::Show("Truck " + gcnew String(psIni->sLog3.sT.truck_id) + " not found !", "Lane C",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// test target versus truck capacity
		if (psIni->sLog3.sT.load_size > pTruck3->nCapacity)	//DC 3.2.4 && !psIni->bUseTrkMax)		//DC 3.2.0
		{
			MessageBox::Show("Target exceeds truck capacity !", "Lane C",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!bAuto3)
		{
			str2arr(customer3->Text, psIni->sLog3.sT.customer_name_1);
			str2arr(Job3->Text, psIni->sLog3.sT.project_code);
			str2arr(material3->Text, psIni->sLog3.sT.mix_code);
			str2arr(truck3->Text, psIni->sLog3.sT.truck_id);

			pJob3 = gcnew Job();
			pJob3->nLogIdx = poLog->log(C_APPEND, &psIni->sLog3, 0);
			pJob3->nTicket = psIni->sLog3.sT.ticket_num;
			pJob3->nSilo = psIni->sLog3.nSilo;
			pJob3->stCustomer = gcnew String(psIni->sLog3.sT.customer_name_1);
			pJob3->eStatus = psIni->sLog3.eJobStatus;
			//					 psIni->sLog3.fTruckTare = psIni->sScale3.dValue;
		}

		// lock job record
		customer3->BackColor = COL_G;
		customer3->ReadOnly = true;
		Job3->BackColor = COL_G;
		Job3->ReadOnly = true;
		material3->BackColor = COL_G;
		material3->ReadOnly = true;
		truck3->BackColor = COL_G;
		target3->BackColor = COL_G;
		target3->ReadOnly = true;		//DC 3.2.4

		nextBt3->Enabled = true;
		nextBt3->BackColor = COL_TRANS;
		autoBt3->Enabled = true;
		autoBt3->BackColor = COL_TRANS;

		if (psIni->bBotScale)
		{
			if (!psIni->bSendBitWise)			//DC 4.0.1
				psIni->sLog3.fTruckTare = psIni->sScale3.dValue;
			if (psIni->bUseTrkMax)				//DC 3.2.0
				psIni->sLog3.sT.load_size = psIni->sLog3.sT.load_size - psIni->sLog3.fTruckTare;
		}
		fCumTarget3 = 0.0;
		fFall3 = 0;
		setDrops3(psIni->sLog3.nDrops);
		setState3(S_READY);
	}

			 //--------------------------------------------------------------------
	private: System::Void printOnly3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (taxExempt3->Checked)
			psIni->sLog3.fTax = 0;
		poLog->calcTarget(&psIni->sLog3);

		if (psIni->bScaleInLB)	//DC 3.2.0
		{
			tareC->Text = psIni->sLog3.fTruckTare.ToString("F00");
			grossC->Text = psIni->sLog3.fGross.ToString("F00");
		}
		else
		{
			tareC->Text = psIni->sLog3.fTruckTare.ToString("F02");
			grossC->Text = psIni->sLog3.fGross.ToString("F02");
		}
		groupBoxC->Visible = true;
	}

			 //--------------------------------------------------------------------
	private: System::Void okC_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int nPrinter = 3;
		if (laneCCb1->Checked)
			nPrinter = 1;
		else if (laneCCb2->Checked)
			nPrinter = 2;
		try
		{
			psIni->sLog3.fTruckTare = Convert::ToDouble(tareC->Text);
			psIni->sLog3.fGross = Convert::ToDouble(grossC->Text);
			psIni->sLog3.fLoad = psIni->sLog3.fGross - psIni->sLog3.fTruckTare;
		}
		catch (System::FormatException^)
		{
			MessageBox::Show("Please correct numeric entry !", "Lane C",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		groupBoxC->Visible = false;

		poLog->calcLoad(&psIni->sLog3);
		poLog->printTicket(&psIni->sLog3, nPrinter, false);
		psIni->sLog3.eJobStatus = S_PRINTED;
		poLog->log(C_UPDATE, &psIni->sLog3, pJob3->nLogIdx);

		// add to old job list
		pJob3->stStatus = pAll->lStat[pJob3->eStatus];
		pAll->lOld->Add(pJob3);

		setState3(S_IDLE);
	}

			 //================================================================
	private: System::Void setDrops3(int nDropsIn)
	{
		int	nDropsMin = (int)(psIni->sLog3.sT.load_size / psIni->fDropMaxL3) + 1;
		int nDrops = nDropsIn > nDropsMin ? nDropsIn : nDropsMin;

		// test size of drop against scale capacity
		fTarget3 = psIni->sLog3.sT.load_size / nDrops;
		fTol3 = max(psIni->fTarTolAbs, psIni->fTarTolPerc * fTarget3 / 100);
		truckBar3->Separators = nDrops - 1;
		psIni->sLog3.nDrops = nDrops;

		if (psIni->bBotScale)
		{
			switch (psIni->sLog3.nSilo)
			{
			case 7:  siloBar3->Target = fTarget3;	break;
			case 8:  siloBar32->Target = fTarget3;	break;
			case 9:  siloBar33->Target = fTarget3;	break;
			}
			scaleBar3->Target = fTarget3 + psIni->sLog3.fTruckTare;
		}
		else
		{
			siloBar3->Target = fTarget3;
			scaleBar3->Target = fTarget3;
		}
		switch (psIni->sLog3.nDrops)
		{
		case 1: drops31->Checked = true; break;
		case 2: drops32->Checked = true; break;
		case 3: drops33->Checked = true; break;
		case 4: drops34->Checked = true; break;
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void drops31_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops3(1);
	}
	private: System::Void drops32_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops3(2);
	}
	private: System::Void drops33_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops3(3);
	}
	private: System::Void drops34_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops3(4);
	}

			 //----------------------------------------------------------------
	private: double getFall3(void)
	{
		double fFall;
		int nIdx = (int)fTarget3;

		if (!psIni->bBotScale)
		{
			if (autoFall3->Checked)
				fFall = psIni->sInv.asFall3[nIdx].fFall / SAMPLE_NBR;
			else
				fFall = psIni->afManFall3[nIdx];
		}
		else
		{
			switch (psIni->sLog3.nSilo)
			{
			case 7:
				if (autoFall3->Checked)
					fFall = psIni->sInv.asFall7[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall7[nIdx];
				break;
			case 8:
				if (autoFall3->Checked)
					fFall = psIni->sInv.asFall8[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall8[nIdx];
				break;
			case 9:
				if (autoFall3->Checked)
					fFall = psIni->sInv.asFall9[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall9[nIdx];
				break;
			}
		}
		return fFall;
	}

			 //-------------------------------------------------------------------------
	private: System::Void dropBt3_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		bool bSafe = psIni->nSafeTime > 0;
		readyBt3->Enabled = false;
		readyBt3->BackColor = COL_TRANS;

		str2arr(truck3->Text, psIni->sLog3.sT.truck_id);

		if (!psIni->bBotScale)			//#ifdef UPSCALE
		{
			fNewTarget3 = fTarget3;
		}
		else
		{
			if (pAll->eAsType == A_PROD)
				if (!bTruck3) return;

			if (bFirstDrop3 && !psIni->bSendBitWise)
				psIni->sLog3.fTruckTare = psIni->sScale3.dValue;
			fCumTarget3 += fTarget3;
		}
		fFall3 = getFall3();

		if (psIni->bSafeJob)
			bSafe = bFirstDrop3;

		if (bSafe)
			setState3(S_SAFE);
		else
			setState3(S_DROP);
		bFirstDrop3 = false;
	}

			 //-------------------------------------------------------------------------
	private: System::Void dischBt3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		dischBt3->BackColor = COL_PGREEN;
		setState3(S_DISCH);
	}

			 //-------------------------------------------------------------------------
	private: System::Void pause3_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		switch (psIni->sLog3.eState)
		{
		case S_DROP:			setState3(S_HOLD_DROP); //setState3(S_HOLD_SETTLE); 
			pauseBt3->BackColor = COL_HOLD;
			break;
		case S_ASETTLE:		setState3(S_HOLD_ASETTLE);
			pauseBt3->BackColor = COL_HOLD;
			break;
		case S_DISCH:			setState3(S_HOLD_DISCH);
			pauseBt3->BackColor = COL_HOLD;
			break;
		case S_ADD:			setState3(S_HOLD_ADD); //DC 4.0.0
			pauseBt3->BackColor = COL_HOLD;
			break;

		case S_HOLD_ADD:		setState3(S_ADD);		//DC 4.0.0
			pauseBt3->BackColor = COL_HOLDK;
			break;
		case S_HOLD_DROP:		setState3(S_DROP);
			pauseBt3->BackColor = COL_HOLDK;
			break;
		case S_HOLD_ASETTLE:	setState3(S_ASETTLE);
			pauseBt3->BackColor = COL_HOLDK;
			break;
		case S_HOLD_DISCH:		setState3(S_DISCH);
			pauseBt3->BackColor = COL_HOLDK;
			break;
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void stopBt3_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		switch (psIni->sLog3.eState)
		{
		case S_IDLE:
			return;
		case S_NEXT:
		case S_READY:
			if (bAuto3)
			{
				resetTargetOutput();		//DC 4.0.1

				if (MessageBox::Show("Void Ticket ?", "Lane C",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::Yes)
				{
					pJob3->eStatus = S_VOIDED;
					psIni->sLog3.eJobStatus = S_VOIDED;
					psIni->sLog3.eStop = A_VOID;
					psIni->sLog3.eState = S_ABORT;
				}
				else
				{
					pJob3->eStatus = S_NEW;
					pAll->lJob->Add(pJob3);

					if (!psIni->bBotScale)
						switch (psIni->sLog3.nSilo)
						{
						case 1: pAll->nTickets1++; break;
						case 2: pAll->nTickets2++; break;
						case 3: pAll->nTickets3++; break;
						case 4: psIni->nTickets4++; break;
						}
					else
						switch (psIni->sLog3.nSilo)
						{
						case 1:
						case 2:
						case 3: pAll->nTickets1++; break;
						case 4:
						case 5:
						case 6: pAll->nTickets2++; break;
						case 7:
						case 8:
						case 9: pAll->nTickets3++; break;
						case 10:
						case 11:
						case 12: psIni->nTickets4++; break;
						}
					setState3(S_IDLE);
				}
			}
			else
				setState3(S_IDLE);
			return;

		case S_DROP:     setState3(S_HOLD_SETTLE); break;
		case S_DISCH:    setState3(S_HOLD_DISCH); break;
		}
		StopForm^ pStop = gcnew StopForm(&psIni->sLog3, pJob3);
		pStop->Show();
	}

			 //-------------------------------------------------------------------------
	private: System::Void addBt3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bAdd = true;
		bool bAsk = false;
		addBt3->Enabled = false;

		if (!psIni->bBotScale)
		{
			bAsk = (fLoad3 + psIni->dAddQty) > psIni->sLog3.sT.load_size;
		}
		else
		{
			if (!psIni->bPdmPlc)
				bAsk = (fLoad3 + psIni->dAddQty) > fCumTarget3;
			else
				bAsk = (fLoad3 + psIni->asSilos[psIni->sLog3.nSilo - 1].dAddTol) > fCumTarget3;		//DC 4.0.0
		}

		if (bAsk)
		{
			bStopAdd3 = true;		//DC 4.0.0
			if (MessageBox::Show("TRUCK CAPACITY WARNING, continue ?", "Lane C",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::No)
				bAdd = false;
		}
		if (bAdd)
			setState3(S_ADD);
		else
			setState3(S_UPDATE);
	}

	private: bool testHold3(void)
	{
		if (psIni->bHold3 && psIni->sLog3.eState != S_HOLD)
		{
			ePrevHold3 = psIni->sLog3.eState;
			setState3(S_HOLD);
			pauseBt3->BackColor = COL_HOLD;
			return true;
		}
		return false;
	}

#pragma endregion

#pragma region SILO4	
			 //DC 3.3.0 ================================================================
	private: System::Void nextBt4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// if(pAll->eAsType == A_REMOTE)
		{
			/*int k = 0;
			pCmd = gcnew Cmd();
			pCmd->cId = CL_JOB;
			pAll->qCmd->Enqueue(pCmd);

			while(1 > 0 && k++ < 5)
			Thread::Sleep(100);*/
		}

		{
			bool bDone = false;
			int nIdx = 0;

			if (pAll->lJob->Count == 0)
				return;

			if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
			{
				if ((psIni->sScale4.bSerial == false)
					&& (MessageBox::Show("Scale ERROR, continue ?", "Lane D",
						System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
						== System::Windows::Forms::DialogResult::No))
				{
					return;
				}
			}
			else if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
			{
				if (psIni->sScale4.bSerial == false && !pAll->bRemContinue)
				{
					pAll->bRemContinue = false;
					return;
				}
				else
					pAll->bRemContinue = false;

			}
			else if (pAll->eAsType == A_REMOTE)
			{
				if ((psIni->sScale4.bSerial == false)
					&& (MessageBox::Show("Scale ERROR, continue ?", "Lane D",
						System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
						== System::Windows::Forms::DialogResult::No))
				{
					nextBt4->Enabled = false;
					int i = 0;
					int j = 0;
					Cmd^ pCmd = gcnew Cmd();

					pCmd->cId = CL_KEY;
					pCmd->nKey = K_NEXTCONNO4;
					pAll->qCmd->Enqueue(pCmd);

					pAll->cWaitT = 1;

					while (pAll->cWaitT > 0 && i++ < 5)
						Thread::Sleep(100);

					pCmd = gcnew Cmd();
					pCmd->cId = CL_INI;
					pAll->qCmd->Enqueue(pCmd);

					while (pAll->cWaitT > 0 && j++ < 5)
						Thread::Sleep(100);
					nextBt4->Enabled = true;
					return;
				}
				else
				{
					nextBt4->Enabled = false;
					int i = 0;
					int j = 0;
					Cmd^ pCmd = gcnew Cmd();

					pCmd->cId = CL_KEY;
					pCmd->nKey = K_NEXTCONYES4;
					pAll->qCmd->Enqueue(pCmd);

					pAll->cWaitT = 1;

					while (pAll->cWaitT > 0 && i++ < 5)
						Thread::Sleep(100);

					pCmd = gcnew Cmd();
					pCmd->cId = CL_INI;
					pAll->qCmd->Enqueue(pCmd);

					while (pAll->cWaitT > 0 && j++ < 5)
						Thread::Sleep(100);
					nextBt4->Enabled = true;
				}
			}
			bAuto4 = true;

			customer4->BackColor = COL_G;
			customer4->ReadOnly = true;
			Job4->BackColor = COL_G;
			Job4->ReadOnly = true;
			material4->BackColor = COL_G;
			material4->ReadOnly = true;
			truck4->BackColor = COL_W;
			truck4->Select();
			target4->BackColor = COL_W;
			target4->ReadOnly = false;		//DC 3.2.4

											//---------------------------------------
			while (!bDone && (nIdx < pAll->lJob->Count))
			{
				pJob4 = pAll->lJob[nIdx++];

				if (psIni->bBotScale)
				{
					if ((pJob4->eStatus != S_NEW) || (pJob4->nSilo < 10))
						continue;
				}
				else
				{
					if ((pJob4->eStatus != S_NEW) || (pJob4->nSilo != 4))
						continue;
				}
				if (pAll->eAsType != A_REMOTE)							//DC 4.1.0
					poLog->log(C_READ, &psIni->sLog4, pJob4->nLogIdx);
				if (gcnew String(psIni->sLog4.sT.mix_code) != ""
					&& (gcnew String(psIni->sLog4.sT.mix_code) != gcnew String(psIni->asSilos[psIni->sLog4.nSilo - 1].acProduct))) //DC 4.0.1
				{
					if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
					{
						return;
					}
					else if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
					{
						MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[psIni->sLog4.nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog4.sT.ticket_num
							+ " for Truck: " + gcnew String(psIni->sLog4.sT.truck_id)
							+ ", NEED Material: " + gcnew String(psIni->sLog4.sT.mix_code), "Lane A",
							System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
						//						 bWrongMet = true;	//DC 4.0.1
						return;
					}
					else if (pAll->eAsType == A_REMOTE)
					{
						MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[psIni->sLog4.nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog4.sT.ticket_num
							+ " for Truck: " + gcnew String(psIni->sLog4.sT.truck_id)
							+ ", NEED Material: " + gcnew String(psIni->sLog4.sT.mix_code), "Lane A",
							System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
						//						 bWrongMet = true;	//DC 4.0.1
						return;
					}
				}
				pAll->lJob->Remove(pJob4);
				if (pAll->eAsType != A_REMOTE)
				{
					psIni->nTickets4--;
				}

				pTruck4 = findTruck(psIni->sLog4.sT.truck_id);

				customer4->Text = gcnew String(psIni->sLog4.sT.customer_name_1);
				Job4->Text = gcnew String(psIni->sLog4.sT.project_code);
				material4->Text = gcnew String(psIni->sLog4.sT.mix_code);
				tic_num4->Text = psIni->sLog4.sT.ticket_num.ToString();
				truck4->Text = gcnew String(psIni->sLog4.sT.truck_id);
				if (psIni->bScaleInLB)	//DC 3.2.0
					target4->Text = psIni->sLog4.sT.load_size.ToString("F00");
				else
					target4->Text = psIni->sLog4.sT.load_size.ToString("F02");
				plant4->Text = psIni->sLog4.sT.plant_num.ToString();

				if (psIni->bBotScale)
				{
					switch (psIni->sLog4.nSilo)
					{
					case 10:	siloBar4_Click(nullptr, nullptr);	break;
					case 11:	siloBar42_Click(nullptr, nullptr);	break;
					case 12:	siloBar43_Click(nullptr, nullptr);	break;
					}
				}
				bDone = true;
			}
			if (bDone)
				setState4(S_NEXT);

			pAll->bRemoteCall = false;	//DC 4.1.0
		}
	}

			 //-------------------------------------------------------------------------
	private: System::Void autoBt4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bAuto4 = false;

		customer4->BackColor = COL_W;
		customer4->ReadOnly = false;
		Job4->BackColor = COL_W;
		Job4->ReadOnly = false;
		material4->BackColor = COL_W;
		material4->ReadOnly = false;
		truck4->BackColor = COL_W;
		target4->BackColor = COL_W;

		customer4->Text = nullptr;
		Job4->Text = nullptr;
		material4->Text = nullptr;
		truck4->Text = nullptr;
		target4->Text = nullptr;
		tic_num4->Text = psIni->sInv.nLastTicket.ToString();
		plant4->Text = psIni->nPlantNum1.ToString();

		memset(&psIni->sLog4, 0, sizeof(LOG_REC));
		psIni->sLog4.eJobStatus = S_NEW;
		psIni->sLog4.sT.mix_price = psIni->fTonPrice;
		psIni->sLog4.fTax = psIni->fTaxRate;
		psIni->sLog4.sT.ticket_num = psIni->sInv.nLastTicket++;
		psIni->sLog4.sT.plant_num = psIni->nPlantNum1;

		siloBar4_Click(nullptr, nullptr);
		setState4(S_NEXT);
	}

			 //================================================================
	private: System::Void readyBt4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (pAll->eAsType == A_REMOTE)		//DC 4.1.0
		{
			readyBt4->Enabled = false;
			//double fLoadChg;
			Cmd^ pCmd = gcnew Cmd();


			//DC 4.1.1
			/*fLoadChg = Convert::ToDouble(target4->Text);
			if(pJob4->fLoad != fLoadChg)
			{
			pJob4->fLoad = fLoadChg;
			pAll->pJob4 = pJob4;
			int k = 0;
			pCmd = gcnew Cmd();
			pCmd->cId = CL_SJOB4;
			pAll->qCmd->Enqueue(pCmd);

			pAll->cWaitT = 1;

			while(pAll->cWaitT > 0 && k++ < 5)
			Thread::Sleep(100);
			}*/

			int i = 0;
			int j = 0;
			//Cmd^ pCmd = gcnew Cmd();
			pCmd = gcnew Cmd();
			pCmd->cId = CL_KEY;
			pCmd->nKey = K_READY4;
			pAll->qCmd->Enqueue(pCmd);

			pAll->cWaitT = 1;

			while (pAll->cWaitT > 0 && i++ < 5)
				Thread::Sleep(100);

			pCmd = gcnew Cmd();
			pCmd->cId = CL_INI;
			pAll->qCmd->Enqueue(pCmd);

			while (pAll->cWaitT > 0 && j++ < 5)
				Thread::Sleep(100);
			readyBt4->Enabled = true;
		}

		if (pAll->eAsType != A_REMOTE)	//DC 4.1.0
			pAll->nKey = 0;

		if (!psIni->bBotScale)
		{
			if ((psIni->sScale4.dValue < 0.0)
				&& (MessageBox::Show("Scale under 0.0, continue ?", "Lane D",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
			else if ((psIni->sScale4.dValue > psIni->sScale4.fTolerance)
				&& (MessageBox::Show("Scale over 0.0, continue ?", "Lane D",
					System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
					== System::Windows::Forms::DialogResult::No))
			{
				return;
			}
		}

		try
		{
			if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
			{
				//						 pJob4 = pAll->pJob4;
				//						 target4->Text = pJob4->fLoad.ToString("F00");
				/*this->groupBox4->Refresh();*/
			}
			psIni->sLog4.sT.load_size = Convert::ToDouble(target4->Text);
			if (pAll->eAsType != A_REMOTE)	// && !pAll->bRemoteCall)
				pJob4->fLoad = Convert::ToDouble(target4->Text);

			//else if(pAll->eAsType == A_REMOTE)
			//{
			// /*pJob4->fLoad = Convert::ToDouble(target4->Text);
			// pAll->pJob4 = pJob4;
			// int i = 0;	
			//Cmd^ pCmd = gcnew Cmd();
			// pCmd = gcnew Cmd();
			//pCmd->cId = CL_SJOB4;
			//pAll->qCmd->Enqueue(pCmd);

			//pAll->cWaitT = 1;

			//while(pAll->cWaitT > 0 && i++ < 5)
			//Thread::Sleep(100);*/
			//}
		}
		catch (System::FormatException^)
		{
			if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
			{
				MessageBox::Show("Please correct numeric entry !", "Lane D",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			else if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
			{
				return;
			}
			else if (pAll->eAsType == A_REMOTE)
			{
				MessageBox::Show("Please correct numeric entry !", "Lane D",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}

		// find truck
		pTruck4 = findTruck(psIni->sLog4.sT.truck_id);
		if (pTruck4 == nullptr)
		{
			if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
			{
				MessageBox::Show("Truck " + gcnew String(psIni->sLog4.sT.truck_id) + " not found !", "Lane D",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			else if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
			{
				return;
			}
			else if (pAll->eAsType == A_REMOTE)
			{
				MessageBox::Show("Truck " + gcnew String(psIni->sLog4.sT.truck_id) + " not found !", "Lane D",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}

		// test target versus truck capacity
		if (psIni->sLog4.sT.load_size > pTruck4->nCapacity)	//DC 3.2.4 && !psIni->bUseTrkMax)		//DC 3.2.0
		{
			if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
			{
				MessageBox::Show("Target exceeds truck capacity !", "Lane D",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			else if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
			{
				return;
			}
			else if (pAll->eAsType == A_REMOTE)
			{
				MessageBox::Show("Target exceeds truck capacity !", "Lane D",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}

		if (!bAuto4)
		{
			str2arr(customer4->Text, psIni->sLog4.sT.customer_name_1);
			str2arr(Job4->Text, psIni->sLog4.sT.project_code);
			str2arr(material4->Text, psIni->sLog4.sT.mix_code);
			str2arr(truck4->Text, psIni->sLog4.sT.truck_id);

			if (pAll->eAsType != A_REMOTE)
			{
				pJob4 = gcnew Job();
				pJob4->nLogIdx = poLog->log(C_APPEND, &psIni->sLog4, 0);
				pJob4->nTicket = psIni->sLog4.sT.ticket_num;
				pJob4->nSilo = psIni->sLog4.nSilo;
				pJob4->stCustomer = gcnew String(psIni->sLog4.sT.customer_name_1);
				pJob4->eStatus = psIni->sLog4.eJobStatus;
				//					 psIni->sLog4.fTruckTare = psIni->sScale4.dValue;
			}
		}

		// lock job record
		customer4->BackColor = COL_G;
		customer4->ReadOnly = true;
		Job4->BackColor = COL_G;
		Job4->ReadOnly = true;
		material4->BackColor = COL_G;
		material4->ReadOnly = true;
		truck4->BackColor = COL_G;
		target4->BackColor = COL_G;
		target4->ReadOnly = true;		//DC 3.2.4

		nextBt4->Enabled = true;
		nextBt4->BackColor = COL_TRANS;
		autoBt4->Enabled = true;
		autoBt4->BackColor = COL_TRANS;

		if (psIni->bBotScale)
		{
			if (!psIni->bSendBitWise)			//DC 4.0.1
				psIni->sLog4.fTruckTare = psIni->sScale4.dValue;
			if (psIni->bUseTrkMax)				//DC 3.2.0
				psIni->sLog4.sT.load_size = psIni->sLog4.sT.load_size - psIni->sLog4.fTruckTare;
		}
		fCumTarget4 = 0.0;
		fFall4 = 0;
		setDrops4(psIni->sLog4.nDrops);
		setState4(S_READY);
	}

			 //--------------------------------------------------------------------
	private: System::Void printOnly4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// if(pAll->eAsType == A_REMOTE)	//DC 4.1.0
		// {
		//	int i = 0;
		//	Cmd^ pCmd = gcnew Cmd();
		//	pCmd->cId = CL_KEY;
		//	pCmd->nKey = K_PRINT4;
		//	pAll->qCmd->Enqueue(pCmd);

		//	pAll->cWaitT = 1;

		//	while(pAll->cWaitT > 0 && i++ < 5)
		//	Thread::Sleep(100);
		//}
		//else
		{
			if (taxExempt4->Checked)
				psIni->sLog4.fTax = 0;
			poLog->calcTarget(&psIni->sLog4);

			if (psIni->bScaleInLB)	//DC 4.2.0
			{
				tareD->Text = psIni->sLog4.fTruckTare.ToString("F00");
				grossD->Text = psIni->sLog4.fGross.ToString("F00");
			}
			else
			{
				tareD->Text = psIni->sLog4.fTruckTare.ToString("F02");
				grossD->Text = psIni->sLog4.fGross.ToString("F02");
			}
			groupBoxD->Visible = true;
		}
	}

			 //--------------------------------------------------------------------
	private: System::Void okD_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (pAll->eAsType == A_REMOTE)	//DC 4.1.0
		{
			pJob4->fTare = Convert::ToDouble(tareD->Text);
			pJob4->fGross = Convert::ToDouble(grossD->Text);

			int j = 0;
			pAll->cWaitT = 1;
			Cmd^ pCmd = gcnew Cmd();
			pCmd = gcnew Cmd();
			pCmd->cId = CL_SJOB4;
			pAll->qCmd->Enqueue(pCmd);

			while (pAll->cWaitT > 0 && j++ < 5)
				Thread::Sleep(100);

			int i = 0;
			pCmd->cId = CL_KEY;
			pCmd->nKey = K_PRINT4;
			pAll->qCmd->Enqueue(pCmd);

			pAll->cWaitT = 1;

			while (pAll->cWaitT > 0 && i++ < 5)
				Thread::Sleep(100);

			groupBoxD->Visible = false;
		}
		else
		{
			int nPrinter;
			if (pAll->bRemoteCall)
			{
				pAll->bRemoteCall = false;
				/* Job^ pJob;
				pJob = pAll->pJob;*/
				nPrinter = 4;
				try
				{
					psIni->sLog4.fTruckTare = pAll->pJob4->fTare;
					psIni->sLog4.fGross = pAll->pJob4->fGross;
					psIni->sLog4.fLoad = psIni->sLog4.fGross - psIni->sLog4.fTruckTare;
				}
				catch (System::FormatException^)
				{
					MessageBox::Show("Please correct numeric entry !", "Lane D",
						System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}
			}
			else
			{
				nPrinter = 4;
				if (laneDCb1->Checked)
					nPrinter = 1;
				else if (laneDCb2->Checked)
					nPrinter = 2;
				try
				{
					psIni->sLog4.fTruckTare = Convert::ToDouble(tareD->Text);
					psIni->sLog4.fGross = Convert::ToDouble(grossD->Text);
					psIni->sLog4.fLoad = psIni->sLog4.fGross - psIni->sLog4.fTruckTare;
				}
				catch (System::FormatException^)
				{
					MessageBox::Show("Please correct numeric entry !", "Lane D",
						System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}
				groupBoxD->Visible = false;
			}

			poLog->calcLoad(&psIni->sLog4);
			poLog->printTicket(&psIni->sLog4, nPrinter, false);
			psIni->sLog4.eJobStatus = S_PRINTED;
			poLog->log(C_UPDATE, &psIni->sLog4, pJob4->nLogIdx);

			// add to old job list
			pJob4->stStatus = pAll->lStat[pJob4->eStatus];
			pAll->lOld->Add(pJob4);

			setState4(S_IDLE);
		}
	}

			 //================================================================
	private: System::Void setDrops4(int nDropsIn)
	{
		int	nDropsMin = (int)(psIni->sLog4.sT.load_size / psIni->fDropMaxL4) + 1;
		int nDrops = nDropsIn > nDropsMin ? nDropsIn : nDropsMin;

		// test size of drop against scale capacity
		fTarget4 = psIni->sLog4.sT.load_size / nDrops;
		fTol4 = max(psIni->fTarTolAbs, psIni->fTarTolPerc * fTarget4 / 100);
		truckBar4->Separators = nDrops - 1;
		psIni->sLog4.nDrops = nDrops;

		if (psIni->bBotScale)
		{
			switch (psIni->sLog4.nSilo)
			{
			case 10:  siloBar4->Target = fTarget4;	break;
			case 11:  siloBar42->Target = fTarget4;	break;
			case 12:  siloBar43->Target = fTarget4;	break;
			}
			scaleBar4->Target = fTarget4 + psIni->sLog4.fTruckTare;
		}
		else
		{
			siloBar4->Target = fTarget4;
			scaleBar4->Target = fTarget4;
		}
		switch (psIni->sLog4.nDrops)
		{
		case 1: drops41->Checked = true; break;
		case 2: drops42->Checked = true; break;
		case 3: drops43->Checked = true; break;
		case 4: drops44->Checked = true; break;
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void drops41_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops4(1);
	}
	private: System::Void drops42_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops4(2);
	}
	private: System::Void drops43_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops4(3);
	}
	private: System::Void drops44_Click(System::Object^  sender, System::EventArgs^  e)
	{
		setDrops4(4);
	}

			 //----------------------------------------------------------------
	private: double getFall4(void)
	{
		double fFall;
		int nIdx = (int)fTarget4;

		if (!psIni->bBotScale)
		{
			if (autoFall4->Checked)
				fFall = psIni->sInv.asFall4[nIdx].fFall / SAMPLE_NBR;
			else
				fFall = psIni->afManFall4[nIdx];
		}
		else
		{
			switch (psIni->sLog4.nSilo)
			{
			case 10:
				if (autoFall4->Checked)
					fFall = psIni->sInv.asFall10[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall10[nIdx];
				break;
			case 11:
				if (autoFall4->Checked)
					fFall = psIni->sInv.asFall11[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall11[nIdx];
				break;
			case 12:
				if (autoFall4->Checked)
					fFall = psIni->sInv.asFall12[nIdx].fFall / SAMPLE_NBR;
				else
					fFall = psIni->afManFall12[nIdx];
				break;
			}
		}
		return fFall;
	}

			 //-------------------------------------------------------------------------
	private: System::Void dropBt4_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		bool bSafe = psIni->nSafeTime > 0;
		readyBt4->Enabled = false;
		readyBt4->BackColor = COL_TRANS;

		str2arr(truck4->Text, psIni->sLog4.sT.truck_id);

		if (!psIni->bBotScale)			//#ifdef UPSCALE
		{
			fNewTarget4 = fTarget4;
		}
		else
		{
			if (pAll->eAsType == A_PROD)
				if (!bTruck4) return;

			if (bFirstDrop4 && !psIni->bSendBitWise)
				psIni->sLog4.fTruckTare = psIni->sScale4.dValue;
			fCumTarget4 += fTarget4;
		}
		fFall4 = getFall4();

		if (psIni->bSafeJob)
			bSafe = bFirstDrop4;

		if (bSafe)
			setState4(S_SAFE);
		else
			setState4(S_DROP);
		bFirstDrop4 = false;
	}

			 //-------------------------------------------------------------------------
	private: System::Void dischBt4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		dischBt4->BackColor = COL_PGREEN;
		setState4(S_DISCH);
	}

			 //-------------------------------------------------------------------------
	private: System::Void pause4_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		if (pAll->eAsType == A_REMOTE)
		{
			int i = 0;
			Cmd^ pCmd = gcnew Cmd();
			pCmd->cId = CL_KEY;
			pCmd->nKey = K_HOLD4;
			pAll->qCmd->Enqueue(pCmd);

			pAll->cWaitT = 1;

			while (pAll->cWaitT > 0 && i++ < 2)
				Thread::Sleep(100);
		}

		{
			switch (psIni->sLog4.eState)
			{
			case S_DROP:			setState4(S_HOLD_DROP); //setState4(S_HOLD_SETTLE); 
				pauseBt4->BackColor = COL_HOLD;
				break;
			case S_ASETTLE:		setState4(S_HOLD_ASETTLE);
				pauseBt4->BackColor = COL_HOLD;
				break;
			case S_DISCH:			setState4(S_HOLD_DISCH);
				pauseBt4->BackColor = COL_HOLD;
				break;
			case S_ADD:			setState4(S_HOLD_ADD); //DC 4.0.0
				pauseBt4->BackColor = COL_HOLD;
				break;

			case S_HOLD_ADD:		setState4(S_ADD);		//DC 4.0.0
				pauseBt4->BackColor = COL_HOLDK;
				break;
			case S_HOLD_DROP:		setState4(S_DROP);
				pauseBt4->BackColor = COL_HOLDK;
				break;
			case S_HOLD_ASETTLE:	setState4(S_ASETTLE);
				pauseBt4->BackColor = COL_HOLDK;
				break;
			case S_HOLD_DISCH:		setState4(S_DISCH);
				pauseBt4->BackColor = COL_HOLDK;
				break;
			}
		}
	}
			 //-------------------------------------------------------------------------
	private: System::Void stopBt4_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		switch (psIni->sLog4.eState)
		{
		case S_IDLE:
			return;
		case S_NEXT:
		case S_READY:
			if (bAuto4)
			{
				if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
				{
					resetTargetOutput();		//DC 4.0.1

					if (MessageBox::Show("Void Ticket ?", "Lane D",
						System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
						== System::Windows::Forms::DialogResult::Yes)
					{
						pJob4->eStatus = S_VOIDED;
						psIni->sLog4.eJobStatus = S_VOIDED;
						psIni->sLog4.eStop = A_VOID;
						psIni->sLog4.eState = S_ABORT;
					}
					else
					{
						pJob4->eStatus = S_NEW;
						pAll->lJob->Add(pJob4);

						if (!psIni->bBotScale)
							switch (psIni->sLog4.nSilo)
							{
							case 1: pAll->nTickets1++; break;
							case 2: pAll->nTickets2++; break;
							case 3: pAll->nTickets3++; break;
							case 4: psIni->nTickets4++; break;
							}
						else
							switch (psIni->sLog4.nSilo)
							{
							case 1:
							case 2:
							case 3: pAll->nTickets1++; break;
							case 4:
							case 5:
							case 6: pAll->nTickets2++; break;
							case 7:
							case 8:
							case 9: pAll->nTickets3++; break;
							case 10:
							case 11:
							case 12: psIni->nTickets4++; break;
							}
						setState4(S_IDLE);
					}
				}
				else if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
				{
					resetTargetOutput();		//DC 4.0.1

					if (pAll->bRemoteVoid)
					{
						pJob4->eStatus = S_VOIDED;
						psIni->sLog4.eJobStatus = S_VOIDED;
						psIni->sLog4.eStop = A_VOID;
						psIni->sLog4.eState = S_ABORT;
					}
					else
					{
						pJob4->eStatus = S_NEW;
						pAll->lJob->Add(pJob4);

						if (!psIni->bBotScale)
							switch (psIni->sLog4.nSilo)
							{
							case 1: pAll->nTickets1++; break;
							case 2: pAll->nTickets2++; break;
							case 3: pAll->nTickets3++; break;
							case 4: psIni->nTickets4++; break;
							}
						else
							switch (psIni->sLog4.nSilo)
							{
							case 1:
							case 2:
							case 3: pAll->nTickets1++; break;
							case 4:
							case 5:
							case 6: pAll->nTickets2++; break;
							case 7:
							case 8:
							case 9: pAll->nTickets3++; break;
							case 10:
							case 11:
							case 12: psIni->nTickets4++; break;
							}
						setState4(S_IDLE);
					}
				}
				else if (pAll->eAsType == A_REMOTE)
				{
					if (MessageBox::Show("Void Ticket ?", "Lane D",
						System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
						== System::Windows::Forms::DialogResult::Yes)
					{
						int k = 0;
						Cmd^ pCmd = gcnew Cmd();
						pCmd = gcnew Cmd();
						pCmd->cId = CL_ABORT4;
						pCmd->nKey = K_VOIDYES4;
						pAll->qCmd->Enqueue(pCmd);

						pAll->cWaitT = 1;

						while (pAll->cWaitT > 0 && k++ < 5)
							Thread::Sleep(100);
					}
					else
					{
						int k = 0;
						Cmd^ pCmd = gcnew Cmd();
						pCmd = gcnew Cmd();
						pCmd->cId = CL_ABORT4;
						pCmd->nKey = K_VOIDNO4;
						pAll->qCmd->Enqueue(pCmd);

						pAll->cWaitT = 1;

						while (pAll->cWaitT > 0 && k++ < 5)
							Thread::Sleep(100);
					}
				}
			}
			else
				setState4(S_IDLE);
			return;

		case S_DROP:     setState4(S_HOLD_SETTLE); break;
		case S_DISCH:    setState4(S_HOLD_DISCH); break;
		}
		pAll->bRemoteCall = false;		//DC 4.1.0
		StopForm^ pStop = gcnew StopForm(&psIni->sLog4, pJob4);
		pStop->Show();
	}

			 //-------------------------------------------------------------------------
	private: System::Void addBt4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bool bAdd = true;
		bool bAsk = false;
		addBt4->Enabled = false;

		if (!psIni->bBotScale)
		{
			bAsk = (fLoad4 + psIni->dAddQty) > psIni->sLog4.sT.load_size;
		}
		else
		{
			if (!psIni->bPdmPlc)
				bAsk = (fLoad4 + psIni->dAddQty) > fCumTarget4;
			else
				bAsk = (fLoad4 + psIni->asSilos[psIni->sLog4.nSilo - 1].dAddTol) > fCumTarget4;		//DC 4.0.0
		}

		if (bAsk)
		{
			bStopAdd4 = true;		//DC 4.0.0
			if (MessageBox::Show("TRUCK CAPACITY WARNING, continue ?", "Lane D",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::No)
				bAdd = false;
		}
		if (bAdd)
			setState4(S_ADD);
		else
			setState4(S_UPDATE);
	}

	private: bool testHold4(void)
	{
		if (psIni->bHold4 && psIni->sLog4.eState != S_HOLD)
		{
			ePrevHold4 = psIni->sLog4.eState;
			setState4(S_HOLD);
			pauseBt4->BackColor = COL_HOLD;
			return true;
		}
		return false;
	}

#pragma endregion

#pragma region MENU
			 //-------------------------------------------------------------------------
	private: System::Void aboutMenuItem_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		//About^ about = gcnew About(pAll);
		//about->Show();
	}

			 //----------------------------------------------------------------
	private: System::Void printManualJobs_Click(System::Object^  sender, System::EventArgs^  e)
	{
		poLog->printManual();
	}

			 //-------------------------------------------------------------------------
	private: System::Void exitMenuItem_Click(System::Object^  sender,
		System::EventArgs^  e)
	{
		Application::Exit();
	}

			 //-------------------------------------------------------------------------
	private: System::Void inventoryMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		InvForm^ inv = gcnew InvForm(psIni);
		inv->Show();
	}

			 //-------------------------------------------------------------------------
	private: System::Void reprintToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (pAll->eAsType == A_REMOTE)
		{
			int i = 0;
			Cmd^ pCmd;
			pCmd = gcnew Cmd();
			pCmd->cId = CL_OLD;
			pAll->qCmd->Enqueue(pCmd);
			pAll->cWaitT = 1;
			while (pAll->cWaitT > 0 && i++ < 5)
				Thread::Sleep(100);
		}
		ReprintF^ rep = gcnew ReprintF(pAll, poLog);
		rep->Show();
	}

			 //--------------------------------------------------------------------
	private: System::Void testToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->bTest = !psIni->bTest;

		rdLb->Visible = psIni->bTest;
		wrLb->Visible = psIni->bTest;

		optoErr->Visible = psIni->bTest;
		dbLb->Visible = psIni->bTest;
		dbLb1->Visible = psIni->bTest;
		dbLb2->Visible = psIni->bTest;

		scale1->Visible = psIni->bTest;
		scale2->Visible = psIni->bTest;
		scale3->Visible = psIni->bTest;
		scale4->Visible = psIni->bTest;

		cnt1->Visible = psIni->bTest;
		cnt2->Visible = psIni->bTest;
		cnt3->Visible = psIni->bTest;
		cnt4->Visible = psIni->bTest;

		silo1->Visible = psIni->bTest;
		silo2->Visible = psIni->bTest;
		silo3->Visible = psIni->bTest;
		silo4->Visible = psIni->bTest;

		flow1->Visible = psIni->bTest;
		flow2->Visible = psIni->bTest;
		flow3->Visible = psIni->bTest;
		flow4->Visible = psIni->bTest;
		//DC 4.0.0
		lane1StatLB->Visible = psIni->bTest;
		lane2StatLB->Visible = psIni->bTest;
		lane3StatLB->Visible = psIni->bTest;
		lane4StatLB->Visible = psIni->bTest;
	}
			 //-------------------------------------------------------------------------
	private: System::Void ulinkMsgToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		pAll->bUlink = !pAll->bUlink;
		testBox->BackColor = Color::Honeydew;
		testBox->Visible = pAll->bUlink;
	}

			 //-------------------------------------------------------------------------
	private: System::Void exceptionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		pAll->bExcept = !pAll->bExcept;
		testBox->BackColor = Color::Khaki;
		testBox->Visible = pAll->bExcept;
	}
			 //-------------------------------------------------------------------------
	private: System::Void testBox_DoubleClick(System::Object^  sender, System::EventArgs^  e)
	{
		pAll->pTestBox = "";
	}
#pragma endregion

#pragma region RS485

			 //-------------------------------------------------------------------------
			 // stop/start RS485 transmission
			 //-------------------------------------------------------------------------
	private: System::Void optoLb_Click(System::Object^  sender, System::EventArgs^  e)
	{
#ifdef SIM
		//				 b485Ok = !b485Ok;
#endif
	}

	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (pAll->eAsType != A_REMOTE)
		{
			pictureSplash->Enabled = false;
			pictureSplash->Visible = false;
		}
	}
#pragma endregion

#pragma region PRINTER
#ifdef PRINT_SER
			 //-------------------------------------------------------------------------
	private: System::Void printerThread_DoWork(System::Object^  sender,
		System::ComponentModel::DoWorkEventArgs^  e)
	{
		while (true)
		{
			// Create a SerialPort.
			SerialPort port(e->Argument->ToString(), psIni->nPrinterBaud);

			try
			{
				port.Open();

				while (true)
				{
					if (qPrint->Count > 0)
					{
						//printerLb->BackColor = COL_PGREEN;
						port.Write((String^)qPrint->Dequeue());
					}
					else
					{
						Thread::Sleep(500);
						printerLb->BackColor = Color::WhiteSmoke;
					}
				}
			}
			catch (System::UnauthorizedAccessException^ e)
			{
				Console::WriteLine("UnauthorizedAccessException: {0}", e);
			}
			catch (IO::IOException^ e)
			{
				Console::WriteLine("IO Exception: {0}", e);
			}
			// Close everything.
			port.Close();
			psIni->nPrinterOk = false;

			Thread::Sleep(9000);
			psIni->nPrinterOk = true;
			Thread::Sleep(1000);
		}
	}
#endif			

#pragma endregion

#pragma region FALL
			 //================================================================
	private: System::Void flow1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall1, psIni->sInv.asFall1, psIni->sInv.asAdapt1, 1, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall2, psIni->sInv.asFall2, psIni->sInv.asAdapt2, 2, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall3, psIni->sInv.asFall3, psIni->sInv.asAdapt3, 3, psIni->bBotScale);
		Fall->Show();
	}

			 //----------------------------------------------------------------
	private: System::Void flow4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall;

		if (psIni->bBotScale)
			Fall = gcnew FallFm(psIni->afManFall4, psIni->sInv.asFall4, psIni->sInv.asAdapt4, 4, psIni->bBotScale);
		else
			Fall = gcnew FallFm(psIni->afManFall2, psIni->sInv.asFall2, psIni->sInv.asAdapt2, 2, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow5_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall5, psIni->sInv.asFall5, psIni->sInv.asAdapt5, 5, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow6_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall6, psIni->sInv.asFall6, psIni->sInv.asAdapt6, 6, psIni->bBotScale);
		Fall->Show();
	}
			 //----------------------------------------------------------------
	private: System::Void flow7_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall;

		if (psIni->bBotScale)
			Fall = gcnew FallFm(psIni->afManFall7, psIni->sInv.asFall7, psIni->sInv.asAdapt7, 7, psIni->bBotScale);
		else
			Fall = gcnew FallFm(psIni->afManFall3, psIni->sInv.asFall3, psIni->sInv.asAdapt3, 3, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow8_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall8, psIni->sInv.asFall8, psIni->sInv.asAdapt8, 8, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow9_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall9, psIni->sInv.asFall9, psIni->sInv.asAdapt9, 9, psIni->bBotScale);
		Fall->Show();
	}
			 //DC 3.3.0 ----------------------------------------------------------------
	private: System::Void flow10_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall;

		if (psIni->bBotScale)
			Fall = gcnew FallFm(psIni->afManFall10, psIni->sInv.asFall10, psIni->sInv.asAdapt10, 10, psIni->bBotScale);
		else
			Fall = gcnew FallFm(psIni->afManFall4, psIni->sInv.asFall4, psIni->sInv.asAdapt4, 4, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow11_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall11, psIni->sInv.asFall11, psIni->sInv.asAdapt11, 11, psIni->bBotScale);
		Fall->Show();
	}
	private: System::Void flow12_Click(System::Object^  sender, System::EventArgs^  e)
	{
		FallFm^ Fall = gcnew FallFm(psIni->afManFall12, psIni->sInv.asFall12, psIni->sInv.asAdapt12, 12, psIni->bBotScale);
		Fall->Show();
	}
#pragma endregion

#pragma region SELECT_SILO
			 //-------------------------------------------------------------------------
	private: bool clickOk(LOG_REC *psLog, int nLane, int nSilo)
	{
		if (!psIni->bBotScale)
			return false;

		switch (psLog->eState)
		{
		case S_IDLE:
		case S_NEXT:
		case S_READY:
			//					case S_DROP:
			//					case S_SETTLE:
			//					case S_ADD:
			//					case S_ASETTLE:
			//					case S_DISCH_WAIT:
			//					case S_DISCH:
			//					case S_DSETTLE:
			//					case S_HOLD_DISCH:
			//					case S_ABORT:
			//					case S_UPDATE:
			//					case S_HORN:
			return true;

		case S_HOLD_DROP:
			if (psLog->nSilo != nSilo)
			{
				switch (nSilo)
				{
				case 1: siloBar1->BarColor = COL_HOLD;	break;
				case 2: siloBar12->BarColor = COL_HOLD; break;
				case 3: siloBar13->BarColor = COL_HOLD; break;
				case 4: siloBar2->BarColor = COL_HOLD;	break;
				case 5: siloBar22->BarColor = COL_HOLD; break;
				case 6: siloBar23->BarColor = COL_HOLD; break;
				case 7: siloBar3->BarColor = COL_HOLD;	break;
				case 8: siloBar32->BarColor = COL_HOLD; break;
				case 9: siloBar33->BarColor = COL_HOLD; break;
				case 10: siloBar4->BarColor = COL_HOLD;	break;
				case 11: siloBar42->BarColor = COL_HOLD; break;
				case 12: siloBar43->BarColor = COL_HOLD; break;
				}
			}
			return true;

		default:
			return false;
		}
	}

			 //-------------------------------------------------------------------------
	private: System::Void siloBar1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog1.sT.mix_code) != "") && (material1->Text != "")
			&& (gcnew String(psIni->sLog1.sT.mix_code) != gcnew String(psIni->asSilos[0].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[1 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog1.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog1.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog1.sT.mix_code), "Lane A",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog1, 1, 1))
			return;

		idleBar(siloBar12);
		idleBar(siloBar13);

		if (!psIni->bPdmPlc)
			nJogA = psIni->nSiloJog1;
		else
			nJogA = psIni->asSilos[0].nSiloJog;	//DC 4.0.0
		psIni->sLog1.nSilo = 1;
		siloBar1->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar1->Inventory = psIni->sInv.fInv1;
		siloBar1->Value = psIni->sInv.fInv1;
		siloBar1->BorderColor = Color::Black;
		siloBar1->Target = fTarget1;
		siloBar1->Idle = false;

		//				 setState1(psIni->sLog1.eState);
		this->truckBar1->Location = System::Drawing::Point(nOffs1, BAR);
		this->truckPic1->Location = System::Drawing::Point(nOffs1, PIC);

		if (pAll->pCam1 != nullptr)
		{
			webBrowser1->Navigate(pAll->pCam1);
		}
		if (pJob1) pJob1->nSilo = psIni->sLog1.nSilo;
	}

	private: System::Void siloBar12_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog1.sT.mix_code) != "") && (material1->Text != "")
			&& (gcnew String(psIni->sLog1.sT.mix_code) != gcnew String(psIni->asSilos[1].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[2 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog1.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog1.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog1.sT.mix_code), "Lane A",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog1, 1, 2))
			return;

		idleBar(siloBar1);
		idleBar(siloBar13);

		if (!psIni->bPdmPlc)
			nJogA = psIni->nSiloJog2;
		else
			nJogA = psIni->asSilos[1].nSiloJog;	//DC 4.0.0
		psIni->sLog1.nSilo = 2;
		siloBar12->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar12->Inventory = psIni->sInv.fInv2;
		siloBar12->Value = psIni->sInv.fInv2;
		siloBar12->BorderColor = Color::Black;
		siloBar12->Target = fTarget1;
		siloBar12->Idle = false;

		this->truckBar1->Location = System::Drawing::Point(nOffs2, BAR);
		this->truckPic1->Location = System::Drawing::Point(nOffs2, PIC);

		if (pAll->pCam2 != nullptr)
		{
			webBrowser1->Navigate(pAll->pCam2);
		}
		if (pJob1) pJob1->nSilo = psIni->sLog1.nSilo;
	}
	private: System::Void siloBar13_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog1.sT.mix_code) != "") && (material1->Text != "")
			&& (gcnew String(psIni->sLog1.sT.mix_code) != gcnew String(psIni->asSilos[2].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[3 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog1.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog1.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog1.sT.mix_code), "Lane A",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog1, 1, 3))
			return;

		idleBar(siloBar1);
		idleBar(siloBar12);

		if (!psIni->bPdmPlc)
			nJogA = psIni->nSiloJog3;
		else
			nJogA = psIni->asSilos[2].nSiloJog;	//DC 4.0.0
		psIni->sLog1.nSilo = 3;
		siloBar13->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar13->Inventory = psIni->sInv.fInv3;
		siloBar13->Value = psIni->sInv.fInv3;
		siloBar13->BorderColor = Color::Black;
		siloBar13->Target = fTarget1;
		siloBar13->Idle = false;

		this->truckBar1->Location = System::Drawing::Point(nOffs3, BAR);
		this->truckPic1->Location = System::Drawing::Point(nOffs3, PIC);

		if (pAll->pCam3 != nullptr)
		{
			webBrowser1->Navigate(pAll->pCam3);
		}
		if (pJob1) pJob1->nSilo = psIni->sLog1.nSilo;
	}

			 //-------------------------------------------------------------------------
	private: System::Void siloBar2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog2.sT.mix_code) != "") && (material2->Text != "")
			&& (gcnew String(psIni->sLog2.sT.mix_code) != gcnew String(psIni->asSilos[3].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[4 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog2.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog2.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog2.sT.mix_code), "Lane B",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog2, 2, 4))
			return;

		idleBar(siloBar22);
		idleBar(siloBar23);

		if (!psIni->bPdmPlc)
			nJogB = psIni->bBotScale ? psIni->nSiloJog4 : psIni->nSiloJog2;
		else
			nJogB = psIni->asSilos[3].nSiloJog;	//DC 4.0.0
		psIni->sLog2.nSilo = 4;
		siloBar2->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar2->Inventory = psIni->sInv.fInv4;
		siloBar2->Value = psIni->sInv.fInv4;
		siloBar2->BorderColor = Color::Black;
		siloBar2->Target = fTarget2;
		siloBar2->Idle = false;

		this->truckBar2->Location = System::Drawing::Point(nOffs1, BAR);
		this->truckPic2->Location = System::Drawing::Point(nOffs1, PIC);

		if (pAll->pCam4 != nullptr)
			webBrowser2->Navigate(pAll->pCam4);

		if (pJob2) pJob2->nSilo = psIni->sLog2.nSilo;
	}

	private: System::Void siloBar22_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog2.sT.mix_code) != "") && (material2->Text != "")
			&& (gcnew String(psIni->sLog2.sT.mix_code) != gcnew String(psIni->asSilos[4].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[5 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog2.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog2.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog2.sT.mix_code), "Lane B",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog2, 2, 5))
			return;

		idleBar(siloBar2);
		idleBar(siloBar23);

		if (!psIni->bPdmPlc)
			nJogB = psIni->nSiloJog5;
		else
			nJogB = psIni->asSilos[4].nSiloJog;	//DC 4.0.0
		psIni->sLog2.nSilo = 5;
		siloBar22->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar22->Inventory = psIni->sInv.fInv5;
		siloBar22->Value = psIni->sInv.fInv5;
		siloBar22->BorderColor = Color::Black;
		siloBar22->Target = fTarget2;
		siloBar22->Idle = false;
		this->truckBar2->Location = System::Drawing::Point(nOffs2, BAR);
		this->truckPic2->Location = System::Drawing::Point(nOffs2, PIC);

		if (pAll->pCam5 != nullptr)
			webBrowser2->Navigate(pAll->pCam5);

		if (pJob2) pJob2->nSilo = psIni->sLog2.nSilo;
	}

	private: System::Void siloBar23_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog2.sT.mix_code) != "") && (material2->Text != "")
			&& (gcnew String(psIni->sLog2.sT.mix_code) != gcnew String(psIni->asSilos[5].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[6 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog2.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog2.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog2.sT.mix_code), "Lane B",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog2, 2, 6))
			return;

		idleBar(siloBar2);
		idleBar(siloBar22);

		if (!psIni->bPdmPlc)
			nJogB = psIni->nSiloJog6;
		else
			nJogB = psIni->asSilos[5].nSiloJog;	//DC 4.0.0
		psIni->sLog2.nSilo = 6;
		siloBar23->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar23->Inventory = psIni->sInv.fInv6;
		siloBar23->Value = psIni->sInv.fInv6;
		siloBar23->BorderColor = Color::Black;
		siloBar23->Target = fTarget2;
		siloBar23->Idle = false;

		this->truckBar2->Location = System::Drawing::Point(nOffs3, BAR);
		this->truckPic2->Location = System::Drawing::Point(nOffs3, PIC);

		if (pAll->pCam6 != nullptr)
			webBrowser2->Navigate(pAll->pCam6);

		if (pJob2) pJob2->nSilo = psIni->sLog2.nSilo;
	}

			 //-------------------------------------------------------------------------
	private: System::Void siloBar3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog3.sT.mix_code) != "") && (material3->Text != "")
			&& (gcnew String(psIni->sLog3.sT.mix_code) != gcnew String(psIni->asSilos[6].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[7 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog3.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog3.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog3.sT.mix_code), "Lane C",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog3, 3, 7))
			return;

		idleBar(siloBar32);
		idleBar(siloBar33);

		if (!psIni->bPdmPlc)
			nJogC = psIni->bBotScale ? psIni->nSiloJog7 : psIni->nSiloJog3;
		else
			nJogC = psIni->asSilos[6].nSiloJog;	//DC 4.0.0
		psIni->sLog3.nSilo = 7;
		siloBar3->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar3->Inventory = psIni->sInv.fInv7;
		siloBar3->Value = psIni->sInv.fInv7;
		siloBar3->BorderColor = Color::Black;
		siloBar3->Target = fTarget3;
		siloBar3->Idle = false;

		this->truckBar3->Location = System::Drawing::Point(nOffs1, BAR);
		this->truckPic3->Location = System::Drawing::Point(nOffs1, PIC);
		if (pJob3) pJob3->nSilo = psIni->sLog3.nSilo;
	}

	private: System::Void siloBar32_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog3.sT.mix_code) != "") && (material3->Text != "")
			&& (gcnew String(psIni->sLog3.sT.mix_code) != gcnew String(psIni->asSilos[7].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[8 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog3.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog3.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog3.sT.mix_code), "Lane C",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog3, 3, 8))
			return;

		idleBar(siloBar3);
		idleBar(siloBar33);

		if (!psIni->bPdmPlc)
			nJogC = psIni->nSiloJog8;
		else
			nJogC = psIni->asSilos[7].nSiloJog;	//DC 4.0.0
		psIni->sLog3.nSilo = 8;
		siloBar32->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar32->Inventory = psIni->sInv.fInv8;
		siloBar32->Value = psIni->sInv.fInv8;
		siloBar32->BorderColor = Color::Black;
		siloBar32->Target = fTarget3;
		siloBar32->Idle = false;

		this->truckBar3->Location = System::Drawing::Point(nOffs2, BAR);
		this->truckPic3->Location = System::Drawing::Point(nOffs2, PIC);
		if (pJob3) pJob3->nSilo = psIni->sLog3.nSilo;
	}

	private: System::Void siloBar33_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog3.sT.mix_code) != "") && (material3->Text != "")
			&& (gcnew String(psIni->sLog3.sT.mix_code) != gcnew String(psIni->asSilos[8].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[9 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog3.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog3.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog3.sT.mix_code), "Lane C",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		if (!clickOk(&psIni->sLog3, 3, 9))
			return;

		idleBar(siloBar3);
		idleBar(siloBar32);

		if (!psIni->bPdmPlc)
			nJogC = psIni->nSiloJog9;
		else
			nJogC = psIni->asSilos[8].nSiloJog;	//DC 4.0.0
		psIni->sLog3.nSilo = 9;
		siloBar33->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar33->Inventory = psIni->sInv.fInv9;
		siloBar33->Value = psIni->sInv.fInv9;
		siloBar33->BorderColor = Color::Black;
		siloBar33->Target = fTarget3;
		siloBar33->Idle = false;

		this->truckBar3->Location = System::Drawing::Point(nOffs3, BAR);
		this->truckPic3->Location = System::Drawing::Point(nOffs3, PIC);
		if (pJob3) pJob3->nSilo = psIni->sLog3.nSilo;
	}

			 //DC 3.3.0 -------------------------------------------------------------------------
	private: System::Void siloBar4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (pAll->eAsType == A_REMOTE)
		{
			Cmd^ pCmd = gcnew Cmd();
			pCmd->cId = CL_KEY;
			pCmd->nKey = K_SBAR4;
			pAll->qCmd->Enqueue(pCmd);
		}
		else
		{
			if ((gcnew String(psIni->sLog4.sT.mix_code) != "") && (material4->Text != "")
				&& (gcnew String(psIni->sLog4.sT.mix_code) != gcnew String(psIni->asSilos[9].acProduct))) //DC 4.0.1
			{
				MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[10 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog4.sT.ticket_num
					+ " for Truck: " + gcnew String(psIni->sLog4.sT.truck_id)
					+ ", NEED Material: " + gcnew String(psIni->sLog4.sT.mix_code), "Lane R",
					System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			if (!clickOk(&psIni->sLog4, 4, 10))
				return;

			idleBar(siloBar42);
			idleBar(siloBar43);

			if (!psIni->bPdmPlc)
				nJogD = psIni->bBotScale ? psIni->nSiloJog10 : psIni->nSiloJog4;
			else
				nJogD = psIni->asSilos[9].nSiloJog;	//DC 4.0.0
			psIni->sLog4.nSilo = 10;
			siloBar4->DisableInv = psIni->bDisableInv;		//DC 4.0.1
			siloBar4->Inventory = psIni->sInv.fInv10;
			siloBar4->Value = psIni->sInv.fInv10;
			siloBar4->BorderColor = Color::Black;
			siloBar4->Target = fTarget4;
			siloBar4->Idle = false;

			this->truckBar4->Location = System::Drawing::Point(nOffs1, BAR);
			this->truckPic4->Location = System::Drawing::Point(nOffs1, PIC);
			if (pJob4) pJob4->nSilo = psIni->sLog4.nSilo;
		}
	}

	private: System::Void siloBar42_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog4.sT.mix_code) != "") && (material4->Text != "")
			&& (gcnew String(psIni->sLog4.sT.mix_code) != gcnew String(psIni->asSilos[10].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[11 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog4.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog4.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog4.sT.mix_code), "Lane R",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		if (!clickOk(&psIni->sLog4, 4, 11))
			return;

		idleBar(siloBar4);
		idleBar(siloBar43);

		if (!psIni->bPdmPlc)
			nJogD = psIni->nSiloJog11;
		else
			nJogD = psIni->asSilos[10].nSiloJog;	//DC 4.0.0
		psIni->sLog4.nSilo = 11;
		siloBar42->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar42->Inventory = psIni->sInv.fInv11;
		siloBar42->Value = psIni->sInv.fInv11;
		siloBar42->BorderColor = Color::Black;
		siloBar42->Target = fTarget4;
		siloBar42->Idle = false;

		this->truckBar4->Location = System::Drawing::Point(nOffs2, BAR);
		this->truckPic4->Location = System::Drawing::Point(nOffs2, PIC);
		if (pJob4) pJob4->nSilo = psIni->sLog4.nSilo;
	}

	private: System::Void siloBar43_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if ((gcnew String(psIni->sLog4.sT.mix_code) != "") && (material4->Text != "")
			&& (gcnew String(psIni->sLog4.sT.mix_code) != gcnew String(psIni->asSilos[11].acProduct))) //DC 4.0.1
		{
			MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[12 - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog4.sT.ticket_num
				+ " for Truck: " + gcnew String(psIni->sLog4.sT.truck_id)
				+ ", NEED Material: " + gcnew String(psIni->sLog4.sT.mix_code), "Lane R",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		if (!clickOk(&psIni->sLog4, 4, 12))
			return;

		idleBar(siloBar4);
		idleBar(siloBar42);

		if (!psIni->bPdmPlc)
			nJogD = psIni->nSiloJog12;
		else
			nJogD = psIni->asSilos[11].nSiloJog;	//DC 4.0.0
		psIni->sLog4.nSilo = 12;
		siloBar43->DisableInv = psIni->bDisableInv;		//DC 4.0.1
		siloBar43->Inventory = psIni->sInv.fInv12;
		siloBar43->Value = psIni->sInv.fInv12;
		siloBar43->BorderColor = Color::Black;
		siloBar43->Target = fTarget4;
		siloBar43->Idle = false;

		this->truckBar4->Location = System::Drawing::Point(nOffs3, BAR);
		this->truckPic4->Location = System::Drawing::Point(nOffs3, PIC);
		if (pJob4) pJob4->nSilo = psIni->sLog4.nSilo;
	}
#pragma endregion

#pragma region KEYS
			 //--------------------------------------------------------------------
	private: System::Void printTarget1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//			 psIni->sInv.bPrintTarget1 = printTarget1->Checked;
	}
	private: System::Void autoFall1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoFall1 = autoFall1->Checked;
	}
			 //--------------------------------------------------------------------
	private: System::Void adapt1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAdapt1 = adapt1->Checked;
	}

	private: System::Void jog1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bJog1 = jog1->Checked;
		addBt1->Visible = !psIni->sInv.bJog1;
	}
	private: System::Void autoDisch1_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoDisch1 = autoDisch1->Checked;
		dischBt1->Visible = !psIni->sInv.bAutoDisch1;
	}

			 //--------------------------------------------------------------------
	private: System::Void printTarget2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//			 psIni->sInv.bPrintTarget2 = printTarget2->Checked;
	}
	private: System::Void autoFall2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoFall2 = autoFall2->Checked;
	}
	private: System::Void adapt2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAdapt2 = adapt2->Checked;
	}
	private: System::Void jog2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bJog2 = jog2->Checked;
		addBt2->Visible = !psIni->sInv.bJog2;
	}
	private: System::Void autoDisch2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoDisch2 = autoDisch2->Checked;
		dischBt2->Visible = !psIni->sInv.bAutoDisch2;
	}

			 //--------------------------------------------------------------------
	private: System::Void printTarget3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//			 psIni->sInv.bPrintTarget3 = printTarget3->Checked;
	}
	private: System::Void autoFall3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoFall3 = autoFall3->Checked;
	}
	private: System::Void adapt3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAdapt3 = adapt3->Checked;
	}
	private: System::Void jog3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bJog3 = jog3->Checked;
		addBt3->Visible = !psIni->sInv.bJog3;
	}
	private: System::Void autoDisch3_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoDisch3 = autoDisch3->Checked;
		dischBt3->Visible = !psIni->sInv.bAutoDisch3;
	}

			 //DC 3.3.0 --------------------------------------------------------------------
	private: System::Void printTarget4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//			 psIni->sInv.bPrintTarget4 = printTarget4->Checked;
	}
	private: System::Void autoFall4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoFall4 = autoFall4->Checked;
	}
	private: System::Void adapt4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAdapt4 = adapt4->Checked;
	}
	private: System::Void jog4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bJog4 = jog4->Checked;
		addBt4->Visible = !psIni->sInv.bJog4;
	}
	private: System::Void autoDisch4_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		psIni->sInv.bAutoDisch4 = autoDisch4->Checked;
		dischBt4->Visible = !psIni->sInv.bAutoDisch4;
	}

			 //--------------------------------------------------------------------
	private: System::Void zoom1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bZoom1 = !bZoom1;

		if (bZoom1)
		{
			this->webBrowser1->Location = System::Drawing::Point(10, 220);
			this->webBrowser1->Size = System::Drawing::Size(800, 600);
		}
		else
		{
			this->webBrowser1->Location = System::Drawing::Point(65, 620);
			this->webBrowser1->Size = System::Drawing::Size(340, 240);
		}
	}
	private: System::Void zoom2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bZoom2 = !bZoom2;

		if (bZoom2)
		{
			this->webBrowser2->Location = System::Drawing::Point(200, 220);
			this->webBrowser2->Size = System::Drawing::Size(800, 600);
		}
		else
		{
			this->webBrowser2->Location = System::Drawing::Point(495, 620);
			this->webBrowser2->Size = System::Drawing::Size(340, 240);
		}
	}
	private: System::Void zoom3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		bZoom3 = !bZoom3;

		if (bZoom3)
		{
			this->webBrowser3->Location = System::Drawing::Point(460, 220);
			this->webBrowser3->Size = System::Drawing::Size(800, 600);
		}
		else
		{
			this->webBrowser3->Location = System::Drawing::Point(920, 620);
			this->webBrowser3->Size = System::Drawing::Size(340, 240);
		}
	}
	private: System::Void zoom4_Click(System::Object^  sender, System::EventArgs^  e)	//DC 3.3.0
	{
		bZoom4 = !bZoom4;

		if (bZoom4)
		{
			this->webBrowser4->Location = System::Drawing::Point(460, 220);
			this->webBrowser4->Size = System::Drawing::Size(800, 600);
		}
		else
		{
			this->webBrowser4->Location = System::Drawing::Point(920, 620);
			this->webBrowser4->Size = System::Drawing::Size(340, 240);
		}
	}
#pragma endregion

#pragma region SELECT_TRUCK
			 ///////////////////////////////////////////////////////////////////////
	private: System::Void trucksToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TruckFm^ truck = gcnew TruckFm(pAll);
		truck->Show();
	}
			 //--------------------------------------------------------------------
	private: System::Void dataGridTruck_RowHeaderMouseDoubleClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e)
	{
		if (pAll->lTruck->Count == 0) return;

		DataGridViewRow^ row = dataGridTruck->SelectedRows[0];
		Truck^ pTruck = (Truck^)row->DataBoundItem;

		switch (nLane)
		{
		case 0:
			truck1->Text = pTruck->stName;
			pTruck1 = pTruck;
			str2arr(truck1->Text, psIni->sLog1.sT.truck_id);
			break;
		case 1:
			truck2->Text = pTruck->stName;
			pTruck2 = pTruck;
			str2arr(truck2->Text, psIni->sLog2.sT.truck_id);
			break;
		case 2:
			truck3->Text = pTruck->stName;
			pTruck3 = pTruck;
			str2arr(truck3->Text, psIni->sLog3.sT.truck_id);
			break;
		case 3:		//DC 3.3.0
			truck4->Text = pTruck->stName;
			pTruck4 = pTruck;
			str2arr(truck4->Text, psIni->sLog4.sT.truck_id);
			break;
		}
		dataGridTruck->Visible = false;
	}

	private: System::Void dataGridTruck_ColumnHeaderMouseClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e)
	{
		dataGridTruck->Visible = false;
	}

			 //--------------------------------------------------------------------
	private: System::Void truckNum1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		nLane = 0;
		dataGridTruck->DataSource = nullptr;
		dataGridTruck->DataSource = this->truckBindingSource;
		dataGridTruck->Visible = true;
	}
	private: System::Void truckNum2_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		nLane = 1;
		dataGridTruck->DataSource = nullptr;
		dataGridTruck->DataSource = this->truckBindingSource;
		dataGridTruck->Visible = true;
	}
	private: System::Void truckNum3_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		nLane = 2;
		dataGridTruck->DataSource = nullptr;
		dataGridTruck->DataSource = this->truckBindingSource;
		dataGridTruck->Visible = true;
	}
	private: System::Void truckNum4_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		nLane = 3;
		dataGridTruck->DataSource = nullptr;
		dataGridTruck->DataSource = this->truckBindingSource;
		dataGridTruck->Visible = true;
	}
#pragma endregion

#pragma region JOB
			 //--------------------------------------------------------------------
	private: System::Void dataGridJob_RowHeaderMouseDoubleClick(System::Object^  sender
		, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e)
	{

		if (pAll->eAsType == A_REMOTE)	//DC 4.1.0
		{
			DataGridViewRow^ row = dataGridJob->SelectedRows[0];
			Job^ pJob = (Job^)row->DataBoundItem;

			pAll->pJob = pJob;
			int k = 0;
			Cmd^ pCmd = gcnew Cmd();
			pCmd = gcnew Cmd();
			pCmd->cId = CL_SJOB;
			pAll->qCmd->Enqueue(pCmd);

			pAll->cWaitT = 1;

			while (pAll->cWaitT > 0 && k++ < 5)
				Thread::Sleep(100);

			int i = 0;
			pCmd->cId = CL_KEY;
			pCmd->nKey = K_SJOB4;
			pAll->qCmd->Enqueue(pCmd);

			pAll->cWaitT = 1;

			while (pAll->cWaitT > 0 && i++ < 5)
				Thread::Sleep(100);

			dataGridJob->Visible = false;
		}
		else
		{
			Job^ pJob;

			if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
			{
				pJob = pAll->pJob;
				pAll->bRemoteCall = false;
				nLane = 3;
			}
			else
			{
				DataGridViewRow^ row = dataGridJob->SelectedRows[0];
				pJob = (Job^)row->DataBoundItem;
			}

			bWrongMet = false;		//DC 4.0.2
			int	nSilo;			//DC 4.0.2
			int i = 0;				//Dc 4.1.0

			switch (nLane)
			{
				//--------------------------------------------------------
			case 0:

				poLog->log(C_READ, &psIni->sLog1, pJob->nLogIdx);

				if (psIni->bBotScale)
				{
					//DC 4.0.1						 siloBar1_Click(nullptr, nullptr);
					if (!siloBar1->Idle)
					{
						nSilo = 1;
					}
					else if (!siloBar12->Idle)
					{
						nSilo = 2;
					}
					else if (!siloBar13->Idle)
					{
						nSilo = 3;
					}

					if (gcnew String(psIni->sLog1.sT.mix_code) != ""
						&& (gcnew String(psIni->sLog1.sT.mix_code) != gcnew String(psIni->asSilos[nSilo - 1].acProduct))) //DC 4.0.1
					{
						MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog1.sT.ticket_num
							+ " for Truck: " + gcnew String(psIni->sLog1.sT.truck_id)
							+ ", NEED Material: " + gcnew String(psIni->sLog1.sT.mix_code), "Lane A",
							System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
						bWrongMet = true;	//DC 4.0.1
						return;
					}
					else
					{
						//DC 4.0.1
						customer1->Text = pJob->stCustomer;
						tic_num1->Text = pJob->nTicket.ToString();

						Job1->Text = gcnew String(psIni->sLog1.sT.project_code);
						material1->Text = gcnew String(psIni->sLog1.sT.mix_code);
						truck1->Text = gcnew String(psIni->sLog1.sT.truck_id);
						if (psIni->bScaleInLB)	//DC 3.2.0
							target1->Text = psIni->sLog1.sT.load_size.ToString("F00");
						else
							target1->Text = psIni->sLog1.sT.load_size.ToString("F02");
						plant1->Text = psIni->sLog1.sT.plant_num.ToString("F00");
					}

					if (!bWrongMet)
					{
						switch (psIni->sLog1.nSilo)
						{
						case 1:	pAll->nTickets1--; break;// siloBar1_Click(nullptr, nullptr);	break;
						case 2:	pAll->nTickets1--; break;//siloBar12_Click(nullptr, nullptr);	break;
						case 3:	pAll->nTickets1--; break;//siloBar13_Click(nullptr, nullptr);	break;

						case 4:	pAll->nTickets2--; break;//siloBar1_Click(nullptr, nullptr);	break;
						case 5:	pAll->nTickets2--; break;//siloBar12_Click(nullptr, nullptr);	break;
						case 6:	pAll->nTickets2--; break;//siloBar13_Click(nullptr, nullptr);	break;

						case 7:	pAll->nTickets3--; break;//siloBar1_Click(nullptr, nullptr);	break;
						case 8:	pAll->nTickets3--; break;//siloBar12_Click(nullptr, nullptr);	break;
						case 9:	pAll->nTickets3--; break;//siloBar13_Click(nullptr, nullptr);	break;

						case 10:	psIni->nTickets4--; break;// siloBar4_Click(nullptr, nullptr);	break;
						case 11:	psIni->nTickets4--; break;// siloBar42_Click(nullptr, nullptr);	break;
						case 12:	psIni->nTickets4--; break;// siloBar43_Click(nullptr, nullptr);	break;
						default:	siloBar1_Click(nullptr, nullptr);	break;
						}
					}
				}
				else
					switch (psIni->sLog1.nSilo)
					{
					case 1:	pAll->nTickets1--;	break;
					case 2:	pAll->nTickets2--;	break;
					case 3:	pAll->nTickets3--;	break;
					case 4:	psIni->nTickets4--;	break;
					}
				//DC 4.0.1					 psIni->sLog1.nSilo = 1;
				if (!bWrongMet)	//DC 4.0.2
				{
					psIni->sLog1.nSilo = nSilo;
					pJob1 = pJob;
					pJob1->nSilo = psIni->sLog1.nSilo;
					pTruck1 = findTruck(psIni->sLog1.sT.truck_id);
					bAuto1 = true;
					setState1(S_NEXT);
					poLog->log(C_UPDATE, &psIni->sLog1, pJob->nLogIdx);
				}
				break;

				//--------------------------------------------------------
			case 1:
				poLog->log(C_READ, &psIni->sLog2, pJob->nLogIdx);

				if (psIni->bBotScale)
				{
					//DC 4.0.1						 siloBar2_Click(nullptr, nullptr);	
					if (!siloBar2->Idle)
					{
						nSilo = 4;
					}
					else if (!siloBar22->Idle)
					{
						nSilo = 5;
					}
					else if (!siloBar23->Idle)
					{
						nSilo = 6;
					}

					if (gcnew String(psIni->sLog2.sT.mix_code) != ""
						&& (gcnew String(psIni->sLog2.sT.mix_code) != gcnew String(psIni->asSilos[nSilo - 1].acProduct))) //DC 4.0.1
					{
						MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog2.sT.ticket_num
							+ " for Truck: " + gcnew String(psIni->sLog2.sT.truck_id)
							+ ", NEED Material: " + gcnew String(psIni->sLog2.sT.mix_code), "Lane B",
							System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
						bWrongMet = true;	//DC 4.0.1
						return;
					}
					else
					{
						//DC 4.0.1
						customer2->Text = pJob->stCustomer;
						tic_num2->Text = pJob->nTicket.ToString();

						Job2->Text = gcnew String(psIni->sLog2.sT.project_code);
						material2->Text = gcnew String(psIni->sLog2.sT.mix_code);
						truck2->Text = gcnew String(psIni->sLog2.sT.truck_id);
						if (psIni->bScaleInLB)	//DC 3.2.0
							target2->Text = psIni->sLog2.sT.load_size.ToString("F00");
						else
							target2->Text = psIni->sLog2.sT.load_size.ToString("F02");
						plant2->Text = psIni->sLog2.sT.plant_num.ToString();
					}

					if (!bWrongMet)
					{
						switch (psIni->sLog2.nSilo)
						{
						case 1:	pAll->nTickets1--; break;// siloBar2_Click(nullptr, nullptr);	break;
						case 2:	pAll->nTickets1--; break;// siloBar22_Click(nullptr, nullptr);	break;
						case 3:	pAll->nTickets1--; break;// siloBar23_Click(nullptr, nullptr);	break;

						case 4:	pAll->nTickets2--; break;// siloBar2_Click(nullptr, nullptr);	break;
						case 5:	pAll->nTickets2--; break;// siloBar22_Click(nullptr, nullptr);	break;
						case 6:	pAll->nTickets2--; break;// siloBar23_Click(nullptr, nullptr);	break;

						case 7:	pAll->nTickets3--; break;// siloBar2_Click(nullptr, nullptr);	break;
						case 8:	pAll->nTickets3--; break;// siloBar22_Click(nullptr, nullptr);	break;
						case 9:	pAll->nTickets3--; break;// siloBar23_Click(nullptr, nullptr);	break;

						case 10:	psIni->nTickets4--; break;// siloBar4_Click(nullptr, nullptr);	break;
						case 11:	psIni->nTickets4--; break;// siloBar42_Click(nullptr, nullptr);	break;
						case 12:	psIni->nTickets4--; break;// siloBar43_Click(nullptr, nullptr);	break;
						default:	siloBar2_Click(nullptr, nullptr);	break;
						}
					}
				}
				else
				{
					switch (psIni->sLog2.nSilo)
					{
					case 1:	pAll->nTickets1--;	break;
					case 2:	pAll->nTickets2--;	break;
					case 3:	pAll->nTickets3--;	break;
					case 4:	psIni->nTickets4--;	break;
					}
					//DC 4.0.1						 psIni->sLog2.nSilo = 2;
				}
				if (!bWrongMet)	//DC 4.0.2
				{
					psIni->sLog2.nSilo = nSilo;
					pJob2 = pJob;
					pJob2->nSilo = psIni->sLog2.nSilo;
					pTruck2 = findTruck(psIni->sLog2.sT.truck_id);
					bAuto2 = true;
					setState2(S_NEXT);
					poLog->log(C_UPDATE, &psIni->sLog2, pJob->nLogIdx);
				}
				break;

				//--------------------------------------------------------
			case 2:
				poLog->log(C_READ, &psIni->sLog3, pJob->nLogIdx);

				if (psIni->bBotScale)
				{

					//DC 4.0.1						 siloBar3_Click(nullptr, nullptr);
					if (!siloBar3->Idle)
					{
						nSilo = 7;
					}
					else if (!siloBar32->Idle)
					{
						nSilo = 8;
					}
					else if (!siloBar33->Idle)
					{
						nSilo = 9;
					}
					if (gcnew String(psIni->sLog3.sT.mix_code) != ""
						&& (gcnew String(psIni->sLog3.sT.mix_code) != gcnew String(psIni->asSilos[nSilo - 1].acProduct))) //DC 4.0.1
					{
						MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog3.sT.ticket_num
							+ " for Truck: " + gcnew String(psIni->sLog3.sT.truck_id)
							+ ", NEED Material: " + gcnew String(psIni->sLog3.sT.mix_code), "Lane C",
							System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
						bWrongMet = true;	//DC 4.0.1
						return;
					}
					else
					{
						//DC 4.0.1
						customer3->Text = pJob->stCustomer;
						tic_num3->Text = pJob->nTicket.ToString();

						Job3->Text = gcnew String(psIni->sLog3.sT.project_code);
						material3->Text = gcnew String(psIni->sLog3.sT.mix_code);
						truck3->Text = gcnew String(psIni->sLog3.sT.truck_id);
						if (psIni->bScaleInLB)	//DC 3.2.0
							target3->Text = psIni->sLog3.sT.load_size.ToString("F00");
						else
							target3->Text = psIni->sLog3.sT.load_size.ToString("F02");
						plant3->Text = psIni->sLog3.sT.plant_num.ToString();
					}

					if (!bWrongMet)
					{
						switch (psIni->sLog3.nSilo)
						{
						case 1:	pAll->nTickets1--; break;// siloBar3_Click(nullptr, nullptr);	break;
						case 2:	pAll->nTickets1--; break;// siloBar32_Click(nullptr, nullptr);	break;
						case 3:	pAll->nTickets1--; break;// siloBar33_Click(nullptr, nullptr);	break;

						case 4:	pAll->nTickets2--; break;// siloBar3_Click(nullptr, nullptr);	break;
						case 5:	pAll->nTickets2--; break;// siloBar32_Click(nullptr, nullptr);	break;
						case 6:	pAll->nTickets2--; break;// siloBar33_Click(nullptr, nullptr);	break;

						case 7:	pAll->nTickets3--; break;// siloBar3_Click(nullptr, nullptr);	break;
						case 8:	pAll->nTickets3--; break;// siloBar32_Click(nullptr, nullptr);	break;
						case 9:	pAll->nTickets3--; break;// siloBar33_Click(nullptr, nullptr);	break;

						case 10:	psIni->nTickets4--; break;// siloBar4_Click(nullptr, nullptr);	break;
						case 11:	psIni->nTickets4--; break;// siloBar42_Click(nullptr, nullptr);	break;
						case 12:	psIni->nTickets4--; break;// siloBar43_Click(nullptr, nullptr);	break;
						default:	siloBar3_Click(nullptr, nullptr);	break;
						}
					}
				}
				else
				{
					switch (psIni->sLog3.nSilo)
					{
					case 1:	pAll->nTickets1--;	break;
					case 2:	pAll->nTickets2--;	break;
					case 3:	pAll->nTickets3--;	break;
					case 4:	psIni->nTickets4--;	break;
					}
					//DC 4.0.1						 psIni->sLog3.nSilo = 3;
				}
				if (!bWrongMet)	//DC 4.0.2
				{
					psIni->sLog3.nSilo = nSilo;
					pJob3 = pJob;
					pJob3->nSilo = psIni->sLog3.nSilo;
					pTruck3 = findTruck(psIni->sLog3.sT.truck_id);
					bAuto3 = true;
					setState3(S_NEXT);
					poLog->log(C_UPDATE, &psIni->sLog3, pJob->nLogIdx);
				}
				break;

				//DC 3.3.0 --------------------------------------------------------
			case 3:
				/*if(pAll->eAsType == A_REMOTE)
				{
				Cmd^ pCmd = gcnew Cmd();
				pCmd->cId = CL_LOG4;
				pCmd->nKey = C_READ;
				pCmd->nIdx = pJob->nLogIdx;
				pAll->qCmd->Enqueue(pCmd);
				pAll->cWaitT = 1;

				while(pAll->cWaitT > 0 && i++ < REM_CNT)
				Thread::Sleep(100);
				}
				else*/
				poLog->log(C_READ, &psIni->sLog4, pJob->nLogIdx);

				if (psIni->bBotScale)
				{

					//DC 4.0.1						 siloBar4_Click(nullptr, nullptr);
					if (!siloBar4->Idle)
					{
						nSilo = 10;
					}
					else if (!siloBar42->Idle)
					{
						nSilo = 11;
					}
					else if (!siloBar43->Idle)
					{
						nSilo = 12;
					}
					if (gcnew String(psIni->sLog4.sT.mix_code) != ""
						&& (gcnew String(psIni->sLog4.sT.mix_code) != gcnew String(psIni->asSilos[nSilo - 1].acProduct))) //DC 4.0.1
					{
						MessageBox::Show("Wrong Material on Silo" + psIni->asSilos[nSilo - 1].nSiloNum.ToString() + ", Ticket# " + psIni->sLog4.sT.ticket_num
							+ " for Truck: " + gcnew String(psIni->sLog4.sT.truck_id)
							+ ", NEED Material: " + gcnew String(psIni->sLog4.sT.mix_code), "Lane R",
							System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);
						bWrongMet = true;	//DC 4.0.1
						return;
					}
					else
					{
						//DC 4.0.1
						customer4->Text = pJob->stCustomer;
						tic_num4->Text = pJob->nTicket.ToString();

						Job4->Text = gcnew String(psIni->sLog4.sT.project_code);
						material4->Text = gcnew String(psIni->sLog4.sT.mix_code);
						truck4->Text = gcnew String(psIni->sLog4.sT.truck_id);
						if (psIni->bScaleInLB)	//DC 3.2.0
							target4->Text = psIni->sLog4.sT.load_size.ToString("F00");
						else
							target4->Text = psIni->sLog4.sT.load_size.ToString("F02");
						plant4->Text = psIni->sLog4.sT.plant_num.ToString();
					}


					if (!bWrongMet)
					{
						switch (psIni->sLog4.nSilo)
						{
						case 1:	pAll->nTickets1--; break;// siloBar4_Click(nullptr, nullptr);	break;
						case 2:	pAll->nTickets1--; break;// siloBar42_Click(nullptr, nullptr);	break;
						case 3:	pAll->nTickets1--; break;// siloBar43_Click(nullptr, nullptr);	break;

						case 4:	pAll->nTickets2--; break;// siloBar4_Click(nullptr, nullptr);	break;
						case 5:	pAll->nTickets2--; break;// siloBar42_Click(nullptr, nullptr);	break;
						case 6:	pAll->nTickets2--; break;// siloBar43_Click(nullptr, nullptr);	break;

						case 7:	pAll->nTickets3--; break;// siloBar4_Click(nullptr, nullptr);	break;
						case 8:	pAll->nTickets3--; break;// siloBar42_Click(nullptr, nullptr);	break;
						case 9:	pAll->nTickets3--; break;// siloBar43_Click(nullptr, nullptr);	break;

						case 10:	psIni->nTickets4--; break;// siloBar4_Click(nullptr, nullptr);	break;
						case 11:	psIni->nTickets4--; break;// siloBar42_Click(nullptr, nullptr);	break;
						case 12:	psIni->nTickets4--; break;// siloBar43_Click(nullptr, nullptr);	break;
						default:	siloBar4_Click(nullptr, nullptr);	break;
						}
					}
				}
				else
				{
					switch (psIni->sLog4.nSilo)
					{
					case 1:	pAll->nTickets1--;	break;
					case 2:	pAll->nTickets2--;	break;
					case 3:	pAll->nTickets3--;	break;
					case 4:	psIni->nTickets4--;	break;
					}
					//DC 4.0.1						 psIni->sLog4.nSilo = 4;
				}
				if (!bWrongMet)	//DC 4.0.2
				{
					psIni->sLog4.nSilo = nSilo;
					pJob4 = pJob;
					pJob4->nSilo = psIni->sLog4.nSilo;
					pTruck4 = findTruck(psIni->sLog4.sT.truck_id);
					bAuto4 = true;
					setState4(S_NEXT);
					poLog->log(C_UPDATE, &psIni->sLog4, pJob->nLogIdx);
				}
				break;
			}
			if (!bWrongMet)
			{
				pAll->lJob->Remove(pJob);
				pJob->eStatus = S_OK1;
				dataGridJob->Visible = false;
			}
			else
				bWrongMet = false;
		}
	}

			 //--------------------------------------------------------------------
	private: System::Void dataGridJob_ColumnHeaderMouseClick(System::Object^  sender
		, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e)
	{
		dataGridJob->Visible = false;
	}

			 //--------------------------------------------------------------------
	private: System::Void all1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		jobBindingSource->DataSource = nullptr;
		jobBindingSource->DataSource = pAll->lJob;
		nLane = 0;
		dataGridJob->Visible = !dataGridJob->Visible;
		this->dataGridJob->DefaultCellStyle->ForeColor = System::Drawing::Color::MediumBlue;	//DC 4.0.2
	}
	private: System::Void all2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		jobBindingSource->DataSource = nullptr;
		jobBindingSource->DataSource = pAll->lJob;
		nLane = 1;
		dataGridJob->Visible = !dataGridJob->Visible;
		this->dataGridJob->DefaultCellStyle->ForeColor = System::Drawing::Color::DarkGreen;	//DC 4.0.2
	}
	private: System::Void all3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		jobBindingSource->DataSource = nullptr;
		jobBindingSource->DataSource = pAll->lJob;
		nLane = 2;
		dataGridJob->Visible = !dataGridJob->Visible;
		this->dataGridJob->DefaultCellStyle->ForeColor = System::Drawing::Color::DarkRed;	//DC 4.0.2
	}
	private: System::Void all4_Click(System::Object^  sender, System::EventArgs^  e)	//DC 3.3.0
	{
		if (pAll->eAsType == A_REMOTE)
		{
			int j = 0;
			pAll->cWaitT = 1;
			Cmd^ pCmd = gcnew Cmd();
			pCmd = gcnew Cmd();
			pCmd->cId = CL_JOB;
			pAll->qCmd->Enqueue(pCmd);

			while (pAll->cWaitT > 0 && j++ < 5)
				Thread::Sleep(100);
		}
		jobBindingSource->DataSource = nullptr;
		jobBindingSource->DataSource = pAll->lJob;
		nLane = 3;
		dataGridJob->Visible = !dataGridJob->Visible;
		this->dataGridJob->DefaultCellStyle->ForeColor = System::Drawing::Color::MidnightBlue;	//DC 4.0.2
	}
#pragma endregion

	private: System::Void tonnage1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (MessageBox::Show("Reset Tonnage ?", "Lane A",
			System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			== System::Windows::Forms::DialogResult::Yes)
		{
			psIni->sInv.fTon1 = 0;
			tonnage1->Text = psIni->sInv.fTon1.ToString("F01");
		}
	}
	private: System::Void tonnage2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (MessageBox::Show("Reset Tonnage ?", "Lane B",
			System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			== System::Windows::Forms::DialogResult::Yes)
		{
			psIni->sInv.fTon2 = 0;
			tonnage2->Text = psIni->sInv.fTon2.ToString("F01");
		}
	}
	private: System::Void tonnage3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (MessageBox::Show("Reset Tonnage ?", "Lane C",
			System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			== System::Windows::Forms::DialogResult::Yes)
		{
			psIni->sInv.fTon3 = 0;
			tonnage3->Text = psIni->sInv.fTon3.ToString("F01");
		}
	}
	private: System::Void tonnage4_Click(System::Object^  sender, System::EventArgs^  e)	//DC 3.3.0 
	{
		if (pAll->eAsType == A_REMOTE)
		{
			if (MessageBox::Show("Reset Tonnage ?", "Lane D",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::Yes)
			{
				int i = 0;
				Cmd^ pCmd = gcnew Cmd();

				pCmd->cId = CL_KEY;
				pCmd->nKey = K_RESETTON4;
				pAll->qCmd->Enqueue(pCmd);

				pAll->cWaitT = 1;

				while (pAll->cWaitT > 0 && i++ < 5)
					Thread::Sleep(100);
			}
		}
		else if (pAll->eAsType != A_REMOTE && !pAll->bRemoteCall)
		{
			if (MessageBox::Show("Reset Tonnage ?", "Lane D",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::Yes)
			{
				psIni->sInv.fTon4 = 0;
				tonnage4->Text = psIni->sInv.fTon4.ToString("F01");
			}
		}
		else if (pAll->eAsType != A_REMOTE && pAll->bRemoteCall)
		{
			psIni->sInv.fTon4 = 0;
			tonnage4->Text = psIni->sInv.fTon4.ToString("F01");
			pAll->bRemoteCall = false;
		}
	}

	private: System::Void iOTestToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		IOForm^ ioForm = gcnew IOForm(pAll);
		ioForm->Show(this);
	}
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void customer3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void material3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label11_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void grossC_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void webBrowser3_DocumentCompleted(System::Object^  sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^  e) {
	}
	private: System::Void webBrowser4_DocumentCompleted(System::Object^  sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^  e) {
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void taxExempt3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void configToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		CfgForm^ cfgForm = gcnew CfgForm(pAll);
		cfgForm->Show(this);
	}
	private: System::Void fill12_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void groupBox4_Enter(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void numericUpDown3_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void resetBt1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		resetTargetOutput();		//DC 4.0.1

		if (MessageBox::Show("Reset Ticket ?", "Lane A",
			System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			== System::Windows::Forms::DialogResult::Yes)
		{
			pJob1->eStatus = S_NEW;
			pAll->lJob->Add(pJob1);

			if (!psIni->bBotScale)
				switch (psIni->sLog1.nSilo)
				{
				case 1: pAll->nTickets1++; break;
				case 2: pAll->nTickets2++; break;
				case 3: pAll->nTickets3++; break;
				case 4: psIni->nTickets4++; break;
				}
			else
				switch (psIni->sLog1.nSilo)
				{
				case 1:
				case 2:
				case 3: pAll->nTickets1++; break;
				case 4:
				case 5:
				case 6: pAll->nTickets2++; break;
				case 7:
				case 8:
				case 9: pAll->nTickets3++; break;
				case 10:
				case 11:
				case 12: psIni->nTickets4++; break;
				}
			setState1(S_IDLE);
		}
		return;
	}
	private: System::Void resetBt2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		resetTargetOutput();		//DC 4.0.1

		if (MessageBox::Show("Reset Ticket ?", "Lane B",
			System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			== System::Windows::Forms::DialogResult::Yes)
		{
			pJob2->eStatus = S_NEW;
			pAll->lJob->Add(pJob2);

			if (!psIni->bBotScale)
				switch (psIni->sLog2.nSilo)
				{
				case 1: pAll->nTickets1++; break;
				case 2: pAll->nTickets2++; break;
				case 3: pAll->nTickets3++; break;
				case 4: psIni->nTickets4++; break;
				}
			else
				switch (psIni->sLog2.nSilo)
				{
				case 1:
				case 2:
				case 3: pAll->nTickets1++; break;
				case 4:
				case 5:
				case 6: pAll->nTickets2++; break;
				case 7:
				case 8:
				case 9: pAll->nTickets3++; break;
				case 10:
				case 11:
				case 12: psIni->nTickets4++; break;
				}
			setState2(S_IDLE);
		}
		return;
	}
	private: System::Void resetBt3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		resetTargetOutput();		//DC 4.0.1

		if (MessageBox::Show("Reset Ticket ?", "Lane C",
			System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			== System::Windows::Forms::DialogResult::Yes)
		{
			pJob3->eStatus = S_NEW;
			pAll->lJob->Add(pJob3);

			if (!psIni->bBotScale)
				switch (psIni->sLog3.nSilo)
				{
				case 1: pAll->nTickets1++; break;
				case 2: pAll->nTickets2++; break;
				case 3: pAll->nTickets3++; break;
				case 4: psIni->nTickets4++; break;
				}
			else
				switch (psIni->sLog3.nSilo)
				{
				case 1:
				case 2:
				case 3: pAll->nTickets1++; break;
				case 4:
				case 5:
				case 6: pAll->nTickets2++; break;
				case 7:
				case 8:
				case 9: pAll->nTickets3++; break;
				case 10:
				case 11:
				case 12: psIni->nTickets4++; break;
				}
			setState3(S_IDLE);
		}
		return;
	}
	private: System::Void resetBt4_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (pAll->eAsType != A_REMOTE)
			resetTargetOutput();		//DC 4.0.1

		if (pAll->bRemoteCall && pAll->eAsType != A_REMOTE)
		{
			pAll->bRemoteCall = false;
			pJob4->eStatus = S_NEW;
			pAll->lJob->Add(pJob4);

			if (!psIni->bBotScale)
				switch (psIni->sLog4.nSilo)
				{
				case 1: pAll->nTickets1++; break;
				case 2: pAll->nTickets2++; break;
				case 3: pAll->nTickets3++; break;
				case 4: psIni->nTickets4++; break;
				}
			else
				switch (psIni->sLog4.nSilo)
				{
				case 1:
				case 2:
				case 3: pAll->nTickets1++; break;
				case 4:
				case 5:
				case 6: pAll->nTickets2++; break;
				case 7:
				case 8:
				case 9: pAll->nTickets3++; break;
				case 10:
				case 11:
				case 12: psIni->nTickets4++; break;
				}
			setState4(S_IDLE);

		}
		else
		{
			if (MessageBox::Show("Reset Ticket ?", "Lane A",
				System::Windows::Forms::MessageBoxButtons::YesNo, MessageBoxIcon::Question)
				== System::Windows::Forms::DialogResult::Yes)
			{
				if (pAll->eAsType == A_REMOTE)
				{
					int i = 0;
					int j = 0;
					Cmd^ pCmd = gcnew Cmd();
					pCmd->cId = CL_KEY;
					pCmd->nKey = K_RESET4;
					pAll->qCmd->Enqueue(pCmd);

					pAll->cWaitT = 1;

					while (pAll->cWaitT > 0 && i++ < 5)
						Thread::Sleep(100);

					pCmd = gcnew Cmd();
					pCmd->cId = CL_JOB;
					pAll->qCmd->Enqueue(pCmd);

					while (pAll->cWaitT > 0 && j++ < 5)
						Thread::Sleep(100);
				}

				if (pAll->eAsType != A_REMOTE)
				{
					pJob4->eStatus = S_NEW;
					pAll->lJob->Add(pJob4);
				}

				if (!psIni->bBotScale)
					switch (psIni->sLog4.nSilo)
					{
					case 1: pAll->nTickets1++; break;
					case 2: pAll->nTickets2++; break;
					case 3: pAll->nTickets3++; break;
					case 4: psIni->nTickets4++; break;
					}
				else if (pAll->eAsType != A_REMOTE)
					switch (psIni->sLog4.nSilo)
					{
					case 1:
					case 2:
					case 3: pAll->nTickets1++; break;
					case 4:
					case 5:
					case 6: pAll->nTickets2++; break;
					case 7:
					case 8:
					case 9: pAll->nTickets3++; break;
					case 10:
					case 11:
					case 12: psIni->nTickets4++; break;
					}
				setState4(S_IDLE);
			}
		}
		return;
	}
	private: System::Void remLoginBt_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Cmd^ pCmd;
		int i = 0;
		int nTime;

		this->remLoginBt->Enabled = false;
		this->loginErrLb->Visible = true;
		this->loginErrLb->Refresh();

		oClinkThread = gcnew Thread(gcnew ParameterizedThreadStart(&CClink::ThreadProc));
		oClinkThread->IsBackground = true;
		oClinkThread->Start(pAll);
		Thread::Sleep(5000);

		pCmd = gcnew Cmd();
		pCmd->cId = CL_LOGIN;
		pCmd->nKey = 1;

		pAll->qCmd->Enqueue(pCmd);
		pAll->nKey = 1;

		while (pAll->nKey > 0 && i++ < 5)
			Thread::Sleep(500);				//DC

		if (pAll->cLogin != 1)
		{
			oClinkThread->Abort();
			MessageBox::Show("Please Check Remote Server", "Remote Server is not running",
				System::Windows::Forms::MessageBoxButtons::OK, MessageBoxIcon::Error);

			this->loginErrLb->Visible = false;
			this->loginErrLb->Refresh();
			this->remLoginBt->Enabled = true;
			return;
		}

		pAll->nCmd = 0;

		pCmd = gcnew Cmd();
		pCmd->cId = CL_INI;
		pAll->qCmd->Enqueue(pCmd);

		pCmd = gcnew Cmd();
		pCmd->cId = CL_TRUCKS;
		pAll->qCmd->Enqueue(pCmd);

		pCmd = gcnew Cmd();
		pCmd->cId = CL_JOB;
		pAll->qCmd->Enqueue(pCmd);

		nTime = 0;
		//loop:			 nTime = 0;
		while ((pAll->nCmd < 3) && (nTime < 2))
		{
			//		 			testLb->Text = pAll->nCmd.ToString();
			Thread::Sleep(500);					//DC
			nTime++;
		}

		init();
		bRemLogin = true;
		this->remLoginBt->Enabled = false;
		this->remLoginBt->Visible = false;
		this->loginErrLb->Visible = false;
		this->ipAddressLb->Visible = false;
	}
	private: System::Void target4_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{

		if (pAll->eAsType == A_REMOTE && target4->Text != "")
		{
			double fLoadChg;
			fLoadChg = Convert::ToDouble(target4->Text);
			Cmd^ pCmd = gcnew Cmd();
			pJob4->fLoad = fLoadChg;
			pAll->pJob4 = pJob4;
			int k = 0;
			pCmd = gcnew Cmd();
			pCmd->cId = CL_SJOB4;
			pAll->qCmd->Enqueue(pCmd);

			pAll->cWaitT = 1;

			while (pAll->cWaitT > 0 && k++ < 5)
				Thread::Sleep(100);
		}
	}
	};		// Form1 class
}		// namespace as


