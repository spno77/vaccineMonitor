#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "citizen.h"

int main(int argc, char const *argv[])
{
	citizenRecord *citizenRec = NULL;

	char *citizen = malloc(strlen("65 Joseph Larsen Germany 65 H1N1 YES 03-10-2006")+1);
	strcpy(citizen,"65 Joseph Larsen Germany 65 H1N1 YES 03-10-2006");

	citizenRec = createCitizenRecord(citizen);

	printCitizenRecord(citizenRec);


	return 0;
}