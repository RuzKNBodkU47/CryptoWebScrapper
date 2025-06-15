#ifndef BITSOTRACKER_H
#define BITSOTRACKER_H

void init_string(struct string *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
int BitsoTracker_main();
#endif