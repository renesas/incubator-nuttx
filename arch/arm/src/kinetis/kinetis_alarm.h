/****************************************************************************
 * arch/arm/src/kinetis/kinetis_alarm.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_KINETIS_KINETIS_ALARM_H
#define __ARCH_ARM_SRC_KINETIS_KINETIS_ALARM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include "chip.h"

#ifdef CONFIG_RTC_ALARM

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* The form of an alarm callback */

typedef void (*alarmcb_t)(void);

/* These features are in KinetisK 1st generation
 * Time Alarm Interrupt
 * Time Overflow Interrupt
 * Time Seconds Interrupt
 *
 * For KinetisK 2nd Generation devices
 * 64bit Monotonic  register.
 */

enum alm_id_e
{
  /* Used for indexing - must be sequential */

  RTC_ALARMA = 0,    /* RTC ALARM A */
  RTC_ALARMM,        /* FUT: RTC Monotonic */
  RTC_ALARM_LAST
};

/* Structure used to pass parameters to set an alarm */

struct alm_setalarm_s
{
  int as_id;         /* enum alm_id_e */
  struct tm as_time; /* Alarm expiration time */
  alarmcb_t as_cb;   /* Callback (if non-NULL) */
  void *as_arg;      /* Argument for callback */
};

/****************************************************************************
 * Public Functions Prototypes
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: kinetis_rtc_setalarm
 *
 * Description:
 *   Set up an alarm.
 *
 * Input Parameters:
 *   tp - the time to set the alarm
 *   callback - the function to call when the alarm expires.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

int kinetis_rtc_setalarm(const struct timespec *tp, alarmcb_t callback);

/****************************************************************************
 * Name: kinetis_rtc_rdalarm
 *
 * Description:
 *   Query an alarm configured in hardware.
 *
 * Input Parameters:
 *  tp - Location to return the timer match register.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

int kinetis_rtc_rdalarm(struct timespec *tp);

/****************************************************************************
 * Name: kinetis_rtc_cancelalarm
 *
 * Description:
 *   Cancel a pending alarm alarm
 *
 * Input Parameters:
 *   none
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno on failure
 *
 ****************************************************************************/

int kinetis_rtc_cancelalarm(void);

/****************************************************************************
 * Name: kinetis_rtc_lowerhalf
 *
 * Description:
 *   Instantiate the RTC lower half driver for the Kinetis.  General usage:
 *
 *     #include <nuttx/timers/rtc.h>
 *     #include "kinetis_rtc.h>
 *
 *     struct rtc_lowerhalf_s *lower;
 *     lower = kinetis_rtc_lowerhalf();
 *     rtc_initialize(0, lower);
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   On success, a non-NULL RTC lower interface is returned.
 *   NULL is returned on any failure.
 *
 ****************************************************************************/

struct rtc_lowerhalf_s *kinetis_rtc_lowerhalf(void);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* CONFIG_RTC_ALARM */
#endif /* __ARCH_ARM_SRC_KINETIS_KINETIS_ALARM_H */
