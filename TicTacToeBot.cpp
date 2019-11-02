#include<bits/stdc++.h>
using namespace std;

struct Move{
    int row, col;
};
char player = 'x', opponent = 'o';

bool isMovesLeft(char board[3][3]){
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}

int evaluate(char b[3][3]){
    for (int row = 0; row<3; row++){
        if (b[row][0]==b[row][1] && b[row][1]==b[row][2]){
            if (b[row][0]==player)
                return +10;
            else if (b[row][0]==opponent)
                return -10;
        }
    }

    for (int col = 0; col<3; col++){
        if (b[0][col]==b[1][col] && b[1][col]==b[2][col]){
            if (b[0][col]==player)
                return +10;

            else if (b[0][col]==opponent)
                return -10;
        }
    }

    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]){
        if (b[0][0]==player)
            return +10;
        else if (b[0][0]==opponent)
            return -10;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]){
        if (b[0][2]==player)
            return +10;
        else if (b[0][2]==opponent)
            return -10;
    }
    return 0;
}


int minimax(char board[3][3], int depth, bool isMax){
    int score = evaluate(board);
    if (score == 10 or score==-10)
        return score-depth;

    if (isMovesLeft(board)==false)
        return 0-depth;

    if (isMax){
        int best = -1000;

        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                if (board[i][j]=='_'){
                    board[i][j] = player;
                    best = max(best,minimax(board, depth+1,!isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

	else{
        int best = 1000;
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                if(board[i][j]=='_'){
                    board[i][j] = opponent;
                    best = min(best,minimax(board,depth+1,!isMax));
		    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

Move makeMove(char board[3][3]){
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = 0;
    bestMove.col = 0;
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            if(board[i][j]=='_'){
                board[i][j] = player;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '_';
                if(moveVal > bestVal){
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int printboard(char board[3][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++)printf("%c ",board[i][j]);
		printf("\n");
	}
}

int main(){
    char board[3][3] = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };
    int start=0;
    printf("Player: o\nComputer: x\n-----------Beat the bot-----------\n");
    srand(time(NULL));
	if(rand()&1){
		printf("You start first\n");
		while(isMovesLeft(board)){

			printf("Make your move: ");
			int x,y;
			scanf("%d%d",&x,&y);
			while(x<0 or x>3 or y<0 or y>3 or board[x-1][y-1]!='_'){printf("Invalid::re-enter ");scanf("%d%d",&x,&y);}
			board[x-1][y-1]=opponent;

    		printboard(board);
    		printf("\nBot moves\n");
			Move bestMove = makeMove(board);
			board[bestMove.row][bestMove.col]=player;

			printboard(board);

			if(evaluate(board)==10){printf("Bot wins\n");break;}
    		else if(evaluate(board)==-10){printf("You win\n");break;}
    	}
    	if(evaluate(board)==10){printf("Bot wins\n");}
    	else if(evaluate(board)==-10)printf("You win\n");
    	else printf("Tie\n");
    	return 0;
    }
    else{
    	printf("Bot starts first\n");
    	while(isMovesLeft(board)){

			printf("\nBot moves\n");
    		Move bestMove = makeMove(board);
			board[bestMove.row][bestMove.col]=player;

    		printboard(board);

			printf("Make your move: ");
			int x,y;
			scanf("%d%d",&x,&y);
			while(x<0 or x>3 or y<0 or y>3 or board[x-1][y-1]!='_'){printf("Invalid::re-enter ");scanf("%d%d",&x,&y);}
			board[x-1][y-1]=opponent;

			printboard(board);

    		if(evaluate(board)==10){printf("Bot wins\n");break;}
    		else if(evaluate(board)==-10){printf("You win\n");break;}
    	}
    	if(evaluate(board)==10)printf("Bot wins\n");
    	else if(evaluate(board)==-10)printf("You win\n");
    	else printf("Tie\n");
    	return 0;
    }
}
