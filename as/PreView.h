#pragma once



using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;


namespace As {

	/// <summary>
	/// Summary for PreView
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class PreView : public System::Windows::Forms::Form
	{
	public:
		PreView(All^ pAllIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pAll = pAllIn;
			psIni = pAll->psIni;
//			preViewBox->Text = printBuf;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PreView()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		All^ pAll;
		INI *psIni;


	private: System::Windows::Forms::Button^  remLoginBt;


	protected: 

	protected: 

	protected: 

	private:
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
			this->remLoginBt = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// remLoginBt
			// 
			this->remLoginBt->Location = System::Drawing::Point(261, 388);
			this->remLoginBt->Name = L"remLoginBt";
			this->remLoginBt->Size = System::Drawing::Size(148, 23);
			this->remLoginBt->TabIndex = 0;
			this->remLoginBt->Text = L"Remote Login";
			this->remLoginBt->UseVisualStyleBackColor = true;
			this->remLoginBt->Click += gcnew System::EventHandler(this, &PreView::remLoginBt_Click);
			// 
			// PreView
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(669, 454);
			this->Controls->Add(this->remLoginBt);
			this->Name = L"PreView";
			this->Text = L"PreView";
			this->ResumeLayout(false);

		}
#pragma endregion
//	private: System::Void PreView_Load(System::Object^  sender, System::EventArgs^  e) {
//			 }
	private: System::Void remLoginBt_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				
			 }
	};
}
