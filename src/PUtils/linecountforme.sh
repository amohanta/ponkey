for i in $(ls);
do 
	if [ -f $i ]; then 
		str=$(wc -l $i)
		echo "$str"
	 fi;
done
