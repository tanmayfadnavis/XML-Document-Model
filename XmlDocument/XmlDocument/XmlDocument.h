#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.3                                                      //
// Language:    Visual C++, Visual Studio 2013					//
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	           //
// Application: Object Oriented Design,Project-2 2015          //
// Author:      Tanmay Fadnavis, Syracuse University		   //
//				315-560-3370, tfadnavi@syr.edu				  //
// Original Author:      Jim Fawcett, CST 4-187, 443-3948      //
//              jfawcett@twcny.rr.com						//
// Date: 17/03/2015											//
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with 
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, 
*     XmlElement.h, XmlElement.cpp
*
* Public Interfaces:
* -----------------
*   XmlDocument(const std::string& src, const std::string& srcType);
*	XmlDocument(XmlDocument&& x);
*	XmlDocument& operator=(XmlDocument&& x);
*	std::shared_ptr<AbstractXmlElement> parse(std::string& src);
*	std::string toString();
*	bool DFS(sPtr node, const std::string& attribute, const std::string& value);
*	XmlDocument& getElementById(const std::string& attribute, const std::string& value); 
*   XmlDocument& element(const std::string& tag);
*	bool findElementForTag(sPtr node, const std::string& tag);
*	bool findElementsForTag(sPtr node, const std::string& tag);
*    XmlDocument& elements(const std::string& tag);
*	bool addChild(std::shared_ptr<AbstractXmlElement> parent,std::shared_ptr<AbstractXmlElement> pChild);
*	bool removeChild(std::shared_ptr<AbstractXmlElement> parent,std::shared_ptr<AbstractXmlElement> pChild);
*	std::vector<std::shared_ptr<AbstractXmlElement>> children(const std::string& tag = "");
*	std::vector<std::pair<std::string, std::string>> attributes(sPtr node);
*    XmlDocument& descendents(const std::string& tag = ""); 
*   std::vector<sPtr> select();  
*	bool addAttribute(const std::string& name, const std::string& value);
*	bool removeAttribute(const std::string& name);
*	bool addChild(std::shared_ptr<AbstractXmlElement> pChild);
*	bool removeChild(std::shared_ptr<AbstractXmlElement> pChild);
*
* Build Process:
* --------------
*   devenv AST.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.3:March  15
* - added more functionality
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*/

#include <memory>
#include <string>
#include "../XmlElement/XmlElement.h"

namespace XmlProcessing
{
  class XmlDocument
  {
  public:
    using sPtr = std::shared_ptr < AbstractXmlElement > ;

	//Default constructor
	XmlDocument();

    XmlDocument(const std::string& src, const std::string& srcType);

	//move assignment and move constructor.
	XmlDocument(XmlDocument&& x);
	XmlDocument& operator=(XmlDocument&& x);

	std::shared_ptr<AbstractXmlElement> parse(std::string& src);	
	std::string toString();

	bool isEmpty();

	//Method to add root element.
	void addRootElement(const std::string elem);

	//DFS for searching the tree.
	bool DFS(sPtr node, const std::string& attribute, const std::string& value);

	XmlDocument& getElementById(const std::string& attribute, const std::string& value); //for finding element by unique ID.
    XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
	bool findElementForTag(sPtr node, const std::string& tag);
	bool findElementsForTag(sPtr node, const std::string& tag);
    XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag

	bool addChild(std::shared_ptr<AbstractXmlElement> parent,std::shared_ptr<AbstractXmlElement> pChild);
	bool removeChild(std::shared_ptr<AbstractXmlElement> parent,std::shared_ptr<AbstractXmlElement> pChild);

	std::vector<std::shared_ptr<AbstractXmlElement>> children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
	std::vector<std::pair<std::string, std::string>> attributes(sPtr node);					//Found the attributes of the element.

    XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
    std::vector<sPtr> select();                            // return reference to found_.  Use std::move(found_) to clear found_

	bool addAttribute(const std::string& name, const std::string& value);
	bool removeAttribute(const std::string& name);

	bool addChild(std::shared_ptr<AbstractXmlElement> pChild);
	bool removeChild(std::shared_ptr<AbstractXmlElement> pChild);

  private:
    sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
  };
}
#endif
