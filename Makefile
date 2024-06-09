.PHONY: clean

BUILD = build
CC = cc
FLAGS = -Wall -Wextra 
OUTPUT = netfunctions

DEPS = $(BUILD)/main.o $(BUILD)/net.o $(BUILD)/freader.o $(BUILD)/frunner.o
$(OUTPUT): $(DEPS) 
	gcc $^ $(FLAGS) -std=c99 -o $@

$(BUILD)/main.o: main.c
	$(CC) -c $(FLAGS) -o $@ $<

$(BUILD)/net.o: net/net.c net/net.h
	$(CC) -c $(FLAGS) -o $@ $<

$(BUILD)/freader.o: functions/freader.c functions/freader.h
	$(CC) -c $(FLAGS) -o $@ $<

$(BUILD)/frunner.o: functions/frunner.c functions/frunner.h
	$(CC) -c $(FLAGS) -o $@ $<

clean:
	rm -rf $(BUILD)
	rm netfunctions
