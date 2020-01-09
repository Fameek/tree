#include <iostream>
#include <vector>
using namespace std;

#define SHOWER vector<vector<int>>
struct branch
{
	int key;
	int data;
	branch* previos;                // материнская векта 
	branch* right;                // больше
	branch* left;               // меньше
};
class tree {
private:
	branch* head;   // вершина
	

	void fill_shower(SHOWER& shower,int max_level, int level, branch* qq) {
		int shower_value = -999;
		if (qq != nullptr) {
			shower_value = qq->data;
		}
		shower[level].push_back(shower_value);
		if (max_level > level + 1) {
			branch* pointer = nullptr;
			if (qq != nullptr && qq->left != nullptr) {
				pointer = qq->left;
			}
			fill_shower(shower,max_level, level + 1, pointer);

			pointer = nullptr;
			if (qq != nullptr && qq->right != nullptr) {
				pointer = qq->right;
			}
			fill_shower(shower, max_level, level + 1, pointer);

		}
	}
	
	void dellBranchByAdress(branch* qq) {
		if (qq != nullptr) {
			dellBranchByAdress(qq->left);
			dellBranchByAdress(qq->right);
			delete qq;
		}
	}
	branch* findByIndex(int key) {
		branch* pp = head;
		if (head == nullptr) {

		}
		else if (head != nullptr) {
			while (pp != nullptr) {
				if (key == pp->key) {
					break;
				}
				else if (key >= pp->key) {
					if (pp->right != nullptr) {
						pp = pp->right;
					}
					else {
						pp = nullptr;

						break;
					}
				}
				else {
					if (pp->left != nullptr) {
						pp = pp->left;
					}
					else {

						pp = nullptr;
						break;
					}
				}
			}
		}
		return pp;
	}

	string set_tab(int tab_cout) {
		string result = "";
		for (int i = 0; i < tab_cout; i++) {
			result += "  ";
		}
		return result;
	}

	void fasa1(branch* qq, int nn, int* size ) {
		
		nn++;
		if (qq != nullptr) {

			fasa1(qq->right, nn, size);

			fasa1(qq->left, nn, size);

			if (nn > * size) {
				*size = nn;
			}
		}
		

	}
	//
	//  
	void fasa2( int size, int stolb, branch* qq) {
		
		SHOWER shower(size);
		int row_id = 0;
		if (qq != nullptr) {
			fill_shower(shower, size, 0, qq);
			
			int tabb = shower[shower.size() - 1].size();
			for (const auto& row : shower) {
				for (const auto& elem : row) {
					if (elem != -999)
						cout << set_tab(tabb -1) << elem << set_tab(tabb);
					else
						cout << set_tab(tabb-1) << "NN" << set_tab(tabb);
					//cout << " ";

				}
				tabb /= 2;

				

				cout << endl;
			}
			//if (qq == head || qq == head->right || qq == head->right->right  ) {
			//	for (int i = 0; i < kk; i++)
			//	{ cout << " "; 
			//	} 
			//	cout << qq->data;
			//	for (int i = 0; i < kk; i++) { 
			//		cout << " "; 
			//	} 
			//	cout << endl;
			//}
			//else {
			//	for (int i = 0; i < kk; i++) {
			//		cout << " ";
			//	}
			//	cout << qq->data;
			//	for (int i = 0; i < kk; i++) {
			//		cout << " ";
			//	}
			//}
			//fasa2(kk, size, stolb, qq->left); 
			//fasa2(kk, size, stolb, qq->right);
			
		}

	}




public:
	tree() {
		head = nullptr;
	}
	
