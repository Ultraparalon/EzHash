MAKE="Makefile"
MFILES="CMakeFiles"
 
if [ -f "$MAKE" ];
then
	make clean
	rm -f $MAKE
	echo "$MAKE removed"
else
	echo "$MAKE is already removed"
fi

if [ -d "$MFILES" ];
then
	rm -r $MFILES
	echo "MFILES removed"
else
	echo "$MFILES is already removed"
fi

rm -f cmake_install.cmake CMakeCache.txt

cd libraries/libft
sh cleaner.sh
