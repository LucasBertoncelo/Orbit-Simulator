# Orbit-Simulator
Simulador de Mecânica Orbital
Projeto de Engenharia de Software - Engenharia Aeroespacial / Computação
1. Visão Geral do Projeto
Este projeto consiste num simulador de órbita 2D que utiliza uma arquitetura híbrida
para maximizar a performance e a clareza na visualização de dados. O sistema é
dividido em dois módulos principais:
Motor de Física (Back-end): Desenvolvido em Linguagem C para garantir
cálculos de alta precisão e baixo consumo de recursos (ideal para hardware
limitado).
Visualizador (Front-end): Desenvolvido em Python utilizando a biblioteca
Matplotlib para transformar telemetria bruta em gráficos interpretáveis.
Linguagem C
(Cálculo Numérico)
Python
(Visualização)
Linux / Fedora
(Ambiente)
VS Code
(IDE)
3. Metodologia Científica
A simulação baseia-se na Lei da Gravitação Universal de Newton:
F = G * (m1 * m2) / r²
Para a atualização das coordenadas no tempo, foi implementado o Método de Euler,
onde a posição e a velocidade são integradas passo a passo (step-by-step) com um
intervalo de tempo (dt) de 1 segundo.
4. Estrutura de Ficheiros
OrbitSimulator.c: Código fonte do motor físico.
plotar_orbita.py: Script de renderização gráfica.
telemetria_satelite.csv: Base de dados gerada em tempo real (interface
entre C e Python).

Este projeto foi desenvolvido com ajuda de IA, pretendo aperfeiçoa-lo principalmente o front-end, fiz esse projeto como o objeto de estudo para melhorar o meu conhecimento e também como portifólio, parcerias podem ser bem vindas!!!
