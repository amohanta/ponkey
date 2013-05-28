for i in $(ls)
do
	echo $i
	if [ -f $i ]
	then
		cat $i | grep $1
	fi
done
