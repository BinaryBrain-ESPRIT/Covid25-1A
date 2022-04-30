rm *.o
rm game
if !(find Data) 
then
mkdir Data
fi
make
./game
