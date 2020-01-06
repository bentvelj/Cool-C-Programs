/* A simple DFS to find and store the path between two nodes in a two dimensional array */
#include <stdio.h>
#define N 5
#define M 5

// A[i][j] -> A[i * M + j]
int find_path(int n, int m, int A[], int i, int j, int k, int l, int path[][2]){

    if(i < 0 || i >= n) return -2;
    if(j < 0 || j >= m) return -3;
    if(A[i*m + j] || A[k*m + l]) return -1;


    if(i == k && j == l && !A[i*m + j]){
      path[0][0] = i;
      path[0][1] = j;
      return 1;
    }
    A[i*m + j] = 2;
    int  t = 0;
    if(i + 1 < n && !A[(i + 1)*m + j]){ // Down
      t = find_path(n,m,A,i + 1,j,k,l,path + 1);
    }
    if(j + 1 < m && !A[i*m + j + 1] && !t){ // Right
      t = find_path(n,m,A,i,j + 1,k,l,path + 1);
    }
    if(i - 1 >= 0 && !A[(i - 1)*m + j] && !t){ //Up
      t = find_path(n,m,A,i - 1,j,k,l,path + 1);
    }
    if(j - 1 >= 0 && !A[i*m + j - 1] && !t){ // Left
      t = find_path(n,m,A,i,j - 1,k,l,path + 1);
    }
    A[i*m + j] = 0; // Toggle this off to see the explored squares
    if(t > 0){
      path[0][0] = i;
      path[0][1] = j;
      for(int x = 0; x < N*M + 1;x++) if(path[x][0] == k && path[x][1] == l) return x + 1;
      return t;
    }

    return 0;
}

int main(){
  int path[N*M + 1][2];
  int A[N*M] = {0, 0, 0, 1, 0,
                1, 0, 0, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 0, 1, 0,
                1, 1, 0, 0, 0};

  int d = find_path(N,M,A,-1,1,0,1,path);

  printf("%d\n",d);

  for(int j = 0; j < d; j++) printf("%d %d \n",path[j][0],path[j][1]);

  for(int i = 0; i < N;i++){
    printf("\n");
    for(int j = 0; j < M;j++) printf("%d ", A[i*M + j]);
  }

  return 0;
}
