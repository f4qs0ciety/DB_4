#include<iostream>
using namespace std;

class Tree {
private:
	class Branch {
	public:
		int data; //Содержимое элемента
		int height; //Высота поддерева
		Branch* left; //Ссылка на левое поддерево
		Branch* right; //Ссылка на правое поддерево
		Branch(int input, Branch* left = nullptr, Branch* right = nullptr) {
			this->data = input;
			this->height = 1;
			this->left = left;
			this->right = right;
		}
	};
	Branch* root = new Branch(2);

	int getHeight(Branch* current) { return current ? current->height : 0; } //Геттер для поля height, работающий с нулевыми указателями

	void fixHeight(Branch* current) { //Пересчёт высот ветвей
		if (current->left != nullptr) fixHeight(current->left);
		if (current->right != nullptr) fixHeight(current->right);
		if (current->left == nullptr && current->right == nullptr) current->height = 0;
		if (getHeight(current->left) > getHeight(current->right)) current->height = getHeight(current->left) + 1; else current->height = getHeight(current->right) + 1;
	}
	
	Branch* smallLeft(Branch* a) { //Малый левый поворот
		Branch* b = a->right;
		a->right = b->left;
		b->left = a;
		return b;
	}

	Branch* bigLeft(Branch* a) { //Большой левый поворот
		Branch* b = a->right;
		Branch* c = b->left;
		a->right = c->left;
		b->left = c->right;
		c->left = a;
		c->right = b;
		return c;
	}

	Branch* smallRight(Branch* a) { //Малый правый поворот
		Branch* b = a->left;
		a->left = b->right;
		b->right = a;
		return b;
	}

	Branch* bigRight(Branch* a) { //Большой правый поворот
		Branch* b = a->left;
		Branch* c = b->right;
		a->left = c->right;
		b->right = c->left;
		c->right = a;
		c->left = b;
		return c;
	}

	void balance(Branch* current) {
		if (current->left != nullptr) balance(current->left);
		if (current->right != nullptr) balance(current->right);
		if (getHeight(current->right) - getHeight(current->left) == 2 && getHeight(current->right->left) <= getHeight(current->right->right)) { if (current == root) root = smallLeft(current); else current = smallLeft(current); }
		if (getHeight(current->right) - getHeight(current->left) == 2 && getHeight(current->right->left) > getHeight(current->right->right)) { if (current == root) root = bigLeft(current); else current = bigLeft(current); }
		if (getHeight(current->left) - getHeight(current->right) == 2 && getHeight(current->left->right) <= getHeight(current->left->left)) { if (current == root) root = smallRight(current); else current = smallRight(current); }
		if (getHeight(current->left) - getHeight(current->right) == 2 && getHeight(current->left->right) > getHeight(current->left->left)) { if (current == root) root = bigRight(current); else current = bigRight(current); }
	}

	void showTree() {
		int counter = 0;
		Branch* current = root;
		cout << endl << "Текущее дерево: " << endl;
		showBranch(root);
		cout << endl;
	}

	void showBranch(Branch* current) {
		if (current->left != nullptr) showBranch(current->left);
		if (current->right != nullptr) showBranch(current->right);
		cout << current->data << " ";
	}

	void addBranch() {
		int input;
		cout << "Введите число: ";
		cin >> input;
		if (root->data == NULL) root->data = input; else {
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
		}
		fixHeight(root);
		balance(root);
		cout << endl << "Элемент добавлен!" << endl;
		showTree();
	}

	void deleteBranch() {
		int input;
		cout << "Введите число, которое хотите удалить: ";
		cin >> input;
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
		else if (temp->left == nullptr && temp->right == nullptr) {
			if (side == false) current->left = nullptr; else current->right = nullptr;
			delete (temp);
		}
		fixHeight(root);
		balance(root);
		cout << endl << "Элемент удалён!" << endl;
		showTree();
	}
public:
	Tree(int input) {
		this->root->data = input;
	}

	void menu() {
		int option;
		bool stop = false;
		do {
			cout << endl << "Что вы хотите сделать с деревом?" << endl << "[1] Добавить элемент." << endl << "[2] Удалить элемент." << endl << "[3] Просмотреть дерево." << endl << "[4] Выйти из программы." << endl << "Ваш выбор: ";
			cin >> option;
			switch (option) {
			case 1: { addBranch(); break; }
			case 2: { deleteBranch(); break; }
			case 3: { showTree(); break; }
			case 4: { stop = true; }
			}
		} while (stop != true);
	}
};

void main() {
	setlocale(LC_ALL, "Russian");
	Tree Lipa(NULL);
	Lipa.menu();
}