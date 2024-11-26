#include<iostream>
#include <sstream>
using namespace std;

class LinkedList
{
    private:
        LinkedList* next;
        int data;
    public:
  LinkedList* get_next()
  {
      return next;
  }
  int get_data()
  {
      return data;
  }   
  LinkedList* push_front(int x)
  {
    LinkedList* temp = this;
    
    LinkedList* new_node = new LinkedList();
 
    new_node->data = x;
 
    new_node->next = temp;

    temp = new_node;
    
    return temp;
  }
  
  static bool tooshe(LinkedList* header1, int x)
  {
    LinkedList* test = header1;
    
    while(test != nullptr)
    {
        if(test->data == x)
            return true;
            
        test = test->next;
    }
    
    return false;
  }
  static LinkedList* Union(LinkedList* header1, LinkedList* header2)
  {
    LinkedList* tmp = nullptr;
    
    LinkedList* linked_list = header1;
    
    while(linked_list != nullptr)
    {
        if(!LinkedList::tooshe(linked_list->next, linked_list->data))
            tmp = tmp->push_front(linked_list->data);
            
        linked_list = linked_list->next;
    }
    
    while(header2 != nullptr)
    {
        int x = header2->data;
        
        linked_list = header1;
        bool flag = false;
        
        if(!LinkedList::tooshe(linked_list, x))
             tmp = tmp->push_front(x);
      
        header2 = header2->next;
    }
    
    return tmp;
  }
};

int main()
{
    LinkedList* header1 = nullptr;
    LinkedList* header2 = nullptr;
    string line;
    getline( cin, line ); 
    istringstream is( line );
    int n;
    while( is >> n ) 
    {
        header1 = header1->push_front(n);    
    }
    
    getline( cin, line ); 
    
    istringstream is2( line );
    while( is2 >> n ) 
    {
        header1 = header1->push_front(n);    
    }
    
    LinkedList *new_list = LinkedList::Union(header1, header2);
    while(new_list != nullptr)
    {
        cout << new_list->get_data() << " ";
        
        new_list = new_list->get_next();
    }
    return 0;
}
