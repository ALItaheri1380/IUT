#include<iostream>
using namespace std;
struct Node
{
    int key;
    struct Node *leeft;
    struct Node *right;
};
///***signaturs are***///
void sortt(Node *rrr  , int &p ,int arr[]);
Node* insert(Node* node, int key);
void binery(int arr[], int n);
///*** end off signaturs ***///
void sortt(Node *rrr  , int &p ,int arr[])
{
    if (rrr != NULL)
    {
        sortt(rrr->leeft,p , arr);
        arr[p++] = rrr->key;
        sortt(rrr->right, p, arr);
    }
}
Node* insert(Node* node, int key)
{
    if (node == NULL)
    {
        Node *temp = new Node();
        temp->key = key;
        temp->leeft = NULL;
        temp->right = NULL;
        return temp;
    }
    if (key < node->key)
        node->leeft = insert(node->leeft, key);
    else
        node->right = insert(node->right, key);
    return node;
}
void binery(int arr[], int n)
{
    Node *rrr = NULL;
    rrr = insert(rrr, arr[0]);
    int o=1;
    while (o<n){
        rrr= insert( rrr, arr[o]);
        o++;
    }
    int p = 0;
    sortt(rrr,p, arr);
}
int main()
{
    int n;
    cin>>n;
    int *arr =(int *) malloc(sizeof(int)*n) ;
    int ttt=0;
    while(ttt<n)
    {
        cin>>arr[ttt];
        ttt++;
    }
    binery(arr, n);
    int tttt=0;
    while(tttt<n){
        cout << arr[tttt] << " ";
        tttt++;
    }
    free(arr);
    return 0;
}