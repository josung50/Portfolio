#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *PATH_GPIO_EXPORT = "/sys/class/gpio/export";
const char *PATH_GPIO_UNEXPORT = "/sys/class/gpio/unexport";

const char *PATH_GPIO_27_DIRECTION = "/sys/class/gpio/gpio27/direction";
const char *PATH_GPIO_27_VALUE = "/sys/class/gpio/gpio27/value";

const char *PATH_GPIO_17_DIRECTION = "/sys/class/gpio/gpio17/direction";
const char *PATH_GPIO_17_VALUE = "/sys/class/gpio/gpio17/value";

const char *PATH_GPIO_21_DIRECTION = "/sys/class/gpio/gpio21/direction";
const char *PATH_GPIO_21_VALUE = "/sys/class/gpio/gpio21/value";

const char *PATH_GPIO_5_DIRECTION = "/sys/class/gpio/gpio5/direction";
const char *PATH_GPIO_5_VALUE = "/sys/class/gpio/gpio5/value";

const char *PATH_GPIO_6_DIRECTION = "/sys/class/gpio/gpio6/direction";
const char *PATH_GPIO_6_VALUE = "/sys/class/gpio/gpio6/value";

const char *PATH_GPIO_13_DIRECTION = "/sys/class/gpio/gpio13/direction";
const char *PATH_GPIO_13_VALUE = "/sys/class/gpio/gpio13/value";

const char *PATH_GPIO_19_DIRECTION = "/sys/class/gpio/gpio19/direction";
const char *PATH_GPIO_19_VALUE = "/sys/class/gpio/gpio19/value";

const char *PATH_GPIO_26_DIRECTION = "/sys/class/gpio/gpio26/direction";
const char *PATH_GPIO_26_VALUE = "/sys/class/gpio/gpio26/value";


#define GPIO_NUM 27
#define GPIO_NUM2 17
#define GPIO_NUM3 21
#define GPIO_NUM4 5
#define GPIO_NUM5 6
#define GPIO_NUM6 13
#define GPIO_NUM7 19
#define GPIO_NUM8 26

typedef enum {
	OFF = 0,
	ON
}gpio_state;


void slow_on();
void slow_off();
void gpio_init();
void gpio_exit();
void set_gpio_state(gpio_state state);

FILE *GPIO_EXPORT;
FILE *GPIO_27_DIRECTION;
FILE *GPIO_27_VALUE;

FILE *GPIO_17_VALUE;
FILE *GPIO_17_DIRECTION;

FILE *GPIO_21_VALUE;
FILE *GPIO_21_DIRECTION;

FILE *GPIO_5_VALUE;
FILE *GPIO_5_DIRECTION;

FILE *GPIO_6_VALUE;
FILE *GPIO_6_DIRECTION;

FILE *GPIO_13_VALUE;
FILE *GPIO_13_DIRECTION;

FILE *GPIO_19_VALUE;
FILE *GPIO_19_DIRECTION;

FILE *GPIO_26_VALUE;
FILE *GPIO_26_DIRECTION;

int timeT = 3000;

int main()
{
	gpio_state state = OFF;
	
	gpio_init();

	timeT = 3000;
	slow_off();
	gpio_exit();
}

