MODELBEGIN

// insert your equations here, ONLY between the MODELBEGIN and MODELEND words

// antigo modelo (basico)
//EQUATION("Price")
/*
Contrl i = para botão direito de comandos
bloco de comentários está aqui entre barras com asteriscos
linha de comentários (//)
*/

//v[0] = VL("Price", 1); //variável
// VL pega valor defasado, nesse caso  só queremos a primeira defasagem
//v[1] = V("C"); // parâmetro
// V pega valor corrente
// uma forma de diferenciar variáveis de parâmetros é colocar variáveis com letras maiúsculas e os parâmetros minísculos
// quando fizermos o c como componente estocástico, por isso se ele variar, faz sentido ele ser uma variável e vamos criar uma nova equação para isso

//RESULT(v[0]+v[1])
// preço é uma função linear de price_today = price_yesterday + c
// sempre chamar num lag + 1 para não dar deadlock
// O V é a variável, que pode ter várias variáveis v temporais, armazenadores temporais de valor que só funcionam dentro do bloco de equação,
// se dentro do bloco, quiser usar o mesmo v, posso usar, mas pode ficar muito poluído. São caixinhas temporais. Posso usar até 1000 v
//quando terminar de ler a equação, ele vai limpar todas as gavetas
// sempre terminar linhas com ponto e vírgula
// parâmetros não precisam de equação
//nesse caso, não importa se é variável ou parâmetro, pq são valores

//EQUATION("C")
/*
Comment
*/
//v[0] = V("min");
//v[1] = V("max");
//v[2] =uniform(v[0], v[1]);
//RESULT(v[2]) 

// uma boa prática é não colocar valores diretos no código
// para explorarmos o espaço paramétrico, não é uma boa ideia
//por isso, criam-se parâmetros para tudo o que seria valor no código

/* 
p_t = theta p^d_t + (1-theta) avg_p_t-1
*/

EQUATION("Price")
v[0] = V("monopoly_degree");  // parameter: monopoly degree
v[1] = V("Cost");
v[2] = V("Desired");
v[3] = AVEL("Price", 1);
v[4] = v[0]*v[2]+(1 - v[0])*v[3];
RESULT(v[4])

EQUATION("Desired")
v[0]= V("Cost"); // Cost of Firm i in period t
v[1]= V("markup"); // parameter: fixed markup
v[2]= (1 + v[1])*v[0];
RESULT(v[2])

EQUATION ("Cost")
v[0]= V("avg"); //parameter
v[1] = V("sd"); //parameter
v[2] = norm(v[0],v[1]); 
RESULT(v[2])

/*
EQUATION("Avg_Price")
RESULT(AVE("Price"))
alternativa para fazer o preço médio é usanod CYCLE
*/

EQUATION("Avg_Price")
v[0]=0;
v[2]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur, "Price");
	v[0] = v[0] +v[1];
	v[2] = v[2] +1; 
}

// Cada cur indica um ponteiro para um objeto
// se um objeto está dentro de outro, precisamos chamar
// CYCLE (cur, "Market")
//CYCLE (cur, cur1, "Firm")
// { para cada objeto/firma, ele vai pegar o v[1] e inicalizar o v[0]
// v[1] = VS(cur1, "Profit");
// v[0] = v[0] + v[1];
// }

RESULT()