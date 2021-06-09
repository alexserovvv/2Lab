#pragma once
#include "PriorityQueue.h"
#include "RedBlackTree.h"
#include "Stack.h"
#include "PriorityQueue.cpp"
class HuffmanAlg
{
private:
	class Node
	{
	public:
		Node(int f = 0, Node* lC = nullptr, Node* rC = nullptr, char l = '\n') {
			frequence = f;
			letter = l;
			left = lC;
			right = rC;
			parent = nullptr;
		};
		~Node() {};
		int frequence;
		char letter;
		Node* left;
		Node* right;
		Node* parent;
	};
	void copyBoolArray(bool* copy, bool* str, int size) {
		for (size_t i = 0; i < size; i++)
			copy[i] = str[i];
	};
	Node* root;
	char* str;
	size_t sizeStr;
	bool* readyCode;
	size_t sizeReadyCode;
	struct strArr
	{
		bool* str = NULL;
		int size = 0;
	};
	RedBlackTree<char, strArr*> codeLetter;
public:
	HuffmanAlg(char* _str) {
		if (_str == NULL)
		{
			throw exception("null argument");
		}
		codeLetter = RedBlackTree<char, strArr*>();
		str = _str;
		sizeStr = 0;
		for (size_t i = 0; str[i] != '\n'; i++)
			sizeStr++;
		if (sizeStr > 1)
		{
			PriorityQueue<Node*> PQ;
			Node* bufNode_1;
			Node* bufNode_2;
			int chars[256] = { 0 };
			for (int i = 0; str[i] != '\n'; i++)
				chars[str[i] + 128]++;
			int countLetter = 0;
			cout << "Frequency table: " << endl;
			for (int i = 0; i < 256; i++)
				if (chars[i] != 0) {
					countLetter++;
					cout << (char)(i - 128) << " : " << chars[i] << endl;
					bufNode_1 = new Node(chars[i], nullptr, nullptr, (i - 128));
					PQ.push(bufNode_1, chars[i]);
				}
			int bufInt;
			bufInt = PQ.tail_priority();
			bufNode_1 = PQ.pop();
			for (size_t i = 0; (i < countLetter) && (!PQ.isEmpty()); i++)
			{
				bufInt += PQ.tail_priority();
				bufNode_2 = PQ.pop();
				root = new Node(bufInt, bufNode_1, bufNode_2);
				bufNode_1->parent = root;
				bufNode_2->parent = root;
				PQ.push(root, root->frequence);
				bufInt = PQ.tail_priority();
				bufNode_1 = PQ.pop();
			}
			bool* bufStr = new bool[countLetter / 2 + 1];
			memset(bufStr, 0, countLetter / 2 + 1);
			size_t indexStr = 0;
			unsigned int bufCodeLetter = 0;
			Stack<Node*> dft;
			if (root->right != nullptr)
			{
				dft.push(root->right);
			}
			bufNode_1 = root;
			strArr* bufStrArr = new strArr;
			cout << "Code table: " << endl;
			while (!dft.isEmpty())
			{
				while (bufNode_1->left != nullptr)
				{
					bufStr[indexStr] = 0;
					indexStr++;
					bufNode_1 = bufNode_1->left;
					if (bufNode_1->right != nullptr)
					{
						dft.push(bufNode_1->right);
					}
				}
				bufStrArr = new strArr;
				bufStrArr->str = new bool[indexStr];
				bufStrArr->size = indexStr;
				copyBoolArray(bufStrArr->str, bufStr, indexStr);
				cout << bufNode_1->letter << " : ";
				for (size_t i = 0; i < indexStr; i++)
				{
					cout << bufStrArr->str[i];
				}
				cout << endl;
				codeLetter.insert(bufNode_1->letter, bufStrArr);
				indexStr--;
				while ((bufNode_1->parent != nullptr) && (bufNode_1->parent->right != dft.get_last()))
				{
					bufNode_1 = bufNode_1->parent;
					indexStr--;
				}
				bufNode_1 = dft.pop();
				if (bufNode_1->right != nullptr)
				{
					dft.push(bufNode_1->right);
				}
				bufStr[indexStr] = 1;
				indexStr++;
			}
			bufStrArr = new strArr;
			bufStrArr->size = indexStr;
			bufStrArr->str = new bool[indexStr];
			copyBoolArray(bufStrArr->str, bufStr, indexStr);
			cout << bufNode_1->letter << " : ";
			for (size_t i = 0; i < indexStr; i++)
			{
				cout << bufStrArr->str[i];
			}
			cout << endl;
			codeLetter.insert(bufNode_1->letter, bufStrArr);
			readyCode = NULL;
			sizeReadyCode = 0;
			delete bufStr;
		}
		else {
			cout << "Frequency table: " << str[0] << " " << 1 << endl;
			cout << "Code table: " << str[0] << " " << 0 << endl;
			root = new Node(1, nullptr, nullptr, str[0]);
			sizeReadyCode = 0;
			readyCode = NULL;
			strArr* bufStrArr = new strArr;
			bufStrArr->str = new bool[1];
			bufStrArr->str[0] = false;
			bufStrArr->size = 1;
			codeLetter.insert(str[0], bufStrArr);
		}
	}
	bool* Code(int& codeSize) {
		bool* copyStr;
		codeSize = 0;
		for (int i = 0; str[i] != '\n'; i++) {
			codeSize += codeLetter.find(str[i])->size;
		}
		sizeReadyCode = codeSize;
		readyCode = new bool[codeSize];
		size_t indexStr = 0;
		for (int i = 0; str[i] != '\n'; i++) {
			copyStr = codeLetter.find(str[i])->str;
			for (size_t j = 0; j < codeLetter.find(str[i])->size; j++) {
				readyCode[indexStr] = copyStr[j];
				indexStr++;
			}
		}
		return readyCode;
	}
	char* Decode(int& sizeStrDecode) {
		char* decodeStr = new char[sizeStr + 1];
		sizeStrDecode = sizeStr;
		if (sizeStr == 1)
		{
			decodeStr[0] = root->letter;
			decodeStr[0] = '\n';
		}
		else {
			size_t indexCode = 0;
			Node* curNode = root;
			size_t indexDecode = 0;
			while (indexCode < sizeReadyCode)
			{
				if ((readyCode[indexCode] == 0) && (curNode->left != nullptr))
				{
					curNode = curNode->left;
					indexCode++;
				}
				else if ((readyCode[indexCode] == 1) && (curNode->right != nullptr)) {
					curNode = curNode->right;
					indexCode++;
				}
				else {
					decodeStr[indexDecode] = curNode->letter;
					indexDecode++;
					curNode = root;
				}
			}
			decodeStr[indexDecode] = curNode->letter;
			decodeStr[indexDecode + 1] = '\n';
		}
		return decodeStr;
	}
	~HuffmanAlg() {

	}

};


