#!/bin/sh
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install vim g++-4.7 cmake libfreetype6-dev libgraphicsmagick++1-dev doxygen
sudo ln -fs /usr/bin/g++-4.7 /usr/bin/g++
git clone https://github.com/Wicker25/Rpi-hw
cd Rpi-hw*
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFREETYPE_INCLUDE_DIRS=/usr/include/freetype/
make
sudo make install
cd ..
sudo apt-get install libboost-all-dev
sudo apt-get install libmysqlcppconn-dev
sudo bash -c "echo /usr/local/lib/ > /etc/ld.so.conf.d/local.conf"
sudo /sbin/ldconfig
git clone https://github.com/vehagn/DeltaPi
cd DeltaPi/
mkdir Release
cd Release/
cmake .. -DCMAKE_BUILD_TYPE=Release -DFREETYPE_INCLUDE_DIRS=/usr/include/freetype/
make
sudo cp *Pi /usr/local
sudo chown root /usr/local/*Pi
sudo chmod 4755 /usr/local/*Pi
cd ..
chmod 771 startup.sh
sudo chown root:pi /sbin/shutdown
sudo chmod 4770 /sbin/shutdown
echo 'bash ~/DeltaPi/startup.sh' >> ~/.bashrc
cp database.conf ~/

sudo addgroup www-data
sudo adduser www-data www-data
sudo mkdir /var/www
sudo mkdir /var/www/pi.deltahouse.no
sudo mkdir /var/www/pi.deltahouse.no/public_html
sudo chown -R www-data:www-data /var/www
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install php5 apache2
sudo cp -r ~/DeltaPi/web/public_html/* /var/www/pi.deltahouse.no/public_html/
sudo chown www-data:www-data /var/www/pi.deltahouse.no/public_html/*

echo 'Make changes to Apache to complete installation'
