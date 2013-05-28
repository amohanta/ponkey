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

#define WRITELOG "/tmp/write.log"
#define WRITEUCLOG "/tmp/write.uc.log"
#define SETTERLOG "/tmp/navigator.setter.log"
#define METHODLOG "/tmp/navigator.method_calls.log"

static JSClass navigator_class;
static JSPropertySpec navigator_properties[];
enum navigator_property_id {
	navigator_appversion = -1,
};



/* Structure representing the Navigator internally */
typedef struct CMNavigator {
    char        *appVersion;
} CMNavigator;



static const char *navigator_property_str[] = {
	"appVersion"
};

static JSPropertySpec navigator_properties[] = {
	{"appVersion",	navigator_appversion,	JSPROP_ENUMERATE },
	{ 0 }
};

static JSBool navigator_setProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

  if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
        case navigator_appversion:
		fOut = fopen(SETTERLOG, "a");
 		if (fOut == NULL)
      			return JS_FALSE;
      		if (JSVAL_IS_INT(*vp)) {
        		fprintf(fOut, "navigator set property read-only %s = %d\n", navigator_property_str[JSVAL_TO_INT(id)], JSVAL_TO_INT(*vp));
      		}
      		else if (JSVAL_IS_STRING(*vp)) {
      			str = js_ValueToString(cx, *vp);
      			if (!str)
      				return JS_FALSE;
	          if (JSSTRING_IS_DEPENDENT(str)) {
				      n = JSSTRDEP_LENGTH(str);
	          	s = JSSTRDEP_CHARS(str);
      	    } else {
				      n = str->length;
      	    	s = str->chars;
         		}
         		fprintf(fOut, "navigator set property read-only %s = \"", navigator_property_str[JSVAL_TO_INT(id)]);
            if (n != 0)
            {
          	  for (i = 0; i < n; i++)
          		  fputc(s[i], fOut);
            }
         		fprintf(fOut, "\"\n");         		
      		}
      		else {
	      		fprintf(fOut, "navigator set property read-only %s to value of unknown type %x\n", navigator_property_str[JSVAL_TO_INT(id)], JSVAL_TAG(*vp));
      		}
					fclose (fOut);        	
        	break;
      }
  }
  return JS_TRUE;
}

static JSBool navigator_getProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

CMNavigator* cmNav = JS_GetInstancePrivate(cx, obj, &navigator_class, NULL);

if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
        case navigator_appversion:
		*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, cmNav->appVersion));
		break;
	default:
		*vp = JS_GetEmptyStringValue(cx);
	}
}
 return JS_TRUE;

}


static JSClass navigator_class = {
"navigator",
JSCLASS_HAS_PRIVATE,
JS_PropertyStub, JS_PropertyStub, navigator_getProperty, navigator_setProperty,
JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS
};

static JSBool navigator_javaEnabled(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC, *fLog;
  *rval = BOOLEAN_TO_JSVAL(1);
  return JS_TRUE;
}

static JSFunctionSpec navigator_methods[] = {
	{ NULL, NULL, 0, 0, 0 }
};

static JSFunctionSpec navigator_static_methods[] = {
	{ "javaEnabled", navigator_javaEnabled, 0, 0, 0 },
	{ NULL, NULL, 0, 0, 0 }
};

JSObject *
js_InitNavigatorClass(JSContext *cx, JSObject *obj) {
	
	JSObject *Navigator;

	Navigator = JS_DefineObject(cx, obj, "navigator", &navigator_class, NULL, 0);
  if (!Navigator)
  	return NULL;
  if (!JS_DefineFunctions(cx, Navigator, navigator_static_methods))
  	return NULL;
  if (!JS_DefineProperties(cx, Navigator, navigator_properties))
  	return NULL;

    CMNavigator *cmNav;

   cmNav = JS_malloc(cx, sizeof *cmNav);
  if (!cmNav)
     return NULL;
  memset(cmNav, 0 , sizeof *cmNav);

  cmNav->appVersion = JS_malloc(cx, strlen("Firefox/2"));
  cmNav->appVersion = strdup("Firefox/2");

JS_SetPrivate(cx, Navigator, cmNav);

  return Navigator;
}
