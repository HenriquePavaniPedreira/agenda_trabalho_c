#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//Structs 
typedef struct{
    float a;
    float b;
    float c;
}Preferencias;

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    char nome[100];
    char uf[3];
    Data data_nascimento;
    Preferencias preferencia;
}Registro;



int abrir_arquivo_bin(FILE *arq, char nome_arq_bin[80]){
    //Funcao para abrir o arquivo solicitado
    arq = fopen(nome_arq_bin, "rb");
    if(arq != NULL){
        printf("\nArquivo %s aberto com sucesso!\n",nome_arq_bin);
        return 0;
    }else{
        printf("\nERRO: erro ao abrir o arquivo binário %s (verifique se o mesmo existe)\n", nome_arq_bin);
        exit(1);
    }
}
int criar_arquivo_bin(FILE *arq, char nome_arq_bin[80]){
    //Funcao que cria o arquivo binário
    arq = fopen(nome_arq_bin, "wb");
    if(arq != NULL){
        printf("\nArquivo binário %s criado com sucesso\n",nome_arq_bin);
        return 1;
    }else{
        printf("\nERRO: erro ao criar o arquivo binário %s\n", nome_arq_bin);
    }
}
int alocar_struct(int  *registro, int total_de_registros){//(*registro +1 )
    registro = malloc(sizeof(registro)*total_de_registros);




}
void printar_menu(void){
    printf("\n========================= 📜AGENDA INTELIGENTE: TRABALHO 2📜 =========================\n");
    printf("    ( 1 ) ->  Abrir arquivo binário já existente\n");//x
    printf("    ( 2 ) ->  Criar novo arquivo binário\n");//x
    printf("    ( 3 ) -> Cadastrar novo registro\n");//x
    printf("    ( 4 ) ->  Buscar registro🔎\n");//menu proprio
    printf("    ( 5 ) ->  Editar registro\n");
    printf("    ( 6 ) ->  Excluir registro\n");
    printf("    ( 7 ) ->  Ordenar registro\n");//Menu proprio
    printf("    ( 8 ) ->  Agrupar registros\n");
    printf("    ( 9 ) ->  Printar menu\n");//x
    printf("    (10 ) ->  Exportar arquivo\n");
    printf("    ( 0 ) ->  Sair\n");//x
    printf("\n=======================================================================================\n");

}
void cadastrar_registro(FILE*arq){
    if(arq==NULL){
        printf("O arquivo ainda nao foi aberto");
        exit(1);
    }
    Registro pessoa;
    printf("\nDigite o seu nome: ");
    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    printf("\nDigite o seu estado (UF): ");
    scanf("%s",pessoa.uf);
    printf("\nDigite o dia do seu nascimento: ");
    scanf("%d",&pessoa.data_nascimento.dia);
    printf("\nDigite mês do seu nascimento: ");
    scanf("%d",&pessoa.data_nascimento.mes);
    printf("\nDigite o ano do seu nascimento: ");
    scanf("%d",&pessoa.data_nascimento.ano);
    printf("\nDigite o seu grau de preferencia por a: ");
    scanf("%f",&pessoa.preferencia.a);
    printf("\nDigite o seu grau de preferencia por b: ");
    scanf("%f",&pessoa.preferencia.b);
    printf("\nDigite o seu grau de preferencia por c:");
    scanf("%f",&pessoa.preferencia.c);
    printf("\n------------------------------------\n");
    fwrite(&pessoa,sizeof(pessoa),1,arq);
    printf("Registro cadastrado!");
}
void printar_parametros(Registro *r,int index){
        printf("\n------------\n");
        printf("Nome: %s\n",r[index].nome);
        printf("Estado (UF): %s\n",r[index].uf);
        printf("Data de nascimento: %2d/%2d/%2d\n",r[index].data_nascimento.dia,r[index].data_nascimento.mes,r[index].data_nascimento.ano);
        printf("Preferencia por %f: ",r[index].preferencia.a);
        printf("Preferencia por %f: ",r[index].preferencia.b);
        printf("Preferencia por %f: ",r[index].preferencia.c);
} 
int buscar_por_nome(FILE *arq, char nome[80]){
    int count = 0; // contador de elementos (blocos de memeoria) no arquivo binário
    //descobrir o total de registros
    Registro *r = malloc(sizeof(Registro));
    if (r == NULL){
        printf("\nERRO: erro de mémoria (linha 125)");
        exit(1);
    }else{
        while(fread(r,sizeof(Registro),1,arq)){
            count++;
        }
        fread(r,sizeof(Registro),count,arq);
        for(int i = 0; i < count; i++){
            if(!strcmp(r[i].nome,nome)){
                printar_parametros(r,i);
            }
        }
    }
    return 0;
}
int buscar_por_nascimento(FILE *arq){
    int count = 0; // contador de elementos (blocos de memeoria) no arquivo binário
    //descobrir o total de registros
    int dia, mes, ano;
    printf("\nDigite o dia do nascimento: ");
    scanf("%d",&dia);
     printf("\nDigite o mes do nascimento: ");
    scanf("%d",&mes);
     printf("\nDigite o ano do nascimento: ");
    scanf("%d",&ano);
    Registro *r = malloc(sizeof(Registro));
    if (r == NULL){
        printf("\nERRO: erro de mémoria (linha 125)");
        exit(1);
    }else{
        while(fread(r,sizeof(Registro),1,arq)){
            count++;
        }
        fread(r,sizeof(Registro),count,arq);
        for(int i = 0; i < count; i++){
            if(r[i].data_nascimento.dia == dia && 
               r[i].data_nascimento.mes == mes && 
               r[i].data_nascimento.ano == ano 
            ){
                printar_parametros(r,i);
            }
        }
    }
    return 0;
}
void busca(FILE*arq){
    char nome_pesquisa[100];
    int op;
    printf("\n---------- 🔎BUSCA DE REGISTROS🔎 ----------\n");
    printf("    ( 1 ) -> Buscar por nome\n");
    printf("    ( 2 ) -> Busca por data de nascimento\n");
    printf("    ( 3 ) -> Busca por grupo\n");
    printf("    ( 0 ) -> Sair da busca\n\n");
    printf("Digite a opcao: ");
    scanf("%d",&op);
    switch (op)
    {
        case 1:
            printf("Digite o nome que deseja buscar: ");
            scanf("%s", nome_pesquisa);
            buscar_por_nome(arq,nome_pesquisa);
            break;
        case 2:
            buscar_por_nascimento(arq);
            break;
        case 3:
            //buscar_por_grupo()
            break;
        case 0:
            printf("\nSaindo da ferramenta de busca!\n");
        default:
            break;
    }
}

