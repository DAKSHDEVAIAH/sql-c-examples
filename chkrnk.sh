#!/bin/bash
rm results.txt
stockslist='ls *.dat'
for stock in $stockslist
do
	./readranking $stock >>results.txt
done	
