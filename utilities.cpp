/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	if (*myString == NULL){
		return 0;
	}
	return atoi(myString);
}
vector<process_stats> stats;
int loadData(const char* filename, bool ignoreFirstRow) {

	if (!stats.size() == 0){
		stats.clear();
	}


	std::ifstream file;

	stringstream sstream;

	file.open(filename);

	if (!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	std::string line;
	std::string item;

	int numberOfRows = 0;


	std::string falseLine;
	process_stats statRow;
	if(ignoreFirstRow == true){
		getline(file,line);
				//go to next line
	}



	while(!file.eof()){
		getline(file,line);

		sstream.str(line);

		string::iterator i;

		int lineNumbers = 0;



		int numberOfCommas = 0;



		for(i = line.begin(); i < line.end(); i++){
			if (*i == CHAR_TO_SEARCH_FOR){
				numberOfCommas += 1;
			}

		}






		getline(sstream,item,CHAR_TO_SEARCH_FOR);

				if(!item.empty()){

					statRow.process_number = atoi(item.c_str());
					lineNumbers ++;

				}


				getline(sstream,item,CHAR_TO_SEARCH_FOR);
						if (!item.empty() ){
							statRow.start_time = atoi(item.c_str());
							lineNumbers ++;

						}


		getline(sstream,item,CHAR_TO_SEARCH_FOR);
				if (!item.empty() ){
					statRow.cpu_time = atoi(item.c_str());
					lineNumbers ++;

				}














		getline(sstream,item);
		if(!item.empty() ){
			statRow.io_time = atoi(item.c_str());
			lineNumbers ++;



		}



		if(numberOfCommas == 3 && lineNumbers >= 4){
			stats.push_back(statRow);
		}



		sstream.clear();








		}










	file.close();
	return SUCCESS;
	}

bool compareCPU_time(const process_stats& x, const process_stats& y){

	return (x.cpu_time < y.cpu_time);
}

bool compareProcessNumber(const process_stats& x, const process_stats& y){

	return (x.process_number < y.process_number);
}
bool compareStart_time(const process_stats& x, const process_stats& y){

	return (x.start_time < y.start_time);
}

bool compareIOTime(const process_stats& x, const process_stats& y){

	return (x.io_time < y.io_time);
}





//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch (mySortOrder){




	case (PROCESS_NUMBER):
		sort(stats.begin(), stats.end(), compareProcessNumber);
		break;

	case (CPU_TIME):
				sort(stats.begin(), stats.end(), compareCPU_time);
				break;


	case (START_TIME):
			sort(stats.begin(), stats.end(), compareStart_time);
			break;

	case (IO_TIME):
				sort(stats.begin(), stats.end(), compareIOTime);
				break;
			}



}



process_stats getNext() {
	process_stats myFirst;

	//myFirst = statRow;
	myFirst = stats.front();


	stats.erase(stats.begin());




	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	//return numberOfRows;
	return stats.size();
}


