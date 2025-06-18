#pragma once

#include <string>
#include <iostream>
#include <cmath>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
//using namespace System::Data;
using namespace System::Drawing;
using namespace std;


namespace As {

	/// <summary>
	/// Summary for IOForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class IOForm : public System::Windows::Forms::Form
	{
	public:
		IOForm(All^ pAllIn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pAll = pAllIn;
			psIni = pAll->psIni;

			if(pAll->eAsType == A_REMOTE)
				this->enableIOCb->Enabled = false;

			initOutputs();
			timer1->Enabled = true;
			if(!psIni->bPdmPlc)
			{
				psIni->nMask |= P_DROP1;
				psIni->nMask |= P_DROP2;
				psIni->nMask |= P_DROP3;
				psIni->nMask |= P_LIGHTA;
				psIni->nMask |= P_SAFE1;
				psIni->nMask |= P_SAFE2;
				psIni->nMask |= P_SAFE3;
				psIni->nMask |= P_SPAREA;
				psIni->nMask |= P_CLRDRP_A;
				psIni->nMask |= P_CLRSV_A;
				psIni->nMask |= P_CLEAR_A;

				psIni->nMask |= P_DROP4;
				psIni->nMask |= P_DROP5;
				psIni->nMask |= P_DROP6;
				psIni->nMask |= P_LIGHTB;
				psIni->nMask |= P_SAFE4;
				psIni->nMask |= P_SAFE5;
				psIni->nMask |= P_SAFE6;
				psIni->nMask |= P_SPAREB;
				psIni->nMask |= P_CLRDRP_B;
				psIni->nMask |= P_CLRSV_B;
				psIni->nMask |= P_CLEAR_B;

				psIni->nMask |= P_DROP7;
				psIni->nMask |= P_DROP8;
				psIni->nMask |= P_DROP9;
				psIni->nMask |= P_LIGHTC;
				psIni->nMask |= P_SAFE7;
				psIni->nMask |= P_SAFE8;
				psIni->nMask |= P_SAFE9;
				psIni->nMask |= P_SPAREC;
				psIni->nMask |= P_CLRDRP_C;
				psIni->nMask |= P_CLRSV_C;
				psIni->nMask |= P_CLEAR_C;

				psIni->nMask |= P_DROP10;
				psIni->nMask |= P_DROP11;
				psIni->nMask |= P_DROP12;
				psIni->nMask |= P_LIGHTD;
				psIni->nMask |= P_SAFE10;
				psIni->nMask |= P_SAFE11;
				psIni->nMask |= P_SAFE12;
				psIni->nMask |= P_SPARED;
				psIni->nMask |= P_CLRDRP_D;
				psIni->nMask |= P_CLRSV_D;
				psIni->nMask |= P_CLEAR_D;

				psIni->nInpMask |= J_FILL1;
				psIni->nInpMask |= J_FILL2;
				psIni->nInpMask |= J_FILL3;
				psIni->nInpMask |= J_FILL4;
				psIni->nInpMask |= J_FILL5;
				psIni->nInpMask |= J_FILL6;
				psIni->nInpMask |= J_FILL7;
				psIni->nInpMask |= J_FILL8;
				psIni->nInpMask |= J_FILL9;
				psIni->nInpMask |= J_FILL10;
				psIni->nInpMask |= J_FILL11;
				psIni->nInpMask |= J_FILL12;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~IOForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		All^ pAll;
		INI *psIni;
//		OPS *psIni;


		ushort		nRpoints1;
		ushort		nRpoints2;
		ushort		nRpoints3;
		ushort		nWpoints1;
		ushort		nWpoints2;
		ushort		nWpoints3;
		ushort		nWpoints4;
		bool		bOutputTest;	//DC 4.0.0

	private: System::Windows::Forms::Label^  label3;
	protected: 
	private: System::Windows::Forms::Button^  out16;
	private: System::Windows::Forms::Button^  out17;
	private: System::Windows::Forms::Button^  out18;
	private: System::Windows::Forms::Button^  out19;
	private: System::Windows::Forms::Button^  out20;
	private: System::Windows::Forms::Button^  out21;
	private: System::Windows::Forms::Button^  out23;
	private: System::Windows::Forms::Button^  out22;
	private: System::Windows::Forms::Button^  out12;
	private: System::Windows::Forms::Button^  out14;
	private: System::Windows::Forms::Button^  out15;
	private: System::Windows::Forms::Button^  out13;
	private: System::Windows::Forms::Button^  out0;
	private: System::Windows::Forms::Button^  out1;
	private: System::Windows::Forms::Button^  out11;
	private: System::Windows::Forms::Button^  out2;
	private: System::Windows::Forms::Button^  out10;
	private: System::Windows::Forms::Button^  out3;
	private: System::Windows::Forms::Button^  out9;
	private: System::Windows::Forms::Button^  out4;
	private: System::Windows::Forms::Button^  out8;
	private: System::Windows::Forms::Button^  out5;
	private: System::Windows::Forms::Button^  out7;
	private: System::Windows::Forms::Button^  out6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  in16;
	private: System::Windows::Forms::Label^  in17;
	private: System::Windows::Forms::Label^  in18;
	private: System::Windows::Forms::Label^  in19;
	private: System::Windows::Forms::Label^  in21;
	private: System::Windows::Forms::Label^  in22;
	private: System::Windows::Forms::Label^  in20;
	private: System::Windows::Forms::Label^  in23;
	private: System::Windows::Forms::Label^  in24;
	private: System::Windows::Forms::Label^  in25;
	private: System::Windows::Forms::Label^  in26;
	private: System::Windows::Forms::Label^  in27;
	private: System::Windows::Forms::Label^  in28;
	private: System::Windows::Forms::Label^  in29;
	private: System::Windows::Forms::Label^  in30;

	private: System::Windows::Forms::Label^  in0;
	private: System::Windows::Forms::Label^  in1;
	private: System::Windows::Forms::Label^  in2;
	private: System::Windows::Forms::Label^  in3;
	private: System::Windows::Forms::Label^  in5;
	private: System::Windows::Forms::Label^  in6;
	private: System::Windows::Forms::Label^  in4;
	private: System::Windows::Forms::Label^  in7;
	private: System::Windows::Forms::Label^  in8;
	private: System::Windows::Forms::Label^  in9;
	private: System::Windows::Forms::Label^  in10;
	private: System::Windows::Forms::Label^  in11;
	private: System::Windows::Forms::Label^  in12;
	private: System::Windows::Forms::Label^  in13;
	private: System::Windows::Forms::Label^  in14;
	private: System::Windows::Forms::Label^  in15;
	private: System::Windows::Forms::Button^  out28;
	private: System::Windows::Forms::Button^  out30;
	private: System::Windows::Forms::Button^  out31;
	private: System::Windows::Forms::Button^  out29;
	private: System::Windows::Forms::Button^  out27;
	private: System::Windows::Forms::Button^  out26;
	private: System::Windows::Forms::Button^  out25;
	private: System::Windows::Forms::Button^  out24;
private: System::Windows::Forms::Timer^  timer1;
private: System::Windows::Forms::Button^  holdBt1;
private: System::Windows::Forms::Button^  RInpBt1;
private: System::Windows::Forms::Button^  RInpBtIR;




private: System::Windows::Forms::Button^  DInpBt8;
private: System::Windows::Forms::Button^  DInpBtIR;


private: System::Windows::Forms::Button^  DInpBt1;
private: System::Windows::Forms::Button^  RInpBt2;




private: System::Windows::Forms::Button^  holdBt2;
private: System::Windows::Forms::Button^  holdBtIR;



private: System::Windows::Forms::Button^  DInpBt2;
private: System::Windows::Forms::Button^  RInpBt4;





private: System::Windows::Forms::Button^  holdBt4;


private: System::Windows::Forms::Button^  LInpBt4;
private: System::Windows::Forms::Button^  DInpBt4;
private: System::Windows::Forms::Button^  RInpBt5;





private: System::Windows::Forms::Button^  holdBt5;


private: System::Windows::Forms::Button^  LInpBt5;
private: System::Windows::Forms::Button^  DInpBt5;
private: System::Windows::Forms::Button^  RInpBt7;






private: System::Windows::Forms::Button^  holdBt7;


private: System::Windows::Forms::Button^  LInpBt6;
private: System::Windows::Forms::Button^  DInpBt7;
private: System::Windows::Forms::Button^  RInpBt8;




private: System::Windows::Forms::Button^  holdBt8;


private: System::Windows::Forms::Button^  out38;
private: System::Windows::Forms::Button^  out40;
private: System::Windows::Forms::Button^  out39;
private: System::Windows::Forms::Button^  out37;
private: System::Windows::Forms::Button^  out36;
private: System::Windows::Forms::Button^  out35;
private: System::Windows::Forms::Button^  out34;
private: System::Windows::Forms::Button^  out33;
private: System::Windows::Forms::Button^  out32;
private: System::Windows::Forms::Button^  out58;
private: System::Windows::Forms::Button^  out60;


private: System::Windows::Forms::Button^  out59;

private: System::Windows::Forms::Button^  out57;

private: System::Windows::Forms::Button^  out56;

private: System::Windows::Forms::Button^  out55;

private: System::Windows::Forms::Button^  out54;

private: System::Windows::Forms::Button^  out53;

private: System::Windows::Forms::Button^  out52;

private: System::Windows::Forms::Button^  out48;
private: System::Windows::Forms::Button^  out50;
private: System::Windows::Forms::Button^  out51;



private: System::Windows::Forms::Button^  out49;

private: System::Windows::Forms::Button^  out47;

private: System::Windows::Forms::Button^  out46;

private: System::Windows::Forms::Button^  out45;

private: System::Windows::Forms::Button^  out44;

private: System::Windows::Forms::Button^  out41;
private: System::Windows::Forms::Button^  out43;


private: System::Windows::Forms::Button^  out42;
private: System::Windows::Forms::Button^  out78;
private: System::Windows::Forms::Button^  out80;


private: System::Windows::Forms::Button^  out79;

private: System::Windows::Forms::Button^  out77;

private: System::Windows::Forms::Button^  out76;

private: System::Windows::Forms::Button^  out75;

private: System::Windows::Forms::Button^  out74;

private: System::Windows::Forms::Button^  out73;

private: System::Windows::Forms::Button^  out72;

private: System::Windows::Forms::Button^  out68;
private: System::Windows::Forms::Button^  out70;
private: System::Windows::Forms::Button^  out71;



private: System::Windows::Forms::Button^  out69;

private: System::Windows::Forms::Button^  out67;

private: System::Windows::Forms::Button^  out66;

private: System::Windows::Forms::Button^  out65;

private: System::Windows::Forms::Button^  out64;

private: System::Windows::Forms::Button^  out61;
private: System::Windows::Forms::Button^  out63;


private: System::Windows::Forms::Button^  out62;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label4;

private: System::Windows::Forms::Label^  label6;



private: System::Windows::Forms::CheckBox^  enableIOCb;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Label^  targetNumLb;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  in31;
private: System::Windows::Forms::Label^  in32;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::Button^  RInpBt;
private: System::Windows::Forms::Button^  KInpBt;
private: System::Windows::Forms::Button^  inp12Bt;
private: System::Windows::Forms::Button^  inp13Bt;
private: System::Windows::Forms::Button^  inp14Bt;
private: System::Windows::Forms::Button^  inp15Bt;
private: System::Windows::Forms::Button^  inp16Bt;
private: System::Windows::Forms::Button^  inp21Bt;





private: System::Windows::Forms::Button^  inp20Bt;

private: System::Windows::Forms::Button^  inp19Bt;

private: System::Windows::Forms::Button^  inp18Bt;

private: System::Windows::Forms::Button^  inp17Bt;
private: System::Windows::Forms::Button^  inp26Bt;


private: System::Windows::Forms::Button^  inp25Bt;

private: System::Windows::Forms::Button^  inp24Bt;

private: System::Windows::Forms::Button^  inp23Bt;

private: System::Windows::Forms::Button^  inp22Bt;
private: System::Windows::Forms::Button^  inp30Bt;


private: System::Windows::Forms::Button^  inp29Bt;


private: System::Windows::Forms::Button^  inp28Bt;

private: System::Windows::Forms::Button^  inp27Bt;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Label^  in33;
private: System::Windows::Forms::Label^  in34;
private: System::Windows::Forms::Label^  in35;
private: System::Windows::Forms::Label^  in36;
private: System::Windows::Forms::Label^  in37;
private: System::Windows::Forms::Label^  in38;
private: System::Windows::Forms::Label^  in39;
private: System::Windows::Forms::Label^  in40;
private: System::Windows::Forms::Button^  inp31Bt;
private: System::Windows::Forms::Button^  inp32Bt;
private: System::Windows::Forms::Button^  inp33Bt;
private: System::Windows::Forms::Button^  inp34Bt;
private: System::Windows::Forms::Label^  siloNumLb;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::Button^  laneTareBt4;
private: System::Windows::Forms::Button^  laneTareBt3;
private: System::Windows::Forms::Button^  laneTareBt2;
private: System::Windows::Forms::Button^  laneTareBt1;







private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
//		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->out16 = (gcnew System::Windows::Forms::Button());
			this->out17 = (gcnew System::Windows::Forms::Button());
			this->out18 = (gcnew System::Windows::Forms::Button());
			this->out19 = (gcnew System::Windows::Forms::Button());
			this->out20 = (gcnew System::Windows::Forms::Button());
			this->out21 = (gcnew System::Windows::Forms::Button());
			this->out23 = (gcnew System::Windows::Forms::Button());
			this->out22 = (gcnew System::Windows::Forms::Button());
			this->out12 = (gcnew System::Windows::Forms::Button());
			this->out14 = (gcnew System::Windows::Forms::Button());
			this->out15 = (gcnew System::Windows::Forms::Button());
			this->out13 = (gcnew System::Windows::Forms::Button());
			this->out0 = (gcnew System::Windows::Forms::Button());
			this->out1 = (gcnew System::Windows::Forms::Button());
			this->out11 = (gcnew System::Windows::Forms::Button());
			this->out2 = (gcnew System::Windows::Forms::Button());
			this->out10 = (gcnew System::Windows::Forms::Button());
			this->out3 = (gcnew System::Windows::Forms::Button());
			this->out9 = (gcnew System::Windows::Forms::Button());
			this->out4 = (gcnew System::Windows::Forms::Button());
			this->out8 = (gcnew System::Windows::Forms::Button());
			this->out5 = (gcnew System::Windows::Forms::Button());
			this->out7 = (gcnew System::Windows::Forms::Button());
			this->out6 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->in16 = (gcnew System::Windows::Forms::Label());
			this->in17 = (gcnew System::Windows::Forms::Label());
			this->in18 = (gcnew System::Windows::Forms::Label());
			this->in19 = (gcnew System::Windows::Forms::Label());
			this->in21 = (gcnew System::Windows::Forms::Label());
			this->in22 = (gcnew System::Windows::Forms::Label());
			this->in20 = (gcnew System::Windows::Forms::Label());
			this->in23 = (gcnew System::Windows::Forms::Label());
			this->in24 = (gcnew System::Windows::Forms::Label());
			this->in25 = (gcnew System::Windows::Forms::Label());
			this->in26 = (gcnew System::Windows::Forms::Label());
			this->in27 = (gcnew System::Windows::Forms::Label());
			this->in28 = (gcnew System::Windows::Forms::Label());
			this->in29 = (gcnew System::Windows::Forms::Label());
			this->in30 = (gcnew System::Windows::Forms::Label());
			this->in0 = (gcnew System::Windows::Forms::Label());
			this->in1 = (gcnew System::Windows::Forms::Label());
			this->in2 = (gcnew System::Windows::Forms::Label());
			this->in3 = (gcnew System::Windows::Forms::Label());
			this->in5 = (gcnew System::Windows::Forms::Label());
			this->in6 = (gcnew System::Windows::Forms::Label());
			this->in4 = (gcnew System::Windows::Forms::Label());
			this->in7 = (gcnew System::Windows::Forms::Label());
			this->in8 = (gcnew System::Windows::Forms::Label());
			this->in9 = (gcnew System::Windows::Forms::Label());
			this->in10 = (gcnew System::Windows::Forms::Label());
			this->in11 = (gcnew System::Windows::Forms::Label());
			this->in12 = (gcnew System::Windows::Forms::Label());
			this->in13 = (gcnew System::Windows::Forms::Label());
			this->in14 = (gcnew System::Windows::Forms::Label());
			this->in15 = (gcnew System::Windows::Forms::Label());
			this->out28 = (gcnew System::Windows::Forms::Button());
			this->out30 = (gcnew System::Windows::Forms::Button());
			this->out31 = (gcnew System::Windows::Forms::Button());
			this->out29 = (gcnew System::Windows::Forms::Button());
			this->out27 = (gcnew System::Windows::Forms::Button());
			this->out26 = (gcnew System::Windows::Forms::Button());
			this->out25 = (gcnew System::Windows::Forms::Button());
			this->out24 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->holdBt1 = (gcnew System::Windows::Forms::Button());
			this->RInpBt1 = (gcnew System::Windows::Forms::Button());
			this->RInpBtIR = (gcnew System::Windows::Forms::Button());
			this->DInpBt8 = (gcnew System::Windows::Forms::Button());
			this->DInpBtIR = (gcnew System::Windows::Forms::Button());
			this->DInpBt1 = (gcnew System::Windows::Forms::Button());
			this->RInpBt2 = (gcnew System::Windows::Forms::Button());
			this->holdBt2 = (gcnew System::Windows::Forms::Button());
			this->holdBtIR = (gcnew System::Windows::Forms::Button());
			this->DInpBt2 = (gcnew System::Windows::Forms::Button());
			this->RInpBt4 = (gcnew System::Windows::Forms::Button());
			this->holdBt4 = (gcnew System::Windows::Forms::Button());
			this->LInpBt4 = (gcnew System::Windows::Forms::Button());
			this->DInpBt4 = (gcnew System::Windows::Forms::Button());
			this->RInpBt5 = (gcnew System::Windows::Forms::Button());
			this->holdBt5 = (gcnew System::Windows::Forms::Button());
			this->LInpBt5 = (gcnew System::Windows::Forms::Button());
			this->DInpBt5 = (gcnew System::Windows::Forms::Button());
			this->RInpBt7 = (gcnew System::Windows::Forms::Button());
			this->holdBt7 = (gcnew System::Windows::Forms::Button());
			this->LInpBt6 = (gcnew System::Windows::Forms::Button());
			this->DInpBt7 = (gcnew System::Windows::Forms::Button());
			this->RInpBt8 = (gcnew System::Windows::Forms::Button());
			this->holdBt8 = (gcnew System::Windows::Forms::Button());
			this->out38 = (gcnew System::Windows::Forms::Button());
			this->out40 = (gcnew System::Windows::Forms::Button());
			this->out39 = (gcnew System::Windows::Forms::Button());
			this->out37 = (gcnew System::Windows::Forms::Button());
			this->out36 = (gcnew System::Windows::Forms::Button());
			this->out35 = (gcnew System::Windows::Forms::Button());
			this->out34 = (gcnew System::Windows::Forms::Button());
			this->out33 = (gcnew System::Windows::Forms::Button());
			this->out32 = (gcnew System::Windows::Forms::Button());
			this->out58 = (gcnew System::Windows::Forms::Button());
			this->out60 = (gcnew System::Windows::Forms::Button());
			this->out59 = (gcnew System::Windows::Forms::Button());
			this->out57 = (gcnew System::Windows::Forms::Button());
			this->out56 = (gcnew System::Windows::Forms::Button());
			this->out55 = (gcnew System::Windows::Forms::Button());
			this->out54 = (gcnew System::Windows::Forms::Button());
			this->out53 = (gcnew System::Windows::Forms::Button());
			this->out52 = (gcnew System::Windows::Forms::Button());
			this->out48 = (gcnew System::Windows::Forms::Button());
			this->out50 = (gcnew System::Windows::Forms::Button());
			this->out51 = (gcnew System::Windows::Forms::Button());
			this->out49 = (gcnew System::Windows::Forms::Button());
			this->out47 = (gcnew System::Windows::Forms::Button());
			this->out46 = (gcnew System::Windows::Forms::Button());
			this->out45 = (gcnew System::Windows::Forms::Button());
			this->out44 = (gcnew System::Windows::Forms::Button());
			this->out41 = (gcnew System::Windows::Forms::Button());
			this->out43 = (gcnew System::Windows::Forms::Button());
			this->out42 = (gcnew System::Windows::Forms::Button());
			this->out78 = (gcnew System::Windows::Forms::Button());
			this->out80 = (gcnew System::Windows::Forms::Button());
			this->out79 = (gcnew System::Windows::Forms::Button());
			this->out77 = (gcnew System::Windows::Forms::Button());
			this->out76 = (gcnew System::Windows::Forms::Button());
			this->out75 = (gcnew System::Windows::Forms::Button());
			this->out74 = (gcnew System::Windows::Forms::Button());
			this->out73 = (gcnew System::Windows::Forms::Button());
			this->out72 = (gcnew System::Windows::Forms::Button());
			this->out68 = (gcnew System::Windows::Forms::Button());
			this->out70 = (gcnew System::Windows::Forms::Button());
			this->out71 = (gcnew System::Windows::Forms::Button());
			this->out69 = (gcnew System::Windows::Forms::Button());
			this->out67 = (gcnew System::Windows::Forms::Button());
			this->out66 = (gcnew System::Windows::Forms::Button());
			this->out65 = (gcnew System::Windows::Forms::Button());
			this->out64 = (gcnew System::Windows::Forms::Button());
			this->out61 = (gcnew System::Windows::Forms::Button());
			this->out63 = (gcnew System::Windows::Forms::Button());
			this->out62 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->enableIOCb = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->targetNumLb = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->in31 = (gcnew System::Windows::Forms::Label());
			this->in32 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->RInpBt = (gcnew System::Windows::Forms::Button());
			this->KInpBt = (gcnew System::Windows::Forms::Button());
			this->inp12Bt = (gcnew System::Windows::Forms::Button());
			this->inp13Bt = (gcnew System::Windows::Forms::Button());
			this->inp14Bt = (gcnew System::Windows::Forms::Button());
			this->inp15Bt = (gcnew System::Windows::Forms::Button());
			this->inp16Bt = (gcnew System::Windows::Forms::Button());
			this->inp21Bt = (gcnew System::Windows::Forms::Button());
			this->inp20Bt = (gcnew System::Windows::Forms::Button());
			this->inp19Bt = (gcnew System::Windows::Forms::Button());
			this->inp18Bt = (gcnew System::Windows::Forms::Button());
			this->inp17Bt = (gcnew System::Windows::Forms::Button());
			this->inp26Bt = (gcnew System::Windows::Forms::Button());
			this->inp25Bt = (gcnew System::Windows::Forms::Button());
			this->inp24Bt = (gcnew System::Windows::Forms::Button());
			this->inp23Bt = (gcnew System::Windows::Forms::Button());
			this->inp22Bt = (gcnew System::Windows::Forms::Button());
			this->inp30Bt = (gcnew System::Windows::Forms::Button());
			this->inp29Bt = (gcnew System::Windows::Forms::Button());
			this->inp28Bt = (gcnew System::Windows::Forms::Button());
			this->inp27Bt = (gcnew System::Windows::Forms::Button());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->in33 = (gcnew System::Windows::Forms::Label());
			this->in34 = (gcnew System::Windows::Forms::Label());
			this->in35 = (gcnew System::Windows::Forms::Label());
			this->in36 = (gcnew System::Windows::Forms::Label());
			this->in37 = (gcnew System::Windows::Forms::Label());
			this->in38 = (gcnew System::Windows::Forms::Label());
			this->in39 = (gcnew System::Windows::Forms::Label());
			this->in40 = (gcnew System::Windows::Forms::Label());
			this->inp31Bt = (gcnew System::Windows::Forms::Button());
			this->inp32Bt = (gcnew System::Windows::Forms::Button());
			this->inp33Bt = (gcnew System::Windows::Forms::Button());
			this->inp34Bt = (gcnew System::Windows::Forms::Button());
			this->siloNumLb = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->laneTareBt4 = (gcnew System::Windows::Forms::Button());
			this->laneTareBt3 = (gcnew System::Windows::Forms::Button());
			this->laneTareBt2 = (gcnew System::Windows::Forms::Button());
			this->laneTareBt1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(8, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(45, 13);
			this->label3->TabIndex = 633;
			this->label3->Text = L"Output";
			// 
			// out16
			// 
			this->out16->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out16->Enabled = false;
			this->out16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out16->ForeColor = System::Drawing::Color::Black;
			this->out16->Location = System::Drawing::Point(1170, 374);
			this->out16->Name = L"out16";
			this->out16->Size = System::Drawing::Size(31, 24);
			this->out16->TabIndex = 625;
			this->out16->Text = L"16";
			this->out16->UseVisualStyleBackColor = false;
			this->out16->Visible = false;
			this->out16->Click += gcnew System::EventHandler(this, &IOForm::out16_Click);
			// 
			// out17
			// 
			this->out17->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out17->Enabled = false;
			this->out17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out17->ForeColor = System::Drawing::Color::Black;
			this->out17->Location = System::Drawing::Point(1124, 374);
			this->out17->Name = L"out17";
			this->out17->Size = System::Drawing::Size(31, 24);
			this->out17->TabIndex = 626;
			this->out17->Text = L"17";
			this->out17->UseVisualStyleBackColor = false;
			this->out17->Visible = false;
			this->out17->Click += gcnew System::EventHandler(this, &IOForm::out17_Click);
			// 
			// out18
			// 
			this->out18->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out18->Enabled = false;
			this->out18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out18->ForeColor = System::Drawing::Color::Black;
			this->out18->Location = System::Drawing::Point(1078, 374);
			this->out18->Name = L"out18";
			this->out18->Size = System::Drawing::Size(31, 24);
			this->out18->TabIndex = 627;
			this->out18->Text = L"18";
			this->out18->UseVisualStyleBackColor = false;
			this->out18->Visible = false;
			this->out18->Click += gcnew System::EventHandler(this, &IOForm::out18_Click);
			// 
			// out19
			// 
			this->out19->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out19->Enabled = false;
			this->out19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out19->ForeColor = System::Drawing::Color::Black;
			this->out19->Location = System::Drawing::Point(1032, 374);
			this->out19->Name = L"out19";
			this->out19->Size = System::Drawing::Size(31, 24);
			this->out19->TabIndex = 628;
			this->out19->Text = L"19";
			this->out19->UseVisualStyleBackColor = false;
			this->out19->Visible = false;
			this->out19->Click += gcnew System::EventHandler(this, &IOForm::out19_Click);
			// 
			// out20
			// 
			this->out20->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out20->Enabled = false;
			this->out20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out20->ForeColor = System::Drawing::Color::Black;
			this->out20->Location = System::Drawing::Point(947, 374);
			this->out20->Name = L"out20";
			this->out20->Size = System::Drawing::Size(31, 24);
			this->out20->TabIndex = 629;
			this->out20->Text = L"20";
			this->out20->UseVisualStyleBackColor = false;
			this->out20->Visible = false;
			this->out20->Click += gcnew System::EventHandler(this, &IOForm::out20_Click);
			// 
			// out21
			// 
			this->out21->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out21->Enabled = false;
			this->out21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out21->ForeColor = System::Drawing::Color::Black;
			this->out21->Location = System::Drawing::Point(901, 374);
			this->out21->Name = L"out21";
			this->out21->Size = System::Drawing::Size(31, 24);
			this->out21->TabIndex = 630;
			this->out21->Text = L"21";
			this->out21->UseVisualStyleBackColor = false;
			this->out21->Visible = false;
			this->out21->Click += gcnew System::EventHandler(this, &IOForm::out21_Click);
			// 
			// out23
			// 
			this->out23->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out23->Enabled = false;
			this->out23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out23->ForeColor = System::Drawing::Color::Black;
			this->out23->Location = System::Drawing::Point(809, 374);
			this->out23->Name = L"out23";
			this->out23->Size = System::Drawing::Size(31, 24);
			this->out23->TabIndex = 632;
			this->out23->Text = L"23";
			this->out23->UseVisualStyleBackColor = false;
			this->out23->Visible = false;
			this->out23->Click += gcnew System::EventHandler(this, &IOForm::out23_Click);
			// 
			// out22
			// 
			this->out22->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out22->Enabled = false;
			this->out22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out22->ForeColor = System::Drawing::Color::Black;
			this->out22->Location = System::Drawing::Point(855, 374);
			this->out22->Name = L"out22";
			this->out22->Size = System::Drawing::Size(31, 24);
			this->out22->TabIndex = 631;
			this->out22->Text = L"22";
			this->out22->UseVisualStyleBackColor = false;
			this->out22->Visible = false;
			this->out22->Click += gcnew System::EventHandler(this, &IOForm::out22_Click);
			// 
			// out12
			// 
			this->out12->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out12->Enabled = false;
			this->out12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out12->ForeColor = System::Drawing::Color::Black;
			this->out12->Location = System::Drawing::Point(160, 217);
			this->out12->Name = L"out12";
			this->out12->Size = System::Drawing::Size(31, 24);
			this->out12->TabIndex = 622;
			this->out12->Text = L"12";
			this->out12->UseVisualStyleBackColor = false;
			this->out12->Visible = false;
			this->out12->Click += gcnew System::EventHandler(this, &IOForm::out12_Click);
			// 
			// out14
			// 
			this->out14->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out14->Enabled = false;
			this->out14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out14->ForeColor = System::Drawing::Color::Black;
			this->out14->Location = System::Drawing::Point(159, 251);
			this->out14->Name = L"out14";
			this->out14->Size = System::Drawing::Size(31, 24);
			this->out14->TabIndex = 624;
			this->out14->Text = L"14";
			this->out14->UseVisualStyleBackColor = false;
			this->out14->Visible = false;
			this->out14->Click += gcnew System::EventHandler(this, &IOForm::out14_Click);
			// 
			// out15
			// 
			this->out15->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out15->Enabled = false;
			this->out15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out15->ForeColor = System::Drawing::Color::Black;
			this->out15->Location = System::Drawing::Point(125, 303);
			this->out15->Name = L"out15";
			this->out15->Size = System::Drawing::Size(31, 24);
			this->out15->TabIndex = 609;
			this->out15->Text = L"15";
			this->out15->UseVisualStyleBackColor = false;
			this->out15->Visible = false;
			this->out15->Click += gcnew System::EventHandler(this, &IOForm::out15_Click);
			// 
			// out13
			// 
			this->out13->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out13->Enabled = false;
			this->out13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out13->ForeColor = System::Drawing::Color::Black;
			this->out13->Location = System::Drawing::Point(116, 251);
			this->out13->Name = L"out13";
			this->out13->Size = System::Drawing::Size(31, 24);
			this->out13->TabIndex = 623;
			this->out13->Text = L"13";
			this->out13->UseVisualStyleBackColor = false;
			this->out13->Visible = false;
			this->out13->Click += gcnew System::EventHandler(this, &IOForm::out13_Click);
			// 
			// out0
			// 
			this->out0->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out0->Enabled = false;
			this->out0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out0->ForeColor = System::Drawing::Color::Black;
			this->out0->Location = System::Drawing::Point(12, 29);
			this->out0->Name = L"out0";
			this->out0->Size = System::Drawing::Size(31, 24);
			this->out0->TabIndex = 610;
			this->out0->Text = L"00";
			this->out0->UseVisualStyleBackColor = false;
			this->out0->Visible = false;
			this->out0->Click += gcnew System::EventHandler(this, &IOForm::out0_Click);
			// 
			// out1
			// 
			this->out1->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out1->Enabled = false;
			this->out1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out1->ForeColor = System::Drawing::Color::Black;
			this->out1->Location = System::Drawing::Point(116, 61);
			this->out1->Name = L"out1";
			this->out1->Size = System::Drawing::Size(31, 24);
			this->out1->TabIndex = 611;
			this->out1->Text = L"01";
			this->out1->UseVisualStyleBackColor = false;
			this->out1->Visible = false;
			this->out1->Click += gcnew System::EventHandler(this, &IOForm::out1_Click);
			// 
			// out11
			// 
			this->out11->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out11->Enabled = false;
			this->out11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out11->ForeColor = System::Drawing::Color::Black;
			this->out11->Location = System::Drawing::Point(116, 217);
			this->out11->Name = L"out11";
			this->out11->Size = System::Drawing::Size(31, 24);
			this->out11->TabIndex = 621;
			this->out11->Text = L"11";
			this->out11->UseVisualStyleBackColor = false;
			this->out11->Visible = false;
			this->out11->Click += gcnew System::EventHandler(this, &IOForm::out11_Click);
			// 
			// out2
			// 
			this->out2->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out2->Enabled = false;
			this->out2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out2->ForeColor = System::Drawing::Color::Black;
			this->out2->Location = System::Drawing::Point(159, 61);
			this->out2->Name = L"out2";
			this->out2->Size = System::Drawing::Size(31, 24);
			this->out2->TabIndex = 612;
			this->out2->Text = L"02";
			this->out2->UseVisualStyleBackColor = false;
			this->out2->Visible = false;
			this->out2->Click += gcnew System::EventHandler(this, &IOForm::out2_Click);
			// 
			// out10
			// 
			this->out10->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out10->Enabled = false;
			this->out10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out10->ForeColor = System::Drawing::Color::Black;
			this->out10->Location = System::Drawing::Point(159, 185);
			this->out10->Name = L"out10";
			this->out10->Size = System::Drawing::Size(31, 24);
			this->out10->TabIndex = 620;
			this->out10->Text = L"10";
			this->out10->UseVisualStyleBackColor = false;
			this->out10->Visible = false;
			this->out10->Click += gcnew System::EventHandler(this, &IOForm::out10_Click);
			// 
			// out3
			// 
			this->out3->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out3->Enabled = false;
			this->out3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out3->ForeColor = System::Drawing::Color::Black;
			this->out3->Location = System::Drawing::Point(116, 93);
			this->out3->Name = L"out3";
			this->out3->Size = System::Drawing::Size(31, 24);
			this->out3->TabIndex = 613;
			this->out3->Text = L"03";
			this->out3->UseVisualStyleBackColor = false;
			this->out3->Visible = false;
			this->out3->Click += gcnew System::EventHandler(this, &IOForm::out3_Click);
			// 
			// out9
			// 
			this->out9->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out9->Enabled = false;
			this->out9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out9->ForeColor = System::Drawing::Color::Black;
			this->out9->Location = System::Drawing::Point(116, 185);
			this->out9->Name = L"out9";
			this->out9->Size = System::Drawing::Size(31, 24);
			this->out9->TabIndex = 619;
			this->out9->Text = L"09";
			this->out9->UseVisualStyleBackColor = false;
			this->out9->Visible = false;
			this->out9->Click += gcnew System::EventHandler(this, &IOForm::out9_Click);
			// 
			// out4
			// 
			this->out4->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out4->Enabled = false;
			this->out4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out4->ForeColor = System::Drawing::Color::Black;
			this->out4->Location = System::Drawing::Point(159, 93);
			this->out4->Name = L"out4";
			this->out4->Size = System::Drawing::Size(31, 24);
			this->out4->TabIndex = 614;
			this->out4->Text = L"04";
			this->out4->UseVisualStyleBackColor = false;
			this->out4->Visible = false;
			this->out4->Click += gcnew System::EventHandler(this, &IOForm::out4_Click);
			// 
			// out8
			// 
			this->out8->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out8->Enabled = false;
			this->out8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out8->ForeColor = System::Drawing::Color::Black;
			this->out8->Location = System::Drawing::Point(159, 154);
			this->out8->Name = L"out8";
			this->out8->Size = System::Drawing::Size(31, 24);
			this->out8->TabIndex = 618;
			this->out8->Text = L"08";
			this->out8->UseVisualStyleBackColor = false;
			this->out8->Visible = false;
			this->out8->Click += gcnew System::EventHandler(this, &IOForm::out8_Click);
			// 
			// out5
			// 
			this->out5->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out5->Enabled = false;
			this->out5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out5->ForeColor = System::Drawing::Color::Black;
			this->out5->Location = System::Drawing::Point(116, 125);
			this->out5->Name = L"out5";
			this->out5->Size = System::Drawing::Size(31, 24);
			this->out5->TabIndex = 615;
			this->out5->Text = L"05";
			this->out5->UseVisualStyleBackColor = false;
			this->out5->Visible = false;
			this->out5->Click += gcnew System::EventHandler(this, &IOForm::out5_Click);
			// 
			// out7
			// 
			this->out7->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out7->Enabled = false;
			this->out7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out7->ForeColor = System::Drawing::Color::Black;
			this->out7->Location = System::Drawing::Point(116, 154);
			this->out7->Name = L"out7";
			this->out7->Size = System::Drawing::Size(31, 24);
			this->out7->TabIndex = 617;
			this->out7->Text = L"07";
			this->out7->UseVisualStyleBackColor = false;
			this->out7->Visible = false;
			this->out7->Click += gcnew System::EventHandler(this, &IOForm::out7_Click);
			// 
			// out6
			// 
			this->out6->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out6->Enabled = false;
			this->out6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out6->ForeColor = System::Drawing::Color::Black;
			this->out6->Location = System::Drawing::Point(159, 125);
			this->out6->Name = L"out6";
			this->out6->Size = System::Drawing::Size(31, 24);
			this->out6->TabIndex = 616;
			this->out6->Text = L"06";
			this->out6->UseVisualStyleBackColor = false;
			this->out6->Visible = false;
			this->out6->Click += gcnew System::EventHandler(this, &IOForm::out6_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(259, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(36, 13);
			this->label7->TabIndex = 666;
			this->label7->Text = L"Input";
			// 
			// in16
			// 
			this->in16->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in16->Enabled = false;
			this->in16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in16->ForeColor = System::Drawing::Color::Black;
			this->in16->Location = System::Drawing::Point(1079, 412);
			this->in16->Name = L"in16";
			this->in16->Size = System::Drawing::Size(30, 24);
			this->in16->TabIndex = 658;
			this->in16->Text = L" 16";
			this->in16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in16->Visible = false;
			// 
			// in17
			// 
			this->in17->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in17->Enabled = false;
			this->in17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in17->ForeColor = System::Drawing::Color::Black;
			this->in17->Location = System::Drawing::Point(1033, 412);
			this->in17->Name = L"in17";
			this->in17->Size = System::Drawing::Size(30, 24);
			this->in17->TabIndex = 659;
			this->in17->Text = L" 17";
			this->in17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in17->Visible = false;
			// 
			// in18
			// 
			this->in18->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in18->Enabled = false;
			this->in18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in18->ForeColor = System::Drawing::Color::Black;
			this->in18->Location = System::Drawing::Point(948, 412);
			this->in18->Name = L"in18";
			this->in18->Size = System::Drawing::Size(30, 24);
			this->in18->TabIndex = 660;
			this->in18->Text = L" 18";
			this->in18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in18->Visible = false;
			// 
			// in19
			// 
			this->in19->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in19->Enabled = false;
			this->in19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in19->ForeColor = System::Drawing::Color::Black;
			this->in19->Location = System::Drawing::Point(902, 412);
			this->in19->Name = L"in19";
			this->in19->Size = System::Drawing::Size(30, 24);
			this->in19->TabIndex = 661;
			this->in19->Text = L" 19";
			this->in19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in19->Visible = false;
			// 
			// in21
			// 
			this->in21->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in21->Enabled = false;
			this->in21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in21->ForeColor = System::Drawing::Color::Black;
			this->in21->Location = System::Drawing::Point(810, 412);
			this->in21->Name = L"in21";
			this->in21->Size = System::Drawing::Size(30, 24);
			this->in21->TabIndex = 663;
			this->in21->Text = L" 21";
			this->in21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in21->Visible = false;
			// 
			// in22
			// 
			this->in22->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in22->Enabled = false;
			this->in22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in22->ForeColor = System::Drawing::Color::Black;
			this->in22->Location = System::Drawing::Point(764, 412);
			this->in22->Name = L"in22";
			this->in22->Size = System::Drawing::Size(30, 24);
			this->in22->TabIndex = 664;
			this->in22->Text = L" 22";
			this->in22->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in22->Visible = false;
			// 
			// in20
			// 
			this->in20->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in20->Enabled = false;
			this->in20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in20->ForeColor = System::Drawing::Color::Black;
			this->in20->Location = System::Drawing::Point(856, 412);
			this->in20->Name = L"in20";
			this->in20->Size = System::Drawing::Size(30, 24);
			this->in20->TabIndex = 662;
			this->in20->Text = L" 20";
			this->in20->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in20->Visible = false;
			// 
			// in23
			// 
			this->in23->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in23->Enabled = false;
			this->in23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in23->ForeColor = System::Drawing::Color::Black;
			this->in23->Location = System::Drawing::Point(718, 412);
			this->in23->Name = L"in23";
			this->in23->Size = System::Drawing::Size(30, 24);
			this->in23->TabIndex = 665;
			this->in23->Text = L" 23";
			this->in23->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in23->Visible = false;
			// 
			// in24
			// 
			this->in24->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in24->Enabled = false;
			this->in24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in24->ForeColor = System::Drawing::Color::Black;
			this->in24->Location = System::Drawing::Point(672, 412);
			this->in24->Name = L"in24";
			this->in24->Size = System::Drawing::Size(30, 24);
			this->in24->TabIndex = 650;
			this->in24->Text = L" 24";
			this->in24->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in24->Visible = false;
			// 
			// in25
			// 
			this->in25->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in25->Enabled = false;
			this->in25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in25->ForeColor = System::Drawing::Color::Black;
			this->in25->Location = System::Drawing::Point(626, 412);
			this->in25->Name = L"in25";
			this->in25->Size = System::Drawing::Size(30, 24);
			this->in25->TabIndex = 651;
			this->in25->Text = L" 25";
			this->in25->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in25->Visible = false;
			// 
			// in26
			// 
			this->in26->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in26->Enabled = false;
			this->in26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in26->ForeColor = System::Drawing::Color::Black;
			this->in26->Location = System::Drawing::Point(580, 412);
			this->in26->Name = L"in26";
			this->in26->Size = System::Drawing::Size(30, 24);
			this->in26->TabIndex = 652;
			this->in26->Text = L" 26";
			this->in26->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in26->Visible = false;
			// 
			// in27
			// 
			this->in27->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in27->Enabled = false;
			this->in27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in27->ForeColor = System::Drawing::Color::Black;
			this->in27->Location = System::Drawing::Point(534, 412);
			this->in27->Name = L"in27";
			this->in27->Size = System::Drawing::Size(30, 24);
			this->in27->TabIndex = 654;
			this->in27->Text = L" 27";
			this->in27->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in27->Visible = false;
			// 
			// in28
			// 
			this->in28->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in28->Enabled = false;
			this->in28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in28->ForeColor = System::Drawing::Color::Black;
			this->in28->Location = System::Drawing::Point(488, 412);
			this->in28->Name = L"in28";
			this->in28->Size = System::Drawing::Size(30, 24);
			this->in28->TabIndex = 655;
			this->in28->Text = L" 28";
			this->in28->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in28->Visible = false;
			// 
			// in29
			// 
			this->in29->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in29->Enabled = false;
			this->in29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in29->ForeColor = System::Drawing::Color::Black;
			this->in29->Location = System::Drawing::Point(442, 412);
			this->in29->Name = L"in29";
			this->in29->Size = System::Drawing::Size(30, 24);
			this->in29->TabIndex = 653;
			this->in29->Text = L" 29";
			this->in29->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in29->Visible = false;
			// 
			// in30
			// 
			this->in30->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in30->Enabled = false;
			this->in30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in30->ForeColor = System::Drawing::Color::Black;
			this->in30->Location = System::Drawing::Point(397, 412);
			this->in30->Name = L"in30";
			this->in30->Size = System::Drawing::Size(30, 24);
			this->in30->TabIndex = 656;
			this->in30->Text = L" 30";
			this->in30->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in30->Visible = false;
			// 
			// in0
			// 
			this->in0->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in0->Enabled = false;
			this->in0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in0->ForeColor = System::Drawing::Color::Black;
			this->in0->Location = System::Drawing::Point(259, 29);
			this->in0->Name = L"in0";
			this->in0->Size = System::Drawing::Size(30, 24);
			this->in0->TabIndex = 642;
			this->in0->Text = L" 00";
			this->in0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in0->Visible = false;
			// 
			// in1
			// 
			this->in1->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in1->Enabled = false;
			this->in1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in1->ForeColor = System::Drawing::Color::Black;
			this->in1->Location = System::Drawing::Point(309, 52);
			this->in1->Name = L"in1";
			this->in1->Size = System::Drawing::Size(30, 24);
			this->in1->TabIndex = 643;
			this->in1->Text = L" 01";
			this->in1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in1->Visible = false;
			// 
			// in2
			// 
			this->in2->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in2->Enabled = false;
			this->in2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in2->ForeColor = System::Drawing::Color::Black;
			this->in2->Location = System::Drawing::Point(309, 87);
			this->in2->Name = L"in2";
			this->in2->Size = System::Drawing::Size(30, 24);
			this->in2->TabIndex = 644;
			this->in2->Text = L" 02";
			this->in2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in2->Visible = false;
			// 
			// in3
			// 
			this->in3->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in3->Enabled = false;
			this->in3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in3->ForeColor = System::Drawing::Color::Black;
			this->in3->Location = System::Drawing::Point(309, 119);
			this->in3->Name = L"in3";
			this->in3->Size = System::Drawing::Size(30, 24);
			this->in3->TabIndex = 645;
			this->in3->Text = L" 03";
			this->in3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in3->Visible = false;
			// 
			// in5
			// 
			this->in5->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in5->Enabled = false;
			this->in5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in5->ForeColor = System::Drawing::Color::Black;
			this->in5->Location = System::Drawing::Point(309, 183);
			this->in5->Name = L"in5";
			this->in5->Size = System::Drawing::Size(30, 24);
			this->in5->TabIndex = 647;
			this->in5->Text = L" 05";
			this->in5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in5->Visible = false;
			// 
			// in6
			// 
			this->in6->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in6->Enabled = false;
			this->in6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in6->ForeColor = System::Drawing::Color::Black;
			this->in6->Location = System::Drawing::Point(309, 215);
			this->in6->Name = L"in6";
			this->in6->Size = System::Drawing::Size(30, 24);
			this->in6->TabIndex = 648;
			this->in6->Text = L" 06";
			this->in6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in6->Visible = false;
			// 
			// in4
			// 
			this->in4->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in4->Enabled = false;
			this->in4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in4->ForeColor = System::Drawing::Color::Black;
			this->in4->Location = System::Drawing::Point(309, 151);
			this->in4->Name = L"in4";
			this->in4->Size = System::Drawing::Size(30, 24);
			this->in4->TabIndex = 646;
			this->in4->Text = L" 04";
			this->in4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in4->Visible = false;
			// 
			// in7
			// 
			this->in7->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in7->Enabled = false;
			this->in7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in7->ForeColor = System::Drawing::Color::Black;
			this->in7->Location = System::Drawing::Point(309, 247);
			this->in7->Name = L"in7";
			this->in7->Size = System::Drawing::Size(30, 24);
			this->in7->TabIndex = 649;
			this->in7->Text = L" 07";
			this->in7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in7->Visible = false;
			// 
			// in8
			// 
			this->in8->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in8->Enabled = false;
			this->in8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in8->ForeColor = System::Drawing::Color::Black;
			this->in8->Location = System::Drawing::Point(352, 70);
			this->in8->Name = L"in8";
			this->in8->Size = System::Drawing::Size(30, 24);
			this->in8->TabIndex = 634;
			this->in8->Text = L" 08";
			this->in8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in8->Visible = false;
			// 
			// in9
			// 
			this->in9->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in9->Enabled = false;
			this->in9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in9->ForeColor = System::Drawing::Color::Black;
			this->in9->Location = System::Drawing::Point(352, 131);
			this->in9->Name = L"in9";
			this->in9->Size = System::Drawing::Size(30, 24);
			this->in9->TabIndex = 635;
			this->in9->Text = L" 09";
			this->in9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in9->Visible = false;
			// 
			// in10
			// 
			this->in10->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in10->Enabled = false;
			this->in10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in10->ForeColor = System::Drawing::Color::Black;
			this->in10->Location = System::Drawing::Point(352, 195);
			this->in10->Name = L"in10";
			this->in10->Size = System::Drawing::Size(30, 24);
			this->in10->TabIndex = 636;
			this->in10->Text = L" 10";
			this->in10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in10->Visible = false;
			// 
			// in11
			// 
			this->in11->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in11->Enabled = false;
			this->in11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in11->ForeColor = System::Drawing::Color::Black;
			this->in11->Location = System::Drawing::Point(352, 247);
			this->in11->Name = L"in11";
			this->in11->Size = System::Drawing::Size(30, 24);
			this->in11->TabIndex = 638;
			this->in11->Text = L" 11";
			this->in11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in11->Visible = false;
			// 
			// in12
			// 
			this->in12->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in12->Enabled = false;
			this->in12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in12->ForeColor = System::Drawing::Color::Black;
			this->in12->Location = System::Drawing::Point(324, 303);
			this->in12->Name = L"in12";
			this->in12->Size = System::Drawing::Size(30, 24);
			this->in12->TabIndex = 639;
			this->in12->Text = L" 12";
			this->in12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in12->Visible = false;
			// 
			// in13
			// 
			this->in13->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in13->Enabled = false;
			this->in13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in13->ForeColor = System::Drawing::Color::Black;
			this->in13->Location = System::Drawing::Point(324, 336);
			this->in13->Name = L"in13";
			this->in13->Size = System::Drawing::Size(30, 24);
			this->in13->TabIndex = 637;
			this->in13->Text = L" 13";
			this->in13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in13->Visible = false;
			// 
			// in14
			// 
			this->in14->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in14->Enabled = false;
			this->in14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in14->ForeColor = System::Drawing::Color::Black;
			this->in14->Location = System::Drawing::Point(1171, 412);
			this->in14->Name = L"in14";
			this->in14->Size = System::Drawing::Size(30, 24);
			this->in14->TabIndex = 640;
			this->in14->Text = L" 14";
			this->in14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in14->Visible = false;
			// 
			// in15
			// 
			this->in15->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in15->Enabled = false;
			this->in15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in15->ForeColor = System::Drawing::Color::Black;
			this->in15->Location = System::Drawing::Point(1125, 412);
			this->in15->Name = L"in15";
			this->in15->Size = System::Drawing::Size(30, 24);
			this->in15->TabIndex = 641;
			this->in15->Text = L" 15";
			this->in15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in15->Visible = false;
			// 
			// out28
			// 
			this->out28->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out28->Enabled = false;
			this->out28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out28->ForeColor = System::Drawing::Color::Black;
			this->out28->Location = System::Drawing::Point(579, 374);
			this->out28->Name = L"out28";
			this->out28->Size = System::Drawing::Size(31, 24);
			this->out28->TabIndex = 672;
			this->out28->Text = L"28";
			this->out28->UseVisualStyleBackColor = false;
			this->out28->Visible = false;
			this->out28->Click += gcnew System::EventHandler(this, &IOForm::out28_Click);
			// 
			// out30
			// 
			this->out30->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out30->Enabled = false;
			this->out30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out30->ForeColor = System::Drawing::Color::Black;
			this->out30->Location = System::Drawing::Point(487, 374);
			this->out30->Name = L"out30";
			this->out30->Size = System::Drawing::Size(31, 24);
			this->out30->TabIndex = 674;
			this->out30->Text = L"30";
			this->out30->UseVisualStyleBackColor = false;
			this->out30->Visible = false;
			this->out30->Click += gcnew System::EventHandler(this, &IOForm::out30_Click);
			// 
			// out31
			// 
			this->out31->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out31->Enabled = false;
			this->out31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out31->ForeColor = System::Drawing::Color::Black;
			this->out31->Location = System::Drawing::Point(440, 374);
			this->out31->Name = L"out31";
			this->out31->Size = System::Drawing::Size(31, 24);
			this->out31->TabIndex = 667;
			this->out31->Text = L"31";
			this->out31->UseVisualStyleBackColor = false;
			this->out31->Visible = false;
			this->out31->Click += gcnew System::EventHandler(this, &IOForm::out31_Click);
			// 
			// out29
			// 
			this->out29->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out29->Enabled = false;
			this->out29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out29->ForeColor = System::Drawing::Color::Black;
			this->out29->Location = System::Drawing::Point(532, 374);
			this->out29->Name = L"out29";
			this->out29->Size = System::Drawing::Size(31, 24);
			this->out29->TabIndex = 673;
			this->out29->Text = L"29";
			this->out29->UseVisualStyleBackColor = false;
			this->out29->Visible = false;
			this->out29->Click += gcnew System::EventHandler(this, &IOForm::out29_Click);
			// 
			// out27
			// 
			this->out27->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out27->Enabled = false;
			this->out27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out27->ForeColor = System::Drawing::Color::Black;
			this->out27->Location = System::Drawing::Point(625, 374);
			this->out27->Name = L"out27";
			this->out27->Size = System::Drawing::Size(31, 24);
			this->out27->TabIndex = 671;
			this->out27->Text = L"27";
			this->out27->UseVisualStyleBackColor = false;
			this->out27->Visible = false;
			this->out27->Click += gcnew System::EventHandler(this, &IOForm::out27_Click);
			// 
			// out26
			// 
			this->out26->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out26->Enabled = false;
			this->out26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out26->ForeColor = System::Drawing::Color::Black;
			this->out26->Location = System::Drawing::Point(671, 374);
			this->out26->Name = L"out26";
			this->out26->Size = System::Drawing::Size(31, 24);
			this->out26->TabIndex = 670;
			this->out26->Text = L"26";
			this->out26->UseVisualStyleBackColor = false;
			this->out26->Visible = false;
			this->out26->Click += gcnew System::EventHandler(this, &IOForm::out26_Click);
			// 
			// out25
			// 
			this->out25->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out25->Enabled = false;
			this->out25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out25->ForeColor = System::Drawing::Color::Black;
			this->out25->Location = System::Drawing::Point(717, 374);
			this->out25->Name = L"out25";
			this->out25->Size = System::Drawing::Size(31, 24);
			this->out25->TabIndex = 669;
			this->out25->Text = L"25";
			this->out25->UseVisualStyleBackColor = false;
			this->out25->Visible = false;
			this->out25->Click += gcnew System::EventHandler(this, &IOForm::out25_Click);
			// 
			// out24
			// 
			this->out24->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out24->Enabled = false;
			this->out24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out24->ForeColor = System::Drawing::Color::Black;
			this->out24->Location = System::Drawing::Point(763, 374);
			this->out24->Name = L"out24";
			this->out24->Size = System::Drawing::Size(31, 24);
			this->out24->TabIndex = 668;
			this->out24->Text = L"24";
			this->out24->UseVisualStyleBackColor = false;
			this->out24->Visible = false;
			this->out24->Click += gcnew System::EventHandler(this, &IOForm::out24_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &IOForm::timer1_Tick);
			// 
			// holdBt1
			// 
			this->holdBt1->AllowDrop = true;
			this->holdBt1->AutoEllipsis = true;
			this->holdBt1->Location = System::Drawing::Point(584, 49);
			this->holdBt1->Name = L"holdBt1";
			this->holdBt1->Size = System::Drawing::Size(71, 23);
			this->holdBt1->TabIndex = 675;
			this->holdBt1->Text = L"HOLD 1";
			this->holdBt1->UseVisualStyleBackColor = true;
			this->holdBt1->Visible = false;
			this->holdBt1->Click += gcnew System::EventHandler(this, &IOForm::holdBt1_Click);
			// 
			// RInpBt1
			// 
			this->RInpBt1->AllowDrop = true;
			this->RInpBt1->AutoEllipsis = true;
			this->RInpBt1->Location = System::Drawing::Point(495, 534);
			this->RInpBt1->Name = L"RInpBt1";
			this->RInpBt1->Size = System::Drawing::Size(71, 23);
			this->RInpBt1->TabIndex = 676;
			this->RInpBt1->Text = L"DReady_I1";
			this->RInpBt1->UseVisualStyleBackColor = true;
			this->RInpBt1->Visible = false;
			this->RInpBt1->Click += gcnew System::EventHandler(this, &IOForm::ERHInpBt1_Click);
			// 
			// RInpBtIR
			// 
			this->RInpBtIR->AllowDrop = true;
			this->RInpBtIR->AutoEllipsis = true;
			this->RInpBtIR->Location = System::Drawing::Point(495, 654);
			this->RInpBtIR->Name = L"RInpBtIR";
			this->RInpBtIR->Size = System::Drawing::Size(71, 23);
			this->RInpBtIR->TabIndex = 677;
			this->RInpBtIR->Text = L"DReady_IR";
			this->RInpBtIR->UseVisualStyleBackColor = true;
			this->RInpBtIR->Visible = false;
			this->RInpBtIR->Click += gcnew System::EventHandler(this, &IOForm::HInpBt1_Click);
			// 
			// DInpBt8
			// 
			this->DInpBt8->AllowDrop = true;
			this->DInpBt8->AutoEllipsis = true;
			this->DInpBt8->Location = System::Drawing::Point(498, 219);
			this->DInpBt8->Name = L"DInpBt8";
			this->DInpBt8->Size = System::Drawing::Size(71, 23);
			this->DInpBt8->TabIndex = 678;
			this->DInpBt8->Text = L"Done Inp 8";
			this->DInpBt8->UseVisualStyleBackColor = true;
			this->DInpBt8->Visible = false;
			this->DInpBt8->Click += gcnew System::EventHandler(this, &IOForm::DInpBt8_Click);
			// 
			// DInpBtIR
			// 
			this->DInpBtIR->AllowDrop = true;
			this->DInpBtIR->AutoEllipsis = true;
			this->DInpBtIR->Location = System::Drawing::Point(498, 253);
			this->DInpBtIR->Name = L"DInpBtIR";
			this->DInpBtIR->Size = System::Drawing::Size(71, 23);
			this->DInpBtIR->TabIndex = 682;
			this->DInpBtIR->Text = L"Done IR";
			this->DInpBtIR->UseVisualStyleBackColor = true;
			this->DInpBtIR->Visible = false;
			this->DInpBtIR->Click += gcnew System::EventHandler(this, &IOForm::DInpBtIR_Click);
			// 
			// DInpBt1
			// 
			this->DInpBt1->AllowDrop = true;
			this->DInpBt1->AutoEllipsis = true;
			this->DInpBt1->Location = System::Drawing::Point(498, 49);
			this->DInpBt1->Name = L"DInpBt1";
			this->DInpBt1->Size = System::Drawing::Size(71, 23);
			this->DInpBt1->TabIndex = 681;
			this->DInpBt1->Text = L"Done Inp 1";
			this->DInpBt1->UseVisualStyleBackColor = true;
			this->DInpBt1->Visible = false;
			this->DInpBt1->Click += gcnew System::EventHandler(this, &IOForm::DInpBt1_Click);
			// 
			// RInpBt2
			// 
			this->RInpBt2->AllowDrop = true;
			this->RInpBt2->AutoEllipsis = true;
			this->RInpBt2->Location = System::Drawing::Point(495, 568);
			this->RInpBt2->Name = L"RInpBt2";
			this->RInpBt2->Size = System::Drawing::Size(71, 23);
			this->RInpBt2->TabIndex = 680;
			this->RInpBt2->Text = L"DReady_I2";
			this->RInpBt2->UseVisualStyleBackColor = true;
			this->RInpBt2->Visible = false;
			this->RInpBt2->Click += gcnew System::EventHandler(this, &IOForm::ERHInpBt2_Click);
			// 
			// holdBt2
			// 
			this->holdBt2->AllowDrop = true;
			this->holdBt2->AutoEllipsis = true;
			this->holdBt2->Location = System::Drawing::Point(584, 83);
			this->holdBt2->Name = L"holdBt2";
			this->holdBt2->Size = System::Drawing::Size(71, 23);
			this->holdBt2->TabIndex = 679;
			this->holdBt2->Text = L"HOLD 2";
			this->holdBt2->UseVisualStyleBackColor = true;
			this->holdBt2->Visible = false;
			this->holdBt2->Click += gcnew System::EventHandler(this, &IOForm::holdBt2_Click);
			// 
			// holdBtIR
			// 
			this->holdBtIR->AllowDrop = true;
			this->holdBtIR->AutoEllipsis = true;
			this->holdBtIR->Location = System::Drawing::Point(584, 253);
			this->holdBtIR->Name = L"holdBtIR";
			this->holdBtIR->Size = System::Drawing::Size(71, 23);
			this->holdBtIR->TabIndex = 686;
			this->holdBtIR->Text = L"HOLD IR";
			this->holdBtIR->UseVisualStyleBackColor = true;
			this->holdBtIR->Visible = false;
			this->holdBtIR->Click += gcnew System::EventHandler(this, &IOForm::holdBtIR_Click);
			// 
			// DInpBt2
			// 
			this->DInpBt2->AllowDrop = true;
			this->DInpBt2->AutoEllipsis = true;
			this->DInpBt2->Location = System::Drawing::Point(498, 83);
			this->DInpBt2->Name = L"DInpBt2";
			this->DInpBt2->Size = System::Drawing::Size(71, 23);
			this->DInpBt2->TabIndex = 685;
			this->DInpBt2->Text = L"Done Inp 2";
			this->DInpBt2->UseVisualStyleBackColor = true;
			this->DInpBt2->Visible = false;
			this->DInpBt2->Click += gcnew System::EventHandler(this, &IOForm::DInpBt2_Click);
			// 
			// RInpBt4
			// 
			this->RInpBt4->AllowDrop = true;
			this->RInpBt4->AutoEllipsis = true;
			this->RInpBt4->Location = System::Drawing::Point(495, 602);
			this->RInpBt4->Name = L"RInpBt4";
			this->RInpBt4->Size = System::Drawing::Size(71, 23);
			this->RInpBt4->TabIndex = 684;
			this->RInpBt4->Text = L"DReady_I4";
			this->RInpBt4->UseVisualStyleBackColor = true;
			this->RInpBt4->Visible = false;
			this->RInpBt4->Click += gcnew System::EventHandler(this, &IOForm::ERHInpBt3_Click);
			// 
			// holdBt4
			// 
			this->holdBt4->AllowDrop = true;
			this->holdBt4->AutoEllipsis = true;
			this->holdBt4->Location = System::Drawing::Point(584, 117);
			this->holdBt4->Name = L"holdBt4";
			this->holdBt4->Size = System::Drawing::Size(71, 23);
			this->holdBt4->TabIndex = 683;
			this->holdBt4->Text = L"HOLD 4";
			this->holdBt4->UseVisualStyleBackColor = true;
			this->holdBt4->Visible = false;
			this->holdBt4->Click += gcnew System::EventHandler(this, &IOForm::holdBt4_Click);
			// 
			// LInpBt4
			// 
			this->LInpBt4->AllowDrop = true;
			this->LInpBt4->AutoEllipsis = true;
			this->LInpBt4->Location = System::Drawing::Point(428, 678);
			this->LInpBt4->Name = L"LInpBt4";
			this->LInpBt4->Size = System::Drawing::Size(71, 23);
			this->LInpBt4->TabIndex = 690;
			this->LInpBt4->Text = L"Low Inp 4";
			this->LInpBt4->UseVisualStyleBackColor = true;
			this->LInpBt4->Visible = false;
			// 
			// DInpBt4
			// 
			this->DInpBt4->AllowDrop = true;
			this->DInpBt4->AutoEllipsis = true;
			this->DInpBt4->Location = System::Drawing::Point(498, 117);
			this->DInpBt4->Name = L"DInpBt4";
			this->DInpBt4->Size = System::Drawing::Size(71, 23);
			this->DInpBt4->TabIndex = 689;
			this->DInpBt4->Text = L"Done Inp 4";
			this->DInpBt4->UseVisualStyleBackColor = true;
			this->DInpBt4->Visible = false;
			this->DInpBt4->Click += gcnew System::EventHandler(this, &IOForm::DInpBt4_Click);
			// 
			// RInpBt5
			// 
			this->RInpBt5->AllowDrop = true;
			this->RInpBt5->AutoEllipsis = true;
			this->RInpBt5->Location = System::Drawing::Point(495, 636);
			this->RInpBt5->Name = L"RInpBt5";
			this->RInpBt5->Size = System::Drawing::Size(71, 23);
			this->RInpBt5->TabIndex = 688;
			this->RInpBt5->Text = L"DReady_I5";
			this->RInpBt5->UseVisualStyleBackColor = true;
			this->RInpBt5->Visible = false;
			this->RInpBt5->Click += gcnew System::EventHandler(this, &IOForm::ERHInpBt4_Click);
			// 
			// holdBt5
			// 
			this->holdBt5->AllowDrop = true;
			this->holdBt5->AutoEllipsis = true;
			this->holdBt5->Location = System::Drawing::Point(584, 151);
			this->holdBt5->Name = L"holdBt5";
			this->holdBt5->Size = System::Drawing::Size(71, 23);
			this->holdBt5->TabIndex = 687;
			this->holdBt5->Text = L"HOLD 5";
			this->holdBt5->UseVisualStyleBackColor = true;
			this->holdBt5->Visible = false;
			this->holdBt5->Click += gcnew System::EventHandler(this, &IOForm::holdBt5_Click);
			// 
			// LInpBt5
			// 
			this->LInpBt5->AllowDrop = true;
			this->LInpBt5->AutoEllipsis = true;
			this->LInpBt5->Location = System::Drawing::Point(517, 678);
			this->LInpBt5->Name = L"LInpBt5";
			this->LInpBt5->Size = System::Drawing::Size(71, 23);
			this->LInpBt5->TabIndex = 694;
			this->LInpBt5->Text = L"Low Inp 5";
			this->LInpBt5->UseVisualStyleBackColor = true;
			this->LInpBt5->Visible = false;
			// 
			// DInpBt5
			// 
			this->DInpBt5->AllowDrop = true;
			this->DInpBt5->AutoEllipsis = true;
			this->DInpBt5->Location = System::Drawing::Point(498, 151);
			this->DInpBt5->Name = L"DInpBt5";
			this->DInpBt5->Size = System::Drawing::Size(71, 23);
			this->DInpBt5->TabIndex = 693;
			this->DInpBt5->Text = L"Done Inp 5";
			this->DInpBt5->UseVisualStyleBackColor = true;
			this->DInpBt5->Visible = false;
			this->DInpBt5->Click += gcnew System::EventHandler(this, &IOForm::DInpBt5_Click);
			// 
			// RInpBt7
			// 
			this->RInpBt7->AllowDrop = true;
			this->RInpBt7->AutoEllipsis = true;
			this->RInpBt7->Location = System::Drawing::Point(495, 670);
			this->RInpBt7->Name = L"RInpBt7";
			this->RInpBt7->Size = System::Drawing::Size(71, 23);
			this->RInpBt7->TabIndex = 692;
			this->RInpBt7->Text = L"DReady_I7";
			this->RInpBt7->UseVisualStyleBackColor = true;
			this->RInpBt7->Visible = false;
			this->RInpBt7->Click += gcnew System::EventHandler(this, &IOForm::ERHInpBt5_Click);
			// 
			// holdBt7
			// 
			this->holdBt7->AllowDrop = true;
			this->holdBt7->AutoEllipsis = true;
			this->holdBt7->Location = System::Drawing::Point(584, 185);
			this->holdBt7->Name = L"holdBt7";
			this->holdBt7->Size = System::Drawing::Size(71, 23);
			this->holdBt7->TabIndex = 691;
			this->holdBt7->Text = L"HOLD 7";
			this->holdBt7->UseVisualStyleBackColor = true;
			this->holdBt7->Visible = false;
			this->holdBt7->Click += gcnew System::EventHandler(this, &IOForm::holdBt7_Click);
			// 
			// LInpBt6
			// 
			this->LInpBt6->AllowDrop = true;
			this->LInpBt6->AutoEllipsis = true;
			this->LInpBt6->Location = System::Drawing::Point(607, 594);
			this->LInpBt6->Name = L"LInpBt6";
			this->LInpBt6->Size = System::Drawing::Size(71, 23);
			this->LInpBt6->TabIndex = 698;
			this->LInpBt6->Text = L"LInpBt6";
			this->LInpBt6->UseVisualStyleBackColor = true;
			this->LInpBt6->Visible = false;
			// 
			// DInpBt7
			// 
			this->DInpBt7->AllowDrop = true;
			this->DInpBt7->AutoEllipsis = true;
			this->DInpBt7->Location = System::Drawing::Point(498, 185);
			this->DInpBt7->Name = L"DInpBt7";
			this->DInpBt7->Size = System::Drawing::Size(71, 23);
			this->DInpBt7->TabIndex = 697;
			this->DInpBt7->Text = L"Done Inp 7";
			this->DInpBt7->UseVisualStyleBackColor = true;
			this->DInpBt7->Visible = false;
			this->DInpBt7->Click += gcnew System::EventHandler(this, &IOForm::DInpBt7_Click);
			// 
			// RInpBt8
			// 
			this->RInpBt8->AllowDrop = true;
			this->RInpBt8->AutoEllipsis = true;
			this->RInpBt8->Location = System::Drawing::Point(495, 620);
			this->RInpBt8->Name = L"RInpBt8";
			this->RInpBt8->Size = System::Drawing::Size(71, 23);
			this->RInpBt8->TabIndex = 696;
			this->RInpBt8->Text = L"DReady_I8";
			this->RInpBt8->UseVisualStyleBackColor = true;
			this->RInpBt8->Visible = false;
			this->RInpBt8->Click += gcnew System::EventHandler(this, &IOForm::ERHInpBt6_Click);
			// 
			// holdBt8
			// 
			this->holdBt8->AllowDrop = true;
			this->holdBt8->AutoEllipsis = true;
			this->holdBt8->Location = System::Drawing::Point(584, 219);
			this->holdBt8->Name = L"holdBt8";
			this->holdBt8->Size = System::Drawing::Size(71, 23);
			this->holdBt8->TabIndex = 695;
			this->holdBt8->Text = L"HOLD 8";
			this->holdBt8->UseVisualStyleBackColor = true;
			this->holdBt8->Visible = false;
			this->holdBt8->Click += gcnew System::EventHandler(this, &IOForm::RoHeadInpBt6_Click);
			// 
			// out38
			// 
			this->out38->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out38->Enabled = false;
			this->out38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out38->ForeColor = System::Drawing::Color::Black;
			this->out38->Location = System::Drawing::Point(126, 374);
			this->out38->Name = L"out38";
			this->out38->Size = System::Drawing::Size(31, 24);
			this->out38->TabIndex = 705;
			this->out38->Text = L"38";
			this->out38->UseVisualStyleBackColor = false;
			this->out38->Visible = false;
			this->out38->Click += gcnew System::EventHandler(this, &IOForm::out38_Click);
			// 
			// out40
			// 
			this->out40->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out40->Enabled = false;
			this->out40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out40->ForeColor = System::Drawing::Color::Black;
			this->out40->Location = System::Drawing::Point(74, 61);
			this->out40->Name = L"out40";
			this->out40->Size = System::Drawing::Size(31, 24);
			this->out40->TabIndex = 707;
			this->out40->Text = L"40";
			this->out40->UseVisualStyleBackColor = false;
			this->out40->Visible = false;
			this->out40->Click += gcnew System::EventHandler(this, &IOForm::out40_Click);
			// 
			// out39
			// 
			this->out39->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out39->Enabled = false;
			this->out39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out39->ForeColor = System::Drawing::Color::Black;
			this->out39->Location = System::Drawing::Point(125, 337);
			this->out39->Name = L"out39";
			this->out39->Size = System::Drawing::Size(31, 24);
			this->out39->TabIndex = 706;
			this->out39->Text = L"39";
			this->out39->UseVisualStyleBackColor = false;
			this->out39->Visible = false;
			this->out39->Click += gcnew System::EventHandler(this, &IOForm::out39_Click);
			// 
			// out37
			// 
			this->out37->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out37->Enabled = false;
			this->out37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out37->ForeColor = System::Drawing::Color::Black;
			this->out37->Location = System::Drawing::Point(168, 374);
			this->out37->Name = L"out37";
			this->out37->Size = System::Drawing::Size(31, 24);
			this->out37->TabIndex = 704;
			this->out37->Text = L"37";
			this->out37->UseVisualStyleBackColor = false;
			this->out37->Visible = false;
			this->out37->Click += gcnew System::EventHandler(this, &IOForm::out37_Click);
			// 
			// out36
			// 
			this->out36->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out36->Enabled = false;
			this->out36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out36->ForeColor = System::Drawing::Color::Black;
			this->out36->Location = System::Drawing::Point(214, 374);
			this->out36->Name = L"out36";
			this->out36->Size = System::Drawing::Size(31, 24);
			this->out36->TabIndex = 703;
			this->out36->Text = L"36";
			this->out36->UseVisualStyleBackColor = false;
			this->out36->Visible = false;
			this->out36->Click += gcnew System::EventHandler(this, &IOForm::out36_Click);
			// 
			// out35
			// 
			this->out35->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out35->Enabled = false;
			this->out35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out35->ForeColor = System::Drawing::Color::Black;
			this->out35->Location = System::Drawing::Point(257, 374);
			this->out35->Name = L"out35";
			this->out35->Size = System::Drawing::Size(31, 24);
			this->out35->TabIndex = 702;
			this->out35->Text = L"35";
			this->out35->UseVisualStyleBackColor = false;
			this->out35->Visible = false;
			this->out35->Click += gcnew System::EventHandler(this, &IOForm::out35_Click);
			// 
			// out34
			// 
			this->out34->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out34->Enabled = false;
			this->out34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out34->ForeColor = System::Drawing::Color::Black;
			this->out34->Location = System::Drawing::Point(303, 374);
			this->out34->Name = L"out34";
			this->out34->Size = System::Drawing::Size(31, 24);
			this->out34->TabIndex = 701;
			this->out34->Text = L"34";
			this->out34->UseVisualStyleBackColor = false;
			this->out34->Visible = false;
			this->out34->Click += gcnew System::EventHandler(this, &IOForm::out34_Click);
			// 
			// out33
			// 
			this->out33->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out33->Enabled = false;
			this->out33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out33->ForeColor = System::Drawing::Color::Black;
			this->out33->Location = System::Drawing::Point(352, 374);
			this->out33->Name = L"out33";
			this->out33->Size = System::Drawing::Size(31, 24);
			this->out33->TabIndex = 700;
			this->out33->Text = L"33";
			this->out33->UseVisualStyleBackColor = false;
			this->out33->Visible = false;
			this->out33->Click += gcnew System::EventHandler(this, &IOForm::out33_Click);
			// 
			// out32
			// 
			this->out32->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out32->Enabled = false;
			this->out32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out32->ForeColor = System::Drawing::Color::Black;
			this->out32->Location = System::Drawing::Point(397, 374);
			this->out32->Name = L"out32";
			this->out32->Size = System::Drawing::Size(31, 24);
			this->out32->TabIndex = 699;
			this->out32->Text = L"32";
			this->out32->UseVisualStyleBackColor = false;
			this->out32->Visible = false;
			this->out32->Click += gcnew System::EventHandler(this, &IOForm::out32_Click);
			// 
			// out58
			// 
			this->out58->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out58->Enabled = false;
			this->out58->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out58->ForeColor = System::Drawing::Color::Black;
			this->out58->Location = System::Drawing::Point(73, 601);
			this->out58->Name = L"out58";
			this->out58->Size = System::Drawing::Size(31, 24);
			this->out58->TabIndex = 725;
			this->out58->Text = L"58";
			this->out58->UseVisualStyleBackColor = false;
			this->out58->Visible = false;
			// 
			// out60
			// 
			this->out60->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out60->Enabled = false;
			this->out60->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out60->ForeColor = System::Drawing::Color::Black;
			this->out60->Location = System::Drawing::Point(159, 601);
			this->out60->Name = L"out60";
			this->out60->Size = System::Drawing::Size(31, 24);
			this->out60->TabIndex = 727;
			this->out60->Text = L"60";
			this->out60->UseVisualStyleBackColor = false;
			this->out60->Visible = false;
			// 
			// out59
			// 
			this->out59->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out59->Enabled = false;
			this->out59->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out59->ForeColor = System::Drawing::Color::Black;
			this->out59->Location = System::Drawing::Point(116, 601);
			this->out59->Name = L"out59";
			this->out59->Size = System::Drawing::Size(31, 24);
			this->out59->TabIndex = 726;
			this->out59->Text = L"59";
			this->out59->UseVisualStyleBackColor = false;
			this->out59->Visible = false;
			// 
			// out57
			// 
			this->out57->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out57->Enabled = false;
			this->out57->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out57->ForeColor = System::Drawing::Color::Black;
			this->out57->Location = System::Drawing::Point(30, 601);
			this->out57->Name = L"out57";
			this->out57->Size = System::Drawing::Size(31, 24);
			this->out57->TabIndex = 724;
			this->out57->Text = L"57";
			this->out57->UseVisualStyleBackColor = false;
			this->out57->Visible = false;
			// 
			// out56
			// 
			this->out56->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out56->Enabled = false;
			this->out56->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out56->ForeColor = System::Drawing::Color::Black;
			this->out56->Location = System::Drawing::Point(331, 571);
			this->out56->Name = L"out56";
			this->out56->Size = System::Drawing::Size(31, 24);
			this->out56->TabIndex = 723;
			this->out56->Text = L"56";
			this->out56->UseVisualStyleBackColor = false;
			this->out56->Visible = false;
			// 
			// out55
			// 
			this->out55->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out55->Enabled = false;
			this->out55->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out55->ForeColor = System::Drawing::Color::Black;
			this->out55->Location = System::Drawing::Point(288, 571);
			this->out55->Name = L"out55";
			this->out55->Size = System::Drawing::Size(31, 24);
			this->out55->TabIndex = 722;
			this->out55->Text = L"55";
			this->out55->UseVisualStyleBackColor = false;
			this->out55->Visible = false;
			// 
			// out54
			// 
			this->out54->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out54->Enabled = false;
			this->out54->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out54->ForeColor = System::Drawing::Color::Black;
			this->out54->Location = System::Drawing::Point(245, 571);
			this->out54->Name = L"out54";
			this->out54->Size = System::Drawing::Size(31, 24);
			this->out54->TabIndex = 721;
			this->out54->Text = L"54";
			this->out54->UseVisualStyleBackColor = false;
			this->out54->Visible = false;
			// 
			// out53
			// 
			this->out53->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out53->Enabled = false;
			this->out53->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out53->ForeColor = System::Drawing::Color::Black;
			this->out53->Location = System::Drawing::Point(202, 571);
			this->out53->Name = L"out53";
			this->out53->Size = System::Drawing::Size(31, 24);
			this->out53->TabIndex = 720;
			this->out53->Text = L"53";
			this->out53->UseVisualStyleBackColor = false;
			this->out53->Visible = false;
			// 
			// out52
			// 
			this->out52->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out52->Enabled = false;
			this->out52->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out52->ForeColor = System::Drawing::Color::Black;
			this->out52->Location = System::Drawing::Point(159, 571);
			this->out52->Name = L"out52";
			this->out52->Size = System::Drawing::Size(31, 24);
			this->out52->TabIndex = 719;
			this->out52->Text = L"52";
			this->out52->UseVisualStyleBackColor = false;
			this->out52->Visible = false;
			// 
			// out48
			// 
			this->out48->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out48->Enabled = false;
			this->out48->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out48->ForeColor = System::Drawing::Color::Black;
			this->out48->Location = System::Drawing::Point(331, 541);
			this->out48->Name = L"out48";
			this->out48->Size = System::Drawing::Size(31, 24);
			this->out48->TabIndex = 716;
			this->out48->Text = L"48";
			this->out48->UseVisualStyleBackColor = false;
			this->out48->Visible = false;
			this->out48->Click += gcnew System::EventHandler(this, &IOForm::out48_Click);
			// 
			// out50
			// 
			this->out50->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out50->Enabled = false;
			this->out50->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out50->ForeColor = System::Drawing::Color::Black;
			this->out50->Location = System::Drawing::Point(73, 571);
			this->out50->Name = L"out50";
			this->out50->Size = System::Drawing::Size(31, 24);
			this->out50->TabIndex = 718;
			this->out50->Text = L"50";
			this->out50->UseVisualStyleBackColor = false;
			this->out50->Visible = false;
			this->out50->Click += gcnew System::EventHandler(this, &IOForm::button11_Click);
			// 
			// out51
			// 
			this->out51->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out51->Enabled = false;
			this->out51->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out51->ForeColor = System::Drawing::Color::Black;
			this->out51->Location = System::Drawing::Point(116, 571);
			this->out51->Name = L"out51";
			this->out51->Size = System::Drawing::Size(31, 24);
			this->out51->TabIndex = 711;
			this->out51->Text = L"51";
			this->out51->UseVisualStyleBackColor = false;
			this->out51->Visible = false;
			// 
			// out49
			// 
			this->out49->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out49->Enabled = false;
			this->out49->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out49->ForeColor = System::Drawing::Color::Black;
			this->out49->Location = System::Drawing::Point(30, 571);
			this->out49->Name = L"out49";
			this->out49->Size = System::Drawing::Size(31, 24);
			this->out49->TabIndex = 717;
			this->out49->Text = L"49";
			this->out49->UseVisualStyleBackColor = false;
			this->out49->Visible = false;
			// 
			// out47
			// 
			this->out47->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out47->Enabled = false;
			this->out47->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out47->ForeColor = System::Drawing::Color::Black;
			this->out47->Location = System::Drawing::Point(288, 541);
			this->out47->Name = L"out47";
			this->out47->Size = System::Drawing::Size(31, 24);
			this->out47->TabIndex = 715;
			this->out47->Text = L"47";
			this->out47->UseVisualStyleBackColor = false;
			this->out47->Visible = false;
			this->out47->Click += gcnew System::EventHandler(this, &IOForm::out47_Click);
			// 
			// out46
			// 
			this->out46->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out46->Enabled = false;
			this->out46->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out46->ForeColor = System::Drawing::Color::Black;
			this->out46->Location = System::Drawing::Point(74, 251);
			this->out46->Name = L"out46";
			this->out46->Size = System::Drawing::Size(31, 24);
			this->out46->TabIndex = 714;
			this->out46->Text = L"46";
			this->out46->UseVisualStyleBackColor = false;
			this->out46->Visible = false;
			this->out46->Click += gcnew System::EventHandler(this, &IOForm::out46_Click);
			// 
			// out45
			// 
			this->out45->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out45->Enabled = false;
			this->out45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out45->ForeColor = System::Drawing::Color::Black;
			this->out45->Location = System::Drawing::Point(74, 217);
			this->out45->Name = L"out45";
			this->out45->Size = System::Drawing::Size(31, 24);
			this->out45->TabIndex = 713;
			this->out45->Text = L"45";
			this->out45->UseVisualStyleBackColor = false;
			this->out45->Visible = false;
			this->out45->Click += gcnew System::EventHandler(this, &IOForm::out45_Click);
			// 
			// out44
			// 
			this->out44->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out44->Enabled = false;
			this->out44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out44->ForeColor = System::Drawing::Color::Black;
			this->out44->Location = System::Drawing::Point(74, 185);
			this->out44->Name = L"out44";
			this->out44->Size = System::Drawing::Size(31, 24);
			this->out44->TabIndex = 712;
			this->out44->Text = L"44";
			this->out44->UseVisualStyleBackColor = false;
			this->out44->Visible = false;
			this->out44->Click += gcnew System::EventHandler(this, &IOForm::out44_Click);
			// 
			// out41
			// 
			this->out41->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out41->Enabled = false;
			this->out41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out41->ForeColor = System::Drawing::Color::Black;
			this->out41->Location = System::Drawing::Point(74, 93);
			this->out41->Name = L"out41";
			this->out41->Size = System::Drawing::Size(31, 24);
			this->out41->TabIndex = 708;
			this->out41->Text = L"41";
			this->out41->UseVisualStyleBackColor = false;
			this->out41->Visible = false;
			this->out41->Click += gcnew System::EventHandler(this, &IOForm::out41_Click);
			// 
			// out43
			// 
			this->out43->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out43->Enabled = false;
			this->out43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out43->ForeColor = System::Drawing::Color::Black;
			this->out43->Location = System::Drawing::Point(74, 154);
			this->out43->Name = L"out43";
			this->out43->Size = System::Drawing::Size(31, 24);
			this->out43->TabIndex = 710;
			this->out43->Text = L"43";
			this->out43->UseVisualStyleBackColor = false;
			this->out43->Visible = false;
			this->out43->Click += gcnew System::EventHandler(this, &IOForm::out43_Click);
			// 
			// out42
			// 
			this->out42->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out42->Enabled = false;
			this->out42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out42->ForeColor = System::Drawing::Color::Black;
			this->out42->Location = System::Drawing::Point(74, 125);
			this->out42->Name = L"out42";
			this->out42->Size = System::Drawing::Size(31, 24);
			this->out42->TabIndex = 709;
			this->out42->Text = L"42";
			this->out42->UseVisualStyleBackColor = false;
			this->out42->Visible = false;
			this->out42->Click += gcnew System::EventHandler(this, &IOForm::out42_Click);
			// 
			// out78
			// 
			this->out78->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out78->Enabled = false;
			this->out78->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out78->ForeColor = System::Drawing::Color::Black;
			this->out78->Location = System::Drawing::Point(245, 660);
			this->out78->Name = L"out78";
			this->out78->Size = System::Drawing::Size(31, 24);
			this->out78->TabIndex = 745;
			this->out78->Text = L"78";
			this->out78->UseVisualStyleBackColor = false;
			this->out78->Visible = false;
			// 
			// out80
			// 
			this->out80->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out80->Enabled = false;
			this->out80->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out80->ForeColor = System::Drawing::Color::Black;
			this->out80->Location = System::Drawing::Point(331, 660);
			this->out80->Name = L"out80";
			this->out80->Size = System::Drawing::Size(31, 24);
			this->out80->TabIndex = 747;
			this->out80->Text = L"80";
			this->out80->UseVisualStyleBackColor = false;
			this->out80->Visible = false;
			// 
			// out79
			// 
			this->out79->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out79->Enabled = false;
			this->out79->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out79->ForeColor = System::Drawing::Color::Black;
			this->out79->Location = System::Drawing::Point(288, 660);
			this->out79->Name = L"out79";
			this->out79->Size = System::Drawing::Size(31, 24);
			this->out79->TabIndex = 746;
			this->out79->Text = L"79";
			this->out79->UseVisualStyleBackColor = false;
			this->out79->Visible = false;
			// 
			// out77
			// 
			this->out77->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out77->Enabled = false;
			this->out77->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out77->ForeColor = System::Drawing::Color::Black;
			this->out77->Location = System::Drawing::Point(202, 660);
			this->out77->Name = L"out77";
			this->out77->Size = System::Drawing::Size(31, 24);
			this->out77->TabIndex = 744;
			this->out77->Text = L"77";
			this->out77->UseVisualStyleBackColor = false;
			this->out77->Visible = false;
			// 
			// out76
			// 
			this->out76->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out76->Enabled = false;
			this->out76->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out76->ForeColor = System::Drawing::Color::Black;
			this->out76->Location = System::Drawing::Point(159, 660);
			this->out76->Name = L"out76";
			this->out76->Size = System::Drawing::Size(31, 24);
			this->out76->TabIndex = 743;
			this->out76->Text = L"76";
			this->out76->UseVisualStyleBackColor = false;
			this->out76->Visible = false;
			// 
			// out75
			// 
			this->out75->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out75->Enabled = false;
			this->out75->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out75->ForeColor = System::Drawing::Color::Black;
			this->out75->Location = System::Drawing::Point(116, 660);
			this->out75->Name = L"out75";
			this->out75->Size = System::Drawing::Size(31, 24);
			this->out75->TabIndex = 742;
			this->out75->Text = L"75";
			this->out75->UseVisualStyleBackColor = false;
			this->out75->Visible = false;
			// 
			// out74
			// 
			this->out74->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out74->Enabled = false;
			this->out74->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out74->ForeColor = System::Drawing::Color::Black;
			this->out74->Location = System::Drawing::Point(73, 660);
			this->out74->Name = L"out74";
			this->out74->Size = System::Drawing::Size(31, 24);
			this->out74->TabIndex = 741;
			this->out74->Text = L"74";
			this->out74->UseVisualStyleBackColor = false;
			this->out74->Visible = false;
			// 
			// out73
			// 
			this->out73->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out73->Enabled = false;
			this->out73->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out73->ForeColor = System::Drawing::Color::Black;
			this->out73->Location = System::Drawing::Point(30, 660);
			this->out73->Name = L"out73";
			this->out73->Size = System::Drawing::Size(31, 24);
			this->out73->TabIndex = 740;
			this->out73->Text = L"73";
			this->out73->UseVisualStyleBackColor = false;
			this->out73->Visible = false;
			// 
			// out72
			// 
			this->out72->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out72->Enabled = false;
			this->out72->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out72->ForeColor = System::Drawing::Color::Black;
			this->out72->Location = System::Drawing::Point(331, 630);
			this->out72->Name = L"out72";
			this->out72->Size = System::Drawing::Size(31, 24);
			this->out72->TabIndex = 739;
			this->out72->Text = L"72";
			this->out72->UseVisualStyleBackColor = false;
			this->out72->Visible = false;
			// 
			// out68
			// 
			this->out68->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out68->Enabled = false;
			this->out68->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out68->ForeColor = System::Drawing::Color::Black;
			this->out68->Location = System::Drawing::Point(159, 630);
			this->out68->Name = L"out68";
			this->out68->Size = System::Drawing::Size(31, 24);
			this->out68->TabIndex = 736;
			this->out68->Text = L"68";
			this->out68->UseVisualStyleBackColor = false;
			this->out68->Visible = false;
			// 
			// out70
			// 
			this->out70->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out70->Enabled = false;
			this->out70->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out70->ForeColor = System::Drawing::Color::Black;
			this->out70->Location = System::Drawing::Point(245, 630);
			this->out70->Name = L"out70";
			this->out70->Size = System::Drawing::Size(31, 24);
			this->out70->TabIndex = 738;
			this->out70->Text = L"70";
			this->out70->UseVisualStyleBackColor = false;
			this->out70->Visible = false;
			// 
			// out71
			// 
			this->out71->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out71->Enabled = false;
			this->out71->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out71->ForeColor = System::Drawing::Color::Black;
			this->out71->Location = System::Drawing::Point(288, 630);
			this->out71->Name = L"out71";
			this->out71->Size = System::Drawing::Size(31, 24);
			this->out71->TabIndex = 731;
			this->out71->Text = L"71";
			this->out71->UseVisualStyleBackColor = false;
			this->out71->Visible = false;
			// 
			// out69
			// 
			this->out69->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out69->Enabled = false;
			this->out69->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out69->ForeColor = System::Drawing::Color::Black;
			this->out69->Location = System::Drawing::Point(202, 630);
			this->out69->Name = L"out69";
			this->out69->Size = System::Drawing::Size(31, 24);
			this->out69->TabIndex = 737;
			this->out69->Text = L"69";
			this->out69->UseVisualStyleBackColor = false;
			this->out69->Visible = false;
			// 
			// out67
			// 
			this->out67->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out67->Enabled = false;
			this->out67->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out67->ForeColor = System::Drawing::Color::Black;
			this->out67->Location = System::Drawing::Point(116, 630);
			this->out67->Name = L"out67";
			this->out67->Size = System::Drawing::Size(31, 24);
			this->out67->TabIndex = 735;
			this->out67->Text = L"67";
			this->out67->UseVisualStyleBackColor = false;
			this->out67->Visible = false;
			// 
			// out66
			// 
			this->out66->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out66->Enabled = false;
			this->out66->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out66->ForeColor = System::Drawing::Color::Black;
			this->out66->Location = System::Drawing::Point(73, 630);
			this->out66->Name = L"out66";
			this->out66->Size = System::Drawing::Size(31, 24);
			this->out66->TabIndex = 734;
			this->out66->Text = L"66";
			this->out66->UseVisualStyleBackColor = false;
			this->out66->Visible = false;
			// 
			// out65
			// 
			this->out65->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out65->Enabled = false;
			this->out65->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out65->ForeColor = System::Drawing::Color::Black;
			this->out65->Location = System::Drawing::Point(30, 630);
			this->out65->Name = L"out65";
			this->out65->Size = System::Drawing::Size(31, 24);
			this->out65->TabIndex = 733;
			this->out65->Text = L"65";
			this->out65->UseVisualStyleBackColor = false;
			this->out65->Visible = false;
			// 
			// out64
			// 
			this->out64->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out64->Enabled = false;
			this->out64->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out64->ForeColor = System::Drawing::Color::Black;
			this->out64->Location = System::Drawing::Point(331, 600);
			this->out64->Name = L"out64";
			this->out64->Size = System::Drawing::Size(31, 24);
			this->out64->TabIndex = 732;
			this->out64->Text = L"64";
			this->out64->UseVisualStyleBackColor = false;
			this->out64->Visible = false;
			// 
			// out61
			// 
			this->out61->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out61->Enabled = false;
			this->out61->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out61->ForeColor = System::Drawing::Color::Black;
			this->out61->Location = System::Drawing::Point(202, 600);
			this->out61->Name = L"out61";
			this->out61->Size = System::Drawing::Size(31, 24);
			this->out61->TabIndex = 728;
			this->out61->Text = L"61";
			this->out61->UseVisualStyleBackColor = false;
			this->out61->Visible = false;
			// 
			// out63
			// 
			this->out63->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out63->Enabled = false;
			this->out63->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out63->ForeColor = System::Drawing::Color::Black;
			this->out63->Location = System::Drawing::Point(288, 600);
			this->out63->Name = L"out63";
			this->out63->Size = System::Drawing::Size(31, 24);
			this->out63->TabIndex = 730;
			this->out63->Text = L"63";
			this->out63->UseVisualStyleBackColor = false;
			this->out63->Visible = false;
			// 
			// out62
			// 
			this->out62->BackColor = System::Drawing::Color::LightSteelBlue;
			this->out62->Enabled = false;
			this->out62->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->out62->ForeColor = System::Drawing::Color::Black;
			this->out62->Location = System::Drawing::Point(245, 600);
			this->out62->Name = L"out62";
			this->out62->Size = System::Drawing::Size(31, 24);
			this->out62->TabIndex = 729;
			this->out62->Text = L"62";
			this->out62->UseVisualStyleBackColor = false;
			this->out62->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(76, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 748;
			this->label1->Text = L"DrO";
			this->label1->Click += gcnew System::EventHandler(this, &IOForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(119, 40);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(25, 13);
			this->label2->TabIndex = 749;
			this->label2->Text = L"HO";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(162, 40);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(25, 13);
			this->label4->TabIndex = 750;
			this->label4->Text = L"DO";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(8, 379);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(105, 13);
			this->label6->TabIndex = 752;
			this->label6->Text = L"Target Bit Output";
			// 
			// enableIOCb
			// 
			this->enableIOCb->AutoSize = true;
			this->enableIOCb->Location = System::Drawing::Point(81, 12);
			this->enableIOCb->Name = L"enableIOCb";
			this->enableIOCb->Size = System::Drawing::Size(118, 17);
			this->enableIOCb->TabIndex = 756;
			this->enableIOCb->Text = L"Enable Output Test";
			this->enableIOCb->UseVisualStyleBackColor = true;
			this->enableIOCb->Click += gcnew System::EventHandler(this, &IOForm::enableIOCb_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(399, 29);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(37, 13);
			this->label5->TabIndex = 759;
			this->label5->Text = L"TareI";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(352, 29);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(20, 13);
			this->label8->TabIndex = 758;
			this->label8->Text = L"HI";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(309, 29);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(20, 13);
			this->label9->TabIndex = 757;
			this->label9->Text = L"DI";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(12, 66);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(30, 13);
			this->label10->TabIndex = 760;
			this->label10->Text = L"Silo1";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(12, 98);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(30, 13);
			this->label11->TabIndex = 761;
			this->label11->Text = L"Silo2";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(12, 130);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(30, 13);
			this->label12->TabIndex = 762;
			this->label12->Text = L"Silo4";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(12, 162);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(30, 13);
			this->label13->TabIndex = 763;
			this->label13->Text = L"Silo5";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(12, 194);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(30, 13);
			this->label14->TabIndex = 764;
			this->label14->Text = L"Silo7";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(12, 226);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(30, 13);
			this->label15->TabIndex = 765;
			this->label15->Text = L"Silo8";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(12, 258);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(36, 13);
			this->label16->TabIndex = 766;
			this->label16->Text = L"Silo10";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(492, 21);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(96, 16);
			this->label17->TabIndex = 767;
			this->label17->Text = L"DEMO TEST";
			// 
			// targetNumLb
			// 
			this->targetNumLb->AutoSize = true;
			this->targetNumLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->targetNumLb->Location = System::Drawing::Point(219, 489);
			this->targetNumLb->Name = L"targetNumLb";
			this->targetNumLb->Size = System::Drawing::Size(74, 15);
			this->targetNumLb->TabIndex = 768;
			this->targetNumLb->Text = L"targetNum";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(15, 308);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(101, 13);
			this->label18->TabIndex = 769;
			this->label18->Text = L"Send Target Output";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(17, 342);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(93, 13);
			this->label19->TabIndex = 770;
			this->label19->Text = L"Keep Alive Output";
			// 
			// in31
			// 
			this->in31->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in31->Enabled = false;
			this->in31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in31->ForeColor = System::Drawing::Color::Black;
			this->in31->Location = System::Drawing::Point(353, 412);
			this->in31->Name = L"in31";
			this->in31->Size = System::Drawing::Size(30, 24);
			this->in31->TabIndex = 771;
			this->in31->Text = L"31";
			this->in31->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in31->Visible = false;
			// 
			// in32
			// 
			this->in32->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in32->Enabled = false;
			this->in32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in32->ForeColor = System::Drawing::Color::Black;
			this->in32->Location = System::Drawing::Point(304, 412);
			this->in32->Name = L"in32";
			this->in32->Size = System::Drawing::Size(30, 24);
			this->in32->TabIndex = 772;
			this->in32->Text = L"32";
			this->in32->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in32->Visible = false;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(187, 310);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(114, 13);
			this->label20->TabIndex = 773;
			this->label20->Text = L"Recevied Target Input";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(189, 342);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(85, 13);
			this->label21->TabIndex = 774;
			this->label21->Text = L"Keep Alive Input";
			// 
			// RInpBt
			// 
			this->RInpBt->AllowDrop = true;
			this->RInpBt->AutoEllipsis = true;
			this->RInpBt->Location = System::Drawing::Point(498, 298);
			this->RInpBt->Name = L"RInpBt";
			this->RInpBt->Size = System::Drawing::Size(90, 23);
			this->RInpBt->TabIndex = 775;
			this->RInpBt->Text = L"Recevied Inp";
			this->RInpBt->UseVisualStyleBackColor = true;
			this->RInpBt->Visible = false;
			this->RInpBt->Click += gcnew System::EventHandler(this, &IOForm::RInpBt_Click);
			// 
			// KInpBt
			// 
			this->KInpBt->AllowDrop = true;
			this->KInpBt->AutoEllipsis = true;
			this->KInpBt->Location = System::Drawing::Point(498, 337);
			this->KInpBt->Name = L"KInpBt";
			this->KInpBt->Size = System::Drawing::Size(90, 23);
			this->KInpBt->TabIndex = 776;
			this->KInpBt->Text = L"Keep Alive Inp";
			this->KInpBt->UseVisualStyleBackColor = true;
			this->KInpBt->Visible = false;
			this->KInpBt->Click += gcnew System::EventHandler(this, &IOForm::KInpBt_Click);
			// 
			// inp12Bt
			// 
			this->inp12Bt->AllowDrop = true;
			this->inp12Bt->AutoEllipsis = true;
			this->inp12Bt->Location = System::Drawing::Point(1170, 452);
			this->inp12Bt->Name = L"inp12Bt";
			this->inp12Bt->Size = System::Drawing::Size(31, 23);
			this->inp12Bt->TabIndex = 777;
			this->inp12Bt->Text = L"14";
			this->inp12Bt->UseVisualStyleBackColor = true;
			this->inp12Bt->Visible = false;
			this->inp12Bt->Click += gcnew System::EventHandler(this, &IOForm::inp12Bt_Click);
			// 
			// inp13Bt
			// 
			this->inp13Bt->AllowDrop = true;
			this->inp13Bt->AutoEllipsis = true;
			this->inp13Bt->Location = System::Drawing::Point(1128, 451);
			this->inp13Bt->Name = L"inp13Bt";
			this->inp13Bt->Size = System::Drawing::Size(31, 23);
			this->inp13Bt->TabIndex = 778;
			this->inp13Bt->Text = L"15";
			this->inp13Bt->UseVisualStyleBackColor = true;
			this->inp13Bt->Visible = false;
			this->inp13Bt->Click += gcnew System::EventHandler(this, &IOForm::inp13Bt_Click);
			// 
			// inp14Bt
			// 
			this->inp14Bt->AllowDrop = true;
			this->inp14Bt->AutoEllipsis = true;
			this->inp14Bt->Location = System::Drawing::Point(1078, 452);
			this->inp14Bt->Name = L"inp14Bt";
			this->inp14Bt->Size = System::Drawing::Size(31, 23);
			this->inp14Bt->TabIndex = 779;
			this->inp14Bt->Text = L"16";
			this->inp14Bt->UseVisualStyleBackColor = true;
			this->inp14Bt->Visible = false;
			this->inp14Bt->Click += gcnew System::EventHandler(this, &IOForm::inp14Bt_Click);
			// 
			// inp15Bt
			// 
			this->inp15Bt->AllowDrop = true;
			this->inp15Bt->AutoEllipsis = true;
			this->inp15Bt->Location = System::Drawing::Point(1032, 452);
			this->inp15Bt->Name = L"inp15Bt";
			this->inp15Bt->Size = System::Drawing::Size(31, 23);
			this->inp15Bt->TabIndex = 780;
			this->inp15Bt->Text = L"17";
			this->inp15Bt->UseVisualStyleBackColor = true;
			this->inp15Bt->Visible = false;
			this->inp15Bt->Click += gcnew System::EventHandler(this, &IOForm::inp15Bt_Click);
			// 
			// inp16Bt
			// 
			this->inp16Bt->AllowDrop = true;
			this->inp16Bt->AutoEllipsis = true;
			this->inp16Bt->Location = System::Drawing::Point(947, 451);
			this->inp16Bt->Name = L"inp16Bt";
			this->inp16Bt->Size = System::Drawing::Size(31, 23);
			this->inp16Bt->TabIndex = 781;
			this->inp16Bt->Text = L"18";
			this->inp16Bt->UseVisualStyleBackColor = true;
			this->inp16Bt->Visible = false;
			this->inp16Bt->Click += gcnew System::EventHandler(this, &IOForm::inp16Bt_Click);
			// 
			// inp21Bt
			// 
			this->inp21Bt->AllowDrop = true;
			this->inp21Bt->AutoEllipsis = true;
			this->inp21Bt->Location = System::Drawing::Point(714, 452);
			this->inp21Bt->Name = L"inp21Bt";
			this->inp21Bt->Size = System::Drawing::Size(31, 23);
			this->inp21Bt->TabIndex = 786;
			this->inp21Bt->Text = L"23";
			this->inp21Bt->UseVisualStyleBackColor = true;
			this->inp21Bt->Visible = false;
			this->inp21Bt->Click += gcnew System::EventHandler(this, &IOForm::inp21Bt_Click);
			// 
			// inp20Bt
			// 
			this->inp20Bt->AllowDrop = true;
			this->inp20Bt->AutoEllipsis = true;
			this->inp20Bt->Location = System::Drawing::Point(760, 452);
			this->inp20Bt->Name = L"inp20Bt";
			this->inp20Bt->Size = System::Drawing::Size(31, 23);
			this->inp20Bt->TabIndex = 785;
			this->inp20Bt->Text = L"22";
			this->inp20Bt->UseVisualStyleBackColor = true;
			this->inp20Bt->Visible = false;
			this->inp20Bt->Click += gcnew System::EventHandler(this, &IOForm::inp20Bt_Click);
			// 
			// inp19Bt
			// 
			this->inp19Bt->AllowDrop = true;
			this->inp19Bt->AutoEllipsis = true;
			this->inp19Bt->Location = System::Drawing::Point(808, 452);
			this->inp19Bt->Name = L"inp19Bt";
			this->inp19Bt->Size = System::Drawing::Size(31, 23);
			this->inp19Bt->TabIndex = 784;
			this->inp19Bt->Text = L"21";
			this->inp19Bt->UseVisualStyleBackColor = true;
			this->inp19Bt->Visible = false;
			this->inp19Bt->Click += gcnew System::EventHandler(this, &IOForm::inp19Bt_Click);
			// 
			// inp18Bt
			// 
			this->inp18Bt->AllowDrop = true;
			this->inp18Bt->AutoEllipsis = true;
			this->inp18Bt->Location = System::Drawing::Point(855, 452);
			this->inp18Bt->Name = L"inp18Bt";
			this->inp18Bt->Size = System::Drawing::Size(31, 23);
			this->inp18Bt->TabIndex = 783;
			this->inp18Bt->Text = L"20";
			this->inp18Bt->UseVisualStyleBackColor = true;
			this->inp18Bt->Visible = false;
			this->inp18Bt->Click += gcnew System::EventHandler(this, &IOForm::inp18Bt_Click);
			// 
			// inp17Bt
			// 
			this->inp17Bt->AllowDrop = true;
			this->inp17Bt->AutoEllipsis = true;
			this->inp17Bt->Location = System::Drawing::Point(903, 451);
			this->inp17Bt->Name = L"inp17Bt";
			this->inp17Bt->Size = System::Drawing::Size(31, 23);
			this->inp17Bt->TabIndex = 782;
			this->inp17Bt->Text = L"19";
			this->inp17Bt->UseVisualStyleBackColor = true;
			this->inp17Bt->Visible = false;
			this->inp17Bt->Click += gcnew System::EventHandler(this, &IOForm::inp17Bt_Click);
			// 
			// inp26Bt
			// 
			this->inp26Bt->AllowDrop = true;
			this->inp26Bt->AutoEllipsis = true;
			this->inp26Bt->Location = System::Drawing::Point(485, 452);
			this->inp26Bt->Name = L"inp26Bt";
			this->inp26Bt->Size = System::Drawing::Size(31, 23);
			this->inp26Bt->TabIndex = 791;
			this->inp26Bt->Text = L"28";
			this->inp26Bt->UseVisualStyleBackColor = true;
			this->inp26Bt->Visible = false;
			this->inp26Bt->Click += gcnew System::EventHandler(this, &IOForm::inp26Bt_Click);
			// 
			// inp25Bt
			// 
			this->inp25Bt->AllowDrop = true;
			this->inp25Bt->AutoEllipsis = true;
			this->inp25Bt->Location = System::Drawing::Point(531, 452);
			this->inp25Bt->Name = L"inp25Bt";
			this->inp25Bt->Size = System::Drawing::Size(31, 23);
			this->inp25Bt->TabIndex = 790;
			this->inp25Bt->Text = L"27";
			this->inp25Bt->UseVisualStyleBackColor = true;
			this->inp25Bt->Visible = false;
			this->inp25Bt->Click += gcnew System::EventHandler(this, &IOForm::inp25Bt_Click);
			// 
			// inp24Bt
			// 
			this->inp24Bt->AllowDrop = true;
			this->inp24Bt->AutoEllipsis = true;
			this->inp24Bt->Location = System::Drawing::Point(576, 452);
			this->inp24Bt->Name = L"inp24Bt";
			this->inp24Bt->Size = System::Drawing::Size(31, 23);
			this->inp24Bt->TabIndex = 789;
			this->inp24Bt->Text = L"26";
			this->inp24Bt->UseVisualStyleBackColor = true;
			this->inp24Bt->Visible = false;
			this->inp24Bt->Click += gcnew System::EventHandler(this, &IOForm::inp24Bt_Click);
			// 
			// inp23Bt
			// 
			this->inp23Bt->AllowDrop = true;
			this->inp23Bt->AutoEllipsis = true;
			this->inp23Bt->Location = System::Drawing::Point(621, 452);
			this->inp23Bt->Name = L"inp23Bt";
			this->inp23Bt->Size = System::Drawing::Size(31, 23);
			this->inp23Bt->TabIndex = 788;
			this->inp23Bt->Text = L"25";
			this->inp23Bt->UseVisualStyleBackColor = true;
			this->inp23Bt->Visible = false;
			this->inp23Bt->Click += gcnew System::EventHandler(this, &IOForm::inp23Bt_Click);
			// 
			// inp22Bt
			// 
			this->inp22Bt->AllowDrop = true;
			this->inp22Bt->AutoEllipsis = true;
			this->inp22Bt->Location = System::Drawing::Point(668, 452);
			this->inp22Bt->Name = L"inp22Bt";
			this->inp22Bt->Size = System::Drawing::Size(31, 23);
			this->inp22Bt->TabIndex = 787;
			this->inp22Bt->Text = L"24";
			this->inp22Bt->UseVisualStyleBackColor = true;
			this->inp22Bt->Visible = false;
			this->inp22Bt->Click += gcnew System::EventHandler(this, &IOForm::inp22Bt_Click);
			// 
			// inp30Bt
			// 
			this->inp30Bt->AllowDrop = true;
			this->inp30Bt->AutoEllipsis = true;
			this->inp30Bt->Location = System::Drawing::Point(305, 452);
			this->inp30Bt->Name = L"inp30Bt";
			this->inp30Bt->Size = System::Drawing::Size(31, 23);
			this->inp30Bt->TabIndex = 795;
			this->inp30Bt->Text = L"32";
			this->inp30Bt->UseVisualStyleBackColor = true;
			this->inp30Bt->Visible = false;
			this->inp30Bt->Click += gcnew System::EventHandler(this, &IOForm::inp30Bt_Click);
			// 
			// inp29Bt
			// 
			this->inp29Bt->AllowDrop = true;
			this->inp29Bt->AutoEllipsis = true;
			this->inp29Bt->Location = System::Drawing::Point(348, 452);
			this->inp29Bt->Name = L"inp29Bt";
			this->inp29Bt->Size = System::Drawing::Size(31, 23);
			this->inp29Bt->TabIndex = 794;
			this->inp29Bt->Text = L"31";
			this->inp29Bt->UseVisualStyleBackColor = true;
			this->inp29Bt->Visible = false;
			this->inp29Bt->Click += gcnew System::EventHandler(this, &IOForm::inp29Bt_Click);
			// 
			// inp28Bt
			// 
			this->inp28Bt->AllowDrop = true;
			this->inp28Bt->AutoEllipsis = true;
			this->inp28Bt->Location = System::Drawing::Point(394, 452);
			this->inp28Bt->Name = L"inp28Bt";
			this->inp28Bt->Size = System::Drawing::Size(31, 23);
			this->inp28Bt->TabIndex = 793;
			this->inp28Bt->Text = L"30";
			this->inp28Bt->UseVisualStyleBackColor = true;
			this->inp28Bt->Visible = false;
			this->inp28Bt->Click += gcnew System::EventHandler(this, &IOForm::inp28Bt_Click);
			// 
			// inp27Bt
			// 
			this->inp27Bt->AllowDrop = true;
			this->inp27Bt->AutoEllipsis = true;
			this->inp27Bt->Location = System::Drawing::Point(440, 452);
			this->inp27Bt->Name = L"inp27Bt";
			this->inp27Bt->Size = System::Drawing::Size(31, 23);
			this->inp27Bt->TabIndex = 792;
			this->inp27Bt->Text = L"29";
			this->inp27Bt->UseVisualStyleBackColor = true;
			this->inp27Bt->Visible = false;
			this->inp27Bt->Click += gcnew System::EventHandler(this, &IOForm::inp27Bt_Click);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(9, 417);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(95, 13);
			this->label22->TabIndex = 796;
			this->label22->Text = L"Check Bit Input";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label23->Location = System::Drawing::Point(13, 456);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(68, 13);
			this->label23->TabIndex = 797;
			this->label23->Text = L"Demo Test";
			// 
			// in33
			// 
			this->in33->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in33->Enabled = false;
			this->in33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in33->ForeColor = System::Drawing::Color::Black;
			this->in33->Location = System::Drawing::Point(259, 412);
			this->in33->Name = L"in33";
			this->in33->Size = System::Drawing::Size(30, 24);
			this->in33->TabIndex = 798;
			this->in33->Text = L"33";
			this->in33->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in33->Visible = false;
			// 
			// in34
			// 
			this->in34->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in34->Enabled = false;
			this->in34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in34->ForeColor = System::Drawing::Color::Black;
			this->in34->Location = System::Drawing::Point(215, 412);
			this->in34->Name = L"in34";
			this->in34->Size = System::Drawing::Size(30, 24);
			this->in34->TabIndex = 799;
			this->in34->Text = L"34";
			this->in34->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in34->Visible = false;
			// 
			// in35
			// 
			this->in35->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in35->Enabled = false;
			this->in35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in35->ForeColor = System::Drawing::Color::Black;
			this->in35->Location = System::Drawing::Point(169, 412);
			this->in35->Name = L"in35";
			this->in35->Size = System::Drawing::Size(30, 24);
			this->in35->TabIndex = 800;
			this->in35->Text = L"35";
			this->in35->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in35->Visible = false;
			// 
			// in36
			// 
			this->in36->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in36->Enabled = false;
			this->in36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in36->ForeColor = System::Drawing::Color::Black;
			this->in36->Location = System::Drawing::Point(126, 412);
			this->in36->Name = L"in36";
			this->in36->Size = System::Drawing::Size(30, 24);
			this->in36->TabIndex = 801;
			this->in36->Text = L"36";
			this->in36->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in36->Visible = false;
			// 
			// in37
			// 
			this->in37->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in37->Enabled = false;
			this->in37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in37->ForeColor = System::Drawing::Color::Black;
			this->in37->Location = System::Drawing::Point(406, 71);
			this->in37->Name = L"in37";
			this->in37->Size = System::Drawing::Size(30, 24);
			this->in37->TabIndex = 802;
			this->in37->Text = L"37";
			this->in37->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in37->Visible = false;
			// 
			// in38
			// 
			this->in38->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in38->Enabled = false;
			this->in38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in38->ForeColor = System::Drawing::Color::Black;
			this->in38->Location = System::Drawing::Point(406, 132);
			this->in38->Name = L"in38";
			this->in38->Size = System::Drawing::Size(30, 24);
			this->in38->TabIndex = 803;
			this->in38->Text = L"38";
			this->in38->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in38->Visible = false;
			// 
			// in39
			// 
			this->in39->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in39->Enabled = false;
			this->in39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in39->ForeColor = System::Drawing::Color::Black;
			this->in39->Location = System::Drawing::Point(406, 194);
			this->in39->Name = L"in39";
			this->in39->Size = System::Drawing::Size(30, 24);
			this->in39->TabIndex = 804;
			this->in39->Text = L"39";
			this->in39->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in39->Visible = false;
			// 
			// in40
			// 
			this->in40->BackColor = System::Drawing::Color::LightSteelBlue;
			this->in40->Enabled = false;
			this->in40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->in40->ForeColor = System::Drawing::Color::Black;
			this->in40->Location = System::Drawing::Point(406, 247);
			this->in40->Name = L"in40";
			this->in40->Size = System::Drawing::Size(30, 24);
			this->in40->TabIndex = 805;
			this->in40->Text = L"40";
			this->in40->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->in40->Visible = false;
			// 
			// inp31Bt
			// 
			this->inp31Bt->AllowDrop = true;
			this->inp31Bt->AutoEllipsis = true;
			this->inp31Bt->Location = System::Drawing::Point(260, 452);
			this->inp31Bt->Name = L"inp31Bt";
			this->inp31Bt->Size = System::Drawing::Size(31, 23);
			this->inp31Bt->TabIndex = 806;
			this->inp31Bt->Text = L"33";
			this->inp31Bt->UseVisualStyleBackColor = true;
			this->inp31Bt->Visible = false;
			this->inp31Bt->Click += gcnew System::EventHandler(this, &IOForm::inp31Bt_Click);
			// 
			// inp32Bt
			// 
			this->inp32Bt->AllowDrop = true;
			this->inp32Bt->AutoEllipsis = true;
			this->inp32Bt->Location = System::Drawing::Point(211, 451);
			this->inp32Bt->Name = L"inp32Bt";
			this->inp32Bt->Size = System::Drawing::Size(31, 23);
			this->inp32Bt->TabIndex = 807;
			this->inp32Bt->Text = L"34";
			this->inp32Bt->UseVisualStyleBackColor = true;
			this->inp32Bt->Visible = false;
			this->inp32Bt->Click += gcnew System::EventHandler(this, &IOForm::inp32Bt_Click);
			// 
			// inp33Bt
			// 
			this->inp33Bt->AllowDrop = true;
			this->inp33Bt->AutoEllipsis = true;
			this->inp33Bt->Location = System::Drawing::Point(165, 451);
			this->inp33Bt->Name = L"inp33Bt";
			this->inp33Bt->Size = System::Drawing::Size(31, 23);
			this->inp33Bt->TabIndex = 808;
			this->inp33Bt->Text = L"35";
			this->inp33Bt->UseVisualStyleBackColor = true;
			this->inp33Bt->Visible = false;
			this->inp33Bt->Click += gcnew System::EventHandler(this, &IOForm::inp33Bt_Click);
			// 
			// inp34Bt
			// 
			this->inp34Bt->AllowDrop = true;
			this->inp34Bt->AutoEllipsis = true;
			this->inp34Bt->Location = System::Drawing::Point(122, 451);
			this->inp34Bt->Name = L"inp34Bt";
			this->inp34Bt->Size = System::Drawing::Size(31, 23);
			this->inp34Bt->TabIndex = 809;
			this->inp34Bt->Text = L"36";
			this->inp34Bt->UseVisualStyleBackColor = true;
			this->inp34Bt->Visible = false;
			this->inp34Bt->Click += gcnew System::EventHandler(this, &IOForm::inp34Bt_Click);
			// 
			// siloNumLb
			// 
			this->siloNumLb->AutoSize = true;
			this->siloNumLb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->siloNumLb->Location = System::Drawing::Point(1029, 489);
			this->siloNumLb->Name = L"siloNumLb";
			this->siloNumLb->Size = System::Drawing::Size(60, 15);
			this->siloNumLb->TabIndex = 810;
			this->siloNumLb->Text = L"siloNum";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label24->Location = System::Drawing::Point(743, 21);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(136, 16);
			this->label24->TabIndex = 811;
			this->label24->Text = L"LANE TARE TEST";
			// 
			// laneTareBt4
			// 
			this->laneTareBt4->AllowDrop = true;
			this->laneTareBt4->AutoEllipsis = true;
			this->laneTareBt4->Location = System::Drawing::Point(769, 253);
			this->laneTareBt4->Name = L"laneTareBt4";
			this->laneTareBt4->Size = System::Drawing::Size(71, 23);
			this->laneTareBt4->TabIndex = 815;
			this->laneTareBt4->Text = L"LANE 4";
			this->laneTareBt4->UseVisualStyleBackColor = true;
			this->laneTareBt4->Visible = false;
			this->laneTareBt4->Click += gcnew System::EventHandler(this, &IOForm::laneTareBt4_Click);
			// 
			// laneTareBt3
			// 
			this->laneTareBt3->AllowDrop = true;
			this->laneTareBt3->AutoEllipsis = true;
			this->laneTareBt3->Location = System::Drawing::Point(769, 196);
			this->laneTareBt3->Name = L"laneTareBt3";
			this->laneTareBt3->Size = System::Drawing::Size(71, 23);
			this->laneTareBt3->TabIndex = 814;
			this->laneTareBt3->Text = L"LANE 3";
			this->laneTareBt3->UseVisualStyleBackColor = true;
			this->laneTareBt3->Visible = false;
			this->laneTareBt3->Click += gcnew System::EventHandler(this, &IOForm::laneTareBt3_Click);
			// 
			// laneTareBt2
			// 
			this->laneTareBt2->AllowDrop = true;
			this->laneTareBt2->AutoEllipsis = true;
			this->laneTareBt2->Location = System::Drawing::Point(769, 132);
			this->laneTareBt2->Name = L"laneTareBt2";
			this->laneTareBt2->Size = System::Drawing::Size(71, 23);
			this->laneTareBt2->TabIndex = 813;
			this->laneTareBt2->Text = L"LANE 2";
			this->laneTareBt2->UseVisualStyleBackColor = true;
			this->laneTareBt2->Visible = false;
			this->laneTareBt2->Click += gcnew System::EventHandler(this, &IOForm::laneTareBt2_Click);
			// 
			// laneTareBt1
			// 
			this->laneTareBt1->AllowDrop = true;
			this->laneTareBt1->AutoEllipsis = true;
			this->laneTareBt1->Location = System::Drawing::Point(767, 71);
			this->laneTareBt1->Name = L"laneTareBt1";
			this->laneTareBt1->Size = System::Drawing::Size(71, 23);
			this->laneTareBt1->TabIndex = 812;
			this->laneTareBt1->Text = L"LANE 1";
			this->laneTareBt1->UseVisualStyleBackColor = true;
			this->laneTareBt1->Visible = false;
			this->laneTareBt1->Click += gcnew System::EventHandler(this, &IOForm::laneTareBt1_Click);
			// 
			// IOForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1225, 524);
			this->Controls->Add(this->laneTareBt4);
			this->Controls->Add(this->laneTareBt3);
			this->Controls->Add(this->laneTareBt2);
			this->Controls->Add(this->laneTareBt1);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->siloNumLb);
			this->Controls->Add(this->inp34Bt);
			this->Controls->Add(this->inp33Bt);
			this->Controls->Add(this->inp32Bt);
			this->Controls->Add(this->inp31Bt);
			this->Controls->Add(this->in40);
			this->Controls->Add(this->in39);
			this->Controls->Add(this->in38);
			this->Controls->Add(this->in37);
			this->Controls->Add(this->in36);
			this->Controls->Add(this->in35);
			this->Controls->Add(this->in34);
			this->Controls->Add(this->in33);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->inp30Bt);
			this->Controls->Add(this->inp29Bt);
			this->Controls->Add(this->inp28Bt);
			this->Controls->Add(this->inp27Bt);
			this->Controls->Add(this->inp26Bt);
			this->Controls->Add(this->inp25Bt);
			this->Controls->Add(this->inp24Bt);
			this->Controls->Add(this->inp23Bt);
			this->Controls->Add(this->inp22Bt);
			this->Controls->Add(this->inp21Bt);
			this->Controls->Add(this->inp20Bt);
			this->Controls->Add(this->inp19Bt);
			this->Controls->Add(this->inp18Bt);
			this->Controls->Add(this->inp17Bt);
			this->Controls->Add(this->inp16Bt);
			this->Controls->Add(this->inp15Bt);
			this->Controls->Add(this->inp14Bt);
			this->Controls->Add(this->inp13Bt);
			this->Controls->Add(this->inp12Bt);
			this->Controls->Add(this->KInpBt);
			this->Controls->Add(this->RInpBt);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->in32);
			this->Controls->Add(this->in31);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->targetNumLb);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->enableIOCb);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->out78);
			this->Controls->Add(this->out80);
			this->Controls->Add(this->out79);
			this->Controls->Add(this->out77);
			this->Controls->Add(this->out76);
			this->Controls->Add(this->out75);
			this->Controls->Add(this->out74);
			this->Controls->Add(this->out73);
			this->Controls->Add(this->out72);
			this->Controls->Add(this->out68);
			this->Controls->Add(this->out70);
			this->Controls->Add(this->out71);
			this->Controls->Add(this->out69);
			this->Controls->Add(this->out67);
			this->Controls->Add(this->out66);
			this->Controls->Add(this->out65);
			this->Controls->Add(this->out64);
			this->Controls->Add(this->out61);
			this->Controls->Add(this->out63);
			this->Controls->Add(this->out62);
			this->Controls->Add(this->out58);
			this->Controls->Add(this->out60);
			this->Controls->Add(this->out59);
			this->Controls->Add(this->out57);
			this->Controls->Add(this->out56);
			this->Controls->Add(this->out55);
			this->Controls->Add(this->out54);
			this->Controls->Add(this->out53);
			this->Controls->Add(this->out52);
			this->Controls->Add(this->out48);
			this->Controls->Add(this->out50);
			this->Controls->Add(this->out51);
			this->Controls->Add(this->out49);
			this->Controls->Add(this->out47);
			this->Controls->Add(this->out46);
			this->Controls->Add(this->out45);
			this->Controls->Add(this->out44);
			this->Controls->Add(this->out41);
			this->Controls->Add(this->out43);
			this->Controls->Add(this->out42);
			this->Controls->Add(this->out38);
			this->Controls->Add(this->out40);
			this->Controls->Add(this->out39);
			this->Controls->Add(this->out37);
			this->Controls->Add(this->out36);
			this->Controls->Add(this->out35);
			this->Controls->Add(this->out34);
			this->Controls->Add(this->out33);
			this->Controls->Add(this->out32);
			this->Controls->Add(this->LInpBt6);
			this->Controls->Add(this->DInpBt7);
			this->Controls->Add(this->RInpBt8);
			this->Controls->Add(this->holdBt8);
			this->Controls->Add(this->LInpBt5);
			this->Controls->Add(this->DInpBt5);
			this->Controls->Add(this->RInpBt7);
			this->Controls->Add(this->holdBt7);
			this->Controls->Add(this->LInpBt4);
			this->Controls->Add(this->DInpBt4);
			this->Controls->Add(this->RInpBt5);
			this->Controls->Add(this->holdBt5);
			this->Controls->Add(this->holdBtIR);
			this->Controls->Add(this->DInpBt2);
			this->Controls->Add(this->RInpBt4);
			this->Controls->Add(this->holdBt4);
			this->Controls->Add(this->DInpBtIR);
			this->Controls->Add(this->DInpBt1);
			this->Controls->Add(this->RInpBt2);
			this->Controls->Add(this->holdBt2);
			this->Controls->Add(this->DInpBt8);
			this->Controls->Add(this->RInpBtIR);
			this->Controls->Add(this->RInpBt1);
			this->Controls->Add(this->holdBt1);
			this->Controls->Add(this->out28);
			this->Controls->Add(this->out30);
			this->Controls->Add(this->out31);
			this->Controls->Add(this->out29);
			this->Controls->Add(this->out27);
			this->Controls->Add(this->out26);
			this->Controls->Add(this->out25);
			this->Controls->Add(this->out24);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->in16);
			this->Controls->Add(this->in17);
			this->Controls->Add(this->in18);
			this->Controls->Add(this->in19);
			this->Controls->Add(this->in21);
			this->Controls->Add(this->in22);
			this->Controls->Add(this->in20);
			this->Controls->Add(this->in23);
			this->Controls->Add(this->in24);
			this->Controls->Add(this->in25);
			this->Controls->Add(this->in26);
			this->Controls->Add(this->in27);
			this->Controls->Add(this->in28);
			this->Controls->Add(this->in29);
			this->Controls->Add(this->in30);
			this->Controls->Add(this->in0);
			this->Controls->Add(this->in1);
			this->Controls->Add(this->in2);
			this->Controls->Add(this->in3);
			this->Controls->Add(this->in5);
			this->Controls->Add(this->in6);
			this->Controls->Add(this->in4);
			this->Controls->Add(this->in7);
			this->Controls->Add(this->in8);
			this->Controls->Add(this->in9);
			this->Controls->Add(this->in10);
			this->Controls->Add(this->in11);
			this->Controls->Add(this->in12);
			this->Controls->Add(this->in13);
			this->Controls->Add(this->in14);
			this->Controls->Add(this->in15);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->out16);
			this->Controls->Add(this->out17);
			this->Controls->Add(this->out18);
			this->Controls->Add(this->out19);
			this->Controls->Add(this->out20);
			this->Controls->Add(this->out21);
			this->Controls->Add(this->out23);
			this->Controls->Add(this->out22);
			this->Controls->Add(this->out12);
			this->Controls->Add(this->out14);
			this->Controls->Add(this->out15);
			this->Controls->Add(this->out13);
			this->Controls->Add(this->out0);
			this->Controls->Add(this->out1);
			this->Controls->Add(this->out11);
			this->Controls->Add(this->out2);
			this->Controls->Add(this->out10);
			this->Controls->Add(this->out3);
			this->Controls->Add(this->out9);
			this->Controls->Add(this->out4);
			this->Controls->Add(this->out8);
			this->Controls->Add(this->out5);
			this->Controls->Add(this->out7);
			this->Controls->Add(this->out6);
			this->Name = L"IOForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"IOForm";
			this->Load += gcnew System::EventHandler(this, &IOForm::IOForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region COMMON
	private:
		//---------------------------------------------
		// initialize IO
		//---------------------------------------------
		void initOutputs(void)
		{
			out0->Visible  = (psIni->nMask & 0x0000000000000001) > 0;
			out1->Visible  = (psIni->nMask & 0x0000000000000002) > 0;
			out2->Visible  = (psIni->nMask & 0x0000000000000004) > 0;
			out3->Visible  = (psIni->nMask & 0x0000000000000008) > 0;
			out4->Visible  = (psIni->nMask & 0x0000000000000010) > 0;
			out5->Visible  = (psIni->nMask & 0x0000000000000020) > 0;
			out6->Visible  = (psIni->nMask & 0x0000000000000040) > 0;
			out7->Visible  = (psIni->nMask & 0x0000000000000080) > 0;
			out8->Visible  = (psIni->nMask & 0x0000000000000100) > 0;
			out9->Visible  = (psIni->nMask & 0x0000000000000200) > 0;
			out10->Visible = (psIni->nMask & 0x0000000000000400) > 0;
			out11->Visible = (psIni->nMask & 0x0000000000000800) > 0;
			out12->Visible = (psIni->nMask & 0x0000000000001000) > 0;
			out13->Visible = (psIni->nMask & 0x0000000000002000) > 0;
			out14->Visible = (psIni->nMask & 0x0000000000004000) > 0;
			out15->Visible = (psIni->nMask & 0x0000000000008000) > 0;
			// outputs addr 5
			out16->Visible = (psIni->nMask & 0x0000000000010000) > 0;
			out17->Visible = (psIni->nMask & 0x0000000000020000) > 0;
			out18->Visible = (psIni->nMask & 0x0000000000040000) > 0;
			out19->Visible = (psIni->nMask & 0x0000000000080000) > 0;
			out20->Visible = (psIni->nMask & 0x0000000000100000) > 0;
			out21->Visible = (psIni->nMask & 0x0000000000200000) > 0;
			out22->Visible = (psIni->nMask & 0x0000000000400000) > 0;
			out23->Visible = (psIni->nMask & 0x0000000000800000) > 0;
			out24->Visible = (psIni->nMask & 0x0000000001000000) > 0;
			out25->Visible = (psIni->nMask & 0x0000000002000000) > 0;
			out26->Visible = (psIni->nMask & 0x0000000004000000) > 0;
			out27->Visible = (psIni->nMask & 0x0000000008000000) > 0;
			out28->Visible = (psIni->nMask & 0x0000000010000000) > 0;
			out29->Visible = (psIni->nMask & 0x0000000020000000) > 0;
			out30->Visible = (psIni->nMask & 0x0000000040000000) > 0;
			out31->Visible = (psIni->nMask & 0x0000000080000000) > 0;
			// outputs addr 6
			out32->Visible = (psIni->nMask & 0x0000000100000000) > 0;
			out33->Visible = (psIni->nMask & 0x0000000200000000) > 0;
			out34->Visible = (psIni->nMask & 0x0000000400000000) > 0;
			out35->Visible = (psIni->nMask & 0x0000000800000000) > 0;
			out36->Visible = (psIni->nMask & 0x0000001000000000) > 0;
			out37->Visible = (psIni->nMask & 0x0000002000000000) > 0;
			out38->Visible = (psIni->nMask & 0x0000004000000000) > 0;
			out39->Visible = (psIni->nMask & 0x0000008000000000) > 0;
			out40->Visible = (psIni->nMask & 0x0000010000000000) > 0;
			out41->Visible = (psIni->nMask & 0x0000020000000000) > 0;
			out42->Visible = (psIni->nMask & 0x0000040000000000) > 0;
			out43->Visible = (psIni->nMask & 0x0000080000000000) > 0;
			out44->Visible = (psIni->nMask & 0x0000100000000000) > 0;
			out45->Visible = (psIni->nMask & 0x0000200000000000) > 0;
			out46->Visible = (psIni->nMask & 0x0000400000000000) > 0;
			out47->Visible = (psIni->nMask & 0x0000800000000000) > 0;
			// outputs addr 7
			out48->Visible = (psIni->nMask & 0x0001000000000000) > 0;
			out49->Visible = (psIni->nMask & 0x0002000000000000) > 0;
			out50->Visible = (psIni->nMask & 0x0004000000000000) > 0;
			out51->Visible = (psIni->nMask & 0x0008000000000000) > 0;
			out52->Visible = (psIni->nMask & 0x0010000000000000) > 0;
			out53->Visible = (psIni->nMask & 0x0020000000000000) > 0;
			out54->Visible = (psIni->nMask & 0x0040000000000000) > 0;
			out55->Visible = (psIni->nMask & 0x0080000000000000) > 0;
			out56->Visible = (psIni->nMask & 0x0100000000000000) > 0;
			out57->Visible = (psIni->nMask & 0x0200000000000000) > 0;
			out58->Visible = (psIni->nMask & 0x0400000000000000) > 0;
			out59->Visible = (psIni->nMask & 0x0800000000000000) > 0;
			out60->Visible = (psIni->nMask & 0x1000000000000000) > 0;
			out61->Visible = (psIni->nMask & 0x2000000000000000) > 0;
			out62->Visible = (psIni->nMask & 0x4000000000000000) > 0;
			out63->Visible = (psIni->nMask & 0x8000000000000000) > 0;
			// inputs --------------------------------------------------------
			in0->Visible  = (psIni->nInpMask & 0x0000000000000001) > 0;
			in1->Visible  = (psIni->nInpMask & 0x0000000000000002) > 0;
			in2->Visible  = (psIni->nInpMask & 0x0000000000000004) > 0;
			in3->Visible  = (psIni->nInpMask & 0x0000000000000008) > 0;
			in4->Visible  = (psIni->nInpMask & 0x0000000000000010) > 0;
			in5->Visible  = (psIni->nInpMask & 0x0000000000000020) > 0;
			in6->Visible  = (psIni->nInpMask & 0x0000000000000040) > 0;
			in7->Visible  = (psIni->nInpMask & 0x0000000000000080) > 0;
			in8->Visible  = (psIni->nInpMask & 0x0000000000000100) > 0;
			in9->Visible  = (psIni->nInpMask & 0x0000000000000200) > 0;
			in10->Visible = (psIni->nInpMask & 0x0000000000000400) > 0;
			in11->Visible = (psIni->nInpMask & 0x0000000000000800) > 0;
			in12->Visible = (psIni->nInpMask & 0x0000000000001000) > 0;
			in13->Visible = (psIni->nInpMask & 0x0000000000002000) > 0;
			in14->Visible = (psIni->nInpMask & 0x0000000000004000) > 0;
			in15->Visible = (psIni->nInpMask & 0x0000000000008000) > 0;
			// inputs 
			in16->Visible = (psIni->nInpMask & 0x0000000000010000) > 0;
			in17->Visible = (psIni->nInpMask & 0x0000000000020000) > 0;
			in18->Visible = (psIni->nInpMask & 0x0000000000040000) > 0;
			in19->Visible = (psIni->nInpMask & 0x0000000000080000) > 0;
			in20->Visible = (psIni->nInpMask & 0x0000000000100000) > 0;
			in21->Visible = (psIni->nInpMask & 0x0000000000200000) > 0;
			in22->Visible = (psIni->nInpMask & 0x0000000000400000) > 0;
			in23->Visible = (psIni->nInpMask & 0x0000000000800000) > 0;
			in24->Visible = (psIni->nInpMask & 0x0000000001000000) > 0;
			in25->Visible = (psIni->nInpMask & 0x0000000002000000) > 0;
			in26->Visible = (psIni->nInpMask & 0x0000000004000000) > 0;
			in27->Visible = (psIni->nInpMask & 0x0000000008000000) > 0;
			in28->Visible = (psIni->nInpMask & 0x0000000010000000) > 0;
			in29->Visible = (psIni->nInpMask & 0x0000000020000000) > 0;
			in30->Visible = (psIni->nInpMask & 0x0000000040000000) > 0;
			in31->Visible = (psIni->nInpMask & 0x0000000080000000) > 0;
			in32->Visible = (psIni->nInpMask & 0x0000000100000000) > 0;	
			in33->Visible = (psIni->nInpMask & 0x0000000200000000) > 0;
			in34->Visible = (psIni->nInpMask & 0x0000000400000000) > 0;
			in35->Visible = (psIni->nInpMask & 0x0000000800000000) > 0;
			in36->Visible = (psIni->nInpMask & 0x0000001000000000) > 0;
			in37->Visible = (psIni->nInpMask & 0x0000002000000000) > 0;
			in38->Visible = (psIni->nInpMask & 0x0000004000000000) > 0;
			in39->Visible = (psIni->nInpMask & 0x0000008000000000) > 0;
			in40->Visible = (psIni->nInpMask & 0x0000010000000000) > 0;

			if(pAll->eAsType != A_PROD)
			{
				holdBt1->Visible = true;	holdBt2->Visible = true;	holdBt4->Visible = true;	holdBt5->Visible = true;
				holdBt7->Visible = true;	holdBt8->Visible = true;	holdBtIR->Visible = true;
				RInpBt1->Visible = true;	RInpBt2->Visible = true;	RInpBt4->Visible = true;	RInpBt5->Visible = true;
				RInpBt7->Visible = true;	RInpBt8->Visible = true;	RInpBtIR->Visible = true;
				DInpBt1->Visible = true;	DInpBt2->Visible = true;	DInpBt4->Visible = true;	DInpBt5->Visible = true;
				DInpBt7->Visible = true;	DInpBt8->Visible = true;	DInpBtIR->Visible = true;
				inp12Bt->Visible = true;	inp13Bt->Visible = true;	inp14Bt->Visible = true;	inp15Bt->Visible = true;
				inp16Bt->Visible = true;	inp17Bt->Visible = true;	inp18Bt->Visible = true;	inp19Bt->Visible = true;
				inp20Bt->Visible = true;	inp21Bt->Visible = true;	inp22Bt->Visible = true;	inp23Bt->Visible = true;
				inp24Bt->Visible = true;	inp25Bt->Visible = true;	inp26Bt->Visible = true;	inp27Bt->Visible = true;
				inp28Bt->Visible = true;	inp29Bt->Visible = true;	inp30Bt->Visible = true;	inp31Bt->Visible = true;
				inp32Bt->Visible = true;	inp33Bt->Visible = true;	inp34Bt->Visible = true;
				laneTareBt1->Visible = true;	laneTareBt2->Visible = true;	laneTareBt3->Visible = true;	laneTareBt4->Visible = true;
				RInpBt->Visible = true;		KInpBt->Visible = true;
			}
		}

		private:
		//---------------------------------------------
		// Demo Screen
		//---------------------------------------------
		void demoScreen(void)
		{
/*
			if(psIni->asUpBins[0].bUsed)
			{
				this->RoHeadInpBt1->Visible = true;
				this->ERHInpBt1->Visible = true;
				this->HInpBt1->Visible = true;
				this->LInpBt1->Visible = true;
			}
			if(psIni->asUpBins[1].bUsed)
			{
				this->RoHeadInpBt2->Visible = true;
				this->ERHInpBt2->Visible = true;
				this->HInpBt2->Visible = true;
				this->LInpBt2->Visible = true;
			}
			if(psIni->asUpBins[2].bUsed)
			{
				this->RoHeadInpBt3->Visible = true;
				this->ERHInpBt3->Visible = true;
				this->HInpBt3->Visible = true;
				this->LInpBt3->Visible = true;
			}
			if(psIni->asUpBins[3].bUsed)
			{
				this->RoHeadInpBt4->Visible = true;
				this->ERHInpBt4->Visible = true;
				this->HInpBt4->Visible = true;
				this->LInpBt4->Visible = true;
			}
			if(psIni->asUpBins[4].bUsed)
			{
				this->RoHeadInpBt5->Visible = true;
				this->ERHInpBt5->Visible = true;
				this->HInpBt5->Visible = true;
				this->LInpBt5->Visible = true;
			}
			if(psIni->asUpBins[5].bUsed)
			{
				this->RoHeadInpBt6->Visible = true;
				this->ERHInpBt6->Visible = true;
				this->HInpBt6->Visible = true;
				this->LInpBt6->Visible = true;
			}
*/
		}
#pragma endregion

#pragma region TIMER_TEST
		private:
		//---------------------------------------------------------------------
		System::Void timerTest(void)
		{
			Color coLsb = Color::LightSteelBlue;
			Color coW = Color::Yellow;
			Color coY = Color::Yellow;
			ushort  nTmp;
			
			//DC 4.0.0 convert binary to decimal
			int nTargetWeight = 0;
			int nSiloNumber = 0;
			for(int i = 0; i <19; i++)
			{
				nTargetWeight = nTargetWeight + psIni->nBinaryNumber[i]*(int(pow(2,double(i))));
			}
			for(int i = 0; i <4; i++)
			{
				nSiloNumber = nSiloNumber+ psIni->nSiloBitNum[i]*(int(pow(2,double(i))));
			}
			
			targetNumLb->Text = nTargetWeight.ToString();
			siloNumLb->Text = nSiloNumber.ToString();

			//-----------------------------------------------------------------
			nTmp = (ushort)(psIni->nRpoints & 0xffff);
			if(nRpoints1 != nTmp)
			{
				// inputs addr2
				in0->BackColor = (nTmp & 0x0001)> 0 ? coW : coLsb;
				in1->BackColor = (nTmp & 0x0002)> 0 ? coW : coLsb;
				in2->BackColor = (nTmp & 0x0004)> 0 ? coW : coLsb;
				in3->BackColor = (nTmp & 0x0008)> 0 ? coW : coLsb;
				in4->BackColor = (nTmp & 0x0010)> 0 ? coW : coLsb;
				in5->BackColor = (nTmp & 0x0020)> 0 ? coW : coLsb;
				in6->BackColor = (nTmp & 0x0040)> 0 ? coW : coLsb;
				in7->BackColor = (nTmp & 0x0080)> 0 ? coW : coLsb;
				in8->BackColor = (nTmp & 0x0100)> 0 ? coW : coLsb;
				in9->BackColor = (nTmp & 0x0200)> 0 ? coW : coLsb;
				in10->BackColor = (nTmp & 0x0400)> 0 ? coW : coLsb;
				in11->BackColor = (nTmp & 0x0800)> 0 ? coW : coLsb;
				in12->BackColor = (nTmp & 0x1000)> 0 ? coW : coLsb;
				in13->BackColor = (nTmp & 0x2000)> 0 ? coW : coLsb;
				in14->BackColor = (nTmp & 0x4000)> 0 ? coW : coLsb;
				in15->BackColor = (nTmp & 0x8000)> 0 ? coW : coLsb;
				nRpoints1 = nTmp;
			}
			nTmp = (ushort)(psIni->nRpoints >> 16);
			if(nRpoints2 != nTmp)
			{
				// inputs addr3
				in16->BackColor =(nTmp & 0x0001) > 0 ?  coW : coLsb;
				in17->BackColor = (nTmp & 0x0002) > 0 ? coW : coLsb;
				in18->BackColor = (nTmp & 0x0004) > 0 ? coW : coLsb;
				in19->BackColor = (nTmp & 0x0008) > 0 ? coW : coLsb;
				in20->BackColor = (nTmp & 0x0010) > 0 ? coW : coLsb;
				in21->BackColor = (nTmp & 0x0020) > 0 ? coW : coLsb;
				in22->BackColor = (nTmp & 0x0040) > 0 ? coW : coLsb;
				in23->BackColor = (nTmp & 0x0080) > 0 ? coW : coLsb;
				in24->BackColor = (nTmp & 0x0100) > 0 ? coW : coLsb;
				in25->BackColor = (nTmp & 0x0200) > 0 ? coW : coLsb;
				in26->BackColor = (nTmp & 0x0400) > 0 ? coW : coLsb;
				in27->BackColor = (nTmp & 0x0800) > 0 ? coW : coLsb;
				in28->BackColor = (nTmp & 0x1000) > 0 ? coW : coLsb;
				in29->BackColor = (nTmp & 0x2000) > 0 ? coW : coLsb;
				in30->BackColor = (nTmp & 0x4000) > 0 ? coW : coLsb;
				in31->BackColor = (nTmp & 0x8000) > 0 ? coW : coLsb;
				nRpoints2 = nTmp;
			}
			nTmp = (ushort)(psIni->nRpoints >> 32);
			if(nRpoints3 != nTmp)
			{
				// inputs addr3
				in32->BackColor =(nTmp & 0x0001) > 0 ?  coW : coLsb;
				in33->BackColor = (nTmp & 0x0002) > 0 ? coW : coLsb;
				in34->BackColor = (nTmp & 0x0004) > 0 ? coW : coLsb;
				in35->BackColor = (nTmp & 0x0008) > 0 ? coW : coLsb;
				in36->BackColor = (nTmp & 0x0010) > 0 ? coW : coLsb;
				in37->BackColor = (nTmp & 0x0020) > 0 ? coW : coLsb;
				in38->BackColor = (nTmp & 0x0040) > 0 ? coW : coLsb;
				in39->BackColor = (nTmp & 0x0080) > 0 ? coW : coLsb;
				in40->BackColor = (nTmp & 0x0100) > 0 ? coW : coLsb;
//				in25->BackColor = (nTmp & 0x0200) > 0 ? coW : coLsb;
//				in26->BackColor = (nTmp & 0x0400) > 0 ? coW : coLsb;
//				in27->BackColor = (nTmp & 0x0800) > 0 ? coW : coLsb;
//				in28->BackColor = (nTmp & 0x1000) > 0 ? coW : coLsb;
//				in29->BackColor = (nTmp & 0x2000) > 0 ? coW : coLsb;
//				in30->BackColor = (nTmp & 0x4000) > 0 ? coW : coLsb;
//				in31->BackColor = (nTmp & 0x8000) > 0 ? coW : coLsb;
				nRpoints3 = nTmp;
			}
			// write ----------------------------------------------------------
			nTmp = (ushort) (psIni->nWpoints & 0xffff);
			if(nWpoints1 != nTmp)
			{
				// outputs addr 4
				out0->BackColor = (nTmp & 0x0001) > 0 ? coY : coLsb;
				out1->BackColor = (nTmp & 0x0002) > 0 ? coY : coLsb;
				out2->BackColor = (nTmp & 0x0004) > 0 ? coY : coLsb;
				out3->BackColor = (nTmp & 0x0008) > 0 ? coY : coLsb;
				out4->BackColor = (nTmp & 0x0010) > 0 ? coY : coLsb;
				out5->BackColor = (nTmp & 0x0020) > 0 ? coY : coLsb;
				out6->BackColor = (nTmp & 0x0040) > 0 ? coY : coLsb;
				out7->BackColor = (nTmp & 0x0080) > 0 ? coY : coLsb;
				out8->BackColor = (nTmp & 0x0100) > 0 ? coY : coLsb;
				out9->BackColor = (nTmp & 0x0200) > 0 ? coY : coLsb;
				out10->BackColor = (nTmp & 0x0400) > 0 ? coY : coLsb;
				out11->BackColor = (nTmp & 0x0800) > 0 ? coY : coLsb;
				out12->BackColor = (nTmp & 0x1000) > 0 ? coY : coLsb;
				out13->BackColor = (nTmp & 0x2000) > 0 ? coY : coLsb;
				out14->BackColor = (nTmp & 0x4000) > 0 ? coY : coLsb;
				out15->BackColor = (nTmp & 0x8000) > 0 ? coY : coLsb;
				nWpoints1 = nTmp;
			}
			nTmp = (ushort) ((psIni->nWpoints >> 16) & 0xffff);
			if(nWpoints2 != nTmp)
			{
				// outputs addr 5
				out16->BackColor = (nTmp & 0x0001) > 0 ? coY : coLsb;
				out17->BackColor = (nTmp & 0x0002) > 0 ? coY : coLsb;
				out18->BackColor = (nTmp & 0x0004) > 0 ? coY : coLsb;
				out19->BackColor = (nTmp & 0x0008) > 0 ? coY : coLsb;
				out20->BackColor = (nTmp & 0x0010) > 0 ? coY : coLsb;
				out21->BackColor = (nTmp & 0x0020) > 0 ? coY : coLsb;
				out22->BackColor = (nTmp & 0x0040) > 0 ? coY : coLsb;
				out23->BackColor = (nTmp & 0x0080) > 0 ? coY : coLsb;
				out24->BackColor = (nTmp & 0x0100) > 0 ? coY : coLsb;
				out25->BackColor = (nTmp & 0x0200) > 0 ? coY : coLsb;
				out26->BackColor = (nTmp & 0x0400) > 0 ? coY : coLsb;
				out27->BackColor = (nTmp & 0x0800) > 0 ? coY : coLsb;
				out28->BackColor = (nTmp & 0x1000) > 0 ? coY : coLsb;
				out29->BackColor = (nTmp & 0x2000) > 0 ? coY : coLsb;
				out30->BackColor = (nTmp & 0x4000) > 0 ? coY : coLsb;
				out31->BackColor = (nTmp & 0x8000) > 0 ? coY : coLsb;	
				nWpoints2 = nTmp;
			}
			nTmp = (ushort) ((psIni->nWpoints >> 32) & 0xffff);
			if(nWpoints3 != nTmp)
			{
				// outputs addr 5
				out32->BackColor = (nTmp & 0x0001) > 0 ? coY : coLsb;
				out33->BackColor = (nTmp & 0x0002) > 0 ? coY : coLsb;
				out34->BackColor = (nTmp & 0x0004) > 0 ? coY : coLsb;
				out35->BackColor = (nTmp & 0x0008) > 0 ? coY : coLsb;
				out36->BackColor = (nTmp & 0x0010) > 0 ? coY : coLsb;
				out37->BackColor = (nTmp & 0x0020) > 0 ? coY : coLsb;
				out38->BackColor = (nTmp & 0x0040) > 0 ? coY : coLsb;
				out39->BackColor = (nTmp & 0x0080) > 0 ? coY : coLsb;
				out40->BackColor = (nTmp & 0x0100) > 0 ? coY : coLsb;
				out41->BackColor = (nTmp & 0x0200) > 0 ? coY : coLsb;
				out42->BackColor = (nTmp & 0x0400) > 0 ? coY : coLsb;
				out43->BackColor = (nTmp & 0x0800) > 0 ? coY : coLsb;
				out44->BackColor = (nTmp & 0x1000) > 0 ? coY : coLsb;
				out45->BackColor = (nTmp & 0x2000) > 0 ? coY : coLsb;
				out46->BackColor = (nTmp & 0x4000) > 0 ? coY : coLsb;
				out47->BackColor = (nTmp & 0x8000) > 0 ? coY : coLsb;	
				nWpoints3 = nTmp;
			}
			nTmp = (ushort) ((psIni->nWpoints >> 48) & 0xffff);
			if(nWpoints4 != nTmp)
			{
				// outputs addr 5
				out48->BackColor = (nTmp & 0x0001) > 0 ? coY : coLsb;
				out49->BackColor = (nTmp & 0x0002) > 0 ? coY : coLsb;
				out50->BackColor = (nTmp & 0x0004) > 0 ? coY : coLsb;
				out51->BackColor = (nTmp & 0x0008) > 0 ? coY : coLsb;
				out52->BackColor = (nTmp & 0x0010) > 0 ? coY : coLsb;
				out53->BackColor = (nTmp & 0x0020) > 0 ? coY : coLsb;
				out54->BackColor = (nTmp & 0x0040) > 0 ? coY : coLsb;
				out55->BackColor = (nTmp & 0x0080) > 0 ? coY : coLsb;
				out56->BackColor = (nTmp & 0x0100) > 0 ? coY : coLsb;
				out57->BackColor = (nTmp & 0x0200) > 0 ? coY : coLsb;
				out58->BackColor = (nTmp & 0x0400) > 0 ? coY : coLsb;
				out59->BackColor = (nTmp & 0x0800) > 0 ? coY : coLsb;
				out60->BackColor = (nTmp & 0x1000) > 0 ? coY : coLsb;
				out61->BackColor = (nTmp & 0x2000) > 0 ? coY : coLsb;
				out62->BackColor = (nTmp & 0x4000) > 0 ? coY : coLsb;
				out63->BackColor = (nTmp & 0x8000) > 0 ? coY : coLsb;	
				nWpoints4 = nTmp;
			}
		}

#pragma endregion

	private: 
		System::Void out0_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0001) != 0)
				psIni->nWpoints &= ~0x0001;
			else
				psIni->nWpoints |= 0x0001;
		}
		System::Void out1_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0002) != 0)
				psIni->nWpoints &= ~0x0002;
			else
				psIni->nWpoints |= 0x0002;
		}
		System::Void out2_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0004L) != 0)
				psIni->nWpoints &= ~0x0004L;
			else
				psIni->nWpoints |= 0x0004L;
		}
		System::Void out3_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0008L) != 0)
				psIni->nWpoints &= ~0x0008L;
			else				 
				psIni->nWpoints |= 0x0008L;
		}
		System::Void out4_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0010) != 0)
				psIni->nWpoints &= ~0x0010;
			else
				psIni->nWpoints |= 0x0010;
		}
		System::Void out5_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0020) != 0)
				psIni->nWpoints &= ~0x0020;
			else
				psIni->nWpoints |= 0x0020;
		}
		System::Void out6_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0040) != 0)
				psIni->nWpoints &= ~0x0040;
			else
				psIni->nWpoints |= 0x0040;
		}
		System::Void out7_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0080) != 0)
				psIni->nWpoints &= ~0x0080;
			else
				psIni->nWpoints |= 0x0080;
		}

		System::Void out8_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0100) != 0)
				psIni->nWpoints &= ~0x0100;
			else
				psIni->nWpoints |= 0x0100;
		}
		System::Void out9_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0200) != 0)
				psIni->nWpoints &= ~0x0200;
			else
				psIni->nWpoints |= 0x0200;
		}
		System::Void out10_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0400) != 0)
				psIni->nWpoints &= ~0x0400;
			else
				psIni->nWpoints |= 0x0400;
		}
		System::Void out11_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x0800) != 0)
				psIni->nWpoints &= ~0x0800;
			else
				psIni->nWpoints |= 0x0800;
		}
		System::Void out12_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x1000) != 0)
				psIni->nWpoints &= ~0x1000;
			else
				psIni->nWpoints |= 0x1000;
		}
		System::Void out13_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x2000) != 0)
				psIni->nWpoints &= ~0x2000;
			else
				psIni->nWpoints |= 0x2000;
		}
		System::Void out14_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x4000) != 0)
				psIni->nWpoints &= ~0x4000;
			else
				psIni->nWpoints |= 0x4000;
		}
		System::Void out15_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x8000) != 0)
				psIni->nWpoints &= ~0x8000;
			else
				psIni->nWpoints |= 0x8000;
		}
		//-----------------------------------------------------------------------
		System::Void out16_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x00010000) != 0)
				psIni->nWpoints &= ~0x00010000;
			else
				psIni->nWpoints |= 0x00010000;
		}
		System::Void out17_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if((psIni->nWpoints & 0x00020000) != 0)
				psIni->nWpoints &= ~0x00020000;
			else
				psIni->nWpoints |= 0x00020000;
		}
		System::Void out18_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x00040000L) != 0)
				psIni->nWpoints &= ~0x00040000L;
			else
				psIni->nWpoints |= 0x00040000L;
		}
		System::Void out19_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x00080000L) != 0)
				psIni->nWpoints &= ~0x00080000L;
			else				 
				psIni->nWpoints |= 0x00080000L;
		}
		System::Void out20_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x00100000) != 0)
				psIni->nWpoints &= ~0x00100000;
			else
				psIni->nWpoints |= 0x00100000;
		}
		System::Void out21_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x00200000) != 0)
				psIni->nWpoints &= ~0x00200000;
			else
				psIni->nWpoints |= 0x00200000;
		}
		System::Void out22_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x00400000) != 0)
				psIni->nWpoints &= ~0x00400000;
			else
				psIni->nWpoints |= 0x00400000;
		}
		System::Void out23_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x00800000) != 0)
				psIni->nWpoints &= ~0x00800000;
			else
				psIni->nWpoints |= 0x00800000;
		}
		System::Void out24_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x01000000) != 0)
				psIni->nWpoints &= ~0x01000000;
			else
				psIni->nWpoints |= 0x01000000;
		}
		System::Void out25_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x02000000) != 0)
				psIni->nWpoints &= ~0x02000000;
			else
				psIni->nWpoints |= 0x02000000;
		}
		System::Void out26_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints & 0x04000000) != 0)
				psIni->nWpoints &= ~0x04000000;
			else
				psIni->nWpoints |= 0x04000000;
		}
		System::Void out27_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x08000000) != 0)
				psIni->nWpoints &= ~0x08000000;
			else
				psIni->nWpoints |=  0x08000000;
		}
		System::Void out28_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x10000000) != 0)
				psIni->nWpoints &= ~0x10000000;
			else
				psIni->nWpoints |=  0x10000000;
		}
		System::Void out29_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x20000000) != 0)
				psIni->nWpoints &= ~0x20000000;
			else
				psIni->nWpoints |=  0x20000000;
		}
		System::Void out30_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x40000000) != 0)
				psIni->nWpoints &= ~0x40000000;
			else
				psIni->nWpoints |=  0x40000000;
		}
		System::Void out31_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &  0x0000000080000000UL) != 0)
			   psIni->nWpoints &=  0xffffffff7fffffffUL;
			else
				psIni->nWpoints |= 0x0000000080000000UL;
		}
		System::Void out32_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000000100000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000000100000000UL;
			else
				psIni->nWpoints |= 0x0000000100000000UL;
		}
		System::Void out33_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000000200000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000000200000000UL;
			else
				psIni->nWpoints |= 0x0000000200000000UL;
		}
		System::Void out34_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000000400000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000000400000000UL;
			else
				psIni->nWpoints |= 0x0000000400000000UL;
		}
		System::Void out35_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000000800000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000000800000000UL;
			else
				psIni->nWpoints |= 0x0000000800000000UL;
		}
		System::Void out36_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000001000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000001000000000UL;
			else
				psIni->nWpoints |= 0x0000001000000000UL;
		}
		System::Void out37_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000002000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000002000000000UL;
			else
				psIni->nWpoints |= 0x0000002000000000UL;
		}
		System::Void out38_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000004000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000004000000000UL;
			else
				psIni->nWpoints |= 0x0000004000000000UL;
		}
		System::Void out39_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000008000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000008000000000UL;
			else
				psIni->nWpoints |= 0x0000008000000000UL;
		}
		System::Void out40_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000010000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000010000000000UL;
			else
				psIni->nWpoints |= 0x0000010000000000UL;
		}
		System::Void out41_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000020000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000020000000000UL;
			else
				psIni->nWpoints |= 0x0000020000000000UL;
		}
		System::Void out42_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000040000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000040000000000UL;
			else
				psIni->nWpoints |= 0x0000040000000000UL;
		}
		System::Void out43_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000080000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000080000000000UL;
			else
				psIni->nWpoints |= 0x0000080000000000UL;
		}
		System::Void out44_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000100000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000100000000000UL;
			else
				psIni->nWpoints |= 0x0000100000000000UL;
		}
		System::Void out45_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000200000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000200000000000UL;
			else
				psIni->nWpoints |= 0x0000200000000000UL;
		}
		System::Void out46_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000400000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000400000000000UL;
			else
				psIni->nWpoints |= 0x0000400000000000UL;
		}
		System::Void out47_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0000800000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0000800000000000UL;
			else
				psIni->nWpoints |= 0x0000800000000000UL;
		}
		System::Void out48_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if((psIni->nWpoints &   0x0001000000000000UL) != 0)
			   psIni->nWpoints &=  ~0x0001000000000000UL;
			else
				psIni->nWpoints |= 0x0001000000000000UL;
		}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 timerTest();
		 }

	private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void IOForm_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void holdBt1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[0].uHoldI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[0].uHoldI;
			 else
				 psIni->nRpoints |= psIni->asSilos[0].uHoldI;
		 }
