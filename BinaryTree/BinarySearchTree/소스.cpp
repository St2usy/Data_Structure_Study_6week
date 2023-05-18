#include "���.h"
#include <conio.h>
void help() {
	std::cout << "[����] i-�߰� d-���� w-�ܾ�˻� m-�ǹ̰˻� p-��� q-���� =>";
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
			std::cout << "  > ���� �ܾ�: "; fgets(word, 80, stdin);
			std::cout << "  > �ܾ� ����: "; fgets(meaning, 200, stdin);
			tree.insert(new BinaryNode(word, meaning));
			break;
		case 'd':
			std::cout << "  > ���� �ܾ�: "; fgets(word, 80, stdin);
			tree.remove(word);
			break;
		case 'p':
			tree.printAllWords();
			std::cout << std::endl;
			break;
		case 'w':
			std::cout << "  > �˻� �ܾ�: "; fgets(word, 80, stdin);
			tree.searchWord(word);
			break;
		case 'm':
			std::cout << "  > �˻� �ǹ�: "; fgets(word, 80, stdin);
			tree.searchMeaning(word);
			break;
		}
		fflush(stdin);
	} while (command != 'q');
}