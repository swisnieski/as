#pragma once
#include "stdafx.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace As
{

	/// <summary>
	/// Summary for About
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class About : public System::Windows::Forms::Form
	{
	public:
		About(All^ pAll)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			verLb->Text += VERSION;
			snLb->Text += pAll->pSerialNum;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~About()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  verLb;
	protected: 

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  snLb;
	private: System::Windows::Forms::Label^  label1;
	private: System::ComponentModel::IContainer^  components;
	protected: 


	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(About::typeid));
			this->verLb = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->snLb = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// verLb
			// 
			this->verLb->AutoSize = true;
			this->verLb->BackColor = System::Drawing::Color::Transparent;
			this->verLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->verLb->ForeColor = System::Drawing::Color::Black;
			this->verLb->Location = System::Drawing::Point(343, 256);
			this->verLb->Name = L"verLb";
			this->verLb->Size = System::Drawing::Size(43, 17);
			this->verLb->TabIndex = 1;
			this->verLb->Text = L"Ver: ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Location = System::Drawing::Point(436, 398);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(184, 17);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Written by George Cewe";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Black;
			this->label3->Location = System::Drawing::Point(343, 323);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(277, 17);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Copyright (C) 2006 GivenHansco Inc.";
			// 
			// snLb
			// 
			this->snLb->AutoSize = true;
			this->snLb->BackColor = System::Drawing::Color::Transparent;
			this->snLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->snLb->ForeColor = System::Drawing::Color::Black;
			this->snLb->Location = System::Drawing::Point(343, 288);
			this->snLb->Name = L"snLb";
			this->snLb->Size = System::Drawing::Size(49, 17);
			this->snLb->TabIndex = 4;
			this->snLb->Text = L"S/N:  ";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Black;
			this->label1->Location = System::Drawing::Point(343, 224);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(232, 17);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Model: Keystone Silo Load Out";
			// 
			// About
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(632, 446);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->snLb);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->verLb);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"About";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;			//DC 3.1.5
			this->Text = L"Keystone Silo Load Out";
			this->Click += gcnew System::EventHandler(this, &About::About_Click);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void About_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->Close();
		 }


};
}
