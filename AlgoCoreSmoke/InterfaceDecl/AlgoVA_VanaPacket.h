
#ifndef _ALGOVA_VANA_PACKET_H_
#define _ALGOVA_VANA_PACKET_H_

#include "AlgoVA_Vana.h"


#ifdef __cplusplus
extern "C"
{
#endif


VA_EXPORTS int32_t VA_WriteVZIMAGE( GRAYIMAGE *pImage, uint8_t *pData );
VA_EXPORTS int32_t VA_ReadVZIMAGE( uint8_t *pData, GRAYIMAGE *pImage );


#define PARSE_PARFILE_START \
	i=0; \
	while( i<len ) \
	{ \
		str1 = data+i; \
		while( i<len && data[i++] != '=' ); \
		len1 = data+i-str1-1; \
		str2 = data+i; \
		while( i<len && data[i++] != '\n' ); \
		if(0) \
		{ \
		}
// 	int32_t len2;
// 		len2 = data+i-str2-1;

#define PARSE_PARFILE_END \
	}

#define PARSE_PARFILE_ITEM_INT( str, par ) \
		else if( strncmp( str1, str, len1 ) == 0 ) \
		{ \
			par = atoi( str2 ); \
		}
#define PARSE_PARFILE_ITEM_REAL( str, par ) \
		else if( strncmp( str1, str, len1 ) == 0 ) \
		{ \
			par = (real)atof( str2 ); \
		}

#define PARSE_PARFILE_ITEM_LINE( str, line ) \
		else if( strncmp( str1, str, len1 ) == 0 ) \
		{ \
			int32_t xs, ys, xe, ye; \
			sscanf( str2, "((%d,%d),(%d,%d))", &xs, &ys, &xe, &ye ); \
			line.pt_s.x = xs; line.pt_s.y = ys;	line.pt_e.x = xe; line.pt_e.y = ye; \
		}

#define PARSE_PARFILE_ITEM_FINTVAL( str, intval ) \
		else if( strncmp( str1, str, len1 ) == 0 ) \
		{ \
			int32_t forbidden, minimum, maximum; \
			sscanf( str2, "(%d,%d,%d)", &forbidden, &minimum, &maximum ); \
			intval.forbidden = forbidden; intval.minimum = minimum; intval.maximum = maximum; \
		}

#define PARSE_PARFILE_ITEM_ZRECT( str, rect ) \
		else if( strncmp( str1, str, len1 ) == 0 ) \
		{ \
			int32_t lb_x, lb_y, ru_x, ru_y; \
			sscanf( str2, "(%d,%d,%d,%d)", &lb_x, &lb_y, &ru_x, &ru_y ); \
			rect.lb_x = lb_x; rect.lb_y = lb_y; rect.ru_x = ru_x; rect.ru_y = ru_y; \
		}


#define PACKET_PARFILE_START \
	{ \
		str1 = data; \
		str2 = data;

#define PACKET_PARFILE_END \
		len = str2 - str1; \
	}

#define PACKET_PARFILE_ITEM_INT( str, par ) \
		{ \
			str2 += sprintf( str2, "%s=%d\n", str, par ); \
		}
#define PACKET_PARFILE_ITEM_REAL( str, par ) \
		{ \
			str2 += sprintf( str2, "%s=%.2f\n", str, par ); \
		}

#define PACKET_PARFILE_ITEM_LINE( str, line ) \
		{ \
			int32_t xs, ys, xe, ye; \
			xs = line.pt_s.x; ys = line.pt_s.y;	xe = line.pt_e.x; ye = line.pt_e.y; \
			str2 += sprintf( str2, "%s=((%d,%d),(%d,%d))\n", str, xs, ys, xe, ye ); \
		}

#define PACKET_PARFILE_ITEM_FINTVAL( str, intval ) \
		{ \
			int32_t forbidden, minimum, maximum; \
			forbidden = intval.forbidden; minimum = intval.minimum; maximum = intval.maximum; \
			str2 += sprintf( str2, "%s=(%d,%d,%d)\n", str, forbidden, minimum, maximum ); \
		}

#define PACKET_PARFILE_ITEM_ZRECT( str, rect ) \
		{ \
			str2 += sprintf( str2, "%s=(%d,%d,%d,%d)\n", str, rect.lb_x, rect.lb_y, rect.ru_x, rect.ru_y ); \
		}


#ifdef __cplusplus
}
#endif


#endif

