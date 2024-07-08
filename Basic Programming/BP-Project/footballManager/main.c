#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asciis.h"
struct TeamManager // vase safe 2
{
    char email[30];
    char password[30];
    int teamId;
};
struct FederasionManager // vase admin
{
    char username[30];
    char password[30];
};
struct Player
{
    int id;
    char name[30];
    int attackPower;
    int defensePower;
    int value;
    char teamName[30];
};
struct Team
{
    char name[30];
    char managerEmail[30];
    int teamId;
    int budget;
    struct Player teamPlayers[8];
    int teamPlayerCounter;
    int isReadyToPlay;
    int wins;
    int loses;
    int draws;
    int gf;
    int ga;
    int gd;
    int pts;
};

struct League
{
    struct Team teams[4];
    struct Team teamsOpponents[4][6]; ////harif
    int ehtiat[6];
    int ehtiat2[6];
};

struct LeagueOtherInfo
{
    int IthWeek;
    int doesLeagueStarted;
    int doesTransferWindowOpened;
};

struct FederasionManager federasionManager;
struct LeagueOtherInfo leagueOtherInfo;
struct Team teams[100];
struct TeamManager teamManagers[100];
struct League league;
int teamsCounter = 0;
struct Player players[800];
int playersCounter = 0;
int IthWeek = 1;
int doesLeagueStarted = 0;
int doesTransferWindowOpened = 0;
////////////////////////////////////////////////////////////////////////////////////
void login();
void forgetPassword();
void federasionManagerMenu();
void teamManagerMenu(int index);
int doesTeamManagerExist(char username[], char password[]);
int doesTeamExist(char teamName[]);
int doesTeamManagerEmailExist(char email[]);
void addTeam();
int createIdForTeam();
int createIdForPlayer();
void changePassword(int teamIndex);
void addPlayer();
void showTeams();
void showTeam();
void showPlayers();
int defalt();
int defalt2();
void showPlayer(struct Player player);
void startLeague();
void chooseTeamsForLeague();
void createFixtures();
void playWeekIthGames();
void startWeekIthGames();
int getTeamAttack(struct Team team);
int getTeamDefense(struct Team team);
void showStandings();
void openCloseTransferWindows();
void announceChampion();
void sortPlayers();
void buyPlayer(int index);
void sellPlayer(int index);
void selectSquad(int index);
void leagueStanding();
void showFixtures(int index);
void showNextOpponent(int index);
void updatePassword(int index);
void readFromFiles();
void writeToFiles();
void welcome();
void futureGame(int week);
void createFixtures2();
void sortTeams(struct Team *teams);
void swapInt(int *a, int *b);
void paian();
///////////////////////////////
int main()
{
    printf(CLEAR);
    welcome();
    readFromFiles();
    strcpy(federasionManager.username, "admin");
    strcpy(federasionManager.password, "admin");
    while (1)
    {
        printf(FCYAN"1_login\n2_forget password\n3_exit\n");
        int caass;
        scanf("%d", &caass);
        switch (caass)
        {
        case 1:
            login();
            break;
        case 2:
            forgetPassword();
            break;
        case 3:
            writeToFiles();
            exit(0);
        default:
            printf(FRED"invelid....!!!!!\n");
        }
    }
}

//////////////////////////////////////////
/////////////////////////////////////////
void paian(){
printf(FRED"\n\n\n\nOOOOOOOOOOOOO   OO        OO   OOOOOOOOO     OOOOOOOOOOO    NN         N   DDD\n"); 
printf("      OO        OO        OO   OO            O              N  N       N   D   D\n");
printf("      OO        OO        OO   OO            O              N    N     N   D    D\n");
printf("      OO        OO        OO   OO            O              N     N    N   D     D\n");
printf("      OO        OOOOOOOOOOOO   OOOOOOOOO     OOOOOOOOOOO    N       N  N   D     D\n");
printf("      OO        OO        OO   OO            O              N        N N   D    D\n");
printf("      OO        OO        OO   OO            O              N         NN   D   D\n");
printf("      OO        OO        OO   OOOOOOOOO     OOOOOOOOOOO    N         NN   DDD\n\n\n");
}      
////////////////////////////////
void login()
{
    char password[30];
    char username[30];
    printf(FYELLOW"enter userName:\t");
    scanf("%s", &username);
    printf(FYELLOW"enter passWord:\t");
    scanf("%s", &password);

    if (strcmp(username, federasionManager.username) == 0 && strcmp(password, federasionManager.password) == 0)
        federasionManagerMenu();
    else
    {
        int teamMangerIndex = doesTeamManagerExist(username, password);

        if (teamMangerIndex == -1)
            printf(FRED"invelid userName or password..!!!\n");
        else
            teamManagerMenu(teamMangerIndex);
    }
}

void forgetPassword()
{
    printf(FMAGNETA"enter team name:\t\n");
    char teamName[30];
    scanf("%s",&teamName);

    printf(FMAGNETA"pls enter team manager; email:\t\n");
    char managerEmail[30];
    scanf("%s", &managerEmail);

    int teamIndex = doesTeamExist(teamName);
    if (teamIndex == -1)
    {
        printf(FRED"invelid team name or manager email....!!!!!\n");
        return;
    }
    else
    {
        if (strcmp(teams[teamIndex].managerEmail, managerEmail) == 0)
        {
            changePassword(teamIndex);
        }
        else
        {
            printf(FRED"invalid team name or manager email!\n");
            return;
        }
    }
}

