/*
 * DataUtil.h
 *
 *  Created on: Sep 30, 2017
 *      Author: Binki
 */

#ifndef DATAUTIL_H_
#define DATAUTIL_H_

#include <iostream>
#include<list>
#include<fstream>
#include<string>


//Defining a structure for each hypothesis or data point
struct feature {
	char name[50];
	int attributes[17];
};
typedef struct feature feature;

std::list<feature> Input(std::string &file, int n);

std::list<feature> processData(std::list<feature> data,int positive);

#endif /* DATAUTIL_H_ */
