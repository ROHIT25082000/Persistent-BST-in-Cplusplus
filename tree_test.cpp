#include <iostream> 
#include "tree.h"  

using namespace std; 

int main() 
{ 	/*
	node<int>obj1(12); 
	node<int>obj2(13); 
	*/ 
	//cout << boolalpha;  
	//cout << (obj1 == obj2); 

	Tree<int>t1("one.dat"); 
	cout << "Inorder :\n";  
	t1.display_inorder(); 
	cout << "Preorder \n"; 
	t1.display_preorder();
	cout << "Postorder \n"; 
	t1.display_postorder();
	
	int n; 
	cout << "Enter n : "; 
	cin >> n;  
	
	cout << "Enter " << n << "numbers : ";  
	for(int i = 0; i < n; ++i){
		int temp; 
		cin >> temp; 	
		t1.insert(temp);
	}

	t1.display_inorder();  
	
	return 0;
}
