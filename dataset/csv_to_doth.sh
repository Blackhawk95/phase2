#####!bin/bash
# USAGE : ./csv_to_doth input_file.csv output_file.h
# TO.DO : change the hardcoded 3, also the csv is currently space seperated
var=`tail -n 1 $1 | awk -F' ' '{print $3}'`
begpart1="long long int arr["
begpart2="][3]={{"
endpart="}};"

sed ':a;N;$!ba;s/\n/},{/g' $1 > $2 # remove "linefeed and not cariage return" and replace with },{
sed -i 's/ /,/g' $2 # remove space and replace it with ,
echo $endpart >> $2 # add endpart
sed -i ':a;N;$!ba;s/\n//g' $2 # remove \n due to endpart
sed -i "1s;^;$begpart1$var$begpart2;" $2 #combine the beggining part

