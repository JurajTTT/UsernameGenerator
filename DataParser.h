#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "stdafx.h"

class DataParser
{
public:
	DataParser();
	virtual ~DataParser();

	virtual void parseData() = 0;
};

#endif