void federasionManagerMenu()
{
    int x2 = 10000;
    while (x2)
    {
        printf(FLIMOIE"1.add team\n2.add player\n3.show teams\n4.show players\n");
        printf("5.start league\n6.open/close transfer window\n7.start %d th week\n8.announce champion and end league\n9.exit\n", IthWeek);

        int caass2;
        scanf("%d", &caass2);

        switch (caass2)
        {
        case 1:
            addTeam();
            break;
        case 2:
            addPlayer();
            break;
        case 3:
            showTeams();
            break;
        case 4:
            showPlayers();
            break;
        case 5:
            startLeague();
            break;
        case 6:
            openCloseTransferWindows();
            break;
        case 7:
            playWeekIthGames();
            break;
        case 8:
            announceChampion();
            break;
        case 9:
            x2 = 0;
            break;
        default:
            printf(FRED"invelid option!\n");
        }

        if (x2 == 0)
            break;
    }
}
void welcome()
{

    printf(FLIMOIE "\n\nH   H    EEEEE   L       L        OOOOO\n");
    printf("H   H    E       L       L       O     O\n");
    printf("H   H    E       L       L       O     O\n");
    printf("HHHHH    EEEEE   L       L       O     O\n");
    printf("H   H    E       L       L       O     O\n");
    printf("H   H    E       L       L       O     O\n");
    printf("H   H    EEEEE   LLLLL   LLLLL    OOOOO\n\n" );
}
void teamManagerMenu(int index)
{
    system("cls");

    int x = 10000;
    while (x)
    {
        printf(FBLUE"1.buy player\n2.sell player\n3.select/submit squad\n4.league standing\n5.fixtures\n6.upcomming opponent\n7.change password\n8.exit\n");

        int cass3;
        scanf("%d", &cass3);

        switch (cass3)
        {
        case 1:
            buyPlayer(index);
            break;
        case 2:
            sellPlayer(index);
            break;
        case 3:
            selectSquad(index);
            break;
        case 4:
            leagueStanding();
            break;
        case 5:
            showFixtures(index);
            break;
        case 6:
            showNextOpponent(index);
            break;
        case 7:
            updatePassword(index);
            break;
        case 8:
            x = 0;
            break;
        }

        if (x == 0)
            break;
    }
}

int doesTeamManagerExist(char username[], char password[])
{
    int i;
    for (i = 0; i < teamsCounter; i++)
    {
        if (strcmp(username, teamManagers[i].email) == 0 && strcmp(password, teamManagers[i].password) == 0)
        {
            return i;
        }
    }

    return -1;
}
int doesTeamExist(char teamName[])
{
    int i;
    for (i = 0; i < teamsCounter; i++)
    {
        if (strcmp(teamName, teams[i].name) == 0)
            return i;
    }

    return -1;
}

void changePassword(int teamIndex)
{
    printf(FCYAN"enter new password:\t");
    char newPassword[30];
    scanf("%s", newPassword);

    strcpy(teamManagers[teamIndex].password, newPassword);

    printf(FRED"changed was  succesfully..!!!\n");

    writeToFiles();
}

int doesTeamManagerEmailExist(char email[])
{
    int i;
    for (i = 0; i < teamsCounter; i++)
    {
        if (strcmp(email, teamManagers[i].email) == 0)
            return i;
    }

    return -1;
}
void addTeam()
{
    printf(FBLUE"enter team name:\t");
    char teamName[30];
    fflush(stdin); 
    scanf("%s",teamName);
    if (doesTeamExist(teamName) != -1)
    {
        printf(FRED"team is exist!\n");
        return;
    }

    printf(FORANGE"enter team manager email:\t");
    char managerEmail[30];
    scanf("%s", managerEmail);

    if (doesTeamManagerEmailExist(managerEmail) != -1)
    {
        printf(FRED"email is registered...!!!!\n");
        return;
    }

    int teamId = createIdForTeam();
    struct Team team;
    strcpy(team.managerEmail, managerEmail);
    strcpy(team.name, teamName);
    team.isReadyToPlay = 0;
    team.budget = 100;
    team.teamId = teamId;
    team.teamPlayerCounter = 0;
    struct TeamManager teamManager;
    strcpy(teamManager.email, managerEmail);
    strcpy(teamManager.password, managerEmail);
    teamManager.teamId = teamId;
    teams[teamsCounter] = team;
    teamManagers[teamsCounter] = teamManager;
    teamsCounter++;

    printf(FORANGE"\nsuccessfully aded!\nname:%s  , manager email :%s , budget:%d $ ,id:%d\n\n",
           teamName, managerEmail, team.budget, teamId);

    writeToFiles();
}

int createIdForTeam()
{
    srand(time(0));
    int random = (rand() % (9999 - 1000)) + 1000;
    while (1)
    {
        int doesExist = 0;
        int i;
        for (i = 0; i < teamsCounter; i++)
            if (teams[i].teamId == random)
            {
                doesExist = 1;
                break;
            }

        if (doesExist == 1)
            random = (rand() % (9999 - 1000)) + 1000;
        else
            return random;
    }
}

int createIdForPlayer()
{
    srand(time(0));
    int random = (rand() % (9999 - 1000)) + 1000;
    while (1)
    {
        int doesExist = 0;
        int i;
        for (i = 0; i < playersCounter; i++)
            if (players[i].id == random)
            {
                doesExist = 1;
                break;
            }

        if (doesExist == 1)
            random = (rand() % (9999 - 1000)) + 1000;
        else
            return random;
    }
}

