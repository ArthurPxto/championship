#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// declaração do struct competidor
typedef struct competidor
{
   char faixa[15], nome[50];
   float peso;
   int idade, inscricao;
} Competidor;

// Remove competidor do vetor, e salva vetor atualizado no arquivo
void removerCompetidor(int nCompetidores, Competidor *vetorCompetidores)
{
   system("cls");

   int id;
   char confirma;

   printf("-------Remover Competidor-------- \n");
   printf("\n Digite o id do competidor: ");
   scanf("%d", &id);

   // carregarCompetidores(nCompetidores, vetorCompetidores);
   // Realmente necessário chamar essa função aqui ?
   // já foi chamada na main() e suas variáveis foram exportadas para a função atual

   for (int i = 0; i < nCompetidores; i++)
   {
      if (id == vetorCompetidores[i].inscricao)
      {
         printf("Competidor  %s encontrado deseja remove-lo? (S/n)", vetorCompetidores[i].nome);
         scanf(" %c", &confirma);

         if (toupper(confirma) == 'S')
         {
            vetorCompetidores[i].inscricao = 0;
         }
      }
   }

   salvarCompetidores(nCompetidores, vetorCompetidores);

   system("cls");
   printf("\ncompetidor removido com sucesso!\n");
}

// carrega os competidores do arquivo no vetor
int carregarCompetidores(int nCompetidores, Competidor *vetorCompetidores)
{
   int maiorInscricao = 0;
   // declaração do ponteiro tipo FILE
   FILE *cadastro;
   cadastro = fopen("cadastro.txt", "r");

   if (cadastro == NULL)
   {
      printf("Error opening file.\n");
      printf("Function: carregarCompetidores\n");
      // return 1;
   }

   for (int i = 0; i < nCompetidores; i++)
   {
      if (vetorCompetidores[i].inscricao > maiorInscricao)
      {
         maiorInscricao = vetorCompetidores[i].inscricao;
      }
      fscanf(cadastro, "%d %s %s %f %d",
             &vetorCompetidores[i].inscricao,
             vetorCompetidores[i].nome,
             vetorCompetidores[i].faixa,
             &vetorCompetidores[i].peso,
             &vetorCompetidores[i].idade);
   }
   fclose(cadastro);
   ordenarCompetidores(nCompetidores, vetorCompetidores);
   salvarCompetidores(nCompetidores, vetorCompetidores);

   return maiorInscricao;
}

// salva os competidores no arquivo
void salvarCompetidores(int nCompetidores, Competidor *vetorCompetidores)
{
   // declaração do ponteiro tipo FILE
   FILE *cadastro;
   cadastro = fopen("cadastro.txt", "w+");

   if (cadastro == NULL)
   {
      printf("Error opening file.\n");
      printf("Function: salvarCompetidores\n");
      // return 1;
   }

   for (int i = 0; i < nCompetidores; i++)
   {
      if (vetorCompetidores[i].inscricao != 0)
      {
         fprintf(cadastro, "%d %s %s %g %d\n",
                 vetorCompetidores[i].inscricao,
                 vetorCompetidores[i].nome,
                 vetorCompetidores[i].faixa,
                 vetorCompetidores[i].peso,
                 vetorCompetidores[i].idade);
      }
   }
   fclose(cadastro);
}

// Alterna a ordem dos competidores, CHAMADA APENAS PELA ordenarCompetidores
void alternaCompetidor(int comp1, int comp2, Competidor *vetorCompetidores)
{
   Competidor temp;
   temp.inscricao = vetorCompetidores[comp1].inscricao;
   temp.idade = vetorCompetidores[comp1].idade;
   temp.peso = vetorCompetidores[comp1].peso;
   strcpy(temp.nome, vetorCompetidores[comp1].nome);
   strcpy(temp.faixa, vetorCompetidores[comp1].faixa);

   vetorCompetidores[comp1].inscricao = vetorCompetidores[comp2].inscricao;
   vetorCompetidores[comp1].idade = vetorCompetidores[comp2].idade;
   vetorCompetidores[comp1].peso = vetorCompetidores[comp2].peso;
   strcpy(vetorCompetidores[comp1].nome, vetorCompetidores[comp2].nome);
   strcpy(vetorCompetidores[comp1].faixa, vetorCompetidores[comp2].faixa);

   vetorCompetidores[comp2].inscricao = temp.inscricao;
   vetorCompetidores[comp2].idade = temp.idade;
   vetorCompetidores[comp2].peso = temp.peso;
   strcpy(vetorCompetidores[comp2].nome, temp.nome);
   strcpy(vetorCompetidores[comp2].faixa, temp.faixa);
}

