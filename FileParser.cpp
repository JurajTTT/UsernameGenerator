
#include "stdafx.h"
#include "FileParser.h"
#include <fstream>
#include <algorithm>
#include "sql\sqlite3.h"

/**
 *
 */
FileParser::FileParser()
{
	fileNames_.clear();
	inputCollection_.clear();
}

/**
 *
 */
FileParser::FileParser(vector<string> fileNames)
{
	fileNames_ = fileNames;
	inputCollection_.clear();
}

/**
 *
 */
FileParser::~FileParser()
{

}

/**
 *
 */
void FileParser::parseFile()
{
	SingleRecord rec;
	std::string line;

	if (fileNames_.size() == 0)
	{
		cout << "Error: No filename defined!" << endl;
		return;
	}

	for (it_ = fileNames_.begin(); it_ < fileNames_.end(); it_++)
	{
		ifstream f(*it_);

		if (!f.is_open())
		{
			cout << "Error opening file for Read" << endl;
			continue;
		}

		while (getline(f, line))
		{
			vector<string> substring = getSplittedLine(line, ":");

			if (substring.size() != 5)
			{
				cout << "Error: Invalid record. Try next record..." << endl;
				continue;
			}

			rec.setID(substring[0]);
			rec.setFirstName(substring[1]);
			rec.setMidName(substring[2]);
			rec.setSurName(substring[3]);
			rec.setDepartment(substring[4]);

			inputCollection_.push_back(rec);
		}

		f.close();

	}

	cout << "Collection has: " << inputCollection_.size() << " items." << endl;
}

/**
 *
 */
void FileParser::parseData()
{
	parseFile();
}

/**
 *
 */
vector<string> FileParser::getSplittedLine(string line, string delimiter)
{
	size_t pos = 0;
	std::string token;
	vector <string> result;

	// tokenize input line
	while ((pos = line.find(delimiter)) != std::string::npos) 
	{
		token = line.substr(0, pos);
		result.push_back(token);
		line.erase(0, pos + delimiter.length());
	}
	
	// insert last token into result vector
	result.push_back(line);
	return result;
}

/**
 *
 */
vector<string> FileParser::getFileNames()
{
	return fileNames_;
}

/**
 *
 */
vector<SingleRecord> FileParser::getInputCollection()
{
	return inputCollection_;
}

/**
 *
 */
void FileParser::printInputCollection()
{
	cout << "Collection of Input data:" << endl;

	for (it1_ = inputCollection_.begin(); it1_ < inputCollection_.end(); it1_++)
		(*it1_).printData();
}

/**
 *
 */
void FileParser::buildOutputCollection()
{
	string outputRecord = "";
	SingleRecord rec;
	int numOfSameNames = 0;
	vector<string> generatedNames;

	for (it1_ = inputCollection_.begin(); it1_ < inputCollection_.end(); it1_++)
	{
		rec = *it1_;

		string generatedName = generateName(rec);
		generatedNames.push_back(generatedName);

		numOfSameNames = std::count(generatedNames.begin(), generatedNames.end(), generatedName);

		outputRecord += rec.getID() + ":";

		if (numOfSameNames == 1)
			outputRecord += generatedName + ":";
		else
			outputRecord += generatedName + std::to_string(numOfSameNames - 1) + ":";

		outputRecord += rec.getFirstName() + ":";
		outputRecord += rec.getMidName() + ":";
		outputRecord += rec.getSurName() + ":";
		outputRecord += rec.getDepartment();
		
		outputCollection_.push_back(outputRecord);
		
		outputRecord = "";
		numOfSameNames = 0;
	}
}

/**
 *
 */
string FileParser::generateName(SingleRecord rec)
{
	string name = "";

	name += rec.getFirstName().substr(0, 1);

	if (rec.getMidName() != "")
		name += rec.getMidName().substr(0, 1);

	name += rec.getSurName();


	std::for_each(name.begin(), name.end(), [](char &c)
	{
		c = ::tolower(c);
	});

	if (name.length() < 8)
		return name;

	return name.substr(0, 8);
}

/**
 *
 */
void FileParser::printOutputCollection()
{
	cout << "Collection of Output data:" << endl;

	for (it_ = outputCollection_.begin(); it_ < outputCollection_.end(); it_++)
		cout << "\t" << *it_ << endl;
}

/**
 *
 */
void FileParser::saveOutputDataToFile(string fileName)
{
	fstream of;

	if (fileName.empty())
	{
		cout << "Cannot store data into file. FileName not defined." << endl;
		return;
	}

	of.open(fileName, ios_base::out);

	if (!of.is_open())
	{
		cout << "Error opening output file." << endl;
		return;
	}

	for (it_ = outputCollection_.begin(); it_ < outputCollection_.end(); it_++)
		of << *it_ << endl;
	

	of.close();
}

/**
 *
 */
void FileParser::saveOutputDataToSqLite()
{
	sqlite3 *DB = nullptr;
	int result = 0;
	char *errMsg;
	string checkStr = "SELECT 1 FROM sqlite_master WHERE type='table' AND name='PERSON'";
	string sqlCmd = "CREATE TABLE PERSON("
					"ID INT NOT NULL,"
					"GENUNAME TEXT PRIMARY KEY  NOT NULL,"
					"FIRSTNAME TEXT  NOT NULL,"
					"MIDDLENAME TEXT  NULL,"
					"SURNAME TEXT  NOT NULL,"
					"DEPARTMENT TEXT  NOT NULL);";

	result = sqlite3_open("output.db", &DB);
	
	if (result != SQLITE_OK)
		cout << "Error: " << sqlite3_errmsg(DB);

	cout << "Database opened" << endl;
	
	//result = sqlite3_exec(DB, checkStr.c_str(), NULL, 0, &errMsg);

	result = sqlite3_exec(DB, sqlCmd.c_str(), NULL, 0, &errMsg);
	if (result != SQLITE_OK)
	{
		cout << "Error: " << sqlite3_errmsg(DB);
		sqlite3_free(errMsg);
	}
	cout << "Database table PERSON created." << endl;

	for (it_ = outputCollection_.begin(); it_ < outputCollection_.end(); it_++)
	{
		vector<string> substring = getSplittedLine((*it_), ":");
		sqlCmd = "";
		sqlCmd += "INSERT INTO PERSON VALUES(";
		sqlCmd += substring[0] + ",";
		sqlCmd += "'" + substring[1] + "',";
		sqlCmd += "'" + substring[2] + "',";
		sqlCmd += "'" + substring[3] + "',";
		sqlCmd += "'" + substring[4] + "',";
		sqlCmd += "'" + substring[5] + "');";

		result = sqlite3_exec(DB, sqlCmd.c_str(), NULL, 0, &errMsg);
		if (result != SQLITE_OK)
		{
			cout << "Error: " << sqlite3_errmsg(DB);
			sqlite3_free(errMsg);
		}
		cout << "1 Row added." << endl;

	}

	sqlite3_close(DB);
}