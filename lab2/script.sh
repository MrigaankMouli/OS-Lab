echo the name of this script is $0
echo Please enter your name:
read name
echo your name is $name
echo this script places the date into a temporary file
echo called $name.$$
date > $name.$$
ls 
