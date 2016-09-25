///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// version 1.3													//
// Language:    Visual C++, Visual Studio 2013                   //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	              //
// Application: Object Oriented Design,Project-2 2015             //
// Author:      Tanmay Fadnavis, Syracuse University				//
//				315-560-3370, tfadnavi@syr.edu						//
/////////////////////////////////////////////////////////////////////////////  
///////////////////////////////////////////////////////////////////


#include "XmlDocument.h"
#include "../../XmlElementParts/XmlElementParts/xmlElementParts.h"
#include "../../XmlElementParts/XmlElementParts/Tokenizer.h"
#include "../../XmlElementParts/XmlElementParts/itokcollection.h"

#include <iostream>
#include <stack>
#include <memory>

using namespace XmlProcessing;

//------------------< Default constructor >---------------
XmlProcessing::XmlDocument::XmlDocument()
{
	pDocElement_ = makeDocElement();
}

//----------------< Function to add root element >-----------

void XmlProcessing::XmlDocument::addRootElement(const std::string element)
{
	sPtr node = makeTaggedElement(element);
	pDocElement_->addChild(node);
}

//-----------------< Parameterized contructor for XmlDocument >---------------------

XmlProcessing::XmlDocument::XmlDocument(const std::string& src, const std::string& srcType)
{
	bool isFile = true;
	try
	{
		if (srcType == "filename")
		{
			isFile = true;
		}
		else if (srcType == "string")
		{
			isFile = false;
		}

		Toker toker(src, isFile);
		toker.setMode(Toker::xml);
		XmlParts parts(&toker);

		std::stack < std::shared_ptr<AbstractXmlElement>> s;
		pDocElement_ = makeDocElement();
		s.push(pDocElement_);
		while (parts.get()){
			sPtr temp = parse(parts.show());
			
			if (temp == nullptr)
				s.pop();
			else
			{
				
				s.top()->addChild(temp);
				TaggedElement* te = dynamic_cast<TaggedElement*>(temp.get());
				if (te != nullptr)
					s.push(temp);
			}
		}

	}
	catch (std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}
}

//------------------< Move Constructor >----------------------
XmlProcessing::XmlDocument::XmlDocument(XmlDocument&& x) : pDocElement_(x.pDocElement_), found_(x.found_)
{
	x.pDocElement_ = nullptr;
	x.found_.clear();
}

//------------------< Move Assignment >-----------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::operator=(XmlDocument&& x)
{
	if (this == &x) return *this;
	pDocElement_ = x.pDocElement_;
	found_ = x.found_;
	x.pDocElement_ = nullptr;
	x.found_.clear();
	return *this;
}

//-------------------< the toString method >-----------------
std::string XmlProcessing::XmlDocument::toString()
{
	return pDocElement_->toString();
}

//--------------< Method to check if the object is empty >-----------
bool XmlProcessing::XmlDocument::isEmpty()
{
	return (pDocElement_ == nullptr);
}

//---------------------< Method to parse the tokens >----------------
std::shared_ptr<AbstractXmlElement> XmlProcessing::XmlDocument::parse(std::string& src)
{
	sPtr node;
	if (src.find("<") != std::string::npos && src.find("!") != std::string::npos)
	{
		std::size_t found = src.find("<");
		std::size_t foundLast = src.find(">");
		std::string temp = src.substr(found + 6, foundLast - (found + 6 ) -4);
		node = makeCommentElement(temp);
	}
	else if (src.find("<") != std::string::npos && src.find("/") !=std::string::npos && src.find("?")==std::string::npos)
	{ return nullptr; }
	else if (src.find("<") != std::string::npos && src.find("?") !=std::string::npos)
	{	node = makeProcInstrElement(src); }
	else if (src.find("<") != std::string::npos && src.find("!") == std::string::npos && src.find("?") == std::string::npos)
	{
		std::size_t found = src.find("<");
		std::size_t foundSpace = src.find(" ", found + 2);
		std::size_t foundEnd = src.find(">");
		std::string temp = src.substr(found + 2, foundSpace - (found + 2) );
		node = makeTaggedElement(temp);
		std::string tempString = src.substr(foundSpace + 1, foundEnd - (foundSpace + 1));
		for (std::size_t i = 0; i < tempString.length() - 1;)
		{
			std::string attrName, attrValue;
			if (tempString.find("=",i) != std::string::npos)
			{
				attrName = tempString.substr(i, tempString.find("=")-1);
				if (tempString.find("\"",i) !=std::string::npos)
				{
					std::size_t tempSize = tempString.find("\"", i);
					std::size_t tempSize2 = tempString.find("\"", tempSize + 1);
					attrValue = tempString.substr(tempSize + 1, tempSize2 - (tempSize + 1));
					i = tempSize2+1;
				}
				else if (tempString.find("\'",i) !=std::string::npos)
				{
					std::size_t tempSize = tempString.find("\'", i);
					std::size_t tempSize2 = tempString.find("\'", tempSize + 1);
					attrValue = tempString.substr(tempSize + 1, tempSize2 - (tempSize + 1));
					i = tempSize2+1;
				}
				node->addAttrib(attrName, attrValue);
			}
			else break;
		}
	}
	else if (src.find("<") == std::string::npos)
	{ node = makeTextElement(src); }
	return node;
}

//----< return found results >-----------------------------------------------

std::vector<std::shared_ptr<AbstractXmlElement>> XmlDocument::select()
{
	return std::move(found_);  // returns results and clears found_
}

