#include <iostream>
#include<list>
#include<fstream>
#include<string>
#include "DataUtil.h"

struct feature;

using namespace std;

/**
 * Function to take data point input from file in the form of struct feature
 * @param file: file path
 * @param n: number of points to take
 * @return list of struct feature containing all datapoints as given in the file
 */

list<feature> Input(std::string &file, int n) {
	std::list<feature> t;
	std::list<feature>::iterator tit = t.begin();
	ifstream inFile;
	inFile.open(file.c_str());

	char END_OF_FEATURE = '\n';
	char singleCharacter;

	inFile.get(singleCharacter);

	for (int i = 0; i < n; i++) {

		feature t0;
		int m = 0;
		while (singleCharacter != END_OF_FEATURE) {
			if (singleCharacter == ',') {
				break;
			} else {
				t0.name[m] = singleCharacter;
				m = m + 1;
			}
			inFile.get(singleCharacter);
		}

		inFile.get(singleCharacter);
		//now at first attribute
		for (int k = 0; k < 17; k++) {
			int temp = singleCharacter - '0';
			t0.attributes[k] = temp;
			inFile.get(singleCharacter);
			inFile.get(singleCharacter);
		}

		t.push_back(t0);

	}

	inFile.close();
	return t;
}

/**
 * Function to process data so as to put all positive examples in front
 * @param data: List containing data to be processed
 * @param positive: target attribute value to be classified as positive
 * @return list containing all positive attributes in the front
 */

list<feature> processData(list<feature> data,int positive) {
	list<feature>::iterator train_it=data.begin();
	for (; train_it != data.end(); train_it++) {
			if ((*train_it).attributes[16] == positive)
				data.push_front(*train_it);
		}
	return data;
}
