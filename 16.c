#include <stdio.h>
#include "my_list.h"
#include "asd.h"
int main()
{
	int l_zLicenseAcquired = 1;
	int l_zIphoneLicenseAcquired = 1;

	init_list();
	init_flexible();
	int l_iLicRetryCount = 0;
	for ( l_iLicRetryCount=0;
			l_iLicRetryCount < 5;
			++l_iLicRetryCount)
	{
		l_zLicenseAcquired = acquire(
				"arts-rtsp", 1, "1.0",0,0
				);
		if (l_zLicenseAcquired)
			break;
		sleep(2); // retry after 2 seconds
	}

	if (!l_zLicenseAcquired)
	{
		printf("Could not acquire license of rtspserver");
		return -1;
	}
	return 0;
}
