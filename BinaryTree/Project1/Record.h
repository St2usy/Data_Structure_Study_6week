#pragma once
#include <string>
#include <iostream>
#define MAX_WORD_SIZE 40
#define MAX_MEANING_SIZE 200
using std::string;
class Record {
	string word;
	string meaning;
public:
	Record(string w, string m) { set(w, m); }
	void set(string w, string m) {
		word = w;
		meaning = m;
	}
	bool compare(Record* n) { return compare(n->word); }
	bool compare(string w) { return w == word; }
	bool comparemeaing(string m) { return m == meaning; }
	void display() { std::cout << word << " : " << meaning; }
	void copy(Record* n) { set(n->word, n->meaning); }
};