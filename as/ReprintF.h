#pragma once
#include "StdAfx.h"
#include "Log.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
//using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;


namespace As 
{
	/// <summary>
	/// Summary for ReprintF
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class ReprintF : public System::Windows::Forms::Form
	{
	public:
		ReprintF(All^ pAllIn, CLog^ poLogIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pAll = pAllIn;
			poLog = poLogIn;

			this->dataGridOld->DefaultCellStyle->SelectionBackColor = this->dataGridOld->DefaultCellStyle->BackColor;	//DC 4.1.0
			this->dataGridOld->DefaultCellStyle->SelectionForeColor = this->dataGridOld->DefaultCellStyle->ForeColor;

			if(pAll->eAsType == A_REMOTE)
				printerCb4->Checked = true;
			else
				printerCb1->Checked = true;		//DC 4.0.2

			if(pAll->lOld->Count > 0)
			{
//DC 4.0.2				oldBindingSource->DataSource = pAll->lOld;
//DC 4.0.2				pJob = pAll->lOld[0];
				Job^     pJob;
				DateTime^ pDate; 
				DateTime^ pJobDate; 
				lSel = gcnew Generic::List<Job^>();

				pDate = dateTimePicker1->Value;

				for(int i=0; i<pAll->lOld->Count; i++)
				{
					pJob = pAll->lOld[i];
					pJobDate = DateTime::FromBinary(pJob->tTime);

					if(pDate->Date.CompareTo(pJobDate->Date) == 0)
					{
						lSel->Add(pJob);
					}
				}
				oldBindingSource->DataSource = nullptr;
				oldBindingSource->DataSource = lSel;
				if(lSel->Count > 0)
				{
					pJob = pAll->lOld[0];
				}
			}
			else
			{
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ReprintF()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		All^  pAll;
		CLog^ poLog;
		Job^  pJob;
		Generic::List<Job^>^ lSel;

		/// <summary>
		/// Required designer variable.
		/// </summary>
	private: System::Windows::Forms::Button^  printBt;
	private: System::Windows::Forms::Button^  cancelBt;
	private: System::Windows::Forms::DataGridView^  dataGridOld;
	private: System::Windows::Forms::BindingSource^  oldBindingSource;
	private: System::Windows::Forms::DateTimePicker^  dateTimePicker1;








	private: System::Windows::Forms::CheckBox^  printerCb3;
	private: System::Windows::Forms::CheckBox^  printerCb2;
	private: System::Windows::Forms::CheckBox^  printerCb4;
	private: System::Windows::Forms::CheckBox^  printerCb1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stLane;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stSilo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stMaterial;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nTicketDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  fLoad;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  eStatus;


























	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ReprintF::typeid));
			this->printBt = (gcnew System::Windows::Forms::Button());
			this->cancelBt = (gcnew System::Windows::Forms::Button());
			this->dataGridOld = (gcnew System::Windows::Forms::DataGridView());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->printerCb3 = (gcnew System::Windows::Forms::CheckBox());
			this->printerCb2 = (gcnew System::Windows::Forms::CheckBox());
			this->printerCb4 = (gcnew System::Windows::Forms::CheckBox());
			this->printerCb1 = (gcnew System::Windows::Forms::CheckBox());
			this->oldBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->stTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->stLane = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->stSilo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->stMaterial = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nTicketDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->fLoad = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->eStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridOld))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->oldBindingSource))->BeginInit();
			this->SuspendLayout();
			// 
			// printBt
			// 
			this->printBt->AutoSize = true;
			this->printBt->BackColor = System::Drawing::Color::PaleGreen;
			this->printBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->printBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->printBt->Location = System::Drawing::Point(682, 672);
			this->printBt->Margin = System::Windows::Forms::Padding(4);
			this->printBt->Name = L"printBt";
			this->printBt->Size = System::Drawing::Size(80, 39);
			this->printBt->TabIndex = 2;
			this->printBt->Text = L"PRINT";
			this->printBt->UseVisualStyleBackColor = false;
			this->printBt->Click += gcnew System::EventHandler(this, &ReprintF::printBt_Click);
			// 
			// cancelBt
			// 
			this->cancelBt->AutoSize = true;
			this->cancelBt->BackColor = System::Drawing::Color::Red;
			this->cancelBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cancelBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancelBt->Location = System::Drawing::Point(579, 672);
			this->cancelBt->Margin = System::Windows::Forms::Padding(4);
			this->cancelBt->Name = L"cancelBt";
			this->cancelBt->Size = System::Drawing::Size(80, 39);
			this->cancelBt->TabIndex = 3;
			this->cancelBt->Text = L"CLOSE";
			this->cancelBt->UseVisualStyleBackColor = false;
			this->cancelBt->Click += gcnew System::EventHandler(this, &ReprintF::cancelBt_Click);
			// 
			// dataGridOld
			// 
			this->dataGridOld->AllowUserToAddRows = false;
			this->dataGridOld->AllowUserToDeleteRows = false;
			this->dataGridOld->AutoGenerateColumns = false;
			this->dataGridOld->CausesValidation = false;
			this->dataGridOld->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridOld->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {this->stTime, this->Column1, 
				this->stLane, this->stSilo, this->stMaterial, this->nTicketDataGridViewTextBoxColumn, this->dataGridViewTextBoxColumn3, this->fLoad, 
				this->dataGridViewTextBoxColumn1, this->eStatus});
			this->dataGridOld->DataSource = this->oldBindingSource;
			this->dataGridOld->Location = System::Drawing::Point(28, 15);
			this->dataGridOld->Margin = System::Windows::Forms::Padding(4);
			this->dataGridOld->MultiSelect = false;
			this->dataGridOld->Name = L"dataGridOld";
			this->dataGridOld->ReadOnly = true;
			this->dataGridOld->RowHeadersVisible = false;
			this->dataGridOld->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGridOld->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridOld->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridOld->Size = System::Drawing::Size(906, 635);
			this->dataGridOld->TabIndex = 42;
			this->dataGridOld->CellMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &ReprintF::dataGridOld_RowHeaderMouseClick);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTimePicker1->Location = System::Drawing::Point(28, 672);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(158, 35);
			this->dateTimePicker1->TabIndex = 43;
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &ReprintF::dateTimePicker1_ValueChanged);
			// 
			// printerCb3
			// 
			this->printerCb3->AutoSize = true;
			this->printerCb3->BackColor = System::Drawing::Color::Gainsboro;
			this->printerCb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->printerCb3->Location = System::Drawing::Point(397, 684);
			this->printerCb3->Name = L"printerCb3";
			this->printerCb3->Size = System::Drawing::Size(41, 17);
			this->printerCb3->TabIndex = 49;
			this->printerCb3->Text = L"P3";
			this->printerCb3->UseVisualStyleBackColor = false;
			this->printerCb3->CheckedChanged += gcnew System::EventHandler(this, &ReprintF::printerCb3_CheckedChanged);
			// 
			// printerCb2
			// 
			this->printerCb2->AutoSize = true;
			this->printerCb2->BackColor = System::Drawing::Color::Gainsboro;
			this->printerCb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->printerCb2->Location = System::Drawing::Point(351, 684);
			this->printerCb2->Name = L"printerCb2";
			this->printerCb2->Size = System::Drawing::Size(41, 17);
			this->printerCb2->TabIndex = 48;
			this->printerCb2->Text = L"P2";
			this->printerCb2->UseVisualStyleBackColor = false;
			this->printerCb2->CheckedChanged += gcnew System::EventHandler(this, &ReprintF::printerCb2_CheckedChanged);
			// 
			// printerCb4
			// 
			this->printerCb4->AutoSize = true;
			this->printerCb4->BackColor = System::Drawing::Color::Gainsboro;
			this->printerCb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->printerCb4->Location = System::Drawing::Point(441, 684);
			this->printerCb4->Name = L"printerCb4";
			this->printerCb4->Size = System::Drawing::Size(41, 17);
			this->printerCb4->TabIndex = 50;
			this->printerCb4->Text = L"P4";
			this->printerCb4->UseVisualStyleBackColor = false;
			this->printerCb4->CheckedChanged += gcnew System::EventHandler(this, &ReprintF::printerCb4_CheckedChanged);
			// 
			// printerCb1
			// 
			this->printerCb1->AutoSize = true;
			this->printerCb1->BackColor = System::Drawing::Color::Gainsboro;
			this->printerCb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->printerCb1->Location = System::Drawing::Point(305, 684);
			this->printerCb1->Name = L"printerCb1";
			this->printerCb1->Size = System::Drawing::Size(41, 17);
			this->printerCb1->TabIndex = 51;
			this->printerCb1->Text = L"P1";
			this->printerCb1->UseVisualStyleBackColor = false;
			this->printerCb1->CheckedChanged += gcnew System::EventHandler(this, &ReprintF::printerCb1_CheckedChanged);
			// 
			// oldBindingSource
			// 
			this->oldBindingSource->DataSource = As::Job::typeid;
			// 
			// stTime
			// 
			this->stTime->DataPropertyName = L"stTime";
			this->stTime->HeaderText = L"Time Sent ";
			this->stTime->Name = L"stTime";
			this->stTime->ReadOnly = true;
			// 
			// Column1
			// 
			this->Column1->DataPropertyName = L"nPlant";
			this->Column1->HeaderText = L"Plant";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 60;
			// 
			// stLane
			// 
			this->stLane->DataPropertyName = L"stLane";
			this->stLane->HeaderText = L"Lane";
			this->stLane->Name = L"stLane";
			this->stLane->ReadOnly = true;
			this->stLane->Width = 50;
			// 
			// stSilo
			// 
			this->stSilo->DataPropertyName = L"stSilo";
			this->stSilo->HeaderText = L"Silo";
			this->stSilo->Name = L"stSilo";
			this->stSilo->ReadOnly = true;
			this->stSilo->Width = 50;
			// 
			// stMaterial
			// 
			this->stMaterial->DataPropertyName = L"stMaterial";
			this->stMaterial->HeaderText = L"Material";
			this->stMaterial->Name = L"stMaterial";
			this->stMaterial->ReadOnly = true;
			// 
			// nTicketDataGridViewTextBoxColumn
			// 
			this->nTicketDataGridViewTextBoxColumn->DataPropertyName = L"nTicket";
			this->nTicketDataGridViewTextBoxColumn->HeaderText = L"Ticket #";
			this->nTicketDataGridViewTextBoxColumn->Name = L"nTicketDataGridViewTextBoxColumn";
			this->nTicketDataGridViewTextBoxColumn->ReadOnly = true;
			this->nTicketDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nTicketDataGridViewTextBoxColumn->Width = 90;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->DataPropertyName = L"stCustomer";
			this->dataGridViewTextBoxColumn3->HeaderText = L"Customer";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			this->dataGridViewTextBoxColumn3->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewTextBoxColumn3->Width = 260;
			// 
			// fLoad
			// 
			this->fLoad->DataPropertyName = L"fLoad";
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
			dataGridViewCellStyle1->Format = L"N2";
			this->fLoad->DefaultCellStyle = dataGridViewCellStyle1;
			this->fLoad->HeaderText = L"Load";
			this->fLoad->Name = L"fLoad";
			this->fLoad->ReadOnly = true;
			this->fLoad->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->fLoad->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->fLoad->Width = 70;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->DataPropertyName = L"nSilo";
			this->dataGridViewTextBoxColumn1->HeaderText = L"Matrix";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			this->dataGridViewTextBoxColumn1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewTextBoxColumn1->Width = 50;
			// 
			// eStatus
			// 
			this->eStatus->DataPropertyName = L"stStatus";
			this->eStatus->HeaderText = L"Status";
			this->eStatus->Name = L"eStatus";
			this->eStatus->ReadOnly = true;
			this->eStatus->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->eStatus->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->eStatus->Width = 80;
			// 
			// ReprintF
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(947, 726);
			this->ControlBox = false;
			this->Controls->Add(this->printerCb1);
			this->Controls->Add(this->printerCb4);
			this->Controls->Add(this->printerCb3);
			this->Controls->Add(this->printerCb2);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->dataGridOld);
			this->Controls->Add(this->cancelBt);
			this->Controls->Add(this->printBt);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"ReprintF";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Reprint Ticket";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridOld))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->oldBindingSource))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		///////////////////////////////////////////////////////////////////////
