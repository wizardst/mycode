/*
 * $QNXLicenseC:
 * Copyright 2015, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include "camera_lib.h"

#include <screen/screen.h>
#include <vcapture/capture.h>
static void* CameraRun(void* arg);
static volatile int aborted = 1;



int CameraOn(void)
{
	int rc;
	printf("Camera On!\n");
	aborted = 1;
	rc = pthread_create(NULL, NULL, CameraRun, NULL);
	if (rc) {
		perror("pthread_create failed");
		goto fail;
	}

	return 0;

fail:
	return -1;
}

void CameraOff(void)
{
	printf("Camera Off!\n");
	aborted = 0;
}

static void* CameraRun(void* arg)
{
	const char* idstr = "vcapture-demo";
	screen_context_t screen_ctx = NULL;
	screen_window_t screen_win = NULL;
	screen_display_t* screen_disp;
	int screen_ndisplays;
	const char* display = NULL;
	int screen_val;

	screen_buffer_t* screen_buf = NULL;
	void** pointers = NULL;

	int device = 0;
	int source = 0;

	int sfsize[2] = { -1, -1 };
	int bsize[2] = { -1, -1 };
	int size[2] = { -1, -1 };
	int pos[2] = { 0, 0 };
	int pos_set=0;
	int fs_set=0;
	int flip_set=0;
	int mirror_set=0;
	int rotation_set=0;
	float scale=1.0f;
	int format = SCREEN_FORMAT_UYVY;
	int nbufs = 10;
	const char* tok;
	int rval = EXIT_FAILURE;
	int i, rc, val;
	capture_context_t context = NULL;

	int n_pointers = -1;
	int buf_idx, prev_buf_idx = -1;
	int stride = -1;
	int dst_bpp = -1;
	int deinterlace_mode = CAPTURE_DEINTERLACE_WEAVE_MODE;
	int deinterlace_flags = 0;
	int zorder = 0;
	char* norm="";

	sfsize[0] = 720;
	sfsize[1] = 480;
	deinterlace_flags |= CAPTURE_DEI_WEAVE_FLAG_BOTTOM_TOP;
	norm = CAPTURE_NORM_NTSC_M_J;
	bsize[0] = sfsize[0];
	bsize[1] = sfsize[1];
	size[0] = sfsize[0];
	size[1] = sfsize[1];
    
	device = 0; 
	source = 1;   
	display = "2";	


	if ((screen_buf = calloc(nbufs, sizeof(screen_buffer_t))) == NULL ||
		(pointers = calloc(nbufs, sizeof(void*))) == NULL) {
		perror("calloc");
		goto fail;
	}

	if (bsize[0] == -1 || bsize[1] == -1) {
		fprintf(stderr, "error: you have to specify video standard (-std option)!\n");
		goto fail;
	}

	rc = screen_create_context(&screen_ctx, 0);
	if (rc) {
		perror("screen_context_create");
	}

	rc = screen_create_window(&screen_win, screen_ctx);
	if (rc) {
		perror("screen_create_window");
		goto fail;
	}

	if (display) {
		rc = screen_get_context_property_iv(screen_ctx, SCREEN_PROPERTY_DISPLAY_COUNT, &screen_ndisplays);
		if (rc) {
			perror("screen_get_context_property_iv(SCREEN_PROPERTY_DISPLAY_COUNT)");
			goto fail;
		}

		screen_disp = calloc(screen_ndisplays, sizeof(*screen_disp));
		if (screen_disp == NULL) {
			fprintf(stderr, "could not allocate memory for display list\n");
			goto fail;
		}

		rc = screen_get_context_property_pv(screen_ctx, SCREEN_PROPERTY_DISPLAYS,
			(void**)screen_disp);
		if (rc) {
			perror("screen_get_context_property_ptr(SCREEN_PROPERTY_DISPLAYS)");
			free(screen_disp);
			goto fail;
		}

		if (isdigit(*display)) {
			int want_id = atoi(display);
			for (i = 0; i < screen_ndisplays; ++i) {
				int actual_id = 0;  // invalid
				screen_get_display_property_iv(screen_disp[i], SCREEN_PROPERTY_ID, &actual_id);
				if (want_id == actual_id) {
					break;
				}
			}
		} else {
			int type = -1;
			if (strcmp(display, "internal") == 0) {
				type = SCREEN_DISPLAY_TYPE_INTERNAL;
			} else if (strcmp(display, "composite") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPOSITE;
			} else if (strcmp(display, "svideo") == 0) {
				type = SCREEN_DISPLAY_TYPE_SVIDEO;
			} else if (strcmp(display, "YPbPr") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPONENT_YPbPr;
			} else if (strcmp(display, "rgb") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPONENT_RGB;
			} else if (strcmp(display, "rgbhv") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPONENT_RGBHV;
			} else if (strcmp(display, "dvi") == 0) {
				type = SCREEN_DISPLAY_TYPE_DVI;
			} else if (strcmp(display, "hdmi") == 0) {
				type = SCREEN_DISPLAY_TYPE_HDMI;
			} else if (strcmp(display, "other") == 0) {
				type = SCREEN_DISPLAY_TYPE_OTHER;
			} else {
				fprintf(stderr, "unknown display type %s\n", display);
				free(screen_disp);
				goto fail;
			}
			for (i = 0; i < screen_ndisplays; i++) {
				screen_get_display_property_iv(screen_disp[i], SCREEN_PROPERTY_TYPE, &screen_val);
				if (screen_val == type) {
					break;
				}
			}
		}
		if (i >= screen_ndisplays) {
			fprintf(stderr, "couldn't find display %s\n", display);
			free(screen_disp);
			goto fail;
		}

		rc = screen_set_window_property_pv(screen_win, SCREEN_PROPERTY_DISPLAY, (void**)&screen_disp[i]);
		if (rc) {
			perror("screen_set_window_property_ptr(SCREEN_PROPERTY_DISPLAY)");
			free(screen_disp);
			goto fail;
		}

		free(screen_disp);
	}

	val = SCREEN_USAGE_WRITE | SCREEN_USAGE_CAPTURE | SCREEN_USAGE_ROTATION;
	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_USAGE, &val);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_USAGE)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_FORMAT, &format);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_FLIP, &flip_set);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_FLIP)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_MIRROR, &mirror_set);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_MIRROR)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_ROTATION, &rotation_set);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_ROTATION)");
		goto fail;
	}

	if (fs_set) {
		rc = screen_get_window_property_iv(screen_win, SCREEN_PROPERTY_SIZE, size);
		if (rc) {
			perror("screen_get_window_property_iv(SCREEN_PROPERTY_SIZE)");
			goto fail;
		}
	} else {
		size[0]*=scale;
		size[1]*=scale;

		switch (rotation_set) {
			int temp;

			case 90:
			case 270:
				 temp=size[0];
				 size[0]=size[1];
				 size[1]=temp;
				 break;
		}

		if (pos_set) {
			rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_POSITION, pos);
			if (rc) {
				perror("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION)");
				goto fail;
			}
		} else {
			int fssize[2];

			rc = screen_get_window_property_iv(screen_win, SCREEN_PROPERTY_SIZE, fssize);
			if (rc) {
				perror("screen_get_window_property_iv(SCREEN_PROPERTY_SIZE)");
				goto fail;
			}
			pos[0]=(fssize[0]-size[0])/2;
			pos[1]=(fssize[1]-size[1])/2;
			rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_POSITION, pos);
			if (rc) {
				perror("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION)");
				goto fail;
			}
		}
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_SIZE, size);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_SIZE)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_BUFFER_SIZE, bsize);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE)");
		goto fail;
	}

	if (zorder) {
		rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_ZORDER, &zorder);
		if (rc) {
			perror("screen_set_window_property_iv(SCREEN_PROPERTY_ZORDER)");
			goto fail;
		}
	}

	rc = screen_set_window_property_cv(screen_win, SCREEN_PROPERTY_ID_STRING, strlen(idstr), idstr);
	if (rc) {
		perror("screen_set_window_property_cv(SCREEN_PROPERTY_ID_STRING)");
		goto fail;
	}

	rc = screen_create_window_buffers(screen_win, nbufs);
	if (rc) {
		perror("screen_create_window_buffers");
	goto fail;
	}

	rc = screen_get_window_property_iv(screen_win, SCREEN_PROPERTY_RENDER_BUFFER_COUNT, &n_pointers);
	if (rc) {
		perror("screen_get_window_property_iv(SCREEN_PROPERTY_RENDER_BUFFER_COUNT)");
		goto fail;
	}

	rc = screen_get_window_property_pv(screen_win, SCREEN_PROPERTY_RENDER_BUFFERS, (void**)screen_buf);
	if (rc) {
		perror("screen_get_window_property_pv(SCREEN_PROPERTY_RENDER_BUFFERS)");
		goto fail;
	}

	for (i = 0; i < n_pointers; i++) {
		/* obtain the pointer of the buffers, for the capture use */
		rc = screen_get_buffer_property_pv(screen_buf[i], SCREEN_PROPERTY_POINTER, &(pointers[i]));
		if (rc) {
			perror("screen_get_window_property_pv(SCREEN_PROPERTY_POINTER)");
			goto fail;
		}
	}

	rc = screen_get_buffer_property_iv(screen_buf[0], SCREEN_PROPERTY_STRIDE, &stride);
	if (rc) {
		perror("screen_get_buffer_property_iv(SCREEN_PROPERTY_STRIDE)");
		goto fail;
	}

	/* Connect to a capture device */
	context = capture_create_context(0);
	if (!context) {
		perror("capture_create_context failed");
		goto fail;
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_DEVICE, device);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_DEVICE)");
		goto fail;
	}

    /* [CX] debug */
    {
        const char *info = NULL;
        capture_get_property_p( context, CAPTURE_PROPERTY_DEVICE_INFO, &info );
        printf( "capture device-info = '%s'\n", info );
    }

	if (source >= 0) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_SRC_INDEX, source);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_SRC_INDEX)");
			goto fail;
		}
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_DEINTERLACE_MODE)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DEINTERLACE_MODE, deinterlace_mode);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DEINTERLACE_MODE)");
			goto fail;
		}
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_DEINTERLACE_FLAGS)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DEINTERLACE_FLAGS, deinterlace_flags);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DEINTERLACE_FLAGS)");
			goto fail;
		}
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_FRAME_NBUFFERS, n_pointers);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_FRAME_NBUFFERS)");
	goto fail;
	}

	rc = capture_set_property_p(context, CAPTURE_PROPERTY_FRAME_BUFFERS, pointers);
	if (rc) {
		perror("capture_set_property_p(CAPTURE_PROPERTY_FRAME_BUFFERS)");
		goto fail;
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_STRIDE, stride);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_DST_STRIDE)");
		goto fail;
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_FORMAT, format);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_DST_FORMAT)");
		goto fail;
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_SRC_WIDTH) &&
		capture_is_property(context, CAPTURE_PROPERTY_SRC_HEIGHT) &&
		(sfsize[0] != -1) && (sfsize[1] != -1)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_SRC_WIDTH, sfsize[0]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_SRC_WIDTH)");
			goto fail;
		 }
		 rc = capture_set_property_i(context, CAPTURE_PROPERTY_SRC_HEIGHT, sfsize[1]);
		 if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_SRC_HEIGHT)");
			goto fail;
		 }
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_CROP_WIDTH) &&
		capture_is_property(context, CAPTURE_PROPERTY_CROP_HEIGHT) &&
		(sfsize[0] != -1) && (sfsize[1] != -1)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_CROP_WIDTH, sfsize[0]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_CROP_WIDTH)");
		}
        rc = capture_set_property_i(context, CAPTURE_PROPERTY_CROP_HEIGHT, sfsize[1]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_CROP_HEIGHT)");
		}
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_DST_WIDTH) &&
		capture_is_property(context, CAPTURE_PROPERTY_DST_HEIGHT)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_WIDTH, sfsize[0]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DST_WIDTH)");
			goto fail;
		}
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_HEIGHT, sfsize[1]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DST_HEIGHT)");
			goto fail;
		}
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_SOURCE_SIZE, sfsize);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_SOURCE_SIZE)");
		goto fail;
	}

	if ((strlen(norm) != 0) && (capture_is_property(context, CAPTURE_PROPERTY_NORM))) {
		rc = capture_set_property_p(context, CAPTURE_PROPERTY_NORM, norm);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_NORM)");
			goto fail;
		}
	}

	/* tell the driver to start capturing (when capture_update() is called). */
	capture_set_property_i(context, CAPTURE_ENABLE, 1);

	/* commit changes to the H/W -- and start capturing... */
	if (capture_update(context, 0) == -1) {
		fprintf(stderr, "capture_update failed\n");
		goto fail;
	}

	int rect[4] = { 0, 0, sfsize[0], sfsize[1] };
	while(aborted) {
		buf_idx = capture_get_frame(context, CAPTURE_TIMEOUT_INFINITE, 0);
		if (buf_idx == -1) {
			fprintf(stderr, "capture_get_frame failed(%s)\n", strerror(errno));
			goto fail;
		}

		/* update screen */
		rc = screen_post_window(screen_win, screen_buf[buf_idx], 1, rect, 0);

		/* Make the buffer identified by the prev_buf_idx as available for capturing. */
		if (prev_buf_idx != -1) {
			capture_release_frame(context, prev_buf_idx);
		}
		prev_buf_idx = buf_idx;
	}

	rval = EXIT_SUCCESS;

