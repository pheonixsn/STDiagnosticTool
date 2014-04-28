
#ifndef _ALGOVA_COMMON_H_
#define _ALGOVA_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>


#ifdef __cplusplus
extern "C"
{
#endif

#if defined(VAAPI_EXPORTS)
#define VA_EXPORTS __declspec(dllexport)
#elif defined(VAAPI_IMPORTS)
#define VA_EXPORTS __declspec(dllimport)
#else
#define VA_EXPORTS extern
#endif

#define INLINE	__inline

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifndef PI
#define PI 3.1415926
#endif

#define NAME_BUF_SIZE 16
#define FILE_BUF_SIZE (1024*4)

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef float real;
typedef void *MODULE_HANDLE;

typedef struct
{
	uint8_t b, g, r;
} PIXVAL;

typedef struct
{
	int32_t	width, height;
	uint8_t	*data;
	uint32_t time;
} RGBIMAGE;

typedef struct
{
	int32_t	width, height;
	uint8_t	*dataY, *dataU, *dataV;
	uint32_t time;
	uint32_t flag;
} YUVIMAGE422;

typedef struct
{
	int32_t width, height;
	uint8_t *data;
} GRAYIMAGE;

typedef struct
{
	int32_t width, height;
	int16_t *data;
} GRAYIMAGE2;

typedef struct
{
	int32_t width, height;
	int32_t buf_len;
	uint8_t *data;
} TMPLIMAGE;

typedef struct
{
	int16_t x, y;
} ZPOINT;

typedef struct
{
	int32_t x, y, z;
} ZPOINT3D;

typedef struct
{
	ZPOINT pt_s, pt_e;
} ZLINE;

typedef struct
{
	int16_t lb_x, lb_y, ru_x, ru_y;
} ZRECT;

typedef struct
{
	uint32_t time;
	uint32_t date;
} ZSYSTIME;

typedef struct
{
	int32_t	buf_len, dat_len;
	uint8_t	*buffer;
} ZDATBUF;

#define ZSTRING_BUF_LEN	(1024*4)
typedef struct
{
	int32_t	dat_len;
	uint8_t	buffer[ZSTRING_BUF_LEN-sizeof(int32_t)*1];
} ZSTRING;

// 使能标志
typedef enum
{
	VAENA_FLAG_DISABLE		= 0,	// 未使能
	VAENA_FLAG_ENABLE		= 1		// 使能
} VAENA_FLAG;

// 警报级别
typedef enum
{
	VAALARM_LEVEL_NOT		= 0,	// 非警报
	VAALARM_LEVEL_LOW		= 1,	// 低级
	VAALARM_LEVEL_MEDIUM	= 2,	// 中级
	VAALARM_LEVEL_HIGH		= 3		// 高级
} VAALARM_LEVEL;

#define ZANB_MAKE_VERSION( type_m, type_s, seri_m, seri_s ) \
		( 0	\
		| ( (((uint32_t)type_m)&0xFF)<<0 ) \
		| ( (((uint32_t)type_s)&0xFF)<<8 ) \
		| ( (((uint32_t)seri_m)&0xFF)<<16 ) \
		| ( (((uint32_t)seri_s)&0xFF)<<24 ) \
		)


VA_EXPORTS void RGBIMAGE_create( RGBIMAGE *img, int32_t w, int32_t h, void *mmgr );
VA_EXPORTS void RGBIMAGE_destroy( RGBIMAGE *img, void *mmgr );
VA_EXPORTS void RGBIMAGE_clear( RGBIMAGE *img );
VA_EXPORTS void RGBIMAGE_clone( RGBIMAGE *src, RGBIMAGE *dst );
VA_EXPORTS void RGBIMAGE_get_pixel_val( RGBIMAGE *img, int32_t x, int32_t y, PIXVAL *pix );
VA_EXPORTS void RGBIMAGE_set_pixel_val( RGBIMAGE *img, int32_t x, int32_t y, PIXVAL *pix );

VA_EXPORTS void YUVIMAGE422_create( YUVIMAGE422 *img, int32_t w, int32_t h, void *mmgr );
VA_EXPORTS void YUVIMAGE422_destroy( YUVIMAGE422 *img, void *mmgr );
VA_EXPORTS void YUVIMAGE422_clear( YUVIMAGE422 *img );
VA_EXPORTS void YUVIMAGE422_clone( YUVIMAGE422 *src, YUVIMAGE422 *dst );

VA_EXPORTS void GRAYIMAGE_create( GRAYIMAGE *img, int32_t w, int32_t h, void *mmgr );
VA_EXPORTS void GRAYIMAGE_destroy( GRAYIMAGE *img, void *mmgr );
VA_EXPORTS void GRAYIMAGE_clear( GRAYIMAGE *img );
VA_EXPORTS void GRAYIMAGE_set( GRAYIMAGE *img, uint8_t val );
VA_EXPORTS void GRAYIMAGE_clone( GRAYIMAGE *src, GRAYIMAGE *dst );
VA_EXPORTS void GRAYIMAGE_clone2( GRAYIMAGE *src, GRAYIMAGE *dst );
VA_EXPORTS uint8_t GRAYIMAGE_get_pixel_val( GRAYIMAGE *img, int32_t x, int32_t y );
VA_EXPORTS void GRAYIMAGE_set_pixel_val( GRAYIMAGE *img, int32_t x, int32_t y, uint8_t val );

VA_EXPORTS void GRAYIMAGE2_create( GRAYIMAGE2 *img, int32_t w, int32_t h, void *mmgr );
VA_EXPORTS void GRAYIMAGE2_destroy( GRAYIMAGE2 *img, void *mmgr );
VA_EXPORTS void GRAYIMAGE2_clear( GRAYIMAGE2 *img );

VA_EXPORTS void TMPLIMAGE_create( TMPLIMAGE *img, int32_t buf_len, void *mmgr );
VA_EXPORTS void TMPLIMAGE_destroy( TMPLIMAGE *img, void *mmgr );
VA_EXPORTS void TMPLIMAGE_clear( TMPLIMAGE *img );
VA_EXPORTS void TMPLIMAGE_clone( TMPLIMAGE *src, TMPLIMAGE *dst );

VA_EXPORTS void ZDATBUF_alloc( ZDATBUF *zdb, int32_t buf_len, void *mmgr );
VA_EXPORTS void ZDATBUF_free( ZDATBUF *zdb, void *mmgr );
VA_EXPORTS void ZDATBUF_clear( ZDATBUF *zdb );
VA_EXPORTS void ZDATBUF_clone( ZDATBUF *src, ZDATBUF *dst );

VA_EXPORTS void read_stringdata( char *str, ZDATBUF *datbuf );
VA_EXPORTS void write_stringdata( ZDATBUF *datbuf, char *str );
VA_EXPORTS void read_filedata( char *filnam, ZDATBUF *datbuf );
VA_EXPORTS void write_filedata( ZDATBUF *datbuf, char *filnam );

VA_EXPORTS void VA_GenerateCRC( uint8_t *crc_buffer, int32_t len );
VA_EXPORTS int32_t VA_CheckCRC( uint8_t *crc_buffer, int32_t len );

VA_EXPORTS void *VA_malloc( int32_t sz, void *mmgr );
VA_EXPORTS void VA_mfree( void *mem, void *mmgr );

VA_EXPORTS void ZRECT_and( ZRECT *rc1, ZRECT *rc2, ZRECT *rc3 );
VA_EXPORTS void ZRECT_or( ZRECT *rc1, ZRECT *rc2, ZRECT *rc3 );
VA_EXPORTS void ZRECT_limit( ZRECT *rc1, ZRECT *rc2 );
VA_EXPORTS int32_t ZRECT_point( ZRECT *rc, int32_t x, int32_t y );


#ifdef __cplusplus
}
#endif


#endif
