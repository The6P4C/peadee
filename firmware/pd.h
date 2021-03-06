#ifndef PD_H
#define PD_H
#include <stddef.h>
#include <stdint.h>

#define PD_REG_DEVICE_ID (0x01)
#define PD_REG_SWITCHES0 (0x02)
#define PD_REG_SWITCHES1 (0x03)
#define PD_REG_MEASURE (0x04)
#define PD_REG_SLICE (0x05)
#define PD_REG_CONTROL0 (0x06)
#define PD_REG_CONTROL1 (0x07)
#define PD_REG_CONTROL2 (0x08)
#define PD_REG_CONTROL3 (0x09)
#define PD_REG_MASK1 (0x0a)
#define PD_REG_POWER (0x0b)
#define PD_REG_RESET (0x0c)
#define PD_REG_OCPREG (0x0d)
#define PD_REG_MASKA (0x0e)
#define PD_REG_CONTROL4 (0x0f)
#define PD_REG_STATUS0A (0x3c)
#define PD_REG_STATUS1A (0x3d)
#define PD_REG_INTERRUPTA (0x3e)
#define PD_REG_INTERRUPTB (0x3f)
#define PD_REG_STATUS0 (0x40)
#define PD_REG_STATUS1 (0x41)
#define PD_REG_INTERRUPT (0x42)
#define PD_REG_FIFOS (0x43)

#define PD_SWITCHES0_MEAS_CC2 (1 << 3)
#define PD_SWITCHES0_MEAS_CC1 (1 << 2)
#define PD_SWITCHES0_PDWN2 (1 << 1)
#define PD_SWITCHES0_PDWN1 (1 << 0)
#define PD_SWITCHES1_SPECREV_POS (5)
#define PD_SWITCHES1_AUTO_CRC (1 << 2)
#define PD_SWITCHES1_TXCC2 (1 << 1)
#define PD_SWITCHES1_TXCC1 (1 << 0)
#define PD_CONTROL0_TX_START (1 << 0)
#define PD_CONTROL3_SEND_HARD_RESET (1 << 6)
#define PD_CONTROL3_N_RETRIES_POS (1)
#define PD_CONTROL3_AUTO_RETRY (1 << 0)
#define PD_RESET_PD_RESET (1 << 1)
#define PD_RESET_SW_RES (1 << 0)
#define PD_STATUS0_BC_LVL_MASK (0b11 << 0)
#define PD_STATUS1_RX_EMPTY (1 << 5)

#define PD_TXFIFO_TOK_SOP1 (0x12)
#define PD_TXFIFO_TOK_SOP2 (0x13)
#define PD_TXFIFO_TOK_PACKSYM(n) (0x80 + (n))
#define PD_TXFIFO_TOK_JAM_CRC (0xFF)
#define PD_TXFIFO_TOK_EOP (0x14)
#define PD_TXFIFO_TOK_TXOFF (0xFE)
#define PD_RXFIFO_TOK_SOP_MASK (0b11100000)
#define PD_RXFIFO_TOK_SOP (0b11100000)

struct pd_message_standard {
	uint32_t data_objects[7];
};

struct pd_message_extended {
	uint16_t extended_header;
	// Though the spec allows 260 bytes of data, the FUSB302 only has 48 bytes
	// of space in the TxFIFO. Subtracting the header and extended header
	// leaves us with 44 bytes of data.
	uint8_t data[44];
};

struct pd_message {
	uint16_t header;
	union {
		struct pd_message_standard standard;
		struct pd_message_extended extended;
	} payload;
	uint32_t crc;
};

void pd_setup();
int pd_try_attach();

int pd_poll_rxfifo(struct pd_message *message);
void pd_tx_standard(uint16_t header, struct pd_message_standard *payload);
void pd_tx_extended(uint16_t header, struct pd_message_extended *payload);

void pd_write_reg(uint8_t reg, uint8_t value);
void pd_write_fifo(uint8_t *data, size_t count);
uint8_t pd_read_reg(uint8_t reg);
void pd_read_fifo(uint8_t *data, size_t count);
#endif