	void addBranch(int key, int data) {
		branch* pp = new branch;
		pp->data = data;
		pp->key = key;
		if (head == nullptr) {
			pp->left = nullptr;
			pp->previos = nullptr;
			pp->right = nullptr;
			head = pp;
		}
		else {
			branch* qq = head;
			
			while (qq != nullptr) 
			{
				
					if (qq->key == key) {
						qq->data = pp->data;
						
						break;
					}
					else if (key >= qq->key) {
						if (qq->right != nullptr) {
							qq = qq->right;
						}
						else {
							break;
						}
					}
					else
						if (qq->left != nullptr) {
							qq = qq->left;
						}
						else
							break;
				
				
			}
			if (qq->key != pp->key) {
				pp->previos = qq;
				pp->left = nullptr;
				pp->right = nullptr;
				if (key >= qq->key)
					qq->right = pp;
				else if (key <= qq->key)
					qq->left = pp;
			}
			else
				delete pp;
		}
	}
	void findBranch(int key) {
		branch* pp = head;
		if (head == nullptr) {
			cout << "Not find!";
		}
		else if (head != nullptr) {
			while (pp != nullptr) {
				if (key == pp->key) {
					cout << pp->data;
					break;
				}
				else if (key >= pp->key) {
					if (pp->right != nullptr) {
						pp = pp->right;
					}
					else {
						cout << "Not Find!";
						break;
					}
				}
				else {
					if (pp->left != nullptr) {
						pp = pp->left;
					}
					else {
						cout << "Not Find!";
						break;
					}
				}
			}
		}
	}
	void dellBrench(int key) {
		branch* pp = findByIndex(key);
		
		if (pp != nullptr) {
			if (key == pp->key) {
				if (pp->previos != nullptr) {
					branch* qq = pp->previos;
					if (key >= qq->key)
						qq->right = nullptr;
					else if (key <= qq->key)
						qq->left = nullptr;
					dellBranchByAdress(pp);
				}
				else {
					head = nullptr;
					dellBranchByAdress(pp);
				}
			}
			else
				cout << "Not Find!";
		}

	}

	void dellTree() {
		if (head != nullptr) {
			branch* pp = head;
			dellBranchByAdress(pp);
			head = nullptr;
		}
		else
			cout << "Tree is not find";

	}
	void dellElementByIndex(int key) {
		branch* del = findByIndex(key);
		if (del != head) {
			

			if (del != nullptr) {
				branch* mat = del->previos;
				branch* left = del->left;
				branch* right = del->right;
				if (right != nullptr) {
					if (right->key >= mat->key) {
						mat->right = right;

					}
					else if (right->key <= mat->key) {
						mat->left = right;
					}
					right->previos = mat;
					while (right->left != nullptr) {
						right = right->left;
					}
					right->left = left;
					left->previos = right;
					delete del;
				}
				else if (right == nullptr && left != nullptr) {
					if (left->key >= mat->key) {
						mat->right = left;

					}
					else if (left->key <= mat->key) {
						mat->left = left;
					}
					left->previos = mat;
					delete del;

				}
				else if (right == nullptr && left == nullptr) {
					if (del->key >= mat->key)
						mat->right = nullptr;
					else if (del->key <= mat->key)
						mat->left = nullptr;
					delete del;
				}
			}
			else
				cout << "Not find!" << endl;
		}
		else
			cout << "Head cannot be removed!!" << endl;
	}


	void printTree() {

		int size = 0;
		
		int nn = 0;
		branch* qq = head;
		fasa1(qq, nn, &size);
		int stolb = 0;
		for (int i = 0; i < size; i++) {
			nn = 1 + nn * 2;
			stolb = stolb + nn;
		}
		stolb = stolb + size;

		int kk = stolb;


		fasa2(size, stolb, qq);
		
		
			











	


		//int size = 0;
		//branch* qq = head;
		//int nn = 1;
		//int kk = 0;
		//while (1) {
		//	if (qq->left != nullptr && kk == 0) {
		//		qq = qq->left;
		//		nn++;
		//	}
		//	else if (qq->left == nullptr && qq->right != nullptr) {
		//		qq = qq->right;
		//		nn++;
		//	}
		//	else if (qq->left == nullptr && qq->right == nullptr) {
		//		qq = qq->previos;
		//		nn--;
		//	}
		//  }
		//////////////////
		//int i;
		//
		//if (qq != nullptr) {
		//	
		//	printTree(qq->right, p + 3);
		//	for (i = 0; i < p; i++) {
		//		cout << " ";

		//	}
		//	cout << qq->data ;
		//	
		//	printTree(qq->left, p + 3);
		//}
		//////////////////
		//
		//if (qq != NULL)
		//{
		//	printTree(qq->left, k + 3);

		//	for (unsigned i = 0; i < k; i++)
		//	{
		//		cout << "  ";
		//	}
		//	cout << qq->data << endl;
		//	printTree(qq->right, k + 3);
		//}
		//






	}
	~tree() {
		branch* pp = head;
		head = nullptr;
		dellBranchByAdress(pp);

	}
};

int main() {
	tree n;
	n.addBranch(10, 4);
	n.addBranch(5, 5);
	n.addBranch(15, 4);


	
	n.printTree();
	return 0;
}