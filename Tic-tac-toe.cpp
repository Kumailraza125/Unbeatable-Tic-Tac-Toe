#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node {
public:
char board[9];
char turn;
int score;
std::vector<Node*> children;
};

void printboard(const char board[9]){
    for(int i=0; i<9;i++){
        if( board[i]=='b'){
            cout << ' ';
        }
        else{
             cout<< board[i];
        }
        if((i +1)%3==0){
            cout<< endl;
            if(i ==2 || i==5){
                cout << "-----"<< endl;
                }
        }
        else{
            cout<<"|";
        }
    }
}

char checkWin( const char board[9]){
        if(board[0]==board[1] && board[1]==board[2] && board[0] != 'b'){
           // cout << "winner: " << board[0]  <<endl;
            return board[0];
        }
        else if(board[0]==board[3] && board[3]==board[6] && board[0] != 'b'){
           // cout << "winner: " << board[0]  <<endl;
            return board[0];
        }
        else if(board[3]==board[4] && board[4]==board[5] && board[3] != 'b'){
           // cout << "winner: " << board[3]  <<endl;
            return board[3];
        }
        else if(board[6]==board[7] && board[7]==board[8] && board[6] != 'b'){
            //cout << "winner: " << board[6]  <<endl;
            return board[6];
        }
        else if(board[1]==board[4] && board[4]==board[7] && board[1] != 'b'){
            //cout << "winner: " << board[1]  <<endl;
            return board[1];
        }
        else if(board[2]==board[5] && board[5]==board[8] && board[2] != 'b'){
            //cout << "winner: " << board[2]  <<endl;
            return board[2];
        }
        else if(board[0]==board[4] && board[4]==board[8] && board[0] != 'b'){
           // cout << "winner: " << board[0]  <<endl;
            return board[0];
        }
        else if(board[2]==board[4] && board[4]==board[6] && board[2] != 'b'){
           // cout << "winner: " << board[2]  <<endl;
            return board[2];
        }
         for(int i=0; i<9;i++){
            if(board[i]== 'b'){
             //   cout << "n";
                return 'n';
            }

         }
//cout << "draw";
return 'd';
}

void generateChildren(Node *node){
    node->children.clear();
    if (checkWin(node->board) != 'n'){
        return;
    }
    for(int i=0; i<9;i++){
        if(node->board[i] == 'b'){
            Node* child = new Node;

        for(int j=0; j<9; j++){
            child->board[j] = node->board[j];
        }

        child->board[i] = node->turn;

        if(node->turn == 'x'){
            child->turn ='o';
        }
        else{
            child->turn ='x';
        }
        child->score =0;
        node->children.push_back(child);

        }
    }
}

int minimax(Node *node){
    char result = checkWin(node->board);

    if(result == 'o'){
        return +1;
    }
    if(result == 'x'){
        return -1;
    }
    if(result =='d'){
        return 0;
    }

    
    generateChildren(node);
    int bestscore;

    if (node->turn == 'o'){
        bestscore = -100;
        for(int i =0; i< node->children.size(); i++){
            Node* child = node->children[i];
            int score = minimax(child);
            if(score >bestscore){
                bestscore = score;
            }
        }

    }

    if(node->turn == 'x'){
        bestscore = 100;
        for(int i =0; i< node->children.size(); i++){
            Node* child = node->children[i];
            int score = minimax(child);
            if(score < bestscore){
                bestscore = score;
            }
        }
    }

    return bestscore;
}

Node* bestmove(Node *node){
    generateChildren(node);
    int bestscore = -100;
    vector<Node*> bestmoves;

    for(int i=0; i< node->children.size(); i++){
        Node* child = node->children[i];
        int score = minimax(child);

        if( score > bestscore){
            bestscore = score;
            bestmoves.clear();
            bestmoves.push_back(child);
        }
        else if(score == bestscore){
            bestmoves.push_back(child);
        }
    }
        int r = rand() % bestmoves.size();
return bestmoves[r];

}
int main(){
    srand(time(0));
    Node* current = new Node;
    for(int i =0; i<9; i++){
        current->board[i] = 'b';
    }
    printboard(current->board);
    char current_turn;
    while(true){
    cout << "Whos turn is it?" << endl;
    cout << "'o' for computer, 'x' for user" << endl;
    cin >> current_turn;
    if(current_turn == 'o' || current_turn == 'x'){
        break;
    }
    cout << "Invalid input" << endl;
    }

    if(current_turn == 'o'){
        current-> turn = 'o';
    }
    else{
        current->turn = 'x';
    }
    int user_input;

    while(checkWin(current->board) == 'n'){

        if(current->turn == 'x'){
         while(true){
        cout << "Enter a number between 0-8 " << endl;
        cin >> user_input;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input" << endl;
            continue;
        }

        if( user_input > 8 || user_input<0 || current->board[user_input] != 'b' ){
            cout << "Invalid, please try again" << endl;
            continue;
        }
        break;
        }
        current->board[user_input] = 'x';
        current->turn = 'o';
        }
        else{
            cout << "Computers play: " << endl;
            Node * next = bestmove(current);
            current = next;
            printboard(current->board);

        }
    
    }
   
    char winner = checkWin(current->board);
    if(winner == 'x'){
        cout << "user wins";
    }
    if(winner == 'o'){
        cout << "computer wins";
    }
    if(winner == 'd'){
        cout << "draw";
    }

}
