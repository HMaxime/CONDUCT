/* ------------------------------------------------------------
author: "Romain Michon (rmichon@ccrma.stanford.edu)"
copyright: "Romain Michon"
name: "piano"
version: "1.0"
Code generated with Faust 2.14.4 (https://faust.grame.fr)
Compilation options: -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2006-2011 Albert Graef <Dr.Graef@t-online.de>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
    published by the Free Software Foundation; either version 2.1 of the 
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA. 
 ************************************************************************
 ************************************************************************/

/* Pd architecture file, written by Albert Graef <Dr.Graef@t-online.de>.
   This was derived from minimal.cpp included in the Faust distribution.
   Please note that this is to be compiled as a shared library, which is
   then loaded dynamically by Pd as an external. */

#include <stdlib.h>
#include <math.h>
#include <string.h>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <cstdlib>
#include <string.h>

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

static int lsr(int x, int n) { return int(((unsigned int)x) >> n); }

static int int2pow2(int x) { int r = 0; while ((1<<r) < x) r++; return r; }

static long lopt(char* argv[], const char* name, long def)
{
	int	i;
    for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return std::atoi(argv[i+1]);
	return def;
}

static bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

static const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

#endif
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param samplingRate - the sampling rate in Hertz
         */
        virtual void init(int samplingRate) = 0;

        /**
         * Init instance state
         *
         * @param samplingRate - the sampling rate in Hertz
         */
        virtual void instanceInit(int samplingRate) = 0;

        /**
         * Init instance constant state
         *
         * @param samplingRate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/***************************************************************************
   Pd UI interface
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  char *label;
  float *zone;
  float init, min, max, step;
};

class PdUI : public UI
{
public:
  const char *name;
  int nelems, level;
  ui_elem_t *elems;
		
  PdUI();
  PdUI(const char *nm, const char *s);
  virtual ~PdUI();

protected:
  std::string path;
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, float *zone);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float min, float max);

public:
  virtual void addButton(const char* label, float* zone);
  virtual void addCheckButton(const char* label, float* zone);
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);
    
  virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
  
  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();
	
  virtual void run();
};

static std::string mangle(const char *name, int level, const char *s)
{
  const char *s0 = s;
  std::string t = "";
  if (!s) return t;
  // Get rid of bogus "0x00" labels in recent Faust revisions. Also, for
  // backward compatibility with old Faust versions, make sure that default
  // toplevel groups and explicit toplevel groups with an empty label are
  // treated alike (these both return "0x00" labels in the latest Faust, but
  // would be treated inconsistently in earlier versions).
  if (!*s || strcmp(s, "0x00") == 0) {
    if (level == 0)
      // toplevel group with empty label, map to dsp name
      s = name;
    else
      // empty label
      s = "";
  }
  while (*s)
    if (isalnum(*s))
      t += *(s++);
    else {
      const char *s1 = s;
      while (*s && !isalnum(*s)) ++s;
      if (s1 != s0 && *s) t += "-";
    }
  return t;
}

static std::string normpath(std::string path)
{
  path = std::string("/")+path;
  int pos = path.find("//");
  while (pos >= 0) {
    path.erase(pos, 1);
    pos = path.find("//");
  }
  size_t len = path.length();
  if (len > 1 && path[len-1] == '/')
    path.erase(len-1, 1);
  return path;
}

static std::string pathcat(std::string path, std::string label)
{
  if (path.empty())
    return normpath(label);
  else if (label.empty())
    return normpath(path);
  else
    return normpath(path+"/"+label);
}

PdUI::PdUI()
{
  nelems = level = 0;
  elems = NULL;
  name = "";
  path = "";
}

PdUI::PdUI(const char *nm, const char *s)
{
  nelems = level = 0;
  elems = NULL;
  name = nm?nm:"";
  path = s?s:"";
}

PdUI::~PdUI()
{
  if (elems) {
    for (int i = 0; i < nelems; i++)
      if (elems[i].label)
	free(elems[i].label);
    free(elems);
  }
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 1.0;
  elems[nelems].step = 1.0;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			  float init, float min, float max, float step)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = init;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = step;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			  float min, float max)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = 0.0;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = 0.0;
  nelems++;
}

void PdUI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void PdUI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void PdUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void PdUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void PdUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void PdUI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void PdUI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void PdUI::openTabBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::openHorizontalBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::openVerticalBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::closeBox()
{
  int pos = path.rfind("/");
  if (pos < 0) pos = 0;
  path.erase(pos);
  level--;
}

void PdUI::run() {}

/******************************************************************************
*******************************************************************************

			    FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------
		
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <math.h>
#include <piano.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fRec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fEntry0;
	float fConst2;
	FAUSTFLOAT fHslider2;
	float fConst3;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fButton0;
	float fRec8[2];
	FAUSTFLOAT fHslider4;
	int iRec14[2];
	float fConst4;
	float fConst5;
	float fRec16[2];
	float fConst6;
	FAUSTFLOAT fHslider5;
	float fConst7;
	float fRec15[2];
	float fConst8;
	FAUSTFLOAT fEntry1;
	float fRec17[2];
	float fRec13[2];
	float fRec12[2];
	float fRec11[2];
	float fRec10[2];
	float fRec9[2];
	float fVec0[2];
	float fRec7[2];
	float fRec6[2];
	int IOTA;
	float fRec5[8192];
	float fVec1[2];
	float fRec21[2];
	float fRec20[2];
	float fRec19[8192];
	float fVec2[2];
	float fRec18[2];
	float fRec2[2];
	float fRec3[2];
	float fConst9;
	float fRec1[3];
	float fVec3[2];
	float fVec4[2];
	float fRec31[2];
	float fRec30[2];
	float fRec29[2];
	float fRec28[2];
	float fRec27[2];
	float fConst10;
	float fRec26[3];
	float fRec25[3];
	float fRec24[3];
	float fRec23[3];
	float fRec22[2];
	float fVec5[8192];
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	FAUSTFLOAT fHslider6;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec43[2];
	float fRec42[2];
	float fVec6[32768];
	float fConst19;
	int iConst20;
	float fConst21;
	FAUSTFLOAT fHslider7;
	float fVec7[4096];
	int iConst22;
	float fVec8[2048];
	int iConst23;
	float fRec40[2];
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec47[2];
	float fRec46[2];
	float fVec9[32768];
	float fConst28;
	int iConst29;
	float fVec10[4096];
	int iConst30;
	float fRec44[2];
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fRec51[2];
	float fRec50[2];
	float fVec11[16384];
	float fConst35;
	int iConst36;
	float fVec12[4096];
	int iConst37;
	float fRec48[2];
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fRec55[2];
	float fRec54[2];
	float fVec13[32768];
	float fConst42;
	int iConst43;
	float fVec14[4096];
	int iConst44;
	float fRec52[2];
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fRec59[2];
	float fRec58[2];
	float fVec15[16384];
	float fConst49;
	int iConst50;
	float fVec16[4096];
	float fVec17[2048];
	int iConst51;
	float fRec56[2];
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec63[2];
	float fRec62[2];
	float fVec18[16384];
	float fConst56;
	int iConst57;
	float fVec19[4096];
	int iConst58;
	float fRec60[2];
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec67[2];
	float fRec66[2];
	float fVec20[16384];
	float fConst63;
	int iConst64;
	float fVec21[4096];
	int iConst65;
	float fRec64[2];
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fRec71[2];
	float fRec70[2];
	float fVec22[16384];
	float fConst70;
	int iConst71;
	float fVec23[2048];
	int iConst72;
	float fRec68[2];
	float fRec32[3];
	float fRec33[3];
	float fRec34[3];
	float fRec35[3];
	float fRec36[3];
	float fRec37[3];
	float fRec38[3];
	float fRec39[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("copyright", "Romain Michon");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("description", "A commuted WaveGuide piano.");
		m->declare("filename", "piano");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("instruments.lib/author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("instruments.lib/copyright", "Romain Michon");
		m->declare("instruments.lib/licence", "STK-4.3");
		m->declare("instruments.lib/name", "Faust-STK Tools Library");
		m->declare("instruments.lib/version", "1.0");
		m->declare("licence", "STK-4.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "piano");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (1.0f / mydsp_faustpower2_f(fConst0));
		fConst2 = (0.159154937f * fConst0);
		fConst3 = (6.28318548f / fConst0);
		fConst4 = std::exp((0.0f - (5.0f / fConst0)));
		fConst5 = std::exp((0.0f - (0.5f / fConst0)));
		fConst6 = (0.100000001f * fConst0);
		fConst7 = (10.0f / fConst0);
		fConst8 = (7.0f / fConst0);
		fConst9 = (2.0f / fConst0);
		fConst10 = (0.0500000007f / fConst0);
		fConst11 = std::cos((37699.1133f / fConst0));
		fConst12 = std::floor(((0.219990999f * fConst0) + 0.5f));
		fConst13 = ((0.0f - (6.90775537f * fConst12)) / fConst0);
		fConst14 = (0.5f * fConst13);
		fConst15 = (0.333333343f * fConst13);
		fConst16 = (1.0f / std::tan((628.318542f / fConst0)));
		fConst17 = (1.0f / (fConst16 + 1.0f));
		fConst18 = (1.0f - fConst16);
		fConst19 = std::floor(((0.0191229992f * fConst0) + 0.5f));
		iConst20 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst12 - fConst19))));
		fConst21 = (0.5f * fConst0);
		iConst22 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (0.0199999996f * fConst0))));
		iConst23 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst19 + -1.0f))));
		fConst24 = std::floor(((0.256891012f * fConst0) + 0.5f));
		fConst25 = ((0.0f - (6.90775537f * fConst24)) / fConst0);
		fConst26 = (0.5f * fConst25);
		fConst27 = (0.333333343f * fConst25);
		fConst28 = std::floor(((0.0273330007f * fConst0) + 0.5f));
		iConst29 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst24 - fConst28))));
		iConst30 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst28 + -1.0f))));
		fConst31 = std::floor(((0.192303002f * fConst0) + 0.5f));
		fConst32 = ((0.0f - (6.90775537f * fConst31)) / fConst0);
		fConst33 = (0.5f * fConst32);
		fConst34 = (0.333333343f * fConst32);
		fConst35 = std::floor(((0.0292910002f * fConst0) + 0.5f));
		iConst36 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst31 - fConst35))));
		iConst37 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst35 + -1.0f))));
		fConst38 = std::floor(((0.210389003f * fConst0) + 0.5f));
		fConst39 = ((0.0f - (6.90775537f * fConst38)) / fConst0);
		fConst40 = (0.5f * fConst39);
		fConst41 = (0.333333343f * fConst39);
		fConst42 = std::floor(((0.0244210009f * fConst0) + 0.5f));
		iConst43 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst38 - fConst42))));
		iConst44 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst42 + -1.0f))));
		fConst45 = std::floor(((0.125f * fConst0) + 0.5f));
		fConst46 = ((0.0f - (6.90775537f * fConst45)) / fConst0);
		fConst47 = (0.5f * fConst46);
		fConst48 = (0.333333343f * fConst46);
		fConst49 = std::floor(((0.0134579996f * fConst0) + 0.5f));
		iConst50 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst45 - fConst49))));
		iConst51 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst49 + -1.0f))));
		fConst52 = std::floor(((0.127837002f * fConst0) + 0.5f));
		fConst53 = ((0.0f - (6.90775537f * fConst52)) / fConst0);
		fConst54 = (0.5f * fConst53);
		fConst55 = (0.333333343f * fConst53);
		fConst56 = std::floor(((0.0316039994f * fConst0) + 0.5f));
		iConst57 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst52 - fConst56))));
		iConst58 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst56 + -1.0f))));
		fConst59 = std::floor(((0.174713001f * fConst0) + 0.5f));
		fConst60 = ((0.0f - (6.90775537f * fConst59)) / fConst0);
		fConst61 = (0.5f * fConst60);
		fConst62 = (0.333333343f * fConst60);
		fConst63 = std::floor(((0.0229039993f * fConst0) + 0.5f));
		iConst64 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst59 - fConst63))));
		iConst65 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst63 + -1.0f))));
		fConst66 = std::floor(((0.153128996f * fConst0) + 0.5f));
		fConst67 = ((0.0f - (6.90775537f * fConst66)) / fConst0);
		fConst68 = (0.5f * fConst67);
		fConst69 = (0.333333343f * fConst67);
		fConst70 = std::floor(((0.0203460008f * fConst0) + 0.5f));
		iConst71 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst66 - fConst70))));
		iConst72 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst70 + -1.0f))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.59999999999999998f);
		fHslider1 = FAUSTFLOAT(0.13700000000000001f);
		fEntry0 = FAUSTFLOAT(440.0f);
		fHslider2 = FAUSTFLOAT(0.28000000000000003f);
		fHslider3 = FAUSTFLOAT(0.10000000000000001f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.10000000000000001f);
		fEntry1 = FAUSTFLOAT(1.0f);
		fHslider6 = FAUSTFLOAT(0.71999999999999997f);
		fHslider7 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec8[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec14[l2] = 0;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec16[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec15[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec17[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec13[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec12[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec11[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec10[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec9[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec0[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec7[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec6[l13] = 0.0f;
			
		}
		IOTA = 0;
		for (int l14 = 0; (l14 < 8192); l14 = (l14 + 1)) {
			fRec5[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec1[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec21[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec20[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 8192); l18 = (l18 + 1)) {
			fRec19[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec2[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec2[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec3[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec1[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec3[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec4[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec31[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec30[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec29[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec28[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec27[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec26[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec25[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec24[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec23[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec22[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 8192); l36 = (l36 + 1)) {
			fVec5[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec43[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec42[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 32768); l39 = (l39 + 1)) {
			fVec6[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 4096); l40 = (l40 + 1)) {
			fVec7[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2048); l41 = (l41 + 1)) {
			fVec8[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec40[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec47[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec46[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 32768); l45 = (l45 + 1)) {
			fVec9[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 4096); l46 = (l46 + 1)) {
			fVec10[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec44[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec51[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec50[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 16384); l50 = (l50 + 1)) {
			fVec11[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 4096); l51 = (l51 + 1)) {
			fVec12[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec48[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec55[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec54[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 32768); l55 = (l55 + 1)) {
			fVec13[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 4096); l56 = (l56 + 1)) {
			fVec14[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec52[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec59[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec58[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 16384); l60 = (l60 + 1)) {
			fVec15[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 4096); l61 = (l61 + 1)) {
			fVec16[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			fVec17[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec56[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec63[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec62[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 16384); l66 = (l66 + 1)) {
			fVec18[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 4096); l67 = (l67 + 1)) {
			fVec19[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec60[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec67[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec66[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 16384); l71 = (l71 + 1)) {
			fVec20[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 4096); l72 = (l72 + 1)) {
			fVec21[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec64[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec71[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec70[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 16384); l76 = (l76 + 1)) {
			fVec22[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2048); l77 = (l77 + 1)) {
			fVec23[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec68[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec32[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec33[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec34[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec35[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec36[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec37[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec38[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec39[l86] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("piano");
		ui_interface->openHorizontalBox("Basic_Parameters");
		ui_interface->declare(&fEntry0, "1", "");
		ui_interface->declare(&fEntry0, "tooltip", "Tone frequency");
		ui_interface->declare(&fEntry0, "unit", "Hz");
		ui_interface->addNumEntry("freq", &fEntry0, 440.0f, 20.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fEntry1, "1", "");
		ui_interface->declare(&fEntry1, "tooltip", "Gain (value between 0 and 1)");
		ui_interface->addNumEntry("gain", &fEntry1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fButton0, "1", "");
		ui_interface->declare(&fButton0, "tooltip", "noteOn = 1, noteOff = 0");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Physical_Parameters");
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "tooltip", "A value between 0 and 1");
		ui_interface->addHorizontalSlider("Brightness_Factor", &fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "tooltip", "A value between 0 and 1");
		ui_interface->addHorizontalSlider("Detuning_Factor", &fHslider3, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "tooltip", "A value between 0 and 1");
		ui_interface->addHorizontalSlider("Hammer_Hardness", &fHslider5, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "tooltip", "A value between 0 and 1");
		ui_interface->addHorizontalSlider("Stiffness_Factor", &fHslider2, 0.280000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Reverb");
		ui_interface->addHorizontalSlider("reverbGain", &fHslider1, 0.136999995f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("roomSize", &fHslider6, 0.720000029f, 0.00999999978f, 2.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Spat");
		ui_interface->addHorizontalSlider("pan angle", &fHslider0, 0.600000024f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("spatial width", &fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (12.0f * (1.0f - fSlow0));
		float fSlow2 = (0.00100000005f * float(fHslider1));
		float fSlow3 = float(fEntry0);
		int iSlow4 = int(((17.3123398f * (std::log(fSlow3) + -6.08677483f)) + 69.5f));
		float fSlow5 = float(getValueEQBandWidthFactor(float(iSlow4)));
		float fSlow6 = (fConst1 * (mydsp_faustpower2_f(fSlow3) * mydsp_faustpower2_f(fSlow5)));
		float fSlow7 = (0.5f * (1.0f - fSlow6));
		float fSlow8 = float(getValueEQGain(float(iSlow4)));
		float fSlow9 = float(fHslider2);
		float fSlow10 = float(getValueStiffnessCoefficient(float(iSlow4)));
		float fSlow11 = (13.6899996f * (mydsp_faustpower2_f(fSlow9) * mydsp_faustpower2_f(fSlow10)));
		float fSlow12 = (fSlow11 + -1.0f);
		float fSlow13 = (5.0f * (float(fHslider3) * float(getValueDetuningHz(float(iSlow4)))));
		float fSlow14 = (fSlow3 + fSlow13);
		float fSlow15 = (fConst3 * fSlow14);
		float fSlow16 = std::sin(fSlow15);
		float fSlow17 = (fSlow9 * fSlow10);
		float fSlow18 = (7.4000001f * fSlow17);
		float fSlow19 = (fSlow11 + 1.0f);
		float fSlow20 = std::cos(fSlow15);
		float fSlow21 = (3.0f * std::atan2((fSlow12 * fSlow16), (fSlow18 + (fSlow19 * fSlow20))));
		float fSlow22 = std::pow(10.0f, (0.0500000007f * (float(getValueSingleStringDecayRate(float(iSlow4))) / fSlow3)));
		float fSlow23 = float(getValueSingleStringZero(float(iSlow4)));
		float fSlow24 = float(getValueSingleStringPole(float(iSlow4)));
		float fSlow25 = (1.0f - fSlow24);
		float fSlow26 = ((fSlow22 * fSlow23) * fSlow25);
		float fSlow27 = (1.0f - fSlow23);
		float fSlow28 = (fSlow24 * fSlow27);
		float fSlow29 = (3.0f * fSlow28);
		float fSlow30 = (fSlow26 - fSlow29);
		float fSlow31 = (fSlow22 * fSlow25);
		float fSlow32 = ((3.0f * fSlow27) - fSlow31);
		float fSlow33 = (((fSlow20 * fSlow30) / fSlow32) + 1.0f);
		float fSlow34 = (fSlow28 - fSlow26);
		float fSlow35 = (4.0f * fSlow34);
		float fSlow36 = (fSlow35 + fSlow30);
		float fSlow37 = ((fSlow23 + fSlow31) + -1.0f);
		float fSlow38 = (4.0f * fSlow37);
		float fSlow39 = (((fSlow38 + (fSlow20 * fSlow36)) / fSlow32) + 1.0f);
		float fSlow40 = mydsp_faustpower2_f(fSlow16);
		float fSlow41 = mydsp_faustpower2_f(fSlow32);
		float fSlow42 = (fConst2 * (((fSlow21 + std::atan2(((fSlow33 * (0.0f - ((fSlow16 * fSlow36) / fSlow32))) + (((fSlow16 * fSlow30) * fSlow39) / fSlow32)), ((fSlow33 * fSlow39) + (((fSlow40 * fSlow36) * fSlow30) / fSlow41)))) + 6.28318548f) / fSlow14));
		float fSlow43 = std::floor(fSlow42);
		float fSlow44 = (fSlow42 - fSlow43);
		float fSlow45 = float(fButton0);
		float fSlow46 = (0.0f - (fSlow45 + -1.0f));
		float fSlow47 = (0.00100000005f * ((0.999599993f * fSlow45) + (0.899999976f * (fSlow46 * float(getValueReleaseLoopGain(float(iSlow4)))))));
		float fSlow48 = float(getValueDCBa1(float(iSlow4)));
		float fSlow49 = (1.0f - fSlow48);
		float fSlow50 = (0.5f * fSlow49);
		float fSlow51 = float(getValueLoudPole(float(iSlow4)));
		float fSlow52 = (0.25f * float(fHslider4));
		float fSlow53 = (fSlow51 + (0.0199999996f - fSlow52));
		float fSlow54 = ((fSlow52 + (0.980000019f - fSlow51)) * float(getValueLoudGain(float(iSlow4))));
		float fSlow55 = (1.39698386e-09f * (fSlow54 * float((iSlow4 < 88))));
		float fSlow56 = (fConst4 * fSlow46);
		float fSlow57 = float(fHslider5);
		float fSlow58 = (fConst6 * fSlow57);
		float fSlow59 = std::exp((0.0f - (fConst7 / fSlow57)));
		float fSlow60 = (0.200000003f * float(getValueSustainPedalLevel(float(iSlow4))));
		int iSlow61 = (fSlow45 > 0.0f);
		float fSlow62 = std::exp((0.0f - (fConst8 / (float(getValueDryTapAmpT60(float(iSlow4))) * float(fEntry1)))));
		int iSlow63 = (fSlow45 < 1.0f);
		float fSlow64 = (0.0f - fSlow50);
		float fSlow65 = (3.70000005f * fSlow17);
		float fSlow66 = ((fSlow35 + fSlow26) - fSlow29);
		float fSlow67 = (((fSlow38 + (fSlow20 * fSlow66)) / fSlow32) + 1.0f);
		int iSlow68 = int((fConst2 * (((fSlow21 + std::atan2((0.0f - ((fSlow16 * ((fSlow66 * fSlow33) - (fSlow30 * fSlow67))) / fSlow32)), ((((fSlow40 * fSlow30) * fSlow66) / fSlow41) + (fSlow33 * fSlow67)))) + 6.28318548f) / fSlow14)));
		int iSlow69 = std::min<int>(4097, std::max<int>(0, (iSlow68 + 1)));
		float fSlow70 = (1.0f / fSlow32);
		float fSlow71 = (fSlow3 - fSlow13);
		float fSlow72 = (fConst3 * fSlow71);
		float fSlow73 = std::sin(fSlow72);
		float fSlow74 = std::cos(fSlow72);
		float fSlow75 = (3.0f * std::atan2((fSlow73 * fSlow12), (fSlow18 + (fSlow19 * fSlow74))));
		float fSlow76 = (((fSlow74 * fSlow30) / fSlow32) + 1.0f);
		float fSlow77 = ((((fSlow74 * fSlow36) + fSlow38) / fSlow32) + 1.0f);
		float fSlow78 = mydsp_faustpower2_f(fSlow73);
		float fSlow79 = (fConst2 * (((fSlow75 + std::atan2((((0.0f - ((fSlow73 * fSlow36) / fSlow32)) * fSlow76) + (((fSlow73 * fSlow30) * fSlow77) / fSlow32)), ((fSlow76 * fSlow77) + (((fSlow78 * fSlow36) * fSlow30) / fSlow41)))) + 6.28318548f) / fSlow71));
		float fSlow80 = std::floor(fSlow79);
		float fSlow81 = (fSlow80 + (1.0f - fSlow79));
		float fSlow82 = ((((fSlow74 * fSlow66) + fSlow38) / fSlow32) + 1.0f);
		int iSlow83 = int((fConst2 * (((fSlow75 + std::atan2(((fSlow73 * ((fSlow30 * fSlow82) - (fSlow76 * fSlow66))) / fSlow32), ((fSlow76 * fSlow82) + (((fSlow78 * fSlow30) * fSlow66) / fSlow41)))) + 6.28318548f) / fSlow71)));
		int iSlow84 = std::min<int>(4097, std::max<int>(0, iSlow83));
		float fSlow85 = (fSlow79 - fSlow80);
		int iSlow86 = std::min<int>(4097, std::max<int>(0, (iSlow83 + 1)));
		float fSlow87 = (fSlow43 + (1.0f - fSlow42));
		int iSlow88 = std::min<int>(4097, std::max<int>(0, iSlow68));
		float fSlow89 = (std::cos((fConst3 * (fSlow3 / float(getValueStrikePosition(float(iSlow4)))))) * (0.0f - (fConst9 * (fSlow3 * fSlow5))));
		float fSlow90 = float(getValueBq4_gEarBalled(float(iSlow4)));
		float fSlow91 = (2.0f * fSlow90);
		float fSlow92 = float((iSlow4 >= 88));
		float fSlow93 = (2.32830644e-10f * fSlow92);
		float fSlow94 = (1.16415322e-10f * fSlow92);
		float fSlow95 = std::pow(10.0f, (fConst10 * float(getValuer3db(float(iSlow4)))));
		float fSlow96 = mydsp_faustpower2_f(fSlow95);
		float fSlow97 = (std::cos((fConst3 * (fSlow3 * float(getValueThirdPartialFactor(float(iSlow4)))))) * (0.0f - (2.0f * fSlow95)));
		float fSlow98 = std::pow(10.0f, (fConst10 * float(getValuer2db(float(iSlow4)))));
		float fSlow99 = (std::cos((fConst3 * (fSlow3 * float(getValueSecondPartialFactor(float(iSlow4)))))) * (0.0f - (2.0f * fSlow98)));
		float fSlow100 = mydsp_faustpower2_f(fSlow98);
		float fSlow101 = std::pow(10.0f, (fConst10 * float(getValuer1_1db(float(iSlow4)))));
		float fSlow102 = mydsp_faustpower2_f(fSlow101);
		float fSlow103 = std::cos((fConst3 * fSlow3));
		float fSlow104 = (fSlow103 * (0.0f - (2.0f * fSlow101)));
		float fSlow105 = std::pow(10.0f, (0.0500000007f * float(getValueSecondStageAmpRatio(float(iSlow4)))));
		float fSlow106 = std::pow(10.0f, (fConst10 * float(getValuer1_2db(float(iSlow4)))));
		float fSlow107 = mydsp_faustpower2_f(fSlow106);
		float fSlow108 = (1.0f - fSlow105);
		float fSlow109 = ((fSlow105 * fSlow102) + (fSlow107 * fSlow108));
		float fSlow110 = (0.0f - (2.0f * ((fSlow105 * fSlow101) + (fSlow106 * fSlow108))));
		float fSlow111 = (0.0f - (2.0f * fSlow106));
		float fSlow112 = float(fHslider6);
		float fSlow113 = std::exp((fConst14 / fSlow112));
		float fSlow114 = mydsp_faustpower2_f(fSlow113);
		float fSlow115 = (1.0f - (fConst11 * fSlow114));
		float fSlow116 = (1.0f - fSlow114);
		float fSlow117 = (fSlow115 / fSlow116);
		float fSlow118 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow115) / mydsp_faustpower2_f(fSlow116)) + -1.0f)));
		float fSlow119 = (fSlow117 - fSlow118);
		float fSlow120 = (fSlow113 * (fSlow118 + (1.0f - fSlow117)));
		float fSlow121 = ((std::exp((fConst15 / fSlow112)) / fSlow113) + -1.0f);
		float fSlow122 = (12.0f * fSlow0);
		int iSlow123 = int(std::min<float>(4096.0f, std::max<float>(0.0f, (fConst21 * (float(fHslider7) / fSlow3)))));
		float fSlow124 = std::exp((fConst26 / fSlow112));
		float fSlow125 = mydsp_faustpower2_f(fSlow124);
		float fSlow126 = (1.0f - (fConst11 * fSlow125));
		float fSlow127 = (1.0f - fSlow125);
		float fSlow128 = (fSlow126 / fSlow127);
		float fSlow129 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow126) / mydsp_faustpower2_f(fSlow127)) + -1.0f)));
		float fSlow130 = (fSlow128 - fSlow129);
		float fSlow131 = (fSlow124 * (fSlow129 + (1.0f - fSlow128)));
		float fSlow132 = ((std::exp((fConst27 / fSlow112)) / fSlow124) + -1.0f);
		float fSlow133 = std::exp((fConst33 / fSlow112));
		float fSlow134 = mydsp_faustpower2_f(fSlow133);
		float fSlow135 = (1.0f - (fConst11 * fSlow134));
		float fSlow136 = (1.0f - fSlow134);
		float fSlow137 = (fSlow135 / fSlow136);
		float fSlow138 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow135) / mydsp_faustpower2_f(fSlow136)) + -1.0f)));
		float fSlow139 = (fSlow137 - fSlow138);
		float fSlow140 = (fSlow133 * (fSlow138 + (1.0f - fSlow137)));
		float fSlow141 = ((std::exp((fConst34 / fSlow112)) / fSlow133) + -1.0f);
		float fSlow142 = std::exp((fConst40 / fSlow112));
		float fSlow143 = mydsp_faustpower2_f(fSlow142);
		float fSlow144 = (1.0f - (fConst11 * fSlow143));
		float fSlow145 = (1.0f - fSlow143);
		float fSlow146 = (fSlow144 / fSlow145);
		float fSlow147 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow144) / mydsp_faustpower2_f(fSlow145)) + -1.0f)));
		float fSlow148 = (fSlow146 - fSlow147);
		float fSlow149 = (fSlow142 * (fSlow147 + (1.0f - fSlow146)));
		float fSlow150 = ((std::exp((fConst41 / fSlow112)) / fSlow142) + -1.0f);
		float fSlow151 = std::exp((fConst47 / fSlow112));
		float fSlow152 = mydsp_faustpower2_f(fSlow151);
		float fSlow153 = (1.0f - (fConst11 * fSlow152));
		float fSlow154 = (1.0f - fSlow152);
		float fSlow155 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow153) / mydsp_faustpower2_f(fSlow154)) + -1.0f)));
		float fSlow156 = (fSlow153 / fSlow154);
		float fSlow157 = (fSlow151 * (fSlow155 + (1.0f - fSlow156)));
		float fSlow158 = ((std::exp((fConst48 / fSlow112)) / fSlow151) + -1.0f);
		float fSlow159 = (fSlow156 - fSlow155);
		float fSlow160 = std::exp((fConst54 / fSlow112));
		float fSlow161 = mydsp_faustpower2_f(fSlow160);
		float fSlow162 = (1.0f - (fConst11 * fSlow161));
		float fSlow163 = (1.0f - fSlow161);
		float fSlow164 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow162) / mydsp_faustpower2_f(fSlow163)) + -1.0f)));
		float fSlow165 = (fSlow162 / fSlow163);
		float fSlow166 = (fSlow160 * (fSlow164 + (1.0f - fSlow165)));
		float fSlow167 = ((std::exp((fConst55 / fSlow112)) / fSlow160) + -1.0f);
		float fSlow168 = (fSlow165 - fSlow164);
		float fSlow169 = std::exp((fConst61 / fSlow112));
		float fSlow170 = mydsp_faustpower2_f(fSlow169);
		float fSlow171 = (1.0f - (fConst11 * fSlow170));
		float fSlow172 = (1.0f - fSlow170);
		float fSlow173 = (fSlow171 / fSlow172);
		float fSlow174 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow171) / mydsp_faustpower2_f(fSlow172)) + -1.0f)));
		float fSlow175 = (fSlow173 - fSlow174);
		float fSlow176 = (fSlow169 * (fSlow174 + (1.0f - fSlow173)));
		float fSlow177 = ((std::exp((fConst62 / fSlow112)) / fSlow169) + -1.0f);
		float fSlow178 = std::exp((fConst68 / fSlow112));
		float fSlow179 = mydsp_faustpower2_f(fSlow178);
		float fSlow180 = (1.0f - (fConst11 * fSlow179));
		float fSlow181 = (1.0f - fSlow179);
		float fSlow182 = std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow180) / mydsp_faustpower2_f(fSlow181)) + -1.0f)));
		float fSlow183 = (fSlow180 / fSlow181);
		float fSlow184 = (fSlow178 * (fSlow182 + (1.0f - fSlow183)));
		float fSlow185 = ((std::exp((fConst69 / fSlow112)) / fSlow178) + -1.0f);
		float fSlow186 = (fSlow183 - fSlow182);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow2 + (0.999000013f * fRec0[1]));
			float fTemp0 = (1.0f - fRec0[0]);
			fRec8[0] = (fSlow47 + (0.999000013f * fRec8[1]));
			iRec14[0] = (((1103515245 * iRec14[1]) & 2147483647) + 12345);
			fRec16[0] = ((fSlow45 * fRec16[1]) + 1.0f);
			float fTemp1 = (fRec16[0] + -1.0f);
			int iTemp2 = (fTemp1 < fSlow58);
			float fTemp3 = (fSlow45 * ((fConst5 * float((fTemp1 >= fSlow58))) + (fSlow59 * float(iTemp2))));
			fRec15[0] = (((fSlow56 + fTemp3) * fRec15[1]) + (fSlow60 * (((1.0f - fTemp3) - fSlow56) * float((iTemp2 & iSlow61)))));
			float fTemp4 = float(((fTemp1 < 2.0f) & iSlow61));
			float fTemp5 = ((0.0301973838f * fTemp4) + (fSlow62 * float(((fTemp1 >= 2.0f) | iSlow63))));
			fRec17[0] = ((fRec17[1] * fTemp5) + (0.150000006f * ((1.0f - fTemp5) * fTemp4)));
			float fTemp6 = (float(iRec14[0]) * (fRec15[0] + fRec17[0]));
			fRec13[0] = ((fSlow53 * fRec13[1]) + (fSlow55 * fTemp6));
			fRec12[0] = ((fSlow54 * fRec13[0]) + (fSlow53 * fRec12[1]));
			fRec11[0] = ((fSlow53 * fRec11[1]) + (fSlow54 * fRec12[0]));
			fRec10[0] = ((fSlow53 * fRec10[1]) + (fSlow54 * fRec11[0]));
			fRec9[0] = (((fSlow50 * fRec10[0]) + (fSlow64 * fRec10[1])) - (fSlow48 * fRec9[1]));
			float fTemp7 = (fRec8[0] * (fRec9[0] + fRec2[1]));
			fVec0[0] = fTemp7;
			fRec7[0] = (fVec0[1] + (fSlow65 * (fTemp7 - fRec7[1])));
			fRec6[0] = (fRec7[1] - (fSlow65 * (fRec6[1] - fRec7[0])));
			fRec5[(IOTA & 8191)] = (fRec6[1] - (fSlow65 * (fRec5[((IOTA - 1) & 8191)] - fRec6[0])));
			float fTemp8 = (fSlow44 * fRec5[((IOTA - iSlow69) & 8191)]);
			float fTemp9 = (fRec9[0] + (fRec8[0] * fRec3[1]));
			fVec1[0] = fTemp9;
			fRec21[0] = (fVec1[1] + (fSlow65 * (fTemp9 - fRec21[1])));
			fRec20[0] = (fRec21[1] - (fSlow65 * (fRec20[1] - fRec21[0])));
			fRec19[(IOTA & 8191)] = (fRec20[1] + (fSlow65 * (fRec20[0] - fRec19[((IOTA - 1) & 8191)])));
			float fTemp10 = (fSlow81 * fRec19[((IOTA - iSlow84) & 8191)]);
			float fTemp11 = (fSlow85 * fRec19[((IOTA - iSlow86) & 8191)]);
			float fTemp12 = (fSlow87 * fRec5[((IOTA - iSlow88) & 8191)]);
			float fTemp13 = (((fTemp10 + fTemp11) + fTemp12) + fTemp8);
			fVec2[0] = fTemp13;
			fRec18[0] = (fSlow70 * ((2.0f * ((fSlow37 * fTemp13) + (fSlow34 * fVec2[1]))) - (fSlow30 * fRec18[1])));
			fRec2[0] = (fTemp8 + (fRec18[0] + fTemp12));
			fRec3[0] = (fTemp11 + (fRec18[0] + fTemp10));
			float fRec4 = fTemp13;
			fRec1[0] = ((fSlow8 * fRec4) - ((fSlow89 * fRec1[1]) + (fSlow6 * fRec1[2])));
			fVec3[0] = (fSlow93 * fTemp6);
			float fTemp14 = (0.0f - ((0.5f * fVec3[1]) + (fSlow94 * fTemp6)));
			fVec4[0] = fTemp14;
			fRec31[0] = (((fSlow50 * fTemp14) + (fSlow64 * fVec4[1])) - (fSlow48 * fRec31[1]));
			fRec30[0] = ((fSlow54 * fRec31[0]) + (fSlow53 * fRec30[1]));
			fRec29[0] = ((fSlow54 * fRec30[0]) + (fSlow53 * fRec29[1]));
			fRec28[0] = ((fSlow54 * fRec29[0]) + (fSlow53 * fRec28[1]));
			fRec27[0] = ((fSlow54 * fRec28[0]) + (fSlow53 * fRec27[1]));
			fRec26[0] = ((fSlow90 * (fRec27[0] - fRec27[1])) - ((fSlow96 * fRec26[2]) + (fSlow97 * fRec26[1])));
			fRec25[0] = ((fSlow91 * fRec26[0]) - ((fSlow99 * fRec25[1]) + (fSlow100 * fRec25[2])));
			fRec24[0] = (fRec25[0] - ((fSlow102 * fRec24[2]) + (fSlow104 * fRec24[1])));
			fRec23[0] = (((fRec24[0] + (fSlow109 * fRec24[2])) + (fSlow103 * ((fSlow110 * fRec24[1]) - (fSlow111 * fRec23[1])))) - (fSlow107 * fRec23[2]));
			fRec22[0] = ((fSlow49 * fRec23[0]) - (fSlow48 * fRec22[1]));
			float fTemp15 = ((fSlow7 * (fRec1[0] - fRec1[2])) + (fRec4 + fRec22[0]));
			fVec5[(IOTA & 8191)] = fTemp15;
			fRec43[0] = (0.0f - (fConst17 * ((fConst18 * fRec43[1]) - (fRec39[2] + fRec39[1]))));
			fRec42[0] = ((fSlow119 * fRec42[1]) + (fSlow120 * (fRec39[1] + (fSlow121 * fRec43[0]))));
			fVec6[(IOTA & 32767)] = ((0.353553385f * fRec42[0]) + 9.99999968e-21f);
			float fTemp16 = fVec5[((IOTA - iSlow123) & 8191)];
			fVec7[(IOTA & 4095)] = (fSlow122 * (fRec0[0] * fTemp16));
			float fTemp17 = (0.300000012f * fVec7[((IOTA - iConst22) & 4095)]);
			float fTemp18 = (((0.600000024f * fRec40[1]) + fVec6[((IOTA - iConst20) & 32767)]) - fTemp17);
			fVec8[(IOTA & 2047)] = fTemp18;
			fRec40[0] = fVec8[((IOTA - iConst23) & 2047)];
			float fRec41 = (0.0f - (0.600000024f * fTemp18));
			fRec47[0] = (0.0f - (fConst17 * ((fConst18 * fRec47[1]) - (fRec35[2] + fRec35[1]))));
			fRec46[0] = ((fSlow130 * fRec46[1]) + (fSlow131 * (fRec35[1] + (fSlow132 * fRec47[0]))));
			fVec9[(IOTA & 32767)] = ((0.353553385f * fRec46[0]) + 9.99999968e-21f);
			float fTemp19 = (((0.600000024f * fRec44[1]) + fVec9[((IOTA - iConst29) & 32767)]) - fTemp17);
			fVec10[(IOTA & 4095)] = fTemp19;
			fRec44[0] = fVec10[((IOTA - iConst30) & 4095)];
			float fRec45 = (0.0f - (0.600000024f * fTemp19));
			fRec51[0] = (fConst17 * ((fRec37[2] + fRec37[1]) - (fConst18 * fRec51[1])));
			fRec50[0] = ((fSlow139 * fRec50[1]) + (fSlow140 * (fRec37[1] + (fSlow141 * fRec51[0]))));
			fVec11[(IOTA & 16383)] = ((0.353553385f * fRec50[0]) + 9.99999968e-21f);
			float fTemp20 = ((fTemp17 + (0.600000024f * fRec48[1])) + fVec11[((IOTA - iConst36) & 16383)]);
			fVec12[(IOTA & 4095)] = fTemp20;
			fRec48[0] = fVec12[((IOTA - iConst37) & 4095)];
			float fRec49 = (0.0f - (0.600000024f * fTemp20));
			fRec55[0] = (0.0f - (fConst17 * ((fConst18 * fRec55[1]) - (fRec33[1] + fRec33[2]))));
			fRec54[0] = ((fSlow148 * fRec54[1]) + (fSlow149 * (fRec33[1] + (fSlow150 * fRec55[0]))));
			fVec13[(IOTA & 32767)] = ((0.353553385f * fRec54[0]) + 9.99999968e-21f);
			float fTemp21 = (((0.600000024f * fRec52[1]) + fTemp17) + fVec13[((IOTA - iConst43) & 32767)]);
			fVec14[(IOTA & 4095)] = fTemp21;
			fRec52[0] = fVec14[((IOTA - iConst44) & 4095)];
			float fRec53 = (0.0f - (0.600000024f * fTemp21));
			fRec59[0] = (fConst17 * ((fRec38[2] + fRec38[1]) - (fConst18 * fRec59[1])));
			fRec58[0] = ((fSlow157 * ((fSlow158 * fRec59[0]) + fRec38[1])) + (fSlow159 * fRec58[1]));
			fVec15[(IOTA & 16383)] = ((0.353553385f * fRec58[0]) + 9.99999968e-21f);
			fVec16[(IOTA & 4095)] = (fSlow1 * (fRec0[0] * fTemp15));
			float fTemp22 = (0.300000012f * fVec16[((IOTA - iConst22) & 4095)]);
			float fTemp23 = (fVec15[((IOTA - iConst50) & 16383)] - (fTemp22 + (0.600000024f * fRec56[1])));
			fVec17[(IOTA & 2047)] = fTemp23;
			fRec56[0] = fVec17[((IOTA - iConst51) & 2047)];
			float fRec57 = (0.600000024f * fTemp23);
			fRec63[0] = (0.0f - (fConst17 * ((fConst18 * fRec63[1]) - (fRec34[2] + fRec34[1]))));
			fRec62[0] = ((fSlow166 * ((fSlow167 * fRec63[0]) + fRec34[1])) + (fSlow168 * fRec62[1]));
			fVec18[(IOTA & 16383)] = ((0.353553385f * fRec62[0]) + 9.99999968e-21f);
			float fTemp24 = (fVec18[((IOTA - iConst57) & 16383)] - (fTemp22 + (0.600000024f * fRec60[1])));
			fVec19[(IOTA & 4095)] = fTemp24;
			fRec60[0] = fVec19[((IOTA - iConst58) & 4095)];
			float fRec61 = (0.600000024f * fTemp24);
			fRec67[0] = (0.0f - (fConst17 * ((fConst18 * fRec67[1]) - (fRec36[1] + fRec36[2]))));
			fRec66[0] = ((fSlow175 * fRec66[1]) + (fSlow176 * (fRec36[1] + (fSlow177 * fRec67[0]))));
			fVec20[(IOTA & 16383)] = ((0.353553385f * fRec66[0]) + 9.99999968e-21f);
			float fTemp25 = ((fTemp22 + fVec20[((IOTA - iConst64) & 16383)]) - (0.600000024f * fRec64[1]));
			fVec21[(IOTA & 4095)] = fTemp25;
			fRec64[0] = fVec21[((IOTA - iConst65) & 4095)];
			float fRec65 = (0.600000024f * fTemp25);
			fRec71[0] = (fConst17 * ((fRec32[1] + fRec32[2]) - (fConst18 * fRec71[1])));
			fRec70[0] = ((fSlow184 * ((fSlow185 * fRec71[0]) + fRec32[1])) + (fSlow186 * fRec70[1]));
			fVec22[(IOTA & 16383)] = ((0.353553385f * fRec70[0]) + 9.99999968e-21f);
			float fTemp26 = ((fVec22[((IOTA - iConst71) & 16383)] + fTemp22) - (0.600000024f * fRec68[1]));
			fVec23[(IOTA & 2047)] = fTemp26;
			fRec68[0] = fVec23[((IOTA - iConst72) & 2047)];
			float fRec69 = (0.600000024f * fTemp26);
			float fTemp27 = (fRec69 + fRec65);
			float fTemp28 = (fRec57 + (fRec61 + fTemp27));
			fRec32[0] = (fRec40[1] + (fRec44[1] + (fRec48[1] + (fRec52[1] + (fRec56[1] + (fRec60[1] + (fRec64[1] + (fRec68[1] + (fRec41 + (fRec45 + (fRec49 + (fRec53 + fTemp28))))))))))));
			fRec33[0] = ((fRec56[1] + (fRec60[1] + (fRec64[1] + (fRec68[1] + fTemp28)))) - (fRec40[1] + (fRec44[1] + (fRec48[1] + (fRec52[1] + (fRec41 + (fRec45 + (fRec53 + fRec49))))))));
			float fTemp29 = (fRec61 + fRec57);
			fRec34[0] = ((fRec48[1] + (fRec52[1] + (fRec64[1] + (fRec68[1] + (fRec49 + (fRec53 + fTemp27)))))) - (fRec40[1] + (fRec44[1] + (fRec56[1] + (fRec60[1] + (fRec41 + (fRec45 + fTemp29)))))));
			fRec35[0] = ((fRec40[1] + (fRec44[1] + (fRec64[1] + (fRec68[1] + (fRec41 + (fRec45 + fTemp27)))))) - (fRec48[1] + (fRec52[1] + (fRec56[1] + (fRec60[1] + (fRec49 + (fRec53 + fTemp29)))))));
			float fTemp30 = (fRec69 + fRec61);
			float fTemp31 = (fRec65 + fRec57);
			fRec36[0] = ((fRec44[1] + (fRec52[1] + (fRec60[1] + (fRec68[1] + (fRec45 + (fRec53 + fTemp30)))))) - (fRec40[1] + (fRec48[1] + (fRec56[1] + (fRec64[1] + (fRec41 + (fRec49 + fTemp31)))))));
			fRec37[0] = ((fRec40[1] + (fRec48[1] + (fRec60[1] + (fRec68[1] + (fRec41 + (fRec49 + fTemp30)))))) - (fRec44[1] + (fRec52[1] + (fRec56[1] + (fRec64[1] + (fRec45 + (fRec53 + fTemp31)))))));
			float fTemp32 = (fRec69 + fRec57);
			float fTemp33 = (fRec65 + fRec61);
			fRec38[0] = ((fRec40[1] + (fRec52[1] + (fRec56[1] + (fRec68[1] + (fRec41 + (fRec53 + fTemp32)))))) - (fRec44[1] + (fRec48[1] + (fRec60[1] + (fRec64[1] + (fRec45 + (fRec49 + fTemp33)))))));
			fRec39[0] = ((fRec44[1] + (fRec48[1] + (fRec56[1] + (fRec68[1] + (fRec45 + (fRec49 + fTemp32)))))) - (fRec40[1] + (fRec52[1] + (fRec60[1] + (fRec64[1] + (fRec41 + (fRec53 + fTemp33)))))));
			output0[i] = FAUSTFLOAT(((fSlow1 * (fTemp0 * fTemp15)) + (0.370000005f * (fRec34[0] + fRec33[0]))));
			output1[i] = FAUSTFLOAT(((fSlow122 * (fTemp0 * fTemp16)) + (0.370000005f * (fRec33[0] - fRec34[0]))));
			fRec0[1] = fRec0[0];
			fRec8[1] = fRec8[0];
			iRec14[1] = iRec14[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fVec0[1] = fVec0[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			IOTA = (IOTA + 1);
			fVec1[1] = fVec1[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fVec2[1] = fVec2[0];
			fRec18[1] = fRec18[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec40[1] = fRec40[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec44[1] = fRec44[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec48[1] = fRec48[0];
			fRec55[1] = fRec55[0];
			fRec54[1] = fRec54[0];
			fRec52[1] = fRec52[0];
			fRec59[1] = fRec59[0];
			fRec58[1] = fRec58[0];
			fRec56[1] = fRec56[0];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
			fRec60[1] = fRec60[0];
			fRec67[1] = fRec67[0];
			fRec66[1] = fRec66[0];
			fRec64[1] = fRec64[0];
			fRec71[1] = fRec71[0];
			fRec70[1] = fRec70[0];
			fRec68[1] = fRec68[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			
		}
		
	}

	
};

#include <stdio.h>
#include <string>
#include "m_pd.h"

#define sym(name) xsym(name)
#define xsym(name) #name
#define faust_setup(name) xfaust_setup(name)
#define xfaust_setup(name) name ## _tilde_setup(void)

// time for "active" toggle xfades in secs
#define XFADE_TIME 0.1f

static t_class *faust_class;

struct t_faust {
  t_object x_obj;
#ifdef __MINGW32__
  /* This seems to be necessary as some as yet undetermined Pd routine seems
     to write past the end of x_obj on Windows. */
  int fence; /* dummy field (not used) */
