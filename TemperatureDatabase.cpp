#include "TemperatureDatabase.h"
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// Default constructor/destructor
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	ifstream inSS;

	string line;
	string id;
	int year;
	int month;
	double temp;

	//Open file
	inSS.open(filename);

	//Message if error occurs when opening file
	bool notvalid = false;
	if (!inSS.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		notvalid = true;
	}

	while (!inSS.eof()) {
		getline(inSS, line);

		if (line.length() == 0) {
			continue;
		}
		
		double yearCheck = 0;
		double monthCheck = 0;
		double temp = -0.111111;
		
		//Extract information
		stringstream lineString(line);
		lineString >> id >> yearCheck >> monthCheck >> temp;
		year = yearCheck;
		month = monthCheck;
		
		//Message if double value placed in int-type variable
		if ((year != yearCheck) || (month != monthCheck) || (temp == -0.111111)) {
			cout << "Error: Other invalid input" << endl;
			notvalid = true;
		}
		
		//Message if error
		if (inSS.fail()) {
			cout << "Error: Other invalid input" << endl;
			notvalid = true;
		}
		
		//Message if invalid year
		if ((year > 2018) || (year < 1800)) {
			cout << "Error: Invalid year " << year << endl;
			notvalid = true;
		}

		//Message if invalid month
		if ((month > 12) || (month < 1)) {
			cout << "Error: Invalid month " << month << endl;
			notvalid = true;
		}

		//Message if invalid temperature
		if (((temp > 50.0) || (temp < -50.0)) && (temp != -99.99)) {
			cout << "Error: Invalid temperature " << temp << endl;
			notvalid = true;
		}
		
		if (!notvalid) {
		    records.insert(id, year, month, temp);
		}
	}
	//Close file
	inSS.close();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// Implement this function for part 2
	ifstream inFS;
    ofstream outFS;
    
	string line;
	string id;
	string query;
	int year1;
	int year2;

	//Open query file
	inFS.open(filename);
	
	//Open result file
	outFS.open("result.dat");
	stringstream outputString; //needed to write to file

	//Message if error occurs when opening files
	bool notvalid = false;
	if (!inFS.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		notvalid = true;
	}
	
	if (!outFS.is_open()) {
		cout << "Error: Unable to open result.dat" << endl;
		notvalid = true;
	}

	while (!inFS.eof()) {
		getline(inFS, line);

        cout<<"***line:"<<line<<endl;
		if (line.length() == 0) {
			continue;
		}
		
		double year1Check = 0;
		double year2Check = 0;
		int year2 = 888888;
		
		//Extract information
		stringstream lineString(line);
		lineString >> id >> query >> year1Check >> year2Check;
		year1 = year1Check;
		year2 = year2Check;
		
		//Message if double value placed in int-type variable or have missing information
		if ((year1 != year1Check) || (year2 != year2Check) || (year2 == 888888) || (id.length() != 6) || (year2 == 0)) {
			cout << "Error: Other invalid query" << endl;
			notvalid = true;
		}
		
		//Message if error
		if (inFS.fail()) {
			cout << "Error: Other invalid query" << endl;
			notvalid = true;
		}
		
		//Message if invalid years or range
		if ((year1 > 2018) || (year1 < 1800) || (year2 > 2018) || (year2 < 1800) || (year2 < year1)) {
			cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
			notvalid = true;
		}

		//Message if invalid query
		if ((query != "MODE") && (query != "AVG")) {
			cout << "Error: Unsupported query " << query << endl;
			notvalid = true;
		}
		
		//Don't process
		if (notvalid) {
		    notvalid = false;
		    continue;
		}
		
		//Find Average
		if (query == "AVG") {
            double result = records.findAVG(id, year1, year2);
            if (result == -0.111111) {
                outputString << id << " " << year1 << " " << year2 << " " << query << " unknown" << '\n';
            }
            else {
                outputString << id << " " << year1 << " " << year2 << " " << query << " " << result << '\n';
            }
        }
		
		//Find Mode
		if (query == "MODE") {
            int result = records.findMODE(id, year1, year2);
            if (result == 888888) {
                outputString << id << " " << year1 << " " << year2 << " " << query << " unknown" << '\n';
            }
            else {
                outputString << id << " " << year1 << " " << year2 << " " << query << " " << result << '\n';
            }
		}
	}
	
	//Close query file
	inFS.close();

	//Write to result file
	outFS << outputString.str();
	
	//Close result file
	outFS.close();

}

LinkedList& TemperatureDatabase::getRecords() {
	return records;
}
