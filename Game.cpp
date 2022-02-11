// header files
#include <iostream>
#include <tuple>
#include <limits>
#include <cctype>


// includes windows.h if device using windows other than that includes unistd.h for linux and Mac-os
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// for speed replaces every endl with '\n' which is faster for output
#define endl '\n'

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


class player{
    private:
        int hp,age;
        double high_school_result;
        double GPA;
        string name, gender;
    public:
        player(int h, int a, double r, string n, string g, double gp){
            hp = h;
            age = a;
            high_school_result = r;
            name = n;
            gender = g;
            GPA = gp;
        }
        tuple<int,int,double,string> get_info(){
            tuple<int,int,double,string> t;
            t = make_tuple(hp,age,high_school_result,name);
            return t;
        }
        int get_hp(){
            return hp;
        }
        string get_name(){
            return name;
        }
        int get_age(){
            return age;
        }
        double get_GPA(){
            return GPA;
        }
        void set_hp(int h){
            hp = h;
        }
        void set_GPA(double gp){
            GPA = gp;
        }

};


class game{
    public:
        void start(){
            cout << "Welcome to FCAI game" << endl;
            string s;
            pause();
            getline(cin,s);
            system ("CLS");
            main_menu();
        }
        void main_menu(){
            int choice;
            cout << "1 - Start a new game" << endl;
            cout << "2 - Load last saved game" << endl;
            cout << "3 - Credits" << endl;
            cout << "4 - Exit" << endl;

            cout << endl << endl;
            cout << "Please choose your option: ";
            cin >> choice;


            switch (choice)
            {
            case 1:
                system ("CLS");
                new_game();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                exit(0);
                break;
            
            default:
                system ("CLS");
                cout << "Please enter a valid option next time";
                pause();
                system ("CLS");
                main_menu();
                break;
            }
        }
        void new_game(){
            /*
            string s;
            s = "Welcome to FCAI game.";
            write(s, 500);
            s = "In this game you will take the role as a student who have just finished high-school.";
            write(s, 500);
            s = "And.....";
            write(s, 1000);
            s = "Yes you guessed it right!! he will join FCAI - Cairo university.";
            write(s, 2000);
            */
            
            pause();
            system ("CLS");
            
            player player = register_player();
            level_1(player);
            

        }
        void write(string s, int t, int e = 1, int mode = 0){
            int color;
            if(mode){
                color = 10;
            }else{
                color = 15;
            }
            SetConsoleTextAttribute(hConsole, color);
            for(int i = 0, q = s.size(); i < q; i++)cout << s[i], Sleep(100);
            SetConsoleTextAttribute(hConsole, 15);

            for(int i = 0; i < e; i++)cout << endl;
            
            Sleep(t);
        }
        void pause(){
            string s;
            cout << endl << endl;
            cout << "Please enter any key to continue....." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,s);
        }

        player register_player(){
            string name,gender;
            int age,choice = 3;
            double high_school_result;

            // Register name
            do{
                cout << "Now please enter your name: ", getline(cin,name);
            }while(name == "");
            

            // Register gender
            do
            {
                try{
                    cout << "Please choose your gender:" << endl << "1 - Male" << endl << "2 - Female" << endl;
                    cin >> choice;
                    if(!cin || (choice != 1 && choice != 2)){
                        throw 1;
                    }
                    system ("CLS");
                }catch(int n){
                    system("CLS");
                    cout << "Please enter a valid choice" << endl;
                    pause();
                    system("CLS");
                }
            }
            while(choice != 1 && choice != 2);

            switch(choice){
                case 1:
                    gender = "male";
                    break;
                case 2:
                    gender = "female";
                    break;
            }

            // Register age
            bool f = false;
            do{
                try{
                    cout << "Please enter your age: ";
                    cin >> age;
                    f = true;
                    if(!cin){
                        throw 1;
                    }
                } 
                catch(int n){
                    f = false;
                    system("CLS");
                    cout << "Please enter a valid age" << endl;
                    pause();
                    system("CLS");
                }  
            }while(f == false);
            

            // Register high_school_result
            system("CLS");
            f = false;
            do{
                try{
                    cout << "Please enter your high-school result in percentage: ";
                    cin >> high_school_result;
                    f = true;
                    if(!cin || high_school_result > 100.0 || high_school_result <= 0.0){
                        throw 1;
                    }
                } 
                catch(int n){
                    f = false;
                    system("CLS");
                    cout << "Please enter a valid high-school result between (1\% - 100\%)" << endl;
                    pause();
                    system("CLS");
                }  
            }while(f == false);
            player player_obj(100, age, high_school_result, name, gender, 0.0);
            return player_obj;
        }
        void show_health_name_GPA(int hp, string name, double GPA){
            //show health bar
            int hp_points = (hp + 9)/10;
            int color;
            if(hp_points >= 9){
                color = 10;
            }else if(hp_points > 5){
                color = 14;
            }else{
                color = 12;
            }
            
            cout << "HEALTH: ";
            cout << "|";
            SetConsoleTextAttribute(hConsole, color);
            for(int i = 0; i < hp_points; i++){ 
                cout << '|';
            }
            SetConsoleTextAttribute(hConsole, 15);
            for(int i = 0; i < 10-hp_points; i++){
                cout << ' ';
            }
            cout << "|";
            SetConsoleTextAttribute(hConsole, color);
            printf("(%d%)", hp);
            SetConsoleTextAttribute(hConsole, 15);


            //show player name
            cout << "\t\t\t";
            cout << "NAME: " << name;

            //show player age
            cout << "\t\t\t";
            if(GPA >= 3.5){
                color = 10;
            }else if(GPA >= 3.0){
                color = 14;
            }else{
                color = 12;
            }
            cout << "GPA: ";
            SetConsoleTextAttribute(hConsole, color);
            cout << GPA;
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\v\v\v\v\v";
        }
        void update_screen(player& player){
            system ("CLS");
            show_health_name_GPA(player.get_hp(), player.get_name(), player.get_GPA());
        }

        void level_1(player& player){
            update_screen(player);
            string s;
            /*
            s = "Welcome to your first day in FCAI, before you begin as a student who attend lectures (I hope you do so :) ), we want to explain things for you.";
            write(s, 500);
            s = "First you will notice your HEALTH bar at the top-left corner of the screen it indicates your current health and if it dropped to 0% you die x_x (just kidding you will continue from your most-recent saved progress).";
            write(s, 500);
            s = "Second your GPA (I know it is 0 right now but we hope you will make it better as you progress in the game <3 ).";
            write(s, 500);
            s = "That's it, you are now officially a junior student at FCAI (you should be proud of yourself :) ).";
            write(s, 500);
            */
            pause();

            update_screen(player);
            string group;
            s = "Because of the Covid-19 Pandemic (as you know of course) the students are divided into two groups (A and B), so now you must register for one of the two groups.";
            write(s, 500);
            do{
                try{
                    update_screen(player);
                    s = "Please, choose one of the groups (A or B): ";
                    write(s, 500);
                    cin >> group;
                    if(!cin || group != "A" && group != "a" && group != "b" && group != "B"){
                        throw 1;
                    }
                }catch(int n){
                    system("CLS");
                    cout << "Please enter a valid choice" << endl;
                    pause();
                    system("CLS");
                }
            }while(group != "A" && group != "a" && group != "b" && group != "B");
            
            s = "So, you have chosen group ";
            write(s, 0, 0);
            cout << (char)toupper(group[0]) << ' ';
            if(tolower(group[0]) == 'a'){
                s = "Wow, what a brilliant idea you and 99.999% of other students choose that group (I don't know why by the way).";
            }else{
                s = "I hope you enjoy your life with your other 5 colleagues at that group.";
            }
            write(s, 500, 1, 1);
            pause();
        }
};


int main(){
    system ("CLS");
    game g;
    g.start();
    


    return 0;
}