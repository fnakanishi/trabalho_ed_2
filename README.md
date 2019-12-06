# Trabalho final de DS141 - Estrutura de Dados II

# Integrantes:
   &nbsp;&nbsp;GRR20184630&nbsp;&nbsp;&nbsp;&nbsp;Carlos Felipe Godinho Silva<br />
   &nbsp;&nbsp;GRR20184616&nbsp;&nbsp;&nbsp;&nbsp;David Gomes de Carvalho<br />
   &nbsp;&nbsp;GRR20186254&nbsp;&nbsp;&nbsp;&nbsp;Guilherme Alves da Silva<br />

# Estratégia:

# --freq
   Para a função --freq foi utilizada uma tabela Hash onde cada palavra é armazenada numa árvore red-black caída para a esquerda
na posição correspondente ao seu tamanho (da palavra) - 1 fazendo com que cada árvore armazene apenas palavras de mesmo tamanho.
Cada nó da árvore era um objeto que era composto de uma string que armaenava a palavra (e também era o critério de ordenação),
um inteiro que era encarregado de armazenar a quantidade de vezes que a palavra em questão apareceu no texto, além dos elementos
necessários para compor a árvore (2 nós filhos e um valor para determinar se o nó é vermelho ou preto). A determinação das "n"
palavras mais recorrentes no arquivo é feita após a inserção da palavra em sua árvore, para isso é criado um vetor de nós para
armazenar as mais recorrentes, caso a palavra recém inserida não esteja neste vetor e possua uma recorrência maior que as demais
presentes no vetor, ela substitui a com menor ocorrência do vetor. Ao final da leitura do arquivo e armazenamento de palavras
ordena-se o vetor contendo as palavras mais recorrentes e as apresenta ao usuário.

# --freq-word
   Para a função --freq-word ultiliza-se uma busca no arquivo pela palavra inserida, e quando encontrada é verificado se os
caracteres anterior e posterior são letras/números, se forem consideramos que trata-se de outra palavra que apenas contém a
palavra escolhida, ao final da leitura do arquivo é apresentado a quantidade de vezes que a palavra se repete no arquivo.

# --search
  Para a função --search utiliza-se o mesmo critério de busca de --freq-word, após percorrer o arquivo inteiro é feita nova
leitura no arquivo, desta vez contando a quantidade de palavras presentes no mesmo. Depois de realizada estes procedimentos em
todos os arquivos é feito o cálculo do TFIDF e apresentado em tela o arquivo cujo termo é mais relevante.
