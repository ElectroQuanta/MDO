# Makefile 
# author: Tian Xia
# org: Infolab@tamu
# date: Aug 19, 2015

CC=g++
CC=/home/zmpl/OneDrive-UM/Univ/MI_Electro/Sem7/SEC/2021-22/Buildroot/buildroot-2021.08.1/output/host/bin/aarch64-buildroot-linux-gnu-g++

all : twitterClient

libcurl : 
	cd ../libtwitcurl && make install 
	cd ../twitterClient

twitterClient : twitterClient.cpp
	$(CC) twitterClient.cpp -I./include/ -L /usr/local/lib/ -ltwitcurl -o twitterClient

twitterClientStatic : twitterClient.cpp
	$(CC) twitterClient.cpp -I./include/ -L ./staticlibs/libtwitcurl.a -o twitterClient

clean:
	rm twitterClient

clean-all : 
	rm twitterClient
	cd ../libtwitcurl && sudo make clean
	cd ../twitterClient

