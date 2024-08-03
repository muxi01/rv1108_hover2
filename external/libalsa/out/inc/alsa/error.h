/*
 *  SALSA-Lib - Error handler
 *
 *  Copyright (c) 2007-2012 by Takashi Iwai <tiwai@suse.de>
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation; either version 2.1 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __ALSA_ERROR_H
#define __ALSA_ERROR_H

typedef void (*snd_lib_error_handler_t)(const char *file, int line, const char *function, int err, const char *fmt, ...) /* __attribute__ ((format (printf, 5, 6))) */;

__SALSA_EXPORT_FUNC
const char *snd_strerror(int errnum)
{
	if (errnum < 0)
		errnum = -errnum;
	return (const char *) strerror(errnum);
}

__SALSA_EXPORT_FUNC
int snd_lib_error_set_handler(snd_lib_error_handler_t handler)
{
	return 0;
}

#endif /* __ALSA_ERROR_H */
