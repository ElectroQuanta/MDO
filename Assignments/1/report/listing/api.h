/**
 * @brief Reads from the designated address a byte
 * @param addr: device address to read from
 * @param data: byte to read
 * @return 0 if success, and the error code otherwise
 */
int i2c_read(char addr, char *data);
