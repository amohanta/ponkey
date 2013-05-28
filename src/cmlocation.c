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

#define JSLOG "/tmp/js_function.log"

static JSClass cmlocation_class;
static JSPropertySpec cmlocation_properties[];
enum cmlocation_property_id {
	cmlocation_search = -1,
};



/* Structure representing the Navigator internally */
typedef struct CMLocation {
    char        *search;
} CMLocation;



static const char *cmlocation_property_str[] = {
	"appVersion",
};

static JSPropertySpec cmlocation_properties[] = {
	{"search",	cmlocation_search,	JSPROP_ENUMERATE },
	{ 0 }
};

static JSBool cmlocation_setProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

  if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
        case cmlocation_search:
		fOut = fopen(JSLOG, "a");
 		if (fOut == NULL)
      			return JS_FALSE;
      		if (JSVAL_IS_INT(*vp)) {
        		fprintf(fOut, "LOCATION set property read-only %s = %d\n", cmlocation_property_str[JSVAL_TO_INT(id)], JSVAL_TO_INT(*vp));
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
         		fprintf(fOut, "LOCATION set property read-only %s = \"", cmlocation_property_str[JSVAL_TO_INT(id)]);
            if (n != 0)
            {
          	  for (i = 0; i < n; i++)
          		  fputc(s[i], fOut);
            }
         		fprintf(fOut, "\"\n");         		
      		}
      		else {
	      		fprintf(fOut, "LOCATION set property read-only %s to value of unknown type %x\n", cmlocation_property_str[JSVAL_TO_INT(id)], JSVAL_TAG(*vp));
      		}
					fclose (fOut);        	
        	break;
      }
  }
  return JS_TRUE;
}

static JSBool cmlocation_getProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

CMLocation* cmLoc = JS_GetInstancePrivate(cx, obj, &cmlocation_class, NULL);

if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
        case cmlocation_search:
		*vp = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, cmLoc->search));
		break;
	default:
		*vp = JS_GetEmptyStringValue(cx);
	}
}
 return JS_TRUE;

}


static JSClass cmlocation_class = {
"location",
JSCLASS_HAS_PRIVATE,
JS_PropertyStub, JS_PropertyStub, cmlocation_getProperty, cmlocation_setProperty,
JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS
};

static JSFunctionSpec cmlocation_methods[] = {
	{ NULL, NULL, 0, 0, 0 }
};

static JSFunctionSpec cmlocation_static_methods[] = {
	{ NULL, NULL, 0, 0, 0 }
};

JSObject *
js_InitLocationClass(JSContext *cx, JSObject *obj) {
	
	JSObject *Location;

	Location = JS_DefineObject(cx, obj, "location", &cmlocation_class, NULL, 0);
  if (!Location)
  	return NULL;
  if (!JS_DefineFunctions(cx, Location, cmlocation_static_methods))
  	return NULL;
  if (!JS_DefineProperties(cx, Location, cmlocation_properties))
  	return NULL;

    CMLocation *cmLoc;

   cmLoc = JS_malloc(cx, sizeof *cmLoc);
  if (!cmLoc)
     return NULL;
memset(cmLoc, 0 , sizeof *cmLoc);

   cmLoc->search = JS_malloc(cx, strlen("search"));
  cmLoc->search = strdup("search");

JS_SetPrivate(cx, Location, cmLoc);

  return Location;
}