private: System::Void holdBt2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[1].uHoldI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[1].uHoldI;
			 else
				 psIni->nRpoints |= psIni->asSilos[1].uHoldI;
		 }
private: System::Void enableIOCb_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 bOutputTest = enableIOCb->Checked;
			 if(bOutputTest == true)
			 {
				 out0->Enabled = true;
				 out1->Enabled = true; out2->Enabled = true; out3->Enabled = true; out4->Enabled = true; out5->Enabled = true;
				 out6->Enabled = true; out7->Enabled = true; out8->Enabled = true; out9->Enabled = true; out10->Enabled = true;
				 out11->Enabled = true; out12->Enabled = true; out13->Enabled = true; out14->Enabled = true; out15->Enabled = true;
				 out16->Enabled = true; out17->Enabled = true; out18->Enabled = true; out19->Enabled = true; out20->Enabled = true;
				 out21->Enabled = true; out22->Enabled = true; out23->Enabled = true; out24->Enabled = true; out25->Enabled = true;
				 out26->Enabled = true; out27->Enabled = true; out28->Enabled = true; out29->Enabled = true; out30->Enabled = true;
				 out31->Enabled = true; out32->Enabled = true; out33->Enabled = true; out34->Enabled = true; out35->Enabled = true;
				 out36->Enabled = true; out37->Enabled = true; out38->Enabled = true; out39->Enabled = true; out40->Enabled = true;
				 out41->Enabled = true; out42->Enabled = true; out43->Enabled = true; out44->Enabled = true; out45->Enabled = true;
				 out46->Enabled = true; out47->Enabled = true; out48->Enabled = true; out49->Enabled = true; out50->Enabled = true;
				 out51->Enabled = true; out52->Enabled = true; out53->Enabled = true; out54->Enabled = true; out55->Enabled = true;
				 out56->Enabled = true; out57->Enabled = true; out58->Enabled = true; out59->Enabled = true; out60->Enabled = true;
				 out61->Enabled = true; out62->Enabled = true; out63->Enabled = true; out64->Enabled = true; out65->Enabled = true;
				 out66->Enabled = true; out67->Enabled = true; out68->Enabled = true; out69->Enabled = true; out70->Enabled = true;
				 out71->Enabled = true; out72->Enabled = true; out73->Enabled = true; out74->Enabled = true; out75->Enabled = true;
				 out76->Enabled = true; out77->Enabled = true; out78->Enabled = true; out79->Enabled = true; out80->Enabled = true;
			 }
			 else
			 {
				 out0->Enabled = false;
				 out1->Enabled = false; out2->Enabled = false; out3->Enabled = false; out4->Enabled = false; out5->Enabled = false;
				 out6->Enabled = false; out7->Enabled = false; out8->Enabled = false; out9->Enabled = false; out10->Enabled = false;
				 out11->Enabled = false; out12->Enabled = false; out13->Enabled = false; out14->Enabled = false; out15->Enabled = false;
				 out16->Enabled = false; out17->Enabled = false; out18->Enabled = false; out19->Enabled = false; out20->Enabled = false;
				 out21->Enabled = false; out22->Enabled = false; out23->Enabled = false; out24->Enabled = false; out25->Enabled = false;
				 out26->Enabled = false; out27->Enabled = false; out28->Enabled = false; out29->Enabled = false; out30->Enabled = false;
				 out31->Enabled = false; out32->Enabled = false; out33->Enabled = false; out34->Enabled = false; out35->Enabled = false;
				 out36->Enabled = false; out37->Enabled = false; out38->Enabled = false; out39->Enabled = false; out40->Enabled = false;
				 out41->Enabled = false; out42->Enabled = false; out43->Enabled = false; out44->Enabled = false; out45->Enabled = false;
				 out46->Enabled = false; out47->Enabled = false; out48->Enabled = false; out49->Enabled = false; out50->Enabled = false;
				 out51->Enabled = false; out52->Enabled = false; out53->Enabled = false; out54->Enabled = false; out55->Enabled = false;
				 out56->Enabled = false; out57->Enabled = false; out58->Enabled = false; out59->Enabled = false; out60->Enabled = false;
				 out61->Enabled = false; out62->Enabled = false; out63->Enabled = false; out64->Enabled = false; out65->Enabled = false;
				 out66->Enabled = false; out67->Enabled = false; out68->Enabled = false; out69->Enabled = false; out70->Enabled = false;
				 out71->Enabled = false; out72->Enabled = false; out73->Enabled = false; out74->Enabled = false; out75->Enabled = false;
				 out76->Enabled = false; out77->Enabled = false; out78->Enabled = false; out79->Enabled = false; out80->Enabled = false;
			 }
		 }
