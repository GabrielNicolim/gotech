<h1 align = "center">Projeto de Fundamento de Processamento de Dados</h1>

<h2>Sobre o projeto</h2>

Este projeto visa aplicar os conceitos aprendidos em FPD e TP ao longo de 2020. Buscamos fazer uma espécie de gerenciador de estoque de uma loja de computadores com um pseudo banco de dados feito em C/C++.<br><br>


:computer: <b>Tema: </b>Loja de Informática<br>
:rocket: <b>Integrantes: </b>Gabriel Nicolim e Felipe Lima<br>
:dart: <b>Objetivo: </b>Gerenciamento de estoque<br>

<img src="https://user-images.githubusercontent.com/69210720/111396661-555c5000-869e-11eb-84d8-cc96c92d3640.png"/>

<hr>

<h2>Bibliotecas utilizadas: </h2>
<li><a href = "https://pt.wikipedia.org/wiki/Stdio.h"><cite>Stdio.h</cite></a>
<li><a href = "http://linguagemc.com.br/a-biblioteca-math-h/"><cite>Math.h</cite></a>
<li><a href = "https://en.wikipedia.org/wiki/Windows.h"><cite>Windows.h</cite></a>
<li><a href = "https://www.programmingsimplified.com/c/conio.h"><cite>Conio.h</cite></a>
<li><a href = "https://pt.wikipedia.org/wiki/Time.h"><cite>Time.h</cite></a>
<li><a href = "http://linguagemc.com.br/a-biblioteca-string-h/"><cite>String.h</cite></a>
<li><a href = "http://www.nongnu.org/avr-libc/user-manual/io_8h_source.html"><cite>Io.h</cite></a>
<li><a href = "https://github.com/GabrielNicolim/Trabalho-de-FPD/blob/remaster/scripts/functions/desenhos.h"><cite>desenhos.h</cite></a>
<br>
  
<p>
O projeto <b>REMASTER</b> é focado em rodar na versão do <a href="https://github.com/Embarcadero/Dev-Cpp">DevC++ 6.3 da Embarcadero</a>, porém
o projeto tambem tem uma retrocompatibilidade com a versão 5.8.3 e <a href="https://sourceforge.net/projects/orwelldevcpp/">DevC++ 5.11 versão Orwell</a>,
para conseguir compilar o projeto nessa versão mais antiga basta remover os comentários( // ) nas 3 referencias a função *text_info vActual*, as
instruções estão no arquivo para em quais linhas essa função está mencionada, e para rodar na versão da Embarcadero basta apenas comentar essas linhas
</p>

<p>
Após a finalização do trabalho percebemos gradativamente alguns erros e problemas sérios e não corrigidos no programa, que passava das 4600 linhas após o envio do trabalho, 
então com um pouco de tempo livre e saudades de C, em 2021 o o indivíduo Felipe decidiu dar uma refatorada no código de verdade, cortando desperdicios de linhas, otimizando 
o programa e implementando features e verificações que queriamos implementar desde o começo mas que não tivemos sucesso devido a falta de conhecimento na época, e esperamos
que com essa refatorada grande do código conseguimos criar algo mais dinâmico de entender e dar manutenção.

Caso queira estudar mais sobre manupulação de arquivos em C:
https://terminalroot.com.br/2014/12/linguagem-c-utilizando-as-funcoes-fopen.html
</p>

Ultima versão estável: 4.5