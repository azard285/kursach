#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100000

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
            exit(1);
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


struct DictionaryItem {
    char key[50]; 
    int value; 
};


struct Dictionary {
    struct DictionaryItem items[MAX_SIZE]; 
    int size; 
};


void put(struct Dictionary *dict, char *key, int value) {
    //printf("%s put %d size\n", key, dict->size);
    if (dict->size >= MAX_SIZE) {
        printf("Словарь заполнен\n");
        return;
    }

    for (int i = 0; i < dict->size; i++){
        if(!strcmp(dict->items[i].key, key)){
            dict->items[i].value = value;
            return;
        }
    }
    
    struct DictionaryItem newItem;
    strcpy(newItem.key, key);
    newItem.value = value;

    dict->items[dict->size] = newItem;
    dict->size++;
}

int get(struct Dictionary *dict, char *key) {
    int i;
    //printf("%d get size %s key\n", dict->size, key);

    for (i = 0; i < dict->size; i++) {
        //printf("%d %s dfdfdfdfdfdfdfdfdfdf\n", i, dict->items[i].key);
        if (strcmp(dict->items[i].key, key) == 0) {
            //printf("%d value\n", dict->items[i].value);
            return dict->items[i].value;
        }
    }

    printf("Элемент с ключом %s не найден\n", key);
    exit(1);
}

void cas(struct Dictionary *dict, char *token, char *strg, FILE *fp)
{
	//printf("%s sdgedsfrhgsfdfth\n", token);
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
            {  
                const int a = strlen(token)-2;
                char slag1[a];
                strncpy(slag1, token, strlen(token)); 
                slag1[strlen(token)] = '\0';

                token = strtok(NULL, " ");
                char slag2[23];
                strncpy(slag2, token, strlen(token)); 
                slag2[strlen(token)] = '\0';

                if(strchr(cif, slag1[0])){
                    s1 = atoi(slag1);
                }
                else{
                    s1 = get(dict, slag1);
                }
                if(strchr(cif, slag2[0])){
                   s2 = atoi(slag2);
                }
                else{
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

void write(struct Dictionary *dict, char* token)
{
	//printf("%s dsdsdsdsd\n", token);
    token = strtok(NULL, " ");
    char slag1[strlen(token)-1];
    strncpy(slag1, token, strlen(token)); 
    slag1[strlen(token)] = '\0';
    //printf("%s heh %s print\n", token, slag1);
    printf("%d\n", get(dict, slag1));
}

void rede(struct Dictionary *dict, char* token)
{
    int x; 
    scanf("%d", &x);
    //printf("%s tok\n", token);
    token = strtok(NULL, " ");
    //printf("%s tok\n", token);
    char slag1[256];
    strncpy(slag1, token, strlen(token));
    //printf("%s rede\n", slag1);
    slag1[strlen(token)] = '\0';
    //printf("%s rede\n", slag1);
    put(dict, slag1, x);
}

void Whil(struct Dictionary *dict, char* token, FILE *fp)
{
    char cif[14] = "п1234567890i", *ni, *nn, *str = malloc(100), *tok = token;
    int s = 0, i = 0;
    token = strtok(NULL, " ");

    if (strchr(cif, token))
    {
        i = atoi(token);
        ni = NULL;
    }
    else
    {
        i = get(dict, token);
        ni = token;
    }
    token = strtok(NULL, " ");
    if (!strcmp(token, "do"))
    {
        while(i)
        {
            while(strcmp(strtok(str, " "), "done"))
            {
                fgets(str, 100, fp);
                s += strlen(str)-2;
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
        if (!strchr(cif, token)){
            op = token;
        }
        token = strtok(NULL, " ");
        int n; 
        if (strchr(cif, token[0])){
            n = atoi(token);
            nn = NULL;
        }
        else{
            n = get(dict, token);
            nn = *token;
            printf("%s wh\n", n);
        }

        while(logical(i,n,*op))
        {
            while(1)
            {
                fgets(str,100, fp);
                s += strlen(str);
                char strg[strlen(str)];
                strcpy(strg,str);
                tok = strtok(str, " ");
                if (!strcmp(tok, "done")){
                    break;
                }
                cas(dict, tok, strg, fp);
            }
            fseek(fp, -s, SEEK_CUR);
            s = 0;
            i++;
                    
            if(ni){
                i = get(dict, ni);
            }
            if(nn){
                 n = get(dict, nn);
            }
            else if((ni == NULL) & (nn == NULL))
            {
                printf("infinity while");
                exit(1);
            }
        }
        while(1)
        {
            fgets(str,100, fp);
            s += strlen(str);
            char strg[strlen(str)];
            strcpy(strg,str);
            tok = strtok(str, " ");
            if (!strcmp(tok, "done"))
            {
                break;
            }
        }
    }
}

void moshi(struct Dictionary *dict, char* token, FILE *fp)
{
    char cif[14] = "п1234567890i", *str = malloc(100), *tok = token;
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
            while(strcmp(tok, "fi"))
            {
                fgets(str,100, fp);
                char strg[strlen(str)];
                strcpy(strg,str);
                tok = strtok(str, " ");
                if (!strcmp(tok, "else") || !strcmp(tok, "fi")){
                    break;
                }
                cas(dict, tok, strg, fp);
            }
        }

        else
        {
            int b = 0;
            while(strcmp(str, "fi"))
            {
                
                fgets(str, 100, fp);
                const int a = strlen(str);
                char strg[a], *el = malloc(4);
                strcpy(strg,str);
                tok = strtok(str, " "); 
                strncpy(el, tok, 4);
                if (!strcmp(tok, "fi")){
                    break;
                }

                if (!strcmp(el, "else")){
                    b = 1;
                    fgets(str, 100, fp);
                    strcpy(strg,str);
                    tok = strtok(str, " ");
                    }
                    free(el);
                if(b == 1){
                    cas(dict, tok, strg, fp);
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
            int b = 0;
            while(strcmp(tok, "fi"))
            {
                fgets(str, 100, fp);
                char strg[strlen(str)], *el = malloc(4);
                strcpy(strg,str);
                tok = strtok(str, " "); 
                strncpy(el, tok, 4);
                if (!strcmp(tok, "fi") || !strcmp(tok, "else")){
                    break;
                }
                cas(dict, tok, strg, fp);
            }
        }

        else
        {
            int b = 0;
            while(strcmp(str, "fi"))
            {
                
                fgets(str, 100, fp);
                char strg[strlen(str)], *el = malloc(4);
                strcpy(strg,str);
                tok = strtok(str, " "); 
                strncpy(el, tok, 4);
                if (!strcmp(tok, "fi")){
                    break;
                }

                if (!strcmp(el, "else")){
                    b = 1;
                    fgets(str, 100, fp);
                    strcpy(strg,str);
                    tok = strtok(str, " ");
                    }
                    free(el);
                if(b == 1){
                    cas(dict, tok, strg, fp);
                }
            }
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("The number of arguments passed must be one\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    char *str = malloc(100), strg[100];
    char *YN, *token;

    if (!fp){
        printf("не удалось открыть файл\n");
        return 1;
    }
    struct Dictionary dict;
    dict.size = 0;

    while(1)
    {
        YN = fgets(str, 123, fp);
        strcpy(strg,str);
        //printf("%s str\n", str);

        if (!YN)
        {
            if (!fp)
                break;
            else
            {
                //printf("файл закончился\n");
                break;
            }
        }
        token = strtok(str, " ");
        cas(&dict, token, strg, fp);
    }

    return 1;
}
