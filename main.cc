#include "controller.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char* argv[]){
	bool invalid = false;
	vector<string> args = vector<string>();
	bool graphics = false;
	string l1 = ""; string l2 = "";
       	string a1 = ""; string a2 = "";
	for(int i = 1; i < argc; ++i){
		string cmd(argv[i]);
		if(cmd == "-link1" || cmd == "-link2"){
			try {
			string s(argv[i+1]);
			if(s[0] == '-') invalid = true;
			else if(s.size() != 16) invalid = true;
			for(int i = 0; i < s.size(); i+=2){
				if(s[i] != 'D' && s[i] != 'V') invalid = true;
				else if(s[i+1] < '1' || s[i+1] > '4') invalid = true;
			}
			if(!invalid && cmd == "-link1") l1 = s;
		       	else if(!invalid && cmd == "-link2") l2 = s;
			++i;
			} catch(...) { invalid = true; }	
		} else if(cmd == "-ability1" || cmd == "-ability2"){
			try{
			string s(argv[i+1]);
			if(s[0] == '-') invalid = true;
			else if(s.size() != 5) invalid = true;
			for(int i = 0; i < s.size(); ++i){
				if(s[i] != 'L' && s[i] != 'F' && s[i] != 'D' && s[i] != 'S'
						&& s[i] != 'P'){
					invalid = true;
				}
			}
			if(!invalid && cmd == "-ability1") a1 = s;
			else if(!invalid && cmd == "-ability2") a2 = s;
			++i;
			} catch(...) { invalid = true; }
		} else if(cmd == "-graphics") {
			graphics = true;
		} else {
			cout << "G" << endl;
			invalid = true;
		}

	}

	if(invalid){
		cerr << "Usage: RAIInet [options]" << endl;
		cerr << "\t-ability1 <order> - the cards P1 wants to start with" << endl;
		cerr << "\t-ability2 <order> - the cards P2 wants to start with" << endl;
		cerr << "\t-link1 <order> - the link order P1 wants their pieces in" << endl;
		cerr << "\t-link2 <order> - the link order P2 wants their pieces in" << endl;
		cerr << "\t-graphics - enable graphical interface" << endl;
		return 1;
	}

	unique_ptr<Controller> con = make_unique<Controller>(l1, l2, a1, a2, graphics);
	con->startGame();
}
