#include <iostream>
#include<string.h>
#include<string>
using namespace std;

//**signaturs**//
void draw(int position);
void guessword(string word);
void guess_string(string word);
//**end of signaturs**//
int main(int argc, char* argv[])
{
    if(argc==1)
       return 0;
	bool test=true;
     int number;
	 int flag;
     int count = 0;
     int position;
     string word = argv[1]; 
     char letter;
     
	 for (int i = 0; i < word.length(); i++)
  	{
  		word[i] = tolower(word[i]);
  	}
    cout<<"do you want guess char or string?"<<"\nif you want guess char input 0"<<"\nif you guess the string input 1\n";
    int worody;
    cin>>worody;
    if(worody==0)
        guessword(word);
    else
        guess_string(word);
}
void guess_string(string word){
     cout<<"\n\n\nYou have only one chance; If you make a mistake, you will be executed\n\n\n";
     string gues;
     cin>>gues;
     if(gues==word){
        cout<<"\n\nyou win :))\n\n";
        return;
     }
     else
     {
        cout<<"\n\n\nYOU LOSE....,You will be executed\n\n\n";
        draw(5);
        return;

     }
}
void guessword(string word)
{
	string* bakht=new string[5];
	int flag=0;
	int cntr=0;
	int con;
    char letter;
    int position;
    int i=0;
	bool test=true;
	int Size=word.size();
   string* blankword=new string[Size];
    for (int i = 0; i < word.size(); i++)
	{
		blankword[i]='_';
	} 
     while (i<5&&con!=word.size())
     {
		 con=0;

     cout << "What letter would you like to guess?";
     cin >>letter;
	 letter=tolower(letter);
     position = word.find(letter);
     if (position > word.length())
        {
            bakht[cntr]=letter;
			flag++;
			draw(flag);
			
         cout<<letter<< " is not in the word "<<endl;
		 cout<<"invalid guessword is :";
		 for ( int i1 = 0; i1 <=cntr; i1++)
		 {
			  cout<<bakht[i1]<<" ";
		 }
		 cout<<'\n';
		 cntr++;
         i++;
        }
     else 
     {
        cout<< letter << " is in the word"<<endl;
	for (int t = 0; t < word.size(); t++)
	{
		if(word[t]==letter){
			blankword[t]=letter;
		}
	}
	
		for (int i = 0; i < word.size(); i++)
		{
			cout<<blankword[i];
		}
		cout<<"\n";
		for (int i = 0; i < word.size(); i++)
	    {
		if(blankword[i]!="_")
            con++;
		if(con==word.size()){	
            cout<<"Congratulations, You Win!!";
            break;
     	 }
		}
		
     }  
  if (i==5&&con!=word.size()){
  cout<<"You Lose :("<<endl;
  cout<<"you die........."<<endl;
  draw(5);
  exit(0);
  }
 }
}  
void draw(int position)
{
     if(position==1){
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |         " <<endl;
            cout << "_|______________"<<endl; 
            
	 }  
     else if(position==2){   
	        cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |         0 " <<endl;
            cout << "_|______________"<<endl;     
    
	 }
     else if(position==3){       
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 /" <<endl;
            cout << "_|______________"<<endl;
   
	 }  
     else if(position==4){
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 /" <<endl;
            cout << " |         |"<<endl;
            cout << "_|______________"<<endl;
	 }          
     else if(position==5){  
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 /" <<endl;
            cout << " |         |"<<endl;
            cout << " |        / \\ "<<endl;
            cout << "_|______________"<<endl;
     }    
}     