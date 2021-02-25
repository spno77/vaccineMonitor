#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"

int main(int argc, char const *argv[])
{

	char *citizenRecordsFile;
	int bloomSize;

	readArguments(argc,argv,&citizenRecordsFile,&bloomSize);

	readFile(citizenRecordsFile);

	freeArguments(&citizenRecordsFile);

	return 0;
}

