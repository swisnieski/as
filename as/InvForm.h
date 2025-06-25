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
	/// Summary for InvForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class InvForm : public System::Windows::Forms::Form
	{
	public:
		InvForm(INI *psIniIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			psIni = psIniIn;
			psInv = &psIni->sInv;

			if(psIni->bBotScale)
			{
				inv1->Text = psInv->fInv1.ToString("F01");
				inv2->Text = psInv->fInv2.ToString("F01");
				inv3->Text = psInv->fInv3.ToString("F01");

				inv4->Text = psInv->fInv4.ToString("F01");
				inv5->Text = psInv->fInv5.ToString("F01");
				inv6->Text = psInv->fInv6.ToString("F01");

				inv7->Text = psInv->fInv7.ToString("F01");
				inv8->Text = psInv->fInv8.ToString("F01");
				inv9->Text = psInv->fInv9.ToString("F01");

				inv10->Text = psInv->fInv10.ToString("F01");
				inv11->Text = psInv->fInv11.ToString("F01");
				inv12->Text = psInv->fInv12.ToString("F01");
				
				groupBox2->Visible = psIni->nNumLanes > 1;
				groupBox3->Visible = psIni->nNumLanes > 2;
				groupBox4->Visible = psIni->nNumLanes > 3;
			}
			else
			{
				inv1->Text = psInv->fInv1.ToString("F01");
				inv4->Text = psInv->fInv2.ToString("F01");
				inv7->Text = psInv->fInv3.ToString("F01");
				inv10->Text = psInv->fInv3.ToString("F01");

				silo4->Text = "Silo 2";
				silo7->Text = "Silo 3";
				silo10->Text = "Silo 4";

				inv2->Visible = false;
				inv3->Visible = false;
				silo2->Visible = false;
				silo3->Visible = false;

				inv5->Visible = false;
				inv6->Visible = false;
				silo5->Visible = false;
				silo6->Visible = false;

				inv8->Visible = false;
				inv9->Visible = false;
				silo8->Visible = false;
				silo9->Visible = false;

				//DC 3.3.0
				inv11->Visible = false;
				inv12->Visible = false;
				silo11->Visible = false;
				silo12->Visible = false;
			}

			if(psIni->bRevPlant)
			{
				 this->groupBox1->Location = System::Drawing::Point(695, 12);
				 this->groupBox2->Location = System::Drawing::Point(467, 12);
				 this->groupBox3->Location = System::Drawing::Point(239, 12);
				 this->groupBox4->Location = System::Drawing::Point(11, 12);

				  this->inv1->Location = System::Drawing::Point(149, 54);
				  this->inv3->Location = System::Drawing::Point(11, 54);
				 this->silo1->Location = System::Drawing::Point(152, 33);
				 this->silo3->Location = System::Drawing::Point(12, 33);

				  this->inv4->Location = System::Drawing::Point(149, 54);
				  this->inv6->Location = System::Drawing::Point(11, 54);
				 this->silo4->Location = System::Drawing::Point(152, 33);
				 this->silo6->Location = System::Drawing::Point(12, 33);

				  this->inv7->Location = System::Drawing::Point(149, 54);
				  this->inv9->Location = System::Drawing::Point(11, 54);
				 this->silo7->Location = System::Drawing::Point(152, 33);
				 this->silo9->Location = System::Drawing::Point(12, 33);
				 //3.3.0
				  this->inv10->Location = System::Drawing::Point(149, 54);
				  this->inv12->Location = System::Drawing::Point(11, 54);
				 this->silo10->Location = System::Drawing::Point(152, 33);
				 this->silo12->Location = System::Drawing::Point(12, 33);
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~InvForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		INI *psIni;
		INV *psInv;

	private: System::Windows::Forms::Label^  silo1;
	private: System::Windows::Forms::Label^  silo2;
	private: System::Windows::Forms::Label^  silo3;
	protected: 
	private: System::Windows::Forms::TextBox^  inv1;
	private: System::Windows::Forms::TextBox^  inv4;
	private: System::Windows::Forms::TextBox^  inv7;
	private: System::Windows::Forms::Button^  invSaveBt;
	private: System::Windows::Forms::Button^  invCancelBt;
	private: System::Windows::Forms::TextBox^  inv8;
	private: System::Windows::Forms::TextBox^  inv5;
	private: System::Windows::Forms::TextBox^  inv2;
	private: System::Windows::Forms::TextBox^  inv9;
	private: System::Windows::Forms::TextBox^  inv6;
	private: System::Windows::Forms::TextBox^  inv3;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  silo4;
	private: System::Windows::Forms::Label^  silo6;
	private: System::Windows::Forms::Label^  silo5;
	private: System::Windows::Forms::Label^  silo7;
	private: System::Windows::Forms::Label^  silo9;
	private: System::Windows::Forms::Label^  silo8;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  silo10;
	private: System::Windows::Forms::Label^  silo12;
	private: System::Windows::Forms::Label^  silo11;
	private: System::Windows::Forms::TextBox^  inv12;
	private: System::Windows::Forms::TextBox^  inv10;
	private: System::Windows::Forms::TextBox^  inv11;

			 /// <summary>
			 /// Required designer variable.
			 /// </summary>
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(InvForm::typeid));
				 this->silo1 = (gcnew System::Windows::Forms::Label());
				 this->silo2 = (gcnew System::Windows::Forms::Label());
				 this->silo3 = (gcnew System::Windows::Forms::Label());
				 this->inv1 = (gcnew System::Windows::Forms::TextBox());
				 this->inv4 = (gcnew System::Windows::Forms::TextBox());
				 this->inv7 = (gcnew System::Windows::Forms::TextBox());
				 this->invSaveBt = (gcnew System::Windows::Forms::Button());
				 this->invCancelBt = (gcnew System::Windows::Forms::Button());
				 this->inv8 = (gcnew System::Windows::Forms::TextBox());
				 this->inv5 = (gcnew System::Windows::Forms::TextBox());
				 this->inv2 = (gcnew System::Windows::Forms::TextBox());
				 this->inv9 = (gcnew System::Windows::Forms::TextBox());
				 this->inv6 = (gcnew System::Windows::Forms::TextBox());
				 this->inv3 = (gcnew System::Windows::Forms::TextBox());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->silo4 = (gcnew System::Windows::Forms::Label());
				 this->silo6 = (gcnew System::Windows::Forms::Label());
				 this->silo5 = (gcnew System::Windows::Forms::Label());
				 this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
				 this->silo7 = (gcnew System::Windows::Forms::Label());
				 this->silo9 = (gcnew System::Windows::Forms::Label());
				 this->silo8 = (gcnew System::Windows::Forms::Label());
				 this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
				 this->silo10 = (gcnew System::Windows::Forms::Label());
				 this->silo12 = (gcnew System::Windows::Forms::Label());
				 this->silo11 = (gcnew System::Windows::Forms::Label());
				 this->inv12 = (gcnew System::Windows::Forms::TextBox());
				 this->inv10 = (gcnew System::Windows::Forms::TextBox());
				 this->inv11 = (gcnew System::Windows::Forms::TextBox());
				 this->groupBox1->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 this->groupBox3->SuspendLayout();
				 this->groupBox4->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // silo1
				 // 
				 this->silo1->AutoSize = true;
				 this->silo1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo1->ForeColor = System::Drawing::Color::Blue;
				 this->silo1->Location = System::Drawing::Point(12, 33);
				 this->silo1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo1->Name = L"silo1";
				 this->silo1->Size = System::Drawing::Size(49, 17);
				 this->silo1->TabIndex = 0;
				 this->silo1->Text = L"Silo 1";
				 // 
				 // silo2
				 // 
				 this->silo2->AutoSize = true;
				 this->silo2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo2->ForeColor = System::Drawing::Color::Blue;
				 this->silo2->Location = System::Drawing::Point(82, 33);
				 this->silo2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo2->Name = L"silo2";
				 this->silo2->Size = System::Drawing::Size(49, 17);
				 this->silo2->TabIndex = 1;
				 this->silo2->Text = L"Silo 2";
				 // 
				 // silo3
				 // 
				 this->silo3->AutoSize = true;
				 this->silo3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo3->ForeColor = System::Drawing::Color::Blue;
				 this->silo3->Location = System::Drawing::Point(152, 33);
				 this->silo3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo3->Name = L"silo3";
				 this->silo3->Size = System::Drawing::Size(49, 17);
				 this->silo3->TabIndex = 2;
				 this->silo3->Text = L"Silo 3";
				 // 
				 // inv1
				 // 
				 this->inv1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv1->Location = System::Drawing::Point(11, 54);
				 this->inv1->Margin = System::Windows::Forms::Padding(4);
				 this->inv1->MaxLength = 6;
				 this->inv1->Name = L"inv1";
				 this->inv1->Size = System::Drawing::Size(57, 26);
				 this->inv1->TabIndex = 3;
				 this->inv1->Text = L"000.00";
				 // 
				 // inv4
				 // 
				 this->inv4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv4->Location = System::Drawing::Point(11, 54);
				 this->inv4->Margin = System::Windows::Forms::Padding(4);
				 this->inv4->MaxLength = 6;
				 this->inv4->Name = L"inv4";
				 this->inv4->Size = System::Drawing::Size(57, 26);
				 this->inv4->TabIndex = 4;
				 this->inv4->Text = L"000.00";
				 // 
				 // inv7
				 // 
				 this->inv7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv7->Location = System::Drawing::Point(11, 54);
				 this->inv7->Margin = System::Windows::Forms::Padding(4);
				 this->inv7->MaxLength = 6;
				 this->inv7->Name = L"inv7";
				 this->inv7->Size = System::Drawing::Size(57, 26);
				 this->inv7->TabIndex = 5;
				 this->inv7->Text = L"000.00";
				 // 
				 // invSaveBt
				 // 
				 this->invSaveBt->BackColor = System::Drawing::Color::PaleGreen;
				 this->invSaveBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->invSaveBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->invSaveBt->Location = System::Drawing::Point(799, 130);
				 this->invSaveBt->Margin = System::Windows::Forms::Padding(4);
				 this->invSaveBt->Name = L"invSaveBt";
				 this->invSaveBt->Size = System::Drawing::Size(70, 38);
				 this->invSaveBt->TabIndex = 6;
				 this->invSaveBt->Text = L"SAVE";
				 this->invSaveBt->UseVisualStyleBackColor = false;
				 this->invSaveBt->Click += gcnew System::EventHandler(this, &InvForm::invSaveBt_Click);
				 // 
				 // invCancelBt
				 // 
				 this->invCancelBt->BackColor = System::Drawing::Color::Red;
				 this->invCancelBt->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				 this->invCancelBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->invCancelBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->invCancelBt->Location = System::Drawing::Point(713, 130);
				 this->invCancelBt->Margin = System::Windows::Forms::Padding(4);
				 this->invCancelBt->Name = L"invCancelBt";
				 this->invCancelBt->Size = System::Drawing::Size(70, 38);
				 this->invCancelBt->TabIndex = 7;
				 this->invCancelBt->Text = L"QUIT";
				 this->invCancelBt->UseVisualStyleBackColor = false;
				 this->invCancelBt->Click += gcnew System::EventHandler(this, &InvForm::invCancelBt_Click);
				 // 
				 // inv8
				 // 
				 this->inv8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv8->Location = System::Drawing::Point(80, 54);
				 this->inv8->Margin = System::Windows::Forms::Padding(4);
				 this->inv8->MaxLength = 6;
				 this->inv8->Name = L"inv8";
				 this->inv8->Size = System::Drawing::Size(57, 26);
				 this->inv8->TabIndex = 10;
				 this->inv8->Text = L"000.00";
				 // 
				 // inv5
				 // 
				 this->inv5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv5->Location = System::Drawing::Point(80, 54);
				 this->inv5->Margin = System::Windows::Forms::Padding(4);
				 this->inv5->MaxLength = 6;
				 this->inv5->Name = L"inv5";
				 this->inv5->Size = System::Drawing::Size(57, 26);
				 this->inv5->TabIndex = 9;
				 this->inv5->Text = L"000.00";
				 // 
				 // inv2
				 // 
				 this->inv2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv2->Location = System::Drawing::Point(80, 54);
				 this->inv2->Margin = System::Windows::Forms::Padding(4);
				 this->inv2->MaxLength = 6;
				 this->inv2->Name = L"inv2";
				 this->inv2->Size = System::Drawing::Size(57, 26);
				 this->inv2->TabIndex = 8;
				 this->inv2->Text = L"000.00";
				 // 
				 // inv9
				 // 
				 this->inv9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv9->Location = System::Drawing::Point(149, 54);
				 this->inv9->Margin = System::Windows::Forms::Padding(4);
				 this->inv9->MaxLength = 6;
				 this->inv9->Name = L"inv9";
				 this->inv9->Size = System::Drawing::Size(57, 26);
				 this->inv9->TabIndex = 13;
				 this->inv9->Text = L"000.00";
				 // 
				 // inv6
				 // 
				 this->inv6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv6->Location = System::Drawing::Point(149, 54);
				 this->inv6->Margin = System::Windows::Forms::Padding(4);
				 this->inv6->MaxLength = 6;
				 this->inv6->Name = L"inv6";
				 this->inv6->Size = System::Drawing::Size(57, 26);
				 this->inv6->TabIndex = 12;
				 this->inv6->Text = L"000.00";
				 // 
				 // inv3
				 // 
				 this->inv3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv3->Location = System::Drawing::Point(149, 54);
				 this->inv3->Margin = System::Windows::Forms::Padding(4);
				 this->inv3->MaxLength = 6;
				 this->inv3->Name = L"inv3";
				 this->inv3->Size = System::Drawing::Size(57, 26);
				 this->inv3->TabIndex = 11;
				 this->inv3->Text = L"000.00";
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox1->Controls->Add(this->inv3);
				 this->groupBox1->Controls->Add(this->inv2);
				 this->groupBox1->Controls->Add(this->inv1);
				 this->groupBox1->Controls->Add(this->silo1);
				 this->groupBox1->Controls->Add(this->silo3);
				 this->groupBox1->Controls->Add(this->silo2);
				 this->groupBox1->ForeColor = System::Drawing::Color::Blue;
				 this->groupBox1->Location = System::Drawing::Point(11, 12);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(217, 101);
				 this->groupBox1->TabIndex = 14;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Lane A";
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox2->Controls->Add(this->silo4);
				 this->groupBox2->Controls->Add(this->silo6);
				 this->groupBox2->Controls->Add(this->silo5);
				 this->groupBox2->Controls->Add(this->inv4);
				 this->groupBox2->Controls->Add(this->inv6);
				 this->groupBox2->Controls->Add(this->inv5);
				 this->groupBox2->ForeColor = System::Drawing::Color::Green;
				 this->groupBox2->Location = System::Drawing::Point(239, 12);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(218, 101);
				 this->groupBox2->TabIndex = 15;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"Lane B";
				 // 
				 // silo4
				 // 
				 this->silo4->AutoSize = true;
				 this->silo4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo4->ForeColor = System::Drawing::Color::Green;
				 this->silo4->Location = System::Drawing::Point(12, 33);
				 this->silo4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo4->Name = L"silo4";
				 this->silo4->Size = System::Drawing::Size(49, 17);
				 this->silo4->TabIndex = 15;
				 this->silo4->Text = L"Silo 4";
				 // 
				 // silo6
				 // 
				 this->silo6->AutoSize = true;
				 this->silo6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo6->ForeColor = System::Drawing::Color::Green;
				 this->silo6->Location = System::Drawing::Point(152, 33);
				 this->silo6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo6->Name = L"silo6";
				 this->silo6->Size = System::Drawing::Size(49, 17);
				 this->silo6->TabIndex = 14;
				 this->silo6->Text = L"Silo 6";
				 // 
				 // silo5
				 // 
				 this->silo5->AutoSize = true;
				 this->silo5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo5->ForeColor = System::Drawing::Color::Green;
				 this->silo5->Location = System::Drawing::Point(82, 33);
				 this->silo5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo5->Name = L"silo5";
				 this->silo5->Size = System::Drawing::Size(49, 17);
				 this->silo5->TabIndex = 13;
				 this->silo5->Text = L"Silo 5";
				 // 
				 // groupBox3
				 // 
				 this->groupBox3->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox3->Controls->Add(this->silo7);
				 this->groupBox3->Controls->Add(this->silo9);
				 this->groupBox3->Controls->Add(this->silo8);
				 this->groupBox3->Controls->Add(this->inv9);
				 this->groupBox3->Controls->Add(this->inv7);
				 this->groupBox3->Controls->Add(this->inv8);
				 this->groupBox3->ForeColor = System::Drawing::Color::Red;
				 this->groupBox3->Location = System::Drawing::Point(467, 12);
				 this->groupBox3->Name = L"groupBox3";
				 this->groupBox3->Size = System::Drawing::Size(217, 101);
				 this->groupBox3->TabIndex = 16;
				 this->groupBox3->TabStop = false;
				 this->groupBox3->Text = L"Lane C";
				 // 
				 // silo7
				 // 
				 this->silo7->AutoSize = true;
				 this->silo7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo7->ForeColor = System::Drawing::Color::Red;
				 this->silo7->Location = System::Drawing::Point(12, 33);
				 this->silo7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo7->Name = L"silo7";
				 this->silo7->Size = System::Drawing::Size(49, 17);
				 this->silo7->TabIndex = 16;
				 this->silo7->Text = L"Silo 7";
				 // 
				 // silo9
				 // 
				 this->silo9->AutoSize = true;
				 this->silo9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo9->ForeColor = System::Drawing::Color::Red;
				 this->silo9->Location = System::Drawing::Point(152, 33);
				 this->silo9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo9->Name = L"silo9";
				 this->silo9->Size = System::Drawing::Size(49, 17);
				 this->silo9->TabIndex = 15;
				 this->silo9->Text = L"Silo 9";
				 // 
				 // silo8
				 // 
				 this->silo8->AutoSize = true;
				 this->silo8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo8->ForeColor = System::Drawing::Color::Red;
				 this->silo8->Location = System::Drawing::Point(82, 33);
				 this->silo8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo8->Name = L"silo8";
				 this->silo8->Size = System::Drawing::Size(49, 17);
				 this->silo8->TabIndex = 14;
				 this->silo8->Text = L"Silo 8";
				 // 
				 // groupBox4
				 // 
				 this->groupBox4->BackColor = System::Drawing::Color::Gainsboro;
				 this->groupBox4->Controls->Add(this->silo10);
				 this->groupBox4->Controls->Add(this->silo12);
				 this->groupBox4->Controls->Add(this->silo11);
				 this->groupBox4->Controls->Add(this->inv12);
				 this->groupBox4->Controls->Add(this->inv10);
				 this->groupBox4->Controls->Add(this->inv11);
				 this->groupBox4->ForeColor = System::Drawing::Color::Coral;
				 this->groupBox4->Location = System::Drawing::Point(695, 12);
				 this->groupBox4->Name = L"groupBox4";
				 this->groupBox4->Size = System::Drawing::Size(217, 101);
				 this->groupBox4->TabIndex = 17;
				 this->groupBox4->TabStop = false;
				 this->groupBox4->Text = L"Lane D";
				 // 
				 // silo10
				 // 
				 this->silo10->AutoSize = true;
				 this->silo10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo10->ForeColor = System::Drawing::Color::Coral;
				 this->silo10->Location = System::Drawing::Point(12, 33);
				 this->silo10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo10->Name = L"silo10";
				 this->silo10->Size = System::Drawing::Size(58, 17);
				 this->silo10->TabIndex = 16;
				 this->silo10->Text = L"Silo 10";
				 // 
				 // silo12
				 // 
				 this->silo12->AutoSize = true;
				 this->silo12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo12->ForeColor = System::Drawing::Color::Coral;
				 this->silo12->Location = System::Drawing::Point(152, 33);
				 this->silo12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo12->Name = L"silo12";
				 this->silo12->Size = System::Drawing::Size(58, 17);
				 this->silo12->TabIndex = 15;
				 this->silo12->Text = L"Silo 12";
				 // 
				 // silo11
				 // 
				 this->silo11->AutoSize = true;
				 this->silo11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->silo11->ForeColor = System::Drawing::Color::Coral;
				 this->silo11->Location = System::Drawing::Point(82, 33);
				 this->silo11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->silo11->Name = L"silo11";
				 this->silo11->Size = System::Drawing::Size(58, 17);
				 this->silo11->TabIndex = 14;
				 this->silo11->Text = L"Silo 11";
				 // 
				 // inv12
				 // 
				 this->inv12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv12->Location = System::Drawing::Point(149, 54);
				 this->inv12->Margin = System::Windows::Forms::Padding(4);
				 this->inv12->MaxLength = 6;
				 this->inv12->Name = L"inv12";
				 this->inv12->Size = System::Drawing::Size(57, 26);
				 this->inv12->TabIndex = 13;
				 this->inv12->Text = L"000.00";
				 // 
				 // inv10
				 // 
				 this->inv10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv10->Location = System::Drawing::Point(11, 54);
				 this->inv10->Margin = System::Windows::Forms::Padding(4);
				 this->inv10->MaxLength = 6;
				 this->inv10->Name = L"inv10";
				 this->inv10->Size = System::Drawing::Size(57, 26);
				 this->inv10->TabIndex = 5;
				 this->inv10->Text = L"000.00";
				 // 
				 // inv11
				 // 
				 this->inv11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->inv11->Location = System::Drawing::Point(80, 54);
				 this->inv11->Margin = System::Windows::Forms::Padding(4);
				 this->inv11->MaxLength = 6;
				 this->inv11->Name = L"inv11";
				 this->inv11->Size = System::Drawing::Size(57, 26);
				 this->inv11->TabIndex = 10;
				 this->inv11->Text = L"000.00";
				 // 
				 // InvForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::Color::Silver;
				 this->ClientSize = System::Drawing::Size(921, 188);
				 this->ControlBox = false;
				 this->Controls->Add(this->groupBox4);
				 this->Controls->Add(this->invCancelBt);
				 this->Controls->Add(this->invSaveBt);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->groupBox3);
				 this->Controls->Add(this->groupBox2);
				 this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				 this->Margin = System::Windows::Forms::Padding(4);
				 this->Name = L"InvForm";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"Change Inventory";
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 this->groupBox3->ResumeLayout(false);
				 this->groupBox3->PerformLayout();
				 this->groupBox4->ResumeLayout(false);
				 this->groupBox4->PerformLayout();
				 this->ResumeLayout(false);

			 }