#endif
  mydsp *dsp;
  PdUI *ui;
  std::string *label;
  int active, xfade, n_xfade, rate, n_in, n_out;
  t_sample **inputs, **outputs, **buf;
  t_outlet *out;
  t_sample f;
};

static t_symbol *s_button, *s_checkbox, *s_vslider, *s_hslider, *s_nentry,
  *s_vbargraph, *s_hbargraph;

static inline void zero_samples(int k, int n, t_sample **out)
{
  for (int i = 0; i < k; i++)
#ifdef __STDC_IEC_559__
    /* IEC 559 a.k.a. IEEE 754 floats can be initialized faster like this */
    memset(out[i], 0, n*sizeof(t_sample));
#else
    for (int j = 0; j < n; j++)
      out[i][j] = 0.0f;
#endif
}

static inline void copy_samples(int k, int n, t_sample **out, t_sample **in)
{
  for (int i = 0; i < k; i++)
    memcpy(out[i], in[i], n*sizeof(t_sample));
}

static t_int *faust_perform(t_int *w)
{
  t_faust *x = (t_faust *)(w[1]);
  int n = (int)(w[2]);
  if (!x->dsp || !x->buf) return (w+3);
  AVOIDDENORMALS;
  if (x->xfade > 0) {
    float d = 1.0f/x->n_xfade, f = (x->xfade--)*d;
    d = d/n;
    x->dsp->compute(n, x->inputs, x->buf);
    if (x->active)
      if (x->n_in == x->n_out)
	/* xfade inputs -> buf */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->inputs[i][j]+(1.0f-f)*x->buf[i][j];
      else
	/* xfade 0 -> buf */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = (1.0f-f)*x->buf[i][j];
    else
      if (x->n_in == x->n_out)
	/* xfade buf -> inputs */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->buf[i][j]+(1.0f-f)*x->inputs[i][j];
      else
	/* xfade buf -> 0 */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->buf[i][j];
  } else if (x->active) {
    x->dsp->compute(n, x->inputs, x->buf);
    copy_samples(x->n_out, n, x->outputs, x->buf);
  } else if (x->n_in == x->n_out) {
    copy_samples(x->n_out, n, x->buf, x->inputs);
    copy_samples(x->n_out, n, x->outputs, x->buf);
  } else
    zero_samples(x->n_out, n, x->outputs);
  return (w+3);
}

