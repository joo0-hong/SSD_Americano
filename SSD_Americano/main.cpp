#include <stdio.h>
#include <iostream>
#include "hostInterface.cpp"
using namespace std;


int main(int argc, char* argv[])
{
	HostInterface hostIF;
	hostIF.ParseCommand(argc, argv);
	
	return 0;
}