# vaccineMonitor

## Data structures implemented

![l](https://user-images.githubusercontent.com/20780442/232837990-ea7ffeeb-4947-47a3-ba96-eaab91c5ab93.png)

## Create data

`./testFile.sh virusesFile countriesFile numLines duplicatesAllowed`

**virusesFile**   --> file with viruses names(one name per line) <br>
**countriesFile** --> file with countries names(one name per line) <br>
**numLines**      --> number of lines for the created file <br>
**numLines**      --> 0 for unique ids, 1 for duplicates allowed <br>

## Compile and run

* Compile the program using `make`
* Run the program `./vaccineMonitor -c citizenRecordsFile –b bloomSize` 

## Execute queries

* /vaccineStatusBloom citizenID virusName
* /vaccineStatus citizenID virusName
* /vaccineStatus citizenID
* /populationStatus [country] virusName date1 date2
* /popStatusByAge [country] virusName date1 date2
* /insertCitizenRecord citizenID firstName lastName country age virusName YES/NO
* /vaccinateNow citizenID firstName lastName country age virusName
* /list-nonVaccinated-Persons virusName
* /exit
