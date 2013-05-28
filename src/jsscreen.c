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
#define SETTERLOG "/tmp/screen.setter.log"
#define GETTERLOG "/tmp/screen.getter.log"
#define METHODLOG "/tmp/screen.method_calls.log"

enum screen_property_id
{
  SCREEN_AVAILHEIGHT,
  SCREEN_AVAILWIDTH,
  SCREEN_COLORDEPTH,
  SCREEN_HEIGHT,
  SCREEN_WIDTH
};

static const char *screen_property_str[] = {
  "availHeight",
  "availWidth",
  "colorDepth",
  "height",
  "width"
};

static JSPropertySpec screen_properties[] = {
  {"availHeight", SCREEN_AVAILHEIGHT, JSPROP_ENUMERATE | JSPROP_EXPORTED},
  {"availWidth", SCREEN_AVAILWIDTH,
   JSPROP_ENUMERATE | JSPROP_EXPORTED},
  {"colorDepth", SCREEN_COLORDEPTH,
   JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
  {"height", SCREEN_HEIGHT, JSPROP_ENUMERATE | JSPROP_EXPORTED},
  {"width", SCREEN_WIDTH,
   JSPROP_ENUMERATE | JSPROP_EXPORTED},
  {0}
};

static JSBool
screen_getProperty (JSContext * cx, JSObject * obj, jsval id, jsval * vp)
{
FILE* fOut;	
	
if (JSVAL_IS_INT (id))
    {
      switch (JSVAL_TO_INT (id))
	{
	case SCREEN_AVAILHEIGHT:
	case SCREEN_AVAILWIDTH:
	case SCREEN_COLORDEPTH:
	case SCREEN_HEIGHT:
	case SCREEN_WIDTH:
	  fOut = fopen (GETTERLOG, "a");
	  if (fOut == NULL)
	    return JS_FALSE;
	  if (JSVAL_IS_INT (*vp))
	    {
	      fprintf (fOut, "screen got property %s\n",
		       screen_property_str[JSVAL_TO_INT (id)]);
	    }
	fclose(fOut);
	  break;
	}
    }

  return JS_TRUE;
}

static JSBool
screen_setProperty (JSContext * cx, JSObject * obj, jsval id, jsval * vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

  if (JSVAL_IS_INT (id))
    {
      switch (JSVAL_TO_INT (id))
	{
	case SCREEN_AVAILHEIGHT:
	case SCREEN_AVAILWIDTH:
	case SCREEN_COLORDEPTH:
	case SCREEN_HEIGHT:
	case SCREEN_WIDTH:
	  fOut = fopen (SETTERLOG, "a");
	  if (fOut == NULL)
	    return JS_FALSE;
	  if (JSVAL_IS_INT (*vp))
	    {
	      fprintf (fOut, "screen set property read-only %s = %d\n",
		       screen_property_str[JSVAL_TO_INT (id)],
		       JSVAL_TO_INT (*vp));
	    }
	  else if (JSVAL_IS_STRING (*vp))
	    {
	      str = js_ValueToString (cx, *vp);
	      if (!str)
		return JS_FALSE;
	      if (JSSTRING_IS_DEPENDENT (str))
		{
		  n = JSSTRDEP_LENGTH (str);
		  s = JSSTRDEP_CHARS (str);
		}
	      else
		{
		  n = str->length;
		  s = str->chars;
		}
	      fprintf (fOut, "screen set property read-only %s = \"",
		       screen_property_str[JSVAL_TO_INT (id)]);
	      if (n != 0)
		{
		  for (i = 0; i < n; i++)
		    fputc (s[i], fOut);
		}
	      fprintf (fOut, "\"\n");
	    }
	  else
	    {
	      fprintf (fOut,
		       "screen set property read-only %s to value of unknown type %x\n",
		       screen_property_str[JSVAL_TO_INT (id)],
		       JSVAL_TAG (*vp));
	    }
	  fclose (fOut);
	  break;
	}
    }
  return JS_TRUE;
}

static JSClass screen_class = {
  "screen",
  0,
  JS_PropertyStub, JS_PropertyStub, screen_getProperty, screen_setProperty,
  JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

static JSBool
screen_captureEvents (JSContext * cx, JSObject * obj, uintN argc,
		      jsval * argv, jsval * rval)
{
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC;

  str = js_ValueToString (cx, argv[0]);
  if (!str)
    return JS_FALSE;

  if (JSSTRING_IS_DEPENDENT (str))
    {
      n = JSSTRDEP_LENGTH (str);
      s = JSSTRDEP_CHARS (str);
    }
  else
    {
      n = str->length;
      s = str->chars;
    }

  fOut = fopen (METHODLOG, "a");
  if (fOut == NULL)
    return JS_FALSE;

  fprintf (fOut, "screen.captureEvents(\"");

  if (n != 0)
    {
      for (i = 0; i < n; i++)
	fputc (s[i], fOut);
    }
  fprintf (fOut, "\")\n");

  fclose (fOut);

  return JS_TRUE;
}


static JSFunctionSpec screen_methods[] = {
  {NULL, NULL, 0, 0, 0}
};

static JSFunctionSpec screen_static_methods[] = {
  {NULL, NULL, 0, 0, 0}
};

JSObject *
js_InitScreenClass (JSContext * cx, JSObject * obj)
{

  JSObject *Screen;

  Screen = JS_DefineObject (cx, obj, "screen", &screen_class, NULL, 0);
  if (!Screen)
    return NULL;
  if (!JS_DefineFunctions (cx, Screen, screen_static_methods))
    return NULL;
  if (!JS_DefineProperties (cx, Screen, screen_properties))
    return NULL;

  return Screen;
}
