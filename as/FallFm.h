#pragma once
#include "stdafx.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
//using namespace System::Data;
using namespace System::Drawing;


namespace As 
{

	/// <summary>
	/// Summary for FallFm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FallFm : public System::Windows::Forms::Form
	{
	public:
		FallFm(double afManFall[], FALL *psFallIn, ADAPT *psAdaptIn, int nSilo, bool bTruckScale)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			nMax = bTruckScale ? 24 : 12;
			lFall = gcnew Generic::List<Fall^>();
			psFall = psFallIn;
			psAdapt = psAdaptIn;

			 for(int i=0; i<nMax; i++)
			 {
				pFall = gcnew Fall();
				pFall->nLoad = i+1;
				pFall->dMan = afManFall[i];
				pFall->dAuto = psFall->fFall / SAMPLE_NBR;
				pFall->dAdapt = psAdapt->fAdapt / SAMPLE_NBR;
				lFall->Add(pFall);
				psFall++;
				psAdapt++;
			 }
			psFall = psFallIn;
			psAdapt = psAdaptIn;

			 if(bTruckScale)
				this->dataGridView1->Size = System::Drawing::Size(363, 554);
			
			dataGridView1->DataSource = lFall;
			this->Text = "Free Fall Table, Silo " + nSilo.ToString();
		}		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FallFm()
		{
			if (components)
			{
				delete components;
			}
		} 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		int						nMax;
		Fall^					pFall;
		Generic::List<Fall^>^	lFall;
		FALL					*psFall;
		ADAPT					*psAdapt;


	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nLoadDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dManDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dAutoDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::Button^  quitBt;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::BindingSource^  fallBindingSource;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  saveBt;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FallFm::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->nLoadDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dManDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dAutoDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->fallBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->saveBt = (gcnew System::Windows::Forms::Button());
			this->quitBt = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->fallBindingSource))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AutoGenerateColumns = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->nLoadDataGridViewTextBoxColumn, 
				this->dManDataGridViewTextBoxColumn, this->dAutoDataGridViewTextBoxColumn, this->Column1});
			this->dataGridView1->DataSource = this->fallBindingSource;
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::Gainsboro;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle5;
			this->dataGridView1->Location = System::Drawing::Point(12, 13);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(4);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
			this->dataGridView1->Size = System::Drawing::Size(362, 290);
			this->dataGridView1->TabIndex = 0;
			// 
			// nLoadDataGridViewTextBoxColumn
			// 
			this->nLoadDataGridViewTextBoxColumn->DataPropertyName = L"nLoad";
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::ControlLight;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::ControlLight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::Color::Black;
			this->nLoadDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle1;
			this->nLoadDataGridViewTextBoxColumn->HeaderText = L"Load";
			this->nLoadDataGridViewTextBoxColumn->Name = L"nLoadDataGridViewTextBoxColumn";
			this->nLoadDataGridViewTextBoxColumn->ReadOnly = true;
			this->nLoadDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nLoadDataGridViewTextBoxColumn->Width = 60;
			// 
			// dManDataGridViewTextBoxColumn
			// 
			this->dManDataGridViewTextBoxColumn->DataPropertyName = L"dMan";
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::ControlLight;
			dataGridViewCellStyle2->Format = L"N3";
			this->dManDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle2;
			this->dManDataGridViewTextBoxColumn->HeaderText = L"Manual";
			this->dManDataGridViewTextBoxColumn->Name = L"dManDataGridViewTextBoxColumn";
			this->dManDataGridViewTextBoxColumn->ReadOnly = true;
			this->dManDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// dAutoDataGridViewTextBoxColumn
			// 
			this->dAutoDataGridViewTextBoxColumn->DataPropertyName = L"dAuto";
			dataGridViewCellStyle3->Format = L"N3";
			dataGridViewCellStyle3->NullValue = nullptr;
			this->dAutoDataGridViewTextBoxColumn->DefaultCellStyle = dataGridViewCellStyle3;
			this->dAutoDataGridViewTextBoxColumn->HeaderText = L"Auto";
			this->dAutoDataGridViewTextBoxColumn->Name = L"dAutoDataGridViewTextBoxColumn";
			this->dAutoDataGridViewTextBoxColumn->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// Column1
			// 
			this->Column1->DataPropertyName = L"dAdapt";
			dataGridViewCellStyle4->Format = L"n3";
			this->Column1->DefaultCellStyle = dataGridViewCellStyle4;
			this->Column1->HeaderText = L"Adaptive";
			this->Column1->Name = L"Column1";
			this->Column1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// fallBindingSource
			// 
			this->fallBindingSource->DataSource = As::Fall::typeid;
			// 
			// saveBt
			// 
			this->saveBt->BackColor = System::Drawing::Color::LightGreen;
			this->saveBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->saveBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->saveBt->Location = System::Drawing::Point(299, 603);
			this->saveBt->Name = L"saveBt";
			this->saveBt->Size = System::Drawing::Size(75, 26);
			this->saveBt->TabIndex = 1;
			this->saveBt->Text = L"Save";
			this->saveBt->UseVisualStyleBackColor = false;
			this->saveBt->Click += gcnew System::EventHandler(this, &FallFm::saveBt_Click);
			// 
			// quitBt
			// 
			this->quitBt->BackColor = System::Drawing::Color::Red;
			this->quitBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->quitBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->quitBt->Location = System::Drawing::Point(205, 603);
			this->quitBt->Name = L"quitBt";
			this->quitBt->Size = System::Drawing::Size(75, 26);
			this->quitBt->TabIndex = 2;
			this->quitBt->Text = L"Quit";
			this->quitBt->UseVisualStyleBackColor = false;
			this->quitBt->Click += gcnew System::EventHandler(this, &FallFm::quitBt_Click);
			// 
			// FallFm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(389, 645);
			this->ControlBox = false;
			this->Controls->Add(this->quitBt);
			this->Controls->Add(this->saveBt);
			this->Controls->Add(this->dataGridView1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"FallFm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;			//DC 3.1.5
			this->Text = L"Fall Tables";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->fallBindingSource))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

#pragma region CODE
	private: System::Void saveBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 for(int i=0; i<nMax; i++)
				 {
					 pFall = lFall[i];

					 if(pFall->dAuto != (psFall->fFall / SAMPLE_NBR))
					 {
						 psFall->fFall = pFall->dAuto * SAMPLE_NBR;

						 for(int j=0; j<SAMPLE_NBR; j++)
							psFall->afFall[j] = pFall->dAuto;
					 }
					 if(pFall->dAdapt != (psAdapt->fAdapt / SAMPLE_NBR))
					 {
						 psAdapt->fAdapt = pFall->dAdapt * SAMPLE_NBR;

						 for(int j=0; j<SAMPLE_NBR; j++)
							 psAdapt->afAdapt[j] = pFall->dAdapt;
					 }
					 psFall++;
					 psAdapt++;
				 }
				 this->Close();
			 }
			 //----------------------------------------------------------------
private: System::Void quitBt_Click(System::Object^  sender, System::EventArgs^  e)
		 {
				 this->Close();
		 }
 #pragma endregion

};
}
