#ifndef XXH3_H
#define XXH3_H

#include <stdint.h>
#include <stdlib.h>

static uint64_t xxh64(const void* data, size_t len, uint64_t seed) {
    uint64_t p1=0x9e3779b185ebca87,p2=0xc2b2ae3d27d4eb4f,p3=0x165667b19e3779f9;
    uint64_t p4=0x85ebca77c2b2ae63,p5=0x27d4eb2f165667c5;
    uint64_t n=len,h=seed+p5+n,x,v0=seed+p1+p2,v1=seed+p2,v2=seed+0,v3=seed-p1;
    uint8_t *p=(uint8_t*)data;
    #define XXH8()(x=*((uint64_t*)p),p+=8,len-=8,x)
    #define XXH4()(x=*((uint32_t*)p),p+=4,len-=4,x)
    #define XXHR(x,r)(((x)<<(r))|((x)>>(64-(r))))
    #define XXHS(v)v+=XXH8()*p2,v=XXHR(v,31),v*=p1
    #define XXHF(v)v*=p2,v=XXHR(v,31),v*=p1,h^=v,h=h*p1+p4
    if(n<32)goto l8;
    do XXHS(v0),XXHS(v1),XXHS(v2),XXHS(v3);while(len>=32);
    h=XXHR(v0,1)+XXHR(v1,7)+XXHR(v2,12)+XXHR(v3,18);
    XXHF(v0),XXHF(v1),XXHF(v2),XXHF(v3),h+=n;
    l8:while(len>=8)XXH8(),x*=p2,x=XXHR(x,31),x*=p1,h^=x,h=XXHR(h,27)*p1+p4;
    if(len>=4)h^=XXH4()*p1,h=XXHR(h,23)*p2+p3;
    while(len)h^=(*p)*p5,h=XXHR(h,11)*p1,p++,len--;
    h=(h^(h>>33))*p2;h=(h^(h>>29))*p3;h=(h^(h>>32));
    return h;
}

#endif