static void faust_dsp(t_faust *x, t_signal **sp)
{
  int n = sp[0]->s_n, sr = (int)sp[0]->s_sr;
  if (x->rate <= 0) {
    /* default sample rate is whatever Pd tells us */
    PdUI *ui = x->ui;
    float *z = NULL;
    if (ui->nelems > 0 &&
	(z = (float*)malloc(ui->nelems*sizeof(float)))) {
      /* save the current control values */
      for (int i = 0; i < ui->nelems; i++)
	if (ui->elems[i].zone)
	  z[i] = *ui->elems[i].zone;
    }
    /* set the proper sample rate; this requires reinitializing the dsp */
    x->rate = sr;
    x->dsp->init(sr);
    if (z) {
      /* restore previous control values */
      for (int i = 0; i < ui->nelems; i++)
	if (ui->elems[i].zone)
	  *ui->elems[i].zone = z[i];
      free(z);
    }
  }
  if (n > 0)
    x->n_xfade = (int)(x->rate*XFADE_TIME/n);
  dsp_add(faust_perform, 2, x, n);
  for (int i = 0; i < x->n_in; i++)
    x->inputs[i] = sp[i+1]->s_vec;
  for (int i = 0; i < x->n_out; i++)
    x->outputs[i] = sp[x->n_in+i+1]->s_vec;
  if (x->buf != NULL)
    for (int i = 0; i < x->n_out; i++) {
      x->buf[i] = (t_sample*)malloc(n*sizeof(t_sample));
      if (x->buf[i] == NULL) {
	for (int j = 0; j < i; j++)
	  free(x->buf[j]);
	free(x->buf);
	x->buf = NULL;
	break;
      }
    }
}

