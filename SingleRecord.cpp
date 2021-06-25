
#include "stdafx.h"
#include "SingleRecord.h"

/**
 *
 */
SingleRecord::SingleRecord() : id_(""), firstName_(""), midleName_(""), surName_(""), department_("")
{

}

/**
 *
 */
SingleRecord::SingleRecord(string id, std::string firstName, std::string midName, std::string surname, std::string department)
{
	id_			= id;
	firstName_	= firstName;
	midleName_	= midName;
	surName_	= surname;
	department_ = department;
}

/**
 *
 */
SingleRecord::~SingleRecord()
{

}

/**
 *
 */
string SingleRecord::getID() const
{
	return id_;
}

/**
 *
 */
string SingleRecord::getFirstName() const
{
	return firstName_;
}

/**
 *
 */
string SingleRecord::getMidName() const
{
	return midleName_;
}

/**
 *
 */
string SingleRecord::getSurName() const
{
	return surName_;
}

/**
 *
 */
string SingleRecord::getDepartment() const
{
	return department_;
}

/**
 *
 */
void SingleRecord::setID(string id)
{
	id_ = id;
}

/**
 *
 */
void SingleRecord::setFirstName(string name)
{
	firstName_ = name;
}

/**
 *
 */
void SingleRecord::setMidName(string name)
{
	midleName_ = name;
}

/**
 *
 */
void SingleRecord::setSurName(string name)
{
	surName_ = name;
}

/**
 *
 */
void SingleRecord::setDepartment(string department)
{
	department_ = department;
}

/**
 *
 */
void SingleRecord::printData()
{
	cout << "\t" << id_ << ":" << firstName_ << ":" << midleName_ << ":" << surName_ << ":" << department_ << endl;
}