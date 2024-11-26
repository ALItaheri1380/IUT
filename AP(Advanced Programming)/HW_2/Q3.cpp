#include<iostream>
#include<string>
using namespace std;
template<typename T>
 struct Node
{
    T data;
    struct Node* next;
	struct Node *preview;
};
struct size{
    
    int SIZE;
};
struct size a;
template<typename T>
int SIze(Node<T>*head){
	int f=0;
	  while (head != NULL)
    {
        head=head->next;
        f++;
    }
	return f;
}
template<typename T>
Node<T>* CreateNode(T data){
    Node<T>* newNode = new Node<T>();
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}
double Avg(Node<string>*head){
    double sum=0;
    double avg;
    int flag=0;
    while (head!=NULL)
    {
        sum+=(head->data).size();
        head=head->next;
        flag++;
    }
    if(flag==0){
        return 0;
    }
    avg=sum/flag;
    return avg;
    
}
template<typename T>
double Avg(Node<T>*head){
    double sum=0;
    double avg=0;
    int flag=0;
    while (head != NULL)
    {
        sum+=head->data;
        head=head->next;
        flag++;
    }
    if (flag==0){
        return 0;
    }
    avg=sum/flag;
    return avg;
}
template<typename T>
void printNode(Node<T>*node){
    cout<<node->data<<endl;
}
template<typename T>
void PrintLinkedList(Node<T>* head)
{
    while (head != NULL)
    {
        cout<<head->data<<endl;
        head = head->next;
    }
    return;
}
template<typename T>
void push_front(Node<T>** head,T data)
{
    Node<T>* newNode = CreateNode(data);
    (*newNode).next = *head;
    *head = newNode;  

}
template<typename T>
void push_back(Node<T>** head, T data)
{
    Node<T>* newNode = CreateNode(data);
    Node<T>* tmp = *head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = newNode;
}
template<typename T>
void pop_front(Node<T>** head)
{
    if (*head!=NULL)
    {
        Node<T>* tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
}
template<typename T>
void pop_back(Node<T>** head)
{
    if (*head!=NULL)
    {
    Node<T>* tmp = *head;
    Node<T>* old = *head;
    for(;tmp->next!=NULL;tmp = tmp->next){
       old=tmp;
    }
    old->next = NULL;
    free(tmp);
    }
}
template<typename T>
void bubble_sort_LinkedList_itr(Node<T>** head)
{
    int n = SIze(*head)-1;
  
   while(n--)

   {
    Node<T>* prev =NULL;
    Node<T>*cur = *head;
    while(cur->next!=NULL)
    {
        if(cur->data >=cur->next->data)
        {
            
            if(prev==NULL)
            {
                //first node
                Node<T>* nxt = cur->next ;
                cur->next = nxt->next ;
                nxt->next = cur ;
                 prev=nxt ;
                *head = prev ;
               
                
            }
            
            else
            {
                
                Node<T>* nxt = cur->next ;
                prev->next = nxt ;
                cur->next = nxt->next ;
                nxt->next = cur ;
                prev = nxt ;   
            }   
        }
        else
        {
             prev = cur ; 
            cur=cur->next ;  
        }
       }   
   }  
}
void bubble_sort_LinkedList_itr(Node<string>** head)
{
    int n = SIze(*head)-1;
  
   while(n--)

   {
    Node<string>* prev =NULL;
    Node<string>*cur = *head;
    while(cur->next!=NULL)
    {
        if(cur->data.size() >=cur->next->data.size())
        {   
            if(prev==NULL)
            {
                //first node
                Node<string>* nxt = cur->next ;
                cur->next = nxt->next ;
                nxt->next = cur ;
                 prev=nxt ;
                *head = prev ;
            }
            else
            {   
                Node<string>* nxt = cur->next ;
                prev->next = nxt ;
                cur->next = nxt->next ;
                nxt->next = cur ;
                prev = nxt ;   
            }   
        }
        else
        {
             prev = cur ; 
            cur=cur->next ;  
        }
       }   
   }  
}
template<typename T>
void insert(Node<T>** head, int index, T data)
{
    if (index == 0)
        push_front(head, data);
    else{
        int dd;
        Node<T>* tmp = *head;
        Node<T>* old = *head;
        for(dd=0;dd<index;dd++)
        {
            if (tmp == NULL)
                break;
            old = tmp;
            tmp = tmp->next;
        }
        if (tmp == NULL && index == dd)
            push_back(head, data);
        else 
        {
            if(index == dd && tmp != NULL){
                Node<T>* newNode = CreateNode(data);
                newNode->next = tmp;
                old->next = newNode;
            }
            else
               cout<<"invalid input size!";    
            
        }
    }
}
template<typename T>
void Delete(Node<T>** head, int index)
{
    if (index < 0)
        cout<<"invalid input size!"<<endl;
    else
    {
        if (index == 0)
            pop_front(head);
        else
        {
            int dd ;
            Node<T>* tmp = *head;
            Node<T>* old = *head;
            for(dd=0;dd!=index;dd++){
                if (tmp->next == NULL)
                      break;
                old = tmp;
                tmp = tmp->next;
            }
            if (tmp == NULL && index == dd)
                pop_front(head);
            else if (index == dd && tmp != NULL)
            {
                old->next = tmp->next;
                free(tmp);
            }
            else
                cout<<"invalid input size!"<<endl;
        }
    }
}
template<typename T>
int search(Node<T>* head,T key)
{
    int index = 0;
    Node<T>* temp = head;
    while (head->data != key)
    {
        if (temp->data == key)
        {
            return index ;
        }
        index++;
        temp = temp->next;
    }
    return -1;
}
string maxx(Node<string>* head){
    int x=head->data.size();
    string Max;
    while (head!=NULL)
    {
        if(head->data.size() > x)
            Max=head->data;
        x=head->data.size();
        head=head->next; 
    }
    return Max;
}
template<typename T>
T maxx(Node<T>* head)
{
    T M=head->data;    
    while (head != NULL){
        if (head->data > M)
            M = head->data;
        head=head->next;    
    }
    return M;
}   
template<typename T>
Node<T>* searchNode(Node<T>* head, int index)///tabe azafe vase car khodame
{
    Node<T>* tmp = head;
    int ff ;
    for(ff=0;ff !=  index;ff++){
        tmp = tmp->next;
    }
    return tmp;
}
template<typename T>
void swap(Node<T>** head, int index1, int index2)
{
    Node<T>* node1 = searchNode(*head, index1);
    Node<T>* node2 = searchNode(*head, index2);
    T tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}
template<typename T>
void deleteList(Node<T>** head)
{
	Node<T>* current = *head;
	Node<T>* next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}
template<typename T>
void reassign(Node<T>**node,int index,T newdata){
     Delete(node,index);
     insert(node,index,newdata);
}
int main(){
    string a="ali";
    string b="lalalalal";
    string c="jasjjsjj";
    string z="a";
    string zz="zzzzz";
     Node<string>* head=CreateNode(a);
	 push_front(&head,b);
     push_front(&head,c);
     push_front(&head,z);
     push_front(&head,zz);
     /*PrintLinkedList(head);
	 cout<<"-------"<<endl;
     reassign(&head,search(head,a),z);
     PrintLinkedList(head);
     cout<<"-------"<<endl;*/
    PrintLinkedList(head);
    cout<<"\n----------------\n";
    bubble_sort_LinkedList_itr(&head);
    PrintLinkedList(head);
   	//cout<<maxx(head);
}