#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 52

typedef struct TCarta{
    char face[3];
    char naipe;
    int valor;
    char nome[20];
}TCarta;
void main(){
    int n, i=0;
    FILE *fp;
    TCarta cartas[TAM];

        // char faces[TAM][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
        //                     "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
        //                     "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
        //                     "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};



        // char naipes[TAM][1] = {"P","P","P","P","P","P","P","P","P","P","P","P","P",
        //                     "C","C","C","C","C","C","C","C","C","C","C","C","C",
        //                     "E","E","E","E","E","E","E","E","E","E","E","E","E",
        //                     "O","O","O","O","O","O","O","O","O","O","O","O","O"};

        // int valores[TAM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        //                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        //                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        //                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};



        // char nomes[TAM][20] = {"As de Paus\n", "Dois de Paus\n","Tres de Paus\n","Quatro de Paus\n","Cinco de Paus\n","Seis de Paus\n","Sete de Paus\n","Oito de Paus\n","Nove de Paus\n","Dez de Paus\n","Valete de Paus\n","Rainha de Paus\n","Rei de Paus\n",
        //                     "As de Copas\n", "Dois de Copas\n","Tres de Copas\n","Quatro de Copas\n","Cinco de Copas\n","Seis de Copas\n","Sete de Copas\n","Oito de Copas\n","Nove de Copas\n","Dez de Copas\n","Valete de Copas\n","Rainha de Copas\n","Rei de Copas\n",
        //                     "As de Espadas\n", "Dois de Espadas\n","Tres de Espadas\n","Quatro de Espadas\n","Cinco de Espadas\n","Seis de Espadas\n","Sete de Espadas\n","Oito de Espadas\n","Nove de Espadas\n","Dez de Espadas\n","Valete de Espadas\n","Rainha de Espadas\n","Rei de Espadas\n",
        //                     "As de Ouros\n", "Dois de Ouros\n","Tres de Ouros\n","Quatro de Ouros\n","Cinco de Ouros\n","Seis de Ouros\n","Sete de Ouros\n","Oito de Ouros\n","Nove de Ouros\n","Dez de Ouros\n","Valete de Ouros\n","Rainha de Ouros\n","Rei de Ouros\n",};


    

    fp = fopen("Cartas.txt","r");
        // fp = fopen("NOVASCARTAS.txt","w+");


        // for(int i = 0; i < TAM; i++){
        //     strcpy(cartas[i].face, faces[i]);
        //     // cartas[i].naipe = naipes[i];
        //     strcpy(cartas[i].naipe, naipes[i]);
        //     cartas[i].valor = valores[i];
        //     strcpy(cartas[i].nome, nomes[i]);
        // }


        // fwrite(cartas, sizeof(TCarta), TAM, fp);
    //fread(cartas, sizeof(TCarta), TAM, fp);
    while(!feof(fp)){
		fscanf(fp,"%s %c %d %[^\n]s",cartas[i].face, &cartas[i].naipe, &cartas[i].valor , cartas[i].nome);
		i++;
    }
    
	for(int j = 0; j < 1; j++){
		printf("%s %c %d %s\n",cartas[j].face, cartas[j].naipe, cartas[j].valor , cartas[j].nome);
	}
/*
    srand(time(NULL));
      do{
        printf("---- Entre com um numero ----\n1 - Gera uma carta aleatória\n0 - Finaliza o programa\n");
        scanf("%d", &n);
        switch(n){
            case 1:
                printf("------------------------------------------------------------------------\n ");
                int aleat = (rand() % TAM);
                printf("CARTAS SORTEADA: Face:%s Naipe:%c Valor:%d Nome:%s\n", cartas[aleat].face,cartas[aleat].naipe,cartas[aleat].valor,cartas[aleat].nome);
                break;
            case 0:
                break;
            default:  
            printf("Numero inválido\n1 - Gera uma carta aleatória\n0 - Finaliza o programa\n");
            scanf("%d", &n);
        }

        
       
     }while(n!=0);
        // for(int i = 0; i < 52; i++){
        //     printf("%s %c %d %s\n", cartas[i].face,cartas[i].naipe,cartas[i].valor,cartas[i].nome );
        // }
*/
    fclose(fp);
}
