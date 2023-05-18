#include "헤더.h"
#include <conio.h>
void help() {
	std::cout << "[사용법] i-추가 d-삭제 w-단어검색 m-의미검색 p-출력 q-종료 =>";
}
void main() {
	char command;
	char word[80];
	char meaning[200];
	Dictionary tree;
	do {
		help();
		command = getchar();
		std::cout << std::endl;
		switch (command) {
		case 'i':
			std::cout << "  > 삽입 단어: "; fgets(word, 80, stdin);
			std::cout << "  > 단어 설명: "; fgets(meaning, 200, stdin);
			tree.insert(new BinaryNode(word, meaning));
			break;
		case 'd':
			std::cout << "  > 삭제 단어: "; fgets(word, 80, stdin);
			tree.remove(word);
			break;
		case 'p':
			tree.printAllWords();
			std::cout << std::endl;
			break;
		case 'w':
			std::cout << "  > 검색 단어: "; fgets(word, 80, stdin);
			tree.searchWord(word);
			break;
		case 'm':
			std::cout << "  > 검색 의미: "; fgets(word, 80, stdin);
			tree.searchMeaning(word);
			break;
		}
		fflush(stdin);
	} while (command != 'q');
}