//-----< function to search element based on unique id attributes >----------

XmlDocument& XmlProcessing::XmlDocument::getElementById(const std::string& attribute, const std::string& value)
{
	DFS(pDocElement_, attribute, value);
		return *this;
}

//----------< function to perform the DFS traversal of the tree >---------------
bool XmlProcessing::XmlDocument::DFS(std::shared_ptr<AbstractXmlElement> node, const std::string& attribute, const std::string& value)
{
	for (auto attib:node->getAttributes())
	{
		if (attib.first == attribute && attib.second == value)
		{
			found_.push_back(node);
			break;
		}
	}
	for (auto pChild : node->children())
		DFS(pChild, attribute, value);

	return (found_.size() > 0);
}

//-----------< Function to search all elements with a particular tag >-----------------
XmlDocument& XmlProcessing::XmlDocument::elements(const std::string& tag)
{
	findElementsForTag(pDocElement_, tag);
	return *this;
}

//------------< Helper Function for elements >-------------------------
bool XmlProcessing::XmlDocument::findElementsForTag(std::shared_ptr<AbstractXmlElement> node, const std::string& tag)
{
	if (node->value() == tag)
	{
		found_.push_back(node);
		return true;
	}
	for (auto pChild : node->children())
		findElementsForTag(pChild, tag);

	return (found_.size() > 0);
}

//--------------< Function to search for a single element with tag  >--------------
XmlDocument& XmlProcessing::XmlDocument::element(const std::string& tag)
{
	findElementForTag(pDocElement_, tag);
	return *this;
}

//-------------< Helper Function for element >-------------------
bool XmlProcessing::XmlDocument::findElementForTag(std::shared_ptr<AbstractXmlElement> node, const std::string& tag)
{
	if (node->value() == tag)
	{
		found_.push_back(node);
		return (found_.size() > 0);
	}
	for (auto pChild : node->children())
		findElementForTag(pChild, tag);

	return (found_.size() > 0);
}

//--------------< Function to add child to an element >----------------------
bool XmlProcessing::XmlDocument::addChild(std::shared_ptr<AbstractXmlElement> parent,std::shared_ptr<AbstractXmlElement> pChild)
{
	if (parent->addChild(pChild))
		return true;
	else
		return false;
}

//-------------< Function to remove child from an element >-------------
bool XmlProcessing::XmlDocument::removeChild(std::shared_ptr<AbstractXmlElement> parent,std::shared_ptr<AbstractXmlElement> pChild)
{
	if (parent->removeChild(pChild))
		return true;
	else
		return false;
}


//----------< Function to find the attributes of an element >-----------

std::vector<std::pair<std::string, std::string>> XmlProcessing::XmlDocument::attributes(std::shared_ptr<AbstractXmlElement> node)
{
	
	std::vector<std::pair<std::string, std::string>> attributesVector;	//vector for storing attibutes
	for (auto attib : node->getAttributes())
	{
		std::pair<std::string, std::string> atPair(attib.first, attib.second);
		attributesVector.push_back(atPair);
	}
	return attributesVector;
}

//----------< Function to find the children of an element  >-----------
std::vector<std::shared_ptr<AbstractXmlElement>> XmlProcessing::XmlDocument::children(const std::string& tag)
{
	std::shared_ptr<AbstractXmlElement> node = element(tag).select().front();
	std::vector<std::shared_ptr<AbstractXmlElement>> childrenVector;	//vector for storing children
	childrenVector = node->children();
	return childrenVector;
}

//-----------< Function to add attribute of an element >--------------
bool XmlProcessing::XmlDocument::addAttribute(const std::string& name, const std::string& value)
{
	std::shared_ptr<AbstractXmlElement> node = this->select().front();
	if (node->addAttrib(name, value))
		return true;
	else
		return false;
}

//-----------< Function to remove attribute of an element >-----------
bool XmlProcessing::XmlDocument::removeAttribute(const std::string& name)
{
	std::shared_ptr<AbstractXmlElement> node = this->select().front();
	if (node->removeAttrib(name))
		return true;
	else
		return false;
}

//-----------< Function to add a child to an element >---------------
bool XmlProcessing::XmlDocument::addChild(std::shared_ptr<AbstractXmlElement> pChild)
{
	std::shared_ptr<AbstractXmlElement> node = this->select().front();
	if (node->addChild(pChild))
		return true;
	else
		return false;
}

//-----------< Function to remove a child from an element >-----------
bool XmlProcessing::XmlDocument::removeChild(std::shared_ptr<AbstractXmlElement> pChild)
{
	//std::shared_ptr<AbstractXmlElement> node = element(pChild).select().front();
	std::vector<std::shared_ptr<AbstractXmlElement>> x=pChild->children();

	for (auto y : x)
	{
		pChild->removeChild(y);
	}
	return true;
}


#ifdef TEST_XMLDOCUMENT

int main()
{
	XmlDocument doc("../Debug/LectureNote.xml", "filename");
	std::cout<<doc.toString();
	bool flag = true;
	for (auto x : doc.getElementById("city", "syracuse").select())
	{
		flag = false;
		std::cout << "Elements are  " << x->toString();
	}
	if (flag)
		std::cout << "No such element exists\n";
	for (auto x : doc.elements("title").select())
	{
		flag = false;
		std::cout << "Elements are  " << x->toString();
	}
	if (flag)
  std::cout << "\n\n";
}

#endif