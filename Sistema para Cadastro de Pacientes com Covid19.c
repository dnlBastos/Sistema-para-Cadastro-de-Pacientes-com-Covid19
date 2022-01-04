#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char user[31] = "admin"; //coloque aqui o nome de usuário desejado, podendo conter no máximo 30 caractéres.
char password[31] = "123"; //coloque aqui a senha desejada, podendo conter no máximo 30 caractéres.

FILE *arquivoPaciente;
FILE *arquivoRisco;

static int idade; //variável para fazer o calculo da idade do paciente.
int diaAtual, mesAtual, anoAtual; //variável para armazenar a data atual do sistema.

typedef struct {
    char nome[50], rua[50], bairro[50], cidade[50], estado[50], email[50];
    char cpf[15], cep[10], telefone[13];
    int diaDiagnostico, mesDiagnostico, anoDiagnostico,  diaNascimento, mesNascimento, anoNascimento, numeroCasa, idadePaciente;
    char diabetes[4], obesidade[4], hipertensao[4], tuberculose[4];
}dados_paciente;
dados_paciente paciente;


int main(void){
    int opcaoMenu; //variável para a manipulação do menu de opções.
    int permissaoEntrada = entradaSistema();

    time_t meuTempo;
    meuTempo = time(NULL);
    struct tm data = *localtime(&meuTempo);
    anoAtual = data.tm_year+1900;
    mesAtual = data.tm_mon+1;
    diaAtual = data.tm_mday;

    if (permissaoEntrada == 1){
        do{
            system("cls"); //limpa as mensagens da tela.
            printf("========================== Bem-Vindo ==========================\n\n");
            printf("======================= MENU PRINCIPAL ========================");
            printf("\n                       Data: %d/%d/%d\n\n\n", diaAtual, mesAtual, anoAtual);
            printf(" Digite o numero equivalente para a opcao que deseja acessar:\n 1 - Cadastrar paciente\n 2 - Listar todos os pacientes cadastrados\n 3 - Pesquisar paciente pelo CPF\n 4 - Deletar dados do pacinte pelo CPF\n 5 - Sair\n\n");
            fflush(stdin); //limpa o buffer do teclado, que pode conter alguma informação armazernada.
            scanf("%d", &opcaoMenu);
            switch(opcaoMenu){
                case 1:
                    cadastroPaciente();
                break;
                case 2:
                    listarPacientes();
                break;
                case 3:
                    pesquisarCpf();
                break;
                case 4:
                    deletarCadastro();
                break;
                case 5:
                    system("exit");
                break;
                default:
                    printf(" Opcao invalida\n\n");
                    system("pause");
                break;
            }
        }while(opcaoMenu!=5);
    }
    return 0;
}

int entradaSistema(){
    char usuarioPadrao[30], senhaPadrao[30];
    char login[30], senha[30];
    int retornoLogin, retornoSenha;
    int contaExistente;

    strcpy(usuarioPadrao, user);
    strcpy(senhaPadrao, password);

    do{
        printf(" Digite seu login: ");
        scanf("%s", login);
        printf(" Digite sua senha: ");
        scanf("%s", senha);
        retornoLogin = strcmp(usuarioPadrao, login);
        retornoSenha = strcmp(senhaPadrao, senha);

        if ((retornoLogin == 0) && (retornoSenha == 0)){
            contaExistente=1;
        }else{
            contaExistente=0;
            printf(" Login e/ou senha invalidos.\nTente novamente.\n");
        }
    }while(contaExistente==0);
    return contaExistente;
}

