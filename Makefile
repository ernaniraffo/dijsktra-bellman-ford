# -------------------
#  Ernani Raffo
#  Makefile
#  ------------------

SOURCES        = $(wildcard *.c)
OBJ 		   = $(SOURCES:%.c=%.o)
OBJ_FIND_PATH  = FindPath.o Graph.o PriorityQueue.o List.o
OBJ_GRAPH_TEST = GraphTest.o Graph.o PriorityQueue.o List.o
OBJ_QUEUE_TEST = PriorityQueueTest.o PriorityQueue.o
OBJ_LIST_TEST  = ListTest.o List.o

CFLAGS 		   = -Wall
COMPILE        = gcc -std=c17 $(CLFAGS) -c
LINK           = gcc -std=c17 -Wall $(CFLAGS) -o

.PHONY: clean tidy debug

FindPath: $(OBJ_FIND_PATH)
	$(LINK) $@ $^

GraphTest: $(OBJ_GRAPH_TEST)
	$(LINK) $@ $^

PriorityQueueTest: $(OBJ_QUEUE_TEST)
	$(LINK) $@ $^

ListTest: $(OBJ_LIST_TEST)
	$(LINK) $@ $^

%.o: %.c
	$(COMPILE) $<

debug: CFLAGS += -g
debug: clean FindPath
	lldb ./FindPath in1 out1

tidy: 
	rm -f $(OBJ)

clean: tidy
	rm -f FindPath GraphTest PriorityQueueTest ListTest