void addPlayer()
{
    printf(FMAGNETA"enter name:\t");
    char name[30];
    fflush(stdin);
    gets(name);

    int attackPower;
    printf("enter attackpower(range [0-100] ):\t");
    scanf("%d", &attackPower);

    while (1)
    {
        if (attackPower >= 0 && attackPower <= 100)

            break;
        else
        {
            printf(FRED"attackpower must be in range [0-100]:\t");
            scanf("%d", &attackPower);
        }
    }
    int defensePower;
    printf(FMAGNETA"enter defense power(range [0-100] ):\t");
    scanf("%d", &defensePower);

    while (1)
    {
        if (defensePower >= 0 && defensePower <= 100){
            break;
        }
        else
        {
            printf(FRED"defense power must be in range [0-100]//: :\t");
            scanf("%d", &defensePower);
        }
    }
    int value;
    printf(FMAGNETA"enter value(range [10-20] ):\t");
    scanf("%d", &value);

    while (1)
    {
        if (value >= 10 && value <= 20)
            break;
        else
        {
            printf(FRED"value must be in range [10-20]!!!!!//:\t");
            scanf("%d", &value);
        }
    }

    int id = createIdForPlayer();

    struct Player player;
    strcpy(player.name, name);
    strcpy(player.teamName, "free agent");
    player.attackPower = attackPower;
    player.defensePower = defensePower;
    player.id = id;
    player.value = value;
    players[playersCounter] = player;
    playersCounter++;

    printf(FRED"player sucessfully added!\n");

    showPlayer(player);

    writeToFiles();
}
void showTeams()
{
    if (teamsCounter == 0)
    {
        printf(FRED"no team exist!\n");
        return;
    }

    int i;
    for (i = 0; i < teamsCounter; i++)
        showTeam(teams[i]);
}

void showPlayers()
{
    if (playersCounter == 0)
    {
        printf(FRED"no player exist!\n");
        return;
    }

    int i;
    for (i = 0; i < playersCounter; i++)
        showPlayer(players[i]);
}

void showTeam(struct Team team)
{
    printf(FYELLOW"name : %s , manager email : %s , id : %d , budget : %d , No of players: %d\n",
           team.name, team.managerEmail, team.teamId, team.budget, team.teamPlayerCounter);
    printf(FORANGE"\n----------------------------------\n");
    printf("players infos:\n");
    printf("\n----------------------------------\n");

    int i;
    int size = team.teamPlayerCounter;
    for (i = 0; i < size; i++)
        showPlayer(team.teamPlayers[i]);
}

void showPlayer(struct Player player)
{
    printf(FBLACK"\nid : %-3d  name : %-10s  value : %-3d  attacking power : %-3d  defense power : %-3d   team name : %-10s\n",
           player.id, player.name, player.value, player.attackPower, player.defensePower, player.teamName);
}

int defalt(struct Player player)
{
    return (player.attackPower);
}
int defalt2(struct Player player)
{
    return (player.defensePower);
}
void startLeague()
{
    if (doesLeagueStarted == 1)
        printf(FRED"league is already started!\n");
    else
    {
        if (teamsCounter < 4)
            printf("at least should exist 4 teams!\n");
        else
        {

            int readyTeamsCounts = 0;
            int i;
            for (i = 0; i < teamsCounter; i++)
                if (teams[i].isReadyToPlay == 1)
                    readyTeamsCounts++;

            if (readyTeamsCounts < 4)
                printf("teams are not yet sibmit squads!\n");
            else
                chooseTeamsForLeague();
        }
    }
}
void chooseTeamsForLeague()
{
    for (int i = 0; i < teamsCounter; i++)
    {
        printf("No . %d:\n", i);
        printf(FCYAN"name:%s  , manager email :%s , budget:%d $ ,id:%d\n\n",
               teams[i].name, teams[i].managerEmail, teams[i].budget, teams[i].teamId);
    }

    for (int i = 0; i < 4; i++)
    {
        printf(FBLUE"enter team %d number(No. that show above) to join the league:\t", i + 1);
        int index;
        scanf("%d", &index);

        if (index < 0 || index > teamsCounter)
        {
            printf(FRED"out of band index try again!\n");
            i--;
        }
        else
        {
            league.teams[i] = teams[index];
        }
    }

    createFixtures();
    for (int i = 0; i < 6; i++)
    {
        league.ehtiat[i] = 0;
    }
    printf(FRED"league successfully created!\n");
    doesLeagueStarted = 1;

    writeToFiles();
}
////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void createFixtures2()
{
    struct Team team;
    team.teamId = -1;
    //////////////////////////////////////////////////////////////////
    league.teamsOpponents[0][0] = league.teams[1];
    league.teamsOpponents[0][1] = league.teams[2];
    league.teamsOpponents[0][2] = league.teams[3];
    league.teamsOpponents[0][3] = league.teams[1];
    league.teamsOpponents[0][4] = league.teams[2];
    league.teamsOpponents[0][5] = league.teams[3];
    //////////////////////////////////////////////////////////////////
    strcpy(team.name, league.teams[0].name);
    league.teamsOpponents[1][0] = team;
    league.teamsOpponents[1][1] = league.teams[2];
    league.teamsOpponents[1][2] = league.teams[3];
    strcpy(team.name, league.teams[0].name);
    league.teamsOpponents[1][3] = team;
    league.teamsOpponents[1][4] = league.teams[2];
    league.teamsOpponents[1][5] = league.teams[3];
    //////////////////////////////////////////////////////////////////
    league.teamsOpponents[2][0] = league.teams[3];
    strcpy(team.name, league.teams[0].name);
    league.teamsOpponents[2][1] = team;
    strcpy(team.name, league.teams[1].name);
    league.teamsOpponents[2][2] = team;
    league.teamsOpponents[2][3] = league.teams[3];
    strcpy(team.name, league.teams[0].name);
    league.teamsOpponents[2][4] = team;
    strcpy(team.name, league.teams[1].name);
    league.teamsOpponents[2][5] = team;
    //////////////////////////////////////////////////////////////////
    strcpy(team.name, league.teams[2].name);
    league.teamsOpponents[3][0] = team;
    strcpy(team.name, league.teams[1].name);
    league.teamsOpponents[3][1] = team;
    strcpy(team.name, league.teams[0].name);
    league.teamsOpponents[3][2] = team;
    strcpy(team.name, league.teams[2].name);
    league.teamsOpponents[3][3] = team;
    strcpy(team.name, league.teams[1].name);
    league.teamsOpponents[3][4] = team;
    strcpy(team.name, league.teams[0].name);
    league.teamsOpponents[3][5] = team;
}
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void createFixtures()
{
    createFixtures2();
    int i;
    for (i = 0; i < 4; i++)
    {
        league.teams[i].gf = 0;
        league.teams[i].ga = 0;
        league.teams[i].gd = 0;
        league.teams[i].pts = 0;
        league.teams[i].wins = 0;
        league.teams[i].loses = 0;
        league.teams[i].draws = 0;
    }
    for (int ii = 0; ii < 6; ii++)
    {
        league.ehtiat[ii] = 0;
    }
    writeToFiles();
}

