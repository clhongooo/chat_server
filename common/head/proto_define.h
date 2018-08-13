#pragma once

#ifndef PROTO_DEFINE_H
#define PROTO_DEFINE_H

#include "base_type.h"

#ifdef WIN32
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include <string>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#endif


/*namespace NS_PROTO
{
*/
inline  uint32 hton__(uint32 h)    {        return htonl(h);    }
inline  uint32 ntoh__(uint32 n)    {        return ntohl(n);    }


inline    int32 hton__(int32 h)    {        return htonl(h);    }
inline    int32 ntoh__(int32 n)    {        return ntohl(n);    }


inline    uint16 hton__(uint16 h)    {        return htons(h);    }
inline     uint16 ntoh__(uint16 n)    {        return ntohs(n);    }

inline    int16 hton__(int16 h)    {        return htons(h);    }
inline    int16 ntoh__(int16 n)    {        return ntohs(n);    }


inline    uint8 hton__(uint8 h)        {        return h;    }
inline    uint8 ntoh__(uint8 h)        {        return h;    }

inline    int8 hton__(int8 h)            {        return h;    }
inline    int8 ntoh__(int8 h)            {        return h;    }


inline     uint64 ntoh64__(uint64 src)
    {
        uint64 dst;
        uint8* dbytep = (uint8*)&dst;
        uint8* sbytep = (uint8*)&src;
        dbytep[0] = sbytep[7];
        dbytep[1] = sbytep[6];
        dbytep[2] = sbytep[5];
        dbytep[3] = sbytep[4];
        dbytep[4] = sbytep[3];
        dbytep[5] = sbytep[2];
        dbytep[6] = sbytep[1];
        dbytep[7] = sbytep[0];
        return dst;
    }

inline uint64 ntoh__(uint64 src)    {    return ntoh64__(src);    }
inline uint64 hton__(uint64 src)    {    return ntoh64__(src);    }

inline int64 ntoh__(int64 src)    {    return ntoh64__(src);    }
inline int64 hton__(int64 src)    {    return ntoh64__(src);    }




    //////////////////////////////////////////////////////////////////////////

    enum ProtoErrorDefine
    {
        PROTO_ERROR_DST_BUF_NOT_ENOUGH = -1,
        PROTO_ERROR_SRC_BUF_TOO_SHORT = -2,
        PROTO_ERROR_ARRAY_COUNT_OVERFLOW = -3,
        PROTO_ERROR_C_STRING_TOO_LONG = -4,
        PROTO_ERROR_UNDEFINE_UNION_SELECT = -5,
        PROTO_ERROR_TLV_LEN_TOO_SHORT = -6,
    };


    #define checkadd(p_, exp_)\
    ret = (exp_);    \
    if (ret < 0) return ret; \
    (p_) += ret;\

    #define checkaddlen(p_, len_, exp_)\
    ret = (exp_);    \
    if (ret < 0) return ret; \
    if (ret > len_) return PROTO_ERROR_TLV_LEN_TOO_SHORT;\
    (p_) += len_;\

    template<class T>
    int32 proto_pack__(void *dst, const void * const dep, const T &src)
    {
        if ((uint8 *)dst + sizeof(T) > (uint8 *)dep)
        {
            return PROTO_ERROR_DST_BUF_NOT_ENOUGH;
        }
        *(T*)dst = hton__(src);
        return (int32)sizeof(T);
    }

    template<class T>
    int32 proto_unpack__(T &dst, const void *src, const void * const sep)
    {
        if ((uint8 *)src + sizeof(T) > (uint8 *)sep)
        {
            return PROTO_ERROR_SRC_BUF_TOO_SHORT;
        }
        dst = ntoh__(*(T*)(src));
        return (int32)sizeof(T);
    }


inline    int32 proto_pack(void *dst, const void * const dep, const int8 &src)
    {
        return proto_pack__<int8>(dst, dep, src);
    }

inline    int32 proto_pack(void *dst, const void * const dep, const uint8 &src)
    {
        return proto_pack__<uint8>(dst, dep, src);
    }

inline    int32 proto_pack(void *dst, const void * const dep, const int16 &src)
    {
        return proto_pack__<int16>(dst, dep, src);
    }

inline    int32 proto_pack(void *dst, const void * const dep, const uint16 &src)
    {
        return proto_pack__<uint16>(dst, dep, src);
    }

inline    int32 proto_pack(void *dst, const void * const dep, const int32 &src)
    {
        return proto_pack__<int32>(dst, dep, src);
    }

inline    int32 proto_pack(void *dst, const void * const dep, const uint32 &src)
    {
        return proto_pack__<uint32>(dst, dep, src);
    }

inline    int32 proto_pack(void *dst, const void * const dep, const int64 &src)
    {
        return proto_pack__<int64>(dst, dep, src);
    }

inline    int32 proto_pack(void *dst, const void * const dep, const uint64 &src)
    {
        return proto_pack__<uint64>(dst, dep, src);
    }






    //////////////////////////////////////////////////////////////////////////

inline    int32 proto_unpack(int8 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<int8>(dst, src, sep);
    }

inline    int32 proto_unpack(uint8 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<uint8>(dst, src, sep);
    }

inline    int32 proto_unpack(int16 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<int16>(dst, src, sep);
    }

inline    int32 proto_unpack(uint16 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<uint16>(dst, src, sep);
    }

inline    int32 proto_unpack(int32 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<int32>(dst, src, sep);
    }

inline    int32 proto_unpack(uint32 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<uint32>(dst, src, sep);
    }


inline    int32 proto_unpack(int64 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<int64>(dst, src, sep);
    }

