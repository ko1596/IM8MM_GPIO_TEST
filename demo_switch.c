#include <stdio.h>
#include <stdlib.h> 

#include <wiringPi.h>

#define byte  unsigned char

void LCD_Init(void);

void LCD_WrDat(unsigned char dat)
{
	unsigned char i=8;
	digitalWrite(10, 0);	//LCD_CS=0;
	digitalWrite(5, 1);	//LCD_DC=1;
	digitalWrite(14, 0);	//LCD_SCL=0;
	int j;

	while(i--)
	{
		if(dat&0x80){digitalWrite(12, 1);}	//LCD_SDA=1;
		else{digitalWrite(12, 0);}			//LCD_SDA=0; 
		digitalWrite(14, 1);	//LCD_SCL=1;
		;;;           
		digitalWrite(14, 0);	//LCD_SCL=0;    Data falling away 
		dat<<=1;    

		//for (j = 0; j < 100; j++)
	//		;;
	}
	digitalWrite(10, 1);	//LCD_CS=1;
}

void LCD_WrDat_QSPI(unsigned char dat)
{
        unsigned char i=2;
        digitalWrite(10, 0);
        digitalWrite(14, 0);

        while(i--)
        {
                if(dat&0x80){digitalWrite(12, 1);}
                else{digitalWrite(12, 0);}

                if(dat&0x40){digitalWrite(2, 1);} 
                else{digitalWrite(2, 0);}

                if(dat&0x20){digitalWrite(1, 1);} 
                else{digitalWrite(1, 0);}

                if(dat&0x10){digitalWrite(0, 1);} 
                else{digitalWrite(0, 0);}


                digitalWrite(14, 1);
                ;;;
                digitalWrite(14, 0);
                dat<<=4;
        }

        digitalWrite(10, 1);
}

void LCD_WrCmd(unsigned char cmd)
{
	unsigned char i=8;
	int j;

	digitalWrite(10, 0);	//LCD_CS=0;
	digitalWrite(5, 0);	//LCD_DC=0;

	//digitalWrite(14, 1);	//LCD_SCL=0;
	//digitalWrite(12, 1);	//LCD_SCL=0;

	while(i--)
	{
		if(cmd&0x80){digitalWrite(12, 1);}	//LCD_SDA=1;
		else{digitalWrite(12, 0);}			//LCD_SDA=0; 
		digitalWrite(14, 1);	//LCD_SCL=1;
		;;;            
		digitalWrite(14, 0);	//LCD_SCL=0;;    
		cmd<<=1;;   

		//for (j = 0; j < 100; j++)
		//	;;
	} 	
	digitalWrite(10, 1);	//LCD_CS=1;
	digitalWrite(5, 1);	//LCD_DC=0;
	//digitalWrite(14, 1);	//LCD_SCL=0;
	//digitalWrite(12, 1);	//LCD_SCL=0;
}

void LCD_SetPage(unsigned char page)
{
	LCD_WrCmd(0xFF);
	LCD_WrDat(0x20);
	LCD_WrDat(0x10);
	LCD_WrDat(page);
}

void LCD_SetCmd1(unsigned char cmd, unsigned char dat)
{
	LCD_WrCmd(cmd);
	LCD_WrDat(dat);
}

void LCD_SetCmd2(unsigned char cmd, unsigned char dat1, unsigned char dat2)
{
	LCD_WrCmd(cmd);
	LCD_WrDat(dat1);
	LCD_WrDat(dat2);
}

void LCD_SetCmd3(unsigned char cmd, unsigned char dat1, unsigned char dat2, unsigned char dat3)
{
	LCD_WrCmd(cmd);
	LCD_WrDat(dat1);
	LCD_WrDat(dat2);
	LCD_WrDat(dat3);
}

void LCD_SetCmd4(unsigned char cmd, unsigned char dat1, unsigned char dat2, unsigned char dat3, unsigned char dat4)
{
	LCD_WrCmd(cmd);
	LCD_WrDat(dat1);
	LCD_WrDat(dat2);
	LCD_WrDat(dat3);
	LCD_WrDat(dat4);
}

