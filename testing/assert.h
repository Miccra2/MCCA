#ifndef __ASSERT_H__
#define __ASSERT_H__

#define ASSERT(cond, msg, ...) {if (!(cond)) { fprintf(stderr, "ERROR: "msg"\n", ##__VA_ARGS__); ERRORCODE = 1; goto ASSERTED; } fprintf(stderr, "SUCCESS: "msg"\n", ##__VA_ARGS__);}

#endif // __ASSERT_H__
