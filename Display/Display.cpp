///////////////////////////////////////////////////////////////////
// Display.cpp - a package to display requirements.            //
// version 1.0													//
// Language:    Visual C++, Visual Studio 2013                   //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	              //
// Application: Object Oriented Design,Project-2 2015             //
// Author:      Tanmay Fadnavis, Syracuse University				//
//				315-560-3370, tfadnavi@syr.edu						//
/////////////////////////////////////////////////////////////////////////////  
///////////////////////////////////////////////////////////////////

#include "Display.h"

#include<iostream>
#include<fstream>

//---------< Constructor to initialize the Display object >--------------
Display::Display(XmlProcessing::XmlDocument& doc) :doc_(doc)
{

}

//---------< Function to display the internal parse tree >--------------
void Display::displayRequirement3()
{
	std::cout << "-=-=-=-=-=- Demonstrating Requirement 3 to build an internal parse tree-=-=-=--=\n";
	std::cout << doc_.toString() << "\n\n";
}

//------------< Function to display string input >----------------
void Display::displayRequirement3b()
{
	std::cout << "-=-=-=-= Demonstrating making XML from a string-=-=-=-=-\n";
	std::string xmlString = "<!-- XML String --><Country name=\"USA\"><city>Syracuse</city></Country>";
	XmlProcessing::XmlDocument doc2(xmlString, "string");
	std::cout << doc2.toString() << "\n\n";
}

//-----------< Function to display the move constructor >------------
void Display::displayRequirement4()
{
	std::cout << "-=-=-=-=-=-=-Demonstrating Requirement 4 move constructor-=-=-=-=-=-=-=\n";
	XmlProcessing::XmlDocument doc1("Debug/LectureNote.xml", "filename");
	XmlProcessing::XmlDocument doc2 = std::move(doc1);
	std::cout << "printing doc2\n";
	std::cout << doc2.toString() <<"\n";
	std::cout << "printing doc1\n";
	if (doc1.isEmpty())
		std::cout << "doc1 is empty\n";
	std::cout << "Thus, by printing doc2, the tree is being printed and doc1 is empty.\n\n";
}

//-----------< Function to display getelementbyId >--------------
void Display::displayRequirement5()
{
	bool flag = true;
	std::cout << "-=-=-=-=- Demonstrating Requirement 5 to get elemeny By Id-=-=-=--=\n";
	std::cout << "The arguments are city and syracuse,hence we get the author element\n";
	for (auto x : doc_.getElementById("city", "syracuse").select())
	{
		flag = false;
		std::cout << "Elements are  " << x->toString() <<"\n\n";
	}
	if (flag)
		std::cout << "No such element exists\n";
}

//-------------< Function to display getting elements of similar tags >----------------
void Display::displayRequirement6()
{
	bool flag = true;
	std::cout << "-=-=-=-=- Demonstrating Requirement 6 to find collection of elements by Tag-=-=-=--=\n";
	std::cout << "The argument is title. Hence, we are getting the results for title tags\n";
	for (auto x : doc_.elements("title").select())
	{
		flag = false;
		std::cout << "Elements are  " << x->toString() <<"\n\n";
	}
	if (flag)
		std::cout << "No such element exists\n";
}

//-------------< Function to display adding a child to element >--------------
void Display::displayRequirement7a()
{
	std::cout << "-=-=-=-=- Demonstrating Requirement 7 to add a child-=-=-=--=\n";
	std::cout << "The argument is reference node. Hence the tagged element is being added to reference node\n";
	using sptr = std::shared_ptr < XmlProcessing::AbstractXmlElement >;
	sptr child = XmlProcessing::makeTaggedElement("adding this Taged child to reference Node");


	if (doc_.addChild(doc_.element("reference").select().front(), child))
	{
		std::cout << "Child addedd auccessfully\n";
		std::cout << doc_.toString() <<"\n\n";
	}
	else
	{
		std::cout << "Not able to add child\n";
	}

}