void LCD_Init(void)        
{  
	digitalWrite(14, 0);	//LCD_SCL=1;
	digitalWrite(12, 0);	//LCD_SCL=1;
	digitalWrite(10, 1);	//LCD_CS=1;		//Prefabricated SLK and CD HIGH
	digitalWrite(6, 0);	//LCD_RST=0;
	delay(50);		//LCD_DLY_ms(50);
	digitalWrite(6, 1);	//LCD_RST=1;
	delay(200);		//LCD_DLY_ms(50);

#if 1
	LCD_SetCmd1(0x35, 0x00);
	LCD_SetCmd1(0x38, 0x00);

	//LCD_SetCmd1(0x39, 0x1F);
	//LCD_SetCmd1(0x39, 0x00);
	LCD_SetCmd1(0x39, 0x0F);

	LCD_SetCmd1(0x36, 0x08);
	LCD_SetCmd1(0x3A, 0x01);
	LCD_SetCmd2(0x2A, 0x00, 0x85);
	LCD_SetCmd4(0x2B, 0x00, 0x00, 0x04, 0xAF);

	LCD_SetCmd3(0xFF,0x21,0x71,0x45);
	LCD_SetCmd1(0x00,0x04);
	LCD_SetCmd1(0x01,0xB0);
	LCD_SetCmd1(0x07,0x10);
	LCD_SetCmd1(0x32,0x2C);
	LCD_SetCmd1(0x33,0x57);
	LCD_SetCmd1(0x34,0x00);
	LCD_SetCmd1(0x35,0x2B);
	LCD_SetCmd1(0x36,0x58);
	LCD_SetCmd1(0x37,0x85);
	LCD_SetCmd1(0x42,0x10);
	LCD_SetCmd1(0x43,0x3b);
	LCD_SetCmd1(0x44,0x10);
	LCD_SetCmd1(0x45,0x3b);
	LCD_SetCmd1(0x46,0x00);
	LCD_SetCmd1(0x47,0x2D);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd3(0xFF,0x21,0x71,0x11);
	LCD_SetCmd1(0x02,0xB2);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd1(0xF0,0x01);

	LCD_SetCmd3(0xFF,0x21,0x71,0x28);
	LCD_SetCmd1(0x0C,0x04);
	LCD_SetCmd1(0x0D,0x74);
	LCD_SetCmd1(0x0E,0x04);
	LCD_SetCmd1(0x0F,0xAF);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd1(0xF0,0x02);

	LCD_SetCmd3(0xFF,0x21,0x71,0x28);
	LCD_SetCmd1(0x01,0x80);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd1(0xF0,0x03);

	LCD_SetCmd3(0xFF,0x21,0x71,0x28);
	LCD_SetCmd1(0x01,0x40);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd1(0xF0,0x00);


	LCD_SetCmd3(0xFF,0x21,0x71,0x12);
	LCD_SetCmd1(0x87,0xA9);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd3(0xFF,0x21,0x71,0xA0);
	LCD_SetCmd1(0x04,0x17);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd3(0xFF,0x21,0x71,0x2D);
	LCD_SetCmd1(0x00,0x01);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd3(0xFF,0x21,0x71,0x43);
	LCD_SetCmd1(0x03,0x04);
	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	LCD_SetCmd3(0xFF,0x21,0x71,0x11);
	LCD_SetCmd1(0x0A,0x00);
	LCD_SetCmd1(0x0B,0x18);
	LCD_SetCmd1(0x0C,0x18);

	LCD_SetCmd3(0xFF,0x21,0x71,0x00);

	// bist mode
	//LCD_SetCmd3(0xFF,0x21,0x71,0x2D);
	//LCD_SetCmd1(0x02,0x21);
	//LCD_SetCmd3(0xFF,0x21,0x71,0x00);
#endif

} 

#define ROW_BYTE_NUM (1600 * 3)

