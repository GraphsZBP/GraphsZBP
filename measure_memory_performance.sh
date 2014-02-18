wypelnienie=50
powtorzen=4

echo -e Rozmiar'\t'Original'\t'Boost - adjacency_matrix'\t'Boost - adjacency_list 1'\t'Boost - adjacency_list 2

declare -A array
for constant in in 100 500 1000 1500 2000 2500 3000 3500 4000 4500 5000 6000 7000 8000 9000 10000 11000 12000
do
    array[$constant]=1
done

for rozmiar in {0..12000..100}; do
	echo -en $rozmiar'\t'
	if [[ ${array[$rozmiar]} ]]; then
		for rodzaj in o s w j; do 
			wynik=0
			for i in {1 .. $powtorzen}; do
				#echo "Release/graphs.exe $rodzaj $rozmiar $wypelnienie"
				czas=`Release/graphs.exe $rodzaj $rozmiar $wypelnienie`
				#echo $czas $?
				wynik=$(($wynik + $czas))
			done;
			echo -en $(($wynik/$powtorzen))'\t'
		done
	fi
	echo ""
done