/*
 * Copyright (C) 2020  Joshua Minter
 *
 * This file is part of ReplaySorcery.
 *
 * ReplaySorcery is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ReplaySorcery is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ReplaySorcery.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "../config.h"
#include "device.h"
#include "ffdev.h"

int rsKMSDeviceCreate(RSDevice *device) {
   int ret;
   AVFrame *frame = av_frame_alloc();
   if (frame == NULL) {
      return AVERROR(ENOMEM);
   }
   if ((ret = rsFFmpegDeviceCreate(device, "kmsgrab")) < 0) {
      goto error;
   }

   rsFFmpegDeviceSetOption(device, "framerate", "%i", rsConfig.videoFramerate);
   if ((ret = rsFFmpegDeviceOpen(device, NULL)) < 0) {
      goto error;
   }
   if ((ret = rsDeviceNextFrame(device, frame)) < 0) {
      goto error;
   }

   device->hwFrames = av_buffer_ref(frame->hw_frames_ctx);
   if (device->hwFrames == NULL) {
      ret = AVERROR(ENOMEM);
      goto error;
   }
   av_frame_free(&frame);

   return 0;
error:
   av_frame_free(&frame);
   rsDeviceDestroy(device);
   return ret;
}
