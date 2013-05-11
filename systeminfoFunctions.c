//** requires lm_sensors
//** ONLY WORKS ON MY FUJITSU LAPTOP FOR DEMO PURPOSE


#include "getSensor.h"

void getTime(char *temp){

	FILE *fp;
	char* command = "uptime > uptime";
	system(command);
	char uptime_load[BUF_SIZE] = "\0";
	fp = fopen("uptime", "r");
    	if(fp != NULL){
      		size_t ulen = fread(uptime_load, sizeof(char), BUF_SIZE, fp);
      		if(ulen == 0){
        		fputs("getTime()", stderr);
      		}
      		else{
        		uptime_load[++ulen] ='\0';
      		}
    		fclose(fp);
    	}
    	else{
      		perror("getTime()");
      		exit(1);
    	}
	strncpy(temp,uptime_load, strlen(uptime_load));
}

void getTemp(char *temp){
	
	FILE *fp;
	char* command = "sensors > sensor";
	system(command);
	char cpu[BUF_SIZE] = "\0";
	fp = fopen("sensor", "r");
  	if(fp != NULL){
    		size_t clen = fread(cpu, sizeof(char), BUF_SIZE, fp);
    		if(clen == 0){
      			fputs("getTemp()", stderr);
    		}
    		else{
      			cpu[++clen] ='\0';
    		}
    		fclose(fp);
	}
  	else{
      		perror("getTemp()");
      		exit(1);
    	}
	strncpy(temp, cpu, strlen(cpu));
}

//** broken
char* parseTemp(){
	char temp[BUF_SIZE];
	getTemp(temp);
	char* cputemp = temp;
	char* coretemp = strstr(cputemp, "Core 0");
  	char* core0;
  	
	char*result = malloc(sizeof(char *));
	strncpy(result, core0, strlen(core0));
	printf("CPU: %s\n", result);
	return result;
}

char* parseUptime(){
	int i;
	char temp[BUF_SIZE];
	getTime(temp);
	char* uptime = temp;
	//uptime = uptime + 14;
	uptime = strstr(uptime, "up") + 2;
	for(i = 0; i < sizeof(uptime); i++){
    		if(uptime[i] == ','){
      			uptime[i] = '\0';
      			break;
    		}
  	}

	char*result = malloc(sizeof(char*));
	strncpy(result, uptime, strlen(uptime));
	printf("Up: %s\n", result);
	return result;
}

char *parseLoadtime(){
	char temp[BUF_SIZE];
	getTime(temp);
	char *loadtime = temp;
	char *load = strstr(temp, "load average: ")+strlen("load average: ");
	int i;
	for(i = 0; i < sizeof(load); i++){
    		if(load[i] == ','){
      			load[i] = '\0';
      			break;
    		}
  	}
	char *result = malloc(sizeof(char*));
	strncpy(result,load, strlen(load));
	printf("Load: %s\n", result);
	return result;
}


