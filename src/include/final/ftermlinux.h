/***********************************************************************
* ftermlinux.h - Contains the Linux terminal functions                 *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2018-2019 Markus Gans                                      *
*                                                                      *
* The Final Cut is free software; you can redistribute it and/or       *
* modify it under the terms of the GNU Lesser General Public License   *
* as published by the Free Software Foundation; either version 3 of    *
* the License, or (at your option) any later version.                  *
*                                                                      *
* The Final Cut is distributed in the hope that it will be useful,     *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU Lesser General Public License for more details.                  *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

/*  Standalone class
 *  ════════════════
 *
 * ▕▔▔▔▔▔▔▔▔▔▔▔▔▏
 * ▕ FTermLinux ▏
 * ▕▁▁▁▁▁▁▁▁▁▁▁▁▏
 */

#ifndef FTERMLINUX_H
#define FTERMLINUX_H

#if !defined (USE_FINAL_H) && !defined (COMPILE_FINAL_CUT)
  #error "Only <final/final.h> can be included directly."
#endif

#if defined(__linux__)
  #include <linux/fb.h>        // Linux framebuffer console

  #if defined(__x86_64__) || defined(__i386) || defined(__arm__)
    #include <sys/io.h>        // <asm/io.h> is deprecated
  #endif  // defined(__x86_64__) || defined(__i386) || defined(__arm__)

  #include <sys/kd.h>
#endif  // defined(__linux__)

#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdio>  // need for sprintf
#include <cstring>

#include "final/ftermdata.h"

namespace finalcut
{

// class forward declaration
class FSystem;
class FTermData;
class FTermDetection;

//----------------------------------------------------------------------
// class FTermLinux
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FTermLinux final
{
  public:
    // Typedef
    typedef fc::linuxConsoleCursorStyle  CursorStyle;

    // Constructors
    FTermLinux() = default;

    // Disable copy constructor
    FTermLinux (const FTermLinux&) = delete;

    // Destructor
    virtual ~FTermLinux();

    // Disable assignment operator (=)
    FTermLinux& operator = (const FTermLinux&) = delete;

    // Accessors
    const char*          getClassName() const;
    static fc::linuxConsoleCursorStyle getCursorStyle();
    static char*         getCursorStyleString();
    static int           getFramebufferBpp();

    // Mutators
    static bool          setCursorStyle (CursorStyle);
    static bool          setPalette (FColor, int, int, int);
    static void          setUTF8 (bool);

    // Inquiries
    static bool          isLinuxConsole();
    static bool          isVGAFontUsed();
    static bool          isNewFontUsed();

    // Methods
    static void          init();
    static void          initCharMap();
    static void          finish();
    static bool          loadVGAFont();
    static bool          loadNewFont();
    static bool          loadOldFont();
    static bool          saveColorMap();
    static bool          resetColorMap();
    static void          setBeep (int, int);
    static void          resetBeep();

    static FKey          modifierKeyCorrection (const FKey&);

  private:
    // Typedef
    static struct modifier_key  // bit field
    {
      uChar shift  : 1;  // 0..1
      uChar alt_gr : 1;  // 0..1
      uChar ctrl   : 1;  // 0..1
      uChar alt    : 1;  // 0..1
      uChar        : 4;  // padding bits
    } mod_key;

    typedef struct
    {
      uChar red;
      uChar green;
      uChar blue;
    } rgb;

    typedef struct
    {
      rgb color[16];
    } ColorMap;

    // Accessors
    static int           getFramebuffer_bpp();
    static bool          getScreenFont();
    static bool          getUnicodeMap ();
    static modifier_key& getModifierKey();

    // Mutators
    static int           setScreenFont ( uChar[], uInt, uInt, uInt
                                       , bool = false );
    static int           setUnicodeMap (struct unimapdesc*);
    static void          setLinuxCursorStyle (fc::linuxConsoleCursorStyle);

    // Methods
#if defined(__x86_64__) || defined(__i386) || defined(__arm__)
    static uInt16        getInputStatusRegisterOne();
    static uChar         readAttributeController (uChar);
    static void          writeAttributeController (uChar, uChar);
    static uChar         getAttributeMode();
    static void          setAttributeMode (uChar);
    static int           setBlinkAsIntensity (bool);
    static void          getVGAPalette();
    static void          setVGADefaultPalette();
    static bool          setVGAPalette (FColor, int, int, int);
    static bool          saveVGAPalette();
    static bool          resetVGAPalette();
#endif  // defined(__x86_64__) || defined(__i386) || defined(__arm__)
    static FKey          shiftKeyCorrection (const FKey&);
    static FKey          ctrlKeyCorrection (const FKey&);
    static FKey          altKeyCorrection (const FKey&);
    static FKey          shiftCtrlKeyCorrection (const FKey&);
    static FKey          shiftAltKeyCorrection (const FKey&);
    static FKey          ctrlAltKeyCorrection (const FKey&);
    static FKey          shiftCtrlAltKeyCorrection (const FKey&);
    static sInt16        getFontPos (wchar_t ucs);
    static void          initSpecialCharacter();
    static void          characterFallback (wchar_t, std::vector<wchar_t>);

    // Data Members
#if defined(__linux__)
    static bool                   vga_font;
    static bool                   new_font;
    static bool                   has_saved_palette;
    static FTermData*             fterm_data;
    static FSystem*               fsystem;
    static FTermDetection*        term_detection;
    static CursorStyle            linux_console_cursor_style;
    static console_font_op        screen_font;
    static unimapdesc             screen_unicode_map;
    static ColorMap               saved_color_map;
    static ColorMap               cmap;
    static int                    framebuffer_bpp;
#endif  // defined(__linux__)
};
#pragma pack(pop)

// FTermLinux inline functions
//----------------------------------------------------------------------
inline const char* FTermLinux::getClassName() const
{ return "FTermLinux"; }

//----------------------------------------------------------------------
#if defined(__linux__)
inline int FTermLinux::getFramebufferBpp()
{ return framebuffer_bpp; }

//----------------------------------------------------------------------
inline bool FTermLinux::isVGAFontUsed()
{ return vga_font; }

//----------------------------------------------------------------------
inline bool FTermLinux::isNewFontUsed()
{ return new_font; }
#endif  // defined(__linux__)

}  // namespace finalcut

#endif  // FTERMLINUX_H
