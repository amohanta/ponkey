/*
 *
 * AUTHOR: Pankaj Tanwar <pankaj.tux@gmail.com>
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

#include "jselement.h"

#define JSLOG "/tmp/js_function.log"

enum document_property_id {
	DOCUMENT_ALINKCOLOR,
	DOCUMENT_ANCHORS, // array
	DOCUMENT_APPLETS, // array
	DOCUMENT_BGCOLOR,
        DOCUMENT_COOKIE,
	DOCUMENT_DOCUMENTELEMENT, //
	DOCUMENT_DOMAIN,
	DOCUMENT_EMBEDS, // array
	DOCUMENT_FGCOLOR,
	DOCUMENT_FORMNAME,
	DOCUMENT_FORMS, // array
	DOCUMENT_IMAGES, // array
	DOCUMENT_LASTMODIFIED,
	DOCUMENT_LAYERS, // array
	DOCUMENT_LINKCOLOR,
	DOCUMENT_LINKS, // array
	DOCUMENT_PLUGINS, // array
	DOCUMENT_REFERRER,
	DOCUMENT_TITLE,
	DOCUMENT_URL,
	DOCUMENT_VLINKCOLOR
};

static const char *document_property_str[] = {
	"alinkColor",
	"anchors",
	"applets",
	"bgColor",
	"cookie",
	"documentElement", //
	"domain",
	"embeds",
	"fgColor",
	"formname",
	"forms",
	"images",
	"lastModified",
	"layers",
	"linkColor",
	"links",
	"plugins",
	"referrer",
	"title",
	"URL",
	"vlinkColor"
};
/*//P Original  ugliest hack till INTERFACE is found
static JSPropertySpec document_properties[] = {
	{"alinkColor",	DOCUMENT_ALINKCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"anchors",	DOCUMENT_ANCHORS,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"applets",	DOCUMENT_APPLETS,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"bgColor",	DOCUMENT_BGCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"cookie",	DOCUMENT_COOKIE,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"domain",	DOCUMENT_DOMAIN,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"embeds",	DOCUMENT_EMBEDS,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"fgColor",	DOCUMENT_FGCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"formname",	DOCUMENT_FORMNAME,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"forms",	DOCUMENT_FORMS,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"images",	DOCUMENT_IMAGES,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"lastModified",	DOCUMENT_LASTMODIFIED,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"layers",	DOCUMENT_LAYERS,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"linkColor",	DOCUMENT_LINKCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"links",	DOCUMENT_LINKS,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"plugins",	DOCUMENT_PLUGINS,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"referrer",	DOCUMENT_REFERRER,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"title",	DOCUMENT_TITLE,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"URL",	DOCUMENT_URL,	JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_EXPORTED},
	{"vlinkColor",	DOCUMENT_VLINKCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{ NULL, 0, 0 }
};
*/

static JSPropertySpec document_properties[] = {
	{"alinkColor",	DOCUMENT_ALINKCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"anchors",	DOCUMENT_ANCHORS,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"applets",	DOCUMENT_APPLETS,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"bgColor",	DOCUMENT_BGCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"cookie",	DOCUMENT_COOKIE,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"documentElement", DOCUMENT_DOCUMENTELEMENT, JSPROP_EXPORTED }, //
	{"domain",	DOCUMENT_DOMAIN,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"embeds",	DOCUMENT_EMBEDS,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"fgColor",	DOCUMENT_FGCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"formname",	DOCUMENT_FORMNAME,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"forms",	DOCUMENT_FORMS,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"images",	DOCUMENT_IMAGES,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"lastModified",	DOCUMENT_LASTMODIFIED,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"layers",	DOCUMENT_LAYERS,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"linkColor",	DOCUMENT_LINKCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"links",	DOCUMENT_LINKS,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"plugins",	DOCUMENT_PLUGINS,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"referrer",	DOCUMENT_REFERRER,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"title",	DOCUMENT_TITLE,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"URL",	DOCUMENT_URL,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{"vlinkColor",	DOCUMENT_VLINKCOLOR,	JSPROP_ENUMERATE | JSPROP_EXPORTED},
	{ NULL, 0, 0 }
};

typedef struct JSD {
	int alinkColor
} JSD;

//P Now start setting properties
/*
static JSBool
document_settitle (JSContext *cx, JSObject *obj, uintNargc, jsval *argv, jsval *rval)
{

}
*/

//P FIXME I am dumb
JSBool
document_getProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{

	if(JSVAL_IS_INT(id)) {
		switch(JSVAL_TO_INT(id)) {
//P Please consider reviewing document_properties[] names taken as string BAD HACK 
			case DOCUMENT_ALINKCOLOR: 
			case DOCUMENT_ANCHORS: // array 
			case DOCUMENT_APPLETS: // array 
			case DOCUMENT_BGCOLOR: 
		        case DOCUMENT_COOKIE: 
			case DOCUMENT_DOCUMENTELEMENT: // 
			case DOCUMENT_DOMAIN: 
			case DOCUMENT_EMBEDS: // array 
			case DOCUMENT_FGCOLOR: 
			case DOCUMENT_FORMNAME: 
			case DOCUMENT_FORMS: // array 
			case DOCUMENT_IMAGES: // array 
			case DOCUMENT_LASTMODIFIED: 
			case DOCUMENT_LAYERS: // array 
			case DOCUMENT_LINKCOLOR: 
			case DOCUMENT_LINKS: //array 
			case DOCUMENT_PLUGINS: //array 
			case DOCUMENT_REFERRER: 
			case DOCUMENT_TITLE: 
			case DOCUMENT_URL: 
			case DOCUMENT_VLINKCOLOR: {
		//P	
//				printf("This is a getproperty in document: %s\n", 
//					document_properties[JSVAL_TO_INT(id)].name);
			}
//P not property nothing to do
		}
	}
	return JS_TRUE;
}

static JSBool document_setProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
  FILE *fOut;
  JSString *str;
  size_t n, i;
  jschar *s;

  if (JSVAL_IS_INT(id)) {
      switch (JSVAL_TO_INT(id)) {
        case DOCUMENT_ALINKCOLOR:
        case DOCUMENT_BGCOLOR:
        case DOCUMENT_DOMAIN:
        case DOCUMENT_FGCOLOR:
        case DOCUMENT_LINKCOLOR:
        case DOCUMENT_VLINKCOLOR:
				  fOut = fopen(JSLOG, "a");
 					if (fOut == NULL)
      			return JS_FALSE;
      		if (JSVAL_IS_INT(*vp)) {
        		fprintf(fOut, "document set property %s = %d\n", document_property_str[JSVAL_TO_INT(id)], JSVAL_TO_INT(*vp));
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
         		fprintf(fOut, "document set property %s = \"", document_property_str[JSVAL_TO_INT(id)]);
            if (n != 0)
            {
          	  for (i = 0; i < n; i++)
          		  fputc(s[i], fOut);
            }
         		fprintf(fOut, "\"\n");         		
      		}
      		else {
	      		fprintf(fOut, "document set property %s to value of unknown type %x\n", document_property_str[JSVAL_TO_INT(id)], JSVAL_TAG(*vp));
      		}
					fclose (fOut);
        	break;
	case DOCUMENT_DOCUMENTELEMENT:
		break;
        case DOCUMENT_ANCHORS:
        case DOCUMENT_APPLETS:
        case DOCUMENT_COOKIE:
        case DOCUMENT_EMBEDS:
        case DOCUMENT_FORMNAME:
        case DOCUMENT_FORMS:
        case DOCUMENT_IMAGES:
        case DOCUMENT_LASTMODIFIED:
        case DOCUMENT_LAYERS:
        case DOCUMENT_LINKS:
        case DOCUMENT_PLUGINS:
        case DOCUMENT_REFERRER:
        case DOCUMENT_TITLE:
        case DOCUMENT_URL:
				  fOut = fopen(JSLOG, "a");
 					if (fOut == NULL)
      			return JS_FALSE;
      		if (JSVAL_IS_INT(*vp)) {
        		fprintf(fOut, "document set property read-only %s = %d\n", document_property_str[JSVAL_TO_INT(id)], JSVAL_TO_INT(*vp));
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
         		fprintf(fOut, "document set property read-only %s = \"", document_property_str[JSVAL_TO_INT(id)]);
            if (n != 0)
            {
          	  for (i = 0; i < n; i++)
          		  fputc(s[i], fOut);
            }
         		fprintf(fOut, "\"\n");         		
      		}
      		else {
	      		fprintf(fOut, "document set property read-only %s to value of unknown type %x\n", document_property_str[JSVAL_TO_INT(id)], JSVAL_TAG(*vp));
      		}
					fclose (fOut);        	
        	break;
      }
  }

  return JS_TRUE;
}

static JSClass document_class = {
"document",
0,
JS_PropertyStub, JS_PropertyStub, document_getProperty /*//P*/, document_setProperty,
JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS
};

static JSBool document_captureEvents(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC;

  str = js_ValueToString(cx, argv[0]);
  if (!str)
      return JS_FALSE;

  if (JSSTRING_IS_DEPENDENT(str)) {
      n = JSSTRDEP_LENGTH(str);
      s = JSSTRDEP_CHARS(str);
  } else {
      n = str->length;
      s = str->chars;
  }

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

	fprintf(fOut, "document.captureEvents(\"");

  if (n != 0)
  {
      for (i = 0; i < n; i++)
          fputc(s[i], fOut);
  }
	fprintf(fOut, "\")\n");

  fclose (fOut);
	
	return JS_TRUE;
}

static JSBool document_close(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  FILE *fOut;

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

	fprintf(fOut, "document.close()\n");
  fclose (fOut);
	
	return JS_TRUE;
}

static JSBool document_getSelection(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  FILE *fOut;

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

	fprintf(fOut, "document.getSelection()\n");
  fclose (fOut);
	
	return JS_TRUE;
}

static JSBool document_handleEvent(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC;

  str = js_ValueToString(cx, argv[0]);
  if (!str)
      return JS_FALSE;

  if (JSSTRING_IS_DEPENDENT(str)) {
      n = JSSTRDEP_LENGTH(str);
      s = JSSTRDEP_CHARS(str);
  } else {
      n = str->length;
      s = str->chars;
  }

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

	fprintf(fOut, "document.handleEvent(\"");

  if (n != 0)
  {
      for (i = 0; i < n; i++)
          fputc(s[i], fOut);
  }
	fprintf(fOut, "\")\n");

  fclose (fOut);
	
	return JS_TRUE;
}

static JSBool document_open(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut;


  str = js_ValueToString(cx, argv[0]);
  if (!str)
      return JS_FALSE;

  if (JSSTRING_IS_DEPENDENT(str)) {
      n = JSSTRDEP_LENGTH(str);
      s = JSSTRDEP_CHARS(str);
  } else {
      n = str->length;
      s = str->chars;
  }

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

	fprintf(fOut, "document.open(\"");

  if (n != 0)
  {
      for (i = 0; i < n; i++)
          fputc(s[i], fOut);
  }
	fprintf(fOut, "\")\n");

  fclose (fOut);
	
	return JS_TRUE;
}

static JSBool document_releaseEvents(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC;

  str = js_ValueToString(cx, argv[0]);
  if (!str)
      return JS_FALSE;

  if (JSSTRING_IS_DEPENDENT(str)) {
      n = JSSTRDEP_LENGTH(str);
      s = JSSTRDEP_CHARS(str);
  } else {
      n = str->length;
      s = str->chars;
  }

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

	fprintf(fOut, "document.releaseEvents(\"");

  if (n != 0)
  {
      for (i = 0; i < n; i++)
          fputc(s[i], fOut);
  }
	fprintf(fOut, "\")\n");

  fclose (fOut);
	
	return JS_TRUE;
}


//Very very dumb createObject skeleton

static JSBool element_createObject(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
FILE* fOut;
const char* bytes;
JSString* str;

str = js_ValueToString(cx, argv[0]);

 bytes = JS_GetStringBytes(str);
  fOut = fopen("/tmp/js_function.log", "a");

       if(fOut){
	       fprintf(fOut, "OBJECT_CREATED: %s\n", bytes);
       fclose(fOut);
       }
return JS_TRUE;
}


//Very very dumb setAttribute skeleton
static JSBool element_setAttribute(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval){
FILE* fOut;
const char* attr_bytes;
const char* val_bytes;
const char* name_bytes;
JSString* str;

str = js_ValueToString(cx, argv[0]);

 attr_bytes = JS_GetStringBytes(str);

str = js_ValueToString(cx, argv[1]);

val_bytes = JS_GetStringBytes(str);

jsval jv;
if(!JS_GetProperty(cx, obj, "name", &jv)){
	return JS_FALSE;
}


str = js_ValueToString(cx, jv);
name_bytes = JS_GetStringBytes(str);
	
  fOut = fopen("/tmp/js_function.log", "a");

       if(fOut){
	       fprintf(fOut, "%s.setAttribute: %s to %s\n", name_bytes,attr_bytes, val_bytes);
       fclose(fOut);
       }
return JS_TRUE;
}



//TODO expand, this is DUMB!
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

static JSBool document_routeEvent(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC;

  str = js_ValueToString(cx, argv[0]);
  if (!str)
      return JS_FALSE;

  if (JSSTRING_IS_DEPENDENT(str)) {
      n = JSSTRDEP_LENGTH(str);
      s = JSSTRDEP_CHARS(str);
  } else {
      n = str->length;
      s = str->chars;
  }

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

	fprintf(fOut, "document.routeEvent(\"");

  if (n != 0)
  {
      for (i = 0; i < n; i++)
          fputc(s[i], fOut);
  }
	fprintf(fOut, "\")\n");

  fclose (fOut);
	
	return JS_TRUE;
}


static JSBool document_write(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC, *fLog;

  str = js_ValueToString(cx, argv[0]);
  if (!str)
      return JS_FALSE;

//  if (JSSTRING_IS_DEPENDENT(str)) {
//      n = JSSTRDEP_LENGTH(str);
//      s = JSSTRDEP_CHARS(str);
//  } else {
 //     n = str->length;
  //    s = str->chars;
//  }

//  if ((fOutUC = fopen(JSLOG, "r")) == NULL)
 // {
  //    fOutUC = fopen(JSLOG, "w");
   //   fputc(0xFF, fOutUC);
    //  fputc(0xFE, fOutUC);
     // fclose(fOutUC);
  //}

 // fOutUC = fopen(JSLOG, "a");
//  if (fOutUC == NULL)
//      return JS_FALSE;
//
 // fclose (fOutUC);

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

  fprintf(fOut, "DOCUMENT_WRITE: %s\n", JS_GetStringBytes(str));  
  
  fclose (fOut);

//  fLog = fopen(JSLOG, "a");
//  if (fLog == NULL)
//      return JS_FALSE;
//
//	fprintf(fLog, "document.write(\"");
 // if (n != 0)
 // {
  //    for (i = 0; i < n; i++)
  //        fputc(s[i], fLog);
 // }
//	fprintf(fLog, "\")\n");
//
 // fclose (fLog);
	
	return JS_TRUE;
}

static JSBool document_writeln(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) {
  JSString *str;
  size_t n, i;
  jschar *s;
  FILE *fOut, *fOutUC, *fLog;

  str = js_ValueToString(cx, argv[0]);
  if (!str)
      return JS_FALSE;

  if (JSSTRING_IS_DEPENDENT(str)) {
      n = JSSTRDEP_LENGTH(str);
      s = JSSTRDEP_CHARS(str);
  } else {
      n = str->length;
      s = str->chars;
  }

  if ((fOutUC = fopen(JSLOG, "r")) == NULL)
  {
      fOutUC = fopen(JSLOG, "w");
      fputc(0xFF, fOutUC);
      fputc(0xFE, fOutUC);
      fclose(fOutUC);
  }

  fOutUC = fopen(JSLOG, "a");
  if (fOutUC == NULL)
      return JS_FALSE;

  fwrite(s, n, 2, fOutUC);

	// LF
  fputc(0x0A, fOutUC);
  fputc(0x00, fOutUC);

  fclose (fOutUC);

  fOut = fopen(JSLOG, "a");
  if (fOut == NULL)
      return JS_FALSE;

  if (n != 0)
  {
      for (i = 0; i < n; i++)
          fputc(s[i], fOut);
  }
  // LF
  fputc('\n', fOut);

  fclose (fOut);
  
  fLog = fopen(JSLOG, "a");
  if (fLog == NULL)
      return JS_FALSE;

	fprintf(fLog, "DOCUMENT_WRITELN :");
  if (n != 0)
  {
      for (i = 0; i < n; i++)
          fputc(s[i], fLog);
  }
	fprintf(fLog, "\n");

  fclose (fLog);
	
	return JS_TRUE;
}


static JSBool document_getelementbyid (JSContext*, JSObject*, uintN, jsval* ,jsval*);

static JSFunctionSpec document_methods[] = {
	{ NULL, NULL, 0, 0, 0 }
};

static JSFunctionSpec document_static_methods[] = {
	{ "captureEvents", document_captureEvents, 1, 0, 0 },
	{ "close", document_close, 0, 0, 0 },
	{ "getSelection", document_getSelection, 0, 0, 0 },
	{ "handleEvent", document_handleEvent, 1, 0, 0 },
	{ "open", document_open, 2, 0, 0 },
	{ "releaseEvents", document_releaseEvents, 1, 0, 0 },
	{ "routeEvent", document_routeEvent, 1, 0, 0 },
	{ "write", document_write, 1, 0, 0 },
	{ "writeln", document_writeln, 1, 0, 0 },
	{ "createElement", document_createElement, 1, 0, 0 },
	{ "getElementById", document_getelementbyid, 1, 0, 0 },
	{ NULL, NULL, 0, 0, 0 }
};


//P #define INITPROPERTIES
//P to fill

enum jselement_property_id {
	ELEMENT_BASEURI,
	ELEMENT_CHILDELEMENTCOUNT,
	ELEMENT_CLIENTHEIGHT,
	ELEMENT_CLIENTTOP,
	ELEMENT_NAME,
	ELEMENT_CLIENTWIDTH,
	ELEMENT_CONTENTEDITABLE
};

static JSPropertySpec element_properties[] = {
	{ "baseURI", 		ELEMENT_BASEURI , 		JSPROP_ENUMERATE },
	{ "childElementCount", 	ELEMENT_CHILDELEMENTCOUNT , 	JSPROP_ENUMERATE },
	{ "clientHeight", 	ELEMENT_CLIENTHEIGHT , 		JSPROP_ENUMERATE },
	{ NULL, 0, 0}
};

//P just to work 
static JSBool document_getelementbyid(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) 
{
	jsid id;
	JSString *str;
	JS_ValueToId(cx, argv[0], &id);
	printf("I got this id: %d\n", JSID_TO_INT(id)); //now what can i do with this id....
	str = js_NumberToString(cx, (jsdouble) JSID_TO_INT(id));
	printf("The string with this id is: %s\n", JS_GetStringBytes(str));
	return JS_TRUE;
/*  }

  if(!JS_DefineProperties(cx, elementObj, element_properties)) {
	return JS_FALSE;
  }
	*rval= OBJECT_TO_JSVAL(elementObj);
	return JS_TRUE;
///P End */
}

JSObject *
js_InitDocumentClass(JSContext *cx, JSObject *obj) {
	
  JSObject *Document;
  JSObject* bodyObj;

  JSObject *elementObj;
//printf("document object created\n");//P
/*
//P
#ifdef INITPROPERTIES
  JSObject *proto;
  proto=JS_InitClass(cx, obj, NULL, &document_class, initdocumentproperties,
		0, NULL, document_methods, NULL, document_static_methods);
  if(!proto)
	return NULL;
  return proto;
#else
*/
  Document = JS_DefineObject(cx, obj, "document", &document_class, NULL, 0);
  if (!Document) 
  	return NULL;
  if (!JS_DefineFunctions(cx, Document, document_static_methods))
  	return NULL;
//printf("document functions defined\n"); //P
  if (!JS_DefineProperties(cx, Document, document_properties)) {
  	return NULL;
  }
//printf("document properties defined\n");//P
  if(!(bodyObj = JS_DefineObject(cx, Document, "body", NULL, NULL, 0))){
	  return NULL;
  }
  if(!JS_DefineProperty(cx, bodyObj, "innerHTML", JS_GetEmptyStringValue(cx), NULL, NULL, 0)){
              return JS_FALSE;
  }	      
  if(!JS_DefineProperty(cx, Document, "referer", JS_GetEmptyStringValue(cx), NULL, NULL, 0)){
              return JS_FALSE;
  }
  js_InitElementClass(cx, Document);
/*
  if(!(elementObj = JS_DefineObject(cx, Document, "documentElement", NULL, NULL, 0))) {
	return NULL;
  }

  if(!JS_DefineProperties(cx, elementObj, element_properties)) {
	return JS_FALSE;
  }
*/
/*
  JSD *jsDoc;
  jsDoc = JS_malloc(cx, sizeof *jsDoc);
  if(!jsDoc)
	return NULL;

  memset(jsDoc, 0, sizeof *jsDoc);
  jsDoc->alinkColor=JS_malloc(cx, strlen("try")); 
  jsDoc->alinkColor=strdup("try");
  JS_SetPrivate(cx, Document, jsDoc);
*/
  return Document;
//P#endif
}
