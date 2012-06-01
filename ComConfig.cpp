// ComConfig.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

int _tmain(int argc, _TCHAR* argv[])
{

	COMMTIMEOUTS timeouts;
	HANDLE hCommPort;
	TCHAR pcCommPort[30];

	if(argc < 2) {
		_tprintf (TEXT("Please specifiy a COMM port\n"));
		return 0;
	}

	_sntprintf(pcCommPort, 29, TEXT("%s"), argv[1]);
	pcCommPort[29] = 0;

	hCommPort = CreateFile(pcCommPort,
		GENERIC_READ|GENERIC_WRITE,//access ( read and write)
		0,    //(share) 0:cannot share the COM port
		0,    //security  (None)
		OPEN_EXISTING,// creation : open_existing
		FILE_ATTRIBUTE_NORMAL,// we want overlapped operation
		0// no templates file for COM port...
		);
	if (hCommPort == INVALID_HANDLE_VALUE) {
		_tprintf (TEXT("Unable to open %s\n"), pcCommPort);
		exit(1);
	}

	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;

	if(!SetCommTimeouts(hCommPort, &timeouts)) {
		printf("Error setting timeouts\r\n");
	} else {
		_tprintf (TEXT("Serial port %s successfully reconfigured.\r\n"), pcCommPort);
	}


	return 0;
}

