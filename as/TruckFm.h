#pragma once
#include "StdAfx.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::Serialization::Formatters::Binary;


namespace As 
{
	
	//----------------------------------------------------------------------------
	int CompareTruck(Truck^ x, Truck^ y)
	{
		return String::Compare(x->stName, y->stName);
	}

	/// <summary>
	/// Summary for TruckFm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class TruckFm : public System::Windows::Forms::Form
	{
	public:
		TruckFm(All^ pAllIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pAll = pAllIn;
			truckBindingSource->DataSource = pAll->lTruck;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TruckFm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	protected:
	private: System::Windows::Forms::BindingSource^  truckBindingSource;
	private: System::Windows::Forms::BindingNavigator^  bindingNavigatorTruck;
	private: System::Windows::Forms::ToolStripButton^  bindingNavigatorAddNewItem;
	private: System::Windows::Forms::ToolStripLabel^  bindingNavigatorCountItem;
	private: System::Windows::Forms::ToolStripButton^  bindingNavigatorDeleteItem;
	private: System::Windows::Forms::ToolStripButton^  bindingNavigatorMoveFirstItem;
	private: System::Windows::Forms::ToolStripButton^  bindingNavigatorMovePreviousItem;
	private: System::Windows::Forms::ToolStripSeparator^  bindingNavigatorSeparator;
	private: System::Windows::Forms::ToolStripTextBox^  bindingNavigatorPositionItem;
	private: System::Windows::Forms::ToolStripSeparator^  bindingNavigatorSeparator1;
	private: System::Windows::Forms::ToolStripButton^  bindingNavigatorMoveNextItem;
	private: System::Windows::Forms::ToolStripButton^  bindingNavigatorMoveLastItem;
	private: System::Windows::Forms::ToolStripSeparator^  bindingNavigatorSeparator2;
	private: System::Windows::Forms::Button^  saveBt;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  cancelBt;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  stNameDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nRateDataGridViewTextBoxColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nCapacityDataGridViewTextBoxColumn;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		All^ pAll;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TruckFm::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->truckBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->bindingNavigatorTruck = (gcnew System::Windows::Forms::BindingNavigator(this->components));
			this->bindingNavigatorAddNewItem = (gcnew System::Windows::Forms::ToolStripButton());
			this->bindingNavigatorCountItem = (gcnew System::Windows::Forms::ToolStripLabel());
			this->bindingNavigatorDeleteItem = (gcnew System::Windows::Forms::ToolStripButton());
			this->bindingNavigatorMoveFirstItem = (gcnew System::Windows::Forms::ToolStripButton());
			this->bindingNavigatorMovePreviousItem = (gcnew System::Windows::Forms::ToolStripButton());
			this->bindingNavigatorSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->bindingNavigatorPositionItem = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->bindingNavigatorSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->bindingNavigatorMoveNextItem = (gcnew System::Windows::Forms::ToolStripButton());
			this->bindingNavigatorMoveLastItem = (gcnew System::Windows::Forms::ToolStripButton());
			this->bindingNavigatorSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveBt = (gcnew System::Windows::Forms::Button());
			this->cancelBt = (gcnew System::Windows::Forms::Button());
			this->stNameDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nRateDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nCapacityDataGridViewTextBoxColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckBindingSource))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingNavigatorTruck))->BeginInit();
			this->bindingNavigatorTruck->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoGenerateColumns = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->stNameDataGridViewTextBoxColumn, 
				this->nRateDataGridViewTextBoxColumn, this->nCapacityDataGridViewTextBoxColumn});
			this->dataGridView1->DataSource = this->truckBindingSource;
			this->dataGridView1->Location = System::Drawing::Point(16, 53);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(4);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(366, 455);
			this->dataGridView1->TabIndex = 0;
			this->dataGridView1->ColumnHeaderMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &TruckFm::dataGridViewTruck_ColumnHeaderMouseClick);
			// 
			// truckBindingSource
			// 
			this->truckBindingSource->DataSource = As::Truck::typeid;
			// 
			// bindingNavigatorTruck
			// 
			this->bindingNavigatorTruck->AddNewItem = this->bindingNavigatorAddNewItem;
			this->bindingNavigatorTruck->BindingSource = this->truckBindingSource;
			this->bindingNavigatorTruck->CountItem = this->bindingNavigatorCountItem;
			this->bindingNavigatorTruck->DeleteItem = this->bindingNavigatorDeleteItem;
			this->bindingNavigatorTruck->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->bindingNavigatorTruck->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {this->bindingNavigatorMoveFirstItem, 
				this->bindingNavigatorMovePreviousItem, this->bindingNavigatorSeparator, this->bindingNavigatorPositionItem, this->bindingNavigatorCountItem, 
				this->bindingNavigatorSeparator1, this->bindingNavigatorMoveNextItem, this->bindingNavigatorMoveLastItem, this->bindingNavigatorSeparator2, 
				this->bindingNavigatorAddNewItem, this->bindingNavigatorDeleteItem});
			this->bindingNavigatorTruck->Location = System::Drawing::Point(0, 0);
			this->bindingNavigatorTruck->MoveFirstItem = this->bindingNavigatorMoveFirstItem;
			this->bindingNavigatorTruck->MoveLastItem = this->bindingNavigatorMoveLastItem;
			this->bindingNavigatorTruck->MoveNextItem = this->bindingNavigatorMoveNextItem;
			this->bindingNavigatorTruck->MovePreviousItem = this->bindingNavigatorMovePreviousItem;
			this->bindingNavigatorTruck->Name = L"bindingNavigatorTruck";
			this->bindingNavigatorTruck->PositionItem = this->bindingNavigatorPositionItem;
			this->bindingNavigatorTruck->Size = System::Drawing::Size(402, 25);
			this->bindingNavigatorTruck->TabIndex = 1;
			this->bindingNavigatorTruck->Text = L"bindingNavigator1";
			// 
			// bindingNavigatorAddNewItem
			// 
			this->bindingNavigatorAddNewItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->bindingNavigatorAddNewItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"bindingNavigatorAddNewItem.Image")));
			this->bindingNavigatorAddNewItem->Name = L"bindingNavigatorAddNewItem";
			this->bindingNavigatorAddNewItem->RightToLeftAutoMirrorImage = true;
			this->bindingNavigatorAddNewItem->Size = System::Drawing::Size(23, 22);
			this->bindingNavigatorAddNewItem->Text = L"Add new";
			// 
			// bindingNavigatorCountItem
			// 
			this->bindingNavigatorCountItem->Name = L"bindingNavigatorCountItem";
			this->bindingNavigatorCountItem->Size = System::Drawing::Size(53, 22);
			this->bindingNavigatorCountItem->Text = L"of {0}";
			this->bindingNavigatorCountItem->ToolTipText = L"Total number of items";
			// 
			// bindingNavigatorDeleteItem
			// 
			this->bindingNavigatorDeleteItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->bindingNavigatorDeleteItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"bindingNavigatorDeleteItem.Image")));
			this->bindingNavigatorDeleteItem->Name = L"bindingNavigatorDeleteItem";
			this->bindingNavigatorDeleteItem->RightToLeftAutoMirrorImage = true;
			this->bindingNavigatorDeleteItem->Size = System::Drawing::Size(23, 22);
			this->bindingNavigatorDeleteItem->Text = L"Delete";
			// 
			// bindingNavigatorMoveFirstItem
			// 
			this->bindingNavigatorMoveFirstItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->bindingNavigatorMoveFirstItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"bindingNavigatorMoveFirstItem.Image")));
			this->bindingNavigatorMoveFirstItem->Name = L"bindingNavigatorMoveFirstItem";
			this->bindingNavigatorMoveFirstItem->RightToLeftAutoMirrorImage = true;
			this->bindingNavigatorMoveFirstItem->Size = System::Drawing::Size(23, 22);
			this->bindingNavigatorMoveFirstItem->Text = L"Move first";
			// 
			// bindingNavigatorMovePreviousItem
			// 
			this->bindingNavigatorMovePreviousItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->bindingNavigatorMovePreviousItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"bindingNavigatorMovePreviousItem.Image")));
			this->bindingNavigatorMovePreviousItem->Name = L"bindingNavigatorMovePreviousItem";
			this->bindingNavigatorMovePreviousItem->RightToLeftAutoMirrorImage = true;
			this->bindingNavigatorMovePreviousItem->Size = System::Drawing::Size(23, 22);
			this->bindingNavigatorMovePreviousItem->Text = L"Move previous";
			// 
			// bindingNavigatorSeparator
			// 
			this->bindingNavigatorSeparator->Name = L"bindingNavigatorSeparator";
			this->bindingNavigatorSeparator->Size = System::Drawing::Size(6, 25);
			// 
			// bindingNavigatorPositionItem
			// 
			this->bindingNavigatorPositionItem->AccessibleName = L"Position";
			this->bindingNavigatorPositionItem->AutoSize = false;
			this->bindingNavigatorPositionItem->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->bindingNavigatorPositionItem->Name = L"bindingNavigatorPositionItem";
			this->bindingNavigatorPositionItem->Size = System::Drawing::Size(65, 24);
			this->bindingNavigatorPositionItem->Text = L"0";
			this->bindingNavigatorPositionItem->ToolTipText = L"Current position";
			// 
			// bindingNavigatorSeparator1
			// 
			this->bindingNavigatorSeparator1->Name = L"bindingNavigatorSeparator1";
			this->bindingNavigatorSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// bindingNavigatorMoveNextItem
			// 
			this->bindingNavigatorMoveNextItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->bindingNavigatorMoveNextItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"bindingNavigatorMoveNextItem.Image")));
			this->bindingNavigatorMoveNextItem->Name = L"bindingNavigatorMoveNextItem";
			this->bindingNavigatorMoveNextItem->RightToLeftAutoMirrorImage = true;
			this->bindingNavigatorMoveNextItem->Size = System::Drawing::Size(23, 22);
			this->bindingNavigatorMoveNextItem->Text = L"Move next";
			// 
			// bindingNavigatorMoveLastItem
			// 
			this->bindingNavigatorMoveLastItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->bindingNavigatorMoveLastItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"bindingNavigatorMoveLastItem.Image")));
			this->bindingNavigatorMoveLastItem->Name = L"bindingNavigatorMoveLastItem";
			this->bindingNavigatorMoveLastItem->RightToLeftAutoMirrorImage = true;
			this->bindingNavigatorMoveLastItem->Size = System::Drawing::Size(23, 22);
			this->bindingNavigatorMoveLastItem->Text = L"Move last";
			// 
			// bindingNavigatorSeparator2
			// 
			this->bindingNavigatorSeparator2->Name = L"bindingNavigatorSeparator2";
			this->bindingNavigatorSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// saveBt
			// 
			this->saveBt->BackColor = System::Drawing::Color::PaleGreen;
			this->saveBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->saveBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->saveBt->Location = System::Drawing::Point(302, 534);
			this->saveBt->Margin = System::Windows::Forms::Padding(4);
			this->saveBt->Name = L"saveBt";
			this->saveBt->Size = System::Drawing::Size(80, 40);
			this->saveBt->TabIndex = 2;
			this->saveBt->Text = L"SAVE";
			this->saveBt->UseVisualStyleBackColor = false;
			this->saveBt->Click += gcnew System::EventHandler(this, &TruckFm::saveBt_Click);
			// 
			// cancelBt
			// 
			this->cancelBt->BackColor = System::Drawing::Color::Red;
			this->cancelBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cancelBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancelBt->Location = System::Drawing::Point(206, 534);
			this->cancelBt->Margin = System::Windows::Forms::Padding(4);
			this->cancelBt->Name = L"cancelBt";
			this->cancelBt->Size = System::Drawing::Size(80, 40);
			this->cancelBt->TabIndex = 3;
			this->cancelBt->Text = L"CANCEL";
			this->cancelBt->UseVisualStyleBackColor = false;
			this->cancelBt->Click += gcnew System::EventHandler(this, &TruckFm::cancelBt_Click);
			// 
			// stNameDataGridViewTextBoxColumn
			// 
			this->stNameDataGridViewTextBoxColumn->DataPropertyName = L"stName";
			this->stNameDataGridViewTextBoxColumn->HeaderText = L"Truck Id";
			this->stNameDataGridViewTextBoxColumn->Name = L"stNameDataGridViewTextBoxColumn";
			// 
			// nRateDataGridViewTextBoxColumn
			// 
			this->nRateDataGridViewTextBoxColumn->DataPropertyName = L"nRate";
			this->nRateDataGridViewTextBoxColumn->HeaderText = L"Rate";
			this->nRateDataGridViewTextBoxColumn->Name = L"nRateDataGridViewTextBoxColumn";
			// 
			// nCapacityDataGridViewTextBoxColumn
			// 
			this->nCapacityDataGridViewTextBoxColumn->DataPropertyName = L"nCapacity";
			this->nCapacityDataGridViewTextBoxColumn->HeaderText = L"Capacity";
			this->nCapacityDataGridViewTextBoxColumn->Name = L"nCapacityDataGridViewTextBoxColumn";
			// 
			// TruckFm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(402, 599);
			this->ControlBox = false;
			this->Controls->Add(this->cancelBt);
			this->Controls->Add(this->saveBt);
			this->Controls->Add(this->bindingNavigatorTruck);
			this->Controls->Add(this->dataGridView1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"TruckFm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;			//DC 3.1.5
			this->Text = L"Truck List";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->truckBindingSource))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingNavigatorTruck))->EndInit();
			this->bindingNavigatorTruck->ResumeLayout(false);
			this->bindingNavigatorTruck->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//---------------------------------------------------------------------
	private: System::Void saveBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 FileStream^ fs = gcnew FileStream( pAll->pAcPath + gcnew String("as.truck"), FileMode::Create );		//DC 3.2.3

				 // Construct a BinaryFormatter and use it to serialize the data to the stream.
				 BinaryFormatter^ formatter = gcnew BinaryFormatter;
				 try
				 {
					 formatter->Serialize( fs, pAll->lTruck );
				 }
				 catch ( SerializationException^ e ) 
				 {
					 Console::WriteLine( "Failed to serialize. Reason: {0}", e->Message );
					 throw;
				 }
				 finally
				 {
					 fs->Close();
				 }
				 this->Close();
			 }
		 //-------------------------------------------------------------------------
private: System::Void cancelBt_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				 this->Close();
		 }

		 //-------------------------------------------------------------------------
	private: System::Void dataGridViewTruck_ColumnHeaderMouseClick(System::Object^  sender
				 , System::Windows::Forms::DataGridViewCellMouseEventArgs^  e) 
		{
			 pAll->lTruck->Sort(gcnew Comparison<Truck^>(CompareTruck));

			 truckBindingSource->DataSource = nullptr;
			 truckBindingSource->DataSource = pAll->lTruck;

		 }

};
///////////////////////////////////////////////////////////////////////////////
}
