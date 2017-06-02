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

void criarTabelaBanco()
{
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

}

void menuEntrada();
void menuPrincipal();
void telaGerenciamento();
void telaTurmas();

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
    int IDTURMA,IDADE,MATRICULA;
    char voltar;
    char NOME[50],EMAIL[100];
    char prt1[200],frase2[200];

    system("cls");

    cout<<"Número da turma do novo aluno(Digite 0 para voltar):";
    cin>>IDTURMA;

    if(IDTURMA==0)
        telaGerenciamento();

    system("cls");

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

backInseridoSucesso:
    system("cls");

    cout<<"Aluno inserido com sucesso."\
        "\n1-Inserir outro aluno"\
        "\n2-Voltar ao menu de gerenciamento das turmas";
    cin>>voltar;

    switch(voltar)
    {
    case '1':
        inserirAluno();
        break;
    case '2':
        telaGerenciamento();
        break;
    default:
        goto backInseridoSucesso;
    }
}

void deletarTurma()
{
    char *sql;
    char frase[150];
    int NUMERO;

    system("cls");

    sql = (char *) "SELECT disciplina, numero, id from TURMAS";
    exec(sql);

    cout<<"Digite o numero da turma que deseja excluir (Digite 0 para voltar):";
    cin>>NUMERO;

    if(NUMERO==0)
        telaGerenciamento();

    sprintf(frase,"DELETE from TURMAS where NUMERO=%d;",NUMERO);
    sql=(char *)frase;
    exec(sql);

    sprintf(frase,"DELETE from ALUNOS where IDTURMA=%d;",NUMERO);
    sql=(char *)frase;
    exec(sql);

}

void deletarAluno()
{
    int numero, id;
    char voltar;
    char *sql;
    char frase[50],str[100];

    system("cls");

    sql = (char *) "SELECT disciplina, numero, id from TURMAS";
    exec(sql);

    cout<<"Digite o numero da turma da qual deseja remover o aluno (Digite 0 para voltar):";
    cin>>numero;

    if(numero==0)
        telaGerenciamento();

    system("cls");

    sprintf(str, "SELECT nome,id,matricula from ALUNOS where IDTURMA=%d",numero);
    sql = (char *)str;
    exec(sql);

    cout<<"\nDigite o ID do aluno que deseja remover:";
    cin>>id;

    sprintf(frase,"DELETE from ALUNOS where ID=%d;",id);
    sql=(char *)frase;
    exec(sql);

    sprintf(frase, "UPDATE TURMAS set QUANTALUNOS = (QUANTALUNOS-1) where NUMERO=%d;",numero);
    sql = (char *) frase;
    exec(sql);

backRemovidoSucesso:
    system("cls");

    cout<<"Aluno removido com sucesso."\
        "\n1-Remover outro aluno"\
        "\n2-Voltar ao menu de gerenciamento das turmas";
    cin>>voltar;

    switch(voltar)
    {
    case '1':
        deletarAluno();
        break;
    case '2':
        telaGerenciamento();
        break;
    default:
        goto backRemovidoSucesso;
    }
}

void atualizarNotas()
{
    char *sql;
    char voltar;
    char frase[50],str[100];
    int numero,idaluno, unidade;
    float nota;

    system("cls");

    sql = (char *) "SELECT disciplina, numero, id from TURMAS";
    exec(sql);

    cout<<"Digite o numero da turma que deseja acessar (Digite 0 para voltar):";
    cin>>numero;

    if(numero==0)
        telaGerenciamento();

    system("cls");

    sprintf(str, "SELECT nome,id,matricula,nota1,nota2,nota3,media from ALUNOS where IDTURMA=%d",numero);
    sql = (char *)str;
    exec(sql);

    cout<<"Digite o ID do aluno que deseja alterar as notas:";
    cin>>idaluno;

    cout<<"Digite a unidade (1,2 ou 3) da qual deseja alterar a nota:";
    cin>>unidade;

    cout<<"Digite a nova nota:";
    cin>>nota;

    sprintf(frase,"UPDATE ALUNOS set NOTA%d=%f  where ID=%d; \n SELECT * from ALUNOS",unidade,nota,idaluno);
    sql=(char*)frase;
    exec(sql);

    sprintf(frase,"UPDATE ALUNOS set MEDIA=((NOTA1+NOTA2+NOTA3)/3); \n SELECT * from ALUNOS",unidade,nota,idaluno);
    sql=(char*)frase;
    exec(sql);

backNotaSucesso:
    system("cls");

    cout<<"Nota alterada com sucesso."\
        "\n1-Alterar outra nota"\
        "\n2-Voltar ao menu de gerenciamento das turmas";
    cin>>voltar;

    switch(voltar)
    {
    case '1':
        atualizarNotas();
        break;
    case '2':
        telaGerenciamento();
        break;
    default:
        goto backNotaSucesso;
    }
}

void inserirTurma()
{
    char *sql;
    char frase[200];
    char DISCIPLINA[100];
    int NUMERO;

backDisciplina:

    system("cls");

    cout<<"Digite o nome da disciplina da nova turma (Digite 0 para voltar):";
    cin.ignore();
    cin.getline(DISCIPLINA,100);

    if(DISCIPLINA[0]=='0' && DISCIPLINA[1]=='\0')
    {
        telaGerenciamento();
    }

    cout<<"Digite o numero da turma (Digite 0 para voltar):";
    cin>>NUMERO;

    if(NUMERO==0)
    {
        goto backDisciplina;
    }

    sprintf(frase,"INSERT INTO TURMAS(DISCIPLINA,NUMERO,QUANTALUNOS)\nVALUES('%s',%d,0);",DISCIPLINA,NUMERO);

    sql = (char *)frase;
    exec(sql);
}

void telaAlunoPessoal(int IDALUNO)
{

    char *sql;
    char voltar;
    char idA[4];

    sprintf(idA,"%d",IDALUNO);

    system("cls");

    char frase[500]="SELECT nome,matricula,idade,email,nota1,nota2,nota3,media from ALUNOS where ID=";
    sql= (char*)strcat(frase, idA);
    exec(sql);

    cout<<"\nDigite 0 para voltar pra tela de turmas:";
    cin>>voltar;

    if(voltar=='0')
        telaTurmas();
    else
        telaAlunoPessoal(IDALUNO);

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

    cout<<"\nDigite o ID do aluno que deseja vizualizar (Digite 0 para voltar):";
    cin>>ID;

    if(ID==0)
        telaTurmas();
    else
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

    cout<<"\nDigite o ID da turma que deseja acessar (Digite 0 para voltar)";
    cin>>ID;

    if(ID==0)
        menuPrincipal();
    else
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

    switch(opcaoGerenciamento)
    {

    case '1':

        inserirTurma();

        break;

    case '2':

        deletarTurma();

        break;

    case '3':

        inserirAluno();

        break;

    case '4':

        deletarAluno();

        break;

    case '5':

        atualizarNotas();

        break;

    case '6':

        menuPrincipal();

        break;
    default:

        telaGerenciamento();

        break;
    }
}

//Menu
void menuPrincipal()
{
    system("cls");
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
        menuEntrada();
        break;

    default:
        menuPrincipal();

    }


}

//Menu
void menuEntrada()
{
    system("cls");

    char opcaoEntrada;



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
        menuEntrada();

    }
}

int main()
{
    connect("test.db");

    criarTabelaBanco();

    menuEntrada();

    return 0;
}