#pragma endregion

			 //----------------------------------------------------------------
	private: System::Void invSaveBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if(psIni->bBotScale)
				 {
					 psInv->fInv1 = Convert::ToDouble(inv1->Text);
					 psInv->fInv2 = Convert::ToDouble(inv2->Text);
					 psInv->fInv3 = Convert::ToDouble(inv3->Text);

					 psInv->fInv4 = Convert::ToDouble(inv4->Text);
					 psInv->fInv5 = Convert::ToDouble(inv5->Text);
					 psInv->fInv6 = Convert::ToDouble(inv6->Text);

					 psInv->fInv7 = Convert::ToDouble(inv7->Text);
					 psInv->fInv8 = Convert::ToDouble(inv8->Text);
					 psInv->fInv9 = Convert::ToDouble(inv9->Text);

					 psInv->fInv10 = Convert::ToDouble(inv10->Text);
					 psInv->fInv11 = Convert::ToDouble(inv11->Text);
					 psInv->fInv12 = Convert::ToDouble(inv12->Text);
				 }
				 else
				 {
					 psInv->fInv1 = Convert::ToDouble(inv1->Text);
					 psInv->fInv2 = Convert::ToDouble(inv4->Text);
					 psInv->fInv3 = Convert::ToDouble(inv7->Text);
					 psInv->fInv4 = Convert::ToDouble(inv10->Text);
				 }
				 psIni->bSaveInv = true;
				 this->Close();
			 }
			 //----------------------------------------------------------------
	private: System::Void invCancelBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->Close();
			 }



	};
}
