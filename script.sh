g++ -O3 yoannC.cpp -o prog
echo "C"
./prog < data/c.txt > c.out
g++ -O3 yoannD.cpp -o prog
echo "D"
./prog < data/d.txt > d.out
g++ -O3 yoann.cpp -o prog
echo "A"
./prog < data/a.txt > a.out
echo "B"
./prog < data/b.txt > b.out
echo "F"
./prog < data/f.txt > f.out
g++ -O3 -DDIVIDE yoann.cpp -o prog
echo "E"
./prog < data/e.txt > e.out

rm prog