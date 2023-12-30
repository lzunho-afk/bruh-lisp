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
#include "config.h"

/* Buffer de input do prompt */
static char input[2048];

void locale_code_verification(void) {
    char lang[3];
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
	fputs("bruh> ", stdout);
	fgets(input, 2048, stdin);
	printf("Você digitou %s", input);
    }
    return 0;
}
