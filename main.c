#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ClearMatrix(int m[4][4]) {
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      m[i][j] = 0;
    }
  }
}

void PrintMatrix(int m[4][4]) {
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      printf(" %d", m[i][j]);
    }
    printf("\n");
  }
}

void MoveMatrix(int m[4][4], char pos, int *c){
  for(int i = 0; i < 4; i++){
    switch(pos){
      case 'w':
        for(int j = 0; j < 3; j++){ //merge for
          for(int k = j+1; k <= 3 && m[i][j] != 0; k++){
            if(m[j][i] == m[k][i]){
              m[j][i] = 2*m[j][i];
              m[k][i] = 0;
              c--;
            }else if(m[k][i] != 0){break;}
          }
        }
        for(int l = 3; l >= 0; l--){ //move for
          for(int j = 3; j >= 0; j--){
            if(m[j][i] != 0){
              for(int k = j-1; k >= 0; k--){
                if(m[k][i] == 0){
                  m[k][i] = m[j][i];
                  m[j][i] = 0;
                } else{break;}
              }
            }
          }
        }

        break;
      case 'a':
        for(int j = 0; j < 3; j++){ //merge for
          for(int k = j+1; k <= 3 && m[i][j] != 0; k++){
            if(m[i][j] == m[i][k]){
              m[i][j] = 2*m[i][j];
              m[i][k] = 0;
              c--;
            }else if(m[i][k] != 0){break;}
          }
        }
        for(int l = 3; l >= 0; l--){ //move for
          for(int j = 3; j >= 0; j--){
            if(m[i][j] != 0){
              for(int k = j-1; k >= 0; k--){
                if(m[i][k] == 0){
                  m[i][k] = m[i][j];
                  m[i][j] = 0;
                } else{break;}
              }
            }
          }
        }
        break;
      case 's':
        for(int j = 3; j > 0; j--){ //merge for
          for(int k = j-1; k >= 0 && m[i][j] != 0; k--){
            if(m[j][i] == m[k][i]){
              m[j][i] = 2*m[j][i];
              m[k][i] = 0;
              c--;
            }else if(m[k][i] != 0){break;}
          }
        }
        for(int l = 0; l < 4; l++){ //move for
          for(int j = 0; j < 4; j++){
            if(m[j][i] != 0){
              for(int k = j+1; k < 4; k++){
                if(m[k][i] == 0){
                  m[k][i] = m[j][i];
                  m[j][i] = 0;
                } else{break;}
              }
            }
          }
        }
        break;
      case 'd':
        for(int j = 3; j > 0; j--){ //merge for
          for(int k = j-1; k >= 0 && m[i][j] != 0; k--){
            if(m[i][j] == m[i][k]){
              m[i][j] = 2*m[i][j];
              m[i][k] = 0;
              c--;
            }else if(m[i][k] != 0){break;}
          }
        }
        for(int l = 0; l < 4; l++){ //move for
          for(int j = 0; j < 4; j++){
            if(m[i][j] != 0){
              for(int k = j+1; k < 4; k++){
                if(m[i][k] == 0){
                  m[i][k] = m[i][j];
                  m[i][j] = 0;
                } else{break;}
              }
            }
          }
        }
        break;
    }
  }
}

void NewBlock(int m[4][4], int *c){
  int a, b, n = 2;
  if(rand()%10 == 1) n = 4;

  while(1){
    a = rand()%4;
    b = rand()%4;
    if (m[a][b] == 0){
      m[a][b] = n;
      c += 1;
      break;
    }
  }
}

int main(){
  srand(time(0));
  int matrix[4][4];
  int count = 0;
  char pos = 0;
  ClearMatrix(matrix);
  NewBlock(matrix, &count);
  NewBlock( matrix, &count);
  // matrix[0][0] = 2;
  // matrix[0][1] = 2;
  // matrix[0][2] = 8;
  while(1){
    system("clear");
    printf("Count: %d\n", count);
    PrintMatrix(matrix);
    scanf("%s1[^\n]", &pos);
    scanf("%*c");
    MoveMatrix(matrix, pos, &count);
  }
}
