// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ArgumentParser.h"
#include "FileParser.h"
#include <memory>

/**
 *
 */
int main(int argc, char* argv[])
{
	// create Argument parser object
	std::shared_ptr<ArgumentParser> ap(new ArgumentParser(argc, argv));

	if (ap == nullptr)
	{
		cout << "Cannot create ArgumentParser instance => fail" << endl;
		return 1;
	}

	// parse command prompt input line
	ap->parseData();

	// check parse result
	if (ap->getParsingStatus() == false)
	{
		ap->printUsage();
		ap = nullptr;
		return 1;
	}

	// print parsed command prompt string into console
	ap->printParsedData();

	cout << endl << endl;

	// create File Parser object
	std::shared_ptr<FileParser> fp(new FileParser(ap->getInputFiles()));

	if (fp == nullptr)
	{
		cout << "Cannot create FileParser instance => fail" << endl;
		return 1;
	}

	// parse data from input files
	fp->parseData();

	// print input data into console
	fp->printInputCollection();

	// build output data
	fp->buildOutputCollection();

	// print output data into console
	fp->printOutputCollection();
	
	// store output data into defined output file
	fp->saveOutputDataToFile(ap->getOutputFile());

	// store output data into SQLite database
	fp->saveOutputDataToSqLite();

	return 0;
}
