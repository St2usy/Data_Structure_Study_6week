#pragma once
#include "BinaryNode.h"
#include <cstdlib>
#define MAX_QUEUE_SIZE 100

inline void error(const char* str)
{
	std::cout << str << '\n';
	exit(1);
}

class CircularQueue_BinaryNode_ver {
private:
	int front;
	int rear;
	BinaryNode* data[MAX_QUEUE_SIZE];
public:
	CircularQueue_BinaryNode_ver() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }
	void enqueue(BinaryNode* n) {
		if (isFull())
			error("Error : 큐가 포화 상태입니다.\n");
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	BinaryNode* dequeue() {
		if (isEmpty())
			error("Error : 큐가 공백 상태입니다.");
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
};

class BinaryTree : public CircularQueue_BinaryNode_ver {
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
			printf(" [%d] ", node->getData());
			inorder(node->getRight());
		}
	}
	void preorder() {
		printf("\n%11s ", "preorder:");
		preorder(root);
	}
	void preorder(BinaryNode* node)	{ // 전위
		if (node != NULL) {
			printf(" [%d] ", node->getData());
			preorder(node->getLeft());
			preorder(node->getRight());
		}
	}
	void postorder() {
		printf("\n%11s ", "postorder:");
		postorder(root);
	}
	void postorder(BinaryNode* node) { // 후위
		if (node != NULL) {
			postorder(node->getLeft());
			postorder(node->getRight());
			printf(" [%d] ", node->getData());
		}
	}
	void levelorder() {
		printf("\n%11s ", "levelorder:");
		if (!isEmpty()) {
			CircularQueue_BinaryNode_ver q;
			q.enqueue(root);
			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();
				if (n != NULL) {
					printf(" [%d] ", n->getData());
					q.enqueue(n->getLeft());
					q.enqueue(n->getRight());
				}
			}
		}
	}

	bool isFull() { return isEmpty() ? 0 : isFull(root); }
	bool isFull(BinaryNode* node) {
		if (node->isLeaf())   return true; // 인자가 단말노드면 true다.
		if (getHeight(node->getLeft()) == getHeight(node->getRight())) { // 왼쪽 서브트리의 높이가 오른쪽 서브트리의 높이와 같다면
			return isFull(node->getLeft()) && isFull(node->getRight()); // 왼쪽 서브트리와 오른쪽 서브트리에 순환 호출을 해준다. 
		}
		return false; // 단말노드에 도달하기 전에 높이가 다르다면 false를 반환한다.
	}
	int getHeight() { return isEmpty() ? 0 : getHeight(root); }
	int getHeight(BinaryNode* node) { //매개변수를 각 서브트리의 root부터 시작하여 가장 깊은 곳까지 탐색을 진행함
		if (node == NULL) return 0;
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
	}
	bool isBalanced() { return isEmpty() ? 1 : isBalanced(root); }
	bool isBalanced(BinaryNode* node) {
		int leftHeight;
		int rightHeight;
		if (node == NULL) // 단말노드는 참을 반환한다. 혹은 루트노드 단독일때도 참을 반환한다.
			return true;
		leftHeight = getHeight(node->getLeft());
		rightHeight = getHeight(node->getRight());
		if ((leftHeight - rightHeight) <= 1 && (leftHeight - rightHeight) >= -1 && isBalanced(node->getLeft()) && isBalanced(node->getRight())) //좌우의 높이차이가 1 ~ -1 사이이며 자식노드들 또한 동일한 조건을 만족 
			return true;
		return false;
	}
	void reverse(BinaryNode* node) {
		if (node == NULL)	return;
		else {
			reverse(node->getLeft()); // 단말노드까지 순환호출
			reverse(node->getRight()); // 단말노드까지 순환호출
			BinaryNode* temp = node->getLeft(); // 숫자 바꾸는 알고리즘과 동일
			node->setLeft(node->getRight());
			node->setRight(temp);
		}
		return;
	}
	int getLeafCount() { return isEmpty() ? 0 : getLeafCount(root); }
	int getLeafCount(BinaryNode* node) {
		if (node == NULL) return 0;
		if (node->isLeaf())return 1;
		else return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
	}
	int getCount() { return isEmpty() ? 0 : getCount(root); }
	int getCount(BinaryNode* node) {
		if (node == NULL) return 0;
		return 1 + getCount(node->getLeft()) + getCount(node->getRight());
	}

	int evaluate(BinaryNode* node) {
		if (node == NULL) return 0;
		if (node->isLeaf()) return node->getData();
		else {
			int op1 = evaluate(node->getLeft());
			int op2 = evaluate(node->getRight());
			switch (node->getData()) {
			case'+': return op1 + op2; break;
			case'-': return op1 - op2; break;
			case'*': return op1 * op2; break;
			case'/': return op1 / op2; break;
			}
			return 0;
		}
	}
	int calcSize() { return calcSize(root); }
	int calcSize(BinaryNode* node) {
		if (node == NULL) return 0;
		return node->getData() + calcSize(node->getLeft()) + calcSize(node->getRight());
	}
};