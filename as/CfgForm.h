#pragma once
#include "stdafx.h"
#include "cfx.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
//using namespace System::Data;
using namespace System::Drawing;


namespace As {

	/// <summary>
	/// Summary for CfgForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CfgForm : public System::Windows::Forms::Form
	{
	public:
		CfgForm(All^ pAllIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pAll = pAllIn;
			psIni = pAll->psIni;
			bSave = false;
			bReboot = false;

			if(pAll->eAsType == A_REMOTE)		//DC 4.1.0
				this->editIOCB->Enabled = false;

			if(psIni->bSendBitWise)
			{
				dataGridView2->Visible = true;
				sendTargetLb->Visible = true;
				sendTargetOTb->Visible = true;
				receivedTargetLb->Visible = true;
				receivedTargetITb->Visible = true;
				keepAliveOLb->Visible = true;
				keepAliveOTb->Visible = true;
				keepAliveILb->Visible = true;
				keepAliveITb->Visible = true;

				keepOnTimeLb->Visible = true;
				keepOffTimeLb->Visible = true;
				keepTimeLb->Visible =true;
				keepOnTimeTb->Visible = true;
				keepOffTimeTb->Visible = true;
				
				siloBit1Lb->Visible = true;
				siloBit2Lb->Visible = true;
				siloBit3Lb->Visible = true;
				siloBit4Lb->Visible = true;
				siloBit1Tb->Visible = true;
				siloBit2Tb->Visible = true;
				siloBit3Tb->Visible = true;
				siloBit4Tb->Visible = true;

				siloOutputLb->Visible = true;
				siloCheckLb->Visible = true;

				siloBitCheck1Tb->Visible = true;
				siloBitCheck2Tb->Visible = true;
				siloBitCheck3Tb->Visible = true;
				siloBitCheck4Tb->Visible = true;

				laneTare1Tb->Visible = true;
				laneTare2Tb->Visible = true;
				laneTare3Tb->Visible = true;
				laneTare4Tb->Visible = true;
			}
			loadCfg();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CfgForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		All^					pAll;
		INI						*psIni;
		Generic::List<Cfg^>^	lCfg;
		Generic::List<Cfg^>^	bCfg;
		bool					bSave;
		bool					bReboot;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	protected: 
	private: System::Windows::Forms::BindingSource^  cfgBindingSource;
	private: System::Windows::Forms::Button^  saveBt;
	private: System::Windows::Forms::CheckBox^  pdmPlcCB;
	private: System::Windows::Forms::CheckBox^  showAllCB;
	private: System::Windows::Forms::CheckBox^  editIOCB;
	private: System::Windows::Forms::Button^  exitBt;
	private: System::Windows::Forms::CheckBox^  autoAddCb;
	private: System::Windows::Forms::Button^  closeBt;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckBox^  sendTargetCB;
	private: System::Windows::Forms::Label^  lineLB1;

	private: System::Windows::Forms::Label^  lineLB4;
	private: System::Windows::Forms::Label^  truckMaxLB;
	private: System::Windows::Forms::Label^  truckMaxLB4;
	private: System::Windows::Forms::TextBox^  truckScaledMinTB;
	private: System::Windows::Forms::Label^  trkScaledMinLB;
	private: System::Windows::Forms::Label^  trkScaledMaxLB;
	private: System::Windows::Forms::TextBox^  truckScaledMaxTB;
	private: System::Windows::Forms::Label^  cartScaledMinLB;
	private: System::Windows::Forms::TextBox^  cartScaledMinTB;
	private: System::Windows::Forms::Label^  cartScaledMaxLB;
	private: System::Windows::Forms::TextBox^  cartScaledMaxTB;
	private: System::Windows::Forms::GroupBox^  analogOutputGB;
	private: System::Windows::Forms::DataGridView^  dataGridView2;
	private: System::Windows::Forms::CheckBox^  bitWiseCB;
	private: System::Windows::Forms::BindingSource^  bitWiseBindingSource;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nBitWise;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nBitCheckI;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nBitWiseDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dAddTolDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nSiloJogDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nSiloNumDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  fFallDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nHoldIDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDropReadyIDataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nAddODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nHoldODataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDoneODataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDropODataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nReadyODataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDoneIDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRate4ODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRate3ODataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRate2ODataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRate1ODataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDelayTimeDataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDelayPctDataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRatePct4DataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRatePct3DataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRatePct2DataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRatePct1DataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  bUsedDataGridViewCheckBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stLblDataGridViewTextBoxColumn1;
	private: System::Windows::Forms::TextBox^  sendTargetOTb;
	private: System::Windows::Forms::Label^  sendTargetLb;
	private: System::Windows::Forms::Label^  receivedTargetLb;
	private: System::Windows::Forms::TextBox^  receivedTargetITb;
	private: System::Windows::Forms::Label^  keepAliveOLb;
	private: System::Windows::Forms::TextBox^  keepAliveOTb;
	private: System::Windows::Forms::Label^  keepAliveILb;
	private: System::Windows::Forms::TextBox^  keepAliveITb;
	private: System::Windows::Forms::Label^  siloBit1Lb;
	private: System::Windows::Forms::TextBox^  siloBit1Tb;
	private: System::Windows::Forms::TextBox^  siloBit2Tb;
	private: System::Windows::Forms::Label^  siloBit2Lb;
	private: System::Windows::Forms::TextBox^  siloBit3Tb;
	private: System::Windows::Forms::Label^  siloBit3Lb;
	private: System::Windows::Forms::TextBox^  siloBit4Tb;
	private: System::Windows::Forms::Label^  siloBit4Lb;
	private: System::Windows::Forms::Label^  siloOutputLb;
	private: System::Windows::Forms::Label^  siloCheckLb;
	private: System::Windows::Forms::TextBox^  siloBitCheck1Tb;
	private: System::Windows::Forms::TextBox^  siloBitCheck2Tb;
	private: System::Windows::Forms::TextBox^  siloBitCheck3Tb;
	private: System::Windows::Forms::TextBox^  siloBitCheck4Tb;
	private: System::Windows::Forms::TextBox^  keepOnTimeTb;
	private: System::Windows::Forms::TextBox^  keepOffTimeTb;
	private: System::Windows::Forms::Label^  keepOnTimeLb;
	private: System::Windows::Forms::Label^  keepOffTimeLb;
	private: System::Windows::Forms::Label^  keepTimeLb;
	private: System::Windows::Forms::TextBox^  laneTare4Tb;
	private: System::Windows::Forms::TextBox^  laneTare3Tb;

	private: System::Windows::Forms::TextBox^  laneTare2Tb;

	private: System::Windows::Forms::TextBox^  laneTare1Tb;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  bUsedDataGridViewCheckBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nSiloNum;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stLblDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stProduct;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDropODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nHoldODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDoneODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDoneI;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nHoldI;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nReadyODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRatePct1DataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRate1ODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRatePct2DataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRate2ODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRatePct3DataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nFlowRate3ODataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDropReadyIDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nSiloJog;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dAddTol;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDelayPctDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nDelayTimeDataGridViewTextBoxColumn;
	private: System::Windows::Forms::Label^  truckMaxLB2;
	private: System::Windows::Forms::Label^  lineLB2;
	private: System::Windows::Forms::Label^  truckMaxLB3;
	private: System::Windows::Forms::Label^  lineLB3;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle23 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle38 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle39 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle24 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle25 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle26 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle27 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle28 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle29 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle30 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle31 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle32 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle33 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle34 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle35 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle36 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle37 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle40 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle43 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle44 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle41 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle42 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->bUsedDataGridViewCheckBoxColumn = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->nSiloNum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->stLblDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->stProduct = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDropODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nHoldODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDoneODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDoneI = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nHoldI = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nReadyODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRatePct1DataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRate1ODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRatePct2DataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRate2ODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRatePct3DataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRate3ODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDropReadyIDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nSiloJog = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dAddTol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDelayPctDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDelayTimeDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->cfgBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->saveBt = (gcnew System::Windows::Forms::Button());
			this->pdmPlcCB = (gcnew System::Windows::Forms::CheckBox());
			this->showAllCB = (gcnew System::Windows::Forms::CheckBox());
			this->editIOCB = (gcnew System::Windows::Forms::CheckBox());
			this->exitBt = (gcnew System::Windows::Forms::Button());
			this->autoAddCb = (gcnew System::Windows::Forms::CheckBox());
			this->closeBt = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->sendTargetCB = (gcnew System::Windows::Forms::CheckBox());
			this->lineLB1 = (gcnew System::Windows::Forms::Label());
			this->lineLB4 = (gcnew System::Windows::Forms::Label());
			this->truckMaxLB = (gcnew System::Windows::Forms::Label());
			this->truckMaxLB4 = (gcnew System::Windows::Forms::Label());
			this->truckScaledMinTB = (gcnew System::Windows::Forms::TextBox());
			this->trkScaledMinLB = (gcnew System::Windows::Forms::Label());
			this->trkScaledMaxLB = (gcnew System::Windows::Forms::Label());
			this->truckScaledMaxTB = (gcnew System::Windows::Forms::TextBox());
			this->cartScaledMinLB = (gcnew System::Windows::Forms::Label());
			this->cartScaledMinTB = (gcnew System::Windows::Forms::TextBox());
			this->cartScaledMaxLB = (gcnew System::Windows::Forms::Label());
			this->cartScaledMaxTB = (gcnew System::Windows::Forms::TextBox());
			this->analogOutputGB = (gcnew System::Windows::Forms::GroupBox());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->nBitWise = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nBitCheckI = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nBitWiseDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dAddTolDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nSiloJogDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nSiloNumDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->fFallDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nHoldIDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDropReadyIDataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nAddODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nHoldODataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDoneODataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDropODataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nReadyODataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDoneIDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRate4ODataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRate3ODataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRate2ODataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRate1ODataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDelayTimeDataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nDelayPctDataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRatePct4DataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRatePct3DataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRatePct2DataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nFlowRatePct1DataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->bUsedDataGridViewCheckBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->stLblDataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->bitWiseBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->bitWiseCB = (gcnew System::Windows::Forms::CheckBox());
			this->sendTargetOTb = (gcnew System::Windows::Forms::TextBox());
			this->sendTargetLb = (gcnew System::Windows::Forms::Label());
			this->receivedTargetLb = (gcnew System::Windows::Forms::Label());
			this->receivedTargetITb = (gcnew System::Windows::Forms::TextBox());
			this->keepAliveOLb = (gcnew System::Windows::Forms::Label());
			this->keepAliveOTb = (gcnew System::Windows::Forms::TextBox());
			this->keepAliveILb = (gcnew System::Windows::Forms::Label());
			this->keepAliveITb = (gcnew System::Windows::Forms::TextBox());
			this->siloBit1Lb = (gcnew System::Windows::Forms::Label());
			this->siloBit1Tb = (gcnew System::Windows::Forms::TextBox());
			this->siloBit2Tb = (gcnew System::Windows::Forms::TextBox());
			this->siloBit2Lb = (gcnew System::Windows::Forms::Label());
			this->siloBit3Tb = (gcnew System::Windows::Forms::TextBox());
			this->siloBit3Lb = (gcnew System::Windows::Forms::Label());
			this->siloBit4Tb = (gcnew System::Windows::Forms::TextBox());
			this->siloBit4Lb = (gcnew System::Windows::Forms::Label());
			this->siloOutputLb = (gcnew System::Windows::Forms::Label());
			this->siloCheckLb = (gcnew System::Windows::Forms::Label());
			this->siloBitCheck1Tb = (gcnew System::Windows::Forms::TextBox());
			this->siloBitCheck2Tb = (gcnew System::Windows::Forms::TextBox());
			this->siloBitCheck3Tb = (gcnew System::Windows::Forms::TextBox());
			this->siloBitCheck4Tb = (gcnew System::Windows::Forms::TextBox());
			this->keepOnTimeTb = (gcnew System::Windows::Forms::TextBox());
			this->keepOffTimeTb = (gcnew System::Windows::Forms::TextBox());
			this->keepOnTimeLb = (gcnew System::Windows::Forms::Label());
			this->keepOffTimeLb = (gcnew System::Windows::Forms::Label());
			this->keepTimeLb = (gcnew System::Windows::Forms::Label());
			this->laneTare4Tb = (gcnew System::Windows::Forms::TextBox());
			this->laneTare3Tb = (gcnew System::Windows::Forms::TextBox());
			this->laneTare2Tb = (gcnew System::Windows::Forms::TextBox());
			this->laneTare1Tb = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->truckMaxLB2 = (gcnew System::Windows::Forms::Label());
			this->lineLB2 = (gcnew System::Windows::Forms::Label());
			this->truckMaxLB3 = (gcnew System::Windows::Forms::Label());
			this->lineLB3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cfgBindingSource))->BeginInit();
			this->analogOutputGB->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bitWiseBindingSource))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AutoGenerateColumns = false;
			dataGridViewCellStyle23->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle23->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle23->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle23->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle23->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle23->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle23;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(22) {this->bUsedDataGridViewCheckBoxColumn, 
				this->nSiloNum, this->stLblDataGridViewTextBoxColumn, this->stProduct, this->nDropODataGridViewTextBoxColumn, this->nHoldODataGridViewTextBoxColumn, 
				this->nDoneODataGridViewTextBoxColumn, this->nDoneI, this->nHoldI, this->nReadyODataGridViewTextBoxColumn, this->nFlowRatePct1DataGridViewTextBoxColumn, 
				this->nFlowRate1ODataGridViewTextBoxColumn, this->nFlowRatePct2DataGridViewTextBoxColumn, this->nFlowRate2ODataGridViewTextBoxColumn, 
				this->nFlowRatePct3DataGridViewTextBoxColumn, this->nFlowRate3ODataGridViewTextBoxColumn, this->nDropReadyIDataGridViewTextBoxColumn, 
				this->Column1, this->nSiloJog, this->dAddTol, this->nDelayPctDataGridViewTextBoxColumn, this->nDelayTimeDataGridViewTextBoxColumn});
			this->dataGridView1->DataSource = this->cfgBindingSource;
			dataGridViewCellStyle38->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle38->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle38->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle38->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle38->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle38->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle38;
			this->dataGridView1->Location = System::Drawing::Point(12, 126);
			this->dataGridView1->Name = L"dataGridView1";
			dataGridViewCellStyle39->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle39->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle39->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle39->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle39->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle39->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->RowHeadersDefaultCellStyle = dataGridViewCellStyle39;
			this->dataGridView1->Size = System::Drawing::Size(554, 289);
			this->dataGridView1->TabIndex = 0;
			this->dataGridView1->CellBeginEdit += gcnew System::Windows::Forms::DataGridViewCellCancelEventHandler(this, &CfgForm::dataGridView1_CellBeginEdit);
			// 
			// bUsedDataGridViewCheckBoxColumn
			// 
			this->bUsedDataGridViewCheckBoxColumn->DataPropertyName = L"bUsed";
			dataGridViewCellStyle24->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle24->BackColor = System::Drawing::Color::LightGray;
			dataGridViewCellStyle24->NullValue = false;
			this->bUsedDataGridViewCheckBoxColumn->DefaultCellStyle = dataGridViewCellStyle24;
			this->bUsedDataGridViewCheckBoxColumn->HeaderText = L"Used";
			this->bUsedDataGridViewCheckBoxColumn->Name = L"bUsedDataGridViewCheckBoxColumn";
			this->bUsedDataGridViewCheckBoxColumn->ReadOnly = true;
			this->bUsedDataGridViewCheckBoxColumn->Width = 40;
			// 
			// nSiloNum
			// 
			this->nSiloNum->DataPropertyName = L"nSiloNum";
			dataGridViewCellStyle25->BackColor = System::Drawing::Color::LightGray;
			this->nSiloNum->DefaultCellStyle = dataGridViewCellStyle25;
			this->nSiloNum->HeaderText = L"SILO#";
			this->nSiloNum->Name = L"nSiloNum";
			this->nSiloNum->ReadOnly = true;
			this->nSiloNum->Width = 45;
			// 
			// stLblDataGridViewTextBoxColumn
			// 
			this->stLblDataGridViewTextBoxColumn->DataPropertyName = L"stLbl";
			dataGridViewCellStyle26->BackColor = System::Drawing::Color::LightGray;
			this->stLblDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle26;
			this->stLblDataGridViewTextBoxColumn->HeaderText = L"Name";
			this->stLblDataGridViewTextBoxColumn->Name = L"stLblDataGridViewTextBoxColumn";
			this->stLblDataGridViewTextBoxColumn->ReadOnly = true;
			this->stLblDataGridViewTextBoxColumn->Width = 60;
			// 
			// stProduct
			// 
			this->stProduct->DataPropertyName = L"stProduct";
			dataGridViewCellStyle27->BackColor = System::Drawing::Color::LightGray;
			this->stProduct->DefaultCellStyle = dataGridViewCellStyle27;
			this->stProduct->HeaderText = L"Product";
			this->stProduct->Name = L"stProduct";
			this->stProduct->ReadOnly = true;
			// 
			// nDropODataGridViewTextBoxColumn
			// 
			this->nDropODataGridViewTextBoxColumn->DataPropertyName = L"nDropO";
			dataGridViewCellStyle28->BackColor = System::Drawing::Color::LightGray;
			this->nDropODataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle28;
			this->nDropODataGridViewTextBoxColumn->HeaderText = L"Drop_O";
			this->nDropODataGridViewTextBoxColumn->Name = L"nDropODataGridViewTextBoxColumn";
			this->nDropODataGridViewTextBoxColumn->ReadOnly = true;
			this->nDropODataGridViewTextBoxColumn->Width = 50;
			// 
			// nHoldODataGridViewTextBoxColumn
			// 
			this->nHoldODataGridViewTextBoxColumn->DataPropertyName = L"nHoldO";
			dataGridViewCellStyle29->BackColor = System::Drawing::Color::LightGray;
			this->nHoldODataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle29;
			this->nHoldODataGridViewTextBoxColumn->HeaderText = L"Hold_O";
			this->nHoldODataGridViewTextBoxColumn->Name = L"nHoldODataGridViewTextBoxColumn";
			this->nHoldODataGridViewTextBoxColumn->ReadOnly = true;
			this->nHoldODataGridViewTextBoxColumn->Width = 50;
			// 
			// nDoneODataGridViewTextBoxColumn
			// 
			this->nDoneODataGridViewTextBoxColumn->DataPropertyName = L"nDoneO";
			dataGridViewCellStyle30->BackColor = System::Drawing::Color::LightGray;
			this->nDoneODataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle30;
			this->nDoneODataGridViewTextBoxColumn->HeaderText = L"Done_O";
			this->nDoneODataGridViewTextBoxColumn->Name = L"nDoneODataGridViewTextBoxColumn";
			this->nDoneODataGridViewTextBoxColumn->ReadOnly = true;
			this->nDoneODataGridViewTextBoxColumn->Width = 50;
			// 
			// nDoneI
			// 
			this->nDoneI->DataPropertyName = L"nDoneI";
			dataGridViewCellStyle31->BackColor = System::Drawing::Color::LightGray;
			this->nDoneI->DefaultCellStyle = dataGridViewCellStyle31;
			this->nDoneI->HeaderText = L"DoneI";
			this->nDoneI->Name = L"nDoneI";
			this->nDoneI->ReadOnly = true;
			this->nDoneI->Width = 55;
			// 
			// nHoldI
			// 
			this->nHoldI->DataPropertyName = L"nHoldI";
			dataGridViewCellStyle32->BackColor = System::Drawing::Color::LightGray;
			this->nHoldI->DefaultCellStyle = dataGridViewCellStyle32;
			this->nHoldI->HeaderText = L"Hold_I";
			this->nHoldI->Name = L"nHoldI";
			this->nHoldI->ReadOnly = true;
			this->nHoldI->Width = 55;
			// 
			// nReadyODataGridViewTextBoxColumn
			// 
			this->nReadyODataGridViewTextBoxColumn->DataPropertyName = L"nReadyO";
			dataGridViewCellStyle33->BackColor = System::Drawing::Color::LightGray;
			this->nReadyODataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle33;
			this->nReadyODataGridViewTextBoxColumn->HeaderText = L"Ready_O";
			this->nReadyODataGridViewTextBoxColumn->Name = L"nReadyODataGridViewTextBoxColumn";
			this->nReadyODataGridViewTextBoxColumn->ReadOnly = true;
			this->nReadyODataGridViewTextBoxColumn->Width = 60;
			// 
			// nFlowRatePct1DataGridViewTextBoxColumn
			// 
			this->nFlowRatePct1DataGridViewTextBoxColumn->DataPropertyName = L"nFlowRatePct1";
			this->nFlowRatePct1DataGridViewTextBoxColumn->HeaderText = L"FR1%";
			this->nFlowRatePct1DataGridViewTextBoxColumn->Name = L"nFlowRatePct1DataGridViewTextBoxColumn";
			this->nFlowRatePct1DataGridViewTextBoxColumn->Width = 40;
			// 
			// nFlowRate1ODataGridViewTextBoxColumn
			// 
			this->nFlowRate1ODataGridViewTextBoxColumn->DataPropertyName = L"nFlowRate1O";
			dataGridViewCellStyle34->BackColor = System::Drawing::Color::LightGray;
			this->nFlowRate1ODataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle34;
			this->nFlowRate1ODataGridViewTextBoxColumn->HeaderText = L"FR1_O";
			this->nFlowRate1ODataGridViewTextBoxColumn->Name = L"nFlowRate1ODataGridViewTextBoxColumn";
			this->nFlowRate1ODataGridViewTextBoxColumn->ReadOnly = true;
			this->nFlowRate1ODataGridViewTextBoxColumn->Width = 50;
			// 
			// nFlowRatePct2DataGridViewTextBoxColumn
			// 
			this->nFlowRatePct2DataGridViewTextBoxColumn->DataPropertyName = L"nFlowRatePct2";
			this->nFlowRatePct2DataGridViewTextBoxColumn->HeaderText = L"FR2%";
			this->nFlowRatePct2DataGridViewTextBoxColumn->Name = L"nFlowRatePct2DataGridViewTextBoxColumn";
			this->nFlowRatePct2DataGridViewTextBoxColumn->Width = 40;
			// 
			// nFlowRate2ODataGridViewTextBoxColumn
			// 
			this->nFlowRate2ODataGridViewTextBoxColumn->DataPropertyName = L"nFlowRate2O";
			dataGridViewCellStyle35->BackColor = System::Drawing::Color::LightGray;
			this->nFlowRate2ODataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle35;
			this->nFlowRate2ODataGridViewTextBoxColumn->HeaderText = L"FR2_O";
			this->nFlowRate2ODataGridViewTextBoxColumn->Name = L"nFlowRate2ODataGridViewTextBoxColumn";
			this->nFlowRate2ODataGridViewTextBoxColumn->ReadOnly = true;
			this->nFlowRate2ODataGridViewTextBoxColumn->Width = 50;
			// 
			// nFlowRatePct3DataGridViewTextBoxColumn
			// 
			this->nFlowRatePct3DataGridViewTextBoxColumn->DataPropertyName = L"nFlowRatePct3";
			this->nFlowRatePct3DataGridViewTextBoxColumn->HeaderText = L"FR3%";
			this->nFlowRatePct3DataGridViewTextBoxColumn->Name = L"nFlowRatePct3DataGridViewTextBoxColumn";
			this->nFlowRatePct3DataGridViewTextBoxColumn->Width = 40;
			// 
			// nFlowRate3ODataGridViewTextBoxColumn
			// 
			this->nFlowRate3ODataGridViewTextBoxColumn->DataPropertyName = L"nFlowRate3O";
			dataGridViewCellStyle36->BackColor = System::Drawing::Color::LightGray;
			this->nFlowRate3ODataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle36;
			this->nFlowRate3ODataGridViewTextBoxColumn->HeaderText = L"FR3_O";
			this->nFlowRate3ODataGridViewTextBoxColumn->Name = L"nFlowRate3ODataGridViewTextBoxColumn";
			this->nFlowRate3ODataGridViewTextBoxColumn->ReadOnly = true;
			this->nFlowRate3ODataGridViewTextBoxColumn->Width = 50;
			// 
			// nDropReadyIDataGridViewTextBoxColumn
			// 
			this->nDropReadyIDataGridViewTextBoxColumn->DataPropertyName = L"nDropReadyI";
			dataGridViewCellStyle37->BackColor = System::Drawing::Color::LightGray;
			this->nDropReadyIDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle37;
			this->nDropReadyIDataGridViewTextBoxColumn->HeaderText = L"DropReady_I";
			this->nDropReadyIDataGridViewTextBoxColumn->Name = L"nDropReadyIDataGridViewTextBoxColumn";
			this->nDropReadyIDataGridViewTextBoxColumn->ReadOnly = true;
			this->nDropReadyIDataGridViewTextBoxColumn->Width = 80;
			// 
			// Column1
			// 
			this->Column1->DataPropertyName = L"fFall";
			this->Column1->HeaderText = L"F_Fall(TN)";
			this->Column1->Name = L"Column1";
			this->Column1->Width = 60;
			// 
			// nSiloJog
			// 
			this->nSiloJog->DataPropertyName = L"nSiloJog";
			this->nSiloJog->HeaderText = L"Add_Pulse";
			this->nSiloJog->Name = L"nSiloJog";
			this->nSiloJog->Width = 70;
			// 
			// dAddTol
			// 
			this->dAddTol->DataPropertyName = L"dAddTol";
			this->dAddTol->HeaderText = L"Load_Tol(TN)";
			this->dAddTol->Name = L"dAddTol";
			this->dAddTol->Width = 75;
			// 
			// nDelayPctDataGridViewTextBoxColumn
			// 
			this->nDelayPctDataGridViewTextBoxColumn->DataPropertyName = L"nDelayPct";
			this->nDelayPctDataGridViewTextBoxColumn->HeaderText = L"Settle%";
			this->nDelayPctDataGridViewTextBoxColumn->Name = L"nDelayPctDataGridViewTextBoxColumn";
			this->nDelayPctDataGridViewTextBoxColumn->Width = 60;
			// 
			// nDelayTimeDataGridViewTextBoxColumn
			// 
			this->nDelayTimeDataGridViewTextBoxColumn->DataPropertyName = L"nDelayTime";
			this->nDelayTimeDataGridViewTextBoxColumn->HeaderText = L"Settle(sec)";
			this->nDelayTimeDataGridViewTextBoxColumn->Name = L"nDelayTimeDataGridViewTextBoxColumn";
			this->nDelayTimeDataGridViewTextBoxColumn->Width = 70;
			// 
			// cfgBindingSource
			// 
			this->cfgBindingSource->DataSource = As::Cfg::typeid;
			// 
			// saveBt
			// 
			this->saveBt->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->saveBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->saveBt->Location = System::Drawing::Point(906, 499);
			this->saveBt->Name = L"saveBt";
			this->saveBt->Size = System::Drawing::Size(96, 31);
			this->saveBt->TabIndex = 1;
			this->saveBt->Text = L"SAVE";
			this->saveBt->UseMnemonic = false;
			this->saveBt->UseVisualStyleBackColor = false;
			this->saveBt->Visible = false;
			this->saveBt->Click += gcnew System::EventHandler(this, &CfgForm::saveBt_Click);
			// 
			// pdmPlcCB
			// 
			this->pdmPlcCB->AutoSize = true;
			this->pdmPlcCB->Enabled = false;
			this->pdmPlcCB->Location = System::Drawing::Point(133, 47);
			this->pdmPlcCB->Name = L"pdmPlcCB";
			this->pdmPlcCB->Size = System::Drawing::Size(159, 17);
			this->pdmPlcCB->TabIndex = 2;
			this->pdmPlcCB->Text = L"Connect to Matrix PDM PLC";
			this->pdmPlcCB->UseVisualStyleBackColor = true;
			this->pdmPlcCB->Click += gcnew System::EventHandler(this, &CfgForm::pdmPlcCB_Click);
			// 
			// showAllCB
			// 
			this->showAllCB->AutoSize = true;
			this->showAllCB->Enabled = false;
			this->showAllCB->Location = System::Drawing::Point(490, 639);
			this->showAllCB->Name = L"showAllCB";
			this->showAllCB->Size = System::Drawing::Size(92, 17);
			this->showAllCB->TabIndex = 3;
			this->showAllCB->Text = L"Show All Silos";
			this->showAllCB->UseVisualStyleBackColor = true;
			this->showAllCB->Visible = false;
			this->showAllCB->CheckedChanged += gcnew System::EventHandler(this, &CfgForm::showAllCB_CheckedChanged);
			// 
			// editIOCB
			// 
			this->editIOCB->AutoSize = true;
			this->editIOCB->Location = System::Drawing::Point(17, 48);
			this->editIOCB->Name = L"editIOCB";
			this->editIOCB->Size = System::Drawing::Size(58, 17);
			this->editIOCB->TabIndex = 4;
			this->editIOCB->Text = L"Edit IO";
			this->editIOCB->UseVisualStyleBackColor = true;
			this->editIOCB->CheckedChanged += gcnew System::EventHandler(this, &CfgForm::editIOCB_CheckedChanged);
			// 
			// exitBt
			// 
			this->exitBt->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->exitBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->exitBt->Location = System::Drawing::Point(1031, 499);
			this->exitBt->Name = L"exitBt";
			this->exitBt->Size = System::Drawing::Size(96, 31);
			this->exitBt->TabIndex = 5;
			this->exitBt->Text = L"EXIT";
			this->exitBt->UseMnemonic = false;
			this->exitBt->UseVisualStyleBackColor = false;
			this->exitBt->Click += gcnew System::EventHandler(this, &CfgForm::exitBt_Click);
			// 
			// autoAddCb
			// 
			this->autoAddCb->AutoSize = true;
			this->autoAddCb->Location = System::Drawing::Point(490, 616);
			this->autoAddCb->Name = L"autoAddCb";
			this->autoAddCb->Size = System::Drawing::Size(70, 17);
			this->autoAddCb->TabIndex = 6;
			this->autoAddCb->Text = L"Auto Add";
			this->autoAddCb->UseVisualStyleBackColor = true;
			this->autoAddCb->Click += gcnew System::EventHandler(this, &CfgForm::autoAddCb_Click);
			// 
			// closeBt
			// 
			this->closeBt->BackColor = System::Drawing::Color::Silver;
			this->closeBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->closeBt->Location = System::Drawing::Point(1031, 499);
			this->closeBt->Name = L"closeBt";
			this->closeBt->Size = System::Drawing::Size(96, 31);
			this->closeBt->TabIndex = 7;
			this->closeBt->Text = L"CLOSE";
			this->closeBt->UseMnemonic = false;
			this->closeBt->UseVisualStyleBackColor = false;
			this->closeBt->Visible = false;
			this->closeBt->Click += gcnew System::EventHandler(this, &CfgForm::closeBt_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(635, 639);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"100 msec";
			// 
			// sendTargetCB
			// 
			this->sendTargetCB->AutoSize = true;
			this->sendTargetCB->Enabled = false;
			this->sendTargetCB->Location = System::Drawing::Point(12, 586);
			this->sendTargetCB->Name = L"sendTargetCB";
			this->sendTargetCB->Size = System::Drawing::Size(224, 17);
			this->sendTargetCB->TabIndex = 9;
			this->sendTargetCB->Text = L"Send Target Weight to PDM (TN, Analog)";
			this->sendTargetCB->UseVisualStyleBackColor = true;
			this->sendTargetCB->Click += gcnew System::EventHandler(this, &CfgForm::sendTargetCB_Click);
			// 
			// lineLB1
			// 
			this->lineLB1->AutoSize = true;
			this->lineLB1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lineLB1->Location = System::Drawing::Point(334, 41);
			this->lineLB1->Name = L"lineLB1";
			this->lineLB1->Size = System::Drawing::Size(125, 16);
			this->lineLB1->TabIndex = 10;
			this->lineLB1->Text = L"Line1 Scale Max:";
			this->lineLB1->Click += gcnew System::EventHandler(this, &CfgForm::label2_Click);
			// 
			// lineLB4
			// 
			this->lineLB4->AutoSize = true;
			this->lineLB4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lineLB4->Location = System::Drawing::Point(753, 41);
			this->lineLB4->Name = L"lineLB4";
			this->lineLB4->Size = System::Drawing::Size(125, 16);
			this->lineLB4->TabIndex = 11;
			this->lineLB4->Text = L"Line4 Scale Max:";
			// 
			// truckMaxLB
			// 
			this->truckMaxLB->AutoSize = true;
			this->truckMaxLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->truckMaxLB->Location = System::Drawing::Point(337, 62);
			this->truckMaxLB->Name = L"truckMaxLB";
			this->truckMaxLB->Size = System::Drawing::Size(68, 16);
			this->truckMaxLB->TabIndex = 12;
			this->truckMaxLB->Text = L"Line1 Max";
			// 
			// truckMaxLB4
			// 
			this->truckMaxLB4->AutoSize = true;
			this->truckMaxLB4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->truckMaxLB4->Location = System::Drawing::Point(753, 63);
			this->truckMaxLB4->Name = L"truckMaxLB4";
			this->truckMaxLB4->Size = System::Drawing::Size(68, 16);
			this->truckMaxLB4->TabIndex = 13;
			this->truckMaxLB4->Text = L"Line4 Max";
			// 
			// truckScaledMinTB
			// 
			this->truckScaledMinTB->Location = System::Drawing::Point(123, 23);
			this->truckScaledMinTB->Name = L"truckScaledMinTB";
			this->truckScaledMinTB->Size = System::Drawing::Size(62, 20);
			this->truckScaledMinTB->TabIndex = 14;
			// 
			// trkScaledMinLB
			// 
			this->trkScaledMinLB->AutoSize = true;
			this->trkScaledMinLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trkScaledMinLB->Location = System::Drawing::Point(7, 27);
			this->trkScaledMinLB->Name = L"trkScaledMinLB";
			this->trkScaledMinLB->Size = System::Drawing::Size(111, 13);
			this->trkScaledMinLB->TabIndex = 15;
			this->trkScaledMinLB->Text = L"Truck Scaled Min:";
			// 
			// trkScaledMaxLB
			// 
			this->trkScaledMaxLB->AutoSize = true;
			this->trkScaledMaxLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->trkScaledMaxLB->Location = System::Drawing::Point(7, 50);
			this->trkScaledMaxLB->Name = L"trkScaledMaxLB";
			this->trkScaledMaxLB->Size = System::Drawing::Size(114, 13);
			this->trkScaledMaxLB->TabIndex = 17;
			this->trkScaledMaxLB->Text = L"Truck Scaled Max:";
			this->trkScaledMaxLB->Click += gcnew System::EventHandler(this, &CfgForm::trkMaxLB_Click);
			// 
			// truckScaledMaxTB
			// 
			this->truckScaledMaxTB->Location = System::Drawing::Point(123, 46);
			this->truckScaledMaxTB->Name = L"truckScaledMaxTB";
			this->truckScaledMaxTB->Size = System::Drawing::Size(62, 20);
			this->truckScaledMaxTB->TabIndex = 16;
			// 
			// cartScaledMinLB
			// 
			this->cartScaledMinLB->AutoSize = true;
			this->cartScaledMinLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cartScaledMinLB->Location = System::Drawing::Point(205, 28);
			this->cartScaledMinLB->Name = L"cartScaledMinLB";
			this->cartScaledMinLB->Size = System::Drawing::Size(101, 13);
			this->cartScaledMinLB->TabIndex = 19;
			this->cartScaledMinLB->Text = L"Cart Scaled Min:";
			// 
			// cartScaledMinTB
			// 
			this->cartScaledMinTB->Location = System::Drawing::Point(313, 24);
			this->cartScaledMinTB->Name = L"cartScaledMinTB";
			this->cartScaledMinTB->Size = System::Drawing::Size(62, 20);
			this->cartScaledMinTB->TabIndex = 18;
			// 
			// cartScaledMaxLB
			// 
			this->cartScaledMaxLB->AutoSize = true;
			this->cartScaledMaxLB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cartScaledMaxLB->Location = System::Drawing::Point(205, 51);
			this->cartScaledMaxLB->Name = L"cartScaledMaxLB";
			this->cartScaledMaxLB->Size = System::Drawing::Size(104, 13);
			this->cartScaledMaxLB->TabIndex = 21;
			this->cartScaledMaxLB->Text = L"Cart Scaled Max:";
			this->cartScaledMaxLB->Click += gcnew System::EventHandler(this, &CfgForm::cartScaleMaxLB_Click);
			// 
			// cartScaledMaxTB
			// 
			this->cartScaledMaxTB->Location = System::Drawing::Point(313, 47);
			this->cartScaledMaxTB->Name = L"cartScaledMaxTB";
			this->cartScaledMaxTB->Size = System::Drawing::Size(62, 20);
			this->cartScaledMaxTB->TabIndex = 20;
			// 
			// analogOutputGB
			// 
			this->analogOutputGB->Controls->Add(this->cartScaledMaxLB);
			this->analogOutputGB->Controls->Add(this->cartScaledMaxTB);
			this->analogOutputGB->Controls->Add(this->cartScaledMinLB);
			this->analogOutputGB->Controls->Add(this->cartScaledMinTB);
			this->analogOutputGB->Controls->Add(this->trkScaledMaxLB);
			this->analogOutputGB->Controls->Add(this->truckScaledMaxTB);
			this->analogOutputGB->Controls->Add(this->trkScaledMinLB);
			this->analogOutputGB->Controls->Add(this->truckScaledMinTB);
			this->analogOutputGB->Enabled = false;
			this->analogOutputGB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->analogOutputGB->Location = System::Drawing::Point(8, 616);
			this->analogOutputGB->Name = L"analogOutputGB";
			this->analogOutputGB->Size = System::Drawing::Size(392, 72);
			this->analogOutputGB->TabIndex = 22;
			this->analogOutputGB->TabStop = false;
			this->analogOutputGB->Text = L"Analog Output Scaled Setting";
			this->analogOutputGB->Visible = false;
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->AutoGenerateColumns = false;
			dataGridViewCellStyle40->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle40->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle40->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle40->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle40->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle40->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView2->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle40;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(27) {this->nBitWise, 
				this->nBitCheckI, this->nBitWiseDataGridViewTextBoxColumn, this->dAddTolDataGridViewTextBoxColumn, this->nSiloJogDataGridViewTextBoxColumn, 
				this->nSiloNumDataGridViewTextBoxColumn, this->fFallDataGridViewTextBoxColumn, this->nHoldIDataGridViewTextBoxColumn, this->nDropReadyIDataGridViewTextBoxColumn1, 
				this->nAddODataGridViewTextBoxColumn, this->nHoldODataGridViewTextBoxColumn1, this->nDoneODataGridViewTextBoxColumn1, this->nDropODataGridViewTextBoxColumn1, 
				this->nReadyODataGridViewTextBoxColumn1, this->nDoneIDataGridViewTextBoxColumn, this->nFlowRate4ODataGridViewTextBoxColumn, this->nFlowRate3ODataGridViewTextBoxColumn1, 
				this->nFlowRate2ODataGridViewTextBoxColumn1, this->nFlowRate1ODataGridViewTextBoxColumn1, this->nDelayTimeDataGridViewTextBoxColumn1, 
				this->nDelayPctDataGridViewTextBoxColumn1, this->nFlowRatePct4DataGridViewTextBoxColumn, this->nFlowRatePct3DataGridViewTextBoxColumn1, 
				this->nFlowRatePct2DataGridViewTextBoxColumn1, this->nFlowRatePct1DataGridViewTextBoxColumn1, this->bUsedDataGridViewCheckBoxColumn1, 
				this->stLblDataGridViewTextBoxColumn1});
			this->dataGridView2->DataSource = this->bitWiseBindingSource;
			dataGridViewCellStyle43->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle43->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle43->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle43->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle43->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle43->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView2->DefaultCellStyle = dataGridViewCellStyle43;
			this->dataGridView2->Location = System::Drawing::Point(926, 20);
			this->dataGridView2->Name = L"dataGridView2";
			dataGridViewCellStyle44->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle44->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle44->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle44->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle44->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle44->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView2->RowHeadersDefaultCellStyle = dataGridViewCellStyle44;
			this->dataGridView2->Size = System::Drawing::Size(186, 461);
			this->dataGridView2->TabIndex = 23;
			this->dataGridView2->Visible = false;
			// 
			// nBitWise
			// 
			this->nBitWise->DataPropertyName = L"nBitWise";
			dataGridViewCellStyle41->BackColor = System::Drawing::Color::LightGray;
			this->nBitWise->DefaultCellStyle = dataGridViewCellStyle41;
			this->nBitWise->HeaderText = L"BitWise_O";
			this->nBitWise->Name = L"nBitWise";
			this->nBitWise->ReadOnly = true;
			this->nBitWise->Width = 70;
			// 
			// nBitCheckI
			// 
			this->nBitCheckI->DataPropertyName = L"nBitCheckI";
			dataGridViewCellStyle42->BackColor = System::Drawing::Color::LightGray;
			this->nBitCheckI->DefaultCellStyle = dataGridViewCellStyle42;
			this->nBitCheckI->HeaderText = L"BitCheck_I";
			this->nBitCheckI->Name = L"nBitCheckI";
			this->nBitCheckI->ReadOnly = true;
			this->nBitCheckI->Width = 70;
			// 
			// nBitWiseDataGridViewTextBoxColumn
			// 
			this->nBitWiseDataGridViewTextBoxColumn->DataPropertyName = L"nBitWise";
			this->nBitWiseDataGridViewTextBoxColumn->HeaderText = L"nBitWise";
			this->nBitWiseDataGridViewTextBoxColumn->Name = L"nBitWiseDataGridViewTextBoxColumn";
			this->nBitWiseDataGridViewTextBoxColumn->Visible = false;
			// 
			// dAddTolDataGridViewTextBoxColumn
			// 
			this->dAddTolDataGridViewTextBoxColumn->DataPropertyName = L"dAddTol";
			this->dAddTolDataGridViewTextBoxColumn->HeaderText = L"dAddTol";
			this->dAddTolDataGridViewTextBoxColumn->Name = L"dAddTolDataGridViewTextBoxColumn";
			this->dAddTolDataGridViewTextBoxColumn->Visible = false;
			// 
			// nSiloJogDataGridViewTextBoxColumn
			// 
			this->nSiloJogDataGridViewTextBoxColumn->DataPropertyName = L"nSiloJog";
			this->nSiloJogDataGridViewTextBoxColumn->HeaderText = L"nSiloJog";
			this->nSiloJogDataGridViewTextBoxColumn->Name = L"nSiloJogDataGridViewTextBoxColumn";
			this->nSiloJogDataGridViewTextBoxColumn->Visible = false;
			// 
			// nSiloNumDataGridViewTextBoxColumn
			// 
			this->nSiloNumDataGridViewTextBoxColumn->DataPropertyName = L"nSiloNum";
			this->nSiloNumDataGridViewTextBoxColumn->HeaderText = L"nSiloNum";
			this->nSiloNumDataGridViewTextBoxColumn->Name = L"nSiloNumDataGridViewTextBoxColumn";
			this->nSiloNumDataGridViewTextBoxColumn->Visible = false;
			// 
			// fFallDataGridViewTextBoxColumn
			// 
			this->fFallDataGridViewTextBoxColumn->DataPropertyName = L"fFall";
			this->fFallDataGridViewTextBoxColumn->HeaderText = L"fFall";
			this->fFallDataGridViewTextBoxColumn->Name = L"fFallDataGridViewTextBoxColumn";
			this->fFallDataGridViewTextBoxColumn->Visible = false;
			// 
			// nHoldIDataGridViewTextBoxColumn
			// 
			this->nHoldIDataGridViewTextBoxColumn->DataPropertyName = L"nHoldI";
			this->nHoldIDataGridViewTextBoxColumn->HeaderText = L"nHoldI";
			this->nHoldIDataGridViewTextBoxColumn->Name = L"nHoldIDataGridViewTextBoxColumn";
			this->nHoldIDataGridViewTextBoxColumn->Visible = false;
			// 
			// nDropReadyIDataGridViewTextBoxColumn1
			// 
			this->nDropReadyIDataGridViewTextBoxColumn1->DataPropertyName = L"nDropReadyI";
			this->nDropReadyIDataGridViewTextBoxColumn1->HeaderText = L"nDropReadyI";
			this->nDropReadyIDataGridViewTextBoxColumn1->Name = L"nDropReadyIDataGridViewTextBoxColumn1";
			this->nDropReadyIDataGridViewTextBoxColumn1->Visible = false;
			// 
			// nAddODataGridViewTextBoxColumn
			// 
			this->nAddODataGridViewTextBoxColumn->DataPropertyName = L"nAddO";
			this->nAddODataGridViewTextBoxColumn->HeaderText = L"nAddO";
			this->nAddODataGridViewTextBoxColumn->Name = L"nAddODataGridViewTextBoxColumn";
			this->nAddODataGridViewTextBoxColumn->Visible = false;
			// 
			// nHoldODataGridViewTextBoxColumn1
			// 
			this->nHoldODataGridViewTextBoxColumn1->DataPropertyName = L"nHoldO";
			this->nHoldODataGridViewTextBoxColumn1->HeaderText = L"nHoldO";
			this->nHoldODataGridViewTextBoxColumn1->Name = L"nHoldODataGridViewTextBoxColumn1";
			this->nHoldODataGridViewTextBoxColumn1->Visible = false;
			// 
			// nDoneODataGridViewTextBoxColumn1
			// 
			this->nDoneODataGridViewTextBoxColumn1->DataPropertyName = L"nDoneO";
			this->nDoneODataGridViewTextBoxColumn1->HeaderText = L"nDoneO";
			this->nDoneODataGridViewTextBoxColumn1->Name = L"nDoneODataGridViewTextBoxColumn1";
			this->nDoneODataGridViewTextBoxColumn1->Visible = false;
			// 
			// nDropODataGridViewTextBoxColumn1
			// 
			this->nDropODataGridViewTextBoxColumn1->DataPropertyName = L"nDropO";
			this->nDropODataGridViewTextBoxColumn1->HeaderText = L"nDropO";
			this->nDropODataGridViewTextBoxColumn1->Name = L"nDropODataGridViewTextBoxColumn1";
			this->nDropODataGridViewTextBoxColumn1->Visible = false;
			// 
			// nReadyODataGridViewTextBoxColumn1
			// 
			this->nReadyODataGridViewTextBoxColumn1->DataPropertyName = L"nReadyO";
			this->nReadyODataGridViewTextBoxColumn1->HeaderText = L"nReadyO";
			this->nReadyODataGridViewTextBoxColumn1->Name = L"nReadyODataGridViewTextBoxColumn1";
			this->nReadyODataGridViewTextBoxColumn1->Visible = false;
			// 
			// nDoneIDataGridViewTextBoxColumn
			// 
			this->nDoneIDataGridViewTextBoxColumn->DataPropertyName = L"nDoneI";
			this->nDoneIDataGridViewTextBoxColumn->HeaderText = L"nDoneI";
			this->nDoneIDataGridViewTextBoxColumn->Name = L"nDoneIDataGridViewTextBoxColumn";
			this->nDoneIDataGridViewTextBoxColumn->Visible = false;
			// 
			// nFlowRate4ODataGridViewTextBoxColumn
			// 
			this->nFlowRate4ODataGridViewTextBoxColumn->DataPropertyName = L"nFlowRate4O";
			this->nFlowRate4ODataGridViewTextBoxColumn->HeaderText = L"nFlowRate4O";
			this->nFlowRate4ODataGridViewTextBoxColumn->Name = L"nFlowRate4ODataGridViewTextBoxColumn";
			this->nFlowRate4ODataGridViewTextBoxColumn->Visible = false;
			// 
			// nFlowRate3ODataGridViewTextBoxColumn1
			// 
			this->nFlowRate3ODataGridViewTextBoxColumn1->DataPropertyName = L"nFlowRate3O";
			this->nFlowRate3ODataGridViewTextBoxColumn1->HeaderText = L"nFlowRate3O";
			this->nFlowRate3ODataGridViewTextBoxColumn1->Name = L"nFlowRate3ODataGridViewTextBoxColumn1";
			this->nFlowRate3ODataGridViewTextBoxColumn1->Visible = false;
			// 
			// nFlowRate2ODataGridViewTextBoxColumn1
			// 
			this->nFlowRate2ODataGridViewTextBoxColumn1->DataPropertyName = L"nFlowRate2O";
			this->nFlowRate2ODataGridViewTextBoxColumn1->HeaderText = L"nFlowRate2O";
			this->nFlowRate2ODataGridViewTextBoxColumn1->Name = L"nFlowRate2ODataGridViewTextBoxColumn1";
			this->nFlowRate2ODataGridViewTextBoxColumn1->Visible = false;
			// 
			// nFlowRate1ODataGridViewTextBoxColumn1
			// 
			this->nFlowRate1ODataGridViewTextBoxColumn1->DataPropertyName = L"nFlowRate1O";
			this->nFlowRate1ODataGridViewTextBoxColumn1->HeaderText = L"nFlowRate1O";
			this->nFlowRate1ODataGridViewTextBoxColumn1->Name = L"nFlowRate1ODataGridViewTextBoxColumn1";
			this->nFlowRate1ODataGridViewTextBoxColumn1->Visible = false;
			// 
			// nDelayTimeDataGridViewTextBoxColumn1
			// 
			this->nDelayTimeDataGridViewTextBoxColumn1->DataPropertyName = L"nDelayTime";
			this->nDelayTimeDataGridViewTextBoxColumn1->HeaderText = L"nDelayTime";
			this->nDelayTimeDataGridViewTextBoxColumn1->Name = L"nDelayTimeDataGridViewTextBoxColumn1";
			this->nDelayTimeDataGridViewTextBoxColumn1->Visible = false;
			// 
			// nDelayPctDataGridViewTextBoxColumn1
			// 
			this->nDelayPctDataGridViewTextBoxColumn1->DataPropertyName = L"nDelayPct";
			this->nDelayPctDataGridViewTextBoxColumn1->HeaderText = L"nDelayPct";
			this->nDelayPctDataGridViewTextBoxColumn1->Name = L"nDelayPctDataGridViewTextBoxColumn1";
			this->nDelayPctDataGridViewTextBoxColumn1->Visible = false;
			// 
			// nFlowRatePct4DataGridViewTextBoxColumn
			// 
			this->nFlowRatePct4DataGridViewTextBoxColumn->DataPropertyName = L"nFlowRatePct4";
			this->nFlowRatePct4DataGridViewTextBoxColumn->HeaderText = L"nFlowRatePct4";
			this->nFlowRatePct4DataGridViewTextBoxColumn->Name = L"nFlowRatePct4DataGridViewTextBoxColumn";
			this->nFlowRatePct4DataGridViewTextBoxColumn->Visible = false;
			// 
			// nFlowRatePct3DataGridViewTextBoxColumn1
			// 
			this->nFlowRatePct3DataGridViewTextBoxColumn1->DataPropertyName = L"nFlowRatePct3";
			this->nFlowRatePct3DataGridViewTextBoxColumn1->HeaderText = L"nFlowRatePct3";
			this->nFlowRatePct3DataGridViewTextBoxColumn1->Name = L"nFlowRatePct3DataGridViewTextBoxColumn1";
			this->nFlowRatePct3DataGridViewTextBoxColumn1->Visible = false;
			// 
			// nFlowRatePct2DataGridViewTextBoxColumn1
			// 
			this->nFlowRatePct2DataGridViewTextBoxColumn1->DataPropertyName = L"nFlowRatePct2";
			this->nFlowRatePct2DataGridViewTextBoxColumn1->HeaderText = L"nFlowRatePct2";
			this->nFlowRatePct2DataGridViewTextBoxColumn1->Name = L"nFlowRatePct2DataGridViewTextBoxColumn1";
			this->nFlowRatePct2DataGridViewTextBoxColumn1->Visible = false;
			// 
			// nFlowRatePct1DataGridViewTextBoxColumn1
			// 
			this->nFlowRatePct1DataGridViewTextBoxColumn1->DataPropertyName = L"nFlowRatePct1";
			this->nFlowRatePct1DataGridViewTextBoxColumn1->HeaderText = L"nFlowRatePct1";
			this->nFlowRatePct1DataGridViewTextBoxColumn1->Name = L"nFlowRatePct1DataGridViewTextBoxColumn1";
			this->nFlowRatePct1DataGridViewTextBoxColumn1->Visible = false;
			// 
			// bUsedDataGridViewCheckBoxColumn1
			// 
			this->bUsedDataGridViewCheckBoxColumn1->DataPropertyName = L"bUsed";
			this->bUsedDataGridViewCheckBoxColumn1->HeaderText = L"bUsed";
			this->bUsedDataGridViewCheckBoxColumn1->Name = L"bUsedDataGridViewCheckBoxColumn1";
			this->bUsedDataGridViewCheckBoxColumn1->Visible = false;
			// 
			// stLblDataGridViewTextBoxColumn1
			// 
			this->stLblDataGridViewTextBoxColumn1->DataPropertyName = L"stLbl";
			this->stLblDataGridViewTextBoxColumn1->HeaderText = L"stLbl";
			this->stLblDataGridViewTextBoxColumn1->Name = L"stLblDataGridViewTextBoxColumn1";
			this->stLblDataGridViewTextBoxColumn1->Visible = false;
			// 
			// bitWiseBindingSource
			// 
			this->bitWiseBindingSource->DataSource = As::Cfg::typeid;
			// 
			// bitWiseCB
			// 
			this->bitWiseCB->AutoSize = true;
			this->bitWiseCB->Enabled = false;
			this->bitWiseCB->Location = System::Drawing::Point(575, 123);
			this->bitWiseCB->Name = L"bitWiseCB";
			this->bitWiseCB->Size = System::Drawing::Size(151, 17);
			this->bitWiseCB->TabIndex = 24;
			this->bitWiseCB->Text = L"Send BitWise to PDM (LB)";
			this->bitWiseCB->UseVisualStyleBackColor = true;
			this->bitWiseCB->Click += gcnew System::EventHandler(this, &CfgForm::bitWiseCB_Click);
			// 
			// sendTargetOTb
			// 
			this->sendTargetOTb->Location = System::Drawing::Point(713, 162);
			this->sendTargetOTb->Name = L"sendTargetOTb";
			this->sendTargetOTb->ReadOnly = true;
			this->sendTargetOTb->Size = System::Drawing::Size(38, 20);
			this->sendTargetOTb->TabIndex = 25;
			this->sendTargetOTb->Visible = false;
			// 
			// sendTargetLb
			// 
			this->sendTargetLb->AutoSize = true;
			this->sendTargetLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->sendTargetLb->Location = System::Drawing::Point(572, 165);
			this->sendTargetLb->Name = L"sendTargetLb";
			this->sendTargetLb->Size = System::Drawing::Size(119, 13);
			this->sendTargetLb->TabIndex = 26;
			this->sendTargetLb->Text = L"Send Target Output";
			this->sendTargetLb->Visible = false;
			// 
			// receivedTargetLb
			// 
			this->receivedTargetLb->AutoSize = true;
			this->receivedTargetLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->receivedTargetLb->Location = System::Drawing::Point(572, 199);
			this->receivedTargetLb->Name = L"receivedTargetLb";
			this->receivedTargetLb->Size = System::Drawing::Size(135, 13);
			this->receivedTargetLb->TabIndex = 28;
			this->receivedTargetLb->Text = L"Received Target Input";
			this->receivedTargetLb->Visible = false;
			// 
			// receivedTargetITb
			// 
			this->receivedTargetITb->Location = System::Drawing::Point(713, 195);
			this->receivedTargetITb->Name = L"receivedTargetITb";
			this->receivedTargetITb->ReadOnly = true;
			this->receivedTargetITb->Size = System::Drawing::Size(38, 20);
			this->receivedTargetITb->TabIndex = 27;
			this->receivedTargetITb->Visible = false;
			// 
			// keepAliveOLb
			// 
			this->keepAliveOLb->AutoSize = true;
			this->keepAliveOLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->keepAliveOLb->Location = System::Drawing::Point(573, 233);
			this->keepAliveOLb->Name = L"keepAliveOLb";
			this->keepAliveOLb->Size = System::Drawing::Size(110, 13);
			this->keepAliveOLb->TabIndex = 30;
			this->keepAliveOLb->Text = L"Keep Alive Output";
			this->keepAliveOLb->Visible = false;
			// 
			// keepAliveOTb
			// 
			this->keepAliveOTb->Location = System::Drawing::Point(713, 228);
			this->keepAliveOTb->Name = L"keepAliveOTb";
			this->keepAliveOTb->ReadOnly = true;
			this->keepAliveOTb->Size = System::Drawing::Size(38, 20);
			this->keepAliveOTb->TabIndex = 29;
			this->keepAliveOTb->Visible = false;
			// 
			// keepAliveILb
			// 
			this->keepAliveILb->AutoSize = true;
			this->keepAliveILb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->keepAliveILb->Location = System::Drawing::Point(574, 267);
			this->keepAliveILb->Name = L"keepAliveILb";
			this->keepAliveILb->Size = System::Drawing::Size(101, 13);
			this->keepAliveILb->TabIndex = 32;
			this->keepAliveILb->Text = L"Keep Alive Input";
			this->keepAliveILb->Visible = false;
			// 
			// keepAliveITb
			// 
			this->keepAliveITb->Location = System::Drawing::Point(713, 261);
			this->keepAliveITb->Name = L"keepAliveITb";
			this->keepAliveITb->ReadOnly = true;
			this->keepAliveITb->Size = System::Drawing::Size(38, 20);
			this->keepAliveITb->TabIndex = 31;
			this->keepAliveITb->Visible = false;
			// 
			// siloBit1Lb
			// 
			this->siloBit1Lb->AutoSize = true;
			this->siloBit1Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->siloBit1Lb->Location = System::Drawing::Point(584, 328);
			this->siloBit1Lb->Name = L"siloBit1Lb";
			this->siloBit1Lb->Size = System::Drawing::Size(50, 13);
			this->siloBit1Lb->TabIndex = 33;
			this->siloBit1Lb->Text = L"SiloBit1";
			this->siloBit1Lb->Visible = false;
			// 
			// siloBit1Tb
			// 
			this->siloBit1Tb->Location = System::Drawing::Point(640, 325);
			this->siloBit1Tb->Name = L"siloBit1Tb";
			this->siloBit1Tb->ReadOnly = true;
			this->siloBit1Tb->Size = System::Drawing::Size(38, 20);
			this->siloBit1Tb->TabIndex = 34;
			this->siloBit1Tb->Visible = false;
			// 
			// siloBit2Tb
			// 
			this->siloBit2Tb->Location = System::Drawing::Point(640, 351);
			this->siloBit2Tb->Name = L"siloBit2Tb";
			this->siloBit2Tb->ReadOnly = true;
			this->siloBit2Tb->Size = System::Drawing::Size(38, 20);
			this->siloBit2Tb->TabIndex = 36;
			this->siloBit2Tb->Visible = false;
			// 
			// siloBit2Lb
			// 
			this->siloBit2Lb->AutoSize = true;
			this->siloBit2Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->siloBit2Lb->Location = System::Drawing::Point(584, 354);
			this->siloBit2Lb->Name = L"siloBit2Lb";
			this->siloBit2Lb->Size = System::Drawing::Size(50, 13);
			this->siloBit2Lb->TabIndex = 35;
			this->siloBit2Lb->Text = L"SiloBit2";
			this->siloBit2Lb->Visible = false;
			// 
			// siloBit3Tb
			// 
			this->siloBit3Tb->Location = System::Drawing::Point(640, 377);
			this->siloBit3Tb->Name = L"siloBit3Tb";
			this->siloBit3Tb->ReadOnly = true;
			this->siloBit3Tb->Size = System::Drawing::Size(38, 20);
			this->siloBit3Tb->TabIndex = 38;
			this->siloBit3Tb->Visible = false;
			// 
			// siloBit3Lb
			// 
			this->siloBit3Lb->AutoSize = true;
			this->siloBit3Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->siloBit3Lb->Location = System::Drawing::Point(584, 380);
			this->siloBit3Lb->Name = L"siloBit3Lb";
			this->siloBit3Lb->Size = System::Drawing::Size(50, 13);
			this->siloBit3Lb->TabIndex = 37;
			this->siloBit3Lb->Text = L"SiloBit3";
			this->siloBit3Lb->Visible = false;
			// 
			// siloBit4Tb
			// 
			this->siloBit4Tb->Location = System::Drawing::Point(640, 407);
			this->siloBit4Tb->Name = L"siloBit4Tb";
			this->siloBit4Tb->ReadOnly = true;
			this->siloBit4Tb->Size = System::Drawing::Size(38, 20);
			this->siloBit4Tb->TabIndex = 40;
			this->siloBit4Tb->Visible = false;
			// 
			// siloBit4Lb
			// 
			this->siloBit4Lb->AutoSize = true;
			this->siloBit4Lb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->siloBit4Lb->Location = System::Drawing::Point(584, 410);
			this->siloBit4Lb->Name = L"siloBit4Lb";
			this->siloBit4Lb->Size = System::Drawing::Size(50, 13);
			this->siloBit4Lb->TabIndex = 39;
			this->siloBit4Lb->Text = L"SiloBit4";
			this->siloBit4Lb->Visible = false;
			// 
			// siloOutputLb
			// 
			this->siloOutputLb->AutoSize = true;
			this->siloOutputLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->siloOutputLb->Location = System::Drawing::Point(635, 303);
			this->siloOutputLb->Name = L"siloOutputLb";
			this->siloOutputLb->Size = System::Drawing::Size(45, 13);
			this->siloOutputLb->TabIndex = 41;
			this->siloOutputLb->Text = L"Output";
			this->siloOutputLb->Visible = false;
			// 
			// siloCheckLb
			// 
			this->siloCheckLb->AutoSize = true;
			this->siloCheckLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->siloCheckLb->Location = System::Drawing::Point(700, 304);
			this->siloCheckLb->Name = L"siloCheckLb";
			this->siloCheckLb->Size = System::Drawing::Size(84, 13);
			this->siloCheckLb->TabIndex = 42;
			this->siloCheckLb->Text = L"Bit Check Inp";
			this->siloCheckLb->Visible = false;
			this->siloCheckLb->Click += gcnew System::EventHandler(this, &CfgForm::siloCheckLb_Click);
			// 
			// siloBitCheck1Tb
			// 
			this->siloBitCheck1Tb->Location = System::Drawing::Point(721, 325);
			this->siloBitCheck1Tb->Name = L"siloBitCheck1Tb";
			this->siloBitCheck1Tb->ReadOnly = true;
			this->siloBitCheck1Tb->Size = System::Drawing::Size(38, 20);
			this->siloBitCheck1Tb->TabIndex = 43;
			this->siloBitCheck1Tb->Visible = false;
			// 
			// siloBitCheck2Tb
			// 
			this->siloBitCheck2Tb->Location = System::Drawing::Point(721, 351);
			this->siloBitCheck2Tb->Name = L"siloBitCheck2Tb";
			this->siloBitCheck2Tb->ReadOnly = true;
			this->siloBitCheck2Tb->Size = System::Drawing::Size(38, 20);
			this->siloBitCheck2Tb->TabIndex = 44;
			this->siloBitCheck2Tb->Visible = false;
			// 
			// siloBitCheck3Tb
			// 
			this->siloBitCheck3Tb->Location = System::Drawing::Point(721, 377);
			this->siloBitCheck3Tb->Name = L"siloBitCheck3Tb";
			this->siloBitCheck3Tb->ReadOnly = true;
			this->siloBitCheck3Tb->Size = System::Drawing::Size(38, 20);
			this->siloBitCheck3Tb->TabIndex = 45;
			this->siloBitCheck3Tb->Visible = false;
			// 
			// siloBitCheck4Tb
			// 
			this->siloBitCheck4Tb->Location = System::Drawing::Point(721, 403);
			this->siloBitCheck4Tb->Name = L"siloBitCheck4Tb";
			this->siloBitCheck4Tb->ReadOnly = true;
			this->siloBitCheck4Tb->Size = System::Drawing::Size(38, 20);
			this->siloBitCheck4Tb->TabIndex = 46;
			this->siloBitCheck4Tb->Visible = false;
			// 
			// keepOnTimeTb
			// 
			this->keepOnTimeTb->Location = System::Drawing::Point(767, 228);
			this->keepOnTimeTb->Name = L"keepOnTimeTb";
			this->keepOnTimeTb->ReadOnly = true;
			this->keepOnTimeTb->Size = System::Drawing::Size(38, 20);
			this->keepOnTimeTb->TabIndex = 47;
			this->keepOnTimeTb->Visible = false;
			// 
			// keepOffTimeTb
			// 
			this->keepOffTimeTb->Location = System::Drawing::Point(811, 228);
			this->keepOffTimeTb->Name = L"keepOffTimeTb";
			this->keepOffTimeTb->ReadOnly = true;
			this->keepOffTimeTb->Size = System::Drawing::Size(38, 20);
			this->keepOffTimeTb->TabIndex = 48;
			this->keepOffTimeTb->Visible = false;
			// 
			// keepOnTimeLb
			// 
			this->keepOnTimeLb->AutoSize = true;
			this->keepOnTimeLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->keepOnTimeLb->Location = System::Drawing::Point(773, 211);
			this->keepOnTimeLb->Name = L"keepOnTimeLb";
			this->keepOnTimeLb->Size = System::Drawing::Size(23, 13);
			this->keepOnTimeLb->TabIndex = 49;
			this->keepOnTimeLb->Text = L"On";
			this->keepOnTimeLb->Visible = false;
			// 
			// keepOffTimeLb
			// 
			this->keepOffTimeLb->AutoSize = true;
			this->keepOffTimeLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->keepOffTimeLb->Location = System::Drawing::Point(817, 211);
			this->keepOffTimeLb->Name = L"keepOffTimeLb";
			this->keepOffTimeLb->Size = System::Drawing::Size(24, 13);
			this->keepOffTimeLb->TabIndex = 50;
			this->keepOffTimeLb->Text = L"Off";
			this->keepOffTimeLb->Visible = false;
			// 
			// keepTimeLb
			// 
			this->keepTimeLb->AutoSize = true;
			this->keepTimeLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->keepTimeLb->Location = System::Drawing::Point(854, 231);
			this->keepTimeLb->Name = L"keepTimeLb";
			this->keepTimeLb->Size = System::Drawing::Size(51, 13);
			this->keepTimeLb->TabIndex = 51;
			this->keepTimeLb->Text = L"(100ms)";
			this->keepTimeLb->Visible = false;
			// 
			// laneTare4Tb
			// 
			this->laneTare4Tb->Location = System::Drawing::Point(834, 403);
			this->laneTare4Tb->Name = L"laneTare4Tb";
			this->laneTare4Tb->ReadOnly = true;
			this->laneTare4Tb->Size = System::Drawing::Size(38, 20);
			this->laneTare4Tb->TabIndex = 56;
			this->laneTare4Tb->Visible = false;
			// 
			// laneTare3Tb
			// 
			this->laneTare3Tb->Location = System::Drawing::Point(834, 377);
			this->laneTare3Tb->Name = L"laneTare3Tb";
			this->laneTare3Tb->ReadOnly = true;
			this->laneTare3Tb->Size = System::Drawing::Size(38, 20);
			this->laneTare3Tb->TabIndex = 55;
			this->laneTare3Tb->Visible = false;
			// 
			// laneTare2Tb
			// 
			this->laneTare2Tb->Location = System::Drawing::Point(834, 351);
			this->laneTare2Tb->Name = L"laneTare2Tb";
			this->laneTare2Tb->ReadOnly = true;
			this->laneTare2Tb->Size = System::Drawing::Size(38, 20);
			this->laneTare2Tb->TabIndex = 54;
			this->laneTare2Tb->Visible = false;
			// 
			// laneTare1Tb
			// 
			this->laneTare1Tb->Location = System::Drawing::Point(834, 325);
			this->laneTare1Tb->Name = L"laneTare1Tb";
			this->laneTare1Tb->ReadOnly = true;
			this->laneTare1Tb->Size = System::Drawing::Size(38, 20);
			this->laneTare1Tb->TabIndex = 53;
			this->laneTare1Tb->Visible = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(813, 304);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(87, 13);
			this->label4->TabIndex = 52;
			this->label4->Text = L"Lane Tare Inp";
			this->label4->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(801, 410);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(21, 13);
			this->label5->TabIndex = 60;
			this->label5->Text = L"L4";
			this->label5->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(801, 380);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(21, 13);
			this->label6->TabIndex = 59;
			this->label6->Text = L"L3";
			this->label6->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(801, 354);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(21, 13);
			this->label7->TabIndex = 58;
			this->label7->Text = L"L2";
			this->label7->Visible = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(801, 328);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(21, 13);
			this->label8->TabIndex = 57;
			this->label8->Text = L"L1";
			this->label8->Visible = false;
			// 
			// truckMaxLB2
			// 
			this->truckMaxLB2->AutoSize = true;
			this->truckMaxLB2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->truckMaxLB2->Location = System::Drawing::Point(481, 62);
			this->truckMaxLB2->Name = L"truckMaxLB2";
			this->truckMaxLB2->Size = System::Drawing::Size(68, 16);
			this->truckMaxLB2->TabIndex = 62;
			this->truckMaxLB2->Text = L"Line2 Max";
			// 
			// lineLB2
			// 
			this->lineLB2->AutoSize = true;
			this->lineLB2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lineLB2->Location = System::Drawing::Point(478, 41);
			this->lineLB2->Name = L"lineLB2";
			this->lineLB2->Size = System::Drawing::Size(125, 16);
			this->lineLB2->TabIndex = 61;
			this->lineLB2->Text = L"Line2 Scale Max:";
			// 
			// truckMaxLB3
			// 
			this->truckMaxLB3->AutoSize = true;
			this->truckMaxLB3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->truckMaxLB3->Location = System::Drawing::Point(617, 62);
			this->truckMaxLB3->Name = L"truckMaxLB3";
			this->truckMaxLB3->Size = System::Drawing::Size(68, 16);
			this->truckMaxLB3->TabIndex = 64;
			this->truckMaxLB3->Text = L"Line3 Max";
			// 
			// lineLB3
			// 
			this->lineLB3->AutoSize = true;
			this->lineLB3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lineLB3->Location = System::Drawing::Point(614, 41);
			this->lineLB3->Name = L"lineLB3";
			this->lineLB3->Size = System::Drawing::Size(125, 16);
			this->lineLB3->TabIndex = 63;
			this->lineLB3->Text = L"Line3 Scale Max:";
			// 
			// CfgForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1150, 546);
			this->Controls->Add(this->truckMaxLB3);
			this->Controls->Add(this->lineLB3);
			this->Controls->Add(this->truckMaxLB2);
			this->Controls->Add(this->lineLB2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->laneTare4Tb);
			this->Controls->Add(this->laneTare3Tb);
			this->Controls->Add(this->laneTare2Tb);
			this->Controls->Add(this->laneTare1Tb);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->keepTimeLb);
			this->Controls->Add(this->keepOffTimeLb);
			this->Controls->Add(this->keepOnTimeLb);
			this->Controls->Add(this->keepOffTimeTb);
			this->Controls->Add(this->keepOnTimeTb);
			this->Controls->Add(this->siloBitCheck4Tb);
			this->Controls->Add(this->siloBitCheck3Tb);
			this->Controls->Add(this->siloBitCheck2Tb);
			this->Controls->Add(this->siloBitCheck1Tb);
			this->Controls->Add(this->siloCheckLb);
			this->Controls->Add(this->siloOutputLb);
			this->Controls->Add(this->siloBit4Tb);
			this->Controls->Add(this->siloBit4Lb);
			this->Controls->Add(this->siloBit3Tb);
			this->Controls->Add(this->siloBit3Lb);
			this->Controls->Add(this->siloBit2Tb);
			this->Controls->Add(this->siloBit2Lb);
			this->Controls->Add(this->siloBit1Tb);
			this->Controls->Add(this->siloBit1Lb);
			this->Controls->Add(this->keepAliveILb);
			this->Controls->Add(this->keepAliveITb);
			this->Controls->Add(this->keepAliveOLb);
			this->Controls->Add(this->keepAliveOTb);
			this->Controls->Add(this->receivedTargetLb);
			this->Controls->Add(this->receivedTargetITb);
			this->Controls->Add(this->sendTargetLb);
			this->Controls->Add(this->sendTargetOTb);
			this->Controls->Add(this->bitWiseCB);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->analogOutputGB);
			this->Controls->Add(this->truckMaxLB4);
			this->Controls->Add(this->truckMaxLB);
			this->Controls->Add(this->lineLB4);
			this->Controls->Add(this->lineLB1);
			this->Controls->Add(this->sendTargetCB);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->closeBt);
			this->Controls->Add(this->autoAddCb);
			this->Controls->Add(this->exitBt);
			this->Controls->Add(this->editIOCB);
			this->Controls->Add(this->showAllCB);
			this->Controls->Add(this->pdmPlcCB);
			this->Controls->Add(this->saveBt);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"CfgForm";
			this->Text = L"CfgForm";
			this->Load += gcnew System::EventHandler(this, &CfgForm::CfgForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->cfgBindingSource))->EndInit();
			this->analogOutputGB->ResumeLayout(false);
			this->analogOutputGB->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bitWiseBindingSource))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			void loadCfg(void)
			{
				lCfg = gcnew Generic::List<Cfg^>();
				bCfg = gcnew Generic::List<Cfg^>();
				Cfg^ pCfg;
				pCfg = gcnew Cfg();

				if(psIni->bSendBitWise)
				{
					 nFlowRate1ODataGridViewTextBoxColumn->Visible = false;
					 nFlowRate2ODataGridViewTextBoxColumn->Visible = false;
					 nFlowRate3ODataGridViewTextBoxColumn->Visible = false;
					 nFlowRatePct1DataGridViewTextBoxColumn->Visible = false;
					 nFlowRatePct2DataGridViewTextBoxColumn->Visible = false;
					 nFlowRatePct3DataGridViewTextBoxColumn->Visible = false;
					 Column1->Visible = false;
					 nSiloJog->Visible = false;
					 nDelayPctDataGridViewTextBoxColumn->Visible = false;
					 nDelayTimeDataGridViewTextBoxColumn->Visible = false;
					 nReadyODataGridViewTextBoxColumn->Visible = false;
					 nDropReadyIDataGridViewTextBoxColumn->Visible = false;
					 label1->Visible = false;
					 autoAddCb->Visible = false;
					 dAddTol->Visible = false;
					 analogOutputGB->Visible = true;

					for (int i=0; i < 12; i++)
					{
						pCfg = gcnew Cfg();
	//					if(psIni->asSilos[i].bUsed)
						{
							pCfg->stLbl = gcnew String(psIni->asSilos[i].acMat);
							pCfg->stProduct = gcnew String(psIni->asSilos[i].acProduct);		//DC 4.0.2
							pCfg->bUsed = psIni->asSilos[i].bUsed;
							pCfg->nFlowRatePct1 = psIni->asSilos[i].nFlowRatePct1;
							pCfg->nFlowRatePct2 = psIni->asSilos[i].nFlowRatePct2;
							pCfg->nFlowRatePct3 = psIni->asSilos[i].nFlowRatePct3;
							pCfg->nFlowRatePct4 = psIni->asSilos[i].nFlowRatePct4;
							pCfg->nDelayPct = psIni->asSilos[i].nDelayPct;
							pCfg->nDelayTime = psIni->asSilos[i].nDelayTime;
							pCfg->nFlowRate1O = psIni->asSilos[i].nFlowRate1O;
							pCfg->nFlowRate2O = psIni->asSilos[i].nFlowRate2O;
							pCfg->nFlowRate3O = psIni->asSilos[i].nFlowRate3O;
							pCfg->nFlowRate4O = psIni->asSilos[i].nFlowRate4O;
							pCfg->nDoneI= psIni->asSilos[i].nDoneI;
							pCfg->nReadyO= psIni->asSilos[i].nReadyO;
							pCfg->nDropO= psIni->asSilos[i].nDropO;
							pCfg->nDoneO= psIni->asSilos[i].nDoneO;
							pCfg->nHoldO= psIni->asSilos[i].nHoldO;
							pCfg->nAddO= psIni->asSilos[i].nAddO;
							pCfg->nDropReadyI= psIni->asSilos[i].nDropReadyI;
							pCfg->nHoldI= psIni->asSilos[i].nHoldI;
							pCfg->fFall = psIni->asSilos[i].fFall;
							pCfg->nSiloNum = psIni->asSilos[i].nSiloNum;					//DC 4.0.3
							pCfg->nSiloJog = psIni->asSilos[i].nSiloJog;
							pCfg->dAddTol = psIni->asSilos[i].dAddTol;
							lCfg->Add(pCfg);
						}
					}
					truckScaledMinTB->Text = psIni->nTruckMin.ToString();
					truckScaledMaxTB->Text = psIni->nTruckMax.ToString();
					cartScaledMinTB->Text = psIni->nCartMin.ToString();
					cartScaledMaxTB->Text = psIni->nCartMax.ToString();
				}
				else
				{
					for (int i=0; i < 12; i++)
					{
						pCfg = gcnew Cfg();
	//					if(psIni->asSilos[i].bUsed)
						{
							pCfg->stLbl = gcnew String(psIni->asSilos[i].acMat);
							pCfg->stProduct = gcnew String(psIni->asSilos[i].acProduct);		//DC 4.0.2
							pCfg->bUsed = psIni->asSilos[i].bUsed;
							pCfg->nFlowRatePct1 = psIni->asSilos[i].nFlowRatePct1;
							pCfg->nFlowRatePct2 = psIni->asSilos[i].nFlowRatePct2;
							pCfg->nFlowRatePct3 = psIni->asSilos[i].nFlowRatePct3;
							pCfg->nFlowRatePct4 = psIni->asSilos[i].nFlowRatePct4;
							pCfg->nDelayPct = psIni->asSilos[i].nDelayPct;
							pCfg->nDelayTime = psIni->asSilos[i].nDelayTime;
							pCfg->nFlowRate1O = psIni->asSilos[i].nFlowRate1O;
							pCfg->nFlowRate2O = psIni->asSilos[i].nFlowRate2O;
							pCfg->nFlowRate3O = psIni->asSilos[i].nFlowRate3O;
							pCfg->nFlowRate4O = psIni->asSilos[i].nFlowRate4O;
							pCfg->nDoneI= psIni->asSilos[i].nDoneI;
							pCfg->nReadyO= psIni->asSilos[i].nReadyO;
							pCfg->nDropO= psIni->asSilos[i].nDropO;
							pCfg->nDoneO= psIni->asSilos[i].nDoneO;
							pCfg->nHoldO= psIni->asSilos[i].nHoldO;
							pCfg->nAddO= psIni->asSilos[i].nAddO;
							pCfg->nDropReadyI= psIni->asSilos[i].nDropReadyI;
							pCfg->nHoldI= psIni->asSilos[i].nHoldI;
							pCfg->fFall = psIni->asSilos[i].fFall;
							pCfg->nSiloNum = psIni->asSilos[i].nSiloNum;						//DC 4.0.3
							pCfg->nSiloJog = psIni->asSilos[i].nSiloJog;
							pCfg->dAddTol = psIni->asSilos[i].dAddTol;
							lCfg->Add(pCfg);
						}
					}
				}
				if(psIni->bSendBitWise)
				{
					pCfg = gcnew Cfg();
					for(int i=0; i < 19;i++)
					{
						pCfg = gcnew Cfg();
						pCfg->nBitWise = psIni->nBitWise[i];
						pCfg->nBitCheckI = psIni->nBitCheckI[i];
						bCfg->Add(pCfg);
					}
					this->sendTargetOTb->Text = psIni->nSendTargetO.ToString();
					this->receivedTargetITb->Text = psIni->nReceivedTargetI.ToString();
					this->keepAliveOTb->Text = psIni->nKeepAliveO.ToString();
					this->keepAliveITb->Text = psIni->nKeepAliveI.ToString();
					this->keepOnTimeTb->Text = psIni->nKeepOnTime.ToString();
					this->keepOffTimeTb->Text = psIni->nKeepOffTime.ToString();
					this->siloBit1Tb->Text = psIni->nSiloBit[0].ToString();
					this->siloBit2Tb->Text = psIni->nSiloBit[1].ToString();
					this->siloBit3Tb->Text = psIni->nSiloBit[2].ToString();
					this->siloBit4Tb->Text = psIni->nSiloBit[3].ToString();
					this->siloBitCheck1Tb->Text = psIni->nSiloBitCheck[0].ToString();
					this->siloBitCheck2Tb->Text = psIni->nSiloBitCheck[1].ToString();
					this->siloBitCheck3Tb->Text = psIni->nSiloBitCheck[2].ToString();
					this->siloBitCheck4Tb->Text = psIni->nSiloBitCheck[3].ToString();
					this->laneTare1Tb->Text = psIni->nLaneTareI[0].ToString();
					this->laneTare2Tb->Text = psIni->nLaneTareI[1].ToString();
					this->laneTare3Tb->Text = psIni->nLaneTareI[2].ToString();
					this->laneTare4Tb->Text = psIni->nLaneTareI[3].ToString();
				}

				bitWiseBindingSource->DataSource = bCfg;				
				cfgBindingSource->DataSource = lCfg;

				this->pdmPlcCB->Checked = psIni->bPdmPlc;
				this->autoAddCb->Checked = psIni->bAutoAdd;
				this->sendTargetCB->Checked = psIni->bSendTarget;

				this->truckMaxLB->Visible = psIni->nNumLanes > 0;	//DC 4.1.2
				this->lineLB1->Visible = psIni->nNumLanes > 0;		//DC 4.1.2
				this->truckMaxLB2->Visible = psIni->nNumLanes > 1;	//DC 4.1.2
				this->lineLB2->Visible = psIni->nNumLanes > 1;		//DC 4.1.2
				this->truckMaxLB3->Visible = psIni->nNumLanes > 2;	//DC 4.1.2
				this->lineLB3->Visible = psIni->nNumLanes > 2;		//DC 4.1.2
				this->truckMaxLB4->Visible = psIni->nNumLanes > 3;	//DC 4.1.2
				this->lineLB4->Visible = psIni->nNumLanes > 3;		//DC 4.1.2

				this->truckMaxLB->Text = psIni->fBotScaleMax.ToString() + " TN";
				this->truckMaxLB2->Text = psIni->fBotScaleMaxL2.ToString() + " TN";		//DC 4.1.2
				this->truckMaxLB3->Text = psIni->fBotScaleMaxL3.ToString() + " TN";		//DC 4.1.2
				this->truckMaxLB4->Text = psIni->fBotScaleMaxL4.ToString() + " TN";
				this->bitWiseCB->Checked = psIni->bSendBitWise;

			}

			void saveCfg(void)
			{
				if(psIni->bSendBitWise)
				{
					for (int i=0; i < 12; i++)
					{
						Cfg^ pCfg = lCfg[i];
						trans(psIni->asSilos[i].acMat, pCfg->stLbl);
						trans(psIni->asSilos[i].acProduct, pCfg->stProduct);		//DC 4.0.2
						psIni->asSilos[i].bUsed = pCfg->bUsed;
						psIni->asSilos[i].nFlowRatePct1 = 0;	//pCfg->nFlowRatePct1;
						psIni->asSilos[i].nFlowRatePct2 = 0;	//pCfg->nFlowRatePct2;
						psIni->asSilos[i].nFlowRatePct3 = 0;	//pCfg->nFlowRatePct3;
						psIni->asSilos[i].nFlowRatePct4 = 0;	//pCfg->nFlowRatePct4;
						psIni->asSilos[i].nDelayPct = 0;	//pCfg->nDelayPct;
						psIni->asSilos[i].nDelayTime = 0;	//pCfg->nDelayTime;
						psIni->asSilos[i].nFlowRate1O = 0;	//pCfg->nFlowRate1O;
						psIni->asSilos[i].nFlowRate2O = 0;	//pCfg->nFlowRate2O;
						psIni->asSilos[i].nFlowRate3O = 0;	//pCfg->nFlowRate3O;
						psIni->asSilos[i].nFlowRate4O = 0;	//pCfg->nFlowRate4O;
						psIni->asSilos[i].nDoneI = pCfg->nDoneI;
						psIni->asSilos[i].nReadyO = 0;	//pCfg->nReadyO;
						psIni->asSilos[i].nDropO = pCfg->nDropO;
						psIni->asSilos[i].nDoneO = pCfg->nDoneO;
						psIni->asSilos[i].nHoldO = pCfg->nHoldO;
						psIni->asSilos[i].nAddO = 0;	//pCfg->nAddO;
						psIni->asSilos[i].nDropReadyI = 0;	// pCfg->nDropReadyI;
						psIni->asSilos[i].nHoldI = pCfg->nHoldI;
						psIni->asSilos[i].fFall = 0;	//pCfg->fFall;
						psIni->asSilos[i].nSiloNum = pCfg->nSiloNum;			//DC 4.0.3
						psIni->asSilos[i].nSiloJog = 0;	//pCfg->nSiloJog;
						psIni->asSilos[i].dAddTol = 0;	//pCfg->dAddTol;
					}
					psIni->nTruckMin = Convert::ToUInt32(truckScaledMinTB->Text);
					psIni->nTruckMax = Convert::ToUInt32(truckScaledMaxTB->Text);
					psIni->nCartMin = Convert::ToUInt32(cartScaledMinTB->Text);
					psIni->nCartMax = Convert::ToUInt32(cartScaledMaxTB->Text);
				}
				else
				{
					for (int i=0; i < 12; i++)
					{
						Cfg^ pCfg = lCfg[i];
						trans(psIni->asSilos[i].acMat, pCfg->stLbl);
						trans(psIni->asSilos[i].acProduct, pCfg->stProduct);		//DC 4.0.2
						psIni->asSilos[i].bUsed = pCfg->bUsed;
						psIni->asSilos[i].nFlowRatePct1 = pCfg->nFlowRatePct1;
						psIni->asSilos[i].nFlowRatePct2 = pCfg->nFlowRatePct2;
						psIni->asSilos[i].nFlowRatePct3 = pCfg->nFlowRatePct3;
						psIni->asSilos[i].nFlowRatePct4 = pCfg->nFlowRatePct4;
						psIni->asSilos[i].nDelayPct = pCfg->nDelayPct;
						psIni->asSilos[i].nDelayTime = pCfg->nDelayTime;
						psIni->asSilos[i].nFlowRate1O = pCfg->nFlowRate1O;
						psIni->asSilos[i].nFlowRate2O = pCfg->nFlowRate2O;
						psIni->asSilos[i].nFlowRate3O = pCfg->nFlowRate3O;
						psIni->asSilos[i].nFlowRate4O = pCfg->nFlowRate4O;
						psIni->asSilos[i].nDoneI = pCfg->nDoneI;
						psIni->asSilos[i].nReadyO = pCfg->nReadyO;
						psIni->asSilos[i].nDropO = pCfg->nDropO;
						psIni->asSilos[i].nDoneO = pCfg->nDoneO;
						psIni->asSilos[i].nHoldO = pCfg->nHoldO;
						psIni->asSilos[i].nAddO = pCfg->nAddO;
						psIni->asSilos[i].nDropReadyI = pCfg->nDropReadyI;
						psIni->asSilos[i].nHoldI = pCfg->nHoldI;
						psIni->asSilos[i].fFall = pCfg->fFall;
						psIni->asSilos[i].nSiloNum = pCfg->nSiloNum;				//DC 4.0.3
						psIni->asSilos[i].nSiloJog = pCfg->nSiloJog;
						psIni->asSilos[i].dAddTol = pCfg->dAddTol;
					}
				}

				if(psIni->bSendBitWise)
				{
					for(int i=0; i < 19;i++)
					{
						Cfg^ pCfg = bCfg[i];
						psIni->nBitWise[i]= pCfg->nBitWise;
						psIni->nBitCheckI[i]= pCfg->nBitCheckI;
					}
					psIni->nSendTargetO = Convert::ToUInt32(this->sendTargetOTb->Text);
					psIni->nReceivedTargetI = Convert::ToUInt32(this->receivedTargetITb->Text);
					psIni->nKeepAliveO = Convert::ToUInt32(this->keepAliveOTb->Text);
					psIni->nKeepAliveI = Convert::ToUInt32(this->keepAliveITb->Text);
					psIni->nKeepOnTime = Convert::ToUInt32(this->keepOnTimeTb->Text);
					psIni->nKeepOffTime = Convert::ToUInt32(this->keepOffTimeTb->Text);
					psIni->nSiloBit[0] = Convert::ToUInt32(this->siloBit1Tb->Text);
					psIni->nSiloBit[1] = Convert::ToUInt32(this->siloBit2Tb->Text);
					psIni->nSiloBit[2] = Convert::ToUInt32(this->siloBit3Tb->Text);
					psIni->nSiloBit[3] = Convert::ToUInt32(this->siloBit4Tb->Text);
					psIni->nSiloBitCheck[0] = Convert::ToUInt32(this->siloBitCheck1Tb->Text);
					psIni->nSiloBitCheck[1] = Convert::ToUInt32(this->siloBitCheck2Tb->Text);
					psIni->nSiloBitCheck[2] = Convert::ToUInt32(this->siloBitCheck3Tb->Text);
					psIni->nSiloBitCheck[3] = Convert::ToUInt32(this->siloBitCheck4Tb->Text);
					psIni->nLaneTareI[0] = Convert::ToUInt32(this->laneTare1Tb->Text);
					psIni->nLaneTareI[1] = Convert::ToUInt32(this->laneTare2Tb->Text);
					psIni->nLaneTareI[2] = Convert::ToUInt32(this->laneTare3Tb->Text);
					psIni->nLaneTareI[3] = Convert::ToUInt32(this->laneTare4Tb->Text);
				}
				/*else
				{
					for(int i=0; i < 18;i++)
					{
						Cfg^ pCfg = bCfg[i];
						psIni->nBitWise[0]= 0;
					}
				}*/

				psIni->bPdmPlc = this->pdmPlcCB->Checked;
				psIni->bAutoAdd = this->autoAddCb->Checked;
				psIni->bSendTarget = this->sendTargetCB->Checked;
				psIni->bSendBitWise = this->bitWiseCB->Checked;
			}

			static bool trans(char *pcMat, String^ pMat)
			{
				if(pMat == nullptr) 
				{
					pcMat[0] = 0;
					return false;
				}
				else
				{
					int nLen = min(pMat->Length, 11-1);
					for(int i=0; i<nLen; i++) pcMat[i] = (char)pMat[i];
					pcMat[pMat->Length] = 0;
					return true;
				}
			}

	private: System::Void saveBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 saveCfg();
				 writeCfx(pAll);
				 saveBt->Visible = false;
				 if(bReboot)
					 closeBt->Visible = true;
			 }

	 private: System::Void closeBt_Click(System::Object^  sender, System::EventArgs^  e) 
			  {
				 this->Close();
				 if(MessageBox::Show("Program must restart to take effect the change, RESTART the Loadout?", "Configuration changed!"
					 , MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::DialogResult::Yes)
					Application::Restart();
				 else
					 MessageBox::Show("Config SAVED, Remember to restart the Loadout!!", "Configuration saved!"
					 ,MessageBoxButtons::OK, MessageBoxIcon::Warning);

			  }
private: System::Void showAllCB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(showAllCB->Checked)
			 {
					lCfg = gcnew Generic::List<Cfg^>();
					Cfg^ pCfg;
					pCfg = gcnew Cfg();

					for (int i=0; i < 12; i++)
					{
						pCfg = gcnew Cfg();
						pCfg->stLbl = gcnew String(psIni->asSilos[i].acMat);
						pCfg->stProduct = gcnew String(psIni->asSilos[i].acProduct);		//DC 4.0.2
						pCfg->bUsed = psIni->asSilos[i].bUsed;
						pCfg->nFlowRatePct1 = psIni->asSilos[i].nFlowRatePct1;
						pCfg->nFlowRatePct2 = psIni->asSilos[i].nFlowRatePct2;
						pCfg->nFlowRatePct3 = psIni->asSilos[i].nFlowRatePct3;
						pCfg->nFlowRatePct4 = psIni->asSilos[i].nFlowRatePct4;
						pCfg->nDelayPct = psIni->asSilos[i].nDelayPct;
						pCfg->nDelayTime = psIni->asSilos[i].nDelayTime;
						pCfg->nFlowRate1O = psIni->asSilos[i].nFlowRate1O;
						pCfg->nFlowRate2O = psIni->asSilos[i].nFlowRate2O;
						pCfg->nFlowRate3O = psIni->asSilos[i].nFlowRate3O;
						pCfg->nFlowRate4O = psIni->asSilos[i].nFlowRate4O;
						pCfg->nDoneI= psIni->asSilos[i].nDoneI;
						pCfg->nReadyO= psIni->asSilos[i].nReadyO;
						pCfg->nDropO= psIni->asSilos[i].nDropO;
						pCfg->nDoneO= psIni->asSilos[i].nDoneO;
						pCfg->nHoldO= psIni->asSilos[i].nHoldO;
						pCfg->nAddO= psIni->asSilos[i].nAddO;
						pCfg->nDropReadyI= psIni->asSilos[i].nDropReadyI;
						pCfg->nHoldI= psIni->asSilos[i].nHoldI;
						pCfg->fFall = psIni->asSilos[i].fFall;
						pCfg->nSiloNum = psIni->asSilos[i].nSiloNum;					//DC 4.0.3
						lCfg->Add(pCfg);
					}
					dataGridView1->Rows->Clear();
					cfgBindingSource->DataSource = lCfg;
				}
			 else
				 loadCfg();
		 }
