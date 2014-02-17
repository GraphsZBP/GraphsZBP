wypelnienie=50
powtorzen=5

echo Rozmiar,Original,Boost - adjacency_matrix,Boost - adjacency_list 1,Boost - adjacency_list 2

for rozmiar in 100 200 300 400 500 600 700 800 900 1000 2000 3000 5000 6000 7000 8000 9000; do
	echo -n $rozmiar,
    for rodzaj in o s w j; do 
		wynik=0
		for i in {1 .. $powtorzen}; do
			czas=`Release/graphs.exe $rodzaj $rozmiar $wypelnienie`
			#echo $czas
			wynik=$(($wynik + $czas))
		done;
		echo -n $(($wynik/$powtorzen)),
	done
	echo ""
done