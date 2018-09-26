//============================================================================
// Name        : CandidateElimination.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Candidate Elimination Algorithm
//============================================================================

#include <iostream>
#include<list>
#include<fstream>
#include<string>
#include "DataUtil.h"
#include "candel.h"

struct feature;

using namespace std;


//Driver function for the program

int main() {

	list<feature> s;
	list<feature>::iterator it = s.begin();

	int x;
	int positive_class;



	std::string filename =
			"training.txt";

	while(1) {
		cout<<"Enter\n 1 for candidate elimination\n 2 for exit \n";
		cin>>x;
		if(x==1) {

			cout<<"Enter class to give hypothesis for\n";

			cin>>positive_class;

			s = Input(filename, 101);

			s = processData(s,positive_class);

			candidateElim(s, positive_class);
		}
		else if(x==2)
			break;
	}
}
