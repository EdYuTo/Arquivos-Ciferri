//EDSON YUDI TOMA - 9791305
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *read(FILE *local) {//read generica
   char *nome = NULL, c;
   int count = 0;
   
   do {
      c = fgetc(local);
      nome = (char *)realloc(nome, sizeof(char) * (count+1));
      nome[count++] = c;
   } while (c != '\n' && c != EOF);

   nome[--count] = '\0';

   return nome;
}

void write(char *nome, FILE *fp) {//ecrever no arquivo um nome todo
   if (nome != NULL) {
      for (int i = 0; nome[i] != '\0'; i++)
         fputc(nome[i], fp);
      fputc('\n', fp);
   }
}

int empty(char *nome) {//aux checa se a string esta vazia
   return !strcmp(nome, "\0");
}

void merging(FILE *fp1, FILE *fp2) {
   FILE *fp = fopen("saidaMerging.txt", "w");
   if (fp1 == NULL && fp2 != NULL) {//apenas copia o 2 arquivo
      char c = fgetc(fp2);
      while (c != EOF)
         fputc(c, fp);

   } else if (fp1 != NULL && fp2 == NULL) {//apenas copia o 1 arquivo
      char c = fgetc(fp1);
      while (c != EOF)
         fputc(c, fp);

   } else if (fp1 != NULL && fp2 != NULL) {
      char *nome1, *nome2;
      nome1 = read(fp1);
      nome2 = read(fp2);
      while (!empty(nome1) || !empty(nome2)) {//mesmo q uma lista chegou ao fim, continua-se na outra
         if (!empty(nome1) && empty(nome2)) {//1 com nome, 2 vazio
            write(nome1, fp);//escreve 1
            free(nome1);
            nome1 = read(fp1);//le novo nome
         }
         else if (empty(nome1) && !empty(nome2)) {//1 vazio, 2 com nome
            write(nome2, fp);//escreve 2
            free(nome2);
            nome2 = read(fp2);//le novo nome
         }
         else {//ambos com nome
            if (strcmp(nome1, nome2) == 0) {//nomes iguais
               write(nome1, fp);//escreve um dos dois
               free(nome1);
               free(nome2);
               nome1 = read(fp1);//|
               nome2 = read(fp2);//|-> le os 2
            }
            else if (strcmp(nome1, nome2) < 0) {//nome1 antes de nome2
               write(nome1, fp);//escreve nome1
               free(nome1);
               nome1 = read(fp1);//le do arquivo 1
            }
            else {//nome1 depois de nome2
               write(nome2, fp);//escreve nome2
               free(nome2);
               nome2 = read(fp2);//le do arquivo 2
            }
         }
      }
      free(nome1);//possui um "\0"
      free(nome2);//possui um "\0"
   }
   fclose(fp);
}

void matching(FILE *fp1, FILE *fp2) {
   FILE *fp = fopen("saidaMatching.txt", "w");
   if (fp1 != NULL && fp2 != NULL) {//se for null nao ha match!
      char *nome1, *nome2;
      nome1 = read(fp1);
      nome2 = read(fp2);
      while (!empty(nome1) && !empty(nome2)) {//quando uma ficar vazia nao ha necessidade de continuar checando
         if (strcmp(nome1, nome2) == 0) {//nomes iguais
            write(nome1, fp);//escreve um dos dois = MATCH!
            free(nome1);
            free(nome2);
            nome1 = read(fp1);//|
            nome2 = read(fp2);//|-> le os 2
         }
         else if (strcmp(nome1, nome2) < 0) {//nome1 antes de nome2 - segue o jogo
            free(nome1);
            nome1 = read(fp1);//le do arquivo 1
         }
         else {//nome1 depois de nome2 - segue o jogo
            free(nome2);
            nome2 = read(fp2);//le do arquivo 2
         }
      }
      free(nome1);//possui pelo menos um "\0"
      free(nome2);//possui pelo menos um "\0"
   }
   fclose(fp);
}

int main(int argc, char *argv[ ]) {
   char *arq1, *arq2;
   int op;
   FILE *fp1, *fp2;

   printf("Digite os nomes do 1 arquivo\n");
   arq1 = read(stdin);
   fp1 = fopen(arq1, "r");
   if (fp1 == NULL) {
      printf("Arquivo inexistente ou sem premissao para abri-lo!\n");
      exit(0);
   }

   printf("Digite os nomes do 2 arquivo\n");
   arq2 = read(stdin);
   fp2 = fopen(arq2, "r");
   if (fp2 == NULL) {
      printf("Arquivo inexistente ou sem premissao para abri-lo!\n");
      exit(0);
   }

   printf("Deseja realizar um Merging (1) ou um Matching (2)?\nDigite o valor: ");
   scanf("%d", &op);

   if (op == 1)
      merging(fp1, fp2);
   else if (op == 2)
      matching(fp1, fp2);
   else
      printf("Valor invalido, encerrando programa...\n");

   free(arq1);
   free(arq2);
   fclose(fp1);
   fclose(fp2);

   return 0;
}
