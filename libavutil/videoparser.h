/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * Frame statistics shared between the videoparser decoders and VideoParser.
 */

#ifndef AVUTIL_VIDEOPARSER_H
#define AVUTIL_VIDEOPARSER_H

#include <stdint.h>

/**
 * @brief Shared frame information to extract from ffmpeg into the parser.
 * This is a struct that is shared between the parser and the ffmpeg library.
 * Some fields are staying inside this struct, others will be copied into the
 * parser.
 */
typedef struct SharedFrameInfo {
  int frame_idx; /**< Index of the frame in the video stream, just a dummy
                  * value, unused
                  */

  // INTERNAL -- stays in the struct
  // temporary QP values
  uint32_t qp_sum;        /**< Sum of QP values */
  uint32_t qp_sum_sqr;    /**< Sum of squared QP values */
  uint32_t qp_cnt;        /**< Count of QP values */
  uint32_t qp_sum_bb;     /**< Sum of QP values without black border */
  uint32_t qp_sum_sqr_bb; /**< Sum of squared QP values without black border */
  uint32_t qp_cnt_bb;     /**< Count of QP values without black border */

  // Temporary MV values
  double mv_length;      /**< Motion Vector (MV) length, overall */
  double mv_sum_sqr;     /**< Sum of squared MV lengths */
  double mv_x_length;    /**< MV length in the X direction */
  double mv_y_length;    /**< MV length in the Y direction */
  double mv_x_sum_sqr;   /**< Sum of squared MV lengths in the X direction */
  double mv_y_sum_sqr;   /**< Sum of squared MV lengths in the Y direction */
  double mv_length_diff; /** < Difference in MV length */

  double mv_diff_sum;     /**< Sum of MV differences */
  double mv_diff_sum_sqr; /**< Sum of squared MV differences */

  // EXTERNAL -- shared with videoparser
  // derived QP values
  uint32_t qp_min;  /**< Minimum QP value encountered in this frame */
  uint32_t qp_max;  /**< Maximum QP value encountered in this frame */
  uint32_t qp_init; /**< QP Value the frame is starting with (to be found in the
                       slice- or frame-header) */
  double qp_avg;    /**< Average QP of the whole frame */
  double qp_stdev;  /**< Standard deviation of Av_QP */
  double qp_bb_avg; /**< Average QP without the black border */
  double qp_bb_stdev; /**< Standard deviation of the average QP */

  // Derived MV values
  double motion_avg;   /**< Average length (sqrt(xx + yy)) of the vectors in the
                         motion field */
  double motion_stdev; /**< Standard Deviation of Av_Motion */
  double motion_x_avg; /**< Average of abs(MotX) */
  double motion_y_avg; /**< Average of abs(MotY) */
  double motion_x_stdev;    /**< Standard deviation of Av_MotionX */
  double motion_y_stdev;    /**< Standard deviation of Av_MotionY */
  double motion_diff_avg;   /**< Difference of the motion with its prediction */
  double motion_diff_stdev; /**< Standard deviation of Av_MotionDif */
  int current_poc;          /**< Picture Order Count of the current frame */
  int poc_diff;             /**< Difference to the previous frame's POC */
  uint32_t motion_bit_count; /**< The number of bits used for coding motion */
  uint32_t coefs_bit_count;  /**< The number of bits used for coding coeffs */
  ;
  int mb_mv_count;    /**< Number of macroblocks with MVs */
  int mv_coded_count; /**< Number of coded MVs */

  // VP9 hidden frame handling (legacy mode only)
  int is_hidden;      /**< VP9: frame is invisible/hidden (altref) */
  int is_short_frame; /**< VP9: frame is show_existing_frame (pkt_size < 100) */
  int frame_distance; /**< VP9: distance from last invisible frame */
  int64_t pts;        /**< Presentation timestamp for FrmDist calculation */
} SharedFrameInfo;

#endif /* AVUTIL_VIDEOPARSER_H */