private: System::Void ERHInpBt1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[0].uDropReadyI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[0].uDropReadyI;
			 else
				 psIni->nRpoints |= psIni->asSilos[0].uDropReadyI;
		 }
private: System::Void ERHInpBt2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[1].uDropReadyI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[1].uDropReadyI;
			 else
				 psIni->nRpoints |= psIni->asSilos[1].uDropReadyI;
		 }
private: System::Void ERHInpBt3_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[3].uDropReadyI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[3].uDropReadyI;
			 else
				 psIni->nRpoints |= psIni->asSilos[3].uDropReadyI;
		 }
private: System::Void ERHInpBt4_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[4].uDropReadyI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[4].uDropReadyI;
			 else
				 psIni->nRpoints |= psIni->asSilos[4].uDropReadyI;
		 }
private: System::Void ERHInpBt5_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[6].uDropReadyI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[6].uDropReadyI;
			 else
				 psIni->nRpoints |= psIni->asSilos[6].uDropReadyI;
		 }
private: System::Void ERHInpBt6_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[7].uDropReadyI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[7].uDropReadyI;
			 else
				 psIni->nRpoints |= psIni->asSilos[7].uDropReadyI;
		 }
private: System::Void HInpBt1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[9].uDropReadyI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[9].uDropReadyI;
			 else
				 psIni->nRpoints |= psIni->asSilos[9].uDropReadyI;
		 }
