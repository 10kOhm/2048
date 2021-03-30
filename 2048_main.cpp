#include <iostream>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <thread>

using namespace std;

int board[4][4];
int dirline[] = {1, 0, -1, 0};
int dircolumn[] = {0, 1, 0, -1};

pair<int, int> generateunoccupiedpos() {
    int occupied = 1, line , column;
    while (occupied){
        line = rand() % 4;
        column = rand() % 4;
        if (board[line][column] == 0 ){
            occupied = 0;
        }
    }
    return make_pair(line, column);
}

void newpiece(int random = 1){
    
    if (random != 1) {
        random = rand();
    }
    pair<int , int > pos = generateunoccupiedpos();
    if (random % 3 == 0){
        board[pos.first][pos.second] = 4;
    } else {
        board[pos.first][pos.second] = 2;
    }

}

void newGame() {
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            board[i][j] = 0;
        }
    }

    newpiece();
}

void printUI() {
    cout << u8"\033[2J\033[1;1H";
    cout << "_________________________________\n";
    for (int i = 0; i < 4; ++i){
        cout<<"|";
        for (int j = 0; j < 4; ++j){
            if (board[i][j] == 0) {
                cout << setw(4) << "   .   |";
            } else {
                cout << setw(4) << board[i][j] << "   |";
            }
                 
        }
        cout << "\n";
    }
    cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
    cout << "n: New game, w: Up, s: Down, a: Left, d: Right q: Quit\n";
}
bool moveoutcome(int line, int column, int nextline, int nextcolumn){
    if(nextline < 0 || nextcolumn < 0 || nextline >= 4 || nextcolumn >= 4 ||
    board[line][column] != board[nextline][nextcolumn] && board[nextline][nextcolumn] != 0 ){
        return false;
    }
    return true;

}
void move(int direction){
    int startl = 0, startc = 0;
    int stepl = 1, stepc = 1;

    if(direction == 0){
        startl = 3;
        stepl= -1;
    }
    if (direction == 1) {
        startc = 3;
        stepc = -1;
    }
    int movepossible, addpiece = 0;
    do {
        movepossible = 0;
        for (int i = startl; i >= 0 && i < 4; i += stepl){
            for (int j = startc; j >=0 && j < 4; j +=stepc){
                int nextI = i + dirline[direction], nextJ = j + dircolumn[direction];
                if (board[i][j] && moveoutcome(i, j, nextI, nextJ)){
                    board[nextI][nextJ] += board[i][j];
                    board[i][j] = 0;
                    movepossible = addpiece = 1;
                }
            }
        
        }

        printUI();
        this_thread::sleep_for(chrono::milliseconds(30));
    } while (movepossible);

    if (addpiece) {
        newpiece(0);
    }
}

int main()
{
    srand(time(0));
    newGame();
    while(true) {
        printUI();
        char command;
        cin >> command;
        cin.clear();
        cin.ignore(INT_MAX,'\n');

        switch(tolower (command))
        {    
        case 'n' : 
        newGame();
        break;

        case 'w' : 
        move(2);
        break;

        case 's' : 
        move(0);
        break;

        case 'a' : 
        move(3);
        break;

        case 'd' : 
        move(1);
        break;

        case 'q': 
        return 0;
        break;

        default : 
        cout << "Incorrect command!";
        
        break;
        }
    }
}