/*
 * candel.h
 *
 *  Created on: Oct 1, 2017
 *      Author: Binki
 */

#ifndef CANDEL_H_
#define CANDEL_H_

#include <iostream>
#include<list>
#include<fstream>
#include<string>
#include "DataUtil.h"

struct feature;


int isConsistent(feature hyp_it, feature data_it);

int isMoreGeneral(feature data_it, feature hyp_it);

int isReachable(feature test, std::list<feature> spec);

void generalise(std::list<feature>::iterator &hyp_it, feature data_it);

std::list<feature> specify(feature hyp_it, feature data_it, std::list<feature> spec);

feature returnPositive(std::list<feature> train_list, int positive_class);

void candidateElim(std::list<feature> train_set, int target_class);

void printList(std::list<feature> ls);

void printFeature(feature s);


#endif /* CANDEL_H_ */
