FROM debian:buster

RUN apt-get update && apt-get install -y procps && apt-get install nano && apt-get install -y wget
RUN apt-get -y install php7.3-fpm php7.3-common php7.3-mysql php7.3-gmp php7.3-curl php7.3-intl php7.3-mbstring php7.3-xmlrpc php7.3-gd php7.3-xml php7.3-cli php7.3-zip php7.3-soap php7.3-imap
RUN apt-get -y install wget
RUN apt-get -y install nginx
RUN apt-get -y install mariadb-server

COPY ./srcs/set_components.sh ./
COPY ./srcs/nginx-conf ./tmp/
COPY ./srcs/phpMyAdmin-4.9.0.1-all-languages.tar.gz ./tmp/
COPY ./srcs/phpmyadmin.inc.php ./tmp/
COPY ./srcs/wp-latest.tar.gz ./tmp/
COPY ./srcs/wp-config.php ./tmp/
COPY ./srcs/autoindex.sh ./tmp/

CMD bash set_components.sh
