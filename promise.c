#include <stdlib.h>
#include <stdio.h>

#include <sys/queue.h>

struct api_ctx;

struct promise {
	void (*promise_cb)(struct api_ctx *);
	TAILQ_ENTRY(promise) promises;
};

struct promise_list {
	struct promise *tqh_first;
	struct promise **tqh_last;
};

struct api_ctx {
	struct promise_list plist;
};

static void
do_second_thing(struct api_ctx *b)
{
	struct promise *p;

	printf("second\n");
	p = TAILQ_FIRST(&b->plist);
	TAILQ_REMOVE(&b->plist, p, promises);
	p->promise_cb(b);
}

static void
do_first_thing(struct api_ctx *b)
{
	struct promise *p;
	printf("first\n");

	p = malloc(sizeof(struct promise));
	p->promise_cb = do_second_thing;

	TAILQ_INSERT_HEAD(&b->plist, p, promises);

	p = TAILQ_FIRST(&b->plist);
	TAILQ_REMOVE(&b->plist, p, promises);
	p->promise_cb(b);
}

static void
do_third_thing(struct api_ctx *b)
{
	printf("third\n");
}

static void
run(void)
{
	struct api_ctx *b = malloc(sizeof(struct api_ctx));
	struct promise *p;

	p = malloc(sizeof(struct promise));
	p->promise_cb = do_third_thing;

	TAILQ_INIT(&b->plist);
	TAILQ_INSERT_TAIL(&b->plist, p, promises);
	do_first_thing(b);
}

int
main(int argc, char *argv[])
{
	run();
	return 0;
}
