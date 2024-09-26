#ifndef SPI_REGS_H

#define SPI_REGS_H

#define SPI0_baseaddr 		    0x43C10000
#define SPI1_baseaddr           0x43C20000

// #define SPI_SRR_OFFSET         	0x40  // Software reset register
// #define SPI_SPICR_OFFSET      	0x60  // SPI control register
// #define SPI_SPISR_OFFSET  		0x64  // SPI status register
// #define SPI_DTR_OFFSET         	0x68  // SPI data transmit register
// #define SPI_DRR_OFFSET        	0x6C  // SPI data receive register
// #define SPI_SPISSR_OFFSET      	0x70  // SPI Slave select register
// #define SPI_TXFIFO_OFFSET     	0x74  // SPI Transmit FIFO Occupancy Register
// #define SPI_RXFIFO_OFFSET      	0x78  // SPI Receive FIFO Occupancy Register

//offsets scaled by sizeof(unsigned int)
#define SPI_SRR_OFFSET         	0x10  // Software reset register (0x40 / 4)
#define SPI_SPICR_OFFSET      	0x18  // SPI control register (0x60 / 4)
#define SPI_SPISR_OFFSET  		0x19  // SPI status register (0x64 / 4)
#define SPI_DTR_OFFSET         	0x1A  // SPI data transmit register (0x68 / 4)
#define SPI_DRR_OFFSET        	0x1B  // SPI data receive register (0x6C / 4)
#define SPI_SPISSR_OFFSET      	0x1C  // SPI Slave select register (0x70 / 4)
#define SPI_TXFIFO_OFFSET     	0x1D  // SPI Transmit FIFO Occupancy Register (0x74 / 4)
#define SPI_RXFIFO_OFFSET      	0x1E  // SPI Receive FIFO Occupancy Register (0x78 / 4)



// SPICR Bit Definitions

#define SPI_CR_LSB_FIRST_SHIFT     9     // LSB first data transfer format
#define SPI_CR_LSB_FIRST_MASK      (1 << SPI_CR_LSB_FIRST_SHIFT)

#define SPI_CR_MSTR_INHIBIT_SHIFT  8     // Master transaction inhibit
#define SPI_CR_MSTR_INHIBIT_MASK   (1 << SPI_CR_MSTR_INHIBIT_SHIFT)

#define SPI_CR_MANUAL_SS_SHIFT     7     // Manual Slave Select assertion enable
#define SPI_CR_MANUAL_SS_MASK      (1 << SPI_CR_MANUAL_SS_SHIFT)

#define SPI_CR_RX_FIFO_RST_SHIFT   6     // Receive FIFO reset
#define SPI_CR_RX_FIFO_RST_MASK    (1 << SPI_CR_RX_FIFO_RST_SHIFT)

#define SPI_CR_TX_FIFO_RST_SHIFT   5     // Transmit FIFO reset
#define SPI_CR_TX_FIFO_RST_MASK    (1 << SPI_CR_TX_FIFO_RST_SHIFT)

#define SPI_CR_CPHA_SHIFT          4     // Clock phase
#define SPI_CR_CPHA_MASK           (1 << SPI_CR_CPHA_SHIFT)

#define SPI_CR_CPOL_SHIFT          3     // Clock polarity
#define SPI_CR_CPOL_MASK           (1 << SPI_CR_CPOL_SHIFT)

#define SPI_CR_MASTER_SHIFT        2     // Master mode
#define SPI_CR_MASTER_MASK         (1 << SPI_CR_MASTER_SHIFT)

#define SPI_CR_SPE_SHIFT           1     // SPI system enable
#define SPI_CR_SPE_MASK            (1 << SPI_CR_SPE_SHIFT)

#define SPI_CR_LOOP_SHIFT          0     // Local loopback mode
#define SPI_CR_LOOP_MASK           (1 << SPI_CR_LOOP_SHIFT)

// SPISR Bit Definitions

#define SPI_SR_CMD_ERR_SHIFT         10  // Command Error
#define SPI_SR_CMD_ERR_MASK          (1 << SPI_SR_CMD_ERR_SHIFT)

#define SPI_SR_LOOP_ERR_SHIFT        9   // Loopback Error
#define SPI_SR_LOOP_ERR_MASK         (1 << SPI_SR_LOOP_ERR_SHIFT)

#define SPI_SR_MSB_ERR_SHIFT         8   // MSB Error
#define SPI_SR_MSB_ERR_MASK          (1 << SPI_SR_MSB_ERR_SHIFT)

#define SPI_SR_SLV_MODE_ERR_SHIFT    7   // Slave Mode Error
#define SPI_SR_SLV_MODE_ERR_MASK     (1 << SPI_SR_SLV_MODE_ERR_SHIFT)

#define SPI_SR_CPOL_CPHA_ERR_SHIFT   6   // CPOL and CPHA Error
#define SPI_SR_CPOL_CPHA_ERR_MASK    (1 << SPI_SR_CPOL_CPHA_ERR_SHIFT)

#define SPI_SR_SLV_MODE_SEL_SHIFT    5   // Slave Mode Select
#define SPI_SR_SLV_MODE_SEL_MASK     (1 << SPI_SR_SLV_MODE_SEL_SHIFT)

#define SPI_SR_MODF_SHIFT            4   // Mode-fault Error
#define SPI_SR_MODF_MASK             (1 << SPI_SR_MODF_SHIFT)

#define SPI_SR_TX_FULL_SHIFT         3   // Transmit Full
#define SPI_SR_TX_FULL_MASK          (1 << SPI_SR_TX_FULL_SHIFT)

#define SPI_SR_TX_EMPTY_SHIFT        2   // Transmit Empty
#define SPI_SR_TX_EMPTY_MASK         (1 << SPI_SR_TX_EMPTY_SHIFT)

#define SPI_SR_RX_FULL_SHIFT         1   // Receive Full
#define SPI_SR_RX_FULL_MASK          (1 << SPI_SR_RX_FULL_SHIFT)

#define SPI_SR_RX_EMPTY_SHIFT        0   // Receive Empty
#define SPI_SR_RX_EMPTY_MASK         (1 << SPI_SR_RX_EMPTY_SHIFT)

#endif