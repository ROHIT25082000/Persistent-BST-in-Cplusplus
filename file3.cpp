#include <iostream> 
#include "tree.h" 

using namespace std;  

int main() 
{
    vector<double> vc_double; 
    
    using namespace tree;  

    char arr[100]; 
    cout << "double test\n";
    cout << "Enter name of the BST-file : (*.dat or *.txt) \n";  
    cin >> arr; 
    
    Tree<double> mytree(arr);

    cout << "<<<<<< BST initialized >>>>>> \n";
    cout << "1. Insert key " << endl; 
    cout << "2. Delete Key " << endl; 
    cout << "3. Inorder traversal " << endl; 
    cout << "4. Preorder traversal " << endl; 
    cout << "5. Postorder traversal " << endl;  
    cout << "6. getvector " << endl;
    cout << "7. Exit " << endl << endl; 
    while(true)
    {
        int n; 
        cout << "Enter the options : "; 
        cin >> n;
        double key; 

        switch (n)
        {
            case 1:
                cout << "Enter the key : "; 
                cin >> key; 
                mytree.insert(key);
                break;
            case 2: 
                cout << "Enter a key to delete : "; 
                cin >> key; 
                mytree.delete_key(key);
                cout << "Success !" << endl;
                break; 
            case 3: 
                mytree.display_inorder();
                break;
            case 4: 
                mytree.display_preorder(); 
                break; 
            case 5: 
                mytree.display_postorder(); 
                break;
            case 6: 
                vc_double = mytree.get_inorder(); 
                cout << "Returned vector : ";
                for(int i = 0; i < vc_double.size(); ++i){
                    cout << vc_double.at(i) << " ";
                }
                cout << "\n";
                vc_double = mytree.get_postorder(); 
                cout << "Returned vector : ";
                for(int i = 0; i < vc_double.size(); ++i){
                    cout << vc_double.at(i) << " ";
                }
                cout << "\n";
                vc_double = mytree.get_preorder(); 
                cout << "Returned vector : ";
                for(int i = 0; i < vc_double.size(); ++i){
                    cout << vc_double.at(i) << " ";
                }
                cout << "\n";
                break; 
            case 7: 
                return 0;
        default:
            cout << "Invalid Input !!" << endl; 
        }

    }
    return 0; 
}