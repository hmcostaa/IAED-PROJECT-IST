#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define max_airport 40             /*máximo de aeroportos permitidos*/
#define n_country 31
#define n_city 51
#define n_id 4
#define n_codfly 7
#define max_passageiros 100        /*máximo de passageiros permitidos*/
#define max_flys 30000             /*máximo de voos permitidos*/
int n_airport = 0, n_fly = 0;
int dia_atual = 1, mes_atual = 1, ano_atual = 2022;


/*estrutura que armazena todos os aeroportos adicionados*/
struct AIR{
	char id[n_id];
	char country[n_country];
	char city[n_city];
	int number_flys;
};
struct AIR airport[max_airport];
struct AIR holderair;             /*estrutura que ajuda na ordenação dos aeroportos*/


/*estrutura que armazena todos os voos adicionados*/
struct FLYS{
	char flycode[n_codfly];
	char idpartida[n_id];
	char idchegada[n_id];
	int diapartida;
	int mespartida;
	int anopartida;
	int horapartida;
	int minutopartida;
	int horaduracao;
	int minutoduracao;
	int diachegada;
	int meschegada;
	int anochegada;
	int horachegada;
	int minutochegada;
	int capacidade;
};
struct FLYS flys[max_flys];
struct FLYS holderflys;       /*estrutura que ajuda na ordenação dos voos*/


/*função selectionSort que ordena por ordem alfabetica os aeroportos que tenham sido adicionados*/
void selectionSort_v1(){

	int i, j, min;

	for(i = 0; i < n_airport - 1; i++){

		min = i;
		for(j = i + 1; j < n_airport; j++){

			if((strcmp(airport[j].id, airport[min].id)) < 0){
				min = j;
			}
		}

		/*swap nas posiçoes*/
		holderair = airport[min];
		airport[min] = airport[i];
		airport[i] = holderair;
	}
}


/*função selectionSort que ordena por ordem tempo(mais antigo para mais recente) os voos cujo o ID foi indicado no terminal*/
void selectionSort(char v[]){

	int i, j, min;

	for(i = 0; i < n_fly - 1; i++){

		if((strcmp(v, flys[i].idpartida)) == 0){  /*faz com que apenas sejam ordenados os IDS pedidos*/

			min = i;
			for(j = i + 1; j < n_fly; j++){

				if((strcmp(v, flys[j].idpartida)) == 0){   /*faz com que apenas sejam ordenados os IDS pedidos*/

					if(flys[j].diapartida == flys[min].diapartida && flys[j].mespartida == flys[min].mespartida && flys[j].anopartida == flys[min].anopartida){  /*se é o mesmo dia comparamos pelas horas*/
				
						if(flys[j].minutopartida < flys[min].minutopartida && flys[j].horapartida == flys[min].horapartida){
							min = j;
						}

						if(flys[j].horapartida < flys[min].horapartida){
							min = j;
						}
					}

					if(flys[j].diapartida < flys[min].diapartida && flys[j].mespartida == flys[min].mespartida && flys[j].anopartida == flys[min].anopartida){
						min = j;
					}

					if(flys[j].mespartida < flys[min].mespartida && flys[j].anopartida == flys[min].anopartida){
						min = j;
					}

					if(flys[j].anopartida < flys[min].anopartida){
						min = j;
					}
				}
			}

			/*swap nas posiçoes*/
			holderflys = flys[min];
			flys[min] = flys[i];
			flys[i] = holderflys;
		}
	}
}

void selectionSort_v2(char v[]){

	int i, j, min;

	for(i = 0; i < n_fly - 1; i++){

		if((strcmp(v, flys[i].idchegada)) == 0){   /*faz com que apenas sejam ordenados os IDS pedidos*/

			min = i;
			for(j = i + 1; j < n_fly; j++){

				if((strcmp(v, flys[j].idchegada)) == 0){   /*faz com que apenas sejam ordenados os IDS pedidos*/

					if(flys[j].diachegada == flys[min].diachegada && flys[j].meschegada == flys[min].meschegada && flys[j].anochegada == flys[min].anochegada){  /*se é o mesmo dia comparamos pelas horas*/

						if(flys[j].minutochegada < flys[min].minutochegada && flys[j].horachegada == flys[min].horachegada){
							min = j;
						}

						if(flys[j].horachegada < flys[min].horachegada){
							min = j;
						}
					}

					if(flys[j].diachegada < flys[min].diachegada && flys[j].meschegada == flys[min].meschegada && flys[j].anochegada == flys[min].anochegada){
						min = j;
					}

					if(flys[j].meschegada < flys[min].meschegada && flys[j].anochegada == flys[min].anochegada){
						min = j;
					}

					if(flys[j].anochegada < flys[min].anochegada){
						min = j;
					}

				}
			}

			/*swap nas posiçoes*/
			holderflys = flys[min];
			flys[min] = flys[i];
			flys[i] = holderflys;
		}
	}
}