//-----------< Function to display adding a root element to empty tree >---------------
void Display::displayRequirement7b()
{
	std::cout << "-=-=-Demonstrating the requirement to add a root element to empty document tree-=-=-=\n";
	std::cout << " We are making a tag element root and adding to empty tree\n";
	XmlProcessing::XmlDocument d;
	d.addRootElement("root");
	std::cout<<d.toString() <<"\n\n";

}

//-------------< Function to display removing a child from an element >-------------
void Display::displayRequirement7c()
{
	std::cout << "-=-=-=-=-Demonstrating removing a child from the element-=-=-=-=-=-=-\n";
	std::cout << "Removing a child\n";
	std::cout << "The argument is title. Hence, the text child of the first title element is being removed\n";
	if (doc_.removeChild(doc_.element("title").select().front()))
	{
		std::cout << "Child removed successfully\n";
		std::cout << doc_.toString() << "\n\n";
	}
	else
	{
		std::cout << "Not able to remove child\n";
	}
	
}

//--------------< Function to display attributes of a particular element >-------------
void Display::displayRequirement8a()
{
	std::cout << "-=-=-=-Demonstrating the requirement for showing the attributes of a particular node-=-=-=-=-\n";
	std::vector<std::pair<std::string, std::string>> attriv = doc_.attributes(doc_.element("LectureNote").select().front());
	std::cout << "The argument is LectureNode. Hence all the attributes of LectureNode are being displayed\n";
	if (attriv.size() == 0)
		std::cout << "no attributes present\n";
	else
	{
		std::cout << "Attributes\t" << "value\n";
		for (auto x : attriv)
			std::cout<< x.first << "\t\t" << x.second <<"\n";
	}
}

//--------------< Function to display children of a particular element >-------------
void Display::displayRequirement8b()
{
	std::cout << "-=-=-=-=Demonstrating the children requirement-=-=-=-=\n";
	std::vector <std::shared_ptr < XmlProcessing::AbstractXmlElement >> children = doc_.children("author");
	std::cout << "The argument is author. Hence, the children of the first author node are being displayed\n";
	if (children.size() == 0)
		std::cout << "No children present\n";
	else
	{
		std::cout << "Children are\n";
		for (auto x : children)
			std::cout << x->toString() <<"\n";
	}
	std::cout << "\n";
	
}

//--------------< Function to add attributes to a particular element >------------
void Display::displayRequirement9a()
{
	std::cout << "-=-=-=-=Demonstrating the adding attributes requirement-=-=-=-=-=\n";
	doc_.element("publisher").addAttribute("name", "Oreily");
	std::cout << "We are adding the attributes to the publisher node\n";
	std::cout << doc_.toString() <<"\n\n";
}

//---------------< Function to remove attributes of a particular element >----------
void Display::displayRequirement9b()
{
	std::cout << "-=-=-=-=-=-Demonstrating the removing attributes requirement-=-=-=-=-\n";
	doc_.element("author").removeAttribute("city");
	std::cout << "We are removing the city attribute from the author.Thus the city attribute of the first author node will be removed\n";
	std::cout << doc_.toString() <<"\n\n";
}

void Display::displayRequirement10()
{
	std::cout << "-=-=-=-Requirement for writing XML to file-=-=-=-=-=\n";
	std::cout << "File named Xml.txt would be generated\n ";
	std::ofstream ResultXml("Xml.txt");
	ResultXml << doc_.toString();
	ResultXml.close();
	std::cout << "-=-=--=-=Requirement for adding the XML to string-=-=-=-=-=\n";
	std::cout << "The below display is from a string\n";
	std::string xmlString = doc_.toString();
	std::cout << xmlString <<"\n";
}


#ifdef TEST_DISPLAY
int main()
{
	XmlProcessing::XmlDocument x("LectureNote.xml", "filename");
	Display d(x);
	d.displayRequirement3();
	d.displayRequirement4();
	d.displayRequirement5();
	d.displayRequirement6();
}

#endif