private: System::Void RoHeadInpBt6_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[7].uHoldI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[7].uHoldI;
			 else
				 psIni->nRpoints |= psIni->asSilos[7].uHoldI;
		 }
private: System::Void DInpBt1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[0].uDoneI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[0].uDoneI;
			 else
				 psIni->nRpoints |= psIni->asSilos[0].uDoneI;
		 }
private: System::Void DInpBt2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[1].uDoneI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[1].uDoneI;
			 else
				 psIni->nRpoints |= psIni->asSilos[1].uDoneI;
		 }
private: System::Void DInpBt4_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[3].uDoneI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[3].uDoneI;
			 else
				 psIni->nRpoints |= psIni->asSilos[3].uDoneI;
		 }
private: System::Void DInpBt5_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[4].uDoneI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[4].uDoneI;
			 else
				 psIni->nRpoints |= psIni->asSilos[4].uDoneI;
		 }
private: System::Void DInpBt7_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[6].uDoneI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[6].uDoneI;
			 else
				 psIni->nRpoints |= psIni->asSilos[6].uDoneI;
		 }
private: System::Void DInpBt8_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[7].uDoneI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[7].uDoneI;
			 else
				 psIni->nRpoints |= psIni->asSilos[7].uDoneI;
		 }
private: System::Void DInpBtIR_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[9].uDoneI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[9].uDoneI;
			 else
				 psIni->nRpoints |= psIni->asSilos[9].uDoneI;
		 }
