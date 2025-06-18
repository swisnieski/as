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
	/// Summary for StopForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class StopForm : public System::Windows::Forms::Form
	{
	public:
		StopForm(LOG_REC *psLogIn, Job^ pJobIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			psLog = psLogIn;
			pJob = pJobIn;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~StopForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  targetBt;
	private: System::Windows::Forms::Button^  loadBt;
	private: System::Windows::Forms::Button^  voidBt;
	private: System::Windows::Forms::Button^  cancelBt;

	private:
		LOG_REC *psLog;
		Job^     pJob;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(StopForm::typeid));
			this->targetBt = (gcnew System::Windows::Forms::Button());
			this->loadBt = (gcnew System::Windows::Forms::Button());
			this->voidBt = (gcnew System::Windows::Forms::Button());
			this->cancelBt = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// targetBt
			// 
			this->targetBt->AutoSize = true;
			this->targetBt->BackColor = System::Drawing::Color::PaleGreen;
			this->targetBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->targetBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->targetBt->Location = System::Drawing::Point(37, 31);
			this->targetBt->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->targetBt->Name = L"targetBt";
			this->targetBt->Size = System::Drawing::Size(150, 39);
			this->targetBt->TabIndex = 0;
			this->targetBt->Text = L"accept Target";
			this->targetBt->UseVisualStyleBackColor = false;
			this->targetBt->Click += gcnew System::EventHandler(this, &StopForm::targetBt_Click);
			// 
			// loadBt
			// 
			this->loadBt->BackColor = System::Drawing::Color::LightSteelBlue;
			this->loadBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->loadBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->loadBt->Location = System::Drawing::Point(37, 90);
			this->loadBt->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->loadBt->Name = L"loadBt";
			this->loadBt->Size = System::Drawing::Size(150, 37);
			this->loadBt->TabIndex = 1;
			this->loadBt->Text = L"accept Load";
			this->loadBt->UseVisualStyleBackColor = false;
			this->loadBt->Click += gcnew System::EventHandler(this, &StopForm::loadBt_Click);
			// 
			// voidBt
			// 
			this->voidBt->BackColor = System::Drawing::Color::Yellow;
			this->voidBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->voidBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->voidBt->Location = System::Drawing::Point(37, 148);
			this->voidBt->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->voidBt->Name = L"voidBt";
			this->voidBt->Size = System::Drawing::Size(150, 37);
			this->voidBt->TabIndex = 2;
			this->voidBt->Text = L"void Ticket";
			this->voidBt->UseVisualStyleBackColor = false;
			this->voidBt->Click += gcnew System::EventHandler(this, &StopForm::voidBt_Click);
			// 
			// cancelBt
			// 
			this->cancelBt->AutoSize = true;
			this->cancelBt->BackColor = System::Drawing::Color::Red;
			this->cancelBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cancelBt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cancelBt->Location = System::Drawing::Point(90, 216);
			this->cancelBt->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->cancelBt->Name = L"cancelBt";
			this->cancelBt->Size = System::Drawing::Size(97, 39);
			this->cancelBt->TabIndex = 3;
			this->cancelBt->Text = L"CANCEL";
			this->cancelBt->UseVisualStyleBackColor = false;
			this->cancelBt->Click += gcnew System::EventHandler(this, &StopForm::cancelBt_Click);
			// 
			// StopForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(221, 289);
			this->ControlBox = false;
			this->Controls->Add(this->cancelBt);
			this->Controls->Add(this->voidBt);
			this->Controls->Add(this->loadBt);
			this->Controls->Add(this->targetBt);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"StopForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;			//DC 3.1.5
			this->Text = L"Stop Batch";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void targetBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 pJob->eStatus = S_ABORTED;
				 psLog->eJobStatus = S_ABORTED;
				 psLog->eStop = A_TARGET;
				 psLog->eState = S_ABORT;
				 this->Close();
			 }
private: System::Void loadBt_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				 pJob->eStatus = S_ABORTED;
				 psLog->eJobStatus  = S_ABORTED;
				 psLog->eStop = A_LOAD;
				 psLog->eState = S_ABORT;
				 this->Close();
		 }
private: System::Void voidBt_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				 pJob->eStatus = S_VOIDED;
				 psLog->eJobStatus  = S_VOIDED;
				 psLog->eStop = A_VOID;
				 psLog->eState = S_ABORT;
				 this->Close();
		 }
private: System::Void cancelBt_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				 this->Close();
		 }

};
}