// ordena os competidores de forma sequencial, considerando o número de inscrição
void ordenarCompetidores(int n, Competidor *vetorCompetidores)
{
   if (n < 1)
      return;

   for (int i = 0; i < n; i++)
   {
      if (vetorCompetidores[i].inscricao > vetorCompetidores[i + 1].inscricao)
         alternaCompetidor(i, i + 1, vetorCompetidores);
   }
   ordenarCompetidores(n - 1, vetorCompetidores);
}

// função que conta competidores
int contarCompetidores()
{
   FILE *cadastro = fopen("cadastro.txt", "r");
   // Testa se arquivo foi aberto corretamente
   if (cadastro == NULL)
   {
      printf("Error opening file.\n");
      printf("Function: getNumberOfStudents\n");
      return 1;
   }

   int nCompetidores = 0;
   char temp;

   while (fscanf(cadastro, "%c", &temp) != EOF)
   {
      if (temp == '\n')
         nCompetidores++;
   }
   fclose(cadastro);
   return nCompetidores;
}

// Calcula se há alguma lacuna na sequencia dos números de inscrições
int temLacuna(int nCompetidores, Competidor *vetorCompetidores)
{
   int temp = 0, temp1, lacuna = 0;
   for (int i = 0; i <= nCompetidores; i++)
   {
      temp1 = vetorCompetidores[i].inscricao;
      if (vetorCompetidores[i].inscricao)
      {
         if ((temp + 1) == temp1)
         {
            temp = temp1;
         }
         {
            lacuna = temp + 1;
         }
      }
   }

   return lacuna;
}

// cadastra o competidor e chama a função pra salvar no arquivo
int cadastrarCompetidor(int nCompetidores, Competidor *vetorCompetidores)
{
   int lacuna = temLacuna(nCompetidores, vetorCompetidores);
   system("cls");
   printf("\n---- CADASTRO DE COMPETIRORES ------\n");

   struct competidor competidor;

   // bug com o modo de cadastro a funciona para adicionar mas no primeiro caso falha
   // o w funciona apenas para o primeiro caso e nao para adicionar
   FILE *cadastro = fopen("cadastro.txt", "a");

   // Testa se arquivo foi aberto corretamente
   if (cadastro == NULL)
   {
      printf("Error opening file.\n");
      printf("Function: getNumberOfStudents\n");
      return 1;
   }
   printf("Informe o nome do competidor:");
   scanf("%15[^\n]", competidor.nome);
   setbuf(stdin, NULL);
   printf("Informe a faixa do competidor:");
   scanf("%50[^\n]", competidor.faixa);
   setbuf(stdin, NULL);
   printf("Informe o peso do competidor:");
   scanf("%f", &competidor.peso);
   setbuf(stdin, NULL);
   printf("Informe a idade do competidor: ");
   scanf("%d", &competidor.idade);
   setbuf(stdin, NULL);

   nCompetidores++;

   if (lacuna)
   {
      competidor.inscricao = lacuna;
   }
   else
   {
      competidor.inscricao = nCompetidores;
   }

   fprintf(cadastro, "%d %s %s %g %d \n", competidor.inscricao, competidor.nome, competidor.faixa, competidor.peso, competidor.idade);
   fclose(cadastro);
   // comando para limpar a tela do terminal

   free(vetorCompetidores);
   vetorCompetidores = (Competidor *)malloc(nCompetidores * sizeof(Competidor));
   // vetorCompetidores = realloc(vetorCompetidores, nCompetidores * sizeof(Competidor));
   carregarCompetidores(nCompetidores, vetorCompetidores);
   system("cls");
   return nCompetidores;
}

// verifica se o competidor esta no arquivo
void acharCompetidor(int nCompetidores, Competidor *vetorCompetidores)
{
   int id, valid = 0;

   system("cls");
   printf("Competidores registrados: %d\n", nCompetidores);

   // do
   // {
   printf("Digite a inscricao do competidor: ");
   scanf(" %d", &id);

   carregarCompetidores(nCompetidores, vetorCompetidores);

   for (int i = 0; i < nCompetidores; i++)
   {
      if (id == vetorCompetidores[i].inscricao)
      {
         valid = 1;

         printf("\nNome: %s\nInscricao: %d\nFaixa: %s\nPeso: %g\nIdade: %d", vetorCompetidores[i].nome, vetorCompetidores[i].inscricao, vetorCompetidores[i].faixa, vetorCompetidores[i].peso, vetorCompetidores[i].idade);
      }
   }
   //    if (id < 1)
   //    {
   //       printf("Menor número de inscricao: 0\n");
   //       printf("Escreva uma inscricao valida!\n");
   //    }
   //    else if (id > nCompetidores)
   //    {
   //       printf("Maior número de inscricao: %d\n", nCompetidores);
   //       printf("Escreva uma inscricao valida!\n");
   //    }
   // } while (id < 1 || id > nCompetidores);

   if (valid == 0)
   {
      printf("\n O competidor com o id %d nao existe!! \n", id);
   }
}

