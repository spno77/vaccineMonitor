#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
	citizenRecord *citizenRec = NULL;
	Date *date = NULL;

	char *citizenStr = malloc(strlen("65 Joseph Larsen Germany 65 H1N1 YES 03-10-2006")+1);
	strcpy(citizenStr,"65 Joseph Larsen Germany 65 H1N1 YES 03-10-2006");

	citizenRec = createCitizenRecord(citizenStr);

	printCitizenRecord(citizenRec);

	deleteCitizenRecord(citizenRec);
	free(citizenStr);

	return 0;
}