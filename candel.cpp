/*
 * candel.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: Binki
 */

#include <iostream>
#include<list>
#include<fstream>
#include<string>
#include "DataUtil.h"

struct feature;

using namespace std;

/**
 * Function to print a list of datapoints/hypotheses
 * @param ls list containing the datapoints/hypotheses
 */

void printList(list<feature> ls) {
	list<feature>::iterator it = ls.begin();
	if (ls.empty())
		cout << "List empty \n";
	for (; it != ls.end(); it++) {
		cout << "\n";
		for (int i = 0; i < 16; i++) {

			if ((*it).attributes[i] == 99)
				cout << "?" << " ";
			else
				cout << (*it).attributes[i] << " ";
		}

	}
	cout<<endl;
}

/**
 * Function to print a single hypothesis/datapoint
 * @param s struct containing hypothesis/datapoint
 */
void printFeature(feature s) {
	for (int i = 0; i < 16; i++)
		cout << (s).attributes[i] << " ";
	cout << "\n";
}

/**
 * Function to check if a datapoint/hypothesis is consistent with a hypothesis
 * @param hyp_it: hypothesis
 * @param data_it: datapoint
 * @return 1 if consistent, 0 if inconsistent
 */

int isConsistent(feature hyp_it, feature data_it) {

	int check = 1;
	for (int i = 0; i < 16; i++) {
		if ((hyp_it).attributes[i] != (data_it).attributes[i]
				&& (hyp_it).attributes[i] != 99) {
			check = 0;
			break;
		}
	}

	return check;
}

/**
 * Function to check if a hypothesis is more general than a datapoint/hypothesis
 * @param data_it: the supposedly less general hypothesis
 * @param hyp_it: the claimed more general hypothesis
 * @return 1 if required hypothesis is more general, 0 if not
 */

int isMoreGeneral(feature data_it, feature hyp_it) {

	//check if hyp_it is more general than data_it

	int check = 1;
	int equal = 1;

	for (int i = 0; i < 16; i++) {
		if ((hyp_it).attributes[i] != (data_it).attributes[i])
			equal = 0;
	}

	if (equal == 1)
		return 0;

	for (int i = 0; i < 16; i++) {
		if ((hyp_it).attributes[i] != (data_it).attributes[i]
				&& (hyp_it).attributes[i] != 99) {
			check = 0;
			break;
		}
	}
	return check;
}

/**
 *Function to check if any of the hypothesis in a list is reachable/less general from a given hypothesis
 * @param test: hypothesis 'from which to reach'/claimed more general hypothesis
 * @param spec: list which contains elements 'to reach'
 * @return 1 if any element is reachable, 0 if none
 */

int isReachable(feature test, list<feature> spec) {

	list<feature>::iterator s_it = spec.begin();

	for (; s_it != spec.end(); s_it++) {
		if (isMoreGeneral((*s_it), (test)) == 1) {
			return 1;
		}
	}
	return 0;
}

/**
 * Function to make a hypothesis more general to accomodate given datapoint
 * @param hyp_it: pointer to the hypothesis in question, so we can edit the original value
 * @param data_it: data point to be accomodated
 */

void generalise(list<feature>::iterator &hyp_it, feature data_it) {

	for (int i = 0; i < 16; i++) {
		if ((*hyp_it).attributes[i] == -1) {
			(*hyp_it).attributes[i] = data_it.attributes[i];
		} else if ((*hyp_it).attributes[i] != (data_it).attributes[i]
				&& (*hyp_it).attributes[i] != 99) {
			(*hyp_it).attributes[i] = 99;
		}
	}
}

/**
 * Function to return list of minimal specializations of a hypothesis made
 * so as to not accommodate inconsistent datapoint, it also checks the reachability
 * in specific boundary
 * @param hyp_it: hypothesis to be specialised
 * @param data_it: inconsistent data point
 * @param spec: list to check reachability
 * @return list containing all required minimal specializations based on given data
 */

list<feature> specify(feature hyp_it, feature data_it, list<feature> spec) {

	list<feature> sp_list;
	feature t0;
	for (int i = 0; i < 16; i++) {
		t0.attributes[i] = hyp_it.attributes[i];
	}

	for (int i = 0; i < 16; i++) {
		feature t1 = t0;
		if (hyp_it.attributes[i] == 99) {
			if (i == 12) {
				if (data_it.attributes[i] == 0) {

					t1.attributes[i] = 2;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);

					t1.attributes[i] = 4;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);

					t1.attributes[i] = 5;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 6;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 8;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
				} else if (data_it.attributes[i] == 2) {

					t1.attributes[i] = 0;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 4;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 5;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 6;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 8;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
				} else if (data_it.attributes[i] == 4) {

					t1.attributes[i] = 2;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 0;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 5;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 6;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 8;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
				} else if (data_it.attributes[i] == 5) {

					t1.attributes[i] = 2;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 4;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 0;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 6;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 8;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
				} else if (data_it.attributes[i] == 6) {

					t1.attributes[i] = 2;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 4;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 5;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 0;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 8;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
				} else if (data_it.attributes[i] == 8) {

					t1.attributes[i] = 2;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 4;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 5;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 6;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
					t1.attributes[i] = 0;
					if (isReachable(t1, spec) == 1)
						sp_list.push_back(t1);
				}
			} else if (data_it.attributes[i] == 1) {
				t1.attributes[i] = 0;
				if (isReachable(t1, spec) == 1)
					sp_list.push_back(t1);
			} else if (data_it.attributes[i] == 0) {
				t1.attributes[i] = 1;
				if (isReachable(t1, spec) == 1)
					sp_list.push_back(t1);
			}
		}
	}
	return sp_list;
}


