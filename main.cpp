#include <iostream>
#include <cstdlib>
#include <string.h>
#include <sqlite3.h>
#include <stdio.h>

//A SENHA INICIAL É 123

using namespace std;

//Variáveis Globais do Banco de Dados SQL
sqlite3 *db;
char *zErrMsg = 0;
int rc;

// Funções Pricipais do Banco de Dados SQL (Início)
void connect(const char *db_file)
{
    rc = sqlite3_open(db_file, &db);

    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++)
    {
        cout<<"\t"<<azColName[i]<<" \t";
    }
    cout<<endl;

    for(i=0; i<argc; i++)
    {
        cout<<"\t"<<argv[i]<<" ";
    }
    cout<<endl;

    return 0;
}

void exec(char *sql)
{
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Instruction executed successfully\n");
    }
}

// Funções Pricipais do Banco de Dados SQL (Fim)

// Função que compara que verifica se duas strings são iguais
bool stringIgual(char s1[], char s2[])
{

    for (int i=0; s1[i]!='\0' || s2[i]!='\0'; i++)
    {
        if (s1[i]!=s2[i])
            return false;
    }

    return true;
}

// Função com senha para acessar o programa
void senhaAcesso()
{

    char senha[11];

    system("cls");

    cin.ignore();
    cout<<"Senha de acesso:";
    cin.getline(senha,11);

    while(!stringIgual(senha,"123"))
    {
        system("cls");

        cout<< "Senha inválida. Tente novamente:";
        cin.getline(senha,11);
    }

    system("cls");

}

void inserirAluno(int idAluno)
{
    idAluno++;

    char *sql;
    char idt[3];

    sprintf(idt,"%d",idAluno);

    char IDTURMA[2]="1",NOME[30]="lucas",IDADE[3]="20",MATRICULA[11]="2016014950";
    char EMAIL[30]="Lucas",NOTA1[5]="10",NOTA2[5]="10",NOTA3[5]="10",MEDIA[5]="10";
    char prt1[200]="INSERT INTO ALUNOS(ID,IDTURMA,NOME,IDADE,MATRICULA,EMAIL)\nVALUES (";
    strcat(prt1,idt);
    strcat(prt1,",");
    strcat(prt1,IDTURMA);
    strcat(prt1,",'");
    strcat(prt1,NOME);
    strcat(prt1,"',");
    strcat(prt1,IDADE);
    strcat(prt1,",");
    strcat(prt1,MATRICULA);
    strcat(prt1,",'");
    strcat(prt1,EMAIL);
    sql = (char *)strcat(prt1,"',0,0,0,0);");

    exec(sql);
}

/*void deletarTurma(char ID[])
{
    char frase[150]="DELETE from TURMAS where ID=";
    strcat(frase,ID);

    char frase[150]="DELETE from ALUNOS where IDTURMA=";
    strcat(frase,ID);

    sql=(char *)strcat(frase,";");
    exec(sql);
}
*/

/*void deletarAluno(char ID[])
{
    char frase[150]="DELETE from ALUNOS where ID=";
    strcat(frase,ID);
    sql=(char *)strcat(frase,";");
    exec(sql);
}
*/

/*void AtualizarAluno(char nota[], char valornota[], char Id[])
{

    char frase[30]="UPDATE ALUNOS set NOTA" ;
    strcat(frase,nota);
    strcat(frase,"= ");
    strcat(frase,valornota);
    char frase2[10]=" where ID=";
    char frase3[20]="; \n SELECT * from ALUNOS";
    strcat(frase,frase2);
    sql=(char*)strcat(frase,frase3);
    exec(sql);
}*/

/*void AtualizarTurma(char Id[], char QuantidadeAluno[])
{
    char frase[31]="UPDATE TURMAS set QUANTALUNOS=";
    char frase2[11]=" where ID=";
    strcat(frase,QuantidadeAluno);
    strcat(frase,frase2);
    strcat(frase,Id);
    char frase3[30]="; \n SELECT * from TURMAS";
    sql=(char*) strcat(frase,frase3);
    exec(sql);
}
*/
/*void inserirTurma(char DISCIPLINA[], char QUANTALUNOS[],int idTurma)
{
    idTurma++;
    char idt[3];

    char prt1[200]="INSERT INTO TURMAS(ID,DISCIPLINA,QUANTALUNOS)\nVALUES(";
    sprintf(idt,"%d",idTurma);
    strcat(prt1,idt);
    strcat(prt1,",'");
    strcat(prt1,DISCIPLINA);
    strcat(prt1,"',");
    strcat(prt1,QUANTALUNOS);
    sql = (char *)strcat(prt1,");");
    exec(sql);
}
*/

