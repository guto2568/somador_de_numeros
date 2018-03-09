/*Laboratorio 1 - EA876
 Augusto Damschi Bernardi
 RA 164491*/

#include<stdio.h>

/*Possiveis estados do sistema*/

/*Algo que não é um numero esta sendo lido*/
#define EMPTY        0
/*Lendo inteiro/parte inteira*/
#define INTEGER        1
/*Um numero na forma fatorial foi lido*/
#define FAT        2
/*Um ponto apos uma parte inteira foi lido*/
#define ENTER_FRACTION     3
/*Parte fracionaria do numero sendo lida*/
#define FRACTION    4

/*Estrutura que guarda numeros sendo lidos e soma*/
typedef struct{
  /*Parte inteira do numero a ser contabilizado*/
  long long number;
  /*Tamanho da parte fracionaria do numero a ser contabilizada*/
  long long frac;
  /*Soma de numeros ja contabilizados*/
  double sum;
} counter;

/*Descarta número que estava sendo lido*/
void discart(counter *c){
  c->number = 0;
  c->frac = 0;
}

/*Contabiliza ulrimo numero lido*/
void count(counter *c){
  double val = (double)c->number;
  /*Coloca parte fracionaria do numero lido depois do ponto*/
  while(c->frac){
     val /= 10;
     c->frac--;
  }
  c->sum += val;
  c->number = 0;
}

/*Aplica fatorial no numero sendo lido*/
void factorial(counter *c){
  long long res = (long long)1;
  long long i;
  for(i = (long long)2; i <= c->number; i++)
      res *= i;
  c->number = res;
}

/*Adiciona digito no numero sendo lido*/
void add_dig(counter *c, long long digit){
  c->number *= (long long)10;
  c->number += digit;
}

/*Adiciona digito na parte fracionaria do contador*/
void add_frac(counter *c){
  c->frac++;
}

int main(){
  char ch;
  counter c;
  c.sum = 0;
  discart(&c);
  int state = INTEGER;

  /*Le caractere, altera estados do programa e vai salvando numero lido e soma*/
  while(scanf("%c", &ch) == 1){

    /*Verifica estado atual*/
    switch(state){
      /*Caso em que não existe um espaço separando o que ja foi lido de um numero, e nenhum numero esta sendo lido*/
      case EMPTY:
        /*Se houver um espaço, é possivel ler um numero em seguida*/
        if(ch == ' ')
            state = INTEGER;
        break;

      /*Caso em que estamos esperando digitos inteiros*/
      case INTEGER:
        /*Le digito*/
        if(ch >= '0' && ch <= '9')
          add_dig(&c, (long long)(ch - '0'));
        /*Calcula fatorial do numero ja lido e passa  para estado correspondente*/
        else if(ch == '!'){
          state = FAT;
          factorial(&c);
        }
        /*Passa para leitura de parte fracionaria*/
        else if(ch == '.')
          state = ENTER_FRACTION;
        /*Termina de ler um inteiro*/
        else if(ch == ' ' || ch == '\n')
          count(&c);
        /*Le algo que desqualifica a sequencia ja lida de inteiros*/
        else{
          discart(&c);
          state = EMPTY;
        }
        break;

      /*Caso de leitura de fatorial*/
      case FAT:
        /*Numero deve ser considerado*/
        if(ch == ' ' || ch == '\n'){
          count(&c);
          state = INTEGER;
        }

        /*Le algo que desqualifica a sequencia ja lida de inteiros*/
        else{
          discart(&c);
          state = EMPTY;
        }
        break;

      /*Um ponto que pode iniciar parte fracionaria de um numero foi lido*/
      case ENTER_FRACTION:
        /*Se proximo caracter for um digito numerico, pode se tratar de um numero fracionario*/
        if(ch >= '0' && ch <= '9'){
          add_frac(&c);
          add_dig(&c, (long long)(ch - '0'));
          state = FRACTION;
        }
        /*Le algo que desqualifica a sequencia ja lida de inteiros*/
        else{
          discart(&c);
          state = EMPTY;
        }
        break;

      /*Estamos lendo um numero fracionario*/
      case FRACTION:
        /*Adiciona digito*/
        if(ch >= '0' && ch <= '9'){
          add_frac(&c);
          add_dig(&c, (long long)(ch - '0'));
        }
        /*Termina numero*/
        else if(ch == ' ' || ch == '\n'){
          count(&c);
          state = INTEGER;
        }
        /*Le algo que desqualifica a sequencia ja lida de inteiros*/
        else{
          discart(&c);
          state = EMPTY;
        }
        break;
        }

  }
  /*Contabiliza número que pode exisstir antes do EOF*/
  count(&c);

  printf("%.2f\n", c.sum);

  return 0;
}