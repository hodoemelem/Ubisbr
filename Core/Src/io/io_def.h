/**
 ******************************************************************************
 *  @attention
 *
 *  All Rights Reserved
 *  Copyright (C) 2023  Henry Odoemelem <hodoemelem@gmail.com>
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *******************************************************************************
 */

#ifndef IO_DEF_H
#define IO_DEF_H

#include "stm32l476xx.h"

#define OUTPUT 0b01
#define INPUT 0
#define ALT 0b10
#define AF1_TIMER 0b0001
#define AF2_TIMER 0b0010
#define USART 0b0111
#define I2C 0b0100
#define SETBIT 0b1
#define USART_1 0
#define USART_2 1
#define USART_3 2
#define TIM_1   0
#define TIM_2   1
#define TIM_3   2
#define I2C_1 0
#define I2C_2 1
#define READ 0
#define WRITE 1
#define DMA1_Ch5 4
#define DMA1_Ch6 5
#define DMA1_Ch2 1
enum ePORT
{
    PORTA,
    PORTB,
    PORTC,
    PORT_END
};

enum eMODE
{
    MODE0,
    MODE1,
    MODE2,
    MODE3,
    MODE4,
    MODE5,
    MODE6,
    MODE7,
    MODE8,
    MODE9,
    MODE10,
    MODE11,
    MODE12,
    MODE13,
    MODE14,
    MODE15,
};

typedef struct
{
    unsigned char MODE0 : 2;
    unsigned char MODE1 : 2;
    unsigned char MODE2 : 2;
    unsigned char MODE3 : 2;
    unsigned char MODE4 : 2;
    unsigned char MODE5 : 2;
    unsigned char MODE6 : 2;
    unsigned char MODE7 : 2;
    unsigned char MODE8 : 2;
    unsigned char MODE9 : 2;
    unsigned char MODE10 : 2;
    unsigned char MODE11 : 2;
    unsigned char MODE12 : 2;
    unsigned char MODE13 : 2;
    unsigned char MODE14 : 2;
    unsigned char MODE15 : 2;
} MODE_t;

typedef union
{
    volatile MODE_t *MODE;    // 32 bits, 4 bytes
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} GPIO_MODER_t;
extern GPIO_MODER_t GPIO_MODER[PORT_END];


enum eBSRR
{
    BS0,
    BS1,
    BS2,
    BS3,
    BS4,
    BS5,
    BS6,
    BS7,
    BS8,
    BS9,
    BS10,
    BS11,
    BS12,
    BS13,
    BS14,
    BS15,
    BR0,
    BR1,
    BR2,
    BR3,
    BR4,
    BR5,
    BR6,
    BR7,
    BR8,
    BR9,
    BR10,
    BR11,
    BR12,
    BR13,
    BR14,
    BR15,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} GPIO_BSRR_t;
extern GPIO_BSRR_t GPIO_BSRR[PORT_END];

enum eAFSEL
{
    AFSEL0_8,
    AFSEL1_9 = 4,
    AFSEL2_10 = 8,
    AFSEL3_11 = 12,
    AFSEL4_12 = 16,
    AFSEL5_13 = 20,
    AFSEL6_14 = 24,
    AFSEL7_15 = 28,
};

typedef struct
{
    // volatile AFSEL_t *AFSEL;  // 32 bits, 4 bytes
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} GPIO_AFR_t;

extern GPIO_AFR_t GPIO_AFR[PORT_END * 2];

enum eAHB2
{
    GPIOAEN,
    GPIOBEN,
    GPIOCEN,
    GPIODEN,
    GPIOEEN,
    GPIOFEN,
    GPIOGEN,
    GPIOHEN,
    GPIOIEN,
    OTGFSEN = 12,
    ADCEN = 13,
    DCMIEN = 14,
    AESEN = 16,
    HASHEN = 17,
    RNGEN = 18,
};
typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} RCC_AHB2ENR_t;

extern RCC_AHB2ENR_t RCC_AHB2ENR;

enum eAPB1
{
    TIM2EN,
    TIM3EN,
    TIM4EN,
    TIM5EN,
    TIM6EN,
    TIM7EN,
    LCDEN = 9,
    RTCAPBEN = 10,
    WWDGEN = 11,
    SPI2EN = 14,
    SPI3EN = 15,
    USART2EN = 17,
    USART3EN = 18,
    USART4EN = 19,
    USART5EN = 20,
    I2C1EN = 21,
    I2C2EN = 22,
    I2C3EN = 23,
    CRSEN = 24,
    CAN1EN = 25,
    CAN2EN = 26,
    PWREN = 28,
    DAC1EN = 29,
    OPAMPEN = 30,
    LPTIM1EN = 31,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} RCC_APB1ENR1_t;

