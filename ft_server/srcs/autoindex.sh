#!/bin/bash

if [ $# = 1 ]
then
# Config autoindex
if [ $1 = "off" ]
then
        echo "autoindex desactivated"
        sed -i 's/autoindex on;/autoindex off;/' /etc/nginx/sites-available/monsiteweb
	service nginx restart
elif [ $1 = "on" ]
then
	echo "autoindex activated"
        sed -i 's/autoindex off;/autoindex on;/' /etc/nginx/sites-available/monsiteweb
	service nginx restart
fi
else
	echo "arg1 must be \"on\" or \"off\""
fi

