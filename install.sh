cd ./bin;
gcc POT.c -o POT;
gcc SUB.c -o SUB;
cd ..;
touch .envir;
echo -e 'export PATH=$PATH:'$(pwd)'/bin'> .envir;
echo -e 'export lib_PBE='$(pwd)'/lib/PBE' >> .envir;
cat .envir >> ~/.bashrc;
source ~/.bashrc
rm .envir;
echo "Done! Restart the Terminal to apply the change."
