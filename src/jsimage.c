/*
 *
 * Author: Pankaj Tanwar <pankaj.tux@gmail.com>
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

static JSClass image_class;
static JSPropertySpec jselement_properties[];
enum jselement_property_id {
	ELEMENT_BASEURI,
	ELEMENT_CHILDELEMENTCOUNT,
	ELEMENT_CLIENTHEIGHT,
	ELEMENT_CLIENTTOP,
	ELEMENT_NAME,
	ELEMENT_CLIENTWIDTH,
	ELEMENT_CONTENTEDITABLE
};




static const char *image_property_str[] = {
	"test"
};

static JSPropertySpec image_properties[] = {
	{ NULL, 0, 0}
};

static JSClass image_class = {
"image",
JSCLASS_HAS_PRIVATE,
JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS
};

/*
static JSBool jselement_setProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

  if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
		case ELEMENT_BASEURI:
	      default:
		fOut = fopen(JSLOG, "a");
 		if (fOut == NULL)
      			return JS_FALSE;
      		if (JSVAL_IS_INT(*vp)) {
        		fprintf(fOut, "ELEMENT set property read-only %s = %d\n", 
				jselement_property_str[JSVAL_TO_INT(id)], JSVAL_TO_INT(*vp));
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
         		fprintf(fOut, "ELEMENT set property read-only %s = \"", jselement_property_str[JSVAL_TO_INT(id)]);
            if (n != 0)
            {
          	  for (i = 0; i < n; i++)
          		  fputc(s[i], fOut);
            }
         		fprintf(fOut, "\"\n");         		
      		}
      		else {
	      		fprintf(fOut, "ELEMENT set property read-only %s to value of unknown type %x\n", 
				jselement_property_str[JSVAL_TO_INT(id)], JSVAL_TAG(*vp));
      		}
					fclose (fOut);        	
        	break;
      }
  }
  return JS_TRUE;
}

static JSBool jselement_getProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

  JSElement* jsEl = JS_GetInstancePrivate(cx, obj, &jselement_class, NULL);

if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
//	case WINDOW_DOCUMENT:
//		break;
	default:
		*vp = JS_GetEmptyStringValue(cx);
	}
}
 return JS_TRUE;

}
*/

static JSObject
*image_constructor(JSContext *cx, JSObject *obj)
{
	JSObject *imageObj;
	imageObj = JS_DefineObject(cx, obj, "img", NULL, 0, 0);

	return imageObj;
}

static JSBool
Image(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
//	rval = OBJECT_TO_JSVAL(image_constructor(cx, obj));
	return JS_TRUE;
}

static JSFunctionSpec image_methods[] = {
	{ NULL, NULL, 0, 0, 0 }
};

static JSFunctionSpec image_static_methods[] = {
	{ "Image", image_constructor, 2, 0, 0},
	{ NULL, NULL, 0, 0, 0 }
};

JSObject *
js_InitImageClass (JSContext *cx, JSObject *obj) {
	
  JSObject *image;

  image = JS_DefineObject(cx, obj, "Image", &image_class, NULL, 0);

//  image = JS_InitClass(cx, obj, NULL, &image_class, Image, 2,
//		NULL, image_methods, NULL, image_static_methods);

  if (!image) {
  	return NULL;
  }
  if (!JS_DefineFunctions(cx, image, image_static_methods))
//  	return NULL;
/*  if (!JS_DefineProperties(cx, Element, jselement_properties))
  	return NULL;

  JSElement *jsEl;

   jsEl = JS_malloc(cx, sizeof *jsEl);
  if (!jsEl)
     return NULL;
  memset(jsEl, 0 , sizeof *jsEl);

  jsEl->baseuri = JS_malloc(cx, strlen("www.uri.com"));
  jsEl->baseuri = strdup("www.uri.com");

  JS_SetPrivate(cx, Element, jsEl);
*/

  return image;
}