private: System::Void holdBt4_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[3].uHoldI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[3].uHoldI;
			 else
				 psIni->nRpoints |= psIni->asSilos[3].uHoldI;
		 }
private: System::Void holdBt5_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[4].uHoldI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[4].uHoldI;
			 else
				 psIni->nRpoints |= psIni->asSilos[4].uHoldI;
		 }
private: System::Void holdBt7_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[6].uHoldI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[6].uHoldI;
			 else
				 psIni->nRpoints |= psIni->asSilos[6].uHoldI;
		 }
private: System::Void holdBtIR_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ((psIni->nRpoints & psIni->asSilos[9].uHoldI) > 0)
				psIni->nRpoints &= ~psIni->asSilos[9].uHoldI;
			 else
				 psIni->nRpoints |= psIni->asSilos[9].uHoldI;
		 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void inp12Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uSiloBitCheckI[0]) > 0)
				psIni->nRpoints &= ~psIni->uSiloBitCheckI[0];
			 else
				 psIni->nRpoints |= psIni->uSiloBitCheckI[0];

		 }
private: System::Void inp13Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			if ((psIni->nRpoints & psIni->uSiloBitCheckI[1]) > 0)
				psIni->nRpoints &= ~psIni->uSiloBitCheckI[1];
			 else
				 psIni->nRpoints |= psIni->uSiloBitCheckI[1];
		 }
