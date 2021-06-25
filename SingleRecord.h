#ifndef SINGLERECORD_H
#define SINGLERECORD_H

#include "stdafx.h"
#include <string>

class SingleRecord
{
public:
	/**
	 * Construct default object.
	 */
	SingleRecord();
	
	/**
	 * Construct object.
	 */
	SingleRecord(string id, std::string firstName, std::string midName, std::string surname, std::string department);

	/**
	 * Destruct default object.
	 */
	~SingleRecord();

	/**
	 * Get Person ID.
	 */
	string getID() const;

	/**
	 * Get Person First Name.
	 */
	string getFirstName() const;

	/**
	 * Get Person Middle Name.
	 */
	string getMidName() const;

	/**
	 * Get Person SurName.
	 */
	string getSurName() const;

	/**
	 * Get Person Department.
	 */
	string getDepartment() const;

	/**
	 * Set Person ID.
	 */
	void setID(string id);

	/**
	 * Set Person First Name.
	 */
	void setFirstName(string name);

	/**
	 * Set Person Middle Name.
	 */
	void setMidName(string name);

	/**
	 * Set Person SurName.
	 */
	void setSurName(string name);

	/**
	 * Set Person Department.
	 */
	void setDepartment(string department);

	/**
	 * Print obtained data into console.
	 */
	void printData();


private:
	string id_;
	string firstName_;
	string midleName_;
	string surName_;
	string department_;
};

#endif