#ifndef EGX_TYPEE_HEADER_
#define EGX_TYPEE_HEADER_

#ifndef EGX_DEFINE_SZ_TYPE
#define EGX_DEFINE_SZ_TYPE unsigned short
#endif

#ifndef EGX_DEFINE_BYTE_TYPE
#define EGX_DEFINE_BYTE_TYPE unsigned char
#endif

typedef EGX_DEFINE_BYTE_TYPE EGX_BYTE;
typedef EGX_DEFINE_SZ_TYPE EGX_SZ;
typedef EGX_BYTE /* <- smallest possible */  EGX_BOOL;
#define EGX_TRUE (1)
#define EGX_FALSE (0)

#endif
