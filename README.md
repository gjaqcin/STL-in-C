# STL-in-C

Biblioteca pessoal de estruturas de dados em **C11**, feita para aprender ponteiros, memória dinâmica, algoritmos e organização de código.

Os módulos atuais são **Vector** (array dinâmico de inteiros) e **Stack** (pilha LIFO que reutiliza o Vector). Usamos nomes curtos e fáceis de ler.

## Estrutura

```text
STL-in-C/
├── include/
│   ├── vector.h          # Interface do Vector
│   └── stack.h           # Interface da Stack
├── src/
│   ├── vector.c          # Implementação do Vector
│   └── stack.c           # Implementação da Stack
├── tests/
│   ├── test_vector.c     # Testes do Vector
│   └── test_stack.c      # Testes da Stack
├── .gitignore
└── README.md
```

`stack.h` inclui `vector.h` porque a Stack contém um membro `vector storage`. O arquivo `stack.c` implementa as operações usando a API pública do Vector, sem recriar o gerenciamento de memória.

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

## API da Stack

| Função | Objetivo |
| --- | --- |
| `stack_init` | Inicializar uma pilha vazia |
| `stack_push` | Inserir no topo |
| `stack_pop` | Remover o topo |
| `stack_top` | Consultar o topo sem remover (usa parâmetro de saída) |
| `stack_destroy` | Liberar os recursos |

`push` custa O(1) amortizado; `pop` e `top` custam O(1). Uma pilha vazia não permite `pop` nem `top`.

## Compilar manualmente

Na raiz do repositório, com GCC no PATH, execute **um comando para cada teste**.

**Windows (PowerShell / MinGW):**

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/vector.c tests/test_vector.c -o test_vector.exe
.\test_vector.exe

gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/vector.c src/stack.c tests/test_stack.c -o test_stack.exe
.\test_stack.exe
```

**Linux / macOS:**

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/vector.c tests/test_vector.c -o test_vector
./test_vector

gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/vector.c src/stack.c tests/test_stack.c -o test_stack
./test_stack
```

Cada header `.h` **declara** a interface pública. Cada arquivo `.c` **define** suas operações. O linker combina o código dos módulos ao programa que chama as funções. Não usamos Batch nem Makefile.

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
- As estruturas atuais armazenam apenas `int`; genericidade e operações como `insert`/`erase` poderão vir depois.
