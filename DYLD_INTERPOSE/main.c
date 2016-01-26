
#include <malloc/malloc.h>
 
#define DYLD_INTERPOSE(_replacement,_replacee) \
__attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
__attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };
 
 
void *hacked_malloc(size_t size){
    void *ret = malloc(size);
     
    malloc_printf("+ %p %d\n", ret, size);
    return ret;
}
 
void hacked_free(void *freed){
    malloc_printf("- %p\n", freed);
    free(freed);
}
ssize_t hacked_write(int fildes, const void *buf, size_t nbyte)
{
    printf("[++++]into hacked_write－－－by piaoyun");
    return write(fildes, buf, nbyte);
}
 
DYLD_INTERPOSE(hacked_write, write);
DYLD_INTERPOSE(hacked_malloc, malloc)
DYLD_INTERPOSE(hacked_free, free);