//Menu
void telaTurmas()
{
    char *sql;
    int ID;

    system("cls");

    sql = (char *) "SELECT disciplina, numero, id, quantalunos from TURMAS";
    exec(sql);

    cout<<"\nDigite o ID da turma que deseja acessar:";
    cin>>ID;

    system("cls");

    sql = (char *) "SELECT nome,matricula from ALUNOS";
    exec(sql);

}

//Menu
void telaGerenciamento()
{

    int opcaoGerenciamento;

    system("cls");

    cout<<"AS OPCOES DESSE MENU AINDA ESTAO EM DESENVOLVIMENTO (Digite 6 para voltar) "<<endl<<endl
        <<"1-Adicionar turmas                                                         "<<endl
        <<"2-Remover turmas                                                           "<<endl
        <<"3-Adicionar alunos a uma turma                                             "<<endl
        <<"4-Remover alunos de uma turma                                              "<<endl
        <<"5-Gerenciar notas                                                          "<<endl
        <<"6-Voltar                                                                   "<<endl;

    cin>>opcaoGerenciamento;


}

//Menu
void menuPrincipal()
{

    char opcaoPrincipal;

backPrincipal:

    cout<<"1- Acessar turmas                          "<<endl
        <<"2- Gerenciar turmas                        "<<endl
        <<"3- Pesquisar aluno(Funcao nao implementada)"<<endl
        <<"4 - Sair                                    "<<endl;

    cin>> opcaoPrincipal;

    switch(opcaoPrincipal)
    {

    case '1':

        telaTurmas();

        break;

    case '2':

        telaGerenciamento();

        break;

    case '3':

        break;

    case '4':

        break;

    default:

        goto backPrincipal;
    }


}

//Menu
void menuEntrada()
{

    char opcaoEntrada;

backEntrada:

    cout<<"           SEGT         "<<endl
        <<"                        "<<endl
        <<"    1- Entrar no Sistema"<<endl
        <<"    2- Sair             "<<endl;

    cin>>opcaoEntrada;

    switch(opcaoEntrada)
    {
    case '1':
        system("cls");

        //senhaAcesso();

        menuPrincipal();

    case '2':
        break;

    default:
        system("cls");
        goto backEntrada;
    }
}

int main()
{
    connect("test.db");

    char *sql;

    sql = (char *)"CREATE TABLE IF NOT EXISTS TURMAS("\
          "ID INTEGER PRIMARY KEY     AUTOINCREMENT,"\
          "DISCIPLINA           TEXT    NOT NULL,"\
          "NUMERO               INT     NOT NULL,"\
          "QUANTALUNOS            INT     NOT NULL);";

    exec(sql);

    sql = (char *)"CREATE TABLE IF NOT EXISTS ALUNOS("  \
          "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
          "IDTURMA        INT     NOT NULL,"\
          "NOME           TEXT    NOT NULL," \
          "IDADE          INT     NOT NULL," \
          "MATRICULA      INT     NOT NULL," \
          "EMAIL          CHAR(100)," \
          "NOTA1          REAL     NOT NULL,"\
          "NOTA2          REAL     NOT NULL,"\
          "NOTA3          REAL     NOT NULL,"\
          "MEDIA          REAL     NOT NULL);";
    exec(sql);

    //sql = (char *) "INSERT INTO TURMAS (DISCIPLINA, NUMERO, QUANTALUNOS) "  \
          "VALUES ('Linguagem de Programacao',1,100); ";

    //sql = (char *) "DELETE from TURMAS where ID=3; ";


    //exec(sql);

    char IDTURMA[2]="1",NOME[30]="lucas",IDADE[3]="20",MATRICULA[11]="2016014950";
    char EMAIL[30]="Lucas",NOTA1[5]="10",NOTA2[5]="10",NOTA3[5]="10",MEDIA[5]="10";
    char prt1[200]="INSERT INTO ALUNOS(IDTURMA,NOME,IDADE,MATRICULA,EMAIL,NOTA1,NOTA2,NOTA3,MEDIA)\nVALUES (";
    strcat(prt1,IDTURMA);
    strcat(prt1,",'");
    strcat(prt1,NOME);
    strcat(prt1,"',");
    strcat(prt1,IDADE);
    strcat(prt1,",");
    strcat(prt1,MATRICULA);
    strcat(prt1,",'");
    strcat(prt1,EMAIL);
    sql = (char *)strcat(prt1,"',0,0,0,0);");

    exec(sql);

    menuEntrada();

    return 0;
}