private: System::Void dataGridOld_RowHeaderMouseClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e) 
		 {
			 this->dataGridOld->DefaultCellStyle->SelectionBackColor = System::Drawing::SystemColors::Highlight;	//DC 4.1.0
			 this->dataGridOld->DefaultCellStyle->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			 if(pAll->eAsType == A_REMOTE)	//DC 4.1.0
			 {
				 DataGridViewRow^ row = dataGridOld->SelectedRows[0];
				 pJob = (Job^)row->DataBoundItem;

				 pAll->pJob = pJob;
				 int k = 0;	
				 Cmd^ pCmd = gcnew Cmd();
				 pCmd = gcnew Cmd();
				 pCmd->cId = CL_SJOB;
				 pAll->qCmd->Enqueue(pCmd);

				pAll->cWaitT = 1;

				while(pAll->cWaitT > 0 && k++ < 5)
				Thread::Sleep(100);

				/*int i = 0;
				pCmd->cId = CL_KEY;
				pCmd->nKey = K_SJOB4;
				pAll->qCmd->Enqueue(pCmd);

				pAll->cWaitT = 1;

				while(pAll->cWaitT > 0 && i++ < 5)
				Thread::Sleep(100);*/
			 }
			 else
			 {
				 DataGridViewRow^ row = dataGridOld->SelectedRows[0];
				 pJob = (Job^)row->DataBoundItem;
			 }
		 }

			//-----------------------------------------------------------------
	private: System::Void printBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if(pAll->eAsType == A_REMOTE)	//DC 4.1.0
				 {
					int i = 0;
					Cmd^ pCmd = gcnew Cmd();
					pCmd->cId = CL_KEY;
					pCmd->nKey = K_RPRINT4;
					pAll->qCmd->Enqueue(pCmd);

					pAll->cWaitT = 1;

					while(pAll->cWaitT > 0 && i++ < 5)
					Thread::Sleep(100);
				}
				else
				{
					LOG_REC sLog;
					int nPrinter;	
					 nPrinter = 1;
					 if(printerCb2->Checked)
						 nPrinter = 2;
					 else if(printerCb3->Checked)
						 nPrinter = 3;
					 else if(printerCb4->Checked)
						 nPrinter = 4;
		
					 if(pJob == nullptr && lSel->Count > 0)	//DC 4.0.2
					 {
						pJob = pAll->lOld[0];
					 }
					 if(pJob == nullptr)					//DC 4.0.2
						 return;

					 if(poLog->findTicket(pJob->nTicket, &sLog) > 0)
					 {
						 poLog->calcTicket(&sLog);					 
						 poLog->printTicket(&sLog, nPrinter, true);					 
	//DC 4.0.2					 this->Close();
					 }
				 }
			 }

			 //----------------------------------------------------------------
	private: System::Void cancelBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->Close();
			 }

			 //----------------------------------------------------------------
