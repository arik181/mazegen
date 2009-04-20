#!/bin/sh

sed "/assignment/ s/assignment/$2/g" header.txt >> header.txt.tmp

for x in *.h; do echo "/*** ${x} " >> ./$1/${x}; done
for x in *.h; do cat header.txt.tmp >> ./$1/${x}; done
for x in *.h; do echo "* Purpose: " >> ./$1/${x}; done
for x in *.h; do echo "* " >> ./$1/${x}; done
for x in ./$1/*.h; do vi ${x}; done
for x in *.h; do echo "* " >> ./$1/${x}; done
for x in *.h; do echo "* ***/" >> ./$1/${x}; done
for x in *.h; do echo "" >> ./$1/${x}; done
for x in *.h; do cat ${x} >> ./$1/${x}; done


for x in *.cpp; do echo "/*** ${x}" >> ./$1/${x}; done
for x in *.cpp; do cat header.txt.tmp ./$1/${x} >> ./$1/${x}; done
for x in *.cpp; do echo "* Purpose:" >> ./$1/${x}; done
for x in *.cpp; do echo "* " >> ./$1/${x}; done
for x in ./$1/*.cpp; do vi ${x}; done
for x in *.cpp; do echo "* " >> ./$1/${x}; done
for x in *.cpp; do echo "* ***/" >> ./$1/${x}; done
for x in *.cpp; do echo "" >> ./$1/${x}; done
for x in *.cpp; do cat ${x} >> ./$1/${x}; done

rm -rf header.txt.tmp
