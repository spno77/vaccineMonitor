#!/bin/bash

SECONDS=0

if [[ "$#" -lt 4 ]]; then
    echo -e '\t' "Wrong number of parameters" ""
    echo -e '\t' "Please run the script the following way:" ""
    echo -e '\t'"./testFile.sh virusesFile countriesFile numLines duplicatesAllowed"
    exit 1
fi

if [[ ! -f "$1" ]]; then
	echo -e '\t' "Parameter 1 virusesFile should be a file"
	exit 1
fi

if [[ ! -f "$2" ]]; then
	echo -e '\t' "Parameter 2 countriesFile should be a file"
	exit 1
fi

if [[ "$3" -gt 10000 ]]; then
	echo -e '\t' "Parameter 3 numLines should be <= 10000"
	exit 1
fi

virusesFile="$1"
countriesFile="$2"
numLines="$3"
dupAllowed="$4"

seqId=$(shuf -i 0-10000 -n 10000)
arrayId=($seqId)


for(( i = 0; i <= $numLines ; i++))
do
	id=${arrayId[$i]} 
	countries=$(shuf -n 1 $countriesFile)
	viruses=$(shuf -n 1 $virusesFile)
	age=$((1 + $RANDOM % 120))

	symbols="ABCDEFGHIGKLMNOPQRSTUVYXWZ"

	count_symbols=${#symbols}

	(( length = RANDOM % 10 + 3 ))
	firstName=""
	for j in $(seq 1 $length) ; do
    	firstName+=${symbols:RANDOM % count_symbols:1}
	done
	
	(( length = RANDOM % 10 + 3 ))
	lastName=""
	for k in $(seq 1 $length) ; do
    	lastName+=${symbols:RANDOM % count_symbols:1}
	done
	
	day=$((1 + $RANDOM%(1+30-1)))
	month=$((1 + $RANDOM %(1+12-1)))
	year=$((2010 + $RANDOM%(1+2021-2010)))

	isVaccinated=$((0 + $RANDOM%(1+1-0)))

	
	if [[ isVaccinated -eq 1 ]]; then
		vaccinated="YES"
		citizen="$id $firstName $lastName $countries $age $viruses $vaccinated $day-$month-$year"
		echo $citizen >> testInputFile
	else
		vaccinated="NO"
		randNum=$((1 + $RANDOM%(1+10-1)))
		if [[ randNum -eq 2 ]]; then
			citizen="$id $firstName $lastName $countries $age $viruses $vaccinated $day-$month-$year"
			echo $citizen >> testInputFile
		else
			citizen="$id $firstName $lastName $countries $age $viruses $vaccinated"
			echo $citizen >> testInputFile
		fi 
	fi

	if [[ dupAllowed -ne 0 ]]; then

		duplicateId=$((1 + $RANDOM%(1+3-1)))

		if [[ duplicateId -gt 2 ]]; then

			numOfTimes=$((1 + $RANDOM%(2+5-1)))	

			for (( ii = 1; ii < $numOfTimes; ii++ )); do

				i=$i+1

				viruses=$(shuf -n 1 $virusesFile)
		
				day=$((1 + $RANDOM%(1+30-1)))
				month=$((1 + $RANDOM %(1+12-1)))
				year=$((2010 + $RANDOM%(1+2021-2010)))
		
				isVaccinated=$((0 + $RANDOM%(1+1-0)))
				if [[ isVaccinated -eq 1 ]]; then
					vaccinated="YES"
					citizen="$id $firstName $lastName $countries $age $viruses $vaccinated $day-$month-$year"
					echo $citizen >> testInputFile

				else
					vaccinated="NO"
					randNum=$((1 + $RANDOM%(1+10-1)))
					if [[ randNum -eq 2 ]]; then
						citizen="$id $firstName $lastName $countries $age $viruses $vaccinated $day-$month-$year"
						echo $citizen >> testInputFile
					else
						citizen="$id $firstName $lastName $countries $age $viruses $vaccinated"
						echo $citizen >> testInputFile
					fi 
				fi

			done
		fi
	fi


done

duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed."