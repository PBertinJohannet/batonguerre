make -f Makefile.debug clean
make -f Makefile.debug
read -p "Do you wish to run a static check ?" yn
case $yn in
	[Yy]* ) cppcheck ~/CLionProjects/batonguerre/ --force --enable=warning >check_result.txt;;
esac
read -p "Do you wish to run the program with valgrind ?" yn
case $yn in
	[Yy]* )   ./valdebug;;
	* ) echo "Please answer yes or no.";;
esac
read -p "do you want to run the programm without valgrind ? " y
case $y in 
	[Yy]* ) ./battle;;
	* ) echo "see you later then";;
esac
