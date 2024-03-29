/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,2011 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

/**
 * @file    test.h
 * @brief   Tests support header.
 *
 * @addtogroup test
 * @{
 */

#ifndef _TEST_H_
#define _TEST_H_

/**
 * @brief   Delay inserted between test cases.
 */
#if !defined(DELAY_BETWEEN_TESTS) || defined(__DOXYGEN__)
#define DELAY_BETWEEN_TESTS     200
#endif

/**
 * @brief   If @p TRUE then benchmarks are not included.
 */
#if !defined(TEST_NO_BENCHMARKS) || defined(__DOXYGEN__)
#define TEST_NO_BENCHMARKS      FALSE
#endif

#define MAX_THREADS             5
#define MAX_TOKENS              16

#if defined(CH_ARCHITECTURE_AVR) || defined(CH_ARCHITECTURE_MSP430)
#define THREADS_STACK_SIZE      48
#elif defined(CH_ARCHITECTURE_STM8)
#define THREADS_STACK_SIZE      64
#elif defined(CH_ARCHITECTURE_SIMIA32)
#define THREADS_STACK_SIZE      512
#else
#define THREADS_STACK_SIZE      128
#endif
#define WA_SIZE THD_WA_SIZE(THREADS_STACK_SIZE)

/**
 * @brief   Structure representing a test case.
 */
struct testcase {
  const char *name;             /**< @brief Test case name.                 */
  void (*setup)(void);          /**< @brief Test case preparation function. */
  void (*teardown)(void);       /**< @brief Test case clean up function.    */
  void (*execute)(void);        /**< @brief Test case execution function.   */
};

#ifndef __DOXYGEN__
union test_buffers {
  struct {
    WORKING_AREA(T0, THREADS_STACK_SIZE);
    WORKING_AREA(T1, THREADS_STACK_SIZE);
    WORKING_AREA(T2, THREADS_STACK_SIZE);
    WORKING_AREA(T3, THREADS_STACK_SIZE);
    WORKING_AREA(T4, THREADS_STACK_SIZE);
  } wa;
  uint8_t buffer[WA_SIZE * 5];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif
  msg_t TestThread(void *p);
  void test_printn(uint32_t n);
  void test_print(const char *msgp);
  void test_println(const char *msgp);
  void test_emit_token(char token);
  bool_t _test_fail(unsigned point);
  bool_t _test_assert(unsigned point, bool_t condition);
  bool_t _test_assert_sequence(unsigned point, char *expected);
  bool_t _test_assert_time_window(unsigned point, systime_t start, systime_t end);
  void test_terminate_threads(void);
  void test_wait_threads(void);
  systime_t test_wait_tick(void);
  void test_start_timer(unsigned ms);
#if CH_DBG_THREADS_PROFILING
  void test_cpu_pulse(unsigned duration);
#endif
#if defined(WIN32)
  void ChkIntSources(void);
#endif
#ifdef __cplusplus
}
#endif

/**
 * @brief   Test failure enforcement.
 */
#define test_fail(point) {                                                  \
  _test_fail(point);                                                        \
  return;                                                                   \
}

/**
 * @brief   Test assertion.
 *
 * @param[in] point     numeric assertion identifier
 * @param[in] condition a boolean expression that must be verified to be true
 * @param[in] msg       failure message
 */
#define test_assert(point, condition, msg) {                                \
  if (_test_assert(point, condition))                                       \
    return;                                                                 \
}

/**
 * @brief   Test sequence assertion.
 *
 * @param[in] point     numeric assertion identifier
 * @param[in] expected  string to be matched with the tokens buffer
 */
#define test_assert_sequence(point, expected) {                             \
  if (_test_assert_sequence(point, expected))                               \
    return;                                                                 \
}

/**
 * @brief   Test time window assertion.
 *
 * @param[in] point     numeric assertion identifier
 * @param[in] start     initial time in the window (included)
 * @param[in] end       final time in the window (not included)
 */
#define test_assert_time_window(point, start, end) {                        \
  if (_test_assert_time_window(point, start, end))                          \
    return;                                                                 \
}

#if !defined(__DOXYGEN__)
extern Thread *threads[MAX_THREADS];
extern union test_buffers test;
extern void * ROMCONST wa[];
extern bool_t test_timer_done;
#endif

#endif /* _TEST_H_ */

/** @} */
