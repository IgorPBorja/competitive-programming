## prepend file problems/template.hpp to another file
## usage: ./prepend.sh file.cpp

cat "~/competitive-programming/problems/template.hpp" > $1.tmp
cat $1 >> $1.tmp
mv $1.tmp $1
