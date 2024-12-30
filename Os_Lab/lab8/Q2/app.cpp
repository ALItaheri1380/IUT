#include<unistd.h>

#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::string;

int main(int argc, char *argv[])
{
    if( argc != 2 ) { cerr<<"argument Faild"; exit(EXIT_FAILURE); }

    std::string str(argv[1]);

    cout<<"i'm going to sleep "<<str<<"sec\n";
    sleep( std::stoi(str) );

    return 0;
}
