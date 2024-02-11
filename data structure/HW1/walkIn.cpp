#include <iostream>
#include "List.h"
#include <string>
using namespace std;

int main()
{
    List *head = new List();

    Patient *temp = new Patient("5232323344");
    temp->setAddress("najaf_abad");
    temp->setEmail("ali@iut.ir");
    temp->setName("ali");
    temp->setPhone("09134515488");

    head->insert(*temp);

    Patient *temp2 = new Patient("7232323344");
    temp2->setAddress("yazd");
    temp2->setEmail("mmd@iut.ir");
    temp2->setName("mohammad");
    temp2->setPhone("09924545441");

    head->insert(*temp2);

    Patient *temp3 = new Patient("1232323344");
    temp3->setAddress("naein");
    temp3->setEmail("amirzand@iut.ir");
    temp3->setName("amir");
    temp3->setPhone("09133238649");

    head->insert(*temp3);

    Patient *temp4 = new Patient("3332323344");
    temp4->setAddress("yazd");
    temp4->setEmail("hrb@iut.ir");
    temp4->setName("hamid");
    temp4->setPhone("09181243457");

    head->insert(*temp4);

    Patient *temp5 = new Patient("9332323344");
    temp5->setAddress("sharkord");
    temp5->setEmail("bigashkan@iut.ir");
    temp5->setName("ashkan");
    temp5->setPhone("09385751248");

    head->insert(*temp5);

    Patient *temp6 = new Patient("4332623344");
    temp6->setAddress("darab");
    temp6->setEmail("darabzsh@iut.ir");
    temp6->setName("Shirazi");
    temp6->setPhone("09196543274s");

    head->insert(*temp6);

    Patient *temp7 = new Patient("6332623344");
    temp7->setAddress("naein");
    temp7->setEmail("naghi@iut.ir");
    temp7->setName("naghi");
    temp7->setPhone("09145469620");

    head->insert(*temp7);

    Patient *temp8 = new Patient("4352683394");
    temp8->setAddress("birjand");
    temp8->setEmail("ejalali@iut.ir");
    temp8->setName("ehsan");
    temp8->setPhone("09941238475");

    head->insert(*temp8);

    Patient *temp9 = new Patient("8122613254");
    temp9->setAddress("naein");
    temp9->setEmail("adelz@iut.ir");
    temp9->setName("adel");
    temp9->setPhone("09136529874");

    head->insert(*temp9);

    Patient *temp10 = new Patient("5421616284");
    temp10->setAddress("abarkooh");
    temp10->setEmail("amirali@iut.ir");
    temp10->setName("amirali");
    temp10->setPhone("816686151");

    head->insert(*temp10);

    Patient *temp11 = new Patient("1421656283");
    temp11->setAddress("esfahan");
    temp11->setEmail("ardalan@iut.ir");
    temp11->setName("delfar");
    temp11->setPhone("09816686151");
    
    head->insert(*temp11);
    
    
    
    head->printList();

    cout<<"\n/**********************************************************************/\n";

    head->Edit("4352683394");
    head->printList();

    cout<<"\n/**********************************************************************/\n";

    head->remove(*temp4);
    head->remove(*temp9);

    head->printList();
}