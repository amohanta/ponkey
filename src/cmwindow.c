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

static JSClass cmwindow_class;
static JSPropertySpec cmwindow_properties[];
enum cmwindow_property_id {
	window_name = -1,
	FOJ_PROPERTY,
	WINDOW_CLOSED,//
	WINDOW_COMPONENTS,//
	WINDOW_CONTENT, //
	WINDOW_DEFAULTSTATUS,//
	WINDOW_DOCUMENT,//
	WINDOW_FRAMEELEMENT,//
	WINDOW_FRAMES,//
	WINDOW_HISTORY,//
	WINDOW_INNERHEIGHT,//
	WINDOW_INNERWIDTH,//
	WINDOW_LENGTH,//
	WINDOW_LOCATION,//
	WINDOW_NAME,//
	WINDOW_STATUS,//
	WINDOW_STATUSBAR//
};



/* Structure representing the Navigator internally */
typedef struct CMWindow {
	JSObject *document;
} CMWindow;



static const char *cmwindow_property_str[] = {
	"FOJ_PROPERTY",
	"closed",//WINDOW_CLOSED,//
	"components",//WINDOW_COMPONENTS,//
	"content",///WINDOW_CONTENT, //
	"defautStatus",//WINDOW_DEFAULTSTATUS,//
	"document",//WINDOW_DOCUMENT,//
	"frameElement",//WINDOW_FRAMEELEMENT,//
	"frames",//WINDOW_FRAMES,//
	"history",//WINDOW_HISTORY,//
	"innerHeight",//WINDOW_INNERHEIGHT,//
	"innerWidth",//WINDOW_INNERWIDTH,//
	"length",//WINDOW_LENGTH,//
	"location",//WINDOW_LOCATION,//
	"name",//WINDOW_NAME,//
	"status",//WINDOW_NAME,//
	"statusbar"//WINDOW_NAME,//
};

static JSPropertySpec cmwindow_properties[] = {
	{ "FOJ_PROPERTY" , 0, 0},
	{ "closed", WINDOW_CLOSED , JSPROP_ENUMERATE },
	{ "components", WINDOW_COMPONENTS, JSPROP_ENUMERATE },
	{ "content", WINDOW_CONTENT , JSPROP_ENUMERATE },
	{ "defaultStatus", WINDOW_DEFAULTSTATUS , JSPROP_ENUMERATE },
	{ "document", WINDOW_DOCUMENT , JSPROP_ENUMERATE },
	{ "frames", WINDOW_FRAMES , JSPROP_ENUMERATE },
	{ "history", WINDOW_HISTORY , JSPROP_ENUMERATE },
	{ "innerHeight", WINDOW_INNERHEIGHT , JSPROP_ENUMERATE },
	{ "innerWidth", WINDOW_INNERWIDTH , JSPROP_ENUMERATE },
	{ "length", WINDOW_LENGTH , JSPROP_ENUMERATE },
	{ "location", WINDOW_LOCATION , JSPROP_ENUMERATE },
	{ "name", WINDOW_NAME , JSPROP_ENUMERATE },
	{ "status", WINDOW_STATUS , JSPROP_ENUMERATE },
	{ "statusbar", WINDOW_STATUSBAR , JSPROP_ENUMERATE },
	{ NULL, 0, 0}
};

static JSBool cmwindow_setProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

  if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
	//	case WINDOW_DOCUMENT:
	//		break;
		case FOJ_PROPERTY:
	      default:
		fOut = fopen(JSLOG, "a");
 		if (fOut == NULL)
      			return JS_FALSE;
      		if (JSVAL_IS_INT(*vp)) {
        		fprintf(fOut, "LOCATION set property read-only %s = %d\n", 
				cmwindow_property_str[JSVAL_TO_INT(id)], JSVAL_TO_INT(*vp));
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
         		fprintf(fOut, "LOCATION set property read-only %s = \"", cmwindow_property_str[JSVAL_TO_INT(id)]);
            if (n != 0)
            {
          	  for (i = 0; i < n; i++)
          		  fputc(s[i], fOut);
            }
         		fprintf(fOut, "\"\n");         		
      		}
      		else {
	      		fprintf(fOut, "LOCATION set property read-only %s to value of unknown type %x\n", 
				cmwindow_property_str[JSVAL_TO_INT(id)], JSVAL_TAG(*vp));
      		}
					fclose (fOut);        	
        	break;
      }
  }
  return JS_TRUE;
}

