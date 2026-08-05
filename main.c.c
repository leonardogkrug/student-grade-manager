#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct {
    int matricula;
    char nome[50];
    float nota1;
    float nota2;
    float media;
} Aluno;

void cadastrarAluno() {
    FILE *arquivo;
    Aluno aluno;

    arquivo = fopen("alunos.dat", "ab");
    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    printf("Matricula: ");
    scanf("%d", &aluno.matricula);
    printf("Nome: ");
    setbuf(stdin, NULL);
    fgets(aluno.nome, 50, stdin);
    printf("Nota 1: ");
    scanf("%f", &aluno.nota1);
    printf("Nota 2: ");
    scanf("%f", &aluno.nota2);

    aluno.media = (aluno.nota1 + aluno.nota2) / 2;

    fwrite(&aluno, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);
    printf("O aluno foi cadastrado com sucesso!\n");
}

void listarAlunos() {
    FILE *arquivo;
    Aluno aluno;

    arquivo = fopen("alunos.dat", "rb");
    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    while(fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        printf("\nMatricula: %d\n", aluno.matricula);
        printf("Nome: %s\n", aluno.nome);
        printf("Nota 1: %.2f\n", aluno.nota1);
        printf("Nota 2: %.2f\n", aluno.nota2);
        printf("Media: %.2f\n", aluno.media);
    }
    fclose(arquivo);
}

void buscarAluno() {
    FILE *arquivo;
    Aluno aluno;
    int matBusca;
    int encontrado = 0;

    arquivo = fopen("alunos.dat", "rb");
    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    printf("Digite a matricula: ");
    scanf("%d", &matBusca);
    while(fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        if(aluno.matricula == matBusca) {

            printf("\nAluno encontrado!\n");
            printf("Nome: %s\n", aluno.nome);
            printf("Media: %.2f\n", aluno.media);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("O aluno nao foi encontrado.\n");
    }
    fclose(arquivo);
}

void atualizarAluno() {
    FILE *arquivo;
    Aluno aluno;
    int matBusca;

    arquivo = fopen("alunos.dat", "rb+");
    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matBusca);

    while(fread(&aluno, sizeof(Aluno), 1, arquivo)) {

        if(aluno.matricula == matBusca) {

            printf("Nova nota 1: ");
            scanf("%f", &aluno.nota1);

            printf("Nova nota 2: ");
            scanf("%f", &aluno.nota2);

            aluno.media = (aluno.nota1 + aluno.nota2) / 2;

            fseek(arquivo, -(long)sizeof(Aluno), SEEK_CUR);

            fwrite(&aluno, sizeof(Aluno), 1, arquivo);

            printf("Aluno atualizado!\n");

            fclose(arquivo);
            return;
        }
    }

    printf("Aluno nao encontrado.\n");
    fclose(arquivo);
}

void mediaTurma() {
    FILE *arquivo;
    Aluno aluno;

    float soma = 0;
    int quantidade = 0;

    arquivo = fopen("alunos.dat", "rb");
    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    while(fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        soma += aluno.media;
        quantidade++;
    }

    fclose(arquivo);

    if(quantidade > 0) {
        printf("Media da turma: %.2f\n",
               soma / quantidade);
    } else {
        printf("Nenhum aluno cadastrado.\n");
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao;

    do {
        printf("\n ======= SISTEMA DE ALUNOS =======\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("3 - Buscar aluno\n");
        printf("4 - Atualizar aluno\n");
        printf("5 - Media da turma\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarAluno();
                break;

            case 2:
                listarAlunos();
                break;

            case 3:
                buscarAluno();
                break;

            case 4:
                atualizarAluno();
                break;

            case 5:
                mediaTurma();
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}