void LCD_Image(unsigned char data[])
{
	int x, y, i, j;
	unsigned char rgb[3] = {0xFF, 0x00, 0x00};
	unsigned char r, g, b;
	unsigned char buf ;

	LCD_WrCmd(0x2C);  

#if 1
	for (y = 1199; y >= 0; y--){
		for(x = 0; x < 1600 / 4; x++){
			buf = 0;
			for (i = 0; i < 4; i++){
				//b = data[y * ROW_BYTE_NUM + (399 - x) * 3 * 4 + i * 3];
				//g = data[y * ROW_BYTE_NUM + (399 - x) * 3 * 4 + i * 3 + 1];
				//r = data[y * ROW_BYTE_NUM + (399 - x) * 3 * 4 + i * 3 + 2];
				b = data[y * ROW_BYTE_NUM + (x) * 3 * 4 + i * 3];
				g = data[y * ROW_BYTE_NUM + (x) * 3 * 4 + i * 3 + 1];
				r = data[y * ROW_BYTE_NUM + (x) * 3 * 4 + i * 3 + 2];

				if (b > 0x7F && g > 0x7F && r > 0x7F)
					//buf |= 0x0 << ((3 - i) * 2);
					buf |= 0x1 << ((i) * 2);

				if (b <= 0x7F && g <= 0x7F && r > 0x7F)
					//buf |= 0x2 << ((3 - i) * 2);
					buf |= 0x2 << ((i) * 2);

				if (b <= 0x7F && g <= 0x7F && r <= 0x7F)
					//buf |= 0x3 << ((3 - i) * 2);
					buf |= 0x3 << ((i) * 2);
			}
			//LCD_WrDat(buf);
                        LCD_WrDat_QSPI(buf); // R
		}
		//LCD_WrDat(0x00);
		LCD_WrDat_QSPI(0x00);
		//LCD_WrDat(0x00);
		LCD_WrDat_QSPI(0x00);
	}
#endif


#if 0
	for (i = 0; i < 1200; i++){
		if (400 % 3)
			x = (400 / 3 + 1) * 3;
		for (j = 0; j < x; j++){
			LCD_WrDat(0xFF);
		}
	}
#endif
}

void main(int argc, char **argv) 
{
	unsigned char i=0;    
	unsigned char rgb[3] = {0x00, 0x00, 0xFF};
	unsigned char *buf;
	FILE *fp;
	unsigned char str[30];

	//printf("==============================\n");
	wiringPiSetup();  
	pinMode (4, INPUT);   // switch 
	pullUpDnControl(4,PUD_DOWN);
	pinMode(10, OUTPUT);	// CS
	pinMode(5, OUTPUT); 	// D/C
	pinMode(14, OUTPUT);	// SCLK
	pinMode(12, OUTPUT);	// MOSI
	pinMode(6, OUTPUT); 	// RESET

        pinMode(0, OUTPUT); 	// D0
        pinMode(1, OUTPUT); 	// D1
        pinMode(2, OUTPUT); 	// D2
//	pinMode(23, INPUT);   // switch 

	LCD_Init();  
	delay(250);

	LCD_WrCmd(0x11);
	delay(50);

	LCD_SetCmd1(0xE4, 0x02);
	LCD_WrCmd(0x29);

	buf = malloc(sizeof(unsigned char) * 1600 * 1200 * 3);
	if (buf == NULL){
		printf("malloc error\n");
		return 0;
	}

#if 1
	while(1){
		for (i = 1; i < argc; i++)
		{
		//if (digitalRead(4) == HIGH) 
		
		if (digitalRead(4)==1)
		{
//	printf("==============================\n");
			//LCD_WrCmd(0x28);
			//LCD_WrCmd(0x00);
			delay(50);

//			//sprintf(argv[i], "%d.bmp", argv[i]);
//			printf("4,23--> %s,%s\n", digitalRead(4),digitalRead (23));

			fp = fopen(argv[i], "rb");
			if (fp == NULL){
				printf("open %s file error\n", str);
				return 0;
			}

			fseek(fp, 54, SEEK_SET);
			fread(buf, sizeof(unsigned char), 1600 * 1200 * 3, fp);
			fclose(fp);

			LCD_Image(buf);  

			delay(5000);	//delay 10 sec
		}
			delay(50);	//delay 10 sec
		}
	}
#endif

	free(buf);
}
