/*
 * TemperatureData.cpp
 *
 *  Created on: November 2018
 *      Author: student
 */
#include <string>
#include "TemperatureData.h"
using namespace std;

TemperatureData::TemperatureData(): id(""), year(0), month(0), temperature(0) {} //initialize everything

TemperatureData::TemperatureData(string id, int year, int month, double temperature) {
	this->id = id; 
	this->year = year;
	this->month = month;
	this->temperature = temperature;

} //initialized everything


TemperatureData::~TemperatureData() {} 

bool TemperatureData::operator<(const TemperatureData& b) {
	bool output = false;
	if (id == b.id) {
		if (year == b.year) {
			if (month == b.month) {
				if (temperature == b.temperature) {
					output = false;
				}
				else if (temperature < b.temperature) {
					output = true;
				}
			}
			else if (month < b.month) {
				output = true;
			}
		}
		else if (year < b.year) {
			output = true;
		}
	}
	else if (id < b.id) {
			output = true;
	}
	return output;
}

