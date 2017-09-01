make -f Makefile.debug clean
make -f Makefile.debug
cppcheck ./
read -p "Do you wish to run the program?" yn
case $yn in
	[Yy]* ) valgrind tool=memcheck ./game;;
	[Nn]* ) exit;;
	* ) echo "Please answer yes or no.";;
esac