private: System::Void inp14Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uSiloBitCheckI[2]) > 0)
				psIni->nRpoints &= ~psIni->uSiloBitCheckI[2];
			 else
				 psIni->nRpoints |= psIni->uSiloBitCheckI[2];
		 }
private: System::Void inp15Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			if ((psIni->nRpoints & psIni->uSiloBitCheckI[3]) > 0)
				psIni->nRpoints &= ~psIni->uSiloBitCheckI[3];
			 else
				 psIni->nRpoints |= psIni->uSiloBitCheckI[3];
		 }
private: System::Void inp16Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[0]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[0];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[0];
		 }
private: System::Void inp17Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[1]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[1];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[1];
		 }
private: System::Void inp18Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[2]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[2];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[2];
		 }
private: System::Void inp19Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[3]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[3];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[3];
		 }
private: System::Void inp20Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[4]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[4];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[4];
		 }
private: System::Void inp21Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[5]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[5];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[5];
		 }
private: System::Void inp22Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[6]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[6];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[6];
		 }
private: System::Void inp23Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[7]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[7];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[7];
		 }
private: System::Void inp24Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[8]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[8];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[8];
		 }
private: System::Void inp25Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[9]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[9];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[9];
		 }
private: System::Void inp26Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[10]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[10];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[10];
		 }
private: System::Void inp27Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[11]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[11];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[11];
		 }