static int pathcmp(const char *s, const char *t)
{
  int n = strlen(s), m = strlen(t);
  if (n == 0 || m == 0)
    return 0;
  else if (t[0] == '/')
    return strcmp(s, t);
  else if (n <= m || s[n-m-1] != '/')
    return strcmp(s+1, t);
  else
    return strcmp(s+n-m, t);
}

static void faust_any(t_faust *x, t_symbol *s, int argc, t_atom *argv)
{
  if (!x->dsp) return;
  PdUI *ui = x->ui;
  if (s == &s_bang) {
    for (int i = 0; i < ui->nelems; i++)
      if (ui->elems[i].label && ui->elems[i].zone) {
	t_atom args[6];
	t_symbol *_s;
	switch (ui->elems[i].type) {
	case UI_BUTTON:
	  _s = s_button;
	  break;
	case UI_CHECK_BUTTON:
	  _s = s_checkbox;
	  break;
	case UI_V_SLIDER:
	  _s = s_vslider;
	  break;
	case UI_H_SLIDER:
	  _s = s_hslider;
	  break;
	case UI_NUM_ENTRY:
	  _s = s_nentry;
	  break;
	case UI_V_BARGRAPH:
	  _s = s_vbargraph;
	  break;
	case UI_H_BARGRAPH:
	  _s = s_hbargraph;
	  break;
	default:
	  continue;
	}
	SETSYMBOL(&args[0], gensym(ui->elems[i].label));
	SETFLOAT(&args[1], *ui->elems[i].zone);
	SETFLOAT(&args[2], ui->elems[i].init);
	SETFLOAT(&args[3], ui->elems[i].min);
	SETFLOAT(&args[4], ui->elems[i].max);
	SETFLOAT(&args[5], ui->elems[i].step);
	outlet_anything(x->out, _s, 6, args);
      }
  } else {
    const char *label = s->s_name;
    int count = 0;
    for (int i = 0; i < ui->nelems; i++)
      if (ui->elems[i].label &&
	  pathcmp(ui->elems[i].label, label) == 0) {
	if (argc == 0) {
	  if (ui->elems[i].zone) {
	    t_atom arg;
	    SETFLOAT(&arg, *ui->elems[i].zone);
	    outlet_anything(x->out, gensym(ui->elems[i].label), 1, &arg);
	  }
	  ++count;
	} else if (argc == 1 &&
		   (argv[0].a_type == A_FLOAT ||
		    argv[0].a_type == A_DEFFLOAT) &&
		   ui->elems[i].zone) {
	  float f = atom_getfloat(argv);
	  *ui->elems[i].zone = f;
	  ++count;
	} else
	  pd_error(x, "[faust] %s: bad control argument: %s",
		   x->label->c_str(), label);
      }
    if (count == 0 && strcmp(label, "active") == 0) {
      if (argc == 0) {
	t_atom arg;
	SETFLOAT(&arg, (float)x->active);
	outlet_anything(x->out, gensym((char*)"active"), 1, &arg);
      } else if (argc == 1 &&
		 (argv[0].a_type == A_FLOAT ||
		  argv[0].a_type == A_DEFFLOAT)) {
	float f = atom_getfloat(argv);
	x->active = (int)f;
	x->xfade = x->n_xfade;
      }
    }
  }
}

