
#define KEY_NULL      0
#define POWER_KEY     0x88
#define POWER_KEY_STR "    ON"

enum {	
	//KEY_NULL,
	KEY_0 = '0',
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_POINT = '.',
	KEY_LJ,
	KEY_CLEAR,
	KEY_ZERO   = 'Z',
	KEY_TARE   = 'T',	
	KEY_END,
	KEY_FULL=0XFF,

};

uchar readKey(void);
void  keyTest(void);
void  initKey(void);
void delayms(uint ms);
void key_init();
void key_end();
bit key_status();
void key_process(unsigned char dat);