/*função chamada pelo comando 'a' no terminal*/

int aeroporto(){

	int i;

	scanf("%s%s", holderair.id, holderair.country);
	getchar();
	scanf("%[^\n]", holderair.city);  /*executa o scanf ate encontar o final de linhal, '\n'*/

	for(i = 0; i < n_id - 1; i++){
		if(holderair.id[i] < 'A' || holderair.id[i] > 'Z'){  /* este ciclo 'for' verifica se o ID é composto apenas por letras maiusculas */
			printf("invalid airport ID\n");                  /* se não for é printado o erro "invalid airport ID" e o programa volta para a função main */
			return 0;
		}
	}

	if(n_airport >= max_airport){
		printf("too many airports\n");   /* se o numero de aeroportos criados for maior que o valor máximo estabelecido */
		return 0;                        /* por max_airports, o programa não armazena o aeroporto criado, printa o erro "too many airports" */ 
	}                                    /* e volta para a função main */

	for(i = 0; i < n_airport; i++){

		if(strcmp(holderair.id, airport[i].id) == 0){   /* este ciclo 'for' verifica se o ID atribuido ao novo aeroporto já existe num aeroporto já criado */
			printf("duplicate airport\n");              /*  se existir é printado o erro "duplicate airport" e o programa volta para a função main */
			return 0;
		}
	}

	airport[n_airport] = holderair;
	airport[n_airport].number_flys = 0; /* atribui numero de voos 0 para este aeroporto pois foi acabado de ser criado */

	printf("airport %s\n", airport[n_airport].id);   /* se passar por todos os checks de erros sem qualquer problema é armazenado na struct airport, */
                                                     /* printa-se ID do aeroporto e adiciona-se o aeroporto a contagem de aeroportos */
	n_airport++;

	return 0;
}

/*função chamada pelo comando 'l' no terminal*/

int airlist(){

	char c, v[n_id];
	int i, j, contador_erros = 0;

	if((c = getchar()) == '\n'){  /* se o único comando no terminal naquela linha for 'l' o programa chama a função selectionSort_v1 explicada anteriormente */
                                  /* depois printa o id, cidade, país e numero de voos de todos os aeroportos previamente adicionados e armazenados */
		selectionSort_v1();

		for(i = 0; i < n_airport; i++){

			printf("%s %s %s %d\n", airport[i].id, airport[i].city, airport[i].country, airport[i].number_flys);
		}
	}
	else{

		i = 0;

		while(c != '\n'){              /* no caso de existirem mais comandos a frente do caracter 'l' são printados */
			scanf("%s", v);            /* o id, cidade, país e numero de voos de todos os aeroportos pedidos e previamente adicionados */

			c = getchar();

			for(j = 0; j < n_airport; j++){

				if((strcmp(v, airport[j].id)) == 0){

					printf("%s %s %s %d\n", airport[j].id, airport[j].city, airport[j].country, airport[j].number_flys);
				}
				else{
					contador_erros += 1;
				}
			}

			if(contador_erros == n_airport){               /* no caso de o ID não pertencer a nenhum aeroporto previamente adicionado, ou seja, */
				printf("%s: no such airport ID\n", v);     /* fazendo com que contador_erros = n_airport, printa o erro "no such airport ID" */
			}
			contador_erros = 0;
		}
	}

	return 0;
}

/*função chamada pelo comando 'v' no terminal*/

