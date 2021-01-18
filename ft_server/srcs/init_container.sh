service mysql start

# Config Access
chown -R www-data /var/www/*
chmod -R 755 /var/www/*

# Generate website folder
mkdir /var/www/siteinternet && touch /var/www/siteinternet/index.php
echo "<?php phpinfo(); ?>" >> /var/www/siteinternet/index.php

# SSL
mkdir /etc/nginx/ssl
openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/nginx/ssl/siteinternet.pem -keyout /etc/nginx/ssl/siteinternet.key -subj "/C=FR/ST=Paris/L=Paris/O=42 School/OU=adesvall/CN=siteinternet"

# Config NGINX
mv ./tmp/nginx-conf /etc/nginx/sites-available/siteinternet
ln -s /etc/nginx/sites-available/siteinternet /etc/nginx/sites-enabled/siteinternet
rm -rf /etc/nginx/sites-enabled/default

# Config MYSQL
echo "CREATE DATABASE wordpress;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost' WITH GRANT OPTION;" | mysql -u root --skip-password
echo "update mysql.user set plugin='mysql_native_password' where user='root';" | mysql -u root --skip-password
echo "FLUSH PRIVILEGES;" | mysql -u root --skip-password

# DL phpmyadmin
mkdir /var/www/siteinternet/phpmyadmin
wget https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-all-languages.tar.gz
tar -xvf phpMyAdmin-4.9.0.1-all-languages.tar.gz --strip-components 1 -C /var/www/siteinternet/phpmyadmin
mv ./tmp/phpmyadmin.inc.php /var/www/siteinternet/phpmyadmin/config.inc.php

# DL wordpress
cd /tmp/
wget -c https://wordpress.org/latest.tar.gz
tar -xvzf latest.tar.gz
mv wordpress/ /var/www/siteinternet
mv /tmp/wp-config.php /var/www/siteinternet/wordpress

service php7.3-fpm start
service nginx start
bash
