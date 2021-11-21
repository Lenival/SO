#!/bin/bash

# Executar "./gerar_dados.sh 100 200 400" onde cada parâmetro é um tamanho de matriz a ser gerado


for i in $(seq 1 10)
do 
	for var in "$@"
	do
		./auxiliar $var $var $var $var 
	done
	sleep 1
done
