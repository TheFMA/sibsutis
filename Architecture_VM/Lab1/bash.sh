#Date
echo -n "Data: "
echo $(date '+%Y-%m-%d')

#Account name
echo -n "Account name: "
echo "$USER"

#PC domain name
echo -n "PC domain name: "
echo -n `cat /proc/sys/kernel/hostname`

#
#echo -n "PC domain name: "
#cat /proc/cpuinfo | grep model
echo -ne "\n"
echo -n "Processor:"
echo -ne "\n\t1. "
grep -m 1 'model name' /proc/cpuinfo

echo -ne "\t2. "
echo -n "Architecture: "
dpkg --print-architecture

echo -ne "\t3. "
cat /proc/cpuinfo | grep -m 1 "cpu MHz"

echo -ne "\t4. "
lscpu | grep "CPU(s):"

echo -ne "\t5. "
lscpu | grep "Thread(s) per core:"

echo
echo -n "RAM:"
free -h

echo
echo -n "Жесткий дистк:"
df -h /home
df -h --total | grep "total"

echo
echo "Сетевые интерфейсы системы"
x=0
for i in $(ifconfig -a | grep "flags" | awk '{print $1}')
do
echo $i
x=$(( $x + 1 ))
done
echo $x
#ifconfig -a | grep "flags" | awk '{print $1}'
#res=$(ls -l)
#echo "$res"
#echo $(echo "$res"|wc -l)
echo
echo "MAC"
ifconfig -a | grep "ether" | awk '{print $2}'
echo
echo "IP-адреса"
ifconfig -a | grep "inet" | awk '{print $2}'
echo
echo "Скорость соединения"
ip -4 -0 a | grep "qlen" | awk '{print $13}'




