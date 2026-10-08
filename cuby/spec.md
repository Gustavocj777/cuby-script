# Especificação Técnica da Cuby & Mini-Geny

## 1. Visão Geral
A **Cuby** é uma linguagem de programação nativa em C, focada em alta performance, sem coletores de lixo (garbage collection), utilizando uma abordagem centrada no sistema de arquivos para modularidade e automação através da **mini-geny**.

## 2. Arquitetura de Micro-Units e Sigla-Matriz
O ecossistema utiliza uma matriz rigorosa de blocos e combinações de duas letras para gerenciar o ciclo de vida de compilação e os artefatos intermediários:

- **Blocos Base:**
  - `.cip`: Unidades centrais de processamento/código.
  - `.hip`: Unidades de cabeçalho/interfaces.
  - `.sip`: Unidades de sistema/baixo nível.

- **Combinações Intermediárias (Sigla-Matriz):**
  O sistema gerencia 6 combinações direcionadas de interações entre C, Assembly e Headers:
  - `-cs`, `-sc`, `-hc`, `-ch`, `-sh`, `-hs`

## 3. Comportamento do Sistema de Arquivos (Auto-Organização)
Quando a CLI do mini-geny é acionada, o sistema executa o seguinte pipeline:
1. **Entrada:** Lê o diretório alvo informado via parâmetro (`-dir -name <diretorio> -<sigla>`).
2. **Centralização:** Cria dinamicamente a pasta raiz de compilação `gen/` caso ela não exista.
3. **Isolamento:** Cria uma subpasta prefixada com underline correspondente à sigla (ex: `gen/_sc/`, `gen/_cs/`) para evitar colisões de namespace.
4. **Migração & Limpeza:** Copia os arquivos de forma segura para o destino isolado e executa a limpeza automática (`unlink`) na origem.

## 4. Sintaxe da CLI
```bash
cuby -dir -name <diretorio> -<sigla>

./cuby -dir -name meu_projeto -sc
---

## Part 2: README.md (Project Presentation)

```markdown
# Cuby Ecosystem & Mini-Geny

> Uma linguagem de programação e ecossistema de baixo nível construído em C puro, projetado para alta performance sem garbage collection e com gerenciamento de pacotes baseado em sistema de arquivos.

## 🚀 Sobre o Projeto
O **Cuby** foge do convencional ao eliminar runtimes pesados, utilizando uma abordagem modular baseada em micro-unidades (`.cip`, `.hip`, `.sip`) e uma ferramenta de automação chamada **mini-geny**. Ela gerencia o isolamento de arquivos e a pré-compilação de forma autônoma através de uma matriz de siglas direcionadas.

## 🛠️ Como Compilar (Termux / Linux / PC)
Você pode compilar o projeto utilizando o compilador GCC padrão:

```bash
gcc main.c -o cuby
make
./cuby -dir -name meu_projeto -sc