// Altera informações do competidor
void alterarCompetidor(int nCompetidores, Competidor *vetorCompetidores)
{
   int competidor, opcao; //, novoPeso, novaIdade;
   // char novoNome[50], novaFaixa[15];
   printf("Digite o id do competidor que deseja alterar: ");
   scanf("%d", &competidor);
   setbuf(stdin, NULL);

   printf("ALTERAR\n");
   printf("1) NOME\n");
   printf("2) FAIXA\n");
   printf("3) PESO\n");
   printf("4) IDADE\n");

   printf("Digite a opcao: ");
   scanf("%d", &opcao);
   setbuf(stdin, NULL);
   switch (opcao)
   {
   case 1:
      printf("Informe o nome do competidor:");
      scanf("%50[^\n]", vetorCompetidores[competidor - 1].nome);
      setbuf(stdin, NULL);
      break;
   case 2:
      printf("Informe a faixa do competidor:");
      scanf("%15[^\n]", vetorCompetidores[competidor - 1].faixa);
      setbuf(stdin, NULL);
      break;
   case 3:
      printf("Informe o peso do competidor:");
      scanf("%f", &vetorCompetidores[competidor - 1].peso);
      setbuf(stdin, NULL);
      break;
   case 4:
      printf("Informe a idade do competidor: ");
      scanf("%d", &vetorCompetidores[competidor - 1].idade);
      setbuf(stdin, NULL);
      break;
   default:
      printf("Opcao invalida!\n");
      break;
   }

   salvarCompetidores(nCompetidores, vetorCompetidores);
   printf("Competidor alterado!\n");
   sleep(3);
}

// Escreve o menu
int menu()
{
   int opcao;

   system("cls");
   printf("------- MENU -------- \n");
   printf("1) CADASTRAR COMPETIDOR \n");
   printf("2) REMOVER COMPETIDOR \n");
   printf("3) ALTERAR DADOS DO COMPETIDOR \n");
   printf("4) PESQUISAR COMPETIDORES\n");
   printf("5) COMECAR CAMPEONATO \n");
   printf("6) SAIR \n");

   printf("\nDigite a Opcao: ");
   scanf("%d", &opcao);

   setbuf(stdin, NULL);
   return opcao;
}

int separaCompetidores(int nCompetidores, Competidor *vetorCompetidores, int *competidores, int quantidadeCompetidores, char faixa, char peso)
{
   for (int i = 0; i < nCompetidores; i++)
   {
      if (tolower(vetorCompetidores[i].faixa[0]) == tolower(faixa))
      {
         if (tolower(peso) == 'g')
         {
            if (vetorCompetidores[i].peso < 60)
            {
               quantidadeCompetidores++;
               competidores = (int *)realloc(competidores, quantidadeCompetidores * sizeof(int));
               competidores[quantidadeCompetidores - 1] = vetorCompetidores[i].inscricao;
            }
         }
         else if (tolower(peso) == 'm')
         {
            if (vetorCompetidores[i].peso >= 60 && vetorCompetidores[i].peso < 75)
            {
               quantidadeCompetidores++;
               competidores = (int *)realloc(competidores, quantidadeCompetidores * sizeof(int));
               competidores[quantidadeCompetidores - 1] = vetorCompetidores[i].inscricao;
            }
         }
         else if (tolower(peso) == 'p')
         {
            if (vetorCompetidores[i].peso >= 75)
            {
               quantidadeCompetidores++;
               competidores = (int *)realloc(competidores, quantidadeCompetidores * sizeof(int));
               competidores[quantidadeCompetidores - 1] = vetorCompetidores[i].inscricao;
            }
         }
      }
   }
   return quantidadeCompetidores;
}