inline    int32 proto_unpack(uint64 &dst, const void *src, const void * const sep)
    {
        return proto_unpack__<uint64>(dst, src, sep);
    }


    template<class T>
    int32 proto_pack_array(void * dst, const void * const dep, const T *array, uint32 maxcount, uint32 count)
    {
        int32 ret;
        if (count > maxcount)
        {
            return PROTO_ERROR_ARRAY_COUNT_OVERFLOW;
        }
        uint8 *d = (uint8 *)dst;
        for (uint32 i = 0; i < count; ++i)
        {
            checkadd(d, proto_pack(d, dep, array[i]));
        }
        return (int32)(d - (uint8 *)dst);
    }

    template<class T>
    int proto_unpack_array(T *array, uint32 maxcount, uint32 count, const void *src, const void * const sep)
    {
        int32 ret;
        if (count > maxcount)
        {
            return PROTO_ERROR_ARRAY_COUNT_OVERFLOW;
        }
        uint8 *s = (uint8 *)src;
        for (uint32 i = 0; i < count; ++i)
        {
            checkadd(s, proto_unpack(array[i], s, sep));
        }
        return (int32)(s - (uint8 *)src);
    };


inline    int32 proto_pack_cstring(void *dst, const void * const dep, const char *src /*, const void const *sep */, uint32 maxsize)
    {
        int32 ret;

        *((char *)src + maxsize - 1) = '\0';        // 强制截断

        uint8 len = (uint8)strlen(src);

        if ((uint8 *)dst + sizeof(len) + len > (uint8 *)dep)
        {
            return PROTO_ERROR_DST_BUF_NOT_ENOUGH;
        }
        uint8 *d = (uint8 *)dst;
        checkadd(d, proto_pack__<uint8>(d, dep, len));                // pack length of string
        memcpy(d, src, len);                                // pack string not include tail '\0';
        d += len;

        return (int32)(d - (uint8 *)dst);
    }

inline    int32 proto_unpack_cstring(char *dst, /* const void * const dep, */ uint32 maxsize, const void *src, const void * const sep)
    {
        int32 ret;
        uint8 *s = (uint8 *)src;
        uint8 len = 0;
        checkadd(s, proto_unpack(len, s, sep));         // unpack length of string

        if (len >= maxsize)        // 等于也为非法，因为要有'\0' 结尾
        {
            return PROTO_ERROR_C_STRING_TOO_LONG;
        }
        if (len > (uint32)((uint8 *)sep - s))
        {
            return PROTO_ERROR_SRC_BUF_TOO_SHORT;
        }
/*        if ((uint8 *)dst + len + 1 > dep)    // 检查
        {
            return PROTO_ERROR_DST_BUF_NOT_ENOUGH;
        }
*/
        memcpy(dst, s, len);
        s += len;
        dst[len] = '\0';
        return (int32)(s - (uint8 *)src);
    }

inline    int32 proto_pack_wstring(void *dst, const void * const dep, const char *src /*, const void const *sep */, uint32 maxsize)
    {
        int32 ret;

        *((char *)src + maxsize - 1) = '\0';        // 强制截断

        uint16 len = (uint16)strlen(src);

        if ((uint8 *)dst + sizeof(len) + len > (uint8 *)dep)
        {
            return PROTO_ERROR_DST_BUF_NOT_ENOUGH;
        }
        uint8 *d = (uint8 *)dst;
        checkadd(d, proto_pack__<uint16>(d, dep, len));                // pack length of string
        memcpy(d, src, len);                                // pack string not include tail '\0';
        d += len;

        return (int32)(d - (uint8 *)dst);
    }


inline    int32 proto_unpack_wstring(char *dst, /* const void * const dep, */ uint32 maxsize, const void *src, const void * const sep)
    {
        int32 ret;
        uint8 *s = (uint8 *)src;
        uint16 len = 0;
        checkadd(s, proto_unpack__<uint16>(len, s, sep));         // unpack length of string

        if (len >= maxsize)        // 等于也为非法，因为要有'\0' 结尾
        {
            return PROTO_ERROR_C_STRING_TOO_LONG;
        }
        if (len > (uint32)((uint8 *)sep - s))
        {
            return PROTO_ERROR_SRC_BUF_TOO_SHORT;
        }
        /*        if ((uint8 *)dst + len + 1 > dep)    // 检查
        {
        return PROTO_ERROR_DST_BUF_NOT_ENOUGH;
        }
        */
        memcpy(dst, s, len);
        s += len;
        dst[len] = '\0';
        return (int32)(s - (uint8 *)src);
    }


inline    int32 proto_pack_string(void *dst, const void * const dep, const void *src /*, const void * const sep */, uint32 maxsize)
    {
        *((char *)src + maxsize - 1) = '\0';        // 强制截断

        uint16 len = (uint16)strlen((const char *)src);        // 最大支持ushort 长度

        if ((uint8 *)dst + len > (uint8 *)dep)
        {
            return PROTO_ERROR_DST_BUF_NOT_ENOUGH;
        }
        memcpy(dst, src, len);                                // pack string not include tail '\0';

        return len;
    }

inline    int32 proto_unpack_string(char *dst, /* const void * const dep, */ uint32 maxsize, uint32 len, const void *src, const void * const sep)
    {
        uint8 *s = (uint8 *)src;

        if (len >= maxsize)        // 等于也为非法，因为要有'\0' 结尾
        {
            return PROTO_ERROR_C_STRING_TOO_LONG;
        }
        if (len > (uint32)((uint8 *)sep - s))
        {
            return PROTO_ERROR_SRC_BUF_TOO_SHORT;
        }
        memcpy(dst, s, len);
        s += len;
        dst[len] = '\0';
        return (int32)(s - (uint8 *)src);
    }

#endif