void playWeekIthGames()
{
    if (doesLeagueStarted == 0)
    {
        printf(FRED"leagues does not started yet!\n");
        return;
    }

    int canStartWeek = 1;

    for (int i = 0; i < 4; i++)
    {
        if (league.teams[i].isReadyToPlay == 0)
        {
            canStartWeek = 0;
            printf(FGREEN"team with name '%s' and manager email '%s' has not submit squad for game\n", /////////////////////////////////////////////////////////////////////////////////
                   league.teams[i].name, league.teams[i].managerEmail);
        }
    }

    if (canStartWeek == 1)
        startWeekIthGames();
    else
        printf(FRED"cannot start week %d th\n", IthWeek);

    writeToFiles();
}
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void futureGame(int week)
{
    for (int i = 0; i < 4; i++)
    {
        struct Team homeTeam = league.teams[i];
        struct Team awayTeam = league.teamsOpponents[i][week];
        int j;
        for (j = 0; j < 4; j++)
        {
            if (strcmp(league.teams[j].name, awayTeam.name) == 0)
                break;
        }

        //////////////////////////////////////////////////////////////////////
        if (awayTeam.teamId == -1)
            continue;
        else if (i == j)
            continue;
        else if (((i == 0) && (j == 3)) || ((i == 3) && (j == 0)))
        {
            league.ehtiat2[0] += 1;
            if (league.ehtiat2[0] >= 3)
                continue;
        }
        else if (((i == 0) && (j == 2)) || ((i == 2) && (j == 0)))
        {
            league.ehtiat2[1] += 1;
            if (league.ehtiat2[1] >= 3)
                continue;
        }
        else if (((i == 0) && (j == 1)) || ((i == 1) && (j == 0)))
        {
            league.ehtiat2[2] += 1;
            if (league.ehtiat2[2] >= 3)
                continue;
        }
        else if (((i == 1) && (j == 3)) || ((i == 3) && (j == 1)))
        {
            league.ehtiat2[3] += 1;
            if (league.ehtiat2[3] >= 3)
                continue;
        }
        else if (((i == 1) && (j == 2)) || ((i == 2) && (j == 1)))
        {
            league.ehtiat2[4] += 1;
            if (league.ehtiat2[4] >= 3)
                continue;
        }
        else if (((i == 2) && (j == 3)) || ((i == 3) && (j == 2)))
        {
            league.ehtiat2[5] += 1;
            if (league.ehtiat2[5] >= 3)
                continue;
        }
        printf(FRED"TIME %s VS--------->%s\n\n\n", homeTeam.name, awayTeam.name);
    }
}
/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
void startWeekIthGames()
{
    int index;
    int index1;
    int index2;
    int index3;
    for (int is = 5; is < 8; is++)
    {
        for (index = 0; index < playersCounter; index++)
        {
            if (strcmp(league.teams[0].teamPlayers[is].name, players[index].name) == 0)
            {
                break;
            }
        }

        league.teams[0].teamPlayers[is].attackPower = defalt(players[index]);
        league.teams[0].teamPlayers[is].defensePower = defalt2(players[index]);
        teams[0].teamPlayers[is].attackPower = defalt(players[index]);
        teams[0].teamPlayers[is].defensePower = defalt2(players[index]);
    }
    ////////////////////////////////////////////////////////////////////////////////////////
    for (int t = 13; t < 16; t++)
    {
        int t21 = t % 8;
        for (index1 = 0; index1 < playersCounter; index1++)
        {
            if (strcmp(league.teams[1].teamPlayers[t21].name, players[index1].name) == 0)
            {
                break;
            }
        }
        league.teams[1].teamPlayers[t21].attackPower = defalt(players[index1]);
        league.teams[1].teamPlayers[t21].defensePower = defalt2(players[index1]);
        teams[1].teamPlayers[t21].attackPower = defalt(players[index1]);
        teams[1].teamPlayers[t21].defensePower = defalt2(players[index1]);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////

    for (int t2 = 21; t2 < 24; t2++)
    {
        int t3 = t2 % 16;
        for (index2 = 0; index2 < playersCounter; index2++)
        {
            if (strcmp(league.teams[2].teamPlayers[t3].name, players[index2].name) == 0)
            {
                break;
            }
        }
        league.teams[2].teamPlayers[t3].attackPower = defalt(players[index2]);
        league.teams[2].teamPlayers[t3].defensePower = defalt2(players[index2]);
        teams[2].teamPlayers[t3].attackPower = defalt(players[index2]);
        teams[2].teamPlayers[t3].defensePower = defalt2(players[index2]);
    }
    ////////////////////////////////////////////////////////////////////////////
    for (int z = 29; z < 32; z++)
    {
        int z1 = z % 24;
        for (index3 = 0; index3 < playersCounter; index3++)
        {
            if (strcmp(league.teams[3].teamPlayers[z1].name, players[index3].name) == 0)
            {
                break;
            }
        }

        league.teams[3].teamPlayers[z1].attackPower = defalt(players[index3]);
        league.teams[3].teamPlayers[z1].defensePower = defalt2(players[index3]);
        teams[3].teamPlayers[z1].attackPower = defalt(players[index3]);
        teams[3].teamPlayers[z1].defensePower = defalt2(players[index3]);
    }
    ////////////////////////////////////////////
    ////////////////////////////////////////////
    ////////////////////////////////////////////
    int i;
    for (i = 0; i < 4; i++)
    {
        struct Team homeTeam = league.teams[i];
        struct Team awayTeam = league.teamsOpponents[i][IthWeek];
        int j;
        for (j = 0; j < 4; j++)
        {
            if (strcmp(league.teams[j].name, awayTeam.name) == 0)
                break;
        }
        //////////////////////////////////////////////////////////////////////
        if (awayTeam.teamId == -1)
            continue;
        else if (i == j)
            continue;
        else if (((i == 0) && (j == 3)) || ((i == 3) && (j == 0)))
        {
            league.ehtiat[0] += 1;
            if (league.ehtiat[0] >= 3)
                continue;
        }
        else if (((i == 0) && (j == 2)) || ((i == 2) && (j == 0)))
        {
            league.ehtiat[1] += 1;
            if (league.ehtiat[1] >= 3)
                continue;
        }
        else if (((i == 0) && (j == 1)) || ((i == 1) && (j == 0)))
        {
            league.ehtiat[2] += 1;
            if (league.ehtiat[2] >= 3)
                continue;
        }
        else if (((i == 1) && (j == 3)) || ((i == 3) && (j == 1)))
        {
            league.ehtiat[3] += 1;
            if (league.ehtiat[3] >= 3)
                continue;
        }
        else if (((i == 1) && (j == 2)) || ((i == 2) && (j == 1)))
        {
            league.ehtiat[4] += 1;
            if (league.ehtiat[4] >= 3)
                continue;
        }
        else if (((i == 2) && (j == 3)) || ((i == 3) && (j == 2)))
        {
            league.ehtiat[5] += 1;
            if (league.ehtiat[5] >= 3)
                continue;
        }
        
        ///////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////
        int goalHome = ((getTeamAttack(homeTeam)) - (getTeamDefense(awayTeam))) / 100;
        int goalAway = ((getTeamAttack(awayTeam)) - (getTeamDefense(homeTeam))) / 100;

        if (goalAway < 0)
            goalAway = 0;
        if (goalHome < 0)
            goalHome = 0;

        league.teams[i].gf += goalHome;
        league.teams[i].ga += goalAway;
        league.teams[i].gd += goalHome - goalAway;

        league.teams[j].gf += goalAway;
        league.teams[j].ga += goalHome;
        league.teams[j].gd += goalAway - goalHome;

        int homeTeamIndexInGlobalArray = doesTeamExist(league.teams[i].name); /// index mide
        int awayTeamIndexInGlobalArray = doesTeamExist(league.teams[j].name); /// index mide
        if (goalAway > goalHome)
        {
            league.teams[j].pts += 3;
            teams[awayTeamIndexInGlobalArray].budget += 5;
            teams[homeTeamIndexInGlobalArray].budget += 1;
            league.teams[j].wins++;
            league.teams[i].loses++;
        }
        else if (goalAway < goalHome)
        {
            league.teams[i].pts += 3;
            teams[awayTeamIndexInGlobalArray].budget += 1;
            teams[homeTeamIndexInGlobalArray].budget += 5;
            league.teams[i].wins++;
            league.teams[j].loses++;
        }
        else
        {
            league.teams[i].pts += 1;
            league.teams[j].pts += 1;

            teams[awayTeamIndexInGlobalArray].budget += 3;
            teams[homeTeamIndexInGlobalArray].budget += 3;

            league.teams[i].draws++;
            league.teams[j].draws++;
        }
        int k;
        for (k = 0; k < 5; k++)
        {
            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////'
            league.teams[i].teamPlayers[k].attackPower -= 5;
            if (league.teams[i].teamPlayers[k].attackPower < 0)
                league.teams[i].teamPlayers[k].attackPower = 0;

            league.teams[i].teamPlayers[k].defensePower -= 5;
            if (league.teams[i].teamPlayers[k].defensePower < 0)
                league.teams[i].teamPlayers[k].defensePower = 0;

            league.teams[j].teamPlayers[k].attackPower -= 5;
            if (league.teams[j].teamPlayers[k].attackPower < 0)
                league.teams[j].teamPlayers[k].attackPower = 0;

            league.teams[j].teamPlayers[k].defensePower -= 5;
            if (league.teams[j].teamPlayers[k].defensePower < 0)
                league.teams[j].teamPlayers[k].defensePower = 0;
            ///////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////
            teams[awayTeamIndexInGlobalArray].teamPlayers[k].attackPower -= 5;
            if (teams[awayTeamIndexInGlobalArray].teamPlayers[k].attackPower < 0)
                teams[awayTeamIndexInGlobalArray].teamPlayers[k].attackPower = 0;
            teams[homeTeamIndexInGlobalArray].teamPlayers[k].defensePower -= 5;
            if (teams[homeTeamIndexInGlobalArray].teamPlayers[k].defensePower < 0)
                teams[homeTeamIndexInGlobalArray].teamPlayers[k].defensePower = 0;
            /////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////
            teams[homeTeamIndexInGlobalArray].teamPlayers[k].attackPower -= 5;
            if (teams[homeTeamIndexInGlobalArray].teamPlayers[k].attackPower < 0)
                teams[homeTeamIndexInGlobalArray].teamPlayers[k].attackPower = 0;
            teams[awayTeamIndexInGlobalArray].teamPlayers[k].defensePower -= 5;
            if (teams[awayTeamIndexInGlobalArray].teamPlayers[k].defensePower < 0)
                teams[awayTeamIndexInGlobalArray].teamPlayers[k].defensePower = 0;
        }
    }
    printf(FLIMOIE"week %d games played!\n", IthWeek + 1);

    IthWeek++;
    if ((IthWeek == 3) || (IthWeek == 6))
    {
        int indexx;
        int indexx1;
        int indexx2;
        int indexx3;
        for (int is = 0; is < 8; is++)
        {
            for (indexx = 0; indexx < playersCounter; indexx++)
            {
                if (strcmp(league.teams[0].teamPlayers[is].name, players[indexx].name) == 0)
                {
                    break;
                }
            }
            league.teams[0].teamPlayers[is].attackPower = defalt(players[indexx]);
            league.teams[0].teamPlayers[is].defensePower = defalt2(players[indexx]);
            teams[0].teamPlayers[is].attackPower = defalt(players[indexx]);
            teams[0].teamPlayers[is].defensePower = defalt2(players[indexx]);
        }
        ////////////////////////////////////////////////////////////////////////////////////////
        for (int t = 8; t < 16; t++)
        {
            int t21 = t % 8;
            for (indexx1 = 0; indexx1 < playersCounter; indexx1++)
            {
                if (strcmp(league.teams[1].teamPlayers[t21].name, players[indexx1].name) == 0)
                {
                    break;
                }
            }
            league.teams[1].teamPlayers[t21].attackPower = defalt(players[indexx1]);
            league.teams[1].teamPlayers[t21].defensePower = defalt2(players[indexx1]);
            teams[1].teamPlayers[t21].attackPower = defalt(players[indexx1]);
            teams[1].teamPlayers[t21].defensePower = defalt2(players[indexx1]);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////

        for (int t2 = 16; t2 < 24; t2++)
        {
            int t3 = t2 % 16;
            for (indexx2 = 0; indexx2 < playersCounter; indexx2++)
            {
                if (strcmp(league.teams[2].teamPlayers[t3].name, players[indexx2].name) == 0)
                {
                    break;
                }
            }
            league.teams[2].teamPlayers[t3].attackPower = defalt(players[indexx2]);
            league.teams[2].teamPlayers[t3].defensePower = defalt2(players[indexx2]);
            teams[2].teamPlayers[t3].attackPower = defalt(players[indexx2]);
            teams[2].teamPlayers[t3].defensePower = defalt2(players[indexx2]);
        }
        ////////////////////////////////////////////////////////////////////////////
        for (int z = 24; z < 32; z++)
        {
            int z1 = z % 24;
            for (indexx3 = 0; indexx3 < playersCounter; indexx3++)
            {
                if (strcmp(league.teams[3].teamPlayers[z1].name, players[indexx3].name) == 0)
                {
                    break;
                }
            }

            league.teams[3].teamPlayers[z1].attackPower = defalt(players[indexx3]);
            league.teams[3].teamPlayers[z1].defensePower = defalt2(players[indexx3]);
            teams[3].teamPlayers[z1].attackPower = defalt(players[indexx3]);
            teams[3].teamPlayers[z1].defensePower = defalt2(players[indexx3]);
        }
        doesTransferWindowOpened = 0;
    }
    writeToFiles();
}

int getTeamAttack(struct Team team)
{
    int sum = 0;
    int i;
    for (i = 0; i < team.teamPlayerCounter; i++)
        sum += team.teamPlayers[i].attackPower;
    return sum;
}

int getTeamDefense(struct Team team)
{
    int sum1 = 0;
    int i;
    for (i = 0; i < team.teamPlayerCounter; i++)
        sum1 += team.teamPlayers[i].defensePower;

    return sum1;
}

void showStandings()
{
    printf(FCYAN"%-20s%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n", "name", "week", "win", "pts", "draws", "lose", "gf(zade)", "ga(khorde)", "gd(ekhtelaf)");
    sortTeams(league.teams);
    for (int i = 0; i < 4; i++)
    {
        printf(FBLUE"%-20s%-12d%-12d%-12d%-12d%-12d%-12d%-12d%-12d\n",
               league.teams[i].name, IthWeek, league.teams[i].wins, league.teams[i].pts, league.teams[i].draws,
               league.teams[i].loses, league.teams[i].gf, league.teams[i].ga, league.teams[i].gd);
    }
}

void leagueStanding()
{
    printf(FLIMOIE"%-20s%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s\n", "name", "week", "win", "pts", "draws", "lose", "gf(zade)", "ga(khorde)", "gd(ekhtelaf)");
    
    struct Team teams[4];
    for(int i=0; i < 4; i++)
    {
        teams[i] = league.teams[i];
    }

    sortTeams(teams);

    for (int i = 0; i < 4; i++)
    {
        printf(FYELLOW"%-20s%-12d%-12d%-12d%-12d%-12d%-12d%-12d%-12d\n",
               teams[i].name, IthWeek, teams[i].wins, teams[i].pts, teams[i].draws,
               teams[i].loses, teams[i].gf, teams[i].ga, teams[i].gd);
    }
}

void openCloseTransferWindows()
{
    if ((IthWeek==3)||(IthWeek==6))
    {
         
    
    
    if (doesTransferWindowOpened == 0)
    {
        printf(FRED"transfer window is now open!\n");
        doesTransferWindowOpened = 1;
    }
    else{
        printf(FRED"transfer window is now closed!\n");
        doesTransferWindowOpened = 0;
      }
    }
    else
      printf(FRED"\n\nnot start yet\n\n");

}

void swapLeagueTeams(struct Team *teams, int i, int j)
{
    struct Team temp = teams[i];
    teams[i] = teams[j];
    teams[j] = temp;
}

void sortTeams(struct Team *teams)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = i + 1; j < 4; j++)
        {
            if (teams[i].pts < teams[j].pts)
            {
                swapLeagueTeams(teams, i, j);
            }
            else if (teams[i].pts == teams[j].pts)
            {
                if (teams[i].gd < teams[j].gd)
                {
                    swapLeagueTeams(teams, i, j);
                }
                else if (teams[i].gd == teams[j].gd)
                {
                    if (teams[i].gf < teams[j].gf)
                    {
                        swapLeagueTeams(teams, i, j);
                    }
                    else if (teams[i].gf == teams[j].gf && teams[i].ga > teams[j].ga)
                    {
                        swapLeagueTeams(teams, i, j);
                    }
                }
            }
        }
    }
}