extern RCC_APB1ENR1_t RCC_APB1ENR1;

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} USART_BRR_t;

extern USART_BRR_t USART_BRR[PORT_END];

enum eUSART_CR1
{
    UE,
    UESM,
    RE,
    TE,
    IDLEIE,
    RXNEIE,
    TCIE,
    TXEIE,
    PEIE,
    PS,
    PCE,
    WAKE,
    M0,
    MME,
    CMIE,
    OVER8,
    DEDT,
    DEAT,
    RTOIE,
    EOBIE,
    M1,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} USART_CR1_t;

extern USART_CR1_t USART_CR1[PORT_END];

enum eUSART_CR3
{
    EIE,
    IREN,
    IRLP,
    HDSEL,
    NACK_U,
    SCEN,
    DMAR,
    DMAT,
    RTSE,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} USART_CR3_t;

extern USART_CR3_t USART_CR3[PORT_END];

enum eUSART_ISR
{
    PE,
    FE,
    NF,
    ORE,
    IDLE,
    RXNE,
    TC,
    TXE,
    LBDF,
    CTSIF,
    CTS,
    RTOF,
    EOBF,
    ABRE,
    ABRF,
    BUSY,
    CMF,
    SBKF,
    RWU,
    WUF,
    TEACK,
    REACK,
    TCBGT,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} USART_ISR_t;
extern USART_ISR_t USART_ISR[PORT_END];

typedef struct
{
    uint16_t TDR : 16;
} USART_TDR_reg_t;

typedef union
{
    volatile USART_TDR_reg_t *U_TDR;
    volatile uint16_t *bytes;
} USART_TDR_t;
extern USART_TDR_t USART_TDR[PORT_END];

typedef struct
{
    uint16_t RDR : 16;
} USART_RDR_reg_t;

typedef union
{
    volatile USART_RDR_reg_t *U_RDR;
    volatile uint16_t *bytes;
} USART_RDR_t;
extern USART_RDR_t USART_RDR[PORT_END];

typedef union
{
    volatile uint32_t *I_TIMINGR;
} I2C_TIMINGR_t;
extern I2C_TIMINGR_t I2C_TIMINGR[PORT_END];

typedef union
{
    volatile uint32_t *TXDATA;
} I2C_TXDR_t;
extern I2C_TXDR_t I2C_TXDR[PORT_END];
typedef union
{
    volatile uint32_t *RXDATA;
} I2C_RXDR_t;
extern I2C_RXDR_t I2C_RXDR[PORT_END];

enum eI2C_CR1
{
    PE_I,
    TXIE,
    RXIE,
    ADDRIE,
    NACKIE,
    STOPIE,
    TCIE_I,
    ERRIE,
    DNF,
    ANFOFF = 12,
    TXDMAEN = 14,
    RXDMAEN = 15,
    SBC = 16,
    NOSTRETCH = 17,
    WUPEN = 18,
    GCEN = 19,
    SMBHEN = 20,
    SMBDEN = 21,
    ALERTEN = 22,
    PECEN = 23,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} I2C_CR1_t;
extern I2C_CR1_t I2C_CR1[PORT_END];

enum eI2C_CR2
{
    SADD07,
    SADD89 = 8,
    RD_WRN = 10,
    ADD10 = 11,
    HEAD10R = 12,
    START = 13,
    STOP = 14,
    NACK = 15,
    NBYTES = 16,
    RELOAD = 24,
    AUTOEND,
    PECBYTE,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} I2C_CR2_t;
extern I2C_CR2_t I2C_CR2[PORT_END];

enum eI2C_ISR
{
    TXE_I,
    TXIS,
    RXNE_I,
    ADDR,
    NACKF,
    STOPF,
    TC_I,
    TCR,
    BERR,
    ARLO,
    OVR,
    PECERR,
    TIMEOUT,
    ALERT,
    BUSY_I = 15,
    DIR,
    ADDCODE = 17,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} I2C_ISR_t;
extern I2C_ISR_t I2C_ISR[PORT_END];

enum eGPIO_OTYPER
{
    OT0,
    OT1,
    OT2,
    OT3,
    OT4,
    OT5,
    OT6,
    OT7,
    OT8,
    OT9,
    OT10,
    OT11,
    OT12,
    OT13,
    OT14,
    OT15,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} GPIO_OTYPER_t;
extern GPIO_OTYPER_t GPIO_OTYPER[PORT_END];

