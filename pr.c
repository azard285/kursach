#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

int arithmetic(int a, int b, char op) {
    int result;
    switch(op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        default:
            printf("Invalid operator\n");
            break;
    }
    return result;
}

int logical(int a, int b, char op) {
    int result;
    switch(op) {
        case '>':
            result = (a > b);
            break;
        case '<':
            result = (a < b);
            break;
        case '=':
            result = (a == b);
            break;
        default:
            printf("Invalid operator\n");
            break;
    }
    return result;
}

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    Pair pairs[MAX_SIZE];
    int size;
} Dictionary;

void init(Dictionary* dict) {
    dict->size = 0;
}

void put(Dictionary* dict, char* key, int value) {
    // проверяем, что словарь не переполнен
    if (dict->size >= MAX_SIZE) {
        printf("Error: dictionary is full\n");
        exit(1);
    }

    // ищем элемент с таким же ключом
    int i;
    for (i = 0; i < dict->size; i++) {
        if (dict->pairs[i].key == *key) {
            // если ключ уже есть, заменяем значение
            dict->pairs[i].value = value;
            return;
        }
    }

    // если ключа еще нет, добавляем элемент в конец словаря
    dict->pairs[dict->size].key = *key;
    dict->pairs[dict->size].value = value;
    dict->size++;
}

int get(Dictionary* dict, char* key) {
    // ищем элемент с таким же ключом
    int i;
    for (i = 0; i < dict->size; i++) {
        if (dict->pairs[i].key == *key) {
            return dict->pairs[i].value;
        }
    }

    // если ключ не найден, выводим ошибку и завершаем программу
    printf("Error: key not found\n");
    exit(1);
}

void cas(Dictionary* dict, char *token, char strg, FILE *fp)
{
    if(!strcmp(token,"read")){
        rede(dict, token);
    }

    else if(!strcmp(token,"print")){
            write(dict, token);
    }

    else if(!strcmp(token,"while"))
        Whil(dict, token, fp);
        
    else if(!strcmp(token,"if")){
        moshi(dict, token, fp);
    }

    else
    {
        char *cif = "п1234567890", nameper[25];
        int s1, s2; 
        strcpy(nameper, token);
        token = strtok(NULL, " ");
        if (!strcmp(token, "="))
        {
            token = strtok(NULL, " ");
            char *op = strtok(NULL, " ");
            if (op == NULL)
            {
                const int a = strlen(token)-2;
                char slag1[a];
                strncpy(slag1, token, strlen(token)); 
                slag1[strlen(token)] = '\0';

                if(strchr(cif, slag1[0]))
                {
                    put(dict, nameper, atoi(slag1));
                }
                else
                {
                    put(dict, nameper, get(dict, slag1));
                }
            }
            else
            {   const int a = strlen(token)-2;
                char slag1[a];
                strncpy(slag1, token, strlen(token)); 
                slag1[strlen(token)] = '\0';

                token = strtok(NULL, " ");
                char slag2[23];
                strncpy(slag2, token, strlen(token)); 
                slag2[strlen(token)] = '\0';

                if(strchr(cif, slag1[0]))
                {
                    s1 = atoi(slag1);
                }
                else
                {
                    s1 = get(dict, slag1);
                }
                if(strchr(cif, slag2[0]))
                {
                   s2 = atoi(slag2);
                }
                else
                {
                    s2 = get(dict, slag2);
                }
                put(dict, nameper, arithmetic(s1, s2, *op));
            }
            memset(nameper, 0, sizeof(nameper));
        }
        else
        {
            printf("Ошибка в этой строке: '%s' \n", strg);
            exit(1);
        }
    }
}

void write(Dictionary* dict, char* token)
{
    token = strtok(NULL, " ");
    char slag1[strlen(token)-2];
    const int a = strlen(token)-2;
    strncpy(slag1, token, a); 
    slag1[strlen(token)-2] = '\0';
    printf("%s\n", slag1);
    printf("%d\n", get(dict, slag1));
    //free(slag1);
}

void rede(Dictionary* dict, char* token)
{
    int x; 
    scanf("%d", &x);
    token = strtok(NULL, " ");
    char slag1[256];
    strncpy(slag1, token, strlen(token)-1);
    slag1[strlen(token)-1] = '\0';
    put(dict, slag1, x);
}

