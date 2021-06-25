#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <vector>
#include "DataParser.h"

class ArgumentParser : public DataParser
{
public:

	/**
	 * Construct object ArgumentParser.
	 *
	 * @param argc - count of input arguments
	 * @param argv - array of input arguments
	 */
	ArgumentParser(int argc, char* argv[]);

	/**
	 * Destruct object ArgumentParser.
	 */
	~ArgumentParser();

	/**
	 * Use for Data parsing.
	 */
	virtual void parseData();

	/**
	 * Print usage of program.
	 */
	void printUsage();

	/**
	 * Check if help should be displayed.
	 * @return - true if help info should be displayed
	 */
	bool isHelpRequired();

	/**
	 * Parse program input line and find out all input files and output file.
	 */
	void searchInOutFiles();

	/**
	 * Check if program input line contains only allowed parameters.
	 * @return - true if unknown parameter was found on input line
	 */
	bool isUnknownParameter();

	/**
	 * Check if parsing was OK or Not.
	 * @return - true if Parsing was Ok, false otherwise
	 */
	bool getParsingStatus();

	/**
	 * Print parsed data to console.
	 */
	void printParsedData();

	/**
	 * Return name of Output file.
	 * @return - file name of found output file
	 */
	string getOutputFile();

	/**
	 * Return name of all Input files.
	 * @return - file names of all found input files
	 */
	vector<string> getInputFiles();

private:

	/**
	 * Parse line from program input string.
	 */
	void parseInput();

private:
	int argCount_;
	vector<string>args_;
	string outFileName_;
	vector<string> inFileNames_;
	vector<string>::iterator it_;
	bool parsingOk_;
};

#endif