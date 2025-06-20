#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Cbc {

#define STX 0x02 
#define ETX 0x03
#define CR  0x0D

	/// <summary>
	/// Summary for UdpFrm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class UdpFrm : public System::Windows::Forms::Form
	{
	public:
		UdpFrm(All^ pAllIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pAll = pAllIn;
			timer->Enabled = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UdpFrm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		All ^ pAll;
		String^		 stMsg;
	private: System::Windows::Forms::TextBox^  trkTB;
	private: System::Windows::Forms::TextBox^  ticTB;
	private: System::Windows::Forms::TextBox^  loadTB;


	protected:


	private: System::Windows::Forms::Label^  trkLb;
	private: System::Windows::Forms::Label^  ticLb;

	private: System::Windows::Forms::Label^  loadLb;
	private: System::Windows::Forms::Button^  BegBt;
	private: System::Windows::Forms::Button^  endDryBt;
	private: System::Windows::Forms::Button^  endWetBt;

	private: System::Windows::Forms::Timer^  timer;
	private: System::Windows::Forms::RichTextBox^  udpMsgBox;



	private: System::ComponentModel::IContainer^  components;







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
			this->components = (gcnew System::ComponentModel::Container());
			this->trkTB = (gcnew System::Windows::Forms::TextBox());
			this->ticTB = (gcnew System::Windows::Forms::TextBox());
			this->loadTB = (gcnew System::Windows::Forms::TextBox());
			this->trkLb = (gcnew System::Windows::Forms::Label());
			this->ticLb = (gcnew System::Windows::Forms::Label());
			this->loadLb = (gcnew System::Windows::Forms::Label());
			this->BegBt = (gcnew System::Windows::Forms::Button());
			this->endDryBt = (gcnew System::Windows::Forms::Button());
			this->endWetBt = (gcnew System::Windows::Forms::Button());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->udpMsgBox = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// trkTB
			// 
			this->trkTB->Location = System::Drawing::Point(13, 36);
			this->trkTB->Name = L"trkTB";
			this->trkTB->Size = System::Drawing::Size(100, 20);
			this->trkTB->TabIndex = 1;
			this->trkTB->Text = L"100";
			this->trkTB->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// ticTB
			// 
			this->ticTB->Location = System::Drawing::Point(152, 36);
			this->ticTB->Name = L"ticTB";
			this->ticTB->Size = System::Drawing::Size(100, 20);
			this->ticTB->TabIndex = 2;
			this->ticTB->Text = L"200";
			this->ticTB->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// loadTB
			// 
			this->loadTB->Location = System::Drawing::Point(297, 36);
			this->loadTB->Name = L"loadTB";
			this->loadTB->Size = System::Drawing::Size(100, 20);
			this->loadTB->TabIndex = 3;
			this->loadTB->Text = L"1";
			this->loadTB->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// trkLb
			// 
			this->trkLb->AutoSize = true;
			this->trkLb->Location = System::Drawing::Point(13, 17);
			this->trkLb->Name = L"trkLb";
			this->trkLb->Size = System::Drawing::Size(63, 13);
			this->trkLb->TabIndex = 4;
			this->trkLb->Text = L"Truck Code";
			// 
			// ticLb
			// 
			this->ticLb->AutoSize = true;
			this->ticLb->Location = System::Drawing::Point(152, 17);
			this->ticLb->Name = L"ticLb";
			this->ticLb->Size = System::Drawing::Size(65, 13);
			this->ticLb->TabIndex = 5;
			this->ticLb->Text = L"Ticket Code";
			// 
			// loadLb
			// 
			this->loadLb->AutoSize = true;
			this->loadLb->Location = System::Drawing::Point(297, 16);
			this->loadLb->Name = L"loadLb";
			this->loadLb->Size = System::Drawing::Size(64, 13);
			this->loadLb->TabIndex = 6;
			this->loadLb->Text = L"Load Status";
			// 
			// BegBt
			// 
			this->BegBt->Location = System::Drawing::Point(13, 79);
			this->BegBt->Name = L"BegBt";
			this->BegBt->Size = System::Drawing::Size(83, 31);
			this->BegBt->TabIndex = 7;
			this->BegBt->Text = L"CommandAlkon";
			this->BegBt->UseVisualStyleBackColor = true;
			this->BegBt->Click += gcnew System::EventHandler(this, &UdpFrm::BegBt_Click);
			// 
			// endDryBt
			// 
			this->endDryBt->Location = System::Drawing::Point(13, 131);
			this->endDryBt->Name = L"endDryBt";
			this->endDryBt->Size = System::Drawing::Size(83, 31);
			this->endDryBt->TabIndex = 8;
			this->endDryBt->Text = L"TrackItWare";
			this->endDryBt->UseVisualStyleBackColor = true;
			this->endDryBt->Click += gcnew System::EventHandler(this, &UdpFrm::endDryBt_Click);
			// 
			// endWetBt
			// 
			this->endWetBt->Location = System::Drawing::Point(13, 183);
			this->endWetBt->Name = L"endWetBt";
			this->endWetBt->Size = System::Drawing::Size(83, 31);
			this->endWetBt->TabIndex = 9;
			this->endWetBt->Text = L"Digi Fleet";
			this->endWetBt->UseVisualStyleBackColor = true;
			this->endWetBt->Click += gcnew System::EventHandler(this, &UdpFrm::endWetBt_Click);
			// 
			// timer
			// 
			this->timer->Interval = 500;
			this->timer->Tick += gcnew System::EventHandler(this, &UdpFrm::timer_Tick);
			// 
			// udpMsgBox
			// 
			this->udpMsgBox->Location = System::Drawing::Point(152, 79);
			this->udpMsgBox->Name = L"udpMsgBox";
			this->udpMsgBox->Size = System::Drawing::Size(354, 362);
			this->udpMsgBox->TabIndex = 11;
			this->udpMsgBox->Text = L"udpMsgBox";
			// 
			// UdpFrm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(518, 481);
			this->Controls->Add(this->udpMsgBox);
			this->Controls->Add(this->endWetBt);
			this->Controls->Add(this->endDryBt);
			this->Controls->Add(this->BegBt);
			this->Controls->Add(this->loadLb);
			this->Controls->Add(this->ticLb);
			this->Controls->Add(this->trkLb);
			this->Controls->Add(this->loadTB);
			this->Controls->Add(this->ticTB);
			this->Controls->Add(this->trkTB);
			this->Name = L"UdpFrm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UdpFrm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		static	char* s2p(String^ stIn, char *pcTmp)
		{
			if (stIn != nullptr)
			{
				for (int i = 0; i< stIn->Length; i++)
					pcTmp[i] = (char)stIn[i];
				pcTmp[stIn->Length] = 0;
			}
			return pcTmp;
		}

	private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		udpMsgBox->Text = pAll->pDisp;
	}
	private: System::Void BegBt_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int nTrkCode = Int32::Parse(trkTB->Text);
		int nTicCode = Int32::Parse(ticTB->Text);
		int nLoadCode = Int32::Parse(loadTB->Text);
		sendUdpMsg(nTrkCode, nTicCode, nLoadCode, 1);
	}
	private: System::Void endDryBt_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int nTrkCode = Int32::Parse(trkTB->Text);
		int nTicCode = Int32::Parse(ticTB->Text);
		int nLoadCode = Int32::Parse(loadTB->Text);
		sendUdpMsg(nTrkCode, nTicCode, nLoadCode, 2);
	}
	private: System::Void endWetBt_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int nTrkCode = Int32::Parse(trkTB->Text);
		int nTicCode = Int32::Parse(ticTB->Text);
		int nLoadCode = Int32::Parse(loadTB->Text);
		sendUdpMsg(nTrkCode, nTicCode, nLoadCode, 4);
	}
	public:
		//----------------------------------------------------------------------
		void sendUdpMsg(int nTrkCode, int nTicCode, int nLoadCode, int nStatus)
		{
			try
			{
				char acBuf[128];
				String^ stDateTime = DateTime::Now.ToString("MM-dd-yyyy HH:mm:ss");
				String^ stDateTime2 = DateTime::UtcNow.ToString("yyyy-MM-ddTHH:mm:ss");
				char acTmp[20];

				//DC 7.1.9
				int nLoadSize = int(10.25*100);
				char acU = 'Y';
				int nSlump = int(4.12*100);
				char acM = 'I';
				int nAddWat = int(75.2);
				char acV = 'G';

				switch (nStatus)
				{
				case 1:
					sprintf(acBuf, "%cL%10d%08d%01d%s%c"
						, STX
						, nTrkCode
						, nTicCode
						, nLoadCode
						, s2p(stDateTime, acTmp)
						, ETX
					);
					pAll->qDisp->Enqueue(gcnew String(acBuf));
					break;

				case 2:
					sprintf(acBuf, "%cL%10d%08d%01d%c"
						, STX
						, nTrkCode
						, nTicCode
						, nLoadCode
						, ETX
					);
					pAll->qDisp->Enqueue(gcnew String(acBuf));
					break;

				case 3:
					sprintf(acBuf, "%c%10d%08d%01d"
						, 'L'
						, nTrkCode
						, nTicCode
						, nLoadCode
					);
					pAll->qDisp->Enqueue(gcnew String(acBuf));
					break;

				case 4:		//DC 7.1.9
					char acTmp2[9];
					sprintf(acBuf, "%s%s%c%01d%04d%08d%04d%c%03d%c%03d%c%s"		//%c%s%01d"
						, "DV03"
						, s2p(pAll->stDigitalFleetId, acTmp2)
						, 'E'
						, nLoadCode
						, nTrkCode
						, nTicCode
						, nLoadSize
						, acU
						, nSlump
						, acM
						, nAddWat
						, acV
						, s2p(stDateTime2, acTmp)
						/*, CR
						, "-L"
						, nLoadCode*/
					);
					pAll->qDisp->Enqueue(gcnew String(acBuf));
					break;
				default:
					break;
				}
				return;
			}
			catch (Exception^ e)
			{
				pAll->stExc += "\nUdpFrm: " + e->ToString();
				return;
			}
		}
	};
}
