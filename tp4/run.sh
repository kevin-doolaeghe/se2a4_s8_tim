#!/bin/bash

make rebuild

clear

echo -e "Chiffrement:\n"

./ex1/chiffrement secret bonjour à tous

echo -e "\n------------------------\n"
echo -e "Déchiffrement:\n"

./ex2/dechiffrement secret TSPASNJ à MGYU
