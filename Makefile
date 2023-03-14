CC = gcc
BIN_DIR = bin
SRC_DIR = src

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $< -lm

clean:
	rm -rf $(BIN_DIR) &> /dev/null