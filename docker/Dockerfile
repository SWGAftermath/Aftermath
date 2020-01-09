FROM debian:stretch

RUN apt-get update && apt-get upgrade -y && apt-get install -y build-essential default-libmysqlclient-dev libmariadbclient-dev liblua5.3-dev libdb5.3-dev libssl-dev cmake git default-jre default-mysql-server libboost-dev libboost-thread-dev

ADD . / /Core3/

WORKDIR /Core3/MMOCoreORB/

RUN  /etc/init.d/mysql start


#ENTRYPOINT /git/run.sh