private: System::Void inp28Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[12]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[12];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[12];
		 }
private: System::Void inp29Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[13]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[13];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[13];
		 }
private: System::Void inp30Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[14]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[14];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[14];
		 }
private: System::Void inp31Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			if ((psIni->nRpoints & psIni->uBitCheckI[15]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[15];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[15];
		 }
private: System::Void inp32Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[16]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[16];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[16];
		 }
private: System::Void inp33Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			if ((psIni->nRpoints & psIni->uBitCheckI[17]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[17];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[17];
		 }
private: System::Void inp34Bt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uBitCheckI[18]) > 0)
				psIni->nRpoints &= ~psIni->uBitCheckI[18];
			 else
				 psIni->nRpoints |= psIni->uBitCheckI[18];
		 }
private: System::Void RInpBt_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uReceivedTargetI) > 0)
				psIni->nRpoints &= ~psIni->uReceivedTargetI;
			 else
				 psIni->nRpoints |= psIni->uReceivedTargetI;
		 }
private: System::Void KInpBt_Click(System::Object^  sender, System::EventArgs^  e) {
			if ((psIni->nRpoints & psIni->uKeepAliveI) > 0)
				psIni->nRpoints &= ~psIni->uKeepAliveI;
			 else
				 psIni->nRpoints |= psIni->uKeepAliveI;
		 }

private: System::Void laneTareBt1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uLaneTareI[0]) > 0)
				psIni->nRpoints &= ~psIni->uLaneTareI[0];
			 else
				 psIni->nRpoints |= psIni->uLaneTareI[0];
		 }
private: System::Void laneTareBt2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uLaneTareI[1]) > 0)
				psIni->nRpoints &= ~psIni->uLaneTareI[1];
			 else
				 psIni->nRpoints |= psIni->uLaneTareI[1];
		 }
private: System::Void laneTareBt3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uLaneTareI[2]) > 0)
				psIni->nRpoints &= ~psIni->uLaneTareI[2];
			 else
				 psIni->nRpoints |= psIni->uLaneTareI[2];
		 }
private: System::Void laneTareBt4_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((psIni->nRpoints & psIni->uLaneTareI[3]) > 0)
				psIni->nRpoints &= ~psIni->uLaneTareI[3];
			 else
				 psIni->nRpoints |= psIni->uLaneTareI[3];
		 }
};
}
