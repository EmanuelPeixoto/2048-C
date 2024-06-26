#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CheckVictory(int m[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (m[i][j] == 2048) {
        return 1;
      }
    }
  }
  return 0;
}

int CheckDefeat(int m[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (m[i][j] == 0) {
        return 0;
      }
      if (i < 3 && m[i][j] == m[i + 1][j]) {
        return 0;
      }
      if (j < 3 && m[i][j] == m[i][j + 1]) {
        return 0;
      }
    }
  }
  return 1;
}

void NewBlock(int m[4][4], int *c) {
  int a, b, n = 2;
  if (rand() % 10 == 1) n = 4;

  while (1) {
    a = rand() % 4;
    b = rand() % 4;
    if (m[a][b] == 0) {
      m[a][b] = n;
      (*c)++;
      break;
    }
  }
}

void ClearMatrix(int m[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m[i][j] = 0;
    }
  }
}

void PrintMatrix(int m[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf(" %4d", m[i][j]);
    }
    printf("\n");
  }
}

void MoveMatrix(int m[4][4], char pos, int *c, int *score) {
  int moved = 0;

  switch (pos) {
    case 'w':
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
          if (m[i][j] != 0) {
            for (int k = i + 1; k < 4; k++) {
              if (m[k][j] != 0) {
                if (m[k][j] == m[i][j]) {
                  m[i][j] *= 2;
                  *score += m[i][j];
                  m[k][j] = 0;
                  (*c)--;
                  moved = 1;
                }
                break;
              }
            }
          }
        }
        for (int i = 0; i < 4; i++) {
          if (m[i][j] == 0) {
            for (int k = i + 1; k < 4; k++) {
              if (m[k][j] != 0) {
                m[i][j] = m[k][j];
                m[k][j] = 0;
                moved = 1;
                break;
              }
            }
          }
        }
      }
      break;
    case 'a':
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (m[i][j] != 0) {
            for (int k = j + 1; k < 4; k++) {
              if (m[i][k] != 0) {
                if (m[i][k] == m[i][j]) {
                  m[i][j] *= 2;
                  *score += m[i][j];
                  m[i][k] = 0;
                  (*c)--;
                  moved = 1;
                }
                break;
              }
            }
          }
        }
        for (int j = 0; j < 4; j++) {
          if (m[i][j] == 0) {
            for (int k = j + 1; k < 4; k++) {
              if (m[i][k] != 0) {
                m[i][j] = m[i][k];
                m[i][k] = 0;
                moved = 1;
                break;
              }
            }
          }
        }
      }
      break;
    case 's':
      for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 0; i--) {
          if (m[i][j] != 0) {
            for (int k = i - 1; k >= 0; k--) {
              if (m[k][j] != 0) {
                if (m[k][j] == m[i][j]) {
                  m[i][j] *= 2;
                  *score += m[i][j];
                  m[k][j] = 0;
                  (*c)--;
                  moved = 1;
                }
                break;
              }
            }
          }
        }
        for (int i = 3; i >= 0; i--) {
          if (m[i][j] == 0) {
            for (int k = i - 1; k >= 0; k--) {
              if (m[k][j] != 0) {
                m[i][j] = m[k][j];
                m[k][j] = 0;
                moved = 1;
                break;
              }
            }
          }
        }
      }
      break;
    case 'd':
      for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
          if (m[i][j] != 0) {
            for (int k = j - 1; k >= 0; k--) {
              if (m[i][k] != 0) {
                if (m[i][k] == m[i][j]) {
                  m[i][j] *= 2;
                  *score += m[i][j];
                  m[i][k] = 0;
                  (*c)--;
                  moved = 1;
                }
                break;
              }
            }
          }
        }
        for (int j = 3; j >= 0; j--) {
          if (m[i][j] == 0) {
            for (int k = j - 1; k >= 0; k--) {
              if (m[i][k] != 0) {
                m[i][j] = m[i][k];
                m[i][k] = 0;
                moved = 1;
                break;
              }
            }
          }
        }
      }
      break;
  }

  if (moved) {
    NewBlock(m, c);
  }
}

int main() {
  srand(time(0));
  int matrix[4][4];
  int count = 0, score = 0;
  char pos = 0;
  ClearMatrix(matrix);
  NewBlock(matrix, &count);
  NewBlock(matrix, &count);

  while (1) {
    printf("\e[1;1H\e[2J"); // clear universal
    printf("Score: %d Count: %d\n", score, count);
    PrintMatrix(matrix);
    if (CheckVictory(matrix)) {
      printf("Congratulations! You reached 2048!\n");
      break;
    }
    if (CheckDefeat(matrix)) {
      printf("Game Over! No more moves possible.\n");
      break;
    }
    scanf(" %c", &pos);
    MoveMatrix(matrix, pos, &count, &score);
  }
  return 0;
}