void Whil(Dictionary* dict, char* token, FILE *fp)
{
    char cif[14] = "п1234567890i", ni, nn, *str = malloc(100);
    int s = 0, i = 0;
    token = strtok(NULL, " ");

    if (strchr(cif, token))
    {
        printf("%s\n", "cif");
        i = atoi(token);
        ni = NULL;
    }
    else
    {
        printf("%s\n", "chis");
        i = get(dict, token);
        printf("%d\n", i);
        strcpy(ni, token);
        printf("%s\n", token);
    }
    token = strtok(NULL, " ");
        printf("%s\n", token);
    if (!strcmp(token, "do"))
    {
        while(i)
        {
            while(!strcmp(strtok(str, " "), "done"))
            {
                fgets(str, sizeof(str), fp);
                s += strlen(str);
                const int a = strlen(str);
                char strg[a];
                strcpy(strg,str);
                cas(dict, strtok(strg, " "), str, fp);
            }
            fseek(fp, -s, SEEK_CUR);
            s = 0;

            if(ni)
            {
                i = get(dict, ni);
            }
            else
            {
                printf("infinity while");
                exit(1);
            }
        }
    }
    else
    {
        char* op;
        if (strchr(cif, token))
        {
            op = token;
        }
        token = strtok(NULL, " ");
        int n; 
        if (strchr(cif, token))
        {
            n = atoi(token);
            nn = NULL;
        }
        else
        {
            n = get(dict, token);
            nn = *token;
        }

        while(logical(i,n,*op))
        {
            while(!strcmp(strtok(str, " "), "done"))
            {
                fgets(str, sizeof(str), fp);
                s += strlen(str);
                char strg[strlen(str)];
                strcpy(strg,str);
                cas(dict, strtok(strg, " "), str, fp);
            }
            fseek(fp, -s, SEEK_CUR);
            s = 0;
            
            if(ni)
            {
                i = get(dict, ni);
            }
            if(nn)
            {
                n = get(dict, nn);
            }
            else if((ni == NULL) & (nn == NULL))
            {
                printf("infinity while");
                exit(1);
            }
        }
    }
}

void moshi(Dictionary* dict, char* token, FILE *fp)
{
    char cif[14] = "п1234567890i", *str = malloc(100), *tok;
    token = strtok(NULL, " ");
    int i = 0;

    if (strchr(cif, token[0]))
    {
        i = atoi(token);
    }
    else
    {
        i = get(dict, token);
    }
    token = strtok(NULL, " ");

    if (!strcmp(token, "then"))
    {
        if(i)
        {
            while(strcmp(str, "fi"))
            {
                fgets(str,100, fp);
                const int a = strlen(str);
                char strg[a];
                strcpy(strg,str);
                tok = strtok(str, " ");
                if (!strcmp(tok, "else")){
                    break;
                }
                cas(&dict, tok, strg, fp);
            }
        }

        else
        {int b = 0;
            while(strcmp(str, "fi"))
            {
                
                fgets(str, 100, fp);
                const int a = strlen(str);
                char strg[a], *el = malloc(4);
                strcpy(strg,str);
                tok = strtok(str, " "); 
                strncpy(el, tok, 4);

                if (!strcmp(el, "else")){
                    b = 1;
                    fgets(str, 100, fp);
                    strcpy(strg,str);
                    tok = strtok(str, " ");
                    }

                if(a == 1){
                    cas(&dict, tok, strg, fp);
                }
            }
        }
    }

    else
    {
        char* op;
        if (!strchr(cif, token))
        {
            op = token;
        }
        token = strtok(NULL, " ");
        int n; 
        if (strchr(cif, token[0]))
        {
            n = atoi(token);
        }
        else
        {
            n = get(dict, token);
        }

        if(logical(i,n,*op))
        {
            while(strcmp(str, "fi"))
            {
                fgets(str,100, fp);
                const int a = strlen(str);
                char strg[a];
                strcpy(strg,str);
                tok = strtok(str, " ");
                if (!strcmp(tok, "else")){
                    break;
                }
                cas(&dict, tok, strg, fp);
            }
        }

        else
        {int b = 0;
            while(strcmp(str, "fi"))
            {
                
                fgets(str, 100, fp);
                const int a = strlen(str);
                char strg[a], *el = malloc(4);
                strcpy(strg,str);
                tok = strtok(str, " "); 
                strncpy(el, tok, 4);

                if (!strcmp(el, "else")){
                    b = 1;
                    fgets(str, 100, fp);
                    strcpy(strg,str);
                    tok = strtok(str, " ");
                    }

                if(a == 1){
                    cas(&dict, tok, strg, fp);
                }
            }
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc != 1){
        printf("The number of arguments passed must be one\n");
        return 1;
    }

    FILE *fp = fopen("a.txt", "r");
    char *str = malloc(100), strg[100];
    char *YN, *token;

    if (!fp){
        printf("не удалось открыть файл\n");
        return 1;
    }
    Dictionary dict;
    init(&dict);

    while(1)
    {
        YN = fgets(str, 123, fp);
        strcpy(strg,str);

        if (!YN)
        {
            if (!fp)
                break;
            else
            {
                printf("ошибка чтения файла\n");
                break;
            }
        }
        token = strtok(str, " ");
        cas(&dict, token, strg, fp);

    }

    return 1;
}
