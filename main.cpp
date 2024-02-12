#include <bits/stdc++.h>
using namespace std;

enum gender {WOMEN, MEN};

int main();

#include "vector.cpp"   //use of multifile

template <typename T>   //template class
class VectorStorage
{
public:
    void saveVector(const vector<T>& data, const string& filename)
    {
        ofstream file(filename, ios::binary);           //usage of filestream
        if (file.is_open())
        {
            size_t size = data.size();
            file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
            for (const auto& item : data)
            {
                file.write(reinterpret_cast<const char*>(&item), sizeof(T));
            }
            file.close();
        }
        else
        {
            cout << "Error saving the file" << endl;
        }
    }
    vector<T> loadVector(const string& filename)
    {
        vector<T> data;
        ifstream file(filename, ios::binary);
        if (file.is_open())
        {
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
            data.reserve(size);
            for (size_t i = 0; i < size; ++i)
            {
                T item;
                file.read(reinterpret_cast<char*>(&item), sizeof(T));
                data.push_back(item);
            }
            file.close();
        }
        else
        {
            cout << "Error Unable reading file" << endl;
        }
        return data;
    }
};

class Match
{
public:
    int score;
    Match() : score(0) {}
    Match(int initial_score) : score(initial_score) {}

    Match operator+(const Match& other) const
    {
        Match result;
        result.score = this->score + other.score;       //operator overloading
        return result;
    }
};

class Team{
protected:                                            //abstract class:;
    int team_num;
    char team_name[50];
    char team_pass[50];
public:
    Team() {}
    Team(const char str[], const char pstr[], int si)       //constructor
    {
        team_num = si;
        strcpy(team_name, str);
        strcpy(team_pass, pstr);
    }

    virtual void setdata() = 0;                            //virtual function

};

class Female_team : public Team                             //inheritance
{
private:
    char player_name1[50], player_name2[50];
    int batch_num;

public:
    Female_team() {}
    Female_team(int si, const char tm[], const char pas[], const char ftm1[], const char ftm2[], int batch): Team(tm, pas, si)
    {
        strcpy(player_name1, ftm1);
        strcpy(player_name2, ftm2);
        batch_num = batch;
    }

    void setdata() override
    {
        cout << endl << "**Team Info**" << endl;
        cout << "Team name: " << team_name << endl;
        cout << "Team number: " << team_num << endl;
        cout << "First Player name: " << player_name1 << endl;
        cout << "Second Player name: " << player_name2 << endl;
        cout << "Batch number: " << batch_num << endl << endl;
    }
};

class Male_team : public Team
{
private:
    char player_name1[50], player_name2[50];
    int batch_num;
public:
    Male_team() {}
    Male_team(int si, const char tim[], const char pas[], const char mtm1[], const char mtm2[], int bach): Team(tim, pas, si)
    {
        strcpy(player_name1, mtm1);
        strcpy(player_name2, mtm2);
        batch_num = bach;
    }

    void setdata() override
    {
        cout << endl << "**Team Info**" << endl;
        cout << "Team name: " << team_name << endl;
        cout << "Team number: " << team_num << endl;
        cout << "First Player name: " << player_name1 << endl;
        cout << "Second Player name: " << player_name2 << endl;
        cout << "Batch number: " << batch_num << endl << endl;
    }
};

class Tournament : public Male_team, public Female_team         //multiple inheritance
{
public:

    void register_info()
    {
        int gen;
        cout << "First enter your gender(0 for Women, 1 for Men): ";
        cin >> gen;
        cout << endl;

        VectorStorage<TempforFile> vectorStorage;
        vector<TempforFile> myClassVector;                  //vector usage

        if (gen == WOMEN)
            myClassVector = vectorStorage.loadVector("female_team.dat");
        else
            myClassVector = vectorStorage.loadVector("male_team.dat");
        if (myClassVector.size() >= 32)
        {
            cout << "Maximum number of teams already registered (32 teams)." << endl << endl;
            main();
        }

        char tname[50], passname[50], pname1[50], pname2[50];
        int bnum, tnum;

        cout << "Enter team name: ";
        cin.ignore();
        cin.getline(tname, sizeof(tname));
        cout << "Enter team number: ";
        cin >> tnum;
        cout << "Enter team password: ";
        cin.ignore();
        cin.getline(passname, sizeof(passname));
        cout << "Enter first player name: ";
        cin.getline(pname1, sizeof(pname1));
        cout << "Enter second player name: ";
        cin.getline(pname2, sizeof(pname2));
        cout << "Enter batch number: ";
        cin >> bnum;

        TempforFile obj;
        obj.timnum = tnum;
        strcpy(obj.timname, tname);
        strcpy(obj.timpas, passname);
        obj.timscore = 0;
        strcpy(obj.playname1, pname1);
        strcpy(obj.playname2, pname2);
        obj.bchnum = bnum;
        obj.stat = 0;

        if(gen == WOMEN)
        {
            Female_team f1(tnum, tname, passname, pname1, pname2, bnum);

            Team* baseptr;
            baseptr = &f1;
            baseptr -> setdata();

            myClassVector.push_back(obj);

            vectorStorage.saveVector(myClassVector, "female_team.dat");
        }
        else
        {
            Male_team M1(tnum, tname, passname, pname1, pname2, bnum);

            Team* baseptr;
            baseptr = &M1;
            baseptr -> setdata();

            myClassVector.push_back(obj);

            vectorStorage.saveVector(myClassVector, "male_team.dat");

        }
        cout << "Registration Successful!!!" << endl << endl;
        main();
    }
    void login()
    {
        int gen;
        cout << "First enter your gender(0 for Women, 1 for Men): ";
        cin >> gen;
        cout << endl;

        char teamName[50], passname[50];
        int batchNum;

        cout << "Enter your team name: ";
        cin.ignore();
        cin.getline(teamName, sizeof(teamName));

        cout << "Enter your team password: ";
        cin.getline(passname, sizeof(passname));

        VectorStorage<TempforFile> vectorStorage;
        vector<TempforFile> myClassVector;

        if (gen == WOMEN)
        {
            myClassVector = vectorStorage.loadVector("female_team.dat");
        }
        else
        {
            myClassVector = vectorStorage.loadVector("male_team.dat");
        }

        bool teamFound = false;

        for (const auto& item : myClassVector)
        {
            if (strcmp(item.timname, teamName) == 0 && strcmp(item.timpas, passname) == 0)
            {
                teamFound = true;
                cout << endl << "Login successful!!" << endl << endl;
                cout << "Displaying team info:" << endl;
                cout << "Team name: " << item.timname << endl;
                cout << "Team score: " << item.timscore << endl;
                cout << "First Player name: " << item.playname1 << endl;
                cout << "Second Player name: " << item.playname2 << endl;
                cout << "Batch number: " << item.bchnum << endl;
                break;
            }
        }

        if (!teamFound)
        {
            cout << "Login failed. Team not found." << endl;
        }
        cout << endl;
        main();
    }

};
class Admin
{
private:
    char pass[50];
public:
    void conductMatch(int gen)
    {
        cout << "Enter your password: ";
        cin.ignore();
        cin.getline(pass, sizeof(pass));
        if(strcmp(pass, "381ju51") != 0)
        {
            cout << "You have entered wrong password!!" << endl << endl;
            main();
        }
        VectorStorage<TempforFile> vectorStorage;
        vector<TempforFile> myClassVector;

        if(gen == MEN)
            myClassVector = vectorStorage.loadVector("male_team.dat");
        else
            myClassVector = vectorStorage.loadVector("female_team.dat");

        cout << endl;
        if (myClassVector.size() < 32)
        {
            cout << "Less than 32 teams registered. Match has not officially started." << endl;
            return;
        }
        TempforFile team1, team2;
        bool foundTeam1 = false;
        bool foundTeam2 = false;

        for (auto& team : myClassVector)
        {
            if (team.timscore == 0 && !foundTeam1)
            {
                cout << "First round of match is ongoing. Please enter match results!!" << endl;
                team1 = team;
                foundTeam1 = true;
            }
            else if (team.timscore == 0 && !foundTeam2)
            {
                team2 = team;
                foundTeam2 = true;
            }
            if (foundTeam1 && foundTeam2)
            {
                break;
            }
        }
        for (auto& team : myClassVector)
        {
            if(team.stat == 1 && !foundTeam1)
            {
                cout << "Second round of match is ongoing. Please enter match results!!" << endl;
                team1 = team;
                foundTeam1 = true;
            }
            else if(team.stat == 1 && !foundTeam2)
            {
                team2 = team;
                foundTeam2 = true;
            }
            if (foundTeam1 && foundTeam2)
            {
                break;
            }
        }
        for (auto& team : myClassVector)
        {
            if(team.stat == 2 && !foundTeam1)
            {
                cout << "Quarter final is ongoing. Please enter match results!!" << endl;
                team1 = team;
                foundTeam1 = true;
            }
            else if(team.stat == 2 && !foundTeam2)
            {
                team2 = team;
                foundTeam2 = true;
            }
            if (foundTeam1 && foundTeam2)
            {
                break;
            }
        }
        for (auto& team : myClassVector)
        {
            if(team.stat == 3 && !foundTeam1)
            {
                cout << "Semi final is ongoing. Please enter match results!!" << endl;
                team1 = team;
                foundTeam1 = true;
            }
            else if(team.stat == 3 && !foundTeam2)
            {
                team2 = team;
                foundTeam2 = true;
            }
            if (foundTeam1 && foundTeam2)
            {
                break;
            }
        }
        for (auto& team : myClassVector)
        {
            if(team.stat == 4 && !foundTeam1)
            {
                cout << "Final is ongoing. Please enter match results!!" << endl;
                team1 = team;
                foundTeam1 = true;
            }
            else if(team.stat == 4 && !foundTeam2)
            {
                team2 = team;
                foundTeam2 = true;
            }
            if (foundTeam1 && foundTeam2)
            {
                break;
            }
        }

        if (!foundTeam1 || !foundTeam2)
        {
            cout << "Tournament has ended :<" << endl << endl;
            return;
        }

        int val1, val2, val3, val4;

        cout << endl << "Enter " << team1.timname << " team score info: " << endl;
        cout << "Enter score of " << team1.playname1 << " : ";
        cin >> val1;
        cout << "Enter score of " << team1.playname2 << " : ";
        cin >> val2;
        Match m1(val1), m2(val2), m3, m4;
        m3 = m1 + m2;
        cout << "Team score: " << m3.score << endl;

        cout << endl << "Enter " << team2.timname << " team score info: " << endl;
        cout << "Enter score of " << team2.playname1 << " : ";
        cin >> val3;
        cout << "Enter score of " << team2.playname2 << " : ";
        cin >> val4;
        m1 = Match(val3);
        m2 = Match(val4);
        m4 = m1 + m2;
        cout << "Team score: " << m4.score << endl;

        team1.timscore = m3.score;
        team2.timscore = m4.score;

        for (auto& team : myClassVector)
        {
            if (strcmp(team.timname, team1.timname) == 0)
            {
                team.timscore = team1.timscore;
                if(m3.score > m4.score)
                    team.stat++;
                else
                    team.stat = 0;
            }
            else if (strcmp(team.timname, team2.timname) == 0)
            {
                team.timscore = team2.timscore;
                if(m4.score > m3.score)
                    team.stat++;
                else
                    team.stat = 0;
            }
        }

        if(gen == MEN)
            vectorStorage.saveVector(myClassVector, "male_team.dat");
        else
            vectorStorage.saveVector(myClassVector, "female_team.dat");

        cout << endl << "Team " << (m3.score > m4.score ? team1.timname : team2.timname) << " wins!" << endl;

    }

};
class Audience
{
public:
    void seeScore()
    {
        int team_score, cnt = -1, choice;
        cout << "Do you want to check male team scores or female(0 for women, 1 for men)? Enter: ";
        cin >> choice;
        char name[50];
        cout << "Enter which teams score you want to see: ";
        cin.ignore();
        cin.getline(name, sizeof(name));

        VectorStorage<TempforFile> vectorStorage;
        vector<TempforFile> myClassVector;

        if(choice == MEN)
            myClassVector = vectorStorage.loadVector("male_team.dat");
        else
            myClassVector = vectorStorage.loadVector("female_team.dat");

        for(auto& team : myClassVector)
        {
            if(strcmp(team.timname, name) == 0)
            {
                team_score = team.timscore;
                cnt++;
            }
        }
        if(cnt != -1)
        {
            cout << endl << "Team score of " << name << "team is : " << team_score << endl;
            if(team_score == 0)
                cout << "Match has not started yet. Try again later" << endl;
        }
        else
        {
            cout << "You have entered wrong team name. Kindly enter right name again." << endl;
        }
        cout << endl;
        main();
    }
    void currentTopteams()
    {
        int gen, maxStatus = 0;
        cout << "Do you want to see male team rankings or female?(0 for women, 1 for men)? Enter: ";
        cin >> gen;
        cout << endl << endl;

        VectorStorage<TempforFile> vectorStorage;
        vector<TempforFile> myClassVector;

        if (gen == MEN)
        {
            cout << "Ranking of male team participants: " << endl << endl;
            myClassVector = vectorStorage.loadVector("male_team.dat");
        }
        else
        {
            cout << "Ranking of female team participants: " << endl << endl;
            myClassVector = vectorStorage.loadVector("female_team.dat");
        }

        vector<TempforFile> topTeams;
        for (const auto &team : myClassVector)
        {
            if (team.stat > maxStatus)
            {
                maxStatus = team.stat;
                topTeams.clear();
                topTeams.push_back(team);
            }
            else if (team.stat == maxStatus)
            {
                topTeams.push_back(team);
            }
        }

        if (maxStatus == 4)
        {
            cout << "Final teams are:" << endl;
            for (const auto &team : topTeams)
            {
                cout << team.timname << endl;
            }
        }
        else if (maxStatus == 3)
        {
            cout << "Semi final teams are:" << endl;
            for (const auto &team : topTeams)
            {
                cout << team.timname << endl;
            }
        }
        else if (maxStatus == 2)
        {
            cout << "Quarter final teams are:" << endl;
            for (const auto &team : topTeams)
            {
                cout << team.timname << endl;
            }
        }
        else if (maxStatus == 1)
        {
            cout << "Second round teams are:" << endl;
            for (const auto &team : topTeams)
            {
                cout << team.timname << endl;
            }
        }
        else if (maxStatus > 4)
        {
            cout << "Champion team is: " << topTeams[0].timname << endl;
        }
        else
        {
            cout << "Match has not officially started!!" << endl;
        }
        cout << endl;
        main();
    }
    void tournamentWinner()
    {
        int gen, maxStatus = 0;
        cout << "Do you want to see the male tournament winner or female?(0 for Women, 1 for Men). Enter: ";
        cin >> gen;

        VectorStorage<TempforFile> vectorStorage;
        vector<TempforFile> myClassVector;

        if(gen == MEN)
            myClassVector = vectorStorage.loadVector("male_team.dat");
        else
            myClassVector = vectorStorage.loadVector("female_team.dat");

        for (const auto &team : myClassVector)
        {
            if (team.stat > maxStatus)
            {
                maxStatus = team.stat;
            }
        }

        cout << endl;
        if (maxStatus > 4)
        {
            cout << "Tournament winner: ";
            for (const auto &team : myClassVector)
            {
                if (team.stat == maxStatus)
                {
                    cout << team.timname << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Tournament has not ended yet." << endl;
        }
        cout << endl;
        main();
    }
};
void menu(Tournament& tournament)
{
    cout << "********Welcome Player********" << endl << endl;
    int op;
    cout << "++++++PLAYER MENU++++++" << endl << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Go back" << endl << endl;

    cout << "Enter your choice: ";
    cin >> op;

    switch(op)
    {
    case 1:
        tournament.register_info();
        break;

    case 2:
        tournament.login();
        break;

    case 3:
        main();
        break;

    default:
        return;
    }
//    cout << "Do you want to register or login(0 for register, 1 for login): ";
//    cin >> op;
//    cout << endl;
//    if(op == REGISTER)
//        tournament.register_info(gen);
//    else
//        tournament.login(gen);
}

void menu(Admin& admin)         //function overloading
{
    cout << "**Welcome Admin**" << endl << endl;
    int gen;
    cout << "Will you enter match results for men match or women match?(0 for Women, 1 for Men)  Enter: ";
    cin >> gen;
    admin.conductMatch(gen);
}

void menu(Audience& audience)       //function overloading
{
    cout << "*********Welcome*********" << endl << endl;
    cout << "You can check these three situations of our tournament as a spectator" << endl;
    cout << "1. Checking score of your desired team" << endl;
    cout << "2. Check out our current top teams" << endl;
    cout << "3. Check the champion team of our tournament" << endl;
    cout << "4. Return to main menu" << endl;

    int choice;
    cout << endl << "Enter what you want to check: ";
    cin >> choice;

    switch(choice)
    {
    case 1:
        audience.seeScore();
        break;
    case 2:
        audience.currentTopteams();
        break;
    case 3:
        audience.tournamentWinner();
        break;
    case 4:
        main();
        break;
    default:
        cout << "You have entered wrong choice" << endl;
        main();
    }
}
int main()
{
    cout << "+------------------------------------------------------------------+" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|          Welcome TO Our Badminton Tournament Program             |" << endl;
    cout << "|        ***********************************************           |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                      User Role Menu                              |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| 1.PLAYER                2.ADMIN                     3.AUDIENCE   |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|                    4.Leave the program                           |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "+------------------------------------------------------------------+" << endl;

    Tournament tournament;
    Admin admin;
    Audience audience;

    int choice;
    cout << "Enter your role: ";
    cin >> choice;
    cout << endl;

    switch(choice)
    {

    case 1:
        menu(tournament);
        break;
    case 2:
        menu(admin);
        break;
    case 3:
        menu(audience);
        break;
    case 4:
        cout << "***Thanks for using our program***" << endl;
        return 0;
    default:
        cout << "Please enter right choice" << endl;
    }

    return 0;
}
