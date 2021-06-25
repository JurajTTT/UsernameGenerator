#include "stdafx.h"
#include "ArgumentParser.h"

/**
 *
 */
ArgumentParser::ArgumentParser(int argc, char* argv[])
{
	argCount_ = argc;
	
	for (int i = 0; i < argCount_; i++)
		args_.push_back(argv[i]);

	parsingOk_ = false;
}

/**
 *
 */
ArgumentParser::~ArgumentParser()
{
}

/**
 *
 */
void ArgumentParser::printUsage()
{
	cout << "This program generate outputfile of usernames from input file(s)." << endl << endl;
	cout << "  ugen.exe [--h(elp) | --o(utput)] outfile file1 file2 ..." << endl;
	
	cout << "Options:" << endl;
	cout << "  --[h|help]" << endl;
	cout << "    - Print this help message." << endl << endl;
	cout << "  --[o|output]" << endl;
	cout << "    - Define Output file name" << endl << endl;
	
	cout << "Examples of usage:" << endl;
	cout << "  ugen.exe --o outfile.txt inputfile1.txt inputfile2.txt ..." << endl;
	cout << "    - Generate outfile.txt from files inputfile1.txt inputfile2.txt and so on ..." << endl << endl;
}

/**
 *
 */
bool ArgumentParser::isHelpRequired()
{
	for (it_ = args_.begin() + 1; it_ < args_.end(); it_++)
	{
		if ((*it_) == "--h" || (*it_) == "--help")
			return true;
	}

	return false;
}

/**
 *
 */
bool ArgumentParser::isUnknownParameter()
{
	bool unknownParam = false;
	int switches = 0;

	for (it_ = args_.begin() + 1; it_ < args_.end(); it_++)
	{
		if ((*it_).substr(0, 2) != "--")
			continue;
		else
			switches++;

		if ((*it_) == "--h" || (*it_) == "--help" || (*it_) == "--o" || (*it_) == "--output")
		{
			unknownParam = false;
		}
		else
		{
			unknownParam = true;
			break;
		}
	}

	// no switch found => wrong format
	if (switches == 0)
		unknownParam = true;


	return unknownParam;
}

/**
 *
 */
void ArgumentParser::searchInOutFiles()
{
	int outputFileIndex = -1;

	for (int i = 1; i < args_.size(); i++)
	{
		// argument is not output file => might be input file
		if (args_[i] != "--o" && args_[i] != "--output")
		{
			// it is neither switch nor output file => must be input file
			if (i != outputFileIndex)
				inFileNames_.push_back(args_[i]);

			continue;
		}
		else if ((args_[i] == "--o" || args_[i] == "--output") && (i < args_.size() - 1))
		{
			// it is switch (output) but not at the End of line => next item must be output file
			if (i + 1 < args_.size())
			{
				outputFileIndex = i + 1;
				outFileName_ = args_[i + 1];
			}
			else
			{
				// switch for output file is at the end of parsed line => no outputfilename defined, so it is error
				printUsage();
				parsingOk_ = false;
			}
		}
	}

	// No output file name found in parsed line
	if (outputFileIndex == -1)
	{
		printUsage();
		parsingOk_ = false;
	}
	
	// output file name found, input file names found => Parsing was successful
	if (outFileName_ != "" && inFileNames_.size() > 0)
		parsingOk_ = true;
}

/**
 *
 */
void ArgumentParser::parseInput()
{
	if (isHelpRequired() || isUnknownParameter())
	{
		printUsage();
		return;
	}

	searchInOutFiles();
}

/**
 *
 */
void ArgumentParser::parseData()
{
	parseInput();
}

/**
 *
 */
void ArgumentParser::printParsedData()
{
	cout << "Output File: " << outFileName_ << endl;

	for (it_ = inFileNames_.begin(); it_ < inFileNames_.end(); it_++)
		cout << "Input File : " << *it_ << endl;

}

/**
 *
 */
bool ArgumentParser::getParsingStatus()
{
	return parsingOk_;
}

/**
 *
 */
string ArgumentParser::getOutputFile()
{
	return outFileName_;
}

/**
 *
 */
vector<string> ArgumentParser::getInputFiles()
{
	return inFileNames_;
}