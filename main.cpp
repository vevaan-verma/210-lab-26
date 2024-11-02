// COMSC-210 | Lab 26 | Vevaan Verma
#include <chrono>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <string>
using namespace std;
using namespace std::chrono;

enum DataStructure { VECTOR, LIST, SET }; // this enum is used to specify the data structure to use; it adds more convenience and readability to the code

/* FUNCTION PROTOTYPES */
long long raceReading(DataStructure dataStructure);
long long raceSorting(DataStructure dataStructure);
long long raceInsertion(DataStructure dataStructure);
long long raceDeletion(DataStructure dataStructure);

/* CONSTANTS */
const string FILE_NAME = "codes.txt"; // file name
const int NUM_SIMULATIONS = 15; // number of simulations

/* GLOBAL VARIABLES */
ifstream fin;
vector<string> v;
list<string> l;
set<string> s;

// main() is the entry point of the program and drives the program
// arguments: none
// returns: int - the exit code of the program
int main() {

	fin.open(FILE_NAME); // open file

	if (!fin) { // if file does not exist

		cout << "Error: File " << FILE_NAME << " not found." << endl; // output error message
		return 1; // return error code

	}
	cout << "Number of simulations: " << NUM_SIMULATIONS << endl;

	cout << setw(10) << "Operation" << setw(10) << "Vector" << setw(10) << "List" << setw(10) << "Set" << endl; // output header
	cout << setw(10) << "Read" << setw(10) << raceReading(VECTOR) << setw(10) << raceReading(LIST) << setw(10) << raceReading(SET) << endl; // output read duration
	cout << setw(10) << "Sort" << setw(10) << raceSorting(VECTOR) << setw(10) << raceSorting(LIST) << setw(10) << raceSorting(SET) << endl; // output sort duration
	cout << setw(10) << "Insert" << setw(10) << raceInsertion(VECTOR) << setw(10) << raceInsertion(LIST) << setw(10) << raceInsertion(SET) << endl; // output insert duration
	cout << setw(10) << "Delete" << setw(10) << raceDeletion(VECTOR) << setw(10) << raceDeletion(LIST) << setw(10) << raceDeletion(SET) << endl; // output delete duration

	fin.close(); // close file

	return 0;

}

// raceReading() reads codes from a file and stores them in the given data structure
// arguments: DataStructure dataStructure - the data structure to store the codes in
// returns: long long - the duration of the operation in milliseconds
long long raceReading(DataStructure dataStructure) {

	long long totalDuration = 0; // to hold the duration of the operation

	for (int i = 0; i < NUM_SIMULATIONS; i++) { // loop through simulations

		fin.seekg(0, ios::beg); // go to beginning of file

		string code; // to hold the input codes
		auto start = high_resolution_clock::now(); // start time

		switch (dataStructure) { // switch statement to determine data structure (switch statements make the code more readable and scalable)

		case VECTOR: // if data structure is vector

			while (!fin.eof()) { // while the end of the file has not been reached

				fin >> code; // read code
				v.push_back(code); // add code to vector

			}

			break;

		case LIST: // if data structure is list

			while (!fin.eof()) { // while the end of the file has not been reached

				fin >> code; // read code
				l.push_back(code); // add code to list

			}

			break;

		case SET: // if data structure is set

			while (!fin.eof()) { // while the end of the file has not been reached

				fin >> code; // read code
				s.insert(code); // add code to set

			}

			break;

		}

		auto end = high_resolution_clock::now(); // end time
		auto duration = duration_cast<milliseconds>(end - start); // duration
		totalDuration += duration.count(); // add duration to total duration
	}

	return totalDuration / NUM_SIMULATIONS; // return average duration

}

// raceSorting() sorts the codes in the given data structure
// arguments: DataStructure dataStructure - the data structure to store the codes in
// returns: long long - the duration of the operation in milliseconds
long long raceSorting(DataStructure dataStructure) {

	long long totalDuration = 0; // to hold the duration of the operation

	for (int i = 0; i < NUM_SIMULATIONS; i++) { // loop through simulations

		fin.seekg(0, ios::beg); // go to beginning of file

		string code; // to hold the input codes
		auto start = high_resolution_clock::now(); // start time

		switch (dataStructure) { // switch statement to determine data structure

		case VECTOR: // if data structure is vector

			sort(v.begin(), v.end()); // sort vector
			break;

		case LIST: // if data structure is list

			l.sort(); // sort list
			break;

		case SET: // if data structure is set

			return -1; // return -1 because sets are already sorted

		}

		auto end = high_resolution_clock::now(); // end time
		auto duration = duration_cast<milliseconds>(end - start); // duration
		totalDuration += duration.count(); // add duration to total duration

	}

	return totalDuration / NUM_SIMULATIONS; // return average duration

}

// raceInsertion() inserts a new code into the middle of the given data structure
// arguments: DataStructure dataStructure - the data structure to store the codes in
// returns: long long - the duration of the operation in milliseconds
long long raceInsertion(DataStructure dataStructure) {

	long long totalDuration = 0; // to hold the duration of the operation

	for (int i = 0; i < NUM_SIMULATIONS; i++) { // loop through simulations

		fin.seekg(0, ios::beg); // go to beginning of file

		string code; // to hold the input codes
		auto start = high_resolution_clock::now(); // start time
		list<string>::iterator it = l.begin(); // iterator to traverse list (unfortunately, the iterator has to be declared here because it cannot be declared in the switch statement)

		switch (dataStructure) { // switch statement to determine data structure

		case VECTOR: // if data structure is vector

			v.insert(v.begin() + 10000, "TESTCODE"); // add new value to the middle of the vector
			break;

		case LIST: // if data structure is list

			advance(it, 10000); // advance iterator to middle of list
			l.insert(it, "TESTCODE"); // add new value to the middle of the list
			break;

		case SET: // if data structure is set

			s.insert("TESTCODE"); // add new value to the set
			break;

		}

		auto end = high_resolution_clock::now(); // end time
		auto duration = duration_cast<milliseconds>(end - start); // duration
		totalDuration += duration.count(); // add duration to total duration

	}

	return totalDuration / NUM_SIMULATIONS; // return average duration

}

// raceDeletion() deletes a code from the middle of the given data structure
// arguments: DataStructure dataStructure - the data structure to store the codes in
// returns: long long - the duration of the operation in milliseconds
long long raceDeletion(DataStructure dataStructure) {

	long long totalDuration = 0; // to hold the duration of the operation

	for (int i = 0; i < NUM_SIMULATIONS; i++) { // loop through simulations

		fin.seekg(0, ios::beg); // go to beginning of file

		string code; // to hold the input codes
		auto start = high_resolution_clock::now(); // start time
		list<string>::iterator it = l.begin(); // iterator to traverse list (once again, unfortunately, the iterator has to be declared here because it cannot be declared in the switch statement)

		switch (dataStructure) { // switch statement to determine data structure

		case VECTOR: // if data structure is vector

			v.erase(v.begin() + 10000); // delete value from the middle of the vector
			break;

		case LIST: // if data structure is list

			advance(it, 10000); // advance iterator to middle of list
			l.erase(it); // delete value from the middle of the list
			break;

		case SET: // if data structure is set

			s.erase("TESTCODE"); // delete value from the set
			break;

		}

		auto end = high_resolution_clock::now(); // end time
		auto duration = duration_cast<milliseconds>(end - start); // duration
		totalDuration += duration.count(); // add duration to total duration

	}

	return totalDuration / NUM_SIMULATIONS; // return average duration

}