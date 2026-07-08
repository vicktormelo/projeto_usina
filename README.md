# SIGDE 3.0

## Sistema Inteligente de Gerenciamento e Despacho de Energia

Projeto Final da disciplina **PRG22007 - PROGRAMAÇÃO DE COMPUTADORES II**
Prof. EVERTON LUIZ FERRET DOS SANTOS

Autor: **Vicktor Melo**

---

# Descrição

O SIGDE (Sistema Inteligente de Gerenciamento e Despacho de Energia) é um sistema desenvolvido em linguagem C para simular o gerenciamento operacional de usinas geradoras de energia elétrica.

O sistema utiliza uma Árvore Binária de Busca (ABB) como estrutura principal de armazenamento das usinas cadastradas e implementa um algoritmo guloso para realizar o despacho de energia conforme diferentes políticas de operação.

Todo o projeto foi desenvolvido utilizando conceitos estudados na disciplina de Estrutura de Dados, incluindo:

* Estruturas (`struct`)
* Enumerações (`enum`)
* Modularização
* Árvores Binárias de Busca (ABB)
* Algoritmos de ordenação (QuickSort)
* Algoritmos Gulosos
* Manipulação de arquivos texto
* Alocação dinâmica
* Organização em múltiplos módulos

---

# Objetivos do Sistema

O SIGDE foi desenvolvido para permitir:

* Cadastro de usinas de geração
* Gerenciamento operacional
* Controle de disponibilidade
* Simulação de despacho energético
* Emissão de relatórios
* Persistência dos dados em arquivos texto
* Geração de histórico e tickets dos despachos

---

# Estrutura do Projeto

```
SIGDE/

│
├── main.c
│
├── config.h
├── tipos.h
├── util.h
├── util.c
│
├── usina.h
├── usina.c
│
├── despacho.h
├── despacho.c
│
├── persistencia.h
├── persistencia.c
│
├── relatorios.h
├── relatorios.c
│
├── dados/
│     usinas.txt
│     historico.txt
│
├── tickets/
│
└── logs/
```

---

# Módulos do Sistema

## Utilitários

Responsável pelas funções auxiliares do sistema.

Possui funções para:

* leitura de dados
* validações
* cabeçalhos
* limpeza de tela
* pausas
* geração de IDs
* data e hora
* registro de logs

---

## Gerenciamento de Usinas

Gerencia todas as usinas cadastradas.

Funcionalidades:

* cadastrar
* editar
* ativar
* desativar
* pesquisar
* listar
* atualizar manutenção
* restaurar capacidade

As usinas são armazenadas em uma ABB ordenada pelo código da usina.

---

## Despacho de Energia

Implementa um algoritmo guloso responsável pela seleção automática das usinas.

O algoritmo:

* seleciona apenas usinas ativas
* ordena conforme a política escolhida
* distribui a demanda
* calcula custos
* registra energia fornecida
* gera estatísticas

---

## Persistência

Responsável pelo armazenamento permanente dos dados.

Arquivos utilizados:

* usinas.txt
* historico.txt
* tickets

Todas as informações permanecem disponíveis após o encerramento do programa.

---

## Relatórios

Responsável pela geração das consultas do sistema.

Disponibiliza:

* relatório geral das usinas
* estatísticas
* capacidade disponível
* custos

---

# Estrutura da Usina

Cada usina possui:

* código
* tipo
* região
* status
* potência instalada
* capacidade disponível
* reservatório
* custo por MWh
* produção diária
* produção mensal
* prioridade operacional
* última manutenção
* energia total produzida
* faturamento
* número de despachos
* horas de operação

---

# Tipos de Usina

* Hidrelétrica
* Termelétrica
* Eólica
* Solar
* Biomassa

---

# Regiões

* Sul
* Sudeste
* Centro-Oeste
* Nordeste
* Norte

---

# Status

* Ativa
* Inativa

---

# Políticas de Despacho

O sistema suporta quatro políticas diferentes.

## Econômico

Prioriza:

1. menor custo
2. maior prioridade
3. maior capacidade

---

## Emergência

Prioriza:

1. maior capacidade disponível
2. menor custo

---

## Ecológico

Prioriza fontes renováveis.

Ordem de preferência:

* Solar
* Eólica
* Hidrelétrica
* Biomassa
* Termelétrica

---

## Balanceado

Calcula uma pontuação considerando:

* capacidade disponível
* prioridade operacional
* custo de geração

---

# Estruturas de Dados Utilizadas

* Struct
* Enum
* ABB (Árvore Binária de Busca)
* Vetores
* Arquivos texto

---

# Algoritmos Utilizados

* Busca em ABB
* Inserção em ABB
* Percurso em ordem
* QuickSort
* Algoritmo Guloso

---

# Funcionalidades Disponíveis

Cadastro

* cadastrar usina
* editar usina
* ativar
* desativar

Consulta

* listar usinas
* estatísticas
* capacidade disponível
* custos

Despacho

* selecionar política
* executar despacho
* atualizar estatísticas
* atualizar capacidade

Persistência

* salvar banco
* carregar banco
* histórico
* tickets

---

# Arquivos Gerados

## usinas.txt

Banco principal do sistema.

Armazena todas as usinas cadastradas.

---

## historico.txt

Armazena todos os despachos realizados.

---

## ticket_xxxx.txt

Resumo individual de cada despacho realizado.

---

## sistema.log

Registro das operações realizadas pelo sistema.

---

# Fluxo de Funcionamento

1. Inicialização
2. Carregamento do banco
3. Cadastro das usinas
4. Atualização das informações
5. Execução do despacho
6. Atualização das estatísticas
7. Geração de ticket
8. Registro do histórico
9. Salvamento do banco
10. Encerramento

---

# Tecnologias Utilizadas

* Linguagem C
* Code::Blocks
* GCC
* Arquivos texto
* Estruturas de Dados

---

# Conceitos Acadêmicos Aplicados

* Modularização
* Programação Estruturada
* Árvores Binárias de Busca
* Algoritmos de Ordenação
* Algoritmos Gulosos
* Manipulação de Arquivos
* Estruturas de Dados
* Persistência de Dados

---

# Autor

Vicktor Melo

Projeto desenvolvido para a disciplina de PRG22007 - PROGRAMAÇÃO DE COMPUTADORES II.

Instituto Federal de Santa Catarina (IFSC).
