/**
 * @brief Reads from the designated address a byte
 * @param addr: device address to read from
 * @param data: byte to read
 * @return 0 if success, and the error code otherwise
 */
int i2c_read(char addr, char *data);
/**
 * @brief Push/pop to the buffer a specified command
 * @param fifo: buffer
 * @param data: byte to push/pop/send
 * @return 0 if success, and the error code otherwise
 */
int fifo_push(fifo *f, char data);
int fifo_pop(fifo *f, char *data);
int fifo_init(fifo *fif);
int ir_send(char data);
