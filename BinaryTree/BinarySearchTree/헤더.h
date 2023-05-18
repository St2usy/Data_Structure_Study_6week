#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#define MAX_WORD_SIZE 40
#define MAX_MEANING_SIZE 200
using std::string;
class Record {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
public:
	Record(const char* w="", const char* m="") { set(w, m); }
	void set(const char* w, const char* m) {
		strcpy(word, w);
		strcpy(meaning, m);
	}
	int compare(Record* n) { return compare(n->word); }
	int compare(const char* w) { return strcmp(w, word); }
	int comparemeaing(const char* m) { return strcmp(meaning, m); }
	void display() { std::cout << word << " : " << meaning; }
	void copy(Record* n) { set(n->word, n->meaning); }
	const char* getword() { return word; }
	const char* getmeaning() { return meaning; }
};

#include <iostream>
class BinaryNode : public Record {
protected:
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(const char* w="",const char* m="", BinaryNode * l = NULL, BinaryNode * r = NULL)
		: Record(w,m), left(l), right(r) {}
	void setLeft(BinaryNode* l) { left = l; }
	void setRight(BinaryNode* r) { right = r; }
	BinaryNode* getLeft() { return left; }
	BinaryNode* getRight() { return right; }
	bool isLeaf() { return left == NULL && right == NULL; }
};

#define MAX_QUEUE_SIZE 100
inline void error(const char* str)
{
	std::cout << str << '\n';
	exit(1);
}

class BinaryTree {
protected:
	BinaryNode* root;
public:
	BinaryTree() : root(NULL) {}
	void setRoot(BinaryNode* node) { root = node; }
	BinaryNode* getRoot() { return root; }
	bool isEmpty() { return root == NULL; }

	void inorder() {
		printf("\n%11s ", "inorder:");
		inorder(root);
	}
	void inorder(BinaryNode* node) { // 중위
		if (node != NULL) {
			inorder(node->getLeft());
			node->display();
			inorder(node->getRight());
		}
	}
};

class BinSrchTree : public BinaryTree {
public:
	BinaryNode* search(const char* key) { return searchRecur(root, key); }
	BinaryNode* searchRecur(BinaryNode* n, const char* key) {
		if (n == NULL) return NULL;
		if (n->compare(key)==0) return n;
		else if (n->compare(key)<0) return searchRecur(n->getLeft(), key);
		else return searchRecur(n->getRight(), key);
	}
	void insert(BinaryNode* n) {
		if (n == NULL) return;
		if (isEmpty()) root = n;
		else insertRecur(root, n);
	}
	void insertRecur(BinaryNode* r, BinaryNode* n) {
		if (n->compare(r)==0) return;
		else if (n->compare(r) > 0) {
			if (r->getLeft() == NULL) r->setLeft(n);
			else insertRecur(r->getLeft(), n);
		}
		else {
			if (r->getRight() == NULL) r->setRight(n);
			else insertRecur(r->getRight(), n);
		}
	}
	void remove(const char* key) {
		if (isEmpty()) return;
		BinaryNode* parent = NULL;
		BinaryNode* node = root;
		while (node != NULL && node->compare(key)!=0) {
			parent = node;
			node = (node->compare(key) < 0) ? node->getLeft() : node->getRight();
		}
		if (node == NULL) {
			std::cout << "Error" << std::endl;
			return;
		}
		else remove(parent, node);
	}
	void remove(BinaryNode* parent, BinaryNode* node) {
		if (node->isLeaf()) {
			if (parent == NULL) root = NULL;
			else {
				if (parent->getLeft() == node) parent->setLeft(NULL);
				else parent->setRight(NULL);
			}
		}
		else if (node->getLeft() == NULL || node->getRight() == NULL) {
			BinaryNode* child = (node->getLeft() != NULL) ? node->getLeft() : node->getRight();
			if (node == root) root = child;
			else {
				if (parent->getLeft() == node) parent->setLeft(child);
				else parent->setRight(child);
			}
		}
		else {
			BinaryNode* succp = node;
			BinaryNode* succ = node->getRight();
			while (succ->getLeft() != NULL) {
				succp = succ;
				succ = succ->getLeft();
			}
			if (succp->getLeft() == succ) succp->setLeft(succ->getRight());
			else succp->setRight(succ->getRight());
			node->set(succ->getword(), succ->getmeaning());
			node = succ;
		}
		delete node;
	}
};

class Dictionary : public BinSrchTree {
public:
	void printAllWords() {
		std::cout << "   >> 나의 단어장:" << std::endl;
		if (!isEmpty()) inorder(root);
	}
	void searchWord(const char* word) {
		BinaryNode* node = search(word);
		if (node != NULL) {
			std::cout << "   >> ";
			node->display();
		}
		else std::cout << "   >> 등록되지 않은 단어: " << word << std::endl;
	}
	void searchMeaning(const char* meaning) {
		BinaryNode* node = (isEmpty()) ? NULL : searchByMeaning(root, meaning);
		if (node != NULL) {
			std::cout << "   >> ";
			node->display();
		}
		else std::cout << "   >> 등록되지 않은 의미: " << meaning << std::endl;
	}
	BinaryNode* searchByMeaning(BinaryNode* node, const char* meaning) {
		if (node == NULL || node->comparemeaing(meaning) == 0) return node;
		BinaryNode* theNode = searchByMeaning(node->getLeft(), meaning);
		if (theNode != NULL) return theNode;
		return searchByMeaning(node->getRight(), meaning);
	}
};