fail:
	if (context != NULL) {
		capture_destroy_context(context);
	}
	if (screen_win != NULL) {
		screen_destroy_window(screen_win);
	}
	if (screen_ctx != NULL) {
		screen_destroy_context(screen_ctx);
	}

	free(screen_buf);
	free(pointers);

	pthread_exit(NULL);
	return rval;
}

void CameraRunTest(void)
{
	const char* idstr = "vcapture-demo-test";
	screen_context_t screen_ctx = NULL;
	screen_window_t screen_win = NULL;
	screen_display_t* screen_disp;
	int screen_ndisplays;
	const char* display = NULL;
	int screen_val;

	screen_buffer_t* screen_buf = NULL;
	void** pointers = NULL;

	int device = 0;
	int source = 0;

	int sfsize[2] = { -1, -1 };
	int bsize[2] = { -1, -1 };
	int size[2] = { -1, -1 };
	int pos[2] = { 0, 0 };
	int pos_set=0;
	int fs_set=0;
	int flip_set=0;
	int mirror_set=0;
	int rotation_set=0;
	float scale=1.0f;
	int format = SCREEN_FORMAT_UYVY;
	int nbufs = 10;
	const char* tok;
	int rval = EXIT_FAILURE;
	int i, rc, val;
	capture_context_t context = NULL;

	int n_pointers = -1;
	int buf_idx, prev_buf_idx = -1;
	int stride = -1;
	int dst_bpp = -1;
	int deinterlace_mode = CAPTURE_DEINTERLACE_WEAVE_MODE;
	int deinterlace_flags = 0;
	int zorder = 0;
	char* norm="";

	sfsize[0] = 720;
	sfsize[1] = 480;
	deinterlace_flags |= CAPTURE_DEI_WEAVE_FLAG_BOTTOM_TOP;
	norm = CAPTURE_NORM_NTSC_M_J;
	bsize[0] = sfsize[0];
	bsize[1] = sfsize[1];
	size[0] = sfsize[0];
	size[1] = sfsize[1];
    
	device = 0; 
	source = 1;   
	display = "2";	


	if ((screen_buf = calloc(nbufs, sizeof(screen_buffer_t))) == NULL ||
		(pointers = calloc(nbufs, sizeof(void*))) == NULL) {
		perror("calloc");
		goto fail;
	}

	if (bsize[0] == -1 || bsize[1] == -1) {
		fprintf(stderr, "error: you have to specify video standard (-std option)!\n");
		goto fail;
	}

	rc = screen_create_context(&screen_ctx, 0);
	if (rc) {
		perror("screen_context_create");
	}

	rc = screen_create_window(&screen_win, screen_ctx);
	if (rc) {
		perror("screen_create_window");
		goto fail;
	}

	if (display) {
		rc = screen_get_context_property_iv(screen_ctx, SCREEN_PROPERTY_DISPLAY_COUNT, &screen_ndisplays);
		if (rc) {
			perror("screen_get_context_property_iv(SCREEN_PROPERTY_DISPLAY_COUNT)");
			goto fail;
		}

		screen_disp = calloc(screen_ndisplays, sizeof(*screen_disp));
		if (screen_disp == NULL) {
			fprintf(stderr, "could not allocate memory for display list\n");
			goto fail;
		}

		rc = screen_get_context_property_pv(screen_ctx, SCREEN_PROPERTY_DISPLAYS,
			(void**)screen_disp);
		if (rc) {
			perror("screen_get_context_property_ptr(SCREEN_PROPERTY_DISPLAYS)");
			free(screen_disp);
			goto fail;
		}

		if (isdigit(*display)) {
			int want_id = atoi(display);
			for (i = 0; i < screen_ndisplays; ++i) {
				int actual_id = 0;  // invalid
				screen_get_display_property_iv(screen_disp[i], SCREEN_PROPERTY_ID, &actual_id);
				if (want_id == actual_id) {
					break;
				}
			}
		} else {
			int type = -1;
			if (strcmp(display, "internal") == 0) {
				type = SCREEN_DISPLAY_TYPE_INTERNAL;
			} else if (strcmp(display, "composite") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPOSITE;
			} else if (strcmp(display, "svideo") == 0) {
				type = SCREEN_DISPLAY_TYPE_SVIDEO;
			} else if (strcmp(display, "YPbPr") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPONENT_YPbPr;
			} else if (strcmp(display, "rgb") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPONENT_RGB;
			} else if (strcmp(display, "rgbhv") == 0) {
				type = SCREEN_DISPLAY_TYPE_COMPONENT_RGBHV;
			} else if (strcmp(display, "dvi") == 0) {
				type = SCREEN_DISPLAY_TYPE_DVI;
			} else if (strcmp(display, "hdmi") == 0) {
				type = SCREEN_DISPLAY_TYPE_HDMI;
			} else if (strcmp(display, "other") == 0) {
				type = SCREEN_DISPLAY_TYPE_OTHER;
			} else {
				fprintf(stderr, "unknown display type %s\n", display);
				free(screen_disp);
				goto fail;
			}
			for (i = 0; i < screen_ndisplays; i++) {
				screen_get_display_property_iv(screen_disp[i], SCREEN_PROPERTY_TYPE, &screen_val);
				if (screen_val == type) {
					break;
				}
			}
		}
		if (i >= screen_ndisplays) {
			fprintf(stderr, "couldn't find display %s\n", display);
			free(screen_disp);
			goto fail;
		}

		rc = screen_set_window_property_pv(screen_win, SCREEN_PROPERTY_DISPLAY, (void**)&screen_disp[i]);
		if (rc) {
			perror("screen_set_window_property_ptr(SCREEN_PROPERTY_DISPLAY)");
			free(screen_disp);
			goto fail;
		}

		free(screen_disp);
	}

	val = SCREEN_USAGE_WRITE | SCREEN_USAGE_CAPTURE | SCREEN_USAGE_ROTATION;
	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_USAGE, &val);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_USAGE)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_FORMAT, &format);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_FLIP, &flip_set);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_FLIP)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_MIRROR, &mirror_set);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_MIRROR)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_ROTATION, &rotation_set);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_ROTATION)");
		goto fail;
	}

	if (fs_set) {
		rc = screen_get_window_property_iv(screen_win, SCREEN_PROPERTY_SIZE, size);
		if (rc) {
			perror("screen_get_window_property_iv(SCREEN_PROPERTY_SIZE)");
			goto fail;
		}
	} else {
		size[0]*=scale;
		size[1]*=scale;

		switch (rotation_set) {
			int temp;

			case 90:
			case 270:
				 temp=size[0];
				 size[0]=size[1];
				 size[1]=temp;
				 break;
		}

		if (pos_set) {
			rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_POSITION, pos);
			if (rc) {
				perror("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION)");
				goto fail;
			}
		} else {
			int fssize[2];

			rc = screen_get_window_property_iv(screen_win, SCREEN_PROPERTY_SIZE, fssize);
			if (rc) {
				perror("screen_get_window_property_iv(SCREEN_PROPERTY_SIZE)");
				goto fail;
			}
			pos[0]=(fssize[0]-size[0])/2;
			pos[1]=(fssize[1]-size[1])/2;
			rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_POSITION, pos);
			if (rc) {
				perror("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION)");
				goto fail;
			}
		}
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_SIZE, size);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_SIZE)");
		goto fail;
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_BUFFER_SIZE, bsize);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_BUFFER_SIZE)");
		goto fail;
	}

	if (zorder) {
		rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_ZORDER, &zorder);
		if (rc) {
			perror("screen_set_window_property_iv(SCREEN_PROPERTY_ZORDER)");
			goto fail;
		}
	}

	rc = screen_set_window_property_cv(screen_win, SCREEN_PROPERTY_ID_STRING, strlen(idstr), idstr);
	if (rc) {
		perror("screen_set_window_property_cv(SCREEN_PROPERTY_ID_STRING)");
		goto fail;
	}

	rc = screen_create_window_buffers(screen_win, nbufs);
	if (rc) {
		perror("screen_create_window_buffers");
	goto fail;
	}

	rc = screen_get_window_property_iv(screen_win, SCREEN_PROPERTY_RENDER_BUFFER_COUNT, &n_pointers);
	if (rc) {
		perror("screen_get_window_property_iv(SCREEN_PROPERTY_RENDER_BUFFER_COUNT)");
		goto fail;
	}

	rc = screen_get_window_property_pv(screen_win, SCREEN_PROPERTY_RENDER_BUFFERS, (void**)screen_buf);
	if (rc) {
		perror("screen_get_window_property_pv(SCREEN_PROPERTY_RENDER_BUFFERS)");
		goto fail;
	}

	for (i = 0; i < n_pointers; i++) {
		/* obtain the pointer of the buffers, for the capture use */
		rc = screen_get_buffer_property_pv(screen_buf[i], SCREEN_PROPERTY_POINTER, &(pointers[i]));
		if (rc) {
			perror("screen_get_window_property_pv(SCREEN_PROPERTY_POINTER)");
			goto fail;
		}
	}

	rc = screen_get_buffer_property_iv(screen_buf[0], SCREEN_PROPERTY_STRIDE, &stride);
	if (rc) {
		perror("screen_get_buffer_property_iv(SCREEN_PROPERTY_STRIDE)");
		goto fail;
	}

	/* Connect to a capture device */
	context = capture_create_context(0);
	if (!context) {
		perror("capture_create_context failed");
		goto fail;
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_DEVICE, device);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_DEVICE)");
		goto fail;
	}

    /* [CX] debug */
    {
        const char *info = NULL;
        capture_get_property_p( context, CAPTURE_PROPERTY_DEVICE_INFO, &info );
        printf( "capture device-info = '%s'\n", info );
    }

	if (source >= 0) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_SRC_INDEX, source);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_SRC_INDEX)");
			goto fail;
		}
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_DEINTERLACE_MODE)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DEINTERLACE_MODE, deinterlace_mode);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DEINTERLACE_MODE)");
			goto fail;
		}
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_DEINTERLACE_FLAGS)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DEINTERLACE_FLAGS, deinterlace_flags);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DEINTERLACE_FLAGS)");
			goto fail;
		}
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_FRAME_NBUFFERS, n_pointers);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_FRAME_NBUFFERS)");
	goto fail;
	}

	rc = capture_set_property_p(context, CAPTURE_PROPERTY_FRAME_BUFFERS, pointers);
	if (rc) {
		perror("capture_set_property_p(CAPTURE_PROPERTY_FRAME_BUFFERS)");
		goto fail;
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_STRIDE, stride);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_DST_STRIDE)");
		goto fail;
	}

	rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_FORMAT, format);
	if (rc) {
		perror("capture_set_property_i(CAPTURE_PROPERTY_DST_FORMAT)");
		goto fail;
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_SRC_WIDTH) &&
		capture_is_property(context, CAPTURE_PROPERTY_SRC_HEIGHT) &&
		(sfsize[0] != -1) && (sfsize[1] != -1)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_SRC_WIDTH, sfsize[0]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_SRC_WIDTH)");
			goto fail;
		 }
		 rc = capture_set_property_i(context, CAPTURE_PROPERTY_SRC_HEIGHT, sfsize[1]);
		 if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_SRC_HEIGHT)");
			goto fail;
		 }
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_CROP_WIDTH) &&
		capture_is_property(context, CAPTURE_PROPERTY_CROP_HEIGHT) &&
		(sfsize[0] != -1) && (sfsize[1] != -1)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_CROP_WIDTH, sfsize[0]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_CROP_WIDTH)");
		}
        rc = capture_set_property_i(context, CAPTURE_PROPERTY_CROP_HEIGHT, sfsize[1]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_CROP_HEIGHT)");
		}
	}

	if (capture_is_property(context, CAPTURE_PROPERTY_DST_WIDTH) &&
		capture_is_property(context, CAPTURE_PROPERTY_DST_HEIGHT)) {
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_WIDTH, sfsize[0]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DST_WIDTH)");
			goto fail;
		}
		rc = capture_set_property_i(context, CAPTURE_PROPERTY_DST_HEIGHT, sfsize[1]);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_DST_HEIGHT)");
			goto fail;
		}
	}

	rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_SOURCE_SIZE, sfsize);
	if (rc) {
		perror("screen_set_window_property_iv(SCREEN_PROPERTY_SOURCE_SIZE)");
		goto fail;
	}

	if ((strlen(norm) != 0) && (capture_is_property(context, CAPTURE_PROPERTY_NORM))) {
		rc = capture_set_property_p(context, CAPTURE_PROPERTY_NORM, norm);
		if (rc) {
			perror("capture_set_property_i(CAPTURE_PROPERTY_NORM)");
			goto fail;
		}
	}

	/* tell the driver to start capturing (when capture_update() is called). */
	capture_set_property_i(context, CAPTURE_ENABLE, 1);

	/* commit changes to the H/W -- and start capturing... */
	if (capture_update(context, 0) == -1) {
		fprintf(stderr, "capture_update failed\n");
		goto fail;
	}

	//int rect[4] = { 0, 0, sfsize[0], sfsize[1] };
	//while(aborted) {
	//	buf_idx = capture_get_frame(context, CAPTURE_TIMEOUT_INFINITE, 0);
	//	if (buf_idx == -1) {
	//		fprintf(stderr, "capture_get_frame failed(%s)\n", strerror(errno));
	//		goto fail;
	//	}
    //
	//	/* update screen */
	//	rc = screen_post_window(screen_win, screen_buf[buf_idx], 1, rect, 0);
    //
	//	/* Make the buffer identified by the prev_buf_idx as available for capturing. */
	//	if (prev_buf_idx != -1) {
	//		capture_release_frame(context, prev_buf_idx);
	//	}
	//	prev_buf_idx = buf_idx;
	//}
	sleep(1);

fail:
	if (context != NULL) {
		capture_destroy_context(context);
	}
	if (screen_win != NULL) {
		screen_destroy_window(screen_win);
	}
	if (screen_ctx != NULL) {
		screen_destroy_context(screen_ctx);
	}

	free(screen_buf);
	free(pointers);

	//pthread_exit(NULL);
	return rval;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $Rev$")
#endif
