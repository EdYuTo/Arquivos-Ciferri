//EDSON YUDI TOMA - 9791305
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *read() {
   char *text = NULL, c;
   int i = 0;

   do {
      c = fgetc(stdin);
      text = (char *)realloc(text, sizeof(char) * (i+1));
      text[i++] = c;
   } while (c != '\n');

   text[--i] = '\0';

   return text;
}

int main (int argc, char *argv[ ]) {
   char *nome;
   int comando = 5;
   FILE *fp;

   printf("-->Digite um nome para o arquivo (ate 7 caracteres)\n");
   nome = read();

   printf("-->Digite '0' para sair\n-->Digite '1' para gravacao de dados\n");
   printf("-->Digite '2' para recuperacao de dados\n");
   printf("-->Digite '3' para rever os comandos\n");

   while (comando) {
      scanf("%d", &comando);
      if (comando == 1) {
         getchar();//ignora o enter digitado apos o scanf()!
         char *texto;
         fp = fopen(nome, "ab");
         if (fp != NULL) {
            while (1) {
               printf("-->Digite 'sair' para sair ou um nome para continuar\n");
               texto = read();
               if (strcmp(texto, "sair\0")) {
                  int tam = strlen(texto);
                  fwrite(&tam, sizeof(int), 1, fp);//escreve o tamanho para a leitura
                  fwrite(texto, sizeof(char)*(tam+1), 1, fp);//escreve a string com o '\0'

                  printf("-->Digite o sobrenome\n");
                  free(texto);
                  texto = read();
                  tam = strlen(texto);
                  fwrite(&tam, sizeof(int), 1, fp);
                  fwrite(texto, sizeof(char)*(tam+1), 1, fp);

                  printf("-->Digite o email\n");
                  free(texto);
                  texto = read();
                  tam = strlen(texto);
                  fwrite(&tam, sizeof(int), 1, fp);
                  fwrite(texto, sizeof(char)*(tam+1), 1, fp);

                  printf("-->Digite a idade\n");//idade tratada como string para facilitar(geralmente economiza + bytes tb!)
                  free(texto);
                  texto = read();
                  tam = strlen(texto);
                  fwrite(&tam, sizeof(int), 1, fp);
                  fwrite(texto, sizeof(char)*(tam+1), 1, fp);//tam+1 para incluir o '\0'

               } else {free(texto);break;}
               free(texto);
            }
            fclose(fp);
            printf("-->Algo mais?, digite 3 case nao lembre os comandos!\n");
         }
      }
      else if (comando == 2) {
         getchar();//ignora o enter digitado apos o scaf()!
         fp = fopen(nome, "r");
         if (fp != NULL) {
            char string[32];
            fseek(fp, 0, SEEK_END);
            int tamanho = ftell(fp), i = 0, aux;
            fseek(fp, 0, SEEK_SET);
            while (i < tamanho) {
               fread(&aux, sizeof(int), 1, fp);//pega o tamanho da string
               fread(string, sizeof(char), aux+1, fp);//pega a string + o '\0'
               i += aux+5;//+4 para cada inteiro alocado para indicar tamanho e +1 para o '\0'
               printf("Nome: %s\n", string);

               fread(&aux, sizeof(int), 1, fp);//pega o tamanho da string
               fread(string, sizeof(char), aux+1, fp);//pega a string + o '\0'
               i += aux+5;//+4 para cada inteiro alocado para indicar tamanho e +1 para o '\0'
               printf("Sobrenome: %s\n", string);

               fread(&aux, sizeof(int), 1, fp);//pega o tamanho da string
               fread(string, sizeof(char), aux+1, fp);//pega a string + o '\0'
               i += aux+5;//+4 para cada inteiro alocado para indicar tamanho e +1 para o '\0'
               printf("Email: %s\n", string);

               fread(&aux, sizeof(int), 1, fp);//pega o tamanho da string
               fread(string, sizeof(char), aux+1, fp);//pega a string + o '\0'
               i += aux+5;//+4 para cada inteiro alocado para indicar tamanho e +1 para o '\0'
               printf("Idade: %s\n", string);

               printf("-->Pressione qualquer tecla para continuar...");
               getchar();
            }
            printf("-->Fim da impressao, digite outro comando...\n");
            fclose(fp);
         }
      }
      else if (comando == 0) {
         printf("-->Deseja mesmo sair? y\n");
         char c;
         scanf("\n%c", &c);
         if (c == 'y' || c == 'Y')
            comando = 0;
         else
            comando = 5;
      }
      else if (comando == 3) {
         printf("-->Digite '0' para sair\n-->Digite '1' para gravacao de dados\n");
         printf("-->Digite '2' para recuperacao de dados\n");
         printf("-->Digite '3' para rever os comandos\n");
      }
   }
   free(nome);
   return 0;
}
