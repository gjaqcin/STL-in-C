# STL-in-C

Biblioteca pessoal de estruturas de dados em **C11**, feita para aprender ponteiros, memória dinâmica, algoritmos e organização de código.

O primeiro módulo é um **vector de inteiros**, inspirado na STL do C++, mas escrito do zero em C. Usamos nomes curtos e fáceis de ler.

## Estrutura

```text
STL-in-C/
├── include/
│   └── vector.h          # Tipos e funções públicas
├── src/
│   └── vector.c          # Implementação
├── tests/
│   └── test_vector.c     # Testes com assert
├── .gitignore
└── README.md
```

Os próximos módulos (stack, queue etc.) terão seus próprios arquivos `.h`, `.c` e testes.

## API do Vector

| Função | Objetivo |
| --- | --- |
| `vector_init` | Inicializar uma estrutura vazia |
| `vector_push` | Inserir no final e expandir a memória, se necessário |
| `vector_pop` | Remover logicamente o último elemento |
| `vector_get` | Ler um elemento por índice, usando parâmetro de saída |
| `vector_set` | Alterar um elemento existente |
| `vector_destroy` | Liberar a memória e zerar os campos |

As funções que podem falhar retornam `bool`. Apenas índices `index < size` são válidos. O tipo `vector` contém um ponteiro para memória alocada; **não copie a estrutura por atribuição**, pois isso duplicaria a propriedade sobre o mesmo bloco e poderia causar `double free`.

## Compilar manualmente

Na raiz do repositório, com GCC no PATH:

**Windows (PowerShell/MinGW)**

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/vector.c tests/test_vector.c -o test_vector.exe
.\test_vector.exe
```

**Linux/macOS**

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/vector.c tests/test_vector.c -o test_vector
./test_vector
```

O header `vector.h` **declara** a API e o arquivo `vector.c` **define** suas operações. O linker combina a implementação e o programa de testes. Não usamos arquivos Batch ou Makefile neste projeto.

## Crescimento e complexidade

A capacidade cresce geometricamente: `0 → 4 → 8 → 16 → 32 → ...`.

| Operação | Complexidade |
| --- | --- |
| `vector_push` | O(1) amortizado; O(n) em expansão com cópia |
| `vector_pop` | O(1) |
| `vector_get` / `vector_set` | O(1) |
| `vector_init` / `vector_destroy` | O(1) para inteiros |

A implementação verifica overflow dos cálculos de capacidade e bytes. Em falha de `realloc`, a alocação e os elementos anteriores são preservados.

## Contratos

- Inicialize com `vector_init` antes de chamar outras operações.
- Chame `vector_destroy` ao terminar de usar o vetor.
- Não altere manualmente `data`, `size` ou `capacity` fora das funções.
- Os testes usam `assert`; compile sem `-DNDEBUG`.
- Esta primeira versão armazena apenas `int`; genericidade e operações como `insert`/`erase` poderão vir depois.
