#ifndef DISPLAY_H
#define DISPLAY_H

/////////////////////////////////////////////////////////////////////////////
// Display.h - Supports operations to display the requirements of Pr2      //
// ver 1.0                                                                //
// ----------------------------------------------------------------------- // 
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	                       //
// Application: Object Oriented Design,Project-1 2015                      //
// Author:      Tanmay Fadnavis, Syracuse University					  //
//				315-560-3370, tfadnavi@syr.edu							//
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This module provides Display class. The Display class provides
* methods to display the information,it receives the XmlDocument
* object from the Executive. It displays all the requirements
* of project-2.
*
* Public Interface:
* =================
*	Display(XmlProcessing::XmlDocument&);
*	void displayRequirement3();
*	void displayRequirement4();
*	void displayRequirement5();
*	void displayRequirement6();
*	void displayRequirement7a();
*	void displayRequirement7b();
*	void displayRequirement7c();
*	void displayRequirement8a();
*	void displayRequirement8b();
*	void displayRequirement9a();
*	void displayRequirement9b();
*	void displayRequirement10();
*
* Required Files:
* ===============
* Display.h Display.cpp XmlDocument.h XmlElement.h XmlElementParts.h
*
* Build Command:
* ==============
* cl /EHa /TEST_DISPLAY Display.cpp
*
* Maintenance History:
* ====================
* ver 1.0, First Release
* March 15,2015
*/


#include "../XmlDocument/XmlDocument/XmlDocument.h"

class Display
{
	public:
		Display(XmlProcessing::XmlDocument&);

		//For basic display of the parse tree
		void displayRequirement3();

		//For building XML from string
		void displayRequirement3b();

		//For move operations.
		void displayRequirement4();

		//For get element by Id
		void displayRequirement5();

		//For elements with a particular tag
		void displayRequirement6();

		//For adding a child to element found by Id,Tag
		void displayRequirement7a();

		//For adding root to empty document tree.
		void displayRequirement7b();

		//For removing a child
		void displayRequirement7c();

		//For getting attributes of a particular element
		void displayRequirement8a();

		//For getting the children of a particular element
		void displayRequirement8b();

		//For adding the attributes
		void displayRequirement9a();

		//For deleting the attributes
		void displayRequirement9b();

		void displayRequirement10();

	private:
		XmlProcessing::XmlDocument& doc_;
};

#endif