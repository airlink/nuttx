/************************************************************************************
 * configs/ekk-lm3s9b96/include/board.h
 * include/arch/board/board.h
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Authors: Gregory Nutt <gnutt@nuttx.org>
 *            Jose Pablo Rojas V. <jrojas@nx-engineering.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __ARCH_BOARD_BOARD_H
#define __ARCH_BOARD_BOARD_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

/************************************************************************************
 * Definitions
 ************************************************************************************/

/* Clocking *************************************************************************/

/* RCC settings */

#define SYSCON_RCC_XTAL      SYSCON_RCC_XTAL16000KHZ /* 16.000 MHz crystal */
#define XTAL_FREQUENCY       16000000

/* Oscillator source is the main oscillator (not internal, internal/4, 30KHz or
 * 30KHz from hibernate module) */

#define SYSCON_RCC_OSCSRC    SYSCON_RCC_OSCSRC_MOSC
#define SYSCON_RCC2_OSCSRC   SYSCON_RCC2_OSCSRC2_MOSC
#define OSCSRC_FREQUENCY     XTAL_FREQUENCY

/* Use system divider = 4; this corresponds to a system clock frequency
 * of (400 / 2) / 4 = 50MHz
 */

#define LM3S_SYSDIV          4
#define SYSCLK_FREQUENCY     50000000  /* 50MHz */

/* Other RCC settings:
 *
 * - Main and internal oscillators enabled.
 * - PLL and sys dividers not bypassed
 * - PLL not powered down
 * - No auto-clock gating reset
 */

#define LM3S_RCC_VALUE (SYSCON_RCC_OSCSRC | SYSCON_RCC_XTAL | SYSCON_RCC_USESYSDIV | SYSCON_RCC_SYSDIV(LM3S_SYSDIV))

/* RCC2 settings -- RCC2 not used.  Other RCC2 settings
 *
 * - PLL and sys dividers not bypassed.
 * - PLL not powered down
 * - Not using RCC2
 */

#define LM3S_RCC2_VALUE (SYSCON_RCC2_OSCSRC | SYSCON_RCC2_SYSDIV(LM3S_SYSDIV))

/* LED definitions ******************************************************************/

/* The EKK-LMS39B96 Eval Kit has only one user LED: Port D, Bit 0.  Below is the mapping of this
 * single LED.  From this single LED, we can get the following information:
 *
 *   OFF Steady:    The system has failed to boot to the point of enabling interrupts
 *   ON Steady:     The systems has enabled interrupts, but none have been received
 *   Dull glow:     The system is taking interrupts
 *   Slow blinking: The system has panicked
 */
                                /* ON   OFF */
#define LED_STARTED       0     /* OFF  OFF */
#define LED_HEAPALLOCATE  1     /* OFF  OFF */
#define LED_IRQSENABLED   2     /* ON   ON */
#define LED_STACKCREATED  3     /* ON   ON */
#define LED_INIRQ         4     /* ON   OFF */
#define LED_SIGNAL        5     /* ON   OFF */
#define LED_ASSERTION     6     /* ON   OFF */
#define LED_PANIC         7     /* ON   OFF */

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Name: lm3s_boardinitialize
 *
 * Description:
 *   All LM3S architectures must provide the following entry point.  This entry point
 *   is called early in the intitialization -- after all memory has been configured
 *   and mapped but before any devices have been initialized.
 *
 ************************************************************************************/

extern void lm3s_boardinitialize(void);

/************************************************************************************
 * Name: lm3s_ethernetmac
 *
 * Description:
 *   For the Ethernet Eval Kits, the MAC address will be stored in the non-volatile
 *   USER0 and USER1 registers.  If CONFIG_LM3S_BOARDMAC is defined, this function
 *   will obtain the MAC address from these registers.
 *
 ************************************************************************************/

#ifdef CONFIG_LM3S_BOARDMAC
struct ether_addr;
extern void lm3s_ethernetmac(struct ether_addr *ethaddr);
#endif

#endif /* __ASSEMBLY__ */
#endif  /* __ARCH_BOARD_BOARD_H */
