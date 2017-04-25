//EDSON YUDI TOMA - 9791305
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct pessoa {
   char nome[16], sobrenome[16], email[32], idade[8];
} PESSOA;

void criar (PESSOA *pessoa, char *texto) {
   strcpy(pessoa->nome, texto);
   printf("-->Digite o sobrenome\n");
   scanf("%s", pessoa->sobrenome);
   printf("-->Digite o email\n");
   scanf("%s", pessoa->email);
   printf("-->Digite a idade\n");
   scanf("%s", pessoa->idade);
}

void imprimir (PESSOA pessoa) {
   printf("Nome: %s\n", pessoa.nome);
   printf("Sobrenome: %s\n", pessoa.sobrenome);
   printf("Email: %s\n", pessoa.email);
   printf("Idade: %s\n", pessoa.idade);
}

int main (int argc, char *argv[ ]) {
   char nome[8];
   int comando = 5;
   PESSOA pessoa;
   FILE *fp;

   printf("-->Digite um nome para o arquivo (ate 7 caracteres)\n");
   scanf("%s", nome);

   printf("-->Digite '0' para sair\n-->Digite '1' para gravacao de dados\n");
   printf("-->Digite '2' para recuperacao de dados\n-->Digite '3' para recuperar dados de uma pessoa\n");
   printf("-->Digite '4' para rever os comandos\n");

   while (comando) {
      scanf("%d", &comando);
      if (comando == 1) {
         char texto[32];
         texto[0] = '\0';
         fp = fopen(nome, "ab");
         if (fp != NULL) {
            while (1) {
               printf("-->Digite 'sair' para sair ou um nome para continuar\n");
               scanf("%s", texto);
               if (strcmp(texto, "sair\0")) {
                  criar(&pessoa, texto);
                  fwrite(&pessoa, sizeof(PESSOA), 1, fp);
               } else break;
            }
            fclose(fp);
            printf("-->Algo mais?, digite 4 case nao lembre os comandos!\n");
         }
      }
      else if (comando == 2) {
         getchar();
         fp = fopen(nome, "r");
         if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            int tamanho = ftell(fp)/sizeof(PESSOA);
            fseek(fp, 0, SEEK_SET);
            for (int i = 0; i < tamanho; i++) {
               fread(&pessoa, sizeof(PESSOA), 1, fp);
               imprimir(pessoa);
               printf("-->Pressione qualquer tecla para continuar...");
               getchar();
            }
            printf("-->Fim da impressao, digite outro comando...\n");
            fclose(fp);
         }
      }
      else if (comando == 3) {
         fp = fopen(nome, "r");
         if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            int rrn, tamanho = ftell(fp)/sizeof(PESSOA);
            fseek(fp, 0, SEEK_SET);
            
            printf("-->Digite o rrn\n");
            scanf("%d", &rrn);
            
            if (rrn >= tamanho)
               printf("-->Erro, posicao nao disponivel\n");
            else {
               fseek(fp, sizeof(PESSOA) * rrn, SEEK_SET);
               fread(&pessoa, sizeof(PESSOA), 1, fp);
               imprimir(pessoa);
            }
            fclose(fp);
         }
         printf("-->Digite outro comando\n");
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
      else if (comando == 4) {
         printf("-->Digite '0' para sair\n-->Digite '1' para gravacao de dados\n");
         printf("-->Digite '2' para recuperacao de dados\n-->Digite '3' para recuperar dados de uma pessoa\n");
         printf("-->Digite '4' para rever os comandos\n");
      }
   }
   return 0;
}
