<!DOCTYPE html>
<html>
<body>
    <h1>Simulador de Playlist em C</h1>
    <p>Este projeto é um simulador de playlist que lê uma lista de artistas e suas respectivas músicas de um arquivo (musicas.txt) e armazena os registros lidos em uma lista circular duplamente encadeada durante a execução.</p>
    <h2>Funcionalidades</h2>
    <p>O código exibe a música atual da playlist e é capaz de avançar ou retornar a alguma música. Além disso, o programa mostra um menu interativo, pelo qual o usuário será capaz de executar as seguintes ações:</p>
    <ol>
        <li>Exibição da playlist pela ordem de cadastro</li>
        <li>Exibição da playlist ordenada pelo nome das músicas</li>
        <li>Inserção de novas músicas</li>
        <li>Remoção de uma música</li>
        <li>Busca por uma música</li>
        <li>Avançar para próxima música</li>
        <li>Retornar a música anterior</li>
    </ol>
    <h2>Arquivo de Entrada</h2>
    <p>O arquivo de entrada é composto de registros formados pelo nome do artista e uma música, separados por “;”. Exemplo de registros:</p>
    <pre>
    Artista X;Música 3
    Artista Y;Música 42
    </pre>
    <h2>Como Compilar</h2>
    <p>Para compilar o código, você pode usar o gcc da seguinte maneira:</p>
    <pre>
    gcc main.c -o main
    </pre>
    <h2>Como Executar</h2>
    <p>Para executar o programa, você pode usar o seguinte comando:</p>
    <pre>
    ./main
    </pre>
    <h2>Contribuições</h2>
    <p>Contribuições são sempre bem-vindas. Sinta-se à vontade para abrir uma issue ou enviar um pull request.</p>
    <h2>Licença</h2>
    <p>Este projeto está licenciado sob a licença MIT.</p>
</body>
</html>