static void faust_free(t_faust *x)
{
  if (x->label) delete x->label;
  if (x->dsp) delete x->dsp;
  if (x->ui) delete x->ui;
  if (x->inputs) free(x->inputs);
  if (x->outputs) free(x->outputs);
  if (x->buf) {
    for (int i = 0; i < x->n_out; i++)
      if (x->buf[i]) free(x->buf[i]);
    free(x->buf);
  }
}

static void *faust_new(t_symbol *s, int argc, t_atom *argv)
{
  t_faust *x = (t_faust*)pd_new(faust_class);
  int sr = -1;
  t_symbol *id = NULL;
  x->active = 1;
  for (int i = 0; i < argc; i++)
    if (argv[i].a_type == A_FLOAT || argv[i].a_type == A_DEFFLOAT)
      sr = (int)argv[i].a_w.w_float;
    else if (argv[i].a_type == A_SYMBOL || argv[i].a_type == A_DEFSYMBOL)
      id = argv[i].a_w.w_symbol;
  x->rate = sr;
  if (sr <= 0) sr = 44100;
  x->xfade = 0; x->n_xfade = (int)(sr*XFADE_TIME/64);
  x->inputs = x->outputs = x->buf = NULL;
    x->label = new std::string(sym(mydsp) "~");
  x->dsp = new mydsp();
  x->ui = new PdUI(sym(mydsp), id?id->s_name:NULL);
  if (!x->dsp || !x->ui || !x->label) goto error;
  if (id) {
    *x->label += " ";
    *x->label += id->s_name;
  }
  x->n_in = x->dsp->getNumInputs();
  x->n_out = x->dsp->getNumOutputs();
  if (x->n_in > 0)
    x->inputs = (t_sample**)malloc(x->n_in*sizeof(t_sample*));
  if (x->n_out > 0) {
    x->outputs = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
    x->buf = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
  }
  if ((x->n_in > 0 && x->inputs == NULL) ||
      (x->n_out > 0 && (x->outputs == NULL || x->buf == NULL)))
    goto error;
  for (int i = 0; i < x->n_out; i++)
    x->buf[i] = NULL;
  x->dsp->init(sr);
  x->dsp->buildUserInterface(x->ui);
  for (int i = 0; i < x->n_in; i++)
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  x->out = outlet_new(&x->x_obj, 0);
  for (int i = 0; i < x->n_out; i++)
    outlet_new(&x->x_obj, &s_signal);
  return (void *)x;
 error:
  faust_free(x);
  x->dsp = NULL; x->ui = NULL;
  x->inputs = x->outputs = x->buf = NULL;
  return (void *)x;
}

extern "C" void faust_setup(mydsp)
{
  t_symbol *s = gensym(sym(mydsp) "~");
  faust_class =
    class_new(s, (t_newmethod)faust_new, (t_method)faust_free,
	      sizeof(t_faust), CLASS_DEFAULT,
	      A_GIMME, A_NULL);
  class_addmethod(faust_class, (t_method)faust_dsp, gensym((char*)"dsp"), A_NULL);
  class_addanything(faust_class, faust_any);
  class_addmethod(faust_class, nullfn, &s_signal, A_NULL);
  s_button = gensym((char*)"button");
  s_checkbox = gensym((char*)"checkbox");
  s_vslider = gensym((char*)"vslider");
  s_hslider = gensym((char*)"hslider");
  s_nentry = gensym((char*)"nentry");
  s_vbargraph = gensym((char*)"vbargraph");
  s_hbargraph = gensym((char*)"hbargraph");
  /* give some indication that we're loaded and ready to go */
  mydsp dsp = mydsp();
  post("[faust] %s: %d inputs, %d outputs", sym(mydsp) "~",
       dsp.getNumInputs(), dsp.getNumOutputs());
}

#endif
