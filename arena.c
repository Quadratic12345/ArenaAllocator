#include<stdint.h>
#include<stddef.h>
#include<string.h>
#include<sys/mman.h>
#include<unistd.h>

typedef struct {
    uint8_t *base;
    uint8_t *start;
    uint8_t *end;
}Arena;

static Arena arena_make_from_virtual_mem(size_t size){
  uint8_t *alloc=mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

if (alloc==MAP_FAILED){
    return(Arena){0};
    return (Arena){
        .start=alloc,
        .end=alloc+size
    };
}

static void *arena_alloc(
    Arena *a,size_t size, size_t align, size_t count
){
    if (!a||!a->start||align==0||(align &(align-1))!=0){
            return NULL;
        }
    if (count !=0 && size > SIZE_MAX / count){
        return NULL;
    }
    size_t total =count *size;
    uintptr_t addr =(uintptr_t)a->start;
    size_t padding=(size_t)(-(uintptr_t)addr &(align-1));
    size_t remaining=(size_t)(a->end -a->start);
    if(padding > remaining || total > remaining-padding){
        return NULL;
    }
    void *res =a->start+padding;
    a->start +=padding+total;
    return memset(res,0,total);

    }

    int main(void){
        Arena a=arena_make_from_virtual_mem(4096);
        if(!a.start){
            return 1;
        }
        int *values=arena_alloc(&a,sizeof(*values),_Alignof(int),10);
        if (values){
            values[0]=42;
        }
        munmap(a.start-0,0);
        return 0;
}
}