void announceChampion()
{
    if (doesLeagueStarted)
    {
        int i;
        for (i = 0; i < 6; i++)
            startWeekIthGames();

        showStandings();
        paian();
    }

    else
        printf(FRED"leagua does not started!\n");
}

void sortPlayers()
{
    int i;
    for (i = 0; i < playersCounter; i++)
    {
        int j;
        for (j = 0; j < playersCounter - 1; j++)
        {
            if (players[j].value < players[j + 1].value)
            {
                struct Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

void buyPlayer(int index)
{
    sortPlayers();
    if ((IthWeek == 1) || (IthWeek == 2) || (IthWeek == 4) || (IthWeek == 5))
    {
        printf(FRED"NEMISHE;BROO\n");
        return;
    }
    int i;
    for (i = 0; i < playersCounter; i++)
    {
        if (strcmp(players[i].teamName, "free agent") == 0)
        {

            printf(FCYAN"No.%d\n", i);
            showPlayer(players[i]);
        }
    }

    int indexPlayer;
    scanf("%d", &indexPlayer);

    if (players[indexPlayer].value <= teams[index].budget)
    {
        strcpy(players[indexPlayer].teamName, teams[index].name);
        teams[index].teamPlayers[teams[index].teamPlayerCounter] = players[indexPlayer];
        teams[index].teamPlayerCounter++;

        teams[index].budget -= players[indexPlayer].value;
    }
    else
        printf(FRED"budget not enought!\n");
}
void sellPlayer(int index)
{
    sortPlayers();
    if ((IthWeek == 1) || (IthWeek == 2) || (IthWeek == 4) || (IthWeek == 5))
    {
        printf(FRED"NEMISHE;BROO\n");
        return;
    }
    int i;
    for (i = 0; i < playersCounter; i++)
    {
        if (strcmp(players[i].teamName, teams[index].name) == 0)
        {
            printf(FCYAN"No.%d\n", i);
            showPlayer(players[i]);
        }
    }

    int indexPlayer;
    scanf("%d", &indexPlayer);

    for (i = 0; i < teams[index].teamPlayerCounter; i++)
        if (teams[index].teamPlayers[i].id == players[indexPlayer].id)
            break;

    teams[index].teamPlayerCounter--;
    teams[index].budget += players[indexPlayer].value;

    strcpy(players[indexPlayer].teamName, "free agent");

    printf(FRED"sucessfully selled!\n");
}

void selectSquad(int index)
{
    if (teams[index].teamPlayerCounter < 5)
    {
        printf(FRED"at least should have 5 player!\n");
        return;
    }

    int i;
    for (i = 0; i < teams[index].teamPlayerCounter; i++)
    {
        printf(FYELLOW"No.%d\n", i);
        showPlayer(teams[index].teamPlayers[i]);
    }

    int indexPlayers[5];
    int j = 0;
    for (i = 0; i < 5; i++)
    {
        scanf("%d", &indexPlayers[i]);

        if (indexPlayers[i] < 0 || indexPlayers[i] > teams[index].teamPlayerCounter)
        {
            printf(FRED"invalid index!\n");
            i--;
        }
        else
        {
            struct Player p = teams[index].teamPlayers[j];
            teams[index].teamPlayers[j] = teams[index].teamPlayers[indexPlayers[i]];
            teams[index].teamPlayers[indexPlayers[i]] = p;
            //////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////
            struct Player p1 = league.teams[index].teamPlayers[j];
            league.teams[index].teamPlayers[j] = league.teams[index].teamPlayers[indexPlayers[i]];
            league.teams[index].teamPlayers[indexPlayers[i]] = p1;

            j++;
        }
    }

    printf(FRED"successfully submited!\n");
    teams[index].isReadyToPlay = 1;
    /*for (int x = 0; x <32; x++)
	{
		
	}*/
}

///////////////////////////////////////////////
//////////////////////////////////////////////
/////////////////////////////////////////////
////////////////////////////////////////////

void showFixtures(int index)
{
    if (doesLeagueStarted)
    {
        struct Team teams[4];
        for (int i = 0; i < 4; i++)
        {
            teams[i] = league.teams[i];
        }
        
        createFixtures2();
        for (int s = 0; s < 6; s++)
        {
            futureGame(s);
        }
        for (int z1 = 0; z1 < 6; z1++)
        {
            league.ehtiat2[z1] = 0;
        }
        printf("\n\n\n");
        leagueStanding();
        printf("\n\n\n");
    }

    else
        printf(FRED"\n\n not Start\n\n");
}
//////////////////////////////////////////
/////////////////////////////////////////
////////////////////////////////////////
void showNextOpponent(int index)
{
    int indexOfTeamInLeague;
    for (indexOfTeamInLeague = 0; indexOfTeamInLeague < 4; indexOfTeamInLeague++)
    {
        if (strcmp(league.teams[indexOfTeamInLeague].name, teams[index].name) == 0)
            break;
    }

    showTeam(league.teamsOpponents[indexOfTeamInLeague][IthWeek]);
    int m;
    int m2;
    m = getTeamAttack(league.teamsOpponents[indexOfTeamInLeague][IthWeek]);
    m2 = getTeamDefense(league.teamsOpponents[indexOfTeamInLeague][IthWeek]);
    printf("\nopponent attack is %d\n", m);
    printf("opponent defens is %d\n\n\n", m2);
}
void updatePassword(int index)
{
    char newPassword[30];
    printf(FORANGE"enter new password:\t");
    scanf("%s", &newPassword);

    strcpy(teamManagers[index].password, newPassword);

    printf("successfully updated!\n");
}

void readFromFiles()
{
    FILE *file;
    if (file = fopen("league.dat", "rb"))
    {
        fread(&league, 1, sizeof(struct League), file);
    }
    fclose(file);

    if (file = fopen("teams.dat", "rb"))
    {
        while (fread(&teams[teamsCounter], sizeof(struct Team), 1, file))
        {
            teamsCounter++;
        }
    }
    fclose(file);

    if (file = fopen("teamManagers.dat", "rb"))
    {
        int i = 0;
        while (fread(&teamManagers[i], sizeof(struct TeamManager), 1, file))
        {
            i++;
        }
    }
    fclose(file);

    if (file = fopen("players.dat", "rb"))
    {
        struct Player p;
        int i = 0;
        while (fread(&players[i], sizeof(struct Player), 1, file))
        {
            i++;
        }
        playersCounter = i;
    }
    fclose(file);
    if (file = fopen("leagueOtherInfo.dat", "rb"))
    {
        fread(&leagueOtherInfo, 1, sizeof(struct LeagueOtherInfo), file);
    }
    IthWeek = leagueOtherInfo.IthWeek;
    doesLeagueStarted = leagueOtherInfo.doesLeagueStarted;
    doesTransferWindowOpened = leagueOtherInfo.doesTransferWindowOpened;

    fclose(file);
}

void writeToFiles()
{
    /////https://sariasan.com/c-2/files-management/
    FILE *binaryFile = fopen("league.dat", "wb");
    fwrite(&league, sizeof(struct League), 1, binaryFile);
    fclose(binaryFile);

    binaryFile = fopen("teams.dat", "wb");
    int i;
    for (i = 0; i < teamsCounter; i++)
        fwrite(&teams[i], sizeof(struct Team), 1, binaryFile);
    fclose(binaryFile);

    binaryFile = fopen("teamManagers.dat", "wb");
    for (i = 0; i < teamsCounter; i++)
        fwrite(&teamManagers[i], sizeof(struct TeamManager), 1, binaryFile);
    fclose(binaryFile);

    binaryFile = fopen("players.dat", "wb");
    for (i = 0; i < playersCounter; i++)
        fwrite(&players[i], sizeof(struct Player), 1, binaryFile);
    fclose(binaryFile);
    binaryFile = fopen("leagueOtherInfo.dat", "wb");
    fwrite(&leagueOtherInfo, sizeof(struct LeagueOtherInfo), 1, binaryFile);
    fclose(binaryFile);
}
