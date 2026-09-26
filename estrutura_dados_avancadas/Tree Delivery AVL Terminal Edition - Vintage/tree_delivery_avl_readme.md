# Tree Delivery: AVL Terminal Edition

## Sobre o Jogo
**Tree Delivery: AVL Terminal Edition** é um jogo educativo desenvolvido em C++, criado com base em metodologias de engenharia reversa do jogo original "Tree Delivery" (desenvolvido originalmente em Unity para BST). Esta versão de terminal serve como um *upgrade* de mecânica, transferindo a responsabilidade do rebalanceamento da árvore diretamente para o jogador.

## Contexto do Projeto
- **Disciplina:** Estruturas de Dados II
- **Curso:** Ciência da Computação
- **Tema:** Design de Jogos Educativos sobre Árvores Avançadas por meio da Engenharia Reversa e Reuso de Modelos.
- **Objetivo:** Transformar a experiência passiva do jogo original em uma mecânica ativa focada em Árvores AVL.

## Proposta Educacional e Objetivo de Aprendizagem
O principal objetivo acadêmico é consolidar o aprendizado prático das **Árvores AVL**. Em vez de apenas estudar e memorizar no papel as regras de balanceamento, o jogador atua como o "algoritmo vivo". Ele precisa identificar Fatores de Balanceamento (FB) em tempo real e aplicar as operações corretas de Rotações (Simples e Duplas) para manter o custo computacional otimizado em `O(log n)`. O jogo converte abstrações matemáticas em um desafio dinâmico com risco de falha.

## Conceitos de Estrutura de Dados Utilizados
- **Nós e Chaves:** Representam os locais de entrega e os números das caixas.
- **Ordenação via Árvores Binárias de Busca (BST):** A base da ordenação (esquerda < raiz < direita).
- **Altura da Árvore:** Profundidade calculada dinamicamente para cada galho.
- **Fator de Balanceamento (FB):** A métrica central. Permitida apenas nos limites de `-1, 0, e 1`.
- **Rotações Simples (LL e RR):** Manobras básicas para correção de desequilíbrios lineares.
- **Rotações Duplas (LR e RL):** Manobras combinadas para correção de desequilíbrios em "joelho" (ziguezague).

## Funcionamento e Mecânica do Jogo
O jogo funciona em um *core loop* contínuo de entregas:
1. O sistema gera aleatoriamente um valor numérico para uma "caixa" (entre 10 e 99).
2. A caixa é inserida na estrutura seguindo a lógica estrita de **ordenação BST**.
3. O jogo calcula recursivamente a altura e o FB de todos os nós no caminho percorrido.
4. **Intervenção do Jogador:** Se o jogo detectar um nó com FB > 1 ou FB < -1, o tempo para e a subárvore desbalanceada é exibida na tela.
5. O jogador deve analisar visualmente a árvore e decidir qual das 4 rotações (LL, RR, LR, RL) resolve o colapso.

## Sistema de Acertos e Punições
- **Acertos:** Executar a rotação correta recompensa o jogador com **+20 pontos**. A árvore é estabilizada e a rodada segue.
- **Erros:** Escolher a manobra errada custa **1 Vida**. O sistema aplica a rotação correta compulsoriamente para evitar que o código quebre, mas alerta o jogador sobre seu erro.
- **Condição de Vitória:** Entregar com sucesso o número máximo de caixas (15 caixas) preservando as propriedades da AVL.
- **Condição de Derrota:** Perder todas as 3 vidas disponíveis, permitindo que a estrutura entre em colapso e cause a "degradação algorítmica para O(n)".

## Tecnologias Utilizadas
- **Linguagem:** C++
- **Interface:** Terminal / Prompt de Comando (ASCII)
- **Ambiente de Desenvolvimento Recomendado:** Dev-C++ ou Code::Blocks

## Como Executar
1. Abra a sua IDE de preferência (Dev-C++ ou Code::Blocks).
2. Crie um novo arquivo de código-fonte (`.c`) vazio.
3. Cole todo o código-fonte do jogo fornecido anteriormente.
4. Salve o arquivo (ex: `tree_delivery_avl.c`).
5. Compile o programa (geralmente pressionando `F9`).
6. Execute o arquivo compilado (geralmente `F10` ou o botão de Play).
7. Jogue utilizando os números do seu teclado numérico seguido da tecla `ENTER` para selecionar as manobras e prosseguir nos diálogos.
