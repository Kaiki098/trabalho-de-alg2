#include<stdio.h>
#include<stdlib.h>
#include<locale.h>//biblioteca para localização em PT-BR
#include<string.h>
#include<Windows.h>//biblioteca da função Sleep

//Cores usadas no programa
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\e[0;93m"
#define ANSI_COLOR_CIAN "\e[1;96m"
#define ANSI_COLOR_GREEN  "\e[0;92m"
#define ANSI_COLOR_RESET  "\e[0m"

FILE *Id_Arquivo_Candidatos;
FILE *Id_Arquivo_Eleitores;

struct Candidato{
    int numero_candidato;  //codigo do candidato
    char nome[50]; //informaçoes pessoais
    char sexo[15];
    int idade;
    int flag;// variavel para exclusão lógica
};

struct Eleitor{
    int titulo_eleitor; //codigo do eleitor
    char nome[50];  //informações pessoais
    char sexo[15];
    int idade;
    int intencao_de_voto; //relação com o candidato
    int flag;// variavel para exclusão lógica
};

//CRUD Candidato

//Criação
/*Recebe uma struct candidatos e a armazena com flag = 1 para inclusão/exclusão lógica*/
void adicionar_candidato(struct Candidato candidato){

    if((Id_Arquivo_Candidatos = fopen("candidatos.dat", "a+b")) == NULL){
        printf("Erro ao abrir arquivo binário dos candidatos para gravação!\n");
    }

    candidato.flag = 1;// variavel para inclusão/exclusão lógica

    fwrite(&candidato, sizeof(struct Candidato), 1, Id_Arquivo_Candidatos);

    fclose(Id_Arquivo_Candidatos);
}

//Leitura
/*Le struct por struct no arquivo e imprime */
void exibir_candidatos(){

    if((Id_Arquivo_Candidatos = fopen("candidatos.dat", "r")) == NULL){
        printf("Erro ao abrir arquivo binário dos candidatos para leitura!\n");
    }

    rewind(Id_Arquivo_Candidatos);

    struct Candidato candidato;

    while(!feof(Id_Arquivo_Candidatos)){
        fread(&candidato, sizeof(struct Candidato), 1, Id_Arquivo_Candidatos);

        if(ferror(Id_Arquivo_Candidatos)){
            printf("Problema na leitura do arquivo binário!\n");
        }
        else if(!feof(Id_Arquivo_Candidatos) && candidato.flag == 1){
            printf("Numero do candidato: %d\n", candidato.numero_candidato);
            printf("Nome: %s\n", candidato.nome);
            printf("Sexo: %s\n", candidato.sexo);
            printf("Idade: %d\n\n", candidato.idade);
        }

    }
    fclose(Id_Arquivo_Candidatos);

}

//Atualização
/*Encontra o candidato pelo numero_candidato e o sobrescreve */
void atualizar_candidato(struct Candidato candidatoAtualizado){
    if((Id_Arquivo_Candidatos = fopen("candidatos.dat", "r+b")) == NULL){
        printf("Erro ao abrir arquivo binário dos eleitores!\n");
    }

    rewind(Id_Arquivo_Candidatos);

    struct Candidato candidato;


    int i;
    printf("Atualizando");// animação de atualização
    for(i = 0; i < 3; i++){
        printf(".");
        Sleep(500); // usa a biblioteca Windows.h
    }

    int cont = 0;

    while(!feof(Id_Arquivo_Candidatos)){
        fread(&candidato, sizeof(struct Candidato), 1, Id_Arquivo_Candidatos);

        if(ferror(Id_Arquivo_Candidatos)){
            printf("\nErro na leitura do arquivo!\n");
        }
        else if((!feof(Id_Arquivo_Candidatos)) && (candidato.numero_candidato == candidatoAtualizado.numero_candidato) && (candidato.flag == 1)){

            fseek(Id_Arquivo_Candidatos, sizeof(struct Candidato)*cont, SEEK_SET);

            candidatoAtualizado.flag = 1;

            fwrite(&candidatoAtualizado, sizeof(struct Candidato), 1, Id_Arquivo_Candidatos);

            fseek(Id_Arquivo_Candidatos, 0, SEEK_END);

            printf("\nCandidato Atualizado!\n");

            break;
        }
        else if(feof(Id_Arquivo_Candidatos)){
            printf("\nCandidato não encontrado!\n");
        }
        cont++;
    }

    fclose(Id_Arquivo_Candidatos);
}

//Exclusão
/*Encontra o candidato pelo numero_candidato e sobrescreve com a variável flag = 0*/
void excluir_candidato(int numero_candidato){
    if((Id_Arquivo_Candidatos = fopen("candidatos.dat", "r+b")) == NULL){
        printf("Erro ao abrir arquivo binário dos eleitores!\n");
    }

    struct Candidato candidato;

    rewind(Id_Arquivo_Candidatos);

    int cont = 0;

    int i;
    printf("Procurando");// animação de procura
    for(i = 0; i < 3; i++){
        printf(".");
        Sleep(500); // usa a biblioteca Windows.h
    }

    while(!feof(Id_Arquivo_Candidatos)){

        fread(&candidato, sizeof(struct Candidato), 1, Id_Arquivo_Candidatos);

        if(ferror(Id_Arquivo_Candidatos)){
            printf("Erro na leitura do arquivo!\n");
        }else if(!feof(Id_Arquivo_Candidatos) && candidato.flag == 1 && candidato.numero_candidato == numero_candidato){
            candidato.flag = 0;

            fseek(Id_Arquivo_Candidatos, sizeof(struct Candidato) * cont, SEEK_SET);

            fwrite(&candidato, sizeof(struct Candidato), 1, Id_Arquivo_Candidatos);

            fseek(Id_Arquivo_Candidatos, 0, SEEK_END);

            printf("\nCandidato excluido!\n");

            break;
        }
        else if(feof(Id_Arquivo_Candidatos)){
            printf("\nCandidato não encontrado!\n");
        }
        cont++;
    }

    fclose(Id_Arquivo_Candidatos);
}

//CRUD Eleitor

//Criação
/*Recebe uma struct eleitor e a armazena com flag = 1 para inclusão/exclusão lógica e a intencao_de_voto = 0*/
void adicionar_eleitor(struct Eleitor eleitor){

    if((Id_Arquivo_Eleitores = fopen("eleitor.dat", "a+b")) == NULL){
        printf("Erro ao abrir arquivo binário dos eleitores para gravação!");
    }

    eleitor.flag = 1;// variavel para inclusão/exclusão lógica
	eleitor.intencao_de_voto = 0;

    fwrite(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

    fclose(Id_Arquivo_Eleitores);

}

//Leitura
/*Le struct por struct no arquivo e imprime */
void exibir_eleitores(){

    if((Id_Arquivo_Eleitores = fopen("eleitor.dat", "r")) == NULL){
        printf("Erro ao abrir arquivo binário dos eleitores para leitura!\n");
    }

    rewind(Id_Arquivo_Eleitores);

    struct Eleitor eleitor;

    while(!feof(Id_Arquivo_Eleitores)){
        fread(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

        if(ferror(Id_Arquivo_Eleitores)){
            printf("Problema na leitura do arquivo binário!\n");
        }
        else if(!feof(Id_Arquivo_Eleitores) && eleitor.flag == 1){
            printf("Titulo do Eleitor: %d\n", eleitor.titulo_eleitor);
            printf("Nome: %s\n", eleitor.nome);
            printf("Sexo: %s\n", eleitor.sexo);
            printf("Idade: %d\n\n", eleitor.idade);
        }

    }
    fclose(Id_Arquivo_Eleitores);

}

//Atualização
/*Encontra o candidato pelo numero_candidato e o sobrescreve */
void atualizar_eleitor(struct Eleitor eleitorAtualizado){
    if((Id_Arquivo_Eleitores = fopen("eleitor.dat", "r+b")) == NULL){
        printf("Erro ao abrir arquivo binário dos eleitores!\n");
    }

    rewind(Id_Arquivo_Eleitores);

    struct Eleitor eleitor;


    int i;
    printf("Atualizando");// animação de atualização
    for(i = 0; i < 3; i++){
        printf(".");
        Sleep(500);// usa a biblioteca Windows.h
    }

    int cont = 0;

    while(!feof(Id_Arquivo_Eleitores)){
        fread(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

        if(ferror(Id_Arquivo_Eleitores)){
            printf("\nErro na leitura do arquivo!\n");
        }
        else if((!feof(Id_Arquivo_Eleitores)) && (eleitor.titulo_eleitor == eleitorAtualizado.titulo_eleitor) && (eleitor.flag == 1)){

            fseek(Id_Arquivo_Eleitores, sizeof(struct Eleitor)*cont, SEEK_SET);

            eleitorAtualizado.flag = 1;

            fwrite(&eleitorAtualizado, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

            fseek(Id_Arquivo_Eleitores, 0, SEEK_END);

            printf("\nEleitor Atualizado!\n");

            break;
        }
        else if(feof(Id_Arquivo_Eleitores)){
            printf("\nEleitor não encontrado!\n");
        }
        cont++;
    }

    fclose(Id_Arquivo_Eleitores);
}

//Exclusão
/*Encontra o candidato pelo numero_candidato e sobrescreve com a variável flag = 0*/
void excluir_eleitor(int titulo_eleitor){
    if((Id_Arquivo_Eleitores = fopen("eleitor.dat", "r+b")) == NULL){
        printf("Erro ao abrir arquivo binário dos eleitores!\n");
    }

    struct Eleitor eleitor;

    rewind(Id_Arquivo_Eleitores);

    int cont = 0;

    int i;
    printf("Procurando");// animação de procura
    for(i = 0; i < 3; i++){
        printf(".");
        Sleep(500); // usa a biblioteca Windows.h
    }

    while(!feof(Id_Arquivo_Eleitores)){

        fread(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

        if(ferror(Id_Arquivo_Eleitores)){
            printf("Erro na leitura do arquivo!\n");
        }else if(!feof(Id_Arquivo_Eleitores) && eleitor.flag == 1 && eleitor.titulo_eleitor == titulo_eleitor){
            eleitor.flag = 0;

            fseek(Id_Arquivo_Eleitores, sizeof(struct Eleitor) * cont, SEEK_SET);

            fwrite(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

            fseek(Id_Arquivo_Eleitores, 0, SEEK_END);

            printf("\nEleitor excluido!\n");

            break;
        }
        else if(feof(Id_Arquivo_Eleitores)){
            printf("\nEleitor não encontrado!\n");
        }
        cont++;
    }

    fclose(Id_Arquivo_Eleitores);
}

//Voto do eleitor
/*Encontra o candidato pelo titulo informado e sobrescreve salvando a intencao de voto informada*/
void votar(int titulo_eleitor, int intencao_de_voto){
	if((Id_Arquivo_Eleitores = fopen("eleitor.dat", "r+b")) == NULL){
		printf("Erro na abertura do arquivo eleitor!\n");
	}

	struct Eleitor eleitor;

	int cont = 0;

	while(!feof(Id_Arquivo_Eleitores)){//Procura o eleitor e grava sua intenção de voto
		fread(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

		if(ferror(Id_Arquivo_Eleitores)){

			printf("Erro na leitura dos arquivo eleitores!\n");

		}else if(!feof(Id_Arquivo_Eleitores) && eleitor.titulo_eleitor == titulo_eleitor && eleitor.flag == 1){

			printf("Eleitor encontrado!\n");
			printf("\nTitulo do Eleitor: %d\n", eleitor.titulo_eleitor);
            printf("Nome: %s\n", eleitor.nome);
            printf("Sexo: %s\n", eleitor.sexo);
            printf("Idade: %d\n", eleitor.idade);

	   		eleitor.intencao_de_voto = intencao_de_voto;

			fseek(Id_Arquivo_Eleitores, sizeof(struct Eleitor)*cont, SEEK_SET);

			fwrite(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

			fseek(Id_Arquivo_Eleitores, 0, SEEK_END);

			printf("\nVoto computado!\n");
			break;

		}else if(feof(Id_Arquivo_Eleitores)){
			printf("Eleitor NÃO encontrado!\n");
		}

		cont++;
	}

	fclose(Id_Arquivo_Eleitores);

}

//Exibi resultado da pesquisa
/*Para cada candidato procura cada eleitor com a intencao_de_voto igual ao numero_do_candidato, contando quantos votos e exibi os votos*/
void exibir_resultado(){

    if((Id_Arquivo_Candidatos = fopen("candidatos.dat", "rb")) == NULL){
       printf("Erro ao abrir arquivo binário dos candidatos!\n");
    }

    int votos = 0;

    struct Candidato candidato;

    while(!feof(Id_Arquivo_Candidatos)){// acessa o campo votos de cada candidato e os exibi
        votos = 0;

        fread(&candidato, sizeof(struct Candidato),1 , Id_Arquivo_Candidatos);

        if(ferror(Id_Arquivo_Candidatos)){

            printf("Erro ao abrir arquivo binário dos candidatos para leitura!\n");

        }
        else if(!feof(Id_Arquivo_Candidatos) && candidato.flag == 1){

            if((Id_Arquivo_Eleitores = fopen("eleitor.dat", "rb")) == NULL){
                printf("Erro na abertura do arquivo eleitores!\n");
            }

            struct Eleitor eleitor;

            while(!feof(Id_Arquivo_Eleitores)){
                fread(&eleitor, sizeof(struct Eleitor), 1, Id_Arquivo_Eleitores);

                if(ferror(Id_Arquivo_Eleitores)){
                    printf("Erro na leitura do arquivo eleitores!\n");
                }
                else if(!feof(Id_Arquivo_Eleitores) && eleitor.intencao_de_voto == candidato.numero_candidato && eleitor.flag == 1){
                    votos++;
                }
            }

            printf("Candidato: %s\n", candidato.nome);
            printf("Votos: %d\n\n", votos);
            fclose(Id_Arquivo_Eleitores);

        }

    }
    fclose(Id_Arquivo_Candidatos);

}

int main(){

    setlocale(LC_ALL, "Portuguese");
    int opc_menu_geral, opc;
    struct Candidato candidato;
    struct Eleitor eleitor;

    do{//Menu Geral de Candidato e Eleitor

        system("cls");
        printf(ANSI_COLOR_RED "0- Sair\n");
        printf(ANSI_COLOR_CIAN "1- Candidato\n");
        printf(ANSI_COLOR_YELLOW "2- Eleitor\n");
        printf(ANSI_COLOR_GREEN "3- Exibir resultado da pesquisa\n");
        scanf("%d", &opc_menu_geral);

        switch(opc_menu_geral){

            case 0:
                break;

            case 1://Menu Candidato
                system("cls");
                printf(ANSI_COLOR_CIAN "0- Voltar\n");
                printf("1- Adicionar Candidato\n");
                printf("2- Exibir Candidatos\n");
                printf("3- Atualizar Candidato\n");
                printf("4- Excluir Candidato\n");
                scanf("%d", &opc);

                switch(opc){
                    case 0:
                        break;

                    case 1:
                        system("cls");
                        printf("Cadastro do Candidato\n");

                        printf("Digite numero de identificação do candidato: ");
                        scanf("%d", &candidato.numero_candidato);
                        fflush(stdin);

                        printf("Digite o nome do candidato: ");
                        fgets(candidato.nome, 50, stdin);
                        candidato.nome[strlen(candidato.nome) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite o sexo do candidato: ");
                        fgets(candidato.sexo, 50, stdin);
                        candidato.sexo[strlen(candidato.sexo) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite a idade do candidato: ");
                        scanf("%d", &candidato.idade);
                        fflush(stdin);

                        adicionar_candidato(candidato);
                        printf("Candidato Adicionado!\n");
                        system("pause");;
                        break;

                    case 2:
                        system("cls");
                        exibir_candidatos();
                        system("pause");
                        break;

                    case 3:
                        system("cls");
                        printf("Atualização do candidato\n");

                        printf("Digite numero de identificação do candidato a ser alterado: ");
                        scanf("%d", &candidato.numero_candidato);
                        fflush(stdin);

                        printf("Digite o nome do candidato: ");
                        fgets(candidato.nome, 50, stdin);
                        candidato.nome[strlen(candidato.nome) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite o sexo do candidato: ");
                        fgets(candidato.sexo, 50, stdin);
                        candidato.sexo[strlen(candidato.sexo) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite a idade do candidato: ");
                        scanf("%d", &candidato.idade);
                        fflush(stdin);

                        atualizar_candidato(candidato);
                        system("pause");
                        break;

                    case 4:
                        system("cls");
                        int numero_candidato;
                        printf("Digite o número do candidato: ");
                        scanf("%d", &numero_candidato);

                        excluir_candidato(numero_candidato);
                        system("pause");
                        break;

                    default:
                        system("cls");
                        printf("Opção inválida!\n\a");
                        system("pause");
                        break;

                }
                break;

            case 2://Menu Eleitor
                system("cls");
                printf(ANSI_COLOR_YELLOW "0- Sair\n");
                printf("1- Adicionar eleitor\n");
                printf("2- Exibir eleitor\n");
                printf("3- Atualizar eleitor\n");
                printf("4- Excluir eleitor\n");
                printf("5- Votar\n");
                scanf("%d", &opc );

                switch(opc){
                    case 0:
                        break;

                    case 1:
                        system("cls");
                        fflush(stdin);
                        printf("Cadastro do Eleitor\n");

                        printf("Digite o Titulo de eleitor: ");
                        scanf("%d", &eleitor.titulo_eleitor);
                        fflush(stdin);

                        printf("Digite o nome do eleitor: ");
                        fgets(eleitor.nome, 50, stdin);
                        eleitor.nome[strlen(eleitor.nome) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite o sexo do candidato: ");
                        fgets(eleitor.sexo, 50, stdin);
                        eleitor.sexo[strlen(eleitor.sexo) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite a idade: ");
                        scanf("%d", &eleitor.idade);
                        fflush(stdin);

                        adicionar_eleitor(eleitor);
                        break;

                    case 2:
                     	system("cls");
                        exibir_eleitores();
                        system("pause");
                        break;

                    case 3:
                        system("cls");
                        printf("Atualização do eleitor\n");

                        printf("Digite o titulo do eleitor a ser alterado: ");
                        scanf("%d", &eleitor.titulo_eleitor);
                        fflush(stdin);

                        printf("Digite o nome do eleitor: ");
                        fgets(eleitor.nome, 50, stdin);
                        eleitor.nome[strlen(eleitor.nome) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite o sexo do eleitor: ");
                        fgets(eleitor.sexo, 50, stdin);
                        eleitor.sexo[strlen(eleitor.sexo) - 1] = '\0';
                        fflush(stdin);

                        printf("Digite a idade do eleitor: ");
                        scanf("%d", &eleitor.idade);
                        fflush(stdin);

                        atualizar_eleitor(eleitor);
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        int titulo_eleitor;
                        printf("Digite o Titulo de eleitor: ");
                        scanf("%d", &titulo_eleitor);

                        excluir_eleitor(titulo_eleitor);
                        system("pause");
                        break;

                    case 5:
                        system("cls");
                    	printf("Digite seu titulo de eleitor: ");
                    	int intencao_de_voto;
                    	scanf("%d", &titulo_eleitor);

                    	printf("Digite sua intenção de voto: ");
                    	scanf("%d", &intencao_de_voto);

                    	votar(titulo_eleitor, intencao_de_voto);

                    	system("pause");
                    	break;

                    default:
                        system("cls");
                        printf("Opção inválida!\n\a");
                        system("pause");
                        break;
                }
                break;

            case 3: //Exibir resultado da pesquisa
                system("cls");
                exibir_resultado();
                system("pause");
                break;


            default:
                system("cls");
                printf("Opção inválida!\n\a");
                system("pause");
                break;

        }

    }while(opc_menu_geral != 0);

    return 0;
}