/**
 * Driver function for candidate elimination algorithm
 * @param train_set: Set of datapoints
 * @param target_class: value of target attribute to be taken as positive
 */

void candidateElim(list<feature> train_set, int target_class) {

	//Initialize lists

	list<feature> spec_bound;
	list<feature> gen_bound;
	feature s1;
	feature g1;
	for (int i = 0; i < 16; i++) {
		s1.attributes[i] = -1;
		g1.attributes[i] = 99;
	}

	spec_bound.push_back(s1);
	gen_bound.push_back(g1);

	//iterate through training data

	list<feature>::iterator train_it = train_set.begin();

//	cout<<(*train_it).attributes[16]<<"\n";
//	printList(train_set);

	list<feature>::iterator g_it = gen_bound.begin();
	list<feature>::iterator s_it = spec_bound.begin();

	for (; train_it != train_set.end(); train_it++) {

		//handling +ve training data

		if ((*train_it).attributes[16] == target_class) {

//			cout<<"Entered +ve example \n";

			g_it = gen_bound.begin();

			//traverse G and remove inconsistent

			for (; g_it != gen_bound.end(); g_it++) {
				if (isConsistent((*g_it), (*train_it)) == 0) {

	//				cout << "Inconsistent with gen bound \n";

	//				cout << "gen hyp: ";
	//				printFeature(*g_it);
	//				cout << "\n" << "train data:";
	//				printFeature(*train_it);
	//				cout << "\n";

					g_it = gen_bound.erase(g_it);

				}
			}

			//traverse S and add generalisations (Is there more than one minimal generalisation?Need to check)

			s_it = spec_bound.begin();

			for (; s_it != spec_bound.end(); s_it++) {

//				cout<<"Entered S \n";

				if (isConsistent((*s_it), (*train_it)) == 0) {

//					cout<<"Inconsistent with S example \n";

//					cout<<"Hyp:";
//					printFeature(*s_it);
//					cout<<"\n Train Data:";
//					printFeature(*train_it);
//					cout<<"\n";

					int flag = 0;

					generalise(s_it, (*train_it));

//					cout<<"Generalised hyp:";
//					printFeature(*s_it);
//					cout<<"\n";

//traverse G for reachability check

					list<feature>::iterator g_temp_it = gen_bound.begin();

					//check reachability in G for new element

					for (; g_temp_it != gen_bound.end(); g_temp_it++) {
						if (isMoreGeneral((*s_it), (*g_temp_it)) == 1) { //check s_it or train_it
							flag = 1;
							break;
						}
					}
					if (flag == 0) {
						s_it = spec_bound.erase(s_it);
						continue;
					}
					//traverse S to remove any element more general than the other

					list<feature>::iterator s_temp_it = spec_bound.begin();

					for (; s_temp_it != spec_bound.end(); s_temp_it++) {
						if (isMoreGeneral((*s_temp_it), (*s_it)) == 1) {
							s_it = spec_bound.erase(s_it);
							break;
						}
					}
				}
			}
		}

		//handling -ve training data

		else {

			//traverse S check inconsistent, remove

			//		cout << "Entered negative example \n" << (*train_it).attributes[16];

			s_it = spec_bound.begin();

			for (; s_it != spec_bound.end(); s_it++) {

				if (isConsistent((*s_it), (*train_it)) == 1) {
					s_it = spec_bound.erase(s_it);
				}
			}

			//traverse G, add minimal specialisations

			g_it = gen_bound.begin();

			for (; g_it != gen_bound.end();) {

				//CHECK IF WORKING

				list<feature> min_sp;
				if (isConsistent((*g_it), (*train_it)) == 1) {
					min_sp = specify((*g_it), (*train_it), spec_bound);	//specify takes care of reachability

	//				cout << "Removing from gen bound:";
	//				printFeature(*g_it);
	//				cout << endl;
	//				cout << "Inconsistent with:";
	//				printFeature(*train_it);
	//				cout << endl;

					g_it = gen_bound.erase(g_it);

					list<feature>::iterator min_sp_it = min_sp.begin();

					for (; min_sp_it != min_sp.end(); min_sp_it++) {

						//check for more general

						int check = 1;
						list<feature>::iterator gen_comp = gen_bound.begin();
						for (; gen_comp != gen_bound.end(); gen_comp++) {
							if (isMoreGeneral((*min_sp_it), (*gen_comp)) == 1)
								check = 0;
						}
						if (check == 1)
							gen_bound.push_back((*min_sp_it));
					}
				}
				else
					g_it++;

			}

		}

	}

	cout<<"Specific Boundary:"<<endl;
	printList(spec_bound);
	cout << endl;
	cout<<"General Boundary:"<<endl;
	printList(gen_bound);
	cout << endl;

}

