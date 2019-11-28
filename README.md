# Reckoning Structure Pack-Up Code Repository #

[http://www.swgreckoning.com](http://www.swgreckoning.com)

## About This Repository ##

This repository contains the structure pack-up source code that Reckoning uses on its Star Wars Galaxies play server. Reckoning is powered by SWGEmu.

### How to manually add Structure Pack-Up to your own code ###

##### Merge The Pack-Up Code #####
  * Please view the following commit: https://bitbucket.org/Reckoning-Aso/core3-packup/commits/bd46624a70b3f4ff6c36534e823b4b89253359be and merge it manually into your code.
  
##### Download Packup .tre File #####
  * Download the packup.tre from https://swgreckoning.com/download/dev/ and place it in your server's tre file directory. It will also need to be included client side.

### How to build this repository as a whole ###

##### Dependencies #####
  * Debian 9+ or Ubuntu 16.04+
  * CMake 3.1.0 or higher
  * BerkeleyDB 5.3
  * MySQL Client and Server
  * OpenSSL libraries
  * pthreads
  * Lua 5.3 libraries
  * Zlib libraries
  * g++ 5+
  * engine3
  * java jre 1.7+

##### Install dependencies #####
  * apt install build-essential default-libmysqlclient-dev liblua5.3-dev libdb5.3-dev libssl-dev cmake git default-jre libssl-dev git

##### Create SWGEmu user #####
  * adduser swgemu

##### Clone Reckoning Structure Pack-Up Code Repo  #####
  * mkdir -p /home/swgemu/server/git
  * cd /home/swgemu/server/git
  * git clone -b unstable https://Reckoning-Aso@bitbucket.org/Reckoning-Aso/core3-packup.git

##### Build Core3 with 8 threads #####
  * cd /home/swgemu/server/git/core3-packup/MMOCoreORB
  * make -j8

##### Copy Compiled Server Files #####
  * cp -ar /home/swgemu/server/git/core3-packup/MMOCoreORB/bin/ /home/swgemu/server/

##### Import sql database #####
  * mysql -h<MYSQLHOST> -u<MYSQLUSER> -p<MYSQLPASSWORD> < sql/swgemu.sql

##### Modify Config #####
  * Modify config.lua located at: /home/swgemu/server/bin/conf

##### Run The Server #####
  * cd /home/swgemu/server/bin
  * ./core3

### License ###
    Copyright (C) 2019 SWG Reckoning

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.