private: System::Void dateTimePicker1_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Job^     pJob;
			DateTime^ pDate; 
			DateTime^ pJobDate; 
			lSel = gcnew Generic::List<Job^>();

			pDate = dateTimePicker1->Value;

			for(int i=0; i<pAll->lOld->Count; i++)
			{
				pJob = pAll->lOld[i];
				pJobDate = DateTime::FromBinary(pJob->tTime);

				if(pDate->Date.CompareTo(pJobDate->Date) == 0)
				{
					lSel->Add(pJob);
				}
			}
			oldBindingSource->DataSource = nullptr;
			oldBindingSource->DataSource = lSel;
			if(lSel->Count > 0)
			{
				pJob = pAll->lOld[0];
			}
		 }

private: System::Void printerCb1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(printerCb1->Checked == true)
			 {
				 printerCb1->Checked = true;
				 printerCb2->Checked = false;
				 printerCb3->Checked = false;
				 printerCb4->Checked = false;
			 }
		 }
private: System::Void printerCb2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(printerCb2->Checked == true)
			 {
				 printerCb2->Checked = true;
				 printerCb1->Checked = false;
				 printerCb3->Checked = false;
				 printerCb4->Checked = false;
			 }
		 }
private: System::Void printerCb3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(printerCb3->Checked == true)
			 {
				 printerCb3->Checked = true;
				 printerCb1->Checked = false;
				 printerCb2->Checked = false;
				 printerCb4->Checked = false;
			 }
		 }
private: System::Void printerCb4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(printerCb4->Checked == true)
			 {
				 printerCb4->Checked = true;
				 printerCb1->Checked = false;
				 printerCb2->Checked = false;
				 printerCb3->Checked = false;
			 }
		 }
};
}