enum eDMA1_Channel_CCR
{
    EN_DMA,
    TCIE_DMA,
    HTIE_DMA,
    TEIE_DMA,
    DIR_DMA,
    CIRC_DMA,
    PINC_DMA,
    MINC_DMA,
    PSIZE = 8,
    MSIZE = 10,
    PL = 12,
    MEM2MEM_DMA = 14,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} DMA1_Channel_CCR_t;
extern DMA1_Channel_CCR_t DMA1_Channel_CCR[6];

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} DMA1_Channel_CPAR_t;
extern DMA1_Channel_CPAR_t DMA1_Channel_CPAR[6];

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} DMA1_Channel_CMAR_t;
extern DMA1_Channel_CMAR_t DMA1_Channel_CMAR[6];

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} DMA1_Channel_CNDTR_t;
extern DMA1_Channel_CNDTR_t DMA1_Channel_CNDTR[6];

enum eDMA1_Channel_CSELR
{
    C5S = 16,
    C6S = 20,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} DMA1_Channel_CSELR_t;
extern DMA1_Channel_CSELR_t DMA1_Channel_CSELR;

enum eDMA_IFCR
{
    CTCIF2 = 5,
    CTEIF2 = 7,
    CTCIF5 = 17,
    CTCIF6 = 21,
    CTEIF6 = 23,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} DMA_IFCR_t;
extern DMA_IFCR_t DMA_IFCR;

enum eRCC_APB2ENR
{
    TIM_1EN = 11,
    USART_1EN = 14,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} RCC_APB2ENR_t;
extern RCC_APB2ENR_t RCC_APB2ENR;

enum eRCC_AHB1ENR
{
    DMA_1EN = 0,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} RCC_AHB1ENR_t;
extern RCC_AHB1ENR_t RCC_AHB1ENR;

enum eDMA_ISR
{
    TCIF2 = 5,
    TEIF2 = 7,
    TCIF5 = 17,
    TCIF6 = 21,
    TEIF6 = 23,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
} DMA_ISR_t;
extern DMA_ISR_t DMA_ISR;

enum eTIM_CR1
{
    CEN = 0,
    ARPE = 7,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_CR1_t;
extern TIM_CR1_t TIM_CR1[3];


enum eTIM_CCR1
{
    CCR1_015
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_CCR1_t;
extern TIM_CCR1_t TIM_CCR1[3];

enum eTIM_CCR2
{
    CCR2_015
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_CCR2_t;
extern TIM_CCR2_t TIM_CCR2[3];

enum eTIM_EGR
{
    UG = 0,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_EGR_t;
extern TIM_EGR_t TIM_EGR[3];

enum eTIM_PSC
{
    PSC015 = 0,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_PSC_t;
extern TIM_PSC_t TIM_PSC[3];

enum eTIM_ARR
{
    ARR015 = 0,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_ARR_t;
extern TIM_ARR_t TIM_ARR[3];

enum eTIM_CCER
{
    CC1E = 0,
    CC2E = 4,
    CC3E = 8,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_CCER_t;
extern TIM_CCER_t TIM_CCER[3];

enum eTIM_BDTR
{
    MOE = 15,
};

typedef struct
{
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_BDTR_t;
extern TIM_BDTR_t TIM_BDTR[1];



enum eTIM_CCMR1
{
    CC1S ,
    OC1FE,
    OC1PE,
    OC1M ,
    OC1CE,
    CC2S ,
    OC2FE,
    OC2PE,
    OC2M ,
    OC2CE,
    OC1M3,
    OC2M3 ,
};

//CCMR1 reg for input mode
#define IC1F 3
#define CC2S_in 4
#define IC2F 6

typedef struct
{
    unsigned char CC1S : 2;
    unsigned char OC1FE : 1;
    unsigned char OC1PE : 1;
    unsigned char OC1M : 3;
    unsigned char OC1CE : 1;
    unsigned char CC2S : 2;
    unsigned char OC2FE : 1;
    unsigned char OC2PE : 1;
    unsigned char OC2M : 3;
    unsigned char OC2CE : 1;
    unsigned char OC1M3 : 1;
    unsigned char RSVD1 : 7;
    unsigned char OC2M3 : 1;
    unsigned char RSVD2 : 7;
} TIM_CCMR1_reg_t;

typedef union
{
    volatile TIM_CCMR1_reg_t *CCMR1;    // 32 bits, 4 bytes
    volatile uint32_t *bytes; // 32 bits, 4 bytes
}TIM_CCMR1_t;
extern TIM_CCMR1_t TIM_CCMR1[3];

#endif