int flylist(){

	int i, contador = 0, len;
	char c;

	if((c = getchar()) == '\n'){      /* se o único comando no terminal naquela linha for 'v' o programa printa todos os voos adicionados previamente por ordem de adição */  

		for(i = 0; i < n_fly; i++){

			printf("%s %s %s ", flys[i].flycode, flys[i].idpartida, flys[i].idchegada);

            /* sendo que os valores temporais são de tipo int, algoritmo a seguir vai verificar se algum nṹmero é maior que 10 */
			if(flys[i].diapartida < 10){
				printf("0%d-", flys[i].diapartida);    /* no caso de não ser maior que 10 é colocado um 0 atrás do seu valor */
			}
			else{
				printf("%d-", flys[i].diapartida);
			}

			
			if(flys[i].mespartida < 10){
				printf("0%d-", flys[i].mespartida);
			}
			else{
				printf("%d-", flys[i].mespartida);
			}

			printf("%d ", flys[i].anopartida);

			if(flys[i].horapartida < 10){
				printf("0%d:", flys[i].horapartida);
			}
			else{
				printf("%d:", flys[i].horapartida);
			}


			if(flys[i].minutopartida < 10){
				printf("0%d\n", flys[i].minutopartida);
			}
			else{
				printf("%d\n", flys[i].minutopartida);
			}
		}

		return 0;
	}

	else{     /* se 'v' não for o único comando no terminal o programa entende que é pretendido adicionar um novo voo */

		scanf("%s %s %s", holderflys.flycode, holderflys.idpartida, holderflys.idchegada);    
		scanf("%d-%d-%d", &holderflys.diapartida, &holderflys.mespartida, &holderflys.anopartida);  /* estes scanfs atribuem à struct holderflys os valores colocados à frente de 'v' */
		scanf("%d:%d", &holderflys.horapartida, &holderflys.minutopartida);                         /* para a seguir serem testados antes de serem armazenados no sistema */
		scanf("%d:%d", &holderflys.horaduracao, &holderflys.minutoduracao);
		scanf("%d", &holderflys.capacidade);

		len = strlen(holderflys.flycode);    /* recebe o tamanho do código de voo que se pretende adicionar */

		for(i = 0; i < 2; i++){
			if(holderflys.flycode[i] < 'A' || holderflys.flycode[i] > 'Z'){    /* se os dois primeiros caracteres do código de voo não forem letras maiúsculas */
				printf("invalid flight code\n");                               /* é printado o erro "invalid flight code" e o programa volta para a função main */
				return 0;
			}
		}

		for(i = 2; i < len; i++){                        /* se o resto dos digitos do código de voo não forem números é printado o erro "invalid flight code" */
                                                         /* e o programa volta para a função main */
			if((isdigit(holderflys.flycode[i])) == 0){
				printf("invalid flight code\n");
				return 0;
			}

		}


		for(i = 0; i < n_fly; i++){

			if((strcmp(holderflys.flycode, flys[i].flycode)) == 0){  /* o código de voo do voo que se pretende criar é comparado com todos os voos previamente adicionados */
                                                                     /* e que tenham o mesmo código de voo */
				if(holderflys.diapartida == flys[i].diapartida && holderflys.mespartida == flys[i].mespartida && holderflys.anopartida == flys[i].anopartida){
					printf("flight already exists\n");   
					return 0;                              /* se para o mesmo código de voo o dia, mes e ano de partida forem iguais a um voo previamente adicionado */
				}                                          /* é printado o erro "flight already exists" e o programa volta para a função main */
			}
		}

		for(i = 0; i < n_airport; i++){
			if((strcmp(holderflys.idpartida, airport[i].id)) == 0){  /* o ID do aeroporto de partida do voo que se pretende adicionar é comparado com o ID de todos os */
				contador += 1;                                       /* aeroportos previamente adicionados, se forem iguais o contador é incrementado */
			}
		}
		if(contador == 0){
			printf("%s: no such airport ID\n", holderflys.idpartida);   /* se no final o contador for igual a 0 significa que o ID do aeroporto de partida do voo que se pretende adicionar */
			return 0;                                                   /* não existe pelo que printa o erro "no such airport ID" e o programa volta para a função main */
		}

		contador = 0; /* contador volta a ser igual a 0 para ser utilizado novamente */

		for(i = 0; i < n_airport; i++){
			if((strcmp(holderflys.idchegada, airport[i].id)) == 0){ /* o ID do aeroporto de chegada do voo que se pretende adicionar é comparado com o ID de todos os */
				contador += 1;                                      /* aeroportos previamente adicionados, se forem iguais o contador é incrementado */
			}
		}
		if(contador == 0){
			printf("%s: no such airport ID\n", holderflys.idchegada);  /* se no final o contador for igual a 0 significa que o ID do aeroporto de chegada do voo que se pretende adicionar */
			return 0;                                                  /* não existe pelo que printa o erro "no such airport ID" e o programa volta para a função main */
		}

	
		if(n_fly >= max_flys){
			printf("too many flights\n");    /* se o número de voos adicionados ultrapassar o valor máximo previamente estabelecido por max_flys */
			return 0;                        /* é printado o erro "too many flys" e o programa volta para a função main */
		}

		if(holderflys.anopartida < ano_atual){  
			printf("invalid date\n");
			return 0;
		}

		if(ano_atual == holderflys.anopartida){
			if(holderflys.mespartida < mes_atual){
				printf("invalid date\n");
				return 0;
			}
			if(holderflys.mespartida == mes_atual && holderflys.diapartida < dia_atual){  /* este conjunto de ifs verifica que a data de partida é menor que a data atual do sistema */
				printf("invalid date\n");                                                 /* se for é printado o erro "invalid date" e o programa volta para a função main */
				return 0;
			}
		}

		if(ano_atual < holderflys.anopartida){
			if(mes_atual == holderflys.mespartida && holderflys.diapartida > dia_atual){
				printf("invalid date\n");
				return 0;
			}
			if(holderflys.mespartida > mes_atual){    /* estes conjunto de ifs verifica se a data de partida acontece um ano depois relativamente à data atual do sistema */
				printf("invalid date\n");             /* se acontecer um ano depois é printado o erro "invalid date" e o programa volta para a função main */
				return 0;
			}
		}

		if(holderflys.horaduracao > 12){  /* verifica se a duração de voo é maior que 12 */
			printf("invalid duration\n"); /* se maior é printado o erro "invalid duration" */
			return 0;
		}

		if(holderflys.horaduracao == 12){
			if(holderflys.minutoduracao > 0){   /* verifica se a duração de voo é maior que 12 */
				printf("invalid duration\n");   /* se maior é printado o erro "invalid duration" */
				return 0;
			}
		}

		if(holderflys.capacidade < 10 || holderflys.capacidade > 100){  /* se a capacidade do voo que se pretende adicionar for menor que 10 ou maior que 100 */
			printf("invalid capacity\n");                               /* é printado o erro "invalid capacity" */
			return 0;
		}


		flys[n_fly] = holderflys;  /* passando por todos os testes de erro o voo pode finalmente ser armazenado na struct flys */

		for(i = 0; i < n_airport; i++){

			if((strcmp(holderflys.idpartida, airport[i].id)) == 0){  /* incrementa o número de voos que têm partida naquele aeroporto */
				airport[i].number_flys++;
			}
		}


		n_fly += 1;  /* número de voos total também é incrementado */
	}

	return 0;
}	