void cadastroPaciente(){
    int opcaoMenuCadastro;

    system("cls");
    do{
        printf("\n---------- Insira as informacoes do paciente ----------\n");

        printf("\n Nome: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente.nome);

        printf(" CPF (apenas numeros): ");
        fflush(stdin);
        scanf("%s", paciente.cpf);
        cpfPadronizador();

        printf(" Telefone: ");
        fflush(stdin);
        scanf("%12[^\n]", paciente.telefone);

        printf(" Rua: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente.rua);

        printf(" Numero da casa: ");
        fflush(stdin);
        scanf("%d", &paciente.numeroCasa);

        printf(" Bairro: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente.bairro);

        printf(" Cidade: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente.cidade);;

        printf(" Estado: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente.estado);

        printf(" CEP (apenas numeros): ");
        fflush(stdin);
        scanf("%9[^\n]", paciente.cep);
        cepPadronizador();

        printf(" Dia do nascimento: ");
        fflush(stdin);
        scanf("%2d", &paciente.diaNascimento);

        printf(" Mes do nascimento: ");
        fflush(stdin);
        scanf("%2d", &paciente.mesNascimento);

        printf(" Ano do nascimento: ");
        fflush(stdin);
        scanf("%4d", &paciente.anoNascimento);

        idade = anoAtual-paciente.anoNascimento;
        if(mesAtual<paciente.mesNascimento){
            idade -= 1;
        }else if(mesAtual==paciente.mesNascimento){
            if(diaAtual<paciente.diaNascimento){
                idade -= 1;
            }
        }
        paciente.idadePaciente = idade;

        printf(" Email: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente.email);

        printf(" Dia do diagnostico: ");
        fflush(stdin);
        scanf("%2d", &paciente.diaDiagnostico);

        printf(" Mes do diagnostico: ");
        fflush(stdin);
        scanf("%2d", &paciente.mesDiagnostico);

        printf(" Ano do diagnostico: ");
        fflush(stdin);
        scanf("%4d", &paciente.anoDiagnostico);

        printf("\n\n Diabetes?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente.diabetes);

        printf(" Hipertensao?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente.hipertensao);

        printf(" Tuberculose?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente.tuberculose);

        printf(" Obesidade?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente.obesidade);

        arquivoPaciente = fopen("Pacientes cadastrados.bin", "ab");

        if (arquivoPaciente == NULL){
            printf("\nProblemas ao tentar abrir o arquivo para salvar os dados!\n");
        }else{
            fwrite(&paciente, sizeof(dados_paciente), 1, arquivoPaciente);
        }

        fclose(arquivoPaciente);

        retornoRisco();

        printf("\n\n");
        printf(" Deseja cadastrar mais pacientes? Digite 1 para sim ou qualquer outro numero para nao.\n\n");
        fflush(stdin);
        scanf("%d", &opcaoMenuCadastro);

    }while(opcaoMenuCadastro == 1);
}

void retornoRisco(){
    int retornoDiabetes, retornoHipertensao, retornoTuberculose, retornoObesidade;//variavel para a verificação do valor de .diabetes, .hipertensao, .tuberculose e .obesidade.

    if( strcmp(paciente.diabetes, "sim") == 0 || strcmp(paciente.diabetes, "Sim") == 0 || strcmp(paciente.diabetes, "SIM") == 0){
        retornoDiabetes = 1;
    }else{
        retornoDiabetes = 0;
    }

    if( strcmp(paciente.hipertensao, "sim") == 0 || strcmp(paciente.hipertensao, "Sim") == 0 || strcmp(paciente.hipertensao, "SIM") == 0){
        retornoHipertensao = 1;
    }else{
        retornoHipertensao = 0;
    }

    if( strcmp(paciente.tuberculose, "sim") == 0 || strcmp(paciente.tuberculose, "Sim") == 0 || strcmp(paciente.tuberculose, "SIM") == 0){
        retornoTuberculose = 1;
    }else{
        retornoTuberculose = 0;
    }

    if( strcmp(paciente.obesidade, "sim") == 0 || strcmp(paciente.obesidade, "Sim") == 0 || strcmp(paciente.obesidade, "SIM") == 0){
        retornoObesidade = 1;
    }else{
        retornoObesidade = 0;
    }

    arquivoRisco = fopen("Grupo de Risco.txt", "a");
    if(arquivoRisco == NULL){
        printf("\n Erro ao tentar abrir o arquivo Grupo de Risco!");
        printf("\n Tentando criar o arquivo...\n\n");
        arquivoRisco = fopen("Grupo de Risco", "w");
    }

    if(idade >= 65 || retornoDiabetes == 1 || retornoHipertensao == 1 || retornoObesidade == 1 || retornoTuberculose == 1){
        fprintf(arquivoRisco, "-------------------------------------------------------\n");
        fprintf(arquivoRisco, " Nome do paciente: %s\n", paciente.nome);
        fprintf(arquivoRisco, " CEP: %s", paciente.cep);
        fprintf(arquivoRisco, "\n Idade: %d\n", paciente.idadePaciente);
        fprintf(arquivoRisco, "-------------------------------------------------------\n\n");
    }
    fclose(arquivoRisco);
}

void cpfPadronizador(){
    char traco = '-';
    char ponto = '.';

    paciente.cpf[13] = paciente.cpf[10];
    paciente.cpf[12] = paciente.cpf[9];

    paciente.cpf[10] = paciente.cpf[8];
    paciente.cpf[9] = paciente.cpf[7];
    paciente.cpf[8] = paciente.cpf[6];

    paciente.cpf[6] = paciente.cpf[5];
    paciente.cpf[5] = paciente.cpf[4];
    paciente.cpf[4] = paciente.cpf[3];

    paciente.cpf[11] = traco;
    paciente.cpf[7] = ponto;
    paciente.cpf[3] = ponto;
}

void cepPadronizador(){
    char traco = '-';

    paciente.cep[8] = paciente.cep[7];
    paciente.cep[7] = paciente.cep[6];
    paciente.cep[6] = paciente.cep[5];

    paciente.cep[5] = traco;
}

void listarPacientes(){
    system("cls");
    arquivoPaciente = fopen("Pacientes cadastrados.bin", "rb");

    if(arquivoPaciente == NULL){
        printf("\nProblemas ao ler os pacientes cadastrados!\n");
        system("pause");
    }else{
        while( fread(&paciente, sizeof(dados_paciente), 1, arquivoPaciente) == 1){
            printf("\n Nome: %s\n", paciente.nome);
            printf(" CPF: %s\n", paciente.cpf);
            printf(" Telefone: %s\n", paciente.telefone);
            printf(" Endereco: Rua: %s, No.: %d, %s - %s/%s\n", paciente.rua, paciente.numeroCasa, paciente.bairro, paciente.cidade, paciente.estado);
            printf(" CEP: %s\n", paciente.cep);
            printf(" Data de Nascimento: %d/%d/%d\n", paciente.diaNascimento, paciente.mesNascimento, paciente.anoNascimento);
            printf(" Idade: %d\n", paciente.idadePaciente);
            printf(" Email: %s\n", paciente.email);
            printf(" Data do Diagnostico: %d/%d/%d\n", paciente.diaDiagnostico, paciente.mesDiagnostico, paciente.anoDiagnostico);
            printf(" Diabetes: %s\n", paciente.diabetes);
            printf(" Hipertensao: %s\n", paciente.hipertensao);
            printf(" Tuberculose: %s\n", paciente.tuberculose);
            printf(" Obesidade: %s\n", paciente.obesidade);
            printf("--------------------------------------------------\n\n");
        }
    }
    fclose(arquivoPaciente);
    system("pause");
}

void pesquisarCpf(){
    system("cls");
    char cpf[15];

    arquivoPaciente = fopen("Pacientes cadastrados.bin", "rb");

    if(arquivoPaciente == NULL){
        printf("\nProblemas ao ler os dados dos pacientes cadastrados!\n");
        system("pause");
    }else{
        fflush(stdin);
        printf("Digite o CPF do paciente: ");
        scanf("%s", paciente.cpf);
        cpfPadronizador();
        strcpy(cpf, paciente.cpf);

        while( fread(&paciente, sizeof(dados_paciente), 1, arquivoPaciente) == 1){
            if(strcmp(paciente.cpf, cpf) != 0){
                printf("\n Numero de CPF nao encontrado!\n\n");
                goto fimpesquisar;
            }
            if( strcmp (paciente.cpf, cpf) == 0){
                printf("\n Nome: %s\n", paciente.nome);
                printf(" CPF: %s\n", paciente.cpf);
                printf(" Telefone: %s\n", paciente.telefone);
                printf(" Endereco: Rua: %s, No.: %d, %s - %s/%s\n", paciente.rua, paciente.numeroCasa, paciente.bairro, paciente.cidade, paciente.estado);
                printf(" CEP: %s\n", paciente.cep);
                printf(" Data de Nascimento: %d/%d/%d\n", paciente.diaNascimento, paciente.mesNascimento, paciente.anoNascimento);
                printf(" Idade: %d\n", paciente.idadePaciente);
                printf(" Email: %s\n", paciente.email);
                printf(" Data do Diagnostico: %d/%d/%d\n", paciente.diaDiagnostico, paciente.mesDiagnostico, paciente.anoDiagnostico);
                printf(" Diabetes: %s\n", paciente.diabetes);
                printf(" Hipertensao: %s\n", paciente.hipertensao);
                printf(" Tuberculose: %s\n", paciente.tuberculose);
                printf(" Obesidade: %s\n", paciente.obesidade);
                printf("--------------------------------------------------\n\n");
            }
        }
    }
    fimpesquisar:
    fclose(arquivoPaciente);
    system("pause");
}


void deletarCadastro(){

    FILE *deletarDados;
    int confirmacaoDados;
    int opcaoMenu;
    int quantPacientes = 0;
    int cpf[15];

    do{
        arquivoPaciente = fopen("Pacientes cadastrados.bin", "rb");
        deletarDados = fopen("temp.bin", "wb");

        if(arquivoPaciente == NULL && deletarDados == NULL){
            printf("\n Problemas ao ler o arquivo de dados!\n");
            system("pause");
        }else{
            system("cls");
            printf(" Digite o numero do CPF do paciente que deseja apagar os dados (apenas numeros): ");
            fflush(stdin);
            scanf("%s", paciente.cpf);
            cpfPadronizador();
            strcpy(cpf, paciente.cpf);

            while(fread(&paciente, sizeof(dados_paciente), 1, arquivoPaciente) == 1){
                if(strcmp(paciente.cpf, cpf) != 0){
                    printf("\n Numero de CPF nao encontrado!\n");
                    goto fimdeletar;
                }
                if (strcmp(paciente.cpf, cpf) == 0){
                    printf("\n Nome: %s\n", paciente.nome);
                    printf(" CPF: %s\n", paciente.cpf);
                    printf(" Telefone: %s\n", paciente.telefone);
                    printf(" Endereco: Rua: %s, No.: %d, %s - %s/%s\n", paciente.rua, paciente.numeroCasa, paciente.bairro, paciente.cidade, paciente.estado);
                    printf(" CEP: %s\n", paciente.cep);
                    printf(" Data de Nascimento: %d/%d/%d\n", paciente.diaNascimento, paciente.mesNascimento, paciente.anoNascimento);
                    printf(" Idade: %d\n", paciente.idadePaciente);
                    printf(" Email: %s\n", paciente.email);
                    printf(" Data do Diagnostico: %d/%d/%d\n", paciente.diaDiagnostico, paciente.mesDiagnostico, paciente.anoDiagnostico);
                    printf(" Diabetes: %s\n", paciente.diabetes);
                    printf(" Hipertensao: %s\n", paciente.hipertensao);
                    printf(" Tuberculose: %s\n", paciente.tuberculose);
                    printf(" Obesidade: %s\n", paciente.obesidade);
                    printf("--------------------------------------------------\n\n");
                }else{
                    fwrite(&paciente, sizeof(dados_paciente), 1, deletarDados);
                }
            }

            fclose(arquivoPaciente);
            fclose(deletarDados);
            printf("\n\n Esses sao os dados do paciente que deseja excluir? Digite 1 para sim ou qualquer outro numero para nao.\n");
            fflush(stdin);
            scanf("%d", &confirmacaoDados);

            if(confirmacaoDados == 1){
                if(remove("Pacientes cadastrados.bin") == 0 && rename("temp.bin", "Pacientes cadastrados.bin") == 0){
                    printf("\n Dados deletados com sucesso!");
                }
            }else{
                remove("temp.bin");
            }
        }

        fimdeletar:
        printf("\n Deseja excluir mais algum dado de algum paciente? Digite 1 para sim e qualquer outro numero para nao.\n");
        fflush(stdin);
        scanf("%d", &opcaoMenu);
    }while(opcaoMenu == 1);
}