static JSBool cmwindow_getProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

CMWindow* cmWin = JS_GetInstancePrivate(cx, obj, &cmwindow_class, NULL);

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

static JSBool window_foj(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
	printf("Window.FOJ() mean F*** OFF J****\n");
	return JS_TRUE;
}

//
/*
static JSBool document_createElement(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
JSObject* element;
	
FILE* fOut;
const char* bytes;
JSString* str;


str = js_ValueToString(cx, argv[0]);
     
	
 bytes = JS_GetStringBytes(str);
 fOut = fopen("/tmp/js_function.log", "a");

     if(fOut){
	     fprintf(fOut, "NEW_ELEMENT: %s\n", bytes);
	     fclose(fOut);
			 
	}

 element = JS_DefineObject(cx, obj, bytes, NULL, NULL, 0);
 if(!element){
	return JS_FALSE;
 }
 if(!JS_DefineFunction(cx, element, "CreateObject", element_createObject, 1, NULL)){
	return JS_FALSE;
 }

 if(!JS_DefineFunction(cx, element, "setAttribute", element_setAttribute, 2, NULL)){
	return JS_FALSE;
 }

if(!JS_DefineProperty(cx, element, "name", argv[0], NULL, NULL, 0)){
	return JS_FALSE;
}
 
     *rval = OBJECT_TO_JSVAL(element);
     return JS_TRUE;

}
*/


static JSBool window_alert(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
	FILE *fOut;
	JSString *str;
	size_t n,i;
	jschar *s;

	fOut = fopen(JSLOG, "a");
	if(!fOut) 
		return JS_FALSE;

	str= js_ValueToString(cx, argv[0]);
	if(!str)
		return JS_FALSE;

	if(JSSTRING_IS_DEPENDENT(str)) {
		n=JSSTRDEP_LENGTH(str);
		s=JSSTRDEP_CHARS(str);
	} else {
		n=str->length;
		s=str->chars;
	}

	fprintf(fOut, "WINDOW_ALERT : ");
	if(n!=0) {
		for(i=0;i<n;i++)
			fputc(s[i], fOut);
	}
	fprintf(fOut,"\n");

	fclose(fOut);

	return JS_TRUE;
}

static JSClass cmwindow_class = {
"window",
JSCLASS_HAS_PRIVATE,
JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS
};

static JSFunctionSpec cmwindow_methods[] = {
	{ NULL, NULL, 0, 0, 0 }
};

static JSFunctionSpec cmwindow_static_methods[] = {
	{"FOJ", window_foj, 0, 0, 0},
	{"alert", window_alert,1,0,0},
	{ NULL, NULL, 0, 0, 0 }
};
//P for windows.document
static JSClass document_class = {
"document",
0,
JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS
};

JSObject *
js_InitWindowClass(JSContext *cx, JSObject *obj) {
	
	JSObject *Window;

	Window = JS_DefineObject(cx, obj, "window", &cmwindow_class, NULL, 0);
  if (!Window)
  	return NULL;
  if (!JS_DefineFunctions(cx, Window, cmwindow_static_methods))
  	return NULL;
  if (!JS_DefineProperties(cx, Window, cmwindow_properties))
  	return NULL;
  if (!JS_DefineFunction(cx, Window, "open", JS_PropertyStub, 4, 0))
  	return NULL;
  

  CMWindow *cmWin;

   cmWin = JS_malloc(cx, sizeof *cmWin);
  if (!cmWin)
     return NULL;
  memset(cmWin, 0 , sizeof *cmWin);

  JSObject *document=JS_DefineObject(cx, Window, "document", &document_class, NULL, 0);
  cmWin->document = JS_malloc(cx, sizeof(document_class));
  cmWin->document = document;

  JS_SetPrivate(cx, Window, cmWin);


  return Window;
}
