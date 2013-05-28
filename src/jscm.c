/*
 *
 * Copyright (C) 2007 SecureWorks, Inc.
 *
 * This program is free software subject to the terms of the GNU General Public
 * License.  You can use, copy, redistribute and/or modify the program under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version. You should have received a copy of the GNU General Public
 * License along with this program.  If not, please see
 * http://www.gnu.org/licenses/ for a copy of the GNU General Public License.
 *
 * The program is subject to a disclaimer of warranty and a limitation of
 * liability, as disclosed below.
 *
 * Disclaimer of Warranty.
 *
 * THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
 * APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
 * HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
 * IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
 * ALL NECESSARY SERVICING, REPAIR, CORRECTION OR RECOVERY FROM DATA LOSS OR
 * DATA ERRORS.
 *
 * Limitation of Liability.
 *
 * IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
 * WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
 * THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
 * GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
 * USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
 * DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
 * PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
 * EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "jsapi.h"
#include "jsstddef.h"
#include "jsstr.h"

#define WRITELOG "/tmp/unescape.log"
#define WRITEUCLOG "/tmp/unescape.uc.log"

const char js_cm_unescape_str[] = "unescape";

static JSBool cm_unescape(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut;


  const char* bytes;
	
  fOut = fopen(WRITELOG, "a");
  if (!fOut){
	  fprintf(stderr, "js: cannot open WRITE_LOG\n");
      return JS_FALSE;
	}
	str = JS_ValueToString(cx, argv[0]);
	if (!str){
		return JS_FALSE;
	}
	bytes = JS_GetStringBytes(str);
	fprintf(fOut, "unescape(\"%s\")\n", bytes);
  
	close(fOut);
	return str_unescape(cx, obj, argc, argv, rval);
}

static JSFunctionSpec cm_functions[] = {
	{js_cm_unescape_str, cm_unescape, 1, 0, 0},
	{ NULL, NULL, 0, 0, 0 }
};

JSObject *
js_InitCMClass(JSContext *cx, JSObject *obj) {
	if (!JS_DefineFunctions(cx, obj, cm_functions))
  	return NULL;

}
