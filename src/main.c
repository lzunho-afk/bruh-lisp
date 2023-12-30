/*
 * main.c - chamadas primárias de sistema e definições do interpretador.
 *
 * Copyright 2023,2024 Lucas Zunho <lucaszunho17@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:*www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h> /* Caracteres pt_BR */
#include <string.h>

#ifdef _WIN32

/* Buffer de input do prompt */
static char buff[2048];

/* char *readline(char *prompt)
   Substitui a função 'readline' caso o programa esteja rodando
   em sistemas Windows (sem suporte para biblioteca editline).
 */
char *readline(char *prompt) {
    fputs(prompt, stdout);
    fgets(buff, 2048, stdin);
    char *cpy = malloc(strlen(buff) + 1);
    strcpy(cpy, buff);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

/* void add_history(char *unused)
   Substitui a função 'add_history' do editline em sistemas não
   suportados (fundamentalmente Windows).
 */
void add_history(char *unused) {}

#else // != _WIN32

/* Readline & History headers */
#include <editline/readline.h>
#include <editline/history.h>

#endif // _WIN32

#include "config.h"

/* void locale_code_verification(void)
   Verifica o locale do sistema e retorna uma mensagem de alerta para o
   stderr. É verificado se o sistema armazena um locale com prefixo 'pt'.
 */
void locale_code_verification(void) {
    char lang[3];
    memset(lang, '\0', 3);
    strncpy(lang, setlocale(LC_ALL, ""), 2);
    if (strcmp(lang, "pt") != 0) {
	printf("Substring = %s\nLocale = %s\n", lang, setlocale(LC_ALL, ""));
	fprintf(stderr, "%s\nLocale atual - %s\n", "Locale diferente do esperado! Alguns caracteres podem não ser apresentados corretamente.", setlocale(LC_ALL, ""));
    }
}

int main(int argc, char** argv) {
    /* Alterando o locale e verificando-o */
    setlocale(LC_ALL, "Portuguese");
    locale_code_verification();
    
    /* Versão e informações do programa */
    puts(CMD_PROJECT_STRING);
    puts("Use Ctrl+c para sair\n");

    /* Laço do prompt */
    while (1) {
	char *uinput = readline("bruhlisp >>> ");
	add_history(uinput);
	printf("Você digitou %s\n", uinput);
	free(uinput);
    }
    return 0;
}