/*função chamada pelo comando 'p' no terminal*/

int listerfly(){

	int i, contador = 0;
	char v[n_id];

	scanf("%s", v);   /* o vetor v recebe o ID partida pretendido */

	for(i = 0; i < n_airport; i++){

		if((strcmp(airport[i].id, v)) == 0){  /* este ciclo for verifica se o ID fornecido pertence a um aeroporto previamente adicionado */
                                              /* no caso de pretencer o contador é incrementado */
			contador += 1;
		}
	}

	if(contador == 0){
		printf("%s: no such airport ID\n", v);   /* se o ID fornecido não pertencer a nenhum aeroporto na struct airport o contador nunca é incrementado */
		return 0;                                /* pelo que no final do ciclo for o contador tem o valor 0 */
	}                                            /* se isso acontecer é printado o erro "no such airport ID" e o programa volta para a função main */

	selectionSort(v);   /* é chamada a função selectionSort que recebe o vetor v e ordena por ordem temporal todos os voos com o mesmo ID que o fornecido */

	for(i = 0; i < n_fly; i++){

		if((strcmp(flys[i].idpartida, v)) == 0){  /* os voos são printados da mesma maneira verificando novamente a casa das dezenas de cada int */

			printf("%s %s ", flys[i].flycode, flys[i].idchegada);

			if(flys[i].diapartida < 10){
				printf("0%d-", flys[i].diapartida);
			}
			else{
				printf("%d-", flys[i].diapartida);
			}


			if(flys[i].mespartida < 10){
				printf("0%d-", flys[i].mespartida);
			}
			else{
				printf("%d-", flys[i].mespartida);
			}

			printf("%d ", flys[i].anopartida);

			if(flys[i].horapartida < 10){
				printf("0%d:", flys[i].horapartida);
			}
			else{
				printf("%d:", flys[i].horapartida);
			}


			if(flys[i].minutopartida < 10){
				printf("0%d\n", flys[i].minutopartida);
			}
			else{
				printf("%d\n", flys[i].minutopartida);
			}

		}
	}

	

	return 0;
}

