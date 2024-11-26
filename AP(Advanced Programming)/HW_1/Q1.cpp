#include<iostream>
using namespace std;
typedef struct Node
{
    int data;
    struct Node* next;
} Node;
struct size{
    
    int SIZE;
};
struct size a;
///*****************Signatures are*****************///
Node* CreateNode(int data);
int Avg(Node*head);
void printNode(Node*node);
void PrintLinkedList(Node* head);
void push_front(Node** head, int data);
void push_back(Node** head, int data);
void pop_front(Node** head);
void pop_back(Node** head);
void insert(Node** head, int index, int data);
void Delete(Node** head, int index);
int search(Node* head,int key);
int maxx(Node* head);
Node* searchNode(Node* head, int index);
void swap(Node** head, int index1, int index2);
///*****************END OFF*****************///
Node* CreateNode(int data){
    Node* newNode = new Node();
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}
int Avg(Node*head){
    int sum=0;
    int avg=0;
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
void printNode(Node*node){
    cout<<node->data<<endl;
}
void PrintLinkedList(Node* head)
{
    while (head != NULL)
    {
        cout<<head->data<<endl;
        head = head->next;
    }
    return;
}
void push_front(Node** head, int data)
{
    Node* newNode = CreateNode(data);
    (*newNode).next = *head;
    *head = newNode;  

}
void push_back(Node** head, int data)
{
    Node* newNode = CreateNode(data);
    Node* tmp = *head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = newNode;
}
void pop_front(Node** head)
{
    if (*head!=NULL)
    {
        Node* tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
}
void pop_back(Node** head)
{
    if (*head!=NULL)
    {
    Node* tmp = *head;
    Node* old = *head;
    for(;tmp->next!=NULL;tmp = tmp->next){
       old=tmp;
    }
    old->next = NULL;
    free(tmp);
    }
}
void insert(Node** head, int index, int data)
{
    if (index == 0)
        push_front(head, data);
    else
    {
        int dd;
        Node* tmp = *head;
        Node* old = *head;
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
                Node* newNode = CreateNode(data);
                newNode->next = tmp;
                old->next = newNode;
            }
            else
               cout<<"invalid input size!";    
            
        }
    }
}
void Delete(Node** head, int index)
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
            Node* tmp = *head;
            Node* old = *head;
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
int search(Node* head,int key)
{
    int index = 0;
    Node* temp = head;
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
int maxx(Node* head)
{
    int M=head->data;    
    while (head != NULL){
        if (head->data > M)
            M = head->data;
        head=head->next;    
    }
    return M;
}        
Node* searchNode(Node* head, int index)
{
    Node* tmp = head;
    int ff ;
    for(ff=0;ff !=  index;ff++){
        tmp = tmp->next;
    }
    return tmp;
}
void swap(Node** head, int index1, int index2)
{
    Node* node1 = searchNode(*head, index1);
    Node* node2 = searchNode(*head, index2);
    int tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}
int main(){
   int x;
   //in ro gozashtam ta khata kompail nade
}