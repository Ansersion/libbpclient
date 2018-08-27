#ifndef MD5_H  
#define MD5_H  
#include <bpclient_config.h>

typedef struct  
{  
	BP_UINT32 count[2];  
	BP_UINT32 state[4];  
	BP_UINT8 buffer[64];     
}MD5_CTX;  


#define F(x,y,z) ((x & y) | (~x & z))  
#define G(x,y,z) ((x & z) | (y & ~z))  
#define H(x,y,z) (x^y^z)  
#define I(x,y,z) (y ^ (x | ~z))  
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))  
#define FF(a,b,c,d,x,s,ac) \
{ \
	a += F(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
}
#define GG(a,b,c,d,x,s,ac) \
{ \
	a += G(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
}
#define HH(a,b,c,d,x,s,ac) \
{ \
	a += H(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
}
#define II(a,b,c,d,x,s,ac) \
{ \
	a += I(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
}
void MD5Init(MD5_CTX *context);  
void MD5Update(MD5_CTX *context,BP_UINT8 *input,BP_WORD inputlen);  
void MD5Final(MD5_CTX *context,BP_UINT8 digest[16]);  
void MD5Transform(BP_UINT32 state[4],BP_UINT8 block[64]);  
void MD5Encode(BP_UINT8 *output,BP_UINT32 *input,BP_WORD len);  
void MD5Decode(BP_UINT32 *output,BP_UINT8 *input,BP_WORD len);  

#endif  
