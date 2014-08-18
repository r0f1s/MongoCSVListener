This is designed for Linux/Unix systems. It monitors the installation directory for files with a '.csv' 
extension and inserts them into a mongoDB database called "listener" with the collection name that 
matches the file, without the extension.

To compile, first make sure you have the inotify headers and that they're in the correct location:
sudo mv inotify.h /usr/include/sys/
sudo mv inotify-syscalls.h /usr/include/sys/

You also may need to install python-dev (on Ubuntu, for example):
sudo apt-get install python-dev

Then you can modify the config file for your settings, and compile:
gcc -I/usr/include/python2.7 p.c -lpython2.7 

The options help gcc locate the Python headers from the python-dev package.
