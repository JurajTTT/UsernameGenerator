#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "stdafx.h"
#include <vector>
#include "SingleRecord.h"
#include "DataParser.h"

class FileParser : public DataParser
{
public:
	/**
	 * Implicit Constructor of object FileParser.
	 *
	 * @param argc - count of input arguments
	 * @param argv - array of input arguments
	 */
	FileParser();

	/**
	 * Construct object FileParser.
	 *
	 * @param argc - count of input arguments
	 * @param argv - array of input arguments
	 */
	FileParser(vector<string> fileNames);

	/**
	 * Destruct object FileParser.
	 */
	~FileParser();

	/**
	 * Use for Data parsing.
	 */
	virtual void parseData();

	/**
	 * Return vector of strings from input line, split according delimiter character.
	 */
	vector<string> getSplittedLine(string line, string delimiter);

	/**
	 * Generate name from input data.
	 */
	string generateName(SingleRecord rec);

	/**
	 * Return vector of file names.
	 */
	vector<string> getFileNames();

	/**
	 * Return vector of parsed input data.
	 */
	vector<SingleRecord> getInputCollection();

	/**
	 * Print input collection into console.
	 */
	void printInputCollection();

	/**
	 * Build output collection including Generated name.
	 */
	void buildOutputCollection();

	/**
	 * Print output collection into console.
	 */
	void printOutputCollection();

	/**
	 * Store output result into output file.
	 */
	void saveOutputDataToFile(string fileName);

	/**
	 * Store output result into SQLite database.
	 */
	void saveOutputDataToSqLite();

private:

	/**
	 * Parse data from file.
	 */
	void parseFile();

private:
	vector<string> fileNames_;
	vector<string>::iterator it_;
	vector<SingleRecord>::iterator it1_;
	vector<SingleRecord> inputCollection_;
	vector<string> outputCollection_;
};

#endif