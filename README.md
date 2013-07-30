DeltaPiBeer
===========

#Dependencies
Rpi-hw 0.4.1<br>
https://github.com/Wicker25/Rpi-hw

Boost 1.49.0<br> 
sudo apt-get install libboost-all-dev

MySQL connector<br>
C++ 1.1.3

#Root access to shared libraries (for MySQL connector)
sudo bash -c "echo /usr/local/lib/ > /etc/ld.so.conf.d/local.conf"<br>
sudo /sbin/ldconfig

#Give file root access without running sudo
sudo chown root ./DeltaPi <br>
sudo chmod 4755 ./DeltaPi

#Startup on boot
$ nano ~/startup.sh

 #!/bin/bash<br>
/etc/local/DeltaPi

$ chmod ugo+x startup.sh

$ nano ~/.bashrc

 # Run the startup bash script:<br>
echo starting DeltaPi<br>
bash startup.sh
