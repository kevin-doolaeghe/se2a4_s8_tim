#!/bin/bash

make rebuild

clear

echo -e "Exercice n°1:\n"

./ex1/stenographie images/mon_image.ppm images/ex1.ppm bonjour à tous

echo -e "\n------------------------\n"
echo -e "Exercice n°2:\n"

./ex2/stenographie images/ex1.ppm

echo -e "\n------------------------\n"
echo -e "Exercice n°3:\n"

./ex3/stenographie images/mon_image.ppm images/ex3.ppm bonjour à nouveau
