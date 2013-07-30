DeltaPiBeer
===========

Rpi-hw 0.4.0<br>
https://github.com/Wicker25/Rpi-hw

Boost 1.49.0<br> 
sudo apt-get install libboost-all-dev

MySQL connector<br>
C++ 1.1.3

sudo bash -c "echo /usr/local/lib/ > /etc/ld.so.conf.d/local.conf"<br>
sudo /sbin/ldconfig

sudo chown root ./DeltaPi <br>
sudo chmod 4755 ./DeltaPi

$ nano ~/startup.sh

#!/bin/bash<br>
/etc/local/DeltaPi

$ chmod ugo+x startup.sh

$ nano ~/.bashrc

# Run the startup bash script:<br>
echo starting DeltaPi<br>
bash startup.sh
