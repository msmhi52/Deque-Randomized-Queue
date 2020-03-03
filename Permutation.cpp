#include <iostream>
#include <string>
#include <sstream>

#include "RandomizedQueue.cpp"

using namespace std;

int main(int argc, char** argv){
	RandomizedQueue<string> rq;

	string str;
	getline(cin, str);
	istringstream sstr(str);

	string n;
	while(sstr >> n){
		rq.enqueue(n);
	}
	
	size_t count = 0;
	for(RandomizedQueue<string>::iterator_t itr = rq.begin(); itr != rq.end(); itr++){
		cout << *itr << "\n";
		count++;
		if(count == atoi(argv[1])) break;
	}
	return 0;
}