/*função chamada pelo comando 'c' no terminal*/

int listerfly_v2(){

	int i, contador = 0;
	char v[n_id];

	scanf("%s", v);   /* o vetor v recebe o ID partida pretendido */

	for(i = 0; i < n_airport; i++){

		if((strcmp(airport[i].id, v)) == 0){   /* este ciclo for verifica se o ID fornecido pertence a um aeroporto previamente adicionado */
                                               /* no caso de pretencer o contador é incrementado */
			contador += 1;
		}
	}

	if(contador == 0){
		printf("%s: no such airport ID\n", v);   /* se o ID fornecido não pertencer a nenhum aeroporto na struct airport o contador nunca é incrementado */
		return 0;                                /* pelo que no final do ciclo for o contador tem o valor 0 */
	}                                            /* se isso acontecer é printado o erro "no such airport ID" e o programa volta para a função main */

	for(i = 0; i < n_fly; i++){

		if((strcmp(v, flys[i].idchegada)) == 0){  /* este ciclo for é responsável pelo cálculo da hora de chegada dos voos com o mesmo ID de chegada que o ID fornecido */

			flys[i].diachegada = flys[i].diapartida;
			flys[i].meschegada = flys[i].mespartida;
			flys[i].anochegada = flys[i].anopartida;
			flys[i].horachegada = flys[i].horapartida + flys[i].horaduracao;
			flys[i].minutochegada = flys[i].minutopartida + flys[i].minutoduracao;

			if(flys[i].mespartida == 1 || flys[i].mespartida == 3 || flys[i].mespartida == 5 || flys[i].mespartida == 7 || flys[i].mespartida == 8 || flys[i].mespartida == 10 || flys[i].mespartida == 12){

				if(flys[i].minutochegada >= 60){
					flys[i].horachegada += 1;
					flys[i].minutochegada -= 60;    /* para meses de 31 dias é feito este cálculo incremental que vai adicionando minutos e horas */
				}                                   /* e incrementado devidamente linhas temporais maiores */

				if(flys[i].horachegada >= 24){
					flys[i].diachegada += 1;
					flys[i].horachegada -= 24;
				}

				if(flys[i].diachegada > 31){
					flys[i].diachegada = 1;
					flys[i].meschegada += 1;
				}

				if(flys[i].meschegada > 12){
					flys[i].meschegada = 1;
					flys[i].anochegada += 1;
				}
			}

			if(flys[i].mespartida == 4 || flys[i].mespartida == 6 || flys[i].mespartida == 9 || flys[i].mespartida == 11){

				if(flys[i].minutochegada >= 60){
					flys[i].horachegada += 1;
					flys[i].minutochegada -= 60;     /* para meses de 30 dias é feito este cálculo incremental que vai adicionando minutos e horas */
				}                                    /* e incrementado devidamente linhas temporais maiores */

				if(flys[i].horachegada >= 24){
					flys[i].diachegada += 1;
					flys[i].horachegada -= 24;
				}

				if(flys[i].diachegada > 30){
					flys[i].diachegada = 1;
					flys[i].meschegada += 1;
				}
			}

			if(flys[i].mespartida == 2){

				if(flys[i].minutochegada >= 60){  /* para o mês de fevereiro com 28 dias */
					flys[i].horachegada += 1;
					flys[i].minutochegada -= 60;
				}

				if(flys[i].horachegada >= 24){
					flys[i].diachegada += 1;
					flys[i].horachegada -= 24;
				}

				if(flys[i].diachegada > 28){
					flys[i].diachegada = 1;
					flys[i].meschegada += 1;
				}
			}
		}
	}

	selectionSort_v2(v);   /* depois de calculado quando cada voo chega, é chamada a função selectionSort_v2 que ordena por ordem de chegada os voos */
                           /* com o mesmo ID de chegada que o ID fornecido */

	for(i = 0; i < n_fly; i++){

		if((strcmp(flys[i].idchegada, v)) == 0){    /* os voos são printados da mesma maneira verificando novamente a casa das dezenas de cada int */

			printf("%s %s ", flys[i].flycode, flys[i].idpartida);

			if(flys[i].diachegada < 10){
				printf("0%d-", flys[i].diachegada);
			}
			else{
				printf("%d-", flys[i].diachegada);
			}


			if(flys[i].meschegada < 10){
				printf("0%d-", flys[i].meschegada);
			}
			else{
				printf("%d-", flys[i].meschegada);
			}

			printf("%d ", flys[i].anochegada);

			if(flys[i].horachegada < 10){
				printf("0%d:", flys[i].horachegada);
			}
			else{
				printf("%d:", flys[i].horachegada);
			}


			if(flys[i].minutochegada < 10){
				printf("0%d\n", flys[i].minutochegada);
			}
			else{
				printf("%d\n", flys[i].minutochegada);
			}
		}
	}


	return 0;
}

