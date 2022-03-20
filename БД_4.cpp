#include<iostream>
using namespace std;

class Tree {
private:
	class Branch {
	public:
		int data; //Содержимое элемента
		Branch* left; //Ссылка на левое поддерево
		Branch* right; //Ссылка на правое поддерево
		Branch(int input, Branch* left = nullptr, Branch* right = nullptr) {
			this->data = input;
			this->left = left;
			this->right = right;
		}
	};
	Branch* root = new Branch(2);
public:
	void showTree() {
		int counter = 0;
		Branch* current = root;
		cout << "Текущее дерево: " << endl;
		/*do {
			current = current->left;
		} while (current->left != nullptr || current->right != nullptr);*/
		showBranch(root);
	}

	void showBranch(Branch* current) {
		if (current->left != nullptr) showBranch(current->left);
		if (current->right != nullptr) showBranch(current->right);
		cout << current->data << " ";
	}

	int searchBranch(Branch* current, int input) {
		
	}

	void addBranch(int input) {
		/*int input;
		cout << "Введите число: ";
		cin >> input;*/
		Branch* current = root;
		while (true) {
			if (input == current->data) { cout << "Такой элемент уже существует!" << endl; break; }
			if (input < current->data) {
				if (current->left == nullptr) {
					current->left = new Branch(input);
					break;
				}
				else current = current->left;
			}
			if (input > current->data) {
				if (current->right == nullptr) {
					current->right = new Branch(input);
					break;
				}
				else current = current->right;
			}
		}
		cout << "Элемент добавлен!" << endl;
		showBranch(root);
	}

	void deleteBranch(int input) {
		/*int input;
		cout << "Введите число, которое хотите удалить: ";
		cin >> input;*/
		Branch* current = root;
		Branch* temp;
		bool side; //Индикатор для temp: если false - левый элемент от current, если true - правый
		while (true) {
			if (input == current->left->data) { temp = current->left; side = false; break; }
			else if (input == current->right->data) { temp = current->right; side = true; break; }
			if (input < current->data) current = current->left;
			else if (input > current->data) current = current->right;
		}
		if (temp->left != nullptr && temp->right != nullptr) {
			Branch* replace = temp->right;
			while (true) {
				if (replace->left->left == nullptr && replace->left->right == nullptr) {
					temp->data = replace->left->data;
					replace->left = nullptr;
					delete replace->left;
					break;
				}
				replace = replace->left;
			}
		}
		else if (temp->left == nullptr && temp->right != nullptr) {
			if (side == false) current->left = temp->right; else current->right = temp->right;
			delete (temp);
		}
		else if (temp->right == nullptr && temp->left != nullptr) {
			if (side == false) current->left = temp->left; else current->right = temp->left;
			delete (temp);
		}
		else if (temp->left == nullptr && temp->left == nullptr) {
			if (side == false) current->left = nullptr; else current->right = nullptr;
			delete (temp);
		}
		cout << endl << "Элемент удалён!" << endl;
		showBranch(root);
	}

	Tree() {
		this->root->data = 8;
	}
};

void main() {
	setlocale(LC_ALL, "Russian");
	Tree Lipa;
	Lipa.showTree();
	Lipa.addBranch(4);
	Lipa.addBranch(10);
	Lipa.addBranch(2);
	Lipa.addBranch(6);
	Lipa.addBranch(1);
	Lipa.addBranch(3);
	Lipa.addBranch(5);
	Lipa.addBranch(7);
	Lipa.addBranch(9);
	Lipa.deleteBranch(9);
}