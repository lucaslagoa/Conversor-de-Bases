#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

FILE *arq,*arq1; //abertura dos arquivos para a leitura e impressão dos números que se deseja realizar a conversão
int binoct_decimal (char *numerobase, int base, int basedestino) { //função utilizada para a conversão das bases binário ou octal para a base decimal
	int numero,soma=0,i,j;
	numero=strlen(numerobase); 
	j=0;
	for(i=numero-1;i>=0;i--){ 
		soma=soma+(numerobase[j]-48)*pow(base,i); 
		j++;
	}
	if (basedestino==10) {
		printf("%d",soma); 
		fprintf(arq1,"%d",soma);
	}
	return soma;
}
int hexa_decimal (char *numerobase, int base, int basedestino) { //função utilizada para a conversão da base hexadecimal para a base decimal
	int inteiro,i,j,numero,soma=0;
	numero=strlen(numerobase);
	j=0;
	for(i=numero-1;i>=0;i--){
		switch(numerobase[j]) {
			case 'A':
				inteiro=10;
				break;
			case 'B':
				inteiro=11;
				break;
			case 'C':
				inteiro=12;
				break;
			case 'D':
				inteiro=13;
				break;
			case 'E':
				inteiro=14;
				break;
			case 'F':
				inteiro=15;
				break;
			default:
				inteiro=numerobase[j]-48;
		}
		soma=soma+(inteiro*pow(base,i));
		j++;
	}
	if (basedestino==10) {
		printf("%d",soma);
		fprintf(arq1,"%d", soma);
	}
	
	return soma;
} 
void dec_bases (int numero, int base) { //função de conversão da base decimal para as bases binário ou octal
	int resto,posicao=0,i=0;
    char inverter[100];
    while(numero!=0){
		resto=numero%base;
		numero=(numero/base);
		inverter[posicao]=resto;
		posicao++;
	}
	for(i=(posicao-1);i>=0;i--){
		fprintf(arq1,"%d",inverter[i]);
		printf("%d",inverter[i]);
	} 
	
}
void dec_hexa (int numero) { //função de conversão de decimal para hexadecimal
	    int resto=0,i=0;
        char inverter[100];
        int posicao=0;
        while(numero!=0){
            resto=numero%16;
            numero=(numero/16);
            inverter[posicao]=resto;
            posicao++;
        }
            for(i=(posicao-1);i>=0;i--) {
                switch(inverter[i]) { 
                        case 10:
                        printf("A");
                        fprintf(arq1,"A");
                        break;
                        case 11:
                        printf("B");
                        fprintf(arq1,"B");
                        break;
                        case 12:
                        printf("C");
                        fprintf(arq1,"C");
                        break;
                        case 13:
                        printf("D");
                        fprintf(arq1,"D");
                        break;
                        case 14:
                        printf("E");
                        fprintf(arq1,"E");
                        break;
                        case 15:
                        printf("F");
                        fprintf(arq1,"F");
                        break;
                        default:
                        fprintf(arq1,"%d",inverter[i]);
                        printf("%d",inverter[i]);
                }
    }
}           
           
int main () {
	int quantidade,base,basedestino,soma,i; //declaração das variáveis que serão utilizadas no código 
	char numerobase[100],nomearquivo[100]; //essa variável foi utilizada para ler o número do arquivo
	printf("Calculadora de conversão de bases\n");
	printf("A ordem de digitação no arquivo é: Quantidade de conversões, base do número a ser convertido, o número e a base destino\n");
	printf("Digite o nome do arquivo que você criou onde está localizado as informações sobre a conversão(não se esqueça do .txt):\n");
	scanf("%s",nomearquivo); //nome do arquivo que o usuário deverá digitar
	arq=fopen(nomearquivo,"r"); //abertura do arquivo como leitura das bases destino, origem e o número
    fscanf(arq,"%d",&quantidade); //leitura da quantidade de vezes de conversões a serem realizadas 
    arq1=fopen("arquivo1.txt","w"); //abertura do segundo arquivo para a impressão os resultados obtidos durante o programa
    printf("E o(s) número(s) após a conversão são:\n");
    fprintf(arq1,"Base destino / Número convertido");
   for(i=0;i<quantidade;i++) { //estrutura de repetição para fazer várias conversões de acordo com o arquivo
		fscanf(arq,"%d",&base);
		fscanf(arq,"%s",numerobase);
		fscanf(arq,"%d",&basedestino);
		
		if (base==basedestino) {
			printf("A base de origem e a base destino são as mesmas, então o número continua %s",numerobase);
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			fprintf(arq1,"%s",numerobase);
		}
		
		if ((base==2 || base==8)  && basedestino==10) {
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			soma=binoct_decimal(numerobase,base,basedestino); 
		}
		if (base==16 && basedestino==10){
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			hexa_decimal(numerobase,base,basedestino);
		}
		if (base==10 && (basedestino==2 || basedestino==8)){
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			soma=atoi(numerobase);
			dec_bases(soma,basedestino);
		}
		if (base==10 && basedestino==16) {
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			soma=atoi(numerobase);
			dec_hexa(soma);
		}
		
		if ((base==2 && basedestino==8) || (base==8 && basedestino==2)) {
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			soma=binoct_decimal(numerobase,base,basedestino);
			dec_bases(soma,basedestino);
		}
		if ((base==2 && basedestino==16) || (base==8 && basedestino==16)) {
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			soma=binoct_decimal(numerobase,base,basedestino);
			dec_hexa(soma);
		}
		
		if ((base==16 && basedestino==2) || (base==16 && basedestino==8)) {
			fprintf(arq1,"\n");
			fprintf(arq1,"%d\t\t",basedestino);
			soma=hexa_decimal(numerobase,base,basedestino);
			dec_bases(soma,basedestino);
		}
		printf("\n");
	}	
	fclose(arq); //fechamento do arquivo que foi aberto para a leitura dos números
	return 0;
}



