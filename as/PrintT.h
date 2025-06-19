#pragma once
#include "StdAfx.h"
#include "PreView.h"
#include <queue>
using namespace System;
using namespace System::Threading;

namespace As
{
// THREAD class printing tickets ==============================================
ref class CPrint
{
public:
	CPrint(All^ pAllIn, String^ pName, bool *pbOkIn, int nPrinterIn)
	{
		pAll = pAllIn;
		pbOk = pbOkIn;
		nPrinter = nPrinterIn;

		printDoc = (gcnew System::Drawing::Printing::PrintDocument());
		printDoc->PrinterSettings->PrinterName = pName;
		printDoc->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &CPrint::printDoc_PrintPage);

		printFont = gcnew System::Drawing::Font("Courier New", 10, FontStyle::Regular);
	}

private: 
	All^ pAll;
	bool *pbOk;
	int nPrinter;
	String^ printBuf;
	System::Drawing::Printing::PrintDocument^  printDoc;
	System::Drawing::Font^ printFont;

public:
	//-------------------------------------------------------------------------
	void ThreadProc(Object^ pQueIn)
	{
		System::Collections::Generic::Queue<String^>^ printq = (System::Collections::Generic::Queue<String^> ^)pQueIn;

		while(true)
		{	
			*pbOk = printDoc->PrinterSettings->IsValid; 
					 
			if(*pbOk && (printq->Count > 0))
			{								 
				printBuf = (String^)printq->Dequeue();

				try
				{
					printDoc->Print();
				}
				catch (System::Drawing::Printing::InvalidPrinterException^ ex ) 
				{
					 pAll->pExc += "\nPRINT Exception: " + ex->Message;
				} 	
				catch (System::ComponentModel::Win32Exception^ ex ) 
				{
					 pAll->pExc += "\nPRINT Win32 Exception: " + ex->Message;
				} 
				if(pAll->eAsType != A_PROD)
				{
//					MessageBox::Show(printBuf, "Printer "+nPrinter.ToString()
//						 , System::Windows::Forms::MessageBoxButtons::OK);
//					PreView^ preView = gcnew PreView(pAll);
//					preView->Show();
				}
			}
			else
			{
				Thread::Sleep(200);
			}
		}
	}

	//-------------------------------------------------------------------------
private: System::Void printDoc_PrintPage(System::Object^  sender, 
			 System::Drawing::Printing::PrintPageEventArgs^  e) 
		 {
			 e->Graphics->DrawString(printBuf, printFont, Brushes::Black, 0, 1);
		 }
		 
};
}
