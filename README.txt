# CS 3307 - Group 9 - Phillips Hue Project

## Introduction

Our web application allows a user to set up an account and create, delete and modify bridges for their Phillips Hue Lighting system.

## Team

Group Members:
	Allan Rashad Khan
	Frances Plancke
	Michael Davis
	Steven Crossman
	Jose Rivera

## Build Project
To build and compile our project simply enter the following commands:
	cd team09
	make

## Installation
To build our web application you will need 3 important libraries:
	Boost
	Wt 3.8.8
	sqlite3

To install Boost type the following into the command line:
	
	sudo apt-get install libboost-all-dev

To install Wt 3.8.8 download the official release from: https://www.webtoolkit.eu/wt/download<br/> To install follow these instructions:

	cd wt-3.8.8
	mkdir build; cd build
	cmake ..
	make
	make -C examples
	sudo make install
	sudo ldconfig

To install sqlite3 type these commands into a terminal:

	sudo apt-get install sqlite3 libsqlite3-dev

*****************IMPORTANT****************

To check the contents of the database use the following commands in the terminal:

sqlite3

.open userAccounts.db

.dump

.exit
