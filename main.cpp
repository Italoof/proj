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
        cout<<azColName[i]<<" "<<argv[i]<<endl;
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

void inserirAluno()
{
    char *sql;
    int IDTURMA;
    int IDADE,MATRICULA;
    char NOME[50],EMAIL[100];
    char prt1[200],frase2[200];

    cout<<"Número da turma do novo aluno:";
    cin>>IDTURMA;

    cout<<"Nome do aluno:";
    cin.ignore();
    cin.getline(NOME, 50);

    cout<<"Idade do aluno:";
    cin>>IDADE;

    cout<<"Matricula do aluno:";
    cin>>MATRICULA;

    cout<<"Email do aluno:";
    cin.ignore();
    cin.getline(EMAIL,100);

    sprintf(prt1,"INSERT INTO ALUNOS(IDTURMA,NOME,IDADE,MATRICULA,EMAIL,NOTA1,NOTA2,NOTA3,MEDIA)\nVALUES (%d,'%s',%d,%d,'%s',0,0,0,0);",IDTURMA,NOME,IDADE,MATRICULA,EMAIL);

    sql = (char *)prt1;
    exec(sql);

    sprintf(frase2, "UPDATE TURMAS set QUANTALUNOS = (QUANTALUNOS+1) where NUMERO=%d;",IDTURMA );
    sql = (char *) frase2;
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
void inserirTurma()
{
    char *sql;
    char frase[200];
    char DISCIPLINA[100];
    int NUMERO;

    system("cls");

    cout<<"Digite o nome da disciplina da nova turma:";
    cin.ignore();
    cin.getline(DISCIPLINA,100);

    cout<<"Digite o numero da turma:";
    cin>>NUMERO;

    sprintf(frase,"INSERT INTO TURMAS(DISCIPLINA,NUMERO,QUANTALUNOS)\nVALUES('%s',%d,0);",DISCIPLINA,NUMERO);

    sql = (char *)frase;
    exec(sql);
}

void telaAlunoPessoal(int IDALUNO)
{

    char *sql;
    char idA[4];

    sprintf(idA,"%d",IDALUNO);

    system("cls");

    char frase[500]="SELECT nome,matricula,idade,email,nota1,nota2,nota3,media from ALUNOS where ID=";
    sql= (char*)strcat(frase, idA);
    exec(sql);

}

void telaAlunoGeral(int IDTURMA)
{

    char *sql;
    char str[150];
    int ID;

    system("cls");

    sprintf(str, "SELECT nome,id,matricula from ALUNOS where IDTURMA=%d",IDTURMA );
    sql = (char *)str;
    exec(sql);

    cout<<"\nDigite o ID do aluno que deseja vizualizar:";
    cin>>ID;

    telaAlunoPessoal(ID);
}
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

    telaAlunoGeral(ID);
}
//Menu
void telaGerenciamento()
{

    char opcaoGerenciamento;

    system("cls");

    cout<<"AS OPCOES DESSE MENU AINDA ESTAO EM DESENVOLVIMENTO (Digite 6 para voltar) "<<endl<<endl
        <<"1-Adicionar turmas                                                         "<<endl
        <<"2-Remover turmas                                                           "<<endl
        <<"3-Adicionar alunos a uma turma                                             "<<endl
        <<"4-Remover alunos de uma turma                                              "<<endl
        <<"5-Gerenciar notas                                                          "<<endl
        <<"6-Voltar                                                                   "<<endl;

    cin>>opcaoGerenciamento;

    switch(opcaoGerenciamento){

        case '1':

            inserirTurma();

        break;

        case '3':

            inserirAluno();

        break;
    }
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

    char IDTURMA[2]="2",NOME[30]="Jose",IDADE[3]="18",MATRICULA[11]="2016011170";
    char EMAIL[30]="italo.of@email.com";
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

 //   exec(sql);

    menuEntrada();

    return 0;
}
