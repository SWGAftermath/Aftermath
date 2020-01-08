FROM debian:stretch

RUN apt-get update && apt-get upgrade -y && apt-get install -y build-essential default-libmysqlclient-dev libmariadbclient-dev liblua5.3-dev libdb5.3-dev libssl-dev cmake git default-jre default-mysql-server && mkdir git && cd git && mkdir Core3

#ADD MMOCoreORB /git/Core3/MMOCoreORB

#ADD .git /git/Core3/.git

#ADD .gitmodules /git/Core3/.gitmodules

#ADD run.sh /git

#WORKDIR /git/Core3/MMOCoreORB/

WORKDIR /Core3/MMOCoreORB/

#RUN  git submodule update --remote

#WORKDIR /git/Core3/MMOCoreORB/


#ENTRYPOINT /git/run.sh