int main(){
    int op_main; // Opcão do menu na func main
    char nome_arq_bin[80];
    FILE *arq;
    printar_menu();
    do{
        printf("\n>> Digite a opcão: ");
        scanf("%d", &op_main);
        switch (op_main)
        {
        case 1:
            printf("Digite o nome do arquivo binário que deseja abrir: ");
            scanf("%s",nome_arq_bin);
            if(arq != NULL){
                printf("WARNING: Já existia um arquivo aberto, ele foi fechado");
                fclose(arq);
            }
            abrir_arquivo_bin(arq,nome_arq_bin);
            break;
        case 2:
            printf("Digite o nome do arquivo binário que deseja criar: ");
            scanf("%s",nome_arq_bin);
            criar_arquivo_bin(arq,nome_arq_bin);
            break;
        case 3:
            cadastrar_registro(arq);
            
            break;
        case 4:
            busca(arq);
            break;
        case 5:
            break;
        case 7:
            
            break;
        case 8:
            
            break;
        case 9:
            printar_menu();
            break;
        case 10:
            
            break;
        
        default:
            break;
        }
    }while(op_main !=0);
    return 0;
}
/*

 printf("\n========================= 📜AGENDA INTELIGENTE: TRABALHO 2📜 =========================\n");
    printf("    ( 1 ) .  Abrir arquivo binário já existente\n");//x
    printf("    ( 2 ) .  Criar novo arquivo binário\n");//x
    printf("    ( 3 ) .  Cadastrar novo registro\n");//x
    printf("    ( 4 ) .  Buscar registro🔎\n");//menu proprio
    printf("    ( 5 ) .  Editar registro\n");
    printf("    ( 6 ) .  Excluir registro\n");
    printf("    ( 7 ) .  Ordenar registro\n");//Menu proprio
    printf("    ( 8 ) .  Agrupar registros\n");
    printf("    ( 9 ) .  Printar menu\n");//x
    printf("    (10 ) .  Exportar arquivo\n");
    printf("    ( 0 ) .  Sair\n");//x
    printf("\n=======================================================================================\n"); printf("\n========================= 📜AGENDA INTELIGENTE: TRABALHO 2📜 =========================\n");
    printf("    ( 1 ) .  Abrir arquivo binário já existente\n");//x
    printf("    ( 2 ) .  Criar novo arquivo binário\n");//x
    printf("    ( 3 ) .  Cadastrar novo registro\n");//x
    printf("    ( 4 ) .  Buscar registro🔎\n");//menu proprio
    printf("    ( 5 ) .  Editar registro\n");
    printf("    ( 6 ) .  Excluir registro\n");
    printf("    ( 7 ) .  Ordenar registro\n");//Menu proprio
    printf("    ( 8 ) .  Agrupar registros\n");
    printf("    ( 9 ) .  Printar menu\n");//x
    printf("    (10 ) .  Exportar arquivo\n");
    printf("    ( 0 ) .  Sair\n");//x
    printf("\n=======================================================================================\n");

*/