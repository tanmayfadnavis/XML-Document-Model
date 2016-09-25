/////////////////////////////////////////////////////////////////////////////
// Executive.cpp - The main entry point for the application- XMLDocumentModel//
// ver 1.0                                                                //
// ----------------------------------------------------------------------- // 
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	                       //
// Application: Object Oriented Design,Project-2 2015                      //
// Author:      Tanmay Fadnavis, Syracuse University					  //
//				315-560-3370, tfadnavi@syr.edu							//
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This is the entry point for the application-XMLDocument Model.
* It creates an XML Model by calling the XmlDocument file.
* It then calls the display package to demonstrate each and every requirement.
* Public Interface:
* =================
*	int main(int argc, char *argv[])
*
* Required Files:
* ===============
* Display.h XmlDocument.h XmlElement.h XmlElementParts.h
*
* Build Command:
* ==============
* cl /EHa / Executive.cpp
*
* Maintenance History:
* ====================
* ver 1.0, First Release
* March 15 2015
*/




#include "../Display/Display.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"

#include<string>
#include<iostream>

	int main(int argc, char *argv[])
	{
		//For requirement-3
		XmlProcessing::XmlDocument doc(argv[1],"filename");
		Display d(doc);
		d.displayRequirement3();

		d.displayRequirement5();

		d.displayRequirement6();

		d.displayRequirement7a();

		d.displayRequirement7c();
		
		d.displayRequirement8a();
		
		d.displayRequirement8b();
		
		d.displayRequirement9a();
		
		d.displayRequirement9b();
		
		d.displayRequirement3b();
		
		d.displayRequirement4();
		
		d.displayRequirement7b();
		
		d.displayRequirement10();
		getchar();
}