void gpio_init()
{
	if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
		printf("%s open failed\n", PATH_GPIO_EXPORT);
		exit(0);
	}

	// 27 //
	fprintf(GPIO_EXPORT, "%d", GPIO_NUM);
	fclose(GPIO_EXPORT);

	if((GPIO_27_DIRECTION = fopen(PATH_GPIO_27_DIRECTION, "w")) == NULL)
	{
		printf("%s open failed\n", PATH_GPIO_27_DIRECTION);
		exit(0);
	}
	fprintf(GPIO_27_DIRECTION, "out");
	fclose(GPIO_27_DIRECTION);

	if((GPIO_27_VALUE = fopen(PATH_GPIO_27_VALUE,"w"))==NULL) {
		printf("%s open failed\n", PATH_GPIO_27_VALUE);
		exit(0);
	}


	// 17 //
        if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
               printf("%s open failed\n", PATH_GPIO_EXPORT);
               exit(0);
        }

        fprintf(GPIO_EXPORT, "%d", GPIO_NUM2);
        fclose(GPIO_EXPORT);

        if((GPIO_17_DIRECTION = fopen(PATH_GPIO_17_DIRECTION, "w")) == NULL)
        {
                printf("%s open failed\n", PATH_GPIO_17_DIRECTION);
                exit(0);
        }
        fprintf(GPIO_17_DIRECTION, "out");
        fclose(GPIO_17_DIRECTION);

        if((GPIO_17_VALUE = fopen(PATH_GPIO_17_VALUE,"w"))==NULL) {
                printf("%s open failed\n", PATH_GPIO_17_VALUE);
                exit(0);
        }


	// 21 //
        if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
              printf("%s open failed\n", PATH_GPIO_EXPORT);
              exit(0);
        }

        fprintf(GPIO_EXPORT, "%d", GPIO_NUM3);
        fclose(GPIO_EXPORT);

        if((GPIO_21_DIRECTION = fopen(PATH_GPIO_21_DIRECTION, "w")) == NULL)
        {
                printf("%s open failed\n", PATH_GPIO_21_DIRECTION);
                exit(0);
        }
        fprintf(GPIO_21_DIRECTION, "out");
        fclose(GPIO_21_DIRECTION);

        if((GPIO_21_VALUE = fopen(PATH_GPIO_21_VALUE,"w"))==NULL) {
                printf("%s open failed\n", PATH_GPIO_21_VALUE);
                exit(0);
        }


	// 5 //
        if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
             printf("%s open failed\n", PATH_GPIO_EXPORT);
             exit(0);
        }

        fprintf(GPIO_EXPORT, "%d", GPIO_NUM4);
        fclose(GPIO_EXPORT);

        if((GPIO_5_DIRECTION = fopen(PATH_GPIO_5_DIRECTION, "w")) == NULL)
        {
                printf("%s open failed\n", PATH_GPIO_5_DIRECTION);
                exit(0);
        }
        fprintf(GPIO_5_DIRECTION, "out");
        fclose(GPIO_5_DIRECTION);

        if((GPIO_5_VALUE = fopen(PATH_GPIO_5_VALUE,"w"))==NULL) {
                printf("%s open failed\n", PATH_GPIO_5_VALUE);
                exit(0);
        }


	// 6 //
        if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
            printf("%s open failed\n", PATH_GPIO_EXPORT);
            exit(0);
        }

        fprintf(GPIO_EXPORT, "%d", GPIO_NUM5);
        fclose(GPIO_EXPORT);

        if((GPIO_6_DIRECTION = fopen(PATH_GPIO_6_DIRECTION, "w")) == NULL)
        {
                printf("%s open failed\n", PATH_GPIO_6_DIRECTION);
                exit(0);
        }
        fprintf(GPIO_6_DIRECTION, "out");
        fclose(GPIO_6_DIRECTION);

        if((GPIO_6_VALUE = fopen(PATH_GPIO_6_VALUE,"w"))==NULL) {
                printf("%s open failed\n", PATH_GPIO_6_VALUE);
                exit(0);
        }

	// 13 //
        if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
           printf("%s open failed\n", PATH_GPIO_EXPORT);
           exit(0);
        }

        fprintf(GPIO_EXPORT, "%d", GPIO_NUM6);
        fclose(GPIO_EXPORT);

        if((GPIO_13_DIRECTION = fopen(PATH_GPIO_13_DIRECTION, "w")) == NULL)
        {
                printf("%s open failed\n", PATH_GPIO_13_DIRECTION);
                exit(0);
        }
        fprintf(GPIO_13_DIRECTION, "out");
        fclose(GPIO_13_DIRECTION);

        if((GPIO_13_VALUE = fopen(PATH_GPIO_13_VALUE,"w"))==NULL) {
                printf("%s open failed\n", PATH_GPIO_13_VALUE);
                exit(0);
        }

	// 19 //
	if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
          printf("%s open failed\n", PATH_GPIO_EXPORT);
          exit(0);
        }

        fprintf(GPIO_EXPORT, "%d", GPIO_NUM7);
        fclose(GPIO_EXPORT);

        if((GPIO_19_DIRECTION = fopen(PATH_GPIO_19_DIRECTION, "w")) == NULL)
        {
                printf("%s open failed\n", PATH_GPIO_19_DIRECTION);
                exit(0);
        }
        fprintf(GPIO_19_DIRECTION, "out");
        fclose(GPIO_19_DIRECTION);

        if((GPIO_19_VALUE = fopen(PATH_GPIO_19_VALUE,"w"))==NULL) {
                printf("%s open failed\n", PATH_GPIO_19_VALUE);
                exit(0);
        }

	// 26 //
        if((GPIO_EXPORT = fopen(PATH_GPIO_EXPORT,"w"))==NULL) {
          printf("%s open failed\n", PATH_GPIO_EXPORT);
          exit(0);
        }

        fprintf(GPIO_EXPORT, "%d", GPIO_NUM8);
        fclose(GPIO_EXPORT);

        if((GPIO_26_DIRECTION = fopen(PATH_GPIO_26_DIRECTION, "w")) == NULL)
        {
                printf("%s open failed\n", PATH_GPIO_26_DIRECTION);
                exit(0);
        }
        fprintf(GPIO_26_DIRECTION, "out");
        fclose(GPIO_26_DIRECTION);

        if((GPIO_26_VALUE = fopen(PATH_GPIO_26_VALUE,"w"))==NULL) {
                printf("%s open failed\n", PATH_GPIO_26_VALUE);
                exit(0);
        }
	

}
void gpio_exit()
{
	FILE *GPIO_UNEXPORT;

	fclose(GPIO_27_VALUE);

	if((GPIO_UNEXPORT = fopen(PATH_GPIO_UNEXPORT, "w")) == NULL) {
		printf("%s open failed\n", PATH_GPIO_UNEXPORT);
		exit(0);
	}
	fprintf(GPIO_UNEXPORT, "%d", GPIO_NUM);
	close(GPIO_UNEXPORT);
}

