#!/bin/bash

make rebuild

clear

echo -e "Exercice n°1:\n"

./ex1/quantification images/mon_image.pgm images/ex1.pgm
./ex1/quantification images/mon_image.ppm images/ex1.ppm
./ex1/quantification images/mon_image_bin.ppm images/ex1_bin.ppm

echo -e "\n------------------------\n"
echo -e "Exercice n°2:\n"

./ex2/quantification images/mon_image.pgm images/ex2.pgm
./ex2/quantification images/mon_image.ppm images/ex2.ppm
./ex2/quantification images/mon_image_bin.ppm images/ex2_bin.ppm

echo -e "\n------------------------\n"
echo -e "Exercice n°3:\n"

./ex3/quantification images/mon_image.pgm images/ex3.pgm
./ex3/quantification images/mon_image.ppm images/ex3.ppm
./ex3/quantification images/mon_image_bin.ppm images/ex3_bin.ppm
