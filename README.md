# STL-in-C

Uma pequena biblioteca de estruturas de dados escrita em **C11** para estudar ponteiros, alocação dinâmica, APIs, complexidade, testes e compilação separada.

O projeto é inspirado em operações da STL do C++, mas **não é uma implementação da STL**. O primeiro módulo é um vetor dinâmico de inteiros.

## Estrutura

```text
STL-in-C/
├── include/cstl/int_vector.h    # API publica
├── src/int_vector.c             # Implementacao
├── tests/test_int_vector.c      # Testes com assert
├── examples/vector_example.c    # Exemplo de uso
├── Makefile                     # GNU Make / ambiente Unix
├── build.bat                    # Windows + GCC MinGW
└── .gitignore
```

## API atual

- `cstl_int_vector_init`: inicializa um vetor vazio.
- `cstl_int_vector_push_back`: insere um inteiro; expande a capacidade quando necessário.
- `cstl_int_vector_pop_back`: remove logicamente o ultimo inteiro.
- `cstl_int_vector_get`: consulta um inteiro, usando parametro de saida.
- `cstl_int_vector_set`: modifica um inteiro existente.
- `cstl_int_vector_destroy`: libera memoria e zera os campos.

As operacoes que podem falhar retornam `bool`. Um indice valido satisfaz `index < size`. A memoria pertence ao vetor: **nao copie a struct por atribuicao** sem definir uma politica de copia.

## Compilar no Windows (VS Code + GCC MinGW)

Abra o terminal **na raiz do repositorio** e execute:

```powershell
.\build.bat
.\build\vector_example.exe
```

O script compila `src/int_vector.c`, cria a biblioteca estatica `build/libcstl.a`, compila os testes e exemplo e executa os testes. Necessita de `gcc` e `ar` no PATH.

## Compilar com GNU Make (Linux / Git Bash / MSYS)

```sh
make
make test
make example
```

## Compilacao manual (aprendizado)

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude -c src/int_vector.c -o int_vector.o
ar rcs libcstl.a int_vector.o
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude examples/vector_example.c libcstl.a -o vector_example
```

O header **declara** a API; o arquivo `.c` **define** as funcoes. O linker encontra as definicoes na biblioteca `.a`.

## Politica de crescimento e complexidade

A capacidade segue `0 -> 4 -> 8 -> 16 -> 32 -> ...`.

| Operacao | Complexidade |
| --- | --- |
| `push_back` | O(1) amortizado; O(n) quando precisa mover os elementos |
| `pop_back` | O(1) |
| `get` / `set` | O(1) |
| `init` / `destroy` | O(1) para os elementos `int` |

A implementacao protege o calculo da capacidade e dos bytes contra overflow de `size_t`. Em falhas de `realloc`, o vetor anterior permanece intacto.

## Contratos e limites

- Passe um ponteiro para vetor valido e inicializado em todas as operacoes, exceto `init`.
- Chame `destroy` quando terminar de usar o vetor.
- Nao altere manualmente `data`, `size` ou `capacity` fora das funcoes da biblioteca.
- A API atual so armazena `int`; tipos genericos ficam para versoes futuras.
- Testes utilizam `assert`: execute sem `-DNDEBUG`.
- A biblioteca ainda nao fornece iteradores, insercao no meio, `reserve` ou clonagem.

## Proximos marcos

1. Investigar os arquivos `.o`, a biblioteca estatica `.a` e o linker.
2. Ampliar os testes e executar ferramentas de diagnostico de memoria.
3. Adicionar `reserve`, `insert`, `erase` e benchmarks.
4. Implementar as proximas estruturas de dados, sem esconder os mecanismos estudados.