void set_gpio_state(gpio_state state)
{
	fprintf(GPIO_17_VALUE, "%d", state);
	fflush(GPIO_17_VALUE);
	fprintf(GPIO_27_VALUE, "%d", state);
	fflush(GPIO_27_VALUE);
	fprintf(GPIO_21_VALUE, "%d", state);
	fflush(GPIO_21_VALUE);
	fprintf(GPIO_5_VALUE, "%d", state);
	fflush(GPIO_5_VALUE);
	fprintf(GPIO_6_VALUE, "%d", state);
	fflush(GPIO_6_VALUE);
	fprintf(GPIO_13_VALUE, "%d", state);
	fflush(GPIO_13_VALUE);
	fprintf(GPIO_19_VALUE, "%d", state);
	fflush(GPIO_19_VALUE);
	fprintf(GPIO_26_VALUE, "%d", state);
	fflush(GPIO_26_VALUE);
}	

void slow_off() {

	while(1) {
		set_gpio_state(ON);
		usleep(timeT);
		set_gpio_state(OFF);
		usleep(3000-timeT);
		timeT = timeT - 100;
		if(timeT < 0){
			timeT = 0;
			return;
		}
	}
}

void slow_on() {
	while(1) {
		set_gpio_state(ON);
		usleep(timeT);
		set_gpio_state(OFF);
		usleep(3000-timeT);
		timeT = timeT + 100;
		if(timeT > 3000) {
			timeT = 3000;
			return;
		}
	}
}