// Falta testar para checar o funcionamento
int chaveamento(int quantidadeCompetidores, int *competidores)
{
   if (quantidadeCompetidores > 2)
   {
      int *vencedores[quantidadeCompetidores];
      int nVencedores = 0;
      for (int i = 0; i < quantidadeCompetidores / 2; i += 2)
      {
         if (luta())
         {
            vencedores[nVencedores] = competidores[i];
         }
         else
         {
            vencedores[nVencedores] = competidores[i];
         }
         nVencedores++;
      }
      if (quantidadeCompetidores >= 2)
      {
         return chaveamento(nVencedores, vencedores);
      }
      else
      {
         return vencedores[0];
      }
   }
   else if (quantidadeCompetidores == 1)
   {
      return competidores[0];
   }
   else
   {
      return 0;
   }
}

// testar a veracidade da aleatoriedade
int luta()
{
   int a = 0, b = 0;
   int matrizLutas[2][3];
   for (int j = 0; j < 3; j++)
      do
      {
         matrizLutas[0][j] = rand() % 11;
         matrizLutas[1][j] = rand() % 11;
      } while (matrizLutas[0][j] == matrizLutas[1][j]);
   matrizLutas[0][0] > matrizLutas[1][0] ? a++ : b++;
   matrizLutas[0][1] > matrizLutas[1][1] ? a++ : b++;

   if (a == b)
      matrizLutas[0][2] > matrizLutas[1][2] ? a++ : b++;

   // testar a veracidade da aleatoriedade

   printf("A: %d, B: %d.\n", a, b);

   if (a > b)
      return 0;
   else
      return 1;
}

void comecarCampeonato(int nCompetidores, Competidor *vetorCompetidores)
{
   int *competidores, quantidadeCompetidores = 0;
   competidores = (int *)malloc(quantidadeCompetidores * sizeof(int));

   char faixa[30], peso[30];

   system("cls");

   // Mostra alguns exemplos, falta testar a veracidade da aleatoriedade
   printf("Winner: %d\n", luta());
   printf("Winner: %d\n", luta());
   printf("Winner: %d\n", luta());
   printf("Winner: %d\n", luta());
   printf("Winner: %d\n", luta());
   printf("Winner: %d\n", luta());
   printf("Winner: %d\n", luta());

   printf("Escolha a categoria:\n");
   printf("Faixas disponiveis para a luta:\n-Branca\n-Azul\n-Marrom\n-Preta\n");
   printf("Digite a faixa: ");
   scanf("%s", &faixa);

   system("cls");
   printf("Pesos disponiveis para a luta:\n-Galo\n-Medio\n-Pesado\n");
   printf("Escolha a categoria:\n");
   printf("Digite o peso: ");
   scanf("%s", &peso);

   quantidadeCompetidores = separaCompetidores(nCompetidores, vetorCompetidores, competidores, quantidadeCompetidores, faixa[0], peso[0]);

   system("cls");
   printf("\n------ O CAMPEONATO COMECOU------- \n");

   printf("Quantidade de competidores: %d\n", quantidadeCompetidores);
   for (int i = 0; i < quantidadeCompetidores; i++)
   {
      printf("Competidor %d: %s\n", i + 1, vetorCompetidores[competidores[i] - 1].nome);
      printf("Competidor %d: %d\n", i + 1, competidores[i]);
   }

   printf("\nVencedor: %d", chaveamento(quantidadeCompetidores, competidores));
}

int main()
{
   srand(time(NULL));
   int opcao, nCompetidores = contarCompetidores(), maiorCompetidor;

   // declaração do vetor de competidores
   Competidor *vetorCompetidores;

   vetorCompetidores = (Competidor *)malloc(nCompetidores * sizeof(Competidor));

   maiorCompetidor = carregarCompetidores(nCompetidores, vetorCompetidores);

   while (1)
   {
      switch (opcao = menu())
      {
      case 1:
         // nCompetidores = cadastrarCompetidor(nCompetidores, vetorCompetidores);
         nCompetidores = cadastrarCompetidor(nCompetidores, vetorCompetidores);
         break;
      case 2:
         removerCompetidor(nCompetidores, vetorCompetidores);
         nCompetidores = contarCompetidores();
         break;
      case 3:
         alterarCompetidor(contarCompetidores, vetorCompetidores);
         break;
      case 4:
         acharCompetidor(nCompetidores, vetorCompetidores);

         printf("\nAperte Enter para continuar.\n");
         getchar();
         getchar();
         break;
      case 5:
         comecarCampeonato(nCompetidores, vetorCompetidores);

         printf("\nAperte Enter para continuar.\n");
         getchar();
         getchar();
         break;
      case 6:
         printf("\nPrograma encerrado.\n");
         return 0;
         break;
      default:
         printf(" \n Opcao invalida! \n");
         break;
      }
   }
   free(vetorCompetidores);
}