private: System::Void CfgForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void editIOCB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bReboot = true;
			 exitBt->Visible = false;
			 if(editIOCB->Checked)
			 {
				 bUsedDataGridViewCheckBoxColumn->ReadOnly = false;
				 nSiloNum->ReadOnly = false;	//DC 4.0.3
				 stLblDataGridViewTextBoxColumn->ReadOnly = false;
				 stProduct->ReadOnly = false;							//DC 4.0.2
				 nFlowRate1ODataGridViewTextBoxColumn->ReadOnly = false;
				 nFlowRate2ODataGridViewTextBoxColumn->ReadOnly = false;
				 nFlowRate3ODataGridViewTextBoxColumn->ReadOnly = false;
				 nReadyODataGridViewTextBoxColumn->ReadOnly = false;
				 nDropODataGridViewTextBoxColumn->ReadOnly = false;
				 nHoldODataGridViewTextBoxColumn->ReadOnly = false;
				 nDoneODataGridViewTextBoxColumn->ReadOnly = false;
				 nDropReadyIDataGridViewTextBoxColumn->ReadOnly = false;
				 nHoldI->ReadOnly = false;
				 nDoneI->ReadOnly = false;
				 analogOutputGB->Enabled = true;
				 nBitWise->ReadOnly = false;
				 nBitCheckI->ReadOnly = false;
				 pdmPlcCB->Enabled = true;
				 sendTargetCB->Enabled = true;
				 bitWiseCB->Enabled = true;
				 sendTargetOTb->ReadOnly = false;
				 receivedTargetITb->ReadOnly = false;
				 keepAliveOTb->ReadOnly = false;
				 keepAliveITb->ReadOnly = false;
				 keepOnTimeTb->ReadOnly = false;
				 keepOffTimeTb->ReadOnly = false;
				 siloBit1Tb->ReadOnly = false;
				 siloBit2Tb->ReadOnly = false;
				 siloBit3Tb->ReadOnly = false;
				 siloBit4Tb->ReadOnly = false;
				 siloBitCheck1Tb->ReadOnly = false;
				 siloBitCheck2Tb->ReadOnly = false;
				 siloBitCheck3Tb->ReadOnly = false;
				 siloBitCheck4Tb->ReadOnly = false;
				 laneTare1Tb->ReadOnly = false;
				 laneTare2Tb->ReadOnly = false;
				 laneTare3Tb->ReadOnly = false;
				 laneTare4Tb->ReadOnly = false;
				 
				 bUsedDataGridViewCheckBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nSiloNum->DefaultCellStyle->BackColor = System::Drawing::Color::White;	//DC 4.0.3
				 stLblDataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 stProduct->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nFlowRate1ODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nFlowRate2ODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White; 
				 nFlowRate3ODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nReadyODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nDropODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White; 
				 nHoldODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nDoneODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White; 
				 nDropReadyIDataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nHoldI->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nDoneI->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nBitWise->DefaultCellStyle->BackColor = System::Drawing::Color::White;
				 nBitCheckI->DefaultCellStyle->BackColor = System::Drawing::Color::White;
			 }
			 else
			 {
				 bUsedDataGridViewCheckBoxColumn->ReadOnly = true;
				 nSiloNum->ReadOnly = true;	//DC 4.0.3
				 stLblDataGridViewTextBoxColumn->ReadOnly = true;
				 stProduct->ReadOnly = true;							//DC 4.0.2
				 nFlowRate1ODataGridViewTextBoxColumn->ReadOnly = true;
				 nFlowRate2ODataGridViewTextBoxColumn->ReadOnly = true;
				 nFlowRate3ODataGridViewTextBoxColumn->ReadOnly = true;
				 nReadyODataGridViewTextBoxColumn->ReadOnly = true;
				 nDropODataGridViewTextBoxColumn->ReadOnly = true;
				 nHoldODataGridViewTextBoxColumn->ReadOnly = true;
				 nDoneODataGridViewTextBoxColumn->ReadOnly = true;
				 nDropReadyIDataGridViewTextBoxColumn->ReadOnly = true;
				 nHoldI->ReadOnly = true;
				 nDoneI->ReadOnly = true;

				 bUsedDataGridViewCheckBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 nSiloNum->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;	//DC 4.0.3
				 stLblDataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 stProduct->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;						//DC 4.0.2
				 nFlowRate1ODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 nFlowRate2ODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray; 
				 nFlowRate3ODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 nReadyODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 nDropODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray; 
				 nHoldODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 nDoneODataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray; 
				 nDropReadyIDataGridViewTextBoxColumn->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 nHoldI->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
				 nDoneI->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
			 }
		 }
private: System::Void exitBt_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->Close();
		 }

private: System::Void dataGridView1_CellBeginEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellCancelEventArgs^  e)
		 {
			 bSave = true;
			 saveBt->Visible = true;
		 }
private: System::Void autoAddCb_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bSave = true;
			 saveBt->Visible = true;
		 }
private: System::Void sendTargetCB_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bSave = true;
			 saveBt->Visible = true;
		 }
private: System::Void bitWiseCB_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bSave = true;
			 saveBt->Visible = true;
		 }
private: System::Void pdmPlcCB_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bSave = true;
			 saveBt->Visible = true;
		 }
private: System::Void trkMaxLB_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void cartScaleMaxLB_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void keepAliveITb_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void siloCheckLb_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
