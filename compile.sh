#!/bin/bash
# compile.sh -- Spript para auxílio na compilação e montagem do projeto.
# Altera variáveis conforme as configurações do usuário e define objetos
# de compilação.
#
# Versão 0: Funcionalidades básicas de compilação e organização do projeto.
#
# Copyright 2023,2024 Lucas Zunho <lucaszunho17@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Arquivos SOURCE e INCLUDE
readarray -d '' SOURCES < <(find src/ -type f)

FLAGS=(-std=c99 -Wall)
LIBRARIES=(-ledit -lm)
PROJ_OUTPUT=build/

USAGE_MSG="
USAGE: $(basename "$0") [-h | -p | -V | -o [PATH]]
  -h, --help	  Mostra essa tela de ajuda.
  -V, --version	  Mostra a versão do script.
  -o, --output	  Define o diretório de saída (build).
"

while test -n "$1"; do
    case "$1" in
	-h | --help)
	    echo "$USAGE_MSG"
	    exit 0
	    ;;
	-V | --version)
	    echo -n $(basename "$0")
	    grep '^# Versão ' "$0" | tail -1 | cut -d : -f 1 | tr -d \#
	    exit 0
	    ;;
	-o | --output)
	    shift
	    PROJ_OUTPUT="$1"
	    if test -z "$PROJ_OUTPUT"; then
		echo "Um caminho deve ser definido para a saída!"
		exit 1
	    fi
	    ;;
	*)
	    if test -n "$1"; then
		echo "Opção inválida '$1'"
		exit 1
	    fi
	    ;;
    esac
    shift
done

echo -e "Flags do compilador:\n\t${FLAGS[@]}"
echo -e "Arquivos de código-fonte adicionados:\n${SOURCES[@]}"
echo -e "Strings de libs adicionadas:\n\t${LIBRARIES[@]}"

mkdir -p $PROJ_OUTPUT
PROJ_OUTPUT="${PROJ_OUTPUT}/bruhlisp"
gcc ${FLAGS} ${SOURCES[@]} ${LIBRARIES[@]} -o $PROJ_OUTPUT
