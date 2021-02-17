service mysql start

# Generate website folder
mkdir /var/www/monsiteweb && touch /var/www/monsiteweb/index.php
echo "<?php phpinfo(); ?>" >> /var/www/monsiteweb/index.php

# SSL
mkdir /etc/nginx/ssl
openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/nginx/ssl/monsiteweb.pem -keyout /etc/nginx/ssl/monsiteweb.key -subj "/C=FR/ST=Paris/L=Paris/O=42 School/OU=adesvall/CN=monsiteweb"

# Config NGINX
mv ./tmp/nginx-conf /etc/nginx/sites-available/monsiteweb
ln -s /etc/nginx/sites-available/monsiteweb /etc/nginx/sites-enabled/monsiteweb
rm -rf /etc/nginx/sites-enabled/default

# Config MYSQL
echo "CREATE DATABASE wordpress;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost' WITH GRANT OPTION;" | mysql -u root --skip-password
echo "update mysql.user set plugin='mysql_native_password' where user='root';" | mysql -u root --skip-password
echo "FLUSH PRIVILEGES;" | mysql -u root --skip-password

# DL phpmyadmin
mkdir /var/www/monsiteweb/phpmyadmin
wget https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-all-languages.tar.gz
tar -xvf phpMyAdmin-4.9.0.1-all-languages.tar.gz --strip-components 1 -C /var/www/monsiteweb/phpmyadmin
mv ./tmp/phpmyadmin.inc.php /var/www/monsiteweb/phpmyadmin/config.inc.php

# DL wordpress
cd /tmp/
wget -c https://wordpress.org/latest.tar.gz
tar -xvzf latest.tar.gz
mv wordpress/ /var/www/monsiteweb
mv /tmp/wp-config.php /var/www/monsiteweb/wordpress/

# Config wordpress
wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
mv wp-cli.phar /usr/local/bin/wp
wp core install --path='/var/www/monsiteweb/wordpress' --url='localhost/wordpress' --title='LE TITRE' --admin_user='adesvall' --admin_password='shrek' --admin_email='adesvall@42.student.fr' --skip-email --allow-root
wp theme install --path='/var/www/monsiteweb/wordpress' twentyseventeen --activate --allow-root

# Config Access
chown -R www-data /var/www
chmod -R 755 /var/www

service php7.3-fpm start
service nginx start
bash
