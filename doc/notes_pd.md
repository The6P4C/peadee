# An initialisation sequence
- Writes 0x02 then 0x03 to 0x0C (Reset)
	- reset PD then reset all
- Delay
- Writes 0x0F to 0x0B (Power)
	- enable power to all internal functions
- Write 0x07 to 0x02 (Switches0)
	- enable pull-down on CC2, CC1
	- measure voltage CC1
- Delay
- Read 0x40 (Status)
	- Stores it somewhere
- Write 0x03 to 0x02
	- disable CC1 voltage measurement
- Write 0x0B to 0x02
	- measure voltage CC2
- Read 0x40 (Status)
	- Store it somewhere too
- Write 0x03 to 0x02
	- disable CC2 voltage measurement

# Other function
- Write 0x0F to 0x0B
	- power on
- Write 0x40 to 0x06
	- flush TX FIFO
- Writes 0xe hex = 14 dec bytes to the TX fifo
- Write 0x05 to 0x06
	- start TX, set current to default USB power
- Write 0x07 to 0x0B
	- turn off internal oscillator??

# Another one (`FUN_0800363c`)
- Check some values
	- Path 1: write 0x0B to 0x02 (meas CC2), write 0x26 to 0x03 (rev2, auto CRC + TX on CC2)
	- Path 2: write 0x07 to 0x02 (meas CC1), write 0x25 to 0x03 (rev2, auto CRC + TX on CC1)
- Write 0x02 to 0x0C
	- Reset PD logic
- Write 0x04 to 0x07
	- RX flush + ignore SOP' and SOP''