/*função chamada pelo comando 't' no terminal*/

int changetime(){

	int dia, mes, ano;

	scanf("%d-%d-%d", &dia, &mes, &ano);  /* atribui às variaveis que recebem tipo int, a nova data pretendida para o sistema */

	if(ano < ano_atual){
		printf("invalid date\n");    
		return 0;
	}

	if(ano_atual == ano){
		if(mes < mes_atual){
			printf("invalid date\n");
			return 0;
		}
		if(mes == mes_atual && dia < dia_atual){
			printf("invalid date\n");             /* estes ciclos if verificaram se a data fornecida é mais antiga que a do sistema */
			return 0;                             /* no caso de ser é printado o erro "invalid date" e o programa volta para a função main */
		}
	}

	if(ano_atual < ano){
		if(mes_atual == mes && dia > dia_atual){
			printf("invalid date\n");
			return 0;
		}
		if(mes > mes_atual){                  /* estes ciclos if verificaram se a data fornecida é um ano maior que a data atual */
			printf("invalid date\n");         /* no caso de ser é printado o erro "invalid date" e o programa volta para a função main */
			return 0;
		}
	}



	dia_atual = dia; 
	mes_atual = mes;   /* passando todos os checks de erros a data atual do sistema é substituida pela data fornecida */
	ano_atual = ano;

	if(dia_atual < 10){
		printf("0%d-", dia_atual);
	}
	else{
		printf("%d-", dia_atual);    /* é printada a data tendo novamente atenção ao facto de que se o número é menor que 10 */
	}                                /* deve ser printado com um 0 atrás */

			
	if(mes_atual < 10){
		printf("0%d-", mes_atual);
	}
	else{
		printf("%d-", mes_atual);
	}

	printf("%d\n", ano_atual);


	return 0;
}


int main(){

	int i = 1;
	char n;

	while(i == 1){

		n = getchar();   /* atribui a n o primeiro comando desejado pelo o ultilizador */
		                 /* a partir dai o n é comparado com todos as opções de comando disponiveis */
		if(n == 'q'){  
			i = 0;
		}                /* no caso de n ser igual a 'q' o valor de i é trocado para 0 acabando o ciclo while e terminando o programa */
		
		if(n == 'a'){
			getchar();
			aeroporto();
		}

		if(n == 'l'){
			airlist();
		}

		if(n == 'v'){
			flylist();
		}

		if(n == 'p'){
			listerfly();
		}

		if(n == 'c'){
			listerfly_v2();
		}

		if(n == 't'){
			changetime();
		}
	}

	return 0;
}
