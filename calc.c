/* Program to add and subtract integers of arbitrary length */

#include <stdio.h>
#include <string.h>
#define N 80
//0 = 48

void add(const char a[], const char b[], char res[]){
  short carry = 0;
  int len_a = strlen(a);
  int len_b = strlen(b);
  int diff = len_a - len_b > 0 ? len_a - len_b : len_b - len_a;
  int temp = 0;
  res[0] = 8;
  if(len_a >= len_b){
    for(int i = len_a - 1; i >= len_a - len_b;i--){
      temp = a[i] + b[i - diff] - 96 + carry;
      if(temp > 9){
        temp %= 10;
        carry = 1;
      }
      else carry = 0;
      res[i + 1] = temp + 48;
    }
    for(int i = len_a - len_b - 1;i >= 0;i--){
      temp = a[i] - 48 + carry;
      if(temp > 9){
        temp %= 10;
        carry = 1;
      }
      else carry = 0;
      res[i + 1] = temp + 48;
    }
    if(carry) res[0] = 49;
  }
  else{
      for(int i = len_b - 1; i >= len_b - len_a;i--){
        temp = b[i] + a[i - diff] - 96 + carry;
        if(temp > 9){
          temp %= 10;
          carry = 1;
        }
        else carry = 0;
        res[i + 1] = temp + 48;
      }
      for(int i = len_b - len_a - 1;i >= 0;i--){
        temp = b[i] - 48 + carry;
        if(temp > 9){
          temp %= 10;
          carry = 1;
        }
        else carry = 0;
        res[i + 1] = temp + 48;
      }
      if(carry) res[0] = 49;
    }
}

void sub(const char a[], const char b[], char res[]){
    int len_a = strlen(a);
    int len_b = strlen(b);
    int diff = len_a - len_b > 0 ? len_a - len_b : len_b - len_a;
    int temp = 0;
    short make_negative = 0;
    short carry = 0;
    int n = -1;
    res[0] = 8;
    short aa = 0;
    if(len_a > len_b) aa = 1;
    if(len_b > len_a) aa = 0;
    if(len_a == len_b){
      short flag = 0;
      for(int i = 0; i < len_a;i++){
        if(a[i] > b[i]){
          flag = 1;
          aa = 1;
          break;
       }
        if(b[i] > a[i]){
          flag = 1;
          aa = 0;
          break;
        }
      }

      if(!flag){ //Numbers are equal so their difference is 0
        res[0] = 48;
        return;
      }
    }

    if(aa){
      for(int i = len_a - 1; i >= len_a - len_b;i--){
        if(n > 0){
          carry = 9;
          n--;
        }
        if(!n){
          carry = -1;
          n = -1;
        }
        temp = a[i] - b[i - diff] + carry;
        //printf("%d",temp);
        if(temp < 0 && len_a > 1){
          temp += 10;
          if(n == -1) n = 0;
          for(int k = i - 1;k >= 0 && a[k] == 48;k--) n++;
          carry = - 1;
        }
        else carry = 0;
        if(temp < 0) temp *= -1;

        res[i + 1] = temp + 48;
      }

      for(int i = len_a - len_b - 1;i >= 0;i--){
        if(n > 0){
          res[i + 1] = 57;
          n--;
        }
        else if(!n){
          res[i + 1] = a[i] - 1;
          n = -1;
        }
        else res[i + 1] = a[i];
      }
    }

    else{
      make_negative = 1;
      for(int i = len_b - 1; i >= len_b - len_a;i--){
        if(n > 0){
          carry = 9;
          n--;
        }
        if(!n){
          carry = -1;
          n = -1;
        }
        temp = b[i] - a[i - diff] + carry;
        if(temp < 0){
          temp += 10;
          if(n == -1) n = 0;
          for(int k = i - 1;k >= 0 && b[k] == 48;k--) n++;
          carry = - 1;
        }
        else carry = 0;
        res[i + 1] = temp + 48;
      }

      for(int i = len_b - len_a - 1;i >= 0;i--){
        if(n > 0){
          res[i + 1] = 57;
          n--;
        }
        else if(!n){
          res[i + 1] = b[i] - 1;
          n = -1;
        }
        else res[i + 1] = b[i];
      }
    }
    for(int i = 1; i < N;i++){
      if(res[i] == 48) res[i] = 7;
      else break;
    }
    if(make_negative) res[0] = 45;
}

char a[N], b[N], res[N + 1];

int main(){

    scanf("%s %s",a,b);
    add(a,b,res);

    printf("%s",res);

  return 0;
}
