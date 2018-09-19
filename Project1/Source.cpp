#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <list>

using namespace std;

ifstream ifs;
ofstream ofs;
vector<string> strVctr;
map<list<string>, vector<string>> wordMap;
list<string> state;
int M = 2;
string fileName;

string removePunctuation(string word) {
	for (int i = 0; i < word.size(); ++i) {
		if (!isalpha(word.at(i))) {
			word.erase(word.begin() + i);
		}
	}

	return word;
}

void openFile() {

	string openFile = fileName + ".txt";

	ifs.open(openFile);

	if (!ifs.is_open())
	{
		cout << "File \"" << fileName << "\" could not open." << endl;
	}

	else {
		cout << "Reading file \"" << fileName << "\"." << endl;
	}
}

void createWordVector() {

	string temp;
	string word;
	int wordCount = 0;

	while (ifs >> temp) {
		word = removePunctuation(temp);
		strVctr.push_back(word);
		wordCount++;
	}

	string openFile = fileName + "_vector.txt";

	ofs.open(openFile);

	for (int i = 0; i < strVctr.size(); ++i) {
		ofs << strVctr.at(i) << endl;
	}

	ofs << endl << "Word Count: " << wordCount << endl;

	cout << "Word Vector Created..." << endl << endl;

	ofs.close();
	ifs.close();


}

void createWordSet() {

	string temp = "";
	set <string> strset;
	string word;
	int wordCount = 0;

	while (ifs >> temp) {
		word = removePunctuation(temp);
		strset.insert(word);
	}

	string openFile = fileName + "_set.txt";

	ofs.open(openFile);

	for (set<string>::iterator i = strset.begin(); i != strset.end(); ++i) {
		ofs << *i << endl;
		wordCount++;
	}

	ofs << endl << "Word Count: " << wordCount << endl;

	cout << "Word Set Created..." << endl << endl;

	ofs.close();
	ifs.close();

}

void createWordMap() {

	for (int i = 0; i < M; ++i) {
		state.push_back("");
	}

	for (int i = 0; i < strVctr.size(); i++) {
		wordMap[state].push_back(strVctr.at(i));
		state.push_back(strVctr.at(i));
		state.pop_front();
	}

	string openFile = fileName + "_1_1.txt";

	ofs.open(openFile);

	/*map<list<string>, vector<string>>::iterator i;

	for (i = wordMap.begin(); i != wordMap.end(); ++i)
	{
	for (int k = 0; k < i->first.size(); ++k) {
	ofs << i->first.
	}
	ofs << i->first.
	for (int j = 0; j < i->second.size(); ++j) {
	ofs << ", " << i->second.at(j);
	}
	ofs << endl;
	}
	*/
	cout << "Word Map Created..." << endl << endl;

	ifs.close();
	ofs.close();

}


int main() {

	cout << "What file would you like to read from?" << endl;
	cin >> fileName;

	openFile();

	createWordSet();

	openFile();

	createWordVector();

	createWordMap();

	state.clear();

	srand(time(NULL));

	for (int i = 0; i < M; i++) {
		state.push_back("");
	}
	for (int i = 0; i < 100; i++) {
		int ind = rand() % (wordMap[state].size());
		cout << wordMap[state][ind] << " ";
		state.push_back(wordMap[state][ind]);
		state.pop_front();
	}

	cout << endl;

	return 0;
}

