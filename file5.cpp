#include <iostream> 
#include "tree.h" 

using namespace std;  


class rectangle
{
    public:
        int length;
        int breadth; 
        explicit rectangle(int length = 0, int breadth = 0)
        :length(length),breadth(breadth){

        }
        rectangle(const rectangle & source)
        :length(source.length),breadth(source.breadth){ 
        }

        rectangle & operator=(const rectangle & source)
        {
            if(this != &source){
                this->length = source.length; 
                this->breadth = source.breadth; 
            }
            return *this;
        }
        
        friend bool operator==(const rectangle & lhs, const rectangle & rhs); 
        friend bool operator<(const rectangle & lhs, const rectangle & rhs); 
        friend bool operator>(const rectangle & lhs, const rectangle & rhs);  
        friend bool operator!=(const rectangle & lhs, const rectangle & rhs); 
        friend std::ostream & operator<<(std::ostream & os, const rectangle & obj); 
};

bool operator==(const rectangle & lhs, const rectangle & rhs){
    if(lhs.length * lhs.breadth == rhs.length * rhs.breadth){
        return true; 
    }
    else{ 
        return false; 
    }
} 

bool operator<(const rectangle & lhs, const rectangle & rhs){
    if(lhs.length * lhs.breadth < rhs.length * rhs.breadth){
        return true; 
    }
    else{ 
        return false; 
    }
}


bool operator>(const rectangle & lhs, const rectangle & rhs){
    
    if(lhs.length * lhs.breadth > rhs.length * rhs.breadth){
        return true; 
    }
    else{ 
        return false; 
    }
}  
bool operator!=(const rectangle & lhs, const rectangle & rhs){
    if(lhs.length * lhs.breadth != rhs.length * rhs.breadth){
        return true; 
    }
    else{ 
        return false; 
    }
} 


std::ostream & operator<<(std::ostream & os, const rectangle & obj){
    os << "{ " << obj.length << " , " << obj.breadth  << " }"; 
    return os;
}




int main() 
{
    vector<rectangle> vc_int; 
    
    using namespace tree;  

    char arr[100]; 
    cout << "user defined test \n";
    cout << "Enter name of the BST-file : (*.dat or *.txt) \n";  
    cin >> arr; 
    
    Tree<rectangle> mytree(arr);

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
        int length;
        int breadth;  

        switch (n)
        {
            case 1:{
                
                cout << "Enter  length : "; 
                cin >> length;
                cout << "Enter  breadth: "; 
                cin >> breadth; 
                mytree.insert(rectangle(length,breadth));
                break;
            }
            case 2: 
                cout << "Enter a rectangle to delete "; 
                cout << "Enter  length : "; 
                cin >> length;
                cout << "Enter  breadth: "; 
                cin >> breadth; 
                mytree.delete_key(rectangle(length,breadth));
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
                vc_int = mytree.get_inorder(); 
                cout << "Returned vector : ";
                for(int i = 0; i < vc_int.size(); ++i){
                    cout << vc_int.at(i) << " ";
                }
                cout << "\n";
                vc_int = mytree.get_postorder(); 
                cout << "Returned vector : ";
                for(int i = 0; i < vc_int.size(); ++i){
                    cout << vc_int.at(i) << " ";
                }
                cout << "\n";
                vc_int = mytree.get_preorder(); 
                cout << "Returned vector : ";
                for(int i = 0; i < vc_int.size(); ++i){
                    cout << vc_int.at(